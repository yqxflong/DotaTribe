//Name��HeroWindowSubView
//Function���ṩHeroWindowSubViewͳһ�ӿ�
//Written By����ǿ

#ifndef  _DOTATRIBE_HeroWindowSubView_H_
#define  _DOTATRIBE_HeroWindowSubView_H_

#include <cocos2d.h>
#include <cocos-ext.h>


class HeroWindowSubView:public cocos2d::CCNode{
public:
	virtual bool onLoad()=0;
	virtual bool onDestroy()=0;
	virtual bool onTick()=0;
	virtual void onChangeTabIndex(int idx)=0;
	//
	virtual void EventWindowCallBack(int iEventType, std::list<std::string>& paramList)=0;
};
#endif