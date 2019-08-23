////////////////////////////////////////////////////////////////
//Name:	 SelectSkillControler
//Auchor: 	xiaobo.wu
//Func:	 技能选择控制器
//Maintainer: 	xiaobo.wu
//date:  2013.06.30 
////////////////////////////////////////////////////////////////
#include   <cocos2d.h>
#include   "../include/SelectSkillController.h"
#include   "../include/SkillTableDataManager.h"
#include   "../include/ResourceIDDataManager.h"
#include   "../include/EventTyper.h"
#include   "../include/VariableSystem.h"
#include   "../include/DOTATribeApp.h"
#include   "../include/EventSystem.h"
#include   "../include/InputCommand.h"
#include   "../include/SkillTableDataManager.h"
#include   "../include/ResourceIDDataManager.h"
#include   "../include/CCSignSprite.h"
#include    "../include/GuideSystem.h"
 
using  namespace  cocos2d;
using  namespace  cobra_win;

#define  _GUIDE_SKILL_NOTCH_INDEX_   1				//新手引导技能凹槽索引ID 0开始
#define  _MAX_SKILL_NOTCH_NUM_		 6				//最大技能凹槽个数

 
SelectSkillController::SelectSkillController()
{  
	  pSelectSkillMode_=NULL;
      pSelectSkillWindow_=NULL;
	  curSkillContollerState_=_SKILLCONTROLLER_UNKONW_STATE_;
	  m_heroIndex = 0;
}

SelectSkillController::~SelectSkillController()
{
	CCLOG("SelectSkillController Destroy!");
	Destroy();
}


SelectSkillController *  SelectSkillController::createSelectSkillController(SelectSkillWindow * pSelectSkillWindow)
{
    SelectSkillController * pSelectSkillController=new SelectSkillController();
	pSelectSkillController->m_heroIndex = pSelectSkillWindow->heroIndex;
	if(pSelectSkillController&&pSelectSkillController->initSelectSkillController(pSelectSkillWindow))
	{ 
		return pSelectSkillController;
	}
	return NULL;
}

bool  SelectSkillController::initSelectSkillController(SelectSkillWindow * pSelectSkillWindow)
{ 
	//初始化数据管理器
	pSelectSkillMode_=SelectSkillMode::createSelectSkillModeWithController(this);

	if(pSelectSkillWindow!=NULL)
	{
		pSelectSkillWindow_=pSelectSkillWindow;
	}
    return true;
}


/*
拖拽事件通知
*/
bool	SelectSkillController::delegateDragEndEventHandler(int eventType,CCSignSprite * pSignSprite,cocos2d::CCPoint & touchPoint)
{
	if(eventType==CCDragLayerProtocol::_CLICK_DRAG_END_TYPE_)
	{  
		pSignSprite->forceToInitPosition(); 
		pSelectSkillWindow_->ShowSkilInfoDialogFromSkillID(pSignSprite->getSingleTouchUniqueID());
	}
	else if(eventType==CCDragLayerProtocol::_OTHER_DRAG_END_TYPE_)
	{ 
		if(pSignSprite->getDragNodeType()==_SIGNSPRITE_COMMON_TYPE_)
		{
			equipSkillToSkillNotch(pSelectSkillWindow_->checkTargetNotchCoverID(pSignSprite),pSignSprite->getSingleTouchUniqueID());
			pSignSprite->forceToInitPosition();  //强制设置回初始位置
		}
		else if(pSignSprite->getDragNodeType()==_SIGNSPRITE_TARGET_TYPE_)
		{
			int tmpValue=pSelectSkillWindow_->checkTargetNotchCoverID(pSignSprite);
			if(tmpValue!=_UIDRAGNODE_DEFAULT_VALUE_)
			{
				//选中凹槽
				if(!changeEquipSkillToOtherNotch(tmpValue,pSignSprite->getSingleTouchUniqueID()))
				{
					pSignSprite->forceToInitPosition();  //强制设置回初始位置
					return true;
				}
			}
			else
			{ 
				removeEquipSkillWithID(pSignSprite->getSingleTouchUniqueID());   //删除装备技能
				return true;
			}
		}
	}
   	 return true;
}

 

