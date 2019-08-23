//Name : InputNumWindow
//Function : 复数输入框
//Author : fangjun
//Date : 201308

#ifndef  _DOTATRIBE_INPUTNUMWINDOW_H_
#define  _DOTATRIBE_INPUTNUMWINDOW_H_


#include "IWindow.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include <string>

class InputNumWindow : public IWindow, cocos2d::extension::CCEditBoxDelegate
{
private:
	enum{
		udGRAYLAYER = 0,
		udBG,
		udTITLEBG,
		udBTNOKTXTBG,
		udBTNMAXTXTBG,
		udBTNCLOSE,
		udBTNOK,
		udBTNDELETE,
		udBTNADD,
		udBTNMAX,
		udTITLE,
		udEDITBOX,
	};
	cocos2d::CCNode* m_pRoot;
	std::string m_windowTitle;//标题
	//int m_functionType;
	int m_maxNum;//最大数量
	int m_minNum;//最小数量

	//cocos2d::CCLabelTTF * m_pEditBoxMask;//输入框，window面具
	cocos2d::extension::CCEditBox * m_pEditBox;	//输入框

	bool m_bIfAreadySetted;//是否已设置过

public:
	InputNumWindow();
	virtual ~InputNumWindow();
private:
	inline void _initLayout();

	inline void _mapBtn();
	inline void _mapEditBox();
public:
	void setTitle(const char* title);
	void deleteNum();//左边减少按钮
	void addNum();//右边增加按钮
	void setMaxNum();//设为最大数量
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
		show事件处理
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);


	/*
		EditBox
	*/
	virtual void keyboardWillShow(cocos2d::CCIMEKeyboardNotificationInfo& info); 
	virtual void keyboardDidShow(cocos2d::CCIMEKeyboardNotificationInfo& info); 
	virtual void keyboardWillHide(cocos2d::CCIMEKeyboardNotificationInfo& info); 
	virtual void keyboardDidHide(cocos2d::CCIMEKeyboardNotificationInfo& info);

	virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);

private:

	void   On_Btn_Click(cocos2d::CCObject* pSender);

};


#endif
