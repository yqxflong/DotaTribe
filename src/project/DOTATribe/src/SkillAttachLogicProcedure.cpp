//Name：SkillAttachLogicProcedure
//Function： 技能附加逻辑处理单元
//Author:	Johny

#include <cocos2d.h>
#include "../include/SkillAttachLogicProcedure.h"
#include  "../include/AthleticsSceneManager.h"
#include  "../include/CommonSkillActionProcedure.h"




SkillAttachLogicObject::SkillAttachLogicObject()
{
	objectType_=SKILLATTACHLOGIC_OBJECT_TYPE;
	objectSubID_=_ATHLETICS_SKILL_UNKONW_TYPE_;
}

SkillAttachLogicObject::~SkillAttachLogicObject()
{  

} 
 
void SkillAttachLogicObject::Tick()
{

}
void SkillAttachLogicObject::Destroy()
{

} 

//////////////////////////////////////////////////////////////////////////
//技能附加特效逻辑
//////////////////////////////////////////////////////////////////////////


SkillAttachLogicSourceHPDamage::SkillAttachLogicSourceHPDamage()
{
   objectSubID_=_ATHLETICS_SKILL_SOURCE_HP_DAMAGE_TYPE_;
}

SkillAttachLogicSourceHPDamage::~SkillAttachLogicSourceHPDamage()
{

}


void   SkillAttachLogicSourceHPDamage::OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft)
{
    if(attachParams.size()>=4)
	{
		HeroicRole * pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
	    if(pHeroicRole!=NULL&&(pHeroicRole->GetSubObjectID()!=atoi(attachParams.at(2).c_str())||pHeroicRole->getRoleType()!=atoi(attachParams.at(1).c_str())))
		{
			pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
		}
		if(pHeroicRole!=NULL)
		{
			int effectID=atoi(attachParams.at(0).c_str());
			if(effectID!=_ATHLETICS_SKILL_UNKONW_TYPE_)
			{
				pHeroicRole->OnPlayCommonEffect(effectID);
			}
			if(attachParams.size()>=5)
			{
				pHeroicRole->OnPlayNumberBufferByID(_BAOJI_NUMBERICALFONT_FOAMATID_,_BAOJI_NUMBERICALFONT_FOAMATID_,atoi(attachParams[3].c_str()));
			}
			else
			{
				pHeroicRole->OnPlayNumberBufferByID(_HPDAMAGE_NUMBERICALFONT_FORMATID_,_HPDAMAGE_NUMBERICALFONT_FORMATID_,atoi(attachParams[3].c_str()));
			}
		}
	}
}

  
SkillAttachLogicSourceHPHeal::SkillAttachLogicSourceHPHeal()
{
    objectSubID_=_ATHLETICS_SKILL_SOURCE_HP_HEAL_TYPE_;
}

SkillAttachLogicSourceHPHeal::~SkillAttachLogicSourceHPHeal()
{

}
void SkillAttachLogicSourceHPHeal::OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft)
{
	if(attachParams.size()>=4)
	{
		HeroicRole * pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
		if(pHeroicRole!=NULL&&(pHeroicRole->GetSubObjectID()!=atoi(attachParams.at(2).c_str())||pHeroicRole->getRoleType()!=atoi(attachParams.at(1).c_str())))
		{
			pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
		}
		if(pHeroicRole!=NULL)
		{
			int effectID=atoi(attachParams.at(0).c_str());
			if(effectID!=_ATHLETICS_SKILL_UNKONW_TYPE_)
			{
				pHeroicRole->OnPlayCommonEffect(effectID);
			}
		    pHeroicRole->OnPlayNumberBufferByID(_HPHEAL_NUMBERICALFONT_FORMATID_,_HPHEAL_NUMBERICALFONT_FORMATID_,atoi(attachParams[3].c_str()));
		}
	}
}


SkillAttachLogicSourceMPDamage::SkillAttachLogicSourceMPDamage()
{
   objectSubID_=_ATHLETICS_SKILL_SOURCE_MP_DAMAGE_TYPE_;
}

