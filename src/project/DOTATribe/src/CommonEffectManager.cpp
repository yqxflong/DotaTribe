//Name：CommonEffectManager
//Function：特效管理器
//Author:	Johny

#include "../include/CommonEffectManager.h"
#include "../include/AthleticConfig.h"

#include "../include/HeroicRole.h"
#include "../include/CommonEffect.h"
#include "../include/FrameAnimateEffect.h"
#include "../include/ScreenEffect.h"
#include "../include/RoleEffect.h"
#include "../include/ScreenShakeEffect.h"
#include "../include/ParticleEffect.h"
#include "../include/IntellectDelayRemoveManager.h"

CommonEffectManager::CommonEffectManager()
{
	Init();
}
CommonEffectManager::~CommonEffectManager()
{ 
	Destroy();
}

void CommonEffectManager::Init()
{
	//to do 
	m_loopEffectList.clear();
	m_unLoopEffectList.clear();
	m_screenEffectList.clear();
	m_roleEffectList.clear();
	m_fSpeedScale=1.0f;
	m_pHeroicRole=NULL;
}
void CommonEffectManager::Tick()
{  
	std::multimap<int,std::vector<CommonEffect *> >::iterator  loop_Iter=m_loopEffectList.begin();
	while(loop_Iter!=m_loopEffectList.end())
	{ 
		std::vector<CommonEffect *>::iterator  effect_iter=loop_Iter->second.begin();
		while(effect_iter!=loop_Iter->second.end())
		{
			if((*effect_iter)->IsValid())
			{
				(*effect_iter)->Tick();
			}
			else
			{
				//关闭骨骼绑定结点
				RemoveBoneBindCallBack((*effect_iter));
				(*effect_iter)->Destroy();
				delete (*effect_iter);
				effect_iter=loop_Iter->second.erase(effect_iter);
				continue;
			}
			effect_iter++;
		}
		if(loop_Iter->second.empty())
		{
			m_loopEffectList.erase(loop_Iter++);
			continue;
		}
		loop_Iter++;
	}


	std::multimap<int,std::vector<CommonEffect *> >::iterator  unLoop_iter=m_unLoopEffectList.begin();
	while(unLoop_iter!=m_unLoopEffectList.end())
	{ 
		std::vector<CommonEffect *>::iterator  effect_iter=unLoop_iter->second.begin();
		while(effect_iter!=unLoop_iter->second.end())
		{
			if((*effect_iter)->IsValid())
			{
				(*effect_iter)->Tick();
			}
			else
			{
				//关闭骨骼绑定结点
				RemoveBoneBindCallBack((*effect_iter));
				(*effect_iter)->Destroy();
				delete (*effect_iter);
				effect_iter=unLoop_iter->second.erase(effect_iter);
				continue;
			}
			effect_iter++;
		}
		 
		if(unLoop_iter->second.empty())
		{
			m_unLoopEffectList.erase(unLoop_iter++);
			continue;
		}
		unLoop_iter++;
	}

	std::map<int,CommonEffect *>::iterator  screen_iter=m_screenEffectList.begin();
	while(screen_iter!=m_screenEffectList.end())
	{
		if(screen_iter->second!=NULL)
		{ 
			if(screen_iter->second->IsValid())
			{
				screen_iter->second->Tick();
			}
			else
			{ 
				screen_iter->second->Destroy();
				delete screen_iter->second; 
				m_screenEffectList.erase(screen_iter++);
				continue;
			}
		}
		screen_iter++;
	}

	  
	std::map<int,CommonEffect *>::iterator  role_iter=m_roleEffectList.begin();
	while(role_iter!=m_roleEffectList.end())
	{
		if(role_iter->second!=NULL)
		{ 
			if(role_iter->second->IsValid())
			{
				role_iter->second->Tick();
			}
			else
			{
				role_iter->second->Destroy();
				delete role_iter->second; 
				m_roleEffectList.erase(role_iter++);
				continue;
			}
		}
		role_iter++;
	} 

}


void  CommonEffectManager::RemoveBoneBindCallBack(CommonEffect * pCommonEffect)
{
	if(pCommonEffect!=NULL&&m_pHeroicRole!=NULL)
	{
		if(pCommonEffect->IsBoneBindEffect())
		{
			m_pHeroicRole->getRoleSkeletonNode()->removeBoneEffect(pCommonEffect->GetEffectID(),pCommonEffect->GetEffectBindBoneName());
		} 
	}
}


