//Name：CommonNumberEffect
//Function：战斗数值动画
//Author:	Johny

#include  "../include/CommonNumberEffect.h"
#include  "../include/AthleticProcedureDataType.h"
#include "../include/AthleticsSceneManager.h"
#include  "../include/SkillAttachLogicManager.h"
#include   "../include/SkillAttachLogicProcedure.h"
#include   "../include/CPublicVarReader.h"
#include   "../include/ArtFontDataManager.h"
 
 
CommonNumberEffect::CommonNumberEffect()
{   
	m_bRunning = true;
	Init();
}


CommonNumberEffect::~CommonNumberEffect()
{  
     Destroy();
}

void  CommonNumberEffect::Init()
{
	objectType_=COMMON_NUMBEREFFECT_OBJECT_TYPE;
	objectSubID_=0;
	m_parentNode=NULL;
	m_numberType=-1;
	m_numbericalValue=0;
	m_curEffectState=_NUMBEREFFECT_UNKONW_STATE_;
	 
	m_pArtFontLabel=NULL;
	m_pMoveAnimation=NULL;
	m_pNumberBufferEffect=NULL;
	m_speedScale=1.0f;
	m_bHadTriggeredNumberUpdate=false;
	m_bNeedUpdateNumber=false;
	m_fFadeOutDuration=0.0f;
	m_numberIndexVector.clear();
  
}

void CommonNumberEffect::Tick()
{
	if(!IsValid())
		return ;
	BaseObject::Tick();

   if(m_curEffectState==_NUMBEREFFECT_END_STATE_)
   {
	   OnEndNumberEffect();
	   return ;
   }
   else  if(m_curEffectState==_NUMBEREFFECT_BEIGIN_STATE_)
   {
	   OnBeginNumberEffect();
	   return ;
   }
}

void CommonNumberEffect::Destroy()
{   
    if(m_pMoveAnimation)
	{  
		m_pMoveAnimation->destroy();
		m_pMoveAnimation->setForceDelete(true);
		m_pMoveAnimation=NULL;
	}
	if(m_pNumberBufferEffect)
	{
		m_pNumberBufferEffect->setForceDelete(true);
		m_pNumberBufferEffect=NULL;
	}
	if(m_pArtFontLabel!=NULL)
	{  
		m_pArtFontLabel->GetBatchNodeLabel()->stopAllActions();
		m_pArtFontLabel->Destroy();
		delete  m_pArtFontLabel;
		m_pArtFontLabel=NULL;
	}
	CCLog("CommonNumberEffect Destroy!");
}

void CommonNumberEffect::OnCommandHanlder(int EventTypeID)
{
} 

void  CommonNumberEffect::OnBeginNumberEffect()
{
     m_curEffectState=_NUMBEREFFECT_RUNNING_STATE_;
	 
	 if(m_numberType!=_ATHLETICS_SKILL_HIT_NOTE_TYPE_)
	 m_bNeedUpdateNumber=true;
	  
     NumberBufferData *  pNumberBufferData=GetNumberBufferData();

	 if(!pNumberBufferData)
	 { 
         m_curEffectState=_NUMBEREFFECT_END_STATE_;
	     return ;
	 } 
	 InitArtFontIndexVector(m_bNeedUpdateNumber,pNumberBufferData);  
	 if(m_parentNode)
	 {
		 m_pArtFontLabel=ArtFontLabelBatchNode::CreateArtFontWithArray(m_numberIndexVector); 
		 m_pArtFontLabel->SetAnchorPoint(ccp(0.5f,0.0f));
		 m_pArtFontLabel->SetPosition(ccp(0,pNumberBufferData->numberBufferInitHeigh));
		 m_pArtFontLabel->SetScale(pNumberBufferData->numberBufferScale);
		 m_parentNode->addChild(m_pArtFontLabel->GetBatchNodeLabel(),10);  
		 DoNumberEffectAction(pNumberBufferData); 
	 	 //Update Number 
		 if(m_bNeedUpdateNumber)
		 UpdateNumbericalValue();
		 m_bHadTriggeredNumberUpdate=true;
	 }
	 else
	 {
		 m_curEffectState=_NUMBEREFFECT_END_STATE_;
		 return ;
	 }
} 

