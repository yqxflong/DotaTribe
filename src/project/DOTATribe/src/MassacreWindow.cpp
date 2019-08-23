// Name :		MassacreWindow.h
// Function:	扫荡窗口
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "cocos-ext.h"
#include "../include/MassacreWindow.h"
#include "../include/DOTATribeApp.h"
#include "../include/NFControlsManager.h"
#include "../include/NFAnimationController.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/WindowManager.h"
#include "../include/TimeSystem.h"
#include "../include/LoggerSystem.h"
#include "../include/MissionDataHandler.h"
#include "../include/SceneInfoDataManager.h"
#include "../include/UIViewDataManger.h"
#include "../include/MassacrePacket.h"
#include "../include/MassacreDataHandler.h"
#include "../include/SysLangDataManager.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/SelectSonMissionWindow.h"
#include "../include/MessageBoxWindow.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/CPublicVarReader.h"
#include "../include/CMenuItemSprite.h"
#include "../include/LevelUpDataHandler.h"
#include "../include/BagWindowDataHandler.h"
#include "../include/PopWindowManager.h"

using  namespace  cocos2d;
using  namespace  extension;

#define FontName	"ArialRoundedMTBold" //默认字体

#define CountNumNormal	5
#define CountNumMax	20
#define CounsumeVitality 5
#define Massacre_Finish 4015
#define EXPBALL 8

#define MaxItemNum 10
MassacreWindow::MassacreWindow()
{
	m_WindowType = _TYPED_WINDOW_MASSACRE_;
	m_selectIndex = 0;
	m_MassacreCount = 0;
	m_IsRealMassacreCount = 0;
	m_Massacre_Interval_Time = 0;
	m_exp = 0;
	m_money = 0;
	m_Count = 0;
	m_AllCount = 0;
	m_IsNeedSend = false;
}
MassacreWindow::~MassacreWindow()
{

}
bool MassacreWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_MASSACREWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_MASSACREWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATEDATA_MASSACREWINDOW_);

	//设置该弹窗的优先级
	IPopWindow::priority_=GetPriorityByCurWindowDef(POP_PRIORITY_SAODANG);
	return IWindow::Init();
}
bool MassacreWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;	
		InitControl();
		return true;
	} 
	while (false);

	return false;
}
void MassacreWindow::Tick()
{
	_uckCheckIsNeedSend();
	IWindow::Tick();
}
void MassacreWindow::Destroy()
{
	//
	PopWindowDidHide();
	//
	std::vector<MassacreData*>::iterator iter =  MassacreDataHandler::get_instance2()->MassacreDataList.begin();
	std::vector<MassacreData*>::iterator iter_end =  MassacreDataHandler::get_instance2()->MassacreDataList.end();
	for(;iter!=iter_end;++iter)
	{
		std::vector<ItemData*>::iterator iter2 =  (*iter)->ItemDataList.begin();
		std::vector<ItemData*>::iterator iter2_end = (*iter)->ItemDataList.end();
		for (;iter2!=iter2_end;++iter2)
		{
			delete *(iter2);
		}
		(*iter)->ItemDataList.clear();
		delete *(iter);
	}
	MassacreDataHandler::get_instance2()->MassacreDataList.clear();
	m_selectIndex = 0;
	m_MassacreCount = 0;
	m_IsRealMassacreCount = 0;
	m_Massacre_Interval_Time = 0;
	m_exp = 0;
	m_money = 0;
	m_Count = 0;
	m_AllCount = 0;
	m_IsNeedSend = false;
	IWindow::Destroy();
}

//显示弹窗
void MassacreWindow::ShowPopWindow()
{
	IPopWindow::ShowPopWindow();
	ShowWindow();
}
//弹窗已经隐藏
void MassacreWindow::PopWindowDidHide()
{
	IPopWindow::PopWindowDidHide();
}

void MassacreWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_MASSACREWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_MASSACREWINDOW_)
	{
		PushEvent(_TYPED_EVENT_UPDATA_MISSIONNEXTSTATES_);
		Destroy();
	}
	else if (iEventType == _TYPED_EVENT_UPDATEDATA_MASSACREWINDOW_)
	{
		_uckUpDataMassacreInfo();
	}
}

void MassacreWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	PopWindowManager::get_instance2()->AddPopWindow(this);
}

	/*
		展示自己的窗口
	*/
void MassacreWindow::ShowWindow(){
	NFC_showCommunicationWating(false);
	Show(true);
	NFC_Action_fallDown(m_pRoot);
}

void MassacreWindow::InitControl()
{
	_uckCreateLayer();
	_uckInitButton();
	_uckInitBossStates();
	_uckUpdataRewardInfo();
}

void MassacreWindow::On_Click_Close(cocos2d::CCObject* pSender)
{
	if (m_IsRealMassacreCount == 0||MassacreDataHandler::get_instance2()->getCanForceCloseState())
	{
		MassacreDataHandler::get_instance2()->setToForceCloseInitState();
		PushEvent(_TYPED_EVENT_UPDATE_UI_TEXT_);
		PushEvent(_TYPED_EVENT_HIDE_MASSACREWINDOW_);
	}
	else
		m_MassacreCount = -1;
}

void MassacreWindow::On_Click_Choice(cocos2d::CCObject* pSender)
{
	_uckSetSelectIndex((CMenuItemSprite*)pSender);
	if (_uckCheckIsBagFull())
		return;
	if (!_uckCheckIsHasChallengeTimes())
		return;
	_uckCheckIsBossStates();
	_uckClearMassacreInfo();
	_uckSetMassacreCount();	
	_uckUpdataRewardInfo();
	_uckSendMassacrePacket();
}

StatesInfoData* MassacreWindow::_uckGetCurStates()
{
	int statesid = 0;
	statesid = MissionDataHandler::get_instance2()->getCurStatesID();
	StatesInfoData* pData =  MissionDataHandler::get_instance2()->GetStatesInfoInfo(statesid);

	return pData;
}

void MassacreWindow::_uckCheckIsNeedSend()
{
	if (m_IsNeedSend)
		m_Massacre_Interval_Time += TimeSystem::get_instance2()->GetLastTickTime();

	if (m_IsNeedSend && m_Massacre_Interval_Time > CLIENTCONSTDATAMANGER->getValueByKey(Massacre_Interval_Time)/1000.0f)
	{
		int statesid = 0;
		statesid = MissionDataHandler::get_instance2()->getCurStatesID();
		//send Packet
		int missionID=MissionDataHandler::get_instance2()->getCurMissionID();
		MassacreDataHandler::get_instance2()->ToServerPacket(missionID,statesid);
		 
		m_Massacre_Interval_Time = 0;
		m_IsNeedSend = false;
	}
}

void MassacreWindow::_uckCreateLayer()
{
	m_pRoot  = CCLayer::create();
	m_pRootNode->addChild(m_pRoot,1);
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kMASSACREVIEW,m_pRoot);
}

void MassacreWindow::_uckInitButton()
{
	CPriorityLayerColor* pTempNode = (CPriorityLayerColor*)m_pRoot->getChildByTag(MassacreMakeLayer);
	pTempNode->removeFromParent();
	m_pRootNode->addChild(pTempNode);

	CCMenu* ptemp = (CCMenu*)m_pRoot->getChildByTag(MassacreCloseButton);
	CMenuItemSprite* ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(MassacreWindow::On_Click_Close));

	ptemp = (CCMenu*)m_pRoot->getChildByTag(MassacreChoice1Button);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(MassacreWindow::On_Click_Choice));
	m_choice1 =ptempItem;

	ptemp = (CCMenu*)m_pRoot->getChildByTag(MassacreChoice2Button);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(MassacreWindow::On_Click_Choice));
	m_choice2 =ptempItem;

	ptemp = (CCMenu*)m_pRoot->getChildByTag(MassacreChoice3Button);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(MassacreWindow::On_Click_Choice));
	m_choice3 =ptempItem;

	ptemp = (CCMenu*)m_pRoot->getChildByTag(MassacreChoice4Button);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(MassacreWindow::On_Click_Choice));
	m_choice4 =ptempItem;
}

