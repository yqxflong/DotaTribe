#ifndef _DOTATRIBE_CSIMPLEACTIONSPRITE_H_
#define _DOTATRIBE_CSIMPLEACTIONSPRITE_H_
#include <cocos2d.h>
#include "../include/CPublicVarReader.h"
////////////////////////////////////////////////////////////////
//Name:	 CSimpleActionSprite
//Auchor: 	xiaobo.wu
//Func:	 简单动画精灵
//Maintainer: 	xiaobo.wu
//date:   2014/01/21
////////////////////////////////////////////////////////////////
class   CSimpleActionSprite: public cocos2d::CCSprite
{    
public:
	enum
	{
		_UNKONW_ACTION_TYPE_,			//未知动画类型
		_STANDBY_TYPE_,					//待机不动
		_FLOAT_UP_AND_DOWN_TYPE_,		//上下浮动动画 
		_FLOAT_LEFT_AND_RIGHT_TYPE_,	//左右浮动动画
	};
    default_construct_vdestroy(CSimpleActionSprite)
public:
	static CSimpleActionSprite *  create(int actionType,std::vector<float> attachParam);
	void  PlayAction();
	void  StopAction(); 
	property_unit_rw(int,m_nActionType,ActionType) 
	property_unit_rw(std::vector<float>,m_vAttachParam,AttachParams) 
	property_unit_ronly(cocos2d::CCPoint ,m_cInitPosition,InitPosition) 
	void  SetInitPosition(const cocos2d::CCPoint & position);
	property_unit_ronly(std::vector<cocos2d::CCNode * >,m_vChildArray,ChildArray) 
	property_unit_ronly(std::vector<cocos2d::CCPoint>,m_vInitPosition,InitPositionArray) 
	virtual	void addChild(cocos2d::CCNode *pChild); 
protected:
	bool  init(int actionType,std::vector<float> attachParam);
	void  runActionType();
	void  floatUpAndDonwAction();
	void  floatLeftAndRightAction();
 	  
};
 
#endif