void CommonEffectManager::Destroy()
{ 
	RemoveAllCommonEffect();
}

CommonEffectManager *   CommonEffectManager::CreateCommonEffectManager(HeroicRole * pHeroicRole)
{
    CommonEffectManager * pCommonEffectManager=new  CommonEffectManager();
	if(pCommonEffectManager&&pCommonEffectManager->InitCommonEffectManager(pHeroicRole))
	{
		return pCommonEffectManager;
	}
	if(pCommonEffectManager!=NULL)
	{
		delete pCommonEffectManager;
		pCommonEffectManager=NULL;
	}
	return NULL;
}

bool   CommonEffectManager::InitCommonEffectManager(HeroicRole * pHeroicRole)
{ 
	 if(pHeroicRole!=NULL)
	 { 
		 m_pHeroicRole=pHeroicRole;
		 return true;
	 }
	 return false;
}
 
void    CommonEffectManager::CommonEffectFactory(int compositeEffectID,int effectType,int commonEffectID)
{
	switch(effectType)
	{
	 case  CommonEffect::_COMMONEFFECT_FRAME_ANIMATE_EFFECT_TYPE_:
		  {
			  CommonEffect * pFrameAnimationEffect=FrameAnimateEffect::CreateFrameAnimateEffect(compositeEffectID,commonEffectID,!m_pHeroicRole->isFightAtLeft());	   
			  AddCommonEffect(pFrameAnimationEffect);
			  break;
		  }
	 case CommonEffect::_COMMONEFFECT_PARTICLE_EFFECT_TYPE_:
		  {
			  CommonEffect *  pParticleEffect=ParticleEffect::CreateParticleEffect(compositeEffectID,commonEffectID,!m_pHeroicRole->isFightAtLeft());
			  AddCommonEffect(pParticleEffect);
			 break;
		  }
	 case CommonEffect::_COMMONEFFECT_SKELETON_EFFECT_TYPE_:
		  {
			 break;
		  }
	 case CommonEffect::_COMMONEFFECT_SHAKE_EFFECT_TYPE_:
		  {
			  AthleticsSceneManager::get_instance2()->OnPlayScreenShake(compositeEffectID,commonEffectID);
			 break;
		  }
	 case CommonEffect::_COMMONEFFECT_SCREEN_EFFECT_TYPE_:
		  { 
			  RemoveScreenEffect();
			  CommonEffect * pScreenEffect=ScreenEffect::CreateScreenEffectWithID(compositeEffectID,commonEffectID);
			  AddCommonEffect(pScreenEffect);
			 break;
		  }
	 case  CommonEffect::_COMMONEFFECT_ROLE_EFFECT_TYPE_:
		  {
			  RemoveRoleEffect();
			  CommonEffect * pRoleEffect=RoleEffect::CreateRoleEffect(compositeEffectID,m_pHeroicRole,commonEffectID);
			  AddCommonEffect(pRoleEffect);
			 break;
		  }
	 default:
		 break;
	}
}

