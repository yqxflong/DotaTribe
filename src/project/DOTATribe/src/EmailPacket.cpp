//Name：EmailPacket
//Function：邮件相关包
//Written By：尹强

#include <cocos2d.h>
#include "../include/EmailPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include <include/mem/DPacket.h>
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include <list>
#include "../include/LoggerSystem.h"

/************************************************************************/
/* 玩家邮件信息请求<br>				                     */
/************************************************************************/

CSEmailListPacket::CSEmailListPacket()
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}

unsigned  int  CSEmailListPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_EMAILLIST_;
}

unsigned  int CSEmailListPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) ;
}

void  CSEmailListPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	NETSYSTEM->SendPacket(pNode);
}
/*
	玩家邮件信息返回<br>		
*/
unsigned  int  SCEmailListPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_EMAILLIST_;
}

unsigned  int  SCEmailListPacket::GetPacketLength()
{
	return sizeof(1);
}

bool  SCEmailListPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer,iLen);
	packet.read(m_head, 2);
	packet>>m_len;
	packet>>m_pn;
	EMAILDATAHANDLER->decodePacketData(packet);
	EMAILDATAHANDLER->FeedBack_QueryEmail();
	return true;
}
/*
	接收任务列表工厂
*/
unsigned int SCEmailListPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_EMAILLIST_;
}

bool SCEmailListPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCEmailListPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	return true;
}

/************************************************************************/
/* 发送邮件请求<br>												    */
/************************************************************************/

CSEmailSendPacket::CSEmailSendPacket(EmailWriteData* emailData)
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();	
	m_dataEmailSend = emailData;
	m_len = GetPacketLength();
}

unsigned  int  CSEmailSendPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_EMAILSEND_;
}

unsigned  int  CSEmailSendPacket::GetPacketLength()
{
	unsigned int size1=sizeof(m_head) + sizeof(m_pn) + sizeof(m_len);
	unsigned int size2=sizeof(m_dataEmailSend->id_)+sizeof(unsigned short)+m_dataEmailSend->targetName_.length()+sizeof(unsigned short)+m_dataEmailSend->title_.length()+sizeof(unsigned short)+m_dataEmailSend->content_.length()+sizeof(m_dataEmailSend->attachmentCount_);
	unsigned int size3=0;
	std::list<EmailWriteDataObject*>::iterator it=m_dataEmailSend->attlist_.begin();
	std::list<EmailWriteDataObject*>::iterator it_end=m_dataEmailSend->attlist_.end();
	for (;it!=it_end;it++)
	{
		size3+=(*it)->type_;
		size3+=(*it)->amount_;
		size3+=(*it)->itemId_;
		size3+=(*it)->templateId_;
	}
	return size1+size2+size3;
}

void  CSEmailSendPacket::Send()
{
	unsigned short stringSize = 0;
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	char *buff = NULL;
	char *buff1 = NULL;
	char *buff2 = NULL;
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_dataEmailSend->id_);
//~TargetName
	stringSize=m_dataEmailSend->targetName_.length();
	buff = const_cast<char*>(m_dataEmailSend->targetName_.c_str());
	pNode->push(stringSize);
	pNode->push(buff,stringSize);
//~Title
	stringSize=m_dataEmailSend->title_.length();
	buff1 = const_cast<char*>(m_dataEmailSend->title_.c_str());
	pNode->push(stringSize);
	pNode->push(buff1,stringSize);
//~Content
	stringSize=m_dataEmailSend->content_.length();
	buff2 = const_cast<char*>(m_dataEmailSend->content_.c_str());
	pNode->push(stringSize);
	pNode->push(buff2,stringSize);

//~~~
	pNode->push(m_dataEmailSend->attachmentCount_);
	std::list<EmailWriteDataObject*>::iterator it=m_dataEmailSend->attlist_.begin();
	std::list<EmailWriteDataObject*>::iterator it_end=m_dataEmailSend->attlist_.end();
	for (;it!=it_end;it++)
	{
		pNode->push((*it)->type_);
		pNode->push((*it)->amount_);
		pNode->push((*it)->itemId_);
		pNode->push((*it)->templateId_);
	}
	NETSYSTEM->SendPacket(pNode);
}
/*
	发送邮件反馈
*/
unsigned  int  SCEmailSendPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_EMAILSEND_;
}

unsigned  int  SCEmailSendPacket::GetPacketLength()
{
	//no need
	return sizeof(0);
}

bool  SCEmailSendPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head, 2);
	packet>>m_len;
	packet>>m_pn;
	packet>>m_result;
	if (m_result==0)
		EMAILDATAHANDLER->FeedBack_WriteEmail(true);
	else if(m_result==1)
		EMAILDATAHANDLER->FeedBack_WriteEmail(false);
	return true;
}

/*
	发送邮件反馈工厂
*/
unsigned  int  SCEmailSendPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_EMAILSEND_;
}

bool  SCEmailSendPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCEmailSendPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	return true;
}

/************************************************************************/
/* 提取邮件附件请求<br>																	  */
/************************************************************************/

