//Name：HeroSummonControlDataHandler
//Function：英雄召唤信息数据控制器
//Written By：lvyunlong
//Date：20131205

#ifndef   _DOTATRIBE_HEROSUMMONCONTROLDATAHANDLER_H_
#define   _DOTATRIBE_HEROSUMMONCONTROLDATAHANDLER_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <string>
#include <map>
#include <vector>
#include <include/mem/DPacket.h>
#include "../include/CommonDataDef.h"

#define  SUMMONNEWHERO		0
#define  SUMMONOLDHERO		1
#define  SUMMONOLDITEM		2


#define  ONCE_TAKECARD		1
#define  TEN_TAKECARD		10

#define  COMMON_SUMMON		0
//#define  HIGH_SUMMON		1
#define  GOLD_SUMMON		1

#define  HERO_POWER			0
#define  HERO_QUICK			1
#define  HERO_INTELIGENCE	2

class SummonData
{
public:
	SummonData();
	~SummonData();
public:
	// 0:首抽 1：非首次
	int mFirstSummon;
	//0 : 普通 1:精英 2:神圣
	unsigned char Arrcalltype[2];
	//花费类型 0: 物品 3:钻石
	int consumeType[2];
	//抽卡道具ID 钻石-1
	int itemid[2];
	//单次抽取花费数量
	unsigned short consumeCount[2];
	//剩余时间 -1:无倒计时 0：有一次免费 n:剩余时间（秒）
	int leftTime[2];
	//十连抽类型（神圣）
	unsigned char tenRecruitType;
	unsigned short tenRecruitConsumeCount;//十连抽花费钻石数量
public:
	void decodePacketData(cobra_win::DPacket & packet);
};


class GainHeroOrDebriData{
public:
	GainHeroOrDebriData();
	~GainHeroOrDebriData();
public:
	unsigned char gaintype_;
	int heroId_;
	unsigned char herotype_;
	unsigned char quality_;
	unsigned char rank_;
	unsigned short pre_herolv_;
	int pre_heroexp_;
	int pre_maxheroexp_;
	unsigned short addexp_;
	unsigned short after_herolv_;
	int after_heroexp_;
	int after_maxheroexp_;
	std::string strheroname;
	int honorLevel_;

	std::string stritem;
	unsigned short itemcount;
	
	RewardItemNode  m_RewardData;
public:
	void decodePacketData(cobra_win::DPacket & packet);

};

class TenCallGainData{
public:
	TenCallGainData();
	~TenCallGainData();
public:
	unsigned char gaintype_;
	int heroid;
	int heroiconid;
	std::string  heroName; 
	unsigned char herotype;
	unsigned char quality;
	RewardItemNode  m_RewardData;
	
public:
	void decodePacketData(cobra_win::DPacket & packet);
};

class HeroSummonControlDataHandler:public IDataHandler,public cobra_win::Singleton2<HeroSummonControlDataHandler>{
public:
	std::vector<GainHeroOrDebriData*>  m_pGainList;
	SummonData* m_pSunmonInfoData;
	GainHeroOrDebriData* m_pCurGainData;
	std::vector<TenCallGainData>	m_pTenCallList;
public:
	HeroSummonControlDataHandler();
	virtual ~HeroSummonControlDataHandler();
	/*
		当收到服务器相关包的时候，用此函数把对应包的数据转化成对应的数据结构
		存入map中，用于之后的内存中的增删改查
	*/
	virtual void handlePacket(IPacket* packet);
	virtual bool init();
	virtual void onDestroy();
public:
	void ClearGainList();
public:
	
	void ToServerRequestSummonInfo();
	void ToServerCallHero(unsigned char type,unsigned char times,unsigned char freetype);
	void CallBackShowNewOrOldHero();
	void RemoveGainListFornt();
	void ReadTenCallData(cobra_win::DPacket & packet);

};
#define HEROSUMMONCONTROLDATAHANDLER	 HeroSummonControlDataHandler::get_instance2()

#endif