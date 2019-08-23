// Name : TeamInfoWindow.h
// Function:队伍信息窗口
// Author : lvyunlong
// Date: 20140610

#include "../include/TeamInfoWindow.h"
#include "../include/EventTyper.h"
#include "../include/UIViewDataManger.h"
#include "../include/NFControlsManager.h"
#include "../include/WindowManager.h"
#include "../include/AnimationFileDataManager.h"
#include "../include/RoleShapeDataManager.h"
#include "../include/HERoleInfoNode.h"
#include "../include/PESWindow.h"
#include "../include/HeroteamChangePacket.h"
#include "../include/TimeSystem.h"
#include "../include/RoleInfoDataHandler.h"
USING_NS_CC;


TeamInfoWindow::TeamInfoWindow()
:m_nBackWindowType(-1)
{
	m_WindowType   = _TYPED_WINDOW_TEAMINFOWINDOW_;
	m_bModelWindow = true;
	m_pSkeletonArray[0] = NULL;
	m_pSkeletonArray[1] = NULL;
	m_pSkeletonArray[2] = NULL;
}

TeamInfoWindow::~TeamInfoWindow()
{
	
}

bool TeamInfoWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_TEAMINFOWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_TEAMINFOWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_TEAMINFOWINDOW_, true);

	return IWindow::Init();
}
bool TeamInfoWindow::Load()
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

void TeamInfoWindow::Tick()
{
	IWindow::Tick();
}

void TeamInfoWindow::Destroy()
{
	if (m_pSkeletonArray[0])
	{
		m_pSkeletonArray[0]->removeFromParentAndCleanup(true);
		m_pSkeletonArray[0]=NULL;
	}
	if (m_pSkeletonArray[1])
	{
		m_pSkeletonArray[1]->removeFromParentAndCleanup(true);
		m_pSkeletonArray[1]=NULL;
	}
	if (m_pSkeletonArray[2])
	{
		m_pSkeletonArray[2]->removeFromParentAndCleanup(true);
		m_pSkeletonArray[2]=NULL;
	}
	m_pRootNode->removeAllChildrenWithCleanup(true);

	IWindow::Destroy();
}

void TeamInfoWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_TEAMINFOWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_TEAMINFOWINDOW_)
	{
		OnHideWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_TEAMINFOWINDOW_)
	{
		OnUpDateWindowEventHandler(paramList);
	}
}

void TeamInfoWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
	list<string>::iterator it=paramList.begin();
	string tmp;
	//第一个参数为子界面
	if (paramList.size()>0){
		tmp=*it++;
		m_nBackWindowType=atoi(tmp.c_str());
	}
}

void  TeamInfoWindow::OnHideWindowEventHandler(std::list<std::string>& paramList)
{
	Destroy();
}

void  TeamInfoWindow::OnUpDateWindowEventHandler(std::list<std::string>& paramList)
{
	for (int index = 0;index<3;index++)
	{
		CCNode* node = NFC_getNode(udHERONODE1+index,m_pRootNode);
		_setHeroInfoVisible(index,node);
	}
}

void TeamInfoWindow::_initLayout()
{
	_initControl();
	_mapBtn();
	_setEXTeamBtn();
	_setRoleInfoNode();
	_setheroinfo();
	
}


void TeamInfoWindow::_initControl()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kTEAMINFOWINDOW,m_pRootNode);
}

void TeamInfoWindow::_mapBtn()
{
	CCMenu* menu =(CCMenu*)m_pRootNode->getChildByTag(udCLOSEBTN);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setTarget(this,menu_selector(TeamInfoWindow::On_Close_ClickBtn));

	menu =(CCMenu*)m_pRootNode->getChildByTag(udEXCHANGEHEROBTN1);
	cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udEXCHANGEHEROBTN1);
	cc->setTarget(this,menu_selector(TeamInfoWindow::On_Check_ClickBtn));

	menu =(CCMenu*)m_pRootNode->getChildByTag(udEXCHANGEHEROBTN2);
	cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udEXCHANGEHEROBTN2);
	cc->setTarget(this,menu_selector(TeamInfoWindow::On_Check_ClickBtn));
}

void TeamInfoWindow::_setRoleInfoNode()
{
	MaskNode* node = (MaskNode*)NFC_getNode(udCOMMANDNODE,m_pRootNode);
	HERoleInfoNode* pRINode=HERoleInfoNode::create();
	pRINode->setZOrder(node->GetViewData().zorder_);
	pRINode->setPosition(node->getPosition());
	m_pRootNode->addChild(pRINode);
}

void TeamInfoWindow::_setheroinfo()
{
	for (int index = 0;index<3;index++)
	{
		CCNode* node = NFC_getNode(udHERONODE1+index,m_pRootNode);
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kTEAMHEROSHOWNODE,node);
		_mapHeroInfoBtn(index);
		_setHeroInfoVisible(index,node);
	}
}

