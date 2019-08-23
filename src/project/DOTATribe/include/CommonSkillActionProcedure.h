//Name：CommonSkillActionProcedure
//Function：技能动画控制流程
//Author:	Johny

#ifndef   _DOTATRIBE_COMMONSKILLACTIONPROCEDURE_H
#define   _DOTATRIBE_COMMONSKILLACTIONPROCEDURE_H

#include    <cocos2d.h>
#include	"../include/BaseObject.h"
#include    "../include/CommonSkillItemProcedure.h"
#include    "../include/HeroicRole.h"
#include	"../include/CallFuncAction.h"
#include    <list>
 
 
class   CommonSkillItemProcedure;
class   ListenProxyObject;
 
 
//动作组数据结点
typedef  struct  actiondata_tag
{
    int actionID;
	int actionType;
	float moveSpeed;
public:
	actiondata_tag()
	{
		actionID=0;
		actionType=0;
		moveSpeed=0.0f;
	}
}ACTIONDATA,*PACTIONDATA;

 
const  unsigned char  Max_Assailant_Squence_Count=4;			 //攻击者的最大动作单元数目

 
class    CommonSkillActionProcedure: public BaseObject,public CallFunctionProtocol
{
public:
	//@技能动画流程各种状态
	enum
	{
		_SKILLACTIONPROCEDURE_UNKONW_TYPE_,				//未知技能动画流程
		_SKILLACTIONPROCEDURE_BEGINPROCEDURE_TYPE_,		//开始技能流程
		_SKILLACTIONPROCEDURE_RUNNINGPROCEDURE_TYPE_,	//运行技能流程
		_SKILLACTIONPROCEDURE_PAUSEPROCEDURE_TYPE_,		//暂停技能流程
		_SKILLACTIONPROCEDURE_ENDPROCEDURE_TYPE_,		//结束技能流程
	};

	//@技能动画的参数
	enum
	{
		_COMMONACTION_DEFAULT_PARAM_=-1,				//缺省默认的 全动作组
		_COMMONACTION_RETURN_PARAM_,				    //返回到角色初始位置
		_COOMONACTION_NORETURN_PARAM_,				    //位移到目的位置不返还
	};

	//@动作循环参数
	enum
	{
		_COMMONACTION_DEFAULTCYCLE_TYPE_=-1,			//缺省参数
		_COMMONACTION_NOTCYCLE_TYPE_,					//非循环动作指令
		_COMMONACTION_CYCLE_TYPE_,						//循环动作指令
	};
	  
    //@攻击者的动作状态序列
	enum
	{
		 _ASSAILANT_UNKONWACTION_TYPE_,					//未知  动作单元
		 _ASSAILANT_SITUACTION_TYPE_,					//原地动作流程   Key
		 _ASSAILANT_ADVANCEACTION_TYPE_,				//前进动作流程   Key
		 _ASSAILANT_TARGETACTION_TYPE_,					//目标动作流程	Key
		 _ASSAILANT_RETURNACTION_TYPE_,					//返回动作流程   Key
		 _ASSAILANT_ENDACTION_TYPE_,					//攻击者所有动作完成
	};

	//@受害者的动作状态序列
	enum
	{
		 _VICITIMS_UNKOWNACTION_TYPE_,					//未知  动作单元
		 _VICITIMS_HURTACTION_TYPE_,					//伤害动作流程
		 _VICITIMS_ENDACTION_TYPE_,						//伤害者所有动作完成
	};
	//@技能 角色类型
	enum
	{
		_SKILLS_UNKONW_ROLE_TYPE_,						//未知角色类型
		_SKILLS_ASSAILANT_ROLE_TYPE_,					//攻击者角色类型
		_SKILLS_VICTIM_ROLE_TYPE_,						//受击者角色类型
	};

