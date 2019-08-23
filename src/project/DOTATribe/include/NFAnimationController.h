//Name��NFAmimationController
//Function������ؼ���һЩ����
//Written By����ǿ

#ifndef  _DOTATRIBE_NFAmimationController_H_
#define  _DOTATRIBE_NFAmimationController_H_

#include <cocos2d.h>
#include "../include/DOTATribeApp.h"
#include "../include/CPublicVarReader.h"
#include "../include/ClientConstDataManager.h"
#include "../include/NFControlsManager.h"
#include "../include/VariableSpeedSequenceAction.h"
#include "../include/PreCCMoveTo.h"
#include "../include/CallFuncAction.h"
#include "../include/ParticleDataManager.h"
#include "../include/CSimpleActionSprite.h"







//////////////////////////////////////////////////////////////////////////
// Frame Animation Manager Begin  (��Ч�ӿڼ���)

//���ѭ��֡����Sprite
//////////////////////////////////////////////////////////////////////////
static  cocos2d::CCSprite *  NFC_getLoopFrameEffect(int animationID)
{
	cocos2d::CCSprite * pFrameEffect=cocos2d::CCSprite::create();
	cocos2d::CCAnimation * pAnimation=EngineSystem::get_instance2()->GetAnimationByID(animationID);
	AnimationFileData* pAnimationData = AnimationFileDataManager::get_instance2()->GetAnimationByIdx(animationID);
	pFrameEffect->setScale(pAnimationData->mAnimationScale);
	CCAnimationEffect * pAnimationEffect=CCAnimationEffect::create(pFrameEffect,pAnimation);
	cocos2d::CCRepeatForever * pRepeatAction=cocos2d::CCRepeatForever::create(pAnimationEffect);  
	pFrameEffect->runAction(pRepeatAction);
	return pFrameEffect;
}


//////////////////////////////////////////////////////////////////////////
//����������ĵ�UnLoop����
//param1: ����ID
//////////////////////////////////////////////////////////////////////////
static cocos2d::CCSprite * NFC_getUnLoopFrameEffect(int animationID)
{
	cocos2d::CCSprite * pFrameEffect=cocos2d::CCSprite::create();
	cocos2d::CCAnimation * pAnimation=EngineSystem::get_instance2()->GetAnimationByID(animationID);
	AnimationFileData* pAnimationData = AnimationFileDataManager::get_instance2()->GetAnimationByIdx(animationID);
	pFrameEffect->setScale(pAnimationData->mAnimationScale);
	CCAnimationEffect * pAnimationEffect=CCAnimationEffect::create(pFrameEffect,pAnimation);
	pAnimationEffect->setUnLoopAutoRemove(true);
	pFrameEffect->runAction(pAnimationEffect);
	return pFrameEffect;
}


