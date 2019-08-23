////////////////////////////////////////////////////////////////
//Name:	 CCSignSprite
//Auchor: 	xiaobo.wu
//Func:	 标记精灵
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////
#include "../include/CCSignSprite.h"

#define   _DEFAULT_ANCHOR_    ccp(0.5f,0.5f)
#define  MOVINGZORDER			 10								//移动中的ZOrder
#define  NORMALZOEDER			 6								//正常状态下的ZOrder

using namespace cocos2d;

CCSignSprite::CCSignSprite()
{
	m_fInitPosition=CCPointZero;
	m_nIsMoveEnable=false;
	m_eDragNodeType=_SIGNSPRITE_UNKONW_TYPE_;
}

CCSignSprite::~CCSignSprite()
{

}
 
CCSignSprite *  CCSignSprite::createCCSignSpriteWithFile(int signUniqueID,const char * fileName,SignSpriteType nodeType/* =SignSpriteType::_SIGNSPRITE_COMMON_TYPE_ */,bool isMoveEnable/* =true */)
{
	CCSignSprite * pSignSprite=new CCSignSprite();
	if(pSignSprite->initCCSignSpriteWithFile(signUniqueID,fileName,nodeType,isMoveEnable))
	{
		pSignSprite->autorelease();
		return pSignSprite;
	}
	CC_SAFE_DELETE(pSignSprite);
	return NULL;
}

CCSignSprite *  CCSignSprite::createCCSignSpriteWithFrameName(int signUniqueID,const char * frameName,SignSpriteType nodeType/* =SignSpriteType::_SIGNSPRITE_COMMON_TYPE_ */,bool isMoveEnable/* =true */)
{
	CCSignSprite * pSignSprite=new CCSignSprite();
	if(pSignSprite->initCCSignSpriteWithFrameName(signUniqueID,frameName,nodeType,isMoveEnable))
	{
		pSignSprite->autorelease();
		return pSignSprite;
	}
	CC_SAFE_DELETE(pSignSprite);
	return NULL;
}

bool  CCSignSprite::initCCSignSpriteWithFile(int signUniqueID,const char * fileName,SignSpriteType nodeType/* =SignSpriteType::_SIGNSPRITE_COMMON_TYPE_ */,bool isMoveEnable/* =true */)
{
	 if(CCSprite::init())
	 { 
		setProperty("File",fileName);
	    init(signUniqueID,nodeType,isMoveEnable);
		return true;
	 }
	 return false;
}

bool  CCSignSprite::initCCSignSpriteWithFrameName(int signUniqueID,const char * frameName,SignSpriteType nodeType/* =SignSpriteType::_SIGNSPRITE_COMMON_TYPE_ */,bool isMoveEnable/* =true */)
{
	if(initWithSpriteFrameName(frameName))
	{
	    init(signUniqueID,nodeType,isMoveEnable);
		return true;
	}
	return false;
}

bool  CCSignSprite::init(int signUniqueID,SignSpriteType nodeType,bool isMoveEnable)
{
	m_nSingleTouchUniqueID=signUniqueID;
	m_eDragNodeType=nodeType;
	m_nIsMoveEnable=isMoveEnable;
	return true;
}

void   CCSignSprite::setInitPosition(cocos2d::CCPoint initPosition)  
{
	m_fInitPosition=initPosition;
	setAnchorPoint(_DEFAULT_ANCHOR_);
	setPosition(initPosition);
	initCalTouchRectAlgorithm();
}
cocos2d::CCPoint CCSignSprite::getInitPosition()
{ 
	return m_fInitPosition;
}
 
void	CCSignSprite::forceToInitPosition()
{
	//to do 
	this->getParent()->reorderChild(this,NORMALZOEDER);
	this->stopAllActions();
	this->setPosition(getInitPosition());
}

void  CCSignSprite::initCalTouchRectAlgorithm()
{ 
	cocos2d::CCSize contentSize= this->getContentSize(); 
    m_fLeft=m_fInitPosition.x-contentSize.width*0.5f;
	m_fRight=m_fInitPosition.x+contentSize.width*0.5f;
	m_fTop=m_fInitPosition.y+contentSize.height*0.5f;
	m_fBottom=m_fInitPosition.y-contentSize.height*0.5f;

}
 
SignSpriteType  CCSignSprite::getDragNodeType()
{
    return m_eDragNodeType;
}

bool	CCSignSprite::getDragEnable()
{
	return m_nIsMoveEnable;
}


void    CCSignSprite::setDragEnable(bool bDrageEnable)
{ 
	m_nIsMoveEnable=bDrageEnable;
}

bool  CCSignSprite::checkIsCoverWithRect(float targetleft,float targetright,float targettop,float targetbottom,float offWidth)
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