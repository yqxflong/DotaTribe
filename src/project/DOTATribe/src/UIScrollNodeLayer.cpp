////////////////////////////////////////////////////////////////
//Name:	 UIScrollNodeLayer
//Auchor: 	xiaobo.wu
//Func:	 滑动结点层
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////
#include "../include/UIScrollNodeLayer.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"

#define ROLEMOVETIME   0.5f


UIScrollNodeLayer::UIScrollNodeLayer()
{
    CCLOG("UIScrollLayer Construct!");
	isMoveEnable_=true;
	touchPriority_=-100;
	minmumTouchLengthToSlider_=30.0f;
	middleWidth=cocos2d::CCDirector::sharedDirector()->getWinSize().width/2;
	midldleHeight=cocos2d::CCDirector::sharedDirector()->getWinSize().height/2;
	//middleWidth = 240.00;
	//midldleHeight = 160.00;
    memset(initWaitShowRoleIndex,0,sizeof(initWaitShowRoleIndex));
	memset(nextWaitShowRoleIndex,0,sizeof(nextWaitShowRoleIndex));
	middleSelectRoleIndex_=1;
	childrenCount_=0;
	 
}

UIScrollNodeLayer::~UIScrollNodeLayer()
{
    this->removeAllChildrenWithCleanup(true);
	CCLOG("UIScrollLayer Destruct!");
}

UIScrollNodeLayer *  UIScrollNodeLayer::CreateScrollNodeLayerWithArray(cocos2d::CCArray * pnodeArray,cocos2d::CCPoint centerPoint,cocos2d::CCSize contenSize)
{
   UIScrollNodeLayer * pScrollNodeLayer=new UIScrollNodeLayer();
   if(pScrollNodeLayer&&pScrollNodeLayer->InitWithScrollNodeLayerWithArray(pnodeArray,centerPoint,contenSize))
   {
      pScrollNodeLayer->autorelease();
	  return pScrollNodeLayer;
   }
   if(pScrollNodeLayer==NULL)
   {
	   delete pScrollNodeLayer;
	   pScrollNodeLayer=NULL;
   }
   return NULL;
}

bool   UIScrollNodeLayer::InitWithScrollNodeLayerWithArray(cocos2d::CCArray * pnodeArray,cocos2d::CCPoint centerPoint,cocos2d::CCSize contenSize)
{  
   isMoveEnable_=true;
   touchPriority_=0;
   minmumTouchLengthToSlider_=30.0f;
   if(pnodeArray->count()<=0)
   {
	   return false;
   }
   
   if(centerPoint.x==CCPointZero.x&&centerPoint.y==centerPoint.y&&contenSize.width==CCSizeZero.width&&contenSize.height==CCSizeZero.height)
   { 
	  //默认设置
	  CCLayer::init();
      scissorRect_=cocos2d::CCRect(0,0,this->getContentSize().width,this->getContentSize().height); 
   }
   else
   {
	   ignoreAnchorPointForPosition(true);
	   setAnchorPoint(ccp(0.0f,0.0f));
	   setPosition(centerPoint);
	   setContentSize(contenSize);
	   scissorRect_=cocos2d::CCRect(0,0,contenSize.width,contenSize.height); 
   }

   initNodeLayOut();
  // CCSize contentSize=this->getContentSize();

   //自动组合Node  
   //根据children 从左至右的排序
   for(int i=0;i < (int)pnodeArray->count();i++)
   {
	  CCNode * pChildItem=dynamic_cast<CCNode *>(pnodeArray->objectAtIndex(i));
	  if(pChildItem!=NULL)
	  {  
	      this->addChild(pChildItem,2,i+1);  //重点注意的地方
		  pChildItem->setVisible(false);
	  }
   }
   childrenCount_=this->getChildren()->count();  
   OnInitShowNode();

   return  true;
}

void  UIScrollNodeLayer::onEnter()
{
	// then iterate over all the children
	CCLayer::onEnter();
	if(isMoveEnable_)
	{
		cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,touchPriority_,false);
	}
}

void  UIScrollNodeLayer::onExit()
{
	// then iterate over all the children
	CCLayer::onExit();
	if(isMoveEnable_)
	{
		cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	}
}

