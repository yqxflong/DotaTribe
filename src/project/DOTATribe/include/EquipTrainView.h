//Name:EquipTrainView
//Function:装备洗练
//Author:fangjun
//Date:20130819

#ifndef _DOTATRIBE_EQUIPTRAIN_VIEW_H_
#define _DOTATRIBE_EQUIPTRAIN_VIEW_H_

#include "../include/SubView.h"
#include "../include/CDragSprite.h"
#include "../include/BagEquipDataHandler.h"
#include "../include/AnimationEffect.h"
#include "../include/AnimationFileDataManager.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/CAnimationSprite.h"

class EquipTrainView : public HLSubView, AnimationEffectCallBackProtocol
{
private:
	enum{
		tBg = 0,
		tLock1,
		tLock2,
		tLock3,
		tLock4,
		tAttri1,
		tAttri2,
		tAttri3,
		tAttri4,
		tAttri1Max,
		tAttri2Max,
		tAttri3Max,
		tAttri4Max,
		tNewAttri1,
		tNewAttri2,
		tNewAttri3,
		tNewAttri4,
		tNewAttri1Max,
		tNewAttri2Max,
		tNewAttri3Max,
		tNewAttri4Max,
		tLockMask1,//锁位置替代节点，x为左侧x坐标，y为右侧x坐标
		tLockMask2,
		tLockMask3,
		tLockMask4,
		tLockNumBg,
		tLockValue,//锁个数
		tGoldPic,
		tGoldValue,//花费金钱数
		tTrainBtn,
		tTrainLabel,
		tOneTrainBtn,
		tOneTrainLabel,
		tAnimationNode,//特效挂载节点
		tArrow1,
		tArrow2,
		tArrow3,
		tArrow4,
	}Page;

	BagEquipData * m_pCurEquip;//停止使用对象指针，因为在同步对象信息时原有存在的对象可能会被覆盖。

	CAnimationSprite * m_pAnimationPlayNode;//播放动画节点
	CPriorityLayerColor * m_pAnimationGrayLayer;

	bool m_bInOneKeyTrainMode;

	int m_iWillUnLockAttributeIndex;

public:
	EquipTrainView();
	virtual ~EquipTrainView();

private:
	inline void _initLayout();
	inline void _initAnimationEffect();//初始化特效数据
	inline void _mapAllBtn();
	inline void _enableTrainBtn(bool enabled);
	inline void _enableOneKeyTrainBtn(bool enabled);

	inline void _setBtnSelected(int key, bool selected);//for lockbtn only

	inline void _setResultAreaVisiable(bool visiable);

	inline void _setLabel(int key, cocos2d::CCNode * pParent, const char * txt);

	inline void _setNodeVisible(int key, bool isVisible);
	inline void _setNodeVisible(int key, CCNode * pParent, bool isVisible);

	//显示左边为洗练之前的属性
	inline void _showLeftAttribute();
	inline void _showLeftAttributeWhenOneKey();

	inline void _mapAttriToLockPosition();//将属性和锁的位置绑定

	inline void _showLockStatus();//显示属性锁状态
	inline void _showMoney();//显示花费金钱
	inline void _showLockObjectNum();//显示锁物品个数

	inline void Train();//洗练

	//播放动画
	inline void PlayEffect();
	//创建遮罩层，用于特效显示时屏蔽用户点击
	void _createGrayLayer(int pri);
	void _removeGrayLayer();

protected:
	virtual bool onLoad();

	virtual bool onDestroy();

	virtual bool onTick();

	/*
		来自装备列表的调用
	*/
	virtual void EquipHasBeenSeleted(int equipID);
	
	/*
		来自强化窗口的回调
	*/
	virtual void EventWindowCallBack(int iEventType, std::list<std::string>& paramList);

	void On_ClickEvent(cocos2d::CCObject* pSender);

	void On_Lock_ClickEvent(cocos2d::CCObject * pSender);

public:
	//动画结束回调
	virtual void  EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr);

public:
	/*
		接收事件，设置当前锁定的属性
	*/
	void Function_LockAttribute();

	/*
		接收事件，设置当前解锁的属性
	*/
	void Function_UnLockAttribute();

	/*
		接收事件，设置洗练结果
	*/
	void Function_TrainResult();

	/*
		接收事件，获得装备属性锁状态。
	*/
	void Function_GetAttributeStatus();

	/*
		接收事件，获得背包物品更新时通知页面进行更新
	*/
	void Function_RefreshBagObjectShow();

	/*
		确定使用一键洗练
	*/
	void Function_ConfirmUseOneKeyTrain();

public:
	void MoveLockPosition(bool right);//切换锁显示位置,true右边，left，左边
};



#endif