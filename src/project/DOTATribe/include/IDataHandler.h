//Name��IDataHandler
//Function�����ڶ���DataHandlerͳһ�ӿ�		    
//Written By����ǿ
#ifndef   _DOTATRIBE_IDATAHANDLER_H
#define   _DOTATRIBE_IDATAHANDLER_H

#include "../include/IPacket.h"
#include <vector>
#include <CCLuaEngine.h>

class IDataHandler{
public:
	IDataHandler(){
		m_vecLuaFuncReult.clear();
		m_nLuaHandler1=0;
		m_nLuaHandler2=0;
		m_nLuaHandler3=0;
		m_nLuaHandler4=0;
		m_nLuaHandler5=0;
		m_nLuaHandler6=0;
		m_nLuaHandler7=0;
		m_nLuaHandler8=0;
		m_nLuaHandler9=0;
		m_nLuaHandler10=0;
	}
	virtual ~IDataHandler(){};
	/*
		���յ���������ذ���ʱ���ô˺����Ѷ�Ӧ��������ת���ɶ�Ӧ�����ݽṹ
		����map�У�����֮����ڴ��е���ɾ�Ĳ�
	*/
	virtual void handlePacket(IPacket* packet){};

	/*
		���ٽӿ�
	*/
	virtual void onDestroy()=0;	

	/*
		��ʼ���ӿ�
	*/
	virtual bool init()=0;



/*
	#����ע��lua��func��handler
	#
	#Ŀǰ���Խ׶�
*/
public:
	void RegisterLuaHandler1(int nHandler){
		if (m_nLuaHandler1)
			cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nLuaHandler1);
		m_nLuaHandler1 = nHandler;
	}
	void RegisterLuaHandler2(int nHandler){
		if (m_nLuaHandler2)
			cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nLuaHandler2);
		m_nLuaHandler2 = nHandler;
	}
	void RegisterLuaHandler3(int nHandler){
		if (m_nLuaHandler3)
			cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nLuaHandler3);
		m_nLuaHandler3 = nHandler;
	}
	void RegisterLuaHandler4(int nHandler){
		if (m_nLuaHandler4)
			cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nLuaHandler4);
		m_nLuaHandler4 = nHandler;
	}
	void RegisterLuaHandler5(int nHandler){
		if (m_nLuaHandler5)
			cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nLuaHandler5);
		m_nLuaHandler5 = nHandler;
	}
	void RegisterLuaHandler6(int nHandler){
		if (m_nLuaHandler6)
			cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nLuaHandler6);
		m_nLuaHandler6 = nHandler;
	}
	void RegisterLuaHandler7(int nHandler){
		if (m_nLuaHandler7)
			cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nLuaHandler7);
		m_nLuaHandler7 = nHandler;
	}
	void RegisterLuaHandler8(int nHandler){
		if (m_nLuaHandler8)
			cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nLuaHandler8);
		m_nLuaHandler8 = nHandler;
	}
	void RegisterLuaHandler9(int nHandler){
		if (m_nLuaHandler9)
			cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nLuaHandler9);
		m_nLuaHandler9 = nHandler;
	}
	void RegisterLuaHandler10(int nHandler){
		if (m_nLuaHandler10)
			cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nLuaHandler10);
		m_nLuaHandler10 = nHandler;
	}
	//
	//lua��Cpp��������װ���
	//ֻ�ܴ�������ͣ��Զ�������Ҫ����ʵ��
	void PushInt_LuaFunc_Result(int ret){
		void* item=(void*)ret;
		m_vecLuaFuncReult.push_back(item);
	}
public:
	//�洢����lua�����ķ���ֵ
	std::vector<void*> m_vecLuaFuncReult;

	int m_nLuaHandler1;		
	int m_nLuaHandler2;		
	int m_nLuaHandler3;		
	int m_nLuaHandler4;		
	int m_nLuaHandler5;		
	int m_nLuaHandler6;		
	int m_nLuaHandler7;		
	int m_nLuaHandler8;		
	int m_nLuaHandler9;		
	int m_nLuaHandler10;	

	void clearLuaFuncResultStack(){
		m_vecLuaFuncReult.clear();
	}
};
#endif