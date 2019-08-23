//Name£ºHWMoreItems
//Function£ºMoreItems 
//Written By£ºÒüÇ¿

#ifndef  _DOTATRIBE_HWMOREITEMS_H_
#define  _DOTATRIBE_HWMOREITEMS_H_

#include "cocos2d.h"
#include "../include/CMenuItemSprite.h"

class HWMoreItems:public CMenuItemSprite
{
private:
	cocos2d::CCPoint m_oldP;
	cocos2d::CCPoint m_newP;
	const float m_fActionDur;
private:
	void _showItem();
	void _hideItem();
public:
	HWMoreItems()
	:m_fActionDur(0.1f)
	{
		m_nIDX = 0;
		m_nSoundID=-1;
	};
	virtual~HWMoreItems(){}
	static HWMoreItems* create(cocos2d::CCNode* normalSprite,cocos2d::CCObject* target,cocos2d:: SEL_MenuHandler selector);
	bool initWithNormalSprite(cocos2d::CCNode* normalSprite, cocos2d::CCNode* selectedSprite, cocos2d::CCNode* disabledSprite, cocos2d::CCObject* target, cocos2d::SEL_MenuHandler selector);
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
};
#endif