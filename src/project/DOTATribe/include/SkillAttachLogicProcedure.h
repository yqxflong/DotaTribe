//Name��SkillAttachLogicProcedure
//Function�� ���ܸ����߼�����Ԫ
//Author:	Johny

#ifndef   _DOTATRIBE_SKILLATTACHPROCEDURE_H
#define   _DOTATRIBE_SKILLATTACHPROCEDURE_H

#include	"../include/BaseObject.h"
#include    "../include/AthleticProcedureDataType.h"
#include	 <cocos2d.h>
#include     <vector>
#include     <string>

  

//@��ֵ��ʾ��ʽ
enum
{
	_HPDAMAGE_NUMBERICALFONT_FORMATID_=1,     //��Ѫ
	_HPHEAL_NUMBERICALFONT_FORMATID_,		  //��Ѫ
	_BAOJI_NUMBERICALFONT_FOAMATID_,		  //����
	_MPHEAL_NUMBERICALFONT_FORMATID_,         //����
	_MPDAMAGE_NUMBERICALFONT_FORMATID_,       //����
	_HITNOTE_NUMBERICALFONT_FORMATID_=8,	  //�����԰�
};



//@���ܸ����߼���Ļ���
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


//@���ܸ���Ч��1  ��Source�����˺�
class  SkillAttachLogicSourceHPDamage :public SkillAttachLogicObject
{    
public:
    SkillAttachLogicSourceHPDamage();
	~SkillAttachLogicSourceHPDamage();
public:
    virtual   void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};


//@���ܸ���Ч�� ��Source���ӻ�Ѫ
class  SkillAttachLogicSourceHPHeal: public SkillAttachLogicObject
{
public:
	SkillAttachLogicSourceHPHeal();
	~SkillAttachLogicSourceHPHeal();
public:
	virtual   void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};


//@��Source MP �˺�
class  SkillAttachLogicSourceMPDamage: public SkillAttachLogicObject
{
public:
	SkillAttachLogicSourceMPDamage();
	~SkillAttachLogicSourceMPDamage();
public:
	virtual   void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};

//@��Source MP ����
class  SkillAttachLogicSourceMPHeal: public SkillAttachLogicObject
{
public:
	SkillAttachLogicSourceMPHeal();
	~SkillAttachLogicSourceMPHeal();
public:
	virtual   void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};


//@��Targer HP�˺�
class  SkillAttachLogicTargetHPDamage: public SkillAttachLogicObject
{
public:
	SkillAttachLogicTargetHPDamage();
	~SkillAttachLogicTargetHPDamage();
public:
	virtual   void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};

//@��Targer HP ��Ѫ
class  SkillAttachLogicTargetHPHeal: public SkillAttachLogicObject
{
public:
	SkillAttachLogicTargetHPHeal();
	~SkillAttachLogicTargetHPHeal();
public:
	virtual   void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};



//@��Targer MP �˺�
class  SkillAttachLogicTargetMPDamage: public SkillAttachLogicObject
{
public:
	SkillAttachLogicTargetMPDamage();
	~SkillAttachLogicTargetMPDamage();
public:
	virtual   void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};


//@��Targer MP ����
class  SkillAttachLogicTargetMPHeal: public SkillAttachLogicObject
{
public:
	SkillAttachLogicTargetMPHeal();
	~SkillAttachLogicTargetMPHeal();
public:
	virtual   void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};




//@������Ч��
class   SkillAttachLogicChangeShape:  public SkillAttachLogicObject
{
public:
    SkillAttachLogicChangeShape();
    ~SkillAttachLogicChangeShape();
public:
	virtual   void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};


 
//@���״̬
class   SkillAttachLogicAddState:  public SkillAttachLogicObject
{
public:
	SkillAttachLogicAddState();
	~SkillAttachLogicAddState();
public:
	virtual   void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};



//@ɾ��״̬
class   SkillAttachLogicRemoveState:  public SkillAttachLogicObject
{
public:
	SkillAttachLogicRemoveState();
	~SkillAttachLogicRemoveState();
public:
	virtual   void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};


//@���Buffer����Effect
class   SkillAttachLogicAddBuffer:  public SkillAttachLogicObject
{
public:
	SkillAttachLogicAddBuffer();
	~SkillAttachLogicAddBuffer();
public:
	virtual   void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};



//@ɾ��Buffer����Effect
class  SkillAttachLogicRemoveBuffer: public SkillAttachLogicObject
{
public:
	SkillAttachLogicRemoveBuffer();
	~SkillAttachLogicRemoveBuffer();
public:
	virtual   void  OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};
 

//@���ܿ���
class   SkillAttachLogicReduceMP: public SkillAttachLogicObject
{
public:
	SkillAttachLogicReduceMP();
	~SkillAttachLogicReduceMP();
public:
	virtual  void  OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};
 
 
//@����Ѫ��
class  SkillAttachLogicReliveUpdateHP: public SkillAttachLogicObject
{
public:
	SkillAttachLogicReliveUpdateHP();
	~SkillAttachLogicReliveUpdateHP();
public:
	virtual  void  OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};

//@��������
class  SkillAttachLogicReliveUpdateMP: public SkillAttachLogicObject
{
public:
	SkillAttachLogicReliveUpdateMP();
	~SkillAttachLogicReliveUpdateMP();
public:
	virtual void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};


//@����������ע֪ͨ
class  SkillAttachLogicHitNote: public SkillAttachLogicObject
{
public:
	SkillAttachLogicHitNote();
	~SkillAttachLogicHitNote();
public:
	virtual void OnCommandHanlder(std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
};
 

#endif