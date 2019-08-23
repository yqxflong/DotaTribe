//Name：ShopView
//Function：声望商店
//Written By：lvyunlong
//Time：2013-9-11

#include "../include/ShopView.h"
#include "../include/NFControlsManager.h"
#include "../include/UIViewDataManger.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/CMenuItemSprite.h"
#include "../include/CSprite.h"
#include "../include/CPublicVarReader.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/ShopinputNumWindow.h"
#include "../include/ClientConstDataManager.h"
#include "../include/NFControlsManager.h"
#include "../include/SysLangDataManager.h"
#include "../include/ShopTipsDataHandler.h"
#include "../include/TimeSystem.h"
#include "../include/DTAwardBoard.h"
#include "../include/BagOtherObjectHandler.h"
using namespace cocos2d::extension;

bool ShopView::onLoad(){
	if(CCNode::init()){
		_initLayout();
		this->autorelease();
		return true;
	}
	return false;
}

bool ShopView::onDestroy()
{
	this->removeAllChildrenWithCleanup(true);
	this->removeFromParentAndCleanup(true);
	return true;
}

bool ShopView::onTick(){

	return true;
}

bool ShopView::onUpdata()
{
	if (SHOPINFODATAHANDLER->m_isBshopinfoupdate)
	{
		unsigned short icount = SHOPINFODATAHANDLER->m_ShopGoodsBaselist.size()/ 2;
		unsigned short rest = SHOPINFODATAHANDLER->m_ShopGoodsBaselist.size() % 2;
		numberOfCells = icount + rest;
		_setTableView();
		HideWaittingLayer();
		SHOPINFODATAHANDLER->m_isBshopinfoupdate = false;
	}
	return true;
}

void ShopView::EventWindowCallBack(int iEventType, std::list<std::string>& paramList)
{
	if(iEventType == _TYPED_EVENT_UPDATE_SHOPWINDOW_)
	{
		onUpdata();
	}
	else if(iEventType == _TYPED_EVENT_REFRESH_UPDATEUI_)
	{
		onUpdateText();
	}
	else if(iEventType == _TYPED_EVENT_SHOP_BUY_COUNTERSIGN)
	{
		SHOPINFODATAHANDLER->ToServerBuyItemPacket(SHOPINFODATAHANDLER->m_shopId,SHOPINFODATAHANDLER->m_shopItemId,1);
	}
}

void ShopView::_initLayout(){
	_initData();
	_setPrestigeText();
	_showMoneyText();
	_initCell();
}

void ShopView::_initData()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSHOPVIEW,this);
}

void ShopView::_showMoneyText()
{
	NFC_showNode(udPRESTIGE,this,true);
	NFC_showNode(udTEXTCOUNTTTF1,this,true);
	NFC_showNode(udTEXTBG1,this,true);
}

void ShopView::_initCell()
{
	CCNode* node=(CCNode*)this->getChildByTag(udTABLEVIEWCELL);
	m_szCell = node->getContentSize();
}

void ShopView::_setTableView(){
	m_pTable =(CCTableView*)this->getChildByTag(udTABLEVIEW);
	m_pTable->setDataSource(this);
	m_pTable->setDelegate(this);
	m_pTable->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pTable->setTouchEnabled(true);
	m_pTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
	NFC_refreshTableView(m_pTable);	
}

CCSize ShopView::cellSizeForTable(CCTableView *table){
	return m_szCell;
};

CCTableViewCell* ShopView::tableCellAtIndex(CCTableView *table, unsigned int idx){
	CCTableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
		_createTableCell(cell);	
	}
	_setTableCell(cell,idx);
	return cell;
};

unsigned int ShopView::numberOfCellsInTableView(CCTableView *table){
	
	return numberOfCells;//计算有多少个cell
};


void ShopView::_createTableCell(cocos2d::extension::CCTableViewCell * cell){
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSHOPVIEWCELL,cell);
	//_setAllScale(cell,0.7f);
} 


void ShopView::_setAllCurrencyVisible(cocos2d::extension::CCTableViewCell* cell,bool isible,int blockIdx)
{
	NFC_showNode(udDIAMOND1+blockIdx%2,cell,isible);
	NFC_showNode(udDIAMONDDOWN1+blockIdx%2,cell,isible);
	NFC_showNode(udGOLD1+blockIdx%2,cell,isible);
	NFC_showNode(udGOLDDOWN1+blockIdx%2,cell,isible);
	NFC_showNode(udPRESTIGE1+blockIdx%2,cell,isible);
	NFC_showNode(udPRESTIGEDOWN1+blockIdx%2,cell,isible);
	NFC_showNode(udLONGXUE1+blockIdx%2,cell,isible);
	NFC_showNode(udLONGXUEDOWN1+blockIdx%2,cell,isible);
	NFC_showNode(udBUYBTNGREY1+blockIdx%2,cell,isible);
}

