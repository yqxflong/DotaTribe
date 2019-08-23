//Name： PESEquipDataHandler
//Function：人物装备界面数据管理
//Written By：尹强
#ifndef   _DOTATRIBE_PESEquipDataHandler_H
#define   _DOTATRIBE_PESEquipDataHandler_H

#include   <include/common/Singleton.h>
#include "../include/IDataHandler.h"

class PESEquipDataHandler:public IDataHandler,public cobra_win::Singleton2<PESEquipDataHandler>{
public:
	bool isRefreshRoleShapeInfo_;
	bool isRefreshRoleEquip_;
	bool isRefreshEquipList_;
public:
	PESEquipDataHandler();
	virtual ~PESEquipDataHandler();
	virtual void handlePacket(IPacket* packet){};
	virtual bool init();
	virtual void onDestroy();
	void ClearData();
};
#define PESEQUIPDATAHANDLER	 PESEquipDataHandler::get_instance2()
#endif