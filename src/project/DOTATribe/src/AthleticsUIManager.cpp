//Name：AthleticsUIManager
//Function：战斗UI管理器
//Author:	Johny

#include   <cocos2d.h>
#include   "../include/AthleticsUIManager.h"
#include "../include/AthleticConfig.h"


#include   "../include/AthleticsWindow.h"
#include   "../include/AthleticsSceneManager.h"
#include   "../include/EngineSystem.h"
#include   "../include/AnimationFileDataManager.h"
#include   "../include/FrameAnimateDataManager.h"
#include   "../include/NFControlsManager.h"
#include   "../include/CompositeEffectDataManager.h"
#include   "../include/NFCCParicelEffectFactory.h"
#include   "../include/AthleticProcedureDataHandler.h"
 
#include   <list>
#include   <map>



using  namespace  cobra_win;
USING_NS_CC;
using namespace std;


AthleticsUIManager::AthleticsUIManager()
{
	m_bVIPLayOut=false;

    m_bloodWidth_=AthleticsSceneManager::get_instance2()->GetHPRectWidth();
    m_blueWidth_=AthleticsSceneManager::get_instance2()->GetMPRectWidth();
 
	sceneID=0;				 
	sceneName="";	
	sceneEffectList.clear();

	isPlayerGroupInFirstDeque=false;

	pLeftTeamIconProgress=NULL;

	pRightTeamIconProgress=NULL;

	memset(tmpStr,0,sizeof(tmpStr));
  
}

AthleticsUIManager::~AthleticsUIManager()
{

}

void   AthleticsUIManager::Init()
{
	m_bVIPLayOut=false;
   sceneID=0;				 
   sceneName="";	
   pPreAthleticsData_=NULL; 
   pAthleticsMapInfo_=NULL;
 
   firstAthleticsDeque.clear();
   secondAthleticsDeque.clear();
   sceneEffectList.clear();
   totalAthleticsTurnCount=0;
   curAthleticsTurnIndex=0;
   pSkillPanelLayer=NULL;
   pLeftAthleticSkillPanel=NULL;
   pRightAthleticSkillPanel=NULL;
 
 
   memset(tmpStr,0,sizeof(tmpStr));
}

void   AthleticsUIManager::Tick()
{
   
}  

void  AthleticsUIManager::Destroy()
{
    DestroySceneUI();
}


//@加载战斗地图信息数据包
void   AthleticsUIManager::LoadAthleticsMapInfoUIData(PAthleticsMapInfo pAthleticsMapInfo)
{  
	if(pAthleticsMapInfo)
	{
		pAthleticsMapInfo_=pAthleticsMapInfo;
		switch(pAthleticsMapInfo_->battleType)
		{
		case  _ATHLETICS_CUSTOMS_BATTLE_TYPE_:
			{
				PCustomsMapInfo pCustomsMapInfo=(PCustomsMapInfo)pAthleticsMapInfo_->mapInfoData;
				if(pCustomsMapInfo)
				{
					sceneID=pCustomsMapInfo->sceneID;
					sceneName=pCustomsMapInfo->sceneName;
				}
				break;
			}
		case  _ATHLETICS_ARENA_BATTLE_TYPE_:
			{
				PArenaMapInfo pArenaMapInfo = (PArenaMapInfo)pAthleticsMapInfo_->mapInfoData;
				if(pArenaMapInfo)
				{
					sceneID = pArenaMapInfo->sceneID;
				}
				break;
			}
		case _ATHLETICS_CLIMPTOWER_BATTLE_TYPE_:
			{
				PTowerMapInfo pTowerMapInfo = (PTowerMapInfo)pAthleticsMapInfo_->mapInfoData;
				if(pTowerMapInfo)
				{
					sceneID = pTowerMapInfo->sceneID;
					char temp[4] = {0};
					sprintf(temp, "%d", pTowerMapInfo->floor);
					sceneName.assign(temp);
				}
				break;
			}
		case _ATHLETICS_TEAM_BATTLE_TYPE_:
			{
				PTeamMapInfo pTeamMapInfo = (PTeamMapInfo)pAthleticsMapInfo_->mapInfoData;
				if(pTeamMapInfo)
				{
					sceneID=pTeamMapInfo->sceneID;
					sceneName=pTeamMapInfo->sceneName;
				}
				break;
			}
		case _ATHLETICS_SERVANT_BATTLE_TYPE_:
			{
				PServantMapInfo pServantMapInfo = (PServantMapInfo)pAthleticsMapInfo_->mapInfoData;
				if(pServantMapInfo)
				{
					sceneID = pServantMapInfo->sceneID;
					sceneName = pServantMapInfo->sceneName;
				}
				break;
			}
		case  _ATHLETICS_FRIEND_BATTLE_TYPE_:
			{
				PArenaMapInfo pArenaMapInfo = (PArenaMapInfo)pAthleticsMapInfo_->mapInfoData;
				if(pArenaMapInfo)
				{
					sceneID=pArenaMapInfo->sceneID;
				}
				break;
			}
		case _ATHLETICS_KUANGDONG_BATTLE_TYPE_:
			{
				PMiningMapInfo pMiningMapInfo = (PMiningMapInfo)pAthleticsMapInfo_->mapInfoData;
				if(pMiningMapInfo)
				{
					sceneID=pMiningMapInfo->sceneID;
					sceneName=pMiningMapInfo->sceneName;
				}
				break;
			}
		case _ATHLETICS_CHALLENEGE_HEROSOUL_TYPE_:
			{
				PCustomsMapInfo pCustomsMapInfo=(PCustomsMapInfo)pAthleticsMapInfo_->mapInfoData;
				if(pCustomsMapInfo)
				{
					sceneID=pCustomsMapInfo->sceneID;
					sceneName=pCustomsMapInfo->sceneName;
				}
				break;
			}  
		case _ATHLETICS_BOSSSCORE_BATTLE_TYPE_:
			{
				PBossScoreMapInfo pBossScoreMapInfo = (PBossScoreMapInfo)pAthleticsMapInfo->mapInfoData;
				if(pBossScoreMapInfo)
				{
					sceneID = pBossScoreMapInfo->sceneID;
					sceneName = pBossScoreMapInfo->sceneName;
				}
			}break;
		case _ATHLETICS_KUANGDONG_HUNTLIEREN_TYPE_:
			{
				PCustomsMapInfo pCustomsMapInfo=(PCustomsMapInfo)pAthleticsMapInfo_->mapInfoData;
				if(pCustomsMapInfo)
				{
					sceneID=pCustomsMapInfo->sceneID;
					sceneName=pCustomsMapInfo->sceneName;
				}
			}break;
		default: 
			break;
		}

	}
}

