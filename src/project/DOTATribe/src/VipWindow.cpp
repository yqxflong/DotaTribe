// Name : VipWindow.h
// Function:Vip窗口
// Author : lvyunlong
// Date: 20131125

#include "../include/VipWindow.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/LoggerSystem.h"
#include "../include/IAPSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/UIViewDataManger.h"
#include "../include/CPublicVarReader.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/CMenuItemSprite.h"
#include "../include/NFControlsManager.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/VipFontDataManager.h"
#include "../include/FontStyleDataManager.h"
#include "../include/SysLangDataManager.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/CProgressInnerBar.h"
#include "../include/VipControlDataHandler.h"
#include "../include/ActivityDataHandler.h"
using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

VipWindow::VipWindow()
:m_pRoot(NULL),
m_pVipNode(NULL),
m_Layerview(NULL),
m_ScrollView(NULL),
m_CurVipPage(0)
{
	m_WindowType = _TYPED_WINDOW_VIP_WINDOW_;
	m_bModelWindow = true;
}

VipWindow::~VipWindow()
{

}

bool VipWindow::Init()
{	
	RegisterEvent(_TYPED_EVENT_SHOW_VIPWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_VIPWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_VIPWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_VIPGIFTWINDOW_, true);	
	RegisterEvent(_TYPED_EVENT_BACKQA_VIPGIFTWINDOW_, true);
	return IWindow::Init();
}

bool VipWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		_initLayout();
		VIPCONTROLDATAHANDLER->ToServerVIPInfo();
		VIPGIFTACTIVITYHANDLER->ToServerInfoVipGift();
		return true;
	}
	while (false);

	return false;
}

void VipWindow::Tick()
{
	IWindow::Tick();
}

void VipWindow::Destroy()
{
	m_CurVipPage = 0;
	if (m_Layerview != NULL)
		m_Layerview->removeAllChildrenWithCleanup(true);
	m_Layerview = NULL;
	if (m_pVipNode != NULL)
		m_pVipNode->removeAllChildrenWithCleanup(true);
	m_pVipNode = NULL;
	IWindow::Destroy();
}

void VipWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if(iEventType == _TYPED_EVENT_SHOW_VIPWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
		//Fadein(IWINDOW_FADEIN_DURING);
	}
	else if(iEventType == _TYPED_EVENT_HIDE_VIPWINDOW_)
	{
		OnHideWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_VIPWINDOW_)
	{
		OnUpdateWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_VIPGIFTWINDOW_)
	{
		OnUpdateGiftWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_BACKQA_VIPGIFTWINDOW_)
	{
		OnBackQAWindowEventHandler(paramList);
	}
}


void VipWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
	//DOTATribeApp::get_instance2()->ClearAllVisibleWindow(_TYPED_WINDOW_VIP_WINDOW_);
	EVENTSYSTEM->PushEvent2(_TYPED_EVENT_HIDE_HOMEWINDOW_);
	EVENTSYSTEM->PushEvent2(_TYPED_EVENT_HIDE_ROLESTATUSWINDOW_);
	EVENTSYSTEM->PushEvent2(_TYPED_EVENT_HIDE_CHATWINDOW_);
}

void VipWindow::OnHideWindowEventHandler(std::list<std::string>& paramList)
{
	//Fadeout(IWINDOW_FADEOUT_DURING);
	Destroy();
}

