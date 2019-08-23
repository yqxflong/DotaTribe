//Name：AthleticsInstructionSystem
//Function：战斗指令系统
//Author:	Johny

#ifndef   _DOTATRIBE_ATHLETICSINSTRUCTIONSYSTEM_H_
#define   _DOTATRIBE_ATHLETICSINSTRUCTIONSYSTEM_H_

#include     "../include/AthleticsInstructionUnit.h"
#include     "../include/InputCommand.h"
#include	 <include/common/Singleton.h>
#include     <vector>

using  namespace  cobra_win;


class   AthleticsInstructionSystem : public cobra_win::Singleton2<AthleticsInstructionSystem>
{ 
public:
	//@战斗指令系统状态机
	enum
	{
		_INSTRUCTIONSYSTEM_UNKOWN_TYPE_,				  	//未知状态
		_INSTRUCTIONSYSTER_INITRROLEUI_TYPE_,				//战斗角色初始化(入场)状态
		_INSTRUCTIONSYSTRM_BEGININSTRUCTSYS_TYPE_,			//开启指令系统状态
		_INSTRUCTIONSYSTRM_PAUSEINSTRUCTSYS_TYPE_,			//暂停指令系统状态
		_INSTRUCTIONSYSTRM_RUNNINGINSTRUCTSYS_TYPE_,		//指令系统正常状态
		_INSTRUCTIONSYSTEM_FORCEHOMINGINSTRUCTSYS_TYPE_,	//强制角色归位状态
		_INSTRUCTIONSYSTRM_NEXTROUNDATHLETICS_TYPE_,		//进入下个回合状态 
		_INSTRUCTIONSYSTRM_INTERRUPTATHLETICS_TYPE_,		//系统中断结束状态
		_INSTRUCTIONSYSTRM_ENDINSTRUCTIONSYS_TYPE_,			//结束指令系统状态
	};
	AthleticsInstructionSystem();
	virtual ~AthleticsInstructionSystem();
public:
	//@标配
	void Init();
	void Destroy();
	void Tick();

	//@有效性
	bool   IsValid();
	void   SetIsValid(bool isValid);

	//@监听事件
	void OnCommandHandler(int eventType);

	//@设置当前状态
	void SetInstructionSystemCurState(int syatemState);

	
	//@战斗流程初始化
	void   OnBeginAthleticsProcedure();

	//@战斗角色初始化
	void   OnUpdateAthleticsRoleUI();

	//@战斗指令系统结束
	void   OnEndAthleticsProcedure();
	 
	//@战斗指令系统 复位
	void  OnReplayAthleticsProcedure();
  

	//@执行下条战斗指令
	bool  OnExecuteNextUnitInstrunction();

	//@进入下一轮判定流程
	void  OnTurnToNextRoundProcedure();   

	//@战斗指令派发器
	bool  OnDispatchLogicUnitData(PAthleticsUnitData pAthleticsUnitData);

	//@执行技能过程指令
	bool  OnExecuteSkillTypeUnitData(PAthleticsUnitData pAthleticsUnitData);

	//@执行移除驻留特效指令
	bool  OnExecuteRemoveEffectUnitData(PAthleticsUnitData pAthleticsUnitData);

	//@执行移除驻留状态指令
	bool  OnExecuteRemoveStateTypeUnitData(PAthleticsUnitData pAthleticsUnitData);

	//@执行位置改变指令
	bool  OnExecuteLocationTypeUnitData(PAthleticsUnitData pAthleticsUnitData);

	//@执行添加特效指令
	bool  OnExecuteAddEffectUnitData(PAthleticsUnitData pAthleticsUnitData);

	//@执行添加状态指令
	bool  OnExecuteAddStateUnitData(PAthleticsUnitData pAthleticsUnitData);

	//@执行数值特效指令派发
	bool  OnDispatchNumbericalAttachLogic(PAthleticsUnitData pAthleticsUnitData);

  
	//@加载战斗过程数据
	bool   OnLoadAthleticsProcedureData();

	//@获得当前数据包中战斗回合次  暂时废弃
	short  GetAthleticsRoundCount();

	//@获得当前回合战斗指令条数
    short  GetCurAthleticsUnitCount();
 
	//@获得战斗索引
	short  GetCurAthleticsIndex();
 
	//@获得下一条战斗过程指令
	PAthleticsUnitData  GetNextAthleticsUnitData();
	 
protected:
	//@强制角色归位流程
	void	 ForceHomingRole();

	//@分发状态处理事件
	void	 DispatchStateEventHandler();

protected:

	 PAthleticsProData				pAllAthleticsProData;		  //全程战斗数据包
 
  	 PAthleticsProcedureData		pAthleticsProcedureData;	  //单轮 回合制战斗指令数据集

	 PAthleticsUnitData				pAthleticsUnitData;		  //当前指令单元数据

	 AthleticsInstructionUnit  *    pAthleticsInstructionUnit;	  //当前执行指令单元
	  	
     //long long  m_LogicTick_;									  //逻辑帧的Tick  (暂时无用，等待废弃)
	
	 int  curInstructionSystemState_;							  //指令系统的当前状态

	 short  cutAthleticsRound_;						    		  //当前的战斗的轮次 第几轮  重要参数

	 short  curAthleticsInstructionID_;							  //当前轮战斗指令索引  从0开始

	 short  totalAthleticsTurnCount_;							  //总的战斗轮次数目     非常重要
 
	 bool	isValid_;											  //系统是否有效
 
 
public:
	friend  class  cobra_win::Singleton2<AthleticsInstructionSystem>;
};

#define   ATHLETICSICSYSTEM    (AthleticsInstructionSystem::get_instance2())

 
#endif