//加载战前人物信息包
void   AthleticsUIManager::LoadPreAthleticsUIData(PPreAthleticsData pPreAthleticsData)
{
    if(pPreAthleticsData_!=pPreAthleticsData)
	{
       pPreAthleticsData_=pPreAthleticsData;
	   if(pPreAthleticsData_!=NULL)
	   {
		   totalAthleticsTurnCount=pPreAthleticsData_->firstDequeCount;
		   firstAthleticsDeque=pPreAthleticsData->firstdequeRoleVector;
		   secondAthleticsDeque=pPreAthleticsData->seconddequeRoleVector;
	   }
	   //检测当前玩家所在队列
	   CheckPlayGroupIsInFirstDeque();
	}
}
 
void   AthleticsUIManager::CheckPlayGroupIsInFirstDeque()
{	

	int playInstanceID=0;
	if(RoleInfoDataHandler::get_instance2()!=NULL&&RoleInfoDataHandler::get_instance2()->m_pRIData!=NULL)
	{	
		playInstanceID=RoleInfoDataHandler::get_instance2()->m_pRIData->instanceId_;
	}
	totalAthleticsTurnCount=pPreAthleticsData_->firstDequeCount;
	for(size_t dequeIndex=0;dequeIndex<(size_t)totalAthleticsTurnCount;dequeIndex++)
	{
		PBaseRoleInfo pBaseRoleInfo=firstAthleticsDeque.at(dequeIndex);
		if(pBaseRoleInfo!=NULL&&pBaseRoleInfo->roleType==BaseRoleInfo::_BASE_ROLE_PLAYER_TYPE_)
		{
			PPlayerRole pPlayRoleInfo=(PPlayerRole)pBaseRoleInfo->pRoleInfoData;
			if(pPlayRoleInfo!=NULL/*&&pPlayRoleInfo->playerID==playInstanceID*/)
			{
				isPlayerGroupInFirstDeque=true;
				return ;
			}
		}
	}
	if( ATHLETICPROCEDUREDATA->isUsingLocalDataReplace )
	{
		isPlayerGroupInFirstDeque = false;
		return ;
	}  
	if(!isPlayerGroupInFirstDeque)
	{
		//检测玩家是否在第二组队列中
		bool isFindPlayerInSecondDeque=false;
		totalAthleticsTurnCount=pPreAthleticsData_->secondDequeCount;
		FOR_EACH_ATHLETICSUNIT_BEGIN(totalAthleticsTurnCount)
			PBaseRoleInfo pBaseRoleInfo=secondAthleticsDeque.at(athleticsIndex);
		    if(pBaseRoleInfo!=NULL&&pBaseRoleInfo->roleType==BaseRoleInfo::_BASE_ROLE_PLAYER_TYPE_)
		    {
				PPlayerRole pPlayRoleInfo=(PPlayerRole)pBaseRoleInfo->pRoleInfoData;
				if(pPlayRoleInfo!=NULL/*&&pPlayRoleInfo->playerID==playInstanceID*/)
				{ 
					isFindPlayerInSecondDeque=true;
					break ;
				}
		    }
		FOR_EACH_ATHLETICSUNIT_END 
		if(!isFindPlayerInSecondDeque)
		{ 
			isPlayerGroupInFirstDeque=true;
			AthleticsSceneManager::get_instance2()->SetAthleticsWatchType(AthleticsSceneManager::_ATHLECTICS_OTHER_WATCH_TYPE_);
		}
		return ;
	}
}

bool   AthleticsUIManager::GetIsPlayGroupInFirstDeque()
{
	return isPlayerGroupInFirstDeque;
}


void   AthleticsUIManager::ReInitRectImage(bool isLeftGroup)
{
	if(isLeftGroup)
	{  
		cocos2d::CCSprite * leftBloodSprite=(cocos2d::CCSprite *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_LEFT_HP_BG);
		if(leftBloodSprite!=NULL)
		leftBloodSprite->setTextureRect(CCRectMake(0,0,m_bloodWidth_,leftBloodSprite->getContentSize().height));
		cocos2d::CCSprite * leftBlueSprite=(cocos2d::CCSprite *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_LEFT_MP_BG);
		if(leftBlueSprite!=NULL)
		leftBlueSprite->setTextureRect(CCRectMake(0,0,m_blueWidth_,leftBlueSprite->getContentSize().height));
	}
	else
	{
		cocos2d::CCSprite * rightBloodSprite=(cocos2d::CCSprite *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_RIGHT_HP_BG);
		if(rightBloodSprite!=NULL)
		rightBloodSprite->setTextureRect(CCRectMake(0,0,m_bloodWidth_,rightBloodSprite->getContentSize().height)); 
		cocos2d::CCSprite * rightBlueSprite=(cocos2d::CCSprite *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_RIGHT_MP_BG);
		if(rightBlueSprite!=NULL)
		rightBlueSprite->setTextureRect(CCRectMake(0,0,m_blueWidth_,rightBlueSprite->getContentSize().height));
	}
	
}



void   AthleticsUIManager::InitSceneUI()
{  
	ReInitRectImage();
	   
	//背景图片
	cocos2d::CCSprite * sceneBG=(cocos2d::CCSprite *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_BG);
	SceneInfoData * pSceneData =SceneInfoDataManager::get_instance2()->GetCustomPassDataByID(sceneID);
	if(pSceneData!=NULL)
	{
		if(sceneBG!=NULL)
		sceneBG->setProperty("File",pSceneData->mSceneInfoPicture);
	}

	//场景名称
 
	if(pAthleticsMapInfo_!=NULL)
	{
		cocos2d::CCLabelTTF * pSceneName=(cocos2d::CCLabelTTF *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_ICON_NAME);
		if(pAthleticsMapInfo_->battleType==_ATHLETICS_ARENA_BATTLE_TYPE_ || pAthleticsMapInfo_->battleType==_ATHLETICS_FRIEND_BATTLE_TYPE_)
		{  
			cocos2d::CCSprite * precordMark=(cocos2d::CCLabelTTF *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_NAME_BG);
			if(precordMark!=NULL)
			precordMark->setVisible(false);
		    if(pSceneName!=NULL) 
			pSceneName->setVisible(false);
		}
		else
		{ 
			if(pSceneName!=NULL)
			{
				pSceneName->setString(sceneName.c_str());
			}
		}
	}
  
 
	//初始化场景特效
	InitSceneUIEffect();

	//加载技能面板
    InitRolePropertyUI();

    //更新角色属性UI
	UpdateAthleticRoleInfoUI();
 
}

  
void	AthleticsUIManager::InitSceneUIEffect()
{ 
	SceneInfoData * pSceneData =SceneInfoDataManager::get_instance2()->GetCustomPassDataByID(sceneID);
	if(pSceneData!=NULL)
	{ 
	 	PlaySceneEffect(pSceneData->mEffectId1);
		PlaySceneEffect(pSceneData->mEffectId2);
		PlaySceneEffect(pSceneData->mEffectId3);
		//播放场景音乐 
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOUND_PLAY_,_to_event_param_(pSceneData->mSoundID)); 
	} 
}

