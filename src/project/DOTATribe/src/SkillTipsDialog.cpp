////////////////////////////////////////////////////////////////
//Name:	 SkillTipsDialog
//Auchor: 	xiaobo.wu
//Func:	 技能描述对话框
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////

#include      <cocos2d.h>
#include      "../include/IWindow.h"
#include      "../include/SkillTipsDialog.h"
#include      "../include/SelectSkillWindow.h"
#include      "../include/EventTyper.h" 
#include      "../include/DOTATribeApp.h"
#include      "../include/EventSystem.h"
#include      "../include/InputCommand.h"
#include      "../include/ResourceIDDataManager.h"
#include      "../include/CPublicVarReader.h"
#include      "../include/CMenuItemSprite.h" 
#include      "../include/SkillTableDataManager.h"
#include      "../include/SysLangDataManager.h"
#include      "../include/WindowManager.h"
#include      "../include/NFControlsManager.h"


using  namespace  cocos2d; 
using  namespace  cobra_win;
  

SkillTipsDialog::SkillTipsDialog()
{ 
	 
}

SkillTipsDialog::~SkillTipsDialog()
{
	UIViewDataManager::get_instance2()->clearData();
}

SkillTipsDialog *   SkillTipsDialog::createSkillTipsDialog(int priority)
{ 
	SkillTipsDialog * pSkillTipsDialog=new SkillTipsDialog();
	if(pSkillTipsDialog&&pSkillTipsDialog->initSkillTipsDialog(priority))
	{
		pSkillTipsDialog->autorelease();
		return pSkillTipsDialog;
	}
	if(pSkillTipsDialog!=NULL)
	{
		 delete pSkillTipsDialog;
		 pSkillTipsDialog=NULL;
	}
	return NULL;
}
bool  SkillTipsDialog::initSkillTipsDialog(int priority)
{
	if(initUIBaseDialog(priority))
	{
		layOutSkillTemplateDialog();
		return true;
	}
	return false;
}
  

void  SkillTipsDialog::setSkillName(std::string skillName) 							    //设置技能名称
{
	cocos2d::CCNode * pSkillTipsRootLayer=GetSkillTipsRootLayer();
	cocos2d::CCSingleLineLabelTTF * skillNameLabel=(cocos2d::CCSingleLineLabelTTF *)pSkillTipsRootLayer->getChildByTag(_SKILL_TIPS_SKILLNAME_TAG_);
	if(skillNameLabel!=NULL)
	{
          skillNameLabel->setString(skillName.c_str());
	}
  
}
void  SkillTipsDialog::setSkillIcon(int skillIconID) 										//设置技能Icon
{ 
	cocos2d::CCNode * pSkillTipsRootLayer=GetSkillTipsRootLayer(); 
	if(pSkillTipsRootLayer!=NULL)
	{
		std::string  skillName=ResourceIDDataManager::get_instance2()->getDataByID(skillIconID);
		if(!skillName.empty())
		{			
		   cocos2d::CCSprite * skillIcon=(cocos2d::CCSprite *)pSkillTipsRootLayer->getChildByTag(_SKILL_TIPS_SKILL_ICON_TAG_);
		   if(skillIcon!=NULL)
		   {
		      skillIcon->setProperty("File",skillName.c_str());
		   }  
		}
	}
}
void  SkillTipsDialog::setSkillDescription(std::string skillDescription) 					//设置技能描述
{
	cocos2d::CCNode * pSkillTipsRootLayer=GetSkillTipsRootLayer();
	cocos2d::CCMultiLineLabelTTF * skillDescriptionLabel=(cocos2d::CCMultiLineLabelTTF *)pSkillTipsRootLayer->getChildByTag(_SKILL_TIPS_SKILL_DESC_CONTENT_TAG_);
	if(skillDescriptionLabel!=NULL)
	{
		skillDescriptionLabel->setString(skillDescription.c_str());
	}
}

