//Name：SHSubView
//Function：为ShopWindow提供统一接口
//Written By：lvyunlong

#ifndef  _DOTATRIBE_SHSUBVIEW_H_
#define  _DOTATRIBE_SHSUBVIEW_H_

#include <cocos2d.h>
#include <cocos-ext.h>

class SHSubView:public cocos2d::CCNode{
public:
	virtual bool onLoad()=0;
	virtual bool onDestroy()=0;
	virtual bool onTick()=0;
	virtual bool onUpdata()=0;
	virtual bool onUpdateText()=0;

	//来自强化窗口的回调
	virtual void EventWindowCallBack(int iEventType, std::list<std::string>& paramList){};

	void _refreshTableView(cocos2d::extension::CCTableView * table) const
	{
		table->reloadData();
		table->setContentOffset(ccp(0, table->getViewSize().height - table->getContentSize().height));
	}
/*
	enum
	{
		_TYPE_GOLD_ = 0,
		_TYPE_JEWEL_ ,
		_TYPE_PRESTIGE_,
		_TYPE_EXCHANGE_ITEM_,
	};*/
};
#endif