void   CommonEffectManager::AddCompositeEffect(int compositeEffectID)
{ 
	//compositeEffectID
	CompositeEffectData * pCompositeEffectData=CompositeEffectDataManager::get_instance2()->GetCompositeEffectDataByID(compositeEffectID);
	if(compositeEffectID!=NULL)
	{ 
		if(pCompositeEffectData->soundEffectID!=-1)
		{
			//发送播放音效通知
			char _soundID[128] = "";
			sprintf(_soundID,"%d",pCompositeEffectData->soundEffectID);
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOUND_PLAY_,_soundID);
		}
		size_t effectCount=pCompositeEffectData->compositeEffectVec.size();
		FOR_EACH_EFFECT_BEGIN(effectCount)
			CEffectData  effectData=pCompositeEffectData->compositeEffectVec.at(index);
			switch(effectData.effectType)
			{
			case  CommonEffect::_COMMONEFFECT_FRAME_ANIMATE_EFFECT_TYPE_:
				{
					FrameAnimateData * pFrameAnimateData=FrameAnimateDataManager::get_instance2()->GetFrameAnimateDataByID(effectData.effectID);
					if(pFrameAnimateData!=NULL)
					{
						std::string boneName= pFrameAnimateData->frameAnimateEffectBoneName;
						if(boneName!="root"&&boneName!="screen")
						{
							cocos2d::extension::Bone * pParentBone=m_pHeroicRole->getRoleSkeletonNode()->findBone(boneName.c_str());
							if(pParentBone!=NULL)
							{
								BoneEfectData  boneEffectData;
								boneEffectData.boneEffectID=effectData.effectID;
								boneEffectData.compositeEffectID=compositeEffectID;
								boneEffectData.boneEffectType=effectData.effectType;
								boneEffectData.boneName=boneName;
								boneEffectData.parentBone=pParentBone;
								boneEffectData.isLoopBoneEffect=pFrameAnimateData->frameAnimateEffectPlayType==1? true:false;
								boneEffectData.isFollowBoneEffect=(pFrameAnimateData->frameAnimateIsLocationFollow==1? true:false)||(pFrameAnimateData->frameAnimateIsAngleFollow==1? true:false);
								m_pHeroicRole->getRoleSkeletonNode()->addBoneEffectWithData(boneEffectData);
							} 
						} 
						else
						{
							CommonEffectFactory(compositeEffectID,effectData.effectType,effectData.effectID);
						}
						continue;
					} 
				}
				break;
			case  CommonEffect::_COMMONEFFECT_PARTICLE_EFFECT_TYPE_:
				{
					ParticleData * pParticleData=ParticleDataManager::get_instance2()->GetParticleDataByID(effectData.effectID);
					if(pParticleData!=NULL)
					{
						std::string boneName= pParticleData->particleEffectBoneName;
						if(boneName!="root"&&boneName!="screen")
						{
							cocos2d::extension::Bone * pParentBone=m_pHeroicRole->getRoleSkeletonNode()->findBone(boneName.c_str());
							if(pParentBone!=NULL)
							{
								BoneEfectData  boneEffectData;
								boneEffectData.boneEffectID=effectData.effectID;
								boneEffectData.compositeEffectID=compositeEffectID;
								boneEffectData.boneEffectType=effectData.effectType;
								boneEffectData.boneName=boneName;
								boneEffectData.parentBone=pParentBone;
								boneEffectData.isLoopBoneEffect=pParticleData->particleEffectPlayType==1? true:false;
								boneEffectData.isFollowBoneEffect=(pParticleData->particleEffectIsLocationFollow==1? true:false)||(pParticleData->particleEffectIsAngleFollow==1? true:false);
								m_pHeroicRole->getRoleSkeletonNode()->addBoneEffectWithData(boneEffectData);
							} 
						} 
						else
						{
							CommonEffectFactory(compositeEffectID,effectData.effectType,effectData.effectID);
						}
						continue;
					} 
					continue;
				}
				break;
			case  CommonEffect::_COMMONEFFECT_SKELETON_EFFECT_TYPE_:
				{
					CommonEffectFactory(compositeEffectID,effectData.effectType,effectData.effectID);
					continue;
				}
				break;
			case  CommonEffect::_COMMONEFFECT_SHAKE_EFFECT_TYPE_:
				{
					CommonEffectFactory(compositeEffectID,effectData.effectType,effectData.effectID);
					continue;
				}
				break;
			case CommonEffect::_COMMONEFFECT_SCREEN_EFFECT_TYPE_:
				{
					CommonEffectFactory(compositeEffectID,effectData.effectType,effectData.effectID);
					continue;
				}
				break;
			case CommonEffect::_COMMONEFFECT_ROLE_EFFECT_TYPE_:
				{
					CommonEffectFactory(compositeEffectID,effectData.effectType,effectData.effectID);
					continue;
				}
				break;
			default:
				break;
			}
		FOR_EACH_EFFECT_END 
	}
}


 
void    CommonEffectManager::CommonEffectFactoryWithBone(int compositeEffectID,int effectType,int commonEffectID,cocos2d::extension::Bone * pBindBone)
{
	switch(effectType)
	{
	case  CommonEffect::_COMMONEFFECT_FRAME_ANIMATE_EFFECT_TYPE_:
		{
			CommonEffect * pFrameAnimationEffect=FrameAnimateEffect::CreateFrameAnimateEffectWithBone(compositeEffectID,commonEffectID,!m_pHeroicRole->isFightAtLeft(),pBindBone);   
			AddCommonEffect(pFrameAnimationEffect);
			break;
		}
	case CommonEffect::_COMMONEFFECT_PARTICLE_EFFECT_TYPE_:
		{
			CommonEffect *  pParticleEffect=ParticleEffect::CreateParticleEffect(compositeEffectID,commonEffectID,!m_pHeroicRole->isFightAtLeft(),pBindBone);
			AddCommonEffect(pParticleEffect);
			break;
		}
	case CommonEffect::_COMMONEFFECT_SKELETON_EFFECT_TYPE_:
		{
			break;
		}
	default:
		break;
	}
}



