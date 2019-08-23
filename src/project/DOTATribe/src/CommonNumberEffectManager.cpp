//Name：CommonNumberEffectManager
//Function：战斗数值动画管理器
//Author:	Johny

#include   "../include/CommonNumberEffectManager.h"
#include   "../include/AthleticsWindow.h"

#include <cocos2d.h>

using  namespace  cobra_win;
using namespace cocos2d;


#define   LeftNumberEffectManagerTag   10101
#define   RightNumberEffectManagerTag  20202
#define   BASEDELAYTIME    0.45f



CommonNumberEffectManager::CommonNumberEffectManager()
{
     Init(); 
} 

CommonNumberEffectManager::~CommonNumberEffectManager()
{
     Destroy();
}

void CommonNumberEffectManager::Init()
{
	m_isLoopCall=false;
	m_delayTime=0.13f;
	m_isValid=true;
	runningNumberEffectList.clear();
	cacheNumberEffectList.clear();

}

void CommonNumberEffectManager::Tick()
{
     //更新Running队列的Tick
	if(!m_isValid)
		return ;

	std::list<CommonNumberEffect *>::iterator iter_effect=runningNumberEffectList.begin();
	while(iter_effect!=runningNumberEffectList.end())
	{  
		if(*iter_effect!=NULL)
		{
			if((*iter_effect)->IsValid())
			{
				(*iter_effect)->Tick();
			}
			else
			{
				(*iter_effect)->Destroy();
				delete  (*iter_effect);
				runningNumberEffectList.erase(iter_effect++);
				continue;  
			}
		}
		iter_effect++;
	}
}

void CommonNumberEffectManager::Destroy()
{ 
	m_isValid=false;
    StopAllActions();
}

CommonNumberEffectManager *  CommonNumberEffectManager::CreateNumberEffectManager(HeroicRole  * pHeroicRole)
{  
	 //判断是否已经存在CommonNumberEffectManager
	 CommonNumberEffectManager  * pCommonNumberEffectManager=NULL;
	 cocos2d::CCNode * pBaseLayer=Athletics_UI_Root();
 
	  if(pBaseLayer!=NULL)
	  {
		  if(pHeroicRole->isFightAtLeft())
		  {
			  pCommonNumberEffectManager=(CommonNumberEffectManager *)pBaseLayer->getChildByTag(LeftNumberEffectManagerTag);
			  if(pCommonNumberEffectManager!=NULL)
			  {
				  return pCommonNumberEffectManager;
			  } 
		  }
		  else
		  { 
			  pCommonNumberEffectManager=(CommonNumberEffectManager *)pBaseLayer->getChildByTag(RightNumberEffectManagerTag);
			  if(pCommonNumberEffectManager!=NULL)
			  {
				  return pCommonNumberEffectManager;
			  } 
		  }
	  }
	  if(pCommonNumberEffectManager==NULL)
	  {
		  CommonNumberEffectManager  * pCommonNumberEffectManager=new  CommonNumberEffectManager();
		  if(pCommonNumberEffectManager!=NULL)
		  {  
			  pCommonNumberEffectManager->autorelease();
			  if(pBaseLayer!=NULL)
			  {
				  if(pHeroicRole->isFightAtLeft())
				  {
					  pBaseLayer->addChild(pCommonNumberEffectManager,0,LeftNumberEffectManagerTag);
				  }
				  else
				  {
					  pBaseLayer->addChild(pCommonNumberEffectManager,0,RightNumberEffectManagerTag);
				  }
			  }
			  return  pCommonNumberEffectManager;
		  }
	  }

	  return pCommonNumberEffectManager;

}

