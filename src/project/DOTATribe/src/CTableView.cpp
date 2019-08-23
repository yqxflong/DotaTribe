//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//  Type: Override CCTableView to add Priority
//
#include "../include/CTableView.h"
#include "../include/NFControlsManager.h"

USING_NS_CC;
USING_NS_CC_EXT;


cocos2d::CCSize TableViewSourceDelegate::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
	if(m_nScriptCellSizeForIndex)
	{
		cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEvent(m_nScriptCellSizeForIndex, "tableCellSizeForIndex");
	}
	return m_nCellSize;
}

cocos2d::extension::CCTableViewCell* TableViewSourceDelegate::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
	if(m_nScriptCellAtIndex)
	{
		std::list<std::string> paramList;
		paramList.clear();
		cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEvent(m_nScriptCellAtIndex, "tableCellAtIndex", idx, "0", paramList);
	}

	return m_pCell;
}

unsigned int TableViewSourceDelegate::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
	if(m_nScriptNumberOfCells)
	{
		cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEvent(m_nScriptNumberOfCells, "numberOfCellsInTableView");
	}

	return m_nCellNumbers;
}

void TableViewSourceDelegate::scrollViewDidScroll(cocos2d::extension::CCScrollView* view)
{
	if(m_nScriptScrollViewDidScroll)
	{
		cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEvent(m_nScriptScrollViewDidScroll, "scrollViewDidScroll");
	}
}

void TableViewSourceDelegate::registerScript(int cellSizeForIndex, int tableCellAtIndex, int numberOfCellsInTableView, int scrollViewDidScroll)
{
	//cell宽度事件
	if (m_nScriptCellSizeForIndex)
	{
		cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nScriptCellSizeForIndex);
	}
	m_nScriptCellSizeForIndex = cellSizeForIndex;

	//cell绘制事件
	if(m_nScriptCellAtIndex)
	{
		cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nScriptCellAtIndex);
	}
	m_nScriptCellAtIndex = tableCellAtIndex;

	//cell数量事件
	if(m_nScriptNumberOfCells)
	{
		cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nScriptNumberOfCells);
	}
	m_nScriptNumberOfCells = numberOfCellsInTableView;

	//cell滚动事件
	if(m_nScriptScrollViewDidScroll)
	{
		cocos2d::CCScriptEngineManager::sharedManager()->getScriptEngine()->removeScriptHandler(m_nScriptScrollViewDidScroll);
	}
	m_nScriptScrollViewDidScroll = scrollViewDidScroll;
}


CTableView* CTableView::create(CCTableViewDataSource* dataSource, CCSize size,int priority,bool swallow){
	CTableView* cc=new CTableView();
	if (cc&&cc->init(dataSource,size,priority,swallow))
	{
		cc->autorelease();
		return cc;
	}
	delete cc;
	return 0;
}

bool CTableView::init(CCTableViewDataSource* dataSource, CCSize size,int priority,bool swallow){
	if (CCTableView::initWithViewSize(size))
	{
		this->setDataSource(dataSource);
		m_nPriority=priority;
		m_bSwallow=swallow;
		return true;
	}
	return false;
}

TableViewSourceDelegate * CTableView::getMyDelegate()
{
	if(m_pSourceDelegate == NULL)
	{
		m_pSourceDelegate = new TableViewSourceDelegate();
		this->setDelegate(m_pSourceDelegate);
		this->setDataSource(m_pSourceDelegate);
	}

	return m_pSourceDelegate;
}


//======================CScrollView=====================
CScrollView* CScrollView::create(int priority,bool swallow){
	CScrollView* cc=new CScrollView();
	if (cc&&cc->init(priority,swallow))
	{
		cc->autorelease();
		return cc;
	}
	delete cc;
	return 0;
}

bool CScrollView::init(int priority,bool swallow){
	if (CCScrollView::init())
	{
		m_nPriority=priority;
		m_bSwallow=swallow;
		return true;
	}
	return false;
}

//加入内容
void CScrollView::addText(cocos2d::CCNode* content){
	const CCSize& sz=content->getContentSize();
	this->setContentSize(sz);
	content->setAnchorPoint(CCPointZero);
	content->setPosition(CCPointZero);
	this->addChild(content);
}

//重新设置contentsize
void CScrollView::resizeContent(cocos2d::CCNode* content){
	const CCSize& sz=content->getContentSize();
	this->setContentSize(sz);
	NFC_refreshScrollView(this);
}


//======================CMapScrollView=====================
/*
	用于做为滚动map的控件
*/
CMapScrollView* CMapScrollView::create(const cocos2d::CCSize& sz,int priority,bool swallow){
	CMapScrollView* cc=new CMapScrollView();
	if (cc&&cc->initWithViewSize(sz,priority,swallow))
	{
		cc->autorelease();
		return cc;
	}
	delete cc;
	return 0;
}

bool CMapScrollView::initWithViewSize(const cocos2d::CCSize& sz,int priority,bool swallow){
	if (CCScrollView::initWithViewSize(sz,CCLayer::create()))
	{
		m_nPriority=priority;
		m_bSwallow=swallow;
		//setBounceable(false);
		setDirection(kCCScrollViewDirectionHorizontal);
		setNotScrollEmpty(true);
		return true;
	}
	return false;
}

//重写父类函数
cocos2d::CCNode* CMapScrollView::getChildByTag(int aTag){
	CCNode* container=this->getContainer();
	CCNode* child=NULL;
	if (container)
		child=container->getChildByTag(aTag);
	else
		child=this->getChildByTag(aTag);
	return child;
}