void  SkillTipsDialog::setSkillTriggerTime(char skillType)							    	//设置技能触发时机[开场，追加 ...]
{ 
	cocos2d::CCNode * pSkillTipsRootLayer=GetSkillTipsRootLayer();
	cocos2d::CCSingleLineLabelTTF * skillTriggerTime=(cocos2d::CCSingleLineLabelTTF *)pSkillTipsRootLayer->getChildByTag(_SKILL_TIPS_SKILL_TRIGER_TYPE_CONTENT_TAG_);
	if(skillTriggerTime!=NULL)
	{
		switch(skillType)
		{ 
		case  -1:
			skillTriggerTime->setString(SysLangDataManager::get_instance2()->GetSysLangById(340).c_str());
			break;
		case  0:
			skillTriggerTime->setString(SysLangDataManager::get_instance2()->GetSysLangById(341).c_str());
			break;
		case  1:
			skillTriggerTime->setString(SysLangDataManager::get_instance2()->GetSysLangById(342).c_str());
			break;
		case  2:
			skillTriggerTime->setString(SysLangDataManager::get_instance2()->GetSysLangById(343).c_str());
			break;
		case  3:
			skillTriggerTime->setString(SysLangDataManager::get_instance2()->GetSysLangById(344).c_str());
			break;
		case  4:
			skillTriggerTime->setString(SysLangDataManager::get_instance2()->GetSysLangById(345).c_str());
			break;
		case  5:
			skillTriggerTime->setString(SysLangDataManager::get_instance2()->GetSysLangById(346).c_str());
			break;
		case  6:
			skillTriggerTime->setString(SysLangDataManager::get_instance2()->GetSysLangById(347).c_str());
			break;
		case  7:
			skillTriggerTime->setString(SysLangDataManager::get_instance2()->GetSysLangById(348).c_str());
			break;
		case  8:
			skillTriggerTime->setString(SysLangDataManager::get_instance2()->GetSysLangById(350).c_str());
			break;
		case  9:
			skillTriggerTime->setString(SysLangDataManager::get_instance2()->GetSysLangById(350).c_str());
			break;
		case  10:
			skillTriggerTime->setString(SysLangDataManager::get_instance2()->GetSysLangById(351).c_str());
			break;
		case  11:
			skillTriggerTime->setString(SysLangDataManager::get_instance2()->GetSysLangById(352).c_str());
			break;
		case  12:
			skillTriggerTime->setString(SysLangDataManager::get_instance2()->GetSysLangById(346).c_str());
			break;
		case  13:
			skillTriggerTime->setString(SysLangDataManager::get_instance2()->GetSysLangById(345).c_str());
			break;
		case  14:
			skillTriggerTime->setString(SysLangDataManager::get_instance2()->GetSysLangById(348).c_str());
			break;
		case  15:
			skillTriggerTime->setString(SysLangDataManager::get_instance2()->GetSysLangById(348).c_str());
			break;
		default:
			break;
		}
	}
}


void  SkillTipsDialog::setSkillSpConsume(int mpConsum) 									    //设置技能SP消耗
{
	cocos2d::CCNode * pSkillTipsRootLayer=GetSkillTipsRootLayer();
	cocos2d::CCSingleLineLabelTTF * skillSPConsume=(cocos2d::CCSingleLineLabelTTF *)pSkillTipsRootLayer->getChildByTag(_SKILL_TIPS_SKILL_SP_CONTENT_TAG_);
	if(skillSPConsume!=NULL)
	{
		char strValue[32]={0};
		sprintf(strValue,"%d ",mpConsum);
		strcat(strValue,SysLangDataManager::get_instance2()->GetSysLangById(211).c_str());
		skillSPConsume->setString(strValue);
	}
}

void  SkillTipsDialog::setSkillAdpetDesc(std::string skillAdpetDesc,bool isAdepetSkill)			    //设置专精效果描述
{
	cocos2d::CCNode * pSkillTipsRootLayer=GetSkillTipsRootLayer();
	if(!isAdepetSkill)
	{
		NFC_setNodeVisable(_SKILL_TIPS_ADEPT_SEGMENT_TAG_,pSkillTipsRootLayer,true);
		NFC_setNodeVisable(_SKILL_TIPS_ADEPT_BG_TAG_,pSkillTipsRootLayer,true);
		NFC_setNodeVisable(_SKILL_TIPS_ADEPT_LABEL_TAG_,pSkillTipsRootLayer,true);
		NFC_setNodeVisable(_SKILL_TIPS_ADEPT_CONTENT_TAG_,pSkillTipsRootLayer,true);
		cocos2d::CCSingleLineLabelTTF * skillApetDesc=(cocos2d::CCSingleLineLabelTTF *)pSkillTipsRootLayer->getChildByTag(_SKILL_TIPS_ADEPT_CONTENT_TAG_);
		if(skillApetDesc)
		{
			skillApetDesc->setString(skillAdpetDesc.c_str());
		}
	}
	else
	{
		NFC_setNodeVisable(_SKILL_TIPS_ADEPT_SEGMENT_TAG_,pSkillTipsRootLayer,false);
		NFC_setNodeVisable(_SKILL_TIPS_ADEPT_BG_TAG_,pSkillTipsRootLayer,false);
		NFC_setNodeVisable(_SKILL_TIPS_ADEPT_LABEL_TAG_,pSkillTipsRootLayer,false);
		NFC_setNodeVisable(_SKILL_TIPS_ADEPT_CONTENT_TAG_,pSkillTipsRootLayer,false);
	} 
}  

