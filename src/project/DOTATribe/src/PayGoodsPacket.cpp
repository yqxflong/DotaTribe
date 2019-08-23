//Name:PayGoodsPacket
//Function: ��ֵ����Ʒ�����Э��
//Author:lvyunlong
//Date:20131119

#include <cocos2d.h>
#include "../include/PayGoodsPacket.h"
#include "../include/PacketTyper.h"
#include <include/mem/DPacket.h>
#include "../include/LoggerSystem.h"
#include  "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include <include/mem/MemNode.h>
#include "../include/NFControlsManager.h"
#include "../include/PayGoodsControlDataHandler.h"

/************************************************************************/
/* �����ֵ�б�ͷ���	                                                    */
/************************************************************************/
CSPayItemListPacket::CSPayItemListPacket(unsigned char channel)
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_ChannelId = channel;
	m_len = GetPacketLength();
}

CSPayItemListPacket::~CSPayItemListPacket()
{

}

unsigned  int  CSPayItemListPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_PAYITEMLIST_CLIENT_;
}

unsigned  int  CSPayItemListPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_ChannelId) + sizeof(m_len);
}

void  CSPayItemListPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_ChannelId);
	NETSYSTEM->SendPacket(pNode);
}


unsigned  int  SCPayItemListPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_PAYITEMLIST_RESULT_;
}

unsigned  int  SCPayItemListPacket::GetPacketLength()
{
	return sizeof(int);
}


bool  SCPayItemListPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	_readInfo(packet);
	return true;
}
void SCPayItemListPacket::_readInfo(cobra_win::DPacket &packet)
{
	PAYGOODSCONTROLDATAHANDLER->ClearPayItemList();
	packet>>PAYGOODSCONTROLDATAHANDLER->m_GoodsCount;

	unsigned int count = PAYGOODSCONTROLDATAHANDLER->m_GoodsCount;
    PAYGOODSCONTROLDATAHANDLER->ClearPayItemList();
	unsigned int index = 0;
	for (index;index<count;index++)
	{
		PayGoodsData* temp = new PayGoodsData();
		temp->decodeTemplatePacketData(packet);
		PAYGOODSCONTROLDATAHANDLER->m_PayGoodsList.push_back(temp);
	}
}

unsigned  int  SCPayItemListPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_PAYITEMLIST_RESULT_;
}

bool  SCPayItemListPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCPayItemListPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	//ˢ�³�ֵ�����б�
	//EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_RECHARGEWINDOW_);
	PAYGOODSCONTROLDATAHANDLER->m_isBPaylist = true;

	return true;
}
/************************************************************************/
/* �����ֵȷ�Ϻͳ�ֵȷ�Ͻ������											*/
/************************************************************************/
CSPaySurePacket::CSPaySurePacket(unsigned char channel,std::string iapid,std::string orderld,std::string transactReceipt)
{	
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_ChannelId = channel;

	sizegoodsiap = iapid.length();
	m_striapid = iapid;
	sizeOrderld = orderld.length();
	m_strOrderld = orderld;
	sizetransactReceipt = transactReceipt.length();
	m_strtransactReceipt = transactReceipt;

	m_len = GetPacketLength();
}

CSPaySurePacket::~CSPaySurePacket()
{

}

unsigned  int  CSPaySurePacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_PAYCHECK_CLIENT_;
}

unsigned  int  CSPaySurePacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_ChannelId) + sizeof(sizegoodsiap) + sizeof(sizeOrderld) + sizeof(sizetransactReceipt) + sizeof(m_len) + m_striapid.length()+ m_strOrderld.length() + m_strtransactReceipt.length();
}

