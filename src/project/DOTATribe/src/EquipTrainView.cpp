//Name : EquipTrainView
//Function��װ��ϴ������
//Written By : ����
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

	//��ʼ��������Ч
	_initAnimationEffect();

	//������
	for(int i = tLock1; i <= tLock4; ++i)
	{
		CCNode * node = this->getChildByTag(i);
		node->setVisible(false);
	}

	_mapAllBtn();

	_enableTrainBtn(false);

	//��ʾ����Ʒ����
	_showLockObjectNum();
}


void EquipTrainView::_initAnimationEffect()
{
	//��Ч����
	//m_pAnimationPlayNode = cocos2d::CCSprite::create();
	MaskNode * effectNode = (MaskNode *)this->getChildByTag(tAnimationNode);
	m_pAnimationPlayNode = NFC_getAnimationSprite(effectNode->GetViewData().colorR_, false, false, this);
	effectNode->addChild(m_pAnimationPlayNode);

}


void  EquipTrainView::EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr)
{

	//ϴ��
	Train();
	
}

void EquipTrainView::_mapAllBtn(){
	//ϴ����ť
	CCMenu * menu = (CCMenu *)this->getChildByTag(tTrainBtn);
	CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(tTrainBtn);
	item->setTarget(this, menu_selector(EquipTrainView::On_ClickEvent));

	//һ��ϴ��
	menu = (CCMenu *)this->getChildByTag(tOneTrainBtn);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(tOneTrainBtn);
	item->setTarget(this, menu_selector(EquipTrainView::On_ClickEvent));

	//��
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

	//��ͷ
	for(int i = tArrow1; i <= tArrow4; ++i)
	{
		NFC_showNode(i, this, false);
	}

	if(EQUIPTRAINDATAHANDLER->GetCurEquipId() < 0)
		return;

	BagEquipData * bed = EQUIPTRAINDATAHANDLER->GetCurEquip();
	if(!bed)
		return;

	//�궨���Ժ���λ��
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
			NFC_setLabelString(lit->first + 4, this, str, true);//��������+����

			sprintf(str, SysLangDataManager::get_instance2()->GetSysLangById(2019).c_str(), bed->attributeMAX_->mapPropertyList_[lit->second]);
			NFC_setLabelString(lit->first + 4 + 4, this, str, true);//�������

			FSData * dd = NULL;
			int xf = 100 * ((float)bed->attribute_->mapPropertyList_[lit->second] / bed->attributeMAX_->mapPropertyList_[lit->second]);
			if(xf < 60)
			{//��ɫ
				dd = FONTSTYLEDATAMANAGER->getDataByID(92);
			}
			else if(xf >= 60 && xf < 80)
			{//��ɫ
				dd = FONTSTYLEDATAMANAGER->getDataByID(93);
			}
			else if(xf >= 80 && xf < 100)
			{//��ɫ
				dd = FONTSTYLEDATAMANAGER->getDataByID(94);
			}
			else if(xf == 100)
			{//��ɫ
				dd = FONTSTYLEDATAMANAGER->getDataByID(95);
			}
			NFC_setLabelColor(lit->first + 4, this, ccc3(dd->colorR_, dd->colorG_, dd->colorB_));
			NFC_setLabelColor(lit->first + 4 + 4, this, ccc3(dd->colorR_, dd->colorG_, dd->colorB_));

			//��ʾ��
			node = this->getChildByTag(lit->first);
			node->setVisible(true);

			//��ʾ��ͷ
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
			NFC_setLabelString(lit->first + 4, this, str, true);//��������+����

			sprintf(str, SysLangDataManager::get_instance2()->GetSysLangById(2019).c_str(), map_Max_[lit->second]);
			NFC_setLabelString(lit->first + 4 + 4, this, str, true);//�������

			FSData * dd = NULL;
			int xf = 100 * ((float)map_[lit->second] / map_Max_[lit->second]);
			if(xf < 60)
			{//��ɫ
				dd = FONTSTYLEDATAMANAGER->getDataByID(92);
			}
			else if(xf >= 60 && xf < 80)
			{//��ɫ
				dd = FONTSTYLEDATAMANAGER->getDataByID(93);
			}
			else if(xf >= 80 && xf < 100)
			{//��ɫ
				dd = FONTSTYLEDATAMANAGER->getDataByID(94);
			}
			else if(xf == 100)
			{//��ɫ
				dd = FONTSTYLEDATAMANAGER->getDataByID(95);
			}
			NFC_setLabelColor(lit->first + 4, this, ccc3(dd->colorR_, dd->colorG_, dd->colorB_));
			NFC_setLabelColor(lit->first + 4 + 4, this, ccc3(dd->colorR_, dd->colorG_, dd->colorB_));

			//��ʾ��
			node = this->getChildByTag(lit->first);
			node->setVisible(true);

			//��ʾ��ͷ
			NFC_showNode(lit->first + 33, this, true);
		}

	}
}

