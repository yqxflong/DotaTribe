//Name:ClimbTowerDataHandler.h
//Function:爬塔管理器
//Author:fangjun
//date:20130826


#ifndef _DOTATRIBE_CLIMBTOWER_DATAHANDLER_H_
#define _DOTATRIBE_CLIMBTOWER_DATAHANDLER_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>
#include <vector>
#include "../include/CSMapTable.h"
#include <string>

class TowerTodayReward
{
public:
	int type;					//类型 0:物品 1:金钱 2: 经验 3:钻石 4:声望 5:体力
	int iconId;
	unsigned char quality;
	int templateId;
	std::string name;
	short rewardFloor;			//奖励层数
	unsigned short count;
	unsigned char status;		//状态，0已领取，1可领取，2进行中
public:
	TowerTodayReward();
	void decodePacketData(cobra_win::DPacket & packet);
};

class TowerReward
{
public:
	int iconId;
	unsigned char quality;
	int templateId;
	std::string name;
	unsigned short rewardFloor;		//奖励层数
	unsigned char status;			//状态，0已领取，1可领取
public:
	void decodePacketData(cobra_win::DPacket & packet);
};

class TowerRewardData
{
public:
	short topFloor;		//我的最好成绩 add by fangjun at 20140122
	int rank;			//我的排名 add by fangjun at 20140122
	short curFloor;		//当前我的层数

	std::vector<TowerTodayReward *> todayRewardVector;	//当日奖励 add by fangjun at 20140122
	std::vector<TowerReward *> towerRewardVector;		//当日奖励 add by fangjun at 20140122
public:
	TowerRewardData();
	~TowerRewardData();
	void destroyData();
	void decodePacketData(cobra_win::DPacket & packet);
	TowerReward * getFirstUnOpenTowerReward();
};

class TowerFastFightResultItem
{
public:
	unsigned char result;	//战斗结果
	short fightFloor;	//战斗层数
	int gotExp;				//获得经验
	int gotHonor;			//获得荣誉
	void decodePacketData(cobra_win::DPacket & packet);
};

class TowerFastFightResultData
{
public:
	std::vector<TowerFastFightResultItem *> resultData;
public:
	TowerFastFightResultData();
	~TowerFastFightResultData();
	void destroyData();
	void decodePacketData(cobra_win::DPacket & packet);
};

//阶段奖励元素
class TowerSkillItem{
public:
	int skillId;
	int iconId;
	TowerSkillItem()
	{
		skillId = 0;
		iconId = 0;
	}
	void decodePacketData(cobra_win::DPacket & packet);
};

class EnterData{
public:
	unsigned char entertype;//当前进入恶魔塔状态，0首次，1，再次
	//以下为首次进入
	short defaultfloor;//默认选中层
	unsigned char usedTimes;	//使用过的次数
	unsigned char maxTimes;		//最大可使用次数

	//以下为再次进入
	short nowfloor;//当前所在层数
	int gotmoney;//累计获得金钱
	int gotexp;//累计获得经验
	int nextmoney;//下一层获得金钱
	int nextexp;//下一层获得经验
	std::vector<TowerSkillItem *> skillData;//推荐技能

	//以下为自己的排名
	int rankNum;	//排名，<0则为不再排行榜中
	int honor;		//获得的荣耀
	int jewelResetPrice;	//钻石重置价格
	int fastFightPrice;		//快速战斗价格

	char haveFloorReward;	//有未领取的层级奖励

	short leftChallengeTime;	//剩余挑战次数 add by fangjun at 20140122
public:
	EnterData()
	{
		defaultfloor = 0;
		usedTimes = 0;
		maxTimes = 0;
		nowfloor = 0;
		gotmoney = 0;
		gotexp = 0;
		nextmoney = 0;
		nextexp = 0;
		skillData.clear();
		rankNum = 0;
		honor = 0;
		jewelResetPrice = 0;
		fastFightPrice = 0;
		haveFloorReward = 0;
	}
	~EnterData();
public:
	void destroyData();
	void decodePacketData(cobra_win::DPacket & packet);
};

class TowerRankItem//爬塔排行榜每行数据
{
public:
	int playerId;
	int iconId;
	std::string name;
	short level;
	int score;//排名
	int floor;//层数

	void decodePacketData(cobra_win::DPacket & packet);
};

class TowerRankList
{
public:
	std::vector<TowerRankItem *> rankVector;
public:
	void destroyData();		//此destroy可用于外部对象对于此类对象的清空数据，并不仅仅用于类自身析构时的清空数据
public:
	TowerRankList();
	~TowerRankList();
	void decodePacketData(cobra_win::DPacket & packet);
};


class ClimbTowerDataHandler : public IDataHandler, public cobra_win::Singleton2<ClimbTowerDataHandler>{
public:
	EnterData enterData;//进塔数据

	int iCurFloor;			//人物当前所在的层数
	int iPreFloor;			//人物之前所在的层数

	unsigned char fightResult;//1胜利，0失败

	TowerRankList * m_pRankList;//爬塔排行榜数据

	TowerFastFightResultData * m_pFastFightResultData;//快速战斗结果

	TowerRewardData * m_pRewardData;

public:
	ClimbTowerDataHandler();
	virtual ~ClimbTowerDataHandler();

protected:

	virtual void handlePacket(IPacket* packet){};

	virtual void onDestroy();

	virtual bool init(){	return true;	};

public:

	//进入恶魔塔
	void ToServerEnterTower();
	void ToClientEnterTowerResult();

	//开始塔，用于判断及购买次数
	void ToServerStartTower();
	void ToClientStartTowerResult();

	//挑战关卡
	void ToServerChallengeTower();
	void ToClientChallengeTowerResult();

	//重置爬塔记录
	void ToServerResetTower();
	void ToClientResetTowerResult();

	//排行榜
	void ToServerRankList();
	void ToClientRankListResult();

	//快速战斗
	void ToServerFastFight();
	void ToClientFastFightWinResult();

	//钻石重置
	void ToServerJewelReset();
	void ToClientJewelResetResult();

	//进入领去奖励面板
	void ToServerEnterReward();
	void ToClientEnterRewardResult();

	//领取奖励
	void ToServerGetReward(char type, unsigned short floor);
	void ToClientGetRewardResult(char type, unsigned short floor);

	//购买爬塔次数
	void ToServerBuyClimbTowerTimes();
	void ToClientBuyClimbTowerTimesResult();

	//计算是否有免费次数
	//bool HasFreeTimes();

	//计算是否有道具次数
	//bool HasPayTimes();

};

#define CLIMBTOWERDATAHANDLER (ClimbTowerDataHandler::get_instance2())

#endif