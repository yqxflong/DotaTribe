//Name:NewEquipremindDataHandler
//Author: lvyunlong
//Func: new equip remind handler
//Maintainer:lvyunlong

#include <cocos2d.h>
#include "../include/NewEquipremindDataHandler.h"
#include "../include/NFControlsManager.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/IWindow.h"
#include "../include/WindowManager.h"
#include "../include/DOTATribeApp.h"
using namespace std;


NewEquipremindDataHandler::NewEquipremindDataHandler(){

	id_ = -1;
}

NewEquipremindDataHandler::~NewEquipremindDataHandler(){
	id_ = -1;
}

void NewEquipremindDataHandler::handlePacket(IPacket* packet){

}

bool NewEquipremindDataHandler::init(){

	return true;
}

void NewEquipremindDataHandler::onDestroy(){
	id_ = -1;
}

void NewEquipremindDataHandler::ComPareNewEquipandRoleEquip(int id)
{
	BagEquipData *bed =  BAGEQUIPDATAHANDLER->getEquipById(id);
	if (bed==NULL)
		return;
	
	int cat = bed->template_->type_;
	if (cat == kEQUIP_TYPE_EXPBALL)
	{
		return;
	}
	std::map<int,RoleEquipData*>::iterator it = NFC_GetHeroEquipManager()->m_mapEquipList.find(cat);
	RoleEquipData* red=it->second;
	if (red==NULL)
		return;
	if (red->hasEquip_)
	{
		if (red->equipdata_->template_->quality_ < bed->template_->quality_)
		{
			if(!WINDOWMANAGER->IsWindowVisible(IWindow::_TYPED_WINDOW_PESWINDOW_))
			{
				id_ = id;
				DetectRemindShow();
			}
		}
	}
	else
	{
		if(!WINDOWMANAGER->IsWindowVisible(IWindow::_TYPED_WINDOW_PESWINDOW_))
		{
			id_ = id;
			DetectRemindShow();
		}
	}
}

void NewEquipremindDataHandler::DetectRemindShow()
{
	if (id_ != -1 && (DOTATribeApp::get_instance2()->IsHomeProcedureAsActiveProcedure() || DOTATribeApp::get_instance2()->IsTeamBattleAsActiveProcedure() || 
		DOTATribeApp::get_instance2()->IsSelectMissionAsActiveProcedure() || DOTATribeApp::get_instance2()->IsArenaAsActiveProcedure()))
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_NEWEQUIPREMINDWINDOW_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_NEWEQUIPREMINDWINDOW_);
	}
	else
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_NEWEQUIPREMINDWINDOW_);
	}
}

void NewEquipremindDataHandler::SwallowEquip(int id)
{
	if (id_ != -1)
	{
		if (id_ == id)
		{
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_NEWEQUIPREMINDWINDOW_);
			id_ = -1;
		}
	}
}

void NewEquipremindDataHandler::HideClearData()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_NEWEQUIPREMINDWINDOW_);
	id_ = -1;
}