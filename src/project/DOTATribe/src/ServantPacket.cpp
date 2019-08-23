//Name:ServantPacket
//Function: 仆从系统
//Author:方骏
//Date:20131015

#include <cocos2d.h>
#include "../include/ServantPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/ServantDataHandler.h"
#include "../include/TimeSystem.h"


/************************************************************************/
/* 奴隶主抓捕     2113                                                      */
/************************************************************************/
CSMasterCatchPacket::CSMasterCatchPacket(int serialId, int playerId)
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
	m_serialId = serialId;
	m_iPlayerId = playerId;
}

CSMasterCatchPacket::~CSMasterCatchPacket()
{

}

unsigned  int  CSMasterCatchPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_MASTER_CATCH_;
}

unsigned int CSMasterCatchPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_serialId) + sizeof(m_iPlayerId);
}
void CSMasterCatchPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_serialId);
	pNode->push(m_iPlayerId);
	NETSYSTEM->SendPacket(pNode);
}

/************************************************************************/
/* 奴隶主进入抓捕        2115,2116                                                             */
/************************************************************************/

CSMasterEnterCatchPacket::CSMasterEnterCatchPacket()
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}
CSMasterEnterCatchPacket::~CSMasterEnterCatchPacket()
{

}
unsigned  int  CSMasterEnterCatchPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_MASTER_ENTER_CATCH_;
}
unsigned  int  CSMasterEnterCatchPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_len) + sizeof(m_pn);
}
void  CSMasterEnterCatchPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	NETSYSTEM->SendPacket(pNode);
}

unsigned  int  SCMasterEnterCatchResultPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_MASTER_ENTER_CATCH_RESULT_;
}

bool  SCMasterEnterCatchResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	if(SERVANTDATAHANDLER->m_pSMCatchInfo == NULL)
	{
		SERVANTDATAHANDLER->m_pSMCatchInfo = new SMCatchInfo();
	}
	SERVANTDATAHANDLER->m_pSMCatchInfo->decodePacketData(packet);

	SERVANTDATAHANDLER->m_pSMCatchInfo->longTickBeginTime = TimeSystem::get_instance2()->GetCurrentMicroSecond();//记录获取包时的时间
	return true;
}

unsigned  int  SCMasterEnterCatchResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_MASTER_ENTER_CATCH_RESULT_;
}

bool  SCMasterEnterCatchResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCMasterEnterCatchResultPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	SERVANTDATAHANDLER->ToClientMasterEnterCatchResult();

	return true;
}


/************************************************************************/
/* 奴隶主进入互动      2117,2118                                        */
/************************************************************************/

CSMasterEnterPlayPacket::CSMasterEnterPlayPacket()
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}
CSMasterEnterPlayPacket::~CSMasterEnterPlayPacket()
{

}
unsigned  int  CSMasterEnterPlayPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_MASTER_ENTER_PLAY_;
}
unsigned  int  CSMasterEnterPlayPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_len) + sizeof(m_pn);
}
void  CSMasterEnterPlayPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	NETSYSTEM->SendPacket(pNode);
}

unsigned  int  SCMasterEnterPlayResultPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_MASTER_ENTER_PLAY_RESULT_;
}

bool  SCMasterEnterPlayResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	if(!SERVANTDATAHANDLER->m_pSMPlayInfo)
	{
		SERVANTDATAHANDLER->m_pSMPlayInfo = new SMPlayInfo();
	}
	SERVANTDATAHANDLER->m_pSMPlayInfo->decodePacketData(packet);


	SERVANTDATAHANDLER->m_pSMPlayInfo->longTickBeginTime = TimeSystem::get_instance2()->GetCurrentMicroSecond();//记录获取包时的时间
	SERVANTDATAHANDLER->m_pSMPlayInfo->secondsCount = 0;

	return true;
}

unsigned  int  SCMasterEnterPlayResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_MASTER_ENTER_PLAY_RESULT_;
}

