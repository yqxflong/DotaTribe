// Name :EquipTipsWindow.h
// Function：装备物品tips窗口
// Author : lvyunlong
// Date: 20131016

#include "../include/EquipTipsWindow.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/LoggerSystem.h"
#include "../include/UIViewDataManger.h"
#include "../include/CPublicVarReader.h"
#include "../include/RoleEquipDataHandler.h"
#include "../include/NFControlsManager.h"
#include "../include/SysLangDataManager.h"
#include "../include/IDStringDataManager.h"
#include "../include/EquipmentLvUpDataHandler.h"
#include "../include/PESWindow.h"
#include "../include/CMenuItemSprite.h"
#include "../include/MaskNode.h"
#include "../include/BagEquipDataHandler.h"
#include "../include/MessageBoxWindow.h"
#include "../include/DTEquipBoard.h"
#include "../include/StrengthenWindow.h"
#include "../include/FriendDataHandler.h"
#include "../include/EquipStrengthenDataHandler.h"
using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

EquipTipsWindow::EquipTipsWindow()
:m_pRoot(NULL),
m_idx(0),
m_isEquiped(0),
m_pCompareNode(NULL),
m_pCheckNode(NULL),
m_NeedEquipData(NULL)
{
	m_WindowType = _TYPED_WINDOW_EQUIPTIPSWINDOW_;
	m_bModelWindow = false;
}

EquipTipsWindow::~EquipTipsWindow()
{

}

bool EquipTipsWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_EQUIPTIPSWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_EQUIPTIPSWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_SELL_CALLBACK_EQUIPTIPSWINDOW_, true);
	

	return IWindow::Init();
}

bool EquipTipsWindow::Load()
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

void EquipTipsWindow::Tick()
{
	IWindow::Tick();
}

void EquipTipsWindow::Destroy()
{
	m_pRoot->removeAllChildrenWithCleanup(true);
	m_pCompareNode = NULL;
	m_pCheckNode = NULL;
	m_pOtherNode = NULL;
	m_NeedEquipData = NULL;
	IWindow::Destroy();
}	

void EquipTipsWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if(iEventType == _TYPED_EVENT_SHOW_EQUIPTIPSWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if(iEventType == _TYPED_EVENT_HIDE_EQUIPTIPSWINDOW_)
	{
		Destroy();
	}
	else if(iEventType == _TYPED_EVENT_SELL_CALLBACK_EQUIPTIPSWINDOW_)
	{
		BAGEQUIPDATAHANDLER->saleObject(BAGEQUIPDATAHANDLER->m_BagEquipTipsData->id_, 1);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_EQUIPTIPSWINDOW_);
	}
}

void EquipTipsWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	if(paramList.size() > 1)
	{
		std::list<std::string>::iterator it = paramList.begin();
		std::string stridx = *it++;
		std::string strisequiped = *it++;
		sscanf(stridx.c_str(), "%d", &m_idx);
		sscanf(strisequiped.c_str(), "%d", &m_isEquiped);
		m_nHeroPos=0;
		if (it!=paramList.end())
		{
			std::string strHeroPos=*it++;
			sscanf(strHeroPos.c_str(),"%d",&m_nHeroPos);
		}

		_refreshQeuipInfo();
	}
	Show(true);
}

void EquipTipsWindow::_initLayout()
{
	m_pRoot =m_pRootNode;
	m_pRoot->setAnchorPoint(CCPointZero);
	m_pRoot->setPosition(CCPointZero);
	_initControl();
}

void EquipTipsWindow::_initControl()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kEQUIPTIPSWINDOW,m_pRoot);

	m_pCompareNode = (CCNode*)m_pRoot->getChildByTag(udNodeCompareEquiped);
	m_pCheckNode = (CCNode*)m_pRoot->getChildByTag(udNodeCheckCurEquip);
	m_pOtherNode = (CCNode*)m_pRoot->getChildByTag(udNodeOtherEquip);
	CPriorityLayerColor* p = (CPriorityLayerColor*)m_pRoot->getChildByTag(udMASKCCP);
	p->setDelegate(this);
}

