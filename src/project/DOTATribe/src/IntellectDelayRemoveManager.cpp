////////////////////////////////////////////////////////////////
//Name:	 IntellectDelayRemoveManager
//Auchor: 	xiaobo.wu
//Func:	 指令计时器(用于延迟删除控制)
//Maintainer: 	xiaobo.wu
//date:   2013/10/29
////////////////////////////////////////////////////////////////
#include "../include/IntellectDelayRemoveManager.h"

IntellectDelayRemoveManager::IntellectDelayRemoveManager()
{
	Init();
}

IntellectDelayRemoveManager::~IntellectDelayRemoveManager()
{ 
	m_pMySelf=NULL;
	Destroy();
}

void  IntellectDelayRemoveManager::Init()
{
	 m_delayRemoveMap.clear();
}

void  IntellectDelayRemoveManager::Destroy()
{
	 m_delayRemoveMap.clear();
}

void IntellectDelayRemoveManager::InsertDelayRemoveManager(int loopEffectID)
{
	if(loopEffectID>=0)
	{
		std::map<int,int>::iterator  loopElement=m_delayRemoveMap.find(loopEffectID);
		if(loopElement!=m_delayRemoveMap.end())
		{
			m_delayRemoveMap.erase(loopElement);
		}  
		m_delayRemoveMap.insert(std::map<int,int>::value_type(loopEffectID,0)); 
	}
}


std::map<int,int>::iterator IntellectDelayRemoveManager::GetDelayRemvoeElement(int loopEffectID)
{  
	std::map<int,int>::iterator  loopElement=m_delayRemoveMap.find(loopEffectID);
    return  loopElement;
}

void IntellectDelayRemoveManager::UpdateDelayRemoveManager()
{
	std::map<int,int>::iterator  loopElement=m_delayRemoveMap.begin();
	while(loopElement!=m_delayRemoveMap.end())
	{
		loopElement->second=loopElement->second+1;
		++loopElement;
	}
}
void IntellectDelayRemoveManager::RemoveDelayRemoveManager(int loopEffectID)
{
	if(loopEffectID>=0)
	{
		std::map<int,int>::iterator  loopElement=m_delayRemoveMap.find(loopEffectID);
		if(loopElement!=m_delayRemoveMap.end())
		{
			m_delayRemoveMap.erase(loopElement);
		}   
	}
}
bool IntellectDelayRemoveManager::IsDelayRemoveAtInterval(int loopEffectID)
{  
	 std::map<int,int>::iterator  loopElement=m_delayRemoveMap.find(loopEffectID);
	 if(loopElement!=m_delayRemoveMap.end())
	 {
		 if(loopElement->second<=1)
		 {
		   return true;
		 }
	 }
	 return false;
}

void IntellectDelayRemoveManager::RemoveAllDelayElement()
{
	m_delayRemoveMap.clear();
}