void VipWindow::OnUpdateWindowEventHandler(std::list<std::string>& paramList)
{
	if (paramList.size()>0)
	{
		//领取成功
		NFC_setEnabledForMenuItem(udVIPREWARDBTN,m_pVipNode,false);
		NFC_setNodeVisable(udEFFECT1,m_pVipNode,false);
		return;
	}

	//NFC_setNodeVisable(udPRIORITYLAYERBIG,m_pVipNode,false);
	//NFC_setNodeVisable(udSCENEEFFECT,m_pVipNode,false);
	_setText();
	_setExp();
	if (!VIPCONTROLDATAHANDLER->m_isBGetReward)
	{
		NFC_setEnabledForMenuItem(udVIPREWARDBTN,m_pVipNode,true);
		if (ROLEINFODATAHANDLER->m_pRIData->vipLevel_ == 0)
			NFC_setNodeVisable(udEFFECT1,m_pVipNode,false);
		else
			NFC_setNodeVisable(udEFFECT1,m_pVipNode,true);
		
	}
	else
	{
		NFC_setEnabledForMenuItem(udVIPREWARDBTN,m_pVipNode,false);
		NFC_setNodeVisable(udEFFECT1,m_pVipNode,false);
	}
}

void VipWindow::OnUpdateGiftWindowEventHandler(std::list<std::string>& paramList)
{
	_setVipGift(m_CurVipPage);
}

void VipWindow::OnBackQAWindowEventHandler(std::list<std::string>& paramList)
{
	VIPGIFTACTIVITYHANDLER->BuyGift(m_CurVipPage);
}


void VipWindow::_initLayout()
{
	m_pRoot =m_pRootNode;
	m_pRoot->setAnchorPoint(CCPointZero);
	m_pRoot->setPosition(CCPointZero);
	m_pVipNode = CCNode::create();
	m_pVipNode->setAnchorPoint(CCPointZero);
	m_pVipNode->setPosition(CCPointZero);
	m_pRoot->addChild(m_pVipNode,10);
	_initControl();
	m_ScrollView = (CScrollView*)NFC_getNode(udSECROLLVIEW,m_pVipNode);
	m_Layerview = CCLayer::create();
	m_Layerview->setPosition(CCPointZero);
	m_Layerview->setAnchorPoint(CCPointZero);
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kVIPVIEWLAYER,m_Layerview);
	m_ScrollView->addText(m_Layerview);
	if (ROLEINFODATAHANDLER->m_pRIData->vipLevel_ == 10)
		m_CurVipPage = 10;
	else
		m_CurVipPage = ROLEINFODATAHANDLER->m_pRIData->vipLevel_ + 1;

	SetfontByViplevel(m_CurVipPage);
	_mapBtn();
}


void VipWindow::_initControl()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kVIPVIEW,m_pVipNode);
}

void VipWindow::setFontAllVisble(bool isvisble)
{
	for (int i = udVIPFONTTTF0;i<=udVIPFONTTTF19;i++)
	{
		NFC_showNode(i,m_Layerview,isvisble);
	}
}

void VipWindow::SetfontByViplevel(int level)
{
	setFontAllVisble(false);
	//设置当前特权显示
	char buff[64]={0};
	sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(910).c_str(),level);
	NFC_setLabelString(udPRIVILEGETEXT,m_pVipNode,buff);
	memset(buff,0,sizeof(buff));
	sprintf(buff,"%d/%d",level,10);
	NFC_setLabelString(udCURPAGETEXT,m_pVipNode,buff);
	std::vector<VipFontData*> vec = VIPFONTMANAGER->getDataByID(level);
	int leng = vec.size();
	if (leng > 7)
		NFC_showNode(udPRIORITYlAYER,m_pVipNode,false);
	else
		NFC_showNode(udPRIORITYlAYER,m_pVipNode,true);
	
	m_Layerview->setContentSize(CCSizeMake(800,35*(leng)));
	for (int i=0;i<leng;i++)
	{
		CCLabelTTF* ttf = (CCLabelTTF*)m_Layerview->getChildByTag(i);
		ttf->setVisible(true);
		VipFontData* data = VIPFONTMANAGER->getVipFontData(level,i);
		FSData* pFdata = FONTSTYLEDATAMANAGER->getDataByID(data->fsyleid_);
		ttf->setFontName(pFdata->fontname_);
		ttf->setFontSize(pFdata->fontsize_);
		ttf->setColor(ccc3(pFdata->colorR_,pFdata->colorG_,pFdata->colorB_));
		ttf->setString(SysLangDataManager::get_instance2()->GetSysLangById(data->syslangid_).c_str());
	}
	m_ScrollView->resizeContent(m_Layerview);
}

