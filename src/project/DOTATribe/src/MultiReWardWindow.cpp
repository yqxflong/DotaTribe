// Name :		MultiReWardWindow.h
// Function:	多个奖励窗口
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include "../include/MultiReWardWindow.h"
#include "../include/DOTATribeApp.h"
#include "../include/NFControlsManager.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/WindowManager.h"
#include "../include/EngineSystem.h"
#include "../include/SceneInfoDataManager.h"
#include "../include/SysLangDataManager.h"
#include "../include/CPublicVarReader.h"
#include "../include/CMenuItemSprite.h"
#include "../include/NFAnimationController.h"
#include "../include/PopWindowManager.h"

using  namespace  cocos2d;
using  namespace  extension;

#define NormalSize_Hight 350
#define NormalSize_Width 450
#define	Line_Hight	75
#define	Line_Hight_Inteval 15

MultiReWardWindow::MultiReWardWindow()
{
	m_WindowType = _TYPED_WINDOW_MULTIREWARDWINDOW_;
	m_isFirstIn = true;
}
MultiReWardWindow::~MultiReWardWindow()
{

}
bool MultiReWardWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_MULTIREWARDWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_MULTIREWARDWINDOW_, true);


	//设置该弹窗的优先级
	IPopWindow::priority_=GetPriorityByCurWindowDef(POP_PRIORITY_OBJECT_NEW);
	return IWindow::Init();
}
bool MultiReWardWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		
		InitLayer();

		return true;
	} 
	while (false);

	return false;
}
void MultiReWardWindow::Tick()
{
	IWindow::Tick();
}
void MultiReWardWindow::Destroy()
{
	//
	PopWindowDidHide();
	//
	IWindow::Destroy();
	m_isFirstIn = true;
}

//需要子类继承并重写
void MultiReWardWindow::ShowPopWindow(){
	IPopWindow::ShowPopWindow();
	ShowWindow();
}
void MultiReWardWindow::PopWindowDidHide(){
	IPopWindow::PopWindowDidHide();
}

void MultiReWardWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_MULTIREWARDWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_MULTIREWARDWINDOW_)
	{
		Destroy();
	}
}
void MultiReWardWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	NFC_showCommunicationWating(false);
	PopWindowManager::get_instance2()->AddPopWindow(this);
}

void MultiReWardWindow::ShowWindow(){
	Show(true);
	NFC_Action_fallDown(m_pRoot);
}

void MultiReWardWindow::InitLayer()
{
	m_pRoot =CCLayer::create();
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kMULTIREWARDWINDOW,m_pRoot);
	CCNode* maskLayer = m_pRoot->getChildByTag(MultiReward_MaskLayer);
	maskLayer->removeFromParent();
	maskLayer->setParent(NULL);
	m_pRootNode->addChild(maskLayer);
	m_pRootNode->addChild(m_pRoot);
	CCMenu* ptemp = (CCMenu*)m_pRoot->getChildByTag(MultiReward_SureButton);
	CMenuItemSprite* ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(MultiReWardWindow::On_Click_Close));

	_chooseTitle();
	OnUpdateRewardInfo();
}
void MultiReWardWindow::On_Click_Close(cocos2d::CCObject* pSender)
{
	PushEvent(_TYPED_EVENT_HIDE_MULTIREWARDWINDOW_);
}
void MultiReWardWindow::OnUpdateRewardInfo()
{
	MaskNode* node=(MaskNode*)m_pRoot->getChildByTag(MultiReward_ScrollLayer);
	const UIViewData & dd=node->GetViewData();
	scroll=CScrollView::create(kPRIORITYLOWER);
	scroll->setViewSize(CCSizeMake(dd.width_,dd.height_));
	CCLayerColor* layer = CCLayerColor::create(ccc4(0,0,0,0));
	layer->setAnchorPoint(CCPointZero);
	layer->setPosition(CCPointZero);


	scroll->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	scroll->setPosition(ccp(dd.posx_,dd.posy_));
	scroll->setNotScrollEmpty(false);
	scroll->unscheduleAllSelectors();
	float _hight = InitRewardList(layer);

	scroll->setContainer(layer);
	scroll->setContentSize(CCSizeMake(dd.width_, _hight));
	layer->setContentSize(CCSizeMake(dd.width_,_hight));

	scroll->resizeContent(layer);
	NFC_refreshScrollView(scroll);

	scroll->setDelegate(this);
	m_pRoot->addChild(scroll,10,100);
	setArrow(scroll);
}

int MultiReWardWindow::_getQualityByData(MultiRewardData* data){
	if (data->type==kDT_AWARD_OBJECT){
		return data->quality;
	}else if(data->type==kDT_AWARD_MONEY){
		return _GOLD_QUALITY_RESID_;
	}else if(data->type==kDT_AWARD_EXP){
		return _EXP_QUALITY_RESID_;
	}else if(data->type==kDT_AWARD_DIAMOND){
		return _DIAMOND_QUALITY_RESID_;
	}else if(data->type==kDT_AWARD_PRESTIGE){
		return _PREGIST_QUALITY_RESID_;
	}else if(data->type==kDT_AWARD_POWER){
		return _POWER_QUALITY_RESID_;
	}else{
		return -1;
	}
}

