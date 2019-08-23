//Name£ºNoticeBoxWindow
//Function£º¹«¸æµ¯´°
//Written By£ºÒüÇ¿

#include "../include/NoticeBoxWindow.h"
#include "../include/EventTyper.h"
#include "../include/NFControlsManager.h"
#include "../include/CPublicVarReader.h"
#include "../include/UIViewDataManger.h"
#include "../include/CMenuItemSprite.h"
#include "../include/GuideSystem.h"
#include "../include/NFAnimationController.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/LimitedActivityHandler.h"
#include "../include/NoticeGatewayPacket.h"
#include <list>
#include <string>

using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

#define BETWEEN_RANGE20 20.0f
#define BETWEEN_RANGE05 5.0f
NoticeBoxWindow::NoticeBoxWindow()
	:m_pRootLayer(0)
	,m_pScroll(0)
{
	m_WindowType   = _TYPED_WINDOW_NOTICEBOXWINDOW_;
	m_bModelWindow = true;
	m_Type = 0;
}

bool NoticeBoxWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_NOTICEBOXWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_NOTICEBOXWINDOW_, true);

	return IWindow::Init();
}

void NoticeBoxWindow::_initLayout(){
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kNOTICEBOXWINDOW,m_pRootLayer);
	_mapBtn();
	_transferNode();
}

void NoticeBoxWindow::_mapBtn(){
	CCMenu* menu=(CCMenu*)m_pRootLayer->getChildByTag(udCLOSEBTN);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udCLOSEBTN);
	cc->setTarget(this,menu_selector(NoticeBoxWindow::On_Click_BtnClick));
}

void NoticeBoxWindow::_transferNode(){
	//gray
	CCNode* gray=NFC_getNode(udGRAYLAYER,m_pRootLayer);
	gray->removeFromParentAndCleanup(false);
	m_pRootNode->addChild(gray);
	//content

	m_pScroll=(CScrollView*)NFC_getNode(udSCROLLVIEW,m_pRootLayer);
	/*CCNode* content=NFC_getNode(udTEXTCONTENT,m_pRootLayer);
	content->removeFromParentAndCleanup(false);
	m_pScroll->addText(content);*/
}

#if 1
void NoticeBoxWindow::_initLayoutGateWay()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kNOTICEBOXGATEWAYWINDOW,m_pRootLayer);
	_mapBtnGateWay();
	_transferNodeGateWay();
}


void NoticeBoxWindow::_mapBtnGateWay()
{
	CCMenu* menu=(CCMenu*)m_pRootLayer->getChildByTag(GWudCLOSEBTN);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(GWudCLOSEBTN);
	cc->setTarget(this,menu_selector(NoticeBoxWindow::On_Click_BtnClick));
}

void NoticeBoxWindow::_transferNodeGateWay()
{
	//gray
	CCNode* gray=NFC_getNode(GWudGRAYLAYER,m_pRootLayer);
	gray->removeFromParentAndCleanup(false);
	m_pRootNode->addChild(gray);
	//content
	m_pScroll=(CScrollView*)NFC_getNode(GWudSCROLLVIEW,m_pRootLayer);

	CCLabelTTF* defaultLabel = (CCLabelTTF*)NFC_getNode(GWudTEXTDEFAULT,m_pRootLayer);
	defaultLabel->setPositionY(m_pScroll->getViewSize().height - defaultLabel->getPositionY());
	defaultLabel->removeFromParentAndCleanup(false);
	defaultLabel->setTag(GWudTEXTDEFAULT);
	m_pScroll->getContainer()->addChild(defaultLabel);

	m_pScroll->setContentSize(CCSizeMake(m_pScroll->getViewSize().width, m_pScroll->getViewSize().height));

}
#endif
bool NoticeBoxWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		m_pRootLayer=CCLayer::create();
		m_pRootLayer->setPosition(CCPointZero);
		m_pRootNode->addChild(m_pRootLayer);
		return true;
	} 
	while (false);

	return false;
}