void EquipTipsWindow::_createLabel()
{

}

void EquipTipsWindow::_refreshQeuipInfo()
{

	if (m_isEquiped == kTIPS_BAGEQUIP)
	{
		BagEquipData* bb=BAGEQUIPDATAHANDLER->getEquipById(m_idx);
		if (bb == NULL)
			return;
		_copyBagEquipdata(BAGEQUIPDATAHANDLER->m_BagEquipTipsData, bb);
		//BAGEQUIPDATAHANDLER->m_BagEquipTipsData = bb;
		
		
		int cat=bb->template_->type_;
		std::map<int, RoleEquipData*>::iterator it = NFC_GetHeroEquipManager(EquipStrengthenDataHandler::get_instance2()->m_HeroIndex)->m_mapEquipList.find(cat);
		RoleEquipData* red=it->second;
		if (red==NULL)
			return;
		
		if (red->hasEquip_)
		{
			ShowEquipCompare(red->equipdata_,bb);
		}
		else
		{
			ShowEquip(bb);
		}
	}
	else if(m_isEquiped == kTIPS_ROLEEQUIP)
	{
		BagEquipData* bb =NFC_GetHeroEquipManager(m_nHeroPos)->getEquipById(m_idx);
		if (bb)
		{
			_copyBagEquipdata(BAGEQUIPDATAHANDLER->m_BagEquipTipsData, bb);
			ShowEquip(BAGEQUIPDATAHANDLER->m_BagEquipTipsData);
		}
	}
	else if (m_isEquiped == kTIPS_OTHEREQUIP){
		BagEquipData* bb = NULL;
		std::map<int,BagEquipData*>::iterator it = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.equips.begin();
		std::map<int,BagEquipData*>::iterator end = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.equips.end();
		for(;it != end; it++){
			if( (*it).second->id_ == m_idx ){
				bb = (*it).second;	
				break;
			}
		}
		if(bb){
			_copyBagEquipdata(BAGEQUIPDATAHANDLER->m_BagEquipTipsData, bb);
			ShowEquipOthers(BAGEQUIPDATAHANDLER->m_BagEquipTipsData);
		}
	}
}

void EquipTipsWindow::ShowEquipCompare(BagEquipData* equiped,BagEquipData* dd)
{
	MaskNode* node = (MaskNode*)NFC_getNode(udMaskNode,m_pRoot);
	float comparepos = node->GetViewData().width_;
	float checkpos = node->GetViewData().height_;
	m_pCompareNode->setPositionX(comparepos);
	m_pCheckNode->setPositionX(checkpos);

	_initCompareEquipedNode(equiped);
	_initCheckEquipNode(dd);
}

void EquipTipsWindow::ShowEquip(BagEquipData* dd)
{
	_initCheckEquipNode(dd);
}

void EquipTipsWindow::ShowEquipOthers(BagEquipData* dd){
	_initOtherEquipNode(dd);
}

void EquipTipsWindow::_initCompareEquipedNode(BagEquipData* equiped,bool isCompare)
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kEQUIPCOMPARE,m_pCompareNode);
	_fillLocalAtrributeMap(equiped,isCompare);
	_createLabels(equiped,isCompare);
}
void EquipTipsWindow::_initCheckEquipNode(BagEquipData* equip,bool isCompare)
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kEQUIPTIPS,m_pCheckNode);
	m_nEquipID = equip->id_;
	_mapBtn();
	_fillLocalAtrributeMap(equip,isCompare);
	_createLabels(equip,isCompare);
}

void EquipTipsWindow::_initOtherEquipNode(BagEquipData* equip, bool isCompare){

	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kEQUIPTIPS,m_pCheckNode);
	m_nEquipID = equip->id_;

	CCMenu* menu=(CCMenu*)m_pCheckNode->getChildByTag(EudSELLBTN);
	menu->setVisible(false);

	menu=(CCMenu*)m_pCheckNode->getChildByTag(EudEQUIPBTN);
	menu->setVisible(false);

	menu=(CCMenu*)m_pCheckNode->getChildByTag(EudCLOSEBTN);
	CCMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setTarget(this,menu_selector(EquipTipsWindow::On_Check_Close_Event));

	menu=(CCMenu*)m_pCheckNode->getChildByTag(EudDISBOARDBTN);
	menu->setVisible(false);


	_fillLocalAtrributeMap(equip,isCompare);
	_createLabels(equip,isCompare);

	m_pRoot->setZOrder(100);
}

