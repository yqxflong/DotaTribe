////////////////////////////////////////////////////////////////
//Name:	 FrameAnimationEffect
//Auchor: 	xiaobo.wu
//Func:	 战斗时 帧动画特效
//Maintainer: 	xiaobo.wu
//date:   2013/09/23
////////////////////////////////////////////////////////////////
#include "../include/FrameAnimateEffect.h"
#include "../include/EngineSystem.h"
#include "../include/AthleticsSceneManager.h"
#include "../include/HeroicRole.h"
#include "../include/AnimationFileDataManager.h"
#include "../include/ProfSystem.h"
 

FrameAnimateEffect::FrameAnimateEffect()
{
	m_nEffectType=CommonEffect::_COMMONEFFECT_FRAME_ANIMATE_EFFECT_TYPE_;
	m_pEffectNode=NULL;
	m_pAnimationEffect=NULL;
	m_pFrameAnimateData=NULL;
	m_bEffectLoop=false;
}

FrameAnimateEffect::~FrameAnimateEffect()
{  

}



FrameAnimateEffect *  FrameAnimateEffect::CreateFrameAnimateEffect(int compositeEffectID,int effectID,bool isFlipX)
{
	FrameAnimateEffect * pFrameAnimateEffect=new FrameAnimateEffect();
	if(pFrameAnimateEffect&&pFrameAnimateEffect->InitFrameAnimateEffect(compositeEffectID,effectID,isFlipX))
	{ 
		return pFrameAnimateEffect;
	}
	if(pFrameAnimateEffect!=NULL)
	{
		delete pFrameAnimateEffect;
		pFrameAnimateEffect=NULL;
	}
	return NULL;

}
FrameAnimateEffect *  FrameAnimateEffect::CreateFrameAnimateEffectWithBone(int compositeEffectID,int effectID,bool isFlipX,cocos2d::extension::Bone * pBindBone)
{
	FrameAnimateEffect * pFrameAnimateEffect=new FrameAnimateEffect();
	if(pFrameAnimateEffect&&pFrameAnimateEffect->InitFrameAnimateEffectWithBone(compositeEffectID,effectID,isFlipX,pBindBone))
	{
		return pFrameAnimateEffect;
	}
	if(pFrameAnimateEffect!=NULL)
	{
		delete pFrameAnimateEffect;
		pFrameAnimateEffect=NULL;
	}
	return NULL;
}
 

bool  FrameAnimateEffect::InitFrameAnimateEffect(int compositeEffectID,int effectID,bool isFlipX/* =false */,cocos2d::extension::Bone * pBindBone/* =NULL */)
{  
	_BEGIN_PROF_CHUNK_("FrameAnimateEffect  compositeEffectID XXXXXXXXXXXXXXXXXXXXXXXXXXXXX")
	m_nCompositeEffectID=compositeEffectID;
	SetSubObjectID(effectID);
	m_bIsEffectFlipX=isFlipX;
    m_pFrameAnimateData=FrameAnimateDataManager::get_instance2()->GetFrameAnimateDataByID(effectID);
	if(m_pFrameAnimateData!=NULL)
	{
		m_bIsLoopEffect=m_pFrameAnimateData->frameAnimateEffectPlayType==_FRAMEEFFECT_LOOP_TYPE_ ? true:false;
		m_bIsLocationFollow=m_pFrameAnimateData->frameAnimateIsLocationFollow==1 ? true:false;
	 
		m_bIsAngleFollow=m_pFrameAnimateData->frameAnimateIsAngleFollow==1? true:false;
		m_sBoneName=m_pFrameAnimateData->frameAnimateEffectBoneName;
		m_bIsBoneEffect=m_pFrameAnimateData->frameAnimateIsBoneBindEffect;

		if(m_bIsLoopEffect)
		{
			if(IsOwnHadDead())
			return false;
		} 
		m_nCurEffectState=CommonEffect::_COMMONSKILLEFFECT_RUNNINGACTION_STATE_;
		std::string animationName=GetFrameAnimationName();
		if(animationName.empty())
		{
			m_nCurEffectState=CommonEffect::_COMMONSKILLEFFECT_ENDACTION_STATE_;
			return false;
		}
		cocos2d::CCAnimation * pAnimation=EngineSystem::get_instance2()->GetAnimationByID(m_pFrameAnimateData->frameAnimateEffectAnimationID);
		if(pAnimation!=NULL)
		{
			m_pEffectNode=cocos2d::CCSprite::create();

			if(m_pEffectNode!=NULL)
			{   
				m_pEffectNode->setScale(GetFrameAnimationScale());
				if(m_bIsBoneEffect)
				{ 
					if(m_pFrameAnimateData->frameAnimateEffectPlayType==_FRAMEEFFECT_UNLOOP_TYPE_)
					{
						m_bEffectLoop=true;
					}
					m_pEffectNode->setPosition(GetAnimationBoneInitPosition(pBindBone));
				}
				else
				{
					m_pEffectNode->setPosition(GetInitPosition());
					m_pEffectNode->setFlipX(isFlipX);
				}
			
				m_pAnimationEffect=CCAnimationEffect::create(m_pEffectNode,pAnimation,this);
				m_pAnimationEffect->setSpeedScale(AthleticsSceneManager::get_instance2()->AthleticsSpeed); 

				if(m_pAnimationEffect!=NULL&&m_pFrameAnimateData!=NULL)
				{ 
					if(IsEffectLoop()||m_bEffectLoop)
					{
						cocos2d::CCRepeatForever * pRepeatAction=cocos2d::CCRepeatForever::create(m_pAnimationEffect);
						cocos2d::CCNode * pRootLayer=AthleticsSceneManager::get_instance2()->GetAthleticsRootLayer();
						if(pRootLayer!=NULL)
						{
							pRootLayer->addChild(m_pEffectNode,m_pFrameAnimateData->frameAnimateEffectZOrder);
							m_pEffectNode->runAction(pRepeatAction);
						}
					}
					else
					{
						cocos2d::CCNode * pRootLayer=AthleticsSceneManager::get_instance2()->GetAthleticsRootLayer();
						if(pRootLayer!=NULL)
						{
							pRootLayer->addChild(m_pEffectNode,m_pFrameAnimateData->frameAnimateEffectZOrder);
							m_pEffectNode->runAction(m_pAnimationEffect);
						}
					}
				}	
				_END_PROF_CHUNK_()
				return true;
			} 
		} 
	}
	_END_PROF_CHUNK_()
	return false;
}


