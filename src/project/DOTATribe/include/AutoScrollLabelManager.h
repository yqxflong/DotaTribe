#ifndef   _DOTATRIBE_AUTOSCROLLLABEL_H_
#define   _DOTATRIBE_AUTOSCROLLLABEL_H_
#include  <cocos2d.h> 
#include "../include/CallFuncAction.h"

////////////////////////////////////////////////////////////////
//Name:	 AutoScrollLabelManager
//Auchor: 	xiaobo.wu
//Func:	 自动滚动公告管理器
//Maintainer: 	xiaobo.wu
//date:   2013/11/18
////////////////////////////////////////////////////////////////
  
class  CCRectClipNode;
class  AnnouncementData;

class  AutoScrollLabelManager: public CallFunctionProtocol
{ 
public: 
	/*
	内部事件通知类型
	*/
	enum
	{
		_AUTOSCROLL_UNKONW_EVENT_TYPE_,					//未知动画类型
		_AUTOSCROLL_SCROLL_DID_EVENT_TYPE_,				//单局定时器结束通知
		_AUTOSCROLL_INNNAL_TIME_DID_EVENT_TYPE_,
	};
	/*
	默认构建函数
	*/
	AutoScrollLabelManager();
	/*
	析构函数
	*/
	virtual ~AutoScrollLabelManager();
	/*
	静态创建接口
	*/
	static AutoScrollLabelManager * CreateAutoScrollLabelManager(cocos2d::CCNode * parentNode,int noticeStyleID,std::string noticeContent);				
	/*
	结束滚动标签管理器
	*/
	virtual void  EndScrollManager();

	/*
	销毁管理器
	*/
	virtual void  Destroy();

	/*
	管理器事件通知接口
	*/
	virtual void  CallFunctionHandler(int eventType,void * attachParam);

	/*
	设置管理 是否有效
	*/
	void SetValid(bool isValid);
	/*
	获取管理器是否合法
	*/
	bool GetValid();
	 
	cocos2d::CCPoint  GetBackGroundImagePos();

protected:
	/*
	内部管理器初始化
	*/
	bool InitAutoScrollLabelManager(cocos2d::CCNode * parentNode,int noticeStyeID,std::string noticeContent);
	/*
	开启单轮滚动单元
	*/
	void StartSingleDelayUnit();	 
	/*
	清理上一个滚动标签
	*/
	void ClearPreScrollLabel();
	/*
	创建自动裁剪根结点
	*/
	void InitAutoRectClipNode();
	/*
	销毁自动裁剪根结点
	*/
	void DestroyAutoRectClipNode();
protected: 
	int			 m_nNoticeStyleID;						//管理CSS Type ID
	std::string  m_snoticeContent;						//
	std::vector<cocos2d::CCSingleLineLabelTTF *>       m_vScrollLabelVec;
	AnnouncementData * m_pAnnnouncementData;		
	float        m_screenMidHight;
	float        m_screenMidWidth;
	float		 m_fNoticeStringWidth;
	float		 m_fTotalScrollLengh;
	float        m_fSingleDurationTime;
	cocos2d::CCPoint  m_TargetPosition;
	int			 m_nLabelIndex;
	short        m_nRepeatCount;
	cocos2d::CCNode * m_pParentNode;
	CCRectClipNode  * m_pRectClipRootNode;
protected:
	bool  m_bIsValid; 
};



#endif