void    CommonEffectManager::AddCommonEffect(CommonEffect * pCommonEffect)
{
	if(pCommonEffect!=NULL)
	{  
		switch(pCommonEffect->GetEffectType())
		{
			case CommonEffect::_COMMONEFFECT_SHAKE_EFFECT_TYPE_:
			break;
			case CommonEffect::_COMMONEFFECT_SCREEN_EFFECT_TYPE_:
				m_screenEffectList.insert(std::map<int,CommonEffect *>::value_type(pCommonEffect->GetCompositeEffectID(),pCommonEffect));
			break;
			case CommonEffect::_COMMONEFFECT_ROLE_EFFECT_TYPE_:
				m_roleEffectList.insert(std::map<int,CommonEffect *>::value_type(pCommonEffect->GetCompositeEffectID(),pCommonEffect));
			break;
			default:
			{
				if(pCommonEffect->IsEffectLoop())
				{ 
					std::multimap<int,std::vector<CommonEffect *> >::iterator composite_iter=m_loopEffectList.find(pCommonEffect->GetCompositeEffectID());
					if(composite_iter!=m_loopEffectList.end())
					{
						composite_iter->second.push_back(pCommonEffect);
					}
					else
					{
						std::vector<CommonEffect *> effectVector;
						effectVector.push_back(pCommonEffect);
						m_loopEffectList.insert(std::multimap<int,std::vector<CommonEffect *> >::value_type(pCommonEffect->GetCompositeEffectID(),effectVector));
					}
					//打补丁咯 哎
					IntellectDelayRemoveManager::get_instance2()->InsertDelayRemoveManager(pCommonEffect->GetCompositeEffectID());	 
					return ;
				}
				else
				{
					std::multimap<int,std::vector<CommonEffect *> >::iterator composite_iter=m_unLoopEffectList.find(pCommonEffect->GetCompositeEffectID());
					if(composite_iter!=m_unLoopEffectList.end())
					{
						composite_iter->second.push_back(pCommonEffect);
					}
					else
					{
						std::vector<CommonEffect *> effectVector;
						effectVector.push_back(pCommonEffect);
						m_unLoopEffectList.insert(std::multimap<int,std::vector<CommonEffect *> >::value_type(pCommonEffect->GetCompositeEffectID(),effectVector));
					}
				}
			}
			return ;
		}
	}
}
void    CommonEffectManager::RemoveCommonEffect(CommonEffect * pCommonEffect)
{
   if(pCommonEffect->IsEffectLoop())
   {
	   std::multimap<int,std::vector<CommonEffect *> >::iterator composite_iter=m_loopEffectList.find(pCommonEffect->GetCompositeEffectID());
	   if(composite_iter!=m_loopEffectList.end())
	   {
		   std::vector<CommonEffect *>::iterator  effect_iter=composite_iter->second.begin();
		   while(effect_iter!=composite_iter->second.end())
		   {
			   if((*effect_iter)==pCommonEffect)
			   { 
				   (*effect_iter)->Destroy();
				   delete (*effect_iter);
				   effect_iter=composite_iter->second.erase(effect_iter);
				   return ;
			   }
			   effect_iter++;
		   }
		   if(composite_iter->second.empty())
		   {
			   m_loopEffectList.erase(composite_iter);
		   }
	   }
	   return ;
    }
   else
   {
	   std::multimap<int,std::vector<CommonEffect *> >::iterator composite_iter=m_unLoopEffectList.find(pCommonEffect->GetCompositeEffectID());
	   if(composite_iter!=m_unLoopEffectList.end())
	   {
		   std::vector<CommonEffect *>::iterator  effect_iter=composite_iter->second.begin();
		   while(effect_iter!=composite_iter->second.end())
		   {
			   if((*effect_iter)==pCommonEffect)
			   { 
				   (*effect_iter)->Destroy();
				   delete (*effect_iter);
				   effect_iter=composite_iter->second.erase(effect_iter);
				   return ;
			   }
			   effect_iter++;
		   }
		   if(composite_iter->second.empty())
		   {
			   m_unLoopEffectList.erase(composite_iter);
		   }
	   }
	   return ;
   }
}
 
