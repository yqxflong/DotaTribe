//Name: NFCCLayerFactory
//Func: Used to Create CCLayer
//Written by: Johny

#ifndef __AutoCocos__NFCCLayerFactory__
#define __AutoCocos__NFCCLayerFactory__

#include <iostream>
#include "NodeFactoryManager.h"

class NFCCLayerFactory:public NodeFactory {
public:
    virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

class NFCCLayerColorFactory:public NodeFactory {
public:
    virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

class NFCPriorityLayerColorFactory:public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

#endif /* defined(__AutoCocos__NFCCLayerFactory__) */
