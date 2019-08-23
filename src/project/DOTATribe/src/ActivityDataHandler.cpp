// Name :		ActivityDataHandler.h
// Function:	活动数据
// Author :		zhoushaonan
// Maintainer:  zhoushaonan
#include <cocos2d.h>
#include "../include/ActivityDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/CPublicVarReader.h"
#include "../include/FirstRechGiftPacket.h"
#include "../include/NFControlsManager.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/LoginActivityPacket.h"
#include "../include/GrowupPlanPacket.h"
#include "../include/VipGiftPacket.h"
#include "../include/NFToolController.h"
//////////////////////////////////////////////////////////////////////////
ActivityInfoItem::ActivityInfoItem()
{
	m_nActivityItemID = 0;
	m_nActivityItemType = 0;
	m_nActivityItemIconID = 0;
	m_pActivityConfig = NULL; 
}

ActivityInfoItem::~ActivityInfoItem()
{ 
}

void  ActivityInfoItem::decodePacket(cobra_win::DPacket & packet)
{
	packet.read(m_nActivityItemID);
	NFC_ParsePacketString(packet,m_nActivityStrName);
	packet.read(m_nActivityItemType);
	packet.read(m_nActivityItemIconID);
    m_pActivityConfig = ActivityManager::get_instance2()->GetDataByType((int)m_nActivityItemType);
	packet.read(m_isActivityopen);
}
////////////////////////////////////////////////////////////////////////// 

ActivityServerMap::ActivityServerMap()
{
	m_mActivityMap.clear();
}

ActivityServerMap::~ActivityServerMap()
{
	destroyData();
} 
 
void  ActivityServerMap::destroyData()
{
	std::map<short,ActivityInfoItem *>::iterator  activity_iter = m_mActivityMap.begin();
	while(activity_iter != m_mActivityMap.end())
	{
		delete activity_iter->second;
		++ activity_iter;
	}
	m_mActivityMap.clear();
}
 
ActivityInfoItem *   ActivityServerMap::getActivityItemByID(short activityItemID)
{
	std::map<short,ActivityInfoItem *>::iterator  activity_iter = m_mActivityMap.begin();
	 
	while(activity_iter != m_mActivityMap.end())
	{
		if(activity_iter->second->getActivityItemID()==activityItemID)
		return activity_iter->second;
		++activity_iter; 
	}
	return NULL;
}
int				 ActivityServerMap::getActivityItemsCount()
{
	return m_mActivityMap.size();
}
void			 ActivityServerMap::decodePacket(cobra_win::DPacket & packet)
{
	destroyData();
	IByte  activityCount = 0;
	packet.read(activityCount);
	COMMON_BEIGIN_ARRAY(IByte,activityCount)
		ActivityInfoItem * pActivityItem = new ActivityInfoItem();
	    if(pActivityItem)
		{
			pActivityItem->decodePacket(packet);
			m_mActivityMap.insert(std::map<short,ActivityInfoItem *>::value_type(pActivityItem->getActivityItemID(),pActivityItem));
		}
	COMMON_END_ARRAY
}

ActivityInfoItem *  ActivityServerMap::getDefaulActivityItem()
{ 
	if(!m_mActivityMap.empty())
	{
		return  m_mActivityMap.begin()->second;
	}
	return  NULL;
}

ActivityInfoItem *   ActivityServerMap::getActivityItemByIndex(int index)
{
	int  tmpIndex = 0;
	std::map<short,ActivityInfoItem *>::iterator  activity_iter = m_mActivityMap.begin();
	while(activity_iter != m_mActivityMap.end())
	{ 
	   if(tmpIndex == index)
	  { 
		  return activity_iter->second;
	  }
	   tmpIndex++;
	   ++activity_iter;
	}
	return  NULL;
}

std::map<short,ActivityInfoItem *> &  ActivityServerMap::getActivityRefMap()
{
	return m_mActivityMap;
}


//////////////////////////////////////////////////////////////////////////
 
ActivityDataHandler::ActivityDataHandler()
{ 
	m_pActivityServerMap = new ActivityServerMap();
}

ActivityDataHandler::~ActivityDataHandler()
{ 
	destroyData();
}

size_t       ActivityDataHandler::getServerActivitysCount()
{
	if(m_pActivityServerMap)
	{
		return m_pActivityServerMap->getActivityItemsCount();
	}
	return 0;
}
void		ActivityDataHandler::decodePacket(cobra_win::DPacket & packet)
{
	destroyData();
    m_pActivityServerMap = new ActivityServerMap();
	m_pActivityServerMap->decodePacket(packet);
} 