bool  SCMasterEnterPlayResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCMasterEnterPlayResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	SERVANTDATAHANDLER->ToClientMasterEnterPlayResult();

	return true;
}


/************************************************************************/
/* 奴隶主互动      2119,2120                                                 */
/************************************************************************/

CSMasterPlayPacket::CSMasterPlayPacket(char type, char index)
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
	m_cType = type;
	m_cIndex = index;
}
CSMasterPlayPacket::~CSMasterPlayPacket()
{

}
unsigned  int  CSMasterPlayPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_MASTER_PLAY_;
}
unsigned  int  CSMasterPlayPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_cType) + sizeof(m_cIndex);
}
void  CSMasterPlayPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_cType);
	pNode->push(m_cIndex);
	NETSYSTEM->SendPacket(pNode);
}

unsigned  int  SCMasterPlayResultPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_MASTER_PLAY_RESULT_;
}
bool  SCMasterPlayResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	char type = -1;
	char index = -1;
	int cdlefttime = -1;

	packet>>type;
	packet>>index;
	packet>>cdlefttime;

	SERVANTDATAHANDLER->ToClientMasterPlayResult(type, index, cdlefttime);

	return true;
}

unsigned  int  SCMasterPlayResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_MASTER_PLAY_RESULT_;
}

bool  SCMasterPlayResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCMasterPlayResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	return true;
}

/************************************************************************/
/* 奴隶主新闻推送      2122                                                 */
/************************************************************************/
unsigned  int SCMasterNewsPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_MASTER_NEWS_;
}

bool  SCMasterNewsPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	if(SERVANTDATAHANDLER->m_pSNewsInfo == NULL)
	{
		SERVANTDATAHANDLER->m_pSNewsInfo = new SNewsInfo();
	}

	SERVANTDATAHANDLER->m_pSNewsInfo->decodePacketData(packet);

	return true;
}

unsigned  int  SCMasterNewsPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_MASTER_NEWS_;
}

bool  SCMasterNewsPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCMasterNewsPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	SERVANTDATAHANDLER->ToClientMasterNewsCome();

	return true;
}

/************************************************************************/
/* 奴隶主进入解救      2123,2124                                            */
/************************************************************************/

CSMasterEnterRescuePacket::CSMasterEnterRescuePacket()
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}
CSMasterEnterRescuePacket::~CSMasterEnterRescuePacket()
{

}

unsigned  int  CSMasterEnterRescuePacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_MASTER_ENTER_RESCUE_;
}
unsigned  int  CSMasterEnterRescuePacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_len) + sizeof(m_pn);
}

void  CSMasterEnterRescuePacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	NETSYSTEM->SendPacket(pNode);
}

unsigned  int  SCMasterEnterRescueResultPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_MASTER_ENTER_RESCUE_RESULT_;
}
bool  SCMasterEnterRescueResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	if(!SERVANTDATAHANDLER->m_pSMRescueInfo)
	{
		SERVANTDATAHANDLER->m_pSMRescueInfo = new SMRescueInfo();
	}
	SERVANTDATAHANDLER->m_pSMRescueInfo->decodePacketData(packet);

	return true;
}

unsigned  int  SCMasterEnterRescueResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_MASTER_ENTER_RESCUE_RESULT_;
}

bool  SCMasterEnterRescueResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCMasterEnterRescueResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	SERVANTDATAHANDLER->ToClientMasterEnterRescueResult();

	return true;
}


/************************************************************************/
/* 奴隶主解救好友      2125                                            */
/************************************************************************/
CSMasterRescuePacket::CSMasterRescuePacket(int serialId, int playerId)
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
	m_serialId = serialId;
	m_iPlayerId = playerId;
}
CSMasterRescuePacket::~CSMasterRescuePacket()
{

}

unsigned  int  CSMasterRescuePacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_MASTER_RESCUE_;
}
unsigned  int  CSMasterRescuePacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_serialId) + sizeof(m_iPlayerId);
}
void  CSMasterRescuePacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_serialId);
	pNode->push(m_iPlayerId);
	NETSYSTEM->SendPacket(pNode);
}