void NoticeBoxWindow::Tick()
{
	IWindow::Tick();
}

void NoticeBoxWindow::Destroy()
{
	m_pRootNode->removeAllChildrenWithCleanup(true);
	IWindow::Destroy();
}

void NoticeBoxWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_NOTICEBOXWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_NOTICEBOXWINDOW_)
	{
		Destroy();
	}

}


void NoticeBoxWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
	list<string>::iterator it=paramList.begin();
	assert(paramList.size()>0);
	string param1=*it;
	m_Type = atoi(param1.c_str());
	std::string strcontent;
	if (_TYPE_NOTICEBOX_GATEWAY_ == m_Type)
	{
		_initLayoutGateWay();
		_setviewforScroll_gateway();

	}
	else if(_TYPE_NOTICEBOX_GAMESERVER_ == m_Type)
	{
		_initLayout();
		_setviewforScroll();
		/*strcontent = LimitedActivityHandler::get_instance2()->NoticeContent_;*/
		
	}
}
void NoticeBoxWindow::_setviewforScroll_gateway(){
	CCLayer *p  = (CCLayer*)m_pScroll->getContainer();
	CCNode *defaultText = NFC_getNode(GWudTEXTDEFAULT,p);
	defaultText->setVisible(false);

	MaskNode *title = (MaskNode*)NFC_getNode(GWudTEXTTITLE, m_pRootLayer);
	UIViewData* dd_title = title->GetViewPData();
	MaskNode *content = (MaskNode*)NFC_getNode(GWudTEXTCONTENT, m_pRootLayer);
	UIViewData* dd_content = content->GetViewPData();

	float turin = 10;
	float turout = 20;
	float height = 0;


	std::vector<NoticeData>::const_reverse_iterator it = ServerInfoDataHandler::get_instance2()->m_ContentVector.rbegin();
	std::vector<NoticeData>::const_reverse_iterator it_end = ServerInfoDataHandler::get_instance2()->m_ContentVector.rend();
	CCNode* cellRoot = CCNode::create();
	cellRoot->setPosition(CCPointZero);
	cellRoot->setAnchorPoint(CCPointZero);
	for(;it != it_end; it++)
	{
		CCNode* cell = CCNode::create();

		CCLabelTTF* t2 = CCLabelTTF::create("CONTENT",
			FontStyleDataManager::get_instance2()->getDataByID(dd_content->m_nFontStyleID)->fontname_,
			FontStyleDataManager::get_instance2()->getDataByID(dd_content->m_nFontStyleID)->fontsize_,
			CCSizeMake(dd_content->width_,dd_content->height_),kCCTextAlignmentLeft,kCCVerticalTextAlignmentTop);
		t2->setString((*it).mContent.c_str());
		t2->setAnchorPoint(ccp(dd_content->anchorx_,dd_content->anchory_));
		t2->setPosition(ccp(dd_content->posx_, 0));
		cell->addChild(t2);

		//title
		CCLabelTTF* t1 = CCLabelTTF::create("TITLE", 
			FontStyleDataManager::get_instance2()->getDataByID(dd_title->m_nFontStyleID)->fontname_, 
			FontStyleDataManager::get_instance2()->getDataByID(dd_title->m_nFontStyleID)->fontsize_,
			CCSizeMake(dd_title->width_,dd_title->height_),kCCTextAlignmentLeft,kCCVerticalTextAlignmentTop);
		t1->setString((*it).mTitle.c_str());
		t1->setAnchorPoint(ccp(dd_title->anchorx_, dd_title->anchory_));
		t1->setPosition(ccp(dd_title->posx_, t2->getContentSize().height + turin));
		cell->addChild(t1);

		cell->setAnchorPoint(CCPointZero);
		cell->setPosition(ccp(0,height));
		height += t1->getContentSize().height + t2->getContentSize().height + turin + turout;

		cellRoot->addChild(cell);
		
	}
	height -= turout;
	p->addChild(cellRoot);


	if( height >= m_pScroll->getViewSize().height)
	{
		p->setContentSize(CCSizeMake(m_pScroll->getViewSize().width, height));
	}
	else
	{
		p->setContentSize(CCSizeMake(m_pScroll->getViewSize().width, m_pScroll->getViewSize().height));
		float pos = m_pScroll->getViewSize().height - height;
		CCLOG("%f",pos);
		cellRoot->setPositionY(cellRoot->getPositionY() + pos);
	}

	m_pScroll->resizeContent(p);
	NFC_refreshScrollView(m_pScroll);
}