void EquipTipsWindow::_copyBagEquipdata(BagEquipData*& data, BagEquipData* dd)
{
	data->advanceLevel_ = dd->advanceLevel_;
	data->advanceLevelMax_ = dd->advanceLevelMax_;
	data->attribute_ = dd->attribute_;
	data->attributeMAX_ = dd->attributeMAX_;
	data->equipScore_ = dd->equipScore_;
	data->exp_ = dd->exp_;
	data->id_ = dd->id_;
	data->index_ = dd->index_;
	data->isEquiped_ = dd->isEquiped_;
	data->itemcount_ = dd->itemcount_;
	data->level_ = dd->level_;
	data->levelMax_ = dd->levelMax_;
	data->mainAttriValue = dd->mainAttriValue;
	data->mainAttriValueMax = dd->mainAttriValueMax;
	data->maxexp_ = dd->maxexp_;
	data->RoleHeroindexEquip_ = dd->advanceLevel_;
	data->template_->iconId_ = dd->template_->iconId_;
	data->template_->quality_ = dd->template_->quality_;
	data->template_->type_ = dd->template_->type_;
	data->template_->price_ = dd->template_->price_;
	data->template_->name_ = dd->template_->name_;
	data->template_->baseAttrType_ = dd->template_->baseAttrType_;

}

void EquipTipsWindow::_mapBtn()
{
	CCMenu* menu=(CCMenu*)m_pCheckNode->getChildByTag(EudSELLBTN);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setTarget(this,menu_selector(EquipTipsWindow::On_Check_Sell_Event));

	menu=(CCMenu*)m_pCheckNode->getChildByTag(EudEQUIPBTN);
	cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setTarget(this,menu_selector(EquipTipsWindow::On_Check_Equip_Event));

	menu=(CCMenu*)m_pCheckNode->getChildByTag(EudCLOSEBTN);
	cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setTarget(this,menu_selector(EquipTipsWindow::On_Check_Close_Event));

	menu=(CCMenu*)m_pCheckNode->getChildByTag(EudDISBOARDBTN);
	cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setTarget(this,menu_selector(EquipTipsWindow::On_Check_Disboard_Event));

	if (m_isEquiped == kTIPS_ROLEEQUIP)
	{
		NFC_setNodeVisable(EudSELLBTN,m_pCheckNode,false);
		NFC_setNodeVisable(EudSELLLB,m_pCheckNode,false);
		NFC_setNodeVisable(EudEQUIPBTN,m_pCheckNode,false);
		NFC_setNodeVisable(EudEQUIPBTNLB,m_pCheckNode,false);
		NFC_setNodeVisable(EudDISBOARDBTN,m_pCheckNode,true);
		NFC_setNodeVisable(EudDISBOARDLB,m_pCheckNode,true);
	}
	else
	{
		NFC_setNodeVisable(EudSELLBTN,m_pCheckNode,true);
		NFC_setNodeVisable(EudSELLLB,m_pCheckNode,true);
		NFC_setNodeVisable(EudEQUIPBTN,m_pCheckNode,true);
		NFC_setNodeVisable(EudEQUIPBTNLB,m_pCheckNode,true);
		NFC_setNodeVisable(EudPRICEVALUE,m_pCheckNode,true);
		NFC_setNodeVisable(EudPRICEICON,m_pCheckNode,true);
		NFC_setNodeVisable(EudPRICETEXT,m_pCheckNode,true);

		NFC_setNodeVisable(EudDISBOARDBTN,m_pCheckNode,false);
		NFC_setNodeVisable(EudDISBOARDLB,m_pCheckNode,false);
	}
}

