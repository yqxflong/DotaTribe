//Name : GainSoulDebriWindow
//Function : 获得灵魂碎片窗口
//Author : lvyunlong
//Date: 20131208

#include "../include/GainSoulDebriWindow.h"
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


GainSoulDebriWindow::GainSoulDebriWindow()
:m_pRoot(NULL),
m_pGSoulNode(NULL),
m_pGainData(NULL),
m_pSkeletonNode(NULL),
m_isTouch(false)
{
	m_WindowType   = _TYPED_WINDOW_GAINSOULDEBRIWINDOW_;
	m_bModelWindow = true;
}

GainSoulDebriWindow::~GainSoulDebriWindow()
{

}

bool GainSoulDebriWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_GAINSOULDEBRIWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_GAINSOULDEBRIWINDOW_, true);
	//设置该弹窗的优先级
	IPopWindow::priority_=GetPriorityByCurWindowDef(POP_PRIORITY_HERO_NEW);
	return IWindow::Init();
}
bool GainSoulDebriWindow::Load()
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

void GainSoulDebriWindow::Tick()
{
	IWindow::Tick();
}

void GainSoulDebriWindow::Destroy()
{
	//
	PopWindowDidHide();
	//
	HEROSUMMONCONTROLDATAHANDLER->RemoveGainListFornt();
	m_isTouch = false;
	if (m_pSkeletonNode)
	{
		m_pSkeletonNode->removeFromParentAndCleanup(true);
		m_pSkeletonNode=NULL;
	}
	IWindow::Destroy();
}

void GainSoulDebriWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_GAINSOULDEBRIWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_GAINSOULDEBRIWINDOW_)
	{
		OnHideWindowEventHandler(paramList);
	}
}

void GainSoulDebriWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	PopWindowManager::get_instance2()->AddPopWindow(this);
}

void GainSoulDebriWindow::ShowWindow(){
	Show(true);
}

//显示弹窗
void GainSoulDebriWindow::ShowPopWindow(){
	IPopWindow::ShowPopWindow();
	ShowWindow();
}
//弹窗已经隐藏
void GainSoulDebriWindow::PopWindowDidHide(){
	IPopWindow::PopWindowDidHide();
}

void  GainSoulDebriWindow::OnHideWindowEventHandler(std::list<std::string>& paramList)
{
	Destroy();
}

void GainSoulDebriWindow::_initLayout()
{
	m_pRoot = m_pRootNode;
	m_pRoot->setAnchorPoint(CCPointZero);
	m_pRoot->setPosition(CCPointZero);
	m_pGSoulNode = CCNode::create();
	m_pGSoulNode->setAnchorPoint(CCPointZero);
	m_pGSoulNode->setPosition(CCPointZero);
	m_pRoot->addChild(m_pGSoulNode,10);
	//获得当前显示英雄信息
	m_pGainData = HEROSUMMONCONTROLDATAHANDLER->m_pCurGainData;
	_initControl();
	_setShowHeroDaiji(m_pGainData->heroId_);
	_setHeroType(m_pGainData->herotype_);

	//英雄名字
	NFC_setLabelString(udHERONAME,m_pGSoulNode,m_pGainData->strheroname.c_str());
	_setStarRank();
	_setText();

	CPriorityLayerColor* p = (CPriorityLayerColor*)m_pGSoulNode->getChildByTag(udPRIORITY);
	p->setDelegate(this);
}

void GainSoulDebriWindow::_initControl()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kGAINSOULDEBRIWINDOW,m_pGSoulNode);
}

void GainSoulDebriWindow::_setShowHeroDaiji(int heroid)
{
	MaskNode* node = (MaskNode*)m_pGSoulNode->getChildByTag(udHEROMASKNODE);
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

void GainSoulDebriWindow::_setStarRank()
{
	/*std::string str = varConfig::getBigNumBy(m_pGainData->quality_+1).c_str();
	char buff[64]={0};
	sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(961).c_str(),str.c_str(),m_pGainData->rank_);
	NFC_setLabelString(udSTARRANKTEXT,m_pGSoulNode,buff);*/
	NFC_setCardsStarLevel(udSTARRANKTEXT,m_pGSoulNode,m_pGainData->quality_+1);
}

void GainSoulDebriWindow::_setText()
{
	char buff[64]={0};
	sprintf(buff,"%s*%d",m_pGainData->stritem.c_str(),m_pGainData->itemcount);
	NFC_setLabelString(udCHANGEDESCRIBE,m_pGSoulNode,buff);
}

void GainSoulDebriWindow::_setHeroType(int type)
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
	NFC_setPicForCCSprite(udHEROTYPE,m_pGSoulNode,strpath.c_str());
}

/*
	CPriorityLayerColor Delegate
*/
void GainSoulDebriWindow::touchEvent(CPriorityLayerColor* pLayerColor)
{	
	if (m_isTouch)
	{
		PushEvent(_TYPED_EVENT_HIDE_GAINSOULDEBRIWINDOW_);
		HEROSUMMONCONTROLDATAHANDLER->CallBackShowNewOrOldHero();
		return;
	}
	m_isTouch = true;
	NFC_skeletonTransparentAction(m_pSkeletonNode,1.2f);
	cocos2d::CCSprite* pp = NFC_getUnLoopFrameEffect(2053,this);
	MaskNode* node = (MaskNode*)m_pGSoulNode->getChildByTag(udHEROMASKNODE1);
	node->addChild(pp,10);	
}

void GainSoulDebriWindow::EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr)
{
	PushEvent(_TYPED_EVENT_HIDE_GAINSOULDEBRIWINDOW_);
	HEROSUMMONCONTROLDATAHANDLER->CallBackShowNewOrOldHero();
}