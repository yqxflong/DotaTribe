// Name : WriteEmailWindow.h
// Function:写邮件窗口
// Author : lvyunlong
// Date: 20131021

#include "../include/WriteEmailWindow.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/LoggerSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/UIViewDataManger.h"
#include "../include/CPublicVarReader.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/CMenuItemSprite.h"
#include "../include/EmailDataHandler.h"
#include "../include/NFControlsManager.h"

using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define CONST_WRITEUP	0.0f
#define CONST_EDITBOX_UP	0.0f
#else
#define CONST_WRITEUP	150.0f
#define CONST_EDITBOX_UP	1000.0f
#endif

WriteEmailWindow::WriteEmailWindow()
:m_pRoot(NULL)
{
	m_WindowType = _TYPED_WINDOW_WRITEEMAILWINDOW_;
	m_bModelWindow = true;
	pEditBoxInputConTent = NULL;	//内容

	pEditBoxInputName = NULL;	//数字

	m_ContentTTF = NULL;
	m_IsKeyBroadShow = false;

	m_isBegin = false;

}

WriteEmailWindow::~WriteEmailWindow()
{

}

bool WriteEmailWindow::Init()
{	
	RegisterEvent(_TYPED_EVENT_SHOW_WRITEEMAILWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_WRITEEMAILWINDOW_, true);

	return IWindow::Init();
}

bool WriteEmailWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		_initLayout();

		return true;
	}
	while (false);

	return false;
}

void WriteEmailWindow::Tick()
{
	IWindow::Tick();
}

void WriteEmailWindow::Destroy()
{
	m_pRoot->removeAllChildrenWithCleanup(true);
	m_IsKeyBroadShow = false;
	m_isBegin = false;
	IWindow::Destroy();
}

void WriteEmailWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if(iEventType == _TYPED_EVENT_SHOW_WRITEEMAILWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if(iEventType == _TYPED_EVENT_HIDE_WRITEEMAILWINDOW_)
	{
		Destroy();
	}
}


void WriteEmailWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	
	if (paramList.size() > 0)
	{
		std::list<std::string>::iterator  it = paramList.begin();
		std::string name = *it;
		pEditBoxInputName->setText(name.c_str());
	}
	Show(true);
}

void WriteEmailWindow::_initLayout()
{
	m_pRoot =m_pRootNode;
	m_pRoot->setAnchorPoint(CCPointZero);
	m_pRoot->setPosition(CCPointZero);
	_initControl();
	_initEditBox();
	_mapBtn();
}


void WriteEmailWindow::_initControl()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kEMAILWRITELETTERWINDOW,m_pRoot);
}

void WriteEmailWindow::_mapBtn()
{
	CCMenu* menu=(CCMenu*)m_pRoot->getChildByTag(udCloseBtn);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udCloseBtn);
	cc->setTarget(this,menu_selector(WriteEmailWindow::On_Click_BtnClick));//关闭按钮

	menu=(CCMenu*)m_pRoot->getChildByTag(udSENDBtn);
	cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udSENDBtn);
	cc->setTarget(this,menu_selector(WriteEmailWindow::On_Click_BtnClick));//发送按钮

	_enableBtnCell(udSENDBtn,false,m_pRoot);
}
void WriteEmailWindow::_initEditBox()
{	
	pEditBoxInputName = (CCEditBox*)m_pRoot->getChildByTag(udNAMEEDITBOX);
	pEditBoxInputName->setMaxLength(20);
	pEditBoxInputName->setPlaceHolder(SysLangDataManager::get_instance2()->GetSysLangById(6017).c_str());

	pEditBoxInputName->setInputMode(kEditBoxInputModeAny);
	pEditBoxInputName->setReturnType(kKeyboardReturnTypeDone);
	pEditBoxInputName->setDelegate(this);
	pEditBoxInputName->setText("");


	pEditBoxInputConTent = (CCEditBox*)m_pRoot->getChildByTag(udSENDCONTENTBOX);
	pEditBoxInputConTent->setMaxLength(100);
	pEditBoxInputConTent->setInputMode(kEditBoxInputModeAny);
	pEditBoxInputConTent->setReturnType(kKeyboardReturnTypeDone);
	pEditBoxInputConTent->setDelegate(this);
	pEditBoxInputConTent->setText("");
	
	m_ContentTTF = (CCLabelTTF*)m_pRoot->getChildByTag(udCONTENTLB);
	m_ContentTTF->setString("");
	
}


