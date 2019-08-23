#include "../include/MainTaskWindow.h"
#include "../include/WindowManager.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/LoggerSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/CPublicVarReader.h"
#include "../include/ClientConstDataManager.h"
#include "../include/ServantView.h"
#include "../include/VariableSystem.h"
#include "../include/UIViewDataManger.h"
#include "../include/config_HomeWindow.h"
#include "../include/GuideSystem.h"
#include "../include/CMenuItemSprite.h"
#include "../include/MainTaskDataHandler.h"
#include "../include/NFControlsManager.h"
#include "../include/ResourceIDDataManager.h"
#include "../include/StrengthenWindow.h"
#include "../include/MissionDataHandler.h"
#include "../include/TeamBattleProcedure.h"
#include "../include/FriendPacket.h"
#include "../include/C2SArenaInfoPacket.h"
#include "../include/HeroTechnologyPacket.h"
#include "../include/RevenuePacket.h"
#include "../include/HomeProcedure.h"
#include "../include/SelectMissionProcedure.h"
#include "../include/ClimbTowerDataHandler.h"
#include "../include/HeroTechnologyDataHandler.h"
#include "../include/NetObjectTipsDataHandler.h"
#include "../include/MainTaskPacket.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/StrengthenWindow.h"
#include "../include/PuCongWindow.h"

 
using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

#define   _NORMAL_CELL_BG_ID_     619
#define   _SELECT_CELL_BG_ID_	  620
#define   _DEFAULT_VISIABLE_NUM_	4
/*
物品Tips
*/
#define   _REWARD_OBJECT_TIPS_(index)    if(m_pActiveTaskItem!=NULL) \
{\
	if(m_pActiveTaskItem->rewardVector.size()>index) \
	{ \
		MainTaskReward * pTaskItem=m_pActiveTaskItem->rewardVector.at(index);\
		if(pTaskItem->type==kDT_AWARD_OBJECT) \
		{ \
			NETOBJECTTIPSDATAHANDLER->ToServerGetObjectTips(pTaskItem->templateId, _TYPED_WINDOW_MAINTASKWINDOW_);\
		}\
	}\
}\




 
MainTaskWindow::MainTaskWindow()
:m_nBackWindow(-1)
{
	m_WindowType   = _TYPED_WINDOW_MAINTASKWINDOW_;
	m_WindowZOrder = _TYPED_WINDOW_ZORDER_NORMAL_;
	m_pTable=NULL;
	m_szCELL=CCSizeZero; 
	m_nActiveTaskIndex=-1;
	m_pMainTaskData=NULL;
	m_pActiveTaskItem=NULL;
	m_nStartFinishCellIndex=0; 
	m_isNeedToShowTips=false;
}

MainTaskWindow::~MainTaskWindow()
{

}

bool MainTaskWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_MAINTASKWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_MAINTASKWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_MAINTASKWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_REFRESH_UPDATEUI_, true);
	RegisterEvent(_TYPED_EVENT_FADEOUT_MAINTASKWINDOW_, true);

	return IWindow::Init();
}

bool MainTaskWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		initUILayout();
		return true;
	} 
	while (false);

	return false;
}


void MainTaskWindow::Tick()
{
	IWindow::Tick();

}

void MainTaskWindow::Destroy()
{
	if(m_isNeedToShowTips)
	{
		NFC_showErrorTips_2(m_pActiveTaskItem->taskInfo);
		m_isNeedToShowTips=false;
	}
	m_pActiveTaskItem=NULL;
	m_nStartFinishCellIndex=0;
	m_pMainTaskData=NULL;
	m_nActiveTaskIndex=-1;
	IWindow::Destroy();
}

void MainTaskWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if(iEventType == _TYPED_EVENT_SHOW_MAINTASKWINDOW_)
	{
		PushEvent(_TYPED_EVENT_CLEAR_FORCEPUSHTASKWORDWINDOW_);
		OnShowWindowEventHandler(paramList);
	}
	else if(iEventType == _TYPED_EVENT_UPDATE_MAINTASKWINDOW_)
	{
		//动态更新数据  智能锁定 
		DispatchUpdateEvent(atoi((*paramList.begin()).c_str()));
		return ;
	}
	else if(iEventType == _TYPED_EVENT_HIDE_MAINTASKWINDOW_)
	{
		Destroy();
	}
	else if(iEventType == _TYPED_EVENT_FADEOUT_MAINTASKWINDOW_)
	{
		// to do
	}
	else if(iEventType==_TYPED_EVENT_REFRESH_UPDATEUI_)
	{
		UpdateDiamondAndGold();
	}
	 
}

void MainTaskWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
	if(!paramList.empty())
	{ 
		m_nBackWindow=atoi((*paramList.begin()).c_str()); 
	} 
}


