//Name : EquipTrainView
//Function：装备洗练界面
//Written By : 方骏
//AnchorPoint:  (0,0) can not change
//Date: 130813

#include "../include/EquipTrainView.h"
#include "../include/NFControlsManager.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
//
#include "../include/SysLangDataManager.h"
#include "../include/UIViewDataManger.h"
//
#include "../include/IDStringDataManager.h"
#include "../include/EquipTrainDataHandler.h"
#include "../include/BagEquipDataHandler.h"
#include "../include/RoleEquipDataHandler.h"
#include "../include/ResourceIDDataManager.h"
#include "../include/CPublicVarReader.h"
#include <vector>
#include <map>
#include "../include/CMenuItemSprite.h"
#include "../include/MessageBoxWindow.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/MaskNode.h"
#include "../include/EngineSystem.h"
#include "../include/CCardsStarProgress.h"
#include "../include/FontStyleDataManager.h"
#include "../include/NFAnimationController.h"

//
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

EquipTrainView::EquipTrainView()
:m_pCurEquip(NULL)
,m_pAnimationPlayNode(NULL)
,m_pAnimationGrayLayer(NULL)
,m_bInOneKeyTrainMode(false)
,m_iWillUnLockAttributeIndex(-1)
{
	
}

EquipTrainView::~EquipTrainView()
{
	m_pCurEquip = NULL;
}


void EquipTrainView::_initLayout(){
 	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kEQUIPTRAINVIEW,this);

	//初始化动画特效
	_initAnimationEffect();

	//隐藏锁
	for(int i = tLock1; i <= tLock4; ++i)
	{
		CCNode * node = this->getChildByTag(i);
		node->setVisible(false);
	}

	_mapAllBtn();

	_enableTrainBtn(false);

	//显示锁物品个数
	_showLockObjectNum();
}


void EquipTrainView::_initAnimationEffect()
{
	//特效数据
	//m_pAnimationPlayNode = cocos2d::CCSprite::create();
	MaskNode * effectNode = (MaskNode *)this->getChildByTag(tAnimationNode);
	m_pAnimationPlayNode = NFC_getAnimationSprite(effectNode->GetViewData().colorR_, false, false, this);
	effectNode->addChild(m_pAnimationPlayNode);

}


void  EquipTrainView::EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr)
{

	//洗练
	Train();
	
}

void EquipTrainView::_mapAllBtn(){
	//洗练按钮
	CCMenu * menu = (CCMenu *)this->getChildByTag(tTrainBtn);
	CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(tTrainBtn);
	item->setTarget(this, menu_selector(EquipTrainView::On_ClickEvent));

	//一键洗练
	menu = (CCMenu *)this->getChildByTag(tOneTrainBtn);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(tOneTrainBtn);
	item->setTarget(this, menu_selector(EquipTrainView::On_ClickEvent));

	//锁
	for(int i = tLock1; i <= tLock4; ++i)
	{
		menu = (CCMenu *)this->getChildByTag(i);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(i);
		item->setTarget(this, menu_selector(EquipTrainView::On_Lock_ClickEvent));
	}
}

void EquipTrainView::_enableTrainBtn(bool enabled)
{
	CCMenu* menu=(CCMenu*)this->getChildByTag(tTrainBtn);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(tTrainBtn);
	cc->setEnabled(enabled);
}

void EquipTrainView::_enableOneKeyTrainBtn(bool enabled)
{
	CCMenu* menu=(CCMenu*)this->getChildByTag(tOneTrainBtn);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(tOneTrainBtn);
	cc->setEnabled(enabled);
}

void EquipTrainView::_setBtnSelected(int key, bool selected)
{
	CCMenu * menu = (CCMenu *)this->getChildByTag(key);
	CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(key);
	if(selected)
		item->selected(true);
	else
		item->unselected();
	
	item->setIsSelected(selected);

}

void EquipTrainView::_setResultAreaVisiable(bool visiable)
{
	for(int i = tNewAttri1; i <= tNewAttri4Max; ++i)
	{
		_setNodeVisible(i, this, visiable);
	}
}

void EquipTrainView::_setLabel(int key, cocos2d::CCNode * pParent,const char* txt){
	CCLabelTTF* cc=(CCLabelTTF*)pParent->getChildByTag(key);
	cc->setString(txt);
}

