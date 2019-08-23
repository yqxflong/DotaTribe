//Name： RoleSkillsDataHandler
//Function：管理英雄的技能
//Author：Johny

#ifndef   _DOTATRIBE_ROLESKILLSDATAHANDLER_H_ 
#define   _DOTATRIBE_ROLESKILLSDATAHANDLER_H_

#include   <vector>
#include   <string>
#include   <include/mem/DPacket.h>
#include   <include/common/Singleton.h>
#include   "../include/IDataHandler.h" 
#include   "../include/CPublicVarReader.h"

#define    FOR_EACH_SKILL_BEGIN(count)  for(size_t index=0;index<count;index++)  {
#define    FOR_EACH_SKILL_END           }
 
enum{
	rtSKILLITEM,
	rtSKILLNOTOUCH,
};

typedef struct skillItem_tag
{
	short skillID;						 //技能ID
	int   skillIconID;					 //技能Icon
	char  skillType;					 //技能触发时机类型
	int   mpConsumer;					 //SP消耗
	char  ispro;						 //是否专精技能  0 否 1 是
	std::string  skillDescription;       //技能描述
	std::string  skillDescription2;		 //技能描述2 (非专精时候显示)
	std::string  skillTriggerRate;       //技能触发几率
	std::string  skillTriggerCondition;  //技能触发限制
	char  isActive;						 //是否激活
public:
	skillItem_tag()
	{
		skillID=0;
		skillIconID=0;
		skillType=0;
		mpConsumer=0;
		ispro=0; 
		isActive=0;
		skillDescription="";
		skillDescription2="";
		skillTriggerRate="";
		skillTriggerCondition="";
	}
	void decodePacketData(cobra_win::DPacket & packet);
	void decodeSyncPacketData(cobra_win::DPacket & packet);

}SkillItem,*PSkillItem;



typedef struct  skill_desc_node_tag
{
	char  skillType;                    //技能类型
	int   mpConsumer;			        //SP销毁
	char  ispro;				        //是否专精 
	std::string  description;	        //技能描述
	std::string  skillDescription2;	    //技能描述2 (非专精时候显示)
	std::string  skillTriggerRate;      //技能触发几率
	std::string  skillTriggerCondition; //技能触发限制
public:
	skill_desc_node_tag()
	{
		skillType=0;
		mpConsumer=0;
		ispro=0; 
		description="";
		skillDescription2="";
		skillTriggerRate="";
		skillTriggerCondition="";
	}
	void decodePacketData(cobra_win::DPacket & packet);

}Skill_Desc_Node,*PSkill_Desc_Node;



typedef  struct  skillnotouch_tag
{
	char	 index;
	char	 level;
	short	 skillID;
	int      skillIconID;
	PSkill_Desc_Node  pSkillDescNode;
public:
	skillnotouch_tag()
	{
		index=0;
		level=0;
		skillID=-1;
		skillIconID=0;
		pSkillDescNode=NULL;
	}
	~skillnotouch_tag()
	{
		if(pSkillDescNode!=NULL)
		{
			delete  pSkillDescNode;
			pSkillDescNode=NULL;
		}
		pSkillDescNode=NULL; 
	}

	void decodePacketData(cobra_win::DPacket & packet);

	void decodeSyncNotchPacket(cobra_win::DPacket & packet);
	 
	void copyFromBgSkillItem(PSkillItem pSkillItem);

}SkillNotouch,*PSkillNotoch;

 
class  RoleSkillsData
{
public:
	short  skillItemCount;
	std::vector<PSkillItem>   skillBagList;   //技能背包
	char  skillNotouchCount;
	std::vector<PSkillNotoch> skillNotchList; //技能凹槽
	//@
	RoleSkillsData()
	{
		skillItemCount=0;
		skillBagList.clear();
		skillNotouchCount=0;
		skillNotchList.clear();
	}
	~RoleSkillsData()
	{
	   size_t skillCount=skillBagList.size();
       FOR_EACH_SKILL_BEGIN(skillCount)
		   delete  skillBagList.at(index);
	   FOR_EACH_SKILL_END
	   skillBagList.clear();
	   skillItemCount=0;

	   skillCount=skillNotchList.size();
	   FOR_EACH_SKILL_BEGIN(skillCount)
		   delete  skillNotchList.at(index);
	   FOR_EACH_SKILL_END
	   skillNotchList.clear();
	   skillNotouchCount=0;
 	}
};
 

class   RoleSkillsDataHandler: public IDataHandler
{
	default_construct_vdestroy(RoleSkillsDataHandler)
	property_unit_ronly(RoleSkillsData *,m_pRoleSkillsData,RoleSkillsData)
	property_unit_ronly(bool,m_bIsUnLockSixthSkill,IsUnLockSixthSkill)

public:
    //////////////////////////////////////////////////////////////////////////
	virtual void handlePacket(IPacket* packet);  
	/*
		销毁接口
	*/
	virtual void onDestroy();
	/*
		初始化接口
	*/
	virtual bool init(); 
	//////////////////////////////////////////////////////////////////////////
	/*
	清空角色技能数据
	*/
	bool   ReInitSkillsData();

	/*
	设置最后激活技能ID
	*/
	void setLastActiveSkillID(int newActiveSkillID);
	/*
	重置最新技能
	*/
	void resetLastActiveSkillID();
	/*
	获取当前最新技能图标ID
	*/
	int getLastActiveSkillID();
	 
	/*
	获取技能内存数据
	*/
	PSkillItem   getSkillItemInfoByID(int skillID);
public:
	/*
	解析角色技能信息
	*/
	void    decodeRoleSkillsPacket(cobra_win::DPacket & packet);
	/*
	解析同步技能信息
	*/
	void    decodeSyncSkillItemPacket(cobra_win::DPacket & packet);
	/*
	解析同步技能凹槽
	*/
	void    decodeSyncSkillNotchItemPacket(cobra_win::DPacket & packet);
	/*
	解析技能凹槽变动
	*/
	void    decodeSynSkillNotchsChangePacket(cobra_win::DPacket & packet);
	/*
	同步角色解锁第六格技能
	*/
	void    decodeSynUnLockSixthSkill(cobra_win::DPacket & packet);

private:
	/*
	销毁内存数据
	*/
	void    destroyMemData();
private:
	int     m_nLastActiveSkillID; 
};
 
#endif