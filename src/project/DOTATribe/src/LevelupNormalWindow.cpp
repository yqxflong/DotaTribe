// Name :		LevelupNormalWindow.h
// Function:	角色升级窗口
// Author :		zhoushaonan
// PS: 新功能开启升级，新技能升级与普通升级

#include "../include/LevelupNormalWindow.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/SkillTableDataManager.h"
#include "../include/ResourceIDDataManager.h"
#include "../include/SoundSystem.h"
#include "../include/NFControlsManager.h"
#include "../include/NFAnimationController.h"
#include "../include/MissionDataHandler.h"
#include "../include/MainTaskDataHandler.h"
#include "../include/GuideSystem.h"
#include "../include/PopWindowManager.h"
#include "../include/HomeProcedure.h"

using  namespace  cocos2d;

LevelupNormalWindow::LevelupNormalWindow()
{
	m_WindowType = _TYPED_WINDOW_LEVELUPNORMAL_;
	m_pLabel= NULL;
	m_Layer1 = NULL;
	m_Layer2 = NULL;
	m_Layer3 = NULL;
	m_Layer4 = NULL;
	pAdpetEffect2 = NULL;
	pAdpetEffect3 = NULL;
	m_functionID = -1;
	m_newSkillID = -1;
	m_nUiAdpetEffectID=getUIAdpetEffectID();
	m_subType = -1;
}

LevelupNormalWindow::~LevelupNormalWindow()
{

}

bool LevelupNormalWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_LEVELUPNORMALWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_LEVELUPNORMALWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_CLOSE_SELECTSKILLWINDOW_,true);
	RegisterEvent(_TYPED_EVENT_UPDATE_LEVELUPNORMALWINDOW_);
	

	//设置该弹窗的优先级
	IPopWindow::priority_=GetPriorityByCurWindowDef(POP_PRIORITY_ROLE_LVUP);
	return IWindow::Init();
}

bool LevelupNormalWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		
		return true;
	} 
	while (false);

	return false;
}

void LevelupNormalWindow::Tick()
{
	IWindow::Tick();
}

void LevelupNormalWindow::Destroy()
{
	//
	PopWindowDidHide();
	//
	m_functionID = -1;
	m_newSkillID = -1;
	if(LevelUpDataHandler::get_instance2()->m_showIsNeed)
		LevelUpDataHandler::get_instance2()->m_showFlag =true;

	if (m_pLabel)
	{
		m_pLabel->removeFromParentAndCleanup(true);
		m_pLabel= NULL;
	}
	if (pAdpetEffect2)
	{
		pAdpetEffect2->removeFromParentAndCleanup(true);
		pAdpetEffect2= NULL;
	}
	if (pAdpetEffect3)
	{
		pAdpetEffect3->removeFromParentAndCleanup(true);
		pAdpetEffect3= NULL;
	}

	IWindow::Destroy();
}

//需要子类继承并重写
void LevelupNormalWindow::ShowPopWindow(){
	IPopWindow::ShowPopWindow();
	ShowWindow();
}

void LevelupNormalWindow::PopWindowDidHide(){
	IPopWindow::PopWindowDidHide();
}

void LevelupNormalWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_LEVELUPNORMALWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_LEVELUPNORMALWINDOW_)
	{
		Destroy();
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_LEVELUPNORMALWINDOW_)
	{
		OnUpdateUITextEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_CLOSE_SELECTSKILLWINDOW_)
	{
		OnSureButtonClick(NULL);
	}
}

void LevelupNormalWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	if( paramList.size()>0){
		std::list<std::string>::iterator it = paramList.begin();
		int indexid;
		sscanf((*it).c_str(), "%d", &indexid);
		m_subType = indexid;
	}	
	PopWindowManager::get_instance2()->AddPopWindow(this);
}

	/*
		展示自己的窗口
	*/
void LevelupNormalWindow::ShowWindow(){
	InitLayerout();
	SetLayerInfo();
	SetFunctionImage();
	ShowSelfRoot(true);
	Show(true);
	NFC_Action_fallDown(SetLvArtFont());
	SetFunctionId();
	SetNewSkillId();
	DeleteUsedLvUpData();
	//===================新手引导===============
	if (MissionDataHandler::get_instance2()->getCurMissionID()==1&&MissionDataHandler::get_instance2()->getCurStatesID()<=3)
		GUIDESYSTEM->RestoreGuide();
}