void ShopView::_setTableCell(cocos2d::extension::CCTableViewCell* cell,int idx)
{
	idx*=2;
	_setCellBlockInfo(cell,idx);
	_mapCellBtn(cell,idx);
	idx++;
	if (idx==SHOPINFODATAHANDLER->m_ShopGoodsBaselist.size()){
		_showBlock2(cell,false);
		return;
	}else{
		_showBlock2(cell,true);
		_setCellBlockInfo(cell,idx);
		_mapCellBtn(cell,idx);
	}
}

void ShopView::_showBlock2(cocos2d::CCNode* cell,bool isShow){
	for (int i=udBUY2;i<=udVIEWDEBRIS2;i+=2)
		NFC_showNode(i,cell,isShow);
}

void ShopView::_mapCellBtn(cocos2d::extension::CCTableViewCell* cell,int blockIdx){

	CCMenu* menu=(CCMenu*)cell->getChildByTag(udBUYBTN1+blockIdx%2);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(blockIdx);
	cc->setTarget(this,menu_selector(ShopView::On_Cell_SellEvent));

	DTAwardBoard* dd=(DTAwardBoard*)cell->getChildByTag(udVIEWDEBRIS1+blockIdx%2);
	dd->setIDX(blockIdx);
	dd->setTarget(this,menu_selector(ShopView::On_Cell_ClickEvent));

}

void ShopView::_setCellBlockInfo(cocos2d::extension::CCTableViewCell* cell,int blockIdx)
{
	ShopInfoGoodsData *data = SHOPINFODATAHANDLER->m_ShopGoodsBaselist[blockIdx];

	//金币类型隐藏
	_setAllCurrencyVisible(cell,false,blockIdx);

	//隐藏打折框
	NFC_showNode(udTEXT3+blockIdx%2,cell,false);
	//隐藏打折价钱文字
	NFC_showNode(udRED1+blockIdx%2,cell,false);
	//隐藏限售次数
	NFC_showNode(udLIMIT1+blockIdx%2,cell,false);
	//隐藏等级限售
	NFC_showNode(udLevelDAY1+blockIdx%2,cell,false);
	//隐藏每日限售
	NFC_showNode(udDAY1+blockIdx%2,cell,false);
	//折扣线
	NFC_showNode(udLine1+blockIdx%2,cell,false);
	//设置按钮是否置灰
	_setShopBuyEnableBtn(data,cell,blockIdx);
	_setRedText(data,cell,blockIdx);
	//设置正价钱数
	NFC_setLabelStringInt(udYE1+blockIdx%2,cell,data->price);

	//设置货币类型显示
	_setmoneycell(data,cell,blockIdx);
	//购买条件限制
	_setrequireInfo(data,cell,blockIdx);

	//装备名称
	NFC_setLabelString(udNAME1+blockIdx%2,cell,data->nameBase.c_str());
	//商品控件
	DTAwardBoard* dd=(DTAwardBoard*)cell->getChildByTag(udVIEWDEBRIS1+blockIdx%2);
	dd->ChangeObject(data->quality,data->iconId);
	if(data->catogory_ == kBAGSKIN)
	{
		dd->setContentScale(CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f);
	}
	else
	{
		dd->setContentScale(1);
	}
}

void ShopView::On_Cell_SellEvent(cocos2d::CCObject* pSender){
	BTN_INTERVAL("ShopView_Sell",_COMMON_BTN_CLICK_INTERVAL_SMALL);
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int idx  =cc->getIDX();
	
	m_Curblockindex = idx;
	if (idx > SHOPINFODATAHANDLER->m_ShopGoodsBaselist.size()-1)
	{
		return;
	}
	
	ShopInfoGoodsData *data = SHOPINFODATAHANDLER->m_ShopGoodsBaselist[idx];

	if (data!=NULL)
	{
		if (data->multiPurchase != 1)
		{
			char type[32]={0};
			sprintf(type,"%d",idx);

			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_SHOPINPUTNUMWINDOW_, type);
		}
		else
		{
			if (data->moneyType == _TYPE_JEWEL_ || data->moneyType == _TYPE_PRESTIGE_)
			{
				NFC_showMessageBox(SysLangDataManager::get_instance2()->GetSysLangById(6089), _TYPED_EVENT_SHOP_BUY_COUNTERSIGN);
				SHOPINFODATAHANDLER->m_shopItemId = data->shopItemId;
				return;
			}
			SHOPINFODATAHANDLER->ToServerBuyItemPacket(SHOPINFODATAHANDLER->m_shopId,data->shopItemId,1);
		}
	}
}

