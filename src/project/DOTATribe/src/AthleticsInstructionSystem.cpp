//Name：AthleticsInstructionSystem
//Function：战斗指令系统
//Author:	Johny

#include    <cocos2d.h>
#include    "../include/AthleticProcedureDataType.h"
#include    "../include/AthleticsInstructionSystem.h"
#include    "../include/CommonSkillItemProcedure.h"
#include    "../include/AthleticsSceneManager.h"
#include    "../include/BaseObjectManager.h" 
#include    "../include/AthleticProcedureDataHandler.h"
#include    "../include/UnSkillNumbericalProcedure.h"
#include    "../include/UnSkillRemoveBufferProcedure.h"
#include    "../include/IntellectDelayRemoveManager.h"



template<> AthleticsInstructionSystem* cobra_win::Singleton2<AthleticsInstructionSystem>::m_pMySelf = NULL;

AthleticsInstructionSystem::AthleticsInstructionSystem()
{
     curInstructionSystemState_=_INSTRUCTIONSYSTEM_UNKOWN_TYPE_;
	 curAthleticsInstructionID_=0;
	 cutAthleticsRound_=0;
	// m_LogicTick_=0;
	 pAthleticsProcedureData=NULL;
	 pAthleticsInstructionUnit=NULL; 
	 pAllAthleticsProData=NULL;
	 totalAthleticsTurnCount_=0;
	 isValid_=true;
}

AthleticsInstructionSystem::~AthleticsInstructionSystem()
{
	  Destroy();	
	  m_pMySelf=NULL;
}



bool   AthleticsInstructionSystem::IsValid()
{
	return  isValid_;
}


void   AthleticsInstructionSystem::SetIsValid(bool isValid)
{
	if(isValid_!=isValid)
	{
		isValid_=isValid;
	}
}


void  AthleticsInstructionSystem::Init()
{
    //启动技能附加逻辑管理器
	new SkillAttachLogicManager;
	SkillAttachLogicManager::get_instance2()->Init();
	//智能延时删除管理器
	new IntellectDelayRemoveManager;
    IntellectDelayRemoveManager::get_instance2()->Init();
	OnLoadAthleticsProcedureData();
 
}

void  AthleticsInstructionSystem::Destroy()
{ 

	if(SkillAttachLogicManager::get_instance2()!=NULL)
	{
		SkillAttachLogicManager::get_instance2()->Destroy();
		delete SkillAttachLogicManager::get_instance2();
	}

	if(IntellectDelayRemoveManager::get_instance2()!=NULL)
	{
		IntellectDelayRemoveManager::get_instance2()->Destroy();
	    delete IntellectDelayRemoveManager::get_instance2();
	}
}

void  AthleticsInstructionSystem::Tick()
{
	if(!isValid_)
		return ;
	// m_LogicTick_++;

    if(curInstructionSystemState_==_INSTRUCTIONSYSTRM_ENDINSTRUCTIONSYS_TYPE_)
	{ 
		//结束战斗指令系统
		OnEndAthleticsProcedure();
		return ;
	}
	else if(curInstructionSystemState_==_INSTRUCTIONSYSTER_INITRROLEUI_TYPE_)
	{
		//初始化角色UI 调用AthleticSceneManager的接口     角色入场
		OnUpdateAthleticsRoleUI();
		return ;
	}
	else if(curInstructionSystemState_==_INSTRUCTIONSYSTRM_RUNNINGINSTRUCTSYS_TYPE_)
	{
		//执行单元指令
		if(!OnExecuteNextUnitInstrunction())
		Tick();
		return ;
	}
	else if(curInstructionSystemState_==_INSTRUCTIONSYSTRM_NEXTROUNDATHLETICS_TYPE_)
	{
        //进入下个回合战斗
		//判断有没有下个回合 没有就立即结束
		OnTurnToNextRoundProcedure();
		return ;
	}
}
 
