//Name：SkillAttachLogicManager
//Function： 技能附加逻辑管理器
//Author:	Johny

#include    "../include/SkillAttachLogicManager.h"
 
template<> SkillAttachLogicManager* cobra_win::Singleton2<SkillAttachLogicManager>::m_pMySelf = NULL;

SkillAttachLogicManager::SkillAttachLogicManager()
{
	 skillAttachLogicMap.clear();
	 CCLOG("SkillAttachLogicManager init");
}

SkillAttachLogicManager::~SkillAttachLogicManager()
{ 
	Destroy();
	CCLOG("SkillAttachLogicManager destroy");
}

 

bool  SkillAttachLogicManager::OnCommandHandler(int eventType,std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft)
{
  if(CheckHadRegisterSkillAttachLogic(eventType))
  {
	  SkillAttachLogicObject * pLogicItem=GetSkillAttachLoginByType(eventType);
	  if(pLogicItem!=NULL)
	  {
		  pLogicItem->OnCommandHanlder(attachParams,isSourceRoleLeft,isTargetRoleLeft);
		  return true;
	  }
  }
  else
  {  
	  //register Login Event Handlder
	  return false;
  }
  return false;
}






void  SkillAttachLogicManager::Init()
{
   //注册各种的逻辑事件

    RegisterSkillAttachLogic(new SkillAttachLogicSourceHPDamage());
	RegisterSkillAttachLogic(new SkillAttachLogicSourceHPHeal());
	RegisterSkillAttachLogic(new SkillAttachLogicSourceMPDamage());
	RegisterSkillAttachLogic(new SkillAttachLogicSourceMPHeal());
	RegisterSkillAttachLogic(new SkillAttachLogicTargetHPDamage());
	RegisterSkillAttachLogic(new SkillAttachLogicTargetHPHeal());
	RegisterSkillAttachLogic(new SkillAttachLogicTargetMPDamage());
	RegisterSkillAttachLogic(new SkillAttachLogicTargetMPHeal());
	RegisterSkillAttachLogic(new SkillAttachLogicChangeShape());
	RegisterSkillAttachLogic(new SkillAttachLogicAddBuffer());
	RegisterSkillAttachLogic(new SkillAttachLogicRemoveBuffer());
	RegisterSkillAttachLogic(new SkillAttachLogicAddState());
	RegisterSkillAttachLogic(new SkillAttachLogicRemoveState());
	RegisterSkillAttachLogic(new SkillAttachLogicReduceMP());
	RegisterSkillAttachLogic(new SkillAttachLogicReliveUpdateHP());
	RegisterSkillAttachLogic(new SkillAttachLogicReliveUpdateMP()); 
	RegisterSkillAttachLogic(new SkillAttachLogicHitNote()); 

 
}
void  SkillAttachLogicManager::Destroy()
{ 
	//销毁各种附加逻辑事件
	std::map<int ,SkillAttachLogicObject *>::iterator  skillLogicIter=skillAttachLogicMap.begin();
	while(skillLogicIter!=skillAttachLogicMap.end())
	{ 
		skillLogicIter->second->Destroy();
	    delete skillLogicIter->second;
		skillAttachLogicMap.erase(skillLogicIter++);
	}
	skillAttachLogicMap.clear();

}

void  SkillAttachLogicManager::Tick()
{
   //Tick
}


SkillAttachLogicObject *  SkillAttachLogicManager::GetSkillAttachLoginByType(int attachLogicType)
{ 
	std::map<int ,SkillAttachLogicObject *>::iterator  skillAttachLogicIter=skillAttachLogicMap.find(attachLogicType);
	if(skillAttachLogicIter!=skillAttachLogicMap.end())
	{
		return  skillAttachLogicIter->second;
	}
    return NULL;
}

int SkillAttachLogicManager::GetHadRegisterEventCount()
{
	return  skillAttachLogicMap.size();
}


long   SkillAttachLogicManager::GetManagerBlockSize()
{
	return sizeof(SkillAttachLogicObject *)*skillAttachLogicMap.size();
}


void   SkillAttachLogicManager::RegisterSkillAttachLogic(SkillAttachLogicObject * attachLogic)
{
	if(attachLogic!=NULL)
	skillAttachLogicMap.insert(std::map<int ,SkillAttachLogicObject *>::value_type(attachLogic->GetSubObjectID(),attachLogic));
}

bool   SkillAttachLogicManager::CheckHadRegisterSkillAttachLogic(int attachLogicType)				   //检测技能附加是否已经加载
{
    if(GetSkillAttachLoginByType(attachLogicType)!=NULL)
	{
		return true;
	}
	return false;
}



bool   SkillAttachLogicManager::UnRegisterSkillAttachLogic(SkillAttachLogicObject * attachLogic)
{
	std::map<int ,SkillAttachLogicObject *>::iterator  skillAttachLogicIter=skillAttachLogicMap.begin();
	while(skillAttachLogicIter!=skillAttachLogicMap.end())
	{
       if(skillAttachLogicIter->second==attachLogic)
	   {
           skillAttachLogicIter->second->Destroy();
           delete skillAttachLogicIter->second;
		   skillAttachLogicIter->second=NULL;
		   skillAttachLogicMap.erase(skillAttachLogicIter);
		   return true;
	   }
		skillAttachLogicIter++;
	}
	return false;
 }

bool   SkillAttachLogicManager::UnRegisterSkillAttachLogic(int attachLogicType)
{
	std::map<int ,SkillAttachLogicObject *>::iterator  skillAttachLogicIter=skillAttachLogicMap.find(attachLogicType);
	if(skillAttachLogicIter!=skillAttachLogicMap.end())
	{
		 skillAttachLogicIter->second->Destroy();
         delete skillAttachLogicIter->second;
		 skillAttachLogicIter->second=NULL;
		 skillAttachLogicMap.erase(skillAttachLogicIter);
		 return true;
	}
	return false;
}


 