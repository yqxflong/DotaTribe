//Name：SpecialOfferView
//Function：随机商店
//Written By:lvyunlong
//Time：2013-9-11

#include "../include/IWindow.h"
#include "../include/SpecialOfferView.h"
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
#include "../include/BagOtherObjectHandler.h"
using namespace cocos2d::extension;

bool SpecialOfferView::onLoad(){
	if(CCNode::init()){
		_initLayout();
		this->autorelease();
		return true;
	}
	return false;
}
bool SpecialOfferView::onDestroy(){
	m_Pretime = 0;
	this->removeAllChildrenWithCleanup(true);
	this->removeFromParentAndCleanup(true);
	return true;
}
bool SpecialOfferView::onTick(){

	if (RANDOMSHOPDATAHANDLER->m_isRandomTick)
	{
		long long nowtime = TimeSystem::get_instance2()->GetCurrentMicroSecond();
		long long during = nowtime - m_Pretime;
		if (nowtime<m_Pretime)
		{
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_RANDOMMARKETPWINDOW_);
			RANDOMSHOPDATAHANDLER->m_isRandomTick = false;
			return true;
		}
		int seconds = (int)(during / 1000000);
		if(seconds >= 1)
		{
			m_Pretime = nowtime;
			RANDOMSHOPDATAHANDLER->leftSeconds_-=seconds;
			if (RANDOMSHOPDATAHANDLER->leftSeconds_ <= 0)
			{
				EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_RANDOMMARKETPWINDOW_);
				RANDOMSHOPDATAHANDLER->m_isRandomTick = false;
				return true;
			}
			LeftTimeUpdate(RANDOMSHOPDATAHANDLER->leftSeconds_);
		}
	}


	return true;
}
bool SpecialOfferView::onUpdata()
{
	int i = RANDOMSHOPDATAHANDLER->m_RandomInfoList.size();
	unsigned short icount = RANDOMSHOPDATAHANDLER->m_RandomInfoList.size()/ 2;
	unsigned short rest = RANDOMSHOPDATAHANDLER->m_RandomInfoList.size() % 2;
	numberOfCells = icount + rest;
	_setTableView();
	HideWaittingLayer();
	m_Pretime = TimeSystem::get_instance2()->GetCurrentMicroSecond();
	LeftTimeUpdate(RANDOMSHOPDATAHANDLER->leftSeconds_);
	ShowRefreshBall(RANDOMSHOPDATAHANDLER->leftItemCount_);
	return true;
}

void SpecialOfferView::EventWindowCallBack(int iEventType, std::list<std::string>& paramList)
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
		RANDOMSHOPDATAHANDLER->ToServerBuyItemPacket(SHOPINFODATAHANDLER->m_shopItemId,1);
	}
}

void SpecialOfferView::_initLayout(){
	_initData();
	_setMoneyText();
	_showMoneyText();
	_initCell();
	_mapRefBtn();
}

void SpecialOfferView::_initData()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSHOPVIEW,this);
	m_RandomInfonode =(MaskNode*)NFC_getNode(udMASKNODE,this);
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kRANDOMSHOPINFONODE,m_RandomInfonode);
}

void SpecialOfferView::_initCell()
{
	CCNode* node=(CCNode*)this->getChildByTag(udTABLEVIEWCELL);
	m_szCell = node->getContentSize();
}

void SpecialOfferView::_setTableView(){
	m_pTable =(CCTableView*)this->getChildByTag(udTABLEVIEW);
	m_pTable->setDataSource(this);
	m_pTable->setDelegate(this);
	m_pTable->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pTable->setTouchEnabled(true);
	m_pTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
	NFC_refreshTableView(m_pTable);	
}

CCSize SpecialOfferView::cellSizeForTable(CCTableView *table){
	return m_szCell;
};

CCTableViewCell* SpecialOfferView::tableCellAtIndex(CCTableView *table, unsigned int idx){
	CCTableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
		_createTableCell(cell);	
	}
	_setTableCell(cell,idx);
	return cell;
};

unsigned int SpecialOfferView::numberOfCellsInTableView(CCTableView *table){
	
	return numberOfCells;//计算有多少个cell
};


void SpecialOfferView::_createTableCell(cocos2d::extension::CCTableViewCell * cell){
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kRANDOMSHOPCELL,cell);
} 

