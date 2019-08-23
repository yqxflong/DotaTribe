//Name��AthleticsProcedure
//Function��ս������
//Author:	Johny

#include "../include/AthleticsProcedure.h"
#include "../include/DOTATribeApp.h"
#include "../include/ProfSystem.h"
#include "../include/SoundSystem.h"
#include "../include/LoggerSystem.h"
#include "../include/TimeSystem.h"
#include "../include/Common.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/AthleticsSceneManager.h"
#include "../include/AthleticsInstructionSystem.h"
#include "../include/SelectMissionProcedure.h"
#include "../include/HomeProcedure.h"
#include "../include/TeamBattleProcedure.h"
#include "../include/AthleticProcedureDataType.h"
#include "../include/AthleticProcedureDataHandler.h"
#include "../include/MainTaskDataHandler.h"
#include "../include/NFControlsManager.h"

//Ԥ������Ч����ID
#include "../include/CPublicVarReader.h"
#include "../include/VariableSystem.h"



#include "../include/SkillTableDataManager.h"
#include "../include/SkillActionDataManager.h"
#include "../include/RoleShapeDataManager.h"
#include "../include/ActionSetDataManager.h"
#include "../include/CompositeEffectDataManager.h"
#include "../include/SceneInfoDataManager.h"
#include "../include/FrameAnimateDataManager.h"
#include "../include/AnimationFileDataManager.h"
#include "../include/ServerInfoDataHandler.h"

#include <vector>
#include <cocos2d.h>
#include <include/common/String.h>

AthleticsProcedure::AthleticsProcedure()
{
   m_Type    = _TYPED_ATHLETICS_PROCEDURE_;
   m_LogicTickCounter=0;
   m_SubType=_TYPE_ATHLETICSPROCUDURE_UNKONW_;
   m_bReStartProcedure=false;
   m_bStartGame=false;
   m_bSycLoadFinish=false;
   m_preLoadTextureCount=0;
}

AthleticsProcedure::~AthleticsProcedure()
{

}

 
int   AthleticsProcedure::GetSubType()
{	
    return  m_SubType;
}
  
   
std::string  GetPngPathFromPlistPath(std::string plistPath)
{
	size_t startPos = plistPath.find_last_of("."); 
	plistPath = plistPath.erase(startPos);
	// append .png
	plistPath = plistPath.append(".png");
	return plistPath;
}

void AthleticsProcedure::Init_Sub(){
	//@������Դ
	StartAnalysisEffectPool();

	//@����ս������
	EVENTSYSTEM->PushEvent(_TYPE_EVENT_SHOW_ATHLETICWINDOW_);

	//@��ʼ������������
	new AthleticsSceneManager;
	ATHLETICSSCENEMANAGER->Init();
	ATHLETICSSCENEMANAGER->SetSycLoadTexurePlistPool(ATHLETICPROCEDUREDATA->athleticsEffectPlistPool);
}

bool  AthleticsProcedure::Init()
{   
	//begin:��ʼ����Ա����
	m_bSycLoadFinish=false;
	m_bStartGame=false;
	m_preLoadTextureCount=0;
	m_bReStartProcedure=false;
	//end

	//@�첽��ʼ��һЩ��Դ
	Init_Sub();

	//ע�����֪ͨ
	EVENTSYSTEM->RegisterEventHandler(_TYPED_EVENT_SOCKETCLOSED_HINT,Event_Procedure_Handler);
	EVENTSYSTEM->RegisterEventHandler(_TYPED_EVENT_NETWORKCHANGED_HINT,Event_Procedure_Handler);
    return  true;
} 

void  AthleticsProcedure::Tick()
{  
	//�������첽������� ��������ʼ�����
	if(!m_bStartGame&&m_bSycLoadFinish)
	{
		PostStartGameNotification();
		m_bStartGame=true;
	}

	if(ATHLETICSSCENEMANAGER!=NULL&&!m_bReStartProcedure)
	{
		m_LogicTickCounter++;
		ATHLETICSSCENEMANAGER->Tick();
	}
}

