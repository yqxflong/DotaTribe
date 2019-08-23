#ifndef   _DOTATRIBE_ARENAINFODATA_H_ 
#define   _DOTATRIBE_ARENAINFODATA_H_

/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  竞技场数据
//date:   2013/07/22
/////////////////////////////////////////////////
#include   <string>
#include   <include/common/Singleton.h>
#include   "../include/IDataHandler.h"
#include   "../include/AthleticProcedureDataType.h"
#include   "../include/CPublicVarReader.h"
#include   "../include/CommonDataDef.h"
 
typedef  struct  challgenode_tag
{
	int  sourceID;
	std::string name; 
	int   level;
	int   iconID;
	int   btlCapacity;
	int   rank;
public:
	challgenode_tag()
	{
		sourceID=0;
		name="";
		level=0;
		iconID=0;
		btlCapacity=0;
		rank=0;
	}
	void decodePacketData(cobra_win::DPacket & packet);

}ChallgeNode,*PChallgeNode;


typedef  struct  historyarenanode_tag
{
   int	battleID;			//战斗ID
   int	distime;			//距离时间  //单位为毫秒
   int	sourceID;			//攻击者ID
   std::string sourceName;	//攻击者名称
   int	sourceRank;			//攻击者排名
   int  targetID;			//目标者ID
   std::string targetName;	//目标者名称
   int  targetRank;			//目标者排名
   char isWin;				//是否胜利

public:
	historyarenanode_tag()
	{
	 battleID=0;
	 distime=0;
	 sourceID=0;
	 sourceName="";
	 sourceRank=0;
	 targetID=0;
	 targetName="";
	 isWin=0;
	}
	void decodePacketData(cobra_win::DPacket & packet);

}HistoryArenaNode,*PHistoryArenaNode;

class  ArenaInfoData
{
public:
	enum
	{
		_Arena_Info_NoReward_Type_,						  //未领取
		_Arena_Info_HadReward_Type_,					  //已领取
	};
public:
	  int    winCount;									 //胜利次数
	  int	 loseCount;									 //失败次数
	  short  leftChallengeCount;						 //剩余挑战次数 
	  IByte  challengeEnemyCount;						 //可挑战敌军人数
	  std::vector<PChallgeNode> challgeList;			 //敌军列表
	  IByte  historyArenaCount;							 //历史竞技次数
	  std::vector<PHistoryArenaNode>  historyArenaList;  //历史竞技列表 
	  int    arenaRewardDistanceTime;					 //竞技场领取倒计时
public:
	ArenaInfoData()
	{
	   winCount=0;
	   loseCount=0;
	   leftChallengeCount=0; 
	   challengeEnemyCount=0;
	   historyArenaCount=0;
	   challgeList.clear();
	   historyArenaList.clear();
	   arenaRewardDistanceTime=0;
	}
	void  destroy()
	{
        size_t challgeCount=challgeList.size();
		for(size_t challgeIndex=0;challgeIndex<challgeCount;challgeIndex++)
		{
			delete  challgeList.at(challgeIndex); 
		}
		challgeList.clear();

		challgeCount=historyArenaList.size();
		for(size_t challgeIndex=0;challgeIndex<challgeCount;challgeIndex++)
		{
			delete  historyArenaList.at(challgeIndex); 
		}
		historyArenaList.clear();
	}

	void decodePacketData(cobra_win::DPacket & packet);
};




class   ArenaInfoDataHandler: public IDataHandler,public cobra_win::Singleton2<ArenaInfoDataHandler>
{
public: 
    ArenaInfoData * PArenaInfoData;
public:
	ArenaInfoDataHandler();
	~ArenaInfoDataHandler(); 
	virtual void handlePacket(IPacket* packet);  
	virtual void onDestroy(); 
	virtual bool init();  
public:
	/*
	  同步竞技场挑战次数
	*/
	void  decodeLastArenaTime(cobra_win::DPacket & packetData);

public:
	friend   class   cobra_win::Singleton2<ArenaInfoDataHandler>;
};

#define   ARENAINFODATAHANDLER			(ArenaInfoDataHandler::get_instance2())


//////////////////////////////////////////////////////////////////////////
 

typedef struct  chanllengerewardnode_tag
{ 
	bool   rewardHadGot;
	short  rewardChanllengeCount; 
	PRewardItemNode  rewardItemData;
public:
	chanllengerewardnode_tag()
	{
		rewardHadGot=false;
		rewardChanllengeCount=0;
		rewardItemData=new RewardItemNode(); 
	}
	~chanllengerewardnode_tag()
	{
		if(rewardItemData)
		{
			delete  rewardItemData;
		    rewardItemData=NULL;
		} 
	}
public:
	void decodePacketData(cobra_win::DPacket & packet);
}ChallengeRewardData,*PChallengeRewardData;

 
class  ArenaRewardData
{
  default_construct_destroy(ArenaRewardData)
  property_unit_rw(short,m_arenaChallengeCount,ArenaChallengeCount)				//今日剩余挑战次数			
  property_unit_ronly(int,m_nLastArenaRank,LastArenaRank)						//上次竞技场挑战排名
  property_unit_rw(bool,m_arenaHadReward,ArenaHadReward)						//是否获得竞技场奖励
  property_unit_rw(int,m_arenaGetRewardDistance,ArenaGetRewardDistance)			//领取奖励倒计时时间
  property_unit_rwc(std::vector<PRewardItemNode>,m_arenaRankRewardVector,ArenaRankRewardVector)
  property_unit_rwc(std::vector<PChallengeRewardData>,m_arenaChallengeRewardVector,ArenaChallengeRewardVector)
public:
  void decodePacketData(cobra_win::DPacket & packet);
};
 

class   ArenaRewardDataHandler: public IDataHandler,public cobra_win::Singleton2<ArenaRewardDataHandler>
{ 
	default_construct_vdestroy(ArenaRewardDataHandler)
	property_unit_rw(ArenaRewardData * ,m_ArenaRewardData,ArenaRewardDatas)
public:
  	virtual void handlePacket(IPacket* packet);  
	/*
		销毁接口
	*/
	virtual void onDestroy();

	/*
		初始化接口
	*/
	virtual bool init();

	/*
	   数据解析
	*/
	void  decodePacketData(cobra_win::DPacket & packetData);
  
public:
	friend   class   cobra_win::Singleton2<ArenaRewardDataHandler>;
};

#define   ARENAREWARDDATAHANDLER	 	(ArenaRewardDataHandler::get_instance2())




 
#endif