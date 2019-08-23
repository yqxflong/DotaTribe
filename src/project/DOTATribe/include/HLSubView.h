//Name：HLSubView
//Function：为STRENTHENWINDOW提供统一接口
//Written By：尹强

#ifndef  _DOTATRIBE_HLSUBVIEW_H_
#define  _DOTATRIBE_HLSUBVIEW_H_

#include <cocos2d.h>
#include <cocos-ext.h>

class HLSubView:public cocos2d::CCNode{
public:
	virtual bool onLoad()=0;
	virtual bool onDestroy()=0;
	virtual bool onTick()=0;

	//-1：通知没选中任何装备
	virtual void EquipHasBeenSeleted(int equipID){};
	//来自强化窗口的回调
	virtual void EventWindowCallBack(int iEventType, std::list<std::string>& paramList){};
};
#endif