bool UIScrollNodeLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	cocos2d::CCPoint touchPosition=pTouch->getLocationInView();
	touchPosition=cocos2d::CCDirector::sharedDirector()->convertToGL(touchPosition);
 
	startSwipe_=touchPosition.x;
	state_=KCCScrollNodeLayerStateIdle; 
	return true;
}

void UIScrollNodeLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	if(isMoveEnable_)
	{
		cocos2d::CCPoint touchPosition=pTouch->getLocationInView();
		touchPosition=cocos2d::CCDirector::sharedDirector()->convertToGL(touchPosition);
		if ( (state_ != KCCScrollNodeLayerStateSliding) 
			&& (fabsf(touchPosition.x-startSwipe_)>minmumTouchLengthToSlider_) )
		{
			state_ = KCCScrollNodeLayerStateSliding;
			startSwipe_ = touchPosition.x;
			//丢弃本次消息，模拟TouchBegin
			this->cancelAndStoreTouch(pTouch,pEvent);	
		}
	}
}


void UIScrollNodeLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	cocos2d::CCPoint touchPosition=pTouch->getLocationInView();
	touchPosition=cocos2d::CCDirector::sharedDirector()->convertToGL(touchPosition);
	float newX = touchPosition.x;	
	if(isMoveEnable_)
	{
		if ( (newX - startSwipe_) <= -minmumTouchLengthToSlider_)
		{		
		   CCLOG("ccTouchEnded!  left");
		   OnShowNodeLeft();
		}
		else if ( (newX - startSwipe_) >= minmumTouchLengthToSlider_)
		{
		   CCLOG("ccTouchEnded!  right");
		   OnshowNodeRight();
		}
		else
		{
			CCLOG("ccTouchEnded! nothing ");
		}
	} 
}

void UIScrollNodeLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{

}

void  UIScrollNodeLayer::claimTouch(cocos2d::CCTouch * pTouch)
{
	cocos2d::CCTouchHandler * pTouchHandler=cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->findHandler(this);
	if(pTouchHandler!=NULL)
	{
		cocos2d::CCTargetedTouchHandler  * pTargetTouchHandler=(cocos2d::CCTargetedTouchHandler *)pTouchHandler;
		if(!pTargetTouchHandler->getClaimedTouches()->containsObject(pTouch))
		{
			pTargetTouchHandler->getClaimedTouches()->addObject(pTouch);
		}
	}	 
}

void UIScrollNodeLayer::cancelAndStoreTouch(cocos2d::CCTouch * pTouch, cocos2d::CCEvent * pEvent)
{
	cocos2d::CCSet * pSetArray=new CCSet();
	pSetArray->autorelease();
	pSetArray->addObject(pTouch);	 
	cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->touchesCancelled(pSetArray,pEvent);
	this->claimTouch(pTouch);
}


//void  UIScrollNodeLayer::visit()
//{
//	kmGLPushMatrix();
//	glEnable(GL_SCISSOR_TEST);
//	//glScissor(scissorRect_.origin.x,scissorRect_.origin.y,scissorRect_.size.width,scissorRect_.size.height);
//	//glScissor(0,0,middleWidth*2,midldleHeight*2);
//	cocos2d::CCNode::visit(); //ergodic all children
//	glDisable(GL_SCISSOR_TEST);
//	kmGLPopMatrix();
//}


