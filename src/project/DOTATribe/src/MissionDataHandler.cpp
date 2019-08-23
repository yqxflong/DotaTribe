// Name :		MissionDataHandler.h
// Function:	关卡数据
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include "../include/MissionDataHandler.h"
#include "../include/DOTATribeApp.h"
#include "../include/SelectMissionProcedure.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/LoadingWindow.h"

#include <vector>
#include <algorithm> 
using namespace std;


const  IByte maxStarNumForOnCustom = 3;
 
//////////////////////////////////////////////////////////////////////////
// 子关卡信息
//////////////////////////////////////////////////////////////////////////
StatesInfoData::StatesInfoData()
{
	m_StatesID = 0;
	m_StatesName = "";
	m_CanChallenge = false;
	m_IsClear = false;
	m_IsBoss = false;
	m_ClearNeedDiamondNum = 0;
	m_StarCount = 0;
	m_Level = 0;
	m_ChallengeTimes = 0;
	m_MaxChallengeTimes = 0;
	m_BossShapeID = 0;
	m_Money = 0;
	m_Exp = 0;
	m_CostTL = 0; 
	m_ItemInfoDataList.clear();
}

StatesInfoData::~StatesInfoData()
{
	size_t rewardSize = m_ItemInfoDataList.size();
	COMMON_BEIGIN_ARRAY(size_t,rewardSize)
		delete m_ItemInfoDataList.at(index);
	COMMON_END_ARRAY
	m_ItemInfoDataList.clear();
}

void StatesInfoData::decodePacketData(cobra_win::DPacket & packet)
{ 
	packet.read(m_StatesID); 
	NFC_ParsePacketString(packet,m_StatesName); 
	packet.read(m_CostTL);
	IByte tmpByteCode = 0;
	packet.read(tmpByteCode);
	m_CanChallenge = tmpByteCode > 0 ? true : false;
	packet.read(tmpByteCode);
	m_IsClear = tmpByteCode > 0 ? true : false;
	packet.read(m_StarCount);
	packet.read(m_Level);
	packet.read(m_ChallengeTimes);
	packet.read(m_MaxChallengeTimes);
	packet.read(tmpByteCode);
	m_IsBoss = tmpByteCode > 0 ? true : false;
	packet.read(m_ClearNeedDiamondNum);
	packet.read(m_BossShapeID);
	packet.read(m_Exp);
	packet.read(m_Money);

	packet.read(tmpByteCode);
	COMMON_BEIGIN_ARRAY(IByte,tmpByteCode)
		PRewardItemNode pRewardItem = new RewardItemNode();
		pRewardItem->decodePacketData(packet);
	m_ItemInfoDataList.push_back(pRewardItem);
	COMMON_END_ARRAY  
}

UShort StatesInfoData::getLastChallengeTimes()
{
	return  m_MaxChallengeTimes - m_ChallengeTimes;
}

unsigned short StatesInfoData::getStatesID()
{
	return m_StatesID;
} 


//////////////////////////////////////////////////////////////////////////
// 大关卡信息
//////////////////////////////////////////////////////////////////////////

bool  less_compare(const StatesInfoData * first,const StatesInfoData * second)
{
	return  first->m_StatesID < second->m_StatesID;
}
 

MissionInfoData::MissionInfoData()
{
	m_CurMissionFullStarNum = 0;
	m_MissionID = 0;
	m_CanGet3starReward = false;
	m_HasGetReward = false;
	m_StatesNum = false;
	m_CurStatesID = 0;
	m_StatesInfoDataList.clear();
	m_StarRewardDataList.clear();
	m_nHistorySID = -1;
}

MissionInfoData::~MissionInfoData()
{
	size_t vectorSize = m_StatesInfoDataList.size();
	COMMON_BEIGIN_ARRAY(size_t,vectorSize)
		delete m_StatesInfoDataList.at(index);
	COMMON_END_ARRAY
	m_StatesInfoDataList.clear();
	vectorSize = m_StarRewardDataList.size();
	COMMON_BEIGIN_ARRAY(size_t,vectorSize)
		delete m_StarRewardDataList.at(index);
	COMMON_END_ARRAY
	m_StarRewardDataList.clear();
}

