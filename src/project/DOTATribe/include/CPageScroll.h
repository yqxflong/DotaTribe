//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//  Type: Scroll to page
//Notes:	Anchor(0,0)
#ifndef __PUBLIC__CPAGESCROLL__
#define __PUBLIC__CPAGESCROLL__
 
#include <cocos2d.h>
#include <list>

class CPageScrollDelegate
{
public:
	virtual void changePage(int idx)=0;
};

/*
	Class:CPageScroll
*/
class  CPageScroll: public cocos2d::CCLayer
{
private:
	enum{
		kNOMOVE=0,
		kNEXTPAGE,
		kLASTPAGE,
	};
	int m_nPageCount;
	int m_nDirection;		
	CCNode* m_pContainer;
	int m_nCurrPageNum;		//record current index of pages
	CPageScrollDelegate* m_pDelegate;

	int m_iMoveDist;//移动多远才算翻页

	bool m_bTouchInArea;//点击区域中

	bool m_bContainerHasMoved;//容器是否已经移动过
public:
	CPageScroll(){
		m_nPageCount=0;
		m_nDirection=0;
		m_pContainer=0;
		m_nCurrPageNum=0;
		m_pDelegate=0;
		m_iMoveDist = 10;
		m_bTouchInArea = false;
		m_bContainerHasMoved =false;
	};
	virtual ~CPageScroll(){
		m_nPageCount=0;
		m_nDirection=0;
		m_pContainer=0;
		m_nCurrPageNum=0;
		m_pDelegate=0;
		m_bTouchInArea = false;
		m_bContainerHasMoved =false;
	};
	 /*
		the view size is container size
	 */
	 static CPageScroll* create(const cocos2d::CCSize &viewsz,int pagecount,CPageScrollDelegate* delegate);
	 bool init(const cocos2d::CCSize &viewsz,int pagecount,CPageScrollDelegate* delegate);
	 /*
		Get the container layer
	 */
	 cocos2d::CCNode* getContainer() const{
		 return m_pContainer;
	 }

	 //点击事件是否在区域中
	 bool isTouchInArea()
	 {
		 return m_bTouchInArea;
	 }
	 /*
		go to the given page num.add by fj
	 */
	 void moveToPage(int page);

protected:
	virtual void visit();
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	bool cContainsThePoint(cocos2d::CCTouch *pTouch);
};

#endif