void EquipTipsWindow::On_Check_Sell_Event(cocos2d::CCObject* pSender)
{
	//出售
// 	BagEquipData* bb = BAGEQUIPDATAHANDLER->getEquipById(m_idx);
// 	if (bb == NULL)
// 	{
// 		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_EQUIPTIPSWINDOW_);
// 		return;
// 	}
	if (BAGEQUIPDATAHANDLER->m_BagEquipTipsData->template_->quality_ >= 3)
	{
		NFC_showMessageBox(kEQUIPTIPSSELL,SysLangDataManager::get_instance2()->GetSysLangById(686));
	}
	else
	{
		BAGEQUIPDATAHANDLER->saleObject(BAGEQUIPDATAHANDLER->m_BagEquipTipsData->id_, 1);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_EQUIPTIPSWINDOW_);
	}
}
/*
	装备按钮
*/
void EquipTipsWindow::On_Check_Equip_Event(cocos2d::CCObject* pSender)
{
	//装备
// 	BagEquipData* bb = BAGEQUIPDATAHANDLER->getEquipById(m_idx);
// 	if (bb == NULL)
// 	{
// 		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_EQUIPTIPSWINDOW_);
// 		return;
// 	}
	int idx = BAGEQUIPDATAHANDLER->m_BagEquipTipsData->id_;
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_PESEQUIPSUBVIEW_TIPS_CALLBACK_EQUIP,_to_event_param_(idx));
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_EQUIPTIPSWINDOW_);
}
/*
	关闭按钮
*/
void EquipTipsWindow::On_Check_Close_Event(cocos2d::CCObject* pSender)
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_EQUIPTIPSWINDOW_);
}

void EquipTipsWindow::On_Check_Disboard_Event(cocos2d::CCObject* pSender)
{
	//卸下
	int type = BAGEQUIPDATAHANDLER->m_BagEquipTipsData->template_->type_;
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_PESEQUIPSUBVIEW_TIPS_CALLBACK_DISBOARD,_to_event_param_(type));
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_EQUIPTIPSWINDOW_);
	
}

void EquipTipsWindow::_fillLocalAtrributeMap(BagEquipData* dd,bool isCompare)
{
	if (isCompare)
	{
		m_ComparemapAttribute=dd->attribute_->mapPropertyList_;
		m_ComparemapAttributeMAX=dd->attributeMAX_->mapPropertyList_;
		m_nCompareMainAttribute=dd->mainAttriValue;
		m_nCompareMainAttributeMax=dd->mainAttriValueMax;
	}
	else
	{
		m_mapAttribute=dd->attribute_->mapPropertyList_;
		m_mapAttributeMAX=dd->attributeMAX_->mapPropertyList_;
		m_nMainAttribute=dd->mainAttriValue;
		m_nMainAttributeMax=dd->mainAttriValueMax;
	}
}

void EquipTipsWindow::_createLabels(BagEquipData* data,bool isCompare)
{
	_createNAME(data, isCompare);
	_createEquiptype(data,isCompare);
	_createEquipInfo(data,isCompare);
	_createPrice(data,isCompare);
	_createBASIC(data, isCompare);
	_createBASICVALUE(data, isCompare);
	if (isCompare)
	{
		map<int,int>::iterator it=m_ComparemapAttribute.begin();
		map<int,int>::iterator it_end=m_ComparemapAttribute.end();
		int udEnum=udEATTACH1;
		for(;it!=it_end;it++){
			_createATT(it->first,udEnum,isCompare);
			_createATTValue(it->first,it->second,udEnum+1,isCompare);
			udEnum+=2;
		}
	}
	else
	{
		map<int,int>::iterator it=m_mapAttribute.begin();
		map<int,int>::iterator it_end=m_mapAttribute.end();
		int udEnum=EudEATTACH1;
		for(;it!=it_end;it++){
			_createATT(it->first,udEnum,isCompare);
			_createATTValue(it->first,it->second,udEnum+1,isCompare);
			udEnum+=2;
		}
	}
	
}

