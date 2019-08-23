//Name：HELinkNode
//Function：当英雄没装备时，链接玩家去各场景
//Written By：尹强

#ifndef  _DOTATRIBE_HELinkNode_H_
#define  _DOTATRIBE_HELinkNode_H_

#include <cocos2d.h>

class HELinkNode : public cocos2d::CCNode
{
private:
	enum{
		kHINT,
		kBAR_RISK,
		kBAR_FUBEN,
		kBAR_TOWER,
		kNAME_RISK,
		kNAME_FUBEN,
		kNAME_TOWER,
		kBTN_RISK,
		kBTN_FUBEN,
		kBTN_TOWER,
	};
public:
	HELinkNode();
	virtual ~HELinkNode(){};
public:
	static HELinkNode* create();
	bool init();
	//
	
private:
	inline void _initLayout();
	inline void _mapBtn();
	inline void _checkCondition();
	
protected:
	void On_Click_Event(cocos2d::CCObject* pSender);
};


#endif
