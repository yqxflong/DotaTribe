//Name：LoginPakcet
//Function：登陆相关包
//Written By：尹强

#include "../include/LoginPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/LimitedActivityHandler.h"

using namespace std;
using  namespace  cobra_win;

//##########################客户端激活包##################//
CSClientActivePacket::CSClientActivePacket(std::string version,int accType,std::string deviceID,std::string macAddr){
	PushData(version);
	PushData(accType);
	PushData(deviceID);
	PushData(macAddr);
}

unsigned  int  CSClientActivePacket::GetPacketType(){
	return _TYPED_PACKET_C2S_CLIENT_ACTIVE_;
}




//#################平台登陆返回后发送登陆包################
CSLoginPacket::CSLoginPacket(LoginParams params){
	m_Params=params;
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_len=GetPacketLength();
};

unsigned  int  CSLoginPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_LOGIN_P_;
}

unsigned  int  CSLoginPacket::GetPacketLength()
{
	unsigned int length=sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(unsigned short)+m_Params.clientType_.length()
		+sizeof(unsigned short)+m_Params.deviceId_.length()+sizeof(m_Params.channelId_)+sizeof(unsigned short)+m_Params.deviceSystem_.length()
		+sizeof(unsigned short)+m_Params.MACAddress_.length()+sizeof(unsigned short)+m_Params.version_.length()
		+sizeof(unsigned short)+m_Params.telecomOperator_.length()+sizeof(unsigned short)+m_Params.AppendParam_.length()
		+sizeof(m_Params.isHacked_)
		+ m_Params.sdkParam.PacketLength()
		+ m_Params.gameParam.PacketLength();

	return length;
}

void  CSLoginPacket::Send()
{
	unsigned short stringSize = 0;
	char *buff ="";
	MemNode* pNode = NETSYSTEM->QueryMemNode(m_len);
	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
//~clientType
	stringSize=m_Params.clientType_.length();
	buff = const_cast<char*>(m_Params.clientType_.c_str());
	pNode->push(stringSize);
	pNode->push(buff,stringSize);
//~deviceId
	stringSize=m_Params.deviceId_.length();
	buff = const_cast<char*>(m_Params.deviceId_.c_str());
	pNode->push(stringSize);
	pNode->push(buff,stringSize);
//~channelId 
	pNode->push(m_Params.channelId_);
//~deviceSystem 
	stringSize=m_Params.deviceSystem_.length();
	buff = const_cast<char*>(m_Params.deviceSystem_.c_str());
	pNode->push(stringSize);
	pNode->push(buff,stringSize);
//~MACAddress
	stringSize=m_Params.MACAddress_.length();
	buff = const_cast<char*>(m_Params.MACAddress_.c_str());
	pNode->push(stringSize);
	pNode->push(buff,stringSize);
//~version
	stringSize=m_Params.version_.length();
	buff = const_cast<char*>(m_Params.version_.c_str());
	pNode->push(stringSize);
	pNode->push(buff,stringSize);
//~telecomOperator 
	stringSize=m_Params.telecomOperator_.length();
	buff = const_cast<char*>(m_Params.telecomOperator_.c_str());
	pNode->push(stringSize);
	pNode->push(buff,stringSize);
//~AppendParam 
	stringSize=m_Params.AppendParam_.length();
	buff = const_cast<char*>(m_Params.AppendParam_.c_str());
	pNode->push(stringSize);
	pNode->push(buff,stringSize);
//~isHacked 
	pNode->push(m_Params.isHacked_);

	//平台登陆数据
	m_Params.sdkParam.SendParam(pNode);
	//游戏登陆数据
	m_Params.gameParam.SendParam(pNode);
	NETSYSTEM->SendPacket(pNode);
}

//#################平台登陆返回后发送登陆包################
unsigned  int  SCLoginPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_LOGIN_P_;
}

unsigned  int  SCLoginPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  SCLoginPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	packet>>result_;

	return true;
}

unsigned  int SCLoginPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_LOGIN_P_;
}

bool SCLoginPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCLoginPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	SERVERINFODATAINFO->HandleAfterLogin(packet.result_);
	return true;
}


//#################通知强行断开连接################
unsigned  int  SCForceDisConnectPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_FORCEDISCONNECT_;
}

unsigned  int  SCForceDisConnectPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  SCForceDisConnectPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	return true;
}

unsigned  int SCForceDisConnectPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_FORCEDISCONNECT_;
}

bool SCForceDisConnectPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCForceDisConnectPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	SERVERINFODATAINFO->ForceDisconnect();
	return true;
}

//#################登陆公告Request################
CSNoticePacket::CSNoticePacket(){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_len=GetPacketLength();
}

unsigned  int  CSNoticePacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_LOGINNOTICE_;
}

unsigned  int  CSNoticePacket::GetPacketLength()
{
	unsigned int length=sizeof(m_head)+sizeof(m_len)+sizeof(m_pn);
	return length;
}

void  CSNoticePacket::Send()
{
	unsigned short stringSize = 0;
	MemNode* pNode = NETSYSTEM->QueryMemNode(m_len);
	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	NETSYSTEM->SendPacket(pNode);
}

//#################登陆公告Resp################
/**
    * 登陆公告返回<br>
    * string content 内容<br>
*/
unsigned  int SCNoticePacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_LOGINNOTICE_;
}

unsigned  int  SCNoticePacket::GetPacketLength()
{
	return sizeof(int);
}

bool  SCNoticePacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

//读取内容
	/*unsigned short tmpLen=0;
	char *tmpChar = 0;
	packet>>tmpLen;
	tmpChar=new char[tmpLen+1];
	packet.read(tmpChar,tmpLen);
	tmpChar[tmpLen]='\0';
	content_=tmpChar;
	delete [] tmpChar;tmpChar=0;*/
	LimitedActivityHandler::get_instance2()->decodePacketData_Notice(packet);


	return true;
}

unsigned  int SCNoticePacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_LOGINNOTICE_;
}

bool SCNoticePacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCNoticePacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
	SERVERINFODATAINFO->HandleAfterLoginNoticeResp(packet.content_);
	return true;
}