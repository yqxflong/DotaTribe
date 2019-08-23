////////////////////////////////////////////////////////////////
//Name:	 UITwoSileStretchNodeLayer
//Auchor: 	xiaobo.wu
//Func:	 双向拉伸结点层
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////
#include  "../include/UITwoSideStretchNodeLayer.h"
#include  "../include/PreCCMoveTo.h"
using namespace cocos2d;

#define  NORMALORDER   1
#define  SELECTORDER   2

#define  LEFTNORMALTAG     11
#define  LEFTSELECTTAG     12
 
#define  RIGHTNORMALTAG    21
#define  RIGHTSELECTTAG    22

UITowSideStretchNodeLayer::UITowSideStretchNodeLayer()
{
     touchPriority_=0;
	 isTouchEnable_=true;
	 normalstretchTime_=0.2f;
	 selectstretchTime_=0.2f;
	 
	 leftNormalNode_=NULL;
	 leftSelectedNode_=NULL;
	 rightNormalNode_=NULL;
	 rightSelectedNode_=NULL;
 
	 isLeftNormalVisible_=false; 
	 isLeftSelectedVisible_=false;
	 isRightNormalVisible_=false;
	 isRIghtSelectedVisible_=false;

	 normalWidth_=0.0f;
	 selectedWidth_=0.0f;
	 normalYPos_=0.0f;
	 selectedYPos_=0.0f;

}

UITowSideStretchNodeLayer::~UITowSideStretchNodeLayer()
{
	 CCLOG("UITowSideStretchNodeLayer destroy!");
	 this->removeAllChildrenWithCleanup(true);
	 this->removeFromParentAndCleanup(true);
}


UITowSideStretchNodeLayer *  UITowSideStretchNodeLayer::createTowSideStretchLayer(cocos2d::CCNode * leftNormalNode,cocos2d::CCNode * leftSelectedNode,cocos2d::CCNode * rightNormalNode,cocos2d::CCNode * rightSelectedNode)
{
	UITowSideStretchNodeLayer  *  pStretchNodeLayer=new UITowSideStretchNodeLayer();
	if(pStretchNodeLayer&&pStretchNodeLayer->initTwoSideStretchLayer(leftNormalNode,leftSelectedNode,rightNormalNode,rightSelectedNode))
	{
		pStretchNodeLayer->autorelease();
		 return pStretchNodeLayer;
	}
	if(pStretchNodeLayer!=NULL)
	{
		delete pStretchNodeLayer;
		pStretchNodeLayer=NULL;
	} 
	return NULL;
}

bool   UITowSideStretchNodeLayer::initTwoSideStretchLayer(cocos2d::CCNode * leftNormalNode,cocos2d::CCNode * leftSelectedNode,cocos2d::CCNode * rightNormalNode,cocos2d::CCNode * rightSelectedNode)
{   

    setLeftNormalNode(leftNormalNode);
	setleftSelectNode(leftSelectedNode);
	isLeftNormalVisible_=true; 
	isLeftSelectedVisible_=false;

	setRightNormalNode(rightNormalNode);
	setRightSelectNode(rightSelectedNode);
	isRightNormalVisible_=true;
	isRIghtSelectedVisible_=false;

	return true;
} 
void  UITowSideStretchNodeLayer::onEnter()
{
	cocos2d::CCLayer::onEnter();
	if(isTouchEnable_)
	{
	    cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,touchPriority_,false);
	}
} 
void  UITowSideStretchNodeLayer::onExit()
{
	cocos2d::CCLayer::onExit();
	if(isTouchEnable_)
	{
		cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	}
} 


bool  UITowSideStretchNodeLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
     return true;
} 

void  UITowSideStretchNodeLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	//暂时没有使用Move
} 
void  UITowSideStretchNodeLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if(containTouchOnLeftRect(pTouch))
	{ 
		if(isLeftSelectedVisible_)
		{
			onShowShrinkNode(true);
			onShowShrinkNode(false);
		}
		return ;
	}
	else if(containTouchOnRightRect(pTouch))
	{
		if(isRIghtSelectedVisible_)
		{
			onShowShrinkNode(false);
			onShowShrinkNode(true);
		}
		return ;
	}
}

