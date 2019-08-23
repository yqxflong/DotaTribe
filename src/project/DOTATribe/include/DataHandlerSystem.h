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
		��ʼ�����ݹ���ϵͳ
	*/
	bool   Init();
	/*
		���ݹ���ϵͳ֡����
	*/
	void   Tick();
	/*
		�������ݹ���ϵͳ
	*/
	void   Destroy();

	/*
		������������handler
	*/
	void DestroyAllDataHandler();

private:
	/*
		ע�����ݹ�����
	*/
	void   RegisterDataManager(IDataHandler* pDataHandler);

public:
	friend  class  cobra_win::Singleton2<DataHandlerSystem>;
};

#define   DATAHANDLERSYSTEM   (DataHandlerSystem::get_instance2())


#endif
