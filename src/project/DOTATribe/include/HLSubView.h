//Name��HLSubView
//Function��ΪSTRENTHENWINDOW�ṩͳһ�ӿ�
//Written By����ǿ

#ifndef  _DOTATRIBE_HLSUBVIEW_H_
#define  _DOTATRIBE_HLSUBVIEW_H_

#include <cocos2d.h>
#include <cocos-ext.h>

class HLSubView:public cocos2d::CCNode{
public:
	virtual bool onLoad()=0;
	virtual bool onDestroy()=0;
	virtual bool onTick()=0;

	//-1��֪ͨûѡ���κ�װ��
	virtual void EquipHasBeenSeleted(int equipID){};
	//����ǿ�����ڵĻص�
	virtual void EventWindowCallBack(int iEventType, std::list<std::string>& paramList){};
};
#endif