//Name: LuaSystem.h
//Function:Lua�������ʼ��
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
		�ű��¼�
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
		��ʼ���¼���Ӧ����ϵͳ
	*/
	bool   Init();
	/*
		�¼���Ӧ����ϵͳ�����
	*/
	void   Tick();
	/*
		�����¼���Ӧ����ϵͳ
	*/
	void   Destroy();

private:
	void RegisterHelper(std::string name, BaseHelper * helper);

public:
	//����Ϊ�ṩcxx�ڲ�ʹ�ýӿ�
	/*
		�ṩUIVIewDataMananger��ʼ��ʱע��Lua�еĲ����ļ�
	*/
	void RegisterLuaViewFile();

	/*
		�ṩEventSystem��Luaע���¼�
	*/
	void RegisterLuaEvents();
	
	//c++ʱ����Ӧ�������˺����ṩת����lua��ʽ
	static void OnLuaEventHandler(int iEventType, std::string owerData, std::list<std::string>& paramList);
	
	//�ж�������յİ��Ƿ���lua��ע��İ�
	bool IsLuaPacket(int packetType);

	bool OnLuaPacketHandler(unsigned short pn, cobra_win::DPacket * packet);

	bool LoadScriptFile(std::string fileName);

public:
	//����Ϊ�ṩluaʹ�ýӿ�
	/*
		���LuaSystemʵ��
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
