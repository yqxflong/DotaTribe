//Name：AtheleticsSceneManager
//Function：战斗系统总入口
//Author:	Johny

#include <cocos2d.h>
#include "../include/AthleticsSceneManager.h"
#include "../include/AthleticConfig.h"


#include "../include/AthleticsWindow.h"
#include "../include/DOTATribeApp.h"
#include "../include/AthleticsProcedure.h"
#include "../include/AthleticProcedureDataHandler.h"
#include "../include/AthleticsInstructionSystem.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/TimeSystem.h"
#include "../include/InputCommand.h"
#include "../include/SoundSystem.h"
#include "../include/IWindow.h"
#include "../include/Common.h"
#include "../include/GuideSystem.h"
#include "../include/EngineSystem.h"
#include "../include/BaseObjectManager.h"
#include "../include/CameraShakeDataManager.h"

#include "../include/ScreenEffect.h"
#include "../include/ShakeEffect.h"
#include "../include/ScreenShakeEffect.h"
#include "../include/ProfSystem.h"						//性能分析
  
#include <vector>
#include <string>
#include <limits> 

using  namespace  cobra_win;
using  namespace  cocos2d;
 
template<> AthleticsSceneManager* cobra_win::Singleton2<AthleticsSceneManager>::m_pMySelf = NULL;
 
float AthleticsSceneManager::AthleticsSpeed=0.0f;

AthleticsSceneManager::AthleticsSceneManager()
{ 
//////////////////////////////////////////////////////////////////////////
	pAthleticsMapInfo=NULL;
	pPreAthleticsData=NULL;
    pAthleticResultData=NULL;
	 
	pAthleticsUIManager=NULL;
 
	athleticBattleType=_ATHLETICS_UNKONW_BATTLE_TYPE_;
	athleticRecordType=_ATHLETICS_UNKONW_RECORD_TYPE_;
	athleticWatchType=_ATHLECTICS_SELFT_WATCH_TYPE_;
	 
	playGroupHeroicList.clear();
	enemyGroupHeroicList.clear();
	m_shakeEffectList.clear();

	curPlayGroupRoleID=-1;
	curPlayGroupRoleType=0;

	curEnmeyGroupRoleID=-1;
	curEnmeyGroupRoleType=0;

	isPlayGroupRoleChange=false;
	isEnemyGroupRoleChange=false;

	admittanceTickCount=0;
	callBackAdmittanceCount=0;

	preLoadPlistTexturePool.clear();
	 
	isTryPlayNpcTack=false;
	npcBattleTalkState=NpcTalkView::_UNKONW_NPCTALK_TYPE_;
	pNpcTalkView=NULL;

	isBattleWin=false;
	m_bIsLayOutUIData=false;

 //////////////////////////////////////////////////////////////////////////
	isGameOver_=false;

	m_bIsTriggerVIPSkip=false;
 
	leftFightRole_=NULL;
	rightFightRole_=NULL;
 
	cocos2d::CCSprite * leftBloodSprite=(cocos2d::CCSprite *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_LEFT_HP_BG);
	if(leftBloodSprite!=NULL)
	hpRectWidth_=leftBloodSprite->getContentSize().width;

	cocos2d::CCSprite * leftBludSprite=(cocos2d::CCSprite *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_LEFT_MP_BG);
	if(leftBludSprite!=NULL)
	mpRectWidth_=leftBludSprite->getContentSize().width;
	 
	NormalSpeed =  (1.0*ClientConstDataManager::get_instance2()->getValueByKey(CONST_KEY_BATTLE_NORSPD))/10;
	NormalSpeedx2 = (1.0*ClientConstDataManager::get_instance2()->getValueByKey(CONST_KEY_BATTLE_DOUBLESPD))/10;
	NormalSpeedx3 = (1.0*ClientConstDataManager::get_instance2()->getValueByKey(CONST_KEY_BATTLE_TRIPLESPD))/10;

	m_fRoleAdmissonDelayTime=ClientConstDataManager::get_instance2()->getValueByKey(Athletics_Admisson_Delay)/Millisecond_TIME_UNIT;
	m_fResultWinDelayTime=ClientConstDataManager::get_instance2()->getValueByKey(Athletics_Result_Delay)/Millisecond_TIME_UNIT;
	isRePlayAthletics_=false;

	//@初始化战斗速度
	AthleticsSpeed=AthleticsSpeed<0.001?NormalSpeedx2:AthleticsSpeed;
} 
 
AthleticsSceneManager::~AthleticsSceneManager()
{ 
   m_pMySelf=NULL;
}
 
//@战斗地图信息数据包
bool  AthleticsSceneManager::LoadAthleticsMapInfo()
{
	if(ATHLETICPROCEDUREDATA!=NULL)
	{
		pAthleticsMapInfo=ATHLETICPROCEDUREDATA->pAthleticsMapInfo;
		if(pAthleticsMapInfo&&pAthleticsMapInfo->mapInfoData)
		{  
			athleticBattleType=pAthleticsMapInfo->battleType;
			pAthleticsUIManager->LoadAthleticsMapInfoUIData(pAthleticsMapInfo);
			return true;
		} 
	}
	return false;
}


/*
	战前数据包加载
*/
bool   AthleticsSceneManager::LoadAthleticPreData()
{
	 if(ATHLETICPROCEDUREDATA!=NULL)
	 {
	  	pPreAthleticsData=ATHLETICPROCEDUREDATA->pPreAthleticsData;
		if(pPreAthleticsData!=NULL)
		{  
			pAthleticsUIManager->LoadPreAthleticsUIData(pPreAthleticsData);
	   	    return true;
		} 
	 }
	 return false;
}


/*
	 战斗结果信息包加载
*/
bool   AthleticsSceneManager::LoadAthleticResultData()
{
	if(ATHLETICPROCEDUREDATA!=NULL)
	{
		pAthleticResultData=ATHLETICPROCEDUREDATA->pAthleticResultData;
		if(pAthleticResultData!=NULL&&pAthleticResultData->firstBattleCount>0)
		return true;
	}
	return false;
}

