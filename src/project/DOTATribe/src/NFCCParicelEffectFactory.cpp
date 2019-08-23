#include "../include/NFCCParicelEffectFactory.h"
#include "../include/ParticleDataManager.h"
#include "../include/AthleticsSceneManager.h"
 
 
cocos2d::CCParticleSystemQuad *  NFCParticelEffectCreate(cocos2d::CCNode * pParentNode,int paticelEffectID,int tag)
{
	if(pParentNode!=NULL&&paticelEffectID!=-1)
	{
		ParticleData * pParticelData=ParticleDataManager::get_instance2()->GetParticleDataByID(paticelEffectID);
		if(pParticelData!=NULL)
		{ 
			cocos2d::CCParticleSystemQuad * pParticleEffectNode=CCParticleSystemQuad::create(pParticelData->particleEffectFileName);
			if(pParticleEffectNode!=NULL)
			{ 
				if(ATHLETICSSCENEMANAGER!=NULL)
				pParticleEffectNode->setParticleSpeed(ATHLETICSSCENEMANAGER->AthleticsSpeed);
				if(pParticelData->particleEffectIsBlendMode==1)
				{
					pParticleEffectNode->setBlendAdditive(true);
				}
			    pParticleEffectNode->setDuration(-1);  //设置粒子特效为无限时间
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
				
				//获得屏幕中心位置
				cocos2d::CCSize  winSize=cocos2d::CCDirector::sharedDirector()->getWinSize();
				cocos2d::CCPoint offSetPoint=ccp(winSize.width/2+pParticelData->particleEffectXOffSet,winSize.height/2+pParticelData->particleEffectYOffSet);
			    pParticleEffectNode->setPosition(offSetPoint);
			    pParentNode->addChild(pParticleEffectNode,pParticelData->particleEffectZOrder,tag);
				return pParticleEffectNode;
			} 
		} 
	} 
	return NULL;
}
 

