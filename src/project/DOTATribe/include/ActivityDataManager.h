// Name :		ActivityDataManager.h
// Function:	活动数据管理器
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef   _DOTATRIBE_ACTIVITYDATAMANAGER_H
#define   _DOTATRIBE_ACTIVITYDATAMANAGER_H
 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)

class   Activity: public IData
{
public:
	int  m_nActivityType; 							//活动类型
	int  m_nActivityWindowID;				  		//窗口ID  
	int m_nUseLua;				//窗口是否使用了lua
	int m_nShowEventId;			//窗口显示事件
	int m_nHideEventId;			//窗口隐藏事件
	int m_nShowActivityBg;		//是否显示活动窗口的背景图
public:
	Activity();
	~Activity(); 
public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class ActivityManager: public IDataManager, public cobra_win::Singleton2<ActivityManager>
{
public:
	std::map<int,  Activity*> m_ActivityList; 
public:
	ActivityManager(bool bLoadFromDB, bool bEncryption);
	virtual ~ActivityManager();

public:
	
    Activity * GetDataByType(int Id);

	/*
		得到对应的数据管理器名称
	*/
	virtual  std::string   GetName();
	/*
		得到对应的数据管理器内存占用大小
	*/
	virtual  unsigned  int GetSize();

public:
	/*
		初始化数据管理器
	*/
	virtual  bool  Init();
	/*
		数据管理器帧更新处理
	*/
	virtual  void  Tick();
	/*
		销毁数据管理器
	*/
	virtual  void  Destroy();

public:
	/*
		校验加载的数据(单行数据的有效性校验)
	*/
	virtual  bool  Varify(IData* pData);
	/*
		校验加载的数据(所有数据加载完之后进行的表与表关联性校验)
	*/
	virtual  bool  VarifyAfterLoadAll();

protected:
	/*
		创建指定的ItemData数据
	*/
	virtual  bool  LoadData(char* pBuffer, unsigned int iBufferLen);

private:
	friend   class   cobra_win::Singleton2<Activity>;

};
  
#endif