void VipWindow::_mapBtn()
{
	CCMenu *menu = (CCMenu*)m_pVipNode->getChildByTag(udCLOSEBTN);
	CMenuItemSprite* cc = (CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udCLOSEBTN);
	cc->setTarget(this,menu_selector(VipWindow::On_Click_ColseBtn));//关闭按钮

	menu = (CCMenu*)m_pVipNode->getChildByTag(udLEFTBTN);
	cc = (CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udLEFTBTN);
	cc->setTarget(this,menu_selector(VipWindow::On_Click_BtnClick));//向左按钮

	menu = (CCMenu*)m_pVipNode->getChildByTag(udRIGHTBTN);
	cc = (CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udRIGHTBTN);
	cc->setTarget(this,menu_selector(VipWindow::On_Click_BtnClick));//向右按钮

	menu = (CCMenu*)m_pVipNode->getChildByTag(udIMMEDIATELYPAYBTN);
	cc = (CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udIMMEDIATELYPAYBTN);
	cc->setTarget(this,menu_selector(VipWindow::On_Click_BtnClick));//去充值按钮

	menu = (CCMenu*)m_pVipNode->getChildByTag(udVIPREWARDBTN);
	cc = (CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udVIPREWARDBTN);
	cc->setTarget(this,menu_selector(VipWindow::On_Click_BtnClick));//去充值按钮
}

void VipWindow::_setText()
{
	NFC_setLabelStringInt(udVIPLOGOLEVELTEXT,m_pVipNode,ROLEINFODATAHANDLER->m_pRIData->vipLevel_);
	char buff[64] = {0};
	sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(911).c_str(),ROLEINFODATAHANDLER->m_pRIData->vipLevel_);
	NFC_setLabelString(udCURVIPLEVELTEXT,m_pVipNode,buff);
	memset(buff,0,sizeof(buff));
	if(ROLEINFODATAHANDLER->m_pRIData->vipLevel_ == 10)
	{
		NFC_setLabelString(udPAYLATERVIPLEVELTEXT,m_pVipNode,SysLangDataManager::get_instance2()->GetSysLangById(6043).c_str());
	}
	else
	{
		int surplusexp = VIPCONTROLDATAHANDLER->m_maxExp - VIPCONTROLDATAHANDLER->m_exp;
		sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(912).c_str(),surplusexp,ROLEINFODATAHANDLER->m_pRIData->vipLevel_+1);
		NFC_setLabelString(udPAYLATERVIPLEVELTEXT,m_pVipNode,buff);
	}
	NFC_setLabelStringInt(udVIPLOGOLEVELTEXT,m_pVipNode,ROLEINFODATAHANDLER->m_pRIData->vipLevel_);
}

void VipWindow::_setExp()
{
	int curExp=VIPCONTROLDATAHANDLER->m_exp;
	int maxExp=VIPCONTROLDATAHANDLER->m_maxExp;
	float exppercent=(float)(1.0*curExp/maxExp);

	CProgressInnerBar* bar=(CProgressInnerBar*)m_pVipNode->getChildByTag(udVIPEXPPROGRESS);
	bar->setPercent(exppercent);

	//当前经验值
	char buff[64] = {0};
	sprintf(buff,"%d/%d",curExp,maxExp);
	NFC_setLabelString(udVIPEXPTEXT,m_pVipNode,buff);
}