void EquipTipsWindow::_createNAME(BagEquipData* data,bool isCompare){
	if (isCompare)
	{
		//设置装备名字+进阶级别
		if(data->advanceLevel_>0){
			char tmp[128]="";
			string sys=SysLangDataManager::get_instance2()->GetSysLangById(761);
			sprintf(tmp,sys.c_str(),data->template_->name_.c_str(),data->advanceLevel_);
			NFC_setLabelString(udName,m_pCompareNode,tmp);
		}else{
			NFC_setLabelString(udName,m_pCompareNode,data->template_->name_);
		}
	}
	else
	{
		//设置装备名字+进阶级别
		if(data->advanceLevel_>0){
			char tmp[128]="";
			string sys=SysLangDataManager::get_instance2()->GetSysLangById(761);
			sprintf(tmp,sys.c_str(),data->template_->name_.c_str(),data->advanceLevel_);
			NFC_setLabelString(EudName,m_pCheckNode,tmp);
		}else{
			NFC_setLabelString(EudName,m_pCheckNode,data->template_->name_);
		}
	}
}


void EquipTipsWindow::_createPrice(BagEquipData* data,bool isCompare)
{
	if (isCompare)
	{
		CCLabelTTF* ttf = (CCLabelTTF*)NFC_getNode(udPRICEVALUE,m_pCompareNode);
		char tmp[64] = {0};
		sprintf(tmp,"%d",data->template_->price_);
		ttf->setString(tmp);
		std::string str = tmp;
		int i  = str.length();
		CCSprite* icon = (CCSprite*)NFC_getNode(udPRICEICON,m_pCompareNode);
		icon->setPositionX(icon->getPositionX()+i*10);
	}
	else
	{
		CCLabelTTF* ttf = (CCLabelTTF*)NFC_getNode(EudPRICEVALUE,m_pCheckNode);
		char tmp[64] = {0};
		sprintf(tmp,"%d",data->template_->price_);
		ttf->setString(tmp);
		std::string str = tmp;
		int i  = str.length();
		CCSprite* icon = (CCSprite*)NFC_getNode(EudPRICEICON,m_pCheckNode);
		icon->setPositionX(icon->getPositionX()+i*10);
	}
}

void EquipTipsWindow::_createEquiptype(BagEquipData* data,bool isCompare){
	if (isCompare)
	{
		std::string str = NFC_getIDStringFromTag(1,data->template_->type_);
		NFC_setLabelString(udEquiptype,m_pCompareNode,str.c_str());
	}
	else
	{
		std::string str = NFC_getIDStringFromTag(1,data->template_->type_);
		NFC_setLabelString(EudEquiptype,m_pCheckNode,str.c_str());
	}
}

void EquipTipsWindow::_createEquipInfo(BagEquipData* data,bool isCompare)
{
	if (isCompare)
	{
		DTEquipBoard* cc=(DTEquipBoard*)NFC_getNode(udEQUIPBOAD,m_pCompareNode);
		cc->SetEquip(kHETYPE_ELIST,data,NULL);
	}
	else
	{
		DTEquipBoard* cc=(DTEquipBoard*)NFC_getNode(EudEQUIPBOAD,m_pCheckNode);
		cc->SetEquip(kHETYPE_ELIST,data,NULL);
	}
}


