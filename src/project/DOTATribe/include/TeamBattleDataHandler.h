//Name:TeamBattleDataHandler.h
//Function:组队副本数据
//Author:fangjun
//date:20130922

#ifndef _DOTATRIBE_TEAMBATTLE_DATAHANDLER_H_
#define _DOTATRIBE_TEAMBATTLE_DATAHANDLER_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>
#include <vector>
#include "../include/CSMapTable.h"
#include "../include/CPublicVarReader.h"
#include <string>
#include <cocos2d.h>

class TMercenaryItem
{
public:
	int playerId;
	int iconId;
	char quality;
	std::string skinName;
	//char enhanceLevel;
	int btlCapa;
	std::string playerName;
	int hirePrice;
	int pvpRank;
	short playerLevel;
	void decodePacketData(cobra_win::DPacket & packet);
};

class TMercenaryList
{
public:
	std::vector<TMercenaryItem *> mercenaryVector;
	TMercenaryList();
	~TMercenaryList();
	void destroyData();
	void decodePacketData(cobra_win::DPacket & packet);
};

class TSlaveItem
{
public:
	int playerId;
	int iconId;
	char quality;
	std::string skinName;
	//char enhanceLevel;
	int btlCapa;
	std::string playerName;
	short leftMinute;
	short playerLevel;
	void decodePacketData(cobra_win::DPacket & packet);
};

class TSlaveList
{
public:
	std::vector<TSlaveItem *> slaveVector;
	TSlaveList();
	~TSlaveList();
	void destroyData();
	void decodePacketData(cobra_win::DPacket & packet);
};

class TRewardItem
{
public:
	int iconId;
	unsigned char catogory;
	char quality;
	int templateId;
	TRewardItem()
	{
		iconId = 0;
		catogory = 0;
		quality = 0;
		templateId = 0;
	}
	void decodePacketData(cobra_win::DPacket & packet);
};


class TGateItem
{
public:
	char gateId;
	std::string gateName;
	int iconId;	//关图
	unsigned short minLevel;
	IByte mIspreMappass; //0：代表前置未通关  1：前置已通关
	unsigned char nowStage;
	unsigned char maxStage;
	int totalPlayer;//当前进度的总参与人数

	unsigned char rewardNeedVipLevel0;		//奖励0需要vip等级
	int rewardCostJewel0;			//奖励0需要钻石个数
	unsigned char rewardNeedVipLevel1;		//奖励1需要vip等级
	int rewardCostJewel1;			//奖励1需要钻石个数
	unsigned char rewardNeedVipLevel2;		//奖励2需要vip等级
	int rewardCostJewel2;			//奖励2需要钻石个数

	std::vector<TRewardItem *> rewardVector;

	bool canSelect;//是否能选中
private:
	void destroyData();//销毁vector中数据
public:
	TGateItem();
	~TGateItem();
	void decodePacketData(cobra_win::DPacket & packet);
};

class TTeamBattleData
{
public:
	unsigned char challengeTimes;    //已经挑战次数
	unsigned char maxChallengeTimes;//总共可以挑战次数

	std::vector<TGateItem *> gateVector;
public:
	void destroyData();
public:
	TTeamBattleData();
	~TTeamBattleData();
	void decodePacketData(cobra_win::DPacket & packet);
};

class TTeamStageData//当前关卡数据
{
public:
	unsigned char stageId;
	std::string stageName;
	void decodePacketData(cobra_win::DPacket & packet);
};

class TTeamListItem//每个队伍资料
{
public:
	int teamId;
	int leaderPlayerId;//队长playerId
	std::string leaderName;
	char memberCount;//当前队伍人数
	void decodePacketData(cobra_win::DPacket & packet);
};

class TTeamListData//队伍资料
{
public:
	std::vector<TTeamListItem *> teamVector;
public:
	void destroyData();
public:
	TTeamListData();
	~TTeamListData();
	void decodePacketData(cobra_win::DPacket & packet);

};

class TMyTeamMember//我的队伍成员
{
public:
	int index;//排序,这个不用存储
	char gameUnitType;//0玩家，3奴隶，4佣兵
	char isLeader;
	std::string markName;//社会关系
	std::string skinName;//外套名称
	//char enhanceLevel;
	int btlCapacity;//战力
	int iconId;
	char quality;
	std::string playerName;//玩家名字
	int playerId;//玩家Id

