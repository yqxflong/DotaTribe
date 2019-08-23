/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  自动渐隐Label管理器
//date:   2013/10/23
///////////////////////////////////////////////// 
#include "../include/AutoFadeOutLable.h"
#include "../include/NFControlsManager.h"
#include "../include/ErrorTipsDataManager.h"

  
#define   ENDSINGLETIME   1.0f

void  AutoDelayAnimation::update(float time)
{  
	checkTimerEvent(m_fDuration*time);

	if(time>=(ENDSINGLETIME-FLT_EPSILON))
	{  
		if(m_pAutoDelayDelage!=NULL)
		{
			m_pAutoDelayDelage->autoDelayEventHandler(_Move_Animation_Finish_Event_,NULL);
			return ;
		}
	}  
}
void  AutoDelayAnimation::step(float dt)
{
	if (m_bFirstTick)
	{
		m_bFirstTick = false;
		m_elapsed = 0;
	}
	else
	{
		m_elapsed += dt*m_fSpeedScale;
	}

	this->update(MAX (0,                                 
		MIN(1, m_elapsed /
		MAX(m_fDuration, FLT_EPSILON)    
		)
		)
		);
}


AutoDelayAnimation* AutoDelayAnimation::create(float d,AutoDelayProtocol * pDelegate/* =NULL */,PCallBackVec pCallBackVec/* =NULL */)
{ 
	AutoDelayAnimation * pAction=new AutoDelayAnimation();
	if(pAction&&pAction->initDuration(d,pDelegate,pCallBackVec))
	{ 
		pAction->autorelease();
		return pAction;
	} 
	CC_SAFE_DELETE(pAction);
	return NULL;
}
 
bool  AutoDelayAnimation::initDuration(float d,AutoDelayProtocol * pDelegate/* =NULL */,PCallBackVec pCallBackVec/* =NULL */)
{
	if(CCActionInterval::initWithDuration(d))
	{
	  	 m_fSpeedScale=1.0f;
	     m_pAutoDelayDelage=pDelegate;
		 m_pCallEventList=pCallBackVec;
		 return true;
	}
	return false;
}

void  AutoDelayAnimation::setSpeedScale(float speedScale)
{
	 m_fSpeedScale=speedScale;
}

AutoDelayAnimation::~AutoDelayAnimation()
{
	 m_pAutoDelayDelage=NULL;
	 if(m_pCallEventList!=NULL)
	 {
		 delete m_pCallEventList;
		 m_pCallEventList=NULL;
	 }
}

void   AutoDelayAnimation::checkTimerEvent(float time)
{
	//检测定时任务
	if(m_pCallEventList!=NULL)
	{
		size_t  sizeCount=m_pCallEventList->callBackEventVec.size();
		for(size_t eventIndex=0;eventIndex<sizeCount;eventIndex++)
		{
			PCallBackNode pCallBackNode=m_pCallEventList->callBackEventVec.at(eventIndex);
			if(pCallBackNode!=NULL&&!pCallBackNode->isTrigger)
			{
				if((pCallBackNode->triggerTime)<=time)
				{
					m_pAutoDelayDelage->autoDelayEventHandler(pCallBackNode->eventType,pCallBackNode);
					pCallBackNode->isTrigger=true;
					continue; 
				}
			}
		}
	}  
}



//////////////////////////////////////////////////////////////////////////

AutoFadeOutLabelManager::AutoFadeOutLabelManager()
{
	m_pShowLabel=NULL;
	m_bIsValid=true;
	m_pErrorTipsData=NULL;
}

AutoFadeOutLabelManager::~AutoFadeOutLabelManager()
{ 
    Destroy();
}

AutoFadeOutLabelManager * AutoFadeOutLabelManager::CreateAutoFadeOutLabelManager(cocos2d::CCNode * pParent,int lableIndex,std::string message)
{
	 AutoFadeOutLabelManager * pAutoFadeOutLabelManage=new AutoFadeOutLabelManager();
	 if(pAutoFadeOutLabelManage&&pAutoFadeOutLabelManage->InitAutoFadeOutLabelManager(pParent,lableIndex,message))
	 {
		 return pAutoFadeOutLabelManage;
	 }
	 if(pAutoFadeOutLabelManage!=NULL)
	 {
		 delete pAutoFadeOutLabelManage;
		 pAutoFadeOutLabelManage=NULL;
	 }
	 return  NULL;
}

