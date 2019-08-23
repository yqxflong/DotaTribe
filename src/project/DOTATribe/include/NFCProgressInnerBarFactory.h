//Name: NFCProgressInnerBarFactory
//Func: Used to Create NFCProgressInnerBar
//Written by: Johny

#ifndef __AutoCocos__NFCProgressInnerBarFactory__
#define __AutoCocos__NFCProgressInnerBarFactory__

#include <iostream>
#include "NodeFactoryManager.h"
/*
	---->CProgressInnerBar
*/
class NFCProgressInnerBarFactory:public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
	---->CCProgressTimer
*/
class NFCCProgressTimerFactory:public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
	---->CProgressTimer
*/
class NFCProgressTimerFactory:public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};


#endif 
