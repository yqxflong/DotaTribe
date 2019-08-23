// Name :		AthleticResultWindow.h
// Function:	战斗阶段界面
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include "../include/AthleticResultWindow.h"
#include "../include/EventTyper.h"
#include "../include/VariableSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/BaseObjectManager.h"
#include "../include/AthleticsProcedure.h"
#include "../include/HeroicRole.h"
#include "../include/SysLangDataManager.h"
#include "../include/AthleticProcedureDataType.h"
#include "../include/HomeProcedure.h"
#include "../include/ResourceIDDataManager.h"
#include "../include/CPublicVarReader.h"
#include "../include/AthleticProcedureDataHandler.h"
#include "../include/CSEnterTranscriptRequestPacket.h"
#include "../include/ClientConstDataManager.h"
#include "../include/SelectMissionProcedure.h"
#include "../include/C2SArenaInfoPacket.h"
#include "../include/FriendPacket.h"
#include "../include/MissionDataHandler.h"
#include "../include/LogoProcedure.h"
#include "../include/IProcedure.h"
#include "../include/TimeSystem.h"
#include "../include/SoundSystem.h"
#include "../include/VariableSystem.h"
#include "cocos-ext.h"
#include <include/common/Random.h>
#include <cocos2d.h>
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/LevelUpDataHandler.h"
#include "../include/LoadingProcedure.h"
#include "../include/ClimbTowerPacket.h"
#include "../include/TeamBattleDataHandler.h"
#include "../include/TeamBattleProcedure.h"
#include "../include/LoggerSystem.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/ServantDataHandler.h"
#include "../include/UIWindowDataManager.h"
#include "../include/NFControlsManager.h"
#include "../include/NFAnimationController.h"
#include "../include/MiningDataHandler.h"
#include "../include/MineAreaWindow.h"
#include "../include/PopWindowManager.h"
#include "../include/HeroSoulPacket.h"
#include "../include/HeroSoulDataHandler.h"
#include "../include/BossScoreDataHandler.h"
#include "../include/PESWindow.h"



using namespace cocos2d;
#define  _ARENE_PRESTIGE_TXT_ID_   621  //声望 文案ID

#define FontName	"ArialRoundedMTBold" //默认字体

AthleticsResultWindow::AthleticsResultWindow()
	:obj_quality_1(-1)
	,obj_quality_2(-1)
	,obj_quality_3(-1)
	,obj_icon_1(-1)
	,obj_icon_2(-1)
	,obj_icon_3(-1)
{ 
    m_WindowType=_TYPED_WINDOW_ATHLETICSRESULT_;

	athleticsWinType=false;

	rewardOneImage ="";
	rewardOneValue ="";
	rewardTwoImage ="";
	rewardTwoValue ="";
	rewardThreeValue = "";

	rewardGoodsTypeOne =0;
	rewardGoodsTypeTwo =0;
	rewardGoodsTypeThree =0;

	rewardGoodsOneNum=1;
	rewardGoodsTwoNum=1;
	rewardGoodsThreeNum=1;
	rewardNum =0; 

	m_TitleSkeleton=NULL;
	m_StarSkeleton=NULL;
	 
	m_bIsForceClearUnUseTex=false;
	m_bIsForceClearAnimation=false;

}
AthleticsResultWindow::~AthleticsResultWindow()
{
	
}
bool AthleticsResultWindow::Init()
{ 
   RegisterEvent(_TYPE_EVENT_SHOW_ATHLETICSRESULTWINDOW_);
   RegisterEvent(_TYPE_EVENT_HIDE_ATHLETICSRESULTWINDOW_,true);

 
   //设置该弹窗的优先级
   IPopWindow::priority_=GetPriorityByCurWindowDef(POP_PRIORITY_BATTLE_RESULT);
   return IWindow::Init();
} 
bool AthleticsResultWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break; 
		InitLayer(); 
	} 

	while (false);
	return false;
}
void AthleticsResultWindow::Tick()
{
	IWindow::Tick();
} 
void AthleticsResultWindow::Destroy()
{ 
	//
	PopWindowDidHide();
	//
	rewardOneImage ="";
	rewardOneValue ="";
	rewardTwoImage ="";
	rewardTwoValue ="";
	rewardThreeValue = "";
	obj_quality_1=-1;
	obj_quality_2=-1;
	obj_quality_3=-1;
	obj_icon_1=-1;
	obj_icon_2=-1;
	obj_icon_3=-1;
	rewardNum = 0;

	IWindow::Destroy();
}

//需要子类继承并重写
void AthleticsResultWindow::ShowPopWindow(){
	IPopWindow::ShowPopWindow();
	ShowWindow();
}
void AthleticsResultWindow::PopWindowDidHide(){
	IPopWindow::PopWindowDidHide();
}

void AthleticsResultWindow::InitLayer()
{
	m_pRoot= CCNode::create();
	m_pWin= CCNode::create();
	m_pLose= CCNode::create();
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kATHLETICRESULTWINDOW,m_pRoot);
	for (int i=_Result_WinBG_;i<_Result_LoseBG_;i++)
	{
		CCNode* pNode = m_pRoot->getChildByTag(i);
		pNode->removeFromParent();
		pNode->setParent(NULL);
		m_pWin->addChild(pNode,1,i);
	}
	CCMenu* pMenu = (CCMenu*)m_pWin->getChildByTag(_Result_WinRePlayButton_);
	CMenuItemSprite* pItem = (CMenuItemSprite*)pMenu->getChildByTag(0);
	pItem->setTarget(this,menu_selector(AthleticsResultWindow::OnRePlayClick));

	pMenu = (CCMenu*)m_pWin->getChildByTag(_Result_WinSureButton_);
	pItem = (CMenuItemSprite*)pMenu->getChildByTag(0);
	pItem->setTarget(this,menu_selector(AthleticsResultWindow::OnExitClick));

	m_pWin->setVisible(false);
	m_pRoot->addChild(m_pWin);

	for (int i=_Result_LoseBG_;i<_Result_End_;i++)
	{
		CCNode* pNode = m_pRoot->getChildByTag(i);
		pNode->removeFromParent();
		pNode->setParent(NULL);
		m_pLose->addChild(pNode,1,i);
	}