void EquipTrainView::_setNodeVisible(int key,bool isVisible){
	CCNode* cc = this->getChildByTag(key);
	cc->setVisible(isVisible);
}

void EquipTrainView::_setNodeVisible(int key, CCNode * father,bool isVisible){
	CCNode* cc=father->getChildByTag(key);
	cc->setVisible(isVisible);
}

void EquipTrainView::_showLeftAttribute()
{
	//attribute
	for(int i = tLock1; i <= tAttri4Max; ++i)
	{
		CCNode * node = this->getChildByTag(i);
		node->setVisible(false);
	}

	//箭头
	for(int i = tArrow1; i <= tArrow4; ++i)
	{
		NFC_showNode(i, this, false);
	}

	if(EQUIPTRAINDATAHANDLER->GetCurEquipId() < 0)
		return;

	BagEquipData * bed = EQUIPTRAINDATAHANDLER->GetCurEquip();
	if(!bed)
		return;

	//标定属性和锁位置
	_mapAttriToLockPosition();

	CCLabelTTF * ttf = NULL;
	CCNode * node = NULL;
	char str[128] = "";

	std::map<int, int>::iterator lit = EQUIPTRAINDATAHANDLER->m_mapAttributeLockPosition.begin();
	std::map<int, int>::iterator lit_end = EQUIPTRAINDATAHANDLER->m_mapAttributeLockPosition.end();
	for(; lit != lit_end; ++lit)
	{
		if(bed->attribute_->mapPropertyList_[lit->second] > 0)
		{
			std::string name = IDSTRINGDATAMANAGER->GetIDStringByID(3, lit->second);
			sprintf(str, SysLangDataManager::get_instance2()->GetSysLangById(2018).c_str(), name.c_str(), bed->attribute_->mapPropertyList_[lit->second]);
			NFC_setLabelString(lit->first + 4, this, str, true);//属性名称+增加

			sprintf(str, SysLangDataManager::get_instance2()->GetSysLangById(2019).c_str(), bed->attributeMAX_->mapPropertyList_[lit->second]);
			NFC_setLabelString(lit->first + 4 + 4, this, str, true);//属性最大

			FSData * dd = NULL;
			int xf = 100 * ((float)bed->attribute_->mapPropertyList_[lit->second] / bed->attributeMAX_->mapPropertyList_[lit->second]);
			if(xf < 60)
			{//绿色
				dd = FONTSTYLEDATAMANAGER->getDataByID(92);
			}
			else if(xf >= 60 && xf < 80)
			{//蓝色
				dd = FONTSTYLEDATAMANAGER->getDataByID(93);
			}
			else if(xf >= 80 && xf < 100)
			{//紫色
				dd = FONTSTYLEDATAMANAGER->getDataByID(94);
			}
			else if(xf == 100)
			{//橙色
				dd = FONTSTYLEDATAMANAGER->getDataByID(95);
			}
			NFC_setLabelColor(lit->first + 4, this, ccc3(dd->colorR_, dd->colorG_, dd->colorB_));
			NFC_setLabelColor(lit->first + 4 + 4, this, ccc3(dd->colorR_, dd->colorG_, dd->colorB_));

			//显示锁
			node = this->getChildByTag(lit->first);
			node->setVisible(true);

			//显示箭头
			NFC_showNode(lit->first + 33, this, true);
		}

	}

}

