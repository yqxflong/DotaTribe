//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//  Type: fit for experience,life,energy...
//

#include   "../include/CProgressInnerBar.h"

using namespace cocos2d;

CProgressInnerBar* CProgressInnerBar::create(const char *pszFileName){
	CProgressInnerBar* cc=new CProgressInnerBar();
	if (cc&&cc->init(pszFileName))
	{
		cc->autorelease();
		return cc;
	}
	delete cc;
	return 0;
}
bool CProgressInnerBar::init(const char *pszFileName){
	if (CCSprite::init())
	{
		setProperty("File",pszFileName);
		return true;
	}
	return false;
}


void CProgressInnerBar::visit(){
	const CCSize & sz=this->getContentSize();
	CCPoint screenPos = this->getParent()->convertToWorldSpace(this->getPosition());
	glEnable(GL_SCISSOR_TEST);
	float s = this->getScale();
	CCEGLView::sharedOpenGLView()->setScissorInPoints(screenPos.x*s, screenPos.y*s,sz.width*m_fPercent*s, sz.height*s);
	CCSprite::visit();
	glDisable(GL_SCISSOR_TEST);
}