float MultiReWardWindow::InitRewardList(CCLayer* layer)
{
	MaskNode* node=(MaskNode*)m_pRoot->getChildByTag(MultiReward_ScrollLayer);
	const UIViewData & dd=node->GetViewData();

	float hight =Line_Hight_Inteval;
	hight =hight+((MultiRewardDataHandler::get_instance2()->MultiRewardNum-1)/2+1)*(Line_Hight+Line_Hight_Inteval);
	CCLOG("%f,%f", dd.height_,hight);
	if (hight < dd.height_)
		hight = dd.height_;

	for (int i=0;i<MultiRewardDataHandler::get_instance2()->MultiRewardNum;i=i+2)
	{
		MultiRewardData* pData = MultiRewardDataHandler::get_instance2()->MultiRewardDataList[i];
		ReSetData(pData);
		//
		node=(MaskNode*)m_pRoot->getChildByTag(MultiReward_CellBG1);
		const UIViewData & dd1=node->GetViewData();
		CCSprite* pSprite = CCSprite::create();
		pSprite->setProperty("File",dd1.filepath_);
		pSprite->setAnchorPoint(CCPointZero);
		pSprite->setPosition(ccp(dd1.posx_,hight-((i/2+1)*((Line_Hight+Line_Hight_Inteval)))));
		//
		node=(MaskNode*)m_pRoot->getChildByTag(MultiReward_CellObject1);
		const UIViewData & dd2=node->GetViewData();
		DTAwardBoard* obj=NFC_createDTAwardBoardByViewData(pSprite,dd2);
		int quality=_getQualityByData(pData);
		obj->ChangeObject(quality,pData->iconid);
		//
		node=(MaskNode*)m_pRoot->getChildByTag(MultiReward_CellName1);
		const UIViewData & dd3=node->GetViewData();
		CCLabelTTF* pName = CCLabelTTF::create();
		NFC_setLabelByFontStyleID(pName,dd3.m_nFontStyleID);
		pName->setString(pData->name.c_str());
		pName->setAnchorPoint(ccp(dd3.anchorx_,dd3.anchory_));
		pName->setPosition(ccp(dd3.posx_,dd3.posy_));
		pSprite->addChild(pName,dd3.zorder_);
		//
		node=(MaskNode*)m_pRoot->getChildByTag(MultiReward_CellNum1);
		const UIViewData & dd4=node->GetViewData();
		CCLabelTTF* pNum = CCLabelTTF::create();
		NFC_setLabelByFontStyleID(pNum,dd4.m_nFontStyleID);
		char _num[64]="";
		sprintf(_num,"x%d",pData->num);
		pNum->setString(_num);
		pNum->setAnchorPoint(ccp(dd4.anchorx_,dd4.anchory_));
		pNum->setPosition(ccp(dd4.posx_,dd4.posy_));
		pSprite->addChild(pNum,dd4.zorder_);

		CCLOG("%s: %f,%f", pName->getString(), pSprite->getPositionX(), pSprite->getPositionY());
		layer->addChild(pSprite);

		if (i+1 <MultiRewardDataHandler::get_instance2()->MultiRewardNum)
		{
			pData = MultiRewardDataHandler::get_instance2()->MultiRewardDataList[i+1];
			ReSetData(pData);
			//
			node=(MaskNode*)m_pRoot->getChildByTag(MultiReward_CellBG2);
			const UIViewData & dd5=node->GetViewData();
			CCSprite* pSprite = CCSprite::create();
			pSprite->setProperty("File",dd5.filepath_);
			pSprite->setAnchorPoint(CCPointZero);
			pSprite->setPosition(ccp(dd5.posx_,hight-((i/2+1)*((Line_Hight+Line_Hight_Inteval)))));
			//
			node=(MaskNode*)m_pRoot->getChildByTag(MultiReward_CellObject2);
			const UIViewData & dd6=node->GetViewData();
			obj=NFC_createDTAwardBoardByViewData(pSprite,dd6);
			quality=_getQualityByData(pData);
			obj->ChangeObject(pData->quality,pData->iconid);
			//
			node=(MaskNode*)m_pRoot->getChildByTag(MultiReward_CellName2);
			const UIViewData & dd7=node->GetViewData();
			CCLabelTTF* pName = CCLabelTTF::create();
			NFC_setLabelByFontStyleID(pName,dd7.m_nFontStyleID);
			pName->setString(pData->name.c_str());
			pName->setAnchorPoint(ccp(dd7.anchorx_,dd7.anchory_));
			pName->setPosition(ccp(dd7.posx_,dd7.posy_));
			pSprite->addChild(pName,dd7.zorder_);
			//
			node=(MaskNode*)m_pRoot->getChildByTag(MultiReward_CellNum2);
			const UIViewData & dd8=node->GetViewData();
			CCLabelTTF* pNum = CCLabelTTF::create();
			NFC_setLabelByFontStyleID(pNum,dd8.m_nFontStyleID);
			char _num[64]="";
			sprintf(_num,"x%d",pData->num);
			pNum->setString(_num);
			pNum->setAnchorPoint(ccp(dd8.anchorx_,dd8.anchory_));
			pNum->setPosition(ccp(dd8.posx_,dd8.posy_));
			pSprite->addChild(pNum,dd8.zorder_);

			CCLOG("%s: %f,%f", pName->getString(), pSprite->getPositionX(), pSprite->getPositionY());
			layer->addChild(pSprite);
		}
	}
	return hight;
}
void MultiReWardWindow::setArrow(CCScrollView* view)
{
	if (view->getContentOffset().y >= 0)
	{
		if (view->getContentOffset().y == 0 && view->getContentSize().height<= view->getViewSize().height)
		{
			CSprite* pleftArrow = (CSprite*)m_pRoot->getChildByTag(MultiReward_ArrowUp);
			pleftArrow->changeToImage2();
			//
			CSprite* prightArrow = (CSprite*)m_pRoot->getChildByTag(MultiReward_ArrowDown);
			prightArrow->changeToImage2();
			//
			m_scrollflag = false;
			m_isFirstIn = false;
		}
		if (!m_scrollflag || m_isFirstIn)
		{
			CSprite* pArrow = (CSprite*)m_pRoot->getChildByTag(MultiReward_ArrowDown);
			pArrow->changeToImage2();
			//
			m_scrollflag = true;
			m_isFirstIn = false;
		}

	}
	else if (view->getContentOffset().y <= (view->getContentSize().height-view->getViewSize().height)*-1)
	{
		if (!m_scrollflag || m_isFirstIn)
		{
			CSprite* pArrow = (CSprite*)m_pRoot->getChildByTag(MultiReward_ArrowUp);
			pArrow->changeToImage2();
			m_scrollflag = true;
			m_isFirstIn = false;
		}
	}
	else
	{
		if (m_scrollflag || m_isFirstIn)
		{
			CSprite* pleftArrow = (CSprite*)m_pRoot->getChildByTag(MultiReward_ArrowUp);
			pleftArrow->changeToImage1();
			//
			CSprite* prightArrow = (CSprite*)m_pRoot->getChildByTag(MultiReward_ArrowDown);
			prightArrow->changeToImage1();
			//
			m_scrollflag = false;
			m_isFirstIn = false;
		}

	}
}
void MultiReWardWindow::scrollViewDidScroll(CCScrollView* view)
{
//	CCLOG("ViewSize: [%f,%f] LayerSize: [%f,%f]", view->getViewSize().width, view->getViewSize().height, view->getContainer()->getContentSize().width, view->getContainer()->getContentSize().height); 
	setArrow(view);
}
void MultiReWardWindow::ReSetData(MultiRewardData* data)
{
	if (data->iconid == -1)
	{
		switch(data->type)
		{
			case Type_Menoy:
			{
				data->iconid = _GOLD_ICON_RESID_; //金币
				data->name = SysLangDataManager::get_instance2()->GetSysLangById(SysLang_Menoy);
				break;
			}
			case Type_Exp:
			{
				data->iconid = _EXP_ICON_RESID_; //经验
				data->name = SysLangDataManager::get_instance2()->GetSysLangById(SysLang_Exp);
				break;
			}
			case Type_Diamond:
			{
				data->iconid = _DIAMOND_ICON_RESID_; //钻石
				data->name = SysLangDataManager::get_instance2()->GetSysLangById(SysLang_Diamond);
				break;
			}
			case Type_Pregist:
			{
				data->iconid = _PREGIST_ICON_RESID_; //声望
				data->name = SysLangDataManager::get_instance2()->GetSysLangById(SysLang_Pregist);
				break;
			}
			case Type_Energy:
			{
				data->iconid = _POWER_ICON_RESID_; //体力
				data->name = SysLangDataManager::get_instance2()->GetSysLangById(SysLang_Energy);
				break;

			}
		}
	}
}

void MultiReWardWindow::_chooseTitle()
{	
	bool isshow = false;
	if (WINDOWMANAGER->IsWindowVisible(IWindow::_TYPED_WINDOW_VIP_WINDOW_) || WINDOWMANAGER->IsWindowVisible(IWindow::_TYPED_WINDOW_VIPGIFTWINDOW_))
		isshow = false;
	else
		isshow = true;
	NFC_setNodeVisable(MultiReward_GETGOODSTITLE,m_pRoot,isshow);
	NFC_setNodeVisable(MultiReward_PREVIEWTITLE,m_pRoot,!isshow);
}