void  AthleticsInstructionSystem::OnCommandHandler(int eventType)
{
    if(eventType==_TYPED_INPUT_COMMAND_RESUME_ATHLETICSINSTRUCTION_)
	{
		//恢复指令运行状态
		if(!AthleticsSceneManager::get_instance2()->IsGameOver())
		{
			if(curInstructionSystemState_==_INSTRUCTIONSYSTEM_FORCEHOMINGINSTRUCTSYS_TYPE_)
			{ 
				//强制清理归位的临时指令数据
				if(pAthleticsUnitData!=NULL)
				{
					pAthleticsUnitData->Destroy();
				    delete pAthleticsUnitData;
					pAthleticsUnitData=NULL;
				}
			}
			else if(curInstructionSystemState_==_INSTRUCTIONSYSTRM_INTERRUPTATHLETICS_TYPE_)
			{
				return ;
			} 
    		curInstructionSystemState_=_INSTRUCTIONSYSTRM_RUNNINGINSTRUCTSYS_TYPE_;
			Tick();
			return ;
		}
	}
	else if(eventType==_TYPEF_INPUT_COMMAND_REPLAY_ATHLETICSINSTRUCTION_)
	{
       //重播战斗
		OnReplayAthleticsProcedure();
		return ;
	}
}


void AthleticsInstructionSystem::SetInstructionSystemCurState(int syatemState)
{ 
	 curInstructionSystemState_=syatemState;
	 DispatchStateEventHandler();
}

//@分发状态处理事件
void	AthleticsInstructionSystem::DispatchStateEventHandler()
{
	switch(curInstructionSystemState_)
	{    
	case _INSTRUCTIONSYSTRM_INTERRUPTATHLETICS_TYPE_:
		{ 
			AthleticsSceneManager::get_instance2()->SetGameOver();
			break;
		}
	case _INSTRUCTIONSYSTRM_ENDINSTRUCTIONSYS_TYPE_:
		{
			OnEndAthleticsProcedure();
			break;
		}
	default:
		{
			Tick();
			break;
		}
	}
}

 
//@回放上一战斗流程
void  AthleticsInstructionSystem::OnReplayAthleticsProcedure()
{
	IntellectDelayRemoveManager::get_instance2()->Destroy();
	 curAthleticsInstructionID_=0;
	 cutAthleticsRound_=0;
	 if(pAllAthleticsProData!=NULL)
	 {
		 size_t  totalAthleicsSize=pAllAthleticsProData->totalAthleticsDataVector.size();
		 if(totalAthleicsSize>0)
		 {
			 pAthleticsProcedureData=pAllAthleticsProData->totalAthleticsDataVector.at(0);
		 }
	 } 
	 curInstructionSystemState_=_INSTRUCTIONSYSTER_INITRROLEUI_TYPE_;
}

 
//@战斗角色初始化
void   AthleticsInstructionSystem::OnUpdateAthleticsRoleUI()
{
	IntellectDelayRemoveManager::get_instance2()->Destroy();
	if(pAthleticsProcedureData!=NULL)
	{
		RoleUniqeDefine role1;
		role1.sourceID=pAthleticsProcedureData->roleID1;
		role1.unitType=pAthleticsProcedureData->roleType1;

		RoleUniqeDefine role2;
		role2.sourceID=pAthleticsProcedureData->roleID2;
		role2.unitType=pAthleticsProcedureData->roleType2;

		AthleticsSceneManager::get_instance2()->OnUpdateAthleticsRoleSkeleton(role1,role2);
		curInstructionSystemState_=_INSTRUCTIONSYSTRM_PAUSEINSTRUCTSYS_TYPE_;
	}
}


void   AthleticsInstructionSystem::OnBeginAthleticsProcedure()
{
      curInstructionSystemState_=_INSTRUCTIONSYSTRM_RUNNINGINSTRUCTSYS_TYPE_;
}
 
void   AthleticsInstructionSystem::OnEndAthleticsProcedure()
{
	SetIsValid(false);
	Destroy();
}

