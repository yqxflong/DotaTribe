//Name：CommonSkillActionProcedure
//Function：技能控制流程
//Author:	Johny

#include     "../include/CommonSkillItemProcedure.h"
#include     "../include/AthleticsSceneManager.h"
#include     "../include/SkillAttachLogicManager.h"
#include     "../include/HeroicRole.h"
#include     "../include/InputCommand.h"
#include     "../include/AthleticsInstructionSystem.h"
#include     "../include/SkillTableDataManager.h"
#include     "../include/NFAnimationController.h"
#include	 "../include/AthleticProcedureDataType.h"




CommonSkillItemProcedure::CommonSkillItemProcedure()
{
	objectType_=COMMONSKILLITEMPROCEDURE_OBJECT_TYPE;
    pCommonSkillActionProcedure_=NULL;
	skillAttachLogicVector_.clear();       //技能附加逻辑效果
  
	pAttachLogicAction=NULL;
	pExceptionRole=NULL;
	pAthleticsInstructionUnit_=NULL;
	curSkillProcedureState_=_SKILLITEMPROCEDURE_BEGINPROCEDURE_TYPE_;
	curSkillAttachLogicState_=_SKILLATTACHLOGIC_ENDPROCEDURE_TYPE_;
	isExecutorLeft=true;										   //默认初始值
	isVictimLeft=false;											   //作用者的初始值
	IsExistHitNote=false;	
	  
	isCritSkill=false;
	isMutipleBatterSkill=false;
	mutipleBatterCount=0;
 
 	hurtEffectTriggerTime=0;
}

CommonSkillItemProcedure::~CommonSkillItemProcedure()
{

}
 

void  CommonSkillItemProcedure::InitWithInstructionData(AthleticsInstructionUnit * instructionUnit)
{ 
    if(instructionUnit)
	{
		//初始化技能ID
		pAthleticsInstructionUnit_=instructionUnit;
		SetSubObjectID(pAthleticsInstructionUnit_->GetSkillItemID()); 
		 
		//初始化 战斗受击类型
        InitSkillHitType();
		//初始化 战斗逻辑序列 
		InitSkillAttackDirection();
		 
		//初始化附加逻辑   (默认附加流程是End状态)
		IniSkillAttachLogicData();
		//启动技能
		OnBeginSkillItem();
	}
}


//初始化技能命中类型
void   CommonSkillItemProcedure::InitSkillHitType()
{ 
	switch(pAthleticsInstructionUnit_->GetSkillHitType())
	{ 
		case _ATHLETICS_SKILL_HIT_ACTION_TYPE_:
		{
			//命中  
			break;
		}
		case _ATHLETICS_SKILL_CRIT_ACTION_TYPE_:
		{
			//暴击
			isCritSkill=true;
			break;
		}
		case _ATHLETICS_SKILL_DODGE_ACTION_TYPE_:
		{
			IsExistHitNote=true;
			//闪避
			break;
		}
		case _ATHLETICS_SKILL_BLOCK_ACTION_TYPE_:
		{
			//格挡
			IsExistHitNote=true;
			break;
		}
		case  _ATHLETICS_SKILL_BATTER2_ACTION_TYPE_:
		case  _ATHLETICS_SKILL_BATTER3_ACTION_TYPE_:
		case  _ATHLETICS_SKILL_BATTER4_ACTION_TYPE_:
		case  _ATHLETICS_SKILL_BATTER5_ACTION_TYPE_:
		{
			isMutipleBatterSkill=true;
			mutipleBatterCount=2;
			break;
		} 
		default: 
		break;
	}
}



void  CommonSkillItemProcedure::Destroy()
{
	IsExistHitNote=false;
	pAttachLogicAction=NULL;
	SetIsValid(false);
    //资源销毁和释放
	if(pCommonSkillActionProcedure_!=NULL)
	{
		pCommonSkillActionProcedure_->Destroy();
		delete pCommonSkillActionProcedure_;
		pCommonSkillActionProcedure_=NULL;
	}
	if(pAthleticsInstructionUnit_!=NULL)
	{ 
		pAthleticsInstructionUnit_->Destroy();
		delete pAthleticsInstructionUnit_;
		pAthleticsInstructionUnit_=NULL;
	}

	skillAttachLogicVector_.clear();
	curSkillProcedureState_=_SKILLITEMPROCEDURE_UNKONW_TYPE_;
	isExecutorLeft=true;						    //默认初始值
	isVictimLeft=false;							    //作用者的初始值
	CCLOG("CommonSkillItemProcedure : Destroy!");
}

