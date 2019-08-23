////////////////////////////////////////////////////////////////
//Name:	 ParicelEffect
//Auchor: 	xiaobo.wu
//Func:	 粒子特效
//Maintainer: 	xiaobo.wu
//date:   2013/09/22
////////////////////////////////////////////////////////////////
#include "../include/ParticleEffect.h"
#include "../include/AthleticsSceneManager.h"
#include "../include/HeroicRole.h"
#include "../include/ParticleDataManager.h"

ParticleEffect::ParticleEffect()
{
	m_nEffectType=CommonEffect::_COMMONEFFECT_PARTICLE_EFFECT_TYPE_;
	m_pParticleEffectNode=NULL;
	m_bIsHandover=false;
	m_nEffectPlayType=0;
}

ParticleEffect::~ParticleEffect()
{
	OnEndEffect();
}
 
void   ParticleEffect::Tick()
{
	if(!IsValid())
		return ;
	BaseObject::Tick();

	if(m_nCurEffectState==_COMMONSKILLEFFECT_ENDACTION_STATE_)
	{
		OnEndEffect();
		return ;
	}
	else if(m_nCurEffectState==_COMMONSKILLEFFECT_PAUSEAACTION_STATE_)
	{  
		/*
		 等待粒子数减为0 再进行
		*/
		if(m_pParticleEffectNode&&m_pParticleEffectNode->getParticleCount()==0)
		{
			OnEndEffect();
		}
		return ;
	}
}
void   ParticleEffect::Destroy()
{ 
	if(m_pParticleEffectNode!=NULL)
	{
		m_pParticleEffectNode->stopSystem();
	}
}

void   ParticleEffect::Stop()
{
   
}
void   ParticleEffect::OnCommandHanlder(int EventTypeID)
{

}

void   ParticleEffect::OnBeginEffect()
{

}

void   ParticleEffect::OnEndEffect()
{
	SetIsValid(false);
	CCLOG("ParticleEffect  End  Effect Here!");
	m_nCurEffectState=CommonEffect::_COMMONSKILLEFFECT_ENDACTION_STATE_;
	if(m_pParticleEffectNode!=NULL)
	{
		m_pParticleEffectNode->removeFromParentAndCleanup(true);
		m_pParticleEffectNode=NULL;
	}
}
void   ParticleEffect::SetAnimationSpeedScale(float speedScale)
{
	// to do
	// 设置粒子播放速度
	if(m_pParticleEffectNode!=NULL)
	{
		m_pParticleEffectNode->setParticleSpeed(speedScale);
	} 
}

void  ParticleEffect::SetVisible(bool isVisible/* =false */)
{
	if(m_pParticleEffectNode!=NULL)
	{ 
		m_pParticleEffectNode->setVisible(isVisible);
	    m_pParticleEffectNode->update(0.1f);
	} 
}
 

ParticleEffect *  ParticleEffect::CreateParticleEffect(int compositeEffectID,int effectID,bool isFlipX,cocos2d::extension::Bone * pBindBone/* =NULL */)
{
	ParticleEffect * pParticleEffect=new ParticleEffect();
	if(pParticleEffect&&pParticleEffect->InitParticleEffect(compositeEffectID,effectID,isFlipX,pBindBone))
	{
		return pParticleEffect;
	}
	if(pParticleEffect!=NULL)
	{
		delete pParticleEffect;
		pParticleEffect=NULL;
	}
	return NULL;
}

ParticleEffect *  ParticleEffect::CreateParticleEffectWithBone(int compositeEffectID,int effectID,bool isFlipX,cocos2d::extension::Bone * pBindBone)
{
	ParticleEffect * pParticleEffect=new ParticleEffect();
	if(pParticleEffect&&pParticleEffect->InitParticleEffectWithBone(compositeEffectID,effectID,isFlipX,pBindBone))
	{
		return pParticleEffect;
	}
	if(pParticleEffect!=NULL)
	{
		delete pParticleEffect;
		pParticleEffect=NULL;
	}
	return NULL;
}
 
cocos2d::CCPoint  ParticleEffect::GetInitPosition()
{
	if(m_pParticleEffectData!=NULL)
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
			cocos2d::CCPoint rolePosition=pHeroicRole->getRolePosition();
			return ccp(rolePosition.x+m_pParticleEffectData->particleEffectXOffSet,rolePosition.y+m_pParticleEffectData->particleEffectYOffSet);
		}
	}
	return  CCPointZero;	 
}