void ActivityDataHandler::onDestroy()
{ 
} 
void     ActivityDataHandler::destroyData()
{
	if(m_pActivityServerMap)
	{ 
		delete m_pActivityServerMap;
		m_pActivityServerMap = NULL;
	} 
}
bool ActivityDataHandler::init()
{
	return true;
}

void ActivityDataHandler::HasSurplusActivity()
{
	std::map<short,ActivityInfoItem *> &  activityServerMap = getActivityServerMap()->getActivityRefMap();
	std::map<short,ActivityInfoItem *>::iterator activity_iter = activityServerMap.begin();
	bool hassurplus = false;
	while(activity_iter != activityServerMap.end())
	{	
		if (activity_iter->second->getActivityOpen() != 0)
		{
			hassurplus = true;
			break;
		}
		activity_iter++;
	}
	if (!hassurplus)
	{
		ROLEINFODATAHANDLER->m_pRIData->activityprompt_ = 0;
	}
}



//////////////////////////////////////////////////////////////////////////
//温泉活动内存数据
//////////////////////////////////////////////////////////////////////////
SpringActivityDataHandler::SpringActivityDataHandler()
{
	m_SpringIsOpen = 0;
	m_EnergyIsGet = 0;
}
SpringActivityDataHandler::~SpringActivityDataHandler()
{ 
}
void SpringActivityDataHandler::onDestroy()
{ 
}

bool SpringActivityDataHandler::init()
{
	return true;
}
void  SpringActivityDataHandler::decodePacket(cobra_win::DPacket & packet)
{
	packet.read(m_SpringIsOpen);
	packet.read(m_EnergyIsGet);
}
   
/************************************************************************/
/* 首充活动奖励                                                          */
/************************************************************************/
RechGiftDataObject::RechGiftDataObject()
{
	count_ = 0;			//数量<br>
	type_ = 0;	//类型 0物品 1金钱 2经验 3钻石 4声望 5体力 <br>
	catogory = 0; //物品类型
	templateId_ = 0;	//物品模板ID<br>
	quality_ = 0;		//品质<br>
	iconId_ = 0;			//图标ID<br>
	
}

RechGiftDataObject::~RechGiftDataObject()
{
	
}

FirstRechDataHandler::FirstRechDataHandler()
{
	m_strDescribe = "";
	m_RewardNum = 0;
	m_isRechGift = false;
}

FirstRechDataHandler::~FirstRechDataHandler()
{

}

void FirstRechDataHandler::onDestroy()
{
	ClearDataList();
}

bool FirstRechDataHandler::init()
{
	return true;
}

void FirstRechDataHandler::ClearDataList()
{
	std::vector<RechGiftDataObject*>::iterator posbegin = m_RechList.begin(); 
	std::vector<RechGiftDataObject*>::iterator posend = m_RechList.end(); 
	for (posbegin;posbegin != posend;posbegin++)
	{
		if (*posbegin)
		{
			delete (*posbegin);
			(*posbegin) = NULL;
		}
	}
	m_RechList.clear();
}

void FirstRechDataHandler::ReadGiftListInfo(cobra_win::DPacket & packet)
{
	ClearDataList();
	//解析描述
	NFC_ParsePacketString(packet,m_strDescribe);
	//奖励数量
	packet>>m_RewardNum;
	for (int i=0;i<m_RewardNum;i++)
	{
		RechGiftDataObject* temp = new RechGiftDataObject;
		packet>>temp->type_;
		packet>>temp->count_;
		if (0 == temp->type_)
		{
			packet>>temp->catogory;
			packet>>temp->templateId_;
			NFC_ParsePacketString(packet,temp->name_);
			packet>>temp->quality_;
			packet>>temp->iconId_;
		}
		m_RechList.push_back(temp);
	}
}

void FirstRechDataHandler::ToServerInfoFirstRech()
{
	CSFirstRechInfoPacket packet;
	packet.Send();
	NFC_showCommunicationWating(true);
}

void FirstRechDataHandler::ToServerGetGift()
{
	CSGetFirstGiftPacket packet;
	packet.Send();
}

/************************************************************************/
/* 每日登录活动奖励                                                      */
/************************************************************************/

LoginRewardData::LoginRewardData()
{
	m_RewardVec.clear();
}
LoginRewardData::~LoginRewardData()
{

}

