//Author: xiaobo.wu
//Description:  拖拽结点类(支持Sprite变灰,延时拖拽)
//Date:  2013.06.30

#include  "../include/UIDragNode.h"
#include   "../include/InputCommand.h"

////////////////////////////////////////////////////////////////
//Name:	 UIDragNode
//Auchor: 	xiaobo.wu
//Func:	 拖拽结点
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////

using namespace cocos2d;

#define   MOVEZORDER     10
#define   NORAMLZORDER   6


UIDragNode::UIDragNode()
{
	 nodeIdentify_=0;						//结点标号
	 isDisable_=false;						//是否禁用
	 isDragEnable_=true;					//是否可以拖拽
	 isTouchEnable_=true;					//触摸使能
     startDragPoint_=CCPointZero;		    //开始拖拽的坐标
	 initLayoutPoint_=CCPointZero;			//初始化布局坐标
	 touchPriority_=-181;					//结点的触摸优先级别
	 curNodeState_=_UIDRAGNODE_UNKONW_TYPE_;
	 dragDelayTime_=0.11f;					//拖拽延时时间
	 dragNodeType_=_UIDRAGNODE_UNKONW_OBJTYPE_; //拖拽结点类型
	 pDelegateNode_=NULL;
}

UIDragNode::~UIDragNode()
{

}

UIDragNode  *  UIDragNode::createUIDragNodeWithFile(int identify,const char * fileName,bool isDisable/* =false */)
{
	UIDragNode *  pDragNode=new UIDragNode();
	if(pDragNode&&pDragNode->initUIDragNodeWithFile(identify,fileName,isDisable))
	{
		//暂时不使用autoRelease 因为DragPanel需要管理
		pDragNode->autorelease();
		return  pDragNode;
	}
	if(pDragNode!=NULL)
	{
		delete pDragNode;
		pDragNode=NULL;
	}
	return NULL;
}

UIDragNode  *  UIDragNode::createUIDragNodeWithFrame(int identify,cocos2d::CCSpriteFrame * spriteFrame,bool isDisable/* =false */)
{
	UIDragNode *  pDragNode=new UIDragNode();
	if(pDragNode&&pDragNode->initUIDragNodeWithFrame(identify,spriteFrame,isDisable))
	{
		//暂时不使用autoRelease 因为DragPanel需要管理
		return  pDragNode;
	}
	if(pDragNode!=NULL)
	{
		delete pDragNode;
		pDragNode=NULL;
	}
	return NULL;
}

UIDragNode *  UIDragNode::createUIDragNodeWithFrameName(int identify,const char * frameName,bool isDisable/* =false */)
{
	UIDragNode *  pDragNode=new UIDragNode();
	if(pDragNode&&pDragNode->initUIDragNodeWithFrameName(identify,frameName,isDisable))
	{
		//暂时不使用autoRelease 因为DragPanel需要管理
		return  pDragNode;
	}
	if(pDragNode!=NULL)
	{
		delete pDragNode;
		pDragNode=NULL;
	}
	return NULL;
}



//////////////////////////////////////////////////////////////////////////
bool   UIDragNode::initUIDragNodeWithFile(int identify,const char * fileName,bool isDisable)
{
	 if(identify<0||fileName==NULL)
		 return false;
	  if(initWithFile(fileName))
	  {
		  setDragNodeIdentify(identify);
		  setDragNodeIsDisable(isDisable);
		  curNodeState_=_UIDRAGNODE_IDLE_TYPE_;
		  return   true;
	  }
	 return false;
}


bool   UIDragNode::initUIDragNodeWithFrame(int identify,cocos2d::CCSpriteFrame * spriteFrame,bool isDisable)
{
	//暂时未使用之后 之后优化时候使用Plist时候再使用
     return false;
} 

bool   UIDragNode::initUIDragNodeWithFrameName(int identify,const char * frameName,bool isDisable)
{
    //暂时未实现 之后优化使用Plist时候使用
     return  false;
}


void    UIDragNode::onEnter()
{
	CCSprite::onEnter();

    if(isTouchEnable_)
	{
		cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,touchPriority_,false);
	}
}


void  UIDragNode::onExit()
{
	CCSprite::onExit();
	if(isTouchEnable_)
	{
		cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	}
}



bool	UIDragNode::ccCheckIsContainsTouchLocation(cocos2d::CCTouch *pTouch)
{
	cocos2d::CCRect  nodeRect=ccGetNodeRectWithAnchor();

	return  nodeRect.containsPoint(convertTouchToNodeSpaceAR(pTouch));
}

