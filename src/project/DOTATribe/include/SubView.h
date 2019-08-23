//Name��SubView
//Function��ΪSTRENTHENWINDOW�ṩͳһ�ӿ�
//Written By����ǿ

#ifndef  _DOTATRIBE_SubView_H_
#define  _DOTATRIBE_SubView_H_

#include <cocos2d.h>
#include <cocos-ext.h>

class SubView : public cocos2d::CCNode{
public:
	virtual bool onLoad()=0;
	virtual bool onDestroy()=0;
	virtual bool onTick()=0;

	//����ǿ�����ڵĻص�
	virtual void EventWindowCallBack(int iEventType, std::list<std::string>& paramList){};
};


class HLSubView : public SubView{
public:
	//
	virtual void EquipHasBeenSeleted(int equipID) = 0;
};
#endif