void   UIScrollNodeLayer::initNodeLayOut()
{
	//postion lay out
	CCPoint  layOutPosArray[SCROLLNODELAYERITEM]={CCPointZero};
	//layOutPosArray[0]=ccp(middleWidth-350,midldleHeight+145);
	//layOutPosArray[1]=ccp(middleWidth-250,midldleHeight+100);
	//layOutPosArray[2]=ccp(middleWidth-150,midldleHeight+65);
	//layOutPosArray[3]=ccp(middleWidth,midldleHeight);
	//layOutPosArray[4]=ccp(middleWidth+150,midldleHeight+65);
	//layOutPosArray[5]=ccp(middleWidth+250,midldleHeight+100);
	//layOutPosArray[6]=ccp(middleWidth+350,midldleHeight+145);

	layOutPosArray[0]=ccp(middleWidth-450,midldleHeight-50);
	layOutPosArray[1]=ccp(middleWidth-300,midldleHeight-50);
	layOutPosArray[2]=ccp(middleWidth-150,midldleHeight-50);
	layOutPosArray[3]=ccp(middleWidth,midldleHeight-50);
	layOutPosArray[4]=ccp(middleWidth+150,midldleHeight-50);
	layOutPosArray[5]=ccp(middleWidth+300,midldleHeight-50);
	layOutPosArray[6]=ccp(middleWidth+450,midldleHeight-50);

	//scale lay out
	float  layOutScaleArray[SCROLLNODELAYERITEM]={0.0f};
	//layOutScaleArray[0]=0.7f;
	//layOutScaleArray[1]=0.8f;
	//layOutScaleArray[2]=0.9f;
	//layOutScaleArray[3]=1.0f;
	//layOutScaleArray[4]=0.9f;
	//layOutScaleArray[5]=0.8f;
	//layOutScaleArray[6]=0.7f;

	layOutScaleArray[0]=0.8f;
	layOutScaleArray[1]=0.8f;
	layOutScaleArray[2]=0.8f;
	layOutScaleArray[3]=0.8f;
	layOutScaleArray[4]=0.8f;
	layOutScaleArray[5]=0.8f;
	layOutScaleArray[6]=0.8f;

	for(int i=0;i<SCROLLNODELAYERITEM;i++)
	{
		NODEDATA  tmpNode;
		tmpNode.roleIndex_=i+1;
		tmpNode.scaleParam_=layOutScaleArray[i];
		tmpNode.potionParam_=layOutPosArray[i];
		nodeLayOutVector_.push_back(tmpNode);
	}
}


void   UIScrollNodeLayer::initWaitShowNodeArray()
{
	int  tempValue=1;
	for(int i=SCROLLNODELAYERITEM/2;i>=0;i--)
	{
		initWaitShowRoleIndex[i]=tempValue++;
	}
	tempValue=childrenCount_;
	for(int j=SCROLLNODELAYERITEM/2+1;j<SCROLLNODELAYERITEM;j++)
	{
		initWaitShowRoleIndex[j]=tempValue--;
	}
}
void   UIScrollNodeLayer::nextWaitShowNodeArrayForLeft()
{
	int  nextTempValue=middleSelectRoleIndex_-1;
	nextTempValue=nextTempValue<=0 ? childrenCount_:nextTempValue;

	for(int i=SCROLLNODELAYERITEM/2;i>=0;i--)
	{
		nextWaitShowRoleIndex[i]=nextTempValue++;
		nextTempValue = nextTempValue>(int)childrenCount_? 1:nextTempValue;
	}
	nextTempValue=middleSelectRoleIndex_-1<=0 ? childrenCount_:middleSelectRoleIndex_-1;
	nextTempValue=nextTempValue-1<=0 ?   childrenCount_:nextTempValue-1;

	for(int j=SCROLLNODELAYERITEM/2+1;j<SCROLLNODELAYERITEM;j++)
	{
		nextWaitShowRoleIndex[j]=nextTempValue--;
		nextTempValue = nextTempValue<=0 ? childrenCount_:nextTempValue;
	}
}

void   UIScrollNodeLayer::nextWaitShowNodeArrayForRight()
{
	int  nextTempValue=middleSelectRoleIndex_+1;
	nextTempValue=nextTempValue>(int)childrenCount_? 1:nextTempValue;

	for(int i=SCROLLNODELAYERITEM/2;i>=0;i--)
	{
		nextWaitShowRoleIndex[i]=nextTempValue++;
		nextTempValue=nextTempValue>(int)childrenCount_? 1:nextTempValue;
	}
	nextTempValue=middleSelectRoleIndex_;
	for(int j=SCROLLNODELAYERITEM/2+1;j<SCROLLNODELAYERITEM;j++)
	{
		nextWaitShowRoleIndex[j]=nextTempValue--;
		nextTempValue=nextTempValue<=0 ? childrenCount_:nextTempValue;
	}
}


void  UIScrollNodeLayer::OnInitShowNode()
{
	initWaitShowNodeArray();

	for(int i=0;i<SCROLLNODELAYERITEM;i++)
	{
		NODEDATA tmpNode=nodeLayOutVector_.at(i);
		int  nodeIndex=initWaitShowRoleIndex[i];
		CCNode * pNode=getChildByTag(nodeIndex);
		if(pNode!=NULL)
		{
			pNode->setVisible(true);
			pNode->setScale(tmpNode.scaleParam_);
			pNode->setPosition(tmpNode.potionParam_);
	
		}
	}
}