void    CommonEffectManager::RemoveScreenEffect()
{
	std::map<int,CommonEffect *>::iterator screen_effect_Iter=m_screenEffectList.begin();
	while(screen_effect_Iter!=m_screenEffectList.end())
	{
		if(screen_effect_Iter->second!=NULL)
			screen_effect_Iter->second->Destroy();
		delete screen_effect_Iter->second;
		m_screenEffectList.erase(screen_effect_Iter++);
	}
	m_screenEffectList.clear();
}


void    CommonEffectManager::RemoveRoleEffect()
{
	std::map<int,CommonEffect *>::iterator role_effect_Iter=m_roleEffectList.begin();
	while(role_effect_Iter!=m_roleEffectList.end())
	{
		if(role_effect_Iter->second!=NULL)
			role_effect_Iter->second->Destroy();
		delete role_effect_Iter->second;
		m_roleEffectList.erase(role_effect_Iter++);
	}
}
 
void   CommonEffectManager::RemoveScreenShakeEffect()
{  
	AthleticsSceneManager::get_instance2()->OnStopScreenShake();
}


size_t  CommonEffectManager::GetLoopCommonEffectCount()
{
	return m_loopEffectList.size();
}
size_t	CommonEffectManager::GetUnLoopCommonEffectCount()
{
	return m_unLoopEffectList.size();
}


void    CommonEffectManager::RemoveAllCommonEffect()
{ 
	 RemoveScreenEffect();
	 RemoveScreenShakeEffect();
	 RemoveRoleEffect();
	 RemoveAllLoopCommonEffect();
	 RemoveAllUnLoopCommonEffect();
}


void   CommonEffectManager::RemoveAllLoopCommonEffect()
{
	std::multimap<int,std::vector<CommonEffect *> >::iterator composite_Iter=m_loopEffectList.begin();
	while(composite_Iter!=m_loopEffectList.end())
	{
		FOR_EACH_EFFECT_BEGIN(composite_Iter->second.size())
			RemoveBoneBindCallBack(composite_Iter->second.at(index));
			composite_Iter->second.at(index)->Destroy();
		delete composite_Iter->second.at(index);
		FOR_EACH_EFFECT_END
			composite_Iter->second.clear();
		m_loopEffectList.erase(composite_Iter++);
	} 
	m_loopEffectList.clear();

}

void    CommonEffectManager::SetAllBindBoneEffectVisible(bool isVisible/* =false */)
{
	std::multimap<int,std::vector<CommonEffect *> >::iterator loop_iter=m_loopEffectList.begin();
	while(loop_iter!=m_loopEffectList.end())
	{
		FOR_EACH_EFFECT_BEGIN(loop_iter->second.size())
		  SetBondEffectVisible(loop_iter->second.at(index),isVisible);
		FOR_EACH_EFFECT_END 
		++loop_iter; 
	} 

	std::multimap<int,std::vector<CommonEffect *> >::iterator unloop_iter=m_unLoopEffectList.begin();
	while(unloop_iter!=m_unLoopEffectList.end())
	{
		FOR_EACH_EFFECT_BEGIN(unloop_iter->second.size())
		 SetBondEffectVisible(unloop_iter->second.at(index),isVisible);
		FOR_EACH_EFFECT_END
		++unloop_iter;
	}  
}
 

