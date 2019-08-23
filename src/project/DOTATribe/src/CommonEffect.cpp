//Name：CommonEffect
//Function：Dota公共特效基类
//Author:	Johny

#include "../include/CommonEffect.h"

CommonEffect::CommonEffect()
{
	m_nCompositeEffectID=0;
	m_nCurEffectState=_COMMONSKILLEFFECT_UNKONW_STATE_;
	objectType_=COMMON_SKILLEFFECT_OBJECT_TYPE;
	objectSubID_=0;
    m_nEffectType=_COMMONEFFECT_UNKONW_EFFECT_TYPE_; 
	m_bIsEffectFlipX=false;
	m_fSpeedScale=1.0f;
	m_bIsLoopEffect=false;
	m_bIsBoneEffect=false;
	m_bIsLocationFollow=false;
	m_bIsAngleFollow=false;
	m_sEffectBindType=_COMMONEFFECT_UNKONW_BIND_TYPE_;
	m_sBoneName="";
}

CommonEffect::~CommonEffect()
{
	Destroy();
}
 

void   CommonEffect::Tick()
{
	if(!IsValid())
		return ;
	BaseObject::Tick();

	if(m_nCurEffectState==_COMMONSKILLEFFECT_ENDACTION_STATE_)
	{
		OnEndEffect();
		return ;
	}
	else if(m_nCurEffectState==_COMMONSKILLEFFECT_BEGINACTION_STATE_)
	{
		OnBeginEffect();
		return ;
	}
	else if(m_nCurEffectState==_COMMONSKILLEFFECT_PAUSEAACTION_STATE_)
	{
		return ;
	}
}

cocos2d::CCPoint  CommonEffect::GetInitPosition()
{
	return CCPointZero;
}


int    CommonEffect::GetEffectType()
{
	return m_nEffectType;
}

int    CommonEffect::GetCompositeEffectID()
{
	return m_nCompositeEffectID;
}

 int    CommonEffect::GetEffectID()
 {
	 return GetSubObjectID();
 }

 bool   CommonEffect::IsEffectLoop()
 {
	  return m_bIsLoopEffect;
 }

 std::string  CommonEffect::GetEffectBindBoneName()
 {
	 return m_sBoneName;
 }

short   CommonEffect::GetEffectBindType()
{
	 return m_sEffectBindType;
}

bool   CommonEffect::IsBoneBindEffect()
{
	return m_bIsBoneEffect;
}

bool   CommonEffect::IsLocationFollow()
{
    return m_bIsLocationFollow;
}

bool   CommonEffect::IsAngleFollow()
{
	return m_bIsAngleFollow;
}

void   CommonEffect::SetAnimationSpeedScale(float speedScale)
{
	m_fSpeedScale=speedScale;
}

 bool  CommonEffect::IsEffectFlipX()
 {
	 return  m_bIsEffectFlipX;
 }
 
std::vector<PCallBack_Node>   CommonEffect::RegisterCallBackEventVec()
{
	std::vector<PCallBack_Node>  emptyCallVec;
	return emptyCallVec;
}


 








  















