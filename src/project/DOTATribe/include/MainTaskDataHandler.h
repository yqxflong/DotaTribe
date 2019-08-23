//MainTaskDataHandler:任务系统
//author:方骏
//modify:xiaobo.wu
 
#ifndef _DOTATRIBE_MAINTASK_DATAHANDLER_H_
#define _DOTATRIBE_MAINTASK_DATAHANDLER_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>
#include "../include/CSMapTable.h"
#include <deque>
#include <vector>
#include <string>

class MainTaskReward
{
public:
	char type;		  //类型 	0物品 1金钱 2经验 3钻石4声望 5体力
	int  num;		  //数量
	char catagory;	  //类型
	int  templateId;  //模板类型
	std::string name; //名称
	char quality;	  //品质
	int  iconId;	  //图标
public:
	MainTaskReward();
	void decodePacketData(cobra_win::DPacket & packet);
};

class MainTaskItem
{
public:
	enum
	{
		_TASK_ITEM_UNKONW_TYPE_=-1,
		_TASK_ITEM_MAIN_LINE_TYPE_,		//主线任务类型
		_TASK_ITEM_DAILY_LINE_TYPE_,	//每日任务类型
	};
	enum
	{
		_TASK_UNKONW_FINISH_TYPE_=-1,	//未知类型
		_TASK_UNFINISH_TYPE_,			//未完成任务
		_TASK_FINISHED_TYPE_,			//完成任务
	};
public:
	int  taskID;						//任务ID
	char taskType;						//任务类型
	std::string taskName;				//任务名称
	std::string taskInfo;				//任务信息
	std::string taskFinishedInfo;		//任务完成信息
	char isFinish;						//是否完成
	char guidType;						//引导类型
	std::string guideParam;				//引导参数
	short fcGuideID;					//新手功能引导ID
	std::vector<MainTaskReward *> rewardVector;//奖励内容
public:
	MainTaskItem();
	~MainTaskItem();
	void destroyData();					//用于清空数据
	void decodePacketData(cobra_win::DPacket & packet);
};
 
class MainTaskData
{
public:
	int				getIndexFromTaskID(int taskID);
	MainTaskItem *  at(int index);
	size_t		    getTaskNum();
	bool			erase(int index);
	bool			erase(MainTaskItem * pMainTaskItem);
	int				finishCellIndex();
	void			insert(MainTaskItem * pMainTaskItem);
public:
	MainTaskData();
	~MainTaskData();
	void destroyData();//用于清空数据
	void decodePacketData(cobra_win::DPacket & packet);
protected:
	std::map<int,MainTaskItem *> taskMapInfo;
	bool			bFindFinishTask;
	int				finishTaskID;
};

 
class  PromptRewardInfoData
{
public: 
	PromptRewardInfoData();
	~PromptRewardInfoData();
public:
	int   taskID;
	char  taskType;
	std::string taskName;				//任务名称
	std::string taskInfo;
	std::string taskFinishInfo;
	std::vector<MainTaskReward *> rewardVector;//奖励内容
	void destroyData();//用于清空数据
	void decodePacketData(cobra_win::DPacket & packet);
};
 

class MainTaskDataHandler : public IDataHandler, public cobra_win::Singleton2<MainTaskDataHandler>
{
public:
	enum{
		_MODULE_UNDEFINE_ = 0,			//未知跳转
		_MODULE_DEFINE_GATE_ = 1,		//指定关卡
		_MODULE_HIGHEST_GATE_ = 2,		//最高进度关卡
		_MODULE_SHOP_ = 3,				//商店 1精品商店，2声望商店，3秘宝商店
		_MODULE_EQUIO_LEVELUO_GATE_=4,	//装备 1装备升级, 2装备进阶, 3装备洗练
		_MODULE_HEROBAR_GATE_=5,		//英雄召唤
		_MODULE_HERO_EQUIP_GATE_=6,		//英雄装备
		_MODULE_ARENA_GATE_=7,			//竞技场
		_MODULE_HERO_LIST_GATR_=8,		//英雄列表
		_MODULE_MINE_ = 9,				//矿洞   1 矿洞寻宝 2 苦工；3 金矿采集
		_MODULE_REMOTEANTIQUITY_ = 10,  //远古遗迹
		_MODULE_TESTTOWER_ = 11,		//试练塔 
	}; 

public:
	MainTaskData * m_pMainTaskData;								//任务信息包
	std::deque<PromptRewardInfoData *>   m_promptRewardDeque;	//服务器推送送奖励数据包	
	bool		  m_bHadNewTask;
public:
	MainTaskDataHandler();
	virtual ~MainTaskDataHandler();

protected:
	virtual void handlePacket(IPacket* packet){};
	virtual void onDestroy();
	virtual bool init();
public:
	/*
	强制推送奖励模块接口
	*/
	void  PushPromptRewardItem(PromptRewardInfoData * pPromptRewardData);
	bool  PopPromptRewardItem();
	bool  IsHadNextRewardItem();
	void  DestroyAllRewardItem();
	PromptRewardInfoData * FrontPromptRewardItem();
	size_t PromptDequeNum();
public:
	//
	void ToServerEnterMainTask();

	void PushRewardNotification();
 
};

#define MAINTASKDATAHANDLER (MainTaskDataHandler::get_instance2())



#endif