//Name：SkillAttachLogicManager
//Function： 技能附加逻辑管理器
//Author:	Johny

#ifndef   _DOTATRIBE_SKILLATTACHLOGINMANAGER_H_
#define   _DOTATRIBE_SKILLATTACHLOGINMANAGER_H_

#include    <cocos2d.h>
#include   <include/common/Singleton.h>
#include   "../include/SkillAttachLogicProcedure.h"
#include   <map>
#include   <vector>
  
 
class  SkillAttachLogicManager:public cobra_win::Singleton2<SkillAttachLogicManager>
{
protected:
	std::map<int,SkillAttachLogicObject *> skillAttachLogicMap;   //事件队列
public:
	SkillAttachLogicManager();
	~SkillAttachLogicManager();

public:
	//@标配
	void  Init();	
	void  Destroy();
	void  Tick();

	//@Post 附加效果 指令
	bool  OnCommandHandler(int eventType,std::vector<std::string> attachParams,bool isSourceRoleLeft,bool isTargetRoleLeft);
  
public:
	SkillAttachLogicObject * GetSkillAttachLoginByType(int attachLogicType);
	int   GetHadRegisterEventCount();											//获取注册事件数目
public:
	//@性能测试接口
    long   GetManagerBlockSize();
public:
	void   RegisterSkillAttachLogic(SkillAttachLogicObject * attachLogic);     //注册事件队列
    bool   UnRegisterSkillAttachLogic(SkillAttachLogicObject * attachLogic);   //取消注册事件队列
	bool   UnRegisterSkillAttachLogic(int attachLogicType);					//取消注册事件队列		
	bool   CheckHadRegisterSkillAttachLogic(int attachLogicType);			    //检测技能附加是否已经加载
public:
	friend  class  cobra_win::Singleton2<SkillAttachLogicManager>;

};


#define   SKILLATTACHLOGICMANAGER    (SkillAttachLogicManager::get_instance2())
 

#endif