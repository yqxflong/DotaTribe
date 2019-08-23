//Name: NFCCLabelFactory
//Func: Used to Create CCLabel
//Written by: Johny

#ifndef __AutoCocos__NFCCLABELFACTORY__
#define __AutoCocos__NFCCLABELFACTORY__

#include <iostream>
#include "NodeFactoryManager.h"
/*
	---->CCLabelTTF
*/
class NFCCLabelTTFFactory:public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
	---->CCLabelTTF   Mutiline
*/
class NFCCLabelTTFMultilineFactory:public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

class  NFCCTimeLabelFactory: public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

#endif 
