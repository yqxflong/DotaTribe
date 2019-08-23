////////////////////////////////////////////////////////////////
//Name:	 CCDragNodeLayer
//Auchor: 	xiaobo.wu
//Func:	 拖拽控制层
//Maintainer: 	xiaobo.wu
//date:   2013/11/20
////////////////////////////////////////////////////////////////
#include "../include/CCDragNodeLayer.h"
#include "../include/SingleTouchProtocol.h"
 

#define  TOUCH_TO_GL_POINT       cocos2d::CCDirector::sharedDirector()->convertToGL( pTouch->getLocationInView())
#define  MOVINGZORDER			 10								//移动中的ZOrder
#define  NORMALZOEDER			 6								//正常状态下的ZOrder

CCDragNodeLayer::CCDragNodeLayer()
{
	m_bDragEnable=true;
	m_nTouchPriority=-181;
	m_nCurActiveSignID=0;
	m_vTouchsArray.clear();
	m_nRankCount=0;
	m_nColumnCount=0;
	m_pCurActiveSingle=NULL;
	m_fDelayDragTime=0.04f;

	m_fTargetAreaHeight=0.0f;
	m_pDragDelegate=NULL;

	m_vTargetTouchsArray.clear();
	m_vOtherAttachArray.clear();
	m_vOtherTargetAttachArray.clear();

}

CCDragNodeLayer::~CCDragNodeLayer()
{ 
	this->removeAllChildrenWithCleanup(true);
	m_vTouchsArray.clear();
	m_vTargetTouchsArray.clear();
} 

 CCDragNodeLayer * CCDragNodeLayer::createDragNodeLayer(CCDragLayerProtocol * pDrageDelegte/* =NULL */)
 {
	 CCDragNodeLayer * pDragNodeLayer=new CCDragNodeLayer();
	 if(pDragNodeLayer&&pDragNodeLayer->initDragNodeLayer(pDrageDelegte))
	 {    
		 pDragNodeLayer->autorelease();
		 return pDragNodeLayer;
	 }
	 CC_SAFE_DELETE(pDragNodeLayer);
	 return  NULL;
 }

 void  CCDragNodeLayer::onEnter()
 {
	 CCLayer::onEnter();
	 if(m_bDragEnable)
	 { 
		 //注册非吞噬的触摸
		 cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_nTouchPriority,false);
	 }
 }

 void  CCDragNodeLayer::setDragLayerTouchEnable(bool touchEnable)
 { 
	 if(touchEnable)
	 {
		 if(m_bDragEnable!=touchEnable)
		 {
			 //启动触摸
			 m_bDragEnable=touchEnable;
			 cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_nTouchPriority,false);
		 }
	 }
	 else
	 {
		 if(m_bDragEnable!=touchEnable)
		 {
			 m_bDragEnable=touchEnable;
			 //关闭触摸
			 cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
		 }
	 } 
 }
  

 /*
 触摸事件分发器
 */
 void  CCDragNodeLayer::dispatchTouchEvent(cocos2d::CCPoint & touchPosition)
 {    
	 if(m_pCurActiveSingle&&m_pDragDelegate)
	 { 
		if(m_pCurActiveSingle->checkIsContainTouch(touchPosition))
		{  
			m_pDragDelegate->delegateDragEndEventHandler(CCDragLayerProtocol::_CLICK_DRAG_END_TYPE_,m_pCurActiveSingle,touchPosition);
		}
		else
		{
			m_pDragDelegate->delegateDragEndEventHandler(CCDragLayerProtocol::_OTHER_DRAG_END_TYPE_,m_pCurActiveSingle,touchPosition);
		} 
	 } 
 }
  
 bool CCDragNodeLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
 { 
	  if(touchSignCheck(pTouch))
	  return true;
	  else
	  return false;
 }

 void CCDragNodeLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
 {  
	 if(m_pCurActiveSingle&&m_pCurActiveSingle->getDragEnable())
	 { 
		 cocos2d::CCPoint movePosition=TOUCH_TO_GL_POINT;
		 m_pCurActiveSingle->getParent()->reorderChild(m_pCurActiveSingle,MOVINGZORDER);
		 ////延时拖拽效果	 
		 m_pCurActiveSingle->runAction(cocos2d::CCSequence::createWithTwoActions(cocos2d::CCDelayTime::create(m_fDelayDragTime),cocos2d::CCPlace::create(movePosition))); 
	 }
 }

 void CCDragNodeLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
 {
	 if(m_pCurActiveSingle)
	 {
		 cocos2d::CCPoint endTouch=TOUCH_TO_GL_POINT;
		 dispatchTouchEvent(endTouch);
		 m_pCurActiveSingle->getParent()->reorderChild(m_pCurActiveSingle,NORMALZOEDER);
		 m_pCurActiveSingle->forceToInitPosition();
		// m_pCurActiveSingle=NULL;
	 }
	  
 }

 void CCDragNodeLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
 { 
	 if(m_pCurActiveSingle!=NULL)
	 { 
		 m_pCurActiveSingle->getParent()->reorderChild(m_pCurActiveSingle,NORMALZOEDER);
		 m_pCurActiveSingle->forceToInitPosition();
		 m_pCurActiveSingle=NULL;
	 }
 } 
  

 void  CCDragNodeLayer::setDragLayerTouchPriority(int touchPriority)
 { 
	 m_nTouchPriority=touchPriority; 
 }
  
 bool  CCDragNodeLayer::getDragLayerTouchEnabel()
 {
	 return m_bDragEnable;
 }
  
 void  CCDragNodeLayer::onExit()
 { 
	 if(m_bDragEnable)
	 {
		 cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	 }
	 CCLayer::onExit();
 }