void ShopView::On_Cell_ClickEvent(cocos2d::CCObject* pSender){
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int idx  =cc->getIDX();
	ShopInfoGoodsData *data = SHOPINFODATAHANDLER->m_ShopGoodsBaselist[idx];
	_showgoodstips(data);
}

void ShopView::_showgoodstips(ShopInfoGoodsData *data)
{
	SHOPTIPSDATAHANDLER->m_pTips->name_ = data->nameBase;
	SHOPTIPSDATAHANDLER->m_pTips->description_ = data->descriptionBase;
	if (data->discount != -1)
	{
		//打折discountMoneyType
		SHOPTIPSDATAHANDLER->m_pTips->price_ = data->discount;
		SHOPTIPSDATAHANDLER->m_pTips->moneytype_ = data->discountMoneyType;
	}
	else
	{
		//不打折
		SHOPTIPSDATAHANDLER->m_pTips->price_ = data->price;
		SHOPTIPSDATAHANDLER->m_pTips->moneytype_ = data->moneyType;
	}
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_SHOPTIPSWINDOW_);
}

/*
	tips回调事件
*/
void ShopView::cancelTipsLayer(){

}

void ShopView::_enableBtnsCell(bool enabled,CCNode* cell,int blockIdx){
	_enableBtnCell(udBUYBTN1+blockIdx%2,enabled,cell);
	NFC_showNode(udBUYBTNGREY1+blockIdx%2,cell,!enabled);
}

void ShopView::_enableBtnCell(int key,bool enabled,CCNode* cell){
	CCMenu* menu=(CCMenu*)cell->getChildByTag(key);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setEnabled(enabled);
}

void ShopView::HideWaittingLayer()
{
	//NFC_showNode(udColorLayer,this,false);
	//NFC_showNode(udANCOMMON,this,false);
}

void ShopView::_setShopBuyEnableBtn(ShopInfoGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx)
{
	bool isBtnenable = true;
	
	if (data->requireType == 1)
	{
		if (data->require > ROLEINFODATAHANDLER->m_pRIData->level_)
		{
			_enableBtnsCell(false,cell,blockIdx);
			return;
		}
		
	}
	if (data->requireType == 2)
	{
		if (data->require > ROLEINFODATAHANDLER->m_pRIData->vipLevel_)
		{
			_enableBtnsCell(false,cell,blockIdx);
			return;
		}
	}

	if (data->discount == -1)
	{
		//不打折
		long long num = 0;
		if (data->moneyType == _TYPE_GOLD_)
		{
			num = ROLEINFODATAHANDLER->m_pRIData->money_;
		}
		else if (data->moneyType == _TYPE_JEWEL_)
		{
			num = ROLEINFODATAHANDLER->m_pRIData->jewels_;
		}
		else if (data->moneyType == _TYPE_PRESTIGE_)
		{
			num = ROLEINFODATAHANDLER->m_pRIData->prestige_;
		}
		else if (data->moneyType == _TYPE_EXCHANGE_ITEM_)
		{
			num = BAGOTHEROBJECTHANDLER->getObjectCountByTemplateId(data->extemplateId);
		}

		if ((data)->price > num || (data)->limit == 0)
		{
			isBtnenable = false;
		}
		else
		{
			isBtnenable = true;
		}
	}
	else
	{
		//打折
		long long num = 0;
		if (data->discountMoneyType == _TYPE_GOLD_)
		{
			num = ROLEINFODATAHANDLER->m_pRIData->money_;
		}
		else if (data->discountMoneyType == _TYPE_JEWEL_)
		{
			num = ROLEINFODATAHANDLER->m_pRIData->jewels_;
		}
		else if (data->discountMoneyType == _TYPE_PRESTIGE_)
		{
			num = ROLEINFODATAHANDLER->m_pRIData->prestige_;
		}
		else if (data->discountMoneyType == _TYPE_EXCHANGE_ITEM_)
		{
			num = BAGOTHEROBJECTHANDLER->getObjectCountByTemplateId(data->distextemplateId);
		}

		if ((data)->discount > num || (data)->limit == 0)
		{
			isBtnenable = false;
		}
		else
		{
			isBtnenable = true;
		}
	}
	_enableBtnsCell(isBtnenable,cell,blockIdx);
}


