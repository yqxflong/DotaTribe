////////////////////////////////////////////////////////////////
//Name:	 CTeamIconProgress
//Auchor: 	xiaobo.wu
//Func:	  组队头像队列
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////
#include "../include/CTeamIconProgress.h"
#include "../include/CPublicVarReader.h"

#define  _SIMPLE_ANCHOR_ZERO_  ccp(0,0)

CTeamIconProgress::CTeamIconProgress()
{
	m_sNoramName="";
	m_sGrapName="";
	m_nDefaultCount=0;
	m_nActiveCount=0;
	m_bisFlipX=false;
	m_teamItemsVector.clear();
}

CTeamIconProgress::~CTeamIconProgress()
{ 
	this->removeAllChildrenWithCleanup(true);
	m_teamItemsVector.clear();
}

CTeamIconProgress * CTeamIconProgress::createTeamIconProgress(std::string normalFile,std::string grapFile,float finterDistance,bool isFlipX/* =false */,int defualtCount/* =3 */)
{
	CTeamIconProgress * pTeamIconProgress=new CTeamIconProgress();
	if(pTeamIconProgress&&pTeamIconProgress->initTeamIconProgress(normalFile,grapFile,finterDistance,isFlipX,defualtCount))
	{
		pTeamIconProgress->autorelease();
		return pTeamIconProgress;
	} 
	CC_SAFE_DELETE(pTeamIconProgress);
	return pTeamIconProgress;
}

void    CTeamIconProgress::resetProgress()
{ 
	 size_t  iconCount=m_teamItemsVector.size();
	 m_nActiveCount=iconCount;
	 COMMON_BEIGIN_ARRAY(size_t,iconCount)
		 if(m_teamItemsVector.at(index).isGrap)
		 {
			 m_teamItemsVector.at(index).isGrap=false;
			 m_teamItemsVector.at(index).pIconSprite->setProperty("File",m_sNoramName.c_str());
		 }
	 COMMON_END_ARRAY
}
void    CTeamIconProgress::reduceActiveCount()
{
	m_nActiveCount--;
	if(m_nActiveCount<0)
	m_nActiveCount=0;
	setActiveCount(m_nActiveCount);
}

 
void    CTeamIconProgress::setActiveCount(int activeCount)
{
	if(m_bisFlipX)
	{
		//to do
		size_t arrayCount=m_teamItemsVector.size();
		int   activeIndex=arrayCount-activeCount;
		COMMON_BEIGIN_ARRAY(size_t,arrayCount)
			if((int)index>=activeIndex)
			{
				//激活
				setSpriteEnable(m_teamItemsVector.at(index),true);
			}
			else
			{
				//暗下
				setSpriteEnable(m_teamItemsVector.at(index),false);
			}
		COMMON_END_ARRAY
	}
	else
	{
		//to do
		size_t arrayCount=m_teamItemsVector.size();
		COMMON_BEIGIN_ARRAY(size_t,arrayCount)
			if((int)index<activeCount)
			{
				//激活
				setSpriteEnable(m_teamItemsVector.at(index),true);
			}
			else
			{
				//暗下
				setSpriteEnable(m_teamItemsVector.at(index),false);
			}
		COMMON_END_ARRAY
	}
}
 


void    CTeamIconProgress::setSpriteEnable(teamiconitem & iconItem,bool isEnable)
{
	if(isEnable)
	{
		if(iconItem.isGrap)
		{
			iconItem.isGrap=false;
			iconItem.pIconSprite->setProperty("File",m_sNoramName.c_str());
		}
	}
	else
	{
		if(!iconItem.isGrap)
		{ 
			iconItem.isGrap=true;
			iconItem.pIconSprite->setProperty("File",m_sGrapName.c_str());
		}
	}
	
}

void    CTeamIconProgress::unActiveAllProgress()
{
	size_t  iconCount=m_teamItemsVector.size();
	m_nActiveCount=iconCount;
	COMMON_BEIGIN_ARRAY(size_t,iconCount)
		if(!m_teamItemsVector.at(index).isGrap)
		{
			m_teamItemsVector.at(index).isGrap=true;
			m_teamItemsVector.at(index).pIconSprite->setProperty("File",m_sGrapName.c_str());
		}
	COMMON_END_ARRAY
}


bool CTeamIconProgress::initTeamIconProgress(std::string normalFile,std::string grapFile,float finterDistance,bool isFlipX,int defualtCount)
{
	setAnchorPoint(_SIMPLE_ANCHOR_ZERO_);
	m_sNoramName=normalFile;
	m_sGrapName=grapFile;
	m_bisFlipX=isFlipX;
	m_nDefaultCount=defualtCount;
	m_nActiveCount=m_nDefaultCount;
	m_fInterDistance=finterDistance;
	COMMON_BEIGIN_ARRAY(int,m_nDefaultCount)
	 cocos2d::CCSprite * pTeamIcon=cocos2d::CCSprite::create();
	 pTeamIcon->setAnchorPoint(_SIMPLE_ANCHOR_ZERO_);
	 pTeamIcon->setProperty("File",normalFile.c_str());
	 pTeamIcon->setPosition(ccp((pTeamIcon->getContentSize().width+m_fInterDistance)*index,0));
	 this->addChild(pTeamIcon);
	 teamiconitem teamicon;
	 teamicon.pIconSprite=pTeamIcon;
	 m_teamItemsVector.push_back(teamicon);
	COMMON_END_ARRAY

	return true;
}

