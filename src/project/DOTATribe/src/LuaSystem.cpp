//Name: LuaSystem.h
//Function:Lua辅助类初始化
//Author: fangjun
//Date: 20140313

#include "../include/LuaSystem.h"
#include <CCLuaEngine.h>
#include <script_support/CCScriptSupport.h>
#include "../include/DotaGameConfig.h"
#include "../include/LoggerSystem.h"

template<> LuaSystem* cobra_win::Singleton2<LuaSystem>::m_pMySelf = NULL;

int LuaSystem::m_nScriptOnEventHandler = 0;

LuaSystem::LuaSystem()
{
	m_mHelperMap.clear();

	//初始化脚本绑定事件
	m_nScriptInit = 0;
	m_nScriptTick = 0;
	m_nScriptDestroy = 0;
	m_nScriptOnPacketHandler = 0;
}

LuaSystem::~LuaSystem()
{

}

bool LuaSystem::Init()
{
	//初始化Lua引擎
	cocos2d::CCLuaEngine * pEngine = cocos2d::CCLuaEngine::defaultEngine();
	cocos2d::CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);

	cocos2d::CCLuaStack *pStack = pEngine->getLuaStack();
	lua_State *tolua_s = pStack->getLuaState();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)    
	pStack = pEngine->getLuaStack();
	tolua_s = pStack->getLuaState();
#endif

#ifdef kENABLE_PLATFORM_LUA

	//注册辅助类
	RegisterHelper("luaUIHelper", new luaUIHelper);
	RegisterHelper("DBHelper", new DBHelper);
	RegisterHelper("EventHelper", new EventHelper);
	RegisterHelper("PacketHelper", new PacketHelper);


	//初始化辅助类实例
	std::map<std::string, BaseHelper *>::iterator it = m_mHelperMap.begin();
	std::map<std::string, BaseHelper *>::iterator it_end = m_mHelperMap.end();
	for(; it != it_end; ++it)
	{
		it->second->BuildInstance(it->first, it->second);
	}

	//设置lua环境的加密选项
	bool bLuaEncryptioned = false;
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "SYS", "LuaEncryptioned", bLuaEncryptioned);
	cocos2d::CCLuaEngine::defaultEngine()->setScriptEncryption(bLuaEncryptioned);
	cocos2d::CCLuaEngine::defaultEngine()->setScriptEncryptionKey("dtlmcclua");

	if(!this->LoadScriptFile("resource/script/LuaSystem.lua"))
	{
		return false;
	}

	//走lua的Init
	if (m_nScriptInit)
	{
		cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEvent(m_nScriptInit, "Init");
	}

#endif

	return true;
}

void LuaSystem::Tick()
{
#ifdef kENABLE_PLATFORM_LUA


	if (m_nScriptTick)
	{
		cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEvent(m_nScriptTick, "Tick");
	}
#endif
}

void LuaSystem::Destroy()
{
#ifdef kENABLE_PLATFORM_LUA

	if (m_nScriptDestroy)
	{
		cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEvent(m_nScriptDestroy, "Destroy");
	}


	//清空辅助类实例
	std::map<std::string, BaseHelper *>::iterator it = m_mHelperMap.begin();
	std::map<std::string, BaseHelper *>::iterator it_end = m_mHelperMap.end();
	for(; it != it_end; ++it)
	{
		delete it->second;
	}
	m_mHelperMap.clear();
#endif

}

void LuaSystem::RegisterHelper(std::string name, BaseHelper * helper)
{
#ifdef kENABLE_PLATFORM_LUA

	m_mHelperMap.insert(std::map<std::string, BaseHelper *>::value_type(name, helper));
#endif
}

void LuaSystem::RegisterLuaViewFile()
{
#ifdef kENABLE_PLATFORM_LUA

	BaseHelper * h = m_mHelperMap.find(luaUIHelper::LuaGetInstanceName())->second;
	luaUIHelper * uiHelper = (luaUIHelper *)h;
	uiHelper->LoadViewFile();
#endif
}

void LuaSystem::RegisterLuaEvents()
{
#ifdef kENABLE_PLATFORM_LUA

	BaseHelper * h = m_mHelperMap.find(EventHelper::LuaGetInstanceName())->second;
	EventHelper * eventHelper = (EventHelper *)h;
	eventHelper->RegisterLuaEvents();

#endif
}