void   AthleticsProcedure::Destroy()
{   
		m_bSycLoadFinish=false;
		m_bStartGame=false;
		m_preLoadTextureCount=0;
		CCLOG("Athletics Procedure Destroy :");
		EVENTSYSTEM->PushEvent(_TYPE_EVENT_HIDE_ATHLETICSRESULTWINDOW_);
		if(ATHLETICSSCENEMANAGER!=NULL)
		{
			ATHLETICSSCENEMANAGER->Destroy();
			ATHLETICSSCENEMANAGER->DestroySkillsEffectTextureData();
			AthleticProcedureDataHandler::get_instance2()->DestroyMemData();
			SoundSystem::get_instance2()->UnLoadSoundEffectQueue();
			delete  ATHLETICSSCENEMANAGER;
		} 
		EVENTSYSTEM->PushEvent(_TYPE_EVENT_HIDE_ATHLETICWINDOW_);

		_BEGIN_PROF_CHUNK_("AthleticsProcedure::ForceFreeMomery")
		// �ͷ�������Դ
		DOTATribeApp::get_instance2()->ForceFreeMemory(); 
		 
		SET_WEAK_TIPS_SYSTEM(false)
		NFC_showErrorTips(); 
		_END_PROF_CHUNK_()
			 
		//ȡ��ע�����֪ͨ
		EVENTSYSTEM->UnRegisterEventHandler(_TYPED_EVENT_SOCKETCLOSED_HINT,Event_Procedure_Handler);
		EVENTSYSTEM->UnRegisterEventHandler(_TYPED_EVENT_NETWORKCHANGED_HINT,Event_Procedure_Handler);
 
}

void     AthleticsProcedure::DestroyWithOutAthleticsData()
{ 
		m_bSycLoadFinish=false;
		m_bStartGame=false;
		m_preLoadTextureCount=0;
		CCLOG("Athletics Procedure Destroy :");
		EVENTSYSTEM->PushEvent(_TYPE_EVENT_HIDE_ATHLETICSRESULTWINDOW_);
		if(ATHLETICSSCENEMANAGER!=NULL)
		{ 
		ATHLETICSSCENEMANAGER->DestroySkillsEffectTextureData();
		ATHLETICSSCENEMANAGER->Destroy();
		delete  ATHLETICSSCENEMANAGER;
		SoundSystem::get_instance2()->UnLoadSoundEffectQueue();
		} 
		EVENTSYSTEM->PushEvent(_TYPE_EVENT_HIDE_ATHLETICWINDOW_);

		_BEGIN_PROF_CHUNK_("AthleticsProcedure::ForceFreeMomery")
		// �ͷ�������Դ
		DOTATribeApp::get_instance2()->ForceFreeMemory();
		SOUNDSYSTEM->StopBackgroundMusic();
  
		_END_PROF_CHUNK_() 
 
}
 
/*
�л���ѡ��ؿ�����
*/
void  AthleticsProcedure::OnChangeProcedureToMission()
{
	CCLOG("ChangeToProcedure OnChangeProcedureToLoginProcure ");
	DOTATribeApp::get_instance2()->m_pSelectMissionProcedure->m_showWindow = _TYPED_EVENT_SHOW_SELECTSONMISSIONWINDOW_;
	DOTATribeApp::get_instance2()->SetActiveProcedure(DOTATribeApp::get_instance2()->m_pSelectMissionProcedure);
}
 
void AthleticsProcedure::OnChangeProcedureToHome(int windowEventType = _TYPED_EVENT_SHOW_HOMEWINDOW_)
{
	CCLOG("ChangeToProcedure OnChangeProcedureToHomeProcure : %d", windowEventType);
	DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(windowEventType);
	DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
}

void AthleticsProcedure::OnChangeProcedureToTeamBattle()
{
	CCLOG("ChangeToProcedure OnChangeProcedureToTeamBattleProcure ");
	DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pTeamBattleProcedure);
}
 

