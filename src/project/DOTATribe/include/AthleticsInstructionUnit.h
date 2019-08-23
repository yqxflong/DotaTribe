//Name：AtheleticsInstructionUnit
//Function：战斗指令单元
//Author:	Johny

#ifndef   _DOTATRIBE_ATHLETICSINSTRUCTIONUNIT_H
#define   _DOTATRIBE_ATHLETICSINSTRUCTIONUNIT_H

#include     "../include/AthleticProcedureDataType.h"
#include    "../include/SkillAttachLogicManager.h"
#include    <vector>


class    AthleticsInstructionUnit 
{
public:
	//@战斗单元的类型
	enum
	{
		_INSTRUCTIONUNIT_UNKOWN_TYPE_=-1,		    //未知指令类型
		_INSTRUCTIONUNIT_SKILL_TYPE_,				//技能指令
		_INSTRUCTIONUNIT_REMOVE_BUFFER_TYPE_,		//删除Buffer
		_INSTRUCTIONUNIT_REMOVE_STATE_TYPE_,		//删除State类型
		_INSTRUCTIONUNIT_LOCATION_TYPE_,			//位置属性
	};

	//@技能作用目标
	enum
	{
		_SKILLITEM_UNKONW_TYPE_=-1,
		_SKILLITEM_SELFTARGET_TYPE_,				//目标为自己
		_SKILLITEM_RIVALTARGET_TYPE_,				//目标为敌人
	};

	//@Location的指令枚举
	enum
	{
		_INSTRUCTIONUNIT_UNKONW_LOCATION_TYPE_=-1,	//位置Location指令
		_INSTRUCTIONUNIT_TOINIT_LOCATION_TYPE_,		//回到初始位置类型
		_INSTRUCTIONUNIT_TOTARGET_LOCATION_TYPE_,	//回到攻击位置类型
	};

	AthleticsInstructionUnit();
	virtual ~AthleticsInstructionUnit(){};
public:
	//@标配
	virtual void   Init(){};
	virtual void   Destroy();
	virtual void   Tick();

	//@用战斗过程指令单元数据初始化
	virtual void   InitWithConfigData(PAthleticsUnitData pAthleticsUnitData);

	//@获得战斗单元的类型
	char           GetAthleticsUnitType();

public: 
	//@技能释放者位置
	bool	  GetIsAssailantLeft(){
		return isAssailantLeft;
	};	
	//@技能作用者位置
	bool      GetIsTargetLeft(){
		return isTargetLeft;
	};						
  
	//@技能类型访问接口
	short   GetSkillItemID();							//获得技能ID					
	short   GetHurtActionID();							//获得受击动作ID
	int		GetAssailantID();							//获得攻击者的ID	
	char    GetAssailantType();							//获取攻击者的类型
	int     GetTargetID();								//获得目标者的ID 
	char    GetTargetType();							//获得目标者的类型
	char    GetSkillHitType();							//获得技能命中类型(命中 闪避 格挡等)
	short   GetCounterAttackSkillID();					//获得反击技能ID
	char    GetAttachEffectCount();			 	        //获得附加效果数目
	std::vector<PSkillAttach_Base> GetSkillAttachEffectVector();  //获得技能附加效果向量

	//@删除Buffer类型接口
	int		GetRemoveBuffer_SourceID();					//获得删除Buffer的源ID
	short   GetRemoverBuffer_EffectID();				//删除指定特效ID


	//@删除State类型接口
	int     GetRemoveState_SourceID();					//获得删除State的源ID
	char    GetRemoveState_RoleState();					//删除角色状态某个状态
 
	//@改变Location类型接口
	int     GetLocation_SourceID();						 //获得位置改变的ID
	char	GetLocation_Location();						 //获得位置属性
	bool	VerifyInstructionUnitData();				 //指令单元数据校验
  
protected:
	//@指令数据
	PAthleticsData_SKILL   pAthleticsData_Skill_;		 //技能指令数据指针
	
	PAthleticsData_Buffer  pAthleticsData_Buffer_;		 //删除buffer数据指针

	PAthleticsData_State   pAthleticsData_State_;		 //删除State数据指针

	PAthleticsData_Location pAthleticsData_Location_;	 //改变位置数据指针

	//@战斗过程指令数据
	char   curInstructionType;		 //当前指令的类型	
	short  cutInstructionID;	     //指令索引ID

	bool  isAssailantLeft;
	bool  isTargetLeft;
};

#endif

