#ifndef  _DOTATRIBE_SKILLTIPSDIALOG_H_
#define  _DOTATRIBE_SKILLTIPSDIALOG_H_

////////////////////////////////////////////////////////////////
//Name:	 SkillTipsDialog
//Auchor: 	xiaobo.wu
//Func:	 技能描述对话框
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////

#include   "../include/UIBaseDialog.h"
#include   "../include/EventTyper.h"
#include   "../include/CMenuItemSprite.h"
#include	"cocos-ext.h"
 
#define   DEFAULT_SKILLICONID_   1

class    SkillTipsDialog: public  UIBaseDialog
{
public:  
	enum
	{
		_SKILL_TIPS_BG_TAG_,
		_SKILL_TIPS_SKILLNAME_TAG_,
		_SKILL_TIPS_CLOSE_BTN_TAG_,
		_SKILL_TIPS_SKILL_BG_TAG_,
		_SKILL_TIPS_SKILL_ICON_TAG_,
		_SKILL_TIPS_SKILL_DESC_BG_TAG_,
		_SKILL_TIPS_SKILL_DESC_LABEL_TAG_,
		_SKILL_TIPS_SKILL_DESC_CONTENT_TAG_,
		_SKILL_TIPS_SEGEMENT_1_TAG_,
		_SKILL_TIPS_SKILL_TRIGER_TYPE_BG_TAG_,
		_SKILL_TIPS_SKILL_TRIGER_TYPE_LABEL_TAG_,
		_SKILL_TIPS_SKILL_TRIGER_TYPE_CONTENT_TAG_,
		_SKILL_TIPS_SEGMENT_2_TAG_,
		_SKILL_TIPS_SKILL_SP_BG_TAG_,
		_SKILL_TIPS_SKILL_SP_LABEL_TAG_,
		_SKILL_TIPS_SKILL_SP_CONTENT_TAG_,
		_SKILL_TIPS_SEGMENT_3_TAG_,
		_SKILL_TIPS_TRIGER_RATE_BG_TAG_,
		_SKILL_TIPS_TRIGER_RATE_LABEL_TAG_,
		_SKILL_TIPS_TRIGER_RATE_CONTENT_TAG_,
		_SKILL_TIPS_SEGMENT_4_TAG_,
		_SKILL_TIPS_TRIGER_CONDITION_BG_TAG_,
		_SKILL_TIPS_TRIGER_CONDITION_LABEL_TAG_,
		_SKILL_TIPS_TRIGER_CONDITION_CONTENT_TAG_, 
		_SKILL_TIPS_ADEPT_SEGMENT_TAG_,
		_SKILL_TIPS_ADEPT_BG_TAG_,
		_SKILL_TIPS_ADEPT_LABEL_TAG_,
		_SKILL_TIPS_ADEPT_CONTENT_TAG_,
		 
	};
	 
	SkillTipsDialog();
	~SkillTipsDialog();
public:
   static SkillTipsDialog * createSkillTipsDialog(int priority);						//创建对话框		 

   void  setSkillName(std::string skillName);											//设置技能名称
   void  setSkillIcon(int skillIconID);												//设置技能Icon
   void  setSkillDescription(std::string skillDescription);							//设置技能描述

   void  setSkillTriggerTime(char skillType);											//设置技能触发时机
   void  setSkillSpConsume(int mpConsum);												//设置技能SP消耗
   void  setSkillAdpetDesc(std::string skillAdpetDesc,bool isAdepetSkill);		    //设置专精效果描述

   void  setSkillTriggerRate(std::string triggerRate);									//设置触发几率
   void  setSkillTriggerCondition(std::string triggerCondition);						//设置触发限制
    
protected:

   cocos2d::CCNode * GetSkillTipsRootLayer();
   bool  initSkillTipsDialog(int priority);
   void  layOutSkillTemplateDialog();
   void  InitStaticBtnMap();
   bool  checkIsTouchInUnClose(cocos2d::CCPoint touchPoint);
   void  callBackBtnClickHandler(cocos2d::CCObject *pSender);
 
private:
};


#endif