//�л���ѡ�񸱱�����
void  AthleticsProcedure::OnChangeProcedureToSceneLobbyProcure()
{
	CCLOG("ChangeToProcedure SceneLobby ");
   	DOTATribeApp::get_instance2()->SetActiveProcedure(DOTATribeApp::get_instance2()->m_pSelectMissionProcedure);
}

  
//@�첽����ս�����������Դ
void  AthleticsProcedure::StartAnalysisEffectPool()
{
	CCLOG("AthleticsProcedurec: StartAnalysisEffectPool Beigin Handler!");
	if(ATHLETICPROCEDUREDATA!=NULL)
	{  
		//�������ܳأ��Լ��ܻ�������
		ATHLETICPROCEDUREDATA->startAnalysisShapeSkillsArray(); 
		  
		PushEffectsPoolFromSkills();

		PushEffectsPoolFromExtAction();

		PushEffectsPoolFromScene();

		PushPreFrameTextureFromEffects();

		//���ս����ֵ����
		ATHLETICPROCEDUREDATA->pushAnimationPlistPool(ATHLETICS_NUMBERICAL_PLIST);

		PushPreFrameTextureFromRoleShape();

		StartSyncLoadTextureAndPlist();
		//Ԥ������Ч
		PushPreLoadSoundEffectQueue();
	}
}


void  AthleticsProcedure::PushEffectsPoolFromSkills()
{
	std::map<int,std::set<int> >::iterator shape_iter=ATHLETICPROCEDUREDATA->athleticsShapeSkillsPool.begin();
	while(shape_iter!=ATHLETICPROCEDUREDATA->athleticsShapeSkillsPool.end())
	{ 
		std::set<int>::iterator  skill_iter=shape_iter->second.begin();
		while(skill_iter!=shape_iter->second.end())
		{
			//���SkillTable�еĳ�����ЧID
			SkillTableData * pSkillTableData=SkillTableDataManager::get_instance2()->GetSkillTableDataByID(*skill_iter);
			if(pSkillTableData!=NULL)
			{
				//��ȡ����פ����Ч
				ATHLETICPROCEDUREDATA->pushEffectsPool(pSkillTableData->skillItemResidesEffectID);
				//���SkillActiveActionID
				SkillActionData * pSkillActionData=SkillActionDataManager::get_instance2()->GetSkillActionItemByID(pSkillTableData->skillItemActionsID);
				if(pSkillActionData!=NULL)
				{ 
					size_t activeActionCount=pSkillActionData->skillActiveActionVec_.size();
					FOR_EACH_ELEMENT_BEGIN(activeActionCount)
						ATHLETICPROCEDUREDATA->pushEffectsPool(GetCompositeEffectFromShape_Skill(shape_iter->first,pSkillActionData->skillActiveActionVec_.at(index)));
					FOR_EACH_ELEMENT_END
				}    
			} 
			skill_iter++;
		}
		//���ؽ�ɫĬ�϶���
		ATHLETICPROCEDUREDATA->pushEffectsPool(GetCompositeEffectFromShape_Skill(shape_iter->first,HeroicRole::DaiJi)); 
		ATHLETICPROCEDUREDATA->pushEffectsPool(GetCompositeEffectFromShape_Skill(shape_iter->first,HeroicRole::Walk));
		ATHLETICPROCEDUREDATA->pushEffectsPool(GetCompositeEffectFromShape_Skill(shape_iter->first,HeroicRole::ChuChang));			 
		shape_iter++;
	}   
}
void  AthleticsProcedure::PushEffectsPoolFromExtAction()
{
	std::map<int,std::set<int> >::iterator action_iter=ATHLETICPROCEDUREDATA->athleticsShapeActionsPool.begin();
	while (action_iter!=ATHLETICPROCEDUREDATA->athleticsShapeActionsPool.end())
	{
		std::set<int>::iterator second_iter=action_iter->second.begin();
		while (second_iter!=action_iter->second.end())
		{
			ATHLETICPROCEDUREDATA->pushEffectsPool(GetCompositeEffectFromShape_Skill(action_iter->first,*second_iter));
			++second_iter;
		}
		++action_iter;
	} 
}
void  AthleticsProcedure::PushEffectsPoolFromScene()
{
	//���س�����Ч
	SceneInfoData * pSceneInfoData=SceneInfoDataManager::get_instance2()->GetCustomPassDataByID(ATHLETICPROCEDUREDATA->athleticsSceneID);
	if(pSceneInfoData!=NULL)
	{
		PushFrameAnimationPlistFromComEffectID(pSceneInfoData->mEffectId1);
		PushFrameAnimationPlistFromComEffectID(pSceneInfoData->mEffectId2);
		PushFrameAnimationPlistFromComEffectID(pSceneInfoData->mEffectId3);
	}
}
void  AthleticsProcedure::PushPreFrameTextureFromEffects()
{
	//���ظ�����Ч���е�֡��������
	std::set<int>::const_iterator effect_iter=ATHLETICPROCEDUREDATA->athleticsCompositeEffectPool.begin();	
	while(effect_iter!=ATHLETICPROCEDUREDATA->athleticsCompositeEffectPool.end())
	{
		PushFrameAnimationPlistFromComEffectID(*effect_iter);
		++effect_iter;
	}
}
void  AthleticsProcedure::PushPreFrameTextureFromRoleShape()
{
	/*
		���ع���Ƥ�������Լ� ǰ����Ч����
	*/
	std::set<int> rolesShapeArray;
	ATHLETICPROCEDUREDATA->exportAthleticsShapeArray(rolesShapeArray);
	std::set<int>::iterator set_iter=rolesShapeArray.begin();
	while(set_iter!=rolesShapeArray.end())
	{
		PushPreTextureImageWithRoleShapeID(*set_iter);
		++set_iter;
	} 
}

