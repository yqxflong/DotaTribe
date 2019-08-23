//Name：SubView
//Function：为STRENTHENWINDOW提供统一接口
//Written By：尹强

#ifndef  _DOTATRIBE_SubView_H_
#define  _DOTATRIBE_SubView_H_

#include <cocos2d.h>
#include <cocos-ext.h>

class SubView : public cocos2d::CCNode{
public:
	virtual bool onLoad()=0;
	virtual bool onDestroy()=0;
	virtual bool onTick()=0;

	//来自强化窗口的回调
	virtual void EventWindowCallBack(int iEventType, std::list<std::string>& paramList){};
};


class HLSubView : public SubView{
public:
	//
	virtual void EquipHasBeenSeleted(int equipID) = 0;
};
#endif