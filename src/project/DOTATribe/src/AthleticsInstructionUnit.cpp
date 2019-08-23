//Name：AtheleticsInstructionUnit
//Function：战斗指令单元
//Author:	Johny

#include <cocos2d.h>
#include  "../include/AthleticsInstructionUnit.h"
#include  "../include/AthleticsSceneManager.h"


AthleticsInstructionUnit::AthleticsInstructionUnit()
{ 

	curInstructionType=_INSTRUCTIONUNIT_UNKOWN_TYPE_;		 //当前指令的类型	
	cutInstructionID=0;										 //指令ID
	pAthleticsData_Skill_=NULL;								 //技能指令数据指针
	pAthleticsData_Buffer_=NULL;						     //删除buffer数据指针
	pAthleticsData_State_=NULL;								 //删除State数据指针
	pAthleticsData_Location_=NULL;						     //改变位置数据指针

	isAssailantLeft=true;
	isTargetLeft=true;

}


//@用战斗过程指令单元数据初始化
void  AthleticsInstructionUnit::InitWithConfigData(PAthleticsUnitData pAthleticsUnitData)
{
	if(pAthleticsUnitData!=NULL)
   {
        //#根据单元数据类型，初始化对应的成员变量
	   switch(pAthleticsUnitData->athleticsType)
	   {
	   case _ATHLETICSINSTRUCTION_SKILL_TYPE_:
		   {
			   curInstructionType=_INSTRUCTIONUNIT_SKILL_TYPE_;	
			   pAthleticsData_Skill_=(PAthleticsData_SKILL)pAthleticsUnitData->athleticsData;
			   break;
		   }
	   case _ATHLETICSINSTRUCTION_REMOVE_EFFECT_TYPE_:
		   {
			   curInstructionType=_INSTRUCTIONUNIT_REMOVE_BUFFER_TYPE_;	
			   pAthleticsData_Buffer_=(PAthleticsData_Buffer)pAthleticsUnitData->athleticsData;
			   break;
		   }
	   case _ATHLETICSINSTRUCTION_REMOVE_STATE_TYPE_:
		   {
			   curInstructionType=_INSTRUCTIONUNIT_REMOVE_STATE_TYPE_;	
			   pAthleticsData_State_=(PAthleticsData_State)pAthleticsUnitData->athleticsData;
		       break;
		   }
	   case  _ATHLETICSINSTRUCTION_LOCATION_TYPE_:
		   {
			   curInstructionType=_INSTRUCTIONUNIT_LOCATION_TYPE_;	
			   pAthleticsData_Location_=(PAthleticsData_Location)pAthleticsUnitData->athleticsData;
			    break;
		   }
	   default:
		   break;
	   }
 
	   //#计算攻击者和目标者的方向
	   if(AthleticsSceneManager::get_instance2()!=NULL)
	   {   
		   HeroicRole * pHeroicRole=NULL;
		   pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
		   assert(pHeroicRole!=NULL);
		   if(pAthleticsData_Skill_!=NULL)
		   {   
			   if(pHeroicRole->GetSubObjectID()!= pAthleticsData_Skill_->assailantID||pHeroicRole->getRoleType()!=pAthleticsData_Skill_->assailantIDType)
			   {
				   isAssailantLeft=false;
			   }
			   if(pHeroicRole->GetSubObjectID()!=pAthleticsData_Skill_->targetID||pHeroicRole->getRoleType()!=pAthleticsData_Skill_->targetIDType)
			   {
				   isTargetLeft=false;
			   }
			   return ;
		   }
		   if(pAthleticsData_Buffer_!=NULL)
		   {
			   if(pHeroicRole->GetSubObjectID()!=pAthleticsData_Buffer_->sourceID||pHeroicRole->getRoleType()!=pAthleticsData_Buffer_->sourceType)
			   {
				   isTargetLeft=false;
			   }
			   return ;
		   }
		   if(pAthleticsData_State_!=NULL)
		   {
			   if(pHeroicRole->GetSubObjectID()!=pAthleticsData_State_->sourceID||pHeroicRole->getRoleType()!=pAthleticsData_State_->sourceType)
			   {
				   isTargetLeft=false;
			   }
			   return ;
		   }
		   if(pAthleticsData_Location_!=NULL)
		   {
			   if(pHeroicRole->GetSubObjectID()!=pAthleticsData_Location_->sourceID||pHeroicRole->getRoleType()!=pAthleticsData_Location_->sourceType)
			   {
				   isAssailantLeft=false;
			   }
			   return ;
		   }
	   }
   }
}