SkillAttachLogicSourceMPDamage::~SkillAttachLogicSourceMPDamage()
{

}

void SkillAttachLogicSourceMPDamage::OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft)
{
	if(attachParams.size()>=4)
	{
		HeroicRole * pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
		if(pHeroicRole!=NULL&&(pHeroicRole->GetSubObjectID()!=atoi(attachParams.at(2).c_str())||pHeroicRole->getRoleType()!=atoi(attachParams.at(1).c_str())))
		{
			pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
		}
		if(pHeroicRole!=NULL)
		{
			int effectID=atoi(attachParams.at(0).c_str());
			if(effectID!=_ATHLETICS_SKILL_UNKONW_TYPE_)
			{
				pHeroicRole->OnPlayCommonEffect(effectID);
			}
			pHeroicRole->OnPlayNumberBufferByID(_MPDAMAGE_NUMBERICALFONT_FORMATID_,_MPDAMAGE_NUMBERICALFONT_FORMATID_,atoi(attachParams[3].c_str()));
		}
	}
}

 
 
SkillAttachLogicSourceMPHeal::SkillAttachLogicSourceMPHeal()
{
   objectSubID_=_ATHLETICS_SKILL_SOURCE_MP_HEAL_TYPE_;
}
SkillAttachLogicSourceMPHeal::~SkillAttachLogicSourceMPHeal()
{

}


void SkillAttachLogicSourceMPHeal::OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft)
{
	if(attachParams.size()>=4)
	{
		HeroicRole * pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
		if(pHeroicRole!=NULL&&(pHeroicRole->GetSubObjectID()!=atoi(attachParams.at(2).c_str())||pHeroicRole->getRoleType()!=atoi(attachParams.at(1).c_str())))
		{
			pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
		}
		if(pHeroicRole!=NULL)
		{
			int effectID=atoi(attachParams.at(0).c_str());
			if(effectID!=_ATHLETICS_SKILL_UNKONW_TYPE_)
			{
				pHeroicRole->OnPlayCommonEffect(effectID);
			}
			pHeroicRole->OnPlayNumberBufferByID(_MPHEAL_NUMBERICALFONT_FORMATID_,_MPHEAL_NUMBERICALFONT_FORMATID_,atoi(attachParams[3].c_str()));
		}
	}
}

 



//给Targer HP伤害
SkillAttachLogicTargetHPDamage::SkillAttachLogicTargetHPDamage()
{
    objectSubID_=_ATHLETICS_SKILL_TARGET_HP_DAMAGE_TYPE_;

}

SkillAttachLogicTargetHPDamage::~SkillAttachLogicTargetHPDamage()
{
   
}


void SkillAttachLogicTargetHPDamage::OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft)
{
	if(attachParams.size()>=4)
	{
		HeroicRole * pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
		if(pHeroicRole!=NULL&&(pHeroicRole->GetSubObjectID()!=atoi(attachParams.at(2).c_str())||pHeroicRole->getRoleType()!=atoi(attachParams.at(1).c_str())))
		{
			pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
		}
		if(pHeroicRole!=NULL)
		{
			int effectID=atoi(attachParams.at(0).c_str());
			if(effectID!=_ATHLETICS_SKILL_UNKONW_TYPE_)
			{
				pHeroicRole->OnPlayCommonEffect(effectID);
			}
			if(attachParams.size()>=5)
			{
				pHeroicRole->OnPlayNumberBufferByID(_BAOJI_NUMBERICALFONT_FOAMATID_,_BAOJI_NUMBERICALFONT_FOAMATID_,atoi(attachParams[3].c_str()));
			}
			else
			{
				pHeroicRole->OnPlayNumberBufferByID(_HPDAMAGE_NUMBERICALFONT_FORMATID_,_HPDAMAGE_NUMBERICALFONT_FORMATID_,atoi(attachParams[3].c_str()));
			}
		}
	}
}


SkillAttachLogicTargetHPHeal::SkillAttachLogicTargetHPHeal()
{
      objectSubID_=_ATHLETICS_SKILL_TARGET_HP_HEAL_TYPE_;
}

