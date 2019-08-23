// Name :		MissionDataHandler.h
// Function:	�ؿ�����
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef   _DOTATRIBE_MISSIONDATAHANDLER_H
#define   _DOTATRIBE_MISSIONDATAHANDLER_H
 
#include <include/common/Singleton.h>
#include <vector>
#include <string>
#include <include/mem/DPacket.h>
#include "../include/IDataHandler.h"
#include "../include/CommonDataDef.h"
#include "../include/CPublicVarReader.h"
 
/*
小关卡信息
*/
class  StatesInfoData
{
	default_construct_destroy(StatesInfoData)		
	property_unit_ronly(std::string,m_StatesName,StatesName)							  //关卡名称
	property_unit_rw(bool,m_CanChallenge,CanChallenge)									  //是否可以挑战
	property_unit_rw(bool,m_IsClear,IsClear)											  //是否可以扫荡
	property_unit_rw(bool,m_IsBoss,IsBoss)												  //是否为精英关卡
	property_unit_rw(int, m_ClearNeedDiamondNum,ClearNeedDiamondNum)					  //重置所需钻石数
	property_unit_rw(IByte,m_StarCount,StarCount)										  //星级数目							
	property_unit_ronly(UShort,m_Level,ChallengeLevel)									  //开启等级
	property_unit_rw(UShort,m_ChallengeTimes,ChallengeTimes)							  //当前挑战次数
	property_unit_ronly(UShort,m_MaxChallengeTimes,MaxChallengeTimes)					  //最大可挑战次数
	property_unit_ronly(int,m_BossShapeID,BossShapeID)									  //精英怪外形ID
	property_unit_ronly(int,m_Money,Money)												  //奖励金钱	
	property_unit_ronly(int,m_Exp,Exp)													  //奖励经验
	property_unit_ronly(UShort,m_CostTL,CostTL)											  //挑战消耗体力值	
	property_unit_ronly(std::vector<PRewardItemNode>,m_ItemInfoDataList,ItemInfoDataList) //挑战可获得物品数队列

public: 
	void   decodePacketData(cobra_win::DPacket & packet);
	UShort getLastChallengeTimes();
public:
	unsigned short  getStatesID();
	unsigned short	m_StatesID;
};


/*
大关卡信息
*/
class  MissionInfoData
{
	default_construct_destroy(MissionInfoData)
	property_unit_ronly(UShort,m_MissionID,MissionID)										    //大关卡ID
	property_unit_rw(bool,m_CanGet3starReward,CanGet3starReward)							    //是否可以获得三星关卡奖励
	property_unit_rw(bool,m_HasGetReward,HasGetReward)										    //是否可以获得奖励
	property_unit_rw(UShort,m_StatesNum,StatesNum)											    //获得关卡数目
	property_unit_rw(int,m_CurStatesID,CurStatesID)											    //当前子关卡ID
	property_unit_ronly(std::vector<StatesInfoData *>,m_StatesInfoDataList,StatesInfoDataList)  //子关卡列表	
	property_unit_ronly(std::vector<PRewardItemNode>,m_StarRewardDataList,StarRewardDataList)	//三星奖励内容
	property_unit_ronly(IByte,m_CurMissionFullStarNum,CurMissionFullStarNum)					//全三星数值
	property_unit_rw(int,m_nHistorySID,HistorySID)											    //历史子关卡挑战ID
public:
	void  decodePacketData(cobra_win::DPacket & packet);									    //解数据包
	void  decodeUpdatePacketData(cobra_win::DPacket & packet);									//解析更新数据包
	void  sortStatesList();																	    //关卡数据排序
	void  setCurStatesID();																		//定位当前关卡ID
	IByte getCurMissionStarNum();											
	bool  getIsCanReward();	
	IByte getMissionStarNum();																	//获取三星奖励显示星星数

};


class MissionDataHandler:public IDataHandler,public cobra_win::Singleton2<MissionDataHandler>
{
	default_construct_vdestroy(MissionDataHandler)
	property_unit_rw(int,m_CurMissionsID,CurMissionID)												 //当前大关卡ID
	property_unit_rw(int,m_CurStatesID,CurStatesID)													 //当期子关卡ID
	property_unit_rw(bool,m_IsNeedJump,IsNeedJump)													 //是否需要大关卡跳转
	property_unit_rw(bool,m_IsShowGetRewad,IsShowGetRewad)											 //是否引导领取三星奖励
	property_unit_rw(UShort,m_WorldMapStateNum,WorldMapStateNum)									 //当前开启的大关卡数目
	property_unit_rw(bool,m_bForceLocationCustom,IsForceLocationCustom)								 //是否强制定位关卡ID
	property_unit_ronly(std::vector<MissionInfoData*>,m_MissonInfoDataList,MissonInfoDataList)		 //子关卡数据队列
public:
	/*
	解析全地图数据
	*/
	void  decodeTotalMissionsPacket(cobra_win::DPacket & packet);
	/*
	更新关卡数据
	*/
	void  decodeUpdateMissionsPacket(cobra_win::DPacket & packet);
public:
	//更新子关卡星星数和可挑战次数
	void UpdateStatesStar(int missionID,int customID,int star,int challengeTimes);
	//更新子关卡中重置钻石数据
	void UpdateCustomDiamond(int missionID,int customID,int diamondNum);
	//激活指定可挑战关卡
	void ActiveCustomByID(int missionID,int customID);
	//更新玩家简约关卡进度信息
	void UpdatePlayerMissionInfo();
	//重置所有所有关卡挑战次数
	void ResettingMissionInfo();
	//跳转到指定关卡
	void JumpToAppointStates(int missioid,int statesid=-1);
	//跳转指定大关卡最近可挑战关卡
	void JumpToAppointMission(int missioid);
	//检测指定大关卡是可以领取
	bool CheckFullStarsReward(int missioid=-1);
	//检测是否可以挑战下个大关卡
	bool CheckIsNeedJumpNextMisson(); 
	//获取的指定大关卡信息
	MissionInfoData* GetMissionInfo(int missionID =1);
	//获取指定子关卡信息
	StatesInfoData * GetStatesInfoInfo(int missionID,int statesID);
	StatesInfoData * GetStatesInfoInfo(int statesID);
private:
	StatesInfoData * GetStateInfoFromMissionData(MissionInfoData * pMissionInfoData,int statesID);

public:
	virtual void handlePacket(IPacket* packet);
	virtual bool init();
	virtual void onDestroy();
private:
	void   destroyMemData();
};
#endif