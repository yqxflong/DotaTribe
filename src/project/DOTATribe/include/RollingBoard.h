//Name: RollingBoard.h
//Function: �ṩ�������ַ���Ч��
//Author: FangJun
//Date: 3,26,2014

#ifndef _DOTA_ROLLINGBOARD_H_
#define _DOTA_ROLLINGBOARD_H_

#include <cocos2d.h>
#include <string>
#include <vector>
#include "../include/AnimationEffect.h"
#include "../include/BlurSprite.h"

using namespace cocos2d;

class DulNodeList
{
private:
	std::vector<CCNode *> m_vNodeList;
	int m_nSize;
public:
	DulNodeList();
	~DulNodeList();
	void PushBack(CCNode *);
	CCNode * GetNodeById(int id);
};

class RollingBoard : public CCNode
{
private:
	std::vector<std::string> m_vBoardPicPath;
	std::string m_sBoardPath;
	DulNodeList m_lNodeList;
	int m_nResultNumber;
	float m_fDuringTime;
	AnimationEffectCallBackProtocol * m_pCallBack;
	int m_nCallBackScript;

	int m_nShowingId;//��ǰչʾ�Ŀ�ƬId

	float m_A;//��Ӧ��ѧ���ʽΪ y = -a * (x - time/2)^2 + (time/2)^2
	float m_fDistance;//ÿ�ſ�����Ҫ�ƶ��ľ���

	float totalTime;
	float movetime;
	int actionResult;
	int ConstDestActionResult;

	int mileStone1;
	int mileStone2;
	int mileStone3;

	long long t;
	float c;
	float n;
	float ca;
public:
	RollingBoard();
	virtual ~RollingBoard();


public:
	static RollingBoard * create(std::string numPathTemplate, int picNum, std::string boardPath, int resultNumber, float duringTime, AnimationEffectCallBackProtocol * pDelegate, float distance, float w, float h, float rpx, float rpy);

	bool init(std::vector<std::string> filePath, std::string boardPath, int resultNumber, float duringTime, AnimationEffectCallBackProtocol * pDelegate, float distance, float w, float h, float rpx, float rpy);

	void RegisterCallBackScript(int nScript);

	void SetResultNum(int number);

	/*
		�ȼ�������
	*/
	void Run();

	/*
		�ȼ���ֹͣ
	*/
	void Stop();

	/*
		
	*/
	void ResetZero();


private:
	void DoCallBack();

	void Move();

	/*
		���ݵ�ǰʱ�䣬�������һ�ſ�����Ҫ���Ѷ೤ʱ���������ƶ�
	*/
	float CalculateSpentTime(float nowTime);

	float CalculateBlurSize();

	void CalculateMileStone();

	//���ݵ�ǰչʾ���Ƶ�Id������Щ������������λ��
	void SetCardsPosition();

	void MoveToCallback(CCNode* sender);
};


#endif