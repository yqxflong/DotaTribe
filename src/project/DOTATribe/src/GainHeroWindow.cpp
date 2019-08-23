//Name : GainHeroWindow
//Function : 获得英雄窗口
//Author : lvyunlong
//Date: 20131206

#include "../include/GainHeroWindow.h"
#include "../include/EventTyper.h"
#include "../include/UIViewDataManger.h"
#include "../include/CMenuItemSprite.h"
#include "../include/NFControlsManager.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/AnimationFileDataManager.h"
#include "../include/RoleShapeDataManager.h"
#include "../include/NFAnimationController.h"
#include  "../include/RoleHeroSkinsDataHandler.h"
#include "../include/PopWindowManager.h"

USING_NS_CC;


GainHeroWindow::GainHeroWindow()
:m_pRoot(NULL),
m_pGHeroNode(NULL),
m_pGainData(NULL),
m_pSkeletonNode(NULL),
m_isBGainBtn(false),
m_CurViewHeroLV(0)
{
	m_WindowType   = _TYPED_WINDOW_GAINHEROWINDOW_;
	m_bModelWindow = true;

}

GainHeroWindow::~GainHeroWindow()
{

}


bool GainHeroWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_GAINHEROWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_GAINHEROWINDOW_, true);
	
	//设置该弹窗的优先级
	IPopWindow::priority_=GetPriorityByCurWindowDef(POP_PRIORITY_HERO_NEW);
	return IWindow::Init();
}
bool GainHeroWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		_initLayout();
		return true;
	} 
	while (false);

	return false;
}

void GainHeroWindow::Tick()
{
	IWindow::Tick();
}

void GainHeroWindow::Destroy()
{
	//
	PopWindowDidHide();
	//
	HEROSUMMONCONTROLDATAHANDLER->RemoveGainListFornt();
	if (m_pSkeletonNode)
	{
		m_pSkeletonNode->removeFromParentAndCleanup(true);
		m_pSkeletonNode=NULL;
	}
	m_isBGainBtn = false;
	IWindow::Destroy();
}

//显示弹窗
void GainHeroWindow::ShowPopWindow(){
	IPopWindow::ShowPopWindow();
	ShowWindow();
}
//弹窗已经隐藏
void GainHeroWindow::PopWindowDidHide(){
	IPopWindow::PopWindowDidHide();
}

void GainHeroWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_GAINHEROWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_GAINHEROWINDOW_)
	{
		OnHideWindowEventHandler(paramList);
	}
}

void GainHeroWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	PopWindowManager::get_instance2()->AddPopWindow(this);
}

void GainHeroWindow::ShowWindow(){
	Show(true);
}

void  GainHeroWindow::OnHideWindowEventHandler(std::list<std::string>& paramList)
{
	Destroy();
}

void GainHeroWindow::_initLayout()
{
	m_pRoot = m_pRootNode;
	m_pRoot->setAnchorPoint(CCPointZero);
	m_pRoot->setPosition(CCPointZero);
	m_pGHeroNode = CCNode::create();
	m_pGHeroNode->setAnchorPoint(CCPointZero);
	m_pGHeroNode->setPosition(CCPointZero);

	m_pRoot->addChild(m_pGHeroNode,10);
	//获得当前显示英雄信息
	m_pGainData = HEROSUMMONCONTROLDATAHANDLER->m_pCurGainData;

	_initControl();
	_initProgressTimer();
	_setShowHeroDaiji(m_pGainData->heroId_);
	_setHeroType(m_pGainData->herotype_);
	_setStarRank();
	char buff[256]={0};
	std::string sys =SysLangDataManager::get_instance2()->GetSysLangById(5014);
	int leadership = m_pGainData->honorLevel_;
	sprintf(buff,sys.c_str(),leadership);
	NFC_setLabelString(udLEADERSHIPVALUE,m_pGHeroNode,buff);
	//英雄名
	NFC_setLabelString(udHERONAME,m_pGHeroNode,m_pGainData->strheroname.c_str());

	CPriorityLayerColor* p = (CPriorityLayerColor*)m_pGHeroNode->getChildByTag(udPRIORITY);
	p->setDelegate(this);
	StarRankShow();
}

void GainHeroWindow::_initControl()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kGAINHEROWINDOW,m_pGHeroNode);
}

void GainHeroWindow::_initProgressTimer()
{
	m_pProgress = (CProgressTimer *)NFC_getNode(udSCHEDULE,m_pGHeroNode);
	m_pProgress->setDelegate(this);
}

