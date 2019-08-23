#include "../include/InputNumWindow.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/VariableSystem.h"
#include "../include/VariableSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/LocalPlayerDataManager.h"
#include "../include/InputCommand.h"
//
#include "../include/CPublicVarReader.h"
#include "../include/UIViewDataManger.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/CMenuItemSprite.h"
#include <string>
#include <cocos2d.h>
#include <cocos-ext.h>

using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

InputNumWindow::InputNumWindow():
m_pRoot(NULL)
,m_bIfAreadySetted(false)
{
	m_WindowType = _TYPED_WINDOW_INPUTNUMWINDOW_;
	m_bModelWindow = true;
	m_minNum = 1;
}

InputNumWindow::~InputNumWindow()
{

}

bool    InputNumWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_INPUTNUMWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_INPUTNUMWINDOW_, true);
	
	return IWindow::Init();
}

bool    InputNumWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;

		_initLayout();//绘制界面

		return true;
	} 
	while (false);

	return false;
}

void    InputNumWindow::Tick()
{
	IWindow::Tick();
}

void    InputNumWindow::Destroy()
{
	IWindow::Destroy();
}

void    InputNumWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_INPUTNUMWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_INPUTNUMWINDOW_)
	{
		Destroy();
	}
}

void   InputNumWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
	if (paramList.size()>=2)
	{
		std::list<std::string>::iterator it=paramList.begin();
		m_windowTitle=*it;
		std::string max = *(++it);
		sscanf(max.c_str(), "%d", &m_maxNum);
	}
	setTitle(m_windowTitle.c_str());
}

void InputNumWindow::_initLayout()
{
	m_pRoot=m_pRootNode;
	m_pRoot->setAnchorPoint(CCPointZero);//CCEditBox需要使用到
	m_pRoot->setPosition(CCPointZero);


	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kINPUTNUMWINDOW, m_pRoot);

	_mapBtn();//标定所有按钮

	_mapEditBox();//标定editbox
}

void InputNumWindow::_mapBtn()
{
	CCMenu * menu = NULL;
	CMenuItemSprite * item = NULL;

	for(int i = udBTNCLOSE; i <= udBTNMAX; ++i)
	{
		menu = (CCMenu *)m_pRoot->getChildByTag(i);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTarget(this, menu_selector(InputNumWindow::On_Btn_Click));
		item->setTag(i);
	}
}

void InputNumWindow::_mapEditBox()
{
	m_pEditBox = (CCEditBox *)m_pRoot->getChildByTag(udEDITBOX); 
	m_pEditBox->setMaxLength(6);
	m_pEditBox->setInputMode(kEditBoxInputModePhoneNumber);
	m_pEditBox->setReturnType(kKeyboardReturnTypeDone);
	m_pEditBox->setDelegate(this);
	m_pEditBox->setText("1");
	m_pEditBox->setTouchPriority(kPRIORITYMID - 1);
}

void InputNumWindow::setTitle(const char* title){
	cocos2d::CCLabelTTF* cc=(cocos2d::CCLabelTTF*)m_pRoot->getChildByTag(udTITLE);
	cc->setString(title);
}

void InputNumWindow::deleteNum()//减少按钮
{
	int num = 0;
	const char * str = m_pEditBox->getText();
	sscanf(str, "%d", &num);
	if(num > m_minNum)
	{
		num -= 1;
		char tmp[128] = "";
		sprintf(tmp, "%d", num);
		m_pEditBox->setText(tmp);
	}
}

void InputNumWindow::addNum()//增加按钮
{
	int num = 0;
	const char * str = m_pEditBox->getText();
	sscanf(str, "%d", &num);
	if(num < m_maxNum)
	{
		num += 1;
		char tmp[128] = "";
		sprintf(tmp, "%d", num);
		m_pEditBox->setText(tmp);
	}

}

void InputNumWindow::setMaxNum()
{
	char tmp[128] = "";
	sprintf(tmp, "%d", m_maxNum);
	m_pEditBox->setText(tmp);

}

void   InputNumWindow::On_Btn_Click(cocos2d::CCObject* pSender)
{
	CCMenuItem * item = (CCMenuItem *)pSender;
	int tag = item->getTag();
	if(tag == udBTNCLOSE)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_INPUTNUMWINDOW_);
	}
	else if(tag == udBTNOK)
	{
		int num = 0;
		const char * str = m_pEditBox->getText();
		sscanf(str, "%d", &num);
		if(num > m_maxNum)
		{
			num = m_maxNum;
		}

		if(num > 0)
		{
			//将数据push进去
			std::string inputNum = "";
			char tmp[128] = "";
			sprintf(tmp, "%d", num);
			inputNum.assign(tmp);
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_INPUTNUMWINDOW_, inputNum);
		}
		else
		{
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_INPUTNUMWINDOW_);
		}
		

	}
	else if(tag == udBTNDELETE)
	{
		deleteNum();
	}
	else if(tag == udBTNADD)
	{
		addNum();
	}
	else if(tag == udBTNMAX)
	{
		setMaxNum();
	}
}

void InputNumWindow::keyboardWillShow(cocos2d::CCIMEKeyboardNotificationInfo& info) 
{ 
	//m_pRoot->setPositionY(300); 
	//m_pEditBox->setPositionY(pRootNode->getPositionY()+140);   

} 
void InputNumWindow::keyboardDidShow(cocos2d::CCIMEKeyboardNotificationInfo& info) 
{ 

} 
void InputNumWindow::keyboardWillHide(cocos2d::CCIMEKeyboardNotificationInfo& info) 
{ 

} 
void InputNumWindow::keyboardDidHide(cocos2d::CCIMEKeyboardNotificationInfo& info) 
{

}

void InputNumWindow::editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox)
{

}
void InputNumWindow::editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox)
{

}
void InputNumWindow::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text)
{
// 	if(m_bIfAreadySetted)
// 	{
// 		m_bIfAreadySetted = false;
// 		return;
// 	}
// 	int num = 0;
// 	sscanf(text.c_str(), "%d", &num);
// 	m_bIfAreadySetted = true;
// 	editBox->setText(_to_event_param_(num).c_str());

}
void InputNumWindow::editBoxReturn(cocos2d::extension::CCEditBox* editBox)
{
	string str = editBox->getText();
	int num = 0;
	sscanf(str.c_str(), "%d", &num);
	if(num > m_maxNum)
	{
		num = m_maxNum;
		editBox->setText(_to_event_param_(num).c_str());
	}
	if(num < m_minNum)
	{
		num = m_minNum;
		editBox->setText(_to_event_param_(num).c_str());
	}

}