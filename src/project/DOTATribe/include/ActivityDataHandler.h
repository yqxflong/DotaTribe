// Name :		ActivityDataHandler.h
// Function:	�����
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef _DOTATRIBE_ActivityDataHandler_H_
#define _DOTATRIBE_ActivityDataHandler_H_

 
#include <include/mem/DPacket.h>
#include <vector>
#include <string>
#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include "../include/CommonDataDef.h"
#include "../include/ActivityDataManager.h"
#include "../include/CPublicVarReader.h" 
#include "../include/ActivityDataManager.h"


using namespace std;
 
class  ActivityInfoItem
{
	default_construct_destroy(ActivityInfoItem)
    property_unit_ronly(unsigned short,m_nActivityItemID,ActivityItemID)				//�ID
	property_unit_ronly(std::string,m_nActivityStrName,ActivityStrName)						//�����
	property_unit_ronly(short,m_nActivityItemType,ActivityItemType)						//�����
	property_unit_ronly(int,m_nActivityItemIconID,ActivityItemIconID)					//�Icon
	property_unit_rw(Activity *,m_pActivityConfig,ActivityConfig)						//�������̬����
	property_unit_rw(IByte,m_isActivityopen,ActivityOpen)								//��Ƿ���� //0��δ��� ������δ��ȡ����

public:
	void  decodePacket(cobra_win::DPacket & packet);
};

class  ActivityServerMap
{
	default_construct_destroy(ActivityServerMap) 
public:
	ActivityInfoItem *					 getActivityItemByID(short activityItemID);
	ActivityInfoItem *					 getDefaulActivityItem();
	ActivityInfoItem *					 getActivityItemByIndex(int index);
	int									 getActivityItemsCount();
	void								 decodePacket(cobra_win::DPacket & packet);
	std::map<short,ActivityInfoItem *> & getActivityRefMap();
private:
	void  destroyData();
private:
	std::map<short,ActivityInfoItem *>		m_mActivityMap;
}; 
 
class ActivityDataHandler : public IDataHandler, public cobra_win::Singleton2<ActivityDataHandler>
{ 
	default_construct_vdestroy(ActivityDataHandler)
	property_unit_ronly(ActivityServerMap *,m_pActivityServerMap,ActivityServerMap)
public:
	virtual void onDestroy();
	virtual bool init(); 
	size_t       getServerActivitysCount();
	void		 decodePacket(cobra_win::DPacket & packet);

	void HasSurplusActivity();
private:
	void         destroyData();
};

//////////////////////////////////////////////////////////////////////////
//��Ȫ��ڴ�����
//////////////////////////////////////////////////////////////////////////

class SpringActivityDataHandler : public IDataHandler, public cobra_win::Singleton2<SpringActivityDataHandler>
{
	default_construct_vdestroy(SpringActivityDataHandler)
	property_unit_rw(unsigned char,m_SpringIsOpen,SpringIsOpen)
	property_unit_rw(unsigned int,m_SpringActiviId,SpringActiviId)
	property_unit_ronly(unsigned char,m_EnergyIsGet,EnergyIsGet)
public:
	virtual  void onDestroy();
	virtual  bool init();
public:
	void   decodePacket(cobra_win::DPacket & packet);
};

#define SPRINGACTIVITYDATAHANDLER   SpringActivityDataHandler::get_instance2()

 
 

/************************************************************************/
/* �׳�����                                                          */
/************************************************************************/
class RechGiftDataObject{
public:
	RechGiftDataObject();
	~RechGiftDataObject();

public:
	int count_;			//����<br>
	unsigned char type_;	//���� 0��Ʒ 1��Ǯ 2���� 3��ʯ 4���� 5���� <br>
	unsigned char catogory; //��Ʒ����
	int templateId_;	//��Ʒģ��ID<br>
	std::string name_;	//��Ʒ����
	unsigned char quality_;		//Ʒ��<br>
	int iconId_;			//ͼ��ID<br>
};

class FirstRechDataHandler : public IDataHandler, public cobra_win::Singleton2<FirstRechDataHandler>
{
public:
	property_unit_rw(unsigned int,m_FirstRechActiviId,FirstRechActiviId);
	std::string m_strDescribe;
	unsigned char m_RewardNum;
	std::vector<RechGiftDataObject*> m_RechList;
	bool m_isRechGift;
public:
	FirstRechDataHandler();
	virtual ~FirstRechDataHandler();
	virtual void onDestroy();
	virtual bool init();
	/*
		�������
	*/
	void ClearDataList();
	/*
		��ȡ��Ϣ
	*/
	void ReadGiftListInfo(cobra_win::DPacket & packet);
	/*
		��ȡ�׳���Ϣ
	*/
	void ToServerInfoFirstRech();
	/*
		��ȡ�׳���Ʒ
	*/
	void ToServerGetGift();
};