/*
检测是否为查看战斗类型
*/
bool  AthleticsSceneManager::LoadAthleticRecordType()
{
	 if(ATHLETICPROCEDUREDATA!=NULL)
	 {
		if(ATHLETICPROCEDUREDATA->pAthleticBaseReward!=NULL) 
		{ 
			if(ATHLETICPROCEDUREDATA->pAthleticBaseReward->battleType==_ATHLETICS_ARENA_BATTLE_TYPE_)
			{
				switch(ATHLETICPROCEDUREDATA->pAthleticBaseReward->hasReward)
				{

				case  AthleticsBaseReward::_BASEREWARD_NOREWARD_TYPE_:
					athleticRecordType=_ATHLETICS_REPLAY_RECORD_TYPE_;
					return true; 
				case  AthleticsBaseReward::_BASEREWARD_REWARD_TYPE_:
					athleticRecordType=_ATHLETICS_LIVE_RECORD_TYPE_;
					return true;
				default: 
					return false;
				}
			}
			else
			{
				athleticRecordType=_ATHLETICS_LIVE_RECORD_TYPE_;
				return true;
			}
		}
	 }
	 return false;
}

/*
检测NPCTalk播放配置
*/
bool  AthleticsSceneManager::LoadNpcTalkConfigData()
{ 
	if(pAthleticsMapInfo!=NULL)
	{ 
		switch(pAthleticsMapInfo->battleType)
		{
		case  _ATHLETICS_CUSTOMS_BATTLE_TYPE_:
			{
				 //首先判断是否当前是否可以扫荡
				PCustomsMapInfo pCustomsMapInfo=(PCustomsMapInfo)pAthleticsMapInfo->mapInfoData;
				if(pCustomsMapInfo!=NULL)
				{ 
					if(AthleticProcedureDataHandler::get_instance2()!=NULL)
					{
						if(ATHLETICPROCEDUREDATA->preMapInfoData.preIsClear)
						{
							isTryPlayNpcTack=false;
							return true;
						}
					}
					NpcTalkData * pNpcTalkData=NpcTalkDataManager::get_instance2()->GetNpcTalkDataWithMapAndStage(ATHLETICPROCEDUREDATA->preMapInfoData.preMapID,ATHLETICPROCEDUREDATA->preMapInfoData.preStageID);
					if(pNpcTalkData!=NULL)
					{
						pNpcTalkView=NpcTalkView::createNpcTalkView(UIBaseDialog::_UIBASEDIALOG_NORMAL_PRIORITY_);
						if(pNpcTalkView!=NULL)
						{
							pNpcTalkView->setDelegatePrototy(this);
							pNpcTalkView->SetNpcTalkConfigData(pNpcTalkData);
							cocos2d::CCNode * pNpcTalkLayer=GetAthleticsNpcTalkLayer();
							if(pNpcTalkLayer!=NULL)
							{
								 pNpcTalkLayer->addChild(pNpcTalkView);
								 SetAthleticsNpcTalkLayerVisible(false);
							}
						}
						isTryPlayNpcTack=true;
						return true;
					}
				}
			}
			break;
		case _ATHLETICS_CLIMPTOWER_BATTLE_TYPE_:
			{
				PTowerMapInfo pTowerMapInfo=(PTowerMapInfo)pAthleticsMapInfo->mapInfoData;
				NpcTalkData * pNpcTalkData=NpcTalkDataManager::get_instance2()->GetNpcTalkDataWithMapAndStage(pTowerMapInfo->mapID,(int)pTowerMapInfo->floor);
				if(pNpcTalkData!=NULL)
				{
					pNpcTalkView=NpcTalkView::createNpcTalkView(UIBaseDialog::_UIBASEDIALOG_NORMAL_PRIORITY_);
					if(pNpcTalkView!=NULL)
					{
						pNpcTalkView->setDelegatePrototy(this);
						pNpcTalkView->SetNpcTalkConfigData(pNpcTalkData);
						cocos2d::CCNode * pNpcTalkLayer=GetAthleticsNpcTalkLayer();
						if(pNpcTalkLayer!=NULL)
						{
							pNpcTalkLayer->addChild(pNpcTalkView);
							SetAthleticsNpcTalkLayerVisible(false);
						}
					}
					isTryPlayNpcTack=true;
					return true;
				}
				else
				isTryPlayNpcTack=false;

				break;
			} 
		case _ATHLETICS_TEAM_BATTLE_TYPE_:
			isTryPlayNpcTack = false;
			break;
		default: 
			isTryPlayNpcTack=false;
			break;
		}
	}
    return  true;
}


void  AthleticsSceneManager::NpcTalkManagerHandler(int eventType)
{
	//处理Npc播放逻辑控制
	bool isError=false;
	switch(eventType)
	{ 
	case _ATHLETICS_ADMITTANCE_FINISH_CALL_EVENT_:
		{
			if(isTryPlayNpcTack&&pNpcTalkView!=NULL&&!pNpcTalkView->isFinishTalkCur())
			{
				//播放NPC动画 
				isError=pNpcTalkView->SetNpcTalkState(NpcTalkView::_BEFOR_NPCTALK_TYPE_,leftFightRole_->getRoleName(),leftFightRole_->getRoleIconID(),rightFightRole_->getRoleName(),rightFightRole_->getRoleIconID());
				if(!isError)
				{
					SetAthleticsNpcTalkLayerVisible(false);
					ATHLETICSICSYSTEM->OnCommandHandler(_TYPED_INPUT_COMMAND_RESUME_ATHLETICSINSTRUCTION_);
				}
				else
			    SetAthleticsNpcTalkLayerVisible(true);
				return ;
			}
			else
			{
				//继续指令
				ATHLETICSICSYSTEM->OnCommandHandler(_TYPED_INPUT_COMMAND_RESUME_ATHLETICSINSTRUCTION_);
				return;
			}
		}
		break;
	case _ATHLETICS_GAME_OVER_CALL_EVENT_:
		{
			if(isTryPlayNpcTack&&pNpcTalkView!=NULL)
			{
				//播放结果NPC对话
				char npcTalkState=isBattleWin ? NpcTalkView::_WIN_NPCTALK_TYPE_ : NpcTalkView::_FAIL_NPCTALK_TYPE_;
				isError=pNpcTalkView->SetNpcTalkState(npcTalkState,leftFightRole_->getRoleName(),leftFightRole_->getRoleIconID(),rightFightRole_->getRoleName(),rightFightRole_->getRoleIconID());
				if(!isError)
				{
					SetAthleticsNpcTalkLayerVisible(false);
					PostGameOverUINofitication();
				}
				else
				SetAthleticsNpcTalkLayerVisible(true);
				return ;
			}
			else
			{
				//继续指令
				PostGameOverUINofitication();
				return ;
			}
		}
		break;
	default:
		break;
	}
}