void LevelupNormalWindow::SetFunctionId()
{
	LevelUpData* pData = LevelUpDataHandler::get_instance2()->LevelUpDataList[0];
	m_functionID = pData->functionID;
}

void LevelupNormalWindow::SetNewSkillId()
{
	LevelUpData* pData = LevelUpDataHandler::get_instance2()->LevelUpDataList[0];
	if (pData->skill1 != -1)
		m_newSkillID = pData->skill1;
	else
		m_newSkillID = pData->skill2;
}

int  LevelupNormalWindow::GetType(LevelUpData* pData)
{
	if (pData->functionID != -1)
	{
		return LvUp_Type4;
	}
	else if (pData->skill1 == -1 && pData->skill2 == -1 && pData->professionalskill == -1)
	{
		return LvUp_Type1;
	}
	else if(pData->skill1 == -1)
	{
		if (pData->skill2 != -1 && pData->professionalskill != -1)
			return LvUp_Type3;
		else
			return LvUp_Type2;
	}
	else if (pData->skill2 == -1)
	{
		if (pData->skill1 != -1 && pData->professionalskill != -1)
			return LvUp_Type3;
		else
			return LvUp_Type2;
	}
	else if (pData->professionalskill == -1)
	{
		if (pData->skill1 != -1 && pData->skill2 != -1)
			return LvUp_Type3;
		else
			return LvUp_Type2;
	}
	return LvUp_TypeUnknow;
}

void LevelupNormalWindow::ShowSelfRoot(bool flag)
{
	m_Root->setVisible(flag);
}

CCNode* LevelupNormalWindow::SetLvArtFont()
{
	LevelUpData* pData = LevelUpDataHandler::get_instance2()->LevelUpDataList[0];
	int lv = pData->lv;
	int type = GetType(pData);

	if (m_pLabel)
	{
		m_pLabel->removeFromParentAndCleanup(true);
		m_pLabel= NULL;
	}

	if (type == LvUp_Type1)
	{
		_uckSetLayerLv(lv ,m_Layer1,LvUp_Type1LvValue);
		return m_Layer1;
	}
	else if(type == LvUp_Type2)
	{
		_uckSetLayerLv(lv ,m_Layer2,LvUp_Type2LvValue);
		return m_Layer2;
	}
	else if(type == LvUp_Type3)
	{
		_uckSetLayerLv(lv ,m_Layer3,LvUp_Type3LvValue);
		return m_Layer3;
	}
	else if(type == LvUp_Type4)
	{
		_uckSetLayerLv(lv ,m_Layer4,LvUp_Type4LvValue);
		return m_Layer4;
	}
	else
	{
		return NULL;
	}
	
}

CCNode* LevelupNormalWindow::SetShowLayer(int type)
{
	if (type == LvUp_Type1)
	{
		m_Layer1->setVisible(true);
		m_Layer2->setVisible(false);
		m_Layer3->setVisible(false);
		m_Layer4->setVisible(false);
		return m_Layer1;
	}
	else if(type == LvUp_Type2)
	{
		m_Layer1->setVisible(false);
		m_Layer2->setVisible(true);
		m_Layer3->setVisible(false);
		m_Layer4->setVisible(false);
		return m_Layer2;
	}
	else if(type == LvUp_Type3)
	{
		m_Layer1->setVisible(false);
		m_Layer2->setVisible(false);
		m_Layer3->setVisible(true);
		m_Layer4->setVisible(false);
		return m_Layer3;
	}
	else if(type == LvUp_Type4)
	{
		m_Layer1->setVisible(false);
		m_Layer2->setVisible(false);
		m_Layer3->setVisible(false);
		m_Layer4->setVisible(true);
		return m_Layer4;
	}
	else
	{
		return NULL;
	}
}

void LevelupNormalWindow::InitLayerout()
{
	_uckCreateLayerout();
	_uckCreateLayer();
}