void MainTaskWindow::initUILayout()
{
	m_pRoot=m_pRootNode;
	m_pRoot->setAnchorPoint(CCPointZero);
	m_pRoot->setPosition(CCPointZero);
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kMAINTASKWINDOW, m_pRoot);
	mapStaticBtn();
	SetTableView(); 
	UpdateDiamondAndGold();
	HideAllTaskContent();
}

void MainTaskWindow::mapStaticBtn()
{  
	bindSelectorBtnByTag(_TASKUI_CLOSE_BTN_TAG_);
	bindSelectorBtnByTag(_TASKUI_REWARD_BTN_TAG_);
	bindSelectorBtnByTag(_TASKUI_TASK_GOTO_BTN_TAG_);
	BindSelectorForTouchSprite(_TASKUI_REWARD1_OBJ_TAG_);
	BindSelectorForTouchSprite(_TASKUI_REWARD2_OBJ_TAG_);
	BindSelectorForTouchSprite(_TASKUI_REWARD3_OBJ_TAG_);
}

void MainTaskWindow::attachTaskData()
{
	//to do 
	m_pMainTaskData=MainTaskDataHandler::get_instance2()->m_pMainTaskData;
	if(m_pMainTaskData!=NULL)
	{
		m_nStartFinishCellIndex=m_pMainTaskData->finishCellIndex();
		if(m_nStartFinishCellIndex)
		m_nActiveTaskIndex=m_nStartFinishCellIndex;
	}

}


void    MainTaskWindow::bindSelectorBtnByTag(int nodeTag)
{  
	CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(nodeTag);
	if(menu)
	{
		CMenuItemSprite * pMenuItem = (CMenuItemSprite *)menu->getChildByTag(0);
		pMenuItem->setIDX(nodeTag);
		pMenuItem->setTarget(this, menu_selector(MainTaskWindow::CommonBtnCallBackHandler));
	}
}

void   MainTaskWindow::BindSelectorForTouchSprite(int signID)
{
	DTAwardBoard * pTouchSprite=(DTAwardBoard *)m_pRoot->getChildByTag(signID);
	if(pTouchSprite!=NULL)
	{
		pTouchSprite->setIDX(signID);
		pTouchSprite->setTarget(this,menu_selector(MainTaskWindow::OnAwardClicked));
	}
} 


void	MainTaskWindow::DispatchUpdateEvent(int updateAttachParam)
{
	switch(updateAttachParam)
	{
	case 0:
		{
			attachTaskData();
			refreshTableView(m_pTable);
			ShowStartTaskLayer();
			NFC_showCommunicationWating(false);
			break;
		}
	case 1:
		{
			UpdateTaskDataAndUI(true);
			break;
		}
	case 2:
		{ 
			UpdateTaskDataAndUI(false);
		}
		break;
	default:
		break;
	}
}

void    MainTaskWindow::HideAllTaskContent()
{
	NFC_setNodeVisable(_TASKUI_TASK_CONTENT_TAG_,GetRootNode(),false);
	NFC_setNodeVisable(_TASKUI_TASK_GOTO_BTN_TAG_,GetRootNode(),false);
	NFC_setNodeVisable(_TASKUI_BG_GOTO_BTN_EFFECT_TAG_,GetRootNode(),false);
	NFC_setNodeVisable(_TASKUI_REWARD_BTN_TAG_,GetRootNode(),false);
	NFC_setNodeVisable(_TASKUI_REWARD_CONTENT_TAG_,GetRootNode(),false);

	for(int startUIIndex=_TASKUI_REWARD1_OBJ_TAG_;startUIIndex<=_TASKUI_REWARD3_NUM_TAG_;startUIIndex++)
	{
		NFC_setNodeVisable(startUIIndex,GetRootNode(),false);
	} 
}

//奖品点击事件
void MainTaskWindow::OnAwardClicked(cocos2d::CCObject* pSender){
	CMenuItemSprite * pTouchSprite=(CMenuItemSprite *)pSender;
	if(pTouchSprite!=NULL)
	{
		switch(pTouchSprite->getIDX())
		{
		case _TASKUI_REWARD1_OBJ_TAG_:
			{ 
				_REWARD_OBJECT_TIPS_(0)
					CCLOG("Toush Sprite 1 Handler!");
				break;
			}
		case _TASKUI_REWARD2_OBJ_TAG_:
			{
				CCLOG("Toush Sprite 2 Handler!");
				_REWARD_OBJECT_TIPS_(1)
					break;
			}
		case _TASKUI_REWARD3_OBJ_TAG_:
			{
				_REWARD_OBJECT_TIPS_(2)
					CCLOG("Toush Sprite 3 Handler!");
				break;
			}
		default:
			break;
		}
	} 
}