bool   AutoFadeOutLabelManager::InitAutoFadeOutLabelManager(cocos2d::CCNode * pParent,int lableIndex,std::string message)
{
	 m_pErrorTipsData=ErrorTipsDataManager::get_instance2()->GetErrorTipsData();
	if(m_pErrorTipsData!=NULL)
	{ 
		m_nIndex=lableIndex;
		m_pShowLabel=cocos2d::CCLabelTTF::create();
		m_pBackSprite=cocos2d::CCSprite::create();
		m_pBackSprite->setProperty("File",m_pErrorTipsData->errorBackImageFilePath);
		NFC_setLabelByFontStyleID(m_pShowLabel,m_pErrorTipsData->errorFontStyleID);
		m_pShowLabel->setString(message.c_str());
		m_pShowLabel->setAnchorPoint(ccp(m_pErrorTipsData->errorAnchorX,m_pErrorTipsData->errorAnchorY));
		m_pBackSprite->setAnchorPoint(ccp(m_pErrorTipsData->errorAnchorX,m_pErrorTipsData->errorAnchorY));
		cocos2d::CCSize winSize=cocos2d::CCDirector::sharedDirector()->getWinSize();
		float  relateXPosition=winSize.height/2+m_pErrorTipsData->errorRelateY+(lableIndex-1)*m_pErrorTipsData->errorAddHeight;
		SetPosition(ccp(winSize.width/2,relateXPosition));
		AddParent(pParent);

		PCallBackVec pCallBackVec=new CallBackVec();
		if(pCallBackVec!=NULL)
		{	
			PCallBackNode  pFadeOutNode=new CallBackNode();
			if(pFadeOutNode!=NULL)
			{
				pFadeOutNode->eventType=_AUTOLABEL_FADEOUT_TYPE_;
				pFadeOutNode->triggerTime=m_pErrorTipsData->errorFadeOutTime/1000;
				pCallBackVec->callBackEventVec.push_back(pFadeOutNode);
			}
		}
		AutoDelayAnimation  * pAutoDelayAnimation=AutoDelayAnimation::create(m_pErrorTipsData->errorDurationTime/1000,this,pCallBackVec);
		m_pShowLabel->runAction(pAutoDelayAnimation);

		return true;
	}
	return  false;
}

void  AutoFadeOutLabelManager::SetPosition(cocos2d::CCPoint position)
{
	if(m_pShowLabel!=NULL)
	m_pShowLabel->setPosition(position);
	if(m_pBackSprite!=NULL)
    m_pBackSprite->setPosition(position);
}
void  AutoFadeOutLabelManager::AddParent(cocos2d::CCNode * pParent)
{
	if(m_pShowLabel!=NULL&&m_pBackSprite!=NULL)
	{
		pParent->addChild(m_pBackSprite,0);
		pParent->addChild(m_pShowLabel,1);
	}
}
void AutoFadeOutLabelManager::Destroy()
{
	m_bIsValid=false;
	if(m_pShowLabel!=NULL)
	{
		m_pShowLabel->stopAllActions();
		m_pShowLabel->removeFromParentAndCleanup(true);
		m_pShowLabel=NULL;
	}
	if(m_pBackSprite!=NULL)
	{
		m_pBackSprite->stopAllActions();
		m_pBackSprite->removeFromParentAndCleanup(true);
		m_pBackSprite=NULL;
	}
	 
}
bool  AutoFadeOutLabelManager::GetIsValid()
{
	return m_bIsValid;
} 

void  AutoFadeOutLabelManager::SetIndex(int layoutIndex)
{
	m_nIndex=layoutIndex;
	cocos2d::CCSize winSize=cocos2d::CCDirector::sharedDirector()->getWinSize();
	float  relateXPosition=winSize.height/2+m_pErrorTipsData->errorRelateY+(layoutIndex-1)*m_pErrorTipsData->errorAddHeight;
	SetPosition(ccp(winSize.width/2,relateXPosition));
}

int   AutoFadeOutLabelManager::GetIndex()
{  
	return  m_nIndex;
}


void  AutoFadeOutLabelManager::autoDelayEventHandler(int eventType,void * pSender)
{
	if(eventType==_AUTOLABEL_FADEOUT_TYPE_)
	{
		//定时任务 渐隐
		if(m_pShowLabel!=NULL)
		{
		    cocos2d::CCFadeOut * pAction=cocos2d::CCFadeOut::create((m_pErrorTipsData->errorDurationTime-m_pErrorTipsData->errorFadeOutTime)/1000);
			m_pShowLabel->runAction(pAction);
		}
		if(m_pBackSprite!=NULL)
		{
			cocos2d::CCFadeOut * pAction=cocos2d::CCFadeOut::create((m_pErrorTipsData->errorDurationTime-m_pErrorTipsData->errorFadeOutTime)/1000);
			m_pBackSprite->runAction(pAction);
		}
		return ;
	}
	else if(eventType==_Move_Animation_Finish_Event_)
	{
		//播放完毕
		Destroy();
		return;
	}
}

