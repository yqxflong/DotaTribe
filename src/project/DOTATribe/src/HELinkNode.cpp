//Name：HELinkNode
//Function：当英雄没装备时，链接玩家去各场景
//Written By：尹强

#include "../include/HELinkNode.h"
#include "../include/NFControlsManager.h"
#include "../include/UIViewDataManger.h"
#include "../include/CMenuItemSprite.h"
#include "../include/config_HomeWindow.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/MissionDataHandler.h"
#include "../include/DOTATribeApp.h"
#include "../include/ClimbTowerDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/SelectMissionProcedure.h"
#include "../include/HomeProcedure.h"
#include "../include/TeamBattleProcedure.h"

USING_NS_CC;

HELinkNode::HELinkNode(){

}

HELinkNode* HELinkNode::create(){
	HELinkNode* cc=new HELinkNode();
	if (cc&&cc->init())
	{
		cc->autorelease();
		return cc;
	}
	delete cc;
	return NULL;
}
	
bool HELinkNode::init(){
	if(!CCNode::init())
		return false;



	_initLayout();
	_mapBtn();
	_checkCondition();
	return true;
}

void HELinkNode::_initLayout(){
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kHEROEQUIP_LINKNODE,this);
}

void HELinkNode::_mapBtn(){
	CMenuItemSprite* cc;
	//risk
	cc=(CMenuItemSprite*)NFC_getMenuItem(kBTN_RISK,this);
	cc->setIDX(kBTN_RISK);
	cc->setTarget(this,menu_selector(HELinkNode::On_Click_Event));
	//fuben
	cc=(CMenuItemSprite*)NFC_getMenuItem(kBTN_FUBEN,this);
	cc->setIDX(kBTN_FUBEN);
	cc->setTarget(this,menu_selector(HELinkNode::On_Click_Event));
	//tower
	cc=(CMenuItemSprite*)NFC_getMenuItem(kBTN_TOWER,this);
	cc->setIDX(kBTN_TOWER);
	cc->setTarget(this,menu_selector(HELinkNode::On_Click_Event));
}

void HELinkNode::_checkCondition(){
	int level=RoleInfoDataHandler::get_instance2()->m_pRIData->level_;
	if (level>=_LV_HOMEWINDOW_NEWSCENE_TOWER){
		NFC_showNode(kBAR_TOWER,this,true);
		NFC_showNode(kNAME_TOWER,this,true);
		NFC_showNode(kBTN_TOWER,this,true);
		//
		NFC_showNode(kBAR_FUBEN,this,true);
		NFC_showNode(kNAME_FUBEN,this,true);
		NFC_showNode(kBTN_FUBEN,this,true);
	}else if(level>=_LV_HOMEWINDOW_NEWSCENE_TEAMPVE){
		NFC_showNode(kBAR_FUBEN,this,true);
		NFC_showNode(kNAME_FUBEN,this,true);
		NFC_showNode(kBTN_FUBEN,this,true);
	}
}


void HELinkNode::On_Click_Event(cocos2d::CCObject* pSender){
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int idx=cc->getIDX();
	if (idx==kBTN_RISK){
		//go to risk
		if (DOTATribeApp::get_instance2()->m_pActiveProcedure->GetType()==IProcedure::_TYPED_SELECTMISSION_PROCEDURE_)
		{
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_SELECTSONMISSIONWINDOW_);
		}else{
			MissionDataHandler::get_instance2()->setCurMissionID(MissionDataHandler::get_instance2()->getWorldMapStateNum());
			DOTATribeApp::get_instance2()->m_pSelectMissionProcedure->m_showWindow = _TYPED_EVENT_SHOW_SELECTSONMISSIONWINDOW_;
			DOTATribeApp::get_instance2()->m_pHomeProcedure->ChangeProcedureTo((IProcedure*)DOTATribeApp::get_instance2()->m_pSelectMissionProcedure);
		}
	}else if(idx==kBTN_FUBEN){
		//go to fuben
		if (DOTATribeApp::get_instance2()->m_pActiveProcedure->GetType()==IProcedure::_TYPED_TEAMBATTLE_PROCEDURE_)
		{
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_TEAMBATTLEWINDOW_);
		}else{
			DOTATribeApp::get_instance2()->m_pTeamBattleProcedure->ChangeNowState(TeamBattleProcedure::_TEAMBATTLE_STATE_SELECTGATE_);
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_, _to_event_param_(IProcedure::_TYPED_TEAMBATTLE_PROCEDURE_));
		}
	}else if(idx==kBTN_TOWER){
		//go to tower
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_CLIMBTOWERWINDOW_);
		CLIMBTOWERDATAHANDLER->ToServerEnterTower();
	}
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_PESWINDOW_);
}