void   MainTaskWindow::CommonBtnCallBackHandler(cocos2d::CCObject * pSender)
{ 
	CMenuItemSprite  * pMenuItem=(CMenuItemSprite *)pSender;
	if(pMenuItem!=NULL)
	{
		switch(pMenuItem->getIDX())
		{
		case _TASKUI_CLOSE_BTN_TAG_:
			{
				CloseHanlder();
				break;
			}
		case _TASKUI_REWARD_BTN_TAG_:
			{
				RewardHandler();
				break;
			}
		case _TASKUI_TASK_GOTO_BTN_TAG_:
			{
			   GoToGuidModuleHandler();
			   break;
			}
		default: 
			break;
		}
	} 
}


void  MainTaskWindow::SetTableView()
{
	CCNode* cc=m_pRoot->getChildByTag(_TASKUI_TASK_CELL_TAG_);
	m_szCELL=cc->getContentSize();

	m_pTable =(cocos2d::extension::CCTableView *)m_pRoot->getChildByTag(_TASKUI_TASK_TABLEVIEW_TAG_);
	m_pTable->setDataSource(this);
	m_pTable->setDelegate(this);
	m_pTable->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pTable->setTouchEnabled(true);
	m_pTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
}


void  MainTaskWindow::ShowStartTaskLayer()
{   
	if(m_nActiveTaskIndex!=-1)
	{ 
		if(m_nActiveTaskIndex>_DEFAULT_VISIABLE_NUM_)
		{ 
			refreshTableViewOffCount(m_pTable,m_pMainTaskData->getTaskNum()-m_nActiveTaskIndex-1);
		} 
		ActiveCellItemWithCellIndex(m_nActiveTaskIndex);
	}
	else
	{  
		if(!m_pMainTaskData->getTaskNum())
		{ 
			//hide All Content
			HideAllTaskContent();
		}
		else
		{
			//show First TaskContent
			ActiveCellItemWithCellIndex(0);
		}
	}

	UpdateDiamondAndGold();
}
  