bool  FrameAnimateEffect::InitFrameAnimateEffectWithBone(int compositeEffectID,int effectID,bool isFlipX/* =false */,cocos2d::extension::Bone * pBindBone)
{ 
	return InitFrameAnimateEffect(compositeEffectID,effectID,isFlipX,pBindBone);
}
  
void   FrameAnimateEffect::Tick()
{
	CommonEffect::Tick();
}

void   FrameAnimateEffect::Destroy()
{
	SetIsValid(false);
	CCLOG("FrameAnimateEffect Destroy!");
	//销毁动画对象
	if(m_pAnimationEffect!=NULL)
	{
		m_pAnimationEffect->setForceDelete(true);
		m_pAnimationEffect=NULL;
	}
	if(m_pEffectNode!=NULL)
	{
		m_pEffectNode->stopAllActions();
		m_pEffectNode->removeFromParentAndCleanup(true);
		m_pEffectNode=NULL;
	}
	m_pFrameAnimateData=NULL;
}

void  FrameAnimateEffect::OnCommandHanlder(int EventTypeID)
{

}

void  FrameAnimateEffect::OnBeginEffect()
{
	//暂时没有使用
}

void   FrameAnimateEffect::OnEndEffect()
{
	m_nCurEffectState=_COMMONSKILLEFFECT_ENDACTION_STATE_;
	SetIsValid(false);
	Destroy();
	CCLOG("CommonEffect onEndEffect!");
}

void   FrameAnimateEffect::EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr)
{
	if(eventType==_Animation_Effect_Finish_Event_)
	{
		if(m_bIsLoopEffect)
		return ;
		CCLOG("EffectCallBackEventHandler  Finish CallBack");
		OnEndEffect();
		return ;
	}
	 
}

cocos2d::CCPoint  FrameAnimateEffect::GetInitPosition()
{

	if(m_pFrameAnimateData!=NULL)
	{
		if(!m_bIsEffectFlipX)
		{
			//攻击者在左边 
			cocos2d::CCPoint leftRolePosition=AthleticsSceneManager::get_instance2()->GetLeftFightRole()->getRolePosition();
			return ccp(leftRolePosition.x+m_pFrameAnimateData->frameAnimateEffectXOffSet,leftRolePosition.y+m_pFrameAnimateData->frameAnimateEffectYOffSet);

		}
		else
		{
			//攻击者在右边	 
			cocos2d::CCPoint rightRolePosition=AthleticsSceneManager::get_instance2()->GetRightFightRole()->getRolePosition();
			return ccp(rightRolePosition.x-m_pFrameAnimateData->frameAnimateEffectXOffSet,rightRolePosition.y+m_pFrameAnimateData->frameAnimateEffectYOffSet);
		}
	}
	return  CCPointZero;	 
}


void   FrameAnimateEffect::SetAnimationSpeedScale(float speedScale)
{
	if(m_pAnimationEffect!=NULL)
	{
		m_pAnimationEffect->setSpeedScale(speedScale);
	}
}