void EquipTrainView::_showLeftAttributeWhenOneKey()
{
	CCLabelTTF * ttf = NULL;
	CCNode * node = NULL;
	char str[128] = "";

	std::map<int, int> & map_ = EQUIPTRAINDATAHANDLER->m_mapOneKeyTrainLastAttribute;
	std::map<int, int> & map_Max_ = EQUIPTRAINDATAHANDLER->m_mapOneKeyTrainLastAttributeMax;


	std::map<int, int>::iterator lit = EQUIPTRAINDATAHANDLER->m_mapOneKeyAttributeLockPosition.begin();
	std::map<int, int>::iterator lit_end = EQUIPTRAINDATAHANDLER->m_mapOneKeyAttributeLockPosition.end();
	for(; lit != lit_end; ++lit)
	{
		if(map_[lit->second] > 0)
		{
			std::string name = IDSTRINGDATAMANAGER->GetIDStringByID(3, lit->second);
			sprintf(str, SysLangDataManager::get_instance2()->GetSysLangById(2018).c_str(), name.c_str(), map_[lit->second]);
			NFC_setLabelString(lit->first + 4, this, str, true);//属性名称+增加

			sprintf(str, SysLangDataManager::get_instance2()->GetSysLangById(2019).c_str(), map_Max_[lit->second]);
			NFC_setLabelString(lit->first + 4 + 4, this, str, true);//属性最大

			FSData * dd = NULL;
			int xf = 100 * ((float)map_[lit->second] / map_Max_[lit->second]);
			if(xf < 60)
			{//绿色
				dd = FONTSTYLEDATAMANAGER->getDataByID(92);
			}
			else if(xf >= 60 && xf < 80)
			{//蓝色
				dd = FONTSTYLEDATAMANAGER->getDataByID(93);
			}
			else if(xf >= 80 && xf < 100)
			{//紫色
				dd = FONTSTYLEDATAMANAGER->getDataByID(94);
			}
			else if(xf == 100)
			{//橙色
				dd = FONTSTYLEDATAMANAGER->getDataByID(95);
			}
			NFC_setLabelColor(lit->first + 4, this, ccc3(dd->colorR_, dd->colorG_, dd->colorB_));
			NFC_setLabelColor(lit->first + 4 + 4, this, ccc3(dd->colorR_, dd->colorG_, dd->colorB_));

			//显示锁
			node = this->getChildByTag(lit->first);
			node->setVisible(true);

			//显示箭头
			NFC_showNode(lit->first + 33, this, true);
		}

	}
}

void EquipTrainView::_mapAttriToLockPosition()//将属性和锁的位置绑定
{
	BagEquipData * bed = EQUIPTRAINDATAHANDLER->GetCurEquip();
	if(!bed)
		return;
	std::map<int, int>::iterator it = bed->attribute_->mapPropertyList_.begin();
	std::map<int, int>::iterator it_end = bed->attribute_->mapPropertyList_.end();
	std::map<int, int>::iterator lit = EQUIPTRAINDATAHANDLER->m_mapAttributeLockPosition.begin();
	std::map<int, int>::iterator lit_end = EQUIPTRAINDATAHANDLER->m_mapAttributeLockPosition.end();

	std::map<int, int> temp;
	for(int i = tLock1; i <= tLock4; ++i)
	{
		temp.insert(std::map<int, int>::value_type(i, 0));
	}

	//第一次，标定已有的相同的属性
	for(; it != it_end; ++it)
	{
		if(it->second > 0)
		{
			for(; lit != lit_end; ++lit)
			{
				if(it->first == lit->second)
				{
					temp[lit->first] = 1;
					break;
				}
			}
		}
		
		lit = EQUIPTRAINDATAHANDLER->m_mapAttributeLockPosition.begin();
	}

	it = bed->attribute_->mapPropertyList_.begin();
	it_end = bed->attribute_->mapPropertyList_.end();
	lit = EQUIPTRAINDATAHANDLER->m_mapAttributeLockPosition.begin();
	lit_end = EQUIPTRAINDATAHANDLER->m_mapAttributeLockPosition.end();
	std::map<int, int>::iterator tempit = temp.begin();
	std::map<int, int>::iterator tempit_end = temp.end();
	//第二次，将不相同的属性插入到位置队列中
	for(; it != it_end; ++it)
	{
		if(it->second > 0)
		{
			for(; lit != lit_end; ++lit)
			{
				if(it->first == lit->second)
				{
					break;
				}
			}
			if(lit == lit_end)
			{
				for(; tempit != tempit_end; ++tempit)
				{
					if(tempit->second == 0)
					{
						tempit->second = 1;
						EQUIPTRAINDATAHANDLER->m_mapAttributeLockPosition[tempit->first] = it->first;
						break;
					}
				}
			}
		}

		tempit = temp.begin();
		lit = EQUIPTRAINDATAHANDLER->m_mapAttributeLockPosition.begin();

	}

}

