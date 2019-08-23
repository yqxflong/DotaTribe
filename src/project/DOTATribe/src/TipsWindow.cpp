////////////////////////////////////////////////////////////////
//Name:	 TipsWindow
//Auchor: 	xiaobo.wu
//Func:	 服务器应答协议窗口
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////
#include "../include/TipsWindow.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/VariableSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/LocalPlayerDataManager.h"
#include "../include/CMenuItemSprite.h"
#include "../include/CPublicVarReader.h"
#include "../include/TimeSystem.h"
#include "../include/QADataHandler.h"
#include "../include/C2SQAReceiptPacket.h"
#include "../include/NFControlsManager.h"
 

#include <cocos2d.h>
#include "cocos-ext.h"

#include <string>
using  namespace  cocos2d;
using namespace cocos2d::extension;

TipsWindow::TipsWindow()
{
	m_WindowType   = _TYPEF_WINDOW_TIPSWINDOW_;
	m_bModelWindow = false;
	m_SubType      = 0;
	m_pRootLayer=NULL;
}

TipsWindow::~TipsWindow()
{

}

bool    TipsWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_TIPSWINDOW_);
	RegisterEvent(_TYPED_EVNET_HIDE_TIPSWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_TIPSWINDOW_, true);
	return IWindow::Init();
}

 bool   TipsWindow::Load()
 {
	 do 
	 {
		 if (!IWindow::Load())
			 break; 
		  InitLayout();
	 } 
	 while (false);

	 return false;
 }


void    TipsWindow::Tick()
{
	IWindow::Tick();
	 
}

void    TipsWindow::Destroy()
{ 
	cocos2d::CCLayer * pLayerMark=GetRootMarkLayer();
	if(pLayerMark!=NULL)
	{
		pLayerMark->removeAllChildrenWithCleanup(true);
	}
	QADataHandler::get_instance2()->DestroyMemData();
	UIVIEWDATAMANAGER->clearData();
	IWindow::Destroy();
}



void   TipsWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	NFC_showCommunicationWating(false);
	Show(true);
}


void    TipsWindow::LoadUIControl()
{ 
	cocos2d::CCLayer *  rootLayer=GetRootMarkLayer();
	if(rootLayer!=NULL)
	{
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kTIPSWINDOW,rootLayer);
	}  

}


void  TipsWindow::MapBtnWithTag(int tag)
{ 
	cocos2d::CCLayer *  rootLayer=GetRootMarkLayer();
	CCMenu * pMenu=(CCMenu *)rootLayer->getChildByTag(tag);
	if(pMenu!=NULL)
	{
		CMenuItemSprite * pMenuItem=(CMenuItemSprite * )pMenu->getChildByTag(0);
		if(pMenuItem!=NULL)
		{
			pMenuItem->setIDX(tag);
			pMenuItem->setTarget(this,menu_selector(TipsWindow::MenuCallBackHandler));
		}
	} 
}


void    TipsWindow::InitLayout()
{
	m_pRootLayer=CCLayer::create();
	m_pRootLayer->setAnchorPoint(ccp(0.5,0.5));
	m_pRootLayer->setPosition(CCPointZero);
	m_pRootNode->addChild(m_pRootLayer);
	LoadUIControl();
	InitMapBtn();
	UpdateUIWithData();
}


void   TipsWindow::UpdateUIWithData()
{
	if(QADataHandler::get_instance2()!=NULL)
	{
		PQAData pQAData=QADataHandler::get_instance2()->pQAdata;
		if(pQAData!=NULL)
		{
		   cocos2d::CCLayer *  rootLayer=GetRootMarkLayer();
		   if(rootLayer!=NULL)
		   { 
			   //更新UI数据
			   CCMultiLineLabelTTF * pPromptLabel=(CCMultiLineLabelTTF *)rootLayer->getChildByTag(_TIPSUI_TEXT_TAG_);
			   if(pPromptLabel!=NULL)
			   {
				   pPromptLabel->setString(pQAData->prompt.c_str());
			   }
			   ShowBtnWithType(pQAData->qaBtnNumber);
		   } 
		}
	} 

}

