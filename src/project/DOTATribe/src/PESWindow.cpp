//Name：PESWindow
//Function：英雄相关
//Written By：尹强

#include <cocos2d.h>
#include "../include/PESWindow.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/PESEquipSubView.h"
#include "../include/PESoulEquipSubView.h"
#include "../include/UIViewDataManger.h"
#include "../include/NFControlsManager.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/RoleEquipDataHandler.h"



using namespace std;

USING_NS_CC;

PESWindow::PESWindow()
:m_pSubView(0)
,m_nBackWindowType(-1)
,m_CurTabId(-1)
, m_TypeView(-1)
{
	m_WindowType   = _TYPED_WINDOW_PESWINDOW_;
	m_WindowZOrder = _TYPED_WINDOW_ZORDER_NORMAL_;
}

bool PESWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_PESWINDOW_);
	RegisterEvent(_TYPED_EVENT_FADEIN_PESWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_PESWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_PESWINDOW_, true);
	//begin:HeroEquip
	RegisterEvent(_TYPED_EVENT_PESEQUIPSUBVIEW_ROLEEQUIP_REFRESH,true);
	RegisterEvent(_TYPED_EVENT_PESEQUIPSUBVIEW_EQUIPLIST_REFRESH,true);
	//end
	//begin:EquipTips
	RegisterEvent(_TYPED_EVENT_PESEQUIPSUBVIEW_TIPS_CALLBACK_EQUIP,true);
	RegisterEvent(_TYPED_EVENT_PESEQUIPSUBVIEW_TIPS_CALLBACK_DISBOARD,true);
	//end
	//begin:RoleInfoNode
	RegisterEvent(_TYPED_EVENT_HEROWINDOW_ROLEINFO_LEADERSHIP_LVUP,true);
	RegisterEvent(_TYPED_EVENT_REFRESH_UPDATEUI_,true);
	RegisterEvent(_TYPED_EVENT_UPDATE_HEROSOUL_VIEW_,true);
	//end
	return IWindow::Init();
}

bool PESWindow::Load()
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

void PESWindow::Tick()
{
	IWindow::Tick();
	if (m_pSubView)
		m_pSubView->onTick();
}

void PESWindow::Destroy()
{
	if (m_pSubView)
	{
		m_pSubView->onDestroy();
		m_pSubView=NULL;
	}
	m_pRootNode->removeAllChildrenWithCleanup(true);
	IWindow::Destroy();
}

void PESWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_PESWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if(iEventType == _TYPED_EVENT_FADEIN_PESWINDOW_){
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_PESWINDOW_)
	{
		Destroy();
	}else if(iEventType==_TYPED_EVENT_PESEQUIPSUBVIEW_ROLEEQUIP_REFRESH){
		On_Refresh_HeroEquipView(0);
	}else if(iEventType==_TYPED_EVENT_PESEQUIPSUBVIEW_EQUIPLIST_REFRESH){
		On_Refresh_HeroEquipView(1);
	}
	else if(iEventType==_TYPED_EVENT_PESEQUIPSUBVIEW_TIPS_CALLBACK_EQUIP){
		On_Tips_Callback_Equip(paramList);
	}
	else if(iEventType==_TYPED_EVENT_PESEQUIPSUBVIEW_TIPS_CALLBACK_DISBOARD){
		On_Tips_Callback_Disboard(paramList);
	}else if(iEventType==_TYPED_EVENT_HEROWINDOW_ROLEINFO_LEADERSHIP_LVUP){
		if (m_pSubView)
			m_pSubView->EventWindowCallBack(iEventType,paramList);
	}else if(iEventType==_TYPED_EVENT_REFRESH_UPDATEUI_){
		if (m_pSubView)
			m_pSubView->EventWindowCallBack(iEventType,paramList);
	}else if(iEventType == _TYPED_EVENT_UPDATE_HEROSOUL_VIEW_)
	{
		if (m_pSubView)
			m_pSubView->EventWindowCallBack(iEventType,paramList);
	}


}

void PESWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
	list<string>::iterator it=paramList.begin();
	string tmp;
	int ntabNum = 0;
	//第一个参数为子界面
	if (paramList.size()>0){
		tmp=*it++;
		ntabNum=atoi(tmp.c_str());
		ntabNum = (ntabNum - kTAB_1) / 2;
		if (paramList.size()>1){
			tmp = *it++;
			m_TypeView = atoi(tmp.c_str());
			if (m_TypeView == LOAD_EQUIP_VIEW)
			{
				_loadHeroEquipView();
			}
			else if (m_TypeView == LOAD_SOUL_VIEW)
			{
				_loadSoulView();
			}
			else
			{
				_loadHeroEquipView();
			}
		}
		if (paramList.size() > 2){
			tmp = *it++;
			m_nBackWindowType = atoi(tmp.c_str());
		}
		_selectTabItem(ntabNum);
	}else
		_selectTabItem(0);
}

	/*
		刷新英雄装备界面
	*/
void PESWindow::On_Refresh_HeroEquipView(int type){
	if(typeid(* m_pSubView) == typeid(PESEquipSubView)){
		PESEquipSubView* cc=(PESEquipSubView*)m_pSubView;
		if (type==0)
			cc->On_RefreshRoleEquip();
		else if(type==1)
			cc->On_RefreshEquipList();
	}
}

void PESWindow::On_Tips_Callback_Equip(std::list<std::string>& paramList)
{
	if(typeid(* m_pSubView) == typeid(PESEquipSubView))
	{
		std::list<std::string>::iterator it=paramList.begin();
		std::string tmp;
		if (paramList.size()>0){
			tmp=*it++;
		}
		int idx=atoi(tmp.c_str());
		PESEquipSubView* cc=(PESEquipSubView*)m_pSubView;
		cc->On_Tips_CallBack_Equip(idx);
	}
}

void PESWindow::On_Tips_Callback_Disboard(std::list<std::string>& paramList)
{
	if(typeid(* m_pSubView) == typeid(PESEquipSubView))
	{
		std::list<std::string>::iterator it=paramList.begin();
		std::string tmp;
		if (paramList.size()>0){
			tmp=*it++;
		}
		int type=atoi(tmp.c_str());
		PESEquipSubView* cc=(PESEquipSubView*)m_pSubView;
		cc->On_Tips_CallBack_Disboard(type);
	}
}

void PESWindow::_initLayout(){
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kHEROWINDOW,m_pRootNode);
	_mapTitle();
	_mapBtn();
	//_loadHeroEquipView();
	//_selectTabItem(kTAB_1);
}

void PESWindow::_mapTitle(){
	for(int i=0;i<3;i++){
		CCLabelTTF* cc=(CCLabelTTF*)NFC_getNode(kTAB_1_TL+2*i,m_pRootNode);
		string s1=cc->getString();
		char tmp[64]="";
		sprintf(tmp,"%d",i+1);
		string s2=tmp;
		string ss=s1+s2;
		cc->setString(ss.c_str());
	}
}

void PESWindow::_mapBtn(){
	CMenuItemSprite* cc=NULL;
	//close btn
	cc=(CMenuItemSprite*)NFC_getMenuItem(kCLOSE,m_pRootNode);
	cc->setIDX(kCLOSE);
	cc->setTarget(this,menu_selector(PESWindow::On_Click_Event));
	//help btn
	cc=(CMenuItemSprite*)NFC_getMenuItem(kHELP,m_pRootNode);
	cc->setIDX(kHELP);
	cc->setTarget(this,menu_selector(PESWindow::On_Click_Event));

	//kTab
	for (int i=kTAB_1;i<=kTAB_3;i+=2)
	{
		cc=(CMenuItemSprite*)NFC_getMenuItem(i,m_pRootNode);
		cc->setIDX(i);
		cc->setTarget(this,menu_selector(PESWindow::On_Tab_Selected));
	}
	//soulbtn
	cc=(CMenuItemSprite*)NFC_getMenuItem(kBTN_SOUL,m_pRootNode);
	cc->setIDX(kBTN_SOUL);
	cc->setTarget(this,menu_selector(PESWindow::On_Click_Event)); 

}

//点亮页签
void PESWindow::_highlightTabItem(unsigned int idx){
	CMenuItemSprite* cc=NULL;
	for (int i=kTAB_1;i<=kTAB_3;i+=2)
	{
		cc=(CMenuItemSprite*)NFC_getMenuItem(i,m_pRootNode);
		cc->unselected();
	}
	cc = (CMenuItemSprite*)NFC_getMenuItem(kTAB_1+idx*2, m_pRootNode);
	cc->selected(true);
}