void UIScrollNodeLayer::OnShowNodeLeft()
{
	nextWaitShowNodeArrayForLeft();
	middleSelectRoleIndex_= middleSelectRoleIndex_-1 <= 0 ? childrenCount_:middleSelectRoleIndex_-1;
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_COMMOND_TURNLEFT_, _to_event_param_(middleSelectRoleIndex_));	

	//清理位置
	for(int i=0;i<(int)childrenCount_;i++)
	{
		CCNode * pNode=(CCNode*)this->getChildren()->objectAtIndex(i);
		if(pNode->getPosition().x==nodeLayOutVector_.at(0).potionParam_.x)
		{
			pNode->setVisible(false);
		} 
	}

	for(int i=0;i<SCROLLNODELAYERITEM-1;i++)
	{
		NODEDATA tmpNode=nodeLayOutVector_.at(i);
		int  nodeIndex=nextWaitShowRoleIndex[i];
		CCLOG("%d", nodeIndex);
		CCNode * pNode=getChildByTag(nodeIndex);

		if(pNode!=NULL)
		{
			pNode->setVisible(true);
			pNode->setScale(tmpNode.scaleParam_);
			pNode->stopAllActions();
			pNode->runAction(CCMoveTo::create(ROLEMOVETIME, tmpNode.potionParam_ ));
		}
		if (nodeIndex == middleSelectRoleIndex_)
		{
			pNode->setScale(1.1f);	
		}
	}

	//最左边人物滑动效果
	NODEDATA tmpNodeLast=nodeLayOutVector_.at(SCROLLNODELAYERITEM-1);
	int nodeIndexLast = nextWaitShowRoleIndex[SCROLLNODELAYERITEM-1];
	CCLOG("%d", nodeIndexLast);
	CCNode *pNodeLast = getChildByTag(nodeIndexLast);
	if (pNodeLast != NULL)
	{
		pNodeLast->setVisible(true);
		pNodeLast->setScale(tmpNodeLast.scaleParam_);
		pNodeLast->setPosition(tmpNodeLast.potionParam_);

	}

}

void UIScrollNodeLayer::OnshowNodeRight()
{
	nextWaitShowNodeArrayForRight();
	middleSelectRoleIndex_ = middleSelectRoleIndex_+1 > (int)childrenCount_ ? 1:middleSelectRoleIndex_+1;
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_COMMOND_TURNRIGHT_, _to_event_param_(middleSelectRoleIndex_));

	//清理位置
	for(int i=0;i<(int)childrenCount_;i++)
	{
		CCNode * pNode=(CCNode*)this->getChildren()->objectAtIndex(i);
		if(pNode->getPosition().x==nodeLayOutVector_.at(SCROLLNODELAYERITEM-1).potionParam_.x)
		{
			pNode->setVisible(false);
		} 

	}

	for(int i=0;i<SCROLLNODELAYERITEM;i++)
	{

		//最后一个人物滑动效果
		if (i == 0)
		{
			NODEDATA tmpNodeLast=nodeLayOutVector_.at(i);
			int nodeIndexLast = nextWaitShowRoleIndex[i];
			CCLOG("%d", nodeIndexLast);
			CCNode *pNodeLast = getChildByTag(nodeIndexLast);
			if (pNodeLast != NULL)
			{
				pNodeLast->setVisible(true);
				pNodeLast->setScale(tmpNodeLast.scaleParam_);
				pNodeLast->setPosition(tmpNodeLast.potionParam_);

			}
			if (nodeIndexLast == middleSelectRoleIndex_)
			{
				pNodeLast->setScale(1.1f);
			}
		}
		else
		{
			NODEDATA tmpNode=nodeLayOutVector_.at(i);
			int  nodeIndex=nextWaitShowRoleIndex[i];
			CCLOG("%d", nodeIndex);
			CCNode * pNode=getChildByTag(nodeIndex);
			if(pNode!=NULL)
			{
				pNode->setVisible(true);
				pNode->setScale(tmpNode.scaleParam_);
				pNode->stopAllActions();
				pNode->runAction(CCMoveTo::create(ROLEMOVETIME, tmpNode.potionParam_));
			}
			if (nodeIndex == middleSelectRoleIndex_)
			{
				pNode->setScale(1.1f);
			}
		}	
	}

}

int UIScrollNodeLayer::GetMiddleSelectRoleIndex()
{
	return middleSelectRoleIndex_;
}









 

