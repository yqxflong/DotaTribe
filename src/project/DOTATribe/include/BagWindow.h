//Name:BagWindow.h
//Function:背包
//Author:fangjun
//Date:20130902

#ifndef _DOTA_BAGWINDOW_H_
#define _DOTA_BAGWINDOW_H_

#include <cocos2d.h>
#include <cocos-ext.h>
#include "../include/IWindow.h"
#include <string>
#include "../include/CPageScroll.h"
#include "../include/MaskNode.h"
#include "../include/CMenuItemSprite.h"
#include "../include/CSprite.h"
#include "../include/CSMapTable.h"
#include "../include/CTipsViewDelegate.h"

class PanelItem : public cocos2d::CCNode{
public:
	enum
	{
		pQUALITY = 0,
		pICON,
		pHat, //遮罩层
		pELEVEL,//强化等级，右上
		pLEVEL,//等级，左下
		pCOUNT,//数量，右下
		pRIGHTTOPBG,//右上背景
		pLEFTDOWNBG,//左下背景
	};
	int _itemId;		//格子所装物品Id
	int _tag;
	int _type;			//格子类型
public:
	void _setEnhanceLevel(int elevel);
	void _setLevel(int level);
	void _setLabelCount(int count);
public:
	PanelItem();
	~PanelItem();
	static PanelItem* createEmpty(int tag, cocos2d::CCObject* target,cocos2d:: SEL_MenuHandler selector);
	void setItemId(int id);
	int getItemId();
};

class InfoPoolData{
public:
	enum{
		INFO_LOCK = -1,
		INFO_EMPTY = 0,
		INFO_HAS = 1,
	};
	InfoPoolData()
	{
		tag = -1; page = -1; itemid = -1; itemcount = -1; enhancelevel = -1;
		quality = -1; icon = -1; infoType = -1; drawed = false;
	};
public:
	int tag;//与格子匹配的位置
	int page;//分页
	int itemid;//物品的ID，这儿不知道是哪种id，需要在外部使用时注意
	int itemcount;//物品数量
	int enhancelevel;//强化等级
	int level;//等级
	int quality;//质量图
	int icon;//图标

	int infoType;//格子中物品的信息
	
	bool drawed;
};

class BoardPoolData{
public:
	BoardPoolData()
	{
		tag = -1;
		page = -1;
		drawed = false;
	}
public:
	int tag;
	int page;
	bool drawed;
};

class BagPool{
public:
	std::vector<BoardPoolData *> board_pool_data;

	std::vector<InfoPoolData *> info_pool_data;

	float board_position[NEWBAG_NUMPERPAGE][2];
	float page_width;
	
	std::string empty_file;			//空版
	std::string select_file;		//选中框
	std::string lock_file;			//锁图

	bool all_board_drawed;
	bool all_info_drawed;

	int filltype;//池中填充物类型
public:
	BagPool();
public:
	/*
		插入池
	*/
	void Insert(BoardPoolData * data);

	void Insert(InfoPoolData * data);
	/*
		删除池中数据
	*/
	void PopPage(int page);

	/*
		将池中的数据挂载
	*/
	void HangPageBoard(int page, cocos2d::CCNode * parent);

	void HangPageInfo(int page, cocos2d::CCNode * parent);

	void HangData(cocos2d::CCNode * parent);

	void HangPage(cocos2d::CCNode * parent);

	/*
		清除信息页
	*/
	void ClearInfoData();

	/*
		清空
	*/
	void Destroy();

	/*
		初始化
	*/
	void Init();

private:
	void createBoard(BoardPoolData * data, cocos2d::CCNode * parent);
	void createInfo(InfoPoolData * data, cocos2d::CCNode * parent);
};


class BagWindow : public IWindow, public CPageScrollDelegate, CTipsViewDelegate
{
private:
	enum{		
		pageObjectList = 0,
		pageComposeList,

	} PAGEKIND;
	
	enum{
		functionSALE,
		functionUSE,
	}USE_SALE;

	enum{
		oNameBg = 0,
		oName,
		oStar,//星级
		oLevel,
		oLevelValue,
		oPrice,
		oPriceValue,
		oGoldIcon,
		oDes,
		oSaleBtn,
		oSaleLabel,
		oUseBtn,
		oUseLabel,
		oGuideArrow,
	}ObjectList;

	enum{
		cComposeLabel = 0,
		cNamebg,
		cQuality,
		cName,
		cNeedLebel,
		cNeedQuality1,
		cNeedQuality2,
		cNeedQuality3,
		cNeedQuality4,
		cNeedValue1,
		cNeedValue2,
		cNeedValue3,
		cNeedValue4,
		cCostLabel,
		cCostValue,
		cGoldIcon,
		cComposeBtn,
		cComposeBtnLabel,
	}ComposeList;

