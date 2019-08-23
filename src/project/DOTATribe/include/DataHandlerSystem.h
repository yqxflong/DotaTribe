#ifndef  _DOTATRIBE_DATAHANDLERSYSTEM_H_
#define  _DOTATRIBE_DATAHANDLERSYSTEM_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <string>
#include <list>
#include <map>
using  namespace  cobra_win;

class DataHandlerSystem : public cobra_win::Singleton2<DataHandlerSystem>
{

private:
	std::list<IDataHandler*> m_DataHandlerList;

public:
	DataHandlerSystem();
	virtual ~DataHandlerSystem();

public:
	/*
		初始化数据管理系统
	*/
	bool   Init();
	/*
		数据管理系统帧更新
	*/
	void   Tick();
	/*
		销毁数据管理系统
	*/
	void   Destroy();

	/*
		销毁所有数据handler
	*/
	void DestroyAllDataHandler();

private:
	/*
		注册数据管理器
	*/
	void   RegisterDataManager(IDataHandler* pDataHandler);

public:
	friend  class  cobra_win::Singleton2<DataHandlerSystem>;
};

#define   DATAHANDLERSYSTEM   (DataHandlerSystem::get_instance2())


#endif
