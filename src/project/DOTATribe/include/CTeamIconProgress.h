#ifndef   _DOTATRIBE_CTEAMICONPROGRESS_H
#define   _DOTATRIBE_CTEAMICONPROGRESS_H
#include   <cocos2d.h>
#include   <vector>
 
////////////////////////////////////////////////////////////////
//Name:	 CTeamIconProgress
//Auchor: 	xiaobo.wu
//Func:	  组队头像队列
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////

struct  teamiconitem
{
public:
	teamiconitem()
	{
		isGrap=false;
		pIconSprite=NULL;
	} 
	bool isGrap;
	cocos2d::CCSprite * pIconSprite;
};


class CTeamIconProgress: public cocos2d::CCNode 
{  
public:
	CTeamIconProgress();
	virtual ~CTeamIconProgress();
	static  CTeamIconProgress * createTeamIconProgress(std::string normalFile,std::string grapFile,float finterDistance,bool isFlipX=false,int defualtCount=3);
	void    resetProgress();
	void    reduceActiveCount();
	void    setActiveCount(int activeCount);
	void    unActiveAllProgress();
protected:
	bool	initTeamIconProgress(std::string normalFile,std::string grapFile,float finterDistance,bool isFlipX,int defualtCount);
	void    setSpriteEnable(teamiconitem & iconItem,bool isEnable);
protected:
	std::string  m_sNoramName;
	std::string  m_sGrapName;
	int			m_nDefaultCount;
	int			m_nActiveCount;
	bool		m_bisFlipX;
	std::vector<teamiconitem>  m_teamItemsVector;
	float		m_fInterDistance;

};



#endif