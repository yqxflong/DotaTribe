//Name: SceneEffect
//Func: Used to Create SceneEffect
//Written by: Johny

#include "../include/SceneEffect.h"
#include "../include/AnimationFileDataManager.h"
#include "../include/EngineSystem.h"
#include "../include/AnimationEffect.h"
USING_NS_CC;

SceneEffect::SceneEffect(){
	m_nEffectID=0;
	m_fDelay=0.0f;
}

SceneEffect* SceneEffect::createWithEffectID(int effectID,float delay){
	SceneEffect* cc=new SceneEffect();
	if (cc&&cc->initWithEffectID(effectID,delay))
	{
		cc->autorelease();
		return cc;
	}
	delete cc;cc=NULL;
	return cc;
}

bool SceneEffect::initWithEffectID(int effectID,float delay){
	if (!CCSprite::init()||!_setAction(effectID,delay))
		return false;

	m_nEffectID=effectID;
	m_fDelay=delay;
	return true;
}

bool SceneEffect::_setAction(int effectID,float delay){
	AnimationFileData *  pAnimationFileData=AnimationFileDataManager::get_instance2()->GetAnimationByIdx(effectID);
	cocos2d::CCAnimation * pAnimation=EngineSystem::get_instance2()->GetAnimtionByName(pAnimationFileData->mAnimationName);
	if(pAnimation==NULL)return false;
	this->setScale(pAnimationFileData->mAnimationScale);
	CCAnimationEffect   *  pAnimationEffect=CCAnimationEffect::create(this,pAnimation);
	if (!pAnimationEffect)return false;
	if (delay>0)
	{
		CCDelayTime * pDelayTime=CCDelayTime::create(delay);
		CCActionInterval * pSequence=CCSequence::createWithTwoActions(pAnimationEffect,pDelayTime);
		CCRepeatForever * pfor=CCRepeatForever::create(pSequence);
		this->runAction(pfor);	
	}else{//ÎÞÏÞ·Å
		CCRepeatForever * pfor=CCRepeatForever::create(pAnimationEffect);
		this->runAction(pfor);	
	}
	return true;
}

SceneEffect* SceneEffect::clone(){
	SceneEffect* cc=SceneEffect::createWithEffectID(m_nEffectID,m_fDelay);
	cc->setTag(this->getTag());
	cc->setZOrder(this->getZOrder());
	cc->setVisible(this->isVisible());
	cc->setAnchorPoint(this->getAnchorPoint());
	cc->setPosition(this->getPosition());
	return cc;
}

void SceneEffect::ReplayAction(){
	this->stopAllActions();
	_setAction(m_nEffectID,m_fDelay);
}