void ShopView::_setRedText(ShopInfoGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx)
{
	if (data->discount == -1)
	{
		//不打折
		long long num = 0;
		if (data->moneyType == _TYPE_GOLD_)
		{
			num = ROLEINFODATAHANDLER->m_pRIData->money_;
		}
		else if (data->moneyType == _TYPE_JEWEL_)
		{
			num = ROLEINFODATAHANDLER->m_pRIData->jewels_;
		}
		else if (data->moneyType == _TYPE_PRESTIGE_)
		{
			num = ROLEINFODATAHANDLER->m_pRIData->prestige_;
		}
		else if (data->moneyType == _TYPE_EXCHANGE_ITEM_)
		{
			num = BAGOTHEROBJECTHANDLER->getObjectCountByTemplateId(data->extemplateId);
		}

		if ((data)->price > num)
		{
			CCLabelTTF* undiscount = (CCLabelTTF*)cell->getChildByTag(udYE1+blockIdx%2);
			undiscount->setColor(ccRED);
		}
		else
		{
			CCLabelTTF* undiscount = (CCLabelTTF*)cell->getChildByTag(udYE1+blockIdx%2);
			undiscount->setColor(ccYELLOW);
		}
	}
	else
	{
		//打折
		CCLabelTTF* undiscount = (CCLabelTTF*)cell->getChildByTag(udYE1+blockIdx%2);
		undiscount->setColor(ccYELLOW);
		
		long long num = 0;
		if (data->discountMoneyType == _TYPE_GOLD_)
		{
			num = ROLEINFODATAHANDLER->m_pRIData->money_;
		}
		else if (data->discountMoneyType == _TYPE_JEWEL_)
		{
			num = ROLEINFODATAHANDLER->m_pRIData->jewels_;
		}
		else if (data->discountMoneyType == _TYPE_PRESTIGE_)
		{
			num = ROLEINFODATAHANDLER->m_pRIData->prestige_;
		}
		else if (data->discountMoneyType == _TYPE_EXCHANGE_ITEM_)
		{
			num = BAGOTHEROBJECTHANDLER->getObjectCountByTemplateId(data->distextemplateId);
		}

		if ((data)->discount > num)
		{
			CCLabelTTF* undiscount = (CCLabelTTF*)cell->getChildByTag(udRED1+blockIdx%2);
			undiscount->setColor(ccRED);
		}
		else
		{
			CCLabelTTF* undiscount = (CCLabelTTF*)cell->getChildByTag(udRED1+blockIdx%2);
			undiscount->setColor(ccYELLOW);
		}
	}
}

void ShopView::_setmoneycell(ShopInfoGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx)
{
	if (data->moneyType == _TYPE_GOLD_)
	{
		//正价货币类型
		NFC_showNode(udGOLD1+blockIdx%2,cell,true);
	}
	else if (data->moneyType == _TYPE_JEWEL_)
	{
		//正价货币类型
		NFC_showNode(udDIAMOND1+blockIdx%2,cell,true);
	}
	else if (data->moneyType == _TYPE_PRESTIGE_)
	{
		//正价货币类型
		NFC_showNode(udPRESTIGE1+blockIdx%2,cell,true);

	}//对换物品
	else if (data->moneyType == _TYPE_EXCHANGE_ITEM_)
	{
		//正价货币类型
		NFC_showNode(udLONGXUE1+blockIdx%2,cell,true);
	}

	//如果是打折
	if (data->discount != -1)
	{
		if (data->discountMoneyType == _TYPE_GOLD_)
		{
			NFC_showNode(udGOLDDOWN1+blockIdx%2,cell,true);
		}
		else if (data->discountMoneyType == _TYPE_JEWEL_)
		{
			NFC_showNode(udDIAMONDDOWN1+blockIdx%2,cell,true);
		}
		else if (data->discountMoneyType == _TYPE_PRESTIGE_)
		{
			NFC_showNode(udPRESTIGEDOWN1+blockIdx%2,cell,true);
		}
		else if (data->discountMoneyType == _TYPE_EXCHANGE_ITEM_)
		{
			NFC_showNode(udLONGXUEDOWN1+blockIdx%2,cell,true);
		}
		//打折框
		NFC_showNode(udTEXT3+blockIdx%2,cell,true);
		//打折价钱
		NFC_setLabelStringInt(udRED1+blockIdx%2,cell,data->discount,true);
		//折扣线
		NFC_showNode(udLine1+blockIdx%2,cell,true);
	}
}