SkillAttachLogicTargetHPHeal::~SkillAttachLogicTargetHPHeal()
{

}

void SkillAttachLogicTargetHPHeal::OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft)
{
	if(attachParams.size()>=4)
	{
		HeroicRole * pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
		if(pHeroicRole!=NULL&&(pHeroicRole->GetSubObjectID()!=atoi(attachParams.at(2).c_str())||pHeroicRole->getRoleType()!=atoi(attachParams.at(1).c_str())))
		{
			pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
		}
		if(pHeroicRole!=NULL)
		{
			int effectID=atoi(attachParams.at(0).c_str());
			if(effectID!=_ATHLETICS_SKILL_UNKONW_TYPE_)
			{
				pHeroicRole->OnPlayCommonEffect(effectID);
			}
			pHeroicRole->OnPlayNumberBufferByID(_HPHEAL_NUMBERICALFONT_FORMATID_,_HPHEAL_NUMBERICALFONT_FORMATID_,atoi(attachParams[3].c_str()));
		}
	}
}



SkillAttachLogicTargetMPDamage::SkillAttachLogicTargetMPDamage()
{
       objectSubID_=_ATHLETICS_SKILL_TARGET_MP_DAMAGE_TYPE_;
}

SkillAttachLogicTargetMPDamage::~SkillAttachLogicTargetMPDamage()
{

}

void SkillAttachLogicTargetMPDamage::OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft)
{
	if(attachParams.size()>=4)
	{
		HeroicRole * pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
	    if(pHeroicRole!=NULL&&(pHeroicRole->GetSubObjectID()!=atoi(attachParams.at(2).c_str())||pHeroicRole->getRoleType()!=atoi(attachParams.at(1).c_str())))
		{
			pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
		}
		if(pHeroicRole!=NULL)
		{
			int effectID=atoi(attachParams.at(0).c_str());
			if(effectID!=_ATHLETICS_SKILL_UNKONW_TYPE_)
			{
				pHeroicRole->OnPlayCommonEffect(effectID);
			}
			pHeroicRole->OnPlayNumberBufferByID(_MPDAMAGE_NUMBERICALFONT_FORMATID_,_MPDAMAGE_NUMBERICALFONT_FORMATID_,atoi(attachParams[3].c_str()));
		}
	}
}



SkillAttachLogicTargetMPHeal::SkillAttachLogicTargetMPHeal()
{
   objectSubID_=_ATHLETICS_SKILL_TARGET_MP_HEAL_TYPE_;
}


SkillAttachLogicTargetMPHeal::~SkillAttachLogicTargetMPHeal()
{

}

void SkillAttachLogicTargetMPHeal::OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft)
{
	if(attachParams.size()>=4)
	{
		HeroicRole * pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
		if(pHeroicRole!=NULL&&(pHeroicRole->GetSubObjectID()!=atoi(attachParams.at(2).c_str())||pHeroicRole->getRoleType()!=atoi(attachParams.at(1).c_str())))
		{
			pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
		}
		if(pHeroicRole!=NULL)
		{
			int effectID=atoi(attachParams.at(0).c_str());
			if(effectID!=_ATHLETICS_SKILL_UNKONW_TYPE_)
			{
				pHeroicRole->OnPlayCommonEffect(effectID);
			}
			pHeroicRole->OnPlayNumberBufferByID(_MPHEAL_NUMBERICALFONT_FORMATID_,_MPHEAL_NUMBERICALFONT_FORMATID_,atoi(attachParams[3].c_str()));
		}
	}
}


SkillAttachLogicChangeShape::SkillAttachLogicChangeShape()
{
     objectSubID_=_ATHLETICS_SKILL_CHANAGE_SHAPE_TYPE_;
}

SkillAttachLogicChangeShape::~SkillAttachLogicChangeShape()
{

}

void SkillAttachLogicChangeShape::OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft)
{
    //to do
}



SkillAttachLogicAddState::SkillAttachLogicAddState()
{ 
    objectSubID_=_ATHLETICS_SKILL_ADD_STATE_TYPE_;
}