LoginRewardDataHandler::LoginRewardDataHandler()
{
	m_Hasreward = 0;
}

LoginRewardDataHandler::~LoginRewardDataHandler()
{

}

void LoginRewardDataHandler::onDestroy()
{
	ClearDataList();
}

bool LoginRewardDataHandler::init()
{
	return true;
}

void LoginRewardDataHandler::ClearDataList()
{
	std::vector< LoginRewardData* >::iterator it = m_RewardList.begin(); 
	std::vector< LoginRewardData* >::iterator it_end = m_RewardList.end(); 
	for (it;it!=it_end;it++)
	{
		LoginRewardData* temp = (*it);
		if (temp)
		{
			std::vector<PRewardItemNode>::iterator posbeg = temp->m_RewardVec.begin();
			std::vector<PRewardItemNode>::iterator posend = temp->m_RewardVec.end();
			for (;posbeg!=posend;posbeg++)
			{
				CC_SAFE_DELETE((*posbeg));
			}
			temp->m_RewardVec.clear();
			CC_SAFE_DELETE(temp);
		}
	}
	m_RewardList.clear();
}

void LoginRewardDataHandler::ToServerRewardList(cobra_win::DPacket & packet)
{
	ClearDataList();
	unsigned short infosize = 0;
	packet>>infosize;
	for (int i =0;i<infosize;i++)
	{
		unsigned char count = 0;
		packet>>count;
		LoginRewardData* pData = new LoginRewardData;
		for (int j =0;j<count;j++)
		{
			PRewardItemNode pTemp = new RewardItemNode;
			pTemp->decodePacketData(packet);
			pData->m_RewardVec.push_back(pTemp);
		}
		m_RewardList.push_back(pData);
	}
}

void LoginRewardDataHandler::ToServerGetReward()
{
	CSGetLoginRewardPacket packet;
	packet.Send();
	NFC_showCommunicationWating(true);
}

//////////////////////////////////////////////////////////////////////////
LevelUpRewardInfoItem::LevelUpRewardInfoItem()
{
	m_rewardLevel = 0;
	m_rewardItemCount = 0;
	m_bCanReward = false;
	m_rewardVector.clear();
}
LevelUpRewardInfoItem::~LevelUpRewardInfoItem()
{
	size_t infoItemCount = m_rewardVector.size();
	COMMON_BEIGIN_ARRAY(size_t,infoItemCount)
		delete m_rewardVector.at(index);
	COMMON_END_ARRAY
	m_rewardVector.clear();
}

void  LevelUpRewardInfoItem::decodePacket(cobra_win::DPacket & packet)
{ 
	packet.read(m_rewardLevel);
	packet.read(m_rewardItemCount);
	COMMON_BEIGIN_ARRAY(short,m_rewardItemCount)
		PRewardItemNode  pRewardItemNode = new RewardItemNode();
	    if(pRewardItemNode)
		{ 
			pRewardItemNode->decodePacketData(packet);
			m_rewardVector.push_back(pRewardItemNode);
		}
	COMMON_END_ARRAY
}

LevelUpRewardData::LevelUpRewardData()
{
	m_rewardInfoCount = 0;
	m_rewardInfoVector.clear();
}

LevelUpRewardData::~LevelUpRewardData()
{ 
	size_t rewardInfoCount = m_rewardInfoVector.size();
	COMMON_BEIGIN_ARRAY(size_t,rewardInfoCount)
		delete m_rewardInfoVector.at(index);
	COMMON_END_ARRAY
	m_rewardInfoVector.clear();
}

