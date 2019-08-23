//Name��HeroSummonControlDataHandler
//Function��Ӣ���ٻ���Ϣ���ݿ�����
//Written By��lvyunlong
//Date��20131205

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
	// 0:�׳� 1�����״�
	int mFirstSummon;
	//0 : ��ͨ 1:��Ӣ 2:��ʥ
	unsigned char Arrcalltype[2];
	//�������� 0: ��Ʒ 3:��ʯ
	int consumeType[2];
	//�鿨����ID ��ʯ-1
	int itemid[2];
	//���γ�ȡ��������
	unsigned short consumeCount[2];
	//ʣ��ʱ�� -1:�޵���ʱ 0����һ����� n:ʣ��ʱ�䣨�룩
	int leftTime[2];
	//ʮ�������ͣ���ʥ��
	unsigned char tenRecruitType;
	unsigned short tenRecruitConsumeCount;//ʮ���黨����ʯ����
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
		���յ���������ذ���ʱ���ô˺����Ѷ�Ӧ��������ת���ɶ�Ӧ�����ݽṹ
		����map�У�����֮����ڴ��е���ɾ�Ĳ�
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