SkillAttachLogicAddState::~SkillAttachLogicAddState()
{

}
void  SkillAttachLogicAddState::OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft)
{
	if(attachParams.size()>=4)
	{
		HeroicRole * pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
		if(pHeroicRole!=NULL&&(pHeroicRole->GetSubObjectID()!=atoi(attachParams.at(2).c_str())||pHeroicRole->getRoleType()!=atoi(attachParams.at(1).c_str())))
		{
			pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
		}
		if(pHeroicRole!=NULL)
		{
			int effectID=atoi(attachParams.at(0).c_str());
			if(effectID!=_ATHLETICS_SKILL_UNKONW_TYPE_)
			{
				pHeroicRole->OnPlayCommonEffect(effectID);
			}
			//添加State
			pHeroicRole->addRoleState(atoi(attachParams.at(3).c_str()));
		}
	}
}


SkillAttachLogicRemoveState::SkillAttachLogicRemoveState()
{
     objectSubID_=_ATHLETICS_SKILL_REMOVE_STATE_TYPE_;
}

SkillAttachLogicRemoveState::~SkillAttachLogicRemoveState()
{

}


void SkillAttachLogicRemoveState::OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft)
{
	if(attachParams.size()>=4)
	{
		HeroicRole * pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
		if(pHeroicRole!=NULL&&(pHeroicRole->GetSubObjectID()!=atoi(attachParams.at(2).c_str())||pHeroicRole->getRoleType()!=atoi(attachParams.at(1).c_str())))
		{
			pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
		}
		if(pHeroicRole!=NULL)
		{
			int effectID=atoi(attachParams.at(0).c_str());
			if(effectID!=_ATHLETICS_SKILL_UNKONW_TYPE_)
			{
				pHeroicRole->OnPlayCommonEffect(effectID);
			}
			//删除State
			pHeroicRole->removeRoleState(atoi(attachParams.at(3).c_str()));
		}
	}
}



SkillAttachLogicAddBuffer::SkillAttachLogicAddBuffer()
{
      objectSubID_=_ATHLETICS_SKILL_ADD_EFFECT_TYPE_;
} 


SkillAttachLogicAddBuffer::~SkillAttachLogicAddBuffer()
{

}

void  SkillAttachLogicAddBuffer::OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft)
{
	if(attachParams.size()>=3)
	{
		HeroicRole * pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
		if(pHeroicRole!=NULL&&(pHeroicRole->GetSubObjectID()!=atoi(attachParams.at(2).c_str())||pHeroicRole->getRoleType()!=atoi(attachParams.at(1).c_str())))
		{
			pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
		}
		if(pHeroicRole!=NULL)
		{
			int effectID=atoi(attachParams.at(0).c_str());
			if(effectID!=_ATHLETICS_SKILL_UNKONW_TYPE_)
			{
				pHeroicRole->OnPlayCommonEffect(effectID);
			}
		}
	}
}


 
SkillAttachLogicRemoveBuffer::SkillAttachLogicRemoveBuffer()
{
     objectSubID_=_ATHLETICS_SKILL_REMOVE_EFFECT_TYPE_;
}

SkillAttachLogicRemoveBuffer::~SkillAttachLogicRemoveBuffer()
{

}

void SkillAttachLogicRemoveBuffer::OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft)
{
	if(attachParams.size()>=3)
	{
		HeroicRole * pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
		if(pHeroicRole!=NULL&&(pHeroicRole->GetSubObjectID()!=atoi(attachParams.at(2).c_str())||pHeroicRole->getRoleType()!=atoi(attachParams.at(1).c_str())))
		{
			pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
		}
		if(pHeroicRole!=NULL)
		{
			int effectID=atoi(attachParams.at(0).c_str());
			if(effectID!=_ATHLETICS_SKILL_UNKONW_TYPE_)
			{
				pHeroicRole->OnStopCommonEffect(effectID);
			}
		}
	}
}

SkillAttachLogicReduceMP::SkillAttachLogicReduceMP()
{
    objectSubID_=_ATHLETICS_SKILL_REDUCE_MP_TYPE_;
}