void  LevelUpRewardData::decodePacket(cobra_win::DPacket & packet)
{
	packet.read(m_rewardInfoCount);
	COMMON_BEIGIN_ARRAY(short,m_rewardInfoCount)
		LevelUpRewardInfoItem * pLevelUpRewardItem = new LevelUpRewardInfoItem();
		if(pLevelUpRewardItem)
		{ 
			pLevelUpRewardItem->decodePacket(packet);
			m_rewardInfoVector.push_back(pLevelUpRewardItem);
		}
	COMMON_END_ARRAY

    //合并排列数据
	sortAndCombin();
}

 
void  LevelUpRewardData::sortAndCombin()
{  
	std::map<int,LevelUpRewardInfoItem *> levelUpMap;
	size_t rewardInfoCount = m_rewardInfoVector.size();
	COMMON_BEIGIN_ARRAY(size_t,rewardInfoCount)
		levelUpMap.insert(std::map<int,LevelUpRewardInfoItem *>::value_type(m_rewardInfoVector.at(index)->getRewardLevel(),m_rewardInfoVector.at(index)));
	COMMON_END_ARRAY
    std::vector<LevelUpRewardInfoItem * >  tmpCanRewardLevelUpVector;
	std::vector<LevelUpRewardInfoItem * > tmpUnRewardLevelUpVector; 
    short  playerLevel = RoleInfoDataHandler::get_instance2()->m_pRIData->level_;
    std::map<int,LevelUpRewardInfoItem *>::iterator iter = levelUpMap.begin();
    while( iter != levelUpMap.end() )
    {
	   if(playerLevel>=iter->second->getRewardLevel())
	   {  
		   iter->second->setCanReward(true);
		   tmpCanRewardLevelUpVector.push_back(iter->second);
	   }
	   else
	   {
		   tmpUnRewardLevelUpVector.push_back(iter->second);
	   }
	   ++iter;
    }
    m_rewardInfoVector.clear();
    rewardInfoCount =  tmpCanRewardLevelUpVector.size();
    COMMON_BEIGIN_ARRAY(size_t,rewardInfoCount)
	   m_rewardInfoVector.push_back(tmpCanRewardLevelUpVector.at(index));
    COMMON_END_ARRAY

    rewardInfoCount =  tmpUnRewardLevelUpVector.size();
    COMMON_BEIGIN_ARRAY(size_t,rewardInfoCount)
	   m_rewardInfoVector.push_back(tmpUnRewardLevelUpVector.at(index));
    COMMON_END_ARRAY 
   
}

void  LevelUpRewardData::removeRewardInfoItem(int rewardLevel)
{ 
	//todo 
	std::vector<LevelUpRewardInfoItem *>::iterator iter = m_rewardInfoVector.begin();
	while( iter != m_rewardInfoVector.end() )
	{
		if((*iter)->getRewardLevel() == rewardLevel)
		{ 
			delete (*iter);
			m_rewardInfoVector.erase(iter);
			return ;
		}
		++iter;
	}
} 

void  LevelUpRewardData::updateRewardData(int playerLevel)
{  
	size_t  rewardSize = m_rewardInfoVector.size();
	COMMON_BEIGIN_ARRAY(size_t,rewardSize)
		LevelUpRewardInfoItem * pLevelUpRewardInfoItem = m_rewardInfoVector.at(index);
		if(pLevelUpRewardInfoItem&&pLevelUpRewardInfoItem->getRewardLevel()<=playerLevel)
		{  
			pLevelUpRewardInfoItem->setCanReward(true);
		} 
		else
		{
			pLevelUpRewardInfoItem->setCanReward(false);
		}
	COMMON_END_ARRAY
}


LevelUpRewardActivityDataHandler::LevelUpRewardActivityDataHandler()
{ 
	 m_pLevelUpRewardData = NULL;
}

LevelUpRewardActivityDataHandler::~LevelUpRewardActivityDataHandler()
{  
	DestroyData();
}
  
void   LevelUpRewardActivityDataHandler::DecodePacket(cobra_win::DPacket & packet)
{ 
	DestroyData();
	m_pLevelUpRewardData = new LevelUpRewardData();
	m_pLevelUpRewardData->decodePacket(packet);
}

bool  LevelUpRewardActivityDataHandler::init()
{ 
	return  true;
}
 
void  LevelUpRewardActivityDataHandler::onDestroy()
{ 
}

void  LevelUpRewardActivityDataHandler::ToServerActivityRequest()
{
	//to do
}

bool  LevelUpRewardActivityDataHandler::UpdateRewardData()
{
	//to do
	return true;
}


void   LevelUpRewardActivityDataHandler::DestroyData()
{
	if(m_pLevelUpRewardData)
	{
		delete m_pLevelUpRewardData;
		m_pLevelUpRewardData =NULL;
 	}
}  
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
GrowupRewardData::GrowupRewardData()
{
	m_rewardLevel = 0;
	m_bhasReward = 0;

};

GrowupRewardData::~GrowupRewardData()
{
	size_t infoItemCount = m_rewardVector.size();
	COMMON_BEIGIN_ARRAY(size_t,infoItemCount)
		CC_SAFE_DELETE(m_rewardVector.at(index));
	COMMON_END_ARRAY
	m_rewardVector.clear();
};

