//Name : ShopinputNumWindow
//Function : 商店批次购买窗口输入框
//Author : lvyunlong
//Date : 201309

#include <cocos2d.h>
#include <cocos-ext.h>
#include "../include/ShopinputNumWindow.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/BagOtherObjectHandler.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/CPublicVarReader.h"
#include "../include/UIViewDataManger.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/CMenuItemSprite.h"
#include "../include/ShopInfoDataHandler.h"
#include "../include/NFControlsManager.h"
#include "../include/CSprite.h"
#include <string>
#include "../include/ServerInfoDataHandler.h"


using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

ShopinputNumWindow::ShopinputNumWindow():
m_pRoot(NULL)
,m_Curshopdata(0)
,m_moneytype(0)
,m_oneprice(0)
,m_IsKeyBroadShow(0)
,m_bIfAreadySetted(false)
,m_iTypeShop(0)
{
	m_WindowType = _TYPED_WINDOW_SHOPINPUTBUYWINDOW_;
	m_bModelWindow = true;
}

ShopinputNumWindow::~ShopinputNumWindow()
{

}

bool    ShopinputNumWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_SHOPINPUTNUMWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_SHOPINPUTNUMWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_SHOPINPUTNUMWINDOW_, true);
	return IWindow::Init();
}

bool    ShopinputNumWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;

		_initRegister();

		return true;
	} 
	while (false);

	return false;
}

void    ShopinputNumWindow::Tick()
{
	IWindow::Tick();
}

void    ShopinputNumWindow::Destroy()
{
	m_iTypeShop = 0;
	if (m_Curshopdata)
	{
		CC_SAFE_DELETE(m_Curshopdata);
	}
	m_pRoot->removeAllChildrenWithCleanup(true);
	IWindow::Destroy();
}

void    ShopinputNumWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_SHOPINPUTNUMWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_SHOPINPUTNUMWINDOW_)
	{
		Destroy();
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_SHOPINPUTNUMWINDOW_)
	{
		OnUpdateWindowEventHandler(paramList);
	}
}

void ShopinputNumWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
	if(m_Curshopdata==NULL)
	{
		m_Curshopdata = new ShopInfoGoodsData;
	}
	if (paramList.size()>0)
	{
		std::list<std::string>::iterator it=paramList.begin();
		int indexid;
		sscanf((*it).c_str(), "%d", &indexid);
		if (paramList.size()>1)
		{
			m_iTypeShop = 1;
			RandomGoodsData* temp = RANDOMSHOPDATAHANDLER->m_RandomInfoList[indexid];
			if (temp != NULL)
			{
				m_Curshopdata->nameBase = temp->strname;
				m_Curshopdata->extemplateId = temp->templateId;
				m_Curshopdata->multiPurchase = temp->limit;
				m_Curshopdata->limit = temp->limit;
				m_Curshopdata->shopItemId = temp->goodsindex;
				m_Curshopdata->price = temp->price;
				m_Curshopdata->moneyType = temp->moneytype;
				m_Curshopdata->discount = -1;
			}
			setCurMoneyTypeandPrice(m_Curshopdata);
			int countmax = GetBuyAbiliMax();
			char numbuff[64]={0};
			sprintf(numbuff,"%d",countmax);
			pEditBoxInputNum->setText(numbuff);

		}
		else
		{
			m_iTypeShop = 0;
			ShopInfoGoodsData *temp =  SHOPINFODATAHANDLER->m_ShopGoodsBaselist[indexid];
			if (temp != NULL)
			{
				//m_Curshopdata = temp;
				m_Curshopdata->nameBase = temp->nameBase;
				m_Curshopdata->extemplateId = temp->extemplateId;
				m_Curshopdata->multiPurchase = temp->multiPurchase;
				m_Curshopdata->limit = temp->limit;
				m_Curshopdata->shopItemId = temp->shopItemId;
				m_Curshopdata->price = temp->price;
				m_Curshopdata->moneyType = temp->moneyType;
				m_Curshopdata->discount = temp->discount;
				m_Curshopdata->distextemplateId = temp->distextemplateId;
				m_Curshopdata->extemplateId = temp->extemplateId;
				m_Curshopdata->discountMoneyType = temp->discountMoneyType;
			}
			setCurMoneyTypeandPrice(m_Curshopdata);
			char numbuff[64]={0};
			sprintf(numbuff,"%d",1);
			pEditBoxInputNum->setText(numbuff);
			
		}
	}
	NFC_setLabelString(udItemnameLB,m_pRoot,m_Curshopdata->nameBase.c_str());
	_setScaleandible();

	if (m_moneytype == _TYPE_GOLD_)
	{
		NFC_setNodeVisable(udGoldMoney1,m_pRoot,true);
		NFC_setNodeVisable(udGoldMoney2,m_pRoot,true);
	}
	else if(m_moneytype == _TYPE_JEWEL_)
	{
		NFC_setNodeVisable(udJewelMoney1,m_pRoot,true);
		NFC_setNodeVisable(udJewelMoney2,m_pRoot,true);
	}
	else if(m_moneytype == _TYPE_PRESTIGE_)
	{
		NFC_setNodeVisable(udPRESTIGEMoney1,m_pRoot,true);
		NFC_setNodeVisable(udPRESTIGEMoney2,m_pRoot,true);
	}
	else if(m_moneytype == _TYPE_EXCHANGE_ITEM_)
	{
		NFC_setNodeVisable(udLONGXUE1,m_pRoot,true);
		NFC_setNodeVisable(udLONGXUE2,m_pRoot,true);
	}
	NFC_setLabelStringInt(udOnePriceLB,m_pRoot,m_oneprice);


	int num = 0;
	const char * str = pEditBoxInputNum->getText();
	sscanf(str, "%d", &num);
	
	int totle = num*m_oneprice;
	NFC_setLabelStringInt(udTotalPriceLB,m_pRoot,totle);
}

