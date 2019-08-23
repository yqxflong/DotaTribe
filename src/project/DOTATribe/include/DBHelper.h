//Name: DBHelper.h
//Function: 提供Lua使用DBSystem中的部分功能接口,诸如Syslang，ResourceId
//Date: 20140313
//Author: fangjun

#ifndef _LUA_DBHELPER_H_
#define _LUA_DBHELPER_H_

#include "../include/BaseHelper.h"
#include "../include/SysLangDataManager.h"
#include "../include/ResourceIDDataManager.h"
#include "../include/RoleInfoDataHandler.h"

class DBHelper : public BaseHelper
{
private:
	static BaseHelper * m_pHelper;
	static std::string m_sName;

public:
	DBHelper();
	virtual ~DBHelper();

	virtual void BuildInstance(std::string name, BaseHelper * helper);
public:
	static BaseHelper * LuaGetInstance();

	static std::string LuaGetInstanceName();

	std::string LuaGetSysLangById(int langId);

	std::string LuaGetResourcePathByID(int idx);

	//获得人物信息接口
	RoleInfoDataHandler * LuaGetRoleInfoDataHandler();

	//飘字接口
	void LuaShowFlowEffect(int type,int count,int bjcount,int itemiconid=0);
};



#endif