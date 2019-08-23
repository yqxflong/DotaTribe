/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  任务相关数据包
//date:   2013/12/24
///////////////////////////////////////////////// 

#include <cocos2d.h>
#include "../include/MainTaskDataHandler.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/WindowManager.h"
#include "../include/IWindow.h"
#include "../include/MainTaskPacket.h"
#include "../include/MainTaskDataHandler.h"
#include "../include/NFControlsManager.h"


/************************************************************************/
/* 进入主线任务                                                  */
/************************************************************************/

CSEnterMainTaskPacket::CSEnterMainTaskPacket()
{
	m_PacketPrefix[0] = 'Z';
	m_PacketPrefix[1] = 'R';
	m_PacketTyper = GetPacketType();
	m_PacketLength = GetPacketLength();
}

CSEnterMainTaskPacket::~CSEnterMainTaskPacket()
{

}
unsigned  int  CSEnterMainTaskPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_ENTER_MAINTASK_;
}
unsigned  int  CSEnterMainTaskPacket::GetPacketLength()
{
	return sizeof(m_PacketPrefix) + sizeof(m_PacketTyper) + sizeof(m_PacketLength);
}
void  CSEnterMainTaskPacket::Send()
{
	NFC_showCommunicationWating(true);
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_PacketPrefix, sizeof(m_PacketPrefix));
	pNode->push(m_PacketLength);
	pNode->push(m_PacketTyper);
	NETSYSTEM->SendPacket(pNode);
}

/*
服务器回执任务信息包
*/
unsigned  int  SCEnterMainTaskResultPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_ENTER_MAINTASK_RESULT;
}

bool  SCEnterMainTaskResultPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_PacketPrefix,2);
	packet>>m_PacketLength;
	packet>>m_PacketTyper;

	if(MAINTASKDATAHANDLER->m_pMainTaskData == NULL)
	{
		MAINTASKDATAHANDLER->m_pMainTaskData = new MainTaskData();
	}
	MAINTASKDATAHANDLER->m_pMainTaskData->decodePacketData(packet);

	return true;
}
 
/*
同步任务信息
*/
unsigned  int  SCTaskFinishReceiptPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_FINISH_MAINTASK_RESULT_;
}

bool  SCTaskFinishReceiptPacket::Read(char* pBuffer, unsigned int iLen)
{ 
	DPacket packet(pBuffer, iLen);
	packet.read(m_PacketPrefix,2);
	packet>>m_PacketLength;
	packet>>m_PacketTyper; 
	char  isHadNext=0;
	packet>>isHadNext;
	if(isHadNext==1)
	{
		MainTaskItem * pMainTaskItem=new MainTaskItem();
		pMainTaskItem->decodePacketData(packet);
		MainTaskDataHandler::get_instance2()->m_pMainTaskData->insert(pMainTaskItem);
		EventSystem::get_instance2()->PushEvent2(_TYPED_EVENT_UPDATE_MAINTASKWINDOW_,_to_event_param_(1));
		return true;
	} 
	//更新任务数据
	EventSystem::get_instance2()->PushEvent2(_TYPED_EVENT_UPDATE_MAINTASKWINDOW_,_to_event_param_(2));
	return true;
}

 
/************************************************************************/
/* 领取奖励                                               
/************************************************************************/
unsigned  int SCPushTaskFinishRewardPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_TASK_GETREWARD_PROMPT_SERVER_;
}

bool  SCPushTaskFinishRewardPacket::Read(char* pBuffer, unsigned int iLen)
{  
	DPacket packet(pBuffer, iLen);
	packet.read(m_PacketPrefix,2);
	packet>>m_PacketLength;
	packet>>m_PacketTyper;

	if(isTaskWindowVisiable())
		return false; 

	PromptRewardInfoData * pPromptRewardInfo=new PromptRewardInfoData();
	pPromptRewardInfo->decodePacketData(packet);
	MainTaskDataHandler::get_instance2()->PushPromptRewardItem(pPromptRewardInfo);

	return true;

}

bool	SCPushTaskFinishRewardPacket::isTaskWindowVisiable()
{
	if(WindowManager::get_instance2()->IsWindowVisible(IWindow::_TYPED_WINDOW_MAINTASKWINDOW_))
		return true;
	return false;
}
 
CSGetTaskRewardRequestPacket::CSGetTaskRewardRequestPacket(int taskID)
{
	m_PacketPrefix[0] = 'Z';
	m_PacketPrefix[1] = 'R';
	m_PacketTyper = GetPacketType();
	m_PacketLength = GetPacketLength();
	m_taskID=taskID;
}
CSGetTaskRewardRequestPacket::~CSGetTaskRewardRequestPacket()
{ 
}
unsigned  int  CSGetTaskRewardRequestPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_FINISH_MAINTASK_;
}
unsigned  int  CSGetTaskRewardRequestPacket::GetPacketLength()
{ 
	return sizeof(m_PacketPrefix) + sizeof(m_PacketTyper) + sizeof(m_PacketLength) + sizeof(m_taskID);
}
 