void EquipTrainView::_mapAttriToLockPosition()//�����Ժ�����λ�ð�
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

	//��һ�Σ��궨���е���ͬ������
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
	//�ڶ��Σ�������ͬ�����Բ��뵽λ�ö�����
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

void EquipTrainView::_showMoney()//��ʾ���ѽ�Ǯ
{
	//����ϴ�����ѽ�Ǯ
	BagEquipData * bb = EQUIPTRAINDATAHANDLER->GetCurEquip();
	int money = EQUIPTRAINDATAHANDLER->m_iAttriPrice;

	//��ʾ��Ǯ
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

void EquipTrainView::_showLockObjectNum()//��ʾ����Ʒ����
{
	//�������������������������Ʒ
	int num = BAGOTHEROBJECTHANDLER->getObjectCountByTemplateId(CLIENTCONSTDATAMANGER->getValueByKey(ATTRIBUTE_TEMPLATEID));

	//��ʾ����Ʒ����
	CCLabelTTF * ttf = (CCLabelTTF *)this->getChildByTag(tLockValue);
	char str[128] = {0};
	sprintf(str, "%d", num);
	ttf->setString(str);
}


void EquipTrainView::_showLockStatus()
{

	//��������ťѡ��
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
	//ˢ�������Ϣ
	if(m_bInOneKeyTrainMode)
	{
		_showLeftAttributeWhenOneKey();
	}
	else
	{
		_showLeftAttribute();//��ʾ��ߵ���Ϣ
	}

	if(!m_bInOneKeyTrainMode)
	{
		//�������Ҳ���Ϣ
		for(int i = tNewAttri1; i <= tNewAttri4Max; ++i)
		{
			NFC_showNode(i, this, false);
		}
		//������
		for(int i = tLock1; i <= tLock4; ++i)
		{
			NFC_showNode(i, this, false);
		}
	}

	//_showLockStatus();//��ʾװ��������...///�����void EquipTrainView::MoveLockPosition(bool right)����������������������ڶ����ص��е�����


	//-----------------------------------------above is move here from Train() method------------------------------

	//�������ֲ�
	if(m_bInOneKeyTrainMode)
	{//��ֹͣϴ����ť�ܵ��
		_createGrayLayer(-10);
	}
	else
	{
		_createGrayLayer(-30);
	}

	//����
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

		//����������Զ�Ӧ��
		EQUIPTRAINDATAHANDLER->m_mapAttributeLockPosition.clear();

		//��ʾ��ߵ���Ϣ����������ʾ
		_showLeftAttribute();

		//����ǰѡ��װ������״̬
		EQUIPTRAINDATAHANDLER->ToServerGetCurrentAttributeLockStatus();

		//����ϴ�������岻�ɼ�
		_setResultAreaVisiable(false);

		_enableTrainBtn(false);
		_enableOneKeyTrainBtn(false);

		//�л���λ�ã�ͬʱˢ����״̬
		MoveLockPosition(false);
	}
	else
	{
		EQUIPTRAINDATAHANDLER->SetCurEquipId(equipID);

		//�л���λ�ã�ͬʱˢ����״̬
		MoveLockPosition(false);

		//�������
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
	{//ϴ��
		
		//ϴ����Ч
		PlayEffect();
	}
	else if(tag == tOneTrainBtn)
	{//һ��ϴ��
		
		if(m_bInOneKeyTrainMode)
		{//ֹͣϴ��
			m_bInOneKeyTrainMode = false;
			//��ʾһ��ϴ��
			NFC_setLabelString(tOneTrainLabel, this, SysLangDataManager::get_instance2()->GetSysLangById(2017), true);
			_enableTrainBtn(true);
			_removeGrayLayer();

			//ǿ�ƹر�
			if(m_pAnimationPlayNode)
				m_pAnimationPlayNode->StopEffect();
		}
		else
		{//��ʼϴ��
			NFC_showMessageBox(kUSEONEKEY_TRAIN, SysLangDataManager::get_instance2()->GetSysLangById(2021));
		}
	}


}

void EquipTrainView::Train()
{
	//�������һ��ϴ��״̬����Ҫ��¼�ϴε�����
	if(m_bInOneKeyTrainMode)
	{
		//һ��ϴ��ʱ����ǰ���Ա�����������������֮��ϴ������ʱ��ʾ
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
	//��ѡ��
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int tag = item->getTag();
	
	BagEquipData * bb = EQUIPTRAINDATAHANDLER->GetCurEquip();

	int attriIndex = EQUIPTRAINDATAHANDLER->m_mapAttributeLockPosition[tag];
	if(item->getIsSeleted())
	{//����ʱ��Ҫ������ʾ����ʾ
		std::string message = SysLangDataManager::get_instance2()->GetSysLangById(2022);
		NFC_showMessageBox(kWARNINGUNLOCKATTRIBUTE,message);
		item->selected(true);//�ڷ�������ʾ�Ӵ�������֮ǰ��������Ҫһֱά��
		
		m_iWillUnLockAttributeIndex = attriIndex;

		//EQUIPTRAINDATAHANDLER->ToServerUnLockAttribute(-1, EQUIPTRAINDATAHANDLER->GetCurEquipId(), attriIndex);
		
	}
	else
	{
		//�ж����е��������Ƿ�ﵽ�����������������ﵽ�ˣ���ʾ��
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

	//��ʾ��������Ʒ����
	_showLockObjectNum();

	//��ʾϴ�����ѽ�Ǯ
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

	//��ʾ��������Ʒ����
	_showLockObjectNum();

	//��ʾϴ�����ѽ�Ǯ
	_showMoney();
}

void EquipTrainView::Function_TrainResult()
{
	//��ʾ�����Ϣ
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
			NFC_setLabelString(lit->first + 12, this, str, true);//����������+����

			sprintf(str, SysLangDataManager::get_instance2()->GetSysLangById(2019).c_str(), attrMax.mapPropertyList_[lit->second]);
			NFC_setLabelString(lit->first + 16, this, str, true);//���������
			//����������ɫ
			FSData* dd = NULL;
			int xf = 100 * ((float)attr.mapPropertyList_[lit->second] / attrMax.mapPropertyList_[lit->second]);
			if(xf < 60)
			{//��ɫ
				dd = FONTSTYLEDATAMANAGER->getDataByID(92);
			}
			else if(xf >= 60 && xf < 80)
			{//��ɫ
				dd = FONTSTYLEDATAMANAGER->getDataByID(93);
			}
			else if(xf >= 80 && xf < 100)
			{//��ɫ
				dd = FONTSTYLEDATAMANAGER->getDataByID(94);
			}
			else if(xf == 100)
			{//��ɫ
				dd = FONTSTYLEDATAMANAGER->getDataByID(95);
			}
			NFC_setLabelColor(lit->first + 12, this, ccc3(dd->colorR_, dd->colorG_, dd->colorB_));
			NFC_setLabelColor(lit->first + 16, this, ccc3(dd->colorR_, dd->colorG_, dd->colorB_));

		}

	}

	//�л���λ�ã�ͬʱˢ����״̬
	MoveLockPosition(true);

	//��ʾϴ�����ѽ�Ǯ
	_showMoney();

	_removeGrayLayer();

	if(m_bInOneKeyTrainMode)
	{//��һ��ϴ���У��жϽ�Ǯ���ж�����Ʒ��
		if(EQUIPTRAINDATAHANDLER->m_pTrainData.moneyEnough > 0)
		{//��Ǯ�㹻
			if(EQUIPTRAINDATAHANDLER->IsCurEquipCanOneKeyTrain())
			{//û��δ����Ʒ�ʴﵽ����
				//����ϴ��
				PlayEffect();
			}
			else
			{//������ʾһ��ϴ��
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
			NFC_setLabelColor(tGoldValue, this, color_BagRed);//��Ǯ�ú�
		}
	}
	else
	{
		if(EQUIPTRAINDATAHANDLER->m_pTrainData.moneyEnough > 0)
		{//��Ǯ�㹻
			if(EQUIPTRAINDATAHANDLER->IsCurEquipCanOneKeyTrain())
			{//��һ��ϴ������ϴ��
				NFC_setLabelString(tOneTrainLabel, this, SysLangDataManager::get_instance2()->GetSysLangById(2017), true);
				_enableTrainBtn(true);
				_enableOneKeyTrainBtn(true);
			}
			else
			{//����һ��ϴ������ϴ��
				NFC_setLabelString(tOneTrainLabel, this, SysLangDataManager::get_instance2()->GetSysLangById(2017), true);
				_enableTrainBtn(true);
				_enableOneKeyTrainBtn(false);
			}
		}
		else
		{//��Ǯ����
			NFC_setLabelString(tOneTrainLabel, this, SysLangDataManager::get_instance2()->GetSysLangById(2017), true);
			_enableTrainBtn(false);
			_enableOneKeyTrainBtn(false);
			NFC_setLabelColor(tGoldValue, this, color_BagRed);//��Ǯ�ú�
		}
	}
}

void EquipTrainView::Function_GetAttributeStatus()
{
	//��ʾ������״̬
	_showLockStatus();

	//��ʾϴ�����ѽ�Ǯ
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
		//��ʾֹͣϴ��
		NFC_setLabelString(tOneTrainLabel, this, SysLangDataManager::get_instance2()->GetSysLangById(2020), true);
		//����ϴ��
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
	{//������
		for(; i <= tLock4; ++i, ++j)
		{
			node = this->getChildByTag(j);
			lockmenu = this->getChildByTag(i);
			lock = lockmenu->getChildByTag(i);
			lock->setPositionX(node->getPositionY());
		}

	}
	else
	{//������
		for(; i <= tLock4; ++i, ++j)
		{
			node = this->getChildByTag(j);
			lockmenu = this->getChildByTag(i);
			lock = lockmenu->getChildByTag(i);
			lock->setPositionX(node->getPositionX());
		}
	}

	//��ʾ��ѡ��״̬
	_showLockStatus();

}

//�������ֲ㣬������Ч��ʾʱ�����û����
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