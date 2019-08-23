#include "../include/EquipPromoteView.h"
#include "../include/VariableSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/ResourceIDDataManager.h"
#include "../include/CPublicVarReader.h"
#include "../include/BagOtherObjectHandler.h"
#include "../include/UIViewDataManger.h"
#include "../include/EquipPromoteDataHandler.h"
#include "../include/IDStringDataManager.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/CMenuItemSprite.h"
#include "../include/EquipPromotePacket.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/NFControlsManager.h"
#include "../include/NFAnimationController.h"
#include "../include/NetObjectTipsDataHandler.h"
#include "../include/IWindow.h"
#include "../include/DTAwardBoard.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
EquipPromoteView::EquipPromoteView()
{
	
	m_IsCanPromote = true;
	m_IsFirstIn = true;
	m_CurEquipID = -1;
	m_CurEquipLv = -1;
	m_CurEquipLine1 = -1;
	m_CurEquipLine2 = -1;
	m_CurEquipLine3 = -1;
	m_CurEquipLine4 = -1;
	memset(ArrcrystalitemID,0,sizeof(ArrcrystalitemID));
}
EquipPromoteView::~EquipPromoteView()
{

}
bool EquipPromoteView::onLoad()
{
	if(CCNode::init()){
		this->autorelease();
		setPosition(CCPointZero);
		initLayer();

		return true;
	}
	return false;
}
bool EquipPromoteView::onTick()
{

	return true;
}
bool EquipPromoteView::onDestroy()
{
	m_IsCanPromote = true;
	m_IsFirstIn = true;
	m_CurEquipID = -1;
	m_CurEquipLv = -1;
	m_CurEquipLine1 = -1;
	m_CurEquipLine2 = -1;
	m_CurEquipLine3 = -1;
	m_CurEquipLine4 = -1;
	this->removeAllChildrenWithCleanup(true);
	this->removeFromParentAndCleanup(true);
	return true;
}


void EquipPromoteView::EquipHasBeenSeleted(int equipID)
{
	if (m_CurEquipID == equipID)
		return;
	m_CurEquipID = equipID;
	if (m_CurEquipID != -1)
	{
		m_IsFirstIn = true;
		C2SEquipPromotePacket packet(m_CurEquipID);
		packet.Send();
		NFC_showCommunicationWating(true);
	}
	else
	{
		UpdataPromoteInfo();
	}

}
void EquipPromoteView::initLayer()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kEQUIPPROMOTEVIEW,this);
	CCMenu* ptemp = (CCMenu*)this->getChildByTag(EquipPromoteView_Button);
	CMenuItemSprite* ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(EquipPromoteView::On_Promote));
	_MapBtnTips();
	UpdataPromoteInfo();
}
void EquipPromoteView::On_Promote(cocos2d::CCObject* pSender)
{
	C2SSurePromotePacket packet(m_CurEquipID);
	packet.Send();
	NFC_showCommunicationWating(true);
}
void EquipPromoteView::EventWindowCallBack(int iEventType, std::list<std::string>& paramList)
{
	if(iEventType == _TEPED_EVENT_UPDATRA_EQUIPPROMOTE_)
	{
		UpdataPromoteInfo();
	}
	if(iEventType == _TYPED_EVENT_EQUIPPROMOTE_RESULT_)
	{
		MaskNode * node = (MaskNode *)this->getChildByTag(EquipPromoteAnimationMaskNode);
		cocos2d::CCSprite * sp = NFC_getUnLoopFrameEffect(node->GetViewData().colorR_, this);
		node->addChild(sp);
		sp->setPosition(CCPointZero);
	}
};
int EquipPromoteView::GetCurAttribute(int index)
{
	if (index == EquipPromoteView_Line1-1)
		return m_CurEquipLine1;
	else if (index == EquipPromoteView_Line2-1)
		return m_CurEquipLine2;
	else if (index == EquipPromoteView_Line3-1)
		return m_CurEquipLine3;
	else if (index == EquipPromoteView_Line4-1)
		return m_CurEquipLine4;
	else
		return -1;

}
int	EquipPromoteView::GetCurItemLv()
{
	return BAGEQUIPDATAHANDLER->getEquipByAllEquips(m_CurEquipID)->level_;
}

