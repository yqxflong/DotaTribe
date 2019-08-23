//Name：	ServerInfoData
//Function：充值相关的控制器
//Written By：lvyunlong

#include <cocos2d.h>
#include "../include/DOTATribeApp.h"
#include "../include/HeroAltarControlDataHandler.h"
#include "../include/NFControlsManager.h"
#include "../include/HeroAltarPacket.h"
#include "../include/BagOtherObjectHandler.h"
using namespace std;

TotemData::TotemData()
{
	type_ = 0;			//图腾类型
	level_ = 0;		//等级
	exp_ = 0;			//当前经验值
	addvalue_ = 0;		//实行增加值
	maxExp_ = 0;		//满级经验值
	nextValue_ = 0;	//下一级增加的属性值
}
TotemData::~TotemData()
{
	
}

bool TotemData::decodeTemplatePacketData(cobra_win::DPacket &packet)
{
	packet>>type_;
	packet>>level_;
	packet>>exp_;
	packet>>maxExp_;
	packet>>addvalue_;
	packet>>nextValue_;
	
	return true;
}

AltarData::AltarData()
{
	itemId_ = 0;			//物品Id
	iconId_ = 0;			//图标Id
	quality_ = 0;			//物品品质
	expadd_ = 0;			//消耗一个 增加的经验值
}
AltarData::~AltarData()
{

}

bool AltarData::decodeTemplatePacketData(cobra_win::DPacket &packet)
{
	packet>>itemId_;
	packet>>iconId_;
	packet>>quality_;
	packet>>expadd_;

	return true;
}

DebrisData::DebrisData()
{
	itemId_ = 0;			//物品Id
	count_ = 0;
	quality_ = 0;			//物品品质
}
DebrisData::~DebrisData()
{

}

bool DebrisData::decodeTemplatePacketData(cobra_win::DPacket &packet)
{
	packet>>itemId_;
	packet>>count_;
	packet>>quality_;
	return true;
}



AltarCheckData::AltarCheckData()
{
	level_ = 0;
	memset(addNextvalue_,0,sizeof(addNextvalue_));
	maxExp_ = 0;
}

AltarCheckData::~AltarCheckData()
{

}

bool AltarCheckData::decodeTemplatePacketData(cobra_win::DPacket &packet)
{
	packet>>level_;
	for (int i =0;i<3;i++)
	{
		packet>>addNextvalue_[i];
	}
	packet>>maxExp_;
	return true;
}



HeroAltarControlDataHandler::HeroAltarControlDataHandler(){
	m_CurAltarTypeData = 0;
}

HeroAltarControlDataHandler::~HeroAltarControlDataHandler(){
	//只在析构里删除，应用程序打开时一直存在
	ClearCheckAltarInfoTable();
}

void HeroAltarControlDataHandler::handlePacket(IPacket* packet){

}

bool HeroAltarControlDataHandler::init(){
	m_TotemDataList.clear();
	m_AltarDataList.clear();
	m_DebrisDataList.clear();
	m_pCheckAltarTable.clear();
	m_ClickDebriList.clear();
	m_BinitAltarTable = false;
	return true;
}

void HeroAltarControlDataHandler::onDestroy(){
	ClearTotemInfoList();
	ClearAltarInfoList();
	ClearDebrisInfoList();
	ClearClickDebriList();
}


void HeroAltarControlDataHandler::ClearTotemInfoList()
{
	std::vector<TotemData*>::iterator  posbegin = m_TotemDataList.begin();
	std::vector<TotemData*>::iterator  posend = m_TotemDataList.end();
	for (posbegin;posbegin != posend;posbegin++)
	{
		if (*posbegin)
		{
			delete (*posbegin);
			(*posbegin) = NULL;
		}
	}
	m_TotemDataList.clear();
}