SkillAttachLogicReduceMP::~SkillAttachLogicReduceMP()
{

}


void  SkillAttachLogicReduceMP::OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft)
{
	if(attachParams.size()>=4)
	{
		HeroicRole * pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
		if(pHeroicRole!=NULL&&(pHeroicRole->GetSubObjectID()!=atoi(attachParams.at(2).c_str())||pHeroicRole->getRoleType()!=atoi(attachParams.at(1).c_str())))
		{
			pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
		}
		if(pHeroicRole!=NULL)
		{
			int effectID=atoi(attachParams.at(0).c_str());
			if(effectID!=_ATHLETICS_SKILL_UNKONW_TYPE_)
			{
				pHeroicRole->OnPlayCommonEffect(effectID);
			} 
			pHeroicRole->reduceRoleMPValue(atoi(attachParams[3].c_str()));
		}
	}
}
 

//复活血量
SkillAttachLogicReliveUpdateHP::SkillAttachLogicReliveUpdateHP()
{
   objectSubID_=_ATHLETICS_SKILL_RELIVE_HP_TYPE_;
}

SkillAttachLogicReliveUpdateHP::~SkillAttachLogicReliveUpdateHP()
{

}

void  SkillAttachLogicReliveUpdateHP::OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft)
{
	if(attachParams.size()>=4)
	{
		HeroicRole * pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
		if(pHeroicRole!=NULL&&(pHeroicRole->GetSubObjectID()!=atoi(attachParams.at(2).c_str())||pHeroicRole->getRoleType()!=atoi(attachParams.at(1).c_str())))
		{
			pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
		}
		if(pHeroicRole!=NULL)
		{
			int effectID=atoi(attachParams.at(0).c_str());
			if(effectID!=_ATHLETICS_SKILL_UNKONW_TYPE_)
			{
				pHeroicRole->OnPlayCommonEffect(effectID);
			} 
			pHeroicRole->updateRoleHPValue(atoi(attachParams[3].c_str()));
		}
	}
}

 
//复活蓝量
SkillAttachLogicReliveUpdateMP::SkillAttachLogicReliveUpdateMP()
{
    objectSubID_=_ATHLETICS_SKILL_RELIVE_MP_TYPE_;
}

SkillAttachLogicReliveUpdateMP::~SkillAttachLogicReliveUpdateMP()
{

}

void SkillAttachLogicReliveUpdateMP::OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft)
{
	if(attachParams.size()>=4)
	{
		HeroicRole * pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
		if(pHeroicRole!=NULL&&(pHeroicRole->GetSubObjectID()!=atoi(attachParams.at(2).c_str())||pHeroicRole->getRoleType()!=atoi(attachParams.at(1).c_str())))
		{
			pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
		}
		if(pHeroicRole!=NULL)
		{
			int effectID=atoi(attachParams.at(0).c_str());
			if(effectID!=_ATHLETICS_SKILL_UNKONW_TYPE_)
			{
				pHeroicRole->OnPlayCommonEffect(effectID);
			} 
			pHeroicRole->updateRoleMPValue(atoi(attachParams[3].c_str()));
		}
	}
}

SkillAttachLogicHitNote::SkillAttachLogicHitNote()
{
	 objectSubID_=_ATHLETICS_SKILL_HIT_NOTE_TYPE_;
}
SkillAttachLogicHitNote::~SkillAttachLogicHitNote()
{ 

}
void  SkillAttachLogicHitNote::OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft)
{  
	HeroicRole * pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
	if(pHeroicRole&&(pHeroicRole->GetSubObjectID()!=atoi(attachParams.at(1).c_str())||pHeroicRole->getRoleType()!=atoi(attachParams.at(0).c_str())))
	{
		pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
	}
	if(pHeroicRole)
	{
		int hitNoteType=atoi(attachParams.at(2).c_str());
		pHeroicRole->OnPlayNumberBufferByID(_ATHLETICS_SKILL_HIT_NOTE_TYPE_,_HITNOTE_NUMBERICALFONT_FORMATID_,hitNoteType);
	}
}
  