void  MainTaskWindow::GoToGuidModuleHandler()
{
	if(m_pActiveTaskItem!=NULL)
	{  
		m_isNeedToShowTips=true;
		DispatchSwitchModule(m_pActiveTaskItem->guidType,m_pActiveTaskItem->guideParam);
	} 
}

   
void MainTaskWindow::DispatchSwitchModule(int moduleType, std::string param)
{  
	//log for module goto
	LOGGERSYSTEM->LogInfo("MainTaskWindow::_gotoModule  %d, %s", moduleType, param.c_str());

	//==============新手引导===================
	GUIDESYSTEM->Next();

	//关闭任务窗口
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_MAINTASKWINDOW_);
  
	switch(moduleType)
	{
	case MainTaskDataHandler::_MODULE_DEFINE_GATE_:
		{
			DOTATribeApp::get_instance2()->ClearAllVisibleWindow(IWindow::_TYPED_WINDOW_NEWEQUIPREMINDWINDOW_);
			//指定关卡
			int param0(0), param1(0);
			sscanf(param.c_str(), "%d,%d", &param0, &param1);
			StatesInfoData * infodata = MissionDataHandler::get_instance2()->GetStatesInfoInfo(param0, param1);
			if(infodata != NULL && infodata->getCanChallenge())
			{
				MissionDataHandler::get_instance2()->JumpToAppointStates(param0, param1);
			}
			else
			{ 
				MissionDataHandler::get_instance2()->JumpToAppointStates(MissionDataHandler::get_instance2()->getMissonInfoDataList().size());
			}
			break;
		}
	case MainTaskDataHandler::_MODULE_HIGHEST_GATE_:
		{
			DOTATribeApp::get_instance2()->ClearAllVisibleWindow(IWindow::_TYPED_WINDOW_NEWEQUIPREMINDWINDOW_);
			//最高关卡
			MissionDataHandler::get_instance2()->JumpToAppointStates(MissionDataHandler::get_instance2()->getMissonInfoDataList().size());
			break;
		}
	case MainTaskDataHandler::_MODULE_SHOP_:
		{
			DOTATribeApp::get_instance2()->ClearAllVisibleWindow(IWindow::_TYPED_WINDOW_NEWEQUIPREMINDWINDOW_);
			//商店
			int type(0);
			sscanf(param.c_str(), "%d", &type);
			if(DOTATribeApp::get_instance2()->GetActiveProcedure()->GetType()!=IProcedure::_TYPED_HOME_PROCEDURE_)
			{
				DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_MARKETPWINDOW_);
				if(type == 1)
				{//精品商店
					DOTATribeApp::get_instance2()->m_pHomeProcedure->SetSubViewType(1); 
				}
				else if(type == 2)
				{//声望商店
					DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(0);
				}
				else if(type == 3)
				{//秘宝商店
					DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(1); 
				}
				EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_,_to_event_param_(IProcedure::_TYPED_HOME_PROCEDURE_));
			}
			else
			{   
				if(type == 1)
				{//精品商店
					EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_MARKETPWINDOW_, _to_event_param_(0)); 
				}
				else if(type == 2)
				{//声望商店
					EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_SHOPWINDOW_, _to_event_param_(1));
				}
				else if(type == 3)
				{//秘宝商店
					//EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_SHOPWINDOW_, _to_event_param_(1));
				}
			} 
			break;
		}
	case MainTaskDataHandler::_MODULE_EQUIO_LEVELUO_GATE_:
		{
			int type(0);
			sscanf(param.c_str(), "%d", &type);
			DOTATribeApp::get_instance2()->ClearAllVisibleWindow(IWindow::_TYPED_WINDOW_NEWEQUIPREMINDWINDOW_);
		   //装备升级
		   if(DOTATribeApp::get_instance2()->GetActiveProcedure()->GetType()==IProcedure::_TYPED_HOME_PROCEDURE_)
		   {   
			      EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_STRENTHENWINDOW_, _to_event_param_(type)); 
		   }
		   else
		   {
			   DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_STRENTHENWINDOW_);
			   DOTATribeApp::get_instance2()->m_pHomeProcedure->SetSubViewType(type);
			   EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_,_to_event_param_(IProcedure::_TYPED_HOME_PROCEDURE_));
		   } 
		   break;
		}
	case MainTaskDataHandler::_MODULE_HEROBAR_GATE_:
		{
			DOTATribeApp::get_instance2()->ClearAllVisibleWindow(IWindow::_TYPED_WINDOW_NEWEQUIPREMINDWINDOW_);
			//召唤英雄
			if(DOTATribeApp::get_instance2()->GetActiveProcedure()->GetType()==IProcedure::_TYPED_HOME_PROCEDURE_)
			{
				PushEvent(_TYPED_EVENT_SHOW_HEROBARWINDOW_);
			}
			else
			{
				DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_HEROBARWINDOW_);
				EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_,_to_event_param_(IProcedure::_TYPED_HOME_PROCEDURE_));
			} 
			break;
		}
	case MainTaskDataHandler::_MODULE_HERO_EQUIP_GATE_:
		{
			DOTATribeApp::get_instance2()->ClearAllVisibleWindow(IWindow::_TYPED_WINDOW_NEWEQUIPREMINDWINDOW_);
			//召唤英雄
			if(DOTATribeApp::get_instance2()->GetActiveProcedure()->GetType()==IProcedure::_TYPED_HOME_PROCEDURE_)
			{ 
				PushEvent(_TYPED_EVENT_SHOW_PESWINDOW_);
			}
			else
			{
				DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_PESWINDOW_);
				EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_,_to_event_param_(IProcedure::_TYPED_HOME_PROCEDURE_));
			} 
			break; 
		}
	case MainTaskDataHandler::_MODULE_ARENA_GATE_:
		{ 
			//竞技场
			if(DOTATribeApp::get_instance2()->GetActiveProcedure()->GetType()!=IProcedure::_TYPED_ARENA_PROCEDURE_)
			{
				 DOTATribeApp::get_instance2()->ClearAllVisibleWindow(IWindow::_TYPED_WINDOW_NEWEQUIPREMINDWINDOW_);
				C2SArenaInfoPacket  requestArenaInfo;
				requestArenaInfo.Send();
			}   
			break;
		}
	case MainTaskDataHandler::_MODULE_HERO_LIST_GATR_:
		{ 
			DOTATribeApp::get_instance2()->ClearAllVisibleWindow(IWindow::_TYPED_WINDOW_NEWEQUIPREMINDWINDOW_);
			//召唤英雄
			if(DOTATribeApp::get_instance2()->GetActiveProcedure()->GetType()==IProcedure::_TYPED_HOME_PROCEDURE_)
			{ 
				PushEvent(_TYPED_EVENT_SHOW_HeroIllustratedWindow_);
			}
			else
			{
				DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_HeroIllustratedWindow_);
				EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_LOADINGWINDOW_,_to_event_param_(IProcedure::_TYPED_HOME_PROCEDURE_));
			} 
			break;  
		}
	case MainTaskDataHandler::_MODULE_MINE_:
		{   
			// 矿洞
			int type(0);
			sscanf(param.c_str(), "%d", &type);
			if(DOTATribeApp::get_instance2()->GetActiveProcedure()->GetType()!=IProcedure::_TYPED_HOME_PROCEDURE_)
			{  
				DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_PUCONGWINDOW_);
				if(type == 1)
				{
					DOTATribeApp::get_instance2()->m_pHomeProcedure->SetSubViewType(PuCongWindow::HLW_HUNT);
				}
				else if(type == 2)
				{
					DOTATribeApp::get_instance2()->m_pHomeProcedure->SetSubViewType(PuCongWindow::HLW_SERVANT);
				}
				else if(type == 3)
				{
					DOTATribeApp::get_instance2()->m_pHomeProcedure->SetSubViewType(PuCongWindow::HLW_MINING);
				}
				EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_LOADINGWINDOW_,_to_event_param_(IProcedure::_TYPED_HOME_PROCEDURE_));
			}
			else
			{
				DOTATribeApp::get_instance2()->ClearAllVisibleWindow(IWindow::_TYPED_WINDOW_NEWEQUIPREMINDWINDOW_);
				if(type == 1)
				{//矿洞 
					EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_PUCONGWINDOW_, _to_event_param_(PuCongWindow::HLW_HUNT));
				}
				else if(type == 2)
				{//苦工
					EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_PUCONGWINDOW_, _to_event_param_(PuCongWindow::HLW_SERVANT));
				}
				else if(type == 3)
				{//金矿采集
					EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_PUCONGWINDOW_, _to_event_param_(PuCongWindow::HLW_MINING));
				}
			}
			break;
		}
	case MainTaskDataHandler::_MODULE_REMOTEANTIQUITY_:
		{    
			//远古寻迹
			if(DOTATribeApp::get_instance2()->GetActiveProcedure()->GetType()!=IProcedure::_TYPED_TEAMBATTLE_PROCEDURE_)
			{
				//to do 
				DOTATribeApp::get_instance2()->m_pTeamBattleProcedure->ChangeNowState(TeamBattleProcedure::_TEAMBATTLE_STATE_SELECTGATE_);
				EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_, _to_event_param_(IProcedure::_TYPED_TEAMBATTLE_PROCEDURE_));
			}
			else
			{
				//to do  
				return ;
			}
			break;
		}
	case MainTaskDataHandler::_MODULE_TESTTOWER_:
		{ 
			//试练塔
			if(DOTATribeApp::get_instance2()->GetActiveProcedure()->GetType()!=IProcedure::_TYPED_HOME_PROCEDURE_)
			{
				DOTATribeApp::get_instance2()->ClearAllVisibleWindow(IWindow::_TYPED_WINDOW_NEWEQUIPREMINDWINDOW_);
				DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_CLIMBTOWERWINDOW_);
				DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure); 
				CLIMBTOWERDATAHANDLER->ToServerEnterTower();
			}
			else
			{ 
				if(!WindowManager::get_instance2()->IsWindowVisible(_TYPED_WINDOW_CLIMBWINDOW_))
				{
					DOTATribeApp::get_instance2()->ClearAllVisibleWindow(IWindow::_TYPED_WINDOW_NEWEQUIPREMINDWINDOW_);
					PushEvent(_TYPED_EVENT_SHOW_CLIMBTOWERWINDOW_);
					CLIMBTOWERDATAHANDLER->ToServerEnterTower();
				} 
			}
			break;
		}
	default: 
		break;
	}  
}  
  