void MissionInfoData::decodePacketData(cobra_win::DPacket & packet)
{
	m_nHistorySID = -1;
	packet.read(m_MissionID);
	IByte  byteTempCode = 0;
	packet.read(byteTempCode);
	m_CanGet3starReward = byteTempCode > 0 ? true : false;
	packet.read(byteTempCode);
	m_HasGetReward =  byteTempCode > 0 ? true :false; 
	packet.read(m_StatesNum);
	m_CurStatesID = 0; 
	COMMON_BEIGIN_ARRAY(UShort,m_StatesNum)
		StatesInfoData* pStatesInfoData = new StatesInfoData();
	    pStatesInfoData->decodePacketData(packet);
		m_StatesInfoDataList.push_back(pStatesInfoData);
	COMMON_END_ARRAY
		 
	packet.read(byteTempCode);
    COMMON_BEIGIN_ARRAY(IByte,byteTempCode)
		 PRewardItemNode pRewardItem = new RewardItemNode();
	     pRewardItem->decodePacketData(packet);
		 m_StarRewardDataList.push_back(pRewardItem);
	COMMON_END_ARRAY  

	m_CurMissionFullStarNum = maxStarNumForOnCustom * m_StatesNum ;

	sortStatesList();
	setCurStatesID();

}

void MissionInfoData::decodeUpdatePacketData(cobra_win::DPacket & packet)
{
	m_nHistorySID = -1;
	packet.read(m_MissionID);
	IByte  byteTempCode = 0; 
	m_CanGet3starReward = false;
	m_HasGetReward = false;
	packet.read(m_StatesNum);
	m_CurStatesID = 0; 
	COMMON_BEIGIN_ARRAY(UShort,m_StatesNum)
		StatesInfoData* pStatesInfoData = new StatesInfoData();
	pStatesInfoData->decodePacketData(packet);
	m_StatesInfoDataList.push_back(pStatesInfoData);
	COMMON_END_ARRAY
	packet.read(byteTempCode);
	COMMON_BEIGIN_ARRAY(IByte,byteTempCode)
		PRewardItemNode pRewardItem = new RewardItemNode();
	pRewardItem->decodePacketData(packet);
	m_StarRewardDataList.push_back(pRewardItem);
	COMMON_END_ARRAY  

	m_CurMissionFullStarNum = maxStarNumForOnCustom * m_StatesNum ;

	sortStatesList();
	setCurStatesID();
}

void MissionInfoData::sortStatesList()
{
	if(!m_StatesInfoDataList.empty())
	{
		sort(m_StatesInfoDataList.begin(),m_StatesInfoDataList.end(),less_compare);
	} 
}

void MissionInfoData::setCurStatesID()
{ 
	m_CurStatesID = 0;
	size_t statesCount = m_StatesInfoDataList.size();
	COMMON_BEIGIN_ARRAY(size_t,statesCount)
		if(!m_StatesInfoDataList.at(index)->getCanChallenge())
		break; 
		else
		m_CurStatesID = m_StatesInfoDataList.at(index)->getStatesID();
	COMMON_END_ARRAY 
	if(m_CurStatesID == 0)
	m_CurStatesID = 1; 
}

IByte MissionInfoData::getCurMissionStarNum()
{ 
	IByte  curMissionStarNum = 0 ;
	size_t customSize = m_StatesInfoDataList.size();
	COMMON_BEIGIN_ARRAY(size_t,customSize)
		curMissionStarNum += m_StatesInfoDataList.at(index)->getStarCount();
	COMMON_END_ARRAY
	return curMissionStarNum;
}
 
bool MissionInfoData::getIsCanReward()
{
	if(getCurMissionStarNum()==m_CurMissionFullStarNum)
	return true;
	return false;
}

IByte MissionInfoData::getMissionStarNum()
{ 
	IByte curMissionStar = getCurMissionStarNum();
	if(curMissionStar == 0)
	{   
		return 0;
	}
	else
	{ 
		if(curMissionStar <= m_CurMissionFullStarNum/maxStarNumForOnCustom)
		return  1;
		else if(curMissionStar < m_CurMissionFullStarNum)
		return  2; 
		else
		return  3;
	}
}

 
/////////////////////////////////////////////////////////////////////////////
// 关卡内存数据
/////////////////////////////////////////////////////////////////////////////

MissionDataHandler::MissionDataHandler()
{
	init();
}

MissionDataHandler::~MissionDataHandler()
{  
	destroyMemData();
}

void   MissionDataHandler::handlePacket(IPacket* packet)
{
}

void   MissionDataHandler::destroyMemData()
{
	size_t  missionCount = m_MissonInfoDataList.size();
	COMMON_BEIGIN_ARRAY(size_t,missionCount)
		delete m_MissonInfoDataList.at(index);
	COMMON_END_ARRAY
	m_MissonInfoDataList.clear();
}

