//Name:BoseScorePacket.h
//Function:Boss积分系统
//Author:fangjun
//date:20140217

#include "../include/BossScorePacket.h"
#include "../include/PacketTyper.h"
#include <include/mem/MemNode.h>
#include <include/mem/DPacket.h>
#include "../include/BossScoreDataHandler.h"
#include "../include/TimeSystem.h"

/************************************************************************/
/* 进入Boss积分 2233, 2234                                              */
/************************************************************************/

CSEnterBossScorePacket::CSEnterBossScorePacket()
{

}
CSEnterBossScorePacket::~CSEnterBossScorePacket()
{

}
unsigned  int  CSEnterBossScorePacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ENTER_BOSSSCORE_;
}

bool  SCEnterBossScoreResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head, 2);
	packet>>m_len;
	packet>>m_pn;

	if(!BOSSSCOREDATAHANDLER->m_pBossScoreData)
	{
		BOSSSCOREDATAHANDLER->m_pBossScoreData = new BSBossScoreData();
	}
	BOSSSCOREDATAHANDLER->m_pBossScoreData->decodePacketData(packet);

	BOSSSCOREDATAHANDLER->m_pBossScoreData->tickBeginTime = TimeSystem::get_instance2()->GetCurrentMicroSecond();//记录获取包时的时间;

	return true;
}

unsigned  int  SCEnterBossScoreResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ENTER_BOSSSCORE_RESULT_;
}

bool  SCEnterBossScoreResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCEnterBossScoreResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
	{
		return false;
	}

	BOSSSCOREDATAHANDLER->ToClientEnterBossResult();

	return true;
}

/************************************************************************/
/* 挑战Boss积分 2235		                                              */
/************************************************************************/

CSBossScoreChallengePacket::CSBossScoreChallengePacket()
{

}

CSBossScoreChallengePacket::~CSBossScoreChallengePacket()
{

}

unsigned  int  CSBossScoreChallengePacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_CHALLENGE_BOSSSCORE_;
}


/************************************************************************/
/* 进入Boss积分排行榜 2237, 2238                                        */
/************************************************************************/
CSBossScoreRankPacket::CSBossScoreRankPacket()
{

}

CSBossScoreRankPacket::~CSBossScoreRankPacket()
{

}

unsigned  int  CSBossScoreRankPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ENTER_BOSSSCORE_RANK_;
}

bool  SCBossScoreRankResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head, 2);
	packet>>m_len;
	packet>>m_pn;

	if(!BOSSSCOREDATAHANDLER->m_pRankList)
	{
		BOSSSCOREDATAHANDLER->m_pRankList = new BSRankList();
	}
	BOSSSCOREDATAHANDLER->m_pRankList->decodePacketData(packet);

	return true;
}

unsigned  int  SCBossScoreRankResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ENTER_BOSSSCORE_RANK_RESULT_;
}
bool  SCBossScoreRankResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCBossScoreRankResultPacket pa;
	if(!pa.Read(pBuffer, iLen))
		return false;

	BOSSSCOREDATAHANDLER->ToClientEnterRankResult();

	return true;
}


/************************************************************************/
/* 进入Boss积分奖励 2239, 2240                                        */
/************************************************************************/

CSBossScoreRewardPacket::CSBossScoreRewardPacket()
{

}

CSBossScoreRewardPacket::~CSBossScoreRewardPacket()
{

}

unsigned  int  CSBossScoreRewardPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ENTER_BOSSSCORE_REWARD_;
}

bool  SCBossScoreRewardResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head, 2);
	packet>>m_len;
	packet>>m_pn;

	if(!BOSSSCOREDATAHANDLER->m_pRewardData)
	{
		BOSSSCOREDATAHANDLER->m_pRewardData = new BSRewardData();
	}
	BOSSSCOREDATAHANDLER->m_pRewardData->decodePacketData(packet);

	BOSSSCOREDATAHANDLER->m_pRewardData->tickBeginTime = TimeSystem::get_instance2()->GetCurrentMicroSecond();//记录获取包时的时间

	return true;
}

unsigned  int  SCBossScoreRewardResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ENTER_BOSSSCORE_REWARD_RESULT_;
}

bool  SCBossScoreRewardResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCBossScoreRewardResultPacket pa;
	if(!pa.Read(pBuffer, iLen))
		return false;

	BOSSSCOREDATAHANDLER->ToClientEnterRewardResult();

	return true;
}


/************************************************************************/
/* Boss积分奖励领取 2241, 2242                                          */
/************************************************************************/
CSBossScoreGetRewardPacket::CSBossScoreGetRewardPacket(char type, char index)
{
	//type:0积分奖励,1排名奖励; index:积分奖励序号
	PushData(type);
	PushData(index);
}
CSBossScoreGetRewardPacket::~CSBossScoreGetRewardPacket()
{

}

unsigned  int  CSBossScoreGetRewardPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_GET_BOSSSCORE_REWARD_;
}

bool  SCBossScoreGetRewardResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head, 2);
	packet>>m_len;
	packet>>m_pn;

	char type = 0;
	char index = 0;
	packet>>type;
	packet>>index;

	BOSSSCOREDATAHANDLER->ToClientGetRewardResult(type, index);

	return true;
}

unsigned  int  SCBossScoreGetRewardResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_GET_BOSSSCORE_REWARD_RESULT_;
}

bool  SCBossScoreGetRewardResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCBossScoreGetRewardResultPacket pa;
	if(!pa.Read(pBuffer, iLen))
		return false;


	return true;
}