void   TipsWindow::ShowBtnWithType(char btnType)
{	cocos2d::CCLayer *  rootLayer=GetRootMarkLayer();
	switch(btnType)
	{
	case QAData::QADATA_SINGLE_TYPE_:
		{
			HideCCNodeWithTag(_TIPSUI_TYPE1_SURE_BTN_TAG_);
			HideCCNodeWithTag(_TIPSUI_TYPE1_SURE_IMAGE_TAG_);
			HideCCNodeWithTag(_TIPSUI_TYPE1_CANCEL_BTN_TAG_);
			HideCCNodeWithTag(_TIPSUI_TYPE1_CANCEL_IMAGE_TAG_);
			ShowCCNodeWithTag(_TIPSUI_TYPE2_SURE_BTN_TAG_);
			ShowCCNodeWithTag(_TIPSUI_TYPE2_SURE_IMAGE_TAG_);
			MapBtnWithTag(_TIPSUI_TYPE2_SURE_BTN_TAG_);
		}
		break;

	case QAData::QADATA_DOUBLE_TYPE_:
		{
			HideCCNodeWithTag(_TIPSUI_TYPE2_SURE_BTN_TAG_);
			HideCCNodeWithTag(_TIPSUI_TYPE2_SURE_IMAGE_TAG_);
			ShowCCNodeWithTag(_TIPSUI_TYPE1_SURE_BTN_TAG_);
			ShowCCNodeWithTag(_TIPSUI_TYPE1_SURE_IMAGE_TAG_);
			ShowCCNodeWithTag(_TIPSUI_TYPE1_CANCEL_BTN_TAG_);
			ShowCCNodeWithTag(_TIPSUI_TYPE1_CANCEL_IMAGE_TAG_);
			MapBtnWithTag(_TIPSUI_TYPE1_SURE_BTN_TAG_);
			MapBtnWithTag(_TIPSUI_TYPE1_CANCEL_BTN_TAG_);
		}
		break;
	default:
		{
			HideCCNodeWithTag(_TIPSUI_TYPE2_SURE_BTN_TAG_);
			HideCCNodeWithTag(_TIPSUI_TYPE2_SURE_IMAGE_TAG_);
			ShowCCNodeWithTag(_TIPSUI_TYPE1_SURE_BTN_TAG_);
			ShowCCNodeWithTag(_TIPSUI_TYPE1_SURE_IMAGE_TAG_);
			ShowCCNodeWithTag(_TIPSUI_TYPE1_CANCEL_BTN_TAG_);
			ShowCCNodeWithTag(_TIPSUI_TYPE1_CANCEL_IMAGE_TAG_);
			MapBtnWithTag(_TIPSUI_TYPE1_SURE_BTN_TAG_);
			MapBtnWithTag(_TIPSUI_TYPE1_CANCEL_BTN_TAG_);
		}
		break; 
	}
}


void  TipsWindow::HideCCNodeWithTag(int btnTag)
{
	cocos2d::CCLayer *  rootLayer=GetRootMarkLayer();
	if(rootLayer!=NULL)
	{
		cocos2d::CCNode * pCCNode=rootLayer->getChildByTag(btnTag);
		if(pCCNode!=NULL)
		{
			pCCNode->setVisible(false);
		}
	}
}
void TipsWindow::ShowCCNodeWithTag(int tag)
{
	cocos2d::CCLayer *  rootLayer=GetRootMarkLayer();
	if(rootLayer!=NULL)
	{
		cocos2d::CCNode * pCCNode=rootLayer->getChildByTag(tag);
		if(pCCNode!=NULL)
		{
			pCCNode->setVisible(true);
		}
	}
}

 
void   TipsWindow::InitMapBtn()
{
	cocos2d::CCLayer *  rootLayer=GetRootMarkLayer();

// 	CCMenu * pCloseBtn=(CCMenu *)rootLayer->getChildByTag(_TIPSUI_CLOSE_BTN_TAG_);
// 	if(pCloseBtn!=NULL)
// 	{
// 		CMenuItemSprite * pCloseItem=(CMenuItemSprite * )pCloseBtn->getChildByTag(0);
// 		if(pCloseItem!=NULL)
// 		{
// 			pCloseItem->setIDX(_TIPSUI_CLOSE_BTN_TAG_);
// 			pCloseItem->setTarget(this,menu_selector(TipsWindow::MenuCallBackHandler));
// 		}
// 	} 
}

void   TipsWindow::MenuCallBackHandler(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * pMenuItem=(CMenuItemSprite *)pSender;
	if(pMenuItem!=NULL)
	{
		switch(pMenuItem->getIDX())
		{
// 		 case  _TIPSUI_CLOSE_BTN_TAG_:
// 			{
// 				PushEvent(_TYPED_EVNET_HIDE_TIPSWINDOW_);
// 				break;
// 			}
		 case  _TIPSUI_TYPE1_SURE_BTN_TAG_:
			 {  
				 C2SQAReceiptPacket  qaReceiptPacket(C2SQAReceiptPacket::_QA_Receipt_Sure_Type_);
				 qaReceiptPacket.Send();
				 PushEvent(_TYPED_EVNET_HIDE_TIPSWINDOW_);
				 NFC_showCommunicationWating(true);
				 break;
			}
		 case  _TIPSUI_TYPE1_CANCEL_BTN_TAG_:
			 {	
				 C2SQAReceiptPacket  qaReceiptPacket(C2SQAReceiptPacket::_QA_Receipt_Cancel_Type_);
			 	 qaReceiptPacket.Send();
				 PushEvent(_TYPED_EVNET_HIDE_TIPSWINDOW_);
				 break;
			 }
		 case _TIPSUI_TYPE2_SURE_BTN_TAG_:
			 {
				 C2SQAReceiptPacket  qaReceiptPacket(C2SQAReceiptPacket::_QA_Receipt_Sure_Type_);
				 qaReceiptPacket.Send();
				 PushEvent(_TYPED_EVNET_HIDE_TIPSWINDOW_);
				 NFC_showCommunicationWating(true);
				 break;
			 }
		 default: 
			 break;
		}
	}
}

 
void   TipsWindow::OnUpdateUITextEventHandler(std::list<std::string>& paramList)
{
	UpdateUIWithData();
}


void   TipsWindow:: OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_TIPSWINDOW_ )
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVNET_HIDE_TIPSWINDOW_ )
	{
		Destroy();
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_TIPSWINDOW_ )
	{
		OnUpdateUITextEventHandler(paramList);
	}
}

cocos2d::CCLayer  *  TipsWindow::GetRootMarkLayer()
{
	return m_pRootLayer;
}