//析构的时候不需要将战斗数据析构，由场景统一管理

void  AthleticsInstructionUnit::Destroy()
{
 	curInstructionType=_INSTRUCTIONUNIT_UNKOWN_TYPE_;		 //当前指令的类型	
	cutInstructionID=0;										 //指令ID

	pAthleticsData_Skill_=NULL;			//技能指令数据指针
	pAthleticsData_Buffer_=NULL;	    //删除buffer数据指针
	pAthleticsData_State_=NULL;			//删除State数据指针
	pAthleticsData_Location_=NULL;	    //改变位置数据指针

	isAssailantLeft=true;
	isTargetLeft=true;
}

void AthleticsInstructionUnit::Tick()
{
    //to do nothing here   


}

char    AthleticsInstructionUnit::GetAthleticsUnitType()
{
	return curInstructionType;
}


//@技能类型访问接口
short   AthleticsInstructionUnit::GetSkillItemID()							    //获得技能ID		
{
	if(curInstructionType==_INSTRUCTIONUNIT_LOCATION_TYPE_)
	{
		assert(pAthleticsData_Location_!=NULL);
		return	pAthleticsData_Location_->skillItemID;
	}
      assert(pAthleticsData_Skill_!=NULL);
	  return  pAthleticsData_Skill_->skillItemID;
} 
short   AthleticsInstructionUnit::GetHurtActionID()						    	//获得受击动作ID
{
	if(curInstructionType==_INSTRUCTIONUNIT_LOCATION_TYPE_)
	{ 
		assert(pAthleticsData_Location_!=NULL);
		return  _SKILLITEM_UNKONW_TYPE_;
	}
	  assert(pAthleticsData_Skill_!=NULL);
	  return  pAthleticsData_Skill_->hurtActionID;

}
int		AthleticsInstructionUnit::GetAssailantID()							    //获得攻击者的ID	
{
	if(curInstructionType==_INSTRUCTIONUNIT_LOCATION_TYPE_)
	{
		assert(pAthleticsData_Location_!=NULL);
		return  pAthleticsData_Location_->sourceID;
	}
 	  assert(pAthleticsData_Skill_!=NULL);
	  return  pAthleticsData_Skill_->assailantID;
}

char   AthleticsInstructionUnit::GetAssailantType()
{
	if(curInstructionType==_INSTRUCTIONUNIT_LOCATION_TYPE_)
	{
		assert(pAthleticsData_Location_!=NULL);
		return  pAthleticsData_Location_->sourceType;
	}
	assert(pAthleticsData_Skill_!=NULL);
	return  pAthleticsData_Skill_->assailantIDType;
} 
 
 
int     AthleticsInstructionUnit::GetTargetID()								   
{
	if(curInstructionType==_INSTRUCTIONUNIT_LOCATION_TYPE_)
	{ 
		assert(pAthleticsData_Location_!=NULL);
	    return  pAthleticsData_Location_->sourceID;
	}
	 assert(pAthleticsData_Skill_!=NULL);
	 return  pAthleticsData_Skill_->targetID;
}

