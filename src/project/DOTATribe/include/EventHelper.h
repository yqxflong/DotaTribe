//Name: EventHelper.h
//Function: 提供Lua使用UISystem中的部分功能接口
//Date: 20140313
//Author: fangjun

#ifndef _LUA_EVENTHELPER_H_
#define _LUA_EVENTHELPER_H_

#include <string>
#include <map>
#include "../include/BaseHelper.h"

class EventHelper:public BaseHelper
{
private:
	static BaseHelper * m_pHelper;
	static std::string  m_sName;

	std::multimap<int, std::string> m_mRegisterEvent;
public:
	EventHelper();
	virtual ~EventHelper();

	virtual void BuildInstance(std::string name, BaseHelper * helper);

	void RegisterLuaEvents();

public:
	static BaseHelper * LuaGetInstance();

	static std::string LuaGetInstanceName();

	void LuaRegisterEvent(int eventId, std::string ownerData);

	void LuaPushEvent(int eventId);
	
	void LuaPushEvent(int eventId, std::string param0);

	void LuaPushEvent(int eventId, std::string param0, std::string param1);

	void LuaPushEvent(int eventId, std::string param0, std::string param1, std::string param2);

	void LuaPushEvent2(int eventId);

	void LuaPushEvent2(int eventId, std::string param0);

	void LuaPushEvent2(int eventId, std::string param0, std::string param1);

	void LuaPushEvent2(int eventId, std::string param0, std::string param1, std::string param2);

};



#endif