//Function:Ѱ������

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
		mHuntDesc,			//Ѱ��˵��
		mHuntCD,			//Ѱ��CD
		mHuntBtn,			//Ѱ����ť
		mHuntBtnLabel,		//Ѱ����ť��
		mGuideArrow,		//Ѱ����ͷ
		mLeftHuntTime,		//ʣ��Ѱ������
		mBuyBtn,			//����ť
		
	}MainPage;

	cocos2d::CCNode* m_pRoot;//���ڸ��ڵ�

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
		show�¼�����
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);

public:
	//�����水ť����
	void On_Btn_Click(cocos2d::CCObject * pSender);

public:
	//��ý���ץ��ū������
	void Function_GetEnterMiningData();

};

#endif