void GainHeroWindow::_setProgress(GainHeroOrDebriData* pData)
{
	unsigned short prelv = pData->pre_herolv_;
	int premax = pData->pre_maxheroexp_;
	int preexp = pData->pre_heroexp_;

	unsigned short afterlv = pData->after_herolv_;
	int aftermax = pData->after_maxheroexp_;
	int afterexp = pData->after_heroexp_;

	unsigned short times = afterlv - prelv;
	if (times == 0)
	{
		float frontpos = (float)(100.0*preexp/premax);
		float behindpos =(float)(100.0*afterexp/premax);
		m_pProgress->setRunSchedule(frontpos,behindpos,times);
	}
	else
	{
		float frontpos = (float)(100.0*preexp/premax);
		float posend = (float)(100.0*afterexp/aftermax);
		m_pProgress->setRunSchedule(frontpos,posend,times);
	}
}

void GainHeroWindow::_setShowHeroDaiji(int heroid)
{
	MaskNode* node = (MaskNode*)m_pGHeroNode->getChildByTag(udHEROMASKNODE);
	//强制释放无用资源
	if(m_pSkeletonNode) 
	m_pSkeletonNode->removeFromParentAndCleanup(true); 

	DOTATribeApp::get_instance2()->ForceFreeMemory();
	 
	unsigned short shapeID = heroid;
	assert(shapeID>=0);
	IHeroSkinItem * pHeroSkinItem=RoleHeroSkinsDataHandler::get_instance2()->GetHeroSkinItemByID(shapeID);
	RoleShapeData *pData = RoleShapeDataManager::get_instance2()->GetRoleShapeById(pHeroSkinItem->getHeroShapeID());
	m_pSkeletonNode = CCSkeletonAnimation::createWithFile(pData->mShapeAnimationFileDaiJi,pData->mShapeAnimationImage); 
	if(m_pSkeletonNode) 
		m_pSkeletonNode->setAnimation("DaiJi",true);
	m_pSkeletonNode->setAnchorPoint(node->getAnchorPoint());
	m_pSkeletonNode->setPosition(ccp(0.0f,0.0f));
	node->addChild(m_pSkeletonNode,20);
}

void GainHeroWindow::_setStarRank()
{
	NFC_setCardsStarLevel(udSTARRANKTEXT,m_pGHeroNode,m_pGainData->quality_+1);
}

void GainHeroWindow::_setHeroType(int type)
{
	int typeResouleID = 0;
	if (type == HERO_POWER)
	{
		typeResouleID = ClientConstDataManager::get_instance2()->getValueByKey(POWER_ICON);
	}
	else if (type == HERO_QUICK)
	{
		typeResouleID = ClientConstDataManager::get_instance2()->getValueByKey(QUICK_ICON);
	}
	else if (type == HERO_INTELIGENCE)
	{
		typeResouleID = ClientConstDataManager::get_instance2()->getValueByKey(INTELIGENCE_ICON);
	}
	
	std::string strpath = ResourceIDDataManager::get_instance2()->getDataByID(typeResouleID).c_str();
	NFC_setPicForCCSprite(udHEROTYPE,m_pGHeroNode,strpath.c_str());
}


void GainHeroWindow::CallbackTTF()
{
	//m_CurViewHeroLV++;
	//NFC_setLabelStringInt(udHEROCURLEVEL,m_pGHeroNode,m_CurViewHeroLV);
}

void GainHeroWindow::CallbackBtnEnable()
{
	m_isBGainBtn = true;
}

void  GainHeroWindow::CallBack_NextLevel()
{
	CallbackTTF();
}
void  GainHeroWindow::CallBack_RunFinish()
{
	CallbackBtnEnable();
}

void  GainHeroWindow::StarRankShow()
{
	if (m_pGainData->quality_+1 >= 4)
	{
		cocos2d::CCSprite* pp = NFC_getUnLoopFrameEffect(2057,this,1.0f);
		MaskNode* node = (MaskNode*)m_pGHeroNode->getChildByTag(udNEWHEROEFFECTNODE);
		node->addChild(pp,10);

		for (int i = udMAINBG;i<=udHERONAME;i++)
		{
			NFC_setNodeVisable(i,m_pGHeroNode,false);
		}
	}
	else
	{
		_setProgress(m_pGainData);
	}
}

/*
	CPriorityLayerColor Delegate
*/
void GainHeroWindow::touchEvent(CPriorityLayerColor* pLayerColor)
{
	//按钮不可按
	if (!m_isBGainBtn)
		return;
	PushEvent(_TYPED_EVENT_HIDE_GAINHEROWINDOW_);
	HEROSUMMONCONTROLDATAHANDLER->CallBackShowNewOrOldHero();
}


void GainHeroWindow::EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr)
{
	if (eventType == _Animation_Timer_Triger_Event_)
	{
		for (int i = udMAINBG;i<=udHERONAME;i++)
		{
			NFC_setNodeVisable(i,m_pGHeroNode,true);
		}
		_setProgress(m_pGainData);
	}
	else if (eventType == _Animation_Effect_Finish_Event_)
	{
		animationNode->removeFromParentAndCleanup(true);
	}
}