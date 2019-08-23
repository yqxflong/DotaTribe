#ifndef   _COCOS_CCDRAGE_SPRITE_H_
#define   _COCOS_CCDRAGE_SPRITE_H_
#include  <cocos2d.h>
#include  "SingleTouchProtocol.h"

////////////////////////////////////////////////////////////////
//Name:	 CCSignSprite
//Auchor: 	xiaobo.wu
//Func:	 标记精灵
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////

enum   SignSpriteType
{
	_SIGNSPRITE_UNKONW_TYPE_,
	_SIGNSPRITE_COMMON_TYPE_,
	_SIGNSPRITE_TARGET_TYPE_,
};
  
class  CCSignSprite: public cocos2d::CCSprite,public SingleTouchProtocol
{ 
public:
public:
	CCSignSprite();
	~CCSignSprite();
	static  CCSignSprite *  createCCSignSpriteWithFile(int signUniqueID,const char * fileName,SignSpriteType nodeType=_SIGNSPRITE_COMMON_TYPE_,bool isMoveEnable=true);
	static  CCSignSprite *  createCCSignSpriteWithFrameName(int signUniqueID,const char * frameName,SignSpriteType nodeType=_SIGNSPRITE_COMMON_TYPE_,bool isMoveEnable=true);
	void    setInitPosition(cocos2d::CCPoint initPosition);
	cocos2d::CCPoint getInitPosition();
	SignSpriteType   getDragNodeType();
	bool			 getDragEnable();
	void			 setDragEnable(bool bDrageEnable);
	void			 forceToInitPosition();
	bool  checkIsCoverWithRect(float targetleft,float targetright,float targettop,float targetbottom,float offWidth=65.0f);
protected:
	bool  initCCSignSpriteWithFile(int signUniqueID, const char * fileName,SignSpriteType nodeType=_SIGNSPRITE_COMMON_TYPE_,bool isMoveEnable=true);
	bool  initCCSignSpriteWithFrameName(int signUniqueID,const char * frameName,SignSpriteType nodeType=_SIGNSPRITE_COMMON_TYPE_,bool isMoveEnable=true);
	bool  init(int signUniqueID,SignSpriteType nodeType,bool isMoveEnable);
	void  initCalTouchRectAlgorithm();
protected:
	bool		   m_nIsMoveEnable;
	SignSpriteType m_eDragNodeType; 
	cocos2d::CCPoint m_fInitPosition;
};
 

#endif