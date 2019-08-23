////////////////////////////////////////////////////////////////
//Name:	 EquipsRecastSubView.h
//Auchor: 	xiaobo.wu
//Func:	 装备重铸
//Maintainer: 	xiaobo.wu
//date:   2014/03/31
////////////////////////////////////////////////////////////////

#ifndef _DOTATRIBE_EQUIPRECAST_VIEW_H_
#define _DOTATRIBE_EQUIPRECAST_VIEW_H_

#include "../include/SubView.h"
#include "../include/BagEquipDataHandler.h"
#include "../include/AnimationEffect.h"
#include "../include/CAnimationSprite.h"

class  EquipRecastDataInfo;


class EquipsRecastSubView : public HLSubView, AnimationEffectCallBackProtocol
{
public:
	//内部更新事件类型
	enum
	{ 
		_EQUIP_CAST_UPDATE_EQUIP_INFO_,
		_RQUIP_CAST_UPDATE_EQUIP_SUCCESS_DO_,
	};
private:
	enum
	{  
		_EQUOP_CAST_RIGHT_BG_,
		_EQUIP_CAST_REWARD_LABEL_,
		_EQUIP_CAST_REWARD_BG_,
		_EQUIP_CAST_EQUIP_ICON_,
		_EQUIP_CAST_EQUIP_NAME_,
		_EQUIP_CAST_EQUIP_LEVEL_,
		_EQUIP_CAST_REWARD1_BG_,
		_EQUIP_CAST_REWARD1_ICON_,
		_EQUIP_CAST_REWARD1_NAME_,
		_EQUIP_CAST_REWARD1_COUNT_,
		_EQUIP_CAST_REWARD2_BG_,
		_EQUIP_CAST_REWARD2_ICON_,
		_EQUIP_CAST_REWARD2_NAME_,
		_EQUIP_CAST_REWARD2_COUNT_,
		_EQUIP_CAST_REWARD3_BG_,
		_EQUIP_CAST_REWARD3_ICON_,
		_EQUIP_CAST_REWARD3_NAME_,
		_EQUIP_CAST_REWARD3_COUNT_,
		_EQUIP_CAST_CAST_BTN_,
		_EQUIP_CAST_CAST_LABEL_, 
		_EQUIP_CAST_DESC_1_LABEL,  
		_EQUIP_CAST_EFFECT_,
		_EQUIP_CAST_MASK_,
	}PAGE;

public:
	EquipsRecastSubView();
	virtual ~EquipsRecastSubView();

private:
	inline void _initLayout();

	inline void _bindMenuSelector();

protected:
	virtual bool onLoad();

	virtual bool onDestroy();

	virtual bool onTick();

	void  initLayer();

public: 
	/*
	 绑定按钮时事件
	*/
	void   CommonMenuSelectorHandler(cocos2d::CCObject * pSender);
	 
	/*
		来自装备列表的调用
	*/
	virtual void EquipHasBeenSeleted(int equipID);
	
	/*
		来自强化窗口的回调
	*/
	virtual void EventWindowCallBack(int iEventType, std::list<std::string>& paramList);

public:
	//动画结束回调	
	virtual void  EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr);

protected:
	void	  UpdateUIWithData(); 
	void      DispatchEventHandler(int receiptCode);
	BagEquipData *  GetActiveEquipData(int equipID);
	void      _initToDefualtUI();
	void      ShowFunctionDescription(bool visiable);
private:
	int						 m_nActiveEquipID;
	EquipRecastDataInfo *    m_pEquipRecastDataInfo;
	bool					 m_bEquipBreakDownSuccess;
	bool					 m_bEquipEffectFinish;
	 
};



#endif