void TeamInfoWindow::_setHeroInfoVisible(int index,CCNode* node)
{
	if(NFC_HasTeamHero(index))
	{
		NFC_setNodeVisable(HI_LOCK,node,false);
		NFC_setNodeVisable(HI_OPENLEVEL,node,false);
		NFC_setNodeVisable(HI_EXCHANGE_HEROBTN1,node,false); //隐藏加英雄按钮
		NFC_setNodeVisable(HI_EXCHANGE_HEROTTF1,node,false); //隐藏加英雄文字
		//展示英雄
		IHeroSkinItem* pSkin = NFC_GetTeamHero(index);
		if (pSkin == NULL)
			return;
		int id = pSkin->getHeroShapeID();
		_setShowHeroDaiji(index,id,node);
		//设置星阶
		CCardsStarProgress *pStar = (CCardsStarProgress*)NFC_getNode(HI_STAR,node);
		pStar->SetCurcount(pSkin->getHeroQualiy()+1);
		pStar->setVisible(true);
		//设置战力
		NFC_setLabelStringInt(HI_STRENGTHTTF, node, pSkin->getHeroStrength());
		//英雄的名字
		NFC_setLabelString(HI_HERONAMETTF,node,pSkin->getHeroName().c_str());
		
	}
	else
	{
		for (int i =HI_STAR;i<=HI_EXCHANGE_HEROTTF1;i++)
		{
			NFC_setNodeVisable(i,node,false);
		}
		NFC_setNodeVisable(HI_BG,node,true);
		if (index == 1 )
		{
			if (ROLEINFODATAHANDLER->m_pRIData->level_ >= ROLEINFODATAHANDLER->m_pRIData->heroopenIndex2_)
			{
				NFC_setNodeVisable(HI_EXCHANGE_HEROBTN1,node,true);
				NFC_setNodeVisable(HI_EXCHANGE_HEROTTF1,node,true);
			}
			else
			{
				NFC_setNodeVisable(HI_LOCK,node,true);
				char buff[1024] = {0};
				sprintf(buff, SysLangDataManager::get_instance2()->GetSysLangById(6086).c_str(), ROLEINFODATAHANDLER->m_pRIData->heroopenIndex2_);
				NFC_setLabelString(HI_OPENLEVEL,node,buff,true);
			}
		}

		if (index == 2 )
		{
			if (ROLEINFODATAHANDLER->m_pRIData->level_ >= ROLEINFODATAHANDLER->m_pRIData->heroopenIndex3_)
			{
				NFC_setNodeVisable(HI_EXCHANGE_HEROBTN1,node,true);
				NFC_setNodeVisable(HI_EXCHANGE_HEROTTF1,node,true);
			}
			else
			{
				NFC_setNodeVisable(HI_LOCK,node,true);
				char buff[1024] = {0};
				sprintf(buff, SysLangDataManager::get_instance2()->GetSysLangById(6086).c_str(), ROLEINFODATAHANDLER->m_pRIData->heroopenIndex3_);
				NFC_setLabelString(HI_OPENLEVEL,node,buff,true);
			}
		}
	}
	
}

void TeamInfoWindow::_setShowHeroDaiji(int index,int heroid,CCNode* node)
{
	MaskNode* masknode = (MaskNode*)node->getChildByTag(HI_HEROMASKNODE);
	//强制释放无用资源
	if(m_pSkeletonArray[index]) 
		m_pSkeletonArray[index]->removeFromParentAndCleanup(true); 

	DOTATribeApp::get_instance2()->ForceFreeMemory();

	unsigned short shapeID = heroid;
	assert(shapeID>=0);
	RoleShapeData *pData = RoleShapeDataManager::get_instance2()->GetRoleShapeById(shapeID);
	m_pSkeletonArray[index] = CCSkeletonAnimation::createWithFile(pData->mShapeAnimationFileDaiJi,pData->mShapeAnimationImage); 
	if(m_pSkeletonArray[index]) 
		m_pSkeletonArray[index]->setAnimation("DaiJi",true);
	m_pSkeletonArray[index]->setAnchorPoint(node->getAnchorPoint());
	m_pSkeletonArray[index]->setPosition(ccp(0.0f,0.0f));
	masknode->addChild(m_pSkeletonArray[index],20);
}

