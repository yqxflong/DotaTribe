//Name：UnSkillNumbericProcedure
//Function： 非技能指令 数值动画流程
//Author:	Johny

#ifndef    _DOTATRIBE_UNSKILLNUMBERICALPROCEDURE_H_
#define    _DOTATRIBE_UNSKILLNUMBERICALPROCEDURE_H_

#include   "../include/CommonUnSkillItemProcedure.h"
#include   "../include/AthleticProcedureDataType.h"

            
class   UnSkillNumbericalProcedure: public CommonUnSkillItemProcedure
{
public:
	UnSkillNumbericalProcedure();
	~UnSkillNumbericalProcedure();
public: 
	static UnSkillNumbericalProcedure * CreateCommonUnSkillItemProcedure(PAthleticsUnitData pAthleticsUnitData);
	virtual   void   Tick();
	virtual   void   Destroy();
	virtual   void   OnBeginUnSkillProcedure();
	virtual   void   OnEndUnSkillProcedure();
	virtual   bool   OnCheckProcedureFinished();
   	virtual   bool   InitCommonUnSkillItemProcedure(PAthleticsUnitData pAthleticsUnitData);
};
 
#endif