//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//  Type: Scroll to page

#include <cocos2d.h>
#include   "../include/CPageScroll.h"

using namespace cocos2d;

/*
	Class:CPageScroll
*/
CPageScroll* CPageScroll::create(const cocos2d::CCSize &viewsz,int pagecount,CPageScrollDelegate* delegate){
	CPageScroll* cs=new CPageScroll();
	if (cs&&cs->init(viewsz,pagecount,delegate))
	{
		cs->autorelease();
		return cs;
	}
	delete cs;
	return 0;
}
bool CPageScroll::init(const cocos2d::CCSize &viewsz,int pagecount,CPageScrollDelegate* delegate){
	if (CCNode::init())
	{
		m_nPageCount=pagecount;
		m_pDelegate=delegate;
		setTouchEnabled(true);
		this->setContentSize(viewsz);
		m_pContainer=CCLayer::create();
		m_pContainer->setContentSize(viewsz);
		m_pContainer->setPosition(CCPointZero);
		this->addChild(m_pContainer);
		return true;
	}
	return false;
}

void CPageScroll::visit(){
	CCPoint screenPos = this->getParent()->convertToWorldSpace(this->getPosition());
	glEnable(GL_SCISSOR_TEST);
	float s = this->getScale();
	CCEGLView::sharedOpenGLView()->setScissorInPoints(screenPos.x*s, screenPos.y*s, m_pContainer->getContentSize().width*s, m_pContainer->getContentSize().height*s);
	CCNode::visit();
	glDisable(GL_SCISSOR_TEST);
}

void CPageScroll::registerWithTouchDispatcher(){
	CCLayer::registerWithTouchDispatcher();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,false);
}

bool CPageScroll::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	m_nDirection=kNOMOVE;
	return cContainsThePoint(pTouch);
}

bool CPageScroll::cContainsThePoint(CCTouch *pTouch){
	const CCSize& sz = this->getContentSize();
	const CCPoint& anchor = this->getAnchorPoint();
	CCRect rect = CCRectMake(0-sz.width*anchor.x,0-sz.height*anchor.y,sz.width,sz.height);
	const CCPoint &cp_touch=convertTouchToNodeSpaceAR(pTouch);
	bool isContaion=rect.containsPoint(cp_touch);
	std::cout<<"CPageScroll::ccTouchBegan  return : "<<isContaion<<std::endl;
	m_bTouchInArea = isContaion;
	return isContaion;
}

void CPageScroll::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
	//move this layer with the direction of touch
	const CCPoint &cp_previous=pTouch->getPreviousLocation();
	const CCPoint &cp_current=pTouch->getLocation();
	float dis_x=cp_previous.x-cp_current.x;
	m_pContainer->setPositionX(m_pContainer->getPositionX()-dis_x);
	m_bContainerHasMoved = true;
	//
// 	if(dis_x>0)
// 		m_nDirection=kNEXTPAGE;
// 	else if(dis_x<0)
// 		m_nDirection=kLASTPAGE;
// 	else if(dis_x==0)
// 		m_nDirection=kNOMOVE;
	
}
void CPageScroll::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
	//if reach the begin point of next page,go to next page
	//else restore to the begion point of this page
	//获得方向
	const CCPoint & p_begin = pTouch->getStartLocation();
	const CCPoint & p_end = pTouch->getLocation();
	float dx = p_begin.x - p_end.x;
	if(dx > m_iMoveDist)
		m_nDirection = kNEXTPAGE;
	else if(dx < -m_iMoveDist)
		m_nDirection = kLASTPAGE;
	else
	{
		m_nDirection = kNOMOVE;
	}

	float containerwidth=m_pContainer->getContentSize().width;
	float posx=m_pContainer->getPositionX();
	float posy=m_pContainer->getPositionY();
	float endPosX=-(m_nPageCount-1)*containerwidth;
	//
	float newPosX=0;
	if (m_nDirection==kLASTPAGE){
		if(posx >= 0||posx+containerwidth>0){
			newPosX=0;	//check if reach the top
			m_nCurrPageNum=0;
		}
		else{
			float page=-posx/containerwidth;
			int nPage=(int)page;
			//if(nPage!=page)nPage;//1011,fj
			//newPosX=-nPage*containerwidth;
			//m_nCurrPageNum--;

			m_nCurrPageNum = nPage;
			newPosX = -m_nCurrPageNum * containerwidth;
		}
	}
	else if(m_nDirection==kNEXTPAGE){
		if (posx <= endPosX||posx<-m_nPageCount*containerwidth){
			newPosX=endPosX;
			//m_nCurrPageNum=m_nPageCount;
			m_nCurrPageNum = m_nPageCount - 1;
		}
		else{
			float page=-posx/containerwidth;
			int nPage=(int)page;
			//if(nPage!=page)nPage+=1;//1011,fj
			//newPosX=-nPage*containerwidth;
			//m_nCurrPageNum++;

			if(nPage != page)	m_nCurrPageNum = nPage + 1;
			newPosX = -m_nCurrPageNum * containerwidth;
		}
	}
	else if(m_nDirection == kNOMOVE)
	{
		newPosX = m_pContainer->getPositionX() + dx;
	}

	if(m_bContainerHasMoved)
	{
		m_pContainer->setPositionX(newPosX);
		m_bContainerHasMoved = false;
	}

	m_pDelegate->changePage(m_nCurrPageNum);
}

void CPageScroll::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	ccTouchEnded(pTouch, pEvent);
}

//move to given page num. working well.
void CPageScroll::moveToPage(int page)
{
	float containerwidth=m_pContainer->getContentSize().width;
	float newPosX = -page * containerwidth;
	m_nCurrPageNum = page;
	m_pContainer->setPositionX(newPosX);
	m_pDelegate->changePage(m_nCurrPageNum);

}