void  AthleticsUIManager::PlaySceneEffect(int sceneEffectID)
{
	if(sceneEffectID!=-1)
	{ 
		CompositeEffectData * pCompositeEffect=CompositeEffectDataManager::get_instance2()->GetCompositeEffectDataByID(sceneEffectID);
		if(pCompositeEffect!=NULL)
		{
			size_t  effectVecCount=pCompositeEffect->compositeEffectVec.size();
			int   effectType=0;
			int   effectID=0;
			FOR_EACH_ELEMENT_BEGIN(effectVecCount)
			effectType=pCompositeEffect->compositeEffectVec.at(index).effectType;
			effectID=pCompositeEffect->compositeEffectVec.at(index).effectID;
			switch(effectType)
			{
			case _CompositeEffect_FrameAniamteEffect_Type_:
				PlaySceneFrameEffect(effectID);
				break;
			case _CompositeEffect_ParticleEffect_Type_:
				PlaySceneParticelEffect(effectID);
				break;
			default:
				break;
			} 
			FOR_EACH_ELEMENT_END
		}
	} 
}


 
cocos2d::CCNode *   AthleticsUIManager::GetAthleticsRootLayer()
{
	return Athletics_UI_Root();
}

  
void AthleticsUIManager::PlaySceneFrameEffect(int sceneFrameEffectID)
{
	if(sceneFrameEffectID!=-1)
	{     
		cocos2d::CCSprite * pEffectNode=NULL;
		FrameAnimateData * pFramAnimationData = FrameAnimateDataManager::get_instance2()->GetFrameAnimateDataByID(sceneFrameEffectID);
		if (pFramAnimationData)
		{	
			AnimationFileData *  pAnimationFileData=AnimationFileDataManager::get_instance2()->GetAnimationByIdx(pFramAnimationData->frameAnimateEffectAnimationID);
			cocos2d::CCAnimation * pAnimation=EngineSystem::get_instance2()->GetAnimtionByName(pAnimationFileData->mAnimationName);
			if(pAnimation!=NULL)
			{
				pEffectNode=cocos2d::CCSprite::create();
				if(pEffectNode!=NULL)
				{     
					pEffectNode->setScale(pAnimationFileData->mAnimationScale);
					//设置相对坐标位置
					pEffectNode->setPositionX(cocos2d::CCDirector::sharedDirector()->getWinSize().width/2 + pFramAnimationData->frameAnimateEffectXOffSet);
					pEffectNode->setPositionY(cocos2d::CCDirector::sharedDirector()->getWinSize().height/2 + pFramAnimationData->frameAnimateEffectYOffSet);

					CCAnimationEffect   *  pAnimationEffect=CCAnimationEffect::create(pEffectNode,pAnimation);
					if(pAnimationEffect!=NULL)
					{ 
						pAnimationEffect->setSpeedScale(ATHLETICSSCENEMANAGER->AthleticsSpeed);
						CCNode* pNode = GetAthleticsRootLayer();
						pNode->addChild(pEffectNode,pFramAnimationData->frameAnimateEffectZOrder);
						cocos2d::CCRepeatForever * pforEver=cocos2d::CCRepeatForever::create(pAnimationEffect);
						pEffectNode->runAction(pforEver);
						AddScenceEffectList(pEffectNode);
					}			
				} 
			}
		}
	} 
}

void   AthleticsUIManager::PlaySceneParticelEffect(int sceneParticleEffectID)
{ 
	AddScenceEffectList(NFCParticelEffectCreate(GetAthleticsRootLayer(),sceneParticleEffectID,1));
}



void	AthleticsUIManager::AddScenceEffectList(cocos2d::CCNode * pSceneEffect)
{
	if(pSceneEffect!=NULL)
	{
		sceneEffectList.push_back(pSceneEffect);
	}
}

/*
销毁角色属性UI
*/
void   AthleticsUIManager::DestroySceneUI()
{
      if(pLeftAthleticSkillPanel!=NULL)
	  {
		   pLeftAthleticSkillPanel->removeFromParentAndCleanup(true);
		   pLeftAthleticSkillPanel=NULL;
	  }
	 
	  if(pRightAthleticSkillPanel!=NULL)
	  {
		  pRightAthleticSkillPanel->removeFromParentAndCleanup(true);
		  pRightAthleticSkillPanel=NULL;
	  }

	  if(pSkillPanelLayer!=NULL)
	  {  
		  pSkillPanelLayer->removeFromParentAndCleanup(true);
		  pSkillPanelLayer=NULL;
	  }
	 
	  if(!sceneEffectList.empty())
	  {
		  size_t effectCount=sceneEffectList.size();
		  FOR_EACH_ELEMENT_BEGIN(effectCount)
			 sceneEffectList.at(index)->stopAllActions();
             sceneEffectList.at(index)->removeFromParentAndCleanup(true);
		  FOR_EACH_ELEMENT_END
		  sceneEffectList.clear();
	  } 
} 

/*
	分析左右战队列人物 显示组队人员
	*/
