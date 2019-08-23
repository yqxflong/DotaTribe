//Name： PESEquipDataHandler
//Function：人物装备界面数据管理
//Written By：尹强

#include "../include/PESEquipDataHandler.h"

PESEquipDataHandler::PESEquipDataHandler(){
	ClearData();
}

PESEquipDataHandler::~PESEquipDataHandler(){

}

bool PESEquipDataHandler::init(){
	return true;
}

void PESEquipDataHandler::onDestroy(){
	ClearData();
}

void PESEquipDataHandler::ClearData(){
	isRefreshRoleShapeInfo_=0;
	isRefreshRoleEquip_=0;
	isRefreshEquipList_=0;
}