bool   UITowSideStretchNodeLayer::onShowUnfoldNode(bool isLeft)  //展开
{
	if(isLeft)
	{
		if(getChildByTag(LEFTNORMALTAG)!=NULL)
		{
			CCMenu * pNode=(CCMenu *)getChildByTag(LEFTNORMALTAG);
			pNode->setTouchEnabled(false);
			pNode->runAction(PreCCMoveTo::create(normalstretchTime_,ccp(-1.0f*normalWidth_,pNode->getPositionY())));
			isLeftNormalVisible_=false;
		}
		if(getChildByTag(LEFTSELECTTAG)!=NULL)
		{
			CCNode * pChildNode=getChildByTag(LEFTSELECTTAG);
			pChildNode->setVisible(true);
			if(pChildNode!=NULL)
			{
				pChildNode->runAction(PreCCMoveTo::create(selectstretchTime_,ccp(-1,pChildNode->getPositionY())));
			}
			isLeftSelectedVisible_=true;
		}
	}
	else
	{
		if(getChildByTag(RIGHTNORMALTAG)!=NULL)
		{
			CCMenu * pNode=(CCMenu *)getChildByTag(RIGHTNORMALTAG);
			pNode->setTouchEnabled(false);
			pNode->runAction(PreCCMoveTo::create(normalstretchTime_,ccp(cocos2d::CCDirector::sharedDirector()->getWinSize().width+1,pNode->getPositionY())));
			isRightNormalVisible_=false;
		}
		if(getChildByTag(RIGHTSELECTTAG)!=NULL)
		{
			CCNode * pChildNode=getChildByTag(RIGHTSELECTTAG);
			if(pChildNode!=NULL)
			{ 
				pChildNode->runAction(PreCCMoveTo::create(selectstretchTime_,ccp(cocos2d::CCDirector::sharedDirector()->getWinSize().width-selectedWidth_+1,pChildNode->getPositionY())));
			}
			isRIghtSelectedVisible_=true;
		}
	}
	return true;
}

bool   UITowSideStretchNodeLayer::onShowShrinkNode(bool isLeft)  //收缩 
{ 
	if(isLeft)
	{
		if(getChildByTag(LEFTSELECTTAG)!=NULL)
		{
			CCNode * pChildNode=getChildByTag(LEFTSELECTTAG);
			pChildNode->setVisible(true);
			if(pChildNode!=NULL)
			{
				pChildNode->runAction(PreCCMoveTo::create(selectstretchTime_,ccp(-1.0f*selectedWidth_,pChildNode->getPositionY())));
			}
			isLeftSelectedVisible_=false;
		}
		if(getChildByTag(LEFTNORMALTAG)!=NULL)
		{
			CCMenu * pNode=(CCMenu *)getChildByTag(LEFTNORMALTAG);
			pNode->setTouchEnabled(true);
			pNode->runAction(PreCCMoveTo::create(normalstretchTime_,ccp(-1,pNode->getPositionY())));
			isLeftNormalVisible_=true;
		}
	}
	else
	{
		if(getChildByTag(RIGHTSELECTTAG)!=NULL)
		{
			CCNode * pChildNode=getChildByTag(RIGHTSELECTTAG);
			if(pChildNode!=NULL)
			{
				pChildNode->runAction(PreCCMoveTo::create(selectstretchTime_,ccp(cocos2d::CCDirector::sharedDirector()->getWinSize().width+1,pChildNode->getPositionY())));
			}
			isRIghtSelectedVisible_=false;
		}
		if(getChildByTag(RIGHTNORMALTAG)!=NULL)
		{
			CCMenu * pNode=(CCMenu *)getChildByTag(RIGHTNORMALTAG);
			pNode->setTouchEnabled(true);
			pNode->runAction(PreCCMoveTo::create(normalstretchTime_,ccp(cocos2d::CCDirector::sharedDirector()->getWinSize().width-normalWidth_+1,pNode->getPositionY())));
			isRightNormalVisible_=true;
		}
	}
	return true;
} 

