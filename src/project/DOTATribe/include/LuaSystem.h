//Name: LuaSystem.h
//Function:Lua辅助类初始化
//Author: fangjun
//Date: 20140313

#ifndef _DOTATRIBE_LUASYSTEM_H_
#define _DOTATRIBE_LUASYSTEM_H_

#include <include/common/Singleton.h>
#include "../include/UIHelper.h"
#include "../include/DBHelper.h"
#include "../include/PacketHelper.h"
#include "../include/EventHelper.h"
#include "../include/BaseHelper.h"
#include <map>
#include <string>
#include <include/mem/DPacket.h>

using namespace cobra_win;
class LuaSystem : public cobra_win::Singleton2<LuaSystem>
{
private:
	std::map<std::string, BaseHelper *> m_mHelperMap;

private:
	/*
		脚本事件
	*/
	int m_nScriptInit;	
	int m_nScriptTick;
	int m_nScriptDestroy;

	static int m_nScriptOnEventHandler;
	int m_nScriptOnPacketHandler;

public:
	LuaSystem();

	virtual ~LuaSystem();

public:
	/*
		初始化事件响应处理系统
	*/
	bool   Init();
	/*
		事件响应处理系统桢更新
	*/
	void   Tick();
	/*
		销毁事件响应处理系统
	*/
	void   Destroy();

private:
	void RegisterHelper(std::string name, BaseHelper * helper);

public:
	//以下为提供cxx内部使用接口
	/*
		提供UIVIewDataMananger初始化时注册Lua中的布局文件
	*/
	void RegisterLuaViewFile();

	/*
		提供EventSystem的Lua注册事件
	*/
	void RegisterLuaEvents();
	
	//c++时间响应函数，此函数提供转发至lua方式
	static void OnLuaEventHandler(int iEventType, std::string owerData, std::list<std::string>& paramList);
	
	//判断这个接收的包是否是lua中注册的包
	bool IsLuaPacket(int packetType);

	bool OnLuaPacketHandler(unsigned short pn, cobra_win::DPacket * packet);

	bool LoadScriptFile(std::string fileName);

public:
	//以下为提供lua使用接口
	/*
		获得LuaSystem实例
	*/
	static LuaSystem * LuaGetInstance();

	static std::string LuaGetInstanceName();

	void LuaRegisterInitScript(int nHandler);

	void LuaRegisterTickScript(int nHandler);

	void LuaRegisterDestroyScript(int nHandler);

	void LuaRegisterOnEventHandlerScript(int nHandler);

	void LuaRegisterOnPacketHandlerScript(int nHandler);

public:
	friend  class  cobra_win::Singleton2<LuaSystem>;
};

#define LUASYSTEM (LuaSystem::get_instance2())

#endif