#define FIRSTRECHDATAHANDLER   FirstRechDataHandler::get_instance2()

/************************************************************************/
/* ÿ�յ�¼�����                                                      */
/************************************************************************/

class LoginRewardData{
public:
	LoginRewardData();
	~LoginRewardData();
public:
	
	std::vector<PRewardItemNode> m_RewardVec;
};



class LoginRewardDataHandler : public IDataHandler, public cobra_win::Singleton2<LoginRewardDataHandler>
{
public:
	unsigned char m_Hasreward;
	 property_unit_rw(unsigned int,m_LoginRewardActiviId,LoginRewardActiviId);
public:	
	std::vector<LoginRewardData*> m_RewardList; 
public:
	LoginRewardDataHandler();
	virtual ~LoginRewardDataHandler();
public:
	virtual void onDestroy();
	virtual bool init();
public:
	void ClearDataList();
	void ToServerRewardList(cobra_win::DPacket & packet);
	void ToServerGetReward();
};
#define LOGINREWARDDATAHANDLER   LoginRewardDataHandler::get_instance2()

//////////////////////////////////////////////////////////////////////////
////����������ڴ�����
//////////////////////////////////////////////////////////////////////////
class  LevelUpRewardInfoItem
{
  default_construct_destroy(LevelUpRewardInfoItem)
  property_unit_rw(bool,m_bCanReward,CanReward)
  property_unit_rw(int,m_rewardLevel,RewardLevel)
  property_unit_rw(IByte,m_rewardItemCount,RewardItemCount)
  property_unit_rw(std::vector<PRewardItemNode>,m_rewardVector,RewardVector)
public:
  void  decodePacket(cobra_win::DPacket & packet);
};

  
class  LevelUpRewardData
{
    default_construct_destroy(LevelUpRewardData) 
	property_unit_rw(short,m_rewardInfoCount,RewardInfoCount)
	property_unit_rw(std::vector<LevelUpRewardInfoItem *>,m_rewardInfoVector,RewardInfoVector)
public:
	void  decodePacket(cobra_win::DPacket & packet);
	void  sortAndCombin();
	void  removeRewardInfoItem(int rewardLevel);
	void  updateRewardData(int playerLevel);
};

class  LevelUpRewardActivityDataHandler : public IDataHandler, public cobra_win::Singleton2<LevelUpRewardActivityDataHandler>
{
  default_construct_vdestroy(LevelUpRewardActivityDataHandler)
  property_unit_rwc(LevelUpRewardData *,m_pLevelUpRewardData,LevelUpRewardDatas)
  property_unit_rw(unsigned int,m_LevelUpRewardActiviId,LevelUpRewardActiviId);
public: 
	virtual void onDestroy();
	virtual bool init();
public:
	void   ToServerActivityRequest(); 
	bool   UpdateRewardData();
	void   DecodePacket(cobra_win::DPacket & packet);
	void   DestroyData();
};

#define  LEVELUPREWARDDATAHANDLER      (LevelUpRewardActivityDataHandler::get_instance2())

//////////////////////////////////////////////////////////////////////////
////�ɳ��ƻ��
class GrowupRewardData
{
	default_construct_destroy(GrowupRewardData)
	//�����ȼ�
	property_unit_rw(int,m_rewardLevel,RewardLevel)
	//�Ƿ���ȡ
	property_unit_rw(IByte,m_bhasReward,HasReward)
	//������������
	 property_unit_rw(std::vector<PRewardItemNode>,m_rewardVector,RewardVector);
public:
	void  decodePacket(cobra_win::DPacket & packet);
};

class GrowupPlanDataHandler : public IDataHandler, public cobra_win::Singleton2<GrowupPlanDataHandler>
{
	 default_construct_vdestroy(GrowupPlanDataHandler)
public:
	 property_unit_rw(unsigned int,m_GrowupPlanActiviId,GrowupPlanActiviId);
public: 
	virtual void onDestroy();
	virtual bool init();
public:
	IByte m_isBuyPlan;		//0:δ���� 1:�ѹ���
	std::vector<GrowupRewardData*> m_GrowupRewardVector;
public:
	void ClearDataList();
	void ReceiveGrowupInfo(cobra_win::DPacket & packet);
	void ToServerBuyGrowPlan();
	void ToServerGetPlanReward(int level);
	void GetPlanRewardBack(int level);
	int ByLevelPlanRewardListIndex(int level);
};

#define  GROWUPPLANDATAHANDLER      GrowupPlanDataHandler::get_instance2()

