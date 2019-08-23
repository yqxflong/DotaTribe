// Name : WriteEmailWindow.h
// Function:写邮件窗口
// Author : lvyunlong
// Date: 20131021

#ifndef  _DOTATRIBE_WRITEEMAILWINDOW_H_
#define  _DOTATRIBE_WRITEEMAILWINDOW_H_

#include "IWindow.h"
#include "cocos2d.h"
#include <string>
#include "cocos-ext.h"
using namespace cocos2d;
using namespace cocos2d::extension;

class WriteEmailWindow : public IWindow,public cocos2d::extension::CCEditBoxDelegate 
{
private:
	enum{
		udPriorityBG = 0,
		udBG,
		udRECIPIENTS,
		udNAMETEXT,
		udNAMEEDITBOX,
		udSENDCONTENTBOX,
		udCloseBtn,
		udSENDBtn,
		udSENDLB,
		udCONTENTLB,
		udTIPSTTF,
	};

	cocos2d::CCNode* m_pRoot;
	cocos2d::CCNode* m_pWriteRoot;//窗口根节点
private:	
	CCEditBox* pEditBoxInputConTent;	//内容

	CCEditBox* pEditBoxInputName;	//数字

	CCLabelTTF * m_ContentTTF;

	bool m_isBegin;

	bool m_IsKeyBroadShow;
public:
	WriteEmailWindow();
	virtual ~WriteEmailWindow();

private:
	inline void _initLayout();
	inline void _initControl();
	inline void _mapBtn();
	inline void _initEditBox();

public:
	virtual    bool    Init();

	virtual    bool    Load();

	virtual    void    Tick();

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

	void _enableBtnCell(int key,bool enabled,CCNode* cell);

public:
	void On_Click_BtnClick(cocos2d::CCObject* pSender);

public:
	 /**
     * This method is called when an edit box gains focus after keyboard is shown.
     * @param editBox The edit box object that generated the event.
     */
    virtual void editBoxEditingDidBegin(CCEditBox* editBox);
    
    
    /**
     * This method is called when an edit box loses focus after keyboard is hidden.
     * @param editBox The edit box object that generated the event.
     */
    virtual void editBoxEditingDidEnd(CCEditBox* editBox);
    
    /**
     * This method is called when the edit box text was changed.
     * @param editBox The edit box object that generated the event.
     * @param text The new text.
     */
    virtual void editBoxTextChanged(CCEditBox* editBox, const std::string& text);
    
    /**
     * This method is called when the return button was pressed or the outside area of keyboard was touched.
     * @param editBox The edit box object that generated the event.
     */
    virtual void editBoxReturn(CCEditBox* editBox);
};


#endif
