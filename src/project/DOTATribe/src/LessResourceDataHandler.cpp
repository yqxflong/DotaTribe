// Name :		LessResourceDataHandler.h
// Function:	资源不足数据
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include <cocos2d.h>
#include "../include/LessResourceDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/DOTATribeApp.h"
#include "../include/HomeProcedure.h" 
#include "../include/NFToolController.h"
#include "../include/IWindow.h"






using namespace std;

LessResourceDataHandler::LessResourceDataHandler()
{
}

LessResourceDataHandler::~LessResourceDataHandler()
{
	destroyMemData();
}


void LessResourceDataHandler::onDestroy()
{
	destroyMemData();
}
	
bool LessResourceDataHandler::init()
{
	type = 0;
	tips = "";
	jumpID = 0;
	hasNext = 0;
	itemId = 0;
	iconId = 0 ;
	quality = 0;
	name = "";
	description = "";
	leftCount = 0;
	leftUseTime = 0;
	return true;
}

void LessResourceDataHandler::JumpToVIP()
{ 
	if (jumpID == Type_Vip)
	{  
		DOTATribeApp::get_instance2()->ClearAllVisibleWindow(IWindow::_TYPED_WINDOW_NEWEQUIPREMINDWINDOW_);
		//召唤英雄
		if(DOTATribeApp::get_instance2()->GetActiveProcedure()->GetType()==IProcedure::_TYPED_HOME_PROCEDURE_)
		{ 
			EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_SHOW_VIPWINDOW_);
		}
		else
		{
			DOTATribeApp::get_instance2()->m_pHomeProcedure->SetShowWindow(_TYPED_EVENT_SHOW_VIPWINDOW_);
			EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_LOADINGWINDOW_,_to_event_param_(IProcedure::_TYPED_HOME_PROCEDURE_));
		}  
	} 
}
//////////////////////////////////////////////////////////////////////////
 
void  LessResourceDataHandler::decodePacketHandler(cobra_win::DPacket & packet)
{  
	init();
	packet.read(type);
	NFC_ParsePacketString(packet,tips); 
	packet.read(jumpID);
	packet.read(hasNext);
	if(type == _LESS_TOWER_TYPE_ || type == _LESS_TEAM_TYPE_)
	{
		jumpID = 0;
	} 
	if(hasNext)
	{
		packet.read(itemId);
		packet.read(iconId);
		packet.read(quality); 
		NFC_ParsePacketString(packet,name);
		NFC_ParsePacketString(packet,description);
		packet.read(leftCount);
		packet.read(leftUseTime);  
	}
	else
	{
		NFC_ParsePacketString(packet,description);
	}
	destroyMemData();

	COMMON_BEIGIN_ARRAY(size_t,4)
		DoingData* pData = new DoingData;
	    pData->decodePacketData(packet);
		DoingDataList.push_back(pData);
	COMMON_END_ARRAY

	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LESSRESOURCEWINDOW_); 
}

void  LessResourceDataHandler::destroyMemData()
{
	size_t dataSize = DoingDataList.size();
	COMMON_BEIGIN_ARRAY(size_t,dataSize)
		 delete  DoingDataList.at(index);
	COMMON_END_ARRAY
	DoingDataList.clear();
}