void NoticeBoxWindow::_setviewforScroll()
{
	std::vector<NoticeData>::const_reverse_iterator it1= LimitedActivityHandler::get_instance2()->m_ContentVector.rbegin();
	std::vector<NoticeData>::const_reverse_iterator itend= LimitedActivityHandler::get_instance2()->m_ContentVector.rend();
	CCLayerColor* layer =(CCLayerColor*)m_pScroll->getContainer();
	layer->setPosition(CCPointZero);
	layer->setAnchorPoint(CCPointZero);
	CCLOG("%f",layer->getPositionX());
	CCLOG("%f",layer->getPositionY());
	MaskNode* mNodeTitleIcon = (MaskNode*)NFC_getNode(udMASKNODE,m_pRootLayer);
	MaskNode* mNodeTitleTTF = (MaskNode*)NFC_getNode(udTEXTTITLE,m_pRootLayer);
	MaskNode* mNodeContent = (MaskNode*)NFC_getNode(udTEXTCONTENT,m_pRootLayer);
	float heiht = 10.0f;
	float sizeheight = 10.0f;
	for (;it1!=itend;it1++)
	{
		CCLayerColor* bg = CCLayerColor::create();
		bg->setAnchorPoint(ccp(0.5,0.5f));
		CCLabelTTF* ttf1 = (CCLabelTTF*)NFC_createLabelMutilineByViewData(bg,mNodeContent->GetViewData());
		ttf1->setString((*it1).mContent.c_str());
		bg->setContentSize(ttf1->getContentSize());
		bg->setPositionY(bg->getContentSize().height+heiht);
		sizeheight+=bg->getContentSize().height+BETWEEN_RANGE05;
		heiht += (bg->getContentSize().height+BETWEEN_RANGE05);
		layer->addChild(bg);

		bg =CCLayerColor::create();
		bg->setAnchorPoint(ccp(0.5f,0.5f));
		CCSprite* title = NFC_createSpriteByViewData(bg,mNodeTitleIcon->GetViewData());
		title->setAnchorPoint(ccp(0.5,0.5));
		bg->setContentSize(title->getContentSize());
		CCLabelTTF* ttf = (CCLabelTTF*)NFC_createLabelByViewData(title,mNodeTitleTTF->GetViewData());
		ttf->setString((*it1).mTitle.c_str());
		bg->setPositionY(bg->getContentSize().height/2+heiht);
		sizeheight+=bg->getContentSize().height+BETWEEN_RANGE20;
		heiht += (bg->getContentSize().height+BETWEEN_RANGE20);
		layer->addChild(bg);
	}
	if (sizeheight<m_pScroll->getViewSize().height)
	{
		sizeheight = m_pScroll->getViewSize().height;
	}
	else
	{
		sizeheight -= BETWEEN_RANGE20;
	}
	layer->setContentSize(CCSizeMake(m_pScroll->getViewSize().width,sizeheight));
	m_pScroll->resizeContent(layer);
}

void NoticeBoxWindow::On_Click_BtnClick(cocos2d::CCObject* pSender){

	if (_TYPE_NOTICEBOX_GATEWAY_ == m_Type)
	{
		PushEvent(_TYPED_EVENT_HIDE_NOTICEBOXWINDOW_);
	}
	else if(_TYPE_NOTICEBOX_GAMESERVER_ == m_Type)
	{
		PushEvent(_TYPED_EVENT_HIDE_NOTICEBOXWINDOW_);
		GuideSystem::get_instance2()->CheckAndStartGuide();
	}	
}

