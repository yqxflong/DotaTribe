//Function:寻宝界面

#ifndef _DOTATRIBE_HUNTVIEW_H_
#define _DOTATRIBE_HUNTVIEW_H_

#include "../include/SubView.h"

class HuntView : public SubView
{
	enum{
		_STRING_MINING_HUNT_CD_ = 70,
		_STRING_MINING_LEFT_HUNTTIME_ = 71,
	}LabelString;
private:
	enum{
		mBg = 0,
		mPeoplePic,
		mHuntDescBg,
		mHuntDesc,			//寻宝说明
		mHuntCD,			//寻宝CD
		mHuntBtn,			//寻宝按钮
		mHuntBtnLabel,		//寻宝按钮字
		mGuideArrow,		//寻宝箭头
		mLeftHuntTime,		//剩余寻宝次数
		mBuyBtn,			//购买按钮
		
	}MainPage;

	cocos2d::CCNode* m_pRoot;//窗口根节点

public:
	HuntView();
	virtual ~HuntView();

private:
	inline void _initLayout();
	inline void _mapMainPage();

	inline void _setMainPage();

	void _checkNewFunc();

public:
	virtual bool onLoad();
	virtual bool onDestroy();
	virtual bool onTick();
private:
	/*
		show事件处理
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);

public:
	//主界面按钮操作
	void On_Btn_Click(cocos2d::CCObject * pSender);

public:
	//获得进入抓捕奴隶数据
	void Function_GetEnterMiningData();

};

#endif