void EquipPromoteView::UpdataPromoteInfo()
{
	if (EquipPromoteDataHandler::get_instance2()->m_Lv_IsMax && m_CurEquipID != -1)
	{
		m_IsCanPromote = true;
		_updataIsMaxLv();						//最大上限
		_initLocalData();						//上面板初始信息
		_updataInfoLine1();						//上面板第一行信息
		_updataAttributeInfo();					//上面板属性信息
		_updataHideUnuseAttributeInfo();		//隐藏无用属性信息
		_updataItemInfo();						//下面板进阶物品信息
		_updataHideUnuseItemInfo();				//隐藏无用物品信息
		_updataCostMoneyInfo();					//费用信息
		_updataLvLimitInfo();					//等级限制信息
		_updataButtonInfo();					//按钮信息
		_updataLocalData();						//更新本地数
		this->setVisible(true);
	}
	else
	{
		_updataEmpty();
	}
}
void EquipPromoteView::_initLocalData()
{
	if (m_IsFirstIn)
	{
		m_CurEquipLv = BAGEQUIPDATAHANDLER->getEquipByAllEquips(m_CurEquipID)->level_;

		for (int i=0;i<EquipPromoteDataHandler::get_instance2()->m_Attribute_List.size();i++)
		{
			if (i== EquipPromoteView_Line1-1)
				m_CurEquipLine1 = BAGEQUIPDATAHANDLER->getEquipByAllEquips(m_CurEquipID)->attribute_->mapPropertyList_[EquipPromoteDataHandler::get_instance2()->m_Attribute_List[i].type];
			else if (i== EquipPromoteView_Line2-1)
				m_CurEquipLine2 = BAGEQUIPDATAHANDLER->getEquipByAllEquips(m_CurEquipID)->attribute_->mapPropertyList_[EquipPromoteDataHandler::get_instance2()->m_Attribute_List[i].type];
			else if (i== EquipPromoteView_Line3-1)
				m_CurEquipLine3 = BAGEQUIPDATAHANDLER->getEquipByAllEquips(m_CurEquipID)->attribute_->mapPropertyList_[EquipPromoteDataHandler::get_instance2()->m_Attribute_List[i].type];
			else if (i== EquipPromoteView_Line4-1)
				m_CurEquipLine4 = BAGEQUIPDATAHANDLER->getEquipByAllEquips(m_CurEquipID)->attribute_->mapPropertyList_[EquipPromoteDataHandler::get_instance2()->m_Attribute_List[i].type];
		}
		m_IsFirstIn = false;
	}

}
void EquipPromoteView::_updataEmpty()
{
	this->setVisible(true);
	for (int i=EquipPromoteView_Line1_1;i<=EquipPromoteView_LV_Limit;i++)
	{
		CCNode* pNode = (CCNode*)this->getChildByTag(i);
		pNode->setVisible(false);
	}

	for (int i=EquipPromoteView_Button;i<=EquipPromoteView_Button_Label;i++)
	{
		CCNode* pNode = (CCNode*)this->getChildByTag(i);
		pNode->setVisible(true);
	}
	CCMenu* pMenu = (CCMenu*)this->getChildByTag(EquipPromoteView_Button);
	pMenu->setVisible(true);
	CMenuItemSprite* pItem = (CMenuItemSprite*)pMenu->getChildByTag(0);
	pItem->setEnabled(false);

	_updataIsMaxLv();
}
void EquipPromoteView::_updataIsMaxLv()
{
	if (!EquipPromoteDataHandler::get_instance2()->m_Lv_IsMax && m_CurEquipID != -1)
	{
		CCNode* pNode = (CCNode*)this->getChildByTag(EquipPromoteView_Max_LV_Label);
		pNode->setVisible(true);
	}
	else
	{
		CCNode* pNode = (CCNode*)this->getChildByTag(EquipPromoteView_Max_LV_Label);
		pNode->setVisible(false);
	}
}
void EquipPromoteView::_updataLocalData()
{

	m_CurEquipLv = GetCurItemLv();
	for (int i=0;i<EquipPromoteDataHandler::get_instance2()->m_Attribute_List.size();i++)
	{
		if (i== EquipPromoteView_Line1-1)
			m_CurEquipLine1 = EquipPromoteDataHandler::get_instance2()->m_Attribute_List[i].nextValue;
		else if (i== EquipPromoteView_Line2-1)
			m_CurEquipLine2 = EquipPromoteDataHandler::get_instance2()->m_Attribute_List[i].nextValue;
		else if (i== EquipPromoteView_Line3-1)
			m_CurEquipLine3 = EquipPromoteDataHandler::get_instance2()->m_Attribute_List[i].nextValue;
		else if (i== EquipPromoteView_Line4-1)
			m_CurEquipLine4 = EquipPromoteDataHandler::get_instance2()->m_Attribute_List[i].nextValue;
	}


}
void EquipPromoteView::_updataInfoLine1()
{
	CCLabelTTF* pLv = (CCLabelTTF*)this->getChildByTag(EquipPromoteView_Line1_1);
	pLv->setVisible(true);

	CCLabelTTF* pDown = (CCLabelTTF*)this->getChildByTag(EquipPromoteView_Line1_2);
	char _down[128]="";
	sprintf(_down,"%d",m_CurEquipLv);
	pDown->setString(_down);
	pDown->setVisible(true);

	/*
	CCSprite* pArrow = (CCSprite*)this->getChildByTag(EquipPromoteView_Line1_3);
	pArrow->setVisible(true);

	CCLabelTTF* pUp = (CCLabelTTF*)this->getChildByTag(EquipPromoteView_Line1_4);
	char _up[128]="";
	sprintf(_up,"%d",EquipPromoteDataHandler::get_instance2()->m_Lv_Up);
	pUp->setString(_up);
	pUp->setVisible(true);
	*/
}
void EquipPromoteView::_updataAttributeInfo()
{
	for (int i=EquipPromoteView_Empty;i<EquipPromoteView_Line4;i++)
	{
		if (EquipPromoteDataHandler::get_instance2()->m_Attribute_List.size() > i)
		{
			//类型
			CCLabelTTF* pType = (CCLabelTTF*)this->getChildByTag(EquipPromoteView_Line2_1 +i*4);
			char _type[128]="";
			sprintf(_type,"%s",IDStringDataManager::get_instance2()->GetIDStringByID(3,EquipPromoteDataHandler::get_instance2()->m_Attribute_List[i].type).c_str());
			pType->setString(_type);
			pType->setVisible(true);

			//下限
			CCLabelTTF* pDown = (CCLabelTTF*)this->getChildByTag(EquipPromoteView_Line2_1 + i*4 + 1);
			char _down[128]="";
			sprintf(_down,"%d",GetCurAttribute(i));
			pDown->setString(_down);
			pDown->setVisible(true);

			//箭头
			CCSprite* pArrow = (CCSprite*)this->getChildByTag(EquipPromoteView_Line2_1 + i*4 + 2);
			pArrow->setVisible(true);

			//上限
			CCLabelTTF* pUp = (CCLabelTTF*)this->getChildByTag(EquipPromoteView_Line2_1 + i*4 +3);
			char _up[128]="";
			sprintf(_up,"%d",EquipPromoteDataHandler::get_instance2()->m_Attribute_List[i].nextValue);
			pUp->setString(_up);
			pUp->setVisible(true);

		}
	}


}
void EquipPromoteView::_updataHideUnuseAttributeInfo()
{
	int i = EquipPromoteView_Line2_1+EquipPromoteDataHandler::get_instance2()->m_Attribute_List.size()*4;
	for (;i<EquipPromoteView_Item1;i++)
	{
		CCNode* pNode = this->getChildByTag(i);
		pNode->setVisible(false);
	}

}
void EquipPromoteView::_updataItemInfo()
{
	for (int i=EquipPromoteView_Empty;i<EquipPromoteView_Line2;i++)
	{
		if (EquipPromoteDataHandler::get_instance2()->m_Item_List.size()> i)
		{
			DTAwardBoard * dtab = (DTAwardBoard *)this->getChildByTag(EquipPromoteView_Item1 + i * 2);
			dtab->ChangeObject(EquipPromoteDataHandler::get_instance2()->m_Item_List[i].quality, EquipPromoteDataHandler::get_instance2()->m_Item_List[i].iocn, 1);

// 			CCSprite* ItemBG1 = (CCSprite*)this->getChildByTag(EquipPromoteView_Item1_BG+ i*4);
// 			ItemBG1->setProperty("File",varConfig::getCardBGFilePath(EquipPromoteDataHandler::get_instance2()->m_Item_List[i].quality));
// 			ItemBG1->setVisible(true);
// 
// 			CCSprite* ItemIcon1 = (CCSprite*)this->getChildByTag(EquipPromoteView_Item1_BG+ i*4 +1);
// 			ItemIcon1->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(EquipPromoteDataHandler::get_instance2()->m_Item_List[i].iocn));
// 			ItemIcon1->setVisible(true);
			//个数
			CCLabelTTF* Num1 = (CCLabelTTF*)this->getChildByTag(EquipPromoteView_Item1+ i*2 +1);
			char _num[128]="";
			int _num1 = EquipPromoteDataHandler::get_instance2()->m_Item_List[i].hasNum;
			int _num2 = EquipPromoteDataHandler::get_instance2()->m_Item_List[i].needNum;
			if (_num1>=_num2)
			{
				//_num1 = _num2;
				Num1->setColor(ccWHITE);
			}
			else
			{
				Num1->setColor(ccRED);
				m_IsCanPromote = false;
			}
			sprintf(_num,"%d/%d",_num1,_num2);
			Num1->setString(_num);
			Num1->setVisible(true);

			ArrcrystalitemID[i] = EquipPromoteDataHandler::get_instance2()->m_Item_List[i].templateid;
			NFC_setNodeVisable(EquipPromoteView_Item1+ i*2,this,true);
		}
	}
}
void EquipPromoteView::_updataHideUnuseItemInfo()
{
	int i = EquipPromoteView_Item1 + EquipPromoteDataHandler::get_instance2()->m_Item_List.size()*2;
	for (;i<EquipPromoteView_Button;i++)
	{
		CCNode* pNode = this->getChildByTag(i);
		pNode->setVisible(false);
	}

}
void EquipPromoteView::_updataCostMoneyInfo()
{

	//花费
	CCLabelTTF* Gold = (CCLabelTTF*)this->getChildByTag(EquipPromoteView_Gold);
	char _gold[128]="";
	sprintf(_gold,"%d",EquipPromoteDataHandler::get_instance2()->m_CostMoney);
	Gold->setString(_gold);
	Gold->setVisible(true);
	if (ROLEINFODATAHANDLER->m_pRIData->money_ < EquipPromoteDataHandler::get_instance2()->m_CostMoney)
	{
		Gold->setColor(ccRED);
		m_IsCanPromote = false;
	}
	else
		Gold->setColor(ccWHITE);
	if (EquipPromoteDataHandler::get_instance2()->m_CostMoney == -1)
	{
		Gold->setVisible(false);
		this->getChildByTag(EquipPromoteView_Gold_Icon)->setVisible(false);
	}
	else
		this->getChildByTag(EquipPromoteView_Gold_Icon)->setVisible(true);
}
void EquipPromoteView::_updataLvLimitInfo()
{
	CCLabelTTF* Limit = (CCLabelTTF*)this->getChildByTag(EquipPromoteView_LV_Limit);
	char _limit[128]="";
	sprintf(_limit,SysLangDataManager::get_instance2()->GetSysLangById(4002).c_str(),GetCurItemLv(),EquipPromoteDataHandler::get_instance2()->m_Lv_Limit);
	Limit->setString(_limit);
	Limit->setVisible(true);
	if (GetCurItemLv() < EquipPromoteDataHandler::get_instance2()->m_Lv_Limit)
	{
		Limit->setColor(ccRED);
		m_IsCanPromote = false;
	}
	else
		Limit->setColor(ccWHITE);
}
void EquipPromoteView::_updataButtonInfo()
{
	CCMenu* pMenu = (CCMenu*)this->getChildByTag(EquipPromoteView_Button);
	pMenu->setVisible(true);
	CMenuItemSprite* pItem = (CMenuItemSprite*)pMenu->getChildByTag(0);
	if (m_IsCanPromote)
		pItem->setEnabled(true);
	else
		pItem->setEnabled(false);

	CCLabelTTF* pLabel = (CCLabelTTF*)this->getChildByTag(EquipPromoteView_Button_Label);
	pLabel->setVisible(true);
}

