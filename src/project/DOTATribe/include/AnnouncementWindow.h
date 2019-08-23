#ifndef  _DOTATRIBE_ANNNOUNCEMENTWINDOW_H_
#define  _DOTATRIBE_ANNNOUNCEMENTWINDOW_H_
  
#include "IWindow.h"
#include "../include/AnnouncementDataHandler.h"
#include <queue>

class   AutoScrollLabelManager;

class AnnouncementWindow : public IWindow
{
protected:
	int m_SubType;   // 附加子类型
public:
	AnnouncementWindow();
	virtual ~AnnouncementWindow();
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
	   显示窗口
	*/
	void    OnShowWindowEventHandler(std::list<std::string>& paramList);

	/*
	获取公共系统的根节点
	*/
	cocos2d::CCNode *   GetAnnouncementRootNode();

	/*
	激活回调
	*/
	void    OnActiveCallHandler();

	/*
	生成背景
	*/
	void    OnBackGroundInit();

	/*
	销毁背景
	*/
	void   OnBackGroundDestroy();
 
protected:
	bool   IsInAthleticsProcedure();
private:
	std::vector<AutoScrollLabelManager * >  m_vAutoScrollManagerList;

	std::queue<AnnoucementMemData>          m_dAnnouceCacheMemDataQueue;		  //公共信息队列

	cocos2d::CCSprite *						m_pBackGroundImage;					  //背景图片							

	bool  m_bIsDurationWaitting;												  //是否持续等待状态

	float m_fAnnouceWaittingDuration;											  //间隔时间 

	int   m_nAnnoucementBGID;													  //背景图标ID


};


#endif

 