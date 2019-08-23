//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//  Type: The Star Level 
//  modify: xiaobo.wu
//  The Anchor Point is (0,0), can not be changed

#ifndef  _DOTATRIBE_CCardsStarProgress_H_
#define  _DOTATRIBE_CCardsStarProgress_H_

#include <cocos2d.h>
#include <vector>

typedef struct starnode_tag
{
	bool m_bIsAdvance;
	cocos2d::CCSprite * m_pStarSprite;
public:
	starnode_tag()
	{
		m_bIsAdvance=false;
		m_pStarSprite=NULL;
	}
	starnode_tag(bool isAdvance,cocos2d::CCSprite * pStarSprite)
	{
		m_bIsAdvance=isAdvance;
		m_pStarSprite=pStarSprite;
	}
}StarNode,*PStarNode;

 
class CCardsStarProgress:public cocos2d::CCNode{
private:
	int m_nMaxCount;
	int m_nCurCount;
	int m_advanceCount;
	std::vector<starnode_tag>			m_starArray;
	std::string m_strFileNoraml;		//the file name of star
	std::string m_strFileAdvance;			
	float m_fSpace;
private:
	void _updateStars();		
	void _hideAllStars();
public:
	CCardsStarProgress(){
		m_nMaxCount=0;
		m_nCurCount=0;
		m_advanceCount=0;
		m_fSpace=0.0f;
		m_strFileNoraml="";
		m_strFileAdvance=""; 
	};
	virtual ~CCardsStarProgress(){
	   this->removeAllChildrenWithCleanup(true);
	   m_starArray.clear();
	};
	/*
		can not change max count after create
	*/
	static CCardsStarProgress* create(std::string  normalName,std::string advanceName,int maxcount,float space);
	bool init(std::string normalName,std::string advanceName,int maxcount,float space);
	/*
		can change current count after create
	*/
	void SetCurcount(int curcount,int advanceCount=0);

 
	 
};
#endif