void CommonSkillItemProcedure::Tick()
{ 
	if(!IsValid())
		return ;

	BaseObject::Tick();
	 
	if(curSkillProcedureState_==_SKILLITEMPROCEDURE_ENDPROCEDURE_TYPE_&&curSkillAttachLogicState_==_SKILLATTACHLOGIC_ENDPROCEDURE_TYPE_)
	{
		//结束 资源回收和清理
		OnEndSkillItem();
		return ;
	}
    /*
     技能流程状态机
    */
	SkillProcedureStateMachine();

	/*
	 附加逻辑状态机
	*/
	AttachLogicStateMachine();
	 
}
 
//@技能流程的状态机
void  CommonSkillItemProcedure::SkillProcedureStateMachine()
{ 
	if(curSkillProcedureState_==_SKILLITEMPROCEDURE_RUNNINGPROCEDURE_TYPE_)
	{
		//技能流程驱动者动画流程
		if(pCommonSkillActionProcedure_)
		{
			pCommonSkillActionProcedure_->Tick();
		}
		return ;
	}
	else if(curSkillProcedureState_==_SKILLITEMPROCEDURE_BEGINPROCEDURE_TYPE_)
	{
		//初始化操作
		OnBeginSkillItem();
	}
}


//@附加逻辑状态机
void   CommonSkillItemProcedure::AttachLogicStateMachine()
{
	if(curSkillAttachLogicState_==_SKILLATTACHLOGIC_ENDPROCEDURE_TYPE_)
	{
		return ;
	}
	else if(curSkillAttachLogicState_==_SKILLATTACHLOGIC_RUNNINGPROCEDURE_TYPE_)
	{  
		HeroicRole * pVictimsRole=AthleticsSceneManager::get_instance2()->GetExecuteRole(isVictimLeft);
		if(pVictimsRole&&pVictimsRole->GetAllNumberEffectTriggered())
		{
			curSkillAttachLogicState_=_SKILLATTACHLOGIC_ENDPROCEDURE_TYPE_;
			Tick();
		}
	}
}

 
 

//事件通知接口
void CommonSkillItemProcedure::OnCommandHanlder(int EventTypeID)
{
	if(!IsValid())
		return ;

	if(EventTypeID==_TYPED_INPUT_COMMAND_SKILLACTION_END_)
	{
		//技能动画完成回调事件
		CCLOG("Common Skill Actions Procedure Complete!");
        curSkillProcedureState_=_SKILLITEMPROCEDURE_ENDPROCEDURE_TYPE_;
		return ;
	}
	/*
	事件传递
	*/
	if(pCommonSkillActionProcedure_!=NULL)
	{
		pCommonSkillActionProcedure_->OnCommandHanlder(EventTypeID);
	} 
}



void  CommonSkillItemProcedure::OnCommandHanlder(int EventTypeID,std::string attachParam)
{
	if(!IsValid())
		return ;
	if(EventTypeID==_Skeleton_Animation_Change_Event_)
	{    
		int actionID=atoi(attachParam.c_str());
		if(actionID==HeroicRole::SiWang)
		{  
			if(pExceptionRole!=NULL)
			{
				pExceptionRole->unRegisterSkeletonEventDelegate(this);
			}
			OnEndSkillNotification();
		} 
	}
}
  

//开始技能流程
void  CommonSkillItemProcedure::OnBeginSkillItem()
{
    if(pCommonSkillActionProcedure_!=NULL)
	{
		delete  pCommonSkillActionProcedure_;
		pCommonSkillActionProcedure_=NULL;
	}
	//暂时直接分配内存  此后会进行内存回收机制设计

	pCommonSkillActionProcedure_=new CommonSkillActionProcedure();
	if(pCommonSkillActionProcedure_!=NULL)
	{
		curSkillProcedureState_=_SKILLITEMPROCEDURE_RUNNINGPROCEDURE_TYPE_;
		pCommonSkillActionProcedure_->InitWithSkillItemProcedure(this);
		pCommonSkillActionProcedure_->Tick();		
	}
	else
	{
		curSkillProcedureState_=_SKILLITEMPROCEDURE_ENDPROCEDURE_TYPE_;
	}
} 

//结束技能流程
void CommonSkillItemProcedure::OnEndSkillItem()
{ 
	if(CheckRoleExceptionEvent(true))
	return ;
	if(CheckRoleExceptionEvent(false))
	return ;
	OnEndSkillNotification();
}

