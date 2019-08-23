//Name:MiningDataHandler.h
//Function:挖矿
//Author:fangjun
//date:20131127

#ifndef _DOTATRIBE_MINING_DATAHANDLER_H_
#define _DOTATRIBE_MINING_DATAHANDLER_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>
#include "../include/CSMapTable.h"
#include <vector>
#include <string>

// 寻宝猎人信息
class HuntLieRenInfo
{
public:
	std::string name;
	unsigned short level;
	std::string heroLevelDesc;
	unsigned char spentTili;//体力消耗
	unsigned char index;
	unsigned char isActive;//是否激活

	unsigned char probability;//概率，对应客户端文字

	char type;		// 掉落		//0物品 1金钱 2经验 3钻石 4声望 5体力<br>
	int count;
	char catogory;
	int templateId;
	std::string itemName;
	char quality;
	int iconId;
public:
	void decodePacketData(cobra_win::DPacket & packet);
};

//宝箱奖励中宝箱开出数据
class HuntBoxData
{
public:
	char type;		//飘字类型,0物品，1金钱，2经验
	int count;		//数量
	char critValue;	//暴击值
	int itemIconId;	//type == 0时
public:
	HuntBoxData();
	void decodePacketData(cobra_win::DPacket & packet);
};

//寻宝结果
class HuntResult
{
public:
	bool needRespond;		//需要被反馈

	char type;								//遭遇类型，0宝箱，1玩家，2兽人，3夺宝事件
	
	//宝箱奖励时
	std::vector<HuntBoxData *> boxData;		//宝箱奖励数据

	//玩家时
	int playerId;
	char playerIsFriend;
	std::string playerName;
	unsigned short playerLevel;
	int playerHeroIconId;
	int playerHeroShapeId;//谷歌动画
	char playerHeroQuality;
	int playerBtlCapa;

	//兽人时
	std::string orcName;
	unsigned short orcLevel;
	int orcHeroIconId;
	int orcHeroShapeId;//骨骼动画
	char orcHeroQuality;
	int orcBtlCapa;
	int orcBuyPrice;

	//夺宝事件
	unsigned char lieRenIndex;	//猎人的index
	int lieRenShapeId;			//猎人的shapeId

public:
	HuntResult();
	~HuntResult();
	void destroyData();
	void decodePackerData(cobra_win::DPacket & packet);
};

//寻宝遭遇事件状态
class HuntLieRen
{
public:
	unsigned char index;
	std::string name;
	unsigned char isActive;	//0关闭状态，1激活状态
public:
	HuntLieRen();
	void decodePackerData(cobra_win::DPacket & packet);
};

//寻宝信息
class HuntData
{
public:
	short huntTimes;		//剩余寻宝次数
	short maxHuntTimes;		//最大寻宝次数
	std::vector<HuntLieRen *> lieRenVector;
public:
	HuntData();
	~HuntData();
	void destroyData();
	void decodePacketData(cobra_win::DPacket & packet);
};

//巨龙矿区矿主信息
class DragonOwnerData
{
public:
	char index;
	int playerId;
	std::string playerName;
	unsigned short playerLevel;
	int heroIconId;
	char heroQuality;
	int btlCapa;
	unsigned short miningFriendCount;	//挖矿好友数
	unsigned short friendCount;			//总好友数
	char isFriend;		//矿主是我的好友
	char isMining;			//我在这个矿区采矿
	int workedTime;		//累计挖矿时间
	long long tickBegin;
	int outPut;			//累计获得金币
	int outPutPerMin;	//每分钟产出
public:
	DragonOwnerData();
	void workTick();
	void decodePacketData(cobra_win::DPacket & packet);
};

//巨龙矿区
class DragonAreaData
{
public:
	char challengePrice;	//挑战价格
	char slaveCount;		//当前奴隶数量
	char maxSlaveCount;		//最大奴隶数量
	unsigned short improve;			//金币效率加成（*100）
	std::vector<DragonOwnerData *> mineOwnerData;	//矿主信息
public:
	DragonAreaData();
	~DragonAreaData();
	void destroyData();
	void decodePackerData(cobra_win::DPacket & packet);
};

//矮人矿区位置
class DwarvenSitData
{
public:
	char index;		//座位index
	char isNull;	//是否有玩家
	int playerId;	//根据playerID判断是否是自己
	std::string playerName;
	unsigned short playerLevel;
	int heroIconId;
	char heroQuality;	
	int workedTime;		//累计挖矿时间
	long long tickBegin;	//tick计时开始
	int param;			//累计获得/战力
	int outPutPerMin;	//每分钟产出，只发自己的
public:
	DwarvenSitData();
	void workTick();
	void decodePacketData(cobra_win::DPacket & packet);
};

//矮人矿区
class DwarvenAreaData
{
public:
	char slaveCount;		//当前奴隶数量
	char maxSlaveCount;		//最大奴隶数量
	unsigned short improve;			//金币效率加成（*100）
	int leftLootMoney;		//@抢矿花费钱数   
	std::vector<DwarvenSitData *> sitData;		//桌位信息
public:
	DwarvenAreaData();
	~DwarvenAreaData();
	void destroyData();
	void decodePackerData(cobra_win::DPacket & packet);
};

