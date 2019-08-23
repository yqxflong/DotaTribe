//Name: MiningView.h
//Function：挖矿
//Author: fangjun
//Date: 2013-11-26

#ifndef _DOTATRIBE_MININGVIEW_H_
#define _DOTATRIBE_MININGVIEW_H_

#include "../include/SubView.h"

class MiningView : public SubView
{
private:
	enum{
		_STRING_MINING_TIME_ = 68,
		_STRING_MINING_OUTPUT_ = 69,
		_STRING_MINING_HUNT_CD_ = 70,
		_STRING_MINING_LEFT_HUNTTIME_ = 71,
	}LabelString;
private:
	enum{
		mBg = 0,
		mMineDesc,
		mMineDescBg,
		mMineBg1,
		mMinePic1,
		mMineName1,			//名称
		mTime1,				//采集时间
		mOutPut1,			//产量
		mBtn1,				//按钮
		mBtnLabel1,			//按钮字
		mMineBg2,
		mMinePic2,
		mMineName2,			//名称
		mTime2,				//采集时间
		mOutPut2,			//产量
		mBtn2,				//按钮
		mBtnLabel2,			//按钮字
		mMineBg3,
		mMinePic3,
		mMineName3,			//名称
		mTime3,				//采集时间
		mOutPut3,			//产量
		mBtn3,				//按钮
		mBtnLabel3,			//按钮字


	}MainPage;

	cocos2d::CCNode* m_pRoot;//窗口根节点

public:
	MiningView();
	virtual ~MiningView();

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