void MainTaskWindow::Function_GetMainTaskData()
{
	 attachTaskData();
} 
 

void  MainTaskWindow::RewardHandler()
{ 
	CCLOG("Reward Handler!");
	if(m_pActiveTaskItem!=NULL)
	{
		CSGetTaskRewardRequestPacket  rewardRequestPacket(m_pActiveTaskItem->taskID);
		rewardRequestPacket.Send();
	}
} 


void  MainTaskWindow::CloseHanlder()
{
	LOGGERSYSTEM->LogInfo("On_Close_Window");	
	PushEvent(_TYPED_EVENT_CLEAR_FORCEPUSHTASKWORDWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_MAINTASKWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_CLEAR_USING_EFFECT_);
}

//////////////////////////////////////////////////////////////////////////
// Table View 相关接口
//////////////////////////////////////////////////////////////////////////

cocos2d::CCSize MainTaskWindow::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
	return m_szCELL;
}

cocos2d::extension::CCTableViewCell*   MainTaskWindow::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
	cocos2d::extension::CCTableViewCell * cell = table->dequeueCell();
	if(!cell)
	{
		cell = new cocos2d::extension::CCTableViewCell();
		cell->autorelease();
		CreateTableCell(cell);
	}
	SetTableCell(cell,idx);
	return cell;
} 

unsigned int MainTaskWindow::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
	if(m_pMainTaskData!=NULL)
	{
		return m_pMainTaskData->getTaskNum();
	} 
	return 0;
}
 
void   MainTaskWindow::CreateTableCell(cocos2d::extension::CCTableViewCell * pTableCell)
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kTASKLISTCELL,pTableCell);
}