void HeroAltarControlDataHandler::ClearAltarInfoList()
{
	std::vector<AltarData*>::iterator  posbegin = m_AltarDataList.begin();
	std::vector<AltarData*>::iterator  posend = m_AltarDataList.end();
	for (posbegin;posbegin != posend;posbegin++)
	{
		if (*posbegin)
		{
			delete (*posbegin);
			(*posbegin) = NULL;
		}
	}
	m_AltarDataList.clear();
}

void HeroAltarControlDataHandler::ClearDebrisInfoList()
{
	std::vector<DebrisData*>::iterator  posbegin = m_DebrisDataList.begin();
	std::vector<DebrisData*>::iterator  posend = m_DebrisDataList.end();
	for (posbegin;posbegin != posend;posbegin++)
	{
		if (*posbegin)
		{
			delete (*posbegin);
			(*posbegin) = NULL;
		}
	}
	m_DebrisDataList.clear();
}

void HeroAltarControlDataHandler::ClearClickDebriList()
{
	std::vector<DebrisData*>::iterator  posbegin = m_ClickDebriList.begin();
	std::vector<DebrisData*>::iterator  posend = m_ClickDebriList.end();
	for (posbegin;posbegin != posend;posbegin++)
	{
		if (*posbegin)
		{
			delete (*posbegin);
			(*posbegin) = NULL;
		}
	}
	m_ClickDebriList.clear();
}



void HeroAltarControlDataHandler::ClearCheckAltarInfoTable()
{
	std::map<int,AltarCheckData*>::iterator  posbegin = m_pCheckAltarTable.begin();
	std::map<int,AltarCheckData*>::iterator  posend = m_pCheckAltarTable.end();
	for (posbegin;posbegin != posend;posbegin++)
	{
		if (posbegin->second)
		{
			delete posbegin->second;
			posbegin->second = NULL;
		}
	}
	m_pCheckAltarTable.clear();
}

/*
bool HeroAltarControlDataHandler::compareAltarData(AltarData*& a,AltarData*& b)
{
	return a->expadd_ > b->expadd_;

}

void HeroAltarControlDataHandler::SortDebris()
{
	sort(m_AltarDataList.begin(),m_AltarDataList.end(),HeroAltarControlDataHandler::compareAltarData);
}*/

/*
	请求图腾信息
*/
void HeroAltarControlDataHandler::ToServerInfoTotemData()
{
	CSHeroTotemInfoPacket packet;
	packet.Send();
	NFC_showCommunicationWating(true);
}

/*
	请求献祭信息
*/
void HeroAltarControlDataHandler::ToServerInfoAltarData()
{
	CSHeroAltarInfoPacket packet;
	packet.Send();
	NFC_showCommunicationWating(true);
}

/*
	请求碎片信息
*/
void HeroAltarControlDataHandler::ToServerInfoDebris(unsigned char type)
{
	std::vector<DebrisData*>::iterator  posbegin = m_ClickDebriList.begin();
	std::vector<DebrisData*>::iterator  posend = m_ClickDebriList.end();
	unsigned char count = 0;
	for (posbegin;posbegin != posend;posbegin++)
	{
		if (*posbegin)
		{
			if ((*posbegin)->count_ != 0)
			{
				count++;
			}
		}
	}
	CSHeroDebrisAltarPacket packet(type,count);
	packet.Send();
}

void HeroAltarControlDataHandler::RemoveZeroSoulDebrisList()
{
	std::vector<DebrisData*>::iterator  posbegin = m_DebrisDataList.begin();
	std::vector<DebrisData*>::iterator  posend = m_DebrisDataList.end();
	
}