void  GrowupRewardData::decodePacket(cobra_win::DPacket & packet)
{
	packet.read(m_rewardLevel);
	packet.read(m_bhasReward);
	IByte count = 0;
	packet.read(count);
	for (int i =0;i<count;i++)
	{
		PRewardItemNode pTemp = new RewardItemNode;
		pTemp->decodePacketData(packet);
		m_rewardVector.push_back(pTemp);
	}
}

GrowupPlanDataHandler::GrowupPlanDataHandler()
{

}

GrowupPlanDataHandler::~GrowupPlanDataHandler()
{

}

void GrowupPlanDataHandler::onDestroy()
{
	ClearDataList();
}

bool GrowupPlanDataHandler::init()
{
	return true;
}

void GrowupPlanDataHandler::ClearDataList()
{
	std::vector<GrowupRewardData*>::iterator it_begin = m_GrowupRewardVector.begin();
	std::vector<GrowupRewardData*>::iterator it_end = m_GrowupRewardVector.end();
	for (;it_begin!=it_end;it_begin++)
	{
		CC_SAFE_DELETE((*it_begin));
	}
	m_GrowupRewardVector.clear();
}


void GrowupPlanDataHandler::ReceiveGrowupInfo(cobra_win::DPacket & packet)
{
	ClearDataList();
	packet.read(m_isBuyPlan);
	unsigned short sizecount = 0;
	packet>>sizecount;
	for (int i=0;i<sizecount;i++)
	{
		GrowupRewardData* temp = new GrowupRewardData;
		temp->decodePacket(packet);
		m_GrowupRewardVector.push_back(temp);
	}
}
void GrowupPlanDataHandler::ToServerBuyGrowPlan()
{
	CSBuyGrowupPlanPacket packet;
	packet.Send();
	NFC_showCommunicationWating(true);
}
void GrowupPlanDataHandler::ToServerGetPlanReward(int level)
{
	CSGetGrowupPlanRewardPacket packet(level);
	packet.Send();
	NFC_showCommunicationWating(true);
}

void GrowupPlanDataHandler::GetPlanRewardBack(int level)
{
	std::vector<GrowupRewardData*>::iterator it_begin = m_GrowupRewardVector.begin();
	std::vector<GrowupRewardData*>::iterator it_end = m_GrowupRewardVector.end();
	bool hasAllReward = true;
	for (;it_begin!=it_end;it_begin++)
	{
		if (*it_begin)
		{
			if ((*it_begin)->getHasReward() ==0 &&((*it_begin)->getRewardLevel()!= level))
			{
				hasAllReward = false;
			}
			if ((*it_begin)->getRewardLevel() == level)
			{
				(*it_begin)->setHasReward(1);
			}
		}
	}
	if (hasAllReward)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_DELETE_ACTIVITY_);
	}
	else
	{
		unsigned int id = getGrowupPlanActiviId();
		ActivityInfoItem* item = ActivityDataHandler::get_instance2()->getActivityServerMap()->getActivityItemByID(id);
		item->setActivityOpen(item->getActivityOpen() - 1);
		if (item->getActivityOpen() == 0)
		{
			ActivityDataHandler::get_instance2()->HasSurplusActivity();
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEEFFECT_ACTIVITY_,_to_event_param_(id));
		}
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_BTNTEXT_GROWUPPLANACTIVITYWINDOW_,_to_event_param_(level));
	}
}

int GrowupPlanDataHandler::ByLevelPlanRewardListIndex(int level)
{
	std::vector<GrowupRewardData*>::iterator it_begin = m_GrowupRewardVector.begin();
	std::vector<GrowupRewardData*>::iterator it_end = m_GrowupRewardVector.end();
	size_t index = 0;
	for (;it_begin!=it_end;it_begin++)
	{
		if (*it_begin)
		{
			if ((*it_begin)->getRewardLevel() == level)
			{
				return index;
			}
			index++;
		}
	}
	return -1;
}

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//  
//////////////////////////////////////////////////////////////////////////
TemplateItemInfoData::TemplateItemInfoData()
{
	m_ItemType = 0;
	m_ItemNeedCount = 0;
	m_ItemCatogory = 0;
	m_ItemTemplateID = 0;
	m_ItemName = "";
	m_ItemQuality = 0;
	m_ItemIconID = 0;
	m_ItemHadCount = 0;
}
TemplateItemInfoData::~TemplateItemInfoData()
{

}