//////////////////////////////////////////////////////////////////////////
//��ȡ��ѭ������Sprite
//param1: ����ID   
//param2: �ص�����  ����֪ͨ��Ч�ر� �ص����� �������ָ��  pDelegate ����ǿ�
static cocos2d::CCSprite * NFC_getUnLoopFrameEffect(int animationID,AnimationEffectCallBackProtocol * pDelegate)
{
	if(pDelegate)
	{
		cocos2d::CCSprite * pFrameEffect=cocos2d::CCSprite::create();
		cocos2d::CCAnimation * pAnimation=EngineSystem::get_instance2()->GetAnimationByID(animationID);
		AnimationFileData* pAnimationData = AnimationFileDataManager::get_instance2()->GetAnimationByIdx(animationID);
		pFrameEffect->setScale(pAnimationData->mAnimationScale);
		CCAnimationEffect * pAnimationEffect=CCAnimationEffect::create(pFrameEffect,pAnimation,pDelegate);
		pFrameEffect->runAction(pAnimationEffect);
		return pFrameEffect;
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
//��ȡ��ѭ������Sprite
//param1:����ID
//param2:�ص����� �����¼�֪ͨ �ص����� �������ָ��
//param3:��ʱ�ص�ʱ��  ��λs       
//////////////////////////////////////////////////////////////////////////
static cocos2d::CCSprite * NFC_getUnLoopFrameEffect(int animationID,AnimationEffectCallBackProtocol * pDelegate,float callTime)
{ 
	if(pDelegate)
	{
		cocos2d::CCSprite * pFrameEffect=cocos2d::CCSprite::create();
		cocos2d::CCAnimation * pAnimation=EngineSystem::get_instance2()->GetAnimationByID(animationID);
		AnimationFileData* pAnimationData = AnimationFileDataManager::get_instance2()->GetAnimationByIdx(animationID);
		pFrameEffect->setScale(pAnimationData->mAnimationScale);
		PAnimation_Call_Node pAnimationCallNode=new Animation_CALL_Node();
		PCallBack_Node pCallBackNode=new CallBack_Node();
		pCallBackNode->callBackTime=callTime;
		pCallBackNode->eventType=_Animation_Timer_Triger_Event_;
		pAnimationCallNode->callBackVec.push_back(pCallBackNode);
		CCAnimationEffect * pAnimationEffect=CCAnimationEffect::create(pFrameEffect,pAnimation,pDelegate,pAnimationCallNode);
		pFrameEffect->runAction(pAnimationEffect);
		return pFrameEffect;
	}
	return NULL;
}
//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//��ȡ��ѭ������Sprite
//param1:����ID
//param2:�ص����� �����¼�֪ͨ �ص����� �������ָ��
//param3:��ʱ�ص�ʱ��  ��λs
//param4:��ʱ�ص�ʱ��2 ��λs
//////////////////////////////////////////////////////////////////////////
static cocos2d::CCSprite * NFC_getUnLoopFrameEffect(int animationID,AnimationEffectCallBackProtocol * pDelegate,float callTime1,float callTime2)
{    
	if(pDelegate)
	{
		cocos2d::CCSprite * pFrameEffect=cocos2d::CCSprite::create();
		cocos2d::CCAnimation * pAnimation=EngineSystem::get_instance2()->GetAnimationByID(animationID);
		AnimationFileData* pAnimationData = AnimationFileDataManager::get_instance2()->GetAnimationByIdx(animationID);
		pFrameEffect->setScale(pAnimationData->mAnimationScale);
		PAnimation_Call_Node pAnimationCallNode=new Animation_CALL_Node();
		PCallBack_Node pCallBackNode=new CallBack_Node();
		pCallBackNode->callBackTime=callTime1;
		pCallBackNode->eventType=_Animation_Timer_Triger_Event_;
		PCallBack_Node pCallBackNode2=new CallBack_Node();
		pCallBackNode2->callBackTime=callTime2;
		pCallBackNode2->eventType=_Animation_Timer_Triger_Event_02_; 
		pAnimationCallNode->callBackVec.push_back(pCallBackNode);
		pAnimationCallNode->callBackVec.push_back(pCallBackNode2);
		CCAnimationEffect * pAnimationEffect=CCAnimationEffect::create(pFrameEffect,pAnimation,pDelegate,pAnimationCallNode);
		pFrameEffect->runAction(pAnimationEffect);
		return pFrameEffect;
	}
	return NULL;
}


//////////////////////////////////////////////////////////////////////////
// CAnimationSprite ��ؽӿ�
//////////////////////////////////////////////////////////////////////////
static   CAnimationSprite * NFC_getAnimationSprite(int animationID,bool isLoopEffect,bool isPlayEffectAddParent ,AnimationEffectCallBackProtocol * pDelegate)
{ 
	CAnimationSprite * pAnimationSprite=CAnimationSprite::createAnimationSpriteByID(animationID,isLoopEffect,pDelegate);
	if(isPlayEffectAddParent)
	{
		pAnimationSprite->PlayEffect();
	}
	return pAnimationSprite;
}
 
static  void   NFC_PlayEffet(int uiIndex,cocos2d::CCNode * pParent,bool isPlayEffect)
{
	CAnimationSprite * pAnimationSprite = (CAnimationSprite *)pParent->getChildByTag(uiIndex);
	if(pAnimationSprite)
	{
		if(isPlayEffect)
		{ 
			pAnimationSprite->PlayEffect();
		}
		else
		{ 
			pAnimationSprite->StopEffect();
		}
	}
}

/*
��������  ��ԭɫ��͸��  
*/
static   void   NFC_skeletonTransparentAction(cocos2d::extension::CCSkeletonAnimation * pSkeletonAnimation,float actionTime)
{  
	GradualColorAction * pFadeOutAction=GradualColorAction::create(actionTime,255,255,255,0);
	pSkeletonAnimation->runAction(pFadeOutAction);
}


// Frame Animation Manager End
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Particel Effect
static cocos2d::CCParticleSystemQuad *  NFC_getParticelEffect(int paticelEffectID,bool isLoop)
{
	if(paticelEffectID!=-1)
	{
		ParticleData * pParticelData=ParticleDataManager::get_instance2()->GetParticleDataByID(paticelEffectID);
		if(pParticelData!=NULL)
		{ 
			cocos2d::CCParticleSystemQuad * pParticleEffectNode=CCParticleSystemQuad::create(pParticelData->particleEffectFileName);
			if(pParticleEffectNode)
			{  
				if(isLoop)
				{
					pParticleEffectNode->setDuration(-1);
				}
				if(pParticelData->particleEffectIsBlendMode==1)
				{
					pParticleEffectNode->setBlendAdditive(true);
				} 
				pParticleEffectNode->setPositionType(kCCPositionTypeRelative);
				cocos2d::CCPoint particlePos=pParticleEffectNode->getPosVar();
				if(pParticelData->particleEffectVarianceX!=-1)
				{
					particlePos.x=pParticelData->particleEffectVarianceX;
				}
				if(pParticelData->particleEffectVarianceY!=-1)
				{ 
					particlePos.y=pParticelData->particleEffectVarianceY;
				}
				pParticleEffectNode->setPosVar(particlePos);

				return pParticleEffectNode;
			} 
		} 
	} 
	return NULL;
} 
//////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//������϶��� ����ս�����ٶ�����ʹ��

static VariableSpeedSequenceAction *   NFC_getVariableSpeedAction(cocos2d::CCFiniteTimeAction * pAction1,cocos2d::CCFiniteTimeAction * pAction2,float initSpeedScale)
{
	VariableSpeedSequenceAction * pVaribaleSpeedAction=VariableSpeedSequenceAction::createWithTwoActions(pAction1,pAction2);
	pVaribaleSpeedAction->setSpeedScale(initSpeedScale);
	return  pVaribaleSpeedAction;
}

//�����ӳٻص�����
static VariableSpeedSequenceAction *   NFC_getTransimissionDelayComAction(float delayTime,float initSpeedScale,CallFunctionProtocol * pDelegate,int eventType)
{ 
	cocos2d::CCDelayTime * pDelayTimeAction=cocos2d::CCDelayTime::create(delayTime);
    CallFuncAction  * pCallFunction=CallFuncAction::create(eventType,pDelegate);
	return NFC_getVariableSpeedAction(pDelayTimeAction,pCallFunction,initSpeedScale);
}

//�����ƶ��ص�����
static VariableSpeedSequenceAction *  NFC_getTransimissionMoveComAction(float delayTime,float initSpeedScale,cocos2d::CCPoint & endPoint,CallFunctionProtocol * pDelegate,int eventType)
{
	PreCCMoveTo  * pMoveToAction=PreCCMoveTo::create(delayTime,endPoint);
	CallFuncAction  * pCallFunction=CallFuncAction::create(eventType,pDelegate);
    return NFC_getVariableSpeedAction(pMoveToAction,pCallFunction,initSpeedScale);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static CSimpleActionSprite *  NFC_getSimpleActionSprite(int actionType,std::vector<float> attachParam)
{
	CSimpleActionSprite * pSimpleActionSprite=CSimpleActionSprite::create(actionType,attachParam);
	pSimpleActionSprite->setAnchorPoint(ccp(0,0));
	pSimpleActionSprite->setPosition(ccp(0,0));
	return pSimpleActionSprite;
}
 

static CSimpleActionSprite *  NFC_getSimpleActionSprite(const char * fileName,int actionType,std::vector<float> attachParam)
{
	CSimpleActionSprite * pSimpleActionSprite=CSimpleActionSprite::create(actionType,attachParam);
	if(pSimpleActionSprite)
	{
		pSimpleActionSprite->setProperty("File",fileName);
		return pSimpleActionSprite;
	}
	return NULL;
}



//--------------------------------Action Management--------------------------------------//
//�����ڼ䣬���ã�����
/****
	Scale In
**/
static void NFC_Action_scaleIn(cocos2d::CCNode* actionNode){
	int fps=DOTATribeApp::get_instance2()->GetFPS();
	//��һ֡
	int scale_1=ClientConstDataManager::get_instance2()->getValueByKey(CONST_KEY_MSGBOX_POP_SCALE_1);
	actionNode->setScale(scale_1*1.0f/100);
	//�ڶ�֡
	int during_2=ClientConstDataManager::get_instance2()->getValueByKey(CONST_KEY_MSGBOX_POP_DURING_2);
	float scale_2=(float)ClientConstDataManager::get_instance2()->getValueByKey(CONST_KEY_MSGBOX_POP_SCALE_2);
	cocos2d::CCScaleTo *scaleto=cocos2d::CCScaleTo::create(during_2*1.0f/fps,scale_2*1.0f/100);
	//����֡
	int during_3=ClientConstDataManager::get_instance2()->getValueByKey(CONST_KEY_MSGBOX_POP_DURING_3);
	float scale_3=(float)ClientConstDataManager::get_instance2()->getValueByKey(CONST_KEY_MSGBOX_POP_SCALE_3);
	cocos2d::CCScaleTo* scaleto2=cocos2d::CCScaleTo::create(during_3*1.0f/fps,scale_3*1.0f/100);
	//����֡
	int during_4=ClientConstDataManager::get_instance2()->getValueByKey(CONST_KEY_MSGBOX_POP_DURING_3);
	float scale_4=(float)ClientConstDataManager::get_instance2()->getValueByKey(CONST_KEY_MSGBOX_POP_SCALE_3);
	cocos2d::CCScaleTo* scaleto3=cocos2d::CCScaleTo::create(during_4*1.0f/fps,scale_4*1.0f/100);
	//
	cocos2d::CCSequence* seq=cocos2d::CCSequence::create(cocos2d::CCArray::create(scaleto,scaleto2,scaleto3,NULL));
	actionNode->runAction(seq);
}

static void NFC_Action_scaleIn(cocos2d::CCNode* actionNode,std::string param1,std::string param2,std::string param3){
	int fps=DOTATribeApp::get_instance2()->GetFPS();
	//��һ֡
	int scale_1=ClientConstDataManager::get_instance2()->getValueByKey(CONST_KEY_MSGBOX_POP_SCALE_1);
	actionNode->setScale(scale_1*1.0f/100);
	//�ڶ�֡
	int during_2=ClientConstDataManager::get_instance2()->getValueByKey(param1.c_str());
	float scale_2=(float)ClientConstDataManager::get_instance2()->getValueByKey(CONST_KEY_MSGBOX_POP_SCALE_2);
	cocos2d::CCScaleTo *scaleto=cocos2d::CCScaleTo::create(during_2*1.0f/fps,scale_2*1.0f/100);
	//����֡
	int during_3=ClientConstDataManager::get_instance2()->getValueByKey(param2.c_str());
	float scale_3=(float)ClientConstDataManager::get_instance2()->getValueByKey(CONST_KEY_MSGBOX_POP_SCALE_3);
	cocos2d::CCScaleTo* scaleto2=cocos2d::CCScaleTo::create(during_3*1.0f/fps,scale_3*1.0f/100);
	//����֡
	int during_4=ClientConstDataManager::get_instance2()->getValueByKey(param3.c_str());
	float scale_4=(float)ClientConstDataManager::get_instance2()->getValueByKey(CONST_KEY_MSGBOX_POP_SCALE_3);
	cocos2d::CCScaleTo* scaleto3=cocos2d::CCScaleTo::create(during_4*1.0f/fps,scale_4*1.0f/100);
	//
	cocos2d::CCSequence* seq=cocos2d::CCSequence::create(cocos2d::CCArray::create(scaleto,scaleto2,scaleto3,NULL));
	actionNode->runAction(seq);
}

/****
	Fall Down
**/
static void NFC_Action_fallDown(cocos2d::CCNode* actionNode){
	float screenHeight=(float)DOTATribeApp::get_instance2()->GetAppHeight();
	cocos2d::CCPoint endPoint=actionNode->getPosition();
	actionNode->setPositionY(screenHeight);
	int microsecond=ClientConstDataManager::get_instance2()->getValueByKey(CONST_KEY_FALLDOWN_TIME);
	cocos2d::CCMoveTo* moveto=cocos2d::CCMoveTo::create(microsecond*1.0f/1000,endPoint);
	cocos2d::CCEaseExponentialOut* action=cocos2d::CCEaseExponentialOut::create(moveto);
	actionNode->runAction(action);
}

/****
	Move and Reverse
**/
static void NFC_Action_MoveAndReverse(cocos2d::CCNode* actionNode,float during,const CCPoint& deltaPosition,bool forever){
	CCMoveBy* action_move=CCMoveBy::create(during,deltaPosition);
	if (forever){
		actionNode->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(action_move,action_move->reverse())));
	}else{
		actionNode->runAction(CCSequence::createWithTwoActions(action_move,action_move->reverse()));
	}
}

/*
	FadeIn and Reverse
*/
static void NFC_Action_FadeInAndReverse(cocos2d::CCNode * actionNode, float during, bool forever)
{
	assert(actionNode);

	cocos2d::CCActionInterval * fadein = cocos2d::CCFadeIn::create(during);
	CCSequence * se = CCSequence::createWithTwoActions(fadein, fadein->reverse());
	if(forever)
	{
		CCRepeatForever * repeat = CCRepeatForever::create(se);
		actionNode->runAction(repeat);
	}
	else
	{
		actionNode->runAction(se);
	}
}

/*
	
*/

#endif