cocos2d::CCRect  UIDragNode::ccGetNodeRectWithAnchor(bool isUseAnchor)
{
	cocos2d::CCSize nodeSize=this->getContentSize();
	if(isUseAnchor)
	{
        return CCRectMake(-nodeSize.width/2,-nodeSize.height/2,nodeSize.width,nodeSize.height);
	}
	else
	{
        return CCRectMake(this->getPositionX()-nodeSize.width/2,this->getPositionY()-nodeSize.height/2,nodeSize.width,nodeSize.height);
	}
}

cocos2d::CCPoint  UIDragNode::converTouchToGLLocation(cocos2d::CCTouch *pTouch)
{
	if(pTouch!=NULL)
	{
		 return cocos2d::CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	}
	return cocos2d::CCPointZero;
}
 

bool	UIDragNode::ccCheckIsTouchClick(cocos2d::CCPoint touchPosition)
{
	if(touchPosition.x>=startDragPoint_.x-this->getContentSize().width/2&&touchPosition.x<=startDragPoint_.x+this->getContentSize().width/2&&
		touchPosition.y>=startDragPoint_.y-this->getContentSize().height/2&&touchPosition.y<=startDragPoint_.y+this->getContentSize().height/2)
	return  true;

	return false;
}




bool   UIDragNode::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if(ccCheckIsContainsTouchLocation(pTouch))
	{
		curNodeState_=_UIDRAGNODE_STARTDRAG_TYPE_;
		startDragPoint_=converTouchToGLLocation(pTouch); 
		CCLOG("Touch Begin HANDLER!");
		return true;
	}
	return false;
}

void   UIDragNode::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{ 
	if(isDragEnable_)
	{
		curNodeState_=_UIDRAGENODE_DRAGING_TYPE_;
		cocos2d::CCPoint movePosition=converTouchToGLLocation(pTouch); 
		this->getParent()->reorderChild(this,MOVEZORDER);
		//延时拖拽效果	 
	 	this->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(dragDelayTime_),CCPlace::create(movePosition))); 
	}
}

void   UIDragNode::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	 //mandatoryMoveToInitPosition();
	this->getParent()->reorderChild(this,NORAMLZORDER);
	this->stopAllActions();
	 if(isDragEnable_)
	 {
		 curNodeState_=_UIDRAGENODE_ENDDRAG_TYPE;
		 cocos2d::CCPoint endPosition=converTouchToGLLocation(pTouch); 
		 if(!ccCheckIsTouchClick(endPosition))
		 { 
			 this->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(dragDelayTime_),CCPlace::create(endPosition))); 
			 if(pDelegateNode_!=NULL)
			 {
				 pDelegateNode_->onCommandHandler(_TYPED_INPUT_COMMAND_DRAGNODE_DRAGEND_,this);
				 return ;
			 } 
		 }
		 else
		 {
			  CCLOG("Signel Click handler!");
			 if(pDelegateNode_!=NULL)
			 {
				 pDelegateNode_->onCommandHandler(_TYPED_INPUT_COMMAND_DRAGNODE_CLICK_,this);
				 return ;
			 }
		
		 }
	 }
	 else
	 {
		 curNodeState_=_UIDRAGENODE_ENDDRAG_TYPE;
		 cocos2d::CCPoint endPosition=converTouchToGLLocation(pTouch); 
		 if(ccCheckIsTouchClick(endPosition))
		 { 
			 CCLOG("Signel Click handler!");
			 if(pDelegateNode_!=NULL)
			 {
				 pDelegateNode_->onCommandHandler(_TYPED_INPUT_COMMAND_DRAGNODE_CLICK_,this);
				 return ;
			 }
		 }
	 }
}
 
void   UIDragNode::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	mandatoryMoveToInitPosition();
}



int     UIDragNode::getTouchPriority()
{ 
	 return touchPriority_;

}

void    UIDragNode::setTouchPriirity(int touchPriority)
{
    if(touchPriority_!=touchPriority)
	{
		touchPriority_=touchPriority;
	}
}


cocos2d::CCPoint &  UIDragNode::getDragNodeInitPosition()
{
	return initLayoutPoint_;
}
void	UIDragNode::setDragNodeInitPosition(cocos2d::CCPoint initPosition)
{
	initLayoutPoint_=initPosition;
    this->setPosition(initLayoutPoint_);
}