/*
	pMenu = (CCMenu*)m_pLose->getChildByTag(_Result_LoseSkillButton_);
	pItem = (CMenuItemSprite*)pMenu->getChildByTag(0);
	pItem->setTarget(this,menu_selector(AthleticsResultWindow::OnBackToSkillClick));*/

	pMenu = (CCMenu*)m_pLose->getChildByTag(_Result_LoseHeroButton_);
	pItem = (CMenuItemSprite*)pMenu->getChildByTag(0);
	pItem->setTarget(this,menu_selector(AthleticsResultWindow::OnBackToChangeHeroClick));

	pMenu = (CCMenu*)m_pLose->getChildByTag(_Result_LoseEquipButton_);
	pItem = (CMenuItemSprite*)pMenu->getChildByTag(0);
	pItem->setTarget(this,menu_selector(AthleticsResultWindow::OnBackToEmployClick));

	pMenu = (CCMenu*)m_pLose->getChildByTag(_Result_LoseRePlayButton_);
	pItem = (CMenuItemSprite*)pMenu->getChildByTag(0);
	pItem->setTarget(this,menu_selector(AthleticsResultWindow::OnRePlayClick));

	pMenu = (CCMenu*)m_pLose->getChildByTag(_Result_LoseTryAgainButton_);
	pItem = (CMenuItemSprite*)pMenu->getChildByTag(0);
	pItem->setTarget(this,menu_selector(AthleticsResultWindow::OnFightAgainClick));

	pMenu = (CCMenu*)m_pLose->getChildByTag(_Result_LoseSureButton_);
	pItem = (CMenuItemSprite*)pMenu->getChildByTag(0);
	pItem->setTarget(this,menu_selector(AthleticsResultWindow::OnExitClick));
	m_pLose->setVisible(false);
	m_pRoot->addChild(m_pLose);
	m_pRootNode->addChild(m_pRoot);

	MaskNode* node=(MaskNode*)m_pWin->getChildByTag(_Result_WinTitle_);
	const UIViewData & tempData=node->GetViewData();

	CCNode* pNodeTitle = (CCNode*)m_pWin->getChildByTag(_Result_WinTitle_);
	m_TitleSkeleton = CCSkeletonAnimation::createWithFile(tempData.filepath_,tempData.filepath2_);
	m_TitleSkeleton->registerCallBackDelegate(this);
	m_TitleSkeleton->setAnimation("ed1",false);
	pNodeTitle->addChild(m_TitleSkeleton);

	node=(MaskNode*)m_pWin->getChildByTag(_Result_WinStar_);
	const UIViewData & tempData1=node->GetViewData();
	CCNode* pNodeStar = (CCNode*)m_pWin->getChildByTag(_Result_WinStar_);
	m_StarSkeleton = CCSkeletonAnimation::createWithFile(tempData1.filepath_,tempData1.filepath2_);
	m_StarSkeleton->setVisible(false);
	pNodeStar->addChild(m_StarSkeleton);
} 
void AthleticsResultWindow::SetScoreColor(CCMultiLineLabelTTF* pLabel,int num)
{
	if (num<60)
		pLabel->setColor(ccRED);
	else if (num<85)
		pLabel->setColor(ccYELLOW);
	else 
		pLabel->setColor(ccGREEN);

}
void AthleticsResultWindow::OnInitUISetting()
{ 
	InitData();
	 
	if(athleticsWinType)
	{
		if(m_pWin!=NULL)
		{
			//第一行奖励值
			if(rewardOneValue != "")
			{
				CCLabelTTF* rewardvalueone =(CCLabelTTF*)m_pWin->getChildByTag(_Result_WinExpValue_);
				if (rewardvalueone!=NULL)
				rewardvalueone->setString(rewardOneValue.c_str());
				rewardvalueone->setVisible(true);
				NFC_showNode(_Result_WinExp_, m_pWin, true);
			}
			else
			{
				NFC_showNode(_Result_WinExp_, m_pWin, false);
				NFC_showNode(_Result_WinExpValue_, m_pWin, false);
			}

			//第二行奖励值
			if(rewardTwoValue != "")
			{
				CCLabelTTF* rewardvaluetwo =(CCLabelTTF*)m_pWin->getChildByTag(_Result_WinMoneyValue_);
				if (rewardvaluetwo!=NULL)
					rewardvaluetwo->setString(rewardTwoValue.c_str());
				rewardvaluetwo->setVisible(true);
				NFC_showNode(_Result_WinMoney_, m_pWin, true);
			}
			else
			{
				NFC_showNode(_Result_WinMoney_, m_pWin, false);
				NFC_showNode(_Result_WinMoneyValue_, m_pWin, false);
			}

			//第三行奖励值
			if(rewardThreeValue != "")
			{
				CCLabelTTF* rewardvaluethree =(CCLabelTTF*)m_pWin->getChildByTag(_Result_WinShengWangValue_);
				if (rewardvaluethree!=NULL)
				rewardvaluethree->setString(rewardThreeValue.c_str());
				rewardvaluethree->setVisible(true);
				NFC_showNode(_Result_WinShengWang_, m_pWin, false);
			}
			else
			{
				NFC_showNode(_Result_WinShengWang_, m_pWin, false);
				NFC_showNode(_Result_WinShengWangValue_, m_pWin, false);
			}


			//第一个物品奖励
			DTAwardBoard* goods1 =(DTAwardBoard*)m_pWin->getChildByTag(_Result_WinItem1OBJ_);
			CCLabelTTF* num1 =(CCLabelTTF*)m_pWin->getChildByTag(_Result_WinItem1Num_);
			num1->setAnchorPoint(ccp(1.0,0.0));
			if (rewardNum > _ENUM_ZERO_)
			{
				if(goods1 != NULL)
				{
					goods1->ChangeObject(obj_quality_1,obj_icon_1);
					if (rewardGoodsTypeOne == kBAGSKIN)
						goods1->setContentScale(CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f);
					else
						goods1->setContentScale(1.0f);
					char _num[128]="";
					sprintf(_num,"%d",rewardGoodsOneNum);
					num1->setString(_num);
				}
			}
			else
			{
				goods1->setVisible(false);
				num1->setVisible(false);
			}	

			//第二个物品奖励 
			DTAwardBoard* goods2 =(DTAwardBoard*)m_pWin->getChildByTag(_Result_WinItem2OBJ_);
			CCLabelTTF* num2 =(CCLabelTTF*)m_pWin->getChildByTag(_Result_WinItem2Num_);
			num2->setAnchorPoint(ccp(1.0,0.0));
			if (rewardNum > _ENUM_ONE_)
			{
				if(goods2 != NULL)
				{
					goods2->ChangeObject(obj_quality_2,obj_icon_2);
					if (rewardGoodsTypeTwo == kBAGSKIN)
						goods2->setContentScale(CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f);
					else
						goods2->setContentScale(1.0f);
					char _num[128]="";
					sprintf(_num,"%d",rewardGoodsTwoNum);
					num2->setString(_num);
				}
			}
			else
			{
				goods2->setVisible(false);
				num2->setVisible(false);
			}

			//第三个物品奖励
			DTAwardBoard* goods3 =(DTAwardBoard*)m_pWin->getChildByTag(_Result_WinItem3OBJ_);
			CCLabelTTF* num3 =(CCLabelTTF*)m_pWin->getChildByTag(_Result_WinItem3Num_);
			num3->setAnchorPoint(ccp(1.0,0.0));
			if (rewardNum > _ENUM_TWO_)
			{
				if(goods3 != NULL)
				{
					goods3->ChangeObject(obj_quality_3,obj_icon_3);
					if (rewardGoodsTypeThree == kBAGSKIN)
						goods3->setContentScale(CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f);
					else
						goods3->setContentScale(1.0f);
					char _num[128]="";
					sprintf(_num,"%d",rewardGoodsThreeNum);
					num3->setString(_num);
				}
			}
			else
			{
				goods3->setVisible(false);
				num3->setVisible(false);
			}
	
		}
	  
	}
	else
	{
		//失败
		if(m_pLose)
		{
			int type = ATHLETICPROCEDUREDATA->athleticsBattleType;
			if(type == _ATHLETICS_BOSSSCORE_BATTLE_TYPE_)
			{
				//boss积分战的失败界面需要显示当前积分信息
				NFC_setLabelString(_Result_LoseEquipAppraiseValue_, m_pLose, rewardThreeValue, true);
			}
			else
			{
				NFC_setLabelStringInt(_Result_LoseEquipAppraiseValue_, m_pLose, ROLEINFODATAHANDLER->m_pRIData->equipCapaScore_, true);
				FSData * fsdata = NULL;
				if(ROLEINFODATAHANDLER->m_pRIData->equipCapaScore_ < 80)
				{
					fsdata = FONTSTYLEDATAMANAGER->getDataByID(105);
				}
				else
				{
					fsdata = FONTSTYLEDATAMANAGER->getDataByID(103);
				}
				if(fsdata)
				{
					NFC_setLabelColor(_Result_LoseEquipAppraiseValue_, m_pLose, ccc3(fsdata->colorR_, fsdata->colorG_, fsdata->colorB_));
				}
				NFC_setLabelString(_Result_LostPrestigeValue_,m_pLose,rewardThreeValue,false);  
				NFC_setNodeVisable(_Result_LostPrestigeImage_,m_pLose,false);
				if(type == _ATHLETICS_ARENA_BATTLE_TYPE_)
				{ 
					if(rewardThreeValue != "")
					{
						
						NFC_setNodeVisable(_Result_LoseText_,m_pLose,false);
						NFC_setLabelString(_Result_LostPrestigeValue_,m_pLose,rewardThreeValue,true);  
						NFC_setNodeVisable(_Result_LostPrestigeImage_,m_pLose,true);
					} 
				}
			} 
		} 
	} 
	//设置结算面板按钮状态
	SetBtnEnableStatus();

}
void AthleticsResultWindow::SetBtnEnableStatus()
{
	int type = ATHLETICPROCEDUREDATA->athleticsBattleType;
	if(type == _ATHLETICS_TEAM_BATTLE_TYPE_ || type == _ATHLETICS_FRIEND_BATTLE_TYPE_ 
		|| type == _ATHLETICS_BOSSSCORE_BATTLE_TYPE_ || type == _ATHLETICS_CHALLENEGE_HEROSOUL_TYPE_
		|| type == _ATHLETICS_KUANGDONG_HUNTLIEREN_TYPE_)
	{
		NFC_setNodeVisable(_Result_LoseTryAgainButtonLabel_,m_pLose,false);
		NFC_setNodeVisable(_Result_LoseTryAgainButton_,m_pLose,false);  
	}
	else if(type == _ATHLETICS_SERVANT_BATTLE_TYPE_ || type == _ATHLETICS_KUANGDONG_BATTLE_TYPE_)
	{ 
		NFC_setNodeVisable(_Result_LoseTryAgainButtonLabel_,m_pLose,false);
		NFC_setNodeVisable(_Result_LoseTryAgainButton_,m_pLose,false); 

		NFC_setNodeVisable(_Result_LoseRePlayButtonLabel_,m_pLose,true); 
		NFC_setNodeVisable(_Result_LoseRePlayButton_,m_pLose,true); 
		NFC_setNodeVisable(_Result_LoseSureButtonLabel_,m_pLose,true); 
		NFC_setNodeVisable(_Result_LoseSureButton_,m_pLose,true);   
		 
		if(ATHLETICSSCENEMANAGER->GetAthelticsWatchType() == AthleticsSceneManager::_ATHLECTICS_OTHER_WATCH_TYPE_)
		{ 
			//NFC_setNodeVisable(_Result_LoseSkillButton_,m_pLose,false);
			NFC_setNodeVisable(_Result_LoseHeroButton_,m_pLose,false);
			NFC_setNodeVisable(_Result_LoseEquipButton_,m_pLose,false);  
		}
	} 
}
CCNode* AthleticsResultWindow::getShowLayer()
{
	if (athleticsWinType)
	{
		m_pWin->setVisible(true);
		return m_pWin;
	}
	else
	{
		m_pLose->setVisible(true);
		return m_pLose;
	}
	
} 

	/*
		展示自己的窗口
	*/
