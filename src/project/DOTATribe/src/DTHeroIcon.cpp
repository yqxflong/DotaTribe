#include "../include/DTHeroIcon.h" 
#include "../include/ResourceIDDataManager.h"
 

#define  _DEFAULT_ANCHOR_  ccp(0.5f,0.5f)


DTHeroIcon::DTHeroIcon()
{
	m_nTouchPrioty = -5;
	m_nIconID = 0;
	m_nQualiy = 0;
	m_pMenuItemSprite = NULL;
	m_pHeroIcon = NULL;
	m_pBgkHero = NULL;
	m_pMarkMenu = NULL;
	m_fScale = 1.0f;
	m_bLargeIcon = false;
	m_pHeroQualityMask = NULL;
}

DTHeroIcon::~DTHeroIcon()
{
	this->removeAllChildrenWithCleanup(true);
}


DTHeroIcon *  DTHeroIcon::createHeroIcon(int iconID,int qualiy,bool isLargeIcon,int touchPrioty/* =-5 */)
{
	DTHeroIcon * pDTHeroIcon = new DTHeroIcon();
	if(pDTHeroIcon&&pDTHeroIcon->initHeroIcon(iconID,qualiy,isLargeIcon,touchPrioty))
	{
		pDTHeroIcon->autorelease();
		return pDTHeroIcon;
	}
	CC_SAFE_DELETE(pDTHeroIcon);
	return NULL;
}

bool   DTHeroIcon::initHeroIcon(int iconID,int qualiy,bool isLargeIcon,int touchPrioty)
{
	if(cocos2d::CCNode::init())
	{
		m_nIconID = iconID;
		m_nQualiy = qualiy;
		m_bLargeIcon = isLargeIcon;
		if(touchPrioty==0)
		touchPrioty = -5;
		m_nTouchPrioty = touchPrioty;
		m_pMarkMenu = CImmovableMenu::create(m_nTouchPrioty);
		m_pMarkMenu->setAnchorPoint(cocos2d::CCPointZero);
		m_pMarkMenu->setPosition(cocos2d::CCPointZero);
		m_pMarkMenu->setZOrder(2);
		this->addChild(m_pMarkMenu,2); 
		if(qualiy<=0)
		qualiy =1; 

		if(m_bLargeIcon)
		m_pMenuItemSprite = CMenuItemSprite::create(varConfig::getLargeHeroMaskFilePath().c_str(),NULL,NULL);
		else
		m_pMenuItemSprite = CMenuItemSprite::create(varConfig::getCardMaskFilePath(m_nQualiy).c_str(),NULL,NULL);
		m_pMenuItemSprite->setAnchorPoint(_DEFAULT_ANCHOR_);
		m_pMenuItemSprite->setEnabled(false);  
		m_pMarkMenu->addChild(m_pMenuItemSprite,0); 
		if(m_bLargeIcon)
		m_pBgkHero = cocos2d::CCSprite::create(varConfig::getLargeHeroBGFilePath().c_str()); 
		else		
		m_pBgkHero = cocos2d::CCSprite::create(varConfig::getCardBGFilePath(m_nQualiy).c_str()); 
		m_pBgkHero->setAnchorPoint(_DEFAULT_ANCHOR_);
		this->addChild(m_pBgkHero,1);	 
		if(m_nIconID!=0)
		{
		   m_pHeroIcon = ResourceIDDataManager::get_instance2()->GetSpriteFromID(m_nIconID);  
		}
		else
		{
			m_pHeroIcon = cocos2d::CCSprite::create(); 
		}
	    m_pHeroIcon->setAnchorPoint(_DEFAULT_ANCHOR_);

		std::string heroQualityMask = varConfig::getHeroQualityMaskFilePath(m_nQualiy);
		if(!heroQualityMask.empty())
		{ 
			m_pHeroQualityMask->setAnchorPoint(_DEFAULT_ANCHOR_);
			m_pHeroQualityMask = cocos2d::CCSprite::create(heroQualityMask.c_str()); 
			this->addChild(m_pHeroQualityMask,3);
		}  
		this->addChild(m_pHeroIcon,1);
		return true;
	}
	return false;
}


 void  DTHeroIcon::setIconScale(float scale)
 {
	 m_fScale = scale;
	 m_pHeroIcon->setScale(m_fScale);
 }


 void  DTHeroIcon::setIconColor(const cocos2d::ccColor3B& color3)
 {
	 m_pHeroIcon->setColor(color3);
 }

 void  DTHeroIcon::setHeroAttachParam(int attachParam1,int attachParam2)
 {
	 if(m_pMenuItemSprite)	
	 {
		 m_pMenuItemSprite->setAttachData1(attachParam1);
		 m_pMenuItemSprite->setAttachData2(attachParam2);
	 }
 }