void MassacreWindow::_uckInitBossStates()
{
	StatesInfoData* pData = _uckGetCurStates();
	if (pData->getIsBoss())
	{
		m_choice1->setVisible(false);
		m_pRoot->getChildByTag(MassacreChoice1Text)->setVisible(false);
		m_choice2->setVisible(false);
		m_pRoot->getChildByTag(MassacreChoice2Text)->setVisible(false);
		m_choice3->setVisible(false);
		m_pRoot->getChildByTag(MassacreChoice3Text)->setVisible(false);
	}
	else
	{
		m_choice4->setVisible(false);
		m_pRoot->getChildByTag(MassacreChoice4Text)->setVisible(false);
	}
}

void MassacreWindow::_uckSetSelectIndex( CMenuItemSprite* pItem )
{
	if (pItem == m_choice1)
		m_selectIndex = 0;
	else if(pItem == m_choice2)
		m_selectIndex = 1;
	else if(pItem == m_choice3)
		m_selectIndex = 2;
}

void MassacreWindow::_uckCheckIsBossStates()
{
	StatesInfoData* pData = _uckGetCurStates();

	if (pData->getIsBoss())
	{
		m_choice4->setEnabled(false);
	}
	else
	{
		m_choice1->setEnabled(false);
		m_choice2->setEnabled(false);
		m_choice3->setEnabled(false);
	}

	if (pData->getIsBoss())
		m_selectIndex = 2;
}

void MassacreWindow::_uckUpdataBossStates()
{
	StatesInfoData* pData = _uckGetCurStates();

	if (pData->getIsBoss())
	{
		if (pData->getChallengeTimes() != pData ->getMaxChallengeTimes())
			m_choice4->setEnabled(true);
	}
	else
	{
		if (pData->getChallengeTimes() != pData ->getMaxChallengeTimes())
		{
			m_choice1->setEnabled(true);
			m_choice2->setEnabled(true);
			m_choice3->setEnabled(true);			
		}
	}
}

void MassacreWindow::_uckSetMassacreCount()
{
	StatesInfoData* pData = _uckGetCurStates();
	switch (m_selectIndex)
	{
	case MassacreSelectInde1:
		{			
			m_MassacreCount = CountNumNormal;
			m_IsRealMassacreCount = ROLEINFODATAHANDLER->m_pRIData->vitality_ / CounsumeVitality;
			break;
		}
	case MassacreSelectInde2:
		{
			m_MassacreCount = CountNumMax;
			m_IsRealMassacreCount = ROLEINFODATAHANDLER->m_pRIData->vitality_ / CounsumeVitality;
			break;
		}
	case MassacreSelectInde3:
		{
			if (pData->getIsBoss())
			{
				m_MassacreCount = pData->getMaxChallengeTimes() - pData->getChallengeTimes();
				m_IsRealMassacreCount = pData->getMaxChallengeTimes() - pData->getChallengeTimes();
			}
			else
			{
				m_MassacreCount = ROLEINFODATAHANDLER->m_pRIData->vitality_ / CounsumeVitality;
				m_IsRealMassacreCount = ROLEINFODATAHANDLER->m_pRIData->vitality_ / CounsumeVitality;
			}
			break;
		}
	default:
		break;
	}
}

void MassacreWindow::_uckClearMassacreInfo()
{
	StatesInfoData* pData = _uckGetCurStates();
	m_MassacreCount = 0;
	m_exp = 0;
	m_money = 0;
	m_Count = 0;
	m_AllCount = pData->getMaxChallengeTimes()-pData->getChallengeTimes();
	m_ItemList.clear();
	_uckHiedAllItem();
}

void MassacreWindow::_uckSendMassacrePacket()
{
	int statesid=0;
	statesid = MissionDataHandler::get_instance2()->getCurStatesID();
	int missionID=MissionDataHandler::get_instance2()->getCurMissionID();
	MassacreDataHandler::get_instance2()->ToServerPacket(missionID,statesid);
}

bool MassacreWindow::_uckCheckIsBagFull()
{
	int type = BAGWINDOWDATAHANDLER->IsBagFull();
	if (type != -1)
	{
		_uckShowTipBox(type);
		return true;
	}

	return false;
}

bool MassacreWindow::_uckCheckIsHasChallengeTimes()
{
	StatesInfoData* pData = _uckGetCurStates();

	if (pData->getChallengeTimes() >= pData->getMaxChallengeTimes())
	{
		_uckShowTipBox(LESS_TIME);
		return false;
	}

	return true;
}