void LevelupNormalWindow::SetLayerInfo()
{
	LevelUpData* pData = LevelUpDataHandler::get_instance2()->LevelUpDataList[0];
	int type = GetType(pData);
	CCNode* pShowLayer = SetShowLayer(type);
		
	switch(type)
	{
	case LvUp_Type1:
		break;
	case LvUp_Type2:
		{
			if (pData->skill1!=-1)
			{
				_uckSetSkillName(m_Layer2,LvUp_Type2SkillLabel,false);
				_uckSetSkillBG(m_Layer2,LvUp_Type2SkillBG,false);
				_uckSetSkillImage(m_Layer2,LvUp_Type2SkillImage,pData->skill1);
		
			}
			else if(pData->skill2!=-1)
			{ 
				_uckSetSkillName(m_Layer2,LvUp_Type2SkillLabel,false);
				_uckSetSkillBG(m_Layer2,LvUp_Type2SkillBG,false);
				_uckSetSkillImage(m_Layer2,LvUp_Type2SkillImage,pData->skill2);
			}
			else
			{
				_uckSetSkillName(m_Layer2,LvUp_Type2SkillLabel,true);
				_uckSetSkillBG(m_Layer2,LvUp_Type2SkillBG,true);
				_uckSetSkillImage(m_Layer2,LvUp_Type2SkillImage,pData->professionalskill);
			}
			break;
		}
	case LvUp_Type3:
		{
			if (pData->skill1!=-1)
			{
				_uckSetSkillName(m_Layer3,LvUp_Type3Skill1Label,false);
				_uckSetSkillBG(m_Layer3,LvUp_Type3Skill1BG,false);
				_uckSetSkillImage(m_Layer3,LvUp_Type3Skill1Image,pData->skill1);		
			}			
			else
			{
				_uckSetSkillName(m_Layer3,LvUp_Type3Skill1Label,false);
				_uckSetSkillBG(m_Layer3,LvUp_Type3Skill1BG,false);
				_uckSetSkillImage(m_Layer3,LvUp_Type3Skill1Image,pData->skill2);		
			}
			
			{
				_uckSetSkillName(m_Layer3,LvUp_Type3Skill2Label,true);
				_uckSetSkillBG(m_Layer3,LvUp_Type3Skill2BG,true);
				_uckSetSkillImage(m_Layer3,LvUp_Type3Skill2Image,pData->professionalskill);				
			}
			break;
		}
	case LvUp_Type4:
		{
			int i = 0;
			if(pData->skill1 != -1)
			{//有技能1
				_uckSetSkillName(m_Layer4,LvUp_Type4Skill1Label + 3 * i, false);
				_uckSetSkillBG(m_Layer4,LvUp_Type4Skill1BG + 3 * i, false);
				_uckSetSkillImage(m_Layer4,LvUp_Type4Skill1Image + 3 * i, pData->skill1);
				i++;
			}
			if(pData->skill2 != -1)
			{//有技能2
				_uckSetSkillName(m_Layer4,LvUp_Type4Skill1Label + 3 * i, false);
				_uckSetSkillBG(m_Layer4,LvUp_Type4Skill1BG + 3 * i, false);
				_uckSetSkillImage(m_Layer4,LvUp_Type4Skill1Image + 3 * i, pData->skill2);
				i++;
			}
			if(pData->professionalskill != -1)
			{
				_uckSetSkillName(m_Layer4,LvUp_Type4Skill1Label + 3 * i, true);
				_uckSetSkillBG(m_Layer4,LvUp_Type4Skill1BG + 3 * i, true);
				_uckSetSkillImage(m_Layer4,LvUp_Type4Skill1Image + 3 * i, pData->professionalskill);
				i++;
			}
			for(; i < 2; ++i)
			{
				NFC_showNode(LvUp_Type4Skill1Label + 3 * i, m_Layer4, false);
				NFC_showNode(LvUp_Type4Skill1BG + 3 * i,m_Layer4, true);
				NFC_showNode(LvUp_Type4Skill1Image + 3 * i, m_Layer4,pData->professionalskill);
			}


// 			if (pData->skill1!=-1)
// 			{
// 				_uckSetSkillName(m_Layer4,LvUp_Type4Skill1Label,false);
// 				_uckSetSkillBG(m_Layer4,LvUp_Type4Skill1BG,false);
// 				_uckSetSkillImage(m_Layer4,LvUp_Type4Skill1Image,pData->skill1);		
// 			}			
// 			else
// 			{
// 				_uckSetSkillName(m_Layer4,LvUp_Type4Skill1Label,false);
// 				_uckSetSkillBG(m_Layer4,LvUp_Type4Skill1BG,false);
// 				_uckSetSkillImage(m_Layer4,LvUp_Type4Skill1Image,pData->skill2);		
// 			}
// 
// 			{
// 				_uckSetSkillName(m_Layer4,LvUp_Type4Skill2Label,true);
// 				_uckSetSkillBG(m_Layer4,LvUp_Type4Skill2BG,true);
// 				_uckSetSkillImage(m_Layer4,LvUp_Type4Skill2Image,pData->professionalskill);				
// 			}
			break;
		}
	}
}

