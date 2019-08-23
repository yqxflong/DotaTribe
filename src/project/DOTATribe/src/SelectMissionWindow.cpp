// Name :		SelectMissionWindow.h
// Function:	世界地图窗口
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include "../include/SelectMissionWindow.h"
#include "../include/MissionDataHandler.h"
#include "../include/SceneInfoDataManager.h"
#include "../include/HomeProcedure.h"
#include "../include/LevelUpDataHandler.h"
#include "../include/GuideSystem.h"
#include "../include/NFControlsManager.h"


using  namespace  cocos2d;

#define MissionNum	15
#define NormalSize_Width 3368
#define NormalSize_High	768

#define FontName	"ArialRoundedMTBold" //默认字体

SelectMissionWindow::SelectMissionWindow()
{
	m_WindowType = _TYPED_WINDOW_SELECTMISSION_;
	m_BeginPos = CCPointZero;
	m_EndPos = CCPointZero;
	m_MoveLength = 0;
}

SelectMissionWindow::~SelectMissionWindow()
{

}

bool SelectMissionWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_SELECTMISSIONWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_SELECTMISSIONWINDOW_, true);
	return IWindow::Init();
}

bool SelectMissionWindow::Load()
{
	do 
	{	
		if (!IWindow::Load())
			break;

		InitMission();		
		return true;
	} 
	while (false);

	return false;
}

void SelectMissionWindow::Tick()
{
	IWindow::Tick();
}

void SelectMissionWindow::Destroy()
{
	IWindow::Destroy();
}

void SelectMissionWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_SELECTMISSIONWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_SELECTMISSIONWINDOW_)
	{
		Destroy();
	}
}

void SelectMissionWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	PushEvent(_TYPED_EVENT_HIDE_LOADINGWINDOW_);
	if (LevelUpDataHandler::get_instance2()->LevelUpDataList.size()>0)
	{
		//PushEvent(_TYPED_EVENT_SHOW_LEVELUPNORMALWINDOW_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LEVELUPNORMALWINDOW_,_to_event_param_(m_WindowType));
	}
	Show(true);
	
}

float SelectMissionWindow::GetOffsetX()
{
	int id= MissionDataHandler::get_instance2()->getCurMissionID();
	CMenuItemSprite* pMenuItemTemp = (CMenuItemSprite*)NFC_getMenuItem(id+Mission_Return,m_pRoot);
	if (pMenuItemTemp->getPositionX()>0)
	{
		if (pMenuItemTemp->getPositionX()>(cocos2d::CCDirector::sharedDirector()->getWinSize().width/2) && pMenuItemTemp->getPositionX()<(NormalSize_Width-cocos2d::CCDirector::sharedDirector()->getWinSize().width/2))
			return (pMenuItemTemp->getPositionX()-cocos2d::CCDirector::sharedDirector()->getWinSize().width/2)*-1;
		else if(pMenuItemTemp->getPositionX()>(NormalSize_Width-cocos2d::CCDirector::sharedDirector()->getWinSize().width/2))
			return (NormalSize_Width-cocos2d::CCDirector::sharedDirector()->getWinSize().width)*-1;
	}
	return 0.0f;
}

void SelectMissionWindow::OnSceneButtonClick(cocos2d::CCObject* pSender)
{
	cocos2d::CCNode *pmenuimage = (CCNode*)pSender;
	int MissionID = pmenuimage->getParent()->getTag()-Mission_Return;
	MissionDataHandler::get_instance2()->setCurMissionID(MissionID);
	PushEvent(_TYPED_EVENT_HIDE_SELECTMISSIONWINDOW_);
	PushEvent(_TYPED_EVENT_SHOW_SELECTSONMISSIONWINDOW_);
}

void SelectMissionWindow::OnReturnHomeButtonClick(cocos2d::CCObject* pSender)
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_SELECTMISSIONWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_,_to_event_param_(DOTATribeApp::get_instance2()->m_pHomeProcedure->GetType()));
}

void SelectMissionWindow::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	scroll->setContentOffset(ccp(GetOffsetX(),0));
}

void SelectMissionWindow::InitMission()
{	
	_uckCreateLayerout();
	_uckHideAllBuildingAndSetTarget();
	_uckShowOpenBuilding();
	_uckHideAllWay();
	_uckShowOpenWay();
	_uckSetReturnButton();
	_uckCreateScrollView();
}

