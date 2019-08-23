#include      "../include/SelectSkillWindow.h"
#include      "../include/EventTyper.h"
#include      "../include/VariableSystem.h"
#include      "../include/DOTATribeApp.h"
#include      "../include/EventSystem.h"
#include      "../include/ResourceIDDataManager.h"
#include      "../include/InputCommand.h"
#include      "../include/CPublicVarReader.h"
#include      "../include/CMenuItemSprite.h"
#include      "../include/UIBaseDialog.h"
#include      "../include/SkillTableDataManager.h"
#include	  "..//include/MainTaskDataHandler.h"
#include      "../include/IProcedure.h"
#include	  "../include/CSChangeSkillsPacket.h"
//Author: xiaobo.wu
//Description:  技能面板视图
//Date:  2013.06.30 
#include      "../include/AnimationEffect.h"
#include      "../include/AnimationFileDataManager.h"
#include      "../include/EngineSystem.h"
#include      "../include/C2SResetSkillsPacket.h"
#include	  "../include/LevelUpDataHandler.h"
#include	  "../include/RoleInfoDataHandler.h"
#include	  "../include/NFControlsManager.h"
#include	  "../include/NFAnimationController.h"
#include	  "../include/NFCCMenuFactory.h"

#include	  "../include/CSimpleActionSprite.h"
#include	  "../include/MiningDataHandler.h"

#include	  "../include/CCDragNodeLayer.h"
#include	  "../include/CCSignSprite.h"
#include	  <include/common/Random.h>
#include      <cocos2d.h>
#include      <string>

#include "../include/GuideSystem.h"

using  namespace  cocos2d;
using  namespace  cobra_win;
 
USING_NS_CC;
USING_NS_CC_EXT;


//专用选择技能内部数据
#define   EQUIP_SKILL_NODE_TAG		   100			 
#define   EQUIP_SKILL_BGNODE_TAG	   110
 
#define   _START_COMMON_SKILLIONC_ID_   10000

#define   NORMAL_NOTCHS_COUNT			5
#define   MAX_NOTCHS_COUNT				6



 
SelectSkillWindow::SelectSkillWindow()
{ 
	m_WindowType=_TYPED_WINDOW_SELECTSKILLWINDOW_;
	m_WindowZOrder = _TYPED_WINDOW_ZORDER_NORMAL_;
	pSelectSkillController=NULL;
	pSkillTipsDialog=NULL;
	preWindowType=0;
	equipSkillNotchPosVec.clear();
	canUserNotchSkillCount=NORMAL_NOTCHS_COUNT;
	pDragNodeLayer=NULL;
	nUIAdpetEffectID=getUIAdpetEffectID();
	pBaseViewNode=NULL;
	pSkillTipsViewNode=NULL; 
	nDefaultSkillTipsID=0;
	heroIndex=0;
}

SelectSkillWindow::~SelectSkillWindow()
{ 
 
}


bool  SelectSkillWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_SELECTSKILLWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_SELECTSKILLWINDOW_,true);
	RegisterEvent(_TYPED_EVENT_UPDATE_SELECTSKILLWINDOW_,true);
	RegisterEvent(_TYPED_EVENT_FADEOUT_SELECTSKILLWINDOW_,true);
	 
	RegisterEvent(_TYPED_EVENT_COMMUNICATION_TIMEOUT_,true); 
	RegisterEvent(_TYPED_EVENT_ENTERBACK_SELECTSKILLWINDOW_,true); 
	RegisterEvent(_TYPED_EVENT_UPDATE_SKILLNOTCH_SELECTWINDOW_,true); 
	RegisterEvent(_TYPED_EVENT_REFRESH_UPDATEUI_,true);
	RegisterEvent(_TYPED_EVENT_UNLOCK_SKILLNOTCH_SELECTWINDOW_,true);
	 
	  
	return IWindow::Init();
}


bool  SelectSkillWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
 			break;  

	   InitInterDataConfig();
	   LoadUIConfig();
	    
		return true;
	} 
	while (false);

	return false;
}


void    SelectSkillWindow::InitInterDataConfig()  //内部数据初始
{  
	canUserNotchSkillCount = NFC_GetHeroSkillManager()->getIsUnLockSixthSkill() ? MAX_NOTCHS_COUNT:NORMAL_NOTCHS_COUNT;
}

void  SelectSkillWindow::Tick()
{
	IWindow::Tick();
}