bool MissionDataHandler::init()
{
	m_bForceLocationCustom = false;
	m_CurMissionsID = 0;
	m_CurStatesID = 0;  
	m_IsNeedJump = false;
	m_IsShowGetRewad = false;
	m_WorldMapStateNum = 0;
	m_MissonInfoDataList.clear();
	return true;
}

/*
解析开启地图数据包
*/

void MissionDataHandler::decodeTotalMissionsPacket(cobra_win::DPacket & packet)
{ 
	destroyMemData(); 
	packet.read(m_WorldMapStateNum);
	COMMON_BEIGIN_ARRAY(UShort,m_WorldMapStateNum)
		MissionInfoData *  pMissionInfoData = new MissionInfoData();
	    pMissionInfoData->decodePacketData(packet);
		m_MissonInfoDataList.push_back(pMissionInfoData);
	COMMON_END_ARRAY 

	UpdatePlayerMissionInfo();
}

/*
解析更新地图数据包
*/
void  MissionDataHandler::decodeUpdateMissionsPacket(cobra_win::DPacket & packet)
{
	UShort updateMissionID = 0;
	UShort updateStatgeID = 0;
	IByte  updateStar = 0;
	UShort updateChallengeTime = 0;
	packet.read(updateMissionID);
	packet.read(updateStatgeID);
	packet.read(updateStar);
	packet.read(updateChallengeTime);
	UpdateStatesStar(updateMissionID,updateStatgeID,updateStar,updateChallengeTime);
	IByte  bHadNext = 0;
	packet.read(bHadNext);
	if(bHadNext)
	{
		IByte isOpenNewMap = 0;
		packet.read(isOpenNewMap);
		if(isOpenNewMap)
		{
			CheckFullStarsReward(updateMissionID);
			//受新地图信息
			MissionInfoData * pMissionInfoData = new MissionInfoData();
			pMissionInfoData->decodeUpdatePacketData(packet);
			m_MissonInfoDataList.push_back(pMissionInfoData);
			m_WorldMapStateNum = m_MissonInfoDataList.size();
		}
		else
		{
			//开启下一个小关卡
			packet.read(updateMissionID);
			packet.read(updateStatgeID);
			ActiveCustomByID(updateMissionID,updateStatgeID);
		} 
	}
	UpdatePlayerMissionInfo();
}

 
void MissionDataHandler::onDestroy()
{ 
	 //to do
	m_CurStatesID = 0;
} 

 

MissionInfoData* MissionDataHandler::GetMissionInfo(int missionID)
{
	size_t missionCount = m_MissonInfoDataList.size();
	COMMON_BEIGIN_ARRAY(size_t,missionCount)
         if(m_MissonInfoDataList.at(index)->getMissionID() == missionID)
		 return  m_MissonInfoDataList.at(index);
	COMMON_END_ARRAY 
	return NULL;  
}
StatesInfoData* MissionDataHandler::GetStatesInfoInfo(int missionID,int statesID)
{  
	return GetStateInfoFromMissionData(GetMissionInfo(missionID),statesID); 
}

StatesInfoData* MissionDataHandler::GetStatesInfoInfo(int statesID)
{  
	return GetStateInfoFromMissionData(GetMissionInfo(m_CurMissionsID),statesID); 
}


StatesInfoData * MissionDataHandler::GetStateInfoFromMissionData(MissionInfoData * pMissionInfoData,int statesID)
{
	if(pMissionInfoData)
	{  
		size_t  vectorSize = pMissionInfoData->getStatesInfoDataList().size();
		COMMON_BEIGIN_ARRAY(size_t,vectorSize)
			if(pMissionInfoData->getStatesInfoDataList().at(index)->getStatesID() == statesID)
			return pMissionInfoData->getStatesInfoDataList().at(index);
		COMMON_END_ARRAY
	}
	return NULL;
}



void MissionDataHandler::UpdateStatesStar(int missionID,int customID,int star,int challengeTimes)
{
	StatesInfoData * pStatesInfoData = GetStatesInfoInfo(missionID,customID);
	if(pStatesInfoData)
	{
		if(pStatesInfoData->getStarCount() < star)
		pStatesInfoData->setStarCount(star);
		pStatesInfoData->setIsClear(true);
		pStatesInfoData->setChallengeTimes(challengeTimes);
	} 
}

