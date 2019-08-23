//Name：CommonSkillActionProcedure
//Function：技能动画控制流程
//Author:	Johny

#include    "../include/CommonSkillActionProcedure.h"
#include    "../include/SkillActionDataManager.h"
#include    "../include/SkillTableDataManager.h"
#include    "../include/AthleticsSceneManager.h"
#include	"../include/ListenProxyObject.h"
#include    "../include/InputCommand.h"
#include    "../include/TimeSystem.h"
#include    "../include/BaseObjectManager.h"
#include    "../include/ProfSystem.h"
#include    "../include/NFAnimationController.h"
 
 
CommonSkillActionProcedure::CommonSkillActionProcedure()
{
	objectType_=COMMONSKILLACTIONPROCEDURE_OBJECT_TYPE;     

	assailantRole=NULL;											//战斗角色
	vicitimsRole=NULL;											//战斗角色
	pCurrentSkillProcedure=NULL;							    //当前所在的技能流程
	 
	curAssailantExecuteIndex=0;									//当前攻击者的执行序列索引
	totalAssailantActionsCount=0;								//当前攻击者的动作序列数

	hadLoadAssailantActionState=-1;								//Pre执行的攻击者的动作序列
	
	curAssailantActionState=_ASSAILANT_UNKONWACTION_TYPE_;		//攻击者的动作序列状态
	curVicitimsActionState=_VICITIMS_ENDACTION_TYPE_;			//目标者的动作序列状态

	curSkillActionProcedure=_SKILLACTIONPROCEDURE_BEGINPROCEDURE_TYPE_; //技能动画流程的状态
 
	memset(preAssailantActionSequence,-1,sizeof(preAssailantActionSequence));	//攻击者的动作序列数组
  
	rivalHurActionID=-1;										//目标者的受击动作ID 
    skillHurtActionCallTime=0;								    //技能伤害动作触发时间点
	 
	isExecutorLeft=true;
	isVictimLeft=false; 									  
   
	//////////////////////////////////////////////////////////////////////////
	m_pAssailantListenObj=NULL;
	m_pVictimListenObj=NULL; 

	m_pDelayTriggerVictimAction=NULL;
	m_pToTargetComAction=NULL;
	m_pToHomeComAction=NULL;

}

CommonSkillActionProcedure::~CommonSkillActionProcedure()
{  
    Destroy();
}
 
void CommonSkillActionProcedure::InitWithSkillItemProcedure(CommonSkillItemProcedure * pCommonSkillProcedure)
{   

	pCurrentSkillProcedure=pCommonSkillProcedure;
	//初始技能动画组
	InitSkillActions();				
	  
	//预处理动作序列
	ToPrepareActionsSquence();

	//初始化战斗角色
	if(AthleticsSceneManager::get_instance2()!=NULL)
	{
		assailantRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
		vicitimsRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
		if(!isExecutorLeft)
		{
			assailantRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();	
		}
		if(!isVictimLeft)
		{
			vicitimsRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();	
		}
		if(assailantRole!=vicitimsRole)
		{ 
			m_pVictimListenObj=ListenProxyObject::CreateListenProxyObject(_SKILLS_VICTIM_ROLE_TYPE_,this);
			vicitimsRole->registerSkeletonEventDelegate(m_pVictimListenObj);
		}  
		m_pAssailantListenObj=ListenProxyObject::CreateListenProxyObject(_SKILLS_ASSAILANT_ROLE_TYPE_,this);
		assailantRole->registerSkeletonEventDelegate(m_pAssailantListenObj);
		 
	} 
	//开始执行
	OnBeginSkillAction();

}

 
void  CommonSkillActionProcedure::Destroy()
{ 
	if(m_pAssailantListenObj)
	{
		assailantRole->unRegisterSkeletonEventDelegate(m_pAssailantListenObj);
		delete m_pAssailantListenObj;
		m_pAssailantListenObj=NULL;
	}
	if(m_pVictimListenObj)
	{
		vicitimsRole->unRegisterSkeletonEventDelegate(m_pVictimListenObj);
		delete m_pVictimListenObj;
		m_pVictimListenObj=NULL;
	} 
	SetIsValid(false);
	assailantRole=NULL;
	vicitimsRole=NULL; 
	actionDataMap.clear();
}