void   SelectSkillWindow::Destroy()
{  
	if(pDragNodeLayer)
	{
		pDragNodeLayer->removeAllData();
		pDragNodeLayer->removeFromParentAndCleanup(true);
		pDragNodeLayer=NULL;
	}
	nDefaultSkillTipsID=0;
	preWindowType=0;
	if(pSelectSkillController!=NULL)
	{ 
 		pSelectSkillController->Destroy();
		delete pSelectSkillController;
		pSelectSkillController=NULL;
	}
	if(pSkillTipsDialog!=NULL)
	{
		pSkillTipsDialog->removeAllChildrenWithCleanup(true);
		pSkillTipsDialog->removeFromParentAndCleanup(true); 
	    pSkillTipsDialog=NULL;
	}
	cocos2d::CCNode * pBaseLayer=GetViewBaseLayer();
	if(pBaseLayer!=NULL)
	{
		pBaseLayer->removeAllChildrenWithCleanup(true);
	}
	pBaseViewNode=NULL;
	pSkillTipsViewNode=NULL;
	equipSkillNotchPosVec.clear();
	IWindow::Destroy();
}


void  SelectSkillWindow::LoadUIConfig()
{
	pBaseViewNode=cocos2d::CCNode::create();
	pSkillTipsViewNode=cocos2d::CCNode::create();
    UIViewDataManager::get_instance2()->AutoCreateNodeByTable(UIViewDataManager::KSELECTSKILLVIEW,pBaseViewNode);
	m_pRootNode->addChild(pBaseViewNode,5);
	m_pRootNode->addChild(pSkillTipsViewNode,7);
	ShowResetSkillNeedInfo();  //to do
	UpdatePlayerJewleAndGold();
	InitStaticBtnMap();
	GetNotchSkillPosLayout();
    CreateSkillTipTemplateDialog();
	CreateDragControlLayer();
	 
	if(canUserNotchSkillCount!=MAX_NOTCHS_COUNT)
	{
		NFC_setNodeVisable(_SKILL_UI_SKILL_LOCK_TAG_,pBaseViewNode,true);  
		//临时使用直接锁住最后一个技能凹槽
		//封锁最后一个锁  _SKILL_UI_SKILL_LOCK_TAG_ 
	}   
	else
    NFC_setNodeVisable(_SKILL_UI_SKILL_LOCK_TAG_,pBaseViewNode,false);  
	 
}

void   SelectSkillWindow::InitStaticBtnMap()
{
	cocos2d::CCNode * pBaseLayer=GetViewBaseLayer();
	if(pBaseLayer!=NULL)
	{
		 MapBtnWithTag(pBaseLayer,_SKILL_UI_SKILL_LOCK_TAG_);
		 MapBtnWithTag(pBaseLayer,_SKILL_UI_CLOSE_BTN_TAG_);
		 MapBtnWithTag(pBaseLayer,_SKILL_UI_HELP_BTN_TAG_);
		 MapBtnWithTag(pBaseLayer,_SKILL_UI_SKILL_RESET_BTN_TAG_);
		 MapBtnWithTag(pBaseLayer,_SKILL_UI_SKILL_ADDPOINT_BTN_TAG_);
		 MapBtnWithTag(pBaseLayer,_SKILL_UI_ADDPOINT_RESET_BTN_TAG_);
		 MapBtnWithTag(pBaseLayer,_SKILL_UI_ADDPOINT_SURE_BTN_TAG_);
	}

	SetSubNodeVisibleWithTag(_SKILL_UI_ADDPOINT_RESET_BTN_TAG_,false);
	SetSubNodeVisibleWithTag(_SKILL_UI_ADDPOINT_RESET_LABEL_TAG_,false);

	SetSubNodeVisibleWithTag(_SKILL_UI_ADDPOINT_SURE_BTN_TAG_,false);
	SetSubNodeVisibleWithTag(_SKILL_UI_ADDPOINT_SURE_LABEL_TAG_,false);


	SetSubNodeVisibleWithTag(_SKILL_UI_SKILL_ADDPOINT_BTN_TAG_,false);
	SetSubNodeVisibleWithTag(_SKILL_UI_SKILL_ADDPOINT_LABEL_TAG_,false);
	
	 
}

void    SelectSkillWindow::SetSubNodeVisibleWithTag(int tag,bool isVisible)
{
	cocos2d::CCNode * pBaseLayer=GetViewBaseLayer();
	if(pBaseLayer!=NULL)
	{
		cocos2d::CCNode * pNode=(cocos2d::CCNode *)pBaseLayer->getChildByTag(tag);
		if(pNode!=NULL)
		{
			pNode->setVisible(isVisible);
		}
	}
}

void    SelectSkillWindow::RemovePreSkillsIcon()
{
	 pDragNodeLayer->removeAllData();
}

 

