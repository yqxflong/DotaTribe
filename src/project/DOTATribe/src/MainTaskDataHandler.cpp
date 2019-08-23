//MainTaskDataHandler:主线任务
//author:方骏


#include <cocos2d.h>
#include "../include/MainTaskDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/CPublicVarReader.h"
#include "../include/MainTaskPacket.h"
#include "../include/CPublicVarReader.h"
#include "../include/WindowManager.h"
#include "../include/IWindow.h"
#include "../include/VariableSystem.h"
#include "../include/NFToolController.h"

 


MainTaskReward::MainTaskReward()
{
	type = -1;
	num = 0;
	catagory = 0;
	templateId = 0;
	quality = 0;
	iconId = 0;
	name = "";
}
void MainTaskReward::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(type);	//类型
	packet.read(num);	//数量
	if(type ==kDT_AWARD_OBJECT)
	{
		packet.read(catagory);
		packet.read(templateId);
		NFC_ParsePacketString(packet,name);
		packet.read(quality);
		packet.read(iconId);
	}
}

MainTaskItem::MainTaskItem()
{
    taskID=0;								//任务ID
	taskType=_TASK_ITEM_UNKONW_TYPE_;		//任务类型
	taskName="";							//任务名称
	taskInfo="";							//任务信息
	taskFinishedInfo="";					//任务完成信息
	isFinish=_TASK_UNFINISH_TYPE_;			//是否完成
    guidType=0;								//引导类型
	guideParam="";							//引导参数
	fcGuideID=0;							//新手功能引导ID
	rewardVector.clear();
}
MainTaskItem::~MainTaskItem()
{
	destroyData();
}
void MainTaskItem::destroyData()
{
	size_t  size=rewardVector.size();
	COMMON_BEGIN_VECTOR(size)
		delete rewardVector[index];
		rewardVector[index] = NULL;
	COMMON_END_VECROR
	rewardVector.clear();
}
void MainTaskItem::decodePacketData(cobra_win::DPacket & packet)
{
	destroyData();
	packet.read(taskType);
	packet.read(taskID);
	NFC_ParsePacketString(packet,taskName);
	NFC_ParsePacketString(packet,taskInfo);
	NFC_ParsePacketString(packet,taskFinishedInfo);
	packet.read(guidType);
	NFC_ParsePacketString(packet,guideParam);
	packet.read(fcGuideID);
	char count = 0;
	packet.read(count);
	MainTaskReward * rewardItem = NULL;
	COMMON_BEIGIN_ARRAY(char,count)
		rewardItem = new MainTaskReward();
		rewardItem->decodePacketData(packet);
		rewardVector.push_back(rewardItem);
	COMMON_END_ARRAY
	packet.read(isFinish);
}


MainTaskData::MainTaskData()
{
	bFindFinishTask=false;
	finishTaskID=-1;
	taskMapInfo.clear();
}

MainTaskData::~MainTaskData()
{
	destroyData();
}

int	 MainTaskData::getIndexFromTaskID(int taskID)
{ 
	int  tickIndex=0;
	std::map<int,MainTaskItem *>::iterator  task_iter=taskMapInfo.begin();
	while(task_iter!=taskMapInfo.end())
	{
		if(task_iter->second->taskID==taskID)
		{
			return tickIndex;
		}
		++tickIndex;
		++task_iter;
	} 
	return 0;
}
MainTaskItem * MainTaskData::at(int index)
{
	int  tickIndex=0;
	std::map<int,MainTaskItem *>::iterator  task_iter=taskMapInfo.begin();
	while(task_iter!=taskMapInfo.end())
	{
		if(tickIndex==index)
		{
			return  (task_iter->second);
 		} 
		++tickIndex;
		++task_iter;
	} 
	return NULL;
}

size_t	 MainTaskData::getTaskNum()
{
	return taskMapInfo.size();
}
bool	 MainTaskData::erase(int index)
{
	int  tickIndex=0;
	std::map<int,MainTaskItem *>::iterator  task_iter=taskMapInfo.begin();
	while(task_iter!=taskMapInfo.end())
	{
		if(tickIndex==index)
		{
			task_iter->second->destroyData();
			delete task_iter->second;
			taskMapInfo.erase(task_iter);
			return true;
		} 
		++tickIndex;
		++task_iter;
	} 
	return false;
}


bool		MainTaskData::erase(MainTaskItem * pMainTaskItem)
{
	std::map<int,MainTaskItem *>::iterator  task_iter=taskMapInfo.find(pMainTaskItem->taskID);
	if(task_iter!=taskMapInfo.end())
	{   
		task_iter->second->destroyData();
		delete task_iter->second;
		taskMapInfo.erase(task_iter);
		return true;
	}
	return false;
}


int		MainTaskData::finishCellIndex()
{ 
	return getIndexFromTaskID(finishTaskID);
}
 
void	MainTaskData::insert(MainTaskItem * pMainTaskItem)
{
	if(pMainTaskItem!=NULL)
	{
		std::map<int,MainTaskItem *>::iterator task_iter=taskMapInfo.find(pMainTaskItem->taskID);
		if(task_iter!=taskMapInfo.end())
		{
			pMainTaskItem->destroyData();
			delete pMainTaskItem;
			pMainTaskItem=NULL;
		}
		else
		{
		  taskMapInfo.insert(std::map<int,MainTaskItem *>::value_type(pMainTaskItem->taskID,pMainTaskItem));
		} 
	}
}
 