void   AthleticsUIManager::AnlayseTeamRoleNumber(int playGroupNum,int enemGroupNum)
{
	if(playGroupNum>1)
	{
		cocos2d::CCNode * pLeftTeamIconConfig=(cocos2d::CCNode *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_LEFT_TEAM);
		pLeftTeamIconProgress=CTeamIconProgress::createTeamIconProgress(ResourceIDDataManager::get_instance2()->getDataByID(_LITTER_BOY_LIGHT_),
		ResourceIDDataManager::get_instance2()->getDataByID(_LITTER_BOY_GRAP_),10.0f,true,playGroupNum);
		pLeftTeamIconProgress->setPosition(pLeftTeamIconConfig->getPosition());
		GetAthleticsRootLayer()->addChild(pLeftTeamIconProgress,pLeftTeamIconConfig->getZOrder());
	}
	if(enemGroupNum>1)
	{
		cocos2d::CCNode * pRightTeamIconConfig=(cocos2d::CCNode *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_RIGHT_TEAM);
		pRightTeamIconProgress=CTeamIconProgress::createTeamIconProgress(ResourceIDDataManager::get_instance2()->getDataByID(_LITTER_BOY_LIGHT_),
			ResourceIDDataManager::get_instance2()->getDataByID(_LITTER_BOY_GRAP_),10.0f,false,enemGroupNum);
		pRightTeamIconProgress->setPosition(pRightTeamIconConfig->getPosition());
		GetAthleticsRootLayer()->addChild(pRightTeamIconProgress,pRightTeamIconConfig->getZOrder());
	} 
}



 
/*
     根据当前的轮次 更新场景角色属性UI
*/
void   AthleticsUIManager::UpdateAthleticRoleInfoUI()
{
	//获得当前的轮次索引的左右角色信息
	UpdateRoleInfoData();			//更新玩家组
	UpdateRoleInfoData(false);		//更新对方组
}



/*
显示VIPLayout  Speed Exit
*/
void  AthleticsUIManager::ShowVIPLayouBtn()
{
	m_bVIPLayOut=true; 
	cocos2d::CCMenuItem * pRePlayBtn=(cocos2d::CCMenuItem *)Athletics_BTN_Node(AthleticsWindow::ATHLETICS_UI_REPLAY_BTN);
	cocos2d::CCMenuItem * pSpeedBtn=(cocos2d::CCMenuItem *)Athletics_BTN_Node(AthleticsWindow::ATHLETICS_UI_SPEED_BTN);
	cocos2d::CCMenuItem * pExitBtn=(cocos2d::CCMenuItem *)Athletics_BTN_Node(AthleticsWindow::ATHLETICS_UI_EXIT_BTN);
	cocos2d::CCNode * pVipLayOff=Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_VIP_SKIP_CONFIG);
	pRePlayBtn->setPositionX(pRePlayBtn->getPositionX()-pVipLayOff->getPositionX());
	pSpeedBtn->setPositionX(pSpeedBtn->getPositionX()-pVipLayOff->getPositionX());
	pExitBtn->setPositionX(pExitBtn->getPositionX()-pVipLayOff->getPositionX());
	Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_EXIT_BTN)->setVisible(true);

}

/*
显示Replay Speed Exit For Normal
*/
void  AthleticsUIManager::ShowNormalAllLayoutBtn()
{ 
	if(m_bVIPLayOut&&!Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_REPLAY_BTN)->isVisible())
	{
		cocos2d::CCMenuItem * pRePlayBtn=(cocos2d::CCMenuItem *)Athletics_BTN_Node(AthleticsWindow::ATHLETICS_UI_REPLAY_BTN);
		cocos2d::CCMenuItem * pSpeedBtn=(cocos2d::CCMenuItem *)Athletics_BTN_Node(AthleticsWindow::ATHLETICS_UI_SPEED_BTN);
		cocos2d::CCMenuItem * pExitBtn=(cocos2d::CCMenuItem *)Athletics_BTN_Node(AthleticsWindow::ATHLETICS_UI_EXIT_BTN);
		cocos2d::CCNode * pVipLayOff=Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_VIP_SKIP_CONFIG);
		pRePlayBtn->setPositionX(pRePlayBtn->getPositionX()+pVipLayOff->getPositionX());
		pSpeedBtn->setPositionX(pSpeedBtn->getPositionX()+pVipLayOff->getPositionX());
		pExitBtn->setPositionX(pExitBtn->getPositionX()+pVipLayOff->getPositionX());
	}   
	Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_REPLAY_BTN)->setVisible(true);
	Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_SPEED_BTN)->setVisible(true);
	Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_EXIT_BTN)->setVisible(true);
	 
}

 
 
/*
更新玩家组
*/
void   AthleticsUIManager::UpdateRoleInfoData(bool isPlayerGroup)
{
    if(isPlayerGroup)
	{
		 UpdateRoleInfoData(GetFirstPlayGroupRoleInfo(),isPlayerGroup);
	}
	else
	{
		 UpdateRoleInfoData(GetFirstEnemyGroupRoleInfo(),isPlayerGroup);
	}
}


void   AthleticsUIManager::UpdateRoleInfoData(RoleUniqeDefine role,bool isPlayerGroup)  
{
	PBaseRoleInfo  roleInfo=NULL;
	if(isPlayerGroup)
	{ 
		roleInfo=GetPlayGroupRoleInfo(role);	 
	}
	else
	{
		roleInfo=GetEnemyGroupRoleInfo(role);
	}
	UpdateRoleInfoData(roleInfo,isPlayerGroup);
	 
}