	//@内部事件通知类型
	enum
	{
		_INNER_UNKONW_EVENT_TYPE_,
		_INNER_TARGET_EVENT_TYPE_,
		_INNER_RETURN_EVENT_TYPE_,
		_INNER_TIMER_HURT_EVENT_TYPE_,

	};


public:

 	CommonSkillActionProcedure();
	~CommonSkillActionProcedure();

	//@技能动画初始化
	virtual  void InitWithSkillItemProcedure(CommonSkillItemProcedure * pCommonSkillProcedure);
	
	//@技能动画资源释放
	virtual  void Destroy();

	//@技能动画的帧驱动
	virtual  void Tick();

	//@技能动画的事件通知
    virtual  void OnCommandHanlder(int EventTypeID);

	/*
	  角色动作完毕回调通知   
	  param1: 监听代理类型
	  param2: 监听附加参数
	  param3: 回调动作ID
	*/ 
	virtual   void OnCommandHanlder(int EventTypeID,std::string attachParam1,std::string attachParam2,std::string attachParam3);

	//@预处理攻击者的动作序列
	virtual  void  ToPrepareActionsSquence();

    //@开始技能动作
	virtual  void  OnBeginSkillAction();

    //@结束技能动作
	virtual  void  OnEndSkillAction();
	 
	virtual	 void  CallFunctionHandler(int eventType,void * attachParam);
	 
	virtual   void  SetSpeedScale(float speedScale);
 
protected:
	//////////////////////////////////////////////////////////////////////////
	//@重构 Assailant攻击序列
	void    DoNextAssailantActionProcess();
	void    DispatchAttachActionHandler();
	void    PlayAssailantAction();
	void    ToNextAssailantActionState();
	void	StartAttackTimer();
	void    TriggerAttachEventHandler();
	void	AssailantActionCompleteHandler(int attachParam,int actionID);
	void    VictimActionCompleteHandler(int attachParam,int actionID);
	//////////////////////////////////////////////////////////////////////////
	int     GetSkillActionsID();											//获得当前技能动画组ID
	void    InitSkillActions();											    //初始化技能动画组以及受击动作时间点
	void    InitAssailantSquenceWithSkillParam(int  skillParam=-1);		//初始施放者的动作序列

protected:
 
	int  preAssailantActionSequence[Max_Assailant_Squence_Count];   //预处理的攻击者 动作组序列
	int  curAssailantActionState;								    //当前攻击者 动作流程 的状态
	int  curVicitimsActionState;									//当前受害者 动作流程 的状态
	int  totalAssailantActionsCount;								//攻击者动作序列数
	int  curAssailantExecuteIndex;									//当前攻击者执行序列  从0 开始

	int  hadLoadAssailantActionState;							    //已经执行过得状态  上一个状态
	int  curSkillActionProcedure;						            //当前技能动画流程
  
protected:
	CommonSkillItemProcedure    * pCurrentSkillProcedure;			//当前的技能流程	
 
	HeroicRole * assailantRole;										//战斗 攻击者

	HeroicRole * vicitimsRole;									    //战斗 目标
 
	bool   isExecutorLeft;										    //技能执行者是否在左边
	bool   isVictimLeft;											//技能作用帧是否在右边
 
	int    rivalHurActionID;										//目标受击动作ID 

	int    skillHurtActionCallTime;								    //技能伤害动作触发时间点
	 
	std::map<int,ACTIONDATA>      actionDataMap; 
	 
	//////////////////////////////////////////////////////////////////////////
	ListenProxyObject *   m_pAssailantListenObj;					//攻击者的监听代理
	ListenProxyObject *   m_pVictimListenObj;						//目标者的监听代理
		  
	//////////////////////////////////////////////////////////////////////////
	VariableSpeedSequenceAction *  m_pDelayTriggerVictimAction;		//触发攻击事件动画
	VariableSpeedSequenceAction *  m_pToTargetComAction;			//前进动画
	VariableSpeedSequenceAction *  m_pToHomeComAction;				//归位动画
	 
};
#endif