void AthleticsResultWindow::ShowWindow(){
	if(IsVisible())
		return;
	CCLOG("AthleticsResultWindow ShowWindow Handler! From PopManager!");
	OnInitUISetting();
	Show(true);
	_fallDown(getShowLayer()); 
	if (athleticsWinType)
	{
		//胜利
		UIWindowItemData* pItem = UIWindowDataManager::get_instance2()->GetWindowByType(_TYPED_WINDOW_ATHLETICSRESULT_);
		if (pItem==NULL || pItem->mSoundOpen == -1)
			return ;

		char _soundID[64]="";
		sprintf(_soundID,"%d",pItem->mSoundOpen);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOUND_PLAY_,_soundID);

	}
	else
	{
		//失败
		UIWindowItemData* pItem = UIWindowDataManager::get_instance2()->GetWindowByType(_TYPED_WINDOW_ATHLETICSRESULT_);
		if (pItem==NULL || pItem->mSoundClose == -1)
			return ;

		char _soundID[64]="";
		sprintf(_soundID,"%d",pItem->mSoundClose);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOUND_PLAY_,_soundID);
	}
}

void AthleticsResultWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
   if(iEventType==_TYPE_EVENT_SHOW_ATHLETICSRESULTWINDOW_)
   { 
	  CCLOG("AthleticsResultWindow Show Handler ! Add To PopManager !");
	  PopWindowManager::get_instance2()->AddPopWindow(this);
   }
   else if(iEventType==_TYPE_EVENT_HIDE_ATHLETICSRESULTWINDOW_)
   {
        Destroy();
   }
}
void AthleticsResultWindow::OnRePlayClick(CCObject * pSender)
{
	//m_pRootNode->removeAllChildrenWithCleanup(true);
	CCLOG("OnRePlayClick: ");
	ATHLETICSSCENEMANAGER->OnRePlayAthleticsGame();

}
void AthleticsResultWindow::OnFightAgainClick(CCObject * pSender)
{    
	/*
     将当前系统时间插入VariableSystem变量系统中   
	*/ 
	BTN_INTERVAL("ReTryFightBtn",_COMMON_BTN_CLICK_INTERVAL_)
  
	CCLOG("OnFightAgainClick: ");
	NFC_showCommunicationWating(true);
	int type = ATHLETICPROCEDUREDATA->athleticsBattleType;
	char procedueType[128] ={0};
	if(AthleticProcedureDataHandler::get_instance2()!=NULL)
	{
		AthleticProcedureDataHandler::get_instance2()->isReTryBattle=true;
	}
	//重试分支
	if(type == _ATHLETICS_CUSTOMS_BATTLE_TYPE_)
	{ 
		CSEnterTranscriptRequestPacket  transcriptRequest(MissionDataHandler::get_instance2()->getCurMissionID(),MissionDataHandler::get_instance2()->getCurStatesID());
		transcriptRequest.Send();
	}
	else if(type == _ATHLETICS_CLIMPTOWER_BATTLE_TYPE_)
	{
		CSChallengeTowerPacket packet(ROLEINFODATAHANDLER->updateRoleAthleticsSerialID());
		packet.Send();
	} 
}
void AthleticsResultWindow::OnExitClick(CCObject * pSender)
{
	//to do For Close All Sound 
	SOUNDSYSTEM->StopAllEffect();
	  
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
		LOGGERSYSTEM->LogInfo("AthleticsResultWindow::OnExitClick----ClimbTower\n");
		DOTATribeApp::get_instance2()->m_pAthleticsProcudure->OnChangeProcedureToHome(_TYPED_EVENT_SHOW_CLIMBTOWERWINDOW_);

		CLIMBTOWERDATAHANDLER->ToClientChallengeTowerResult();//同时给定事件挑战界面结算退出

	}
	else if(type == _ATHLETICS_TEAM_BATTLE_TYPE_)
	{
		TEAMBATTLEDATAHANDLER->DestroyMyTeam();

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
		LOGGERSYSTEM->LogInfo("AthleticsResultWindow::OnExitClick----Servant\n");
		DOTATribeApp::get_instance2()->m_pAthleticsProcudure->OnChangeProcedureToHome(_TYPED_EVENT_SHOW_PUCONGWINDOW_);
		
		PServantMapInfo mapinfo = (PServantMapInfo)ATHLETICPROCEDUREDATA->pAthleticsMapInfo->mapInfoData;
		SERVANTDATAHANDLER->OnAthleticEnd(mapinfo->stageID, athleticsWinType);
	}
	else if(type == _ATHLETICS_FRIEND_BATTLE_TYPE_)
	{
		C2SFriendPacket crpacket;
		crpacket.Send();
		NFC_showCommunicationWating(true);
	}
	else if(type == _ATHLETICS_KUANGDONG_BATTLE_TYPE_)
	{
		LOGGERSYSTEM->LogInfo("AthleticsResultWindow::OnExitClick----KuangDong\n");
		DOTATribeApp::get_instance2()->m_pAthleticsProcudure->OnChangeProcedureToHome(_TYPED_EVENT_SHOW_MINEAREAWINDOW_);

		PMiningMapInfo mapInfo = (PMiningMapInfo)ATHLETICPROCEDUREDATA->pAthleticsMapInfo->mapInfoData;

		MININGDATAHANDLER->OnAthleticEnd(mapInfo->stageID, athleticsWinType);
	}
	else if(type == _ATHLETICS_KUANGDONG_HUNTLIEREN_TYPE_)
	{
		LOGGERSYSTEM->LogInfo("AthleticsResultWindow::OnExitClick----KuangDong\n");
		DOTATribeApp::get_instance2()->m_pAthleticsProcudure->OnChangeProcedureToHome(_TYPED_EVENT_SHOW_MINEAREAWINDOW_);

		//MININGDATAHANDLER->OnHuntLieRenQiangDuoAthleticEnd(athleticsWinType);//已移至当前页面的InitData中
	}
	else if(type == _ATHLETICS_CHALLENEGE_HEROSOUL_TYPE_)
	{ 
		C2SHeroSoulPacket  heroSoulPacket(HeroSoulDataHandler::get_instance2()->getRequestHeroID());
		heroSoulPacket.Send();
	}
	else if(type == _ATHLETICS_BOSSSCORE_BATTLE_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pAthleticsProcudure->OnChangeProcedureToHome(_TYPED_EVENT_SHOW_BOSSSCOREWINDOW_);

		PBossScoreMapInfo mapInfo = (PBossScoreMapInfo)ATHLETICPROCEDUREDATA->pAthleticsMapInfo->mapInfoData;
		BOSSSCOREDATAHANDLER->OnAthleticEnd(mapInfo->stageID, athleticsWinType);
	}
}
void AthleticsResultWindow::OnBackToChangeHeroClick(CCObject * pSender)
{
	CCLOG("OnBackToEquip: ");
	int type = ATHLETICPROCEDUREDATA->athleticsBattleType;

	if(type == _ATHLETICS_CUSTOMS_BATTLE_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pSelectMissionProcedure->m_skipWindow = _TYPED_EVENT_SHOW_TEAMINFOWINDOW_;
		//DOTATribeApp::get_instance2()->m_pSelectMissionProcedure->m_skipTabNum = PESWindow::kTAB_1;
		DOTATribeApp::get_instance2()->m_pAthleticsProcudure->OnChangeProcedureToMission();
	}
	else if(type == _ATHLETICS_ARENA_BATTLE_TYPE_)
	{
		//发送消息请求
		DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_TEAMINFOWINDOW_);
		DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
/*
		char param[128];
		sprintf(param,"%d",PESWindow::kTAB_1);
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_PESWINDOW_,param);*/

		return ;
	}
	else if(type == _ATHLETICS_CLIMPTOWER_BATTLE_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_TEAMINFOWINDOW_);
		DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