void   AthleticsUIManager::UpdateRoleInfoData(PBaseRoleInfo pBaseRoleInfo,bool isPlayerGroup)
{ 

  PBaseRoleInfo  roleInfo=pBaseRoleInfo;
  if(roleInfo!=NULL)
  {
	char  leftRoleBloodValue[64]={0};
  	if(roleInfo->roleType==BaseRoleInfo::_BASE_ROLE_PLAYER_TYPE_)
  	{
  		PPlayerRole  pPlayerRoleInfo=(PPlayerRole)roleInfo->pRoleInfoData;
  		if(pPlayerRoleInfo!=NULL)
  		{ 
  			//更行IconID
  			cocos2d::CCSprite * pPlayerIcon=NULL;
  			if(isPlayerGroup)
  			{
  				pPlayerIcon=(cocos2d::CCSprite *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_LEFT_ICON);
  			}
  			else
  			{
  				pPlayerIcon=(cocos2d::CCSprite *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_RIGHT_ICON);
  			}
  			if(pPlayerIcon!=NULL)
  			{
  				pPlayerIcon->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(pPlayerRoleInfo->iconID));
  			}
  			//更新等级
  			cocos2d::CCLabelTTF * pLevelLabel=NULL;
  			if(isPlayerGroup)
  			{
  				pLevelLabel=(cocos2d::CCLabelTTF *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_LEFT_LEVEL);
  			}
  			else
  			{
  				pLevelLabel=(cocos2d::CCLabelTTF *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_RIGHT_LEVEL);
  			}
  			if(pLevelLabel!=NULL)
  			{
  				char  leveStr[64]={0};
  				sprintf(leveStr,"%d",pPlayerRoleInfo->playerLevel);
  				pLevelLabel->setString(leveStr);
  			}
  			//更新昵称 
  			cocos2d::CCLabelTTF * pNameLabel=NULL;
  			if(isPlayerGroup)
  			{
  				pNameLabel=(cocos2d::CCLabelTTF *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_LEFT_NAME);
  			}
  			else
  			{
  				pNameLabel=(cocos2d::CCLabelTTF *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_RIGHT_NAME);
  			}					
  			if(pNameLabel!=NULL)
  			{
  				pNameLabel->setString(pPlayerRoleInfo->playerName.c_str());
  			}

  			//更新HP MP
  			PCommonRoleAttribute  pCommonRoleAttribure=pPlayerRoleInfo->pCommonRoleAttribute;
  			if(pCommonRoleAttribure!=NULL)
  			{
  				cocos2d::CCSingleLineLabelTTF * bloodValue=NULL;
  				if(isPlayerGroup)
  				{	
  					bloodValue=(cocos2d::CCSingleLineLabelTTF *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_LEFT_HP_VALUE);
  				}
  				else
  				{
  					bloodValue=(cocos2d::CCSingleLineLabelTTF *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_RIGHT_HP_VALUE);
  				}
  				if(bloodValue!=NULL)
  				{
  					sprintf(leftRoleBloodValue,"%d/%d",pCommonRoleAttribure->hpValue,pCommonRoleAttribure->hpValue);
  					bloodValue->setString(leftRoleBloodValue);
  				}

  				cocos2d::CCSingleLineLabelTTF * blueValue=NULL;
  				if(isPlayerGroup)
  				{
  					blueValue=(cocos2d::CCSingleLineLabelTTF *)Athletics_UI_Node(AthleticsWindow::ATHLTEICS_UI_LEFT_MP_VALUE);
  				}
  				else
  				{
  					blueValue=(cocos2d::CCSingleLineLabelTTF *)Athletics_UI_Node(AthleticsWindow::ATHLTEICS_UI_RIGHT_MP_VALUE);
  				}
  				if(blueValue!=NULL)
  				{
  					sprintf(leftRoleBloodValue,"%d/%d",pCommonRoleAttribure->mpValue,pCommonRoleAttribure->mpValue);
  					blueValue->setString(leftRoleBloodValue);
  				}	
  				
  				char  strValue[64]={0};
  				SKILLPENLDATA  skillData;
  				skillData.coatName=pPlayerRoleInfo->heroicName;
				skillData.petName=SysLangDataManager::get_instance2()->GetSysLangById(_SWORD_LABEL_TXT_);
				sprintf(strValue,"%d",pCommonRoleAttribure->sword);
				skillData.petlevel=strValue;
  				sprintf(strValue,"%d ~ %d",pCommonRoleAttribure->minAttack,pCommonRoleAttribure->maxAttack);
  				skillData.attackValue=strValue;
  				sprintf(strValue,"%d",pCommonRoleAttribure->speed);
  				skillData.speedValue=strValue;
  				sprintf(strValue,"%d",pCommonRoleAttribure->hit);
  				skillData.hitValue=strValue;
  				sprintf(strValue,"%d",pCommonRoleAttribure->dodge);
  				skillData.dodgeValue=strValue;
  				sprintf(strValue,"%d",pCommonRoleAttribure->exposeArmor);
  				skillData.sunderValue=strValue;
  				sprintf(strValue,"%d",pCommonRoleAttribure->armor);
  				skillData.armorValue=strValue;
  				sprintf(strValue,"%d",pCommonRoleAttribure->crit);
  				skillData.critValue=strValue;
  				sprintf(strValue,"%d",pCommonRoleAttribure->uncrit);
  				skillData.toughnessValue=strValue;

  				short skillItemCount=(short)pCommonRoleAttribure->skillIconArray.size();
  				FOR_EACH_ATHLETICSUNIT_BEGIN(skillItemCount)
  					 skillData.skillIconArray[athleticsIndex]=pCommonRoleAttribure->skillIconArray.at(athleticsIndex);
  	            FOR_EACH_ATHLETICSUNIT_END
  
  				//更新技能面板
  				if(isPlayerGroup)
  				{
  					pLeftAthleticSkillPanel->updateAthleticsSkillPanelWithSkillData(skillData);
  				}
  				else
  				{
  					pRightAthleticSkillPanel->updateAthleticsSkillPanelWithSkillData(skillData);
  				}
  			}
  		}
  	}
	else
	{
		PMonsterRole pMonsterRoleInfo=(PMonsterRole)roleInfo->pRoleInfoData;
		if(pMonsterRoleInfo!=NULL)
		{
			//更行IconID
			cocos2d::CCSprite * pMonsterIcon=NULL;
			if(isPlayerGroup)
			{
				pMonsterIcon=(cocos2d::CCSprite *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_LEFT_ICON);
			}
			else
			{
				pMonsterIcon=(cocos2d::CCSprite *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_RIGHT_ICON);
			}				
			if(pMonsterIcon!=NULL)
			{
				pMonsterIcon->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(pMonsterRoleInfo->iconID));
			}
			//更新等级
			cocos2d::CCLabelTTF * pMonsterLevelLabel=NULL;
			if(isPlayerGroup)
			{
				pMonsterLevelLabel=(cocos2d::CCLabelTTF *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_LEFT_LEVEL);
			}
			else
			{
				pMonsterLevelLabel=(cocos2d::CCLabelTTF *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_RIGHT_LEVEL);
			}

			if(pMonsterLevelLabel!=NULL)
			{
				char  leveStr[64]={0};
				sprintf(leveStr,"%d",pMonsterRoleInfo->monsterLevel);
				pMonsterLevelLabel->setString(leveStr);
			}

			//更新昵称 
			cocos2d::CCLabelTTF * pMonsterNameLabel=NULL;
			if(isPlayerGroup)
			{
				pMonsterNameLabel=(cocos2d::CCLabelTTF *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_LEFT_NAME);
			}
			else
			{
				pMonsterNameLabel=(cocos2d::CCLabelTTF *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_RIGHT_NAME);
			}	
			if(pMonsterNameLabel!=NULL)
			{
				pMonsterNameLabel->setString(pMonsterRoleInfo->monsterName.c_str());
			}
			//更新HP
			PCommonRoleAttribute  pCommonRoleAttribure=pMonsterRoleInfo->pCommonRoleAttribute;
			if(pCommonRoleAttribure!=NULL)
			{
				cocos2d::CCSingleLineLabelTTF * bloodValue=NULL;
				if(isPlayerGroup)
				{	
					bloodValue=(cocos2d::CCSingleLineLabelTTF *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_LEFT_HP_VALUE);
				}
				else
				{
					bloodValue=(cocos2d::CCSingleLineLabelTTF *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_RIGHT_HP_VALUE);
				}
				if(bloodValue!=NULL)
				{
					sprintf(leftRoleBloodValue,"%d/%d",pCommonRoleAttribure->hpValue,pCommonRoleAttribure->hpValue);
					bloodValue->setString(leftRoleBloodValue);
				}

				cocos2d::CCSingleLineLabelTTF * blueValue=NULL;
				if(isPlayerGroup)
				{
					blueValue=(cocos2d::CCSingleLineLabelTTF *)Athletics_UI_Node(AthleticsWindow::ATHLTEICS_UI_LEFT_MP_VALUE);
				}
				else
				{
					blueValue=(cocos2d::CCSingleLineLabelTTF *)Athletics_UI_Node(AthleticsWindow::ATHLTEICS_UI_RIGHT_MP_VALUE);
				}
				if(blueValue!=NULL)
				{
					sprintf(leftRoleBloodValue,"%d/%d",pCommonRoleAttribure->mpValue,pCommonRoleAttribure->mpValue);
					blueValue->setString(leftRoleBloodValue);
				}	

				char  strValue[64]={0};
				SKILLPENLDATA  skillData;
				skillData.coatName=pMonsterRoleInfo->monsterName;
				skillData.petName=SysLangDataManager::get_instance2()->GetSysLangById(_SWORD_LABEL_TXT_);
				sprintf(strValue,"%d",pCommonRoleAttribure->sword);
				skillData.petlevel=strValue;
				sprintf(strValue,"%d ~ %d",pCommonRoleAttribure->minAttack,pCommonRoleAttribure->maxAttack);
				skillData.attackValue=strValue;
				sprintf(strValue,"%d",pCommonRoleAttribure->speed);
				skillData.speedValue=strValue;
				sprintf(strValue,"%d",pCommonRoleAttribure->hit);
				skillData.hitValue=strValue;
				sprintf(strValue,"%d",pCommonRoleAttribure->dodge);
				skillData.dodgeValue=strValue;
				sprintf(strValue,"%d",pCommonRoleAttribure->exposeArmor);
				skillData.sunderValue=strValue;
				sprintf(strValue,"%d",pCommonRoleAttribure->armor);
				skillData.armorValue=strValue;
				sprintf(strValue,"%d",pCommonRoleAttribure->crit);
				skillData.critValue=strValue;
				sprintf(strValue,"%d",pCommonRoleAttribure->uncrit);
				skillData.toughnessValue=strValue;

				short skillItemCount=(short)pCommonRoleAttribure->skillIconArray.size();
				FOR_EACH_ATHLETICSUNIT_BEGIN(skillItemCount)
					skillData.skillIconArray[athleticsIndex]=pCommonRoleAttribure->skillIconArray.at(athleticsIndex);
				FOR_EACH_ATHLETICSUNIT_END

				if(isPlayerGroup)
				{
					pLeftAthleticSkillPanel->updateAthleticsSkillPanelWithSkillData(skillData);
				}
				else
				{
					pRightAthleticSkillPanel->updateAthleticsSkillPanelWithSkillData(skillData);
				}
			}
		}
	  } 	 
	}
}