void EquipTrainView::_showMoney()//显示花费金钱
{
	//计算洗练花费金钱
	BagEquipData * bb = EQUIPTRAINDATAHANDLER->GetCurEquip();
	int money = EQUIPTRAINDATAHANDLER->m_iAttriPrice;

	//显示金钱
	CCLabelTTF * ttf = (CCLabelTTF *)this->getChildByTag(tGoldValue);
	char str[128] = {0};
	sprintf(str, "%d", money);
	ttf->setString(str);

	if(m_bInOneKeyTrainMode)
	{
		if(ROLEINFODATAHANDLER->m_pRIData->money_ < money)
		{
			NFC_setLabelColor(tGoldValue, this, color_BagRed);
		}
	}
	else
	{
		if(ROLEINFODATAHANDLER->m_pRIData->money_ >= money)
		{
			if(bb->attribute_->mapPropertyList_.size() == 0)
			{
				NFC_setLabelColor(tGoldValue, this, color_BagNormal);
				_enableTrainBtn(false);
			}
			else
			{
				NFC_setLabelColor(tGoldValue, this, color_BagNormal);
				_enableTrainBtn(true);
			}
			

			if(EQUIPTRAINDATAHANDLER->IsCurEquipCanOneKeyTrain())
				_enableOneKeyTrainBtn(true);
			else
				_enableOneKeyTrainBtn(false);
		}
		else
		{
			NFC_setLabelColor(tGoldValue, this, color_BagRed);
			_enableTrainBtn(false);

			_enableOneKeyTrainBtn(false);
		}
	}

}

void EquipTrainView::_showLockObjectNum()//显示锁物品个数
{
	//获得属性锁个数，属性锁的物品
	int num = BAGOTHEROBJECTHANDLER->getObjectCountByTemplateId(CLIENTCONSTDATAMANGER->getValueByKey(ATTRIBUTE_TEMPLATEID));

	//显示锁物品个数
	CCLabelTTF * ttf = (CCLabelTTF *)this->getChildByTag(tLockValue);
	char str[128] = {0};
	sprintf(str, "%d", num);
	ttf->setString(str);
}


void EquipTrainView::_showLockStatus()
{

	//设置锁按钮选中
	BagEquipData * bb = EQUIPTRAINDATAHANDLER->GetCurEquip();
	int mlock = tLock1;

	if(!bb)
		return;

	std::map<int, int>::iterator it = EQUIPTRAINDATAHANDLER->m_mapAttributeLockPosition.begin();
	std::map<int, int>::iterator it_end = EQUIPTRAINDATAHANDLER->m_mapAttributeLockPosition.end();
	std::vector<int>::iterator lit = EQUIPTRAINDATAHANDLER->m_vecEquipLockStatus.begin();
	std::vector<int>::iterator lit_end = EQUIPTRAINDATAHANDLER->m_vecEquipLockStatus.end();

	for(; it != it_end; ++it)
	{
		_setBtnSelected(it->first, false);
		NFC_showNode(it->first, this, true);

		for(; lit != lit_end; ++lit)
		{
			if(it->second == *lit)
			{
				_setBtnSelected(it->first, true);
				break;
			}

		}
		lit = EQUIPTRAINDATAHANDLER->m_vecEquipLockStatus.begin();

	}

}

void EquipTrainView::PlayEffect()
{
	//Warning, if this need delete.20130830
	//刷新左侧信息
	if(m_bInOneKeyTrainMode)
	{
		_showLeftAttributeWhenOneKey();
	}
	else
	{
		_showLeftAttribute();//显示左边的信息
	}

	if(!m_bInOneKeyTrainMode)
	{
		//先隐藏右侧信息
		for(int i = tNewAttri1; i <= tNewAttri4Max; ++i)
		{
			NFC_showNode(i, this, false);
		}
		//隐藏锁
		for(int i = tLock1; i <= tLock4; ++i)
		{
			NFC_showNode(i, this, false);
		}
	}

	//_showLockStatus();//显示装备锁属性...///这个在void EquipTrainView::MoveLockPosition(bool right)函数中做过，而这个函数在动画回调中调用了


	//-----------------------------------------above is move here from Train() method------------------------------

	//创建遮罩层
	if(m_bInOneKeyTrainMode)
	{//让停止洗练按钮能点击
		_createGrayLayer(-10);
	}
	else
	{
		_createGrayLayer(-30);
	}

	//播放
	if(m_pAnimationPlayNode)
		m_pAnimationPlayNode->PlayEffect();
}

