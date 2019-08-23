//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//  Type: The Star Level 
//
#include "../include/CCardsStarProgress.h"
USING_NS_CC;

CCardsStarProgress* CCardsStarProgress::create(std::string normalName,std::string advanceName,int maxcount,float space)
{
	CCardsStarProgress* cc=new CCardsStarProgress();
	if (cc->init(normalName,advanceName,maxcount,space))
	{
		cc->autorelease();
		return cc;
	}
	CC_SAFE_DELETE(cc);
	return NULL;
}

bool CCardsStarProgress::init(std::string normalName,std::string advanceName,int maxcount,float space)
{
	if (CCNode::init())
	{
		m_strFileNoraml=normalName;
		m_strFileAdvance=advanceName;
		m_nMaxCount=maxcount;
		m_fSpace=space;
		return true;
	}
	return false;
}

void CCardsStarProgress::SetCurcount(int curcount,int advanceCount/* =0 */)
{  
	m_nCurCount=curcount;
	m_advanceCount=advanceCount;
	  
	if(m_nCurCount>m_nMaxCount)
	{
		m_advanceCount=m_nCurCount-m_nMaxCount;
		m_nCurCount=m_nMaxCount;
	}
	if(m_advanceCount>m_nMaxCount)
	m_advanceCount=m_nMaxCount;
	 
	size_t arraySize=m_starArray.size();
	if(curcount<=(int)arraySize)
	{
		//to do
		_updateStars();
	}
	else
	{
		int expandSize=curcount-(int)arraySize;
		cocos2d::CCSprite * pStarSprite=NULL;
		if(m_starArray.empty())
		{
			 float offSet=0.0f;
			 for(int index=0;index<expandSize;index++)
			 { 
				 pStarSprite=cocos2d::CCSprite::create();
				 pStarSprite->setProperty("File",m_strFileNoraml.c_str());
				 pStarSprite->setAnchorPoint(CCPointZero);
				 pStarSprite->setPosition(ccp(offSet,0));
				 offSet=offSet+pStarSprite->getContentSize().width+m_fSpace;
				 this->addChild(pStarSprite);
				 starnode_tag  starnode(false,pStarSprite);
				 m_starArray.push_back(starnode);
			 }
		}
		else
		{    
			pStarSprite=m_starArray.at(arraySize-1).m_pStarSprite;
			float offSet=pStarSprite->getPositionX()+pStarSprite->getContentSize().width+m_fSpace;
			for(int index=0;index<expandSize;index++)
			{
				pStarSprite=cocos2d::CCSprite::create();
				pStarSprite->setProperty("File",m_strFileNoraml.c_str());
				pStarSprite->setAnchorPoint(CCPointZero);
				pStarSprite->setPosition(ccp(offSet,0));
				offSet=offSet+pStarSprite->getContentSize().width+m_fSpace;
				this->addChild(pStarSprite);
				starnode_tag  starnode(false,pStarSprite);
				m_starArray.push_back(starnode); 
			}
		}
		_updateStars();
	} 
}


void CCardsStarProgress::_updateStars()
{
	 size_t starSize=m_starArray.size();
	 int  advanceIndex=0;
	 int  countIndex=0;
	 for(int index=0;index<(int)starSize;index++)
	 {  
		 if(countIndex<m_nCurCount)
		 {
			 if(advanceIndex<m_advanceCount)
			 {
				 if(!m_starArray.at(index).m_bIsAdvance&&!m_strFileAdvance.empty())
				 {
					 m_starArray.at(index).m_bIsAdvance=true;
					 m_starArray.at(index).m_pStarSprite->setProperty("File",m_strFileAdvance.c_str());
					 m_starArray.at(index).m_pStarSprite->setVisible(true);
				 }
				 else
				 m_starArray.at(index).m_pStarSprite->setVisible(true);
			 }
			 else if(m_starArray.at(index).m_bIsAdvance)
			 {
				  m_starArray.at(index).m_bIsAdvance=false;
				  m_starArray.at(index).m_pStarSprite->setProperty("File",m_strFileNoraml.c_str());
				  m_starArray.at(index).m_pStarSprite->setVisible(true);
			 }
			 else
			 m_starArray.at(index).m_pStarSprite->setVisible(true);
		 }
		 else
		 {
			 m_starArray.at(index).m_pStarSprite->setVisible(false);
		 }
		 advanceIndex++;
		 countIndex++; 
	 }
}

 

void CCardsStarProgress::_hideAllStars()
{
	size_t starSize=m_starArray.size();
	for (int i=0;i<(int)starSize;i++)
	{
		m_starArray.at(i).m_pStarSprite->setVisible(false);
	} 
}