PBaseRoleInfo  AthleticsUIManager::GetPlayGroupRoleInfo(RoleUniqeDefine & role)
{ 
   if(isPlayerGroupInFirstDeque)
   {
       size_t dequeCount=firstAthleticsDeque.size();
	   for(size_t dequeIndex=0;dequeIndex<dequeCount;dequeIndex++)
	   {
		  PBaseRoleInfo pBaseRoleInfo=firstAthleticsDeque.at(dequeIndex);
		  if(CheckPBaseInfoEquipUniqeDefine(pBaseRoleInfo,role))
		  {
			  return pBaseRoleInfo;
		  }
	   }
   }
   else
   {
	   size_t dequeCount=secondAthleticsDeque.size();
	   for(size_t dequeIndex=0;dequeIndex<dequeCount;dequeIndex++)
	   {
		   PBaseRoleInfo pBaseRoleInfo=secondAthleticsDeque.at(dequeIndex);
		   if(CheckPBaseInfoEquipUniqeDefine(pBaseRoleInfo,role))
		   {
			   return pBaseRoleInfo;
		   }
	   }
   }
   return NULL;
} 



bool	AthleticsUIManager::CheckPBaseInfoEquipUniqeDefine(PBaseRoleInfo pBaseRoleInfo,RoleUniqeDefine & role)
{
	if(pBaseRoleInfo!=NULL&&pBaseRoleInfo->roleType==role.unitType)
	{
		switch(role.unitType)
		{
		case  BaseRoleInfo::_BASE_ROLE_PLAYER_TYPE_:
			{
				PPlayerRole pPlayRole=(PPlayerRole)pBaseRoleInfo->pRoleInfoData;
				if(pPlayRole->playerID==role.sourceID)
				{
					return true;
				}
			}
			break;
		case  BaseRoleInfo::_BASE_ROLE_MONSTER_TYPE_:
			{
				PMonsterRole pMonsterRole=(PMonsterRole)pBaseRoleInfo->pRoleInfoData;
				if(pMonsterRole->monsterID==role.sourceID)
				{
					return true;
				}
			}
			break;
		default:
			break;
		}
	}
	return false;
}

PBaseRoleInfo  AthleticsUIManager::GetFirstPlayGroupRoleInfo()
{
   if(isPlayerGroupInFirstDeque)
   {
		if(firstAthleticsDeque.size()>0)
		{
			return  firstAthleticsDeque.at(0);
		}
		return NULL;
   }
   else
   {
	   if(secondAthleticsDeque.size()>0)
	   {
		   return  secondAthleticsDeque.at(0);
	   }
	   return NULL;
   }
}

