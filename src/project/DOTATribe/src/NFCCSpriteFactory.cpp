//Name: NFCCSpriteFactory
//Func: Used to Create CCSprite
//Written by: Johny

#include "../include/NFCCSpriteFactory.h"
#include "../include/CTouchSprite.h"
#include "../include/CDragSprite.h"
#include "../include/CSprite.h"
#include "../include/ScaleSprite.h"
#include "../include/CCornerNumIcon.h"
#include "../include/SceneEffect.h"
#include "../include/CCGrapSprite.h"
#include "../include/CAnimationSprite.h"
#include "../include/NFAnimationController.h"
#include "../include/CSimpleActionSprite.h"
#include "../include/NFControlsManager.h"




USING_NS_CC;
USING_NS_CC_EXT;

/*
	---->CSprite
*/
cocos2d::CCNode* NFCSpriteFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	CSprite* cc=CSprite::create(dd->filepath_);
	cc->setFilePath1(dd->filepath_);
	cc->setFilePath2(dd->filepath2_);
	cc->setFilePath3(dd->filepath3_);
	cc->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	cc->setVisible(isVisible);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	parentNode->addChild(cc,dd->zorder_);
	return cc;
}

/*
	---->ScaleSprite
*/
cocos2d::CCNode* NFScaleSpriteFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	ScaleSprite* cc=ScaleSprite::create(dd->filepath_);
	const CCSize & size = cc->getContentSize();
	float x = parentNode->getScaleX();
	cc->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	cc->setVisible(isVisible);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	parentNode->addChild(cc,dd->zorder_);
	return cc;
}

/*
	---->CCAnimationSprite
*/
cocos2d::CCNode* NFCCAnimationSpriteFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	CCNode* cc=CCAnimationSprite::create();
	cc->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	cc->setVisible(isVisible);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	parentNode->addChild(cc,dd->zorder_);
	return cc;
}

/*
	---->CCSprite
*/
cocos2d::CCNode* NFCCSpriteFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	return NFC_createSpriteByViewData(parentNode,*dd);
}

/*
	---->CCScale9Sprite
*/
cocos2d::CCNode* NFCCScale9SpriteFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	bool isVisible=dd->hide_==0?true:false;
	CCScale9Sprite* cc=CCScale9Sprite::create();
	cc->setProperty("File",dd->filepath_);
	cc->setPreferredSize(CCSizeMake(dd->width_,dd->height_));
	cc->setTag(dd->idx_);
	cc->setVisible(isVisible);
	if (dd->scale_!=1.0f)
		cc->setScale(dd->scale_);
	if (dd->rotation_!=0.0f)
		cc->setRotation(dd->rotation_);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	parentNode->addChild(cc,dd->zorder_);
	return cc;
}

/*
	---->CTouchSprite
*/
cocos2d::CCNode* NFCTouchSpriteFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	bool isSwallow=dd->swallow_==0?false:true;
	CTouchSprite* cc=CTouchSprite::create(dd->filepath_,NULL,dd->touchpriority_,isSwallow);
	cc->setTag(dd->idx_);
	cc->setSoundID(dd->soundid_);
	bool isVisible=dd->hide_==0?true:false;
	cc->setVisible(isVisible);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	parentNode->addChild(cc,dd->zorder_);
	return cc;
}

/*
	---->SceneEffect
*/
cocos2d::CCNode* NFSceneEffectFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	int effid=dd->colorR_;
	float delay=dd->rotation_;
	//
	SceneEffect* cc=SceneEffect::createWithEffectID(effid,delay);
	assert(cc!=NULL);
	cc->setTag(dd->idx_);
	cc->setZOrder(dd->zorder_);
	bool isVisible=dd->hide_==0?true:false;
	cc->setVisible(isVisible);
	if (dd->scale_!=1.0f)
		cc->setScale(dd->scale_);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	parentNode->addChild(cc);
	return cc;
}

/*
	---->CCornerNumIcon
*/
cocos2d::CCNode* NFCCornerNumIconFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	CCornerNumIcon* cc=CCornerNumIcon::create(dd->filepath_,dd->filepath2_,dd->filepath3_);
	cc->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	cc->setVisible(isVisible);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	cc->getNumLabel()->setFontName(dd->fontname_);
	cc->getNumLabel()->setFontSize(dd->fontsize_);
	cc->getNumLabel()->setColor(ccc3(dd->colorR_,dd->colorG_,dd->colorB_));
	parentNode->addChild(cc,dd->zorder_);
	return cc;
}


/*
	---->CTitleSprite
*/
cocos2d::CCNode* NFCTitleSpriteFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	bool isVisible=dd->hide_==0?true:false;
	CCLabelTTF* label=CCLabelTTF::create();
	label->setFontName(dd->fontname_);
	label->setFontSize(dd->fontsize_);
	label->setColor(ccc3(dd->colorR_,dd->colorG_,dd->colorB_));
	//
	CTitleSprite* cc=CTitleSprite::create(dd->filepath_,label);
	cc->setTag(dd->idx_);
	cc->setVisible(isVisible);
	if (dd->scale_!=1.0f)
		cc->setScale(dd->scale_);
	if (dd->rotation_!=0.0f)
		cc->setRotation(dd->rotation_);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	parentNode->addChild(cc,dd->zorder_);
	return cc;
}