void  DTHeroIcon::setHeroIconID(int heroIconID)
{  
		m_nIconID = heroIconID;
		m_pHeroIcon->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(m_nIconID));
		m_pHeroIcon->setScale(m_fScale);
		m_pHeroIcon->setVisible(true); 
}

void  DTHeroIcon::setHeroIconVisable(bool isVisiable)
{
	if(m_pHeroIcon)
	{
		m_pHeroIcon->setVisible(isVisiable);
		if(!isVisiable)
		{ 
		  m_pBgkHero->setProperty("File",varConfig::getCardBGFilePath(0)); 
		}
	}
}

void  DTHeroIcon::setHeroQualiy(int heroQualiy)
{
	if(!m_bLargeIcon)
	{
		m_nQualiy = heroQualiy; 
		cocos2d::CCSprite* nor = cocos2d::CCSprite::create();
		nor->setProperty("File",varConfig::getCardMaskFilePath(m_nQualiy));
		m_pMenuItemSprite->setNormalImageAndRelocation(nor); 
		m_pBgkHero->setProperty("File",varConfig::getCardBGFilePath(m_nQualiy)); 
		 
		std::string heroQualityMask = varConfig::getHeroQualityMaskFilePath(m_nQualiy);
		if(!heroQualityMask.empty())
		{ 
			if(m_pHeroQualityMask)
			{
				m_pHeroQualityMask->setAnchorPoint(_DEFAULT_ANCHOR_);
				m_pHeroQualityMask->setPosition(this->getPosition());
				m_pHeroQualityMask->setProperty("File",heroQualityMask.c_str());  
				m_pHeroQualityMask->setVisible(true);
			}
			else
			{ 
				m_pHeroQualityMask = cocos2d::CCSprite::create(heroQualityMask.c_str()); 
				m_pHeroQualityMask->setAnchorPoint(_DEFAULT_ANCHOR_);
				m_pHeroQualityMask->setPosition(this->getPosition());
				this->addChild(m_pHeroQualityMask,3);
				m_pHeroQualityMask->setVisible(true);
			} 
		}
		else
		{  
			if(m_pHeroQualityMask)
			m_pHeroQualityMask->setVisible(false);
		}
	}
}

void  DTHeroIcon::setMenuSelector(int uiIndex,cocos2d::CCNode * pDelegate,SEL_MenuHandler pSelector)
{  
	if(m_pMenuItemSprite)
	{
		m_pMenuItemSprite->setEnabled(true);
		m_pMenuItemSprite->setIDX(uiIndex);
		m_pMenuItemSprite->setTarget(pDelegate,pSelector);
	}
}
 

void  DTHeroIcon::setPosition(const cocos2d::CCPoint &position)
{ 
	m_pMenuItemSprite->setPosition(position);
	m_pHeroIcon->setPosition(position);
	m_pBgkHero->setPosition(position); 
}

const cocos2d::CCPoint& DTHeroIcon::getPosition()
{
	return m_pMenuItemSprite->getPosition();
}
 

void   DTHeroIcon::updateTexrure()
{

}