void MainTaskData::destroyData()
{ 
	std::map<int,MainTaskItem *>::iterator  task_iter=taskMapInfo.begin();
	while(task_iter!=taskMapInfo.end())
	{
		delete (task_iter->second);
		++task_iter;
	}
 	taskMapInfo.clear();
}
 
void MainTaskData::decodePacketData(cobra_win::DPacket & packet)
{
	destroyData(); 
	char taskCount = 0;
	packet.read(taskCount);
	COMMON_BEIGIN_ARRAY(char,taskCount)
		MainTaskItem * pMainTaskItem=new MainTaskItem();
		pMainTaskItem->decodePacketData(packet);
		if(!bFindFinishTask&&pMainTaskItem->isFinish==MainTaskItem::_TASK_FINISHED_TYPE_)
		{
			bFindFinishTask=true;
			finishTaskID=pMainTaskItem->taskID;
		}	
		insert(pMainTaskItem);
	COMMON_END_ARRAY
	if(!bFindFinishTask)
	{
		finishTaskID=-1;
	}
	bFindFinishTask=false;
}


PromptRewardInfoData::PromptRewardInfoData()
{
	 taskID=0;
	 taskType=0;
	 taskName="";
	 taskInfo="";
	 taskFinishInfo="";
	 rewardVector.clear();
}

PromptRewardInfoData::~PromptRewardInfoData()
{
	destroyData();
}

void PromptRewardInfoData::decodePacketData(cobra_win::DPacket & packet)
{
	packet.read(taskType);
	packet.read(taskID);
	NFC_ParsePacketString(packet,taskName);
	NFC_ParsePacketString(packet,taskInfo);
	NFC_ParsePacketString(packet,taskFinishInfo);
	char  rewardCount=0;
	packet.read(rewardCount);
	MainTaskReward * rewardItem = NULL;
	COMMON_BEIGIN_ARRAY(char,rewardCount)
		rewardItem = new MainTaskReward();
		rewardItem->decodePacketData(packet);
		rewardVector.push_back(rewardItem);
	COMMON_END_ARRAY

}

void PromptRewardInfoData::destroyData()
{
	size_t  size=rewardVector.size();
	COMMON_BEGIN_VECTOR(size)
		delete rewardVector[index];
		rewardVector[index] = NULL;
	COMMON_END_VECROR
	rewardVector.clear();
} 
 

void MainTaskDataHandler::PushPromptRewardItem(PromptRewardInfoData * pPromptRewardData)
{
	if(pPromptRewardData!=NULL)
	{
		m_promptRewardDeque.push_back(pPromptRewardData);
	}
}

bool MainTaskDataHandler::PopPromptRewardItem()
{   
	if(!m_promptRewardDeque.empty())
	{    
		PromptRewardInfoData * pPromptRewardInfoData=m_promptRewardDeque.front();
		if(pPromptRewardInfoData!=NULL)
		{
			pPromptRewardInfoData->destroyData();
			delete pPromptRewardInfoData;
			pPromptRewardInfoData=NULL;
		}
		m_promptRewardDeque.pop_front();
		return true;
	} 
	return false;
}

PromptRewardInfoData * MainTaskDataHandler::FrontPromptRewardItem()
{ 
	if(!m_promptRewardDeque.empty())
	{
		PromptRewardInfoData * pPromptRewardInfoData=m_promptRewardDeque.front();
		return pPromptRewardInfoData;
	}
	return NULL;
}

size_t MainTaskDataHandler::PromptDequeNum()
{
	return m_promptRewardDeque.size();
} 

void  MainTaskDataHandler::DestroyAllRewardItem()
{
   size_t rewardNum=m_promptRewardDeque.size();
   COMMON_BEIGIN_ARRAY(size_t,rewardNum)
	   if(!PopPromptRewardItem())
	   return ;
   COMMON_END_VECROR
   m_promptRewardDeque.clear();
}


bool  MainTaskDataHandler::IsHadNextRewardItem()
{
	return  !m_promptRewardDeque.empty();
}
 
  

MainTaskDataHandler::MainTaskDataHandler()
{
	m_bHadNewTask=false;
	m_pMainTaskData = NULL;
	m_promptRewardDeque.clear();
}
MainTaskDataHandler::~MainTaskDataHandler()
{
	if(m_pMainTaskData)
	{
		m_pMainTaskData->destroyData();
		delete m_pMainTaskData;
		m_pMainTaskData = NULL;
	}
	DestroyAllRewardItem();
}

void MainTaskDataHandler::onDestroy()
{
	m_bHadNewTask=false;
	if(m_pMainTaskData)
	{
		m_pMainTaskData->destroyData();
		delete m_pMainTaskData;
		m_pMainTaskData = NULL;
	}
	DestroyAllRewardItem();
}

bool MainTaskDataHandler::init()
{
	return true;
}


void MainTaskDataHandler::ToServerEnterMainTask()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_MAINTASKWINDOW_);
	CSEnterMainTaskPacket packet;
	packet.Send();
}

void MainTaskDataHandler::PushRewardNotification()
{
	if(IsHadNextRewardItem())
	{
		bool m_bPauseLeapTips=false;
		GET_WEAK_TIPS_SYSTEM(m_bPauseLeapTips)
	    if(!m_bPauseLeapTips&&!WindowManager::get_instance2()->IsWindowVisible(IWindow::_TYPED_WINDOW_MAINTASKWINDOW_))
		{   
			EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_SHOW_FORCEPUSHTASKREWARDWINDOW_);
		} 
	}
}

 