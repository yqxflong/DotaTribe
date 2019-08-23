/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  ÍÏ×§´¥ÃþËã·¨
//date:   2013/11/20
/////////////////////////////////////////////////  
#include "../include/SingleTouchProtocol.h"

using namespace cocos2d;
 
SingleTouchProtocol::SingleTouchProtocol(void)
{ 
	m_nSingleTouchUniqueID=0;
	m_fLeft=0.0f;
	m_fRight=0.0f;
	m_fTop=0.0f;
	m_fBottom=0.0f;
	m_fExpendTouchWidth=16.0f;
	m_fExpendTouchHeight=15.0f;

}
 
SingleTouchProtocol::~SingleTouchProtocol()
{

}

int SingleTouchProtocol::getSingleTouchUniqueID()
{
  return m_nSingleTouchUniqueID;
}

void  SingleTouchProtocol::setSingleTouchUniqueID(int singleID)
{
	  m_nSingleTouchUniqueID=singleID;
}  

bool   SingleTouchProtocol::checkRowRank(float touchYPos)
{  
	if((m_fBottom-m_fExpendTouchHeight)<=touchYPos&&touchYPos<=(m_fTop+m_fExpendTouchHeight))
	{
		return true;
	}
	return false;
}

bool   SingleTouchProtocol::checkColumnRank(float touchXPos)
{
	if((m_fLeft-m_fExpendTouchWidth)<=touchXPos&&touchXPos<=(m_fRight+m_fExpendTouchWidth))
	{
		return true;
	}
	return false;
}

bool SingleTouchProtocol::checkIsContainTouch(cocos2d::CCPoint &touchPos)
{ 
	if(checkRowRank(touchPos.y)&&checkColumnRank(touchPos.x))
	{
		return true;
	}
	return false;
} 

void   SingleTouchProtocol::setExpendTouchSize(float touchExpendWidth,float touchExpendHeight/* =0.0f */)
{
	m_fExpendTouchWidth=touchExpendWidth;
	if(touchExpendHeight==0.0f)
	m_fExpendTouchHeight=touchExpendWidth;
	else
    m_fExpendTouchHeight=touchExpendHeight;

}
cocos2d::CCSize  SingleTouchProtocol::getExpendTouchSize()
{
	return  CCSizeMake(m_fExpendTouchWidth,m_fExpendTouchHeight);
}