/*
		char param[128];
		sprintf(param,"%d",PESWindow::kTAB_1);
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_PESWINDOW_,param);*/
	}
	else if(type == _ATHLETICS_TEAM_BATTLE_TYPE_)
	{
		TEAMBATTLEDATAHANDLER->DestroyMyTeam();
		DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_TEAMINFOWINDOW_);
		DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
/*
		char param[128];
		sprintf(param,"%d",PESWindow::kTAB_1);
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_PESWINDOW_,param);*/
	}
	else if(type == _ATHLETICS_SERVANT_BATTLE_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_TEAMINFOWINDOW_);
		DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
/*
		char param[128];
		sprintf(param,"%d",PESWindow::kTAB_1);
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_PESWINDOW_,param);*/
	}
	else if(type == _ATHLETICS_FRIEND_BATTLE_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_TEAMINFOWINDOW_);
		DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
/*
		char param[128];
		sprintf(param,"%d",PESWindow::kTAB_1);
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_PESWINDOW_,param);*/

	}
	else if(type == _ATHLETICS_KUANGDONG_BATTLE_TYPE_ || type == _ATHLETICS_KUANGDONG_HUNTLIEREN_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_TEAMINFOWINDOW_);
		DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
/*
		char param[128];
		sprintf(param,"%d",PESWindow::kTAB_1);
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_PESWINDOW_,param);*/
	}
	else if(type == _ATHLETICS_BOSSSCORE_BATTLE_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_TEAMINFOWINDOW_);
		DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
