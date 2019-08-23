#include <cocos2d.h>
#include "../include/UpdateMissionPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/MissionDataHandler.h"
#include "../include/SysLangDataManager.h"
#include "../include/MessageBoxWindow.h"
#include "../include/NFControlsManager.h"
#include "../include/RoleInfoDataHandler.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>

#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;


C2SUpdateMissionPacket::C2SUpdateMissionPacket(int serialnum){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_serial=serialnum;
	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SUpdateMissionPacket::GetPacketType()
{
	return 0;
}

unsigned  int  C2SUpdateMissionPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_serial);
}
/*
	C->S不需要实现Read函数
*/
bool  C2SUpdateMissionPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SUpdateMissionPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_serial);

	
	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CUpdateMissionPacket::S2CUpdateMissionPacket()
{

}

S2CUpdateMissionPacket::~S2CUpdateMissionPacket()
{

}

unsigned  int  S2CUpdateMissionPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_UPDATEMISSIONRESULT_;
}

unsigned  int  S2CUpdateMissionPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CUpdateMissionPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	//packet>>m_LoginRet;
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	//packet>>serial_;

	//收信息

	MissionDataHandler::get_instance2()->decodeUpdateMissionsPacket(packet); 

	//
	//unsigned short tmp_len=0;
	//char *tmpChar=0;
	//
	//packet>>mapId;
	//packet>>stageId;
	//packet>>star;
	//packet>>challengeTimes;
	//MissionDataHandler::get_instance2()->UpdateStatesStar(mapId,stageId,star,challengeTimes);
	//packet>>hasNext;
	//if (hasNext)
	//{
	//	packet>>isOpenNewMap;
	//	if (isOpenNewMap)
	//	{
	//		//检测是否开需要显示三星奖励
	//		MissionDataHandler::get_instance2()->CheckFullStarsReward(mapId);
	//		  
	//		//接新地图
	//		MissionInfoData *pMissionInfoData = new MissionInfoData();
	//		packet>>pMissionInfoData->MissionID;
	//		pMissionInfoData->canGet3starReward = 0;
	//		pMissionInfoData->hasGetReward = 0;
	//		packet>>pMissionInfoData->StatesNum;
	//		for (int j=0;j<pMissionInfoData->StatesNum;j++)
	//		{
	//			StatesInfoData* pStatesInfoData = new StatesInfoData();
	//			packet>>pStatesInfoData->StatesID;

	//			packet>>tmp_len;
	//			tmpChar=new char[tmp_len+1];
	//			packet.read(tmpChar,tmp_len);
	//			tmpChar[tmp_len]='\0';
	//			pStatesInfoData->StatesName.assign(tmpChar);
	//			delete[] tmpChar;tmpChar=0;

	//			packet>>pStatesInfoData->cost;
	//			packet>>pStatesInfoData->canChallenge;
	//			packet>>pStatesInfoData->isClear;
	//			packet>>pStatesInfoData->star;
	//			packet>>pStatesInfoData->level;
	//			packet>>pStatesInfoData->ChallengeTimes;
	//			packet>>pStatesInfoData->maxChallengeTimes;
	//			packet>>pStatesInfoData->isBoss;
	//			packet>>pStatesInfoData->clearNeedDiamondNum;
	//			packet>>pStatesInfoData->bossShapeID;
	//			packet>>pStatesInfoData->exp;
	//			packet>>pStatesInfoData->money;
	//			packet>>pStatesInfoData->itemCount;
	//			for (int k=0;k<pStatesInfoData->itemCount;k++)
	//			{
	//				ItemInfoData* pItemInfoData = new ItemInfoData();
	//				
	//				pItemInfoData->decodePacketData(packet);

	//				pStatesInfoData->ItemInfoDataList.push_back(pItemInfoData);
	//			}
	//			pMissionInfoData->StatesInfoDataList.push_back(pStatesInfoData);
	//			if (pStatesInfoData->canChallenge && ROLEINFODATAHANDLER->m_pRIData->level_ >= pStatesInfoData->level && !pStatesInfoData->isClear)
	//			{
	//				pMissionInfoData->CurStatesID = pStatesInfoData->StatesID;
	//			}
	//			else if (j+1 == pMissionInfoData->StatesNum && pMissionInfoData->CurStatesID == -1)
	//			{
	//				pMissionInfoData->CurStatesID = pStatesInfoData->StatesID;
	//			}
	//		}

	//		unsigned char num;
	//		packet>>num;
	//		for (int j=0;j<num;j++)
	//		{
	//			ItemInfoData* pItemInfoData = new ItemInfoData();
	//			
	//			pItemInfoData->decodePacketData(packet);

	//			pMissionInfoData->StarRewardDataList.push_back(pItemInfoData);
	//		}

	//		MissionDataHandler::get_instance2()->MissionSort(pMissionInfoData);
	//		MissionDataHandler::get_instance2()->SetCurSraresID(pMissionInfoData);
	//		MissionDataHandler::get_instance2()->MissionInfoDataList.push_back(pMissionInfoData);
	//		MissionDataHandler::get_instance2()->worldMapStateNum =MissionDataHandler::get_instance2()->MissionInfoDataList.size();
	//	}
	//	else
	//	{
	//		//接单关卡
	//		packet>>openmapId;
	//		packet>>openstageId;
	//		MissionDataHandler::get_instance2()->SetCanChallenge(openmapId,openstageId);
	//	}
	//}
	//MissionDataHandler::get_instance2()->UpDatePlayerMissionInfo();
	return true;
}


void  S2CUpdateMissionPacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CUpdateMissionPacketFactory::S2CUpdateMissionPacketFactory()
{

}


S2CUpdateMissionPacketFactory::~S2CUpdateMissionPacketFactory()
{

}

unsigned  int S2CUpdateMissionPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_UPDATEMISSIONRESULT_;
}

bool S2CUpdateMissionPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CUpdateMissionPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CUpdateMissionPacketHandler(&packet);
	return true;
}	

void S2CUpdateMissionPacketFactory::OnS2CUpdateMissionPacketHandler(S2CUpdateMissionPacket* pPacket)
{

}
