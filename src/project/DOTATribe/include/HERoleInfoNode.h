//Name：HERoleInfoNode
//Function：英雄装备--人物信息
//Written By：尹强

#ifndef  _DOTATRIBE_HERoleInfoNode_H_
#define  _DOTATRIBE_HERoleInfoNode_H_

#include <cocos2d.h>
#include "../include/SubView.h"

class HERoleInfoNode : public SubView
{
private:
	enum{
		kHE_LEADERTEXT = 0,
		kHE_LEADERVALUE,
		kHE_QISHITEXT,
		kHE_QISHIVALUE,
		kHE_CHECKBTN,
		kHE_PROGRESSBAR,
	};
public:
	HERoleInfoNode();
	virtual ~HERoleInfoNode(){};
public:
	static HERoleInfoNode* create();
	bool init();
	//
	virtual bool onLoad(){return true;};
	virtual bool onDestroy(){return true;};
	virtual bool onTick(){return true;};

	//来自强化窗口的回调
	virtual void EventWindowCallBack(int iEventType, std::list<std::string>& paramList);
private:
	inline void _initLayout();
	inline void _mapBtn();
	inline void _refreshInfo();
	void _refreshBtnStatus();
protected:
	void On_Click_Event(cocos2d::CCObject* pSender);
};


#endif