void  TemplateItemInfoData::decodePacket(cobra_win::DPacket & packet)
{
	packet.read(m_ItemType);
	packet.read(m_ItemNeedCount);
	if(m_ItemType == 0)
	{
		packet.read(m_ItemCatogory);
		packet.read(m_ItemTemplateID);
		NFC_ParsePacketString(packet,m_ItemName);
		packet.read(m_ItemQuality);
		packet.read(m_ItemIconID);
	}
	packet.read(m_ItemHadCount);
}

void   TemplateItemInfoData::exchangeSuccess()
{
   m_ItemHadCount -= m_ItemNeedCount;
   if(m_ItemHadCount < 0)
   m_ItemHadCount = 0;
}


ExchangeItemInfo::ExchangeItemInfo()
{
	m_nExchangeItemID = 0;
	m_vNeedItemsVector.clear();
	m_pTargetItem = NULL;
	m_nLeftExchangeTimes = 0;
	m_uVipLevel = 0;
}

ExchangeItemInfo::~ExchangeItemInfo()
{ 
	destroyData();
}	


void  ExchangeItemInfo::destroyData()
{
	size_t  itemSize = m_vNeedItemsVector.size();
	COMMON_BEIGIN_ARRAY(size_t,itemSize)
		 delete  m_vNeedItemsVector.at(index);
	COMMON_END_ARRAY
	m_vNeedItemsVector.clear();

	if(m_pTargetItem)
	{
		delete m_pTargetItem;
		m_pTargetItem = NULL;
	} 
}
void  ExchangeItemInfo::decodePacket(cobra_win::DPacket & packet)
{
	destroyData();
	packet.read(m_nExchangeItemID);
	IByte  itemCount = 0;
	packet.read(itemCount);
	COMMON_BEIGIN_ARRAY(IByte,itemCount)
		TemplateItemInfoData * pItemData = new TemplateItemInfoData();
	    if(pItemData)
		{
			pItemData->decodePacket(packet);
			m_vNeedItemsVector.push_back(pItemData);
		}
	COMMON_END_ARRAY

	m_pTargetItem = new RewardItemNode();
	if(m_pTargetItem)
	{
		m_pTargetItem->decodePacketData(packet);
	}
	packet.read(m_nLeftExchangeTimes);
	packet.read(m_uVipLevel); 
} 
 
void  ExchangeItemInfo::exchangeSuccess()
{
	m_nLeftExchangeTimes--;
	if(m_nLeftExchangeTimes < 0)
	m_nLeftExchangeTimes = 0;
	size_t needItemsCount = m_vNeedItemsVector.size();
	COMMON_BEIGIN_ARRAY(size_t,needItemsCount)
		m_vNeedItemsVector.at(index)->exchangeSuccess();
	COMMON_END_ARRAY		
}


ExchangeInfoData::ExchangeInfoData()
{
	m_nActivityID = 0;
	m_nActivityType = 0;
	m_sActivityDesc = "";
	m_nLeftActivityMinute = 0;
	m_vExchangeItemVector.clear();
  
}

ExchangeInfoData::~ExchangeInfoData()
{ 
	destroyData();
}

void  ExchangeInfoData::destroyData()
{
	size_t NeedItemsCount = m_vExchangeItemVector.size();
	COMMON_BEIGIN_ARRAY(size_t,NeedItemsCount)
		delete m_vExchangeItemVector.at(index);
	COMMON_END_ARRAY 
	m_vExchangeItemVector.clear();
}
void  ExchangeInfoData::decodePacket(cobra_win::DPacket & packet)
{
	destroyData();
	packet.read(m_nActivityID);
	packet.read(m_nActivityType); 
	NFC_ParsePacketString(packet,m_sActivityDesc);
	packet.read(m_nLeftActivityMinute); 
	short exchangeItemCount = 0;
	COMMON_BEIGIN_ARRAY(short,exchangeItemCount)
		ExchangeItemInfo * pExchangeItemInfo = new ExchangeItemInfo();
		if(pExchangeItemInfo)
		{
			pExchangeItemInfo->decodePacket(packet);
			m_vExchangeItemVector.push_back(pExchangeItemInfo);
		}
	COMMON_END_ARRAY 
}

void  ExchangeInfoData::decodeSubPacket(cobra_win::DPacket & packet)
{
	destroyData(); 
	NFC_ParsePacketString(packet,m_sActivityDesc);
	packet.read(m_nLeftActivityMinute); 
	short exchangeItemCount = 0;
	packet.read(exchangeItemCount);
	COMMON_BEIGIN_ARRAY(short,exchangeItemCount)
		ExchangeItemInfo * pExchangeItemInfo = new ExchangeItemInfo();
	if(pExchangeItemInfo)
	{
		pExchangeItemInfo->decodePacket(packet);
		m_vExchangeItemVector.push_back(pExchangeItemInfo);
	}
	COMMON_END_ARRAY 
}


