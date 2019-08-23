//Name：SkillAttachLogicProcedure
//Function： 技能附加逻辑处理单元
//Author:	Johny

#ifndef   _DOTATRIBE_SKILLATTACHPROCEDURE_H
#define   _DOTATRIBE_SKILLATTACHPROCEDURE_H

#include	"../include/BaseObject.h"
#include    "../include/AthleticProcedureDataType.h"
#include	 <cocos2d.h>
#include     <vector>
#include     <string>

  

//@数值显示格式
enum
{
	_HPDAMAGE_NUMBERICALFONT_FORMATID_=1,     //减血
	_HPHEAL_NUMBERICALFONT_FORMATID_,		  //加血
	_BAOJI_NUMBERICALFONT_FOAMATID_,		  //暴击
	_MPHEAL_NUMBERICALFONT_FORMATID_,         //回蓝
	_MPDAMAGE_NUMBERICALFONT_FORMATID_,       //减蓝
	_HITNOTE_NUMBERICALFONT_FORMATID_=8,	  //命中旁白
};



//@技能附加逻辑类的基类
class   SkillAttachLogicObject :public BaseObject
{ 
public:
	SkillAttachLogicObject();
	virtual ~SkillAttachLogicObject();
public:
	virtual   void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft)=0;
	virtual   void Tick();
	virtual   void Destroy();
};


//@技能附加效果1  给Source附加伤害
class  SkillAttachLogicSourceHPDamage :public SkillAttachLogicObject
{    
public:
    SkillAttachLogicSourceHPDamage();
	~SkillAttachLogicSourceHPDamage();
public:
    virtual   void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};


//@技能附加效果 给Source附加回血
class  SkillAttachLogicSourceHPHeal: public SkillAttachLogicObject
{
public:
	SkillAttachLogicSourceHPHeal();
	~SkillAttachLogicSourceHPHeal();
public:
	virtual   void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};


//@给Source MP 伤害
class  SkillAttachLogicSourceMPDamage: public SkillAttachLogicObject
{
public:
	SkillAttachLogicSourceMPDamage();
	~SkillAttachLogicSourceMPDamage();
public:
	virtual   void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};

//@给Source MP 回蓝
class  SkillAttachLogicSourceMPHeal: public SkillAttachLogicObject
{
public:
	SkillAttachLogicSourceMPHeal();
	~SkillAttachLogicSourceMPHeal();
public:
	virtual   void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};


//@给Targer HP伤害
class  SkillAttachLogicTargetHPDamage: public SkillAttachLogicObject
{
public:
	SkillAttachLogicTargetHPDamage();
	~SkillAttachLogicTargetHPDamage();
public:
	virtual   void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};

//@给Targer HP 回血
class  SkillAttachLogicTargetHPHeal: public SkillAttachLogicObject
{
public:
	SkillAttachLogicTargetHPHeal();
	~SkillAttachLogicTargetHPHeal();
public:
	virtual   void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};



//@给Targer MP 伤害
class  SkillAttachLogicTargetMPDamage: public SkillAttachLogicObject
{
public:
	SkillAttachLogicTargetMPDamage();
	~SkillAttachLogicTargetMPDamage();
public:
	virtual   void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};


//@给Targer MP 回蓝
class  SkillAttachLogicTargetMPHeal: public SkillAttachLogicObject
{
public:
	SkillAttachLogicTargetMPHeal();
	~SkillAttachLogicTargetMPHeal();
public:
	virtual   void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};




//@变身附加效果
class   SkillAttachLogicChangeShape:  public SkillAttachLogicObject
{
public:
    SkillAttachLogicChangeShape();
    ~SkillAttachLogicChangeShape();
public:
	virtual   void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};


 
//@添加状态
class   SkillAttachLogicAddState:  public SkillAttachLogicObject
{
public:
	SkillAttachLogicAddState();
	~SkillAttachLogicAddState();
public:
	virtual   void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};



//@删除状态
class   SkillAttachLogicRemoveState:  public SkillAttachLogicObject
{
public:
	SkillAttachLogicRemoveState();
	~SkillAttachLogicRemoveState();
public:
	virtual   void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};


//@添加Buffer或者Effect
class   SkillAttachLogicAddBuffer:  public SkillAttachLogicObject
{
public:
	SkillAttachLogicAddBuffer();
	~SkillAttachLogicAddBuffer();
public:
	virtual   void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};



//@删除Buffer或者Effect
class  SkillAttachLogicRemoveBuffer: public SkillAttachLogicObject
{
public:
	SkillAttachLogicRemoveBuffer();
	~SkillAttachLogicRemoveBuffer();
public:
	virtual   void  OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};
 

//@技能扣蓝
class   SkillAttachLogicReduceMP: public SkillAttachLogicObject
{
public:
	SkillAttachLogicReduceMP();
	~SkillAttachLogicReduceMP();
public:
	virtual  void  OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};
 
 
//@复活血量
class  SkillAttachLogicReliveUpdateHP: public SkillAttachLogicObject
{
public:
	SkillAttachLogicReliveUpdateHP();
	~SkillAttachLogicReliveUpdateHP();
public:
	virtual  void  OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};

//@复活蓝量
class  SkillAttachLogicReliveUpdateMP: public SkillAttachLogicObject
{
public:
	SkillAttachLogicReliveUpdateMP();
	~SkillAttachLogicReliveUpdateMP();
public:
	virtual void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};


//@命中类型旁注通知
class  SkillAttachLogicHitNote: public SkillAttachLogicObject
{
public:
	SkillAttachLogicHitNote();
	~SkillAttachLogicHitNote();
public:
	virtual void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};
 

#endif