void  CommonSkillActionProcedure::Tick()
{
	if(!IsValid())
		return ;

	BaseObject::Tick();   

	if(curSkillActionProcedure==_SKILLACTIONPROCEDURE_ENDPROCEDURE_TYPE_)
	{
		//结束技能动画组
		OnEndSkillAction();
		return ;
	}
	else if(curSkillActionProcedure==_SKILLACTIONPROCEDURE_BEGINPROCEDURE_TYPE_)
	{ 
		//开启技能动画组
		CCLOG("_SKILLACTIONPROCEDURE_BEGINPROCEDURE_TYPE_ Handler Handler Handler! SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS");
		OnBeginSkillAction();
		return ;
	}
	else if(curSkillActionProcedure==_SKILLACTIONPROCEDURE_RUNNINGPROCEDURE_TYPE_)
	{
		if(curAssailantActionState==_ASSAILANT_ENDACTION_TYPE_&&curVicitimsActionState==_VICITIMS_ENDACTION_TYPE_)
		{
			OnEndSkillAction();
			return ;
		}   
	} 
}
 

//事件通知接口
void  CommonSkillActionProcedure::OnCommandHanlder(int EventTypeID)
{  
}

void  CommonSkillActionProcedure::OnCommandHanlder(int EventTypeID,std::string attachParam1,std::string attachParam2,std::string attachParam3)
{
	if(!IsValid())
		return ;

	if(EventTypeID==_Skeleton_Animation_Change_Event_)
	{
		int poxyType=atoi(attachParam1.c_str());
		if(poxyType==_SKILLS_ASSAILANT_ROLE_TYPE_)
		{ 
			AssailantActionCompleteHandler(atoi(attachParam2.c_str()),atoi(attachParam3.c_str()));
		}
		else if(poxyType==_SKILLS_VICTIM_ROLE_TYPE_)
		{
			VictimActionCompleteHandler(atoi(attachParam2.c_str()),atoi(attachParam3.c_str()));
		} 
	}  
}
 