void  ExchangeInfoData::resetActivityEndCountDown()
{
	m_nLeftActivityMinute = 0;
}

bool  ExchangeInfoData::exchangeSuccessByID(short exchangeID)
{
	size_t  exchangeItemsCount = m_vExchangeItemVector.size();
	COMMON_BEIGIN_ARRAY(size_t,exchangeItemsCount)
		 if(m_vExchangeItemVector.at(index)->getExchamgeItemID()==exchangeID)
		 {
			 ExchangeItemInfo * pExchangeItemInfo = m_vExchangeItemVector.at(index);
			 if(pExchangeItemInfo)
			 {
				 pExchangeItemInfo->exchangeSuccess();
			 } 
			 return true;
		 }
	COMMON_END_ARRAY
	return false;
}
 

//////////////////////////////////////////////////////////////////////////
ExchangeActivityDataHandler::ExchangeActivityDataHandler()
{ 
	m_mExchangeInfoDataMap.clear();
} 

ExchangeActivityDataHandler::~ExchangeActivityDataHandler()
{ 
	destroyData();
}

void ExchangeActivityDataHandler::onDestroy()
{ 

}

bool ExchangeActivityDataHandler::init()
{
	return true;
}

void   ExchangeActivityDataHandler::decodePacket(cobra_win::DPacket & packet)
{  
	//首先解析ID 然后更新ID解析 
	short  activityID =  0;
	short  activtyType = 0;
	packet.read(activityID);
	packet.read(activtyType);
	std::map<short,ExchangeInfoData *>::iterator  activity_iter = m_mExchangeInfoDataMap.find(activityID);
	if(activity_iter != m_mExchangeInfoDataMap.end())
	{
		activity_iter->second->setActivityID(activityID);
		activity_iter->second->setActivityType(activtyType); 
		activity_iter->second->decodeSubPacket(packet);
	}
	else
	{
		ExchangeInfoData * pExchangeInfoData = new ExchangeInfoData();
		pExchangeInfoData->setActivityID(activityID);
		pExchangeInfoData->setActivityType(activtyType); 
	    pExchangeInfoData->decodeSubPacket(packet);
		m_mExchangeInfoDataMap.insert(std::map<short,ExchangeInfoData *>::value_type(pExchangeInfoData->getActivityID(),pExchangeInfoData));
	}
	//PostEvent
	int activityTypeInt = activityID;
	EventSystem::get_instance2()->PushEvent2(_TYPED_EVENT_UPDATE_EXCHANGEACTIVITYWINDOW_,_to_event_param_(activityTypeInt));
} 

void   ExchangeActivityDataHandler::destroyData()
{ 
	std::map<short,ExchangeInfoData *>::iterator  activity_iter = m_mExchangeInfoDataMap.begin();
	while(activity_iter != m_mExchangeInfoDataMap.end())
	{
		delete activity_iter->second;
		++ activity_iter;
	}
	m_mExchangeInfoDataMap.clear();
}



ExchangeInfoData *  ExchangeActivityDataHandler::getExchangeInfoItemByID(short itemID)
{
	std::map<short,ExchangeInfoData *>::iterator  activity_iter = m_mExchangeInfoDataMap.find(itemID);
	if(activity_iter != m_mExchangeInfoDataMap.end())
	{
	   return activity_iter->second;
	}
	return NULL;
}
//////////////////////////////////////////////////////////////////////////

/*
解析兑换成功包
*/
void		ExchangeActivityDataHandler::decodeExchangeSuccessPacket(cobra_win::DPacket & packet)
{ 
	 short  activityID = 0;
	 short  exchangeID = 0;
	 packet.read(activityID);
	 packet.read(exchangeID);
	  
	 //获取获得类型然后
	 ActivityInfoItem * pActivityInfo = ActivityDataHandler::get_instance2()->getActivityServerMap()->getActivityItemByID(activityID);
	 if(pActivityInfo)
	 {
		 ExchangeInfoData * pExchangeInfoData = getExchangeInfoItemByID(pActivityInfo->getActivityItemID());
		 if(pExchangeInfoData)
		 {
			 pExchangeInfoData->exchangeSuccessByID(exchangeID);
			 //to do 
			 //Post Event Msg
			 EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_REFRESH_EXCHANGEACTIVITYWINDOW_);
		 }
	 }

}