bool  AthleticsSceneManager::Init()
{
	do 
	{
		 CCNode::init();
		//初始化战斗数据
	  
		HideAthleticsDiableLayer();  //关闭禁用层

		pAthleticsUIManager=new  AthleticsUIManager();

		pAthleticsUIManager->Init();
		m_bIsLayOutUIData=true;
		 
		if(!LoadAthleticsMapInfo())
		break;
 
		if(!LoadAthleticPreData())
		break;

		//@耗时巨高
		if(!PreLoadAthleticRole())
			break;
		
		if(!LoadAthleticResultData())
		break;

		if(!LoadAthleticRecordType())
		break;
			
		if(!LoadNpcTalkConfigData())
		break;


		InitAthleticSceneUI();				                        //初始化场景UI
		AnalyseAthleticsResult();									//分析战斗结果

		// 创建技能驱动池
		new BaseObjectManager;										//技能驱动池
		new AthleticsInstructionSystem;								//战斗指令控制系统

		BASEOBJECTMANAGER->Init();						     	    //技能管理池初始化
		ATHLETICSICSYSTEM->Init();							        //战斗指令控制系统初始化

		//@SetVaribleSystem  For Start Athletics
		VARIABLESYSTEM_START_ATHLETICS
	
		return true;
		 
	} while (false);
    return false; 
}
 

void  AthleticsSceneManager::Tick()
{ 
     OnUpdateRoleTickBuffer(); 
	 OnUpdateRoleHPValue();
	 OnUpdateRoleMPValue(); 

	 if(!isGameOver_)
	 { 
		UpdateScreenShakeEffect();
	 	BASEOBJECTMANAGER->Tick();
	 	ATHLETICSICSYSTEM->Tick();
	}
	else
	{
		BASEOBJECTMANAGER->Destroy();
	}
} 
 
//@初始化战斗场景UI   负责场景环境配置以及人物基础属性UI更新
void    AthleticsSceneManager::InitAthleticSceneUI()
{ 
	if(pAthleticsUIManager!=NULL)
	{
		pAthleticsUIManager->InitSceneUI();
	}
	if(athleticRecordType==_ATHLETICS_REPLAY_RECORD_TYPE_)
	{
		isRePlayAthletics_=true;
		if(pAthleticsUIManager!=NULL)
		{
			pAthleticsUIManager->ShowNormalAllLayoutBtn();
		} 
	}
	 
	//////////////////////////////////////////////////////////////////////////
	if(!isRePlayAthletics_&&IsVIPCanSkipAthletics())
	{
		 pAthleticsUIManager->ShowVIPLayouBtn();
	}
	//////////////////////////////////////////////////////////////////////////

 	//初始化速度控制UI
	UpdateAthleticSpeedUI();
}


 

//@根据当前的轮次  创建战斗角色骨骼纹理  延时回调入场动画
void   AthleticsSceneManager::OnUpdateAthleticsRoleSkeleton(RoleUniqeDefine role1,RoleUniqeDefine role2)
{
    bool  isRole1Retain=false;
	bool  isRole2Retain=false;
 
	if((role1.sourceID==curPlayGroupRoleID&&role1.unitType==curPlayGroupRoleType)|| (role1.sourceID==curEnmeyGroupRoleID&&role1.unitType==curEnmeyGroupRoleType))
	{
		isRole1Retain=true;
	}

	if((role2.sourceID==curPlayGroupRoleID&&role2.unitType==curPlayGroupRoleType)|| (role2.sourceID==curEnmeyGroupRoleID&&role2.unitType==curEnmeyGroupRoleType))
	{
		isRole2Retain=true;
	}
	callBackAdmittanceCount=0;

	if(!isRole1Retain)
	{ 
		SetRoleWithRoleData(role1);
	}

	if(!isRole2Retain)
	{
		SetRoleWithRoleData(role2);
	}

	leftFightRole_->reInitRoleAdmissonState();
	rightFightRole_->reInitRoleAdmissonState();
 
	//延时回调入场动画
	cocos2d::CCDelayTime * delayTime=cocos2d::CCDelayTime::create(m_fRoleAdmissonDelayTime/AthleticsSpeed);
	if(delayTime!=NULL)
	{
		cocos2d::CCCallFunc  * callBackFunc=cocos2d::CCCallFunc::create(this,callfunc_selector(AthleticsSceneManager::CallBackPlayAdmittance));
		if(callBackFunc!=NULL)
		{
			cocos2d::CCAction * ruChangeSequence=cocos2d::CCSequence::create(delayTime,callBackFunc,NULL);
			Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_ICON)->runAction(ruChangeSequence);
		}
	} 

}
 

void		AthleticsSceneManager::SetRoleWithRoleData(RoleUniqeDefine & role)
{
	CCNode * rolePosConfig=NULL;
	int  RoleTag=0;
	int  RoleZOrder=0;
	HeroicRole  * pHeroicRole=IsRoleInPlayGroup(role);
	if(pHeroicRole!=NULL)
	{
		//左边
		if(leftFightRole_!=NULL)
		{
			leftFightRole_->OnStopAllEffect();
		 	leftFightRole_->setVisible(false);
		}
		pAthleticsUIManager->ReInitRectImage();
		pAthleticsUIManager->UpdateRoleInfoData(role,true);
		isPlayGroupRoleChange=true;
		rolePosConfig=Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_LEFT_INIT_CONFIG);
		RoleTag=LeftRoleTag;
		RoleZOrder=LowRoleZOrder;
		curPlayGroupRoleID=pHeroicRole->GetSubObjectID();
		curPlayGroupRoleType=pHeroicRole->getRoleType();
		pHeroicRole->setInitPosition(rolePosConfig->getPosition());
        if(pHeroicRole->getParent()!=GetAthleticsRootLayer())
		{
			GetAthleticsRootLayer()->addChild(pHeroicRole,RoleZOrder,RoleTag);       //加载角色Root结点
		}
		else
		{ 
			pHeroicRole->setVisible(true);
		}
		leftFightRole_=pHeroicRole; 
		leftFightRole_->setAnimationTimaScale(AthleticsSpeed);
		leftFightRole_->SetRoleEffectAnimationSpeedScale(AthleticsSpeed);
		callBackAdmittanceCount++;
	}
	else
	{
		pHeroicRole=IsRoleInEnmeyGroup(role);
		if(pHeroicRole!=NULL)
		{
			//右边
			if(rightFightRole_!=NULL)
			{
				rightFightRole_->OnStopAllEffect();
				rightFightRole_->setVisible(false);
			}
			pAthleticsUIManager->ReInitRectImage(false);
			pAthleticsUIManager->UpdateRoleInfoData(role,false);
			isEnemyGroupRoleChange=true;
			curEnmeyGroupRoleID=pHeroicRole->GetSubObjectID();
			curEnmeyGroupRoleType=pHeroicRole->getRoleType();
			rolePosConfig=Athletics_UI_Node(AthleticsWindow::ATHELTICS_UI_RIGHT_INIT_CONFIG);
			RoleTag=RightRoleTag;
			RoleZOrder=HighRoleZOrder;
			pHeroicRole->setInitPosition(rolePosConfig->getPosition());
			if(pHeroicRole->getParent()!=GetAthleticsRootLayer())
			{
				GetAthleticsRootLayer()->addChild(pHeroicRole,RoleZOrder,RoleTag);       //加载角色Root结点
			}
			else
			{
				 pHeroicRole->setVisible(true);
			}
			rightFightRole_=pHeroicRole;
			rightFightRole_->setAnimationTimaScale(AthleticsSpeed);
			rightFightRole_->SetRoleEffectAnimationSpeedScale(AthleticsSpeed);
			callBackAdmittanceCount++;
		}
	}	 
}
 