void	CommonSkillActionProcedure::InitSkillActions()
{ 
	if(pCurrentSkillProcedure!=NULL)
	{
		SkillTableData  *pSkillTableItem=SkillTableDataManager::get_instance2()->GetSkillTableDataByID(pCurrentSkillProcedure->GetSkillProcedureID());
		if(pSkillTableItem!=NULL)
		{
			skillHurtActionCallTime=pSkillTableItem->skillItemHurtCallTime;
			SetSubObjectID(pSkillTableItem->skillItemActionsID);
		}
	}
}


 
int		 CommonSkillActionProcedure::GetSkillActionsID()
{
	CCLOG("SkillActionID: %d",GetSubObjectID());
    return GetSubObjectID();
}

 
//预处理动画组序列
void CommonSkillActionProcedure::ToPrepareActionsSquence()
{   
	//产生技能动作序列
    if(pCurrentSkillProcedure!=NULL)
	{
		isExecutorLeft=pCurrentSkillProcedure->GetIsExecutorLeft();
		isVictimLeft=pCurrentSkillProcedure->GetIsVictimLeft();
		  
		//动态决策目标者受击动作
        if(pCurrentSkillProcedure->GetAthleticsInstrucionUnit()->GetHurtActionID()!=_COMMONACTION_DEFAULT_PARAM_)
		{
			bool  isVictimInInvinvible=false;
			if(isVictimLeft)
			{
				isVictimInInvinvible=AthleticsSceneManager::get_instance2()->GetLeftFightRole()->isRoleInState(HeroicRole::_ROLE_INVINCIBIE_STATE_);
			}
			else
			{
				isVictimInInvinvible=AthleticsSceneManager::get_instance2()->GetRightFightRole()->isRoleInState(HeroicRole::_ROLE_INVINCIBIE_STATE_);
			}  
			if(!isVictimInInvinvible)
			{ 
				curVicitimsActionState=_VICITIMS_UNKOWNACTION_TYPE_;

				rivalHurActionID=pCurrentSkillProcedure->GetAthleticsInstrucionUnit()->GetHurtActionID();
				int  skillActionType=pCurrentSkillProcedure->GetAthleticsInstrucionUnit()->GetSkillHitType();
				switch(skillActionType)
				{
					case _ATHLETICS_SKILL_DODGE_ACTION_TYPE_:   //闪避类型
						{
							rivalHurActionID=HeroicRole::ShanBi;
							break;
						}
					case _ATHLETICS_SKILL_BLOCK_ACTION_TYPE_:   //格挡类型
						{
							rivalHurActionID=HeroicRole::GeDang;
							break;
						}
					default: 
						//case  _ATHLETICS_SKILL_HIT_ACTION_TYPE_:    //普通命中类型
						//case  _ATHLETICS_SKILL_CRIT_ACTION_TYPE_:   //暴击类型
						break;
				}
			} 
		}
	  
		//根据技能参数  动态裁剪 攻击者的动作序列
		if(pCurrentSkillProcedure->GetAthleticsInstrucionUnit()->GetAthleticsUnitType()==AthleticsInstructionUnit::_INSTRUCTIONUNIT_LOCATION_TYPE_)
		{
             InitAssailantSquenceWithSkillParam(pCurrentSkillProcedure->GetAthleticsInstrucionUnit()->GetLocation_Location());
			 return ;
		}
		else
		{
			if(pCurrentSkillProcedure->GetAthleticsInstrucionUnit()->GetCounterAttackSkillID()>_COMMONACTION_DEFAULT_PARAM_)   //有反击技能无返回
			{
			 	InitAssailantSquenceWithSkillParam(_COOMONACTION_NORETURN_PARAM_);
			} 
			else
			{
				InitAssailantSquenceWithSkillParam(_COMMONACTION_DEFAULT_PARAM_);
			}
		}
 	}
}
  

//启动技能动画流程
void  CommonSkillActionProcedure::OnBeginSkillAction()
{
	curSkillActionProcedure=_SKILLACTIONPROCEDURE_RUNNINGPROCEDURE_TYPE_;
	DoNextAssailantActionProcess();
	if(curAssailantActionState==_ASSAILANT_ENDACTION_TYPE_&&curVicitimsActionState==_VICITIMS_ENDACTION_TYPE_)
	{
		curVicitimsActionState=_SKILLACTIONPROCEDURE_ENDPROCEDURE_TYPE_;
		return ;
	} 
	StartAttackTimer();
}
 


//结束技能动画流程
void  CommonSkillActionProcedure::OnEndSkillAction()
{ 
	 if(m_pAssailantListenObj)
	 {
		 assailantRole->unRegisterSkeletonEventDelegate(m_pAssailantListenObj);
		 delete m_pAssailantListenObj;
		 m_pAssailantListenObj=NULL;
	 }
	 if(m_pVictimListenObj)
	 {
		 vicitimsRole->unRegisterSkeletonEventDelegate(m_pVictimListenObj);
		 delete m_pVictimListenObj;
		 m_pVictimListenObj=NULL;
	 } 
     curSkillActionProcedure=_SKILLACTIONPROCEDURE_ENDPROCEDURE_TYPE_;
	 if(pCurrentSkillProcedure)
	 {
		  //给技能流程发送动画结束指令
		 pCurrentSkillProcedure->OnCommandHanlder(_TYPED_INPUT_COMMAND_SKILLACTION_END_);
	 }
	 SetIsValid(false);
	 Destroy();
	 //End Timer
	 CCLOG("OnEndSkillAction "); 	
}
 
 
//////////////////////////////////////////////////////////////////////////
void    CommonSkillActionProcedure::DoNextAssailantActionProcess()
{
	ToNextAssailantActionState();
	DispatchAttachActionHandler();
	PlayAssailantAction();
}