bool EquipTrainView::onLoad(){
	if(CCNode::init()){
		setPosition(CCPointZero);
		_initLayout();
		this->autorelease();
		return true;
	}

	return false;
}
bool EquipTrainView::onDestroy()
{

	EQUIPTRAINDATAHANDLER->SetCurEquipId(-1);
	m_bInOneKeyTrainMode = false;

	m_iWillUnLockAttributeIndex = -1;

	this->removeAllChildrenWithCleanup(true);
	this->removeFromParentAndCleanup(true);

	return true;
}

bool EquipTrainView::onTick()
{
	return true;
}

void EquipTrainView::EquipHasBeenSeleted(int equipID)
{
	if(equipID > 0)
	{

		if(EQUIPTRAINDATAHANDLER->GetCurEquipId() == equipID)
		{
			return;
		}

		EQUIPTRAINDATAHANDLER->m_mapOneKeyTrainLastAttribute.clear();
		EQUIPTRAINDATAHANDLER->m_mapOneKeyTrainLastAttributeMax.clear();
		EQUIPTRAINDATAHANDLER->m_mapOneKeyAttributeLockPosition.clear();

		EQUIPTRAINDATAHANDLER->SetCurEquipId(equipID);

		//清空锁和属性对应表
		EQUIPTRAINDATAHANDLER->m_mapAttributeLockPosition.clear();

		//显示左边的信息，包含锁显示
		_showLeftAttribute();

		//请求当前选中装备的锁状态
		EQUIPTRAINDATAHANDLER->ToServerGetCurrentAttributeLockStatus();

		//设置洗练结果面板不可见
		_setResultAreaVisiable(false);

		_enableTrainBtn(false);
		_enableOneKeyTrainBtn(false);

		//切换锁位置，同时刷新锁状态
		MoveLockPosition(false);
	}
	else
	{
		EQUIPTRAINDATAHANDLER->SetCurEquipId(equipID);

		//切换锁位置，同时刷新锁状态
		MoveLockPosition(false);

		//隐藏面板
		for(int i = tLock1; i <= tNewAttri4Max; ++i)
		{
			NFC_showNode(i, this, false);
		}
		for(int i = tArrow1; i <= tArrow4; ++i)
		{
			NFC_showNode(i, this, false);
		}

		_enableTrainBtn(false);
		_enableOneKeyTrainBtn(false);
	}
}

void EquipTrainView::EventWindowCallBack(int iEventType, std::list<std::string>& paramList)
{
	if(iEventType == _TYPED_EVENT_LOCK_ATTRIBUTE_RESULT_)
	{
		Function_LockAttribute();
	}
	else if(iEventType == _TYPED_EVENT_UNLOCK_ATTRIBUTE_RESULT_)
	{
		Function_UnLockAttribute();
	}
	else if(iEventType == _TYPED_EVENT_EQUIPTRAIN_RESULT_)
	{
		Function_TrainResult();
	}
	else if(iEventType == _TYPED_EVENT_EQUIPTRAIN_GETLOCKSTATUS_RESULT_)
	{
		Function_GetAttributeStatus();
	}
	else if(iEventType == _TYPED_EVENT_REFRESH_UPDATEUI_)
	{
		Function_RefreshBagObjectShow();
	}
	else if(iEventType == _TYPED_EVENT_CONFIRM_EQUIP_USEONEKEYTRAIN_)
	{
		Function_ConfirmUseOneKeyTrain();
	}
	else if(iEventType == _TYPED_EVENT_UNLOCK_EQUIPATTRIBUTELOCK_)
	{
		EQUIPTRAINDATAHANDLER->ToServerUnLockAttribute(-1, EQUIPTRAINDATAHANDLER->GetCurEquipId(), m_iWillUnLockAttributeIndex);
	}
}

void EquipTrainView::On_ClickEvent(cocos2d::CCObject* pSender){
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;

	int tag = cc->getTag();
	if(tag == tTrainBtn)
	{//洗练
		
		//洗练特效
		PlayEffect();
	}
	else if(tag == tOneTrainBtn)
	{//一键洗练
		
		if(m_bInOneKeyTrainMode)
		{//停止洗练
			m_bInOneKeyTrainMode = false;
			//显示一键洗练
			NFC_setLabelString(tOneTrainLabel, this, SysLangDataManager::get_instance2()->GetSysLangById(2017), true);
			_enableTrainBtn(true);
			_removeGrayLayer();

			//强制关闭
			if(m_pAnimationPlayNode)
				m_pAnimationPlayNode->StopEffect();
		}
		else
		{//开始洗练
			NFC_showMessageBox(kUSEONEKEY_TRAIN, SysLangDataManager::get_instance2()->GetSysLangById(2021));
		}
	}


}