//////////////////////////////////////////////////////////////////////////
//  Vip礼包数据
//////////////////////////////////////////////////////////////////////////
VipGiftItem::VipGiftItem()
{
	m_cViplevel = 0;
	m_strName = "";
	m_iIconId = 0;
	m_iOriginalPrice = 0;
	m_iDiscountPrice = 0;
	m_iPreviewId = 0;
}

VipGiftItem::~VipGiftItem()
{
	m_cViplevel = 0;
	m_strName = "";
	m_iIconId = 0;
	m_iOriginalPrice = 0;
	m_iDiscountPrice = 0;
	m_iPreviewId = 0;
}

void  VipGiftItem::decodePacket(cobra_win::DPacket & packet)
{
	packet>>m_cViplevel;
	NFC_ParsePacketString(packet,m_strName);
	packet>>m_iIconId;
	packet>>m_iOriginalPrice;
	packet>>m_iDiscountPrice;
	packet>>m_iPreviewId;
}

VipGiftActivityHandler::VipGiftActivityHandler()
{

}

VipGiftActivityHandler::~VipGiftActivityHandler()
{

}

void VipGiftActivityHandler::decodePacket(cobra_win::DPacket & packet)
{
	IByte count=0;
	packet>>count;
	ClearList();
	for (int i =0;i<count;i++)
	{
		VipGiftItem* temp = new VipGiftItem;
		temp->decodePacket(packet);
		m_VipItemList.push_back(temp);
	}
}

void	VipGiftActivityHandler::onDestroy()
{
	ClearList();
}

bool	VipGiftActivityHandler::init()
{
	m_VipItemList.clear();
	return true;
}

void VipGiftActivityHandler::ClearList()
{
	std::vector<VipGiftItem*>::iterator pos_begin = m_VipItemList.begin();
	std::vector<VipGiftItem*>::iterator pos_end = m_VipItemList.end();
	for (pos_begin;pos_begin!=pos_end;pos_begin++)
	{
		CC_SAFE_DELETE((*pos_begin));
	}
	m_VipItemList.clear();
}


void VipGiftActivityHandler::PreviewGift(int previewId)
{
	CSVipGiftPreViewPacket packet(previewId);
	packet.Send();
	NFC_showCommunicationWating(true);
}

void VipGiftActivityHandler::BuyGift(IByte viplevel)
{
	CSVipGiftBuyPacket packet(viplevel);
	packet.Send();
	NFC_showCommunicationWating(true);
}

void VipGiftActivityHandler::ToServerInfoVipGift()
{
	CSVipGiftInfoPacket packet;
	packet.Send();
	NFC_showCommunicationWating(true);
}

void VipGiftActivityHandler::ShowActiviVipList()
{
	m_ActiviVipShowList.clear();
	int viplevel = ROLEINFODATAHANDLER->m_pRIData->vipLevel_;
	if (viplevel >7)
	{
		m_ActiviVipShowList = m_VipItemList;
	}
	else 
	{
		int showvip = 0;
		if (viplevel < 4)
		{
			showvip = 5;
		}
		else
		{
			showvip = viplevel+2;
		}
		std::vector<VipGiftItem*>::iterator it = m_VipItemList.begin();
		std::vector<VipGiftItem*>::iterator itend = m_VipItemList.end();
		for (it;it!=itend;it++)
		{
			if ((*it)->getVipLevel() <= showvip)
			{
				m_ActiviVipShowList.push_back((*it));
			}
		}
	}
}

VipGiftItem* VipGiftActivityHandler::ByLevelData(int level)
{
	std::vector<VipGiftItem*>::iterator it = m_ActiviVipShowList.begin();
	std::vector<VipGiftItem*>::iterator itend = m_ActiviVipShowList.end();
	for (it;it != itend;it++)
	{
		if ((*it)->getVipLevel() == level)
		{
			return (*it);
		}
	}
	return NULL;
}

void VipGiftActivityHandler::RemoveData(unsigned char level)
{
	std::vector<VipGiftItem*>::iterator it = m_ActiviVipShowList.begin();
	std::vector<VipGiftItem*>::iterator itend = m_ActiviVipShowList.end();
	for (it;it != itend;it++)
	{
		if ((*it)->getVipLevel() == level)
		{
			m_ActiviVipShowList.erase(it);
			return;
		}
	}
}