//@战斗指令派发器
bool  AthleticsInstructionSystem::OnDispatchLogicUnitData(PAthleticsUnitData pAthleticsUnitData)
{
    if(pAthleticsUnitData!=NULL)
	{
		IntellectDelayRemoveManager::get_instance2()->UpdateDelayRemoveManager();
		switch(pAthleticsUnitData->athleticsType)
		{
		  case  _ATHLETICSINSTRUCTION_SKILL_TYPE_:
		  {
			   //技能指令
			  if(OnExecuteSkillTypeUnitData(pAthleticsUnitData))
			  return true;
			  break;
		  }
		  case _ATHLETICSINSTRUCTION_REMOVE_EFFECT_TYPE_:
		  {
			  //删除Effect指令
			   if(OnExecuteRemoveEffectUnitData(pAthleticsUnitData))
			   return true;
			   break;
		  }
		 case  _ATHLETICSINSTRUCTION_REMOVE_STATE_TYPE_:
	      {
			   //删除State指令
			  if(OnExecuteRemoveStateTypeUnitData(pAthleticsUnitData))
			  return true;
			  break;
		  }
		  case _ATHLETICSINSTRUCTION_LOCATION_TYPE_:
		  {
			    //位置改变指令
			  if(OnExecuteLocationTypeUnitData(pAthleticsUnitData))
			  return true;
		      break;
		  }
		  case  _ATHLETICSINSTRUCTION_RESTORE_HP_TYPE_:             //回血指令
		  case  _ATHLETICSINSTRUCTION_RESTORE_MP_TYPE_:				//回蓝指令
		  case  _ATHLETICSINSTRUCTION_DAMAGE_HP_TYPE_:				//失血指令
		  case  _ATHLETICSINSTRUCTION_DAMAGE_MP_TYPE_:				//失蓝指令
		  {
			  //添加数值指令
			  if(OnDispatchNumbericalAttachLogic(pAthleticsUnitData))
			  return true;
			  break;
		  }
		  case  _ATHLETICSINSTRUCTION_ADD_EFFECT_TYPE_:
		  {
			   //加Effect指令
			  if(OnExecuteAddEffectUnitData(pAthleticsUnitData))
			  return true;
		      break;
		  }
		  case  _ATHLETICSINSTRUCTION_ADD_STATE_TYPE_:
		  {
			  //加状态指令
			  if(OnExecuteAddStateUnitData(pAthleticsUnitData))
			  return true;
              break;
		  }
		  case _ATHLETICSINSTRUCTION_ROLE_BRING_TYPE_:
		 {
			 //复活指令
			 return true;
			 break;
	     }
		  default:
		  return false; 
		}
	}
	return false;
}

//@执行技能过程指令  
bool  AthleticsInstructionSystem::OnExecuteSkillTypeUnitData(PAthleticsUnitData pAthleticsUnitData)
{
	  if(pAthleticsUnitData!=NULL)
	  {
		  pAthleticsInstructionUnit=new AthleticsInstructionUnit();
		  if(pAthleticsInstructionUnit!=NULL)
		  {
			 pAthleticsInstructionUnit->InitWithConfigData(pAthleticsUnitData);
			 CommonSkillItemProcedure  *  pCommonSkillItemProcedure=new CommonSkillItemProcedure();
			 if(pCommonSkillItemProcedure!=NULL)
			 {
				pCommonSkillItemProcedure->InitWithInstructionData(pAthleticsInstructionUnit);
				/*
				  将技能流程加入 技能管理池 autorelase 
				*/
				BaseObjectManager::get_instance2()->InsertObject(pCommonSkillItemProcedure);
				return true;
			 }
		  } 
	  }
	 
	  return false;
}