	enum{
		mBagBg = 0,//背包背景
		mBagBg2,	//背景2
		mCloseBtn,	//关闭按钮
		mBagPic,//背包图
		mBagNameBg,	//背包字底图
		mBagName,//背包字
		mObjectListBtn,//物品列表按钮
		mComposeListBtn,//合成按钮
		mLeftArrow,		//向左箭头
		mRightArrow,	//向右箭头
		mLeftArrowMove,		//向左骨骼箭头
		mRightArrowMove,	//向右骨骼箭头
		mPageNumBg,		//页码底图
		mPageNumValue,	//页码值
		mJewelBg,
		mJewelValue,//钻石值
		mGoldBg,
		mGoldValue,//金币值
		mLeftNode,//左挂载点
		mRightNodeMask,//右挂载点
		mObjectGuideArrow,				//指导回物品页背板
		mObjectGuideArrowLabel,			//指导回物品页背板文字
	}Main;

private:
	cocos2d::CCNode * m_pRoot;//本窗口根节点

	cocos2d::CCNode * m_pLeftNode;	//左边的根节点
	CPageScroll* m_pRightPage;		//右侧可翻页面板

	int m_iSubPageKind;//显示子页面号
	cocos2d::CCMenuItemSprite * m_pSelectSubPage;//选择的右侧分面

	//CSprite * m_pCurPage;		//记录当前的分页

	int m_iSelectedTag;	//选中的id，其实就是tag，这是和列表vector位置对应
	cocos2d::CCMenuItemSprite * m_pSelectedItem;//选中的item,为了选中时方便的取消上次选中

	int m_iBtnFunction;//复数输入框弹出前功能

	bool m_bChangedSelectTag;//标记更换了选中框

	int m_iMaxComposeNum;//物品合成时最大可合成数，初值0

private:
	int m_iBackWindow;//返回的界面

private:
	BagPool m_Pool;
	friend class BagPool;

public:
	BagWindow();
	virtual ~BagWindow();
private:
	inline void _initLayout();

	inline void _setText(int tag, cocos2d::CCNode * parent, const char * text);
	inline void _setText(int tag, cocos2d::CCNode * parent, int num);
	inline void _setTexture(int tag,  cocos2d::CCNode * parent, const char * picpath);
	//inline void _setBtnTexture(int tag, cocos2d::CCNode * parent, const char * nor, const char * sel, const char dis);
	inline void _enableBtn(int tag, cocos2d::CCNode * parent, bool enable);
	inline void _setVisible(int tag, cocos2d::CCNode * parent, bool visible);
	inline cocos2d::CCMenuItem * _mapBtnWithTag(int tag, cocos2d::CCNode * parent, CCObject *rec, cocos2d::SEL_MenuHandler selector);

	//初始化右侧列表
	inline void _initRightPanel(MaskNode * node);
	inline void _initLeftPage();//显示左侧界面

	inline void _bindSelectorForTouchSprite(int signID);//绑定点击事件

	inline void _setMainPageInfo();//设置主界面信息
	inline void _setLeftPageInfo(int selecttag);//设置左侧界面信息
	inline void _setRightPanelInfo();//设置右侧显示信息
	inline void _setMenuPage(int pageid);//设置分页选中

	inline void _setDefaultPageAndItem(int selectTag);//设置默认的页和选中框

	inline void _mapMainPageBtn();//绑定主界面按钮//左侧和右侧在各自的init中处理

	inline void _refreshDrawInfoData(int bagType, int tag, int num);//刷新绘制数据部分,参数1是物品分类，参数2为自己容器的index，参数3为物品数量

	inline void _setSelectPage();//选中选取的页面

	//左侧刷新相关
	void _refreshObjectInfo(int selecttag);
	void _refreshComposeInfo(int selecttag);

	//设置金钱\钻石
	void refreshUIData();

public:
	//主页面
	void On_MainPage_Btn_Click(cocos2d::CCObject * pSender);

	//左侧界面
	void On_LeftPage_Btn_Click(cocos2d::CCObject * pSender);

	//右侧表格
	void On_RightMenu_Click(cocos2d::CCObject * pSender);

	//合成界面tips
	void On_ObjectTips_Click(cocos2d::CCObject * pSender);
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
		分页列表继承的事件
	*/
	virtual void changePage(int idx);
	
	/*
		取消tips显示
	*/
	virtual void cancelTipsLayer();

public:
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

private:
	/*
		show事件处理
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	/*
		Refresh主界面等处理
	*/
	void OnRefreshWindowEventHandler(std::list<std::string>& paramList);


private:
	/*
		复数输入功能结果
	*/
	void Function_NumInputResult(int num);

	/*
		确认卖贵重物品
	*/
	void Function_ComfirmSaleImportant();

protected:
	/*
		关闭窗口事件
	*/
	void On_Close_Window(cocos2d::CCObject* pSender);

};

#endif