void SelectMissionWindow::_uckCreateScrollView()
{
	//滚动条
	scroll=cocos2d::extension::CCScrollView::create();
	scroll->setViewSize(cocos2d::CCDirector::sharedDirector()->getWinSize());

	CCLayer* layer = m_pRoot;
	layer->setAnchorPoint(CCPointZero);

	scroll->setDirection(cocos2d::extension::kCCScrollViewDirectionHorizontal);
	scroll->setTouchEnabled(true);

	layer->setContentSize(CCSizeMake(NormalSize_Width,NormalSize_High));
	scroll->setContentSize(CCSizeMake(NormalSize_Width,NormalSize_High));
	scroll->setNotScrollEmpty(true);

	scroll->setContainer(layer);
	scroll->setContentOffset(ccp(GetOffsetX(),0));
	m_pRootNode->addChild(scroll);
}

void SelectMissionWindow::_uckCreateLayerout()
{
	m_pRoot =CCLayer::create();
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kMISSIONWINDOW,m_pRoot);
}

void SelectMissionWindow::_uckHideAllBuildingAndSetTarget()
{
	for (int i=0;i<MissionNum;i++)
	{
		CCNode* pMenu = m_pRoot->getChildByTag(Mission_Item1+i);
		CMenuItemSprite* pMenuItemTemp = (CMenuItemSprite*)pMenu->getChildByTag(0);
		pMenuItemTemp->setTarget(this, menu_selector(SelectMissionWindow::OnSceneButtonClick));
		pMenuItemTemp->setVisible(false);
	}
}

void SelectMissionWindow::_uckHideAllWay()
{
	for (int i=0;i<MissionNum-1;i++)
	{
		CCNode* pNode = m_pRoot->getChildByTag(Mission_Arrow1+i);
		pNode->setVisible(false);
	}
}

void SelectMissionWindow::_uckShowOpenWay()
{
	for (int i=0;i<MissionDataHandler::get_instance2()->getWorldMapStateNum()-1;i++)
	{
		CCNode* pNode = m_pRoot->getChildByTag(Mission_Arrow1+i);
		pNode->setVisible(true);
	}
}

void SelectMissionWindow::_uckShowOpenBuilding()
{ 
	for (int i=0;i<MissionDataHandler::get_instance2()->getWorldMapStateNum();i++)
	{
		MissionInfoData* pMissionInfoData = MissionDataHandler::get_instance2()->getMissonInfoDataList().at(i);
		CMenuItemSprite* pItem = (CMenuItemSprite*)NFC_getMenuItem(Mission_Item1+i,m_pRoot);
		pItem->setVisible(true);

		if (i+1 == MissionDataHandler::get_instance2()->getMissonInfoDataList().size())
			_uckSetEffectPos(pItem->getPosition());

		_uckSetBuildingNameBG(pItem);
		_uckSetBuildingName(pMissionInfoData->getMissionID(),pItem);
	}
}

void SelectMissionWindow::_uckSetReturnButton()
{
	CCNode* pMenu = m_pRoot->getChildByTag(Mission_Return);
	pMenu->removeFromParent();
	pMenu->setParent(NULL);
	m_pRootNode->addChild(pMenu);
	CMenuItemSprite* pMenuItem_home = (CMenuItemSprite*)pMenu->getChildByTag(0);
	pMenuItem_home->setTarget(this, menu_selector(SelectMissionWindow::OnReturnHomeButtonClick));
}

void SelectMissionWindow::_uckSetEffectPos( CCPoint point )
{
	CCNode* pEffect = m_pRoot->getChildByTag(Mission_Effect);
	pEffect->setPosition(point);
}

void SelectMissionWindow::_uckSetBuildingNameBG( CMenuItemSprite* pItem )
{
	MaskNode* node=(MaskNode*)m_pRoot->getChildByTag(Mission_NameBG);
	const UIViewData & dd=node->GetViewData();

	CCSprite* pScenenNamebg =CCSprite::create();
	pScenenNamebg->setProperty("File",dd.filepath_);
	pScenenNamebg->setAnchorPoint(ccp(0.5,1.0));
	pScenenNamebg->setPositionX(pItem->getPositionX()+20);
	pScenenNamebg->setPositionY(pItem->getPositionY() - pItem->getContentSize().height/2 + 8);
	m_pRoot->addChild(pScenenNamebg);
}

void SelectMissionWindow::_uckSetBuildingName( int missionID,CMenuItemSprite* pItem )
{
	SceneInfoData * pSceneData =SceneInfoDataManager::get_instance2()->GetCustomPassDataByID(missionID);
	CCLabelTTF* pScenenName = CCLabelTTF::create();
	pScenenName->setFontName(FontName);
	pScenenName->setFontSize(22);
	pScenenName->setString(SysLangDataManager::get_instance2()->GetSysLangById(pSceneData->mSceneName).c_str());
	pScenenName->setAnchorPoint(ccp(0.5,1.0));
	pScenenName->setPositionX(pItem->getPositionX()+20);
	pScenenName->setPositionY(pItem->getPositionY() - pItem->getContentSize().height/2);
	m_pRoot->addChild(pScenenName);
}