/*
设置Cell状态
*/
void  MainTaskWindow::SetCellBtnState(CCTableViewCell * pTableCell,unsigned int cellIndex)
{
	CMenuItemSprite* cc=(CMenuItemSprite*)NFC_getMenuItem(_TASK_CELL_BTN_TAG_,pTableCell);
	cc->setIDX(cellIndex);
	cc->setTarget(this,menu_selector(MainTaskWindow::TaskCellClickHandler));
	if (m_nActiveTaskIndex==cellIndex)
	{
		setMenuSprite(cc,ResourceIDDataManager::get_instance2()->getDataByID(_SELECT_CELL_BG_ID_));
	}
	else
	{
		setMenuSprite(cc,ResourceIDDataManager::get_instance2()->getDataByID(_NORMAL_CELL_BG_ID_));
	} 
}

/*
更新Cell状态
*/
bool  MainTaskWindow::ActiveCellBtnState(cocos2d::CCObject * pSender)
{
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int idx = cc->getIDX();
	if (idx!=m_nActiveTaskIndex)
	{
		cocos2d::extension::CCTableView* table=(cocos2d::extension::CCTableView*)NFC_getNode(_TASKUI_TASK_TABLEVIEW_TAG_,m_pRoot);
		//将上一个按钮取消选中
		cocos2d::extension::CCTableViewCell * cell= table->cellAtIndex(m_nActiveTaskIndex);
		if(cell)
		{
			CMenuItemSprite* last=(CMenuItemSprite*)NFC_getMenuItem(_TASK_CELL_BTN_TAG_,cell);
			setMenuSprite(last,ResourceIDDataManager::get_instance2()->getDataByID(_NORMAL_CELL_BG_ID_));
		} 
		//选中当前按钮
		setMenuSprite(cc,ResourceIDDataManager::get_instance2()->getDataByID(_SELECT_CELL_BG_ID_));
		m_nActiveTaskIndex = idx;
		CCLOG("tableCellTouched Handler! %d",m_nActiveTaskIndex);
		return true;
	}
	return false;
}


void   MainTaskWindow::SetTableCell(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex)
{
	SetCellBtnState(pTableCell,cellIndex);
	
	std::string  taskInfo="";
	MainTaskItem * pSubTaskItem=m_pMainTaskData->at(cellIndex);
	if(pSubTaskItem!=NULL)
	{
		cocos2d::CCLabelTTF * pTaskContent=(cocos2d::CCLabelTTF *)pTableCell->getChildByTag(_TASK_CELL_CONTENT_TAG_);
		if(pTaskContent)
		{   
			if(pSubTaskItem->taskType==MainTaskItem::_TASK_ITEM_MAIN_LINE_TYPE_)
			NFC_setLabelByFontStyleID(pTaskContent,ClientConstDataManager::get_instance2()->getValueByKey(MAIN_LINE_TASK_FONTID)); 
			else
			NFC_setLabelByFontStyleID(pTaskContent,ClientConstDataManager::get_instance2()->getValueByKey(DAILY_LINE_TASK_FONTID));
			pTaskContent->setString(pSubTaskItem->taskName.c_str());
		}
	}   
}

void MainTaskWindow::ActiveCellItemWithCellIndex(int cellIndex)
{ 
	cocos2d::extension::CCTableView* table=(cocos2d::extension::CCTableView*)NFC_getNode(_TASKUI_TASK_TABLEVIEW_TAG_,m_pRoot);
	//将上一个按钮取消选中
	cocos2d::extension::CCTableViewCell * cell= table->cellAtIndex(cellIndex);
	if(cell)
	{
		CMenuItemSprite* last=(CMenuItemSprite*)NFC_getMenuItem(_TASK_CELL_BTN_TAG_,cell);
		setMenuSprite(last,ResourceIDDataManager::get_instance2()->getDataByID(_SELECT_CELL_BG_ID_));
		m_nActiveTaskIndex = cellIndex; 
		ShowTaskLayerWithCellBtn();
	} 
	else
	{
		m_nActiveTaskIndex = cellIndex; 
		ShowTaskLayerWithCellBtn();
	}
}


void   MainTaskWindow::TaskCellClickHandler(cocos2d::CCObject * pSender)
{  
	if(ActiveCellBtnState(pSender))
	{
		//post Notification
		ShowTaskLayerWithCellBtn();
	} 
} 

