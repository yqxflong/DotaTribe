#ifndef   _DOTATRIBE_SELECTSKILLWINDOW_H_
#define   _DOTATRIBE_SELECTSKILLWINDOW_H_
//Author: xiaobo.wu
//Description:  技能面板视图
//Date:  2013.06.30 
#include        <cocos2d.h>
#include       "../include/SelectSkillMode.h"
#include       "../include/SelectSkillController.h"
#include       "../include/SelectSkillDataType.h"
#include       "../include/UIDragNode.h"
#include       "../include/SkillTipsDialog.h"
#include       "../include/RoleSkillsDataHandler.h"
#include       "../include/UIViewDataManger.h"
#include       "../include/MaskNode.h"
#include	   "../include/CCSignSprite.h"
#include	   "IWindow.h"
#include		"cocos-ext.h"
#include        <vector>
 
class  SelectSkillController;
class  CCDragNodeLayer;


 typedef struct  notch_pos_data_tag
 { 
	 cocos2d::CCPoint position;
	 cocos2d::CCRect touchRect;
 public:
	 notch_pos_data_tag()
	 {
		 position=CCPointZero;
		 touchRect=CCRectZero;
	 }
 }NotchPos_Data,*PNotchPos;

class   SelectSkillWindow :public IWindow, public UIBaseDialogProtory
{
public:
	enum
	{
		_SKILL_UI_BG_TAG_,
		_SKILL_UI_CLOSE_BTN_TAG_,
		_SKILL_UI_HELP_BTN_TAG_,
		_SKILL_UI_SKILL_RESET_BTN_TAG_,
		_SKILL_UI_SKILL_RESET_LABEL_TAG_,
		_SKILL_UI_SKILL_ADDPOINT_BTN_TAG_,
		_SKILL_UI_SKILL_ADDPOINT_LABEL_TAG_,
		_SKILL_UI_ADDPOINT_RESET_BTN_TAG_,
		_SKILL_UI_ADDPOINT_RESET_LABEL_TAG_,
		_SKILL_UI_ADDPOINT_SURE_BTN_TAG_,
		_SKILL_UI_ADDPOINT_SURE_LABEL_TAG_,
		_SKILL_UI_SKILL_PANEL_TAG_,
		_SKILL_UI_COMMON_FIRST_SKILL_TAG_,
		_SKILL_UI_COMMON_OFFSET_SKILL_TAG_,
		_SKILL_UI_SKILL_BG_SKILL_TAG_,
		_SKILL_UI_SKILL_DIABLE_BG_SKILL_TAG_,
		_SKILL_UI_SKILL_ADPET_BG_SKILL_TAG_,

		_SKILL_UI_SKILL_NOTCH_BG_1_TAG_,
		_SKILL_UI_SKILL_POINT_BG_1_TAG_,

		_SKILL_UI_SKILL_NOTCH_BG_2_TAG_,
		_SKILL_UI_SKILL_POINT_BG_2_TAG_,
		 
		_SKILL_UI_SKILL_NOTCH_BG_3_TAG_,
		_SKILL_UI_SKILL_POINT_BG_3_TAG_,
		 
		_SKILL_UI_SKILL_NOTCH_BG_4_TAG_,
		_SKILL_UI_SKILL_POINT_BG_4_TAG_,

		_SKILL_UI_SKILL_NOTCH_BG_5_TAG_,
		_SKILL_UI_SKILL_POINT_BG_5_TAG_,

		_SKILL_UI_SKILL_NOTCH_BG_6_TAG_,
		_SKILL_UI_SKILL_POINT_BG_6_TAG_,
		
		_SKILL_UI_SKILL_LOCK_TAG_,

		_SKILL_UI_SKILL_SEGMENT_HEIGHT_TAG_,	//技能凹槽分割线高度 用于快速搜索

		_SKILL_UI_SKILL_JEWEL_BG_TAG_,
		_SKILL_UI_SKILL_JEWEL_LABEL_TAG_,

		_SKILL_UI_SKILL_GOLD_BG_TAG_,
		_SKILL_UI_SKILL_GOLD_LABEL_TAG_,
		 
		_SKILL_UI_SKILL_NEED_JEWLE_NUM_TAG_,

		_SKILL_UI_SKILL_RESET_SKILL_ICON_TAG_,

		_SKILL_UI_SKILL_NEW_TIPS_TAG_,

		_SKILL_UI_DRAG_CONTROL_TAG_=77,

		_SKILL_UI_SKILL_ROOT_TAG_,   //技能父节点

	}; 

	 
	  SelectSkillWindow();
	  ~SelectSkillWindow();
public:
    /*
		初始化处理
	*/
	virtual    bool    Init();
	/*
		加载处理
	*/
	virtual    bool    Load();
	 