void   SelectSkillWindow::MapBtnWithTag(cocos2d::CCNode * pBaseLayer,int menuTag)
{
	cocos2d::CCMenu * pMenu=(cocos2d::CCMenu *)pBaseLayer->getChildByTag(menuTag);
	if(pMenu!=NULL)
	{
		CMenuItemSprite * pMenuItem=(CMenuItemSprite *)pMenu->getChildByTag(0);
		if(pMenuItem!=NULL)
		{
			pMenuItem->setIDX(menuTag);
			pMenuItem->setTarget(this,menu_selector(SelectSkillWindow::CallBackBtnClickHandler));
		}
	}
}

 

/*
获得左上第一个技能的坐标位置
*/
cocos2d::CCPoint  SelectSkillWindow::GetLeftTopSkillIconPostion()
{
   MaskNode * pFirstPositionNode=(MaskNode *)GetViewBaseLayer()->getChildByTag(_SKILL_UI_COMMON_FIRST_SKILL_TAG_);
   if(pFirstPositionNode!=NULL)
   {
	   return   ccp(pFirstPositionNode->GetViewData().posx_,pFirstPositionNode->GetViewData().posy_);
   }
   return CCPointZero;
}



/*
获得公共技能面板偏移的坐标位置
*/
cocos2d::CCSize  SelectSkillWindow::GetCommonSkillOffSetSize()
{
	 
	MaskNode * pSizeNode=(MaskNode *)GetViewBaseLayer()->getChildByTag(_SKILL_UI_COMMON_OFFSET_SKILL_TAG_);
	if(pSizeNode!=NULL)
	{
		return  CCSizeMake(pSizeNode->GetViewData().width_,pSizeNode->GetViewData().height_);
	}
	return CCSizeZero;
}



MaskNode * SelectSkillWindow::GetMaskNodeWithTag(int maskTag)
{
	MaskNode * pNode=(MaskNode *)GetViewBaseLayer()->getChildByTag(maskTag);
	return pNode;
}


cocos2d::CCPoint SelectSkillWindow::GetCommonSkillPosition(int xPos,int yPos)
{
	 cocos2d::CCPoint startPostion=GetLeftTopSkillIconPostion();
	 cocos2d::CCSize  offSize=GetCommonSkillOffSetSize();
	 return  ccp(startPostion.x+offSize.width*xPos,startPostion.y-offSize.height*yPos);
}


cocos2d::CCPoint  SelectSkillWindow::GetTargetSkillPosition(int index)
{
	int  notchCount=equipSkillNotchPosVec.size();
	if(index<notchCount)
	{
		return equipSkillNotchPosVec.at(index).position;
	}
	return CCPointZero;
}

 


void    SelectSkillWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
    if(iEventType==_TYPED_EVENT_SHOW_SELECTSKILLWINDOW_)
	{  
		std::list<std::string>::iterator iter_param=paramList.begin();
		if(iter_param!=paramList.end())
		{ 
			heroIndex=atoi(iter_param->c_str());
			++iter_param;

			preWindowType=atoi(iter_param->c_str());
			++iter_param;
			if(iter_param!=paramList.end())
			{
				nDefaultSkillTipsID=atoi(iter_param->c_str());
			}
     	}   
		if(m_pRootNode->isVisible())
		return;
		OnShowSelectSkillPanelHandler();
	}
	else if(iEventType==_TYPED_EVENT_HIDE_SELECTSKILLWINDOW_)
	{  
       
		if (!MainTaskDataHandler::get_instance2()->IsHadNextRewardItem()&&LevelUpDataHandler::get_instance2()->LevelUpDataList.empty())
			PushEvent(_TYPED_EVENT_SHOW_MISSIONMESSAGEBOX_);

		 if(preWindowType!=0&&preWindowType!=-1)
		 {
			EventSystem::get_instance2()->PushEvent(preWindowType);
		 }
		 else if(preWindowType==-1)
		 { 
		 }
		 else if(preWindowType == _TYPED_EVENT_SHOW_MINEAREAWINDOW_)
		 {			 
			 EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_MINEAREAWINDOW_, _to_event_param_(MININGDATAHANDLER->m_iBackArea));
		 }
		 else
		 {
			 EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
		 }
		 pDragNodeLayer->removeAllData();
		 Destroy();
		 return ;
	}
	else if(iEventType==_TYPED_EVENT_ENTERBACK_SELECTSKILLWINDOW_)
	{
		cocos2d::CCNode * pBaseLayer=(cocos2d::CCNode * )GetViewBaseLayer();
		if(pBaseLayer!=NULL)
		{
			if(pSelectSkillController!=NULL)
			{ 
				pSelectSkillController->onCommandHandler(_TYPED_INPUT_COMMAND_SELECTSKILLDATA_MODIFY_,NULL);
			}
		} 
		return ;
	}
	else if(iEventType==_TYPED_EVENT_UPDATE_SELECTSKILLWINDOW_)
	{
	   if(pSelectSkillController!=NULL)
	   {
		    pSelectSkillController->UpdateRoleSkillsModeData();
	   }
	   return ;
	}
	else if(iEventType==_TYPED_EVENT_UPDATE_SKILLNOTCH_SELECTWINDOW_)
	{
		if(pSelectSkillController!=NULL)
		{
			pSelectSkillController->onCommandHandler(_TYPED_INPUT_COMMAND_SELECTSKILLDATA_MODIFY_,NULL);
		}
	}
	else if(iEventType==_TYPED_EVENT_COMMUNICATION_TIMEOUT_)
	{
		//处理服务器通信超时事件
		//刷新装备技能表
		if(pSelectSkillController)
		pSelectSkillController->onCommandHandler(_TYPED_INPUT_COMMAND_SELECTSKILLDATA_MODIFY_,NULL);
		return ;
	}
	else if(iEventType==_TYPED_EVENT_REFRESH_UPDATEUI_)
	{
		UpdatePlayerJewleAndGold();
	}
	else if(iEventType ==_TYPED_EVENT_UNLOCK_SKILLNOTCH_SELECTWINDOW_)
	{
		//to do 
		UnLockSixthSkillHandler();
	}
}


