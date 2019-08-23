//Name:BoseScoreDataHandler.h
//Function:Boss积分系统
//Author:fangjun
//date:20140215


#ifndef _DOTATRIBE_BOSSSCORE_DATAHANDLER_H_
#define _DOTATRIBE_BOSSSCORE_DATAHANDLER_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>
#include <vector>
#include <string>

//积分奖励物品单元
class BSScoreRewardItem
{
public:
	char index;
	int minScore;
	char type;				//0物品 1金钱 2经验 3钻石 4声望 5体力<br>
	int count;
	char catogory;
	int templateId;
	std::string name;
	char quality;
	int iconId;
	unsigned char status;		//状态，0已领取，1可领取，2进行中
public:
	void decodePacketData(cobra_win::DPacket & packet);
};

//排名奖励物品单元
class BSRankRewardItem
{
public:
	char type;				//0物品 1金钱 2经验 3钻石 4声望 5体力<br>
	int count;
	char catogory;
	int templateId;
	std::string name;
	char quality;
	int iconId;
public:
	void decodePacketData(cobra_win::DPacket & packet);
};

//奖励界面信息
class BSRewardData
{
public:
	int maxScore;
	short rank;
	std::vector<BSScoreRewardItem *> scoreRewardVector;//积分奖励
	int leftDrawSeconds;	//剩余领取时间
	long long tickBeginTime;
	std::vector<BSRankRewardItem * > rankRewardVector;//排名奖励
public:
	BSRewardData();
	~BSRewardData();
	void destroyData();
	void decodePacketData(cobra_win::DPacket & packet);

};

//排行榜每行信息
class BSRankItem
{
public:
	int playerId;
	int iconId;
	std::string name;
	int score;
	short rank;
	short level;
public:
	void decodePacketData(cobra_win::DPacket & packet);
};

//排行榜界面数据
class BSRankList
{
public:
	std::vector<BSRankItem *> rankVector;
public:
	BSRankList();
	~BSRankList();
	void destroyData();
	void decodePacketData(cobra_win::DPacket & packet);
};

class BSBossInfo
{
public:
	char quality;
	int iconId;
public:
	void decodePacketData(cobra_win::DPacket & packet);
};

//boss积分界面数据
class BSBossScoreData
{
public:
	std::string description;
	char status;
	int leftSeconds;
	long long tickBeginTime;
	std::vector<BSBossInfo *> bossVector;
	int maxScore;
	short rank;
	short leftFreeTimes;
	short leftChallengeItemCount;
	short challengePrice;
	std::vector<std::string> nameVector;
	std::vector<int> scoreVector;
	char hasReward;
public:
	BSBossScoreData();
	~BSBossScoreData();
	void destroyData();
	void decodePacketData(cobra_win::DPacket & packet);

};

class BossScoreDataHandler : public IDataHandler, public cobra_win::Singleton2<BossScoreDataHandler>{
public:
	int m_iFreeTimesSync;//同步获得的免费次数值，仅供主页面角标展示

	BSBossScoreData * m_pBossScoreData;
	BSRankList * m_pRankList;
	BSRewardData * m_pRewardData;

public:
	BossScoreDataHandler();
	virtual ~BossScoreDataHandler();

protected:

	virtual void handlePacket(IPacket* packet){};

	virtual void onDestroy();

	virtual bool init(){	return true;	};
public:
	//战斗结束
	void OnAthleticEnd(int stageID, bool win);

public:
	//进入世界boss
	void ToServerEnterBoss();
	void ToClientEnterBossResult();

	//进入排行榜
	void ToServerEnterRank();
	void ToClientEnterRankResult();

	//进入宝箱奖励
	void ToServerEnterReward();
	void ToClientEnterRewardResult();

	//开始挑战
	void ToServerChallenge();
	
	//领取奖励
	void ToServerGetReward(char type, char index);
	void ToClientGetRewardResult(char type, char index);



};

#define BOSSSCOREDATAHANDLER (BossScoreDataHandler::get_instance2())

#endif