void   ParticleEffect::UpdatePosition(cocos2d::CCPoint & position)
{
	if(!m_bIsLocationFollow)
		return ;
	if(m_sBoneName!="root"&&m_sBoneName!="screen") 
		return ;

	if(m_pParticleEffectNode!=NULL&&m_bIsLocationFollow)
	{
		m_pParticleEffectNode->setPosition(ccp(position.x+m_pParticleEffectData->particleEffectXOffSet,
			position.y+m_pParticleEffectData->particleEffectYOffSet));
	}
}
void   ParticleEffect::UpdateWithBone(cocos2d::extension::Bone * pBindBone)
{
   if(m_bIsLocationFollow)
   {
	   HeroicRole * pHeroicRole=NULL;
	   if(!m_bIsEffectFlipX)
	   {
		   //左边
		   pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
	   }
	   else
	   {
		   //右边
		   pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
	   }
	   if(pHeroicRole!=NULL)
	   { 
		   if(!m_bIsEffectFlipX)
			   m_pParticleEffectNode->setPosition(ccp(pHeroicRole->getPositionX()+pBindBone->worldX+m_pParticleEffectData->particleEffectXOffSet,
			   pHeroicRole->getPositionY()+pBindBone->worldY+m_pParticleEffectData->particleEffectYOffSet));	
		   else
			   m_pParticleEffectNode->setPosition(ccp(pHeroicRole->getPositionX()-pBindBone->worldX+m_pParticleEffectData->particleEffectXOffSet,
			   pHeroicRole->getPositionY()+pBindBone->worldY+m_pParticleEffectData->particleEffectYOffSet));	 
	   }
   }
   if(m_bIsAngleFollow)
    m_pParticleEffectNode->setRotation(-pBindBone->worldRotation+m_pParticleEffectData->particleEffectAngleOffSet);
} 
bool  ParticleEffect::InitParticleEffect(int compositeEffectID,int effectID,bool isFlipX,cocos2d::extension::Bone * pBindBone/* =NULL */)
{
	m_nCompositeEffectID=compositeEffectID;
	SetSubObjectID(effectID);
	m_bIsEffectFlipX=isFlipX;
	m_pParticleEffectData=ParticleDataManager::get_instance2()->GetParticleDataByID(effectID);
	cocos2d::CCNode * pRootLayer=AthleticsSceneManager::get_instance2()->GetAthleticsRootLayer();
	if(m_pParticleEffectData!=NULL&&pRootLayer!=NULL)
	{
		m_bIsLoopEffect=m_pParticleEffectData->particleEffectPlayType==_PARTICLEEFFECT_LOOP_TYPE_ ? true:false;
		m_nEffectPlayType=m_pParticleEffectData->particleEffectPlayType;
		m_bIsLocationFollow=m_pParticleEffectData->particleEffectIsLocationFollow==1 ? true:false;
		m_bIsAngleFollow=m_pParticleEffectData->particleEffectIsAngleFollow==1? true:false;
		m_bIsHandover=m_pParticleEffectData->particleEffectIsHangover==1? true:false;
		m_sBoneName=m_pParticleEffectData->particleEffectBoneName;

		if(m_sBoneName!="root"&&m_sBoneName!="screen")
		{
			m_bIsBoneEffect=true;
		}
		m_pParticleEffectNode=CCParticleSystemQuad::create(m_pParticleEffectData->particleEffectFileName);
		if(m_pParticleEffectNode!=NULL)
		{ 
			m_pParticleEffectNode->setParticleSpeed(AthleticsSceneManager::get_instance2()->AthleticsSpeed);
			if(m_pParticleEffectData->particleEffectIsBlendMode==_PATICLEEFFECT_BLEND_MODE_)
			{
				m_pParticleEffectNode->setBlendAdditive(true);
			}
			if(m_nEffectPlayType!=_PARTICLEEFFECT_SELFTIME_TYPE_)
			{ 
				m_pParticleEffectNode->setDuration(-1);  //暂时设置粒子特效为无限时间
			}
			if(m_bIsHandover)
			{
				m_pParticleEffectNode->setPositionType(kCCPositionTypeRelative);
			}
			else
			{
				m_pParticleEffectNode->setPositionType(kCCPositionTypeGrouped);
			}
			if(m_bIsBoneEffect)
				m_pParticleEffectNode->setPosition(GetAnimationBoneInitPosition(pBindBone));
			else
				m_pParticleEffectNode->setPosition(GetInitPosition());

			if(m_bIsAngleFollow&&pBindBone)
			{
				m_pParticleEffectNode->setRotation(-pBindBone->worldRotation+m_pParticleEffectData->particleEffectAngleOffSet);
			 
			}	 
			m_nCurEffectState=CommonEffect::_COMMONSKILLEFFECT_PAUSEAACTION_STATE_;
		    pRootLayer->addChild(m_pParticleEffectNode,m_pParticleEffectData->particleEffectZOrder);

			return true;
		}  
	}
	return  false;
}
bool  ParticleEffect::InitParticleEffectWithBone(int compositeEffectID,int effectID,bool isFlipX,cocos2d::extension::Bone * pBindBone)
{
	 return InitParticleEffect(compositeEffectID,effectID,isFlipX,pBindBone);
}

cocos2d::CCPoint ParticleEffect::GetAnimationBoneInitPosition(cocos2d::extension::Bone * pBindBone)
{
	HeroicRole * pHeroicRole=NULL;
	if(!m_bIsEffectFlipX)
	{
		//左边
		pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
	}
	else
	{
		//右边
		pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
	}
	if(pHeroicRole!=NULL&&pBindBone!=NULL)
	{
		if(!m_bIsEffectFlipX)
		return ccp(pHeroicRole->getPositionX()+pBindBone->worldX+m_pParticleEffectData->particleEffectXOffSet,
		pHeroicRole->getPositionY()+pBindBone->worldY+m_pParticleEffectData->particleEffectYOffSet);
		else
		return ccp(pHeroicRole->getPositionX()-pBindBone->worldX+m_pParticleEffectData->particleEffectXOffSet,
		pHeroicRole->getPositionY()+pBindBone->worldY+m_pParticleEffectData->particleEffectYOffSet);
	}
	return CCPointZero;
}


 