//事件回调通知
void    SelectSkillWindow::BaseDialogCallBackHandler(int eventType,void * ptr)
{  

	if(eventType==_TYPED_INPUT_COMMAND_BASEDIALOG_CLOSE_)
	{
		if(pSkillTipsDialog!=NULL)
		{
			pSkillTipsDialog->setVisible(false);
			GetSkillTipsViewLayer()->setVisible(false);
		}
	}
}

void   SelectSkillWindow::OnUpdateRoleSkillsUI()
{  
}
 
 
void    SelectSkillWindow::OnShowSelectSkillPanelHandler()
{   
   pSelectSkillController=SelectSkillController::createSelectSkillController(this);
   if(pSelectSkillController)
   {  
	   pDragNodeLayer->setDragEventDelegate(pSelectSkillController);
	   pSelectSkillController->onCommandHandler(_TYPED_INPUT_COMMAND_LOADCOMMONSKILLDATA_END_,NULL);
	   pSelectSkillController->onCommandHandler(_TYPED_INPUT_COMMAND_SELECTSKILLDATA_MODIFY_,NULL);
	   Show(true);
	   ShowSkilInfoDialogFromSkillID(nDefaultSkillTipsID);
   } 
   NFC_showCommunicationWating(false);
}
 

cocos2d::CCNode *   SelectSkillWindow::GetSkillTipsViewLayer()
{
    return pSkillTipsViewNode;
}


cocos2d::CCNode *   SelectSkillWindow::GetViewBaseLayer()
{ 
   return pBaseViewNode;
}
 

void    SelectSkillWindow::CallBackBtnClickHandler(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * pMenuItem=(CMenuItemSprite *)pSender;
	if(pMenuItem!=NULL)
	{
		switch(pMenuItem->getIDX())
		{
		case _SKILL_UI_SKILL_LOCK_TAG_:
			{  
				OpenSixthSkillRequestHandler();
				CCLOG("SelectSkillWindow  CallBackBtnClickHandler !");
				break;
			}
		case  _SKILL_UI_CLOSE_BTN_TAG_:
			{
				//关闭升级界面
				EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_CLOSE_SELECTSKILLWINDOW_);
				//新手引导
				GUIDESYSTEM->Next();
				EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_HIDE_SELECTSKILLWINDOW_);
				CCLOG("_CLOSE_TAG_  ClickCallBack!");
				break;
			}
		case  _SKILL_UI_HELP_BTN_TAG_:
			{ 
				char type[128] = "";
				sprintf(type,"%d",UIViewDataManager::kSELECTSKILL_HELP_);
				PushEvent(_TYPED_EVENT_SHOW_HELPWINDOW_,type);
				CCLOG("_HELP_TAG_  ClickCallBack!");
				break;
			}
		case _SKILL_UI_SKILL_RESET_BTN_TAG_:
			{
				CCLOG("_RESET_TAG_  ClickCallBack!");
				C2SRestRoleSkillsPacket  reseSkillsPacket(heroIndex);
				reseSkillsPacket.Send();
				break;
			}
		case _SKILL_UI_SKILL_ADDPOINT_BTN_TAG_:
			{
				break;
			}

		case  _SKILL_UI_ADDPOINT_RESET_BTN_TAG_:
			{
				break;
			}
		case _SKILL_UI_ADDPOINT_SURE_BTN_TAG_:
			{
				break;
			}
		default: 
			break;
		}
	}
	  
}
 


