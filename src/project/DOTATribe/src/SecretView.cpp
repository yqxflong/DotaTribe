//Name��SecretView
//Function���ر��̵�
//Written By��lvyunlong
//Time��2013-9-11

#include "../include/IWindow.h"
#include "../include/NFControlsManager.h"
#include "../include/SecretView.h"
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

bool SecretView::onLoad(){
	if(CCNode::init()){
		_initLayout();
		this->autorelease();
		return true;
	}
	return false;
}
bool SecretView::onDestroy(){
	m_CurLongxueBlood = 0;
	this->removeAllChildrenWithCleanup(true);
	this->removeFromParentAndCleanup(true);
	return true;
}
bool SecretView::onTick(){

	return true;
}
bool SecretView::onUpdata()
{
	
	if (SHOPINFODATAHANDLER->m_isBshopinfoupdate)
	{
		_setLongXueText();
		unsigned short icount = SHOPINFODATAHANDLER->m_ShopGoodsBaselist.size()/ 2;
		unsigned short rest = SHOPINFODATAHANDLER->m_ShopGoodsBaselist.size() % 2;
		numberOfCells = icount + rest;
		_setTableView();
		HideWaittingLayer();
		SHOPINFODATAHANDLER->m_isBshopinfoupdate = false;
	}
	return true;
}

void SecretView::EventWindowCallBack(int iEventType, std::list<std::string>& paramList)
{
	if(iEventType == _TYPED_EVENT_UPDATE_SHOPWINDOW_)
	{
		onUpdata();
	}
	else if(iEventType == _TYPED_EVENT_REFRESH_UPDATEUI_)
	{
		onUpdateText();
	}
}


void SecretView::_initLayout(){
	_initData();
	_setLongXueText();
	_showMoneyText();
	_initCell();
}

void SecretView::_initData()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSHOPVIEW,this);
}

void SecretView::_initCell()
{
	CCNode* node=(CCNode*)this->getChildByTag(udTABLEVIEWCELL);
	m_szCell = node->getContentSize();
}

void SecretView::_setTableView(){
	m_pTable =(CCTableView*)this->getChildByTag(udTABLEVIEW);
	m_pTable->setDataSource(this);
	m_pTable->setDelegate(this);
	m_pTable->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pTable->setTouchEnabled(true);
	m_pTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
	NFC_refreshTableView(m_pTable);	
}

CCSize SecretView::cellSizeForTable(CCTableView *table){
	return m_szCell;
};

CCTableViewCell* SecretView::tableCellAtIndex(CCTableView *table, unsigned int idx){
	CCTableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
		_createTableCell(cell);	
	}
	_setTableCell(cell,idx);
	return cell;
};

unsigned int SecretView::numberOfCellsInTableView(CCTableView *table){
	
	return numberOfCells;//�����ж��ٸ�cell
};


void SecretView::_createTableCell(cocos2d::extension::CCTableViewCell * cell){
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSHOPVIEWCELL,cell);
} 

void SecretView::_setAllCurrencyVisible(cocos2d::extension::CCTableViewCell* cell,bool isible,int blockIdx)
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

void SecretView::_setTableCell(cocos2d::extension::CCTableViewCell* cell,int idx)
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

void SecretView::_showBlock2(cocos2d::CCNode* cell,bool isShow){
	for (int i=udBUY2;i<=udVIEWDEBRIS2;i+=2)
		NFC_showNode(i,cell,isShow);
}

void SecretView::_mapCellBtn(cocos2d::extension::CCTableViewCell* cell,int blockIdx){

	CCMenu* menu=(CCMenu*)cell->getChildByTag(udBUYBTN1+blockIdx%2);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(blockIdx);
	cc->setTarget(this,menu_selector(SecretView::On_Cell_SellEvent));

	DTAwardBoard* dd=(DTAwardBoard*)cell->getChildByTag(udVIEWDEBRIS1+blockIdx%2);
	dd->setIDX(blockIdx);
	dd->setTarget(this,menu_selector(SecretView::On_Cell_ClickEvent));

}

void SecretView::_setCellBlockInfo(cocos2d::extension::CCTableViewCell* cell,int blockIdx)
{
	ShopInfoGoodsData *data = SHOPINFODATAHANDLER->m_ShopGoodsBaselist[blockIdx];

	//�����������
	_setAllCurrencyVisible(cell,false,blockIdx);

	//���ش��ۿ�
	NFC_showNode(udTEXT3+blockIdx%2,cell,false);
	//���ش��ۼ�Ǯ����
	NFC_showNode(udRED1+blockIdx%2,cell,false);
	//�������۴���
	NFC_showNode(udLIMIT1+blockIdx%2,cell,false);
	//���صȼ�����
	NFC_showNode(udLevelDAY1+blockIdx%2,cell,false);
	//����ÿ������
	NFC_showNode(udDAY1+blockIdx%2,cell,false);
	//�ۿ���
	NFC_showNode(udLine1+blockIdx%2,cell,false);
	//���ð�ť�Ƿ��û�
	_setShopBuyEnableBtn(data,cell,blockIdx);
	_setRedText(data,cell,blockIdx);
	//��������Ǯ��
	NFC_setLabelStringInt(udYE1+blockIdx%2,cell,data->price);

	//���û���������ʾ
	_setmoneycell(data,cell,blockIdx);
	//������������
	_setrequireInfo(data,cell,blockIdx);

	//װ������
	NFC_setLabelString(udNAME1+blockIdx%2,cell,data->nameBase.c_str());
	//��Ʒ�ؼ�
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

void SecretView::On_Cell_SellEvent(cocos2d::CCObject* pSender){
	BTN_INTERVAL("SecretView_Sell",_COMMON_BTN_CLICK_INTERVAL_SMALL);
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
			SHOPINFODATAHANDLER->ToServerBuyItemPacket(SHOPINFODATAHANDLER->m_shopId,data->shopItemId,1);
		}
	}
}

