//Name��	VipContrnlDataHandler
//Function��VIP��صĿ�����
//Written By��lvyunlong
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
		���յ���������ذ���ʱ���ô˺����Ѷ�Ӧ��������ת���ɶ�Ӧ�����ݽṹ
		����map�У�����֮����ڴ��е���ɾ�Ĳ�
	*/
	virtual void handlePacket(IPacket* packet);
	virtual bool init();
	virtual void onDestroy();
public:
	/*
		����VIP��Ϣ
	*/
	void ToServerVIPInfo();
	/*
		VIP��ȡ����
	*/
	void ToServerVIPReward();
};

#define VIPCONTROLDATAHANDLER	 VipControlDataHandler::get_instance2()

#endif