void EquipTrainView::Train()
{
	//如果是在一键洗练状态，需要记录上次的属性
	if(m_bInOneKeyTrainMode)
	{
		//一键洗练时将当前属性保存起来，这样方便之后洗练结束时显示
		EQUIPTRAINDATAHANDLER->m_mapOneKeyTrainLastAttribute.clear();
		EQUIPTRAINDATAHANDLER->m_mapOneKeyTrainLastAttributeMax.clear();
		EQUIPTRAINDATAHANDLER->m_mapOneKeyAttributeLockPosition.clear();
		BagEquipData * bed = EQUIPTRAINDATAHANDLER->GetCurEquip();
		if(bed)
		{
			std::map<int, int>::iterator it = bed->attribute_->mapPropertyList_.begin();
			std::map<int, int>::iterator it_e = bed->attribute_->mapPropertyList_.end();
			std::map<int, int>::iterator it_Max = bed->attributeMAX_->mapPropertyList_.begin();
			for(; it != it_e; ++it, ++it_Max)
			{
				EQUIPTRAINDATAHANDLER->m_mapOneKeyTrainLastAttribute.insert(std::map<int, int>::value_type(it->first, it->second));
				EQUIPTRAINDATAHANDLER->m_mapOneKeyTrainLastAttributeMax.insert(std::map<int, int>::value_type(it_Max->first, it_Max->second));
			}

			std::map<int, int>::iterator lit = EQUIPTRAINDATAHANDLER->m_mapAttributeLockPosition.begin();
			std::map<int, int>::iterator lit_e = EQUIPTRAINDATAHANDLER->m_mapAttributeLockPosition.end();
			for(; lit != lit_e; ++lit)
			{
				EQUIPTRAINDATAHANDLER->m_mapOneKeyAttributeLockPosition.insert(std::map<int, int>::value_type(lit->first, lit->second));
			}
		}
		
	}
	

	EQUIPTRAINDATAHANDLER->ToServerTrain(EQUIPTRAINDATAHANDLER->GetCurEquipId());
}

void EquipTrainView::On_Lock_ClickEvent(cocos2d::CCObject * pSender)
{
	//锁选定
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int tag = item->getTag();
	
	BagEquipData * bb = EQUIPTRAINDATAHANDLER->GetCurEquip();

	int attriIndex = EQUIPTRAINDATAHANDLER->m_mapAttributeLockPosition[tag];
	if(item->getIsSeleted())
	{//解锁时需要出现提示框提示
		std::string message = SysLangDataManager::get_instance2()->GetSysLangById(2022);
		NFC_showMessageBox(kWARNINGUNLOCKATTRIBUTE,message);
		item->selected(true);//在服务器提示接触属性锁之前，此锁需要一直维持
		
		m_iWillUnLockAttributeIndex = attriIndex;

		//EQUIPTRAINDATAHANDLER->ToServerUnLockAttribute(-1, EQUIPTRAINDATAHANDLER->GetCurEquipId(), attriIndex);
		
	}
	else
	{
		//判断已有的属性锁是否达到最大的属性锁数量，达到了，提示框
		int a = EQUIPTRAINDATAHANDLER->m_vecEquipLockStatus.size();
		int b = bb->attribute_->mapPropertyList_.size();
		if(a < b - 1)
		{
			EQUIPTRAINDATAHANDLER->ToServerLockAttribute(-1, EQUIPTRAINDATAHANDLER->GetCurEquipId(), attriIndex);
		}
		else
		{
			std::string message = SysLangDataManager::get_instance2()->GetSysLangById(480);
			NFC_showMessageBox(kDEFAULT,message);
		}
	}

}


void EquipTrainView::Function_LockAttribute()
{
	AttributeLock & lock = EQUIPTRAINDATAHANDLER->m_pLock;
	if(EQUIPTRAINDATAHANDLER->GetCurEquipId() != lock.equipId)
		return;

	BagEquipData * bb = EQUIPTRAINDATAHANDLER->GetCurEquip();

	std::map<int, int>::iterator it = EQUIPTRAINDATAHANDLER->m_mapAttributeLockPosition.begin();
	std::map<int, int>::iterator it_end = EQUIPTRAINDATAHANDLER->m_mapAttributeLockPosition.end();
	for(; it != it_end; ++it)
	{
		if(it->second == lock.attributeIndex)
		{
			break;
		}
	}
	if(it != it_end)
		_setBtnSelected(it->first, true);

	//显示属性锁物品个数
	_showLockObjectNum();

	//显示洗练花费金钱
	_showMoney();

}