bool ShopView::onUpdateText()
{
	_setPrestigeText();

	bool islimit = false;
	if (SHOPINFODATAHANDLER->m_isBshopsellupdate)
	{	
		
		std::vector<ShopInfoGoodsData*>::iterator  posbegin = SHOPINFODATAHANDLER->m_ShopGoodsBaselist.begin();
		std::vector<ShopInfoGoodsData*>::iterator  posend = SHOPINFODATAHANDLER->m_ShopGoodsBaselist.end();
		for (posbegin;posbegin!=posend;posbegin++)
		{
			if ((*posbegin)->shopItemId == SHOPINFODATAHANDLER->m_selledshopItemId)
			{
				if ((*posbegin)->limit != -1)
				{
					(*posbegin)->limit -= SHOPINFODATAHANDLER->m_selledcount;
				}
				break;
			}	
		}
		SHOPINFODATAHANDLER->m_isBshopsellupdate = false;
		int j = 0;
		int numcount = 0;
		bool  isodd;
		if (SHOPINFODATAHANDLER->m_count == numberOfCells*2)
		{
			isodd = false;
		}
		else
		{
			isodd = true;
		}
		for (j;j<numberOfCells;j++)
		{
			cocos2d::extension::CCTableViewCell* pNode = m_pTable->cellAtIndex(j);
			if (pNode!= NULL)
			{
				if (j+1 == numberOfCells && isodd)
				{
					ShopInfoGoodsData *data = SHOPINFODATAHANDLER->m_ShopGoodsBaselist[j*2];
					if (data != NULL)
					{
						_setShopBuyEnableBtn(data,pNode,j*2);
						_setRedText(data,pNode,j*2);
					}
							
				}
				else
				{
					ShopInfoGoodsData *data = SHOPINFODATAHANDLER->m_ShopGoodsBaselist[j*2];
					if (data != NULL)
					{
						_setShopBuyEnableBtn(data,pNode,j*2);
						_setRedText(data,pNode,j*2);
					}
					ShopInfoGoodsData *data1 = SHOPINFODATAHANDLER->m_ShopGoodsBaselist[j*2+1];
					if (data1 != NULL)
					{
						_setShopBuyEnableBtn(data1,pNode,j*2+1);
						_setRedText(data1,pNode,j*2+1);
					}
				}
			}
		}

		int cellindex = m_Curblockindex/2;
		cocos2d::CCNode* pNode = m_pTable->cellAtIndex(cellindex);
		if (pNode != NULL)
		{
			CCLabelTTF* ttf = (CCLabelTTF*)pNode->getChildByTag(udLIMIT1+m_Curblockindex%2);
			char buffer[128]={0};
			sprintf(buffer,"%d/%d",(*posbegin)->limit,(*posbegin)->maxlimit);
			ttf->setString(buffer);
		}
	}
	

	return true;
}

void ShopView::_setPrestigeText()
{
	NFC_setLabelStringInt(udTEXTCOUNTTTF1,this,ROLEINFODATAHANDLER->m_pRIData->prestige_);
}

void ShopView::_setrequireInfo(ShopInfoGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx)
{
	if(data->requireType == 0)
	{
		_setdaylimit(data,cell,blockIdx);
	}
	else if (data->requireType == 1)
	{
		if (data->require >ROLEINFODATAHANDLER->m_pRIData->level_)
		{
			CCLabelTTF* limitttf= (CCLabelTTF*)cell->getChildByTag(udLevelDAY1+blockIdx%2);
			char buffer[64]={0};
			sprintf(buffer,SysLangDataManager::get_instance2()->GetSysLangById(678).c_str(),data->require);
			limitttf->setString(buffer);
			limitttf->setVisible(true);
		}
		else
		{
			_setdaylimit(data,cell,blockIdx);
		}
	}
	else if (data->requireType == 2)
	{
		if (data->require >ROLEINFODATAHANDLER->m_pRIData->vipLevel_)
		{
			CCLabelTTF* limitttf= (CCLabelTTF*)cell->getChildByTag(udLevelDAY1+blockIdx%2);
			char buffer[64]={0};
			sprintf(buffer,SysLangDataManager::get_instance2()->GetSysLangById(679).c_str(),data->require);
			limitttf->setString(buffer);
			limitttf->setVisible(true);
		}
		else
		{
			_setdaylimit(data,cell,blockIdx);
		}
	}
}

void ShopView::_setdaylimit(ShopInfoGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx)
{
	if (data->limit != -1)
	{
		CCLabelTTF* limitttf= (CCLabelTTF*)cell->getChildByTag(udLIMIT1+blockIdx%2);
		char buffer[64]={0};
		sprintf(buffer,"%d/%d",data->limit,data->maxlimit);
		limitttf->setString(buffer);
		limitttf->setVisible(true);

		NFC_showNode(udDAY1+blockIdx%2,cell,true);
	}
}