void   CommonNumberEffect::InitArtFontIndexVector(bool bNeedUpdateNumber,NumberBufferData * pNumberBufferData)
{
	if(!bNeedUpdateNumber)
	{ 
		switch(m_numbericalValue)
		{
	   	   case _ATHLETICS_SKILL_DODGE_ACTION_TYPE_:
		   {
			 m_numberIndexVector.push_back(ArtFontDataManager::get_instance2()->GetArtFontValueFromID(pNumberBufferData->numberBufferFontType,_NUMBERTYPE_MISS_INDEX_VALUE_));
			 break;
		   }
		   case _ATHLETICS_SKILL_BLOCK_ACTION_TYPE_:
		   {
			  m_numberIndexVector.push_back(ArtFontDataManager::get_instance2()->GetArtFontValueFromID(pNumberBufferData->numberBufferFontType,_NUMBERTYPE_BLOCK_INDEX_VALUE_));
			  break; 
		   } 
		default:
			return ;
		} 
	}
	else
	{
		std::vector<int> numberVector;
		int tempNumbericalValue=m_numbericalValue;
		if(tempNumbericalValue==0)
		{
			numberVector.push_back(0);
		}
		else
		{
			while(tempNumbericalValue!=0)
			{
				numberVector.push_back(tempNumbericalValue%10);
				tempNumbericalValue/=10;
			}
		}

		size_t  numberCharSize=numberVector.size();
		std::vector<int> numberVecor2;
		for(int numberIndex=numberCharSize-1;numberIndex>=0;numberIndex--)
		{ 
			numberVecor2.push_back(numberVector.at(numberIndex));
		}
		m_numberIndexVector.clear();
		switch(pNumberBufferData->numberBufferFormatID)
		{
		case _HPDAMAGE_NUMBERICALFONT_FORMATID_:
			{
				m_numberIndexVector.push_back(ArtFontDataManager::get_instance2()->GetArtFontValueFromID(pNumberBufferData->numberBufferFontType,_NUMBERTYPE_SUB_INDEX_VALUE_));
			}
			break;
		case _HPHEAL_NUMBERICALFONT_FORMATID_:
			{
				m_numberIndexVector.push_back(ArtFontDataManager::get_instance2()->GetArtFontValueFromID(pNumberBufferData->numberBufferFontType,_NUMBERTYPE_ADD_INDEX_VALUE_));
			}
			break;
		case _BAOJI_NUMBERICALFONT_FOAMATID_:
			{  
				m_numberIndexVector.push_back(ArtFontDataManager::get_instance2()->GetArtFontValueFromID(pNumberBufferData->numberBufferFontType,_NUMBERTYPE_SUB_INDEX_VALUE_));
			}
			break;
		case _MPHEAL_NUMBERICALFONT_FORMATID_:
			{  
				m_numberIndexVector.push_back(ArtFontDataManager::get_instance2()->GetArtFontValueFromID(pNumberBufferData->numberBufferFontType,_NUMBERTYPE_ADD_INDEX_VALUE_));
			}
			break;
		case _MPDAMAGE_NUMBERICALFONT_FORMATID_:
			{  
				m_numberIndexVector.push_back(ArtFontDataManager::get_instance2()->GetArtFontValueFromID(pNumberBufferData->numberBufferFontType,_NUMBERTYPE_SUB_INDEX_VALUE_));
			}
			break;
		default:
			break;
		} 
		for(size_t numberIndex=0;numberIndex<numberCharSize;numberIndex++)
		{
			m_numberIndexVector.push_back(ArtFontDataManager::get_instance2()->GetArtFontValueFromID(pNumberBufferData->numberBufferFontType,numberVecor2.at(numberIndex)));
		} 
	}
}


