//  Game:DotaTribe
//  Author: fangjun
//  Type: Just A Logic Node,used to Save some data
//
#ifndef _MASKNODE_H_
#define _MASKNODE_H_

#include <cocos2d.h>
#include "../include/UIViewDataManger.h"

class MaskNode : public cocos2d::CCNode{
private:
	UIViewData viewData;
public:
	CREATE_FUNC(MaskNode);
	bool init(){
		return cocos2d::CCNode::init();
	}
	//
	void setViewData(UIViewData * data);
	//
	const UIViewData & GetViewData();

	UIViewData *    GetViewPData();
};

#endif