void    SelectSkillWindow::ShowWaittingLayer()
{
	NFC_showCommunicationWating(true);
}

void    SelectSkillWindow::HideWaittingLayer()
{
	NFC_showCommunicationWating(false);
}
   
  
void    SelectSkillWindow::AddNotchSkillPosDataWithSprite(cocos2d::CCSprite * pNotchSprite)
{
	if(pNotchSprite!=NULL)
	{
		NotchPos_Data  notchPos;
		notchPos.position=pNotchSprite->getPosition();
		notchPos.touchRect=CCRectMake(pNotchSprite->getPositionX()-0.5f*pNotchSprite->getContentSize().width,pNotchSprite->getPositionY()-0.5f*pNotchSprite->getContentSize().height,
			pNotchSprite->getContentSize().width,pNotchSprite->getContentSize().height);  
		equipSkillNotchPosVec.push_back(notchPos);
	} 
}


/*
获取技能凹槽布局配置 
*/
void    SelectSkillWindow::GetNotchSkillPosLayout()
{   
	cocos2d::CCNode * pBaseLayer=(cocos2d::CCNode * )GetViewBaseLayer();
	if(pBaseLayer!=NULL)
	{
		AddNotchSkillPosDataWithSprite((cocos2d::CCSprite *)pBaseLayer->getChildByTag(_SKILL_UI_SKILL_NOTCH_BG_1_TAG_));
		AddNotchSkillPosDataWithSprite((cocos2d::CCSprite *)pBaseLayer->getChildByTag(_SKILL_UI_SKILL_NOTCH_BG_2_TAG_));
		AddNotchSkillPosDataWithSprite((cocos2d::CCSprite *)pBaseLayer->getChildByTag(_SKILL_UI_SKILL_NOTCH_BG_3_TAG_));
		AddNotchSkillPosDataWithSprite((cocos2d::CCSprite *)pBaseLayer->getChildByTag(_SKILL_UI_SKILL_NOTCH_BG_4_TAG_));
		AddNotchSkillPosDataWithSprite((cocos2d::CCSprite *)pBaseLayer->getChildByTag(_SKILL_UI_SKILL_NOTCH_BG_5_TAG_));
		AddNotchSkillPosDataWithSprite((cocos2d::CCSprite *)pBaseLayer->getChildByTag(_SKILL_UI_SKILL_NOTCH_BG_6_TAG_));   
	}
 
}

/*
清理所有装备的技能
*/
void    SelectSkillWindow::ClearAllEquipSkillNode()
{
	 pDragNodeLayer->removeAllTargetSignSprites();
	 pDragNodeLayer->removeAllTargetAttachSprite();
	 
}


//检测拖拽的技能是否在面板的凹槽上
int     SelectSkillWindow::checkTargetNotchCoverID(CCSignSprite * pDragNode)
{
	//canUserNotchSkillCount
	for(int index=0;index<MAX_NOTCH_NUM;index++)
	{
		cocos2d::CCRect notchRect=equipSkillNotchPosVec.at(index).touchRect;
        if(pDragNode->checkIsCoverWithRect(notchRect.origin.x,notchRect.origin.x+notchRect.size.width,
			notchRect.origin.y+notchRect.size.height,notchRect.origin.y))
	    {
			/*if(index==(MAX_NOTCH_NUM-1)&&canUserNotchSkillCount!=MAX_NOTCH_NUM)
			{
				OpenSixthSkillRequestHandler();
				return -1;
			}*/
			return index;
	    }
	}
    return -1;
}
 
/*
隐藏所有装备技能
*/
void    SelectSkillWindow::SetAllEquipSkillIconVisable(bool isVisible)
{
    //隐藏所有安装的技能Icon
	CCNode * pNode=NULL;
	FOR_EACH_ELEMENT_BEGIN(MAX_NOTCH_NUM)
		pNode=(CCNode *)GetViewBaseLayer()->getChildByTag(EQUIP_SKILL_BGNODE_TAG+index);
	if(pNode!=NULL)
		pNode->setVisible(isVisible); 
	pNode=(CCNode *)GetViewBaseLayer()->getChildByTag(EQUIP_SKILL_NODE_TAG+index);
	if(pNode!=NULL)
		pNode->setVisible(isVisible);
	FOR_EACH_ELEMENT_END
}

 

