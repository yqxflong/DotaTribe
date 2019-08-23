//Name：AthleticsWindow
//Function：战斗窗口
//Author:	Johny

#include <cocos2d.h>
#include "../include/AthleticsWindow.h"
#include  "../include/EventTyper.h"
#include  "../include/VariableSystem.h"
#include  "../include/DOTATribeApp.h"
#include  "../include/EventSystem.h"
#include  "../include/AthleticsProcedure.h"
#include  "../include/NFControlsManager.h"
#include  "../include/AthleticsSceneManager.h"
#include  "../include/NumberBufferDataManager.h"
#include  "../include/C2SArenaInfoPacket.h"
#include  "../include/FriendPacket.h"
#include  "../include/TeamBattleDataHandler.h"
#include  "../include/AthleticProcedureDataHandler.h"
#include  "../include/TeamBattleProcedure.h"
#include  "../include/ServantDataHandler.h"
#include  "../include/MiningDataHandler.h"
#include  "../include/UIViewDataManger.h"
#include  "../include/BossScoreDataHandler.h"
#include  "../include/HeroSoulPacket.h"
#include  "../include/HeroSoulDataHandler.h"
 
 
using  namespace  cocos2d;
using  namespace  cobra_win;

AthleticsWindow::AthleticsWindow()
{
     m_WindowType=_TYPED_WINDOW_ATHLETIC_;
 }

AthleticsWindow::~AthleticsWindow()
{ 
}
 
bool    AthleticsWindow::Init()
{
     RegisterEvent(_TYPE_EVENT_SHOW_ATHLETICWINDOW_);
	 RegisterEvent(_TYPE_EVENT_HIDE_ATHLETICWINDOW_,true);
	 RegisterEvent(_TYPE_EVENT_UPDATE_ATHLETICWINDOW_,true);
	 return IWindow::Init();
} 

bool    AthleticsWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;  
		InitUIConfig();
		return true;
	} 
	while (false);

	return false;
}
 
void   AthleticsWindow::Tick()
{
	IWindow::Tick();
}

void   AthleticsWindow::Destroy()
{
	if(AthleticsSceneManager::get_instance2()!=NULL)
	AthleticsSceneManager::get_instance2()->OnStopScreenShake(); 
 	 
	IWindow::Destroy();
} 

 
void    AthleticsWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
   if(iEventType==_TYPE_EVENT_SHOW_ATHLETICWINDOW_)
   {
        Show(true);
   }
   else if(iEventType==_TYPE_EVENT_HIDE_ATHLETICWINDOW_)
   { 
        Destroy();
   }
   else if(iEventType==_TYPE_EVENT_UPDATE_ATHLETICWINDOW_)
   {
        
   }
}
 

//////////////////////////////////////////////////////////////////////////
void  AthleticsWindow::InitUIConfig()
{
	UIViewDataManager::get_instance2()->AutoCreateNodeByTable(UIViewDataManager::kAthleticsWindow,m_pRootNode);
	NFC_setSpriteFlipX(ATHELTICS_UI_RIGHT_MASK,m_pRootNode,true);
	NFC_setSpriteFlipX(ATHLETICS_UI_RIGHT_ICON,m_pRootNode,true);
	NFC_setSpriteFlipX(ATHELTICS_UI_RIGHT_INFO,m_pRootNode,true);
	NFC_setSpriteFlipX(ATHLETICS_UI_RIGHT_HP_BG,m_pRootNode,true);
	NFC_setSpriteFlipX(ATHLETICS_UI_RIGHT_MP_BG,m_pRootNode,true);
 
	BindBtnSelector();
}

void AthleticsWindow::BindBtnSelector()
{
	NFC_bindSelectorForBtn(ATHLETICS_UI_REPLAY_BTN,m_pRootNode,this,menu_selector(AthleticsWindow::CommonBtnSelector));
	NFC_bindSelectorForBtn(ATHLETICS_UI_SPEED_BTN,m_pRootNode,this,menu_selector(AthleticsWindow::CommonBtnSelector));
	NFC_bindSelectorForBtn(ATHLETICS_UI_EXIT_BTN,m_pRootNode,this,menu_selector(AthleticsWindow::CommonBtnSelector));
}

void  AthleticsWindow::CommonBtnSelector(cocos2d::CCObject * pSender)
{
	CMenuItemSprite *  pMenuItemSprite=(CMenuItemSprite *)pSender;
    switch(pMenuItemSprite->getIDX())
	{
	case ATHLETICS_UI_REPLAY_BTN:
		{   
			CCLOG("ATHLETICS_UI_REPLAY_BTN: Handler");
			OnReplayHandler();
			break;
		}
	case ATHLETICS_UI_SPEED_BTN:
		{  
			CCLOG("ATHLETICS_UI_REPLAY_BTN: Handler");
			OnChangeSpeedHandler();
			break;
		}
	case ATHLETICS_UI_EXIT_BTN:
		{
			CCLOG("ATHLETICS_UI_EXIT_BTN : Handler");
			OnExitHandler();
			break;
		}
	default:
		break;
	}
}  
//////////////////////////////////////////////////////////////////////////
//重播处理
void    AthleticsWindow::OnReplayHandler()
{
   ATHLETICSSCENEMANAGER->OnRePlayAthleticsGame();
}

//变速处理
void    AthleticsWindow::OnChangeSpeedHandler()
{
   ATHLETICSSCENEMANAGER->OnChangeAthleticsSpeed();
}
 
