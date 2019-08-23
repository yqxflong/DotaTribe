#include   <cocos2d.h>
#include   "../include/IWindow.h"
#include   "../include/AnnouncementDataHandler.h"
#include   "../include/WindowManager.h"
#include   "../include/IDataHandler.h" 
#include   "../include/EventTyper.h" 
#include   "../include/EventSystem.h" 
#include   "../include/NFToolController.h"
 
  
AnnoucementMemData::AnnoucementMemData()
{
	annoucementCSSType=0;
	annoucementContent="";
}

AnnoucementMemData::~AnnoucementMemData()
{
	annoucementCSSType=0;
	annoucementContent="";
}

 void  AnnoucementMemData::decodePacketData(cobra_win::DPacket & packet)
 {
	  packet.read(annoucementCSSType);
	  NFC_ParsePacketString(packet,annoucementContent);
 }

  
 //void AnnoucementMemData::postAnnouceNotification()
 //{  
	// EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_ANNOUNCEMENTWINDOW_,_to_event_param_(annoucementCSSType),annoucementContent);
 //}


//////////////////////////////////////////////////////////////////////////

 AnnoucementDataHandler::AnnoucementDataHandler()
 { 
	 //to do
 }

 AnnoucementDataHandler::~AnnoucementDataHandler()
 { 
	 //to do
 }

void AnnoucementDataHandler::handlePacket(IPacket* packet)
{ 
	// to do
}

void AnnoucementDataHandler::onDestroy()
{ 
	RemoveAllCacheItem();
}

bool AnnoucementDataHandler::init()
{  
	//to do
	return true;
}

 
bool	AnnoucementDataHandler::IsAnnoucementQueueEmpty()
{
	return m_dAnnouceCacheMemDataQueue.empty();
}
 
bool	AnnoucementDataHandler::TopAnnoucementItem(AnnoucementMemData & topItem)
{
	if(!IsAnnoucementQueueEmpty())
	{ 
		AnnoucementMemData item=m_dAnnouceCacheMemDataQueue.front();
		topItem.setAnnoucementCSSType(item.getAnnoucementCSSType());
		topItem.setAnnoucementContent(item.getAnnoucementContent());
		return true;
	}
	return false;
}
  
bool		AnnoucementDataHandler::PopAnnoucementItem()
{
	if(!IsAnnoucementQueueEmpty())
	{
		m_dAnnouceCacheMemDataQueue.pop();
		return true;
	}
	return false;
}
 
void	AnnoucementDataHandler::RemoveAllCacheItem()
{
	while(!IsAnnoucementQueueEmpty())
	m_dAnnouceCacheMemDataQueue.pop();
}
  

void	AnnoucementDataHandler::decodePacket(cobra_win::DPacket & packet)
{
	//to do
	AnnoucementMemData  memItemData;
	memItemData.decodePacketData(packet);
	m_dAnnouceCacheMemDataQueue.push(memItemData);
	//to do
	if(!WindowManager::get_instance2()->IsWindowLoad(IWindow::_TYPED_WINDOW_ANNOUNCEMENT_WINDOW_))
	{ 
		EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_SHOW_ANNOUNCEMENTWINDOW_);
	}
}


void	AnnoucementDataHandler::PushTeshItem(std::string content)
{
	AnnoucementMemData  memItemData;
	memItemData.setAnnoucementCSSType(0);
	memItemData.setAnnoucementContent(content);
	m_dAnnouceCacheMemDataQueue.push(memItemData);
	if(!WindowManager::get_instance2()->IsWindowLoad(IWindow::_TYPED_WINDOW_ANNOUNCEMENT_WINDOW_))
	{ 
		EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_SHOW_ANNOUNCEMENTWINDOW_);
	}
}