/*
获得当前战斗的观看类型
*/
char    AthleticsSceneManager::GetAthelticsWatchType()
{
	return athleticWatchType;
}

/*
设置当前战斗的观看类型
*/
void    AthleticsSceneManager::SetAthleticsWatchType(char watchType)
{  
	athleticWatchType=watchType;
}

/*
获得左队战斗结果
*/
bool   AthleticsSceneManager::GetAthleticsResult()
{
	return  isBattleWin;
}
 

bool	AthleticsSceneManager::IsWinRoleNeedHoming()
{ 
	if(leftFightRole_!=NULL&&leftFightRole_->hadPlayedDeadAnimation())
	{ 
	    return  !rightFightRole_->isRoleAtInitXPos();
	}
	if(rightFightRole_!=NULL&&rightFightRole_->hadPlayedDeadAnimation())
	{ 
		return  !leftFightRole_->isRoleAtInitXPos();
	}
	return false;
}


void   AthleticsSceneManager::GetNeedHomingRoleInfo(RoleUniqeDefine & roleInfo)
{
     if(leftFightRole_!=NULL&&leftFightRole_->hadPlayedDeadAnimation())
	 { 
		 roleInfo.sourceID=rightFightRole_->GetSubObjectID();
		 roleInfo.unitType=rightFightRole_->getRoleType();
		 return ;
	 }
	 if(rightFightRole_!=NULL&&rightFightRole_->hadPlayedDeadAnimation())
	 { 
		 roleInfo.sourceID=leftFightRole_->GetSubObjectID();
		 roleInfo.unitType=leftFightRole_->getRoleType();
		 return ;
	 }  
}

//@回调->播放出场动画
void   AthleticsSceneManager::CallBackPlayAdmittance()
{
   CCLog("CallBackPlayAdmittance Handler!");
   if(isPlayGroupRoleChange)
   {
	   leftFightRole_->playAdmissonAnimation();
	   isPlayGroupRoleChange=false;
   }
   if(isEnemyGroupRoleChange)
   {
	   rightFightRole_->playAdmissonAnimation();
	   isEnemyGroupRoleChange=false;
   }
}

//@回调->显示战斗结果
void AthleticsSceneManager::CallBackPlayResultUI()
{
	CCLog("CallBackPlayResultUI Handler!");
	ShowAthleticsDisableLayer();
	//设置战斗音效为正常速度
	VARIABLESYSTEM_SET_PLAY_MODE(NormalSpeed)
	EVENTSYSTEM->PushEvent(_TYPE_EVENT_SHOW_ATHLETICSRESULTWINDOW_);
}
 
//@预加载战斗角色骨骼角色
bool   AthleticsSceneManager::PreLoadAthleticRole()
{
	if(pPreAthleticsData!=NULL&&pAthleticsUIManager!=NULL)
	{  
		bool  isPlayGroupInFirstDeque=pAthleticsUIManager->GetIsPlayGroupInFirstDeque();

		//@加载己方骨骼
		size_t roleCount=pPreAthleticsData->firstdequeRoleVector.size();
		for(size_t index=0;index<roleCount;index++) {
			PBaseRoleInfo pBaseRoleInfo=pPreAthleticsData->firstdequeRoleVector.at(index);
			AddHeroicRoleInGroup(pBaseRoleInfo,isPlayGroupInFirstDeque);
		}

		//@加载敌方骨骼
		roleCount=pPreAthleticsData->seconddequeRoleVector.size();
		for(size_t index=0;index<roleCount;index++) {
			PBaseRoleInfo pBaseRoleInfo=pPreAthleticsData->seconddequeRoleVector.at(index);
			AddHeroicRoleInGroup(pBaseRoleInfo,!isPlayGroupInFirstDeque);
		}

		 //@通知UI管理器做战斗人物头像分析
		 pAthleticsUIManager->AnlayseTeamRoleNumber(playGroupHeroicList.size(),enemyGroupHeroicList.size());
		 return true;
	 }
     return   false;
}


char  AthleticsSceneManager::GetAthleticBattleType()
{
	 return  athleticBattleType;
}
 