void  AthleticsProcedure::StartSyncLoadTextureAndPlist()
{
	//�������߳��첽����
	std::set<std::string>::const_iterator plist_iter=ATHLETICPROCEDUREDATA->athleticsEffectPlistPool.begin();
	while(plist_iter!=ATHLETICPROCEDUREDATA->athleticsEffectPlistPool.end())
	{  
		//�ж��ļ�����
		switch(GetFileTypeFromName(*plist_iter))
		{
		case _PLIST_FILE_TYPE_:
			CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFileAsync((*plist_iter).c_str(),this,callfuncO_selector(AthleticsProcedure::SycLoadFinishCallHandler));
			break;
		case _IMAGE_FILE_TYPE_:
			CCTextureCache::sharedTextureCache()->addImageAsync((*plist_iter).c_str(),this,callfuncO_selector(AthleticsProcedure::SycLoadFinishCallHandler));
			break;
		default:
			break;
		} 
		++plist_iter;
	}  
}

/*
Ԥ������Ч����
*/
void   AthleticsProcedure::PushPreLoadSoundEffectQueue()
{  
	if(!SoundSystem::get_instance2()->IsEffectSoundMute())
	{
		std::set<int>::const_iterator effect_iter=ATHLETICPROCEDUREDATA->athleticsCompositeEffectPool.begin();	
		std::set<int> preLoadSoundEffect;
		while(effect_iter!=ATHLETICPROCEDUREDATA->athleticsCompositeEffectPool.end())
		{ 
		   CompositeEffectData * pCompositeEffectData=CompositeEffectDataManager::get_instance2()->GetCompositeEffectDataByID(*effect_iter);
		   if(pCompositeEffectData)
		   {
			   preLoadSoundEffect.insert(pCompositeEffectData->soundEffectID);
		   }
			++effect_iter;
		}
		SoundSystem::get_instance2()->PreLoadSoundEffectQueue(preLoadSoundEffect);
	}
}

/*
��ö����е�
*/
int   AthleticsProcedure::GetCompositeEffectFromShape_Skill(int shapeID,int actionID)
{
	RoleShapeData * pRoleShapeData=RoleShapeDataManager::get_instance2()->GetRoleShapeById(shapeID);
	if(pRoleShapeData&&pRoleShapeData->mActionSetDataManager)
	{    
	   return pRoleShapeData->mActionSetDataManager->GetCompositeEffectByActionID(actionID);
	}
	return -1;
}