void   CommonNumberEffect::DoNumberEffectAction(NumberBufferData * pNumberBufferData)
{ 
	m_fFadeOutDuration=(pNumberBufferData->numberBufferDurationTime-pNumberBufferData->numberBufferTriggerFadeOutTime)/1000.0f;
	if(pNumberBufferData->numberBufferIsNeedScale)
	{
		cocos2d::CCScaleTo * scaleToAction=cocos2d::CCScaleTo::create(pNumberBufferData->numberBufferScaleDurationTime/2000,pNumberBufferData->numberBufferMaxScale);
		cocos2d::CCScaleTo * scaleBackAction=cocos2d::CCScaleTo::create(pNumberBufferData->numberBufferScaleDurationTime/2000,pNumberBufferData->numberBufferScale);
		float bufferMoveDuration=(pNumberBufferData->numberBufferDurationTime-pNumberBufferData->numberBufferScaleDurationTime)/1000;
		float bufferFadeOutDuration=(pNumberBufferData->numberBufferTriggerFadeOutTime-pNumberBufferData->numberBufferScaleDurationTime)/1000;
		PCallBackVec pCallBackVec=new CallBackVec();
		if(pCallBackVec!=NULL)
		{	
			pCallBackVec->pDelegate=this;
			PCallBackNode  pFadeOutNode=new CallBackNode();
			if(pFadeOutNode)
			{
				pFadeOutNode->eventType=_NUMBEREFFECT_FADEOUT_EVENT_TYPE_;
				pFadeOutNode->triggerTime=bufferFadeOutDuration;
				pCallBackVec->callBackEventVec.push_back(pFadeOutNode);
			} 
		} 
		MoveAnimation * pMoveAnimation=MoveAnimation::create(bufferMoveDuration,ccp(0,pNumberBufferData->numberBufferEndHeigh),pCallBackVec);
		cocos2d::CCEaseSineIn* action=cocos2d::CCEaseSineIn::create(pMoveAnimation);
		m_pNumberBufferEffect=VariableSpeedSequenceAction::create(scaleToAction,scaleBackAction,action,NULL);
		m_pNumberBufferEffect->setSpeedScale(AthleticsSceneManager::get_instance2()->AthleticsSpeed);
		m_pArtFontLabel->GetBatchNodeLabel()->runAction(m_pNumberBufferEffect);
	} 
	else
	{
		PCallBackVec pCallBackVec=new CallBackVec();
		if(pCallBackVec!=NULL)
		{	
			pCallBackVec->pDelegate=this;
			PCallBackNode  pFadeOutNode=new CallBackNode();
			if(pFadeOutNode)
			{
				pFadeOutNode->eventType=_NUMBEREFFECT_FADEOUT_EVENT_TYPE_;
				pFadeOutNode->triggerTime=pNumberBufferData->numberBufferTriggerFadeOutTime/1000;
				pCallBackVec->callBackEventVec.push_back(pFadeOutNode);
			} 
		}  
		m_pMoveAnimation=MoveAnimation::create(pNumberBufferData->numberBufferDurationTime/1000,ccp(0,pNumberBufferData->numberBufferEndHeigh),pCallBackVec);
		//cocos2d::CCEaseSineIn* action=cocos2d::CCEaseSineIn::create(m_pMoveAnimation);
		m_pMoveAnimation->setSpeedScale(AthleticsSceneManager::get_instance2()->AthleticsSpeed);
		m_pArtFontLabel->GetBatchNodeLabel()->runAction(m_pMoveAnimation);
	} 
}




void  CommonNumberEffect::OnEndNumberEffect()
{  
	m_curEffectState=_NUMBEREFFECT_END_STATE_;
	SetIsValid(false);
	Destroy();
}