	void decodePacketData(cobra_win::DPacket & packet);
};

class TMyTeamData//我的队伍数据
{
public:
	char isIamLeader;
	std::vector<TMyTeamMember *> memberVector;
public:
	void destroyData();//此destroy可用于外部对象对于此类对象的清空数据，并不仅仅用于类自身析构时的清空数据
public:
	TMyTeamData();
	~TMyTeamData();
	void decodePacketData(cobra_win::DPacket & packet);
};


/************************************************************************/
/* This is DataHandler                                                   */
/************************************************************************/

class TeamBattleDataHandler : public IDataHandler, public cobra_win::Singleton2<TeamBattleDataHandler>
{
public:
	int m_iStartGateIdx;//选中副本在副本列表中的Idx
	int m_iMyTeamId;//我的队伍Id

	bool m_bHaveGateReward;//当前有副本通关奖励

	bool m_bOneMsgIsCoolDowning;//组队界面的一键喊话按钮是否是在冷却
	long long m_lCoolDownTimeCount;//一键喊话时间计数

	TTeamBattleData * m_pTeamBattleData;	//组队副本的副本数据

	TTeamListData * m_pTeamListData;		//队伍列表数据

	TTeamStageData * m_pTeamStageData;		//当前关卡信息

	TMyTeamData * m_pMyTeamData;			//我所在队伍数据

	TSlaveList * m_pSlaveList;				//我的奴隶列表
	
	TMercenaryList * m_pMercenaryList;		//我可租用的佣兵列表

	cocos2d::CCPoint m_fOldGateTableOffset;		//组队关卡的偏移量，add in 2013-12-26
	float m_fOldGateTableWidth;			//组队副本关卡的宽度，add in 2013-12-26

public:
	TeamBattleDataHandler();
	virtual ~TeamBattleDataHandler();

protected:

	virtual void handlePacket(IPacket* packet){};

	virtual void onDestroy();

	virtual bool init(){	return true;	};


public:
	//清空我所在队伍数据
	void ClearMyTeamData();

	//获得选中的副本信息
	TGateItem * GetSelectGateInfo();

	TGateItem * GetGateInfoById(int gateId);

	TGateItem * GetGateInfoByIdx(int gateIdx);

	int GetMaxCanStartGateIdx();

	//销毁我所在队伍
	void DestroyMyTeam();

	//获取我当前所在队伍的队长playerId  add by fangjun @ 20140312
	int GetMyTeamLeaderId();

public:
	//进入组队副本，选关卡
	void ToServerEnterTeamBattle();
	void ToClientEnterTeamBattleResult();

	//重置某个副本进度
	void ToServerResetGate();
	void ToClientResetGateResult();

	//进入组队，选队友
	void ToServerEnterTeamSelect();
	void ToClientEnterTeamSelectResult();

	//获得队伍列表
	void ToClientGetTeamList();

	//加入或者创建队伍
	void ToServerJoinTeam();
	void ToClientJoinTeamResult();//获得我的队伍信息

	//通知服务器离开选队伍界面，关闭队伍同步
	void ToServerStopTeamSync();

	//移除某个队员
	void ToServerRemoveMember(int playerId);
	void ToClientBeRemoved(char removedType);

	//重置某个副本进度
	void ToServerResetTeamBattle(unsigned char fubenId);
	void ToClientResetTeamBattle();

	//开始关卡
	void ToServerStartStage();
	
	//重设队伍出战顺序
	void ToServerReorderMyTeam(std::vector<int> & playerIdVec);
	void ToServerSwitchMemberPlace(int arg0, int arg1);

	//获取通关奖励
	void ToServerGateReward(char rewardTag);
	void ToClientGateRewardResult();

	//获取玩家信息
	void ToServerGetPlayerInfo(int playerid);

	//获取奴隶列表
	void ToServerGetSlaveList();
	void ToClientGetSlaveList();

	//获取佣兵列表
	void ToServerGetMercenaryList();
	void ToClientGetMercenaryList();
	
	//雇佣某个奴隶
	void ToServerRendSlave(int playerId);

	//雇佣某个佣兵
	void ToServerRendMercenary(int playerId);
};

#define TEAMBATTLEDATAHANDLER (TeamBattleDataHandler::get_instance2())

#endif