void LevelupNormalWindow::SetFunctionImage()
{
	LevelUpData* pData = LevelUpDataHandler::get_instance2()->LevelUpDataList[0];
	if (pData->functionID != -1)
	{
		CCSprite* pFunction = (CCSprite*)m_Layer4->getChildByTag(LvUp_Type4FunctionImage);
		pFunction->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(pData->functionID));
	}
}

void LevelupNormalWindow::DeleteUsedLvUpData()
{
	std::vector<LevelUpData*>::iterator bgn = LevelUpDataHandler::get_instance2()->LevelUpDataList.begin();
	delete *(bgn);
	LevelUpDataHandler::get_instance2()->LevelUpDataList.erase(bgn);
}

void LevelupNormalWindow::OnUpdateUITextEventHandler(std::list<std::string>& paramList)
{
	if (!m_pRootNode->isVisible())
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LEVELUPNORMALWINDOW_, _to_event_param_(m_subType));
		//PushEvent(_TYPED_EVENT_SHOW_LEVELUPNORMALWINDOW_);
	}
	else
		PushEvent(_TYPED_EVENT_HIDE_LEVELUPNORMALWINDOW_);
}

void LevelupNormalWindow::OnSureButtonClick(cocos2d::CCObject* pSender)
{
	SOUNDSYSTEM->StopAllEffect();
	ShowSelfRoot(false);
	if ( LevelUpDataHandler::get_instance2()->LevelUpDataList.size() >0)
	{
		PopWindowDidHide();
		//PushEvent(_TYPED_EVENT_SHOW_LEVELUPNORMALWINDOW_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LEVELUPNORMALWINDOW_, _to_event_param_(m_subType));
	}
	else
	{
		PushEvent(_TYPED_EVENT_HIDE_LEVELUPNORMALWINDOW_);
		if (!MainTaskDataHandler::get_instance2()->IsHadNextRewardItem())
			PushEvent(_TYPED_EVENT_SHOW_MISSIONMESSAGEBOX_);
	}
}

//查看按钮
void LevelupNormalWindow::OnViewButtonClick(cocos2d::CCObject* pSender)
{
	if (m_functionID != -1){//去主城查看新功能
		if (!DOTATribeApp::get_instance2()->IsHomeProcedureAsActiveProcedure()){
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_,_to_event_param_(DOTATribeApp::get_instance2()->m_pHomeProcedure->GetType()));
		}
		else{	
			if( m_subType == _TYPED_WINDOW_CLIMBWINDOW_)
			{
				EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_CLIMBTOWERWINDOW_);
				EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
			}
		}
		
		SOUNDSYSTEM->StopAllEffect();
		ShowSelfRoot(false);
		if ( LevelUpDataHandler::get_instance2()->LevelUpDataList.size() >0){//还有升级界面
			PopWindowDidHide();
			//PushEvent(_TYPED_EVENT_SHOW_LEVELUPNORMALWINDOW_);
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LEVELUPNORMALWINDOW_, _to_event_param_(m_subType));
		}else{//最后一个升级界面
			PushEvent(_TYPED_EVENT_HIDE_LEVELUPNORMALWINDOW_);
			if (!MainTaskDataHandler::get_instance2()->IsHadNextRewardItem())
				PushEvent(_TYPED_EVENT_SHOW_MISSIONMESSAGEBOX_);
		}
	}
	else{//查看技能去
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_SELECTSKILLWINDOW_,_to_event_param_(0),"-1",_to_event_param_(m_newSkillID));

	}


	//新手引导
	GUIDESYSTEM->Next();
}