void EquipTrainView::Function_UnLockAttribute()
{
	AttributeLock & unlock = EQUIPTRAINDATAHANDLER->m_pUnLock;
	if(EQUIPTRAINDATAHANDLER->GetCurEquipId() != unlock.equipId)
		return;

	BagEquipData * bb = EQUIPTRAINDATAHANDLER->GetCurEquip();

	std::map<int, int>::iterator it = EQUIPTRAINDATAHANDLER->m_mapAttributeLockPosition.begin();
	std::map<int, int>::iterator it_end = EQUIPTRAINDATAHANDLER->m_mapAttributeLockPosition.end();
	for(; it != it_end; ++it)
	{
		if(it->second == unlock.attributeIndex)
		{
			break;
		}
	}
	if(it != it_end)
		_setBtnSelected(it->first, false);

	//显示属性锁物品个数
	_showLockObjectNum();

	//显示洗练花费金钱
	_showMoney();
}

void EquipTrainView::Function_TrainResult()
{
	//显示结果信息
	Attribute & attr = EQUIPTRAINDATAHANDLER->m_pTrainData.attribute;
	Attribute & attrMax = EQUIPTRAINDATAHANDLER->m_pTrainData.attributeMax;

	CCLabelTTF * ttf = NULL;
	CCNode * node = NULL;
	char str[128] = "";

	_mapAttriToLockPosition();

	std::map<int, int>::iterator lit = EQUIPTRAINDATAHANDLER->m_mapAttributeLockPosition.begin();
	std::map<int, int>::iterator lit_end = EQUIPTRAINDATAHANDLER->m_mapAttributeLockPosition.end();
	for(; lit != lit_end; ++lit)
	{
		if(attr.mapPropertyList_[lit->second] > 0)
		{
			std::string name = IDSTRINGDATAMANAGER->GetIDStringByID(3, lit->second);
			sprintf(str, SysLangDataManager::get_instance2()->GetSysLangById(2018).c_str(), name.c_str(), attr.mapPropertyList_[lit->second]);
			NFC_setLabelString(lit->first + 12, this, str, true);//新属性名称+增加

			sprintf(str, SysLangDataManager::get_instance2()->GetSysLangById(2019).c_str(), attrMax.mapPropertyList_[lit->second]);
			NFC_setLabelString(lit->first + 16, this, str, true);//新属性最大
			//设置文字颜色
			FSData* dd = NULL;
			int xf = 100 * ((float)attr.mapPropertyList_[lit->second] / attrMax.mapPropertyList_[lit->second]);
			if(xf < 60)
			{//绿色
				dd = FONTSTYLEDATAMANAGER->getDataByID(92);
			}
			else if(xf >= 60 && xf < 80)
			{//蓝色
				dd = FONTSTYLEDATAMANAGER->getDataByID(93);
			}
			else if(xf >= 80 && xf < 100)
			{//紫色
				dd = FONTSTYLEDATAMANAGER->getDataByID(94);
			}
			else if(xf == 100)
			{//橙色
				dd = FONTSTYLEDATAMANAGER->getDataByID(95);
			}
			NFC_setLabelColor(lit->first + 12, this, ccc3(dd->colorR_, dd->colorG_, dd->colorB_));
			NFC_setLabelColor(lit->first + 16, this, ccc3(dd->colorR_, dd->colorG_, dd->colorB_));

		}

	}

	//切换锁位置，同时刷新锁状态
	MoveLockPosition(true);

	//显示洗练花费金钱
	_showMoney();

	_removeGrayLayer();

	if(m_bInOneKeyTrainMode)
	{//在一键洗练中，判断金钱，判断完美品质
		if(EQUIPTRAINDATAHANDLER->m_pTrainData.moneyEnough > 0)
		{//金钱足够
			if(EQUIPTRAINDATAHANDLER->IsCurEquipCanOneKeyTrain())
			{//没有未锁定品质达到完美
				//继续洗练
				PlayEffect();
			}
			else
			{//设置显示一键洗练
				if(m_bInOneKeyTrainMode)
				{
					_showLeftAttributeWhenOneKey();
				}
				m_bInOneKeyTrainMode = false;
				NFC_setLabelString(tOneTrainLabel, this, SysLangDataManager::get_instance2()->GetSysLangById(2017), true);
				_enableTrainBtn(true);
				_enableOneKeyTrainBtn(false);

				
			}
		}
		else
		{
			if(m_bInOneKeyTrainMode)
			{
				_showLeftAttributeWhenOneKey();
			}
			m_bInOneKeyTrainMode = false;
			NFC_setLabelString(tOneTrainLabel, this, SysLangDataManager::get_instance2()->GetSysLangById(2017), true);
			_enableTrainBtn(false);
			_enableOneKeyTrainBtn(false);
			NFC_setLabelColor(tGoldValue, this, color_BagRed);//金钱置红
		}
	}
	else
	{
		if(EQUIPTRAINDATAHANDLER->m_pTrainData.moneyEnough > 0)
		{//金钱足够
			if(EQUIPTRAINDATAHANDLER->IsCurEquipCanOneKeyTrain())
			{//可一键洗练，可洗练
				NFC_setLabelString(tOneTrainLabel, this, SysLangDataManager::get_instance2()->GetSysLangById(2017), true);
				_enableTrainBtn(true);
				_enableOneKeyTrainBtn(true);
			}
			else
			{//不可一键洗练，可洗练
				NFC_setLabelString(tOneTrainLabel, this, SysLangDataManager::get_instance2()->GetSysLangById(2017), true);
				_enableTrainBtn(true);
				_enableOneKeyTrainBtn(false);
			}
		}
		else
		{//金钱不够
			NFC_setLabelString(tOneTrainLabel, this, SysLangDataManager::get_instance2()->GetSysLangById(2017), true);
			_enableTrainBtn(false);
			_enableOneKeyTrainBtn(false);
			NFC_setLabelColor(tGoldValue, this, color_BagRed);//金钱置红
		}
	}
}