//@执行移除驻留特效指令
bool  AthleticsInstructionSystem::OnExecuteRemoveEffectUnitData(PAthleticsUnitData pAthleticsUnitData)
{
    PAthleticsData_Buffer   pAthleticsDataBuffer=(PAthleticsData_Buffer)pAthleticsUnitData->athleticsData;
	if(pAthleticsDataBuffer!=NULL)
	{ 
		if(IntellectDelayRemoveManager::get_instance2()->IsDelayRemoveAtInterval(pAthleticsDataBuffer->effectID))
		{
			BaseObject * pUnSkillRemoveBuffer=(BaseObject *)UnSkillRemoveBufferProcedure::CreateCommonUnSkillItemProcedure(pAthleticsUnitData);
			BaseObjectManager::get_instance2()->InsertObject(pUnSkillRemoveBuffer);
			return true;
		}
		else
		{
			HeroicRole  *pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
			if(pAthleticsDataBuffer->sourceID!=pHeroicRole->GetSubObjectID()||pAthleticsDataBuffer->sourceType!=pHeroicRole->getRoleType())
			{ 
				pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
			}
			if(pHeroicRole!=NULL)
			{
				pHeroicRole->OnStopCommonEffect(pAthleticsDataBuffer->effectID);
			}
		}
	} 
    return false;
}

/*
处理删除状态指令逻辑
*/
bool  AthleticsInstructionSystem::OnExecuteRemoveStateTypeUnitData(PAthleticsUnitData pAthleticsUnitData)
{
	if(pAthleticsUnitData!=NULL)
	{
		PAthleticsData_State  pAthleticsDataState=(PAthleticsData_State)pAthleticsUnitData->athleticsData;
		if(pAthleticsDataState!=NULL)
		{
			HeroicRole  *pHeroicRole=AthleticsSceneManager::get_instance2()->GetLeftFightRole();
			if(pAthleticsDataState->sourceID!=pHeroicRole->GetSubObjectID()||pAthleticsDataState->sourceType!=pHeroicRole->getRoleType())
			{ 
				pHeroicRole=AthleticsSceneManager::get_instance2()->GetRightFightRole();
			}
			if(pHeroicRole!=NULL)
			{
				pHeroicRole->removeRoleState(pAthleticsDataState->roleState);
			}
		}
	}
	return false;
}

 
//@执行位置改变指令
bool  AthleticsInstructionSystem::OnExecuteLocationTypeUnitData(PAthleticsUnitData pAthleticsUnitData)
{	
    if(pAthleticsUnitData!=NULL)
	{
	  //抽象指令控制单元
	  pAthleticsInstructionUnit=new AthleticsInstructionUnit();

	  if(pAthleticsInstructionUnit!=NULL)
	  {
		 pAthleticsInstructionUnit->InitWithConfigData(pAthleticsUnitData);

		 //指令数据校验
		 if(!pAthleticsInstructionUnit->VerifyInstructionUnitData())
		 {
			 pAthleticsInstructionUnit->Destroy();
			 delete pAthleticsInstructionUnit;
			 pAthleticsInstructionUnit=NULL;
			 return false;
		 }  
		 CommonSkillItemProcedure  *  pCommonSkillItemProcedure=new CommonSkillItemProcedure();
		 if(pCommonSkillItemProcedure!=NULL)
		 {
			pCommonSkillItemProcedure->InitWithInstructionData(pAthleticsInstructionUnit);
			/*
			  将技能流程加入 技能管理池 autorelase 
			*/
			BaseObjectManager::get_instance2()->InsertObject(pCommonSkillItemProcedure);
			return true;
		 }
	  } 
	}
    return false;
}
 
  

bool  AthleticsInstructionSystem::OnDispatchNumbericalAttachLogic(PAthleticsUnitData pAthleticsUnitData)
{
	BaseObject * pUnSkillProcedure=(BaseObject *)UnSkillNumbericalProcedure::CreateCommonUnSkillItemProcedure(pAthleticsUnitData);
	BaseObjectManager::get_instance2()->InsertObject(pUnSkillProcedure);
	return true;
	return false;
}
 