void  SkillTipsDialog::setSkillTriggerRate(std::string triggerRate) 				    //设置触发几率
{
	cocos2d::CCNode * pSkillTipsRootLayer=GetSkillTipsRootLayer();
	cocos2d::CCSingleLineLabelTTF * skillTriggerRate=(cocos2d::CCSingleLineLabelTTF *)pSkillTipsRootLayer->getChildByTag(_SKILL_TIPS_TRIGER_RATE_CONTENT_TAG_);
	if(skillTriggerRate!=NULL)
	{
		skillTriggerRate->setString(triggerRate.c_str());
	}

}
void  SkillTipsDialog::setSkillTriggerCondition(std::string triggerCondition) 			//设置触发限制
{
	cocos2d::CCNode * pSkillTipsRootLayer=GetSkillTipsRootLayer();
	cocos2d::CCSingleLineLabelTTF * trigerCondition=(cocos2d::CCSingleLineLabelTTF *)pSkillTipsRootLayer->getChildByTag(_SKILL_TIPS_TRIGER_CONDITION_CONTENT_TAG_);
	if(trigerCondition!=NULL)
	{
		trigerCondition->setString(triggerCondition.c_str());
	}
}


void  SkillTipsDialog::callBackBtnClickHandler(cocos2d::CCObject *pSender)
{
	if(pDelegate_!=NULL)
    pDelegate_->BaseDialogCallBackHandler(_TYPED_INPUT_COMMAND_BASEDIALOG_CLOSE_,NULL);
}

void  SkillTipsDialog::InitStaticBtnMap()
{  
	cocos2d::CCNode * pSkillTipsRootLayer=GetSkillTipsRootLayer();
	if(pSkillTipsRootLayer!=NULL)
	{
		cocos2d::CCMenu * pMenu=(cocos2d::CCMenu *)pSkillTipsRootLayer->getChildByTag(_SKILL_TIPS_CLOSE_BTN_TAG_);
		if(pMenu!=NULL)
		{
			CMenuItemSprite * pMenuItem=(CMenuItemSprite *)pMenu->getChildByTag(0);
			if(pMenuItem!=NULL)
			{
				pMenuItem->setIDX(_SKILL_TIPS_CLOSE_BTN_TAG_);
				pMenuItem->setTarget(this,menu_selector(SkillTipsDialog::callBackBtnClickHandler));
			}
		}
	}
	
}

bool  SkillTipsDialog::checkIsTouchInUnClose(cocos2d::CCPoint touchPoint)
{
	return false;
}

cocos2d::CCNode * SkillTipsDialog::GetSkillTipsRootLayer()
{  
	SelectSkillWindow * pSelectSkillWindow=(SelectSkillWindow *)WindowManager::get_instance2()->GetWindowByType(IWindow::_TYPED_WINDOW_SELECTSKILLWINDOW_);
	return pSelectSkillWindow->GetSkillTipsViewLayer();
}



/*
 创建空技能Tips模板
*/
void  SkillTipsDialog::layOutSkillTemplateDialog()		
{     
	cocos2d::CCNode * pSkillTipsRootLayer=GetSkillTipsRootLayer();
	if(pSkillTipsRootLayer!=NULL)
	{
		UIViewDataManager::get_instance2()->AutoCreateNodeByTable(UIViewDataManager::KSKILLTIPSVIEW,pSkillTipsRootLayer); 
		InitStaticBtnMap();
	}
	
}