void   CommonSkillItemProcedure::OnEndSkillNotification()
{
	curSkillProcedureState_=_SKILLITEMPROCEDURE_ENDPROCEDURE_TYPE_;
	if(pExceptionRole!=NULL)
	{
		pExceptionRole->unRegisterSkeletonEventDelegate(this);
		pExceptionRole=NULL;
	}
	if(!AthleticsSceneManager::get_instance2()->IsGameOver())
	{
		AthleticsInstructionSystem::get_instance2()->OnCommandHandler(_TYPED_INPUT_COMMAND_RESUME_ATHLETICSINSTRUCTION_);
	}
	Destroy(); 
}

void  CommonSkillItemProcedure::SetSpeedScale(float speedScale)
{
	if(pAttachLogicAction)
	{
		pAttachLogicAction->setSpeedScale(speedScale);
	}
	if(pCommonSkillActionProcedure_)
	{ 
		pCommonSkillActionProcedure_->SetSpeedScale(speedScale);
	}
}
 
void  CommonSkillItemProcedure::CallFunctionHandler(int eventType,void * attachParam)
{ 
	if(eventType==_SKILLPROCEDURE_ATTACH_LOGIC_EVENT_TYPE_)
	{  
		LuanchAttachLogicHandler();
		pAttachLogicAction=NULL;
	}
}

void   CommonSkillItemProcedure::LuanchAttachLogicHandler()
{ 
	//to do
	if(curSkillAttachLogicState_==_SKILLATTACHLOGIC_ENDPROCEDURE_TYPE_)
	{
		return ;
	}
	if(IsExistHitNote)
	SkillAttachLogicManager::get_instance2()->OnCommandHandler(_ATHLETICS_SKILL_HIT_NOTE_TYPE_,
	AppendAttachHitNoteByType(pAthleticsInstructionUnit_->GetSkillHitType()),isExecutorLeft,isVictimLeft); 
	 
	size_t skillAttachLogicCount=skillAttachLogicVector_.size();
	for(size_t startIndex=0;startIndex<skillAttachLogicCount;startIndex++)
	{ 
		SkillAttachLogicProcedureHandler(startIndex);	 
 	}
    curSkillAttachLogicState_=_SKILLATTACHLOGIC_RUNNINGPROCEDURE_TYPE_;
 
}
 
std::vector<std::string>   CommonSkillItemProcedure::AppendAttachHitNoteByType(int hitType)
{   
	HeroicRole * pHeroicRole=AthleticsSceneManager::get_instance2()->GetExecuteRole(isVictimLeft);
	std::vector<std::string>  attachParams;
	if(pHeroicRole)
	{ 
		char attachParam[16]={0};
		sprintf(attachParam,"%d",pHeroicRole->getRoleType());
		attachParams.push_back(attachParam);
		sprintf(attachParam,"%d",pHeroicRole->GetSubObjectID());
		attachParams.push_back(attachParam);
		sprintf(attachParam,"%d",hitType);
		attachParams.push_back(attachParam);
	} 
	return  attachParams ;
}



/*
检测角色的异常事件
*/
bool   CommonSkillItemProcedure::CheckRoleExceptionEvent(bool isLeftRole)
{
	HeroicRole * pHeroicRole=NULL;
	if(isLeftRole)
		pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
	else
		pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
	if(pHeroicRole&&!pHeroicRole->IsRoleLive())
	{
		if(!(pHeroicRole->hadPlayedDeadAnimation()&&pHeroicRole->isAnimationComplete(HeroicRole::SiWang)))
		{
			ThrowExceptionEvent(pHeroicRole);
			CCLOG("CommonSkillItemProcedure  Trigger Role Exception Event");
			return  true;
		} 
	}
	return false; 
}

/*
角色异常事件处理
*/
void   CommonSkillItemProcedure::ThrowExceptionEvent(HeroicRole * pHeroicRole)
{
	pHeroicRole->onPlayDeadAnimation();
	pHeroicRole->registerSkeletonEventDelegate(this);
	pExceptionRole=pHeroicRole;
	curSkillProcedureState_=_SKILLITEMPROCEDURE_EXCEPTION_DEATH_PROCEDURE_TYPE_;
}

  
bool    CommonSkillItemProcedure::GetIsExecutorLeft()
{ 
	 return  isExecutorLeft;
}

bool    CommonSkillItemProcedure::GetIsVictimLeft()
{
	 return  isVictimLeft;
}

int     CommonSkillItemProcedure::GetSkillProcedureID()
{
     return GetSubObjectID();
}


/*
 * 启动附加逻辑触发定时器
 */
