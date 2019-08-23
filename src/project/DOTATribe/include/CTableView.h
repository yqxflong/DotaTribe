//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//  Type: Override CCTableView to add Priority
//
#ifndef  _DOTATRIBE_CTableView_H_
#define  _DOTATRIBE_CTableView_H_
#include "cocos2d.h"
#include "cocos-ext.h"

class TableViewSourceDelegate : public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
{
private:
	int m_nScriptCellSizeForIndex;
	int m_nScriptCellAtIndex;
	int m_nScriptNumberOfCells;
	int m_nScriptScrollViewDidScroll;

public:
	cocos2d::extension::CCTableViewCell * m_pCell;
	cocos2d::CCSize m_nCellSize;
	int m_nCellNumbers;

public:
	TableViewSourceDelegate()
	{
		m_nScriptCellSizeForIndex = 0;
		m_nScriptCellAtIndex = 0;
		m_nScriptNumberOfCells = 0;
		m_nScriptScrollViewDidScroll = 0;

		m_pCell = NULL;
		m_nCellSize = cocos2d::CCSizeZero;
		m_nCellNumbers = 0;
	}

public:
	virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){		};
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view);
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){		};

	void registerScript(int cellSizeForIndex, int tableCellAtIndex, int numberOfCellsInTableView, int scrollViewDidScroll);

};


class CTableView:public cocos2d::extension::CCTableView
{
	int m_nPriority;
	bool m_bSwallow;

	TableViewSourceDelegate * m_pSourceDelegate;
public:
	CTableView(){
		m_nPriority=0;
		m_pSourceDelegate = NULL;
	};
	virtual ~CTableView(){
		if(m_pSourceDelegate)
		{
			delete m_pSourceDelegate;
			m_pSourceDelegate = NULL;
		}

	};
	static CTableView* create(cocos2d::extension::CCTableViewDataSource* dataSource, cocos2d::CCSize size,int priority=0,bool swallow=true);
	bool init(cocos2d::extension::CCTableViewDataSource* dataSource, cocos2d::CCSize size,int priority,bool swallow);
	//
	virtual void registerWithTouchDispatcher()
	{
		cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
		pDirector->getTouchDispatcher()->addTargetedDelegate(this, m_nPriority, m_bSwallow);
	}
	//
	int getPriority() const{
		return m_nPriority;
	}

	TableViewSourceDelegate * getMyDelegate();
};

//======================CScrollView=====================
class CScrollView:public cocos2d::extension::CCScrollView{
	int m_nPriority;
	bool m_bSwallow;
public:
	CScrollView(){
		m_nPriority=0;
	};
	virtual ~CScrollView(){};
	static CScrollView* create(int priority=0,bool swallow=true);
	bool init(int priority,bool swallow);
	//
	virtual void registerWithTouchDispatcher()
	{
		cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
		pDirector->getTouchDispatcher()->addTargetedDelegate(this, m_nPriority, m_bSwallow);
	}
	//
	int getPriority() const{
		return m_nPriority;
	}

	//加入内容
	void addText(cocos2d::CCNode* content);
	//重新设置contentsize
	void resizeContent(cocos2d::CCNode* content);
};


//======================CMapScrollView=====================
/*
	用于做为滚动map的控件
*/
class CMapScrollView:public cocos2d::extension::CCScrollView{
	int m_nPriority;
	bool m_bSwallow;
public:
	CMapScrollView(){
		m_nPriority=0;
	};
	virtual ~CMapScrollView(){};
	static CMapScrollView* create(const cocos2d::CCSize& sz,int priority=0,bool swallow=true);
	bool initWithViewSize(const cocos2d::CCSize& sz ,int priority,bool swallow);
	//
	virtual void registerWithTouchDispatcher()
	{
		cocos2d::CCDirector* pDirector = cocos2d::CCDirector::sharedDirector();
		pDirector->getTouchDispatcher()->addTargetedDelegate(this, m_nPriority, m_bSwallow);
	}
	//
	int getPriority() const{
		return m_nPriority;
	}

	//重写父类函数
	virtual cocos2d::CCNode* getChildByTag(int aTag);
};
#endif