//事件通知接口
void  SelectSkillController::onCommandHandler(int eventType,void * ptr)
{ 
	if(eventType==_TYPED_INPUT_COMMAND_LOADCOMMONSKILLDATA_END_)
	{
		//加载面板数据完成通知
		pSelectSkillWindow_->UpdateCommonSkillPanelWithUserData(pSelectSkillMode_->GetCommonSkillDataArray());
	}
	else if(eventType==_TYPED_INPUT_COMMAND_SELECTSKILLDATA_MODIFY_)
	{
		//装备数据修改更新UI通知 
        pSelectSkillWindow_->UpdateEquipSkillPanelWithUserData(pSelectSkillMode_->GetNotchSkillEquipVec());
	}
 
}

void  SelectSkillController::Destroy()
{
    if(pSelectSkillMode_!=NULL)
	{
		pSelectSkillMode_->Destroy();
		delete  pSelectSkillMode_;
		pSelectSkillMode_=NULL;
	}
}


void    SelectSkillController::UpdateRoleSkillsModeData()
{
	if(pSelectSkillMode_!=NULL)
	{
		pSelectSkillMode_->OnUpdateLocalSkillData(true);
	}
}

 

std::string SelectSkillController::GetSkillIconNameFromSkillID(int skillItemID)
{
	if(pSelectSkillMode_!=NULL)
	return pSelectSkillMode_->GetSkillIconNameFromSkillID(skillItemID);

	return "";
}

PSkillItem    SelectSkillController::GetSkillsBagInfoFromID(int skillItemID)
{
	if(pSelectSkillMode_!=NULL)
		return pSelectSkillMode_->GetSkillsBagInfoFromID(skillItemID);
	return NULL;
}

PSkillNotoch  SelectSkillController::GetSkillsTargetInfoFromID(int skillItemID)
{

	if(pSelectSkillMode_!=NULL)
		return pSelectSkillMode_->GetSkillsTargetInfoFromID(skillItemID);
	return NULL;

}


 
void    SelectSkillController::closeBtnCallBackHandler(cocos2d::CCObject * pSender)
{
	EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_HIDE_SELECTSKILLWINDOW_);
}



/*
关闭技能信息面板
*/

void	SelectSkillController::closeSkillInfoDialogCallBackHandler(cocos2d::CCObject * pSender)
{
  
}




/*
 安装技能到指定notch
*/
void   SelectSkillController::equipSkillToSkillNotch(int skillNotchIndex,int sourceTargeSkillID)
{  
   if(skillNotchIndex>=0&&skillNotchIndex<_MAX_SKILL_NOTCH_NUM_)
   {
	   if(GUIDESYSTEM->IsNeedGuide()&&skillNotchIndex!=_GUIDE_SKILL_NOTCH_INDEX_)
	    return ;
	   if (skillNotchIndex==_GUIDE_SKILL_NOTCH_INDEX_)
		   GUIDESYSTEM->Next();
	   pSelectSkillMode_->UpdateEquipSkillVectorWithID(true,sourceTargeSkillID,skillNotchIndex);    
   }
}


//交换技能槽
//param 1 凹槽ID
//param 2 技能ID
 
bool  SelectSkillController::changeEquipSkillToOtherNotch(int skillNotchIndex,int skillItemID)
{
    if(skillNotchIndex>=0&&skillNotchIndex<_MAX_SKILL_NOTCH_NUM_)
	{
		return pSelectSkillMode_->ChangeEquipSkillWithID(skillItemID,skillNotchIndex);    
	}
	return false;
}
 

void   SelectSkillController::removeEquipSkillWithID(int skillItemID)
{
   pSelectSkillMode_->UpdateEquipSkillVectorWithID(false,skillItemID);    
}

 
 