void LevelupNormalWindow::_uckCreateLayerout()
{
	m_Root = CCNode::create();
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kLEVELUPNORMALWINDOW,m_Root);
	m_pRootNode->addChild(m_Root);
}

void LevelupNormalWindow::_uckCreateLayer()
{
	_uckCreateLayer1();
	_uckCreateLayer2();
	_uckCreateLayer3();
	_uckCreateLayer4();
}

void LevelupNormalWindow::_uckCreateLayer1()
{
	m_Layer1 = CCNode::create();
	for (int i=LvUp_Type1BG;i<LvUp_Type2BG;i++)
	{
		CCNode* pNode = m_Root->getChildByTag(i);
		pNode->removeFromParent();
		pNode->setParent(NULL);
		m_Layer1->addChild(pNode,1,i);
	}
	CCMenu* pMenu = (CCMenu*)m_Layer1->getChildByTag(LvUp_Type1SureButton);
	CMenuItemSprite* pItem =(CMenuItemSprite*)pMenu->getChildByTag(0);
	pItem->setTarget(this, menu_selector(LevelupNormalWindow::OnSureButtonClick));
	m_Root->addChild(m_Layer1,10);
}

void LevelupNormalWindow::_uckCreateLayer2()
{
	m_Layer2 = CCNode::create();
	for (int i=LvUp_Type2BG;i<LvUp_Type3BG;i++)
	{
		if (i == LvUp_Type2SeeButtonEffect)
		{
			CAnimationSprite* pNode = (CAnimationSprite*)m_Root->getChildByTag(i);
			pNode->StopEffect();
			pNode->removeFromParent();
			pNode->setParent(NULL);
			m_Layer2->addChild(pNode,1,i);
			pNode->PlayEffect();
		}
		else
		{
			CCNode* pNode = m_Root->getChildByTag(i);
			pNode->removeFromParent();
			pNode->setParent(NULL);
			m_Layer2->addChild(pNode,1,i);
		}

	}
	CCMenu* pMenu = (CCMenu*)m_Layer2->getChildByTag(LvUp_Type2SeeButton);
	CMenuItemSprite* pItem =(CMenuItemSprite*)pMenu->getChildByTag(0);
	pItem->setTarget(this, menu_selector(LevelupNormalWindow::OnViewButtonClick));
	pMenu = (CCMenu*)m_Layer2->getChildByTag(LvUp_Type2SureButton);
	pItem =(CMenuItemSprite*)pMenu->getChildByTag(0);
	pItem->setTarget(this, menu_selector(LevelupNormalWindow::OnSureButtonClick));
	m_Root->addChild(m_Layer2,10);
}

void LevelupNormalWindow::_uckCreateLayer3()
{
	m_Layer3 = CCNode::create();
	for (int i=LvUp_Type3BG;i<LvUp_Type4BG;i++)
	{
		if (i == LvUp_Type3SeeButtonEffect)
		{
			CAnimationSprite* pNode = (CAnimationSprite*)m_Root->getChildByTag(i);
			pNode->StopEffect();
			pNode->removeFromParent();
			pNode->setParent(NULL);
			m_Layer3->addChild(pNode,1,i);
			pNode->PlayEffect();
		}
		else
		{
			CCNode* pNode = m_Root->getChildByTag(i);
			pNode->removeFromParent();
			pNode->setParent(NULL);
			m_Layer3->addChild(pNode,1,i);
		}

	}
	CCMenu* pMenu = (CCMenu*)m_Layer3->getChildByTag(LvUp_Type3SeeButton);
	CMenuItemSprite* pItem =(CMenuItemSprite*)pMenu->getChildByTag(0);
	pItem->setTarget(this, menu_selector(LevelupNormalWindow::OnViewButtonClick));
	pMenu = (CCMenu*)m_Layer3->getChildByTag(LvUp_Type3SureButton);
	pItem =(CMenuItemSprite*)pMenu->getChildByTag(0);
	pItem->setTarget(this, menu_selector(LevelupNormalWindow::OnSureButtonClick));
	m_Root->addChild(m_Layer3,10);
}