void MissionDataHandler::UpdateCustomDiamond(int missionID,int customID,int diamondNum)
{ 
	StatesInfoData * pStatesInfoData = GetStatesInfoInfo(missionID,customID);
	if(pStatesInfoData)
	{ 
		pStatesInfoData->setChallengeTimes(0);
		pStatesInfoData->setClearNeedDiamondNum(diamondNum);
	}  
}


void MissionDataHandler::ActiveCustomByID(int missionID,int customID)
{ 
	StatesInfoData * pStatesInfoData = GetStatesInfoInfo(missionID,customID);
	if(pStatesInfoData)
	{ 
		pStatesInfoData->setCanChallenge(true);
		MissionInfoData * pMissionInfoData = GetMissionInfo(missionID);
		if(pMissionInfoData)
		{
			pMissionInfoData->setCurStatesID();
		}
	}   

} 

void MissionDataHandler::UpdatePlayerMissionInfo()
{ 
	 UShort curMapID = (UShort)m_MissonInfoDataList.size();
	 RoleInfoDataHandler::get_instance2()->m_pRIData->mapId_ = curMapID;
	 RoleInfoDataHandler::get_instance2()->m_pRIData->stageId_ = m_MissonInfoDataList.at(curMapID-1)->getCurStatesID(); 
}
 
void MissionDataHandler::ResettingMissionInfo()
{ 
	size_t  missionSize = m_MissonInfoDataList.size();
	size_t  customSize = 0;
	MissionInfoData * pMissionInfoData = NULL;
	StatesInfoData  * pStatesInfoData = NULL;
	COMMON_BEIGIN_ARRAY(size_t,missionSize) 
	    pMissionInfoData = m_MissonInfoDataList.at(index);
		if(pMissionInfoData)
		{  
			customSize = pMissionInfoData->getStatesInfoDataList().size();
			for(size_t curstomIndex = 0; curstomIndex < customSize; curstomIndex++)
			{ 
			   pStatesInfoData = pMissionInfoData->getStatesInfoDataList().at(curstomIndex);
			   if(pStatesInfoData)
			   pStatesInfoData->setChallengeTimes(0);
			} 
		}
	COMMON_END_ARRAY  
}


void MissionDataHandler::JumpToAppointStates(int missioid,int statesid)
{
	m_CurMissionsID = missioid;
	if(statesid != -1)
	{
		m_bForceLocationCustom = true;
		m_CurStatesID = statesid;
	}
	if(DOTATribeApp::get_instance2()->GetActiveProcedure()->GetType()==IProcedure::_TYPED_SELECTMISSION_PROCEDURE_)
	{
		DOTATribeApp::get_instance2()->m_pSelectMissionProcedure->m_showWindow = _TYPED_EVENT_SHOW_SELECTSONMISSIONWINDOW_;
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_,_to_event_param_(LoadingWindow::_RESTART_MISSION_PROCEDURE_));
		return;
	}
	DOTATribeApp::get_instance2()->m_pSelectMissionProcedure->m_showWindow = _TYPED_EVENT_SHOW_SELECTSONMISSIONWINDOW_;
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_,_to_event_param_(IProcedure::_TYPED_SELECTMISSION_PROCEDURE_));
}

void MissionDataHandler::JumpToAppointMission(int missioid)
{
	m_CurMissionsID = missioid;
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_,_to_event_param_(IProcedure::_TYPED_SELECTMISSION_PROCEDURE_));
}	

bool MissionDataHandler::CheckFullStarsReward(int missioid)
{
	if(-1 == missioid)
	{
		missioid = m_CurMissionsID;
	}
	MissionInfoData* Data = GetMissionInfo(missioid);
	if(!Data->getHasGetReward()&&Data->getIsCanReward()) 
	m_IsShowGetRewad = true;
	else
    m_IsShowGetRewad = false; 
	return m_IsShowGetRewad; 
}

bool MissionDataHandler::CheckIsNeedJumpNextMisson()
{
	//检测是否需要跳转到下一章地图
	m_IsNeedJump = false;
	size_t  missonsCount = m_MissonInfoDataList.size();
	for(size_t missonIndex = 0;missonIndex < missonsCount; missonIndex++)
	{
		if(m_MissonInfoDataList.at(missonIndex)->getMissionID() == (m_CurMissionsID+1))
		{
			m_IsNeedJump = m_MissonInfoDataList.at(missonIndex)->getCurStatesID() <= 1 ? true :false;
			break;
		}
	}
	return  m_IsNeedJump;
}