void  MainTaskWindow::ShowTaskLayerWithCellBtn()
{ 
	if(m_nActiveTaskIndex!=-1)
	{
	   m_pActiveTaskItem=m_pMainTaskData->at(m_nActiveTaskIndex);
	  if(m_pActiveTaskItem!=NULL)
	  {  
		 if(m_pActiveTaskItem->isFinish==MainTaskItem::_TASK_FINISHED_TYPE_)
		 {  
			 SetMenuState(false,_TASKUI_TASK_GOTO_BTN_TAG_);
			 SetNodeVisiableByTag(false,_TASKUI_BG_GOTO_BTN_EFFECT_TAG_);
			 SetMenuState(true,_TASKUI_REWARD_BTN_TAG_);
			 SetNodeVisiableByTag(true,_TASKUI_REWARD_CONTENT_TAG_);
			 NFC_setLabelString(_TASKUI_TASK_CONTENT_TAG_,m_pRoot,m_pActiveTaskItem->taskFinishedInfo,true);
		 }
		 else
		 {
			 NFC_setLabelString(_TASKUI_TASK_CONTENT_TAG_,m_pRoot,m_pActiveTaskItem->taskInfo,true);
			 SetNodeVisiableByTag(false,_TASKUI_REWARD_CONTENT_TAG_);
			 SetMenuState(false,_TASKUI_REWARD_BTN_TAG_);
			 ShowGuidWithTaskItem(m_pActiveTaskItem);
		 }  
		 ShowTaskRewardInfo(m_pActiveTaskItem);
	  } 
	}
}
 


void  MainTaskWindow::SetMenuState(bool isVisiable,int nodeTag)
{
	if(isVisiable)
	{
		bindSelectorBtnByTag(nodeTag);
		CCMenu * rewardBtn = (CCMenu *)m_pRoot->getChildByTag(nodeTag);
		rewardBtn->setVisible(true);
	
	}
	else
	{
	   CCMenu * rewardBtn = (CCMenu *)m_pRoot->getChildByTag(nodeTag);
	   rewardBtn->setVisible(false);
	}
}

void  MainTaskWindow::ShowGuidWithTaskItem(MainTaskItem * pTaskItem)
{
	if(pTaskItem!=NULL)
	{
		if(pTaskItem->guidType!=MainTaskItem::_TASK_ITEM_UNKONW_TYPE_)
		{   
			SetMenuState(true,_TASKUI_TASK_GOTO_BTN_TAG_);
			NFC_setNodeVisable(_TASKUI_BG_GOTO_BTN_EFFECT_TAG_,GetRootNode(),true);

		}
		else
		{
			SetMenuState(false,_TASKUI_TASK_GOTO_BTN_TAG_);
			NFC_setNodeVisable(_TASKUI_BG_GOTO_BTN_EFFECT_TAG_,GetRootNode(),false);
		}
	} 
}


void  MainTaskWindow::SetNodeVisiableByTag(bool isVisiable,int nodeTag)
{ 
	cocos2d::CCNode * pNode=(cocos2d::CCNode *)m_pRoot->getChildByTag(nodeTag);
	if(pNode!=NULL)
	{
		pNode->setVisible(isVisiable);
	}
}



void  MainTaskWindow::ShowTaskRewardInfo(MainTaskItem * pTaskItem)
{
	/*
	 隐藏当前奖励内容
	*/ 

	BindSelectorForTouchSprite(_TASKUI_REWARD1_OBJ_TAG_);
	BindSelectorForTouchSprite(_TASKUI_REWARD2_OBJ_TAG_);
	BindSelectorForTouchSprite(_TASKUI_REWARD3_OBJ_TAG_);

	SetNodeVisiableByTag(false,_TASKUI_REWARD1_OBJ_TAG_);
	SetNodeVisiableByTag(false,_TASKUI_REWARD1_NUM_TAG_);

	SetNodeVisiableByTag(false,_TASKUI_REWARD2_OBJ_TAG_);
	SetNodeVisiableByTag(false,_TASKUI_REWARD2_NUM_TAG_);

	SetNodeVisiableByTag(false,_TASKUI_REWARD3_OBJ_TAG_);
	SetNodeVisiableByTag(false,_TASKUI_REWARD3_NUM_TAG_);
 
	if(pTaskItem!=NULL)
	{ 
		size_t  rewardCount=pTaskItem->rewardVector.size();
		int  bgIndex=-1;
		int  iconIndex=-1;
		int  numIndex=-1;
		char  commonStr[32]={0};
		COMMON_BEGIN_VECTOR(rewardCount)	
		   GetRewardBgAndIconTagByIndex(index,bgIndex,iconIndex,numIndex);
		    MainTaskReward * pRewardItem=pTaskItem->rewardVector.at(index);
			DTAwardBoard* award=(DTAwardBoard*)m_pRoot->getChildByTag(iconIndex);
			SetNodeVisiableByTag(true,iconIndex);
			int quality=-1;
			int iconid=-1;
			bool isEnabled=false;
		    switch (pRewardItem->type)
		    {
			case  kDT_AWARD_OBJECT:
				{     
					quality=pRewardItem->quality;
					iconid=pRewardItem->iconId;
					isEnabled=true;
					sprintf(commonStr,"%d",pRewardItem->num);
					NFC_setLabelString(numIndex,m_pRoot,commonStr,true);
					break;
				}
			case   kDT_AWARD_MONEY:
				{   
					quality=_GOLD_QUALITY_RESID_;
					iconid=_GOLD_ICON_RESID_;
					sprintf(commonStr,"%d",pRewardItem->num);
					NFC_setLabelString(numIndex,m_pRoot,commonStr,true);
					break;
				}
			case  kDT_AWARD_EXP:
				{
					quality=_EXP_QUALITY_RESID_;
					iconid=_EXP_ICON_RESID_;
					sprintf(commonStr,"%d",pRewardItem->num);
					NFC_setLabelString(numIndex,m_pRoot,commonStr,true);
					break;
				}
			case  kDT_AWARD_DIAMOND:
				{
					quality=_DIAMOND_QUALITY_RESID_;
					iconid=_DIAMOND_ICON_RESID_;
					sprintf(commonStr,"%d",pRewardItem->num);
					NFC_setLabelString(numIndex,m_pRoot,commonStr,true);
					break;
				}
			case kDT_AWARD_PRESTIGE:
				{
					quality=_PREGIST_QUALITY_RESID_;
					iconid=_PREGIST_ICON_RESID_;
					sprintf(commonStr,"%d",pRewardItem->num);
					NFC_setLabelString(numIndex,m_pRoot,commonStr,true);
					break;
				}
			case kDT_AWARD_POWER:
				{
					quality=_POWER_QUALITY_RESID_;
					iconid=_POWER_ICON_RESID_;
					sprintf(commonStr,"%d",pRewardItem->num);
					NFC_setLabelString(numIndex,m_pRoot,commonStr,true);
					break;
				}
		    }
			award->ChangeObject(quality,iconid);
			award->setEnabled(isEnabled);
 		COMMON_END_ARRAY
 	}
}
 