//@耗时巨高啊
void   AthleticsSceneManager::AddHeroicRoleInGroup(PBaseRoleInfo pBaseRoleInfo,bool isPlayerGronp)
{
	if(pBaseRoleInfo==NULL)
    return ;

	switch(pBaseRoleInfo->roleType)
	{
	case  BaseRoleInfo::_BASE_ROLE_PLAYER_TYPE_:
		{
			PPlayerRole pPlayerRole=(PPlayerRole)pBaseRoleInfo->pRoleInfoData;
			if(pPlayerRole!=NULL)
			{
				HeroicRole * pHeroicRole=new HeroicRole();
				pHeroicRole->setRoleType(BaseRoleInfo::_BASE_ROLE_PLAYER_TYPE_);
				pHeroicRole->SetSubObjectID(pPlayerRole->playerID);
				pHeroicRole->setRoleIconID(pPlayerRole->iconID);
				pHeroicRole->setRoleName(pPlayerRole->playerName);
				pHeroicRole->SetFightAtLeft(isPlayerGronp);
				pHeroicRole->setTargetPosition(GetRoleTargetPositon(isPlayerGronp));
				pHeroicRole->InitRole(pPlayerRole->shapeID);
				pHeroicRole->setInitHpValue(pPlayerRole->pCommonRoleAttribute->hpValue);
				pHeroicRole->setInitMpValue(pPlayerRole->pCommonRoleAttribute->mpValue);
				if(isPlayerGronp)
				playGroupHeroicList.push_back(pHeroicRole);
				else
				enemyGroupHeroicList.push_back(pHeroicRole);
				break;
			}
		}
		break;
	case  BaseRoleInfo::_BASE_ROLE_MONSTER_TYPE_:
		{
			PMonsterRole pMonsterRole=(PMonsterRole)pBaseRoleInfo->pRoleInfoData;
			if(pMonsterRole!=NULL)
			{
				HeroicRole * pHeroicRole=new HeroicRole();
				pHeroicRole->setRoleType(BaseRoleInfo::_BASE_ROLE_MONSTER_TYPE_);
				pHeroicRole->SetSubObjectID(pMonsterRole->monsterID);
				pHeroicRole->setRoleIconID(pMonsterRole->iconID);
				pHeroicRole->setRoleName(pMonsterRole->monsterName);
				pHeroicRole->SetFightAtLeft(isPlayerGronp);
				pHeroicRole->setTargetPosition(GetRoleTargetPositon(isPlayerGronp));
				pHeroicRole->InitRole(pMonsterRole->shapeID);
				pHeroicRole->setInitHpValue(pMonsterRole->pCommonRoleAttribute->hpValue);
				pHeroicRole->setInitMpValue(pMonsterRole->pCommonRoleAttribute->mpValue);
				if(isPlayerGronp)
				playGroupHeroicList.push_back(pHeroicRole);
				else
				enemyGroupHeroicList.push_back(pHeroicRole);
				break;
			}
		}
		break;
	default: 
		break;
	}  
}

 

HeroicRole *    AthleticsSceneManager::IsRoleInPlayGroup(RoleUniqeDefine & role)
{
      size_t  vecCount=playGroupHeroicList.size();
	  for(size_t vecIndex=0;vecIndex<vecCount;vecIndex++)
	  {	
		   HeroicRole  * pHeroicRole=playGroupHeroicList.at(vecIndex);
		   int sourceID=pHeroicRole->GetSubObjectID();
		   int roleType=pHeroicRole->getRoleType();
		   if(sourceID==role.sourceID&&roleType==role.unitType)
		   {
			   return pHeroicRole;
		   }
      }
	  return NULL;
}

HeroicRole *    AthleticsSceneManager::IsRoleInEnmeyGroup(RoleUniqeDefine & role)
{
	size_t  vecCount=enemyGroupHeroicList.size();
	for(size_t vecIndex=0;vecIndex<vecCount;vecIndex++)
	{	
		HeroicRole  * pHeroicRole=enemyGroupHeroicList.at(vecIndex);
		if(pHeroicRole->GetSubObjectID()==role.sourceID&&pHeroicRole->getRoleType()==role.unitType)
		{
			return pHeroicRole;
		}
	}
	return NULL;

}

 

//开启禁用层
void   AthleticsSceneManager::ShowAthleticsDisableLayer()
{
	cocos2d::CCNode * pDiableLayer=Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_DISABLE_MARK);
	if(pDiableLayer!=NULL)
	{
		pDiableLayer->setVisible(true);
	}
}

//关闭禁用层
void   AthleticsSceneManager::HideAthleticsDiableLayer()
{
	cocos2d::CCNode * pDiableLayer=Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_DISABLE_MARK);
	if(pDiableLayer!=NULL)
	{
		pDiableLayer->setVisible(false);
	}
}

 

void  AthleticsSceneManager::OnResetAllRoleHPAndMP()
{
	size_t dequeCount=playGroupHeroicList.size();
	FOR_EACH_ELEMENT_BEGIN(dequeCount)
		playGroupHeroicList.at(index)->reSetRoleHPAndMPValue();
	FOR_EACH_ELEMENT_END
	dequeCount=enemyGroupHeroicList.size();
	FOR_EACH_ELEMENT_BEGIN(dequeCount)
		enemyGroupHeroicList.at(index)->reSetRoleHPAndMPValue();
	FOR_EACH_ELEMENT_END 

	if(pAthleticsUIManager)
	{
		pAthleticsUIManager->ResetTeamIconList();
	} 
}

 
float AthleticsSceneManager::GetHPRectWidth()
{ 
	return  hpRectWidth_;
}

float AthleticsSceneManager::GetMPRectWidth()
{
    return  mpRectWidth_;
}

void  AthleticsSceneManager::OnUpdateRoleHPValue()
{
	if(pAthleticsUIManager!=NULL)
	{
		if(leftFightRole_!=NULL&&leftFightRole_->isRoleHPChange())
		{
			pAthleticsUIManager->UpdateRoleHPValue();
		}
		if(rightFightRole_!=NULL&&rightFightRole_->isRoleHPChange())
		{
			pAthleticsUIManager->UpdateRoleHPValue(false);
		}
	}
}


void  AthleticsSceneManager::OnUpdateRoleMPValue()
{
    if(pAthleticsUIManager!=NULL)
	{
		if(leftFightRole_!=NULL&&leftFightRole_->isRoleMPChange())
		{
            pAthleticsUIManager->UpdateRoleMPValue();
		}
	    if(rightFightRole_!=NULL&&rightFightRole_->isRoleMPChange())
		{
		   pAthleticsUIManager->UpdateRoleMPValue(false);
		}
	}
}

 