bool  AthleticsInstructionSystem::OnExecuteAddEffectUnitData(PAthleticsUnitData pAthleticsUnitData)
{
	if(pAthleticsUnitData!=NULL)
	{
	    PAthleticsData_Buffer  pAthleticsDataBuffer=(PAthleticsData_Buffer)pAthleticsUnitData->athleticsData;
		if(pAthleticsDataBuffer!=NULL)
		{	
			bool isVicitmsleft=false;
			std::vector<std::string>  attachParams;
			char attachParas[16]={0};
			sprintf(attachParas,"%d",pAthleticsDataBuffer->effectID);
			attachParams.push_back(attachParas);
			sprintf(attachParas,"%d",pAthleticsDataBuffer->sourceType);
			attachParams.push_back(attachParas);
			sprintf(attachParas,"%d",pAthleticsDataBuffer->sourceID);
			attachParams.push_back(attachParas);
		    SkillAttachLogicManager::get_instance2()->OnCommandHandler(_ATHLETICS_SKILL_ADD_EFFECT_TYPE_,attachParams,isVicitmsleft,isVicitmsleft); 
		}
	}
	return false;
}

bool  AthleticsInstructionSystem::OnExecuteAddStateUnitData(PAthleticsUnitData pAthleticsUnitData)
{
	if(pAthleticsUnitData!=NULL)
	{
		PAthleticsData_State  pAthleticsDataState=(PAthleticsData_State)pAthleticsUnitData->athleticsData;
		if(pAthleticsDataState!=NULL)
		{	
			bool isVicitmsleft=false;
			if(pAthleticsDataState->sourceID==AthleticsSceneManager::get_instance2()->GetLeftFightRole()->GetSubObjectID())
			{
				isVicitmsleft=true;
			}
			std::vector<std::string>  attachParams;
			char attachParas[16]={0};
			sprintf(attachParas,"%d",-1);
			attachParams.push_back(attachParas);
			sprintf(attachParas,"%d",pAthleticsDataState->sourceType);
			attachParams.push_back(attachParas);
			sprintf(attachParas,"%d",pAthleticsDataState->sourceID);
			attachParams.push_back(attachParas);
			sprintf(attachParas,"%d",pAthleticsDataState->roleState);
			attachParams.push_back(attachParas);
			SkillAttachLogicManager::get_instance2()->OnCommandHandler(_ATHLETICS_SKILL_ADD_STATE_TYPE_,attachParams,isVicitmsleft,isVicitmsleft); 
		}
	}
	return false;
}


//@执行下条战斗指令
bool  AthleticsInstructionSystem::OnExecuteNextUnitInstrunction()
{
	  pAthleticsUnitData=GetNextAthleticsUnitData();
	  if(pAthleticsUnitData!=NULL)
	  { 
		  if(OnDispatchLogicUnitData(pAthleticsUnitData))
		  {
			curInstructionSystemState_=_INSTRUCTIONSYSTRM_PAUSEINSTRUCTSYS_TYPE_;
		  }
		  return true;
	  }
	  return   false;
}

//@进入下一轮判定流程
void   AthleticsInstructionSystem::OnTurnToNextRoundProcedure()
{ 
	 if((cutAthleticsRound_+1)<totalAthleticsTurnCount_)
	 { 
		 //判断胜利者是否需要归位
		 if(ATHLETICSSCENEMANAGER->IsWinRoleNeedHoming())
		 { 
			 //强制角色归位
			 ForceHomingRole();
			 curInstructionSystemState_=_INSTRUCTIONSYSTEM_FORCEHOMINGINSTRUCTSYS_TYPE_;
			 return ; 
		 }
		 ATHLETICSSCENEMANAGER->PostCurRoundWillDid();
         //切换至下一轮
		 IntellectDelayRemoveManager::get_instance2()->Destroy();
		 pAthleticsProcedureData=pAllAthleticsProData->totalAthleticsDataVector.at(++cutAthleticsRound_);
		 //轮次切换初始化操作
		 curAthleticsInstructionID_=0;
		 curInstructionSystemState_=_INSTRUCTIONSYSTER_INITRROLEUI_TYPE_;
		 return ;
	 }
	 else
	 {
		 //游戏最终结束
		 AthleticsSceneManager::get_instance2()->SetGameOver();
		 curInstructionSystemState_=_INSTRUCTIONSYSTEM_UNKOWN_TYPE_;
	 }
}