//选中某个标签
void PESWindow::_selectTabItem(unsigned int idx){
	if (!NFC_HasTeamHero(idx))
	{
		NFC_showErrorTips(SysLangDataManager::get_instance2()->GetSysLangById(6090));
		return;
	}
	m_CurTabId = idx;
	_highlightTabItem(idx);
	m_pSubView->onChangeTabIndex(idx);
}

void PESWindow::On_Click_Event(cocos2d::CCObject* pSender){
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int idx=cc->getIDX();
	if (idx==kCLOSE)
	{
		if (m_nBackWindowType<0)
		{
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
		}else{
			EVENTSYSTEM->PushEvent(m_nBackWindowType);
			m_nBackWindowType=-1;
		}
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_PESWINDOW_);
	}else if(idx==kHELP){
		char type[128] = "";
		if (typeid(*m_pSubView)==typeid(PESEquipSubView))
		{
			sprintf(type,"%d",UIViewDataManager::kEQUIPMENT_HELP_);
		}
		else if (typeid(*m_pSubView) == typeid(PESoulEquipSubView))
		{
			sprintf(type, "%d", UIViewDataManager::kEQUIPMENT_HELP_);
		}
		PushEvent(_TYPED_EVENT_SHOW_HELPWINDOW_,type);
	}else if(idx==kBTN_SOUL){
		if(typeid(*m_pSubView)==typeid(PESoulEquipSubView)){//in战魂界面
			_loadHeroEquipView();
			_selectTabItem(m_CurTabId);
		}else{//in装备界面
			_loadSoulView();
			_selectTabItem(m_CurTabId);
		}
	}
}


void PESWindow::On_Tab_Selected(cocos2d::CCObject* pSender){
	CMenuItemSprite * pMenuItemSprite =(CMenuItemSprite *)pSender;
	if(pMenuItemSprite)
	{
		int idx=pMenuItemSprite->getIDX();
		idx = (idx - kTAB_1) / 2;
		_selectTabItem(idx);
	} 
}

//@载入装备和战魂界面
void PESWindow::_loadHeroEquipView(int tabidx){
	if (m_pSubView){
		m_pSubView->onDestroy();
	}
	m_pSubView=new PESEquipSubView();
	m_pRootNode->addChild(m_pSubView,10);
	m_pSubView->onLoad();
	NFC_setNodeVisable(kHELP,m_pRootNode,true);
	_changeSoulBtnTitle(false);
}

void PESWindow::_loadSoulView(int tabidx){
	if(_isSoulFuncOpen()){
		if (m_pSubView){
			m_pSubView->onDestroy();
		}
		m_pSubView=new PESoulEquipSubView();
		m_pRootNode->addChild(m_pSubView,10);
		m_pSubView->onLoad();
		NFC_setNodeVisable(kHELP,m_pRootNode,false);
		_changeSoulBtnTitle(true);
	}
}

//@检查战魂是否开启
bool PESWindow::_isSoulFuncOpen(){
	int  heroSoulOpenLevel = ClientConstDataManager::get_instance2()->getValueByKey(HEROSOUL_OPEN_LEVEL);
	if(RoleInfoDataHandler::get_instance2()->m_pRIData->level_ < heroSoulOpenLevel)
	{ 
		char commonStr[128]={0};
		std::string advanceTips=SysLangDataManager::get_instance2()->GetSysLangById(_COMMON_LESS_LEVEL_TIPS_);
		sprintf(commonStr,advanceTips.c_str(),heroSoulOpenLevel);
		NFC_showMessageBoxSingle(kDEFAULT,commonStr);
		return false;
	}
	return true;
}

//@更改战魂按钮标题
void PESWindow::_changeSoulBtnTitle(bool isSoul){
	CCLabelTTF* cc=(CCLabelTTF*)NFC_getNode(kBTN_SOUL_TITLE,m_pRootNode);
	if (isSoul)
		cc->setString(SysLangDataManager::get_instance2()->GetSysLangById(1213).c_str());
	else
		cc->setString(SysLangDataManager::get_instance2()->GetSysLangById(223).c_str());
}