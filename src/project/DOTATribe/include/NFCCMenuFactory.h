//Name: NFCCMenuFactory
//Func: Used to Create CCLabel
//Written by: Johny

#ifndef __AutoCocos__NFCCMENUFACTORY__
#define __AutoCocos__NFCCMENUFACTORY__

#include <iostream>
#include "NodeFactoryManager.h"

/*
	---->CMenuItemSprite  Single Img
*/
class NFCMenuItemSpriteSIFactory:public NodeFactory{
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
	FAnimationButton
*/
class NFFAnimationButtonFactory:public NodeFactory
{
	virtual cocos2d::CCNode * createNode(cocos2d::CCNode * parentNode, UIViewData * dd);
};


/*
	---->CMenuItemSprite	Normal
*/
class NFCMenuItemSpriteFactory:public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
	---->CLabelButton	Normal
*/
class NFCLabelButtonFactory:public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
	---->CMenuItemSprite  Normal+Selected
*/
class NFCMenuItemSpriteSelectedFactory:public NodeFactory{
public:
	cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};


/*
	---->CImMenuItemSpriteSI  Normal
*/
class	CImMenuItemSpriteSIFactory:public NodeFactory{
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
	---->CImMenuItemSprite  Normal
*/
class	CImMenuItemSpriteFactory:public NodeFactory{
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
	---->CImMenuItemSprite  Normal+Selected
*/
class NFCImMenuItemSpriteSelectedFactory:public NodeFactory{
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};
/*
	---->CTabMenuItemSprite  Normal
*/
class CTabMenuItemSpriteFactory:public NodeFactory{
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
	---->CTabMenuItemSprite  Normal+Selected
*/
class NFCTabImmovableMenuItemSpriteSelectedFactory:public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
	---->HWMoreItem			(Just for HomeWindow)
*/
class NFHWMoreItemFactory:public NodeFactory{

	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};


#endif 
