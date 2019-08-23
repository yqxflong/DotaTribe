//Name��HomeProcedure
//Function������������
//Written By����ǿ

#include "../include/HomeProcedure.h"
#include "../include/NFControlsManager.h"
#include "../include/DOTATribeApp.h"
#include "../include/LoggerSystem.h"
#include "../include/ProfSystem.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/SelectMissionProcedure.h"
#include "../include/HomeWindow.h"
#include "../include/EffectWindow.h"
#include "../include/SysLangDataManager.h"
#include "../include/MessageBoxWindow.h"
#include "../include/TeamBattleProcedure.h"
#include "../include/MissionDataHandler.h"
#include "../include/LoadingAnimationDataManager.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/IAPSystem.h"
#include "../include/PayGoodsControlDataHandler.h"
#include "../include/HeroAltarControlDataHandler.h"
#include "../include/GuideSystem.h"
#include "../include/ChatPushLogic.h"
#include "../include/EmailDataHandler.h"
#include <string> 
using namespace std;

HomeProcedure::HomeProcedure()
{
	m_Type = _TYPED_HOME_PROCEDURE_;
	m_showWindow = 0;
	m_nSubViewType=0;
	
	m_bIsFristTime=true;
}

HomeProcedure::~HomeProcedure()
{

}


bool HomeProcedure::IsCanEnterScene(int sceneId)
{
	return true;
}

void  HomeProcedure::ChangeProcedureTo(IProcedure* procedure){
	// �л�����
	char type[128] = "";
	sprintf(type,"%d",procedure->GetType());
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_,type);
}

void HomeProcedure::ChangeProcedureToTeamBattle()
{
	DOTATribeApp::get_instance2()->SetActiveProcedure(DOTATribeApp::get_instance2()->m_pTeamBattleProcedure);
}

void HomeProcedure::SetShowWindow(int iWindowEventId)
{
	m_showWindow = iWindowEventId;
}

void HomeProcedure::SetSubViewType(int nSubViewType)
{
	m_nSubViewType=nSubViewType;
}


bool  HomeProcedure::Init()
{
	do 
	{
		_BEGIN_PROF_CHUNK_("HomeProcedure::Init()")


		if (m_bIsFristTime)
		{
			//������¹���
			SERVERINFODATAINFO->LoginNotice_Request();
			m_bIsFristTime=false;
		}else{
			GuideSystem::get_instance2()->CheckAndStartGuide();
		}

		/*
			��ʼ��֧����������Ϸʱֻ��ʼ��һ��
		*/
		if (!PAYGOODSCONTROLDATAHANDLER->m_isBInitmentEnv)
		{	
			//��ʼ��֧��
			IAPSYSTEM->InitPaymentEnv();
			//������Ʒ�б�
			PAYGOODSCONTROLDATAHANDLER->ToServerRechargeListPacket(SERVERINFODATAINFO->Get_Channel_ID());
			PAYGOODSCONTROLDATAHANDLER->m_isBInitmentEnv = true;
			
		}
		//����֧��������鷢��������
		if (!PAYGOODSCONTROLDATAHANDLER->m_isBIAPCheck)
		{
			PAYGOODSCONTROLDATAHANDLER->m_isBIAPCheck = true;
			PAYGOODSCONTROLDATAHANDLER->LocalPayIAPCheck();
		}
		SERVERINFODATAINFO->SetCurGameStatus(_TYPE_LOGIN_STATE_GAMESERVER_ENTERGAME);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_LOADINGWINDOW_);

		//����Ƿ���Ҫ��½����ʾ�ı���������Ϣ
		CHATPUSHLOGIC->StartPushMsg(true);
		
		//��ʾЧ�����ڣ�һֱ����
		EVENTSYSTEM->PushEvent(_TYPEF_EVENT_SHOW_EFFECTWINDOW_);

		// ��ʾUI
		if (m_showWindow!=0)
		{
			if(m_nSubViewType!=0)
			{ 
				EVENTSYSTEM->PushEvent(m_showWindow, _to_event_param_(m_nSubViewType)); 
				m_nSubViewType=0;
			}
			else
			EVENTSYSTEM->PushEvent(m_showWindow);
			if (m_showWindow  == _TYPED_EVENT_SHOW_CLIMBTOWERWINDOW_)
			{
				LoadingAnimationData* pData= LoadingAnimationManager::get_instance2()->GeLoadingAnimationDataByID(IProcedure::_TYPED_CLIMB_TOWER_);
				if (pData->mBackgroundSuondID != -1)
				{
					char _soundID[64]="";
					sprintf(_soundID,"%d",pData->mBackgroundSuondID);
					EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOUND_PLAY_,_soundID);
				}
			}
			else
				PlayBGSound();
			m_showWindow = 0;
		}
		else
		{
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
			PlayBGSound();
		}

		//ע�����֪ͨ
		EVENTSYSTEM->RegisterEventHandler(_TYPED_EVENT_SOCKETCLOSED_HINT,Event_Procedure_Handler);
		EVENTSYSTEM->RegisterEventHandler(_TYPED_EVENT_NETWORKCHANGED_HINT,Event_Procedure_Handler);


		_END_PROF_CHUNK_();
		LOGGERSYSTEM->LogInfo("HomeProcedure: Enter\n");
		return true;
	} 
	while (false);

	return false;
}