void HeroAltarControlDataHandler::UpdateSoulDebris()
{
	ClearDebrisInfoList();
	ClearClickDebriList();
	std::vector<AltarData*>::iterator  posbegin = m_AltarDataList.begin();
	std::vector<AltarData*>::iterator  posend = m_AltarDataList.end();
	for (posbegin;posbegin != posend;posbegin++)
	{
		if (*posbegin)
		{
			int count = BAGOTHEROBJECTHANDLER->getObjectCountByTemplateId((*posbegin)->itemId_);
			DebrisData* data = new DebrisData;
			data->count_ = count;
			data->itemId_ = (*posbegin)->itemId_;
			data->quality_ = (*posbegin)->quality_;
			m_DebrisDataList.push_back(data);

			DebrisData* data1 = new DebrisData;
			data1->count_ = 0;
			data1->itemId_ = (*posbegin)->itemId_;
			data1->quality_ = (*posbegin)->quality_;
			m_ClickDebriList.push_back(data1);
		}
	}
}

AltarCheckData* HeroAltarControlDataHandler::ByLevelCheckAltarTable(int lv)
{
	std::map<int, AltarCheckData*>::iterator iter = m_pCheckAltarTable.find(lv);
	if (iter == m_pCheckAltarTable.end())
		return NULL;

	return iter->second;
}

void HeroAltarControlDataHandler::ToServerCheckAltarTable()
{
	CSAltarCheckInfoTablePacket packet;
	packet.Send();
}

bool HeroAltarControlDataHandler::AltarDebriLater(int curlevel,int SumExp,int &altarlaterlevel,int &altarlaterexp)
{
	int curlevel_ = curlevel;
	int SumExp_ = SumExp;
	int MaxLevel = AllowMaxAltarLevel();
	int unusual = 0;
	do 
	{
		unusual++;
		if (unusual > 300)
		{
			//防止死循环
			return false;
		}
		if (MaxLevel == curlevel_)
		{
			altarlaterlevel = curlevel_;
			altarlaterexp = 0;
			return true;
		}

		int max = ByLevelCheckMaxExp(curlevel_);
		if (max > SumExp_)
		{
			altarlaterlevel = curlevel_;
			altarlaterexp = SumExp_;
			return false;
		}
		else
		{
			curlevel_++;
			SumExp_ = SumExp_ - max;
		}
	} while (1);
}

int HeroAltarControlDataHandler::ByLevelCheckMaxExp(int lv)
{
	std::map<int, AltarCheckData*>::iterator iter = m_pCheckAltarTable.find(lv);
	int i = m_pCheckAltarTable.size();
	if (iter == m_pCheckAltarTable.end())
		return 0;

	return iter->second->maxExp_;
}

int HeroAltarControlDataHandler::ByLevelCheckAddValue_(int lv,int type)
{
	std::map<int, AltarCheckData*>::iterator iter = m_pCheckAltarTable.find(lv);
	if (iter == m_pCheckAltarTable.end())
		return 0;

	return iter->second->addNextvalue_[type];
}

int HeroAltarControlDataHandler::NeedSoulStoneTopLevel(int tyte,int curlevel,int curExp)
{
	int maxlevel = AllowMaxAltarLevel();
	int addexp =  m_AltarDataList[tyte]->expadd_;	
	int temp = ByLevelCheckMaxExp(curlevel);
	int topexp = temp - curExp;
	for (int i = curlevel+1;i<maxlevel;i++)
	{
		topexp += ByLevelCheckMaxExp(i);		
	}
	int count = topexp/addexp;
	if (topexp%addexp)
		count++;
	return count;
}

bool HeroAltarControlDataHandler::FindClickIsSoulDebri()
{
	std::vector<DebrisData*>::iterator  posbegin = m_ClickDebriList.begin();
	std::vector<DebrisData*>::iterator  posend = m_ClickDebriList.end();
	unsigned char count = 0;
	for (posbegin;posbegin != posend;posbegin++)
	{
		if (*posbegin)
		{
			if ((*posbegin)->count_ != 0 && (*posbegin)->quality_ >= 4)
			{
				return true;
			}
		}
	}
	return false;
}

int HeroAltarControlDataHandler::AllowMaxAltarLevel()
{
	return m_pCheckAltarTable.size() - 1;
}