//属性的Set
void   UITowSideStretchNodeLayer::setLeftNormalNode(cocos2d::CCNode * leftNormal)
{
	if(leftNormal!=leftNormalNode_)
	{
		leftNormalNode_=leftNormal;
		if(getChildByTag(LEFTNORMALTAG)!=NULL)
		{
			removeChildByTag(LEFTNORMALTAG,true);
		}
		if(leftNormalNode_!=NULL)
		{
			leftNormalNode_->setAnchorPoint(ccp(0,0));
			leftNormalNode_->setPosition(ccp(-1,normalYPos_));
			this->addChild(leftNormal,NORMALORDER,LEFTNORMALTAG);
		}
	}
}
void   UITowSideStretchNodeLayer::setleftSelectNode(cocos2d::CCNode * leftSelected)
{ 
	if(leftSelected!=leftSelectedNode_)
	{
		leftSelectedNode_=leftSelected;
		if(getChildByTag(LEFTSELECTTAG)!=NULL)
		{
			removeChildByTag(LEFTSELECTTAG,true);
		}
		if(leftSelectedNode_!=NULL)
		{ 
			leftSelectedNode_->setAnchorPoint(ccp(0,0));
           leftSelectedNode_->setPosition(ccp(-1.0f*selectedWidth_,selectedYPos_));
		   this->addChild(leftSelectedNode_,SELECTORDER,LEFTSELECTTAG);
		}
	}

}
void   UITowSideStretchNodeLayer::setRightNormalNode(cocos2d::CCNode * rightNormal)
{
	if(rightNormal!=rightNormalNode_)
	{
		rightNormalNode_=rightNormal;
		if(getChildByTag(RIGHTNORMALTAG)!=NULL)
		{
			removeChildByTag(RIGHTNORMALTAG,true);
		}
		if(rightNormalNode_!=NULL)
		{ 
			rightNormalNode_->setAnchorPoint(ccp(0,0));
			rightNormalNode_->setPosition(ccp(cocos2d::CCDirector::sharedDirector()->getWinSize().width-normalWidth_+1,normalYPos_));
			this->addChild(rightNormalNode_,NORMALORDER,RIGHTNORMALTAG);
		}
	}
}
void   UITowSideStretchNodeLayer::setRightSelectNode(cocos2d::CCNode * rightSelected)
{
	if(rightSelected!=rightSelectedNode_)
	{
		rightSelectedNode_=rightSelected;
		if(getChildByTag(RIGHTSELECTTAG)!=NULL)
		{
			removeChildByTag(RIGHTSELECTTAG,true);
		}
		if(rightSelectedNode_!=NULL)
		{
			rightSelectedNode_->setAnchorPoint(ccp(0,0));
            rightSelectedNode_->setPosition(ccp(cocos2d::CCDirector::sharedDirector()->getWinSize().width+1,selectedYPos_));
			this->addChild(rightSelectedNode_,SELECTORDER,RIGHTSELECTTAG);
		}
	}
}
void   UITowSideStretchNodeLayer::setStretchTime(float stretchTime)
{
	 if(normalstretchTime_!=stretchTime)
	 {
		 normalstretchTime_=stretchTime;
	 }
}
void   UITowSideStretchNodeLayer::setTouchEnable(bool touchEnable)
{
	if(isTouchEnable_!=touchEnable)
	{
		isTouchEnable_=touchEnable;
		if(isTouchEnable_)
		{
			cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,touchPriority_,false);
		}
		else
		{
			cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
		}
	}
}
void   UITowSideStretchNodeLayer::setTouchPriority(int touchPriority)
{
   if(touchPriority_!=touchPriority)
   {
	   touchPriority_=touchPriority;
   }
}



//属性的Get
cocos2d::CCNode *   UITowSideStretchNodeLayer::getLeftNormalNode()
{
	return leftNormalNode_;
}
cocos2d::CCNode *   UITowSideStretchNodeLayer::getleftSelectNode()
{
	return leftSelectedNode_;
}
cocos2d::CCNode *   UITowSideStretchNodeLayer::getRightNormalNode()
{
	return rightNormalNode_;
}
cocos2d::CCNode *   UITowSideStretchNodeLayer::getRightSelectedNode()
{
	return rightSelectedNode_;
}
float   UITowSideStretchNodeLayer::getStretchTime()
{
	return  normalstretchTime_;
}
bool    UITowSideStretchNodeLayer::getTouchEnable()
{
	return isTouchEnable_;
}
int     UITowSideStretchNodeLayer::getTouchPriority()
{
	return touchPriority_;
}


cocos2d::CCRect  UITowSideStretchNodeLayer::getLeftScreenRect()
{
   cocos2d::CCSize winSize=cocos2d::CCDirector::sharedDirector()->getWinSize();
   return CCRectMake(getPositionX(),getPositionY(),winSize.width/2,winSize.height);
}

cocos2d::CCRect  UITowSideStretchNodeLayer::getRightScreenRect()
{
   cocos2d::CCSize winSize=cocos2d::CCDirector::sharedDirector()->getWinSize();
   return CCRectMake(getPositionX()+winSize.width/2,getPositionY(),winSize.width/2,winSize.height);
}
bool   UITowSideStretchNodeLayer::containTouchOnLeftRect(cocos2d::CCTouch * pTouch)
{  
    cocos2d::CCPoint  touchPosition=pTouch->getLocationInView();
	touchPosition=cocos2d::CCDirector::sharedDirector()->convertToGL(touchPosition);
	return  getLeftScreenRect().containsPoint(touchPosition);
}
bool   UITowSideStretchNodeLayer::containTouchOnRightRect(cocos2d::CCTouch * pTouch)
{
	cocos2d::CCPoint  touchPosition=pTouch->getLocationInView();
	touchPosition=cocos2d::CCDirector::sharedDirector()->convertToGL(touchPosition);
	return  getRightScreenRect().containsPoint(touchPosition); 
} 


void   UITowSideStretchNodeLayer::setNormalAndSelectWith(float normalWidth,float selectWidth)
{
	if(normalWidth_!=normalWidth)
	{
		normalWidth_=normalWidth;
	}
	if(selectedWidth_!=selectWidth)
	{
       selectedWidth_=selectWidth;
	}
}
void   UITowSideStretchNodeLayer::setNormalAndSelectYPos(float normalYPos,float selectYPos)
{
	if(normalYPos_!=normalYPos)
	{
		normalYPos_=normalYPos;
	}
	if(selectedYPos_!=selectYPos)
	{
		selectedYPos_=selectYPos;
	}
}