CSGetEmailAttPacket::CSGetEmailAttPacket(int emailID)
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
	m_nEmailID=emailID;
}

unsigned  int  CSGetEmailAttPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_EMAILGETATT_;
}

unsigned  int  CSGetEmailAttPacket::GetPacketLength()
{
	unsigned int size1=sizeof(m_head) + sizeof(m_pn) + sizeof(m_len)+sizeof(m_nEmailID);
	return size1;
}

void  CSGetEmailAttPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_nEmailID);
	NETSYSTEM->SendPacket(pNode);
}
/*
	提取邮件附件返回<br>
*/
unsigned  int  SCGetEmailAttPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_EMAILGETATT_;
}

unsigned  int  SCGetEmailAttPacket::GetPacketLength()
{
	//no need
	return sizeof(0);
}

bool  SCGetEmailAttPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head, 2);
	packet>>m_len;
	packet>>m_pn;
	packet>>m_result;
	if (m_result==0)
		EMAILDATAHANDLER->FeedBack_GetATT(true);
	else if(m_result=1)
		EMAILDATAHANDLER->FeedBack_GetATT(false);
	return true;
}

/*
	提取邮件附件返回工厂<br>
*/
unsigned  int  SCGetEmailAttPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_EMAILGETATT_;
}

bool  SCGetEmailAttPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCGetEmailAttPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	return true;
}

/************************************************************************/
/* 删除邮件请求<br>																  */
/************************************************************************/

CSRemoveEmailPacket::CSRemoveEmailPacket(int emailID)
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
	m_nEmailID=emailID;
}

unsigned  int  CSRemoveEmailPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_EMAILREMOVE_;
}

unsigned  int  CSRemoveEmailPacket::GetPacketLength()
{
	unsigned int size1=sizeof(m_head) + sizeof(m_pn) + sizeof(m_len)+sizeof(m_nEmailID);
	return size1;
}

void  CSRemoveEmailPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_nEmailID);
	NETSYSTEM->SendPacket(pNode);
}
/*
	* 删除邮件请求返回 <br>
*/
unsigned  int  SCRemoveEmailPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_EMAILREMOVE_;
}

unsigned  int  SCRemoveEmailPacket::GetPacketLength()
{
	//no need
	return sizeof(0);
}

bool  SCRemoveEmailPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head, 2);
	packet>>m_len;
	packet>>m_pn;
	packet>>m_result;
	if (m_result==0)
		EMAILDATAHANDLER->FeedBack_RemoveEmail(true);
	else if(m_result=1)
		EMAILDATAHANDLER->FeedBack_RemoveEmail(false);
	return true;
}

/*
	提取邮件附件返回工厂<br>
*/
unsigned  int  SCRemoveEmailPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_EMAILREMOVE_;
}

bool  SCRemoveEmailPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCRemoveEmailPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	return true;
}

/************************************************************************/
/* 查看邮件																*/
/************************************************************************/
CSCheckEmailPacket::CSCheckEmailPacket(int emailID)
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
	m_nEmailID=emailID;
}

unsigned  int  CSCheckEmailPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_CHECK_EMAIL_;
}

unsigned  int  CSCheckEmailPacket::GetPacketLength()
{
	unsigned int size1=sizeof(m_head) + sizeof(m_pn) + sizeof(m_len)+sizeof(m_nEmailID);
	return size1;
}

void  CSCheckEmailPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_nEmailID);
	NETSYSTEM->SendPacket(pNode);
}
/*
* 查看邮件返回结果 <br>
*/
unsigned  int  SCCheckEmailPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_CHECK_EMAIL_RESULT;
}

unsigned  int  SCCheckEmailPacket::GetPacketLength()
{
	//no need
	return sizeof(0);
}

bool  SCCheckEmailPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head, 2);
	packet>>m_len;
	packet>>m_pn;

	EMAILDATAHANDLER->ReceiveCheckEmailInfo(packet);

	return true;
}

/*
	提取邮件附件返回工厂<br>
*/
unsigned  int  SCCheckEmailPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_CHECK_EMAIL_RESULT;
}

bool  SCCheckEmailPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCCheckEmailPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;


	return true;
}


/************************************************************************/
/* 收取所有邮件附件	C->S												*/
/************************************************************************/

CSGetAllMailPacket::CSGetAllMailPacket(){

}

CSGetAllMailPacket::~CSGetAllMailPacket(){

}

unsigned int CSGetAllMailPacket::GetPacketType(){
	return 0;
}

/************************************************************************/
/* 收取所有邮件附件	S->C												*/
/************************************************************************/

unsigned int SCGetAllMailPacket::GetPacketLength(){
	return sizeof(0);
}
unsigned int SCGetAllMailPacket::GetPacketType(){
	return 0;
}

bool SCGetAllMailPacket::Read(char* pBuffer,unsigned int iLen){

	return true;
}

/************************************************************************/
/* 收取所有邮件附件	Factory												*/
/************************************************************************/

unsigned int SCGetAllMailPacketFactory::GetPacketType(){
	return 0;
}

bool SCGetAllMailPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen){

	return true;
}

