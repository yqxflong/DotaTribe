//Name: NFDTBoardFactory
//Func: Used to Create DTBoard
//Written by: Johny

#ifndef __AutoCocos__NFDTBoardFactory__
#define __AutoCocos__NFDTBoardFactory__

#include <iostream>
#include "NodeFactoryManager.h"

/*
	装备组合框
*/
class NFDTEquipBoardFactory:public NodeFactory{
public:
	cocos2d::CCNode * createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
	奖励组合框
*/
class NFDTAwardBoardFactory:public NodeFactory{
public:
	cocos2d::CCNode * createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};


/*
	英雄图像
*/
class NFDTHeroIconFactory:public NodeFactory{
public:
	cocos2d::CCNode * createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

#endif