//////////////////////////////////////////////////////////////////////////

 
//////////////////////////////////////////////////////////////////////////
// �һ���ڴ�����
//////////////////////////////////////////////////////////////////////////
class  TemplateItemInfoData
{
	default_construct_destroy(TemplateItemInfoData)
	property_unit_ronly(IByte,m_ItemType,ItemType)
	property_unit_ronly(int,m_ItemNeedCount,ItemNeedCount)
	property_unit_ronly(IByte,m_ItemCatogory,ItemNeedCatogory)
	property_unit_ronly(int,m_ItemTemplateID,ItemTemplateID)
	property_unit_ronly(std::string,m_ItemName,ItemName)
	property_unit_ronly(IByte,m_ItemQuality,ItemQuality)
	property_unit_ronly(int,m_ItemIconID,ItemIconID)
	property_unit_ronly(int,m_ItemHadCount,ItemHadCount)
public:
	void   decodePacket(cobra_win::DPacket & packet);
	void   exchangeSuccess();
};

class  ExchangeItemInfo
{
	default_construct_destroy(ExchangeItemInfo)
	property_unit_ronly(short,m_nExchangeItemID,ExchamgeItemID)
	property_unit_ronly(std::vector<TemplateItemInfoData *>,m_vNeedItemsVector,NeedItemsVector)
	property_unit_ronly(RewardItemNode *,m_pTargetItem,TargetItem)
	property_unit_rw(short,m_nLeftExchangeTimes,LeftExchangeTimes)
	property_unit_ronly(IByte,m_uVipLevel,VipLevel)
public:
	void  destroyData();
	void  decodePacket(cobra_win::DPacket & packet);
	void  exchangeSuccess();
};
 
//////////////////////////////////////////////////////////////////////////
//  �һ������Ϣ���
//////////////////////////////////////////////////////////////////////////

class  ExchangeInfoData
{
	default_construct_destroy(ExchangeInfoData)
    property_unit_rw(short,m_nActivityID,ActivityID)
	property_unit_rw(short,m_nActivityType,ActivityType)
	property_unit_ronly(std::string,m_sActivityDesc,ActivityDesc)
	property_unit_ronly(int,m_nLeftActivityMinute,LeftActivityMinute)
	property_unit_ronly(std::vector<ExchangeItemInfo *>,m_vExchangeItemVector,ExchangeItemVector)
public:
	void  decodePacket(cobra_win::DPacket & packet);
	void  decodeSubPacket(cobra_win::DPacket & packet);
	void  resetActivityEndCountDown();
	void  destroyData();
	bool  exchangeSuccessByID(short exchangeID);
};

//////////////////////////////////////////////////////////////////////////
//  �һ���ڴ�����
//////////////////////////////////////////////////////////////////////////
class ExchangeActivityDataHandler : public IDataHandler, public cobra_win::Singleton2<ExchangeActivityDataHandler>
{
	default_construct_vdestroy(ExchangeActivityDataHandler)
public: 
	virtual void		onDestroy();
	virtual bool		init();
public: 
	/*
	 �����һ���Ϣ��
	*/
	void			    decodePacket(cobra_win::DPacket & packet);
	/*
	�����һ��ɹ���
	*/
	void				decodeExchangeSuccessPacket(cobra_win::DPacket & packet);
	/*
	��ȡ�һ���Ϣ
	*/
	ExchangeInfoData *  getExchangeInfoItemByID(short itemID);
	/*
	�����ڴ�����
	*/
	void   destroyData(); 
private:
	/* 
	 ���ͺ�����
	*/
	std::map<short,ExchangeInfoData *>		m_mExchangeInfoDataMap; 
}; 
#define  EXCHANGEACTIVITYDATAHANDLER      (ExchangeActivityDataHandler::get_instance2())

//////////////////////////////////////////////////////////////////////////
//  Vip�������
//////////////////////////////////////////////////////////////////////////
class VipGiftItem
{
	default_construct_destroy(VipGiftItem)
public:
	property_unit_ronly(IByte,m_cViplevel,VipLevel)
		property_unit_ronly(std::string ,m_strName,VipName)
		property_unit_ronly(int,m_iIconId,IconId)
		property_unit_ronly(int,m_iOriginalPrice,OriginalPrice)
		property_unit_ronly(int,m_iDiscountPrice,DiscountPrice)
		property_unit_ronly(int,m_iPreviewId,PreviewId)
public:
	void  decodePacket(cobra_win::DPacket & packet);

};

class VipGiftActivityHandler : public IDataHandler, public cobra_win::Singleton2<VipGiftActivityHandler>
{
	default_construct_destroy(VipGiftActivityHandler)
public: 
	virtual void		onDestroy();
	virtual bool		init();
public:
	std::vector<VipGiftItem*> m_VipItemList;
	std::vector<VipGiftItem*> m_ActiviVipShowList;
public:
	void  decodePacket(cobra_win::DPacket & packet);
	void ClearList();
public:
	void PreviewGift(int previewId);
	void BuyGift(IByte viplevel);
	void ToServerInfoVipGift();
	void ShowActiviVipList();
	VipGiftItem* ByLevelData(int level);
	void RemoveData(unsigned char level);

};
#define VIPGIFTACTIVITYHANDLER VipGiftActivityHandler::get_instance2()
#endif