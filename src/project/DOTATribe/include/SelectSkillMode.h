#ifndef    _DOTATRIBE_SELECTSKILLMODE_H_
#define    _DOTATRIBE_SELECTSKILLMODE_H_

//Author: xiaobo.wu
//Description:  技能面板数据层
//Date:  2013.06.30 

#include     "../include/SelectSkillController.h"
#include     "../include/SelectSkillDataType.h"
#include      "../include/RoleSkillsDataHandler.h"
#include	 <include/common/Singleton.h>
#include     <cocos2d.h>
#include     <vector> 
 
class  SelectSkillController;
 
//选择技能数据管理层
class   SelectSkillMode
{  
	enum
	{
		_DEFAULT_SKILL_ITEMID_=-1,
	};
	enum
	{
		_SUCCESS_VALUE_FROM_SERVER_=1,
	};
public:
	SelectSkillMode();
	~SelectSkillMode();
public:
	static SelectSkillMode *  createSelectSkillModeWithController(SelectSkillController * selectSkillController);
	void   OnCommandHandler(int eventType,void * ptr);
	void   Destroy();
    

    /*
	 根据ID获得技能Icon名称
	*/
	std::string  GetSkillIconNameFromSkillID(int skillItemID);

	/*
	 更新用户装备列表
	*/
	bool   UpdateEquipSkillVectorWithID(bool isInstall,int skillItemID,int notchID=0);
 
	/*
	 更改技能凹槽的技能
	*/
	bool   ChangeEquipSkillWithID(int fromSkillItemID,int toNotchiID);
 

	/*获得内存数据中 装备技能的引用*/
	std::vector<PSkillNotoch> &  GetNotchSkillEquipVec();


	/*
	从内存中获得本地技能包
	*/
    std::vector<PSkillItem> &  GetServerSkillsDataVec();

	/*
	 初始化本地技能数据
	*/
	bool   OnUpdateLocalSkillData(bool isNeedPostUpdateUI=false);
 
protected:
	/*
	 初始数据管理
	*/
    bool   InitSelectSkillModeWithController(SelectSkillController * selectSkillController);
	
	/*
	  校验服务器数据
	*/
	bool  CheckSkillsDataFromMemory();
	 
	/*
	 从内存中获得背包技能
	*/
	bool   GetRoleSkillsFromSkillsHandler();
 
	/*
	 增加技能
	*/
	void   AddEquipSkillVectorWithID(int notchID,int skillItemID);

	/*
	 删除技能
	*/
	void   RemoveEquipSkillVectorWithID(int skillItemID);

 
	//获得激活技能组
	void   GetActiveSkillFromSkillsHandler();

	/*
	 更新背包技能
	*/
	void  UpdateRoleSkillsData();
	 
public:

    PSkillItem    GetSkillsBagInfoFromID(int skillItemID);

	PSkillNotoch  GetSkillsTargetInfoFromID(int skillItemID);
  
    PCOMMONSKILLDATA *               GetCommonSkillDataArray(); 
public:
	unsigned char m_HeroIndex;
protected:
	/*
	  本地技能Icon二维数组
	*/
	PCOMMONSKILLDATA *  pCommonSkillDataArray; 

	std::map<short,bool>   dynamicActiveSkills;
     
	/*
	 剩下的技能点
	*/
	int  curSkillPointValue;

	/*
	 角色技能包
	*/
	RoleSkillsData *			 pSkillsData;

    /*
	绑定控制器
	*/
    SelectSkillController * pSelectSkillController;
  
};





#endif