void  CSPaySurePacket::Send()
{
	unsigned short stringSize = 0;
	char* pBuff = NULL;
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_ChannelId);

	stringSize = sizegoodsiap;
	pBuff = const_cast<char*>(m_striapid.c_str());
	pNode->push(stringSize);
	pNode->push(pBuff,stringSize);
	pBuff = NULL;

	stringSize = sizeOrderld;
	pBuff = const_cast<char*>(m_strOrderld.c_str());
	pNode->push(stringSize);
	pNode->push(pBuff,stringSize);
	pBuff = NULL;

	stringSize = sizetransactReceipt;
	pBuff = const_cast<char*>(m_strtransactReceipt.c_str());
	pNode->push(stringSize);
	pNode->push(pBuff,stringSize);

	NETSYSTEM->SendPacket(pNode);
}

unsigned  int  SCPaySurePacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_PAYCHECK_RESULT_;
}

unsigned  int  SCPaySurePacket::GetPacketLength()
{
	return sizeof(int);
}


bool  SCPaySurePacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	_readInfo(packet);
	return true;
}
void SCPaySurePacket::_readInfo(cobra_win::DPacket &packet)
{
	//�����ֵȷ�Ϸ���
	/*
		���ǳ�ֵ��� ֮���Ƕ�����
	*/
	unsigned short tmp_len = 0;
	char * tmpChar = NULL;

	//��ʱ����ȷ�϶������������صĶ���
	packet>>tmp_len;
	tmpChar = new char[tmp_len +1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len] = '\0';
	PAYGOODSCONTROLDATAHANDLER->m_strTempOrderld.assign(tmpChar);
	delete []tmpChar;
	tmpChar = NULL;
	//ȷ�϶������������صĶ���״̬
	packet>>PAYGOODSCONTROLDATAHANDLER->m_aSureOrderldState;
}

unsigned  int  SCPaySurePacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_PAYCHECK_RESULT_;
}

bool  SCPaySurePacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCPaySurePacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	//��������������
	PAYGOODSCONTROLDATAHANDLER->SureServerOrederBack(PAYGOODSCONTROLDATAHANDLER->m_strTempOrderld,PAYGOODSCONTROLDATAHANDLER->m_aSureOrderldState);
	return true;
}

/************************************************************************/
/* Androidר�ù���ʱ����													*/
/************************************************************************/
CSAndroidPayInfoPacket::CSAndroidPayInfoPacket()
{	
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}

CSAndroidPayInfoPacket::~CSAndroidPayInfoPacket()
{

}

unsigned  int  CSAndroidPayInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_PAYADDITION_;
}

unsigned  int  CSAndroidPayInfoPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len);
}

void  CSAndroidPayInfoPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	NETSYSTEM->SendPacket(pNode);
}

unsigned  int  SCAndroidPayInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_PAYADDITION_RESULT_;
}

unsigned  int  SCAndroidPayInfoPacket::GetPacketLength()
{
	return sizeof(int);
}


bool  SCAndroidPayInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	_readInfo(packet);
	return true;
}
void SCAndroidPayInfoPacket::_readInfo(cobra_win::DPacket &packet)
{
	PAYGOODSCONTROLDATAHANDLER->ReadPayAddtionPacketData(packet);
}

unsigned  int  SCAndroidPayInfoPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_PAYADDITION_RESULT_;
}

bool  SCAndroidPayInfoPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCAndroidPayInfoPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_ADDTIONPAYWINDOW_);   
	NFC_showCommunicationWating(false);
	return true;
}

/************************************************************************/
/* �����׳�����������Ϣ													*/
/************************************************************************/
CSDoublePayInfoPacket::CSDoublePayInfoPacket(unsigned char channel)
{
    PushData(channel);
}

CSDoublePayInfoPacket::~CSDoublePayInfoPacket()
{	

}

unsigned  int  CSDoublePayInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_DOUBLE_PAY_INFO_;
}

bool  SCDoublePayInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//Vip������Ϣ
	PAYGOODSCONTROLDATAHANDLER->ReadDoublePayInfoData(packet);
	return true;
}

unsigned  int  SCSCDoublePayInfoPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_DOUBLE_PAY_INFO_RESULT_;
}

bool  SCSCDoublePayInfoPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCDoublePayInfoPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;
	//Refresh UI

	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_DOUBLE_RECHARGEWINDOW_);

	return true;
}