void MassacreWindow::_uckShowTipBox( int type )
{
	switch(type)
	{
	case FULL_ITEM_BEG:
		{
			//物品满
			std::string str2=SysLangDataManager::get_instance2()->GetSysLangById(137);
			NFC_showMessageBox(kDEFAULT,str2);
		}break;
	case FULL_EQUP_BEG:
		{
			//装备满
			std::string str2=SysLangDataManager::get_instance2()->GetSysLangById(138);
			NFC_showMessageBox(kDEFAULT,str2);
		}break;
	case LESS_TILI:
		{
			//体力不足
			std::string str2=SysLangDataManager::get_instance2()->GetSysLangById(128);
			NFC_showMessageBox(kDEFAULT,str2);
		}break;
	case LESS_TIME:
		{
			//次数不够
			std::string str2=SysLangDataManager::get_instance2()->GetSysLangById(127);
			NFC_showErrorTips_2(str2);
		}break;
	case LESS_HEROLEVEL:
		{
			//人物等级不足
			
		}break;
	default:
		break;

	}

}

void MassacreWindow::_uckSetExp()
{
	CCLabelTTF* pExp = (CCLabelTTF*)m_pRoot->getChildByTag(MassacreExp);
	char _exp[128]="";
	sprintf(_exp,"%d", m_exp);
	pExp->setString(_exp);
}

void MassacreWindow::_uckSetMoney()
{
	CCLabelTTF* pMoney = (CCLabelTTF*)m_pRoot->getChildByTag(MassacreMoney);
	char _money[128]="";
	sprintf(_money,"%d", m_money);
	pMoney->setString(_money);
}

void MassacreWindow::_uckSetTimes()
{
	StatesInfoData * pData = _uckGetCurStates();
	CCLabelTTF* pCount = (CCLabelTTF*)m_pRoot->getChildByTag(MassacreCountNum);
	char _count[128]="";
	sprintf(_count,SysLangDataManager::get_instance2()->GetSysLangById(121).c_str(),0,(pData->getMaxChallengeTimes() - pData->getChallengeTimes()));
	pCount->setString(_count);
}

void MassacreWindow::_uckReSetTimes()
{
	CCLabelTTF* pCount = (CCLabelTTF*)m_pRoot->getChildByTag(MassacreCountNum);
	char _count[128]="";
	sprintf(_count,SysLangDataManager::get_instance2()->GetSysLangById(121).c_str(),m_Count,m_AllCount);
	pCount->setString(_count);
}

void MassacreWindow::_uckHiedAllItem()
{
	for (int i=MassacreOBJ_1_;i<=MassacreIconNum10;i++)
	{
		NFC_setNodeVisable(i,m_pRoot,false);
	}
}

void MassacreWindow::_uckUpdataItemList()
{
	MassacreData* pData = MassacreDataHandler::get_instance2()->MassacreDataList[0];
	for (int i=0;i<pData->ItemDataList.size();i++)
	{
		if (m_ItemList.size()>0)
		{	
			bool flag = false;
			for (int j=0;j<m_ItemList.size();j++)
			{
				if (pData->ItemDataList[i]->itemID == m_ItemList[j].itemID && !m_ItemList[j].isEquip)
				{
					m_ItemList[j].itemCount+=pData->ItemDataList[i]->itemCount;
					flag =true;
					break;
				}
			}
			if (!flag)
			{
				if (m_ItemList.size()<MaxItemNum)
					_uckAddItem(pData,i);
			}
		}
		else
			_uckAddItem(pData,i);
	}
}

void MassacreWindow::_uckAddItem( MassacreData* pData,int idx )
{
	ItemData data;
	data.itemName = pData->ItemDataList[idx]->itemName;
	data.itemID = pData->ItemDataList[idx]->itemID;
	data.iconID = pData->ItemDataList[idx]->iconID;
	data.itemCount = pData->ItemDataList[idx]->itemCount;
	data.quality = pData->ItemDataList[idx]->quality;
	data.isEquip = pData->ItemDataList[idx]->isEquip;
	m_ItemList.push_back(data);
}

