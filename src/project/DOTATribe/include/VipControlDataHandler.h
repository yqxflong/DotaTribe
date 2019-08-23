//Name：	VipContrnlDataHandler
//Function：VIP相关的控制器
//Written By：lvyunlong
//Date:20131211

#ifndef   _DOTATRIBE_VIPCONTRILDATAHANDLER_H_
#define   _DOTATRIBE_VIPCONTRILDATAHANDLER_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <cocos2d.h>
#include <include/mem/DPacket.h>

class VipControlDataHandler:public IDataHandler,public cobra_win::Singleton2<VipControlDataHandler>{

public:
	int m_exp;
	int m_maxExp;
	unsigned char m_isBGetReward; 
public:
	VipControlDataHandler();
	virtual ~VipControlDataHandler();
	/*
		当收到服务器相关包的时候，用此函数把对应包的数据转化成对应的数据结构
		存入map中，用于之后的内存中的增删改查
	*/
	virtual void handlePacket(IPacket* packet);
	virtual bool init();
	virtual void onDestroy();
public:
	/*
		请求VIP信息
	*/
	void ToServerVIPInfo();
	/*
		VIP领取奖励
	*/
	void ToServerVIPReward();
};

#define VIPCONTROLDATAHANDLER	 VipControlDataHandler::get_instance2()

#endif