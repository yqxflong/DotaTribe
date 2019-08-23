//Name: NFCCEditBoxFactory
//Func: Used to Create CCEditBox
//Written by: Johny

#ifndef __AutoCocos__NFCCEditBoxFactory__
#define __AutoCocos__NFCCEditBoxFactory__

#include <iostream>
#include "NodeFactoryManager.h"

/*
	---->CCEditBox
*/
class NFCCEditBoxFactory:public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

#endif 