void   CommonSkillItemProcedure::StartAttachLogicTimer()
{
	hurtEffectTriggerTime=GetHurtEffectTriggerTime();   //获得基础特效触发时间点
	pAttachLogicAction=NFC_getTransimissionDelayComAction(hurtEffectTriggerTime/1000.0f,AthleticsSceneManager::get_instance2()->AthleticsSpeed,this,_SKILLPROCEDURE_ATTACH_LOGIC_EVENT_TYPE_);
    HeroicRole * pHeroicRole=NULL;
	pHeroicRole=AthleticsSceneManager::get_instance2()->GetExecuteRole(isExecutorLeft);
	if(pHeroicRole)
	pHeroicRole->runExtAction(pAttachLogicAction);
}


//@初始化技能的释放者和作用目标的方向 
void    CommonSkillItemProcedure::InitSkillAttackDirection()
{
   if(pAthleticsInstructionUnit_!=NULL)
   {
	  isExecutorLeft=pAthleticsInstructionUnit_->GetIsAssailantLeft();
	  isVictimLeft=pAthleticsInstructionUnit_->GetIsTargetLeft();
   }
}

/*
初始化技能附加效果逻辑
*/
void   CommonSkillItemProcedure::IniSkillAttachLogicData()
{
	skillAttachLogicVector_=GetAthleticsInstrucionUnit()->GetSkillAttachEffectVector();
	if(!skillAttachLogicVector_.empty()||IsExistHitNote)
	{
		 //初始化触发触发逻辑
		 curSkillAttachLogicState_=_SKILLATTACHLOGIC_BEGINPROCEDURE_TYPE_;
		 //启动技能逻辑触发定时器
		 StartAttachLogicTimer();
	}
}