void WriteEmailWindow::On_Click_BtnClick(cocos2d::CCObject* pSender)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
	if (m_IsKeyBroadShow)
		return;
#endif
	
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int idx  = cc->getIDX();

	if (idx == udCloseBtn)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_WRITEEMAILWINDOW_);
	}
	else if (idx == udSENDBtn)
	{
		EmailWriteData* data = new EmailWriteData();
		data->id_ = -1;
		data->targetName_ = pEditBoxInputName->getText();

		std::string str = ROLEINFODATAHANDLER->m_pRIData->name_.c_str();
		str += SysLangDataManager::get_instance2()->GetSysLangById(634).c_str();
		data->title_ = str.c_str();
		data->content_ = m_ContentTTF->getString();
		data->attachmentCount_ = 0;
		EMAILDATAHANDLER->WriteEmail(data);
		delete data;

		//PushEvent(_TYPED_EVENT_HIDE_WRITEEMAILWINDOW_);
	}
}

void WriteEmailWindow::editBoxEditingDidBegin(CCEditBox* editBox)
{
	NFC_setNodeVisable(udTIPSTTF,m_pRoot,false);
	m_IsKeyBroadShow = true;
	if (editBox == pEditBoxInputConTent)
	{
		editBox->setText(m_ContentTTF->getString());
		editBoxTextChanged(pEditBoxInputConTent,m_ContentTTF->getString());
		m_ContentTTF->setString(editBox->getText());
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
		pEditBoxInputConTent->setPositionY(pEditBoxInputConTent->getPositionY()+CONST_EDITBOX_UP);
#endif
		m_pRoot->setPositionY(m_pRoot->getPositionY()+CONST_WRITEUP);
	}
}

void WriteEmailWindow::editBoxEditingDidEnd(CCEditBox* editBox)
{

}

void WriteEmailWindow::editBoxTextChanged(CCEditBox* editBox, const std::string& text)
{
	if (pEditBoxInputConTent == editBox)
	{
		if (m_isBegin)
		{
			m_isBegin = false;
			return;
		}

		m_ContentTTF->setString(editBox->getText());
	}
	
}

void WriteEmailWindow::editBoxReturn(CCEditBox* editBox)
{
	m_IsKeyBroadShow = false;
	if (pEditBoxInputConTent == editBox)
	{
		m_isBegin = true;
		m_ContentTTF->setString(editBox->getText());
		pEditBoxInputConTent->setText("");
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
		pEditBoxInputConTent->setPositionY(editBox->getPositionY() - CONST_EDITBOX_UP);
#endif
		m_pRoot->setPositionY(m_pRoot->getPositionY()-CONST_WRITEUP);
	}

	std::string str1 =  m_ContentTTF->getString();
	if (str1 == "")
	{
		NFC_setNodeVisable(udTIPSTTF,m_pRoot,true);
	}
	else
	{
		NFC_setNodeVisable(udTIPSTTF,m_pRoot,false);
	}
	std::string str2 = pEditBoxInputName->getText();
	if (str1 != "" && str2 != "")
	{
		_enableBtnCell(udSENDBtn,true,m_pRoot);
	}
	else
	{
		_enableBtnCell(udSENDBtn,false,m_pRoot);
	}
}

void WriteEmailWindow::_enableBtnCell(int key,bool enabled,CCNode* cell){
	CCMenu* menu=(CCMenu*)cell->getChildByTag(key);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setEnabled(enabled);
}