void AthleticsProcedure::PushFrameAnimationPlistFromComEffectID(int compositeEffectID)
{
	CompositeEffectData * pCompositeEffectData=CompositeEffectDataManager::get_instance2()->GetCompositeEffectDataByID(compositeEffectID);
	if(pCompositeEffectData!=NULL)
	{
		size_t  effectCount=pCompositeEffectData->compositeEffectVec.size();
		FOR_EACH_ELEMENT_BEGIN(effectCount)
			if(pCompositeEffectData->compositeEffectVec.at(index).effectType==_CompositeEffect_FrameAniamteEffect_Type_)
			{
				FrameAnimateData * pFrameAnimationData=FrameAnimateDataManager::get_instance2()->GetFrameAnimateDataByID(pCompositeEffectData->compositeEffectVec.at(index).effectID);
				if(pFrameAnimationData!=NULL)
				{
					ATHLETICPROCEDUREDATA->pushAnimationPlistPool(AnimationFileDataManager::get_instance2()->GetAnimationPlistNameByID(pFrameAnimationData->frameAnimateEffectAnimationID));
				}
			}
		FOR_EACH_ELEMENT_END
	} 
}

void  AthleticsProcedure::PushFrameAnimationPlistFromEffectID(int frameAnimateEffectID)
{
	if(frameAnimateEffectID!=-1)
	{ 
		FrameAnimateData * pFrameAnimationData=FrameAnimateDataManager::get_instance2()->GetFrameAnimateDataByID(frameAnimateEffectID);
		if(pFrameAnimationData!=NULL)
		{
			ATHLETICPROCEDUREDATA->pushAnimationPlistPool(AnimationFileDataManager::get_instance2()->GetAnimationPlistNameByID(pFrameAnimationData->frameAnimateEffectAnimationID));
		}
	}	 
}


void  AthleticsProcedure::PushPreTextureImageWithRoleShapeID(int roleShapeID)
{
	if(roleShapeID!=-1)
	{ 
		RoleShapeData * pRoleShapeData=RoleShapeDataManager::get_instance2()->GetRoleShapeById(roleShapeID);
		if(pRoleShapeData!=NULL)
		{    
			//����Ԥ�������������Լ���Ч����
			ATHLETICPROCEDUREDATA->pushAnimationPlistPool(GetPngPathFromPlistPath(pRoleShapeData->mShapeAnimationImage));
			ATHLETICPROCEDUREDATA->pushAnimationPlistPool(GetPngPathFromPlistPath(pRoleShapeData->mShapeAnimationEffectImageUp));
			ATHLETICPROCEDUREDATA->pushAnimationPlistPool(GetPngPathFromPlistPath(pRoleShapeData->mShapeAnimationEffectImageDown));
		}
	}
}

//�첽������ɻص�֪ͨ
void  AthleticsProcedure::SycLoadFinishCallHandler(cocos2d::CCObject * pSender)
{ 
	 if((++m_preLoadTextureCount)>=(int)ATHLETICPROCEDUREDATA->athleticsEffectPlistPool.size())
	 {
		 m_bSycLoadFinish=true;
	 }	  		
}

//@���ռ������������Ϸ������
void  AthleticsProcedure::PostStartGameNotification()
{ 
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_LOADINGWINDOW_);
	ATHLETICSICSYSTEM->SetInstructionSystemCurState(AthleticsInstructionSystem::_INSTRUCTIONSYSTER_INITRROLEUI_TYPE_);
	ATHLETICSICSYSTEM->Tick();
  
	_END_PROF_CHUNK_()
		 
}




void  AthleticsProcedure::OnSystemEnterBackEventHandler()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_ENTERBACK_SELECTSKILLWINDOW_);
}


void  AthleticsProcedure::OnSystemEnterFrontEventHandler()
{
	SoundSystem::get_instance2()->OnEnterForegroundEventHandler();
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_ENTERBACK_SELECTSKILLWINDOW_);
}

void  AthleticsProcedure::OnSystemPauseEventHandler()
{

}

void   AthleticsProcedure::OnSystemResumeEventHandler()
{

}
 

void AthleticsProcedure::Event_Procedure_Handler(int iEventType, std::string owerData, std::list<std::string>& paramList){
	if (iEventType==_TYPED_EVENT_SOCKETCLOSED_HINT){
		SERVERINFODATAINFO->HandleConnectServerFail();
	}else if(iEventType==_TYPED_EVENT_NETWORKCHANGED_HINT){
		SERVERINFODATAINFO->ForceDisconnect();
	}
}