void   SelectSkillWindow::AddSkillPointIconLayOut(bool isLastVisible)
{ 

}
 
void   SelectSkillWindow::SetAllAddPointIconVisible(bool isVisible)
{ 

}
 
void    SelectSkillWindow::AddSkillPointWithNotchIndex(int index)
{
    
}

 
//更新CommonSkillPanel UI
void    SelectSkillWindow::UpdateCommonSkillPanelWithUserData(PCOMMONSKILLDATA * pCommonSkillData)
{    
	RemovePreSkillsIcon();
	std::vector<CCSignSprite * > columnSignArray;
	MaskNode *  skillMaskNode=GetMaskNodeWithTag(_SKILL_UI_COMMON_FIRST_SKILL_TAG_);
	MaskNode *  bgMarkConfigNode=GetMaskNodeWithTag(_SKILL_UI_SKILL_BG_SKILL_TAG_);
	MaskNode *  diableMarkNode=GetMaskNodeWithTag(_SKILL_UI_SKILL_DIABLE_BG_SKILL_TAG_);
	MaskNode *  adeptMarkNode=GetMaskNodeWithTag(_SKILL_UI_SKILL_ADPET_BG_SKILL_TAG_);
	MaskNode *  newSkillTipsMarkNode=GetMaskNodeWithTag(_SKILL_UI_SKILL_NEW_TIPS_TAG_);
	if(pCommonSkillData)
	{
		for(int i=0;i<MAX_SKILLPANEL_COLUMN;i++)
		{
			columnSignArray.clear();
			for(int j=0;j<MAX_SKILLPANEL_ROW;j++)	
			{ 
				std::string  skillIconName=ResourceIDDataManager::get_instance2()->getDataByID(pCommonSkillData[i][j].skillIconID);
				if(skillIconName.empty()) continue; 
				CCSignSprite *	 skillItemSprite=NULL;     //拖拽图标结点
				cocos2d::CCSprite * bgmarkSprite=NULL;     //背景框
				cocos2d::CCSprite * bgIconSprite=NULL;     //背景Icon  
				cocos2d::CCSprite * diableMark=NULL;	    //禁用背景
				cocos2d::CCSprite * adeptMark=NULL;        //专精背景
				//to do new Skill Tips
				CSimpleActionSprite * newSkillTips=NULL;	//新技能提示 
				if(pCommonSkillData[i][j].skillItemID==NFC_GetHeroSkillManager()->getLastActiveSkillID())
				{
					std::vector<float> attachParam ;
					attachParam.push_back(newSkillTipsMarkNode->GetViewData().width_);
					attachParam.push_back(newSkillTipsMarkNode->GetViewData().height_);
					newSkillTips= NFC_getSimpleActionSprite(newSkillTipsMarkNode->GetViewData().filepath_,newSkillTipsMarkNode->GetViewData().colorR_,attachParam);
					cocos2d::CCPoint commonPos=GetCommonSkillPosition(j,i);
					newSkillTips->SetInitPosition(ccp(commonPos.x+newSkillTipsMarkNode->GetViewData().posx_,commonPos.y+newSkillTipsMarkNode->GetViewData().posy_));
					pDragNodeLayer->addOtherAttachSprite(newSkillTips,newSkillTipsMarkNode->GetViewData().zorder_);
					newSkillTips->PlayAction();
				} 
				if(pCommonSkillData[i][j].isActiveSkill)
				{
					skillItemSprite=CCSignSprite::createCCSignSpriteWithFile(pCommonSkillData[i][j].skillItemID,skillIconName.c_str());
					if(pCommonSkillData[i][j].isAdeptSkill)    //判断是否专精
					{
						if(adeptMarkNode!=NULL)
						{
							adeptMark=NFC_getLoopFrameEffect(nUIAdpetEffectID);
						}			
					}
					bgIconSprite=cocos2d::CCSprite::create();   //背景Sprite
					bgIconSprite->setProperty("File",skillIconName);
				}
				else
				{
					skillItemSprite=CCSignSprite::createCCSignSpriteWithFile(pCommonSkillData[i][j].skillItemID,
						skillIconName.c_str(),_SIGNSPRITE_COMMON_TYPE_,false);
				    if(diableMarkNode!=NULL)
					{
						 diableMark=cocos2d::CCSprite::create();
						 diableMark->setProperty("File",diableMarkNode->GetViewData().filepath_);
					} 
				}
				columnSignArray.push_back(skillItemSprite);
				//背景图标
				if(bgMarkConfigNode!=NULL)
				{
					bgmarkSprite=cocos2d::CCSprite::create();
					bgmarkSprite->setProperty("File",bgMarkConfigNode->GetViewData().filepath_);
				} 

				if(bgmarkSprite!=NULL)
				{
					bgmarkSprite->setPosition(GetCommonSkillPosition(j,i));
					pDragNodeLayer->addOtherAttachSprite(bgmarkSprite,bgMarkConfigNode->GetViewData().zorder_); 
				}
 
				if(bgIconSprite!=NULL)
				{
					bgIconSprite->setPosition(GetCommonSkillPosition(j,i));
					pDragNodeLayer->addOtherAttachSprite(bgIconSprite,skillMaskNode->GetViewData().zorder_); 
				} 
				if(adeptMark!=NULL)
				{
					adeptMark->setPosition(GetCommonSkillPosition(j,i));
					pDragNodeLayer->addOtherAttachSprite(adeptMark,adeptMarkNode->GetViewData().zorder_); 
				}
				skillItemSprite->setInitPosition(GetCommonSkillPosition(j,i));
		 
				if(diableMark!=NULL)
				{
					diableMark->setPosition(GetCommonSkillPosition(j,i));
					pDragNodeLayer->addOtherAttachSprite(diableMark,diableMarkNode->GetViewData().zorder_); 

				}
			}
			pDragNodeLayer->addSignSpriteVector(columnSignArray,skillMaskNode->GetViewData().zorder_);
		} 
	}
	NFC_showCommunicationWating(false);

}