void EquipPromoteView::EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr)
{
	animationNode->removeFromParentAndCleanup(true);

}

void EquipPromoteView::_MapBtnTips()
{
	DTAwardBoard * dtab = (DTAwardBoard *)this->getChildByTag(EquipPromoteView_Item1);
	dtab->setIDX(EquipPromoteView_Item1);
	dtab->setTarget(this,menu_selector(EquipPromoteView::On_Btn_Tips));

	dtab = (DTAwardBoard *)this->getChildByTag(EquipPromoteView_Item2);
	dtab->setIDX(EquipPromoteView_Item2);
	dtab->setTarget(this,menu_selector(EquipPromoteView::On_Btn_Tips));


// 	CCMenu* ptemp = (CCMenu*)this->getChildByTag(EquipPromoteView_Item1_Btn);
// 	CMenuItemSprite* ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
// 	ptempItem->setIDX(EquipPromoteView_Item1_Btn);
// 	ptempItem->setTarget(this,menu_selector(EquipPromoteView::On_Btn_Tips));
// 
// 	ptemp = (CCMenu*)this->getChildByTag(EquipPromoteView_Item2_Btn);
// 	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
// 	ptempItem->setIDX(EquipPromoteView_Item2_Btn);
// 	ptempItem->setTarget(this,menu_selector(EquipPromoteView::On_Btn_Tips));

}

void EquipPromoteView::On_Btn_Tips(cocos2d::CCObject* pSender)
{
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int index = cc->getIDX();
	if (index == EquipPromoteView_Item1)
	{
		NETOBJECTTIPSDATAHANDLER->ToServerGetObjectTips(ArrcrystalitemID[0], IWindow::_TYPED_WINDOW_STRENGTHEN_);
	}
	else if(index == EquipPromoteView_Item2)
	{
		NETOBJECTTIPSDATAHANDLER->ToServerGetObjectTips(ArrcrystalitemID[1], IWindow::_TYPED_WINDOW_STRENGTHEN_);
	}
}