char   AthleticsInstructionUnit::GetTargetType()
{
	if(curInstructionType==_INSTRUCTIONUNIT_LOCATION_TYPE_)
	{ 
		assert(pAthleticsData_Location_!=NULL);
		return  pAthleticsData_Location_->sourceType;
	}
	assert(pAthleticsData_Skill_!=NULL);
	return  pAthleticsData_Skill_->targetIDType;
}

 
char    AthleticsInstructionUnit::GetSkillHitType()							    //获得技能命中类型
{
	if(curInstructionType==_INSTRUCTIONUNIT_LOCATION_TYPE_)
	{ 
		assert(pAthleticsData_Location_!=NULL);
		return  _SKILLITEM_UNKONW_TYPE_;										//未命中
	}
	assert(pAthleticsData_Skill_!=NULL);
	return  pAthleticsData_Skill_->skillActionType;
}
short   AthleticsInstructionUnit::GetCounterAttackSkillID()					    //获得反击技能ID
{
	assert(pAthleticsData_Skill_!=NULL);
	return  pAthleticsData_Skill_->counterAttackSkillID;
}
char    AthleticsInstructionUnit::GetAttachEffectCount()			 	        //获得附加效果数目
{
	if(curInstructionType==_INSTRUCTIONUNIT_LOCATION_TYPE_)
	{ 
		assert(pAthleticsData_Location_!=NULL);
		return  0;
	}
	assert(pAthleticsData_Skill_!=NULL);
	return  pAthleticsData_Skill_->effectCount;
}
std::vector<PSkillAttach_Base> AthleticsInstructionUnit::GetSkillAttachEffectVector()  //获得技能附加效果向量
{
	if(curInstructionType==_INSTRUCTIONUNIT_LOCATION_TYPE_)
	{ 
		assert(pAthleticsData_Location_!=NULL);
		std::vector<PSkillAttach_Base>  empty;
		return  empty;
	}
	assert(pAthleticsData_Skill_!=NULL);
	return  pAthleticsData_Skill_->skillAttachEffectVector;
}


//////////////////////////////////////////////////////////////////////////

//删除Buffer类型接口
int		AthleticsInstructionUnit::GetRemoveBuffer_SourceID()					//获得删除Buffer的源ID
{
    assert(pAthleticsData_Buffer_!=NULL);
	return  pAthleticsData_Buffer_->sourceID;
}
 
short   AthleticsInstructionUnit::GetRemoverBuffer_EffectID()				    //删除指定特效ID
{
	assert(pAthleticsData_Buffer_!=NULL);
	return  pAthleticsData_Buffer_->effectID;
}

//////////////////////////////////////////////////////////////////////////


//删除State类型接口
int     AthleticsInstructionUnit::GetRemoveState_SourceID()					    //获得删除State的源ID
{
	assert(pAthleticsData_State_!=NULL); 
	return  pAthleticsData_State_->sourceID;
}
char    AthleticsInstructionUnit::GetRemoveState_RoleState()					//删除角色状态某个状态
{
	assert(pAthleticsData_State_!=NULL); 
	return  pAthleticsData_State_->roleState;
}

//////////////////////////////////////////////////////////////////////////

//改变Location类型接口
int     AthleticsInstructionUnit::GetLocation_SourceID()					     //获得位置改变的ID
{ 
	assert(pAthleticsData_Location_!=NULL); 
	return  pAthleticsData_Location_->sourceID;

}
char	AthleticsInstructionUnit::GetLocation_Location()						 //获得位置属性
{
	/*
	  param    0   返回原地   1  移动到目标位置
	*/
	assert(pAthleticsData_Location_!=NULL); 
	return  pAthleticsData_Location_->location;
}


bool	AthleticsInstructionUnit::VerifyInstructionUnitData() 					 //指令单元数据校验
{
	if(curInstructionType==_INSTRUCTIONUNIT_LOCATION_TYPE_)
	{   
		//  param    0   返回原地   1  移动到目标位置
		HeroicRole * pExcutorRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
		if(!isAssailantLeft)
		{
			pExcutorRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
		}
		if(GetLocation_Location()==_INSTRUCTIONUNIT_TOINIT_LOCATION_TYPE_&&pExcutorRole->isRoleAtInitXPos())
		{ 
			return false;
		}
		else if(GetLocation_Location()==_INSTRUCTIONUNIT_TOTARGET_LOCATION_TYPE_&&pExcutorRole->isRoleAtTargetXPos())
		{ 
			return false;
		}
	}
	return true;
}


 