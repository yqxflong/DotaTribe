//Name: NFCCTableViewFactory
//Func: Used to Create CCTableView
//Written by: Johny

#ifndef __AutoCocos__NFCCTABLEVIEWFACTORY__
#define __AutoCocos__NFCCTABLEVIEWFACTORY__

#include <iostream>
#include "NodeFactoryManager.h"
/*
	---->CCTableView
*/
class NFCCTableViewFactory:public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
	---->CTableView
*/
class NFCTableViewFactory:public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
	---->CScrollView
*/
class NFCScrollViewFactory:public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
	---->CMapScrollView
*/
class NFCMapScrollViewFactory:public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};


#endif 