void  CommonNumberEffectManager::AddNumberEffect(HeroicRole * pOwnRole,int numberType,int numbericalValue,int numberEffectID)
{
	 if(!m_isValid)
		 return ;
     if(!m_isLoopCall)
	 {
		 m_isLoopCall=true;
         schedule(schedule_selector(CommonNumberEffectManager::UpdateCacheList), m_delayTime);
	 }

	 //创建Effect加入Cache队列  
	 CommonNumberEffect * pCommonNumberEffect=CommonNumberEffect::CreateCommonNumberEffect(pOwnRole,numberType,numberEffectID,numbericalValue);
	 if(pCommonNumberEffect!=NULL)
	 { 
          cacheNumberEffectList.push_back(pCommonNumberEffect);
	 } 

	 if(runningNumberEffectList.empty())
	 {
		 UpdateCacheList(0.0f);
	 }
}

/*
更新cache队列
*/
void    CommonNumberEffectManager::UpdateCacheList(float dt)
{
   //若Cachelist为空  那么关闭update
	if(cacheNumberEffectList.empty())
	{
		m_isLoopCall=false;
		unschedule(schedule_selector(CommonNumberEffectManager::UpdateCacheList));
	}
	else
	{
       //取走Cache加入 Running
        runningNumberEffectList.push_back(cacheNumberEffectList.front());
		cacheNumberEffectList.pop_front();
	}
}

void    CommonNumberEffectManager::StopAllActions()
{ 
	//关闭定时器
	 m_isLoopCall=false;
	 unschedule(schedule_selector(CommonNumberEffectManager::UpdateCacheList));
	 std::list<CommonNumberEffect *>::iterator iter_runeffect=runningNumberEffectList.begin();
	 while(iter_runeffect!=runningNumberEffectList.end())
	 {   
		  (*iter_runeffect)->Destroy();
		  delete  (*iter_runeffect);
		  iter_runeffect++;
	 }
	 runningNumberEffectList.clear();

	 std::list<CommonNumberEffect *>::iterator iter_cacheeffect=cacheNumberEffectList.begin();
	 while(iter_cacheeffect!=cacheNumberEffectList.end())
	 {   
		 (*iter_cacheeffect)->Destroy();
		 delete  (*iter_cacheeffect);
		 iter_cacheeffect++;
	 }
	 cacheNumberEffectList.clear();
    
}


size_t CommonNumberEffectManager::GetCurNumberEffectCount()
{
   return runningNumberEffectList.size()+cacheNumberEffectList.size();
}
 
bool  CommonNumberEffectManager::HadAllEffectTriggeredNumberUpdate()
{
	if(cacheNumberEffectList.empty())
	{ 
		bool isAllEffectTriggeredUpdate=true;
		std::list<CommonNumberEffect *>::iterator iter_cacheeffect=runningNumberEffectList.begin();
		while(iter_cacheeffect!=runningNumberEffectList.end())
		{   
			isAllEffectTriggeredUpdate&=(*iter_cacheeffect)->GetHadTriggeredNumberUpdate();
			iter_cacheeffect++;
		}
		return isAllEffectTriggeredUpdate;
	}
	return false;
}

 
 
void  CommonNumberEffectManager::SetDelayTime(float delayTime)
{
    if(m_delayTime!=delayTime)
	{
		m_delayTime=delayTime;
		unschedule(schedule_selector(CommonNumberEffectManager::UpdateCacheList));
		schedule(schedule_selector(CommonNumberEffectManager::UpdateCacheList), m_delayTime);
		m_isLoopCall=true;
	}
}

float CommonNumberEffectManager::GetDelatTime()
{ 
	return m_delayTime;
}


void    CommonNumberEffectManager::SetAnimationSpeedScale(float speedScale)
{

	std::list<CommonNumberEffect *>::iterator iter_effect=runningNumberEffectList.begin();
	while(iter_effect!=runningNumberEffectList.end())
	{  
		if(*iter_effect!=NULL)
		{
			(*iter_effect)->SetNumberEffectSpeedScale(speedScale);
		}
		iter_effect++;
	}
	SetDelayTime(BASEDELAYTIME/speedScale);
}