/************************************************************************/
/* 奴隶进入反抗      2127,2128                                            */
/************************************************************************/
CSSlaveEnterRevoltPacket::CSSlaveEnterRevoltPacket()
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}
CSSlaveEnterRevoltPacket::~CSSlaveEnterRevoltPacket()
{

}
unsigned  int  CSSlaveEnterRevoltPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_SLAVE_ENTER_REVOLT_;
}
unsigned  int  CSSlaveEnterRevoltPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len);
}
void  CSSlaveEnterRevoltPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	NETSYSTEM->SendPacket(pNode);
}

unsigned  int  SCSlaveEnterRevoltResultPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_SLAVE_ENTER_REVOLT_RESULT_;
}
bool  SCSlaveEnterRevoltResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	if(SERVANTDATAHANDLER->m_pSSRevoltInfo == NULL)
	{
		SERVANTDATAHANDLER->m_pSSRevoltInfo = new SSRevoltInfo();
	}
	SERVANTDATAHANDLER->m_pSSRevoltInfo->decodePacketData(packet);

	return true;
}
unsigned  int  SCSlaveEnterRevoltResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_SLAVE_ENTER_REVOLT_RESULT_;
}
bool  SCSlaveEnterRevoltResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCSlaveEnterRevoltResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	SERVANTDATAHANDLER->ToClientSlaveEnterRevoltResult();

	return true;
}


/************************************************************************/
/* 奴隶贿赂      2129,2130                                            */
/************************************************************************/
CSSlaveBribePacket::CSSlaveBribePacket()
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}
CSSlaveBribePacket::~CSSlaveBribePacket()
{

}
unsigned  int  CSSlaveBribePacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_SLAVE_BRIBE_;
}
unsigned  int  CSSlaveBribePacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len);
}

void  CSSlaveBribePacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	NETSYSTEM->SendPacket(pNode);
}

unsigned  int  SCSlaveBribeResultPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_SLAVE_BRIBE_RESULT_;
}
bool  SCSlaveBribeResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	//nothing to read

	return true;
}
unsigned  int  SCSlaveBribeResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_SLAVE_BRIBE_RESULT_;
}
bool  SCSlaveBribeResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCSlaveBribeResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	SERVANTDATAHANDLER->ToClientSlaveBribeResult();

	return true;
}


/************************************************************************/
/* 奴隶反抗      2131	                                            */
/************************************************************************/
CSSlaveRevoltPacket::CSSlaveRevoltPacket(int serialId)
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
	m_serialId = serialId;
}
CSSlaveRevoltPacket::~CSSlaveRevoltPacket()
{

}
unsigned  int  CSSlaveRevoltPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_SLAVE_REVOLT_;
}
unsigned  int  CSSlaveRevoltPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_serialId);
}
void  CSSlaveRevoltPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_serialId);
	NETSYSTEM->SendPacket(pNode);
}


/************************************************************************/
/* 奴隶进入互动      2141,2142                                            */
/************************************************************************/
CSSlaveEnterPlayPacket::CSSlaveEnterPlayPacket()
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}
CSSlaveEnterPlayPacket::~CSSlaveEnterPlayPacket()
{

}
unsigned  int  CSSlaveEnterPlayPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_SLAVE_ENTER_PLAY_;
}
unsigned  int  CSSlaveEnterPlayPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len);
}
void  CSSlaveEnterPlayPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	NETSYSTEM->SendPacket(pNode);
}

unsigned  int  SCSlaveEnterPlayResultPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_SLAVE_ENTER_PLAT_RESULT_;
}
bool  SCSlaveEnterPlayResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	if(!SERVANTDATAHANDLER->m_pSSPlayInfo)
	{
		SERVANTDATAHANDLER->m_pSSPlayInfo = new SSPlayInfo();
	}
	SERVANTDATAHANDLER->m_pSSPlayInfo->decodePacketData(packet);

	return true;
}
unsigned  int  SCSlaveEnterPlayResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_SLAVE_ENTER_PLAT_RESULT_;
}
bool  SCSlaveEnterPlayResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCSlaveEnterPlayResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	SERVANTDATAHANDLER->ToClientSlaveEnterPlayResult();

	return true;
}