void LevelupNormalWindow::_uckCreateLayer4()
{
	m_Layer4 = CCNode::create();
	for (int i=LvUp_Type4BG;i<LvUp_End;i++)
	{
		if (i == LvUp_Type4SeeButtonEffect)
		{
			CAnimationSprite* pNode = (CAnimationSprite*)m_Root->getChildByTag(i);
			pNode->StopEffect();
			pNode->removeFromParent();
			pNode->setParent(NULL);
			m_Layer4->addChild(pNode,1,i);
			pNode->PlayEffect();
		}
		else
		{
			CCNode* pNode = m_Root->getChildByTag(i);
			pNode->removeFromParent();
			pNode->setParent(NULL);
			m_Layer4->addChild(pNode,1,i);
		}

	}
	CCMenu* pMenu = (CCMenu*)m_Layer4->getChildByTag(LvUp_Type4SeeButton);
	CMenuItemSprite* pItem =(CMenuItemSprite*)pMenu->getChildByTag(0);
	pItem->setTarget(this, menu_selector(LevelupNormalWindow::OnViewButtonClick));
	pMenu = (CCMenu*)m_Layer4->getChildByTag(LvUp_Type4SureButton);
	pItem =(CMenuItemSprite*)pMenu->getChildByTag(0);
	pItem->setTarget(this, menu_selector(LevelupNormalWindow::OnSureButtonClick));
	m_Root->addChild(m_Layer4,10);
}

void LevelupNormalWindow::_uckSetLayerLv(int lv ,CCNode* layer,int tag)
{
	m_pLabel = NFC_getArtFontLabel(7,lv);
	CCNode* pTemp =layer->getChildByTag(tag);
	layer->addChild(m_pLabel,10);
	m_pLabel->setPosition(pTemp->getPosition());
}

void LevelupNormalWindow::_uckSetSkillName( CCNode* layer,int tag,bool isProfessional)
{
	//名字
	CCLabelTTF* pLabel = (CCLabelTTF*)layer->getChildByTag(tag);
	//pLabel->setFontName(FontName);
	if (isProfessional)
	{
		pLabel->setString(SysLangDataManager::get_instance2()->GetSysLangById(115).c_str());
		pLabel->setColor(ccRED);
	}
	else
	{
		pLabel->setString(SysLangDataManager::get_instance2()->GetSysLangById(114).c_str());
		pLabel->setColor(ccWHITE);
	}

}

void LevelupNormalWindow::_uckSetSkillBG( CCNode* layer,int tag,bool isProfessional )
{
	//背景
	CCSprite* pskillbg = (CCSprite*)layer->getChildByTag(tag);
	pskillbg->setProperty("File",varConfig::getCardBGFilePath(0));
	if (isProfessional)
	{
		//专精特效
		if (pAdpetEffect2)
		{
			pAdpetEffect2->removeFromParentAndCleanup(true);
			pAdpetEffect2= NULL;
		}
		pAdpetEffect2=NFC_getLoopFrameEffect(m_nUiAdpetEffectID);
		pAdpetEffect2->setPosition(pskillbg->getPosition());
		layer->addChild(pAdpetEffect2,pskillbg->getZOrder());
	}
}

void LevelupNormalWindow::_uckSetSkillImage( CCNode* layer,int tag,int skill )
{
	//技能
	CCSprite* pskill = (CCSprite*)layer->getChildByTag(tag);
	PSkillItem  pSkillItemInfo = NFC_GetHeroSkillManager()->getSkillItemInfoByID(skill);
	if(pSkillItemInfo)
	pskill->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(pSkillItemInfo->skillIconID));
}