std::vector<std::string>  CommonSkillItemProcedure::GetSkillAttachParamWithLogicType(PSkillAttach_Base skillAttach_tag)
{  
	std::vector<std::string> attachParams;
	char attachParam[16]={0};
	switch(skillAttach_tag->effectType)
	{  
		case _ATHLETICS_SKILL_SOURCE_HP_DAMAGE_TYPE_:
		case _ATHLETICS_SKILL_SOURCE_HP_HEAL_TYPE_:
		case _ATHLETICS_SKILL_SOURCE_MP_DAMAGE_TYPE_:
		case _ATHLETICS_SKILL_SOURCE_MP_HEAL_TYPE_:
		case _ATHLETICS_SKILL_TARGET_HP_DAMAGE_TYPE_:
		case _ATHLETICS_SKILL_TARGET_HP_HEAL_TYPE_:
		case _ATHLETICS_SKILL_TARGET_MP_DAMAGE_TYPE_:
		case _ATHLETICS_SKILL_TARGET_MP_HEAL_TYPE_:
		case _ATHLETICS_SKILL_REDUCE_MP_TYPE_:
		case _ATHLETICS_SKILL_RELIVE_HP_TYPE_:
		case _ATHLETICS_SKILL_RELIVE_MP_TYPE_:
		{
			PSkillAttach_Numberical  pSkillAttachNumberical=(PSkillAttach_Numberical)skillAttach_tag;
			if(pSkillAttachNumberical!=NULL)
			{
				sprintf(attachParam,"%d",pSkillAttachNumberical->effectID);
				attachParams.push_back(attachParam);
				sprintf(attachParam,"%d",pSkillAttachNumberical->targetType);
				attachParams.push_back(attachParam);
				sprintf(attachParam,"%d",pSkillAttachNumberical->targetID);
				attachParams.push_back(attachParam);
				sprintf(attachParam,"%d",pSkillAttachNumberical->numbericalValue);
				attachParams.push_back(attachParam);
				if(isCritSkill)
				{
				    sprintf(attachParam,"%d",isCritSkill);
					attachParams.push_back(attachParam);
				}
			}
			break; 
		}
		case _ATHLETICS_SKILL_CHANAGE_SHAPE_TYPE_:
		{
			PSkillAttach_ChangeShape pSkillAttachChangeShape=(PSkillAttach_ChangeShape)skillAttach_tag;
			if(pSkillAttachChangeShape!=NULL)
			{
				sprintf(attachParam,"%d",pSkillAttachChangeShape->effectID);
				attachParams.push_back(attachParam);
				sprintf(attachParam,"%d",pSkillAttachChangeShape->targetType);
				attachParams.push_back(attachParam);
				sprintf(attachParam,"%d",pSkillAttachChangeShape->targetID);
				attachParams.push_back(attachParam);
			    sprintf(attachParam,"%d",pSkillAttachChangeShape->shapeId);
				attachParams.push_back(attachParam);
			}
		    break;		
		} 
		case _ATHLETICS_SKILL_ADD_STATE_TYPE_:
		case _ATHLETICS_SKILL_REMOVE_STATE_TYPE_:
		{
             PSkillAttach_State  pSkillAttachState=(PSkillAttach_State)skillAttach_tag;
			 if(pSkillAttachState!=NULL)
			 {
				 sprintf(attachParam,"%d",pSkillAttachState->effectID);
				 attachParams.push_back(attachParam);
				 sprintf(attachParam,"%d",pSkillAttachState->targetType);
				 attachParams.push_back(attachParam);
				 sprintf(attachParam,"%d",pSkillAttachState->targetID);
				 attachParams.push_back(attachParam);
				 sprintf(attachParam,"%d",pSkillAttachState->state);
				 attachParams.push_back(attachParam);
			 }
			 break;	
		}
		case _ATHLETICS_SKILL_ADD_EFFECT_TYPE_:
		case _ATHLETICS_SKILL_REMOVE_EFFECT_TYPE_:
		{
			PSkillAttach_Base pSkillAttachEffect=skillAttach_tag;
			if(pSkillAttachEffect!=NULL)
			{	
				sprintf(attachParam,"%d",pSkillAttachEffect->effectID);
				attachParams.push_back(attachParam);
				sprintf(attachParam,"%d",pSkillAttachEffect->targetType);
				attachParams.push_back(attachParam);
				sprintf(attachParam,"%d",pSkillAttachEffect->targetID);
				attachParams.push_back(attachParam);
			}
			break;
		}
		case  _ATHLETICS_SKILL_CHANGE_POSITION_TYPE_:
		{
			PSkillAttach_Change_Position pSkillAttachChangePostion=(PSkillAttach_Change_Position)skillAttach_tag;
			if(pSkillAttachChangePostion!=NULL)
			{	
				sprintf(attachParam,"%d",pSkillAttachChangePostion->effectID);
				attachParams.push_back(attachParam);
				sprintf(attachParam,"%d",pSkillAttachChangePostion->targetType);
				attachParams.push_back(attachParam);
				sprintf(attachParam,"%d",pSkillAttachChangePostion->targetID);
				attachParams.push_back(attachParam);
				sprintf(attachParam,"%d",pSkillAttachChangePostion->position);
				attachParams.push_back(attachParam);
			}
			break;
		}
		default: 
			break;
	}
    return   attachParams;
}
 

  
/*
   处理技能附加效果逻辑  
   param   效果逻辑索引 ID
*/
void    CommonSkillItemProcedure::SkillAttachLogicProcedureHandler(int attachLogicIndex)
{
    if(!skillAttachLogicVector_.empty())
	{
	      int  attachlogicCount=skillAttachLogicVector_.size();
		  if(attachLogicIndex<=(attachlogicCount-1))
		  {
			  PSkillAttach_Base  pSkillAttachLogic=skillAttachLogicVector_.at(attachLogicIndex);
			  if(pSkillAttachLogic!=NULL)
			  { 
				  SkillAttachLogicManager::get_instance2()->OnCommandHandler(pSkillAttachLogic->effectType,GetSkillAttachParamWithLogicType(pSkillAttachLogic),GetIsExecutorLeft(),GetIsVictimLeft()); 
			  }
			  if(attachLogicIndex==(attachlogicCount-1))
			  {
				   curSkillAttachLogicState_=_SKILLATTACHLOGIC_ENDPROCEDURE_TYPE_;
			  }

		  }
		  else
		  {
			  //技能附加技能分发完毕
			  curSkillAttachLogicState_=_SKILLATTACHLOGIC_ENDPROCEDURE_TYPE_;
		  }
	}
}
   

float   CommonSkillItemProcedure::GetHurtEffectTriggerTime()
{
	 int  skillItemID=pAthleticsInstructionUnit_->GetSkillItemID();
	 SkillTableData * pSkillTableData=SkillTableDataManager::get_instance2()->GetSkillTableDataByID(skillItemID);
	 if(pSkillTableData!=NULL)
		 return  pSkillTableData->skillItemEffetCallTime;
	 return  0.0f;
}
 

//@获得绑定的指令单元数据
AthleticsInstructionUnit * CommonSkillItemProcedure::GetAthleticsInstrucionUnit()
{
	if(pAthleticsInstructionUnit_!=NULL)
	{
		return  pAthleticsInstructionUnit_;
	}
	return NULL;
}
