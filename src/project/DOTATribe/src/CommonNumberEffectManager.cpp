//Name��CommonNumberEffectManager
//Function��ս����ֵ����������
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
     //����Running���е�Tick
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
	 //�ж��Ƿ��Ѿ�����CommonNumberEffectManager
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

	 //����Effect����Cache����  
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
����cache����
*/
void    CommonNumberEffectManager::UpdateCacheList(float dt)
{
   //��CachelistΪ��  ��ô�ر�update
	if(cacheNumberEffectList.empty())
	{
		m_isLoopCall=false;
		unschedule(schedule_selector(CommonNumberEffectManager::UpdateCacheList));
	}
	else
	{
       //ȡ��Cache���� Running
        runningNumberEffectList.push_back(cacheNumberEffectList.front());
		cacheNumberEffectList.pop_front();
	}
}

void    CommonNumberEffectManager::StopAllActions()
{ 
	//�رն�ʱ��
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