void  AthleticsSceneManager::Destroy()
{
	//销毁技能池  战斗指令系统  战斗UI管理器  NPC对话框  团战人物信息 各种附加特效  释放加载纹理
	if(m_bIsLayOutUIData)
	{
		m_bIsLayOutUIData=false; 
		leftFightRole_->OnStopAllSkeletonCallBack();
		rightFightRole_->OnStopAllSkeletonCallBack();
		leftFightRole_->stopAllActions();
		rightFightRole_->stopAllActions();

		VARIABLESYSTEM_END_ATHLETICS

		if(BASEOBJECTMANAGER!=NULL)
		{
			BASEOBJECTMANAGER->Destroy();
			delete  BASEOBJECTMANAGER;
		}
		if(ATHLETICSICSYSTEM!=NULL)
		{
			ATHLETICSICSYSTEM->Destroy();
			delete  ATHLETICSICSYSTEM;
		}
		if(	pAthleticsUIManager!=NULL)
		{ 
			pAthleticsUIManager->Destroy();
			delete   pAthleticsUIManager;
			pAthleticsUIManager=NULL;
		}

		if(pNpcTalkView!=NULL)
		{
			pNpcTalkView->removeFromParentAndCleanup(true);
			pNpcTalkView=NULL; 
		}

		//删除团战信息
		size_t  groupCount=playGroupHeroicList.size();
		for (size_t groupIndex=0;groupIndex<groupCount;groupIndex++)
		{
			playGroupHeroicList.at(groupIndex)->Destroy();
			delete  playGroupHeroicList.at(groupIndex);
		}
		playGroupHeroicList.clear();
		leftFightRole_=NULL;

		groupCount=enemyGroupHeroicList.size();
		for (size_t groupIndex=0;groupIndex<groupCount;groupIndex++)
		{
			enemyGroupHeroicList.at(groupIndex)->Destroy();
			delete  enemyGroupHeroicList.at(groupIndex);
		}
		enemyGroupHeroicList.clear();
		rightFightRole_=NULL;

		OnStopScreenShake();
	}
}



void  AthleticsSceneManager::DestroySkillsEffectTextureData()
{   
	//删除Plist和纹理
	std::set<std::string>::const_iterator plist_iter=preLoadPlistTexturePool.begin();
	while(plist_iter!=preLoadPlistTexturePool.end())
	{
		 switch(GetFileTypeFromName(*plist_iter))
		 {
		 case  _PLIST_FILE_TYPE_:
			 _TRACE_UNLOAD_PLIST_((*plist_iter).c_str())
			 cocos2d::CCAnimationCache::sharedAnimationCache()->removeAnimationByName(GetAnimationNameFromPlistOrPng(*plist_iter).c_str());
			 break;
		 case  _IMAGE_FILE_TYPE_:
			 cocos2d::CCAnimationCache::sharedAnimationCache()->removeAnimationByName(GetAnimationNameFromPlistOrPng(*plist_iter).c_str());
			 break;
		 default:
			 break;
		 }  
		++plist_iter;
	}
	preLoadPlistTexturePool.clear();
	DOTATribeApp::get_instance2()->ForceFreeMemory();
} 


//@事件通知接口
void   AthleticsSceneManager::OnCommandHanlder(int EventTypeID,void * ptr)
{
    if(EventTypeID==_TYPED_INPUT_COMMAND_ROLEADMISSION_END_)
	{
       //角色入场动画回调事件  //判断是否强制结束
		if(!isGameOver_)
		{ 
			 admittanceTickCount++;
			 if(admittanceTickCount>=callBackAdmittanceCount)
			 {
				 admittanceTickCount=0;
				 callBackAdmittanceCount=0;
				 NpcTalkManagerHandler(_ATHLETICS_ADMITTANCE_FINISH_CALL_EVENT_);
				 return ;
			 }
		} 
	}
}
 
void  AthleticsSceneManager::BaseDialogCallBackHandler(int eventType,void * ptr)
{
	char  npcTalkState=-1;
	bool  isError=false;
	if(pNpcTalkView!=NULL)
	{ 
		isError=pNpcTalkView->ToNextPage(npcTalkState);
		if(!isError)
		{
		  switch(npcTalkState)
		  {
		  case NpcTalkView::_BEFOR_NPCTALK_TYPE_:
			  {
				  SetAthleticsNpcTalkLayerVisible(false);
				  ATHLETICSICSYSTEM->OnCommandHandler(_TYPED_INPUT_COMMAND_RESUME_ATHLETICSINSTRUCTION_);
				  break;
			  }
		  case NpcTalkView::_WIN_NPCTALK_TYPE_:
		  case NpcTalkView::_FAIL_NPCTALK_TYPE_:
			  {
				  SetAthleticsNpcTalkLayerVisible(false);
				  PostGameOverUINofitication();
				  break;
			  }
		  default:
			  break;
		  }
		}
	} 
}
 
 
 
 

cocos2d::CCNode *  AthleticsSceneManager::GetAthleticsRootLayer()
{
	return Athletics_UI_Root();
	 
}

cocos2d::CCNode *  AthleticsSceneManager::GetAthleticsDiableMark()
{
	return Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_DISABLE_MARK);
  
}
 
cocos2d::CCNode *  AthleticsSceneManager::GetAthleticsNpcTalkLayer()
{
	return Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_NPC_TALK_VIEW);
}


//@设置NPC对话层可视状态
void   AthleticsSceneManager::SetAthleticsNpcTalkLayerVisible(bool isVisible)
{
	if(GetAthleticsNpcTalkLayer()!=NULL)
	{
		if(pNpcTalkView!=NULL)
		pNpcTalkView->setVisible(isVisible);
		GetAthleticsNpcTalkLayer()->setVisible(isVisible);
	}
}


//@获得角色的目标攻击位置
cocos2d::CCPoint  AthleticsSceneManager::GetRoleTargetPositon(bool isLeft/* =true */)
{
	cocos2d::CCNode * targetPosNode=NULL;
	if(isLeft)
	{
		targetPosNode=Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_LEFT_TARGET_CONFIG);
	}
	else
	{
		targetPosNode=Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_RIGHT_TARGET_CONFIG);
	}

	if(targetPosNode!=NULL)
	{
		return targetPosNode->getPosition();
	}
	return CCPointZero;
}
 


//获取左战斗对象
HeroicRole *  AthleticsSceneManager::GetLeftFightRole()
{
	return  leftFightRole_;
}

//获取右边战斗对象
HeroicRole *  AthleticsSceneManager::GetRightFightRole()
{
	return  rightFightRole_;
}

//获取主控者的对象
HeroicRole *  AthleticsSceneManager::GetExecuteRole(bool isLeft)
{
	if(isLeft)
	return leftFightRole_;
	else
	return rightFightRole_;
}



bool   AthleticsSceneManager::IsGameOver()
{
	return  isGameOver_;
}


void  AthleticsSceneManager::SetGameOver()
{   
	////游戏结束
	if(isGameOver_)
	return ;

	isGameOver_=true;
	if(m_bIsTriggerVIPSkip)
	{
		NpcTalkManagerHandler(_ATHLETICS_GAME_OVER_CALL_EVENT_);
		return ;
	}

	//强制清理组队头像队列
	UnActiveAllTeamIcon(!isBattleWin);
	 
	//关闭激活角色所有回调和Buffer
    StopActiveRoleAllAction();
	 
	OnPlayWinAnimation();
	 
	if(!isRePlayAthletics_)
	NpcTalkManagerHandler(_ATHLETICS_GAME_OVER_CALL_EVENT_);
  
    //播放结果界面
	//这个需要做部分资源施放 to do for release resource
}