//更新装备技能栏UI
void    SelectSkillWindow::UpdateEquipSkillPanelWithUserData(std::vector<PSkillNotoch> &  userEquipSkillData)
{ 
   //删除当前装备的技能
   ClearAllEquipSkillNode();

   size_t  equipDataCount=userEquipSkillData.size();
   MaskNode *  skillMaskNode=GetMaskNodeWithTag(_SKILL_UI_COMMON_FIRST_SKILL_TAG_);
   for(size_t index=0;index<equipDataCount;index++)
   { 
	    if(userEquipSkillData.at(index)->skillID>0)
		{
			std::string skillIconName=ResourceIDDataManager::get_instance2()->getDataByID(userEquipSkillData.at(index)->skillIconID);
			cocos2d::CCSprite * bgSprite=cocos2d::CCSprite::create();
			bgSprite->setProperty("File",skillIconName);
			CCSignSprite * pDragNode=CCSignSprite::createCCSignSpriteWithFile(userEquipSkillData.at(index)->skillID,skillIconName.c_str(),_SIGNSPRITE_TARGET_TYPE_,true);
			pDragNode->setInitPosition(GetTargetSkillPosition(index));  
			bgSprite->setPosition(GetTargetSkillPosition(index));
			pDragNodeLayer->addTargetAttachSprite(bgSprite,skillMaskNode->GetViewData().zorder_);
			pDragNodeLayer->addTargetSignSprite(pDragNode,skillMaskNode->GetViewData().zorder_);
		}
   } 
}
 

 

/*
创建技能tips模板
*/
void    SelectSkillWindow::CreateSkillTipTemplateDialog()
{
	pSkillTipsDialog=SkillTipsDialog::createSkillTipsDialog(UIBaseDialog::_UIBASEDIALOG_NORMAL_PRIORITY_);
	pSkillTipsDialog->setDelegatePrototy(this);
	if(GetSkillTipsViewLayer()!=NULL)
	{
		GetSkillTipsViewLayer()->addChild(pSkillTipsDialog);
		pSkillTipsDialog->setVisible(false);
		GetSkillTipsViewLayer()->setVisible(false);
	}
}
 