void    CommonSkillActionProcedure::DispatchAttachActionHandler()
{
	switch(curAssailantActionState)
	{
		case _ASSAILANT_SITUACTION_TYPE_:
			{
				assailantRole->setNodeZOrder(HighRoleZOrder);
				if(assailantRole!=vicitimsRole)
				{vicitimsRole->setNodeZOrder(LowRoleZOrder);}
				break;
			}
		case _ASSAILANT_ADVANCEACTION_TYPE_:
			{
				std::map<int,ACTIONDATA>::iterator  ActionIter=actionDataMap.find(_ASSAILANT_ADVANCEACTION_TYPE_);
				if(ActionIter!=actionDataMap.end())
				{
					m_pToTargetComAction=assailantRole->runMoveToAction(true,0.59f,AthleticsSceneManager::get_instance2()->AthleticsSpeed,
						this,_INNER_TARGET_EVENT_TYPE_);
				} 
				break;
			}
		case _ASSAILANT_TARGETACTION_TYPE_:
			{ 
				assailantRole->setNodeZOrder(HighRoleZOrder);
				if(assailantRole!=vicitimsRole)
				vicitimsRole->setNodeZOrder(LowRoleZOrder);
				assailantRole->forceMoveToTargetPosition();
				break;
			}
		case _ASSAILANT_RETURNACTION_TYPE_:
			{ 
				//判断角色是否当原地 
				if(assailantRole->isRoleAtInitXPos())
				{ 
					ToNextAssailantActionState();
					Tick();
					return ;
				}
				assailantRole->setFlipForAction(true); 

				std::map<int,ACTIONDATA>::iterator  ActionIter=actionDataMap.find(_ASSAILANT_RETURNACTION_TYPE_);
				if(ActionIter!=actionDataMap.end())
				{
					m_pToHomeComAction=assailantRole->runMoveToAction(false,0.38332f,AthleticsSceneManager::get_instance2()->AthleticsSpeed,
						this,_INNER_RETURN_EVENT_TYPE_);
 				}  
				break;
			}
		default:
			break;
	}
}


void    CommonSkillActionProcedure::PlayAssailantAction()
{
	if(curAssailantActionState==_ASSAILANT_ENDACTION_TYPE_)
	return ;

	std::map<int,ACTIONDATA>::iterator  ActionIter=actionDataMap.find(curAssailantActionState);
	if(ActionIter!=actionDataMap.end())
	{ 
		bool  isCycleActionType=(ActionIter->second.actionType==_COMMONACTION_CYCLE_TYPE_) ? true:false;
		if(ActionIter->second.actionID==HeroicRole::FuHuo)
		{

			assailantRole->onPlayBringAnimation();
		}
		else
		{
			CCLOG("PlayAssailantAction Handler : %d", ActionIter->second.actionID);
			assailantRole->setAnimationByID(ActionIter->second.actionID,isCycleActionType);
		}
		m_pAssailantListenObj->SetAttachEventType(curAssailantActionState);
	}  
}



void    CommonSkillActionProcedure::ToNextAssailantActionState()
{
	if(curAssailantActionState==_ASSAILANT_UNKONWACTION_TYPE_)
	{  
		if(totalAssailantActionsCount>0)
		{
			curAssailantExecuteIndex=0;
			curAssailantActionState=preAssailantActionSequence[0];
			return ;
		} 
	}
	else
	{
		if(curAssailantExecuteIndex<totalAssailantActionsCount-1)
		{
		    curAssailantActionState=preAssailantActionSequence[++curAssailantExecuteIndex];
			return ;
		} 
	}
	assailantRole->changeToIdleAnimation();
	m_pAssailantListenObj->UnRegisterNoticeDelegate();
	curAssailantActionState=_ASSAILANT_ENDACTION_TYPE_;
	Tick();
}

 
void	CommonSkillActionProcedure::StartAttackTimer()
{  
	if(rivalHurActionID!=-1)
	{ 
		curVicitimsActionState=_VICITIMS_HURTACTION_TYPE_;
		float hurtActionTriggerTime=(float)skillHurtActionCallTime/1000.0f;
		m_pDelayTriggerVictimAction=NFC_getTransimissionDelayComAction(hurtActionTriggerTime,AthleticsSceneManager::get_instance2()->AthleticsSpeed,
			this,_INNER_TIMER_HURT_EVENT_TYPE_);
		vicitimsRole->runExtAction(m_pDelayTriggerVictimAction);
	}
}

