//Name：HEHeroPropertyNode
//Function：英雄装备--属性
//Written By：尹强

#ifndef  _DOTATRIBE_HEHeroPropertyNode_H_
#define  _DOTATRIBE_HEHeroPropertyNode_H_

#include <cocos2d.h>
#include "../include/SubView.h"

class HEHeroPropertyNode : public SubView
{
private:
	enum{
		kHE_BG,
		kHE_STRENGTH,
		kHE_DEX,
		kHE_INTELLIGENCE,
		kHE_ATTACK,
		kHE_HP,
		kHE_HIT,
		kHE_PJ,
		kHE_BJ,
		kHE_MP,
		kHE_SPEED,
		kHE_DODGE,
		kHE_ARMOR,
		kHE_UNCRIT,
	};

	int m_nCurIdx;
public:
	HEHeroPropertyNode();
	virtual ~HEHeroPropertyNode(){};
public:
	static HEHeroPropertyNode* create();
	bool init();
	void refreshAllProperty(int tabidx=0);
	//
	virtual bool onLoad(){return true;};
	virtual bool onDestroy(){return true;};
	virtual bool onTick(){return true;};

	//来自强化窗口的回调
	virtual void EventWindowCallBack(int iEventType, std::list<std::string>& paramList);
private:
	void _initLayout();
	void _setRoleValue(int idx);	//力，敏，智
	void _setRoleDetail(int idx);	//人物详细信息
};


#endif
