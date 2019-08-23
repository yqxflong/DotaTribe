//Name：StartWindow
//Function：开始窗口
//Written By：尹强

#ifndef  _DOTATRIBE_StartWindow_H_
#define  _DOTATRIBE_StartWindow_H_

#include "IWindow.h"

class StartWindow : public IWindow
{
private:
	enum{
		udBG,
		udPROGRESS,
		udPROGRESS_BG,
		udPERCENTLABEL,
		udSERVERBTN,		//选服按钮
		udENTERBTN,			//进入游戏
		udSERVER_NAME,		//服务器名字
		udSERVER_STATUS,	//服务器状态
		udSERVER_HINT,		//点击选取
		udENTERLABEL,
		udFILECOUNT,
		udLOGOICON,
		udVERSION,

	};
	cocos2d::CCNode* m_pRoot;
	bool isNoticeShowed;
public:
	StartWindow();
	virtual ~StartWindow();
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
private:
	inline void _initLayout();
	inline void _mapBtn();
	inline void _setDefaultServer();
	inline void _setVerson();
	inline void _setFileCount(int filecount,int totalcount);
	inline void _showDownloadControls(bool isshow);
	inline void _showNormalControls(bool isshow);
	//
protected:
	void On_Click_Event(cocos2d::CCObject* pSender);
public:
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);
	//
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	void   On_UI_Show_Download(std::list<std::string>& paramList);
	void   On_UI_Show_Normal(std::list<std::string>& paramList);
	void   On_UI_Update_ByLogin(std::list<std::string>& paramList);
};

#endif
