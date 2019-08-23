//Name：MessageBoxWindow
//Function：信息弹窗
//Written By：尹强

#ifndef  _DOTATRIBE_MESSAGEBOXWINDOW_H_
#define  _DOTATRIBE_MESSAGEBOXWINDOW_H_

#include "IWindow.h"

enum{
	kDEFAULT=0,
	kLOGIN_UPDATEHINT,
	kLOGIN_APPSTOREHINT,
	kLOGIN_NOSURPOTHINT,
	kNETWORKDISCONNECTED,		//网络连接断开
	kSERVERMESSAGEPACKET,
	kSELECTPURPLECARD,			//素材选择处选中紫色卡牌
 	kCLIMBTOWERRESET,			//爬塔重置进度
	kGUIDESTART,				//引导开始
	kGUIDESKIP,					//引导跳过
	kSERVANTIDENTITYCHANGED,	//人物身份转换
	kEMAIL_REMOVE_MESSAGE,		//删除邮件二级框

	kBAGSALEIMPORTANTOBJECT,	//出售贵重物品提示

	kTEAMBATTLE_RESETCOMFIRM,	//组队副本重置进度确认提示
	kFRIEND_DELETEFRIEND,		//删除好友

	kCOSTJEWEL_TEAMREWARD,		//花费钻石领取组队副本通关奖励
	kALTARQUALITYHIGH,			//献祭魂碎片高提醒用户

	kUSEONEKEY_TRAIN,			//使用一键洗练
	kEQUIPTIPSSELL,				//装备Tips提醒用出售物品
	kWARNINGUNLOCKATTRIBUTE,	//解锁洗练属性锁定

	kDWARVEN_PAGEINFOCHANGED,		//矮人矿区界面有更新

	kGATEWAY_CONNECTFAIL,		//网关连接失败处理

	kMISSION_GOTONEXTMAP,		//跳转到下一关
	kMISSION_GETSTARREWARD,		//领取三星奖励
	kMISSION_VIPGIFTBOX,		//是否购买vip礼包


	kAUTOMESSAGEBOX,		//自动反馈message提示框

	kUPDATE_FINISH,			//小版本更新结束
};

class MessageBoxWindow : public IWindow
{
private:
	enum{
		udGRAYLAYER,
		udBOXBG,
		udTITLEBG,
		udBackBTNTXTIMAGE,
		udOKBTNTXTIMAGE,
		udBACKBTN,
		udOKBTN,
		udTITLE,
		udTEXT,
	};
	cocos2d::CCNode* m_pRoot;
	std::string m_strTitle;
	std::string m_strText;
	int m_nType;

	int m_confirmEvent;
	int m_cancelEvent;
private:
	bool m_bInSingleMode;
public:
	MessageBoxWindow();
	virtual ~MessageBoxWindow();
private:
	void _initLayout();
	void _mapBtn();
	void _mapText();
	//
	/*
		处理各种类型的事件
	*/
	void _handle_Delete_Friend(int tag);
	void _handle_Login_update(int tag);
	void _handle_Login_appstore(int tag);
	void _handle_Login_nosupport(int tag);
	void _handleNetWorkDisconnect(int tag);
	void _handleServerMessagePacket(int tag);
	void _handleSelectPurpleCard(int tag);
 	void _handleTowerReset(int tag);
	void _handleGuideStart(int tag);
	void _handleGuideSkip(int tag);
	void _handleServantIdentityChanged(int tag);
	void _handle_Email_remove(int tag);  //删除邮件处理
	void _handle_Sale_Important_object(int tag);
	void _handle_Reset_Team_Progress(int tag);
	void _handle_CostJewel_TeamReward(int tag);
	void _handle_Soul_Altar(int tag);
	void _handle_UseEquip_OneKeyTrain(int tag);
	void _handle_EquipTips_Sell(int tag);
	void _handle_Unlock_EquipAttribute(int tag);
	void _handle_Dwarven_PageInfoChanged(int tag);
	void _handle_GateWay_ConnectFail(int tag);
	void _handle_GoTo_NextMap(int tag);
	void _handle_GetStarReward(int tag);
	void _handle_HasVipGift(int tag);
	void _handle_AutoMessageBox(int tag);
	void _handle_update_finish(int tag);
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

public:
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

	/*
		显示单独按钮的页面
	*/
	void ShowSingleBtnMessage();

private:
	/*
		显示Top面板事件处理
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		更新面板所有控件名称事件处理
	*/
	void   OnUpdateUITextEventHandler(std::list<std::string>& paramList);

private:
	/*
		按钮事件
	*/
	void   On_Click_Event(cocos2d::CCObject* pSender);
};


#endif
