//Name：HeroSummonControlDataHandler
//Function：英雄召唤信息数据控制器
//Written By：lvyunlong
//Date：20131205

#include "../include/HeroSummonControlDataHandler.h"
#include "../include/HeroSummonPacket.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/GuideSystem.h"
#include <string>
#include "../include/CPublicVarReader.h"
#include "../include/NFControlsManager.h"
#include "../include/NFToolController.h"

using namespace std;

SummonData::SummonData()
{
	memset(Arrcalltype,0,sizeof(Arrcalltype));
	memset(consumeType,0,sizeof(consumeType));
	memset(itemid,0,sizeof(itemid));
	memset(consumeCount,0,sizeof(consumeCount));
	memset(leftTime,0,sizeof(leftTime));
	tenRecruitType = 0;
	tenRecruitConsumeCount = 0;
	mFirstSummon = 0;
}

SummonData::~SummonData()
{

}

void SummonData::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>mFirstSummon;
	unsigned char size = 0;
	packet>>size;
	for (int i=0;i<size;i++)
	{
		packet>>Arrcalltype[i];
		packet>>consumeType[i];
		packet>>itemid[i];
		packet>>consumeCount[i];
		packet>>leftTime[i];
	}

	packet>>tenRecruitType;
	packet>>tenRecruitConsumeCount;
}

TenCallGainData::TenCallGainData()
{
	gaintype_ = 0;
	heroid = 0;
	heroiconid = 0;
	heroName=""; 
	herotype = 0;
	quality = 0;
}

TenCallGainData::~TenCallGainData()
{
	gaintype_ = 0;
	heroid = 0;
	heroiconid = 0;
	heroName=""; 
	herotype = 0;
	quality = 0;
}

void TenCallGainData::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>gaintype_;
	if (gaintype_ == SUMMONNEWHERO)
	{
		packet>>heroid;
		packet>>heroiconid;
		NFC_ParsePacketString(packet,heroName);
		packet>>herotype;
		packet>>quality;
	}
	else if (gaintype_ == SUMMONOLDHERO)
	{
		packet>>heroid;
		packet>>heroiconid;
		NFC_ParsePacketString(packet,heroName);
		packet>>herotype;
		packet>>quality;
	}
	else if (gaintype_ == SUMMONOLDITEM)
	{
		m_RewardData.decodePacketData(packet);
	}
}

GainHeroOrDebriData::GainHeroOrDebriData()
{
	gaintype_ = 0;
	heroId_ = 0;
	herotype_ = 0;
	quality_ = 0;
	rank_ = 0;
	pre_herolv_ = 0;
	pre_heroexp_ = 0;
	pre_maxheroexp_ = 0;
	addexp_ = 0;
	after_herolv_ = 0;
	after_heroexp_ = 0;
	after_maxheroexp_ = 0;

	stritem = "";
	itemcount = 0;
}

GainHeroOrDebriData::~GainHeroOrDebriData()
{

}

void GainHeroOrDebriData::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>gaintype_;
	if (gaintype_ == SUMMONNEWHERO)
	{
		unsigned short tmp_len = 0;
		char * tmpChar = NULL;
		packet>>honorLevel_;
		packet>>heroId_;
		//英雄名
		NFC_ParsePacketString(packet,strheroname);

		packet>>herotype_;
		packet>>quality_;
		packet>>rank_;
		packet>>pre_herolv_;
		packet>>pre_heroexp_;
		packet>>pre_maxheroexp_;
		packet>>addexp_;
		packet>>after_herolv_;
		packet>>after_heroexp_;
		packet>>after_maxheroexp_;
	}
	else if(gaintype_ == SUMMONOLDHERO)
	{
		unsigned short tmp_len = 0;
		char * tmpChar = NULL;
		packet>>heroId_;
		//英雄名
		NFC_ParsePacketString(packet,strheroname);
		packet>>herotype_;
		packet>>quality_;
		packet>>rank_;
		NFC_ParsePacketString(packet,stritem);
		packet>>itemcount;
	}
	else if(gaintype_ == SUMMONOLDITEM)
	{
		m_RewardData.decodePacketData(packet);
	}
}

HeroSummonControlDataHandler::HeroSummonControlDataHandler(){
	m_pSunmonInfoData = NULL;
	m_pCurGainData = NULL;
	
}

HeroSummonControlDataHandler::~HeroSummonControlDataHandler(){
	delete m_pSunmonInfoData;
}

void HeroSummonControlDataHandler::handlePacket(IPacket* packet){
	
}

bool HeroSummonControlDataHandler::init(){
	m_pSunmonInfoData = new SummonData();
	m_pGainList.clear();
	m_pTenCallList.clear();
	return true;
}

void HeroSummonControlDataHandler::onDestroy(){

	ClearGainList();
	m_pTenCallList.clear();
}

void HeroSummonControlDataHandler::ClearGainList()
{
	std::vector<GainHeroOrDebriData*>::iterator	 posbegin = m_pGainList.begin();
	std::vector<GainHeroOrDebriData*>::iterator	 posend = m_pGainList.end();
	for (;posbegin != posend;posbegin++)
	{
		if (*posbegin != NULL)
		{
			delete *posbegin;
			*posbegin = NULL;
		}
	}
	m_pGainList.clear();
}

void HeroSummonControlDataHandler::ToServerRequestSummonInfo()
{
	CSHeroSummonInfoPacket packet;
	packet.Send();
	NFC_showCommunicationWating(true);
}
void HeroSummonControlDataHandler::ToServerCallHero(unsigned char type,unsigned char times,unsigned char freetype)
{
	CSHeroSoulSummonPacket packet(type,times,freetype);
	packet.Send();
	//显示等待
	NFC_showCommunicationWating(true);
}

void HeroSummonControlDataHandler::CallBackShowNewOrOldHero()
{
	//===新手引导=====
	GUIDESYSTEM->Next();
	//
	std::vector<GainHeroOrDebriData*>::iterator	 posbegin = m_pGainList.begin();
	std::vector<GainHeroOrDebriData*>::iterator	 posend = m_pGainList.end();
	if (posbegin==posend)
	{
		m_pGainList.clear();
		return;
	}
	for (;posbegin != posend;posbegin++)
	{
		if ((*posbegin))
		{
			if ((*posbegin)->gaintype_ == SUMMONNEWHERO)
			{
				EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_GAINHEROWINDOW_);

			}
			else if((*posbegin)->gaintype_ == SUMMONOLDHERO)
			{
				EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_GAINSOULDEBRIWINDOW_);
			}
			else if((*posbegin)->gaintype_ == SUMMONOLDITEM)
			{
				EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_GAINCALLITEMWINDOW_);
			}
			m_pCurGainData = (*posbegin);
			return;
		}
	}
}

void HeroSummonControlDataHandler::RemoveGainListFornt()
{
	std::vector<GainHeroOrDebriData*>::iterator	 posbegin = m_pGainList.begin();
	if(posbegin == m_pGainList.end())
		return;
	delete (*posbegin);
	(*posbegin) = NULL;
	m_pGainList.erase(posbegin);
}