bool   AthleticsInstructionSystem::OnLoadAthleticsProcedureData()
{
	//从网络数据中加载战斗过程数据
     if(ATHLETICPROCEDUREDATA->pAthleticProData!=NULL)
	 {
		 pAllAthleticsProData=AthleticProcedureDataHandler::get_instance2()->pAthleticProData;   //全程战斗数据包
		 totalAthleticsTurnCount_=pAllAthleticsProData->totalTurnCount;							 //战斗轮次
		 cutAthleticsRound_=0;																	 //初始战斗轮次索引为0
		 if(totalAthleticsTurnCount_>0)
		 {
			 pAthleticsProcedureData=pAllAthleticsProData->totalAthleticsDataVector.at(cutAthleticsRound_);
		 }

		 return  true;
	 }
	 return false;
}


short  AthleticsInstructionSystem::GetAthleticsRoundCount()
{
     return totalAthleticsTurnCount_;
}
 


short  AthleticsInstructionSystem::GetCurAthleticsUnitCount()
{
	 if(pAthleticsProcedureData!=NULL)
	 {
		 return pAthleticsProcedureData->athleticsDataVector.size();
	 }
	 return  0;
}


short  AthleticsInstructionSystem::GetCurAthleticsIndex()
{
	return curAthleticsInstructionID_;
}


//@获得下一条战斗过程指令
PAthleticsUnitData  AthleticsInstructionSystem::GetNextAthleticsUnitData()
{
	if(pAthleticsProcedureData!=NULL)
	{
		//Add 
		if(curAthleticsInstructionID_<GetCurAthleticsUnitCount())
		{
			return pAthleticsProcedureData->athleticsDataVector.at(curAthleticsInstructionID_++);
		}
		else
		{
			curInstructionSystemState_=_INSTRUCTIONSYSTRM_NEXTROUNDATHLETICS_TYPE_;   //进入下一轮
			return NULL;
		}
	}
	else
	{ 
		curInstructionSystemState_=_INSTRUCTIONSYSTRM_NEXTROUNDATHLETICS_TYPE_;     //进入一下论
	}
	return NULL;
}
  
/*
强制角色归位
*/
void	 AthleticsInstructionSystem::ForceHomingRole()
{
	RoleUniqeDefine roleInfo;
	ATHLETICSSCENEMANAGER->GetNeedHomingRoleInfo(roleInfo);
	//构造角色返回指令
	pAthleticsUnitData=new AthleticsUnitData();
	pAthleticsUnitData->athleticsType=_ATHLETICSINSTRUCTION_LOCATION_TYPE_;
	PAthleticsData_Location  pLocationData=new AthleticsData_Location();
	pLocationData->sourceType=roleInfo.unitType;
	pLocationData->sourceID=roleInfo.sourceID;
	pLocationData->skillItemID=_ATHLETICS_NORMAL_SKILL_ID_;
	pLocationData->location=0;
	pAthleticsUnitData->athleticsData=pLocationData;
	pAthleticsInstructionUnit=new AthleticsInstructionUnit();
	if(pAthleticsInstructionUnit!=NULL)
	{
		pAthleticsInstructionUnit->InitWithConfigData(pAthleticsUnitData);
		CommonSkillItemProcedure  *  pCommonSkillItemProcedure=new CommonSkillItemProcedure();
		if(pCommonSkillItemProcedure!=NULL)
		{
			pCommonSkillItemProcedure->InitWithInstructionData(pAthleticsInstructionUnit);
			BaseObjectManager::get_instance2()->InsertObject(pCommonSkillItemProcedure);
		} 
	}  
}