void TeamInfoWindow::_mapHeroInfoBtn(int index)
{
	CCNode* node = NFC_getNode(udHERONODE1+index,m_pRootNode);
	CCMenu* menu =(CCMenu*)node->getChildByTag(HI_EXCHANGE_HEROBTN);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(index);
	cc->setTarget(this,menu_selector(TeamInfoWindow::On_Click_EXHero_Event));

	menu =(CCMenu*)node->getChildByTag(HI_EXCHANGE_HEROBTN1);
	cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(index);
	cc->setTarget(this,menu_selector(TeamInfoWindow::On_Click_EXHero_Event));

	menu =(CCMenu*)node->getChildByTag(HI_EXCHANGE_EQUIPBTN);
	cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(index);
	cc->setTarget(this,menu_selector(TeamInfoWindow::On_Click_EXEquip_Event));

	menu =(CCMenu*)node->getChildByTag(HI_EXCHANGE_SKILLBTN);
	cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(index);
	cc->setTarget(this,menu_selector(TeamInfoWindow::On_Click_EXSkill_Event));

	menu = (CCMenu*)node->getChildByTag(HI_EXCHANGE_SOULBTN);
	cc = (CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(index);
	cc->setTarget(this, menu_selector(TeamInfoWindow::On_Click_EXSoul_Event));
}

void TeamInfoWindow::_setEXTeamBtn()
{
	NFC_setEnabledForMenuItem(udEXCHANGEHEROBTN1,m_pRootNode,NFC_HasTeamHero(1));
	NFC_setEnabledForMenuItem(udEXCHANGEHEROBTN2,m_pRootNode,NFC_HasTeamHero(2));
}

void TeamInfoWindow::On_Check_ClickBtn(cocos2d::CCObject * pSender)
{
	BTN_INTERVAL("TeamInfoWindowBtn",_COMMON_BTN_CLICK_INTERVAL_SMALL);
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int index = cc->getIDX();
	if (index == udEXCHANGEHEROBTN1)
	{
		unsigned char idx = 0;
		unsigned char idx1 = 1;
		CSHeroteamChangePacket packet(idx,idx1);
		packet.Send();
	}
	else if (index == udEXCHANGEHEROBTN2)
	{
		unsigned char idx = 1;
		unsigned char idx1 = 2;
		CSHeroteamChangePacket packet(idx,idx1);
		packet.Send();
	}
	NFC_showCommunicationWating(true);
}

void TeamInfoWindow::On_Close_ClickBtn(cocos2d::CCObject * pSender)
{
	if (m_nBackWindowType<0)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
	}else{
		EVENTSYSTEM->PushEvent(m_nBackWindowType);
		m_nBackWindowType=-1;
	}
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_TEAMINFOWINDOW_);
}

void TeamInfoWindow::On_Click_EXHero_Event(cocos2d::CCObject * pSender)
{
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int heroPos = cc->getIDX();
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_TEAMINFOWINDOW_);
	EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_HeroIllustratedWindow_,_to_event_param_(IWindow::_TYPED_WINDOW_TEAMINFOWINDOW_), _to_event_param_(heroPos));
}

void TeamInfoWindow::On_Click_EXEquip_Event(cocos2d::CCObject * pSender)
{
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int index = cc->getIDX();
	int tabindex = 0;
	if (index == 0)
	{
		tabindex = PESWindow::kTAB_1;
	}
	else if (index == 1)
	{
		tabindex = PESWindow::kTAB_2;
	}
	else if (index == 2)
	{
		tabindex = PESWindow::kTAB_3;
	}
	else
	{
		tabindex = PESWindow::kTAB_1;
	}
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_TEAMINFOWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_FADEIN_PESWINDOW_, _to_event_param_(tabindex), _to_event_param_(PESWindow::LOAD_EQUIP_VIEW), _to_event_param_(_TYPED_EVENT_SHOW_TEAMINFOWINDOW_));

}

void TeamInfoWindow::On_Click_EXSkill_Event(cocos2d::CCObject * pSender)
{
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int index = cc->getIDX();
	
	char type[128] = "";
	sprintf(type,"%d",_TYPED_EVENT_SHOW_TEAMINFOWINDOW_);
	EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_SELECTSKILLWINDOW_,_to_event_param_(index),type);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_TEAMINFOWINDOW_);
}

void TeamInfoWindow::On_Click_EXSoul_Event(cocos2d::CCObject * pSender)
{
	if (!_isSoulFuncOpen())
		return;
	CMenuItemSprite* cc = (CMenuItemSprite*)pSender;
	int index = cc->getIDX();
	int tabindex = 0;
	if (index == 0)
	{
		tabindex = PESWindow::kTAB_1;
	}
	else if (index == 1)
	{
		tabindex = PESWindow::kTAB_2;
	}
	else if (index == 2)
	{
		tabindex = PESWindow::kTAB_3;
	}
	else
	{
		tabindex = PESWindow::kTAB_1;
	}
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_TEAMINFOWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_FADEIN_PESWINDOW_, _to_event_param_(tabindex),_to_event_param_(PESWindow::LOAD_SOUL_VIEW), _to_event_param_(_TYPED_EVENT_SHOW_TEAMINFOWINDOW_));
}

bool TeamInfoWindow::_isSoulFuncOpen(){
	int  heroSoulOpenLevel = ClientConstDataManager::get_instance2()->getValueByKey(HEROSOUL_OPEN_LEVEL);
	if (RoleInfoDataHandler::get_instance2()->m_pRIData->level_ < heroSoulOpenLevel)
	{
		char commonStr[128] = { 0 };
		std::string advanceTips = SysLangDataManager::get_instance2()->GetSysLangById(_COMMON_LESS_LEVEL_TIPS_);
		sprintf(commonStr, advanceTips.c_str(), heroSoulOpenLevel);
		NFC_showMessageBoxSingle(kDEFAULT, commonStr);
		return false;
	}
	return true;
}