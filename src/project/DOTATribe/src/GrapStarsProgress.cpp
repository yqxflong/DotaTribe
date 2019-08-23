#include "../include/GrapStarsProgress.h"
 
//to do 
const std::string  normal_star_bg = "resource/image/newpublic/cards_star_b.png";			//Õý³£ÐÇÐÇ
const std::string  grap_star_bg ="resource/image/newpublic/cards_star_hui.png";			//ÖÃ»ÒÐÇÐÇ
 

GrapStarsProgress::GrapStarsProgress()
{ 
	m_starsVector.clear();
	m_nMaxStarsCount = 0;
	m_nActiveStarsCount = 0;
	m_fSpace = 0;
} 
GrapStarsProgress::~GrapStarsProgress()
{  
	m_starsVector.clear();
	this->removeAllChildrenWithCleanup(true);
}

GrapStarsProgress  *  GrapStarsProgress::createGrapStarsProgress(int maxStarsCount,int activeCount,float fSpace)
{  
	 GrapStarsProgress * pGrapStarsProgress = new GrapStarsProgress();
	 if(pGrapStarsProgress&&pGrapStarsProgress->initGrapStarsProgress(maxStarsCount,activeCount,fSpace))
	 {
		 pGrapStarsProgress->autorelease();
		 return pGrapStarsProgress;
	 }
	 CC_SAFE_DELETE(pGrapStarsProgress);
	 return NULL;
}
 
bool  GrapStarsProgress::initGrapStarsProgress(int maxStarsCount,int activeCount,float fSpace)
{
	if(cocos2d::CCNode::init())
	{  
		m_nMaxStarsCount = maxStarsCount;
		m_nActiveStarsCount = activeCount;
		m_fSpace = fSpace;
		updateTexture();
		return true;
	}
	return false;
}
 

void  GrapStarsProgress::updateTexture()
{
	 size_t  exsitStarSize = m_starsVector.size();
	 if(exsitStarSize < m_nMaxStarsCount)
	 {
		 //À©Õ¹
		 int expandSize=m_nMaxStarsCount-(int)exsitStarSize;
		 cocos2d::CCSprite * pStarSprite=NULL;
		 if(m_starsVector.empty())
		 {
			 float offSet=0.0f;
			 for(int index=0;index<expandSize;index++)
			 { 
				 pStarSprite = cocos2d::CCSprite::create();
				 pStarSprite->setProperty("File",normal_star_bg.c_str());
				 pStarSprite->setAnchorPoint(cocos2d::CCPointZero);
				 pStarSprite->setPosition(ccp(offSet,0));
				 offSet = offSet+pStarSprite->getContentSize().width+m_fSpace;
				 this->addChild(pStarSprite);
				 GrapStarNode  starnode(false,pStarSprite);
				 m_starsVector.push_back(starnode);
			 }
		 }
		 else
		 {    
			 pStarSprite = m_starsVector.at(exsitStarSize-1).pStarSprite;
			 float offSet=pStarSprite->getPositionX()+pStarSprite->getContentSize().width+m_fSpace;
			 for(int index=0;index<expandSize;index++)
			 {
				 pStarSprite=cocos2d::CCSprite::create();
				 pStarSprite->setProperty("File",normal_star_bg.c_str());
				 pStarSprite->setAnchorPoint(cocos2d::CCPointZero);
				 pStarSprite->setPosition(ccp(offSet,0));
				 offSet=offSet+pStarSprite->getContentSize().width+m_fSpace;
				 this->addChild(pStarSprite);
				 GrapStarNode  starnode(false,pStarSprite);
				 m_starsVector.push_back(starnode);
			 }
		 }
		updateInterStar();
	 }  
	 else
	 { 
		updateInterStar();
	 }  
}


void  GrapStarsProgress::updateInterStar()
{ 
	size_t starSize = m_starsVector.size();
	int  activedIndex = 0;
	int  countIndex = 0;
	for(int index = 0;index<(int)starSize;index++)
	{  
		if(countIndex<m_nMaxStarsCount)
		{
			if(activedIndex<m_nActiveStarsCount)
			{
				if(m_starsVector.at(index).bIsGrapNode)
				{
					m_starsVector.at(index).bIsGrapNode = false;
					m_starsVector.at(index).pStarSprite->setProperty("File",normal_star_bg.c_str());
					m_starsVector.at(index).pStarSprite->setVisible(true);
				}
				else
				m_starsVector.at(index).pStarSprite->setVisible(true);
			}
			else if(!m_starsVector.at(index).bIsGrapNode)
			{
				m_starsVector.at(index).bIsGrapNode = true;
				m_starsVector.at(index).pStarSprite->setProperty("File",grap_star_bg.c_str());
				m_starsVector.at(index).pStarSprite->setVisible(true);
			}
			else
			m_starsVector.at(index).pStarSprite->setVisible(true);
		}
		else
		{
			m_starsVector.at(index).pStarSprite->setVisible(false);
		}
		activedIndex++;
		countIndex++; 
	} 
}


void  GrapStarsProgress::setStars(int maxStarsCount,int activeCount)
{  
	m_nMaxStarsCount = maxStarsCount;
	m_nActiveStarsCount = activeCount;
	updateTexture();
}
void  GrapStarsProgress::setStars(int activeCount)
{ 
	m_nActiveStarsCount = activeCount;
	updateTexture();
}