void    UIDragNode::setDragNodeIdentify(int  identify)
{ 
     if(nodeIdentify_!=identify)
	 {
		 nodeIdentify_=identify;
	 }
}

int		UIDragNode::getDragNodeIdentify()
{
	 return nodeIdentify_;
}

void    UIDragNode::setDragNodeIsDisable(bool isDisable)
{
	if(isDisable_!=isDisable)
	{
		isDisable_=isDisable;
		if(isDisable_)
		{
			isDragEnable_=!isDisable_;
			//todo Modify DragSpriteto  Disable
		}
	}
}

bool    UIDragNode::getIsTouchEnable()
{
	return isTouchEnable_;
}
void    UIDragNode::setTouchEnable(bool touchEnable)
{
	if(isTouchEnable_!=touchEnable)
	{
		isTouchEnable_=touchEnable;
		if(!isTouchEnable_)
		{ 
			setDragNodeIsDisable(!isTouchEnable_);
		}
	}
}

bool	UIDragNode::getDragNodeIsDisable()
{
	 return isDisable_;
}
float   UIDragNode::getDragDelayTime()
{
	return dragDelayTime_;
}
void    UIDragNode::setDragDelayTime(float drayDelayTime)
{
	if(dragDelayTime_!=drayDelayTime)
	{
		dragDelayTime_=drayDelayTime;
	}
}

void    UIDragNode::setDragNodeType(int nodeType)
{
    if(dragNodeType_!=nodeType)
	{
         dragNodeType_=nodeType;
	}
}

int     UIDragNode::getDragNodeType()
{
	  return dragNodeType_;
}


void    UIDragNode::setDelegateNode(DragDelegateProtocol * delegateNode)
{
	if(pDelegateNode_!=delegateNode)
	{
		pDelegateNode_=delegateNode;
	}
}

void UIDragNode::mandatoryMoveToInitPosition()
{
	this->getParent()->reorderChild(this,NORAMLZORDER);
	this->stopAllActions();
	this->setPosition(getDragNodeInitPosition());
}


bool  UIDragNode::checkIsCoverWithRect(float targetleft,float targetright,float targettop,float targetbottom,float offWidth)
{ 
	float dragNodeLeft=this->getPositionX()-this->getAnchorPoint().x*this->getContentSize().width;
	float dragNodeRight=this->getPositionX()+this->getAnchorPoint().x*this->getContentSize().width;
	float dragNodeTop=this->getPositionY()+this->getAnchorPoint().y*this->getContentSize().height;
	float dragNodeBottom=this->getPositionY()-this->getAnchorPoint().y*this->getContentSize().height;
 
	if(((0<=dragNodeLeft-targetleft&&dragNodeLeft-targetleft<=offWidth)||(0<=targetright-dragNodeRight&&targetright-dragNodeRight<=offWidth))&&
		((0<=dragNodeBottom-targetbottom&&dragNodeBottom-targetbottom<=offWidth)||(0<=targettop-dragNodeTop&&targettop-dragNodeTop<=offWidth)))
	{
	    return true;
	}
	return false;
}




///*
// 结点底纹变灰色   
//*/
void	UIDragNode::disableDragSprite()
{ 
	cocos2d::CCPoint oldAnchorPos=this->getAnchorPoint();
	this->setAnchorPoint(ccp(0,0));
	CCRenderTexture * outTexture=CCRenderTexture::create((int)this->getContentSize().width,(int)this->getContentSize().height);
	outTexture->begin();
	this->visit();
	outTexture->end();
	this->setAnchorPoint(oldAnchorPos);
	
	CCImage * finalImage=outTexture->newCCImage();
	unsigned char * pData=finalImage->getData();
	int index=0;

	for(int i=0;i<finalImage->getHeight();i++)
	{
		for(int j=0;j<finalImage->getWidth();j++)
		{
			int iBPos=index;
			unsigned int iR=pData[index];
			index++;
			unsigned int iG=pData[index];
			index++;
			unsigned int iB=pData[index];
			index++;

			index++;
			unsigned int iGray=(unsigned int)(0.3*iR+0.4*iG+0.2*iB);
			pData[iBPos]=pData[iBPos+1]=pData[iBPos+2]=(unsigned char) iGray;	 
		}
	}

	CCTexture2D * pTextrue2d=new CCTexture2D;
	pTextrue2d->initWithImage(finalImage);
	this->initWithTexture(pTextrue2d);
	delete finalImage;
	pTextrue2d->release();
}
