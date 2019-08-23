//Name:NewEquipremindDataHandler
//Author: lvyunlong
//Func: new equip remind handler
//Maintainer:lvyunlong

#ifndef   _DOTATRIBE_NEWEQUIPREMINDDATAHANDLER_H_
#define   _DOTATRIBE_NEWEQUIPREMINDDATAHANDLER_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <vector>
#include <cocos2d.h>
#include "../include/BagEquipDataHandler.h"
#include "../include/RoleEquipDataHandler.h"
#include "../include/VariableSystem.h"

class NewEquipremindDataHandler:public IDataHandler,public cobra_win::Singleton2<NewEquipremindDataHandler>{
public:
	int id_;
	bool m_ShowIsSwallow;
public:
	NewEquipremindDataHandler();
	virtual ~NewEquipremindDataHandler();
	/*
		���յ���������ذ���ʱ���ô˺����Ѷ�Ӧ��������ת���ɶ�Ӧ�����ݽṹ
		����map�У�����֮����ڴ��е���ɾ�Ĳ�
	*/
	virtual void handlePacket(IPacket* packet);
	virtual bool init();
	virtual void onDestroy();
public:
	void ComPareNewEquipandRoleEquip(int id);

	void DetectRemindShow();

	void SwallowEquip(int id);

	void HideClearData();
};

#define NEWEQUIPREMINDDATAHANDLER	 NewEquipremindDataHandler::get_instance2()
#endif