//显示指定技能的信息面板
/*
 param 1  技能ID
 param 2  是否为背包技能
*/
void    SelectSkillWindow::ShowSkilInfoDialogFromSkillID(int skillItemID,bool isCommondSkill/* =true */)
{ 
	//======如果在新手引导中，则跳过======//
	if (GUIDESYSTEM->IsNeedGuide())
		return;
	//======如果在新手引导中，则跳过======//
   if(isCommondSkill)
   {
		SkillTableData * pSkillTableData=SkillTableDataManager::get_instance2()->GetSkillTableDataByID(skillItemID);
		if(pSkillTableData!=NULL&&pSelectSkillController!=NULL)
		{
			PSkillItem pSkillItem=pSelectSkillController->GetSkillsBagInfoFromID(skillItemID);
			if(pSkillItem!=NULL)
			{
				pSkillTipsDialog->setSkillName(pSkillTableData->GetSkillItemName());
				pSkillTipsDialog->setSkillIcon(pSkillItem->skillIconID);
				pSkillTipsDialog->setSkillDescription(pSkillItem->skillDescription.c_str());
				pSkillTipsDialog->setSkillAdpetDesc(pSkillItem->skillDescription2.c_str(),pSkillItem->ispro > 0 ? true : false);
				pSkillTipsDialog->setSkillTriggerTime(pSkillItem->skillType); 
				pSkillTipsDialog->setSkillSpConsume(pSkillItem->mpConsumer);
				pSkillTipsDialog->setSkillTriggerRate(pSkillItem->skillTriggerRate);
				pSkillTipsDialog->setSkillTriggerCondition(pSkillItem->skillTriggerCondition);
				pSkillTipsDialog->setVisible(true);
				GetSkillTipsViewLayer()->setVisible(true);
			}
		}
   }
   else
   {
	   SkillTableData * pSkillTableData=SkillTableDataManager::get_instance2()->GetSkillTableDataByID(skillItemID);
	   if(pSkillTableData!=NULL&&pSelectSkillController!=NULL)
	   {
		   PSkillNotoch pSkillItem=pSelectSkillController->GetSkillsTargetInfoFromID(skillItemID);
		   if(pSkillItem!=NULL)
		   {
			   pSkillTipsDialog->setSkillName(pSkillTableData->GetSkillItemName());
			   pSkillTipsDialog->setSkillIcon(skillItemID);
			   pSkillTipsDialog->setSkillDescription(pSkillItem->pSkillDescNode->description.c_str());
			   pSkillTipsDialog->setSkillAdpetDesc(pSkillItem->pSkillDescNode->skillDescription2.c_str(),pSkillItem->pSkillDescNode->ispro > 0 ? true : false);
			   pSkillTipsDialog->setSkillTriggerTime(pSkillItem->pSkillDescNode->skillType);
			   pSkillTipsDialog->setSkillSpConsume(pSkillItem->pSkillDescNode->mpConsumer);
			   pSkillTipsDialog->setSkillTriggerRate(pSkillItem->pSkillDescNode->skillTriggerRate);
			   pSkillTipsDialog->setSkillTriggerCondition(pSkillItem->pSkillDescNode->skillTriggerCondition);
			   pSkillTipsDialog->setVisible(true);
			   GetSkillTipsViewLayer()->setVisible(true);
		   }
	   }
   }
   
}


void    SelectSkillWindow::CreateDragControlLayer()
{  
	pDragNodeLayer=CCDragNodeLayer::createDragNodeLayer(); 
	MaskNode *  adeptMarkNode=GetMaskNodeWithTag(_SKILL_UI_SKILL_SEGMENT_HEIGHT_TAG_);
	pDragNodeLayer->setDefaultTargetSegmentHeight(adeptMarkNode->GetViewData().height_);
	GetViewBaseLayer()->addChild(pDragNodeLayer,adeptMarkNode->GetViewData().zorder_,_SKILL_UI_SKILL_ROOT_TAG_);
}
 

void	SelectSkillWindow::UpdatePlayerJewleAndGold()
{ 
	/*
	 更新人物的金钱和钻石
	*/
	NFC_setLabelStringInt(_SKILL_UI_SKILL_JEWEL_LABEL_TAG_,GetViewBaseLayer(),RoleInfoDataHandler::get_instance2()->m_pRIData->jewels_);
	NFC_setLabelStringInt(_SKILL_UI_SKILL_GOLD_LABEL_TAG_,GetViewBaseLayer(),RoleInfoDataHandler::get_instance2()->m_pRIData->money_);
 
}
 

void	SelectSkillWindow::ShowResetSkillNeedInfo()
{ 
	NFC_setLabelStringInt(_SKILL_UI_SKILL_NEED_JEWLE_NUM_TAG_,GetViewBaseLayer(),10);
}


void    SelectSkillWindow::OpenSixthSkillRequestHandler()
{ 
	NFC_showCommunicationWating_2(true);
	CSUnLockSkillPacket unlockPacket(NORMAL_NOTCHS_COUNT);
	unlockPacket.Send();
}

void    SelectSkillWindow::UnLockSixthSkillHandler()
{ 
	if(NFC_GetHeroSkillManager()->getIsUnLockSixthSkill())
	{
		canUserNotchSkillCount = MAX_NOTCHS_COUNT;
		NFC_setNodeVisable(_SKILL_UI_SKILL_LOCK_TAG_,GetViewBaseLayer(),false);
	}
	else
	{
		canUserNotchSkillCount = NORMAL_NOTCHS_COUNT;
		NFC_setNodeVisable(_SKILL_UI_SKILL_LOCK_TAG_,GetViewBaseLayer(),true);
	} 
}