/*
		char param[128];
		sprintf(param,"%d",PESWindow::kTAB_1);
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_PESWINDOW_,param);*/
	}	
	else if(type == _ATHLETICS_CHALLENEGE_HEROSOUL_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_TEAMINFOWINDOW_);
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_LOADINGWINDOW_,_to_event_param_(IProcedure::_TYPED_HOME_PROCEDURE_));
	}
}
void AthleticsResultWindow::OnBackToSkillClick(CCObject * pSender)
{
	/*CCLOG("OnBackToSkill: ");
	int type = ATHLETICPROCEDUREDATA->athleticsBattleType;

	if(type == _ATHLETICS_CUSTOMS_BATTLE_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pSelectMissionProcedure->m_skipWindow = _TYPED_EVENT_SHOW_SELECTSKILLWINDOW_;
		DOTATribeApp::get_instance2()->m_pAthleticsProcudure->OnChangeProcedureToMission();
	}
	else if(type == _ATHLETICS_ARENA_BATTLE_TYPE_)
	{
		//发送消息请求
		DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_SELECTSKILLWINDOW_);
		DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
		char type[128] = "";
		sprintf(type,"%d",_TYPEF_EVENT_SEND_ARENAREQUEST_);
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_SELECTSKILLWINDOW_,type); 

		return ;
	}
	else if(type == _ATHLETICS_CLIMPTOWER_BATTLE_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_SELECTSKILLWINDOW_);
		DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
		char type[128] = "";
		sprintf(type,"%d",_TYPED_EVENT_SHOW_CLIMBTOWERWINDOW_);
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_SELECTSKILLWINDOW_,type); 
	}
	else if(type == _ATHLETICS_TEAM_BATTLE_TYPE_)
	{
		TEAMBATTLEDATAHANDLER->DestroyMyTeam();
		DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_SELECTSKILLWINDOW_);
		DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
		char type[128] = "";
		sprintf(type,"%d",_TYPED_EVENT_CHANGETO_TEAMBATTLE_);
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_SELECTSKILLWINDOW_,type); 
	}
	else if(type == _ATHLETICS_SERVANT_BATTLE_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_SELECTSKILLWINDOW_);
		DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
		char type[128] = "";
		sprintf(type,"%d",_TYPED_EVENT_SHOW_PUCONGWINDOW_);
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_SELECTSKILLWINDOW_,type); 
	}
	else if(type == _ATHLETICS_FRIEND_BATTLE_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_SELECTSKILLWINDOW_);
		DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
		char type[128] = "";
		sprintf(type,"%d",_TYPED_EVENT_SHOW_FRIENDWINDOW_);
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_SELECTSKILLWINDOW_,type);
	}
	else if(type == _ATHLETICS_KUANGDONG_BATTLE_TYPE_ || type == _ATHLETICS_KUANGDONG_HUNTLIEREN_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_SELECTSKILLWINDOW_);
		DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
		char type[128] = "";
		sprintf(type,"%d",_TYPED_EVENT_SHOW_MINEAREAWINDOW_);
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_SELECTSKILLWINDOW_,type);
	}
	else if(type == _ATHLETICS_BOSSSCORE_BATTLE_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_SELECTSKILLWINDOW_);
		DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
		char type[128] = "";
		sprintf(type,"%d",_TYPED_EVENT_SHOW_BOSSSCOREWINDOW_);
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_SELECTSKILLWINDOW_,type);
	}
	else if(type == _ATHLETICS_CHALLENEGE_HEROSOUL_TYPE_)
	{ 
		DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_SELECTSKILLWINDOW_);
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_LOADINGWINDOW_,_to_event_param_(IProcedure::_TYPED_HOME_PROCEDURE_));
	}*/
}
void AthleticsResultWindow::OnBackToEmployClick(CCObject * pSender)
{
	CCLOG("OnBackToEmploy: ");
	int type = ATHLETICPROCEDUREDATA->athleticsBattleType;
	if(type == _ATHLETICS_CUSTOMS_BATTLE_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pSelectMissionProcedure->m_skipWindow = _TYPED_EVENT_SHOW_STRENTHENWINDOW_;
		DOTATribeApp::get_instance2()->m_pSelectMissionProcedure->m_skipTabNum = 0;
		DOTATribeApp::get_instance2()->m_pAthleticsProcudure->OnChangeProcedureToMission();
	}
	else if(type == _ATHLETICS_ARENA_BATTLE_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_STRENTHENWINDOW_);
		DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
		char param1[128];
		sprintf(param1,"%d",0);
		char param2[128];
		sprintf(param2,"%d",_TYPEF_EVENT_SEND_ARENAREQUEST_);
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_STRENTHENWINDOW_,param1,param2);

		return ;
	}
	else if(type == _ATHLETICS_CLIMPTOWER_BATTLE_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_STRENTHENWINDOW_);
		DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
		char param1[128];
		sprintf(param1,"%d",0);
		char param2[128];
		sprintf(param2,"%d",_TYPED_EVENT_SHOW_CLIMBTOWERWINDOW_);
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_STRENTHENWINDOW_,param1,param2);

	}
	else if(type == _ATHLETICS_TEAM_BATTLE_TYPE_)
	{
		TEAMBATTLEDATAHANDLER->DestroyMyTeam();
		DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_STRENTHENWINDOW_);
		DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
		char param1[128];
		sprintf(param1,"%d",0);
		char param2[128];
		sprintf(param2,"%d",_TYPED_EVENT_CHANGETO_TEAMBATTLE_);
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_STRENTHENWINDOW_,param1,param2);
	}
	else if(type == _ATHLETICS_SERVANT_BATTLE_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_STRENTHENWINDOW_);
		DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
		char param1[128];
		sprintf(param1,"%d",0);
		char param2[128];
		sprintf(param2,"%d",_TYPED_EVENT_SHOW_PUCONGWINDOW_);
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_STRENTHENWINDOW_,param1,param2);
	}
	else if(type == _ATHLETICS_FRIEND_BATTLE_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_STRENTHENWINDOW_);
		DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
		char param1[128];
		sprintf(param1,"%d",0);
		char param2[128];
		sprintf(param2,"%d",_TYPED_EVENT_SHOW_FRIENDWINDOW_);
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_STRENTHENWINDOW_,param1,param2);

	}
	else if(type == _ATHLETICS_KUANGDONG_BATTLE_TYPE_ || type == _ATHLETICS_KUANGDONG_HUNTLIEREN_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_STRENTHENWINDOW_);
		DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
		char param1[128];
		sprintf(param1,"%d",0);
		char param2[128];
		sprintf(param2,"%d",_TYPED_EVENT_SHOW_MINEAREAWINDOW_);
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_STRENTHENWINDOW_,param1,param2, _to_event_param_(MININGDATAHANDLER->m_iBackArea));
	}
	else if(type == _ATHLETICS_BOSSSCORE_BATTLE_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_STRENTHENWINDOW_);
		DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
		char param1[128];
		sprintf(param1,"%d",0);
		char param2[128];
		sprintf(param2,"%d",_TYPED_EVENT_SHOW_BOSSSCOREWINDOW_);
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_STRENTHENWINDOW_,param1,param2);
	}
	else if(type == _ATHLETICS_CHALLENEGE_HEROSOUL_TYPE_)
	{
		DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_STRENTHENWINDOW_);
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_LOADINGWINDOW_,_to_event_param_(IProcedure::_TYPED_HOME_PROCEDURE_));
	}

}
void AthleticsResultWindow::InitData()
{
    //读取战斗结果
	athleticsWinType=false;

	if(AthleticProcedureDataHandler::get_instance2()!=NULL)
	{
		AthleticProcedureDataHandler::get_instance2()->isReTryBattle=false;
	}
	if(ATHLETICPROCEDUREDATA!=NULL)
	{
		//获得战斗结果
		athleticsWinType=AthleticsSceneManager::get_instance2()->GetAthleticsResult();
		 
		//读取战斗奖励信息
		PAthleticsBaseReward pAthleticsBaseReward=ATHLETICPROCEDUREDATA->pAthleticBaseReward;
		CCLOG("Type %d",pAthleticsBaseReward->battleType);
		if(pAthleticsBaseReward!=NULL&&pAthleticsBaseReward->battleType==_ATHLETICS_CUSTOMS_BATTLE_TYPE_&&pAthleticsBaseReward->hasReward==AthleticsBaseReward::_BASEREWARD_REWARD_TYPE_)
		{ 
			//初始化普通战斗结果数据
			InitCustomBattleRewareData();
		}
		else if(pAthleticsBaseReward!=NULL && pAthleticsBaseReward->battleType==_ATHLETICS_CLIMPTOWER_BATTLE_TYPE_ && pAthleticsBaseReward->hasReward==AthleticsBaseReward::_BASEREWARD_REWARD_TYPE_)
		{
			//初始化爬塔结果数据
			InitTowerRewardData();
		}
		else if(pAthleticsBaseReward!=NULL && pAthleticsBaseReward->battleType == _ATHLETICS_ARENA_BATTLE_TYPE_ && pAthleticsBaseReward->hasReward == AthleticsBaseReward::_BASEREWARD_REWARD_TYPE_)
		{
			//初始化竞技结果数据
			InitArenaBattleData();
			if (!athleticsWinType)
			{
				CCLabelTTF* fightAgainTitle = (CCLabelTTF*)m_pLose->getChildByTag(_Result_LoseTryAgainButtonLabel_);
				fightAgainTitle->setVisible(false);
				CCMenu* pMenuItem_FightAgain = (CCMenu*)m_pLose->getChildByTag(_Result_LoseTryAgainButton_);
				pMenuItem_FightAgain->setVisible(false);
			}
			else
			{
				cocos2d::CCLabelTTF * pLabelForRewardTwo=(cocos2d::CCLabelTTF *)m_pWin->getChildByTag(_Result_WinMoneyValue_);
				if(pLabelForRewardTwo!=NULL)
				{
					pLabelForRewardTwo->setString(SysLangDataManager::get_instance2()->GetSysLangById(_ARENE_PRESTIGE_TXT_ID_).c_str());
				}
			}
		}
		else if(pAthleticsBaseReward != NULL && pAthleticsBaseReward->battleType == _ATHLETICS_TEAM_BATTLE_TYPE_ && pAthleticsBaseReward->hasReward == AthleticsBaseReward::_BASEREWARD_REWARD_TYPE_)
		{
			//初始化组队副本结果数据
			InitTeamBattleRewardData();
		}
		else if(pAthleticsBaseReward != NULL && pAthleticsBaseReward->battleType == _ATHLETICS_SERVANT_BATTLE_TYPE_)
		{
			//初始化仆从结果数据
			InitServantRewardData();  
		}
		else if(pAthleticsBaseReward != NULL && pAthleticsBaseReward->battleType == _ATHLETICS_FRIEND_BATTLE_TYPE_ && pAthleticsBaseReward->hasReward == AthleticsBaseReward::_BASEREWARD_NOREWARD_TYPE_)
		{
			//初始化好友切磋结果数据
			InitFriendBattleData();
		}
		else if(pAthleticsBaseReward != NULL && pAthleticsBaseReward->battleType == _ATHLETICS_KUANGDONG_BATTLE_TYPE_)
		{
			//初始化矿洞结果数据
			InitKuangDongBattleData();
		}
		else if(pAthleticsBaseReward != NULL && pAthleticsBaseReward->battleType == _ATHLETICS_CHALLENEGE_HEROSOUL_TYPE_)
		{
			//挑战英雄战魂结果数据
			InitFriendBattleData();
		}
		else if(pAthleticsBaseReward != NULL && pAthleticsBaseReward->battleType == _ATHLETICS_BOSSSCORE_BATTLE_TYPE_)
		{
			//初始化boss积分结果数据
			InitBossScoreBattleData(); 
		}
		else if(pAthleticsBaseReward != NULL && pAthleticsBaseReward->battleType == _ATHLETICS_KUANGDONG_HUNTLIEREN_TYPE_)
		{
			//初始化寻宝猎人抢夺结果数据
			InitHuntLieRenBattleData();
		}
		else
		{
			rewardNum = 0;  //奖励物品的个数
			rewardLv = -1;
			rewardOneValue ="";
			rewardTwoValue ="";
		} 
	}

}
void AthleticsResultWindow::InitCustomBattleRewareData()
{
	rewardNum = 0;  //奖励物品的个数
	cocos2d::CCLabelTTF * pLabelTitle=(cocos2d::CCLabelTTF *)m_pWin->getChildByTag(_Result_WinText_);
	pLabelTitle->setVisible(false);
	PAthleticsBaseReward pAthleticsBaseReward=ATHLETICPROCEDUREDATA->pAthleticBaseReward;

	PCustomsRewardInfo pCustomsRewardInfo=(PCustomsRewardInfo)pAthleticsBaseReward->rewardDataInfo;
	if(pCustomsRewardInfo!=NULL)
	{
		rewardLv = pCustomsRewardInfo->starLevel;
		char temp[128] = {0};
		sprintf(temp, "%d", pCustomsRewardInfo->rewardExp);
		rewardOneValue.assign(temp);
		sprintf(temp, "%d", pCustomsRewardInfo->rewardMoney);
		rewardTwoValue.assign(temp);
		rewardThreeValue="";

		size_t rewardItemCount=pCustomsRewardInfo->rewardVec.size();
		for(size_t rewardIndex=0;rewardIndex<rewardItemCount;rewardIndex++)
		{
			PRewardBaseData pRewardBaseData=pCustomsRewardInfo->rewardVec.at(rewardIndex);
			if(pRewardBaseData)
			{	 
				switch( pRewardBaseData->itemType)
				{
				case RewardBaseData::_REWARDBASE_ITEMS_TYPE_ :
					{
						int	itemQuality  = ((PRewardItem)(pRewardBaseData->rewardData))->itemQuality;
						int	iconID =((PRewardItem)(pRewardBaseData->rewardData))->iconID;
						int	itemCount =((PRewardItem)(pRewardBaseData->rewardData))->itemCount;
						int	itemCatogory =((PRewardItem)(pRewardBaseData->rewardData))->catogory;
						char tempImage[128] = ""; 
						switch(rewardNum)
						{
						case 0:
							{
								obj_quality_1 = itemQuality;
								obj_icon_1 = iconID;
								rewardGoodsTypeOne = itemCatogory;
								rewardGoodsOneNum = itemCount;
								break;
							}
						case  1:
							{
								obj_quality_2 = itemQuality;
								obj_icon_2 = iconID;
								rewardGoodsTypeTwo = itemCatogory;
								rewardGoodsTwoNum = itemCount;
								break;
							}
						case 2:
							{
								obj_quality_3 = itemQuality;
								obj_icon_3 = iconID;
								rewardGoodsTypeThree = itemCatogory;
								rewardGoodsThreeNum = itemCount;
								break;
							}
						default:break;
						}
						rewardNum += 1;
						break;
					}
				}
			}
		}

	}

}
void AthleticsResultWindow::InitTowerRewardData()
{
	rewardNum = 0;  //奖励物品的个数
	PAthleticsBaseReward pAthleticsBaseReward=ATHLETICPROCEDUREDATA->pAthleticBaseReward;

	CCNode* Money = (CCNode*)m_pWin->getChildByTag(_Result_WinMoney_);
	Money->setVisible(false);
	CCNode* MoneyLabel = (CCNode*)m_pWin->getChildByTag(_Result_WinMoneyValue_);
	MoneyLabel->setVisible(false);
	PTowerRewardInfo pTowerRewardInfo=(PTowerRewardInfo)pAthleticsBaseReward->rewardDataInfo;
	if(pTowerRewardInfo!=NULL)
	{
		rewardLv = -1;
		char temp[128] = {0};
		sprintf(temp, "%d", pTowerRewardInfo->rewardExp);
		rewardOneValue.assign(temp);
		rewardTwoValue = "";
		rewardThreeValue = "";

		size_t rewardItemCount=pTowerRewardInfo->rewardVec.size();
		for(size_t rewardIndex=0;rewardIndex<rewardItemCount;rewardIndex++)
		{
			PRewardItem pRewardItem = pTowerRewardInfo->rewardVec.at(rewardIndex);
			if(pRewardItem != NULL)
			{
				int itemQuality = pRewardItem->itemQuality;
				int iconID = pRewardItem->iconID;
				if(0 == rewardNum)
				{
					obj_quality_1 = itemQuality;
					obj_icon_1 = iconID;
					rewardGoodsOneNum = pRewardItem->itemCount;
				}
				else if(1 == rewardNum)
				{
					obj_quality_2 = itemQuality;
					obj_icon_2 = iconID;
					rewardGoodsTwoNum = pRewardItem->itemCount;
				}
				else if(2 == rewardNum)
				{
					obj_quality_3 = itemQuality;
					obj_icon_3 = iconID;
					rewardGoodsThreeNum = pRewardItem->itemCount;
				}
				rewardNum += 1;
			}

		}

	}

}
void AthleticsResultWindow::InitArenaBattleData()
{
	rewardNum = 0;  //奖励物品的个数
	PAthleticsBaseReward pAthleticsBaseReward=ATHLETICPROCEDUREDATA->pAthleticBaseReward;

	CCNode* Money = (CCNode*)m_pWin->getChildByTag(_Result_WinMoney_);
	Money->setVisible(false);
	CCNode* MoneyLabel = (CCNode*)m_pWin->getChildByTag(_Result_WinMoneyValue_);
	MoneyLabel->setVisible(false);

	CCNode* Exp = (CCNode*)m_pWin->getChildByTag(_Result_WinExp_);
	Exp->setVisible(false);
	CCNode* ExpLabel = (CCNode*)m_pWin->getChildByTag(_Result_WinExpValue_);
	ExpLabel->setVisible(false);

	CCNode* sw = (CCNode*)m_pWin->getChildByTag(_Result_WinShengWang_);
	sw->setVisible(true);
	CCNode* swLabel = (CCNode*)m_pWin->getChildByTag(_Result_WinShengWangValue_);
	swLabel->setVisible(true);

	PArenaRewardInfo pArenaRewardInfo=(PArenaRewardInfo)pAthleticsBaseReward->rewardDataInfo;
	if(pArenaRewardInfo!=NULL)
	{
		rewardLv = -1;
		char temp[128] = {0};
		rewardOneValue = "";
		rewardTwoValue = "";
		sprintf(temp, "%d", pArenaRewardInfo->rewardPrestige);//聲望獎勵
		rewardThreeValue.assign(temp);

	}

}
void AthleticsResultWindow::InitFriendBattleData()
{
	CCNode* Money = (CCNode*)m_pWin->getChildByTag(_Result_WinMoney_);
	Money->setVisible(false);
	CCNode* MoneyLabel = (CCNode*)m_pWin->getChildByTag(_Result_WinMoneyValue_);
	MoneyLabel->setVisible(false);

	CCNode* Exp = (CCNode*)m_pWin->getChildByTag(_Result_WinExp_);
	Exp->setVisible(false);
	CCNode* ExpLabel = (CCNode*)m_pWin->getChildByTag(_Result_WinExpValue_);
	ExpLabel->setVisible(false);

	NFC_setNodeVisable(_Result_LoseTryAgainButton_,m_pWin,false);
	NFC_setNodeVisable(_Result_LoseTryAgainButtonLabel_,m_pWin,false);
	 
	rewardNum = 0;  //奖励物品的个数
	rewardLv = -1;
	rewardOneValue ="";
	rewardTwoValue ="";
}
void AthleticsResultWindow::InitKuangDongBattleData()
{
	rewardNum = 0;  //奖励物品的个数
	rewardLv = -1;
	rewardOneValue ="";
	rewardTwoValue ="";
	rewardThreeValue ="";
	PAthleticsBaseReward pAthleticsBaseReward = ATHLETICPROCEDUREDATA->pAthleticBaseReward;

	CCNode* Money = (CCNode*)m_pWin->getChildByTag(_Result_WinMoney_);
	Money->setVisible(false);
	CCNode* MoneyLabel = (CCNode*)m_pWin->getChildByTag(_Result_WinMoneyValue_);
	MoneyLabel->setVisible(false);

	CCNode* Exp = (CCNode*)m_pWin->getChildByTag(_Result_WinExp_);
	Exp->setVisible(false);
	CCNode* ExpLabel = (CCNode*)m_pWin->getChildByTag(_Result_WinExpValue_);
	ExpLabel->setVisible(false);


	PMiningRewardInfo pMiningRewardInfo=(PMiningRewardInfo)pAthleticsBaseReward->rewardDataInfo;
	if(pMiningRewardInfo!=NULL)
	{

		char temp[128] = {0};
		if (pMiningRewardInfo->rewardExp != 0)
		{
			sprintf(temp, "%d", pMiningRewardInfo->rewardExp);
			rewardOneValue.assign(temp);
		}
		if (pMiningRewardInfo->rewardMoney != 0)
		{
			sprintf(temp, "%d", pMiningRewardInfo->rewardMoney);
			rewardTwoValue.assign(temp);
			Money->setVisible(true);
			Money->setPosition(ccp(Money->getPositionX()-220,Money->getPositionY()));
			MoneyLabel->setVisible(true);
			MoneyLabel->setPosition(ccp(MoneyLabel->getPositionX()-220,MoneyLabel->getPositionY()));
		}


		

		size_t rewardItemCount = pMiningRewardInfo->rewardVec.size();
		for(size_t rewardIndex=0; rewardIndex<rewardItemCount; rewardIndex++)
		{
			PRewardItem pRewardItem = pMiningRewardInfo->rewardVec.at(rewardIndex);
			if(pRewardItem != NULL)
			{
				int itemQuality = pRewardItem->itemQuality;
				int iconID = pRewardItem->iconID;
				if(0 == rewardNum)
				{
					obj_quality_1 = itemQuality;
					obj_icon_1 = iconID;
					rewardGoodsOneNum = pRewardItem->itemCount;
				}
				else if(1 == rewardNum)
				{
					obj_quality_2 = itemQuality;
					obj_icon_2 = iconID;
					rewardGoodsTwoNum = pRewardItem->itemCount;
				}
				else if(2 == rewardNum)
				{
					obj_quality_3 = itemQuality;
					obj_icon_3 = iconID;
					rewardGoodsThreeNum = pRewardItem->itemCount;
				}
				rewardNum += 1;
			}

		}

	}

	PMiningMapInfo mapInfo = (PMiningMapInfo)ATHLETICPROCEDUREDATA->pAthleticsMapInfo->mapInfoData;
	MININGDATAHANDLER->m_iFightType = mapInfo->stageID;//存储矿洞战斗类型
	int area = 0;
	int type = MININGDATAHANDLER->m_iFightType;
	if(type == 1)
	{
		area = MineAreaWindow::_PAGE_DWARVENAREA_;
	}
	else if(type == 2)
	{
		area = MineAreaWindow::_PAGE_DRAGONAREA_;
	}
	else if(type == 3 || type == 4)
	{
		area = MineAreaWindow::_PAGE_HUNTMINE_;
	}
	MININGDATAHANDLER->m_iBackArea = area;
}