void   CommonEffectManager::SetBondEffectVisible(CommonEffect * pCommonEffect,bool isVisible)
{
	if(pCommonEffect!=NULL&&pCommonEffect->IsBoneBindEffect())
	{
       pCommonEffect->SetVisible(isVisible);
	}
}

 
void    CommonEffectManager::RemoveAllUnLoopCommonEffect()
{
	std::multimap<int,std::vector<CommonEffect *> >::iterator unloop_Iter=m_unLoopEffectList.begin();
	while(unloop_Iter!=m_unLoopEffectList.end())
	{
		FOR_EACH_EFFECT_BEGIN(unloop_Iter->second.size())
			RemoveBoneBindCallBack(unloop_Iter->second.at(index));
			unloop_Iter->second.at(index)->Destroy();
			delete unloop_Iter->second.at(index);
		FOR_EACH_EFFECT_END
			unloop_Iter->second.clear();
		m_unLoopEffectList.erase(unloop_Iter++);
	}
}

void  CommonEffectManager::RemoveAllUnLoopBindBoneEffect()
{
	std::multimap<int,std::vector<CommonEffect *> >::iterator unloop_Iter=m_unLoopEffectList.begin();
	while(unloop_Iter!=m_unLoopEffectList.end())
	{
		FOR_EACH_EFFECT_BEGIN(unloop_Iter->second.size())
			if(unloop_Iter->second.at(index)->IsBoneBindEffect()&&!unloop_Iter->second.at(index)->IsEffectLoop())
			{  
				unloop_Iter->second.at(index)->Destroy();
			}
		FOR_EACH_EFFECT_END
		unloop_Iter++;
	}
}


 
void    CommonEffectManager::RemoveCompositeEffectWithID(int compositeEffectID)
{  
	std::multimap<int,std::vector<CommonEffect *> >::iterator composite_Iter=m_loopEffectList.find(compositeEffectID);
	if(composite_Iter!=m_loopEffectList.end())
	{
		FOR_EACH_EFFECT_BEGIN(composite_Iter->second.size())
			composite_Iter->second.at(index)->Destroy();
		    delete composite_Iter->second.at(index);
		FOR_EACH_EFFECT_END
		composite_Iter->second.clear();
		m_loopEffectList.erase(composite_Iter);
	}

	std::multimap<int,std::vector<CommonEffect *> >::iterator unloop_Iter=m_unLoopEffectList.find(compositeEffectID);
	if(unloop_Iter!=m_unLoopEffectList.end())
	{
		FOR_EACH_EFFECT_BEGIN(unloop_Iter->second.size())
			unloop_Iter->second.at(index)->Destroy();
		    delete unloop_Iter->second.at(index);
		FOR_EACH_EFFECT_END
			unloop_Iter->second.clear();
		m_unLoopEffectList.erase(unloop_Iter);
	}
	
	std::map<int,CommonEffect *>::iterator screen_effect_Iter=m_screenEffectList.find(compositeEffectID);
	if(screen_effect_Iter!=m_screenEffectList.end())
	{
		if(screen_effect_Iter->second!=NULL)
		screen_effect_Iter->second->Stop();
	}

	AthleticsSceneManager::get_instance2()->OnStopScreenShake(compositeEffectID);

  
	std::map<int,CommonEffect *>::iterator role_effect_Iter=m_roleEffectList.find(compositeEffectID);
	if(role_effect_Iter!=m_roleEffectList.end())
	{
		if(role_effect_Iter->second!=NULL)
		role_effect_Iter->second->Stop();
	}
	  
}

