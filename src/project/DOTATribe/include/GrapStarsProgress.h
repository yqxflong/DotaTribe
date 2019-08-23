#ifndef   _DOTATRIBE_GRAPSTATSPROGRESS_H_
#define   _DOTATRIBE_GRAPSTATSPROGRESS_H_

#include  <cocos2d.h>

typedef struct grapstar_tag
{
	bool				bIsGrapNode;
	cocos2d::CCSprite * pStarSprite;
public:
	grapstar_tag()
	{
		bIsGrapNode = false;
		pStarSprite = NULL;
	}
	grapstar_tag(bool bGrapNode,cocos2d::CCSprite * pSprite)
	{
		bIsGrapNode = bGrapNode;
		pStarSprite = pSprite;
	}
}GrapStarNode,*PGrapStarNode;


class  GrapStarsProgress : public cocos2d::CCNode
{ 
public: 
	GrapStarsProgress();
	virtual ~GrapStarsProgress();
public: 
	static GrapStarsProgress  *  createGrapStarsProgress(int maxStarsCount,int activeCount,float fSpace);
	bool  initGrapStarsProgress(int maxStarsCount,int activeCount,float fSpace);
public: 
	void  setStars(int maxStarsCount,int activeCount);
	void  setStars(int activeCount); 
protected:
	void  updateTexture();
	void  updateInterStar();
protected:
	std::vector<GrapStarNode> m_starsVector;
	int						   m_nMaxStarsCount;
	int						   m_nActiveStarsCount;
	float					   m_fSpace;
};
 
 
 
#endif