void  HomeProcedure::Tick(){
	// ִ�����봦��
	OnInputEventHandler();
}

void  HomeProcedure::Destroy()
{
	_BEGIN_PROF_CHUNK_("HomeProcedure::Destroy()")
	// ����UI
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_BOSSSCOREWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_ROLESTATUSWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_MINEAREAWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_NETOBJECTTIPSWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_MAINTASKWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_HOMEWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_PUCONGWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_FRIENDWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_CHATWINDOW_);

	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_HEROSOULWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_PESWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVNET_HIDE_HeroAdvancedWindow_);
	EVENTSYSTEM->PushEvent(_TYPED_EVNET_HIDE_HeroIllustratedWindow_);
	 
	DOTATribeApp::get_instance2()->ForceClearAnimationCache();
	DOTATribeApp::get_instance2()->ForceFreeMemory(); 

	//ȡ��ע�����֪ͨ
	EVENTSYSTEM->UnRegisterEventHandler(_TYPED_EVENT_SOCKETCLOSED_HINT,Event_Procedure_Handler);
	EVENTSYSTEM->UnRegisterEventHandler(_TYPED_EVENT_NETWORKCHANGED_HINT,Event_Procedure_Handler);

	_END_PROF_CHUNK_()
	LOGGERSYSTEM->LogInfo("HomeProcedure: Leave\n");
}

/*
	�����¼�����
*/
void  HomeProcedure::OnInputEventHandler(){

}

void  HomeProcedure::OnSystemEnterBackEventHandler()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_ENTERBACK_SELECTSKILLWINDOW_);
}

void  HomeProcedure::OnSystemEnterFrontEventHandler()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_ENTERBACK_SELECTSKILLWINDOW_);
}

void  HomeProcedure::OnSystemPauseEventHandler()
{

}

void  HomeProcedure::OnSystemResumeEventHandler()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_GAME_RESUME_);
}



void HomeProcedure::Event_Procedure_Handler(int iEventType, std::string owerData, std::list<std::string>& paramList){
	if (iEventType==_TYPED_EVENT_SOCKETCLOSED_HINT){
		SERVERINFODATAINFO->HandleConnectServerFail();
		EMAILDATAHANDLER->m_isGettingAtt = false;
	}else if(iEventType==_TYPED_EVENT_NETWORKCHANGED_HINT){
		SERVERINFODATAINFO->ForceDisconnect();
		EMAILDATAHANDLER->m_isGettingAtt = false;
	}
}