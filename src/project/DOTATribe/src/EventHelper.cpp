#include "../include/EventHelper.h"
#include "../include/LuaSystem.h"
#include "../include/EventSystem.h"

BaseHelper * EventHelper::m_pHelper = NULL;
std::string EventHelper::m_sName = "";

EventHelper::EventHelper()
{

}

EventHelper::~EventHelper()
{

}

void EventHelper::BuildInstance(std::string name, BaseHelper * helper)
{
	m_pHelper = helper;
	m_sName = name;
}

void EventHelper::RegisterLuaEvents()
{
	//将之前在Lua中缓存的注册事件，此时直接注册进游戏事件控制器，同时清空事件注册器
	std::multimap<int, std::string>::iterator it = m_mRegisterEvent.begin();
	std::multimap<int, std::string>::iterator it_end = m_mRegisterEvent.end();
	for(; it != it_end; ++it)
	{
		EVENTSYSTEM->RegisterEventHandler(it->first, LuaSystem::OnLuaEventHandler, it->second);
	}
	m_mRegisterEvent.clear();

}

BaseHelper * EventHelper::LuaGetInstance()
{
	return m_pHelper;
}

std::string EventHelper::LuaGetInstanceName()
{
	return m_sName;
}

void EventHelper::LuaRegisterEvent(int eventId, std::string ownerData)
{
	m_mRegisterEvent.insert(std::map<int, std::string>::value_type(eventId, ownerData));
}

void EventHelper::LuaPushEvent(int eventId)
{
	EVENTSYSTEM->PushEvent(eventId);
}

void EventHelper::LuaPushEvent(int eventId, std::string param0)
{
	EVENTSYSTEM->PushEvent(eventId, param0);
}

void EventHelper::LuaPushEvent(int eventId, std::string param0, std::string param1)
{
	EVENTSYSTEM->PushEvent(eventId, param0, param1);
}

void EventHelper::LuaPushEvent(int eventId, std::string param0, std::string param1, std::string param2)
{
	EVENTSYSTEM->PushEvent(eventId, param0, param1, param2);
}

void EventHelper::LuaPushEvent2(int eventId)
{
	EVENTSYSTEM->PushEvent2(eventId);
}

void EventHelper::LuaPushEvent2(int eventId, std::string param0)
{
	EVENTSYSTEM->PushEvent2(eventId, param0);
}

void EventHelper::LuaPushEvent2(int eventId, std::string param0, std::string param1)
{
	EVENTSYSTEM->PushEvent2(eventId, param0, param1);
}

void EventHelper::LuaPushEvent2(int eventId, std::string param0, std::string param1, std::string param2)
{
	EVENTSYSTEM->PushEvent2(eventId, param0, param1, param2);
}