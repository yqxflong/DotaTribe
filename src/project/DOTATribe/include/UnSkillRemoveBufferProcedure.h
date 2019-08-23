//Name：UnSkillNumbericProcedure
//Function： 非技能移除Buffer (延迟移除)
//Author:	Johny

#ifndef  _DOTATRIBE_UNSKILLREMOVEBUFFERPROCEDURE_H_
#define  _DOTATRIBE_UNSKILLREMOVEBUFFERPROCEDURE_H_

#include   <cocos2d.h>
#include   "../include/CommonUnSkillItemProcedure.h"
#include   "../include/AutoFadeOutLable.h"
  
class   UnSkillRemoveBufferProcedure: public CommonUnSkillItemProcedure,public AutoDelayProtocol
{
public:
	UnSkillRemoveBufferProcedure();
	~UnSkillRemoveBufferProcedure();
public: 
	static UnSkillRemoveBufferProcedure * CreateCommonUnSkillItemProcedure(PAthleticsUnitData pAthleticsUnitData);
	virtual   void   Tick();
	virtual   void   Destroy();
	virtual   void   OnBeginUnSkillProcedure();					 //为了提速因此暂时废弃Tick中调用BeginUnSkill
	virtual   void   OnEndUnSkillProcedure();
	virtual   bool   OnCheckProcedureFinished();
	virtual   void   OnCheckRoleIsDead();
	virtual   bool   InitCommonUnSkillItemProcedure(PAthleticsUnitData pAthleticsUnitData);
	virtual   void   SetSpeedScale(float speedScale);
	virtual   void   autoDelayEventHandler(int eventType,void * pSender);
protected:
	//@内部事件分发处理器
	void   OnDispatchEventHandler();
	//@移除特效处理
	void   OnRemoveEffectHandler();
	//@移除状态处理
	void   OnRemoveStateHandler();
private:
	AutoDelayAnimation *  m_pAutoDelayAnimation;
	PAthleticsUnitData    m_pAthleticsUnitData;
	bool				  m_bHadTriggerCall;
};

#endif