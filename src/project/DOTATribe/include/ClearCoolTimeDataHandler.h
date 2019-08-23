#ifndef   _DOTATRIBER_CLEARCOLLTIMEDATAHANDLER_H
#define   _DOTATRIBER_CLEARCOLLTIMEDATAHANDLER_H

/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  清除时间数据管理器
//date:   2013/07/22
///////////////////////////////////////////////// 
#include   <include/common/Singleton.h>
#include   "../include/IDataHandler.h" 
#include   <string>

 
class   ClearCoolTimeDataHandler: public IDataHandler,public cobra_win::Singleton2<ClearCoolTimeDataHandler>
{
public: 
	 char  clearResult;
public:
	ClearCoolTimeDataHandler();
	~ClearCoolTimeDataHandler();
	/*
		当收到服务器相关包的时候，用此函数把对应包的数据转化成对应的数据结构
		存入map中，用于之后的内存中的增删改查
	*/
	virtual void handlePacket(IPacket* packet); 
	 
	/*
		销毁接口
	*/
	virtual void onDestroy();

	/*
		初始化接口
	*/
	virtual bool init();
 

public:
	friend   class   cobra_win::Singleton2<ClearCoolTimeDataHandler>;
};

#define   CLEARCOLLTIMEDATA			(ClearCoolTimeDataHandler::get_instance2())
 
#endif