void LuaSystem::OnLuaEventHandler(int iEventType, std::string owerData, std::list<std::string>& paramList)
{
#ifdef kENABLE_PLATFORM_LUA

	if(m_nScriptOnEventHandler)
	{
		cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEvent(m_nScriptOnEventHandler, "OnLuaEventHandler", iEventType, owerData, paramList);
	}
#endif
}

bool LuaSystem::IsLuaPacket(int packetType)
{
#ifdef kENABLE_PLATFORM_LUA

	BaseHelper * h = m_mHelperMap.find(PacketHelper::LuaGetInstanceName())->second;
	PacketHelper * packetHelper = (PacketHelper *)h;
	return packetHelper->IsLuaPacket(packetType);
#else
	return false;
#endif
}

bool LuaSystem::OnLuaPacketHandler(unsigned short pn, cobra_win::DPacket * packet)
{

#ifdef kENABLE_PLATFORM_LUA

	//将Packet对象传递给PacketHelper，形成Packet解析方法
	BaseHelper * h = m_mHelperMap.find(PacketHelper::LuaGetInstanceName())->second;
	PacketHelper * packetHelper = (PacketHelper *)h;
	packetHelper->SetRecievedDPacket(pn, packet);

	if(m_nScriptOnPacketHandler)
	{
		cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEvent(m_nScriptOnPacketHandler, "OnLuaPacketHandler");
		return true;
	}
	else
	{
		return false;
	}

#else
	return false;
#endif
}

bool LuaSystem::LoadScriptFile(std::string fileName) 
{ 
	char buffer[1024] = ""; 
	sprintf(buffer, "require \"%s\"", fileName.c_str()); 
	if (cocos2d::CCLuaEngine::defaultEngine()->executeString(buffer) != 0) 
	{ 
		LOGGERSYSTEM->LogError("Load Lua File Failed, ScriptFile=%s\n", fileName.c_str()); 
		return false; 
	} 

	return true; 
}



LuaSystem * LuaSystem::LuaGetInstance()
{
	return LUASYSTEM;
}

std::string LuaSystem::LuaGetInstanceName()
{
	return "LuaSystem";
}

void LuaSystem::LuaRegisterInitScript(int nHandler)
{

#ifdef kENABLE_PLATFORM_LUA

	//去除之前的事件
	if (m_nScriptInit)
	{
		cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nScriptInit);
		LUALOG("[LUA] Remove Init script handler: %d", m_nScriptInit);
		m_nScriptInit = 0;
	}

	//加入当前的事件
	m_nScriptInit = nHandler;

#endif
}

void LuaSystem::LuaRegisterTickScript(int nHandler)
{

#ifdef kENABLE_PLATFORM_LUA

	//去除之前的事件
	if (m_nScriptTick)
	{
		cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nScriptTick);
		LUALOG("[LUA] Remove Tick script handler: %d", m_nScriptTick);
		m_nScriptInit = 0;
	}

	//加入当前的事件
	m_nScriptTick = nHandler;

#endif
}

void LuaSystem::LuaRegisterDestroyScript(int nHandler)
{

#ifdef kENABLE_PLATFORM_LUA

	//去除之前的事件
	if (m_nScriptDestroy)
	{
		cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nScriptDestroy);
		LUALOG("[LUA] Remove Destroy script handler: %d", m_nScriptDestroy);
		m_nScriptInit = 0;
	}

	//加入当前的事件
	m_nScriptDestroy = nHandler;

#endif
}

void LuaSystem::LuaRegisterOnEventHandlerScript(int nHandler)
{

#ifdef kENABLE_PLATFORM_LUA

	//去除之前的事件
	if (m_nScriptOnEventHandler)
	{
		cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nScriptOnEventHandler);
		LUALOG("[LUA] Remove OnEventHandler script handler: %d", m_nScriptOnEventHandler);
		m_nScriptInit = 0;
	}

	//加入当前的事件
	m_nScriptOnEventHandler = nHandler;

#endif
}

void LuaSystem::LuaRegisterOnPacketHandlerScript(int nHandler)
{
#ifdef kENABLE_PLATFORM_LUA


	if(m_nScriptOnPacketHandler)
	{
		cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nScriptOnPacketHandler);
		LUALOG("[LUA] Remove OnPacketHandler script handler: %d", m_nScriptOnPacketHandler);
		m_nScriptInit = 0;
	}
	
	m_nScriptOnPacketHandler = nHandler;

#endif
}