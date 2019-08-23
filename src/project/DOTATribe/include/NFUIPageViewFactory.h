//Name: NFUIPageViewFactory
//Func: Used to Create UIPageView
//Written by: Johny

#ifndef __AutoCocos__NFUIPAGEVIEWFACTORY__
#define __AutoCocos__NFUIPAGEVIEWFACTORY__
#include <iostream>
#include "NodeFactoryManager.h"

/*
	---->UIPageView
*/
class NFUIPageViewFactory:public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};


#endif 