/************************************************************************/
/* 奴隶互动      2133,2134                                            */
/************************************************************************/
CSSlavePlayPacket::CSSlavePlayPacket()
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}
CSSlavePlayPacket::~CSSlavePlayPacket()
{

}
unsigned  int  CSSlavePlayPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_SLAVE_PLAY_;
}
unsigned  int  CSSlavePlayPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len);
}
void  CSSlavePlayPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	NETSYSTEM->SendPacket(pNode);
}

unsigned  int  SCSlavePlayResultPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_SLAVE_PLAY_RESULT_;
}
bool  SCSlavePlayResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	//nothing to read.

	return true;
}
unsigned  int  SCSlavePlayResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_SLAVE_PLAY_RESULT_;
}
bool  SCSlavePlayResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCSlavePlayResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	SERVANTDATAHANDLER->ToClientSlavePlayResult();

	return true;
}


/************************************************************************/
/* 奴隶新闻推送      2136		                                        */
/************************************************************************/
unsigned  int  SCSlaveNewsPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_SLAVE_NEWS_;
}
bool SCSlaveNewsPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	if(SERVANTDATAHANDLER->m_pSNewsInfo == NULL)
	{
		SERVANTDATAHANDLER->m_pSNewsInfo = new SNewsInfo();
	}

	SERVANTDATAHANDLER->m_pSNewsInfo->decodePacketData(packet);

	return true;
}
unsigned  int  SCSlaveNewsPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_SLAVE_NEWS_;
}
bool  SCSlaveNewsPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCSlaveNewsPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	SERVANTDATAHANDLER->ToClientSlaveNewsCome();

	return true;
}


/************************************************************************/
/* 奴隶进入求救      2137,2138                                            */
/************************************************************************/
CSSlaveEnterSOSPacket::CSSlaveEnterSOSPacket()
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
}
CSSlaveEnterSOSPacket::~CSSlaveEnterSOSPacket()
{

}
unsigned  int  CSSlaveEnterSOSPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_SLAVE_ENTER_SOS_;
}
unsigned  int  CSSlaveEnterSOSPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len);
}
void  CSSlaveEnterSOSPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	NETSYSTEM->SendPacket(pNode);
}

unsigned  int  SCSlaveEnterSOSResultPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_SLAVE_ENTER_SOS_RESULT_;
}
bool  SCSlaveEnterSOSResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	if(!SERVANTDATAHANDLER->m_pSSSOSInfo)
	{
		SERVANTDATAHANDLER->m_pSSSOSInfo = new SSSOSInfo();
	}
	SERVANTDATAHANDLER->m_pSSSOSInfo->decodePacketData(packet);

	return true;
}
unsigned  int  SCSlaveEnterSOSResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_SLAVE_ENTER_SOS_RESULT_;
}
bool  SCSlaveEnterSOSResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCSlaveEnterSOSResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	SERVANTDATAHANDLER->ToClientSlaveEnterSOSResult();

	return true;
}


/************************************************************************/
/* 奴隶求救好友      2139                                            */
/************************************************************************/
CSSlaveSOSPacket::CSSlaveSOSPacket(int serialId, int playerId)
{
	m_head[0] = 'Z';
	m_head[1] = 'R';
	m_pn = GetPacketType();
	m_len = GetPacketLength();
	m_serialId = serialId;
	m_iPlayerId = playerId;
}
CSSlaveSOSPacket::~CSSlaveSOSPacket()
{

}
unsigned  int  CSSlaveSOSPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_SLAVE_SOS_;
}
unsigned  int  CSSlaveSOSPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_serialId) + sizeof(m_iPlayerId);
}
void  CSSlaveSOSPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_serialId);
	pNode->push(m_iPlayerId);
	NETSYSTEM->SendPacket(pNode);
}