void    CommonSkillActionProcedure::TriggerAttachEventHandler()
{
	//触发动作 注册受击动作回调
	curVicitimsActionState=_VICITIMS_HURTACTION_TYPE_;
	CCLOG(">>>>>>>>>>>>>>HurtActionID:   %d",rivalHurActionID);
	if(rivalHurActionID==HeroicRole::_ROLE_DEAD_INSTRUCTION_)
	{ 
		if(!vicitimsRole->hadPlayedDeadAnimation())
	    {
			vicitimsRole->onPlayDeadAnimation(); 
			m_pVictimListenObj->SetAttachEventType(_VICITIMS_ENDACTION_TYPE_);
			return ;
		}
	   else
	   curVicitimsActionState=_VICITIMS_ENDACTION_TYPE_;
	   return ;
	}
	vicitimsRole->setAnimationByID(rivalHurActionID); 
	m_pVictimListenObj->SetAttachEventType(_VICITIMS_ENDACTION_TYPE_);
}


void	CommonSkillActionProcedure::AssailantActionCompleteHandler(int attachParam,int actionID)
{ 
	switch(attachParam)
	{
	case _ASSAILANT_SITUACTION_TYPE_:
	case _ASSAILANT_TARGETACTION_TYPE_:
		{
			DoNextAssailantActionProcess();
			break;
		}
	case _ASSAILANT_ADVANCEACTION_TYPE_:
	case _ASSAILANT_RETURNACTION_TYPE_:
		{
			//to do
			return ;
		}
	default:
		break;
	}
}

void    CommonSkillActionProcedure::VictimActionCompleteHandler(int attachParam,int actionID)
{ 
	if(attachParam==_VICITIMS_ENDACTION_TYPE_&&curVicitimsActionState!=_VICITIMS_ENDACTION_TYPE_)
	{    
		if(rivalHurActionID!=HeroicRole::SiWang&&rivalHurActionID!=HeroicRole::_ROLE_DEAD_INSTRUCTION_)
		{
			vicitimsRole->changeToIdleAnimation();
			vicitimsRole->excuteRoleStateAction();
		}
		curVicitimsActionState=_VICITIMS_ENDACTION_TYPE_; 
		m_pVictimListenObj->UnRegisterNoticeDelegate();
		Tick();
		return ;
	}
}


void  CommonSkillActionProcedure::CallFunctionHandler(int eventType,void * attachParam)
{
	switch(eventType)
	{
	case _INNER_TARGET_EVENT_TYPE_:
		{
			m_pToTargetComAction=NULL;
			assailantRole->setNodeZOrder(HighRoleZOrder);
			vicitimsRole->setNodeZOrder(LowRoleZOrder);
			assailantRole->forceMoveToTargetPosition();
			DoNextAssailantActionProcess();
			break;
		}
	case _INNER_RETURN_EVENT_TYPE_:
		{ 
			m_pToHomeComAction=NULL;
			assailantRole->setFlipForAction(false);
			assailantRole->forceMoveToInitPosition();
			DoNextAssailantActionProcess();
			break;
		}
	case _INNER_TIMER_HURT_EVENT_TYPE_:
		{
			m_pDelayTriggerVictimAction=NULL;
			curVicitimsActionState=_VICITIMS_HURTACTION_TYPE_;
			CCLOG(">>>>>>>>>>>>>>HurtActionID:   %d",rivalHurActionID);
			if(rivalHurActionID==HeroicRole::_ROLE_DEAD_INSTRUCTION_)
			{
				if(!vicitimsRole->hadPlayedDeadAnimation())
				{
					vicitimsRole->onPlayDeadAnimation(); 
					m_pVictimListenObj->SetAttachEventType(_VICITIMS_ENDACTION_TYPE_);
					return ;
				}
				else
				curVicitimsActionState=_VICITIMS_ENDACTION_TYPE_;
				return ; 
			}
			vicitimsRole->setAnimationByID(rivalHurActionID); 
			m_pVictimListenObj->SetAttachEventType(_VICITIMS_ENDACTION_TYPE_);
			break;
		}
	default:
		break;
	} 
} 