bool CCDragNodeLayer::initDragNodeLayer(CCDragLayerProtocol * pDrageDelegte)
{ 
	if(CCLayer::init())
	{
		m_pDragDelegate=pDrageDelegte;
		return true;
	}
	return false;
}
  
void    CCDragNodeLayer::addSignSpriteVector(std::vector<CCSignSprite * >  signSpriteVec,int zOrder)
{
	m_nColumnCount=signSpriteVec.size();
	m_nRankCount++;
	for(size_t columnIndex=0;columnIndex<m_nColumnCount;columnIndex++)
	{ 
		this->addChild(signSpriteVec.at(columnIndex),zOrder);
	}
	m_vTouchsArray.push_back(signSpriteVec);
}

void    CCDragNodeLayer::clearAllSignTouchArray()
{
	m_nRankCount=0;
	m_nColumnCount=0;
	m_vTouchsArray.clear();
}

bool    CCDragNodeLayer::touchSignCheck(cocos2d::CCTouch *pTouch)
{    
	cocos2d::CCPoint touchPosition=TOUCH_TO_GL_POINT;
	
	if(touchPosition.y>=m_fTargetAreaHeight)
	{
		for(size_t rankIndex=0;rankIndex<m_nRankCount;rankIndex++)
		{ 
			if(m_vTouchsArray.at(rankIndex).at(0)->checkRowRank(touchPosition.y))
			{   
				for(size_t columnIndex=0;columnIndex<m_nColumnCount;columnIndex++)
				{ 
					if(m_vTouchsArray.at(rankIndex).at(columnIndex)->checkColumnRank(touchPosition.x))
					{
						m_pCurActiveSingle=m_vTouchsArray.at(rankIndex).at(columnIndex);
						m_nCurActiveSignID=m_pCurActiveSingle->getSingleTouchUniqueID();
						return true;
					}
				} 
				break;
			}
		}   
	}
	else
	{
		//检测Target区域
		std::list<CCSignSprite *>::iterator sign_iter=m_vTargetTouchsArray.begin();
		while(sign_iter!=m_vTargetTouchsArray.end())
		{    
			if((*sign_iter)->checkIsContainTouch(touchPosition))
			{
				m_pCurActiveSingle=*sign_iter;
				m_nCurActiveSignID=m_pCurActiveSingle->getSingleTouchUniqueID();
				return true;
			}
			++sign_iter;
		}
	}
   
	return false;
}


void  CCDragNodeLayer::setDefaultTargetSegmentHeight(float targetSegmentHeigh)
{
	m_fTargetAreaHeight=targetSegmentHeigh;
}


void    CCDragNodeLayer::addTargetSignSprite(CCSignSprite * pSignSprite,int zOrder)
{
	if(pSignSprite)
	{
		this->addChild(pSignSprite,zOrder);
		m_vTargetTouchsArray.push_back(pSignSprite);
	}
}
void    CCDragNodeLayer::removeTargetSignSpriteWithID(int signSpriteUniqueID)
{
	std::list<CCSignSprite *>::iterator sign_iter=m_vTargetTouchsArray.begin();
	while(sign_iter!=m_vTargetTouchsArray.end())
	{  
		if((*sign_iter)->getSingleTouchUniqueID()==signSpriteUniqueID)
		{  
			(*sign_iter)->removeFromParentAndCleanup(true);
			m_vTargetTouchsArray.erase(sign_iter);
			return ;
		}
		++sign_iter;
	}
}


void  CCDragNodeLayer::setDragEventDelegate(CCDragLayerProtocol * pDrageDelegte)
{
	m_pDragDelegate=pDrageDelegte;
}

void  CCDragNodeLayer::addOtherAttachSprite(cocos2d::CCSprite * pAttachSprite,int zOrder)
{
	if(pAttachSprite)
	{
		this->addChild(pAttachSprite,zOrder);
		m_vOtherAttachArray.push_back(pAttachSprite);
	}
}

void  CCDragNodeLayer::addTargetAttachSprite(cocos2d::CCSprite * pTargetAttachSprite,int zOrder)
{
	if(pTargetAttachSprite)
	{
		this->addChild(pTargetAttachSprite,zOrder);
		m_vOtherTargetAttachArray.push_back(pTargetAttachSprite);
	} 
}

void  CCDragNodeLayer::removeAllOtherAttachSprite()
{  
	size_t attachCount=m_vOtherAttachArray.size();
	for(size_t attachIndex=0;attachIndex<attachCount;attachIndex++)
	{
		m_vOtherAttachArray.at(attachIndex)->removeFromParentAndCleanup(true);
	}
	m_vOtherAttachArray.clear();
	 
}

void  CCDragNodeLayer::removeAllTargetAttachSprite()
{
	size_t attachCount=m_vOtherTargetAttachArray.size();
	for(size_t attachIndex=0;attachIndex<attachCount;attachIndex++)
	{
		m_vOtherTargetAttachArray.at(attachIndex)->removeFromParentAndCleanup(true);
	}
	m_vOtherTargetAttachArray.clear();
}



void    CCDragNodeLayer::removeAllTargetSignSprites()
{
	std::list<CCSignSprite *>::iterator sign_iter=m_vTargetTouchsArray.begin();
	while(sign_iter!=m_vTargetTouchsArray.end())
	{   
		(*sign_iter)->removeFromParentAndCleanup(true);
		++sign_iter;
	}
	m_vTargetTouchsArray.clear();
}


void   CCDragNodeLayer::removeAllData()
{
	//to do
	m_pCurActiveSingle=NULL;
	m_nRankCount=0;
	m_nColumnCount=0;
	this->removeAllChildrenWithCleanup(true);
	m_vTouchsArray.clear();
	m_vTargetTouchsArray.clear();
	m_vOtherTargetAttachArray.clear();
	m_vOtherAttachArray.clear();

}