void SpecialOfferView::_setAllCurrencyVisible(cocos2d::extension::CCTableViewCell* cell,bool isible,int blockIdx)
{
	NFC_showNode(udDIAMOND1+blockIdx%2,cell,isible);
	NFC_showNode(udGOLD1+blockIdx%2,cell,isible);
	NFC_showNode(udPRESTIGE1+blockIdx%2,cell,isible);
	NFC_showNode(udLONGXUE1+blockIdx%2,cell,isible);
	NFC_showNode(udBUYBTNGREY1+blockIdx%2,cell,isible);
}

void SpecialOfferView::_setTableCell(cocos2d::extension::CCTableViewCell* cell,int idx)
{
	idx*=2;
	_setCellBlockInfo(cell,idx);
	_mapCellBtn(cell,idx);
	idx++;
	if (idx==RANDOMSHOPDATAHANDLER->m_RandomInfoList.size()){
		_showBlock2(cell,false);
		return;
	}else{
		_showBlock2(cell,true);
		_setCellBlockInfo(cell,idx);
		_mapCellBtn(cell,idx);
	}
}

void SpecialOfferView::_showBlock2(cocos2d::CCNode* cell,bool isShow){
	for (int i=udBUY2;i<=udVIEWDEBRIS2;i+=2)
		NFC_showNode(i,cell,isShow);
}

void SpecialOfferView::_mapCellBtn(cocos2d::extension::CCTableViewCell* cell,int blockIdx){

	CCMenu* menu=(CCMenu*)cell->getChildByTag(udBUYBTN1+blockIdx%2);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(blockIdx);
	cc->setTarget(this,menu_selector(SpecialOfferView::On_Cell_SellEvent));

	DTAwardBoard* dd=(DTAwardBoard*)cell->getChildByTag(udVIEWDEBRIS1+blockIdx%2);
	dd->setIDX(blockIdx);
	dd->setTarget(this,menu_selector(SpecialOfferView::On_Cell_ClickEvent));

}

void SpecialOfferView::_mapRefBtn()
{
	CCMenu* menu=(CCMenu*)m_RandomInfonode->getChildByTag(udREFRESHMENU);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setTarget(this,menu_selector(SpecialOfferView::On_Refresh_Event));
}

void SpecialOfferView::_setCellBlockInfo(cocos2d::extension::CCTableViewCell* cell,int blockIdx)
{
	RandomGoodsData *data = RANDOMSHOPDATAHANDLER->m_RandomInfoList[blockIdx];

	//金币类型隐藏
	_setAllCurrencyVisible(cell,false,blockIdx);

	/*
	//隐藏限售次数
	NFC_showNode(udLIMIT1+blockIdx%2,cell,false);
	//隐藏每日限售
	NFC_showNode(udDAY1+blockIdx%2,cell,false);
	*/
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
	NFC_setLabelString(udNAME1+blockIdx%2,cell,data->strname.c_str());
	//商品控件
	DTAwardBoard* dd=(DTAwardBoard*)cell->getChildByTag(udVIEWDEBRIS1+blockIdx%2);
	dd->ChangeObject(data->quality,data->goodsiconId);
	if(data->type == kBAGSKIN)
	{
		dd->setContentScale(CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f);
	}
	else
	{
		dd->setContentScale(1);
	}
}

void SpecialOfferView::On_Cell_SellEvent(cocos2d::CCObject* pSender){

	BTN_INTERVAL("SpecialOfferView_Sell",_COMMON_BTN_CLICK_INTERVAL_SMALL);
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int idx  =cc->getIDX();
	m_Curblockindex = idx;
	if (idx > RANDOMSHOPDATAHANDLER->m_RandomInfoList.size()-1)
	{
		return;
	}
	RandomGoodsData *data = RANDOMSHOPDATAHANDLER->m_RandomInfoList[idx];

	if (data!=NULL)
	{
		if (data->limit > 1)
		{
			char type[32]={0};
			sprintf(type,"%d",idx);

			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_SHOPINPUTNUMWINDOW_, type,"1");
		}
		else
		{
			if (data->moneytype == _TYPE_JEWEL_ || data->moneytype == _TYPE_PRESTIGE_)
			{
				NFC_showMessageBox(SysLangDataManager::get_instance2()->GetSysLangById(6089), _TYPED_EVENT_SHOP_BUY_COUNTERSIGN);
				SHOPINFODATAHANDLER->m_shopItemId = data->goodsindex;
				return;
			}
			RANDOMSHOPDATAHANDLER->ToServerBuyItemPacket(data->goodsindex,1);
		}
	}
}