void EquipTipsWindow::_createBASIC(BagEquipData* data,bool isCompare){

	if (isCompare)
	{
		CCLabelTTF* cc = (CCLabelTTF*)NFC_getNode(udEBASIC,m_pCompareNode);
		unsigned char mptype=data->template_->baseAttrType_;
		if (mptype==kMINATTACK)
		{//主属性是攻击力	
			NFC_setLabelString(udEBASIC,m_pCompareNode,SysLangDataManager::get_instance2()->GetSysLangById(207).c_str());
		}
		else{
			string str=IDSTRINGDATAMANAGER->GetIDStringByID(3,mptype);
			NFC_setLabelString(udEBASIC,m_pCompareNode,str.c_str());
		}
	}
	else
	{
		CCLabelTTF* cc = (CCLabelTTF*)NFC_getNode(EudEBASIC,m_pCheckNode);
		unsigned char mptype=data->template_->baseAttrType_;
		if (mptype==kMINATTACK)
		{//主属性是攻击力	
			NFC_setLabelString(EudEBASIC,m_pCheckNode,SysLangDataManager::get_instance2()->GetSysLangById(207).c_str());
		}
		else{
			string str=IDSTRINGDATAMANAGER->GetIDStringByID(3,mptype);
			NFC_setLabelString(EudEBASIC,m_pCheckNode,str.c_str());
		}
	}
}
void EquipTipsWindow::_createBASICVALUE(BagEquipData* data,bool isCompare){

	if (isCompare)
	{

		CCLabelTTF* cc = (CCLabelTTF*)NFC_getNode(udEBVALUE,m_pCompareNode);
		char tmp[32]={0};
		unsigned char mptype=data->template_->baseAttrType_;
		if (mptype==kMINATTACK){//主属性是攻击力
			sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(225).c_str(),m_nCompareMainAttribute,m_nCompareMainAttributeMax);
		}else{
			sprintf(tmp,"%d",m_nCompareMainAttribute);
		}
		cc->setString(tmp);
	}
	else
	{

		CCLabelTTF* cc = (CCLabelTTF*)NFC_getNode(EudEBVALUE,m_pCheckNode);
		char tmp[32]={0};
		unsigned char mptype=data->template_->baseAttrType_;
		if (mptype==kMINATTACK){//主属性是攻击力
			sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(225).c_str(),m_nMainAttribute,m_nMainAttributeMax);
		}else{
			sprintf(tmp,"%d",m_nMainAttribute);
		}
		cc->setString(tmp);
	}

}

void EquipTipsWindow::_createATT(int key,int udEnum,bool isCompare){

	if (isCompare)
	{
		CCLabelTTF* ttf = (CCLabelTTF*)NFC_getNode(udEnum,m_pCompareNode);
		string str=IDSTRINGDATAMANAGER->GetIDStringByID(3,key);		ttf->setString(str.c_str());
	}
	else
	{
		CCLabelTTF* ttf = (CCLabelTTF*)NFC_getNode(udEnum,m_pCheckNode);
		string str=IDSTRINGDATAMANAGER->GetIDStringByID(3,key);		ttf->setString(str.c_str());
	}

	
}

void EquipTipsWindow::_createATTValue(int key,int val,int udEnum,bool isCompare){
	if (isCompare)
	{
		CCLabelTTF* ttf = (CCLabelTTF*)NFC_getNode(udEnum,m_pCompareNode);
		char tmp[32]={0};
		sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(226).c_str(),val,m_ComparemapAttributeMAX[key]);
		ttf->setString(tmp);
		_setColorATTValue(val,m_ComparemapAttributeMAX[key],ttf);
	}
	else
	{
		CCLabelTTF* ttf = (CCLabelTTF*)NFC_getNode(udEnum,m_pCheckNode);
		char tmp[32]={0};
		sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(226).c_str(),val,m_mapAttributeMAX[key]);
		ttf->setString(tmp);
		_setColorATTValue(val,m_mapAttributeMAX[key],ttf);
	}
}

/*
	CPriorityLayerColor Delegate
*/
void EquipTipsWindow::touchEvent(CPriorityLayerColor* pLayerColor)
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_EQUIPTIPSWINDOW_);
}

void EquipTipsWindow::_setColorATTValue(int curval,int maxval,CCLabelTTF* ttf)
{
	FSData * dd = NULL; 
	int xf = 100 * ((float)curval / maxval);
	if(xf < 60) 
	{//绿??色?? 
		dd = FONTSTYLEDATAMANAGER->getDataByID(92); 
	} 
	else if(xf >= 60 && xf < 80) 
	{//蓝??色?? 
		dd = FONTSTYLEDATAMANAGER->getDataByID(93); 
	} 
	else if(xf >= 80 && xf < 100) 
	{//紫??色?? 
		dd = FONTSTYLEDATAMANAGER->getDataByID(94); 
	} 
	else if(xf == 100) 
	{//橙??色?? 
		dd = FONTSTYLEDATAMANAGER->getDataByID(95); 
	}
	NFC_setLabelColor(ttf,ccc3(dd->colorR_,dd->colorG_,dd->colorB_));
}

