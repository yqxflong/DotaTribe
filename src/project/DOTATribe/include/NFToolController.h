//Name：NFToolController
//Function：管理控件的一些操作
//Written By：尹强

#ifndef  _DOTATRIBE_NFToolController_H_
#define  _DOTATRIBE_NFToolController_H_

#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/IDataManager.h"
#include "../include/LoggerSystem.h"
#include <include/mem/DPacket.h>

/**
	*重新注册触摸优先级
*/
static void NFC_ReRegisterTouchPriority(cocos2d::CCTouchDelegate* pDel,int priority,bool swallow)
{
	cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(pDel);
	cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(pDel,priority, swallow);
}


/*
	解析包中的string
*/
static void   NFC_ParsePacketString(cobra_win::DPacket & packet,std::string & containStrBuffer)
{
	unsigned short strlen = 0;
	char * str = NULL;
	packet.read(strlen); 
	str = new char[strlen+1];
	packet.read(str, strlen);
	str[strlen] = '\0';
	containStrBuffer=str;
	delete[] str;
	str = NULL;

	//替换<br>换行符
	containStrBuffer = _rich_text_parser_(containStrBuffer);
}

/*
	Log快捷方式
*/
static void NFC_LogMessage(char* logMsg){
	LOGGERSYSTEM->LogInfo(logMsg);
}

#endif