void SpecialOfferView::On_Refresh_Event(cocos2d::CCObject* pSender)
{
	BTN_INTERVAL("RefreshBtn",_COMMON_BTN_CLICK_INTERVAL_SMALL);
	RANDOMSHOPDATAHANDLER->RefreshRandomShop();
}

void SpecialOfferView::On_Cell_ClickEvent(cocos2d::CCObject* pSender){
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int idx  =cc->getIDX();
	RandomGoodsData *data = RANDOMSHOPDATAHANDLER->m_RandomInfoList[idx];
	_showgoodstips(data);
}

void SpecialOfferView::_showgoodstips(RandomGoodsData *data)
{
	SHOPTIPSDATAHANDLER->m_pTips->name_ = data->strname;
	SHOPTIPSDATAHANDLER->m_pTips->description_ = data->strdescription;
	
	//打折discountMoneyType
	SHOPTIPSDATAHANDLER->m_pTips->price_ = data->price;
	SHOPTIPSDATAHANDLER->m_pTips->moneytype_ = data->moneytype;
	
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_SHOPTIPSWINDOW_);
}


void SpecialOfferView::LeftTimeUpdate(int lefttimes)
{
	char buff[512]={0};
	sprintf(buff, "%02d:%02d:%02d", lefttimes / 3600, (lefttimes % 3600) / 60, (lefttimes % 3600) % 60);
	NFC_setLabelString(udNEXTGOODSTIMENUM,m_RandomInfonode,buff);
}

void SpecialOfferView::ShowRefreshBall(int num)
{
	char buff[1024]={0};
	sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(6049).c_str(),num,RANDOMSHOPDATAHANDLER->refreshPrice_);
	NFC_setLabelString(udINFOTEXT,m_RandomInfonode,buff);
}

/*
	tips回调事件
*/
void SpecialOfferView::cancelTipsLayer(){

}

void SpecialOfferView::_enableBtnsCell(bool enabled,CCNode* cell,int blockIdx){
	_enableBtnCell(udBUYBTN1+blockIdx%2,enabled,cell);
	NFC_showNode(udBUYBTNGREY1+blockIdx%2,cell,!enabled);
}

void SpecialOfferView::_enableBtnCell(int key,bool enabled,CCNode* cell){
	CCMenu* menu=(CCMenu*)cell->getChildByTag(key);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setEnabled(enabled);
}

void SpecialOfferView::HideWaittingLayer()
{
	//NFC_showNode(udColorLayer,this,false);
	//NFC_showNode(udANCOMMON,this,false);
}

void SpecialOfferView::_setShopBuyEnableBtn(RandomGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx)
{
	bool isBtnenable = true;
	//不打折
	long long num = 0;
	if (data->moneytype == _TYPE_GOLD_)
	{
		num = ROLEINFODATAHANDLER->m_pRIData->money_;
	}
	else if (data->moneytype == _TYPE_JEWEL_)
	{
		num = ROLEINFODATAHANDLER->m_pRIData->jewels_;
	}
	else if (data->moneytype == _TYPE_PRESTIGE_)
	{
		num = ROLEINFODATAHANDLER->m_pRIData->prestige_;
	}
	else if (data->moneytype == _TYPE_EXCHANGE_ITEM_)
	{
		num = BAGOTHEROBJECTHANDLER->getObjectCountByTemplateId(data->templateId);
	}

	if ((data)->price > num || (data)->limit == 0)
	{
		isBtnenable = false;
	}
	else
	{
		isBtnenable = true;
	}
	_enableBtnsCell(isBtnenable,cell,blockIdx);
}