void   FrameAnimateEffect::UpdatePosition(cocos2d::CCPoint & position)
{
	if(!m_bIsLocationFollow)
		return ;
  
	if(m_sBoneName!="root"&&m_sBoneName!="screen") 
		return ;
	if(m_pEffectNode!=NULL&&m_pFrameAnimateData!=NULL&&m_bIsLocationFollow)
	{
		if(m_bIsEffectFlipX)
		{
			//右边
			m_pEffectNode->setPosition(ccp(position.x-m_pFrameAnimateData->frameAnimateEffectXOffSet,position.y+m_pFrameAnimateData->frameAnimateEffectYOffSet));
		}
		else
		{
			//左边
			m_pEffectNode->setPosition(ccp(position.x+m_pFrameAnimateData->frameAnimateEffectXOffSet,position.y+m_pFrameAnimateData->frameAnimateEffectYOffSet));
		}
	}
}
 
/*
更新骨骼绑定特效位置和角度
*/
void  FrameAnimateEffect::UpdateWithBone(cocos2d::extension::Bone * pBindBone)
{ 
   if(m_bIsLocationFollow)
   {
	   HeroicRole * pHeroicRole=NULL;
	   if(!m_bIsEffectFlipX)
	   {
		   //左边
		   pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
		   if(pHeroicRole!=NULL)
		   {
			   m_pEffectNode->setPosition(ccp(pHeroicRole->getPositionX()+pBindBone->worldX+m_pFrameAnimateData->frameAnimateEffectXOffSet,
				   pHeroicRole->getPositionY()+pBindBone->worldY+m_pFrameAnimateData->frameAnimateEffectYOffSet));
		   }
	   }
	   else
	   {
		   //右边
		   pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
		   if(pHeroicRole!=NULL)
		   {
			   m_pEffectNode->setPosition(ccp(pHeroicRole->getPositionX()-pBindBone->worldX+m_pFrameAnimateData->frameAnimateEffectXOffSet,
				   pHeroicRole->getPositionY()+pBindBone->worldY+m_pFrameAnimateData->frameAnimateEffectYOffSet));
		   } 
	   }
   }
    if(m_bIsAngleFollow)
	m_pEffectNode->setRotation(-pBindBone->worldRotation+m_pFrameAnimateData->frameAnimateEffectAngleOffSet);
} 


std::vector<PCallBack_Node>   FrameAnimateEffect::RegisterCallBackEventVec()
{
	  std::vector<PCallBack_Node>  callVect;
	  return callVect;
}


bool   FrameAnimateEffect::IsOwnHadDead()
{
	HeroicRole * pHeroicRole=NULL;
	if(!m_bIsEffectFlipX)  
	{
		pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
	}
	else
	{
		pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
	}

	if(pHeroicRole!=NULL)
	{
		 return pHeroicRole->hadPlayedDeadAnimation();
	}
	return false; 
}



std::string  FrameAnimateEffect::GetFrameAnimationName()
{
	if(m_pFrameAnimateData!=NULL)
	{
		AnimationFileData *  pAnimationFileData=AnimationFileDataManager::get_instance2()->GetAnimationByIdx(m_pFrameAnimateData->frameAnimateEffectAnimationID);
		if(pAnimationFileData!=NULL)
		{
			return pAnimationFileData->mAnimationName;
		}
	}
	return "";
}


float     FrameAnimateEffect::GetFrameAnimationScale()
{
	if(m_pFrameAnimateData!=NULL)
	{
		AnimationFileData *  pAnimationFileData=AnimationFileDataManager::get_instance2()->GetAnimationByIdx(m_pFrameAnimateData->frameAnimateEffectAnimationID);
		if(pAnimationFileData!=NULL)
		{
			return pAnimationFileData->mAnimationScale;
		}
	}
	return 1.0f;
}


cocos2d::CCPoint  FrameAnimateEffect::GetAnimationBoneInitPosition(cocos2d::extension::Bone * pBindBone)
{ 
	if(pBindBone!=NULL)
	{
		HeroicRole * pHeroicRole=NULL;
		if(!m_bIsEffectFlipX)
		{
			//左边
			pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
			if(pHeroicRole!=NULL)
			return ccp(pHeroicRole->getPositionX()+pBindBone->worldX+m_pFrameAnimateData->frameAnimateEffectXOffSet,
			pHeroicRole->getPositionY()+pBindBone->worldY+m_pFrameAnimateData->frameAnimateEffectYOffSet);
		}
		else
		{
			//右边
			pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
			if(pHeroicRole!=NULL)
			return ccp(pHeroicRole->getPositionX()-pBindBone->worldX+m_pFrameAnimateData->frameAnimateEffectXOffSet,
			pHeroicRole->getPositionY()+pBindBone->worldY+m_pFrameAnimateData->frameAnimateEffectYOffSet);
		}
	}
	return CCPointZero;
}