void   CommonNumberEffect::CallBackEventProtocol(int eventType,void * ptrParam)
{
    if(eventType==_NUMBEREFFECT_FADEOUT_EVENT_TYPE_)
	{
		//开始逐隐效果
        StartFadeOutAnimation();
		return ;
	}
	else if(eventType==_Move_Animation_Finish_Event_)
	{
		//动画完成清理
		OnEndNumberEffect();
		return ;
	}
} 


void   CommonNumberEffect::SetNumberEffectSpeedScale(float speedScale)
{ 
	m_speedScale=speedScale;
	if(m_pMoveAnimation)
	{
		m_pMoveAnimation->setSpeedScale(m_speedScale);
	}
	if(m_pNumberBufferEffect)
	{
		m_pNumberBufferEffect->setSpeedScale(m_speedScale);
	}
	 
}

float  CommonNumberEffect::GetNumberEffectSpeedScale()
{
	return  m_speedScale;
}
 
bool   CommonNumberEffect::GetHadTriggeredNumberUpdate()
{
	return  m_bHadTriggeredNumberUpdate;
}




void   CommonNumberEffect::StartFadeOutAnimation()
{  
	cocos2d::CCFadeOut * pFadeOutAction=cocos2d::CCFadeOut::create(m_fFadeOutDuration);
	if(pFadeOutAction!=NULL&&m_pArtFontLabel->GetBatchNodeLabel()!=NULL)
		m_pArtFontLabel->GetBatchNodeLabel()->runAction(pFadeOutAction);
}
 

/*
更新数值
*/ 
void   CommonNumberEffect::UpdateNumbericalValue()
{
	switch(m_numberType)
	{
	   case  _HPDAMAGE_NUMBERICALFONT_FORMATID_:			
		{
			m_parentNode->reduceRoleHPValue(m_numbericalValue);
			break;
		}
	   case  _HPHEAL_NUMBERICALFONT_FORMATID_:
		{
			m_parentNode->increaseRoleHPValue(m_numbericalValue);
			break;
		}
	   case  _BAOJI_NUMBERICALFONT_FOAMATID_:
		{
			m_parentNode->reduceRoleHPValue(m_numbericalValue);
			break;
		}

	   case  _MPHEAL_NUMBERICALFONT_FORMATID_:
		{
			m_parentNode->increaseRoleMPValue(m_numbericalValue);
			break;
		}
	   case  _MPDAMAGE_NUMBERICALFONT_FORMATID_:
		{
			m_parentNode->reduceRoleMPValue(m_numbericalValue);
			break;
		}
	   default:
		{
			break;
		}
	}
}
 

CommonNumberEffect *  CommonNumberEffect::CreateCommonNumberEffect(HeroicRole * parentNode,char numberType,int numberEffectID,int numbericalValue)
{  
    CommonNumberEffect * pCommonNumberEffect=new CommonNumberEffect();
	//CCLOG("CommonNumberEffect ***************************************************************  new !");
	if(pCommonNumberEffect&&pCommonNumberEffect->InitCommonNumberEffect(parentNode,numberType,numberEffectID,numbericalValue))
	{
		 return pCommonNumberEffect;
	}
	if(pCommonNumberEffect!=NULL)
	{
		delete pCommonNumberEffect;
		pCommonNumberEffect=NULL;
	}
	return NULL;

} 
bool  CommonNumberEffect::InitCommonNumberEffect(HeroicRole * parentNode,char numberType,int numberEffectID,int numbericalValue)
{ 
	 if(parentNode!=NULL)
	 {
		 m_parentNode=parentNode;
		 m_numberType=numberType;
		 SetSubObjectID(numberEffectID);
		 m_numbericalValue=numbericalValue;
		 m_curEffectState=_NUMBEREFFECT_BEIGIN_STATE_;
		 return true;
	 }	 
	 return false;
}

  

NumberBufferData *   CommonNumberEffect::GetNumberBufferData()
{
	return   NumberBufferDataManager::get_instance2()->GetNumberBufferDataByID(GetSubObjectID());
} 

 



























