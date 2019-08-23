//Name��NFToolController
//Function������ؼ���һЩ����
//Written By����ǿ

#ifndef  _DOTATRIBE_NFToolController_H_
#define  _DOTATRIBE_NFToolController_H_

#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/IDataManager.h"
#include "../include/LoggerSystem.h"
#include <include/mem/DPacket.h>

/**
	*����ע�ᴥ�����ȼ�
*/
static void NFC_ReRegisterTouchPriority(cocos2d::CCTouchDelegate* pDel,int priority,bool swallow)
{
	cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(pDel);
	cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(pDel,priority, swallow);
}


/*
	�������е�string
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

	//�滻<br>���з�
	containStrBuffer = _rich_text_parser_(containStrBuffer);
}

/*
	Log��ݷ�ʽ
*/
static void NFC_LogMessage(char* logMsg){
	LOGGERSYSTEM->LogInfo(logMsg);
}

#endif