void AthleticsResultWindow::InitBossScoreBattleData()
{
	rewardNum = 0;  //奖励物品的个数
	rewardLv = -1;
	rewardOneValue ="";
	rewardTwoValue ="";
	rewardThreeValue ="";

	CCNode* Money = (CCNode*)m_pWin->getChildByTag(_Result_WinMoney_);
	Money->setVisible(false);
	CCNode* MoneyLabel = (CCNode*)m_pWin->getChildByTag(_Result_WinMoneyValue_);
	MoneyLabel->setVisible(false);

	CCNode* Exp = (CCNode*)m_pWin->getChildByTag(_Result_WinExp_);
	Exp->setVisible(false);
	CCNode* ExpLabel = (CCNode*)m_pWin->getChildByTag(_Result_WinExpValue_);
	ExpLabel->setVisible(false);

	PBossScoreRewardInfo reward = (PBossScoreRewardInfo)ATHLETICPROCEDUREDATA->pAthleticBaseReward->rewardDataInfo;
	if(!reward)
		return;

	char temp[512] = {0};
	sprintf(temp, "%d", reward->fightScore);
	rewardThreeValue.assign(temp);
	
	NFC_showNode(_Result_WinShengWangValue_, m_pWin, true);
	NFC_showNode(_Result_WinShengWang_, m_pWin, false);

	if(athleticsWinType)
	{
		cocos2d::CCNode * node = m_pWin->getChildByTag(_Result_WinShengWangValue_);
		node->setPositionX(node->getPositionX() - 100);

		sprintf(temp, "%s   %d", SysLangDataManager::get_instance2()->GetSysLangById(2076).c_str(), reward->fightScore);
		rewardThreeValue.assign(temp);
	}
	else
	{
		NFC_setLabelString(_Result_LoseEquipAppraise_, m_pLose, SysLangDataManager::get_instance2()->GetSysLangById(2076), true);
	}
}

