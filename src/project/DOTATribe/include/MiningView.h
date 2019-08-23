//Name: MiningView.h
//Function���ڿ�
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
		mMineName1,			//����
		mTime1,				//�ɼ�ʱ��
		mOutPut1,			//����
		mBtn1,				//��ť
		mBtnLabel1,			//��ť��
		mMineBg2,
		mMinePic2,
		mMineName2,			//����
		mTime2,				//�ɼ�ʱ��
		mOutPut2,			//����
		mBtn2,				//��ť
		mBtnLabel2,			//��ť��
		mMineBg3,
		mMinePic3,
		mMineName3,			//����
		mTime3,				//�ɼ�ʱ��
		mOutPut3,			//����
		mBtn3,				//��ť
		mBtnLabel3,			//��ť��


	}MainPage;

	cocos2d::CCNode* m_pRoot;//���ڸ��ڵ�

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