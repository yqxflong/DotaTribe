//Name : InputNumWindow
//Function : ���������
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
	std::string m_windowTitle;//����
	//int m_functionType;
	int m_maxNum;//�������
	int m_minNum;//��С����

	//cocos2d::CCLabelTTF * m_pEditBoxMask;//�����window���
	cocos2d::extension::CCEditBox * m_pEditBox;	//�����

	bool m_bIfAreadySetted;//�Ƿ������ù�

public:
	InputNumWindow();
	virtual ~InputNumWindow();
private:
	inline void _initLayout();

	inline void _mapBtn();
	inline void _mapEditBox();
public:
	void setTitle(const char* title);
	void deleteNum();//��߼��ٰ�ť
	void addNum();//�ұ����Ӱ�ť
	void setMaxNum();//��Ϊ�������
public:
	/*
		��ʼ������
	*/
	virtual    bool    Init();
	/*
		���ش���
	*/
	virtual    bool    Load();
	/*
		����´���
	*/
	virtual    void    Tick();
	/*
		���ٴ���
	*/ 
	virtual    void    Destroy();

public:
	/*
		��Ϣ�¼���Ӧ����
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

private:
	/*
		show�¼�����
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