void  AthleticsSceneManager::OnPlayWinAnimation()
{ 
	if(isBattleWin)
	{
		if(leftFightRole_!=NULL)
		leftFightRole_->onPlayeWinAnimation();
	}
	else
	{
		if(rightFightRole_!=NULL)
		rightFightRole_->onPlayeWinAnimation();
	} 
}
 
void  AthleticsSceneManager::AnalyseAthleticsResult()
{ 
	PRoleResultData pRoleResultData=NULL;
	if(athleticWatchType==_ATHLECTICS_SELFT_WATCH_TYPE_)
	{    
		if(pAthleticsUIManager->GetIsPlayGroupInFirstDeque())
		{   
			if(!pAthleticResultData->firstBattleResultVector.empty())
				pRoleResultData=pAthleticResultData->firstBattleResultVector.at(0);
		}
		else
		{
			if(!pAthleticResultData->secondBattleResultVector.empty())
				pRoleResultData=pAthleticResultData->secondBattleResultVector.at(0);
		} 
	}
	else if(athleticWatchType==_ATHLECTICS_OTHER_WATCH_TYPE_)
	{  
		if(!pAthleticResultData->firstBattleResultVector.empty())
			pRoleResultData=pAthleticResultData->firstBattleResultVector.at(0);
	} 
	if(pRoleResultData!=NULL)
	{
		switch(pRoleResultData->winType)
		{
		case  _ATHLETICS_RESULT_WIN_TYPE_:
			{
				isBattleWin=true;
				break;
			}
		default: 
			break;
		} 
	} 
}

 

//@重播战斗
void  AthleticsSceneManager::OnRePlayAthleticsGame()
{  
	//恢复战斗音量速度
	VARIABLESYSTEM_SET_PLAY_MODE(AthleticsSpeed)
	//之后会进行轮次切换不需要施放资源   从而加快重播速度  Very Important

	isTryPlayNpcTack=false;

	m_bIsTriggerVIPSkip=false;
	 
	leftFightRole_->OnStopAllSkeletonCallBack();
	rightFightRole_->OnStopAllSkeletonCallBack();
	leftFightRole_->stopAllActions();
	rightFightRole_->stopAllActions(); 
	leftFightRole_->setVisible(false);
	rightFightRole_->setVisible(false);
	 
	if(BASEOBJECTMANAGER!=NULL)
	{
		BASEOBJECTMANAGER->Destroy();
	}
 

	leftFightRole_->OnStopAllEffect();
	rightFightRole_->OnStopAllEffect();
	leftFightRole_->changeToIdleAnimation();
	rightFightRole_->changeToIdleAnimation();
	 
	leftFightRole_->setFlipX(false); 
	rightFightRole_->setFlipX();
	leftFightRole_->forceMoveToInitPosition();
	rightFightRole_->forceMoveToInitPosition();
	 
	isRePlayAthletics_=true;
  
	//关闭结果面板
	HideAthleticsDiableLayer();
    EVENTSYSTEM->PushEvent(_TYPE_EVENT_HIDE_ATHLETICSRESULTWINDOW_);
 
    //初始化指令系统状态  不需要清理
	
	 curPlayGroupRoleID=-1;			//当前玩家组角色ID
	 curPlayGroupRoleType=0;		//当前战斗角色类型

	 curEnmeyGroupRoleID=-1;		//当前敌方组角色ID
	 curEnmeyGroupRoleType=0;		//当前战斗角色类型

	 isPlayGroupRoleChange=false;
	 isEnemyGroupRoleChange=false; 
	  
	 /*
	 重置所有人的血和蓝
	 */
	 OnResetAllRoleHPAndMP();

	 AthleticsInstructionSystem::get_instance2()->OnCommandHandler(_TYPEF_INPUT_COMMAND_REPLAY_ATHLETICSINSTRUCTION_);

	 isGameOver_=false;						//设置游戏全局属性
 
 
	 if(isRePlayAthletics_&&pAthleticsUIManager)
	 {
		//显示重播和退出按钮   不再显示战斗结果  
		pAthleticsUIManager->ShowNormalAllLayoutBtn(); 
	 }
	
}
 

void  AthleticsSceneManager::OnUpdateRoleTickBuffer()
{
	if(leftFightRole_!=NULL)
	{
		leftFightRole_->Tick();
	}
	if(rightFightRole_!=NULL)
	{
		rightFightRole_->Tick();
	} 
}


//@战斗变速实现
//#变换顺序为1->2->3->1倍
void  AthleticsSceneManager::OnChangeAthleticsSpeed()
{ 
	if (AthleticsSpeed==NormalSpeed)
		AthleticsSpeed=NormalSpeedx2;
	else if (AthleticsSpeed==NormalSpeedx2)
		AthleticsSpeed=NormalSpeedx3;
	else
		AthleticsSpeed=NormalSpeed;

	VARIABLESYSTEM_SET_PLAY_MODE(AthleticsSpeed)
	UpdateAthleticsSystemSpeed(AthleticsSpeed); 
	UpdateAthleticSpeedUI();
}	


void  AthleticsSceneManager::UpdateAthleticsSystemSpeed(float athleticsSpeed)
{
	BASEOBJECTMANAGER->SetSpeedScale(athleticsSpeed);
	if (leftFightRole_)
	{
		leftFightRole_->setAnimationTimaScale(athleticsSpeed);
		leftFightRole_->SetRoleEffectAnimationSpeedScale(athleticsSpeed);
	}
 	if (rightFightRole_)
	{
		rightFightRole_->setAnimationTimaScale(athleticsSpeed);
		rightFightRole_->SetRoleEffectAnimationSpeedScale(athleticsSpeed);
	}
}
 

void  AthleticsSceneManager::UpdateAthleticSpeedUI()
{
    if(pAthleticsUIManager!=NULL)
	{
	   VARIABLESYSTEM_SET_PLAY_MODE(AthleticsSpeed)
	   pAthleticsUIManager->UpdateAthleticSpeedBtnUI();
	}
}