void VipWindow::_setVipGift(int viplevel)
{
	VipGiftItem* data = VIPGIFTACTIVITYHANDLER->ByLevelData(viplevel);
	if (data == NULL)
	{
		_showVipGift(false);
		return;
	}
	else
	{
		_showVipGift(true);
	}
	//设置名字
	std::string name = data->getVipName();
	NFC_setLabelString(Box_NAMETTF,m_pVipNode,name);
	//设置原价
	NFC_setLabelStringInt(Box_COSTMONEY,m_pVipNode,data->getOriginalPrice());
	//设置特价
	NFC_setLabelStringInt(Box_OFFERMONEY,m_pVipNode,data->getDiscountPrice());
	//绑定预览
	NFC_bindSelectotForCellBtn(Box_GIFTBOXBTN,data->getVipLevel(),m_pVipNode,this,menu_selector(VipWindow::On_CheckItem_Click));
	//绑定购买
	NFC_bindSelectotForCellBtn(Box_BUYBTN,data->getVipLevel(),m_pVipNode,this,menu_selector(VipWindow::On_Click_Buy_Enevnt));
	//设置当前附件图标
	std::string file=NFC_getFileFromResourceID(data->getIconId());
	assert(file.length()>0);
	NFC_setPicForCCSprite(Box_GIFTBOXICON,m_pVipNode,file.c_str());
}

void VipWindow::_showVipGift(bool visible)
{
	for (int i=Box_VIPBG;i<=Box_BUYBTNTTF;i++)
	{
		NFC_setNodeVisable(i,m_pVipNode,visible);
	}
}

void VipWindow::On_CheckItem_Click(cocos2d::CCObject* pSender)
{
	VipGiftItem* data = VIPGIFTACTIVITYHANDLER->ByLevelData(m_CurVipPage);
	if (data == NULL)
		return;
	//点击预览礼包
	VIPGIFTACTIVITYHANDLER->PreviewGift(data->getPreviewId());
}

void VipWindow::On_Click_Buy_Enevnt(cocos2d::CCObject* pSender)
{
	VipGiftItem* data = VIPGIFTACTIVITYHANDLER->ByLevelData(m_CurVipPage);
	if (data == NULL)
		return;
	//点击预览礼包
	if (ROLEINFODATAHANDLER->m_pRIData->vipLevel_ < data->getVipLevel())
	{
		NFC_showErrorTips(SysLangDataManager::get_instance2()->GetSysLangById(6077));
		return;
	}
	if (ROLEINFODATAHANDLER->m_pRIData->jewels_ < data->getDiscountPrice())
	{
		NFC_showErrorTips(SysLangDataManager::get_instance2()->GetSysLangById(6078));
		return;
	}
	char buff[1024] = {0};
	sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(6080).c_str(),data->getDiscountPrice());
	NFC_showMessageBox(kMISSION_VIPGIFTBOX,buff);
}

void VipWindow::On_Click_BtnClick(cocos2d::CCObject* pSender)
{
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int idx  = cc->getIDX();
	if (idx == udLEFTBTN)
	{
		if (m_CurVipPage == 1)
			m_CurVipPage = 10;
		else
			m_CurVipPage--;
		SetfontByViplevel(m_CurVipPage);
		_setVipGift(m_CurVipPage);
	}
	else if (idx == udRIGHTBTN)
	{
		if (m_CurVipPage == 10)
			m_CurVipPage = 1;
		else
			m_CurVipPage++;
		SetfontByViplevel(m_CurVipPage);
		_setVipGift(m_CurVipPage);
	}
	else if(idx == udIMMEDIATELYPAYBTN)
	{
		PushEvent(_TYPED_EVENT_SHOW_RECHARGEWINDOW_);
		PushEvent(_TYPED_EVENT_HIDE_VIPWINDOW_);
		return;
	}
	else if(idx == udVIPREWARDBTN)
	{
		/*
			领奖励
		*/
		VIPCONTROLDATAHANDLER->ToServerVIPReward();
	}

}

void VipWindow::On_Click_ColseBtn(cocos2d::CCObject* pSender)
{
	PushEvent(_TYPED_EVENT_HIDE_VIPWINDOW_);
	if (DOTATribeApp::get_instance2()->IsHomeProcedureAsActiveProcedure())
	{
		PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
	}
	else
	{
		DOTATribeApp::get_instance2()->SetActiveProcedure((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
	}
}