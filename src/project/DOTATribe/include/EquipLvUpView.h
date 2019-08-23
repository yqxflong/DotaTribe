//Name : EquipLvUpView
//Function：装备升级界面
//Written By : 方骏->尹强
//AnchorPoint:  (0,0) can not change

#ifndef  _DOTATRIBE_EQUIPLVUPVIEW_H_
#define  _DOTATRIBE_EQUIPLVUPVIEW_H_

#include "../include/SubView.h"
#include "../include/CTouchSprite.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/AnimationEffect.h"
#include "../include/AnimationFileDataManager.h"
#include "../include/BagEquipDataHandler.h"

#include "../include/FAnimationButton.h"

class BagEquipData;
class EquipLvUpView: public HLSubView
	,public cocos2d::extension::CCTableViewDataSource
	,public AnimationEffectCallBackProtocol
	,public FrameAnimationDelegate
	,public CPriorityLayerColorDelegate
{
private:
	enum{
		udRIGHTBG,
		udEXPBOARD,
		udEXPBAR,
		udEQUIP,			//替代节点
		udBTNCHOOSE,
		udBTNBUY,
		udBTNLVUP,
		udBTNCHOOSETITLE,
		udBTNBUYTITLE,
		udBTNLVUPTITLE,
		udLV,
		udLVVALUE,
		udATTRIBUTE,
		udATTRIBUTEVALUE,
		udCOSTICON,
		udCOSTNUM,
		udTABLEVIEW,
		udTABLEVIEWCELL,		//替代节点
		udAnimationNode,	//特效挂载点
		udNOCOSTCARDHINT,		//无素材提示
		udNOEXPBALLHINT,		//无经验珠提示
		udDAIJIJIANTOUNODE,	//待机箭头节点
		udADDMATERIAL,		//一件添加点基层
		udADDICON,			
		udADDLABELTEXT,		
	}VIEW;
	enum{
		udBG1,
		udBG2,
		udOBJ1,
		udOBJ2,
		udNAME1,
		udNAME2,
		udSTAR1,
		udSTAR2,
		udTYPE1,
		udTYPE2,
	}CELL;
	cocos2d::CCSize m_szCell;
	cocos2d::CCNode * m_pResultView;
	cocos2d::extension::CCTableView * m_pTableView;
	cocos2d::ccColor3B m_oCostColor;
	//////////////////////
	cocos2d::CCSprite * m_pAnimationPlayNode;//播放动画节点
	AnimationFileData * m_pAnimationFileData;//特效文件
	PAnimation_Call_Node m_pAnimationCallBack;//回调动画
	cocos2d::CCAnimation * m_pAnimation;//动画
	CPriorityLayerColor * m_pAnimationGrayLayer;//灰度
	CPriorityLayerColor * m_pOneKeyAddLayer;//一键添加灰层

	BagEquipData m_OldEquipData;

	int m_iTickAnimationAction;
	bool m_bInPlayingAnimation;
	CCSprite * m_pAnimationWhiteSp;

	FrameAnimationNode * m_pFrameAnimationNode;
	cocos2d::extension::CCSkeletonAnimation* m_pArrow;//购买引导箭头

	cocos2d::CCArray* ProgressArray;
	int ProgressRunTimes;
public:
	EquipLvUpView();
	virtual ~EquipLvUpView(){};
private:
	inline void _initData();
	inline void _initLayout();
	inline void _initOldCostColor();
	inline void _initAddMaterialLayer();
	inline void _initAnimationEffect();
	inline void _setCellSize();
	inline void _mapAllBtn();
	inline void _mapBtn(int key);
	inline void _setTableView();
	inline void _setAddMaterialIconAndLabel();
	inline void _setExpBar(BagEquipData* bb);
	inline void _showAddMaterial(bool flag);
	inline void _showEquip();

	//设置结果面板信息
	inline void _setResultInfo();
	inline void _setResultExpBar(int exp,int mapexp);
	//
	/*
		进入选取素材界面
	*/
	inline void _enterChooseCard();

	//判断并显示选择的英雄信息
	inline void _checkEquipID();
	//查看是否可以启用升级按钮
	inline void _checkLvBtnStatus();
	//
	/*
		隐藏装备信息
	*/
	inline void _showEquipInfo(bool isShow);

	/*
		禁用button
	*/
	inline void _enableBtns(bool enabled);
	/*
		Cell相关
	*/
	inline void _createTableCell(cocos2d::extension::CCTableViewCell* cell);
	inline void _setTableCell(cocos2d::extension::CCTableViewCell* cell,int idx);
	void _setBlockInfo(cocos2d::extension::CCTableViewCell* cell,int blockIdx);
	void _showBlock2(cocos2d::CCNode* cell,bool isShow);
	void _initProgressTimer();
	//播放动画
	inline void PlayEffect();
	//进度条动画
	void _setProgress();
	//进度条动画回调
	void CallbackBtnEnable();
	//进度条动画回调2
	void CallbackTTF();
	//创建遮罩层，用于特效显示时屏蔽用户点击
	void _createGrayLayer();
	void _removeGrayLayer();
	/*
		设置引导购买箭头
	*/
	void _setGuidejiantou();
	/*
		买素材
	*/
	inline void _buyCost();

	//检查金钱颜色
	inline void _checkCostColor();

	//设置花费金钱
	inline void _setCost();

	/*
		显示装备升级结果的动画
	*/
	inline void _showResultView();	
	/*
		检查素材卡是否为空
	*/
	void _checkCostCardEmpty();
	/*
		检查经验珠是否为空
	*/
	bool _checkExpBallEmpty();
	/*
		设置主卡
	*/
	void _resetMainCard(int equipID);
	/*
		设置主卡备份
	*/
	void _setOldEquipInfo(BagEquipData* data);
	/*
		关闭结果界面
	*/
	void _closeResultView();
	/*
		设置装备属性信息
	*/
	void _refreshLeftInfo();
	/*
		刷新右边信息
	*/
	void _refreshRightInfo();
	
protected:
	virtual bool onLoad();
	virtual bool onDestroy();
	virtual bool onTick();
	/*
		来自装备列表的调用
	*/
	virtual void EquipHasBeenSeleted(int equipID);

	//来自强化窗口的回调
	virtual void EventWindowCallBack(int iEventType, std::list<std::string>& paramList);
	//
	void On_ClickEvent(cocos2d::CCObject* pSender);

protected:
	    /**
     * cell height for a given table.
     *
     * @param table table to hold the instances of Class
     * @return cell size
     */
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    /**
     * a cell instance at a given index
     *
     * @param idx index to search for a cell
     * @return cell found at idx
     */
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    /**
     * Returns number of cells in a given table view.
     * 
     * @return number of cells
     */
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

public:
	//动画结束回调
	virtual void  EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr);
	//灰层遮罩回调
	virtual void touchEvent(CPriorityLayerColor* pLayerColor);
public:
	/*
		接受事件，设置当前窗口的花费金钱，并且设置升级按钮是否可用
	*/
	void Function_SetConstMoney();

	/*
		接受事件，显示升级结果窗口
	*/
	void Function_ShowResultView();

	/*
		升级过程结束，清空内存中已存的数据
	*/
	void LvUpCleadEnd();


	//升级操作
	void _toLvUp();

	/*
		选紫色卡的确认使用框返回，确定使用
	*/
	void Function_ConfirmLvUp();

private:
	void LvUpAnimationActionPart();

public:
	virtual void FrameAnimationIntercept(int frameId, cocos2d::CCNode * node);
};


#endif