void AthleticsResultWindow::InitHuntLieRenBattleData()
{
	rewardNum = 0;  //奖励物品的个数
	rewardLv = -1;
	rewardOneValue="";
	rewardTwoValue= "";
	rewardThreeValue ="";
	PAthleticsBaseReward pAthleticsBaseReward = ATHLETICPROCEDUREDATA->pAthleticBaseReward;

	PHuntLieRenRewardInfo pHuntLieRenRewardInfo=(PHuntLieRenRewardInfo)pAthleticsBaseReward->rewardDataInfo;
	if(pHuntLieRenRewardInfo!=NULL)
	{	
		char temp[128] = {0};
		sprintf(temp, "%d", pHuntLieRenRewardInfo->rewardExp);
		rewardOneValue.assign(temp);
		sprintf(temp, "%d", pHuntLieRenRewardInfo->rewardMoney);
		rewardTwoValue.assign(temp);
		rewardThreeValue="";

		if(pHuntLieRenRewardInfo->hasExtra > 0)
		{
			rewardNum = 1;

			PNewRewardItem reward = (PNewRewardItem)pHuntLieRenRewardInfo->pRewardItem;

			obj_quality_1 = reward->quality;
			obj_icon_1 = reward->iconId;
			rewardGoodsOneNum = reward->count;

			//奖励话
			NFC_setLabelString(_Result_WinText_, m_pWin, 2114, true);
		}
		else
		{
			//奖励话
			NFC_setLabelString(_Result_WinText_, m_pWin, 2115, true);
		}
	}
	MININGDATAHANDLER->m_iBackArea = MineAreaWindow::_PAGE_HUNTMINE_;
	//此处对返回到寻宝界面是否要打开选中猎人进行判断(战斗失败，或者抢夺失败)
	if(athleticsWinType == false || pHuntLieRenRewardInfo->hasExtra == 0)
		MININGDATAHANDLER->OnHuntLieRenQiangDuoAthleticEnd(false);
}

