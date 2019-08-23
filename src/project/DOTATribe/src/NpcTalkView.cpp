////////////////////////////////////////////////////////////////
//Name:	 NPCTalkView
//Auchor: 	xiaobo.wu
//Func:	 NPC对话窗口
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////
#include      <cocos2d.h>
#include      "../include/NpcTalkView.h" 
#include      "../include/EventTyper.h"
#include      "../include/VariableSystem.h"
#include      "../include/DOTATribeApp.h"
#include      "../include/EventSystem.h"
#include      "../include/ResourceIDDataManager.h"
#include      "../include/InputCommand.h"
#include      "../include/UIViewDataManger.h"
#include      "../include/CPublicVarReader.h"
#include      "../include/CMenuItemSprite.h"  
#include      "../include/SysLangDataManager.h"
#include	  "../include/MaskNode.h"
#include	  "../include/NFControlsManager.h"
#include	  "../include/AthleticsWindow.h"


using  namespace  cocos2d;
using  namespace  cocos2d::extension;
using  namespace  cobra_win;



NpcTalkView::NpcTalkView()
{
	curNpcTalkState=_UNKONW_NPCTALK_TYPE_;
	pNpcTalkData=NULL;
	curTalkPageIndex=0;
	playerIconID=0;
	npcIconID=0;
	playerName="";
	npcName="";
	isFinishWithCurState=false;
	npcTalkVect.clear();
}

NpcTalkView::~NpcTalkView()
{

}

NpcTalkView * NpcTalkView::createNpcTalkView(int priority)
{
	NpcTalkView * pNpcTalkView=new NpcTalkView();
	if(pNpcTalkView&&pNpcTalkView->InitNpcTalkView(priority))
	{ 
		pNpcTalkView->autorelease();
		return pNpcTalkView;
	}
	if(pNpcTalkView!=NULL)
	{
		delete  pNpcTalkView;
		pNpcTalkView=NULL;
	}
	return pNpcTalkView;	 
}


void   NpcTalkView::SetRoleTalkName(std::string roleName)
{
	cocos2d::CCNode * pRootTalkWindow=Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_NPC_TALK_VIEW);
	if(pRootTalkWindow!=NULL)
	{ 
		cocos2d::CCLabelTTF  * pRoleNameLabel=(cocos2d::CCLabelTTF  *)pRootTalkWindow->getChildByTag(_NPC_TALK_VIEW_NAME_TAG_);
		if(pRoleNameLabel!=NULL)
		{  
			 roleName+=" :";
			 pRoleNameLabel->setString(roleName.c_str());
		}
	}
}


//设置头像Icon
void   NpcTalkView::SetRoleTalkShapeIcon(int iconID)
{
	cocos2d::CCNode * pRootTalkWindow=Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_NPC_TALK_VIEW);
	if(pRootTalkWindow!=NULL)
	{ 
		cocos2d::CCSprite * pShapeIcon=(cocos2d::CCSprite * )pRootTalkWindow->getChildByTag(_NCP_TALK_VIEW_SHAPEICON_TAG_);
		if(pShapeIcon!=NULL)
		{ 
			 pShapeIcon->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(iconID).c_str());
		}
	}
}

void   NpcTalkView::SetRoleTalkContent(std::string  talkContent)
{
	cocos2d::CCNode * pRootTalkWindow=Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_NPC_TALK_VIEW);
	if(pRootTalkWindow!=NULL)
	{
		cocos2d::CCMultiLineLabelTTF  * pContent=(cocos2d::CCMultiLineLabelTTF * )pRootTalkWindow->getChildByTag(_NPC_TALK_VIEW_CONTENT_TAG_);
		if(pContent!=NULL)
		{ 
			pContent->setString(talkContent.c_str());
		}
	}
}

void   NpcTalkView::AutoLayoutWithConfig()
{
	cocos2d::CCNode * pRootTalkWindow=Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_NPC_TALK_VIEW);
	if(pRootTalkWindow!=NULL)
	{
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kNPCTALKVIEW,pRootTalkWindow);    
		MaskNode * pMaskNode=(MaskNode *)pRootTalkWindow->getChildByTag(_NPC_TALK_VIEW_MASK_TAG_);
		if(pMaskNode!=NULL)
		{
			setOpacity(pMaskNode->GetViewData().alpha_);
		}
	}	   
}

bool  NpcTalkView::checkIsTouchInUnClose(cocos2d::CCPoint touchPoint)
{
	return false;
} 
bool  NpcTalkView::InitNpcTalkView(int priority)
{
	if(initUIBaseDialog(priority))
	{
		AutoLayoutWithConfig();
		 
	
		return true;
	}
	return false;
}

bool    NpcTalkView::ShowPageWithIndex(int pageIndex)
{
	if(pageIndex<(int)npcTalkVect.size())
	{  
		TalkNode   talknode=npcTalkVect.at(pageIndex);
		if(talknode.contentRoleType==TalkNode::_TALK_PLAYER_TYPE_)
		{
			SetRoleTalkName(playerName);
			SetRoleTalkShapeIcon(playerIconID);
			SetRoleTalkContent(SysLangDataManager::get_instance2()->GetSysLangById(talknode.contentSysID));
		}
		else if(talknode.contentRoleType==TalkNode::_TALK_NPC_TYPE_)
		{
			SetRoleTalkName(npcName);
			SetRoleTalkShapeIcon(npcIconID);
			SetRoleTalkContent(SysLangDataManager::get_instance2()->GetSysLangById(talknode.contentSysID));
		}
		return true;
	}
	return false;
}


			

bool    NpcTalkView::SetNpcTalkState(char npcTalkState,std::string pName,int pIconID,std::string nName,int nIconID)
{
	if(curNpcTalkState!=npcTalkState)
	{
		playerIconID=pIconID;
		npcIconID=nIconID;
		playerName=pName;
		npcName=nName;
		curNpcTalkState=npcTalkState;
		npcTalkVect.clear(); 
		curTalkPageIndex=0;
		if(pNpcTalkData!=NULL)
		{
			switch(curNpcTalkState)
			{
			case  _BEFOR_NPCTALK_TYPE_:
				{
					npcTalkVect=pNpcTalkData->beforBattlePageVect;
					break;
				}
			case _WIN_NPCTALK_TYPE_:
				{
					npcTalkVect=pNpcTalkData->winBattlePageVect;
					break;
				}
			case  _FAIL_NPCTALK_TYPE_:
				{
					npcTalkVect=pNpcTalkData->failBattlePageVect;
					break;
				}
			default: 
				break;
			}
			if(!npcTalkVect.empty())
			{
				//显示第一页
				ShowPageWithIndex(curTalkPageIndex);
				return true;
			}
		} 
	}  
	return false;
}
 

void    NpcTalkView::SetNpcTalkConfigData(NpcTalkData *  npcTalkData)
{
	 if(pNpcTalkData!=npcTalkData)
	 {
		 pNpcTalkData=npcTalkData;
	 }
}
bool   NpcTalkView::isFinishTalkCur()
{
    return isFinishWithCurState;
}




bool    NpcTalkView::ToNextPage(char & talkState)
{ 
	talkState=curNpcTalkState;
	if((curTalkPageIndex+1)>=(int)npcTalkVect.size())
	{
		isFinishWithCurState=true;
		return false;
	}
	else
	{
		ShowPageWithIndex(++curTalkPageIndex);
		return true;
	}
}