/*
	---->CSpriteInSprite
*/
cocos2d::CCNode* NFCSpriteInSpriteFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	bool isVisible=dd->hide_==0?true:false;
	CCSprite* inner=CCSprite::create();
	inner->setProperty("File",dd->filepath2_);
	//
	CSpriteInSprite* cc=CSpriteInSprite::create(dd->filepath_,inner);
	inner->setPositionX(inner->getPositionX()+dd->width_);
	inner->setPositionY(inner->getPositionY()+dd->height_);
	cc->setTag(dd->idx_);
	cc->setVisible(isVisible);
	if (dd->scale_!=1.0f)
		cc->setScale(dd->scale_);
	if (dd->rotation_!=0.0f)
		cc->setRotation(dd->rotation_);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	parentNode->addChild(cc,dd->zorder_);
	return cc;
}


/*
	---->CExtGrapSprite
*/
cocos2d::CCNode* NFCExtGrapSpriteFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd)
{
	bool isGrapEnable=dd->colorR_==1 ? true:false;
	CCGrapSprite* cc=CCGrapSprite::createGrapSpriteWithFileName(dd->filepath_,isGrapEnable);
	cc->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	if (dd->scale_!=1.0f)
		cc->setScale(dd->scale_);
	if (dd->rotation_!=0.0f)
		cc->setRotation(dd->rotation_);
	cc->setVisible(isVisible);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	parentNode->addChild(cc,dd->zorder_);
	return cc;
} 

cocos2d::extension::CCSkeletonAnimation * NFCSkeletonAnimationFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd)
{  
	cocos2d::extension::CCSkeletonAnimation* cc=CCSkeletonAnimation::createWithFile(dd->filepath_,dd->filepath2_);
	cc->setTag(dd->idx_);
	bool isVisible=dd->hide_==0?true:false;
	if (dd->scale_!=1.0f)
	cc->setScale(dd->scale_);
	if (dd->rotation_!=0.0f)
	cc->setRotation(dd->rotation_);
	cc->setVisible(isVisible);
	cc->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	cc->setPosition(ccp(dd->posx_,dd->posy_));
	cc->setAnimation(dd->filepath3_,true);
	parentNode->addChild(cc,dd->zorder_);
	return cc;
}


cocos2d::CCNode *  NFCAnimationSpriteFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd)
{
	bool isLoopEffect=dd->colorG_>0 ? true:false;
	bool isPlayEffectInit=dd->colorB_ >0 ? true:false;
	bool isVisible=dd->hide_==0?true:false;
	CAnimationSprite * pAnimationSprite=CAnimationSprite::createAnimationSpriteByID(dd->colorR_,isLoopEffect);
	pAnimationSprite->setTag(dd->idx_);
	if (dd->rotation_!=0.0f)
	pAnimationSprite->setRotation(dd->rotation_);
	pAnimationSprite->setVisible(isVisible);
	pAnimationSprite->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	pAnimationSprite->setPosition(ccp(dd->posx_,dd->posy_));
	if(isPlayEffectInit)
	{   
		pAnimationSprite->PlayEffect();
	} 
	parentNode->addChild(pAnimationSprite,dd->zorder_);
	return  (cocos2d::CCNode *)pAnimationSprite;
}


cocos2d::CCNode*  NFCParticelNodeFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd)
{  
	bool isLoopEffect=dd->colorG_>0 ? true:false;
	bool isVisible=dd->hide_==0?true:false;
	CCParticleSystemQuad * pParticleNode=NFC_getParticelEffect(dd->colorR_,isLoopEffect);
	if(pParticleNode)
	{
		pParticleNode->setTag(dd->idx_);
		pParticleNode->setVisible(isVisible);
		pParticleNode->setPosition(ccp(dd->posx_,dd->posy_));
		pParticleNode->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
		parentNode->addChild(pParticleNode,dd->zorder_);
	} 
	return (cocos2d::CCNode *)pParticleNode;
}

cocos2d::CCNode*  NFCCSimpleActionNodeFacrtory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd)
{   
	bool isVisible=dd->hide_==0?true:false;
	std::vector<float> attachParam;
	attachParam.push_back(dd->width_);
	attachParam.push_back(dd->height_);
	CSimpleActionSprite  *  pSimpleActionSprite=CSimpleActionSprite::create(dd->colorR_,attachParam);
	if(pSimpleActionSprite)
	{
		pSimpleActionSprite->setTag(dd->idx_);
		pSimpleActionSprite->setProperty("File",dd->filepath_);
		pSimpleActionSprite->setScale(dd->scale_);
		if (dd->rotation_!=0.0f) 
		pSimpleActionSprite->setRotation(dd->rotation_);
		pSimpleActionSprite->SetInitPosition(ccp(dd->posx_,dd->posy_));
		pSimpleActionSprite->PlayAction();
		pSimpleActionSprite->setVisible(isVisible);
		parentNode->addChild(pSimpleActionSprite,dd->zorder_);
	}
	return pSimpleActionSprite;
}

 
