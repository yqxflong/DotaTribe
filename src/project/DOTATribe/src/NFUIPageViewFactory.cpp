//Name: NFUIPageViewFactory
//Func: Used to Create UIPageView
//Written by: Johny

#include "../include/NFUIPageViewFactory.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

/*
	---->UIPageView
*/
cocos2d::CCNode* NFUIPageViewFactory::createNode(cocos2d::CCNode* parentNode,UIViewData* dd){
	TouchGroup* tg=TouchGroup::create();
	UIPageView* pv=UIPageView::create();
	pv->setTag(0);
	tg->addWidget(pv);
	tg->setTouchPriority(dd->touchpriority_);
	tg->setSwallowsTouches(dd->swallow_==0?false:true);
	tg->setVisible(dd->hide_==0?true:false);
	tg->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
	tg->setPosition(ccp(dd->posx_,dd->posy_));
	parentNode->addChild(tg,dd->zorder_,dd->idx_);

	return tg;
}