void    CommonEffectManager::SetAnimationSpeedScale(float speedScale)
{  
	m_fSpeedScale=speedScale;
	std::multimap<int,std::vector<CommonEffect *> >::iterator  loop_Iter=m_loopEffectList.begin();
	while(loop_Iter!=m_loopEffectList.end())
	{ 
		std::vector<CommonEffect *>::iterator  effect_iter=loop_Iter->second.begin();
		while(effect_iter!=loop_Iter->second.end())
		{
			if((*effect_iter)->IsValid())
			{
				(*effect_iter)->SetAnimationSpeedScale(speedScale);
			}
			effect_iter++;
		}
		loop_Iter++;
	}
	 
	std::multimap<int,std::vector<CommonEffect *> >::iterator  unLoop_iter=m_unLoopEffectList.begin();
	while(unLoop_iter!=m_unLoopEffectList.end())
	{ 
		std::vector<CommonEffect *>::iterator  effect_iter=unLoop_iter->second.begin();
		while(effect_iter!=unLoop_iter->second.end())
		{
			if((*effect_iter)->IsValid())
			{
				(*effect_iter)->SetAnimationSpeedScale(speedScale);
			}
			effect_iter++;
		}
		unLoop_iter++;
	}

	std::map<int,CommonEffect *>::iterator  screen_iter=m_screenEffectList.begin();
	while(screen_iter!=m_screenEffectList.end())
	{
		if(screen_iter->second!=NULL)
		{ 
			if(screen_iter->second->IsValid())
			{
				screen_iter->second->SetAnimationSpeedScale(speedScale);
			}
		}
		screen_iter++;
	}


	AthleticsSceneManager::get_instance2()->OnSetScreenShakeEffectSpeedScale();

	  
	std::map<int,CommonEffect *>::iterator  role_iter=m_roleEffectList.begin();
	while(role_iter!=m_roleEffectList.end())
	{
		if(role_iter->second!=NULL)
		{ 
			if(role_iter->second->IsValid())
			{
				role_iter->second->SetAnimationSpeedScale(speedScale);
			}
		}
		role_iter++;
	} 
}
void   CommonEffectManager::UpdatePosition(cocos2d::CCPoint  position)
{
	std::multimap<int,std::vector<CommonEffect *> >::iterator  loop_Iter=m_loopEffectList.begin();
	while(loop_Iter!=m_loopEffectList.end())
	{ 
		std::vector<CommonEffect *>::iterator  effect_iter=loop_Iter->second.begin();
		while(effect_iter!=loop_Iter->second.end())
		{
			if((*effect_iter)->IsValid()&&!(*effect_iter)->IsBoneBindEffect())
			{
				(*effect_iter)->UpdatePosition(position);
			}
			effect_iter++;
		}
		loop_Iter++;
	}

	std::multimap<int,std::vector<CommonEffect *> >::iterator  unLoop_iter=m_unLoopEffectList.begin();
	while(unLoop_iter!=m_unLoopEffectList.end())
	{ 
		std::vector<CommonEffect *>::iterator  effect_iter=unLoop_iter->second.begin();
		while(effect_iter!=unLoop_iter->second.end())
		{
			if((*effect_iter)->IsValid()&&!(*effect_iter)->IsBoneBindEffect())
			{
				(*effect_iter)->UpdatePosition(position);
			}
			effect_iter++;
		}
		unLoop_iter++;
	} 
}


void    CommonEffectManager::UpdateWithBone(int compositeEffectID,int commonEffectID,int commoneEffectType, std::string  bindBoneName, cocos2d::extension::Bone * pBindBone)
{
	std::multimap<int,std::vector<CommonEffect *> >::iterator  loop_Iter=m_loopEffectList.begin();
	while(loop_Iter!=m_loopEffectList.end())
	{ 
		std::vector<CommonEffect *>::iterator  effect_iter=loop_Iter->second.begin();
		while(effect_iter!=loop_Iter->second.end())
		{
			if((*effect_iter)->IsValid()&&(*effect_iter)->IsBoneBindEffect())
			{
				if((*effect_iter)->GetCompositeEffectID()==compositeEffectID&&(*effect_iter)->GetEffectID()==commonEffectID&&
					(*effect_iter)->GetEffectBindBoneName()==bindBoneName)
				(*effect_iter)->UpdateWithBone(pBindBone);
			}
			effect_iter++;
		}
		loop_Iter++;
	}

	std::multimap<int,std::vector<CommonEffect *> >::iterator  unLoop_iter=m_unLoopEffectList.begin();
	while(unLoop_iter!=m_unLoopEffectList.end())
	{ 
		std::vector<CommonEffect *>::iterator  effect_iter=unLoop_iter->second.begin();
		while(effect_iter!=unLoop_iter->second.end())
		{
			if((*effect_iter)->IsValid()&&(*effect_iter)->IsBoneBindEffect())
			{
				if((*effect_iter)->GetCompositeEffectID()==compositeEffectID&&(*effect_iter)->GetEffectID()==commonEffectID&&
					(*effect_iter)->GetEffectBindBoneName()==bindBoneName)
				(*effect_iter)->UpdateWithBone(pBindBone);
			}
			effect_iter++;
		}
		unLoop_iter++;
	} 
}