	/*
		桢更新处理
	*/
	virtual    void    Tick();
	/*
		销毁处理
	*/ 
	virtual    void    Destroy();
  
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

    /*
	   消息回调函数
	*/ 
	virtual    void    BaseDialogCallBackHandler(int eventType,void * ptr);

	/*
	初始加载UI组件
	*/
	void    LoadUIConfig();
	 
	/*
	绑定静态按钮事件
	*/
	void    InitStaticBtnMap();

	/*
	动态绑定按钮事件回调
	*/
	void    MapBtnWithTag(cocos2d::CCNode * pBaseLayer,int menuTag);

	/*
	动态设置组件的可视属性
	*/
	void    SetSubNodeVisibleWithTag(int tag,bool isVisible);

	/*
	移除之前技能图标
	*/
	void    RemovePreSkillsIcon();
	 
public: 
	 
	 int     checkTargetNotchCoverID(CCSignSprite * pDragNode);	
 
	 void    UpdateCommonSkillPanelWithUserData(PCOMMONSKILLDATA * pCommonSkillData);

     void    UpdateEquipSkillPanelWithUserData(std::vector<PSkillNotoch> &  userEquipSkillData);

	 void    ShowSkilInfoDialogFromSkillID(int skillItemID,bool isCommondSkill=true);

	 void    CallBackBtnClickHandler(cocos2d::CCObject * pSender);
	  
	 cocos2d::CCNode *   GetViewBaseLayer();

	 cocos2d::CCNode *   GetSkillTipsViewLayer();
	  
protected:
     
	void    ShowWaittingLayer();

	void    HideWaittingLayer();

	/*
	获得左上第一个技能的坐标位置
	*/
	cocos2d::CCPoint  GetLeftTopSkillIconPostion();

	/*
	获得公共技能面板偏移的坐标位置
	*/
	cocos2d::CCSize   GetCommonSkillOffSetSize();
	  
	/*
	获取指定二维坐标的技能布局位置
	*/
	cocos2d::CCPoint  GetCommonSkillPosition(int xPos,int yPos);

	/*
	获取凹槽技能坐标位置
	*/
	cocos2d::CCPoint  GetTargetSkillPosition(int index);
	   
	MaskNode * GetMaskNodeWithTag(int maskTag);
	 
	void    OnUpdateRoleSkillsUI();

	void    OnShowSelectSkillPanelHandler(); 
	 
	void    GetNotchSkillPosLayout(); 

	void    AddNotchSkillPosDataWithSprite(cocos2d::CCSprite * pNotchSprite);
 
	void    ClearAllEquipSkillNode();

	void    SetAllEquipSkillIconVisable(bool isVisible);

	void    AddSkillPointIconLayOut(bool isLastVisible);		  //技能加点布局

	void    SetAllAddPointIconVisible(bool isVisible);			  //技能加点图标

	void    AddSkillPointWithNotchIndex(int notouchIndex);      //技能凹槽索引ID
	 
	void    CreateSkillTipTemplateDialog();						  //创建Tips模板

	void    InitInterDataConfig();								  //内部数据初始化

	void    CreateDragControlLayer();							  //创建拖拽控制层

	void	UpdatePlayerJewleAndGold();							  //同步玩家金币和钻石

	void	ShowResetSkillNeedInfo();							  //显示重置技能所需信息

	void    OpenSixthSkillRequestHandler();						  //申请开启第六技能

	void    UnLockSixthSkillHandler();							  //解锁第六格技能
  
protected:

	cocos2d::CCNode *  pBaseViewNode;
	cocos2d::CCNode *  pSkillTipsViewNode;

	int   canUserNotchSkillCount;								//最大可装备技能凹槽数目

	std::vector<NotchPos_Data>    equipSkillNotchPosVec;		//装备的技能凹槽
	
	SelectSkillController  *  pSelectSkillController;			//选择技能管理器

	SkillTipsDialog  * pSkillTipsDialog;						//技能描述对话框

	int		preWindowType;									    //前窗口的类型

	int     roleSkillsEndTagID;						            //技能图标数目

	CCDragNodeLayer *   pDragNodeLayer;							//拖拽控制层

    std::vector<int>     activeSkillIconTagVec;					//激活可以拖拽的图标的tag数组	 

	int		nUIAdpetEffectID;									//专精技能ID

	int		nDefaultSkillTipsID;								//默认打开的技能Tips技能ID
public:
	unsigned char		heroIndex;											//英雄索引
};
 



#endif