void ShopinputNumWindow::_setScaleandible()
{
	for (int i = udJewelMoney1;i<=udLONGXUE2;i++)
	{
		NFC_setNodeVisable(i,m_pRoot,false);
	}
}

void ShopinputNumWindow::OnUpdateWindowEventHandler(std::list<std::string>& paramList){

}

void ShopinputNumWindow::_initRegister()
{
	CCNode* root=m_pRootNode;
	m_pRoot=root;
	_initControl();
	_createLabel();
	_mapBtn();
	_initEditBox();
}	
void ShopinputNumWindow::_initEditBox()
{
	pEditBoxInputNum = (CCEditBox*)m_pRoot->getChildByTag(udItemCountLB);
	pEditBoxInputNum->setTouchPriority(kPRIORITYHIGHER);
	pEditBoxInputNum->setMaxLength(6);
	pEditBoxInputNum->setInputMode(kEditBoxInputModePhoneNumber);
	pEditBoxInputNum->setReturnType(kKeyboardReturnTypeDone);
	pEditBoxInputNum->setDelegate(this);
	pEditBoxInputNum->setText("");	
}

void ShopinputNumWindow::_initControl()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSHOPINPUTNUMWINDOW,m_pRoot);
}

void ShopinputNumWindow::_createLabel()
{
	
}

void ShopinputNumWindow::_mapBtn(){

	CCMenu* menu=(CCMenu*)m_pRoot->getChildByTag(udCloseBtn);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udCloseBtn);
	cc->setTarget(this,menu_selector(ShopinputNumWindow::On_Click_BtnClick));//关闭按钮

	menu = (CCMenu*)m_pRoot->getChildByTag(udDELETEBtn); //减少按钮
	cc= (CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udDELETEBtn);
	cc->setTarget(this,menu_selector(ShopinputNumWindow::On_Click_BtnClick));

	menu = (CCMenu*)m_pRoot->getChildByTag(udADDBtn);	 //增加按钮
	cc= (CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udADDBtn);
	cc->setTarget(this,menu_selector(ShopinputNumWindow::On_Click_BtnClick));

	menu = (CCMenu*)m_pRoot->getChildByTag(udMAXBtn);	//最大按钮
	cc= (CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udMAXBtn);
	cc->setTarget(this,menu_selector(ShopinputNumWindow::On_Click_BtnClick));

	menu = (CCMenu*)m_pRoot->getChildByTag(udBuyBtn);	//购买按钮
	cc= (CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udBuyBtn);
	cc->setTarget(this,menu_selector(ShopinputNumWindow::On_Click_BtnClick));
}

void ShopinputNumWindow::On_Click_BtnClick(cocos2d::CCObject* pSender)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
	if (m_IsKeyBroadShow)
		return;
#endif
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int idx  =cc->getIDX();
	if(idx == udCloseBtn)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_SHOPINPUTNUMWINDOW_);
	}
	else if(idx == udBuyBtn)
	{
		int num = 0;
		const char * str = pEditBoxInputNum->getText();
		sscanf(str, "%d", &num);
		if (m_iTypeShop == 1)
		{
			RANDOMSHOPDATAHANDLER->ToServerBuyItemPacket(m_Curshopdata->shopItemId,num);
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_SHOPINPUTNUMWINDOW_);
			return;
		}
		SHOPINFODATAHANDLER->ToServerBuyItemPacket(SHOPINFODATAHANDLER->m_shopId,m_Curshopdata->shopItemId,num);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_SHOPINPUTNUMWINDOW_);
	}
	else if(idx == udDELETEBtn)
	{
		deleteNum();
	}
	else if(idx == udADDBtn)
	{
		addNum();
	}
	else if(idx == udMAXBtn)
	{
		setMaxNum();
	}
}

void ShopinputNumWindow::deleteNum()//减少按钮
{
	int num = 0;
	const char * str = pEditBoxInputNum->getText();
	sscanf(str, "%d", &num);
	if(num > 1)
	{
		num -= 1;
		char tmp[128] = "";
		sprintf(tmp, "%d", num);
		pEditBoxInputNum->setText(tmp);
	}
	UpDataToTalNumPrice();
}