void  AthleticsSceneManager::PostGameOverUINofitication()  
{
	if(isGameOver_)
	{ 
		if(m_bIsTriggerVIPSkip)
		{
			m_bIsTriggerVIPSkip=false;
			CallBackPlayResultUI();
			return ;
		}
		cocos2d::CCDelayTime * delayTime=cocos2d::CCDelayTime::create(m_fResultWinDelayTime/AthleticsSpeed);
		if(delayTime!=NULL)
		{
			cocos2d::CCCallFunc  * callBackFunc=cocos2d::CCCallFunc::create(this,callfunc_selector(AthleticsSceneManager::CallBackPlayResultUI));
			if(callBackFunc!=NULL)
			{ 
				cocos2d::CCAction * resultSequence=cocos2d::CCSequence::createWithTwoActions(delayTime,callBackFunc);
				Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_ICON)->runAction(resultSequence);
			}
		} 
	}
}
  
//////////////////////////////////////////////////////////////////////////

void  AthleticsSceneManager::OnPlayScreenShake(int compositeEffectID,int shakeItemID)
{  
	 OnStopScreenShake();
	 CommonEffect * pScreenShakeEffect=ScreenShakeEffect::CreateScreenShakeEffect(compositeEffectID,shakeItemID);
	 if(pScreenShakeEffect!=NULL)
	 {
		  m_shakeEffectList.insert(std::multimap<int,CommonEffect *>::value_type(pScreenShakeEffect->GetCompositeEffectID(),pScreenShakeEffect));
	 } 
}


void  AthleticsSceneManager::OnSetScreenShakeEffectSpeedScale()
{
	std::multimap<int,CommonEffect *>::iterator  shake_iter=m_shakeEffectList.begin();
	while(shake_iter!=m_shakeEffectList.end())
	{
		if(shake_iter->second!=NULL&&shake_iter->second->IsValid())
		{  
		    shake_iter->second->SetAnimationSpeedScale(AthleticsSpeed);
		}
		shake_iter++;
	}
}

//@关闭特效
void  AthleticsSceneManager::OnStopScreenShake(int compositeEffectID)
{
	if(compositeEffectID<0)
	{
		//remove ALL
		std::multimap<int,CommonEffect *>::iterator shake_effect_Iter=m_shakeEffectList.begin();
		while(shake_effect_Iter!=m_shakeEffectList.end())
		{
			if(shake_effect_Iter->second!=NULL)
				shake_effect_Iter->second->Destroy();
			delete shake_effect_Iter->second;
			m_shakeEffectList.erase(shake_effect_Iter++);
		}
		m_shakeEffectList.clear();
	}
	else
	{
		std::multimap<int,CommonEffect *>::iterator shake_effect_Iter=m_shakeEffectList.find(compositeEffectID);
		while(shake_effect_Iter!=m_shakeEffectList.end())
		{
			if(shake_effect_Iter->second!=NULL)
				shake_effect_Iter->second->Destroy();
			delete shake_effect_Iter->second;
			m_shakeEffectList.erase(shake_effect_Iter++);
		}
	}

}
 
void  AthleticsSceneManager::UpdateScreenShakeEffect()
{ 
	std::multimap<int,CommonEffect *>::iterator  shake_iter=m_shakeEffectList.begin();
	while(shake_iter!=m_shakeEffectList.end())
	{
		if(shake_iter->second!=NULL)
		{ 
			if(shake_iter->second->IsValid())
			{
				shake_iter->second->Tick();
			}
			else
			{
				shake_iter->second->Destroy();
				delete shake_iter->second; 
				m_shakeEffectList.erase(shake_iter++);
				continue;
			}
		}
		shake_iter++;
	}
}

void  AthleticsSceneManager::SetSycLoadTexurePlistPool(std::set<std::string> & texturePlistPool)
{
	preLoadPlistTexturePool=texturePlistPool;
}


/*
单轮战斗即将结束通知
*/
void    AthleticsSceneManager::PostCurRoundWillDid()
{  
	if(leftFightRole_&&leftFightRole_->hadPlayedDeadAnimation())
	{
		UpdateTeamIcon(true);
	}
	if(rightFightRole_&&rightFightRole_->hadPlayedDeadAnimation())
	{
		UpdateTeamIcon(false);
	}
}
 
/*
更新组队更新
*/
void    AthleticsSceneManager::UpdateTeamIcon(bool isPlayerGroup)
{
	if(pAthleticsUIManager)
	{
		 pAthleticsUIManager->UpdateTeamIconList(isPlayerGroup);
	}
}


void   AthleticsSceneManager::UnActiveAllTeamIcon(bool isPlayerGroup)
{
	if(pAthleticsUIManager)
	{
		pAthleticsUIManager->UnActiveAllTeamIcon(isPlayerGroup);
	}
}
  
 
 
/*
是否触发VIP跳过战斗事件
*/
bool    AthleticsSceneManager::IsTriggerVIPSkipHandler()
{   
	if(!isRePlayAthletics_)
	{
		//DO VIP SKip Handler
		 VipSkipAthleicsHandler();	 
		isRePlayAthletics_=true;
		return true;
	}
	return false;
}
 
 
/*
判断当前VIP等级是否可以跳过此战斗
*/
bool  AthleticsSceneManager::IsVIPCanSkipAthletics()
{
	//to do
	int SkipNeedLevel=AthleticProcedureDataHandler::get_instance2()->getSkipAthleticVIPLevelByType(athleticBattleType);
	if(RoleInfoDataHandler::get_instance2()->m_pRIData->vipLevel_>=SkipNeedLevel)
	{
		return true;
	}
	return false;
}


/*
VIP跳过战斗处理
*/
void  AthleticsSceneManager::VipSkipAthleicsHandler()
{
	//to do 
	m_bIsTriggerVIPSkip=true;
	StopActiveRoleAllAction();
	AthleticsInstructionSystem::get_instance2()->SetInstructionSystemCurState(AthleticsInstructionSystem::_INSTRUCTIONSYSTRM_INTERRUPTATHLETICS_TYPE_);
}


void  AthleticsSceneManager::StopActiveRoleAllAction()
{
	if(leftFightRole_&&rightFightRole_)
	{
		leftFightRole_->OnStopAllSkeletonCallBack();
		rightFightRole_->OnStopAllSkeletonCallBack();
		leftFightRole_->stopAllActions();
		leftFightRole_->setRoleNoneState();
		rightFightRole_->stopAllActions();
		rightFightRole_->setRoleNoneState();
	} 
}