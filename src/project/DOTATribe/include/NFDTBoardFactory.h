//Name: NFDTBoardFactory
//Func: Used to Create DTBoard
//Written by: Johny

#ifndef __AutoCocos__NFDTBoardFactory__
#define __AutoCocos__NFDTBoardFactory__

#include <iostream>
#include "NodeFactoryManager.h"

/*
	װ����Ͽ�
*/
class NFDTEquipBoardFactory:public NodeFactory{
public:
	cocos2d::CCNode * createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
	������Ͽ�
*/
class NFDTAwardBoardFactory:public NodeFactory{
public:
	cocos2d::CCNode * createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};


/*
	Ӣ��ͼ��
*/
class NFDTHeroIconFactory:public NodeFactory{
public:
	cocos2d::CCNode * createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

#endif