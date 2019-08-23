//Name: RollingBoard.h
//Function: 提供奖励数字翻盘效果
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

	int m_nShowingId;//当前展示的卡片Id

	float m_A;//对应数学表达式为 y = -a * (x - time/2)^2 + (time/2)^2
	float m_fDistance;//每张卡牌需要移动的距离

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
		匀加速启动
	*/
	void Run();

	/*
		匀减速停止
	*/
	void Stop();

	/*
		
	*/
	void ResetZero();


private:
	void DoCallBack();

	void Move();

	/*
		根据当前时间，计算出下一张卡牌需要花费多长时间完成这次移动
	*/
	float CalculateSpentTime(float nowTime);

	float CalculateBlurSize();

	void CalculateMileStone();

	//根据当前展示卡牌的Id，将这些卡牌依次设置位置
	void SetCardsPosition();

	void MoveToCallback(CCNode* sender);
};


#endif