void  CommonSkillActionProcedure::SetSpeedScale(float speedScale)
{ 
	if(m_pDelayTriggerVictimAction)
	m_pDelayTriggerVictimAction->setSpeedScale(speedScale);
	if(m_pToTargetComAction)
	m_pToTargetComAction->setSpeedScale(speedScale);
	if(m_pToHomeComAction)
	m_pToHomeComAction->setSpeedScale(speedScale); 
}

 
/*
  初始化攻击者 动作序列
*/
void     CommonSkillActionProcedure::InitAssailantSquenceWithSkillParam(int skillParam/* =-1 */) 	
{   
	SkillActionData  * pSkilActionItem=SkillActionDataManager::get_instance2()->GetSkillActionItemByID(GetSubObjectID());
	if(pSkilActionItem!=NULL)
	{   
		if(skillParam==_COMMONACTION_DEFAULT_PARAM_||skillParam==_COOMONACTION_NORETURN_PARAM_)
		{
			if(pSkilActionItem->skillSituActionID_!=_COMMONACTION_DEFAULT_PARAM_)
			{
				//初始化  原地动作数据
				ACTIONDATA  situActionData;
				situActionData.actionID=pSkilActionItem->skillSituActionID_;
				situActionData.actionType=pSkilActionItem->skillSituActionType_;
				preAssailantActionSequence[totalAssailantActionsCount++]=_ASSAILANT_SITUACTION_TYPE_;
				actionDataMap.insert(std::map<int,ACTIONDATA>::value_type(_ASSAILANT_SITUACTION_TYPE_,situActionData));
			}
			if(pSkilActionItem->skillAdvanceActionID_!=_COMMONACTION_DEFAULT_PARAM_)
			{
				//初始化 前进动作数据
				ACTIONDATA  advanceActionData;
				advanceActionData.actionID=pSkilActionItem->skillAdvanceActionID_;
				advanceActionData.actionType=pSkilActionItem->skillAdvanceType_;
				advanceActionData.moveSpeed=pSkilActionItem->skillAdvanceSpeed_;
				preAssailantActionSequence[totalAssailantActionsCount++]=_ASSAILANT_ADVANCEACTION_TYPE_;
				actionDataMap.insert(std::map<int,ACTIONDATA>::value_type(_ASSAILANT_ADVANCEACTION_TYPE_,advanceActionData));
			}
			if(pSkilActionItem->skillTargetActionID_!=_COMMONACTION_DEFAULT_PARAM_)
			{
				//初始化 攻击动作数据
				ACTIONDATA  targetActionData;
				targetActionData.actionID=pSkilActionItem->skillTargetActionID_;
				targetActionData.actionType=pSkilActionItem->skillTargetActionType_;
				preAssailantActionSequence[totalAssailantActionsCount++]=_ASSAILANT_TARGETACTION_TYPE_;
				actionDataMap.insert(std::map<int,ACTIONDATA>::value_type(_ASSAILANT_TARGETACTION_TYPE_,targetActionData));
			}
		}
		
		if(skillParam!=_COOMONACTION_NORETURN_PARAM_)
		{
			if(pSkilActionItem->skillReturnActionID_!=_COMMONACTION_DEFAULT_PARAM_)
			{
				//初始化 返回动作数据
				ACTIONDATA returnActionData;
				returnActionData.actionID=pSkilActionItem->skillReturnActionID_;
				returnActionData.actionType=pSkilActionItem->skillReturnActionType_;
				returnActionData.moveSpeed=pSkilActionItem->skillReturnSpeed_;
				preAssailantActionSequence[totalAssailantActionsCount++]=_ASSAILANT_RETURNACTION_TYPE_;
				actionDataMap.insert(std::map<int,ACTIONDATA>::value_type(_ASSAILANT_RETURNACTION_TYPE_,returnActionData));
			}
		}
	}	
} 