void AthleticsResultWindow::InitTeamBattleRewardData()
{
	rewardNum = 0;  //奖励物品的个数
	rewardLv = -1;
	rewardOneValue="";
	rewardTwoValue= "";
	rewardThreeValue ="";
	PAthleticsBaseReward pAthleticsBaseReward = ATHLETICPROCEDUREDATA->pAthleticBaseReward;

	CCNode* Money = (CCNode*)m_pWin->getChildByTag(_Result_WinMoney_);
	Money->setVisible(false);
	CCNode* MoneyLabel = (CCNode*)m_pWin->getChildByTag(_Result_WinMoneyValue_);
	MoneyLabel->setVisible(false);

	CCNode* Exp = (CCNode*)m_pWin->getChildByTag(_Result_WinExp_);
	Exp->setVisible(false);
	CCNode* ExpLabel = (CCNode*)m_pWin->getChildByTag(_Result_WinExpValue_);
	ExpLabel->setVisible(false);
	PTeamRewardInfo pTeamRewardInfo=(PTeamRewardInfo)pAthleticsBaseReward->rewardDataInfo;
	if(pTeamRewardInfo!=NULL)
	{	
		char temp[128] = {0};
		size_t rewardItemCount = pTeamRewardInfo->rewardVec.size();
		for(size_t rewardIndex=0; rewardIndex<rewardItemCount; rewardIndex++)
		{
			PRewardItem pRewardItem = pTeamRewardInfo->rewardVec.at(rewardIndex);
			if(pRewardItem != NULL)
			{
				int itemQuality = pRewardItem->itemQuality;
				int iconID = pRewardItem->iconID;
				if(0 == rewardNum)
				{
					obj_quality_1 = itemQuality;
					obj_icon_1 = iconID;
					rewardGoodsOneNum = pRewardItem->itemCount;
				}
				else if(1 == rewardNum)
				{
					obj_quality_2 = itemQuality;
					obj_icon_2 = iconID;
					rewardGoodsTwoNum = pRewardItem->itemCount;
				}
				else if(2 == rewardNum)
				{
					obj_quality_3 = itemQuality;
					obj_icon_3 = iconID;
					rewardGoodsThreeNum = pRewardItem->itemCount;
				}
				rewardNum += 1;
			}

		}

	}

}
void AthleticsResultWindow::InitServantRewardData()
{
	rewardNum = 0;  //奖励物品的个数
	rewardLv = -1;
	rewardOneValue ="";
	rewardTwoValue ="";

	PAthleticsBaseReward pAthleticsBaseReward = ATHLETICPROCEDUREDATA->pAthleticBaseReward;
	  
	PServantRewardInfo pTeamRewardInfo=(PServantRewardInfo)pAthleticsBaseReward->rewardDataInfo;
	if(!pTeamRewardInfo)
	{
		rewardLv = -1;
		return;
	}
	rewardLv = -1;
	char temp[128] = {0};
	sprintf(temp, "%d", pTeamRewardInfo->shengwang);//声望
	rewardThreeValue.assign(temp);
  
}
void AthleticsResultWindow::_fallDown(cocos2d::CCNode* actionNode)
{
	float screenHeight=(float)DOTATribeApp::get_instance2()->GetAppHeight();
	cocos2d::CCPoint endPoint=actionNode->getPosition();
	actionNode->setPositionY(screenHeight);
	int microsecond=ClientConstDataManager::get_instance2()->getValueByKey(CONST_KEY_FALLDOWN_TIME);
	cocos2d::CCMoveTo* moveto=cocos2d::CCMoveTo::create(microsecond*1.0f/1000,endPoint);
	cocos2d::CCEaseExponentialOut* action=cocos2d::CCEaseExponentialOut::create(moveto);
	cocos2d::CCCallFunc  * callBackFunc=cocos2d::CCCallFunc::create(this,callfunc_selector(AthleticsResultWindow::_fallDownCallBack));
	cocos2d::CCAction * ruChangeSequence=cocos2d::CCSequence::create(action,callBackFunc,NULL);
	actionNode->runAction(ruChangeSequence);
}
void AthleticsResultWindow::_fallDownCallBack()
{
	m_TitleSkeleton->setAnimation("ed2",false,2);
	if (rewardLv > 0)
	{
		char _star[128]="";
		sprintf(_star,"star%d",rewardLv);
		m_StarSkeleton->setVisible(true);
		m_StarSkeleton->setAnimation(_star,false);
	}

	CCLog("CallBackPlaySpine Handler!");
}
void AthleticsResultWindow::skeletonTriggerCallHandler(int eventType,int animationID,PSkeletonCallBack_Node  pSkeletonCallBackNode)
{
	if (animationID == 2)
		m_TitleSkeleton->setAnimation("ed3",true);
}