void MassacreWindow::_uckSetItem()
{
	for (int i=0;i<m_ItemList.size();i++)
	{
		//award
		DTAwardBoard* dd = (DTAwardBoard*)m_pRoot->getChildByTag(MassacreOBJ_1_+i*2);
		dd->ChangeObject(m_ItemList[i].quality,m_ItemList[i].iconID);
		dd->setEnabled(false);
		dd->setVisible(true);
		//num
		CCLabelTTF* pNum = (CCLabelTTF*)m_pRoot->getChildByTag(MassacreOBJ_1_+i*2+1);
		char _num[128]="";
		sprintf(_num,"%d",m_ItemList[i].itemCount);
		pNum->setString(_num);
		pNum->setVisible(true);
	}
}

void MassacreWindow::_uckAddExpAndMoney()
{
	MassacreData* pData = MassacreDataHandler::get_instance2()->MassacreDataList[0];
	m_exp += pData->roleExp;
	m_money += pData->money;
}

void MassacreWindow::_uckUpdataTimesAndCloseWindow()
{
	StatesInfoData* pStatesData = _uckGetCurStates();
	pStatesData->setChallengeTimes(pStatesData->getChallengeTimes()+1);
	PushEvent(_TYPED_EVENT_UPDATE_UI_TEXT_);
	PushEvent(_TYPED_EVENT_HIDE_MASSACREWINDOW_);
}

void MassacreWindow::_uckUpdataRewardInfo()
{
	if (MassacreDataHandler::get_instance2()->MassacreDataList.size()<=0)
	{
		_uckSetExp();
		_uckSetMoney();
		_uckSetTimes();
		_uckHiedAllItem();
	}
	else
	{
		_uckAddExpAndMoney();
		_uckSetExp();
		_uckSetMoney();
		_uckReSetTimes();
		_uckUpdataItemList();
		_uckSetItem();
	}

}

/*
	更新扫荡信息
*/
void MassacreWindow::_uckUpDataMassacreInfo()
{
	if (m_MassacreCount < 0)
	{
		_uckUpdataTimesAndCloseWindow();
		return;
	} 
	if (m_MassacreCount >= 0 && this->IsVisible())
	{
		if (MassacreDataHandler::get_instance2()->EndType !=0)
			_uckUpdataTimesAndStopMassacre();
		else
			_uckUpdataTimesAndTheLastMassacre();
	}  
}

//停止扫荡
void MassacreWindow::_uckUpdataTimesAndStopMassacre()
{
	m_IsNeedSend = false;
	m_MassacreCount = 0;
	m_IsRealMassacreCount = 0;
	_uckUpdataBossStates();
	if (MassacreDataHandler::get_instance2()->EndType == 1)//1是背包满
		_uckShowTipBox(BAGWINDOWDATAHANDLER->IsBagFull());
	else
		_uckShowTipBox(MassacreDataHandler::get_instance2()->EndType);
}

//更新最新一次战斗的结果
void MassacreWindow::_uckUpdataTimesAndTheLastMassacre()
{
	m_IsNeedSend =true;
	m_MassacreCount--;
	m_Count++;
	if(m_MassacreCount>=0)
	{
		StatesInfoData* pStatesData = _uckGetCurStates();
		pStatesData->setChallengeTimes(pStatesData->getChallengeTimes()+1);
	} 
	if(m_MassacreCount <= 0)
	{
		m_IsNeedSend = false;
		NFC_showErrorTips_2(SysLangDataManager::get_instance2()->GetSysLangById(Massacre_Finish));
		_uckUpdataBossStates();
		m_MassacreCount = 0;
		m_IsRealMassacreCount = 0;
	} 
	_uckUpdataRewardInfo();
	PushEvent(_TYPED_EVENT_UPDATE_UI_TEXT_);
}

//
////继续扫荡
//void MassacreWindow::_uckUpdataTimesAndContinueMassacre()
//{
//	StatesInfoData* pStatesData = _uckGetCurStates();
//	if (m_IsRealMassacreCount>0)
//	{
//		m_Count++;
//		pStatesData->setChallengeTimes(pStatesData->getChallengeTimes()+1);
//		NFC_showErrorTips_2(SysLangDataManager::get_instance2()->GetSysLangById(Massacre_Finish));
//	}
//	_uckUpdataRewardInfo();
//	_uckUpdataBossStates();
//	m_MassacreCount = 0;
//	m_IsRealMassacreCount = 0;
//	PushEvent(_TYPED_EVENT_UPDATE_UI_TEXT_);
//}

