#ifndef  _DOTATRIBE_DT_HERO_ICON_H_
#define  _DOTATRIBE_DT_HERO_ICON_H_

#include  <cocos2d.h>
#include "../include/CPublicVarReader.h"
#include "../include/CMenuItemSprite.h"

using namespace cocos2d;

//复合英雄头像()
class   DTHeroIcon : public cocos2d::CCNode
{
public:
	default_construct_vdestroy(DTHeroIcon)
public:
	static DTHeroIcon *  createHeroIcon(int iconID,int qualiy,bool isLargeIcon,int touchPrioty=-5);
protected:
	bool   initHeroIcon(int iconID,int qualiy,bool isLargeIcon,int touchPrioty);
public:
	void  setHeroIconID(int heroIconID);
	void  setHeroIconVisable(bool isVisiable);
	void  setHeroQualiy(int heroQualiy); 
	void  setIconScale(float scale);
	void  setIconColor(const cocos2d::ccColor3B& color3);
	void  setHeroAttachParam(int attachParam1,int attachParam2);
	virtual void  setPosition(const cocos2d::CCPoint &position);
	virtual const cocos2d::CCPoint& getPosition(); 
	void  setMenuSelector(int uiIndex,cocos2d::CCNode * pDelegate,SEL_MenuHandler pSelector);
	
private: 
	void   updateTexrure();
	property_unit_ronly(int,m_nIconID,HeroIconID)
	property_unit_ronly(int,m_nQualiy,HeroQualiy)
	property_unit_ronly(float,m_fScale,HeroIconScale)
	property_unit_ronly(bool,m_bLargeIcon,LargeHeroIcon) 
	property_unit_ronly(CMenuItemSprite *,m_pMenuItemSprite,HeroItemSprite) 
	property_unit_ronly(cocos2d::CCSprite *,m_pHeroIcon,HeroIconSprite) 
	property_unit_ronly(cocos2d::CCSprite *,m_pBgkHero,HeroBGSprite) 
	property_unit_ronly(cocos2d::CCMenu *,m_pMarkMenu,MarkMenu) 
	property_unit_ronly(cocos2d::CCSprite *,m_pHeroQualityMask,HeroQualityMask)
	property_unit_ronly(int,m_nTouchPrioty,TouchPrioty); 
};



 
#endif