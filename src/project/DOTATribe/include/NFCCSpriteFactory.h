//Name: NFCCSpriteFactory
//Func: Used to Create CCSprite
//Written by: Johny

#ifndef __AutoCocos__NFCCSPRITEFACTORY__
#define __AutoCocos__NFCCSPRITEFACTORY__

#include <iostream>
#include "NodeFactoryManager.h"
#include "cocos-ext.h"


/*
	---->CCSprite
*/
class NFCCSpriteFactory:public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
	---->CCAnimationSprite
*/
class NFCCAnimationSpriteFactory:public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
	---->CSprite
*/
class NFCSpriteFactory:public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
	---->ScaleSprite
*/
class NFScaleSpriteFactory:public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
	---->CCScale9Sprite
*/
class NFCCScale9SpriteFactory:public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
	---->CTouchSprite
*/
class NFCTouchSpriteFactory:public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
	---->SceneEffect
*/
class NFSceneEffectFactory:public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
	---->CCornerNumIcon
*/
class NFCCornerNumIconFactory:public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
	---->CTitleSprite
*/
class NFCTitleSpriteFactory:public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
	---->CSpriteInSprite
*/
class NFCSpriteInSpriteFactory:public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

/*
	---->CExtGrapSprite
*/
class NFCExtGrapSpriteFactory:public NodeFactory {
public:
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};



//////////////////////////////////////////////////////////////////////////
//CSkeletonAnimation
//////////////////////////////////////////////////////////////////////////
class NFCSkeletonAnimationFactory: public NodeFactory{
public:
	virtual cocos2d::extension::CCSkeletonAnimation * createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};



//////////////////////////////////////////////////////////////////////////
//CAnimationSprite
//////////////////////////////////////////////////////////////////////////
  
class  NFCAnimationSpriteFactory: public NodeFactory{
public:
	virtual  cocos2d::CCNode*  createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};

//////////////////////////////////////////////////////////////////////////
//ParticelEffect
//////////////////////////////////////////////////////////////////////////
class  NFCParticelNodeFactory: public NodeFactory{
public:
	virtual  cocos2d::CCNode*  createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};


class  NFCCSimpleActionNodeFacrtory: public NodeFactory{
public:
	virtual  cocos2d::CCNode*  createNode(cocos2d::CCNode* parentNode,UIViewData* dd);
};




#endif 