//地精矿区
class GoblinAreaData
{
public:
	char slaveCount;		//当前奴隶数量
	char maxSlaveCount;		//最大奴隶数量
	unsigned short improve;			//金币效率加成（*100）
	int workedTime;		//累计挖矿时间,秒,<0时表示不在挖矿
	long long tickBegin;	//tick计时开始
	int outPut;			//累计产出
	int outPutPerMin;	//每分钟产出
public:
	GoblinAreaData();
	void workTick();
	void decodePacketData(cobra_win::DPacket & packet);
};


//矿区信息
class MineAreaData
{
public:
	char areaType;			//地区类型,0,1,2
	char maxMiningTime;		//最大采集时间
	int outPut;				//金币产量
	unsigned char isMining;	//1 是采集 0是不采集
public:
	MineAreaData();
	void decodePacketData(cobra_win::DPacket & packet);
};

//挖矿主界面信息
class MiningData
{
public:
	std::string mineDesc;		//矿区描述
	std::vector<MineAreaData *> mineArea;	//矿区信息
	short leftHuntTimes;			//剩余采集次数
	short maxHuntTimes;			//最大采集次数
	char lookCd;				//寻宝机会增加冷却时间
public:
	MiningData();
	~MiningData();
	void destroyData();
	void decodePackerData(cobra_win::DPacket & packet);
};


/************************************************************************/
/* This is DataHandler                                                  */
/************************************************************************/

class MiningDataHandler : public IDataHandler, public cobra_win::Singleton2<MiningDataHandler>
{
public:
	MiningData * m_pMiningData;		//挖矿主界面数据
	GoblinAreaData * m_pGoblinAreaData;				//地精矿区数据
	DwarvenAreaData * m_pDwarvenAreaData;			//矮人矿区数据
	DragonAreaData * m_pDragonAreaData;				//巨龙矿区数据
	
	HuntData * m_pHuntData;							//寻宝界面信息
	HuntResult * m_pHuntResult;						//寻宝结果
	HuntLieRenInfo * m_pHuntLieRenData;				//寻宝猎人详细信息

public:
	int m_iFightType;//战斗类型
	int m_iBackArea;//战斗后应该回退的子页面
public:
	bool m_isFBDragon;	//是第一次挑战巨龙

public:
	bool m_bNeedOpenTipsPage2;//需要打开寻宝猎人对话框
public:
	MiningDataHandler();
	virtual ~MiningDataHandler();

protected:

	virtual void handlePacket(IPacket* packet){};

	virtual void onDestroy();

	virtual bool init(){	return true;	};

public:
	void OnAthleticEnd(int type, bool win);

	//矿洞寻宝战斗结束回调
	void OnHuntLieRenQiangDuoAthleticEnd(bool qiangduoWin);

public:
	//进入采矿
	void ToServerEnterMining();
	void ToClientEnterMiningResult();

	//进入地精矿区
	void ToServerEnterGoblinArea();
	void ToClientEnterGoblinAreaResult();

	//结束采集
	void ToServerStopMining();
	void ToClientStopMiningResult();

	//进入矮人矿区
	void ToServerEnterDwarvenArea();
	void ToClientEnterDwarvenAreaResult();

	//矮人矿区抢矿位,结果走战斗
	void ToServerDwarvenLoot(char index);
	void ToClientDwarvenLootResult();

	//进入巨人矿区
	void ToServerEnterDragonArea();
	void ToClientEnterDragonAreaResult();

	//挑战巨人矿区的矿主,结果走战斗
	void ToServerDragonChallengeOwner(char index);
	
	//开始采矿,type.1地精，2矮人，3巨人，，index.所在矿区位置
	void ToServerStartMining(char type, char index);
	void ToClientStartMiningResult(char type, char index);

	//进入寻宝
	void ToServerEnterHuntMining();
	void ToClientEnterHuntMiningResult();

	//寻宝
	void ToServerHuntMining();
	void ToClientHuntMiningResult();

	//抢夺、驱逐,结果走战斗
	void ToServerHuntGrab();

	//加好友，打招呼后领钱
	void ToServerHuntHelloMoney();
	void ToClientHuntHelloMoneyResult();

	//申请加好友后返回
	void ToClientAskFriendResult();

	//花费钻石直接买物品
	void ToServerHuntBuyMineral();
	void ToClientHuntBuyMineralResult();

	//购买寻宝次数
	void ToServerBuyHuntTimes();
	void ToClientBuyHuntTimesResult();

	//请求查看猎人信息
	void ToServerChaKanLieRen(unsigned char index);
	void ToClientChaKanLieRenResult();

	//放弃抢夺猎人
	void ToServerQiangDuoLieRenNo(unsigned char index);
	void ToClientQiangDuoLieRenNoResult(unsigned char index);

	//开始抢夺猎人
	void ToServerQiangDuoLieRenYes(unsigned char index);

	/*
		判断玩家是否在该矿区位置  不在返回0
	*/	
	int PlayerinMineIndex();
};

#define MININGDATAHANDLER (MiningDataHandler::get_instance2())

#endif