#include "../include/DBHelper.h"
#include "../include/EffectDataHandler.h"

BaseHelper * DBHelper::m_pHelper = NULL;
std::string DBHelper::m_sName = "";

DBHelper::DBHelper()
{

}

DBHelper::~DBHelper()
{

}

void DBHelper::BuildInstance(std::string name, BaseHelper * helper)
{
	m_pHelper = helper;
	m_sName = name;
}

BaseHelper * DBHelper::LuaGetInstance()
{
	return m_pHelper;
}

std::string DBHelper::LuaGetInstanceName()
{
	return m_sName;
}

std::string DBHelper::LuaGetSysLangById(int langId)
{
	return SysLangDataManager::get_instance2()->GetSysLangById(langId);
}

std::string DBHelper::LuaGetResourcePathByID(int idx)
{
	return RESOURCEDAIDMANAGER->getDataByID(idx);
}

RoleInfoDataHandler * DBHelper::LuaGetRoleInfoDataHandler()
{
	return ROLEINFODATAHANDLER;
}

void DBHelper::LuaShowFlowEffect(int type,int count,int bjcount,int itemiconid)
{
	EFFECTDATAHANDLER->ShowFlowEffect(type, count, bjcount, itemiconid);
}