void   MainTaskWindow::setMenuSprite(CMenuItemSprite* pMenuItem,std::string nameImageName)
{
	if(pMenuItem&&!nameImageName.empty())
	{ 
		CCSprite* cc_nor=CCSprite::create();
		cc_nor->setProperty("File",nameImageName.c_str());
		pMenuItem->setNormalImage(cc_nor);
	}
}

void  MainTaskWindow::GetRewardBgAndIconTagByIndex(size_t & index,int & bgIconTag,int & IconTag,int & numTag)
{
	switch(index)
	{
	case  0:
		{
			bgIconTag=-1;
			IconTag=_TASKUI_REWARD1_OBJ_TAG_;
			numTag=_TASKUI_REWARD1_NUM_TAG_;
			break;
		}
	case 1:
		{
			bgIconTag=-1;
			IconTag=_TASKUI_REWARD2_OBJ_TAG_;
			numTag=_TASKUI_REWARD2_NUM_TAG_;
			break;
		}
	case  2:
		{
			bgIconTag=-1;
			IconTag=_TASKUI_REWARD3_OBJ_TAG_;
			numTag=_TASKUI_REWARD3_NUM_TAG_;
			break;
		}
	default:
	 {
		 bgIconTag=-1;
		 IconTag=-1;
		 numTag=-1;
		break;
	 }
	}
}

void  MainTaskWindow::UpdateTaskDataAndUI(bool bhadNextTask)
{ 
    //删除历史任务数据
	if(m_pActiveTaskItem!=NULL)
	{  
		if(m_pActiveTaskItem->taskType!=MainTaskItem::_TASK_ITEM_MAIN_LINE_TYPE_)
		{
			//up or 0
			if(m_pMainTaskData->getTaskNum()<1)
			{
				m_nActiveTaskIndex=-1;
			}
			else if(m_pMainTaskData->getTaskNum()>=1)
			{
				m_nActiveTaskIndex-=1;
				if(m_nActiveTaskIndex<0&&m_pMainTaskData->getTaskNum()>1)
				m_nActiveTaskIndex=0;
			} 
		}
		else
		{ 
			if(!bhadNextTask)
			{
				m_nActiveTaskIndex-=1;
				if(m_nActiveTaskIndex<0&&m_pMainTaskData->getTaskNum()>1)
				m_nActiveTaskIndex=0; 
			}
		}
		m_pMainTaskData->erase(m_pActiveTaskItem);
	}
	//更新数据UI
	refreshTableView(m_pTable);
	ShowStartTaskLayer();
	NFC_showCommunicationWating(false);
}

void  MainTaskWindow::UpdateDiamondAndGold()
{
	/*
	 更新人物的金钱和钻石
	*/
	NFC_setLabelStringInt(_TASKUI_DIAMOND_NUM_TAG_,GetRootNode(),RoleInfoDataHandler::get_instance2()->m_pRIData->jewels_);
	NFC_setLabelStringInt(_TASKUI_GLOG_NUM_TAG_,GetRootNode(),RoleInfoDataHandler::get_instance2()->m_pRIData->money_);
 
}




 

