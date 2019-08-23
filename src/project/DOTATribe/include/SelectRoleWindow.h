//Name：SelectRoleWindow
//Function：选角色
//Author:周少男

#ifndef  _DOTATRIBE_SELECTROLEWINDOW_H_
#define  _DOTATRIBE_SELECTROLEWINDOW_H_

#include "IWindow.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include <string>
#include <list>

using namespace cocos2d;
using namespace cocos2d::extension;

class CreateRoleData;
class SelectRoleWindow : public IWindow,public cocos2d::extension::CCEditBoxDelegate
{
public:
	SelectRoleWindow();
	virtual ~SelectRoleWindow();

	enum{
		udSKENODE,//骨骼动画结点
		udBG,//背景图
		udTXTBG,//介绍文字背景
		udNAMEBG,//人物名字背景
		udSERVERBG,//服务器背景
		udENTERBTN,//进入游戏按钮
		udSELECTNAMEBTN,//选名字按钮
		udSERVERNAME,//服务器名
		udNAME,//名字
		udTEXT,//介绍
		udEFFECT1,		//特效1
		udEFFECT2,		//特效2
		udEFFECT3,		//特效3
		udROLELEFT,		//人左
		udROLECENTER,	//人中
		udROLERIGHT,	//人右
		udEditBOX,		//输入框
		};
	std::map<int, CCSkeletonAnimation*> m_SelectPlayerMapList;
	int m_PlayerIndex;
	int m_PlayerCount;
	int m_LeftPlayerIndex;
	int m_MidPlayerIndex;
	int m_RightPlayerIndex;
	bool IsInSelectPlayer;
	bool IsFirstInSelectPlayer;
	bool IsMoving;
	bool IsBeginLeave;
	bool IsBeginEnter;
	CCLabelTTF* pRoleDesc;
	cocos2d::CCPoint  touchBeginPos;
	cocos2d::CCPoint  touchEndPos;
	CCSkeletonAnimation* m_LeftPlayerSkeleton;
	CCSkeletonAnimation* m_RightPlayerSkeleton;
	CCSkeletonAnimation* m_MidPlayerSkeleton;
	CreateRoleData* pLeftData;
	CreateRoleData* pMidData;
	CreateRoleData* pRightData;
	CCEditBox* pEditBox;
	CCNode* pRootNode;
	bool m_IsKeyBoard;
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

private:
	/*
		显示大厅面板事件处理
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		更新大厅面板事件处理
	*/
	void   OnUpdateWindowEventHandler(std::list<std::string>& paramList);
		/*
		左滑动事件处理
	*/
	void   OnTurnLeftEventHandler();
	/*
		右滑动事件处理
	*/
	void   OnTurnRightEventHandler(); 

private:
	void   InitControl();
	void   InitRegister();
	inline void   _mapBtn();

	void CheckLeaveAnimation();
	void CheckEnterAnimation();

	void InitRolePosition();
	CCSkeletonAnimation * FindSkeletonByIndex(int index);
	void OnUpdateSelectPlayer();
	void OnPlayLeaveAnimation();
	void OnPlayEnterAnimation();
	void OnUpdatePlayerName(std::string name);

	std::string GetAnimationNameById(int shapeID,int skillID);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);   

/*
	virtual void keyboardWillShow(cocos2d::CCIMEKeyboardNotificationInfo& info); 
	virtual void keyboardDidShow(cocos2d::CCIMEKeyboardNotificationInfo& info); 
	virtual void keyboardWillHide(cocos2d::CCIMEKeyboardNotificationInfo& info); 
	virtual void keyboardDidHide(cocos2d::CCIMEKeyboardNotificationInfo& info);*/

	virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);
public:
	void On_Click_BtnClick(cocos2d::CCObject* pSender);
};

#endif