void SpecialOfferView::_setRedText(RandomGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx)
{
	//不打折
	long long num = 0;
	if (data->moneytype == _TYPE_GOLD_)
	{
		num = ROLEINFODATAHANDLER->m_pRIData->money_;
	}
	else if (data->moneytype == _TYPE_JEWEL_)
	{
		num = ROLEINFODATAHANDLER->m_pRIData->jewels_;
	}
	else if (data->moneytype == _TYPE_PRESTIGE_)
	{
		num = ROLEINFODATAHANDLER->m_pRIData->prestige_;
	}
	else if (data->moneytype == _TYPE_EXCHANGE_ITEM_)
	{
		num = BAGOTHEROBJECTHANDLER->getObjectCountByTemplateId(data->templateId);
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

void SpecialOfferView::_setmoneycell(RandomGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx)
{
	if (data->moneytype == _TYPE_GOLD_)
	{
		//正价货币类型
		NFC_showNode(udGOLD1+blockIdx%2,cell,true);
	}
	else if (data->moneytype == _TYPE_JEWEL_)
	{
		//正价货币类型
		NFC_showNode(udDIAMOND1+blockIdx%2,cell,true);
	}
	else if (data->moneytype == _TYPE_PRESTIGE_)
	{
		//正价货币类型
		NFC_showNode(udPRESTIGE1+blockIdx%2,cell,true);

	}//对换物品
	else if (data->moneytype == _TYPE_EXCHANGE_ITEM_)
	{
		//正价货币类型
		NFC_showNode(udLONGXUE1+blockIdx%2,cell,true);
	}

}

bool SpecialOfferView::onUpdateText()
{
	_setMoneyText();

	bool islimit = false;
	if (SHOPINFODATAHANDLER->m_isBshopsellupdate)
	{	
		
		std::vector<RandomGoodsData*>::iterator  posbegin = RANDOMSHOPDATAHANDLER->m_RandomInfoList.begin();
		std::vector<RandomGoodsData*>::iterator  posend = RANDOMSHOPDATAHANDLER->m_RandomInfoList.end();
		for (posbegin;posbegin!=posend;posbegin++)
		{
			if ((*posbegin)->goodsindex == RANDOMSHOPDATAHANDLER->m_selledshopItemId)
			{
				if ((*posbegin)->limit != -1)
				{
					(*posbegin)->limit -= RANDOMSHOPDATAHANDLER->m_selledcount;
				}
				break;
			}	
		}
		SHOPINFODATAHANDLER->m_isBshopsellupdate = false;
		int j = 0;
		int numcount = 0;
		bool  isodd;
		if (RANDOMSHOPDATAHANDLER->m_count == numberOfCells*2)
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
					RandomGoodsData *data = RANDOMSHOPDATAHANDLER->m_RandomInfoList[j*2];
					if (data != NULL)
					{
						_setShopBuyEnableBtn(data,pNode,j*2);
						_setRedText(data,pNode,j*2);
					}
							
				}
				else
				{
					RandomGoodsData *data = RANDOMSHOPDATAHANDLER->m_RandomInfoList[j*2];
					if (data != NULL)
					{
						_setShopBuyEnableBtn(data,pNode,j*2);
						_setRedText(data,pNode,j*2);
					}
					RandomGoodsData *data1 = RANDOMSHOPDATAHANDLER->m_RandomInfoList[j*2+1];
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
			//剩余数量
			char buffer[1024]={0};
			sprintf(buffer,SysLangDataManager::get_instance2()->GetSysLangById(6059).c_str(),(*posbegin)->limit);
			NFC_setLabelString(udLIMIT1+m_Curblockindex%2,pNode,buffer);
		}
	}
	
	return true;
}

void SpecialOfferView::_setrequireInfo(RandomGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx)
{
	CCLabelTTF* limitttf= (CCLabelTTF*)cell->getChildByTag(udLIMIT1+blockIdx%2);
	char buffer[1024]={0};
	sprintf(buffer,SysLangDataManager::get_instance2()->GetSysLangById(6059).c_str(),data->limit);
	limitttf->setString(buffer);
	limitttf->setVisible(true);

}

void SpecialOfferView::_setMoneyText()
{
	char tmp[64] ={0};
	sprintf(tmp,"%d",ROLEINFODATAHANDLER->m_pRIData->money_);
	NFC_setLabelString(udTEXTCOUNTTTF2,this,tmp);
	memset(tmp,0,sizeof(tmp));
	sprintf(tmp,"%d",ROLEINFODATAHANDLER->m_pRIData->jewels_);
	NFC_setLabelString(udTEXTCOUNTTTF1,this,tmp);
}

void SpecialOfferView::_showMoneyText()
{
	NFC_showNode(udICONMONEY,this,true);
	NFC_showNode(udTEXTCOUNTTTF1,this,true);
	NFC_showNode(udTEXTBG1,this,true);

	NFC_showNode(udICONDIAMOND,this,true);
	NFC_showNode(udTEXTCOUNTTTF2,this,true);
	NFC_showNode(udTEXTBG2,this,true);
}