void  CSGetTaskRewardRequestPacket::Send()
{ 
	NFC_showCommunicationWating(true);
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_PacketPrefix, sizeof(m_PacketPrefix));
	pNode->push(m_PacketLength);
	pNode->push(m_PacketTyper);
	pNode->push(m_taskID);
	NETSYSTEM->SendPacket(pNode);
}

  
CSGetTaskRewardSinglePacket::CSGetTaskRewardSinglePacket(int taskID)
{
	m_PacketPrefix[0] = 'Z';
	m_PacketPrefix[1] = 'R';
	m_PacketTyper = GetPacketType();
	m_PacketLength = GetPacketLength();
	m_taskID=taskID;
}

CSGetTaskRewardSinglePacket::~CSGetTaskRewardSinglePacket()
{ 
}
unsigned  int  CSGetTaskRewardSinglePacket::GetPacketType()
{ 
	return _TYPED_PACKET_C2S_DIALIG_TASK_REWARD_CLIENT_;
}

unsigned  int  CSGetTaskRewardSinglePacket::GetPacketLength()
{ 
	return sizeof(m_PacketPrefix) + sizeof(m_PacketTyper) + sizeof(m_PacketLength) + sizeof(m_taskID);
} 

void  CSGetTaskRewardSinglePacket::Send()
{ 
	//NFC_showCommunicationWating(true);
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_PacketPrefix, sizeof(m_PacketPrefix));
	pNode->push(m_PacketLength);
	pNode->push(m_PacketTyper);
	pNode->push(m_taskID);
	NETSYSTEM->SendPacket(pNode);
} 
 

unsigned  int  SCEnterMainTaskResultPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_ENTER_MAINTASK_RESULT;
}

bool  SCEnterMainTaskResultPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCEnterMainTaskResultPacket packet;
	if(!packet.Read(pBuffer, iLen))
	 return false;
	OnPostNotification();
	return true;
}
void SCEnterMainTaskResultPacketFactory::OnPostNotification()
{
	EventSystem::get_instance2()->PushEvent2(_TYPED_EVENT_UPDATE_MAINTASKWINDOW_,_to_event_param_(0));
}



unsigned  int  SCTaskFinishReceiptPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_FINISH_MAINTASK_RESULT_;
}

bool  SCTaskFinishReceiptPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCTaskFinishReceiptPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;
	return true;
}

unsigned  int  SCPushTaskFinishRewardPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_TASK_GETREWARD_PROMPT_SERVER_;
} 
bool  SCPushTaskFinishRewardPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCPushTaskFinishRewardPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;
	OnPostNotification();
	return true;
} 
void	SCPushTaskFinishRewardPacketFactory::OnPostNotification()
{    
	MainTaskDataHandler::get_instance2()->PushRewardNotification();
	//to do
 	//EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_SHOW_FORCEPUSHTASKREWARDWINDOW_);
}
  

/************************************************************************/
/*=====================限时活动列表请求=================
/************************************************************************/
#include "../include/LimitedActivityHandler.h"
CSLActivityPacket::CSLActivityPacket()
{

}

unsigned  int  CSLActivityPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_QUERY_LACTIVITY_;
}

/*
	接收活动列表的包
*/
unsigned  int  SCLActivityPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_QUERY_LACTIVITY_;
}

bool  SCLActivityPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_PacketPrefix,2);
	packet>>m_PacketLength;
	packet>>m_PacketTyper;

	LimitedActivityHandler::get_instance2()->decodePacketData_Query(packet);
	return true;
}


unsigned  int  SCLActivityPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_QUERY_LACTIVITY_;
}

bool  SCLActivityPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCLActivityPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	LimitedActivityHandler::get_instance2()->HandleAfterQueryLActivity();
	return true;
}



/************************************************************************/
/*=====================领取活动奖励=================
/************************************************************************/
CSLActivityGetAwardPacket::CSLActivityGetAwardPacket(int activityID,int rewardID)
{
	PushData(activityID);
	PushData(rewardID);
}

unsigned  int  CSLActivityGetAwardPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_GETAWARD_LACTIVITY_;
}

/*
	领取奖励结果
*/
unsigned  int  SCLActivityGetAwardPacket::GetPacketType()
{
	return _TYPED_PACKET_S2C_GETAWARD_LACTIVITY_;
}

bool  SCLActivityGetAwardPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_PacketPrefix,2);
	packet>>m_PacketLength;
	packet>>m_PacketTyper;

	return true;
}


unsigned  int  SCLActivityGetAwardPacketFactory::GetPacketType()
{
	return _TYPED_PACKET_S2C_GETAWARD_LACTIVITY_;
}

bool  SCLActivityGetAwardPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCLActivityGetAwardPacket packet;
	if(!packet.Read(pBuffer, iLen))
		return false;

	LimitedActivityHandler::get_instance2()->HandleAfterGetAward(1);
	return true;
}



