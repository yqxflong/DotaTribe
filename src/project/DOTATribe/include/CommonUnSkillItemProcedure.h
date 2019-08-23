//Name：CommonUnSkillItemProcedure
//Function：非技能指令流程(添加非技能公共流程 若侦测到角色死亡，等待死亡动作完成后离开)
//Author:	Johny

#ifndef   _DOTATRIBE_COMMONUNSKILLITEMPROCEDURE_H_
#define   _DOTATRIBE_COMMONUNSKILLITEMPROCEDURE_H_

#include  "../include/BaseObject.h"
#include   "../include/AthleticProcedureDataType.h"

class  HeroicRole;

class  CommonUnSkillItemProcedure: BaseObject
{
public:
	 enum
	 {
		 _UNSKILLPROCEDURE_UNKONW_STATE_=-1,		//未知流程状态
		 _UNSKILLPROCEDURE_BEGIN_STATE_,			//开始非技能流程
		 _UNSKILLPROCEDURE_RUNNING_STATE_,			//运行中状态
		 _UNSKILLPROCEDURE_NULL_STATE_,				//基本非技能流程
		 _UNSKILLPROCEDURE_EXCEPTION_DEAD_STATE_,	//处理异常死亡流程
		 _UNSKILLPROCEDURE_END_STATE_,				//结束非技能流程
	 };

	 enum
	 {
		 _UNSKILLPROCEDURE_UNKONW_TYPE_=-1,
		 _UNSKILLPROCEDURE_NUMBERICAL_TYPE_,	//非技能数字特效流程
		 _UNSKILLPROCEDURE_REMOVE_BUFFER_TYPE_,	//移除Buffer特效流程 
		 _UNSKILLPROCEDURE_BRING_TYPE_,		    //暂时 用不到复活流程  放在最后
	 };
  
	 CommonUnSkillItemProcedure();
	 virtual ~CommonUnSkillItemProcedure();
public:
	static  CommonUnSkillItemProcedure *  CreateCommonUnSkillItemProcedure(PAthleticsUnitData pAthleticsUnitData);
public:
	//@标配
	virtual   void   Tick();
	virtual   void   Destroy();

	//@指令接收处理
	virtual   void   OnCommandHanlder(int EventTypeID){}; 
	virtual   void	 OnCommandHanlder(int EventTypeID,std::string attachParam);
	virtual   void   OnBeginUnSkillProcedure();
	virtual   void   OnEndUnSkillProcedure();
	virtual   bool   OnCheckProcedureFinished();
	virtual   void   OnCheckRoleIsDead();
protected:
	virtual   bool   InitCommonUnSkillItemProcedure(PAthleticsUnitData pAthleticsUnitData);
	void      SetSubObjectTypeID(int subObjectID);
	void      SetObjectIsValid(bool isValid); 
	void      UnRegisterSkeletonCompleteEventHandler();
	bool      CheckRoleExceptionEvent(bool isLeftRole);
	void      ThrowExceptionEvent(HeroicRole * pHeroicRole,bool isPlayAnimation=true);
protected:
	int   curProcedureState;
	bool  hadPlayedRoleDead;
	bool  bIsLeftRoleDead;
	PAthleticsUnitData  m_pAthleticsUnitData;
	HeroicRole   * m_pExceptionRole;
 
}; 

#endif