void ShopinputNumWindow::addNum()//增加按钮
{
	int num = 0;
	const char * str = pEditBoxInputNum->getText();
	sscanf(str, "%d", &num);

	int count = GetBuyAbiliMax(); //可能购买的最大数量

	if(num < count)
	{
		num += 1;
		char tmp[128] = "";
		sprintf(tmp, "%d", num);
		pEditBoxInputNum->setText(tmp);
	}
	UpDataToTalNumPrice();
}

void ShopinputNumWindow::setMaxNum()
{
	char tmp[64] = {0};
	int buyabilimax = GetBuyAbiliMax(); //可能购买的最大数量
	sprintf(tmp, "%d", buyabilimax);
	pEditBoxInputNum->setText(tmp);
	UpDataToTalNumPrice();
}

void   ShopinputNumWindow::UpDataToTalNumPrice()
{
	int num = 0;
	const char * str =pEditBoxInputNum->getText();
	sscanf(str, "%d", &num);

	int totle = num*m_oneprice;
	char totleprice[64]={0};
	sprintf(totleprice,"%d",totle);
	CCLabelTTF*ttf = (CCLabelTTF*)m_pRoot->getChildByTag(udTotalPriceLB);
	ttf->setString(totleprice);

}

void ShopinputNumWindow::setCurMoneyTypeandPrice(ShopInfoGoodsData *data)
{
	if (data->discount == -1)
	{
		m_oneprice = data->price;
		m_moneytype = data->moneyType;
	}
	else
	{
		m_oneprice = data->discount;
		m_moneytype = data->discountMoneyType;
	}
}

int ShopinputNumWindow::GetBuyAbiliMax()
{
	int buyabilimax = 0; //可能购买的最大数量
	int count = 0;
	if (m_Curshopdata->limit == -1)
	{	
		buyabilimax = m_Curshopdata->multiPurchase;
	}
	else
	{
		buyabilimax = m_Curshopdata->multiPurchase > m_Curshopdata->limit?m_Curshopdata->limit:m_Curshopdata->multiPurchase;
	}
	if (m_moneytype == _TYPE_GOLD_)
	{
		if (m_oneprice == 0)
		{
			count = buyabilimax;
		}
		else
		{
			count = ROLEINFODATAHANDLER->m_pRIData->money_/m_oneprice;
			if (count > buyabilimax)
			{
				count = buyabilimax;
			}
		}
	}
	else if(m_moneytype == _TYPE_JEWEL_)
	{
		if (m_oneprice == 0)
		{
			count = buyabilimax;
		}
		else
		{
			count = ROLEINFODATAHANDLER->m_pRIData->jewels_/m_oneprice;
			if (count > buyabilimax)
			{
				count = buyabilimax;
			}
		}
	}
	else if(m_moneytype == _TYPE_PRESTIGE_)
	{
		if (m_oneprice == 0)
		{
			count = buyabilimax;
		}
		else
		{
			count = ROLEINFODATAHANDLER->m_pRIData->prestige_/m_oneprice;
			if (count > buyabilimax)
			{
				count = buyabilimax;
			}
		}
	}
	else if(m_moneytype == _TYPE_EXCHANGE_ITEM_)
	{
		int exchangnum = 0;
		if (m_Curshopdata->discount != -1)
		{
			exchangnum = BAGOTHEROBJECTHANDLER->getObjectCountByTemplateId(m_Curshopdata->distextemplateId);
		}
		else
		{
			exchangnum = BAGOTHEROBJECTHANDLER->getObjectCountByTemplateId(m_Curshopdata->extemplateId);
		}
		count = exchangnum/m_oneprice;
		if (count > buyabilimax)
		{
			count = buyabilimax;
		}
	}

	return count;
}

void ShopinputNumWindow::editBoxEditingDidBegin(CCEditBox* editBox)
{
	m_IsKeyBroadShow = true;
}

void ShopinputNumWindow::editBoxEditingDidEnd(CCEditBox* editBox)
{
	
}


void ShopinputNumWindow::editBoxTextChanged(CCEditBox* editBox, const std::string& text)
{

}

void ShopinputNumWindow::editBoxReturn(CCEditBox* editBox)
{

	m_IsKeyBroadShow = false;

	int num = 0;
	std::string str = pEditBoxInputNum->getText();
	sscanf(str.c_str(), "%d", &num);
	int buyabilimax = GetBuyAbiliMax(); //可能购买的最大数量
	char buffer[32] = {0};

	if (num<1)
	{	sprintf(buffer,"%d",1);
		pEditBoxInputNum->setText(buffer);
	}
	else if (num>buyabilimax)
	{
		sprintf(buffer,"%d",buyabilimax);
		pEditBoxInputNum->setText(buffer);
	}
	UpDataToTalNumPrice();
}