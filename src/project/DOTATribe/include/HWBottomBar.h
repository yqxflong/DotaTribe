//Name£ºHWBottomBar
//Function£ºHWBottomBar 
//Written By£ºÒüÇ¿

#ifndef  _DOTATRIBE_HWBOTTOMBAR_H_
#define  _DOTATRIBE_HWBOTTOMBAR_H_

#include "cocos2d.h"

class HWBottomBar:public cocos2d::CCSprite
{
	cocos2d::CCPoint m_oldP;
	cocos2d::CCPoint m_newP;
	const float m_fActionDur;
public:
	HWBottomBar()
		:m_fActionDur(0.1f)
	{
	};
	virtual~HWBottomBar(){
	}
	static HWBottomBar*  create(const char *pszFileName);
	bool initWithFile(const char *pszFilename);
	//go to their position
	void movetoOldPoint();
	//go to more's position
	void movetoNewPoint();
	//immediately
	void gotoNewPoint();
	//immediately
	void gotoOldPoint();
	void setOldPoint(const cocos2d::CCPoint& pp){
		m_oldP=pp;
	}
	void setNewPoint(const cocos2d::CCPoint& pp){
		m_newP=pp;
	}
protected:
	void _showItem();
	void _hideItem();
};
#endif