void SecretView::On_Cell_ClickEvent(cocos2d::CCObject* pSender){
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int idx  =cc->getIDX();
	ShopInfoGoodsData *data = SHOPINFODATAHANDLER->m_ShopGoodsBaselist[idx];
	_showgoodstips(data);
}

void SecretView::_showgoodstips(ShopInfoGoodsData *data)
{
	SHOPTIPSDATAHANDLER->m_pTips->name_ = data->nameBase;
	SHOPTIPSDATAHANDLER->m_pTips->description_ = data->descriptionBase;
	if (data->discount != -1)
	{
		//����discountMoneyType
		SHOPTIPSDATAHANDLER->m_pTips->price_ = data->discount;
		SHOPTIPSDATAHANDLER->m_pTips->moneytype_ = data->discountMoneyType;
	}
	else
	{
		//������
		SHOPTIPSDATAHANDLER->m_pTips->price_ = data->price;
		SHOPTIPSDATAHANDLER->m_pTips->moneytype_ = data->moneyType;
	}
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_SHOPTIPSWINDOW_);
}

/*
	tips�ص��¼�
*/
void SecretView::cancelTipsLayer(){

}

void SecretView::_enableBtnsCell(bool enabled,CCNode* cell,int blockIdx){
	_enableBtnCell(udBUYBTN1+blockIdx%2,enabled,cell);
	NFC_showNode(udBUYBTNGREY1+blockIdx%2,cell,!enabled);
}

void SecretView::_enableBtnCell(int key,bool enabled,CCNode* cell){
	CCMenu* menu=(CCMenu*)cell->getChildByTag(key);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setEnabled(enabled);
}

void SecretView::HideWaittingLayer()
{
	//NFC_showNode(udColorLayer,this,false);
	//NFC_showNode(udANCOMMON,this,false);
}

void SecretView::_setShopBuyEnableBtn(ShopInfoGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx)
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
		//������
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
			num = m_CurLongxueBlood;
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
		//����
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
			num = m_CurLongxueBlood;
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


void SecretView::_setRedText(ShopInfoGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx)
{
	if (data->discount == -1)
	{
		//������
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
			num = m_CurLongxueBlood;
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
		//����
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
			num = m_CurLongxueBlood;
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

void SecretView::_setmoneycell(ShopInfoGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx)
{
	if (data->moneyType == _TYPE_GOLD_)
	{
		//���ۻ�������
		NFC_showNode(udGOLD1+blockIdx%2,cell,true);
	}
	else if (data->moneyType == _TYPE_JEWEL_)
	{
		//���ۻ�������
		NFC_showNode(udDIAMOND1+blockIdx%2,cell,true);
	}
	else if (data->moneyType == _TYPE_PRESTIGE_)
	{
		//���ۻ�������
		NFC_showNode(udPRESTIGE1+blockIdx%2,cell,true);

	}//�Ի���Ʒ
	else if (data->moneyType == _TYPE_EXCHANGE_ITEM_)
	{
		//���ۻ�������
		NFC_showNode(udLONGXUE1+blockIdx%2,cell,true);
	}

	//����Ǵ���
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
		//���ۿ�
		NFC_showNode(udTEXT3+blockIdx%2,cell,true);
		//���ۼ�Ǯ
		NFC_setLabelStringInt(udRED1+blockIdx%2,cell,data->discount,true);
		//�ۿ���
		NFC_showNode(udLine1+blockIdx%2,cell,true);
	}
}

bool SecretView::onUpdateText()
{
	_setLongXueText();

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

void SecretView::_setrequireInfo(ShopInfoGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx)
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

void SecretView::_setdaylimit(ShopInfoGoodsData *data,cocos2d::extension::CCTableViewCell* cell,int blockIdx)
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

void SecretView::_setLongXueText()
{
	char buffer[128]={0};
	m_CurLongxueBlood = BAGOTHEROBJECTHANDLER->getObjectCountByTemplateId(CLIENTCONSTDATAMANGER->getValueByKey(LONGXUEJINGSHI_TEMPLATEID));
	sprintf(buffer,"%d",m_CurLongxueBlood);
	NFC_setLabelString(udTEXTCOUNTTTF1,this,buffer);
}

void SecretView::_showMoneyText()
{
	NFC_showNode(udBLOODSTONE,this,true);
	NFC_showNode(udTEXTCOUNTTTF1,this,true);
	NFC_showNode(udTEXTBG1,this,true);
}