PBaseRoleInfo  AthleticsUIManager::GetEnemyGroupRoleInfo(RoleUniqeDefine & role)
{
	if(isPlayerGroupInFirstDeque)
	{
		size_t dequeCount=secondAthleticsDeque.size();
		for(size_t dequeIndex=0;dequeIndex<dequeCount;dequeIndex++)
		{
			PBaseRoleInfo pBaseRoleInfo=secondAthleticsDeque.at(dequeIndex);
			if(CheckPBaseInfoEquipUniqeDefine(pBaseRoleInfo,role))
			{
				return pBaseRoleInfo;
			}
		}
	}
	else
	{
		size_t dequeCount=firstAthleticsDeque.size();
		for(size_t dequeIndex=0;dequeIndex<dequeCount;dequeIndex++)
		{
			PBaseRoleInfo pBaseRoleInfo=firstAthleticsDeque.at(dequeIndex);
			if(CheckPBaseInfoEquipUniqeDefine(pBaseRoleInfo,role))
			{
				return pBaseRoleInfo;
			}
		}

	}
	return NULL;
}

PBaseRoleInfo  AthleticsUIManager::GetFirstEnemyGroupRoleInfo()
{
	if(isPlayerGroupInFirstDeque)
	{
		if(secondAthleticsDeque.size()>0)
		{
			return  secondAthleticsDeque.at(0);
		}
		return NULL;
	}
	else
	{
		if(firstAthleticsDeque.size()>0)
		{
			return  firstAthleticsDeque.at(0);
		}
		return NULL;
	}
}

  


/*
	  初始化角色的属性面板  技能面板
*/
void   AthleticsUIManager::InitRolePropertyUI()
{ 
   	cocos2d::CCNode * pAthleticLayer=AthleticsSceneManager::get_instance2()->GetAthleticsRootLayer();
	if(pAthleticLayer!=NULL)
	{
		SKILLPENLDATA skillData;
		pLeftAthleticSkillPanel=AthleticsSkillPanel::createAthleticSkillPanel(skillData);
	    pRightAthleticSkillPanel=AthleticsSkillPanel::createAthleticSkillPanel(skillData,false);
	
		//左按钮
		CCSprite * pnoramlSprite=CCSprite::create();
		pnoramlSprite->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(_SKILLDESC_EXPAND_BTN_UP).c_str());
		CCSprite * pselectSprite=CCSprite::create();
		pselectSprite->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(_SKILLDESC_EXPAND_BTN_DOWN).c_str());
		pnoramlSprite->setFlipX(true);
		pselectSprite->setFlipX(true);
		CCMenuItemSprite * pLeftNormalItem=CCMenuItemSprite::create(pnoramlSprite,pselectSprite,NULL,this,menu_selector(AthleticsUIManager::OnLeftSkillPanelClick));
		pLeftNormalItem->setAnchorPoint(ccp(0,0));
		CCMenu * pLeftSkillButton=CCMenu::create(pLeftNormalItem,NULL);

		//右按钮
		CCSprite * pRightNoramlSprite=CCSprite::create();
		pRightNoramlSprite->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(_SKILLDESC_EXPAND_BTN_UP).c_str());
		CCSprite * pRightSelectSprite=CCSprite::create();
		pRightSelectSprite->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(_SKILLDESC_EXPAND_BTN_DOWN).c_str());
		CCMenuItemSprite * prightNormalItem=CCMenuItemSprite::create(pRightNoramlSprite,pRightSelectSprite,NULL,this,menu_selector(AthleticsUIManager::OnRightSkillPanelClick));
		CCMenu * pRightSkillButton=CCMenu::create(prightNormalItem,NULL);
		prightNormalItem->setAnchorPoint(ccp(0,0));
		pSkillPanelLayer=UITowSideStretchNodeLayer::createTowSideStretchLayer();
		CCNode  * stretchWithConfigNode=Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_STRETCHING_CONFIG);
		CCNode  * stretchYPosConfigNode=Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_STRETCHING_YCONFIG);

		pSkillPanelLayer->setNormalAndSelectWith(stretchWithConfigNode->getPositionX(),stretchWithConfigNode->getPositionY());
		pSkillPanelLayer->setNormalAndSelectYPos(stretchYPosConfigNode->getPositionX(),stretchYPosConfigNode->getPositionY());
		pSkillPanelLayer->setLeftNormalNode(pLeftSkillButton);
		pSkillPanelLayer->setleftSelectNode(pLeftAthleticSkillPanel);
		pSkillPanelLayer->setRightNormalNode(pRightSkillButton);
		pSkillPanelLayer->setRightSelectNode(pRightAthleticSkillPanel);

		pAthleticLayer->addChild(pSkillPanelLayer,SkillsPanelZOrder);
	}  
}



/*
	  更新角色的属性面包 各种属性值
*/
void   AthleticsUIManager::UpdateRolePropertyUI(SKILLPENLDATA  skillData,bool isLeftSkillPanel)
{
     if(isLeftSkillPanel)
	 {
        pLeftAthleticSkillPanel->updateAthleticsSkillPanelWithSkillData(skillData);
	 }
	 else
	 {
        pRightAthleticSkillPanel->updateAthleticsSkillPanelWithSkillData(skillData);
	 }
}
 
void  AthleticsUIManager::OnLeftSkillPanelClick(cocos2d::CCObject * pSenderObj)
{
	if(pSkillPanelLayer!=NULL)
	 pSkillPanelLayer->onShowUnfoldNode(true);

	if(pSkillPanelLayer!=NULL)
		pSkillPanelLayer->onShowUnfoldNode(false);
}

 
void  AthleticsUIManager::OnRightSkillPanelClick(cocos2d::CCObject * pSenderObj)
{   
	if(pSkillPanelLayer!=NULL)
	pSkillPanelLayer->onShowUnfoldNode(true);

	if(pSkillPanelLayer!=NULL)
	pSkillPanelLayer->onShowUnfoldNode(false);
}
 

