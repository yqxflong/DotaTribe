//Name：CommonSkillActionProcedure
//Function：技能控制流程
//Author:	Johny

#ifndef   _DOTATRIBE_COMMONSKILLITEMPROCEDURE_H
#define   _DOTATRIBE_COMMONSKILLITEMPROCEDURE_H
 
#include   "../include/BaseObject.h"
#include   "../include/CommonSkillActionProcedure.h"
#include   "../include/SkillAttachLogicManager.h"
#include   "../include/AthleticsInstructionUnit.h"
#include   "../include/AthleticProcedureDataType.h"
#include   "../include/VariableSpeedSequenceAction.h"
#include   "../include/CallFuncAction.h"
#include    <vector>

class CommonSkillActionProcedure;
class AthleticsInstructionUnit;
class HeroicRole;


class   CommonSkillItemProcedure: public BaseObject,public CallFunctionProtocol
{
public:

	//@技能作用目标
	enum
	{
		_SKILLITEM_UNKONW_TYPE_=-1,
		_SKILLITEM_SELFTARGET_TYPE_,  //目标为自己
		_SKILLITEM_RIVALTARGET_TYPE_, //目标为敌人
	};
    
	//@技能流程的各种状态
	enum
	{
		_SKILLITEMPROCEDURE_UNKONW_TYPE_,				    //未知流程流程
		_SKILLITEMPROCEDURE_BEGINPROCEDURE_TYPE_,		    //开始技能流程
		_SKILLITEMPROCEDURE_RUNNINGPROCEDURE_TYPE_,		    //运行技能流程
		_SKILLITEMPROCEDURE_PAUSEPROCEDURE_TYPE_,		    //暂停技能流程
		_SKILLITEMPROCEDURE_NULLPROCEDURE_TYPE_,		    //技能动画完成回调流程
		_SKILLITEMPROCEDURE_EXCEPTION_DEATH_PROCEDURE_TYPE_,//角色异常死亡处理流程 
		_SKILLITEMPROCEDURE_ENDPROCEDURE_TYPE_,			    //结束技能流程
	};
 

	//@技能附加逻辑状态
	enum
	{
		_SKILLATTACHLOGIC_UNKOWN_TYPE_,				//未知  技能附加流程
		_SKILLATTACHLOGIC_BEGINPROCEDURE_TYPE_,		//开始技能附加逻辑
		_SKILLATTACHLOGIC_RUNNINGPROCEDURE_TYPE_,	//运行技能附加逻辑
		_SKILLATTACHLOGIC_PAUSEPROCEDURE_TYPE_,		//暂停技能附加逻辑
		_SKILLATTACHLOGIC_ENDPROCEDURE_TYPE_,		//结束技能附加逻辑
	};

	//@内部事件通知
	enum
	{
		_SKILLPROCEDURE_UNKOWN_EVENT_TYPE_,			//未知   技能事件通知
		_SKILLPROCEDURE_ATTACH_LOGIC_EVENT_TYPE_,	//技能附加逻辑触发通知
	};
  
public:
	CommonSkillItemProcedure();
	~CommonSkillItemProcedure();
public:
	//@标配
	virtual  void   Destroy();
	virtual  void   Tick(); 

	//@使用指令单元初始化技能流程
	virtual  void   InitWithInstructionData(AthleticsInstructionUnit * instructionUnit=NULL);

	//@事件通知接口
	virtual  void   OnCommandHanlder(int EventTypeID);

	//@事件通知接口2
	virtual   void  OnCommandHanlder(int EventTypeID,std::string attachParam);

    //@技能开始
	virtual  void   OnBeginSkillItem();

	//@技能结束
	virtual  void   OnEndSkillItem();

	 
    //@技能结束Notification
	virtual  void   OnEndSkillNotification();

	//@更新逻辑变速
	virtual  void  SetSpeedScale(float speedScale);

	//@动画定时回调事件通知
	virtual  void  CallFunctionHandler(int eventType,void * attachParam);

public:
    
	//@获得技能流程的ID
	int     GetSkillProcedureID();

	//@获得当前技能的施放者 的方向
	bool    GetIsExecutorLeft();

	//@获取当前技能的作用者的方向
	bool    GetIsVictimLeft();
 
    //@获得绑定的指令单元数据
    AthleticsInstructionUnit * GetAthleticsInstrucionUnit();

protected:
    //@技能流程的状态机
	void    SkillProcedureStateMachine();

	//@附加逻辑状态机
	void    AttachLogicStateMachine();
	 
	//@初始化技能的释放者和作用目标的方向 
	void    InitSkillAttackDirection();

	//@初始化技能命中类型
	void    InitSkillHitType();
 
	//@初始化技能附加逻辑数据
	void    IniSkillAttachLogicData();

	//@处理技能附加逻辑
	void    SkillAttachLogicProcedureHandler(int attachLogicIndex);
  
	//@获得附加效果触发基础时间
	float  GetHurtEffectTriggerTime();

  
	//@根据技能附加效果类型动态参数数据队列
	std::vector<std::string> GetSkillAttachParamWithLogicType(PSkillAttach_Base skillAttach_tag);
  
	//@检测角色的异常事件
	bool   CheckRoleExceptionEvent(bool isLeftRole);

	//@角色异常事件处理
	void   ThrowExceptionEvent(HeroicRole * pHeroicRole);

	//@技能附加逻辑触发定时器
	void   StartAttachLogicTimer();

	//@处理附加技能逻辑
	void   LuanchAttachLogicHandler();

	//@插入命中注释旁白
	std::vector<std::string>   AppendAttachHitNoteByType(int hitType);
	  
protected:

	//技能动画流程
	CommonSkillActionProcedure *  pCommonSkillActionProcedure_;  
 
	//技能附加效果组 
	std::vector<PSkillAttach_Base>   skillAttachLogicVector_;	

	//战斗指令单元
	AthleticsInstructionUnit  *   pAthleticsInstructionUnit_;
 	 

	//基础受击特效触发时间点 单位为ms
	float      hurtEffectTriggerTime;									

	long long  startTimeTick;		
	long long  durationTimeTick;

	VariableSpeedSequenceAction *    pAttachLogicAction;		   //技能附加逻辑触发定时器
 
	bool   isExecutorLeft;										   //技能执行者是否在左边
	bool   isVictimLeft;										   //技能作用者是否在右边

	bool   IsExistHitNote;										   //是否存在命中注释
	bool   isCritSkill;											   //是否暴击技能
	bool   isMutipleBatterSkill;								   //是否多次攻击
	int	   mutipleBatterCount;									   //多次攻击的连击数
 
	//当前技能流程状态
	int  curSkillProcedureState_;

	//当前技能附加流程状态
	int  curSkillAttachLogicState_;	

	HeroicRole * pExceptionRole;

};


#endif







