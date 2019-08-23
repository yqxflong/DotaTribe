//Name: NFCCNodeFactory
//Func: Used to Create CCNode
//Written by: Johny

#ifndef __AutoCocos__NFCCNodeFactory__
#define __AutoCocos__NFCCNodeFactory__

#include <iostream>
#include "NodeFactoryManager.h"

class NFCCNodeFactory:public NodeFactory {
public:
    cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

class NFMaskNodeFactory:public NodeFactory{
public:
	cocos2d::CCNode * createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
	星级节点
*/
class NFStarLevelNodeFactory:public NodeFactory{
public:
	cocos2d::CCNode * createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
   灰色星星结点
*/
class NFGrapStarsProgressFactory : public NodeFactory
{
public:
	cocos2d::CCNode * createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};
#endif /* defined(__AutoCocos__NFCCNodeFactory__) */