//退出处理  
void    AthleticsWindow::OnExitHandler()
{    
	//处理是否为VIP跳过
	if(ATHLETICSSCENEMANAGER->IsTriggerVIPSkipHandler())
	return ;
	 
	bool athleticsWinType = ATHLETICSSCENEMANAGER->GetAthleticsResult();
	 
	int type = ATHLETICPROCEDUREDATA->athleticsBattleType;

	if(type == _ATHLETICS_CUSTOMS_BATTLE_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pAthleticsProcudure->OnChangeProcedureToMission();
	}
	else if(type == _ATHLETICS_ARENA_BATTLE_TYPE_)
	{
		//发送消息请求
		C2SArenaInfoPacket  requestArenaInfo(0);
		requestArenaInfo.Send();	
		return ;
	}
	else if(type == _ATHLETICS_CLIMPTOWER_BATTLE_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pAthleticsProcudure->OnChangeProcedureToHome(_TYPED_EVENT_SHOW_CLIMBTOWERWINDOW_);

		CLIMBTOWERDATAHANDLER->ToClientChallengeTowerResult();//同时给定事件挑战界面结算退出

	}
	else if(type == _ATHLETICS_TEAM_BATTLE_TYPE_)
	{
		if(athleticsWinType)
		{//赢了
			if(TEAMBATTLEDATAHANDLER->m_pTeamStageData->stageId >= TEAMBATTLEDATAHANDLER->GetSelectGateInfo()->maxStage)
			{//表明通关了
				TEAMBATTLEDATAHANDLER->m_bHaveGateReward = true;//有通关奖励
				DOTATribeApp::get_instance2()->m_pTeamBattleProcedure->ChangeNowState(TeamBattleProcedure::_TEAMBATTLE_STATE_SELECTGATE_);
			}
			else
			{
				DOTATribeApp::get_instance2()->m_pTeamBattleProcedure->ChangeNowState(TeamBattleProcedure::_TEAMBATTLE_STATE_WAITTEAMER_);
			}
		}
		else
		{//失败了
			DOTATribeApp::get_instance2()->m_pTeamBattleProcedure->ChangeNowState(TeamBattleProcedure::_TEAMBATTLE_STATE_WAITTEAMER_);
		}

		DOTATribeApp::get_instance2()->m_pAthleticsProcudure->OnChangeProcedureToTeamBattle();
	}
	else if(type == _ATHLETICS_SERVANT_BATTLE_TYPE_)
	{
		LOGGERSYSTEM->LogInfo("AthleticsResultWindow::OnExitClick----ClimbTower\n");
		DOTATribeApp::get_instance2()->m_pAthleticsProcudure->OnChangeProcedureToHome(_TYPED_EVENT_SHOW_PUCONGWINDOW_); 
		//PServantMapInfo mapinfo = (PServantMapInfo)ATHLETICPROCEDUREDATA->pAthleticsMapInfo->mapInfoData;
		//SERVANTDATAHANDLER->OnAthleticEnd(mapinfo->stageID, athleticsWinType);	//已移至战斗结果界面的InitData中
	}
	else if(type == _ATHLETICS_FRIEND_BATTLE_TYPE_)
	{
		C2SFriendPacket crpacket;
		crpacket.Send();
		NFC_showCommunicationWating(true);
	}  
	else if(type == _ATHLETICS_KUANGDONG_BATTLE_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pAthleticsProcudure->OnChangeProcedureToHome(_TYPED_EVENT_SHOW_MINEAREAWINDOW_);

		PMiningMapInfo mapInfo = (PMiningMapInfo)ATHLETICPROCEDUREDATA->pAthleticsMapInfo->mapInfoData;
		MININGDATAHANDLER->OnAthleticEnd(mapInfo->stageID, athleticsWinType);
	}
	else if(type == _ATHLETICS_KUANGDONG_HUNTLIEREN_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pAthleticsProcudure->OnChangeProcedureToHome(_TYPED_EVENT_SHOW_MINEAREAWINDOW_);
		MININGDATAHANDLER->OnHuntLieRenQiangDuoAthleticEnd(athleticsWinType);
	}
	else if(type == _ATHLETICS_BOSSSCORE_BATTLE_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pAthleticsProcudure->OnChangeProcedureToHome(_TYPED_EVENT_SHOW_BOSSSCOREWINDOW_);

		PBossScoreMapInfo mapInfo = (PBossScoreMapInfo)ATHLETICPROCEDUREDATA->pAthleticsMapInfo->mapInfoData;
		BOSSSCOREDATAHANDLER->OnAthleticEnd(mapInfo->stageID, athleticsWinType);
	}
	else if(type == _ATHLETICS_CHALLENEGE_HEROSOUL_TYPE_)
	{ 
		C2SHeroSoulPacket  heroSoulPacket(HeroSoulDataHandler::get_instance2()->getRequestHeroID());
		heroSoulPacket.Send();
	}
}

//////////////////////////////////////////////////////////////////////////

CCNode  *  AthleticsWindow::GetAthleticsUINode(int UIIndex)
{ 
	if(IWindow::IsLoad())
	{
		return m_pRootNode->getChildByTag(UIIndex);
	}
	return NULL;
}

MaskNode *  AthleticsWindow::GetAthleticsUIMarkNode(int UIIndex)
{
	if(IWindow::IsLoad())
	{
		return (MaskNode *)m_pRootNode->getChildByTag(UIIndex);
	}
	return NULL;
}
 
cocos2d::CCNode  *  AthleticsWindow::GetAthleticsRootNode()
{
	if(IWindow::IsLoad())
	{
		return  m_pRootNode;
 	}
	return NULL;
}