void EquipTrainView::Function_GetAttributeStatus()
{
	//显示属性锁状态
	_showLockStatus();

	//显示洗练花费金钱
	_showMoney();
}

void EquipTrainView::Function_RefreshBagObjectShow()
{
	_showLockObjectNum();
}

void EquipTrainView::Function_ConfirmUseOneKeyTrain()
{
	if(!m_bInOneKeyTrainMode)
	{
		m_bInOneKeyTrainMode = true;
		PlayEffect();
		//Train();
		//显示停止洗练
		NFC_setLabelString(tOneTrainLabel, this, SysLangDataManager::get_instance2()->GetSysLangById(2020), true);
		//禁用洗练
		_enableTrainBtn(false);
	}
}

void EquipTrainView::MoveLockPosition(bool right)
{
	CCNode * node = NULL;
	CCNode * lockmenu = NULL;
	CCNode * lock = NULL;
	int i = tLock1;
	int j = tLockMask1;
	if(right)
	{//向右移
		for(; i <= tLock4; ++i, ++j)
		{
			node = this->getChildByTag(j);
			lockmenu = this->getChildByTag(i);
			lock = lockmenu->getChildByTag(i);
			lock->setPositionX(node->getPositionY());
		}

	}
	else
	{//向左移
		for(; i <= tLock4; ++i, ++j)
		{
			node = this->getChildByTag(j);
			lockmenu = this->getChildByTag(i);
			lock = lockmenu->getChildByTag(i);
			lock->setPositionX(node->getPositionX());
		}
	}

	//显示锁选中状态
	_showLockStatus();

}

//创建遮罩层，用于特效显示时屏蔽用户点击
void EquipTrainView::_createGrayLayer(int pri)
{
	m_pAnimationGrayLayer = CPriorityLayerColor::create(ccc4(0,0,0,0),3000,2000,pri);
	m_pAnimationGrayLayer->setAnchorPoint(ccp(0,0));
	m_pAnimationGrayLayer->setPosition(ccp(0,0));
	this->addChild(m_pAnimationGrayLayer,10);
}

void EquipTrainView::_removeGrayLayer()
{
	if(m_pAnimationGrayLayer)
		m_pAnimationGrayLayer->removeFromParentAndCleanup(true);
	m_pAnimationGrayLayer = NULL;
}