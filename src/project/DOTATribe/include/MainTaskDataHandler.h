//MainTaskDataHandler:����ϵͳ
//author:����
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
	char type;		  //���� 	0��Ʒ 1��Ǯ 2���� 3��ʯ4���� 5����
	int  num;		  //����
	char catagory;	  //����
	int  templateId;  //ģ������
	std::string name; //����
	char quality;	  //Ʒ��
	int  iconId;	  //ͼ��
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
		_TASK_ITEM_MAIN_LINE_TYPE_,		//������������
		_TASK_ITEM_DAILY_LINE_TYPE_,	//ÿ����������
	};
	enum
	{
		_TASK_UNKONW_FINISH_TYPE_=-1,	//δ֪����
		_TASK_UNFINISH_TYPE_,			//δ�������
		_TASK_FINISHED_TYPE_,			//�������
	};
public:
	int  taskID;						//����ID
	char taskType;						//��������
	std::string taskName;				//��������
	std::string taskInfo;				//������Ϣ
	std::string taskFinishedInfo;		//���������Ϣ
	char isFinish;						//�Ƿ����
	char guidType;						//��������
	std::string guideParam;				//��������
	short fcGuideID;					//���ֹ�������ID
	std::vector<MainTaskReward *> rewardVector;//��������
public:
	MainTaskItem();
	~MainTaskItem();
	void destroyData();					//�����������
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
	void destroyData();//�����������
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
	std::string taskName;				//��������
	std::string taskInfo;
	std::string taskFinishInfo;
	std::vector<MainTaskReward *> rewardVector;//��������
	void destroyData();//�����������
	void decodePacketData(cobra_win::DPacket & packet);
};
 

class MainTaskDataHandler : public IDataHandler, public cobra_win::Singleton2<MainTaskDataHandler>
{
public:
	enum{
		_MODULE_UNDEFINE_ = 0,			//δ֪��ת
		_MODULE_DEFINE_GATE_ = 1,		//ָ���ؿ�
		_MODULE_HIGHEST_GATE_ = 2,		//��߽��ȹؿ�
		_MODULE_SHOP_ = 3,				//�̵� 1��Ʒ�̵꣬2�����̵꣬3�ر��̵�
		_MODULE_EQUIO_LEVELUO_GATE_=4,	//װ�� 1װ������, 2װ������, 3װ��ϴ��
		_MODULE_HEROBAR_GATE_=5,		//Ӣ���ٻ�
		_MODULE_HERO_EQUIP_GATE_=6,		//Ӣ��װ��
		_MODULE_ARENA_GATE_=7,			//������
		_MODULE_HERO_LIST_GATR_=8,		//Ӣ���б�
		_MODULE_MINE_ = 9,				//��   1 ��Ѱ�� 2 �๤��3 ���ɼ�
		_MODULE_REMOTEANTIQUITY_ = 10,  //Զ���ż�
		_MODULE_TESTTOWER_ = 11,		//������ 
	}; 

public:
	MainTaskData * m_pMainTaskData;								//������Ϣ��
	std::deque<PromptRewardInfoData *>   m_promptRewardDeque;	//�����������ͽ������ݰ�	
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
	ǿ�����ͽ���ģ��ӿ�
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