void   AthleticsUIManager::UpdateRoleHPValue(bool isLeftRole)
{
    HeroicRole  * pHeroicRole=NULL;
	if(isLeftRole)
	{
		pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
		cocos2d::CCSprite * leftBloodSprite=(cocos2d::CCSprite *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_LEFT_HP_BG);
		CCLOG("getCurHPValue : %d, getInitHpValue : %d",pHeroicRole->getCurHPValue(),pHeroicRole->getInitHpValue());
		leftBloodSprite->setTextureRect(CCRectMake(0,0,1.0*pHeroicRole->getCurHPValue()/pHeroicRole->getInitHpValue()*m_bloodWidth_,leftBloodSprite->getContentSize().height));
		cocos2d::CCSingleLineLabelTTF * leftBloodValue=(cocos2d::CCSingleLineLabelTTF *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_LEFT_HP_VALUE);
		sprintf(tmpStr,"%d/%d",pHeroicRole->getCurHPValue(),pHeroicRole->getInitHpValue());
		leftBloodValue->setString(tmpStr);
	}
	else
	{
		pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
		CCLOG("getCurHPValue : %d, getInitHpValue : %d,%f",pHeroicRole->getCurHPValue(),pHeroicRole->getInitHpValue(),1.0*pHeroicRole->getCurHPValue()/pHeroicRole->getInitHpValue()*m_bloodWidth_);
		cocos2d::CCSprite * leftBloodSprite=(cocos2d::CCSprite *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_RIGHT_HP_BG);
		leftBloodSprite->setTextureRect(CCRectMake(0,0,1.0*pHeroicRole->getCurHPValue()/pHeroicRole->getInitHpValue()*m_bloodWidth_,leftBloodSprite->getContentSize().height));
		cocos2d::CCSingleLineLabelTTF * leftBloodValue=(cocos2d::CCSingleLineLabelTTF *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_RIGHT_HP_VALUE);
		sprintf(tmpStr,"%d/%d",pHeroicRole->getCurHPValue(),pHeroicRole->getInitHpValue());
		leftBloodValue->setString(tmpStr);
	}
}
 


void   AthleticsUIManager::UpdateRoleMPValue(bool isLeftRole)
{
   HeroicRole  * pHeroicRole=NULL;
   if(isLeftRole)
   {
	    pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
   		cocos2d::CCSprite * leftBlueSprite=(cocos2d::CCSprite *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_LEFT_MP_BG);
		leftBlueSprite->setTextureRect(CCRectMake(0,0,1.0*pHeroicRole->getCurMpValue()/pHeroicRole->getInitMPValue()*m_blueWidth_,leftBlueSprite->getContentSize().height));
   		cocos2d::CCSingleLineLabelTTF * leftBloodValue=(cocos2d::CCSingleLineLabelTTF *)Athletics_UI_Node(AthleticsWindow::ATHLTEICS_UI_LEFT_MP_VALUE);
   		sprintf(tmpStr,"%d/%d",pHeroicRole->getCurMpValue(),pHeroicRole->getInitMPValue());
   		leftBloodValue->setString(tmpStr);
   } 
   else
   {
	    pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
	    cocos2d::CCSprite * rightBlueSprite=(cocos2d::CCSprite *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_RIGHT_MP_BG);
		rightBlueSprite->setTextureRect(CCRectMake(0,0,1.0*pHeroicRole->getCurMpValue()/pHeroicRole->getInitMPValue()*m_blueWidth_,rightBlueSprite->getContentSize().height));
		cocos2d::CCSingleLineLabelTTF * rightBloodValue=(cocos2d::CCSingleLineLabelTTF *)Athletics_UI_Node(AthleticsWindow::ATHLTEICS_UI_RIGHT_MP_VALUE);
		sprintf(tmpStr,"%d/%d",pHeroicRole->getCurMpValue(),pHeroicRole->getInitMPValue());
		rightBloodValue->setString(tmpStr);
   }
 
}

//@更改按钮图标
//#显示当前速度对应的图标
void   AthleticsUIManager::UpdateAthleticSpeedBtnUI()
{ 
	CMenuItemSprite * speedItem = (CMenuItemSprite *)Athletics_BTN_Node(AthleticsWindow::ATHLETICS_UI_SPEED_BTN);
	if(speedItem!=NULL)
	{
		if (AthleticsSceneManager::get_instance2()->IsNormalSpeed()){//1
			string nor=ResourceIDDataManager::get_instance2()->getDataByID(_SPEED_NORMAL_NORAML_UP);
			string sel=ResourceIDDataManager::get_instance2()->getDataByID(_SPEED_NORAML_SELECT_DONW);
			speedItem->changeNormalAndSelectedImage(nor,sel);
		}
		else if(AthleticsSceneManager::get_instance2()->IsDoubleSpeed()){//2
			string nor=ResourceIDDataManager::get_instance2()->getDataByID(_SPEED_DOUBLE_NORMAL_UP);
			string sel=ResourceIDDataManager::get_instance2()->getDataByID(_SPEED_DOUBLE_SELECT_DOWN);
			speedItem->changeNormalAndSelectedImage(nor,sel);
		}else{//3
			string nor=ResourceIDDataManager::get_instance2()->getDataByID(_SPEED_TRIPLE_NORMAL_UP);
			string sel=ResourceIDDataManager::get_instance2()->getDataByID(_SPEED_TRIPLE_SELECT_DOWN);
			speedItem->changeNormalAndSelectedImage(nor,sel);
		}
	}
}


//@重置组队头像队列
void   AthleticsUIManager::ResetTeamIconList()
{
	if(pLeftTeamIconProgress)
	{
		pLeftTeamIconProgress->resetProgress();
	}

	if(pRightTeamIconProgress)
	{
		pRightTeamIconProgress->resetProgress();
	}
}

//@更新组队头像队列
void   AthleticsUIManager::UpdateTeamIconList(bool isPlayerGroup)
{
	if(isPlayerGroup)
	{
		if(pLeftTeamIconProgress)
		{
			pLeftTeamIconProgress->reduceActiveCount();
		}
	}
	else
	{
		if(pRightTeamIconProgress)
		{
			pRightTeamIconProgress->reduceActiveCount();
		}
	}
}
 

void  AthleticsUIManager::UnActiveAllTeamIcon(bool isPlayerGroup)
{
	if(isPlayerGroup)
	{
		if(pLeftTeamIconProgress)
		{
			pLeftTeamIconProgress->unActiveAllProgress();
		}
	}
	else
	{
		if(pRightTeamIconProgress)
		{
			pRightTeamIconProgress->unActiveAllProgress();
		}
	}
}



 