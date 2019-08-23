// Name : HeroAltarWindow.h
// Function:英雄献祭窗口
// Author : lvyunlong
// Date: 20131130

#include "../include/HeroAltarWindow.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/LoggerSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/UIViewDataManger.h"
#include "../include/CPublicVarReader.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/CMenuItemSprite.h"
#include "../include/NFControlsManager.h"
#include "../include/SysLangDataManager.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/CProgressInnerBar.h"
#include "../include/MessageBoxWindow.h"
#include "../include/BagOtherObjectHandler.h"

using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

HeroAltarWindow::HeroAltarWindow()
:m_pRoot(NULL),
m_pHAltarNode(NULL),
m_pDebrisNode(NULL),
m_CurAltarType(0),
m_ViewHerolevel(0),
m_ViewHeroCurExp(0),
m_isBAltarDebriBtn(true)
{
	m_WindowType = _TYPED_WINDOW_ALTARWINDOW_;
	m_bModelWindow = true;
	memset(ArrTopNextValue,0,sizeof(ArrTopNextValue));
	m_Soulstonetype = 0;
}

HeroAltarWindow::~HeroAltarWindow()
{

}

bool HeroAltarWindow::Init()
{	
	RegisterEvent(_TYPED_EVENT_SHOW_ALTARWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_ALTARWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_ALTARWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATEDEBRIS_ALTARWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATEALTAROVER_ALTARWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_HIDE_INPUTNUMWINDOW_, true);//注册输入框的消失
	RegisterEvent(_TYPED_EVENT_CALLBACK_ALTARWINDOW_, true);
	
	return IWindow::Init();
}

bool HeroAltarWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		_initLayout();
		HEROALTARCONTROLDATAHANDLER->ToServerInfoTotemData();
		return true;
	}
	while (false);

	return false;
}

void HeroAltarWindow::Tick()
{
	IWindow::Tick();
}

void HeroAltarWindow::Destroy()
{
	if (m_pHAltarNode != NULL)
		m_pHAltarNode->removeAllChildrenWithCleanup(true);
	m_pHAltarNode = NULL;
	m_isBAltarDebriBtn = true;
	m_Soulstonetype = 0;
	IWindow::Destroy();
}

void HeroAltarWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{

	if(iEventType == _TYPED_EVENT_SHOW_ALTARWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
		//Fadein(IWINDOW_FADEIN_DURING);
	}
	else if(iEventType == _TYPED_EVENT_HIDE_ALTARWINDOW_)
	{
		OnHideWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_ALTARWINDOW_)
	{
		OnUpdateWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_UPDATEDEBRIS_ALTARWINDOW_)
	{
		OnUpdateDebrisWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_UPDATEALTAROVER_ALTARWINDOW_)
	{
		OnUpdateOverWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_CALLBACK_ALTARWINDOW_)
	{
		OnCallBackWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_INPUTNUMWINDOW_)
	{
		OnInputWindowEventHandler(paramList);
	}
	
}

void HeroAltarWindow::touchEvent(CPriorityLayerColor* pLayerColor)
{
	if (!m_isBAltarDebriBtn)
	{
		m_ViewHerolevel = m_ViewHeroLaterlevel;
		CallbackTTF(m_ViewHeroLaterlevel);
		m_pProgress->setRunSchedule(mAlatrlaterPos,mAlatrlaterPos,0);
		m_isBAltarDebriBtn = true;
	}
}

void HeroAltarWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
	/*
		启动游戏时只请求一次献祭每级最大经验的表 
	*/
	if (!HEROALTARCONTROLDATAHANDLER->m_BinitAltarTable || HEROALTARCONTROLDATAHANDLER->m_pCheckAltarTable.size() == 0)
	{
		HEROALTARCONTROLDATAHANDLER->ToServerCheckAltarTable();
		HEROALTARCONTROLDATAHANDLER->m_BinitAltarTable = true;
	}
}

void HeroAltarWindow::OnHideWindowEventHandler(std::list<std::string>& paramList)
{
	//Fadeout(IWINDOW_FADEOUT_DURING);
	Destroy();
}

void HeroAltarWindow::OnUpdateWindowEventHandler(std::list<std::string>& paramList)
{
	//NFC_setNodeVisable(udPRIORITYLAYER,m_pHAltarNode,false);

	//NFC_setNodeVisable(udSCENEEFFECT,m_pHAltarNode,false);

	_setText();
	_setExp();
}

void HeroAltarWindow::OnUpdateDebrisWindowEventHandler(std::list<std::string>& paramList)
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kALTARDEBRISWINDOW,m_pDebrisNode);
	CPriorityLayerColor* p = (CPriorityLayerColor*)m_pDebrisNode->getChildByTag(udVIEWPRIORITYBG);
	p->setDelegate(this);
	HEROALTARCONTROLDATAHANDLER->UpdateSoulDebris();
	_mapViewBtn();

	//设置确定按钮初始是不可用的

	//确认按钮不可用
	NFC_setEnabledForMenuItem(udVIEWSUREBTN,m_pDebrisNode,false);

	for (int i=0;i<6;i++)
	{
		DTAwardBoard* dd=(DTAwardBoard*)m_pDebrisNode->getChildByTag(udVIEWDEBRIS1+i);

		//个数
		int count = HEROALTARCONTROLDATAHANDLER->m_DebrisDataList[i]->count_;
		if (count == 0)
			dd->setDisabled(true);
		else
			dd->setDisabled(false);
		
		dd->ChangeObject(HEROALTARCONTROLDATAHANDLER->m_AltarDataList[i]->quality_,HEROALTARCONTROLDATAHANDLER->m_AltarDataList[i]->iconId_);
		//
		NFC_setLabelStringInt(udVIEWDEBRISCOUNTTTF1+i,m_pDebrisNode,count);
	}
	ShowDebrisView(m_CurAltarType);
	_initProgressTimer();
}

void HeroAltarWindow::OnUpdateOverWindowEventHandler(std::list<std::string>& paramList)
{
	m_pDebrisNode->removeAllChildrenWithCleanup(true);
}

void HeroAltarWindow::OnCallBackWindowEventHandler(std::list<std::string>& paramList)
{
	HEROALTARCONTROLDATAHANDLER->ToServerInfoDebris(m_CurAltarType);
	m_pDebrisNode->removeAllChildrenWithCleanup(true);
}

void HeroAltarWindow::OnInputWindowEventHandler(std::list<std::string>& paramList)
{
	if (paramList.size()>=1)
	{
		std::list<std::string>::iterator it=paramList.begin();
		std::string str = *it;
		int num = 0;
		sscanf(str.c_str(), "%d", &num);
		//取回了数据，定义操作
		int count = HEROALTARCONTROLDATAHANDLER->m_DebrisDataList[m_Soulstonetype]->count_;
		count -= num;
		NFC_setLabelStringInt(udVIEWDEBRISCOUNTTTF1+m_Soulstonetype,m_pDebrisNode,count);
		HEROALTARCONTROLDATAHANDLER->m_DebrisDataList[m_Soulstonetype]->count_ = count;
		//加到点击列表里
		HEROALTARCONTROLDATAHANDLER->m_ClickDebriList[m_Soulstonetype]->count_ += num;
		//进度条

		int exp = HEROALTARCONTROLDATAHANDLER->m_AltarDataList[m_Soulstonetype]->expadd_;
		exp *= num;
	
		_setProgress(exp);

		//确认按钮可用
		NFC_setEnabledForMenuItem(udVIEWSUREBTN,m_pDebrisNode,true);

		//按钮不可用
		m_isBAltarDebriBtn = false;
		if (count == 0)
		{
			DTAwardBoard* dd=(DTAwardBoard*)m_pDebrisNode->getChildByTag(udVIEWDEBRIS1+m_Soulstonetype);
			dd->setDisabled(true);
			return;
		}		
	}
}

void HeroAltarWindow::_initLayout()
{
	m_pRoot =m_pRootNode;
	m_pRoot->setAnchorPoint(CCPointZero);
	m_pRoot->setPosition(CCPointZero);
	m_pHAltarNode = CCNode::create();
	m_pHAltarNode->setAnchorPoint(CCPointZero);
	m_pHAltarNode->setPosition(CCPointZero);
	m_pDebrisNode = CCNode::create();
	m_pDebrisNode->setAnchorPoint(CCPointZero);
	m_pDebrisNode->setPosition(CCPointZero);
	
	m_pRoot->addChild(m_pHAltarNode,10);
	m_pRoot->addChild(m_pDebrisNode,15);
	_initControl();
	_mapBtn();
	_setJump();

}


void HeroAltarWindow::_initControl()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kALTARWINDOW,m_pHAltarNode);
}


void HeroAltarWindow::_mapBtn()
{
	CCMenu* menu =(CCMenu*)m_pHAltarNode->getChildByTag(udQUICKCITYBTN);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udQUICKCITYBTN);
	cc->setTarget(this,menu_selector(HeroAltarWindow::On_Click_Event));

	menu=(CCMenu*)m_pHAltarNode->getChildByTag(udHEROSUMMONBTN);
	cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udHEROSUMMONBTN);
	cc->setTarget(this,menu_selector(HeroAltarWindow::On_Click_Event));

	menu=(CCMenu*)m_pHAltarNode->getChildByTag(udALTARBTN1);
	cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udALTARBTN1);
	cc->setTarget(this,menu_selector(HeroAltarWindow::On_Click_AltarBtn_Event));

	menu=(CCMenu*)m_pHAltarNode->getChildByTag(udALTARBTN2);
	cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udALTARBTN2);
	cc->setTarget(this,menu_selector(HeroAltarWindow::On_Click_AltarBtn_Event));

	menu=(CCMenu*)m_pHAltarNode->getChildByTag(udALTARBTN3);
	cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udALTARBTN3);
	cc->setTarget(this,menu_selector(HeroAltarWindow::On_Click_AltarBtn_Event));
}

void HeroAltarWindow::_setJump()
{
	for (int i =0;i<3;i++)
	{
		CCActionInterval*  a1 = CCMoveBy::create(2, ccp(0,30));
		CCAction*  action2 = CCRepeatForever::create(
			CCSequence::create((CCActionInterval*)(a1->copy()->autorelease()), a1->reverse(), NULL)
			);
		 CCSprite* pSprite = (CCSprite*)NFC_getNode(udTOTEMICON1+i,m_pHAltarNode);
		  pSprite->runAction( action2);
	}
}

void HeroAltarWindow::_mapViewBtn()
{	
	CCMenu* menu =(CCMenu*)m_pDebrisNode->getChildByTag(udVIEWSUREBTN);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udVIEWSUREBTN);
	cc->setTarget(this,menu_selector(HeroAltarWindow::On_Click_DebrisView_Enevnt));

	menu=(CCMenu*)m_pDebrisNode->getChildByTag(udVIEWCANCELBTN);
	cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udVIEWCANCELBTN);
	cc->setTarget(this,menu_selector(HeroAltarWindow::On_Click_DebrisView_Enevnt));

	for (int i=udVIEWDEBRIS1;i<=udVIEWDEBRIS6;i++)
	{
		DTAwardBoard* dd=(DTAwardBoard*)m_pDebrisNode->getChildByTag(i);
		dd->setIDX(i);
		dd->setTarget(this,menu_selector(HeroAltarWindow::On_Click_DebrisBtn_Event));
	}
}

void HeroAltarWindow::_setText()
{
	for (int i=0;i<3;i++)
	{
		TotemData* temp = HEROALTARCONTROLDATAHANDLER->m_TotemDataList[i];
		char buff[64]={0};
		sprintf(buff,"%d",temp->level_);
		NFC_setLabelString(udLEVELTEXT1+i,m_pHAltarNode,buff);
		memset(buff,0,sizeof(buff));
		sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(765+i).c_str(),temp->addvalue_);
		NFC_setLabelString(udADDTEXT1+i,m_pHAltarNode,buff);
	}
}

void HeroAltarWindow::_setExp()
{
	for (int i=0;i<3;i++)
	{
		TotemData* temp = HEROALTARCONTROLDATAHANDLER->m_TotemDataList[i];
		int curExp = temp->exp_;
		int maxExp = temp->maxExp_;
		float exppercent = (float)(1.0*curExp/maxExp);

		CProgressInnerBar* bar=(CProgressInnerBar*)m_pHAltarNode->getChildByTag(udSCHEDULE1+i);
		bar->setPercent(exppercent);
	}
}

void HeroAltarWindow::_setProgress(int expvalue)
{
	int AltarlaterLevel = 0;
	int AltarlaterExp = 0;
	HEROALTARCONTROLDATAHANDLER->AltarDebriLater(m_ViewHerolevel,m_ViewHeroCurExp+expvalue,AltarlaterLevel,AltarlaterExp);
	int times = AltarlaterLevel - m_ViewHerolevel;
	m_ViewHeroLaterlevel = AltarlaterLevel;
	float posbegin = 0.0f;
	mAlatrlaterPos = 0.0f;
	if (times == 0)
	{
		int maxExp = HEROALTARCONTROLDATAHANDLER->ByLevelCheckMaxExp(m_ViewHerolevel);
		posbegin = (float)(100.0*m_ViewHeroCurExp/maxExp);
		mAlatrlaterPos = (float)(100.0*AltarlaterExp/maxExp);
		m_pProgress->setRunSchedule(posbegin,mAlatrlaterPos,times);
		m_ViewHeroCurExp = AltarlaterExp;
	}
	else
	{
		int maxExp = HEROALTARCONTROLDATAHANDLER->ByLevelCheckMaxExp(m_ViewHerolevel);
		posbegin = (float)(100.0*m_ViewHeroCurExp/maxExp);
		int maxExp1 = HEROALTARCONTROLDATAHANDLER->ByLevelCheckMaxExp(AltarlaterLevel);
		mAlatrlaterPos = (float)(100.0*AltarlaterExp/maxExp1);
		m_pProgress->setRunSchedule(posbegin,mAlatrlaterPos,times);
		m_ViewHeroCurExp = AltarlaterExp;
	}
}

void HeroAltarWindow::On_Click_DebrisBtn_Event(cocos2d::CCObject* pSender)
{
	//顶级之后的操作
	if (ArrTopNextValue[m_CurAltarType] == 0)
	{
		//提醒用户不可献祭
		NFC_showMessageBoxSingle(kDEFAULT,SysLangDataManager::get_instance2()->GetSysLangById(6021).c_str());
		return;
	}
	if (!m_isBAltarDebriBtn)
	{
		return;
	}
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int index = cc->getIDX();
	int Enum_type = 0;
	if(index == udVIEWDEBRIS1)
	{
		Enum_type = _ENUM_TYPE_DEBRIS_0;
	}
	else if (index == udVIEWDEBRIS2)
	{
		Enum_type = _ENUM_TYPE_DEBRIS_1;
	}
	else if (index == udVIEWDEBRIS3)
	{
		Enum_type = _ENUM_TYPE_DEBRIS_2;
	}
	else if (index == udVIEWDEBRIS4)
	{
		Enum_type = _ENUM_TYPE_DEBRIS_3;
	}
	else if (index == udVIEWDEBRIS5)
	{
		Enum_type = _ENUM_TYPE_DEBRIS_4;
	}
	else if (index == udVIEWDEBRIS6)
	{
		Enum_type = _ENUM_TYPE_DEBRIS_5;
	}
	int count = HEROALTARCONTROLDATAHANDLER->m_DebrisDataList[Enum_type]->count_;
	if (count>=10)
	{
		int itemid = HEROALTARCONTROLDATAHANDLER->m_DebrisDataList[Enum_type]->itemId_;
		BagOtherObject *pObject = BAGOTHEROBJECTHANDLER->getObjectByTemplateId(itemid);
		if (pObject != NULL)
		{
			m_Soulstonetype = Enum_type;

			int needcount = HEROALTARCONTROLDATAHANDLER->NeedSoulStoneTopLevel(Enum_type,m_ViewHerolevel,m_ViewHeroCurExp);
			if (needcount <= count)
				count = needcount;
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_INPUTNUMWINDOW_, pObject->template_->name_, _to_event_param_(count));
			return;
		}
	}
	count--;
	NFC_setLabelStringInt(udVIEWDEBRISCOUNTTTF1+Enum_type,m_pDebrisNode,count);
	HEROALTARCONTROLDATAHANDLER->m_DebrisDataList[Enum_type]->count_ = count;
	//加到点击列表里
	HEROALTARCONTROLDATAHANDLER->m_ClickDebriList[Enum_type]->count_++;
	//进度条

	int exp = HEROALTARCONTROLDATAHANDLER->m_AltarDataList[Enum_type]->expadd_;
	_setProgress(exp);

	//确认按钮可用
	NFC_setEnabledForMenuItem(udVIEWSUREBTN,m_pDebrisNode,true);

	//按钮不可用
	m_isBAltarDebriBtn = false;
	if (count == 0)
	{
		DTAwardBoard* dd=(DTAwardBoard*)m_pDebrisNode->getChildByTag(udVIEWDEBRIS1+Enum_type);
		dd->setDisabled(true);
		return;
	}
}

//快速回城和英雄召唤
void HeroAltarWindow::On_Click_Event(cocos2d::CCObject* pSender)
{
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int index = cc->getIDX();
	if(index == udQUICKCITYBTN)
	{
		PushEvent(_TYPED_EVENT_HIDE_ALTARWINDOW_);
		PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
	}
	else if (index == udHEROSUMMONBTN)
	{
		PushEvent(_TYPED_EVENT_HIDE_ALTARWINDOW_);
		PushEvent(_TYPED_EVENT_SHOW_HEROBARWINDOW_);
	}
}

//献祭按钮
void HeroAltarWindow::On_Click_AltarBtn_Event(cocos2d::CCObject* pSender)
{
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int index = cc->getIDX();
	if (index == udALTARBTN1)
	{
		m_CurAltarType = _ENUM_TYPE_STRENGTH;
	}
	else if (index == udALTARBTN2)
	{
		m_CurAltarType = _ENUM_TYPE_NIMBLE;
	}
	else if (index == udALTARBTN3)
	{
		m_CurAltarType = _ENUM_TYPE_MENTALITY;
	}
	HEROALTARCONTROLDATAHANDLER->ToServerInfoAltarData();
}

void HeroAltarWindow::On_Click_DebrisView_Enevnt(cocos2d::CCObject* pSender)
{
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int index = cc->getIDX();
	m_isBAltarDebriBtn = true;

	if (index == udVIEWSUREBTN)
	{
		
		if (HEROALTARCONTROLDATAHANDLER->FindClickIsSoulDebri())
		{
			NFC_showMessageBox(kALTARQUALITYHIGH,SysLangDataManager::get_instance2()->GetSysLangById(6012).c_str());
			return;
		}

		HEROALTARCONTROLDATAHANDLER->ToServerInfoDebris(m_CurAltarType);
		m_pDebrisNode->removeAllChildrenWithCleanup(true);
	}
	else if (index == udVIEWCANCELBTN)
	{
		m_pDebrisNode->removeAllChildrenWithCleanup(true);
	}
}

//碎片献祭显示
void HeroAltarWindow::ShowDebrisView(int type)
{
	if (type == _ENUM_TYPE_STRENGTH)
	{
		NFC_setLabelString(udVIEWTITLETEXT,m_pDebrisNode,SysLangDataManager::get_instance2()->GetSysLangById(986).c_str());
		char buff[64]={0};
		sprintf(buff,"LV%d",HEROALTARCONTROLDATAHANDLER->m_TotemDataList[0]->level_);
		NFC_setLabelString(udVIEWTITLELEVELTEXT,m_pDebrisNode,buff);
		memset(buff,0,sizeof(buff));
		sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(989).c_str(),HEROALTARCONTROLDATAHANDLER->m_TotemDataList[0]->addvalue_);
		NFC_setLabelString(udVIEWCURSTRENGTEXT,m_pDebrisNode,buff);
		memset(buff,0,sizeof(buff));
		ArrTopNextValue[0] = HEROALTARCONTROLDATAHANDLER->m_TotemDataList[0]->nextValue_;
		if (HEROALTARCONTROLDATAHANDLER->m_TotemDataList[0]->nextValue_ == 0)
		{
			sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(6021).c_str());
			NFC_setLabelString(udVIEWNEXTSTRENGTEXT,m_pDebrisNode,buff);
		}
		else
		{
			sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(990).c_str(),HEROALTARCONTROLDATAHANDLER->m_TotemDataList[0]->nextValue_);
			NFC_setLabelString(udVIEWNEXTSTRENGTEXT,m_pDebrisNode,buff);
		}
		
		m_ViewHerolevel = HEROALTARCONTROLDATAHANDLER->m_TotemDataList[0]->level_;
		m_ViewHeroCurExp = HEROALTARCONTROLDATAHANDLER->m_TotemDataList[0]->exp_;

	}
	else if (type == _ENUM_TYPE_NIMBLE)
	{
		NFC_setLabelString(udVIEWTITLETEXT,m_pDebrisNode,SysLangDataManager::get_instance2()->GetSysLangById(987).c_str());
		char buff[64]={0};
		sprintf(buff,"LV%d",HEROALTARCONTROLDATAHANDLER->m_TotemDataList[1]->level_);
		NFC_setLabelString(udVIEWTITLELEVELTEXT,m_pDebrisNode,buff);
		memset(buff,0,sizeof(buff));
		sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(991).c_str(),HEROALTARCONTROLDATAHANDLER->m_TotemDataList[1]->addvalue_);
		NFC_setLabelString(udVIEWCURSTRENGTEXT,m_pDebrisNode,buff);
		memset(buff,0,sizeof(buff));
		ArrTopNextValue[1] = HEROALTARCONTROLDATAHANDLER->m_TotemDataList[1]->nextValue_;
		if (HEROALTARCONTROLDATAHANDLER->m_TotemDataList[1]->nextValue_ == 0)
		{
			sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(6021).c_str());
			NFC_setLabelString(udVIEWNEXTSTRENGTEXT,m_pDebrisNode,buff);
		}
		else
		{
			sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(992).c_str(),HEROALTARCONTROLDATAHANDLER->m_TotemDataList[1]->nextValue_);
			NFC_setLabelString(udVIEWNEXTSTRENGTEXT,m_pDebrisNode,buff);
		}

		m_ViewHerolevel = HEROALTARCONTROLDATAHANDLER->m_TotemDataList[1]->level_;
		m_ViewHeroCurExp = HEROALTARCONTROLDATAHANDLER->m_TotemDataList[1]->exp_;
	}
	else if (type == _ENUM_TYPE_MENTALITY)
	{
		NFC_setLabelString(udVIEWTITLETEXT,m_pDebrisNode,SysLangDataManager::get_instance2()->GetSysLangById(988).c_str());
		char buff[64]={0};
		sprintf(buff,"LV%d",HEROALTARCONTROLDATAHANDLER->m_TotemDataList[2]->level_);
		NFC_setLabelString(udVIEWTITLELEVELTEXT,m_pDebrisNode,buff);
		memset(buff,0,sizeof(buff));
		sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(993).c_str(),HEROALTARCONTROLDATAHANDLER->m_TotemDataList[2]->addvalue_);
		NFC_setLabelString(udVIEWCURSTRENGTEXT,m_pDebrisNode,buff);
		memset(buff,0,sizeof(buff));
		ArrTopNextValue[2] = HEROALTARCONTROLDATAHANDLER->m_TotemDataList[2]->nextValue_;
		if (HEROALTARCONTROLDATAHANDLER->m_TotemDataList[2]->nextValue_ == 0)
		{
			sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(6021).c_str());
			NFC_setLabelString(udVIEWNEXTSTRENGTEXT,m_pDebrisNode,buff);
		}
		else
		{
			sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(994).c_str(),HEROALTARCONTROLDATAHANDLER->m_TotemDataList[2]->nextValue_);
			NFC_setLabelString(udVIEWNEXTSTRENGTEXT,m_pDebrisNode,buff);
		}

		m_ViewHerolevel = HEROALTARCONTROLDATAHANDLER->m_TotemDataList[2]->level_;
		m_ViewHeroCurExp = HEROALTARCONTROLDATAHANDLER->m_TotemDataList[2]->exp_;
	}
}

void HeroAltarWindow::CallbackTTF(int level)
{
	char buff[64]={0};
	sprintf(buff,"LV%d",level);
	NFC_setLabelString(udVIEWTITLELEVELTEXT,m_pDebrisNode,buff);
	memset(buff,0,sizeof(buff));
	int addval = HEROALTARCONTROLDATAHANDLER->ByLevelCheckAddValue_(level,m_CurAltarType);
	int nextaddval = HEROALTARCONTROLDATAHANDLER->ByLevelCheckAddValue_(level+1,m_CurAltarType);

	if (m_CurAltarType == _ENUM_TYPE_STRENGTH)
	{
		sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(989).c_str(),addval);
		NFC_setLabelString(udVIEWCURSTRENGTEXT,m_pDebrisNode,buff);
		memset(buff,0,sizeof(buff));
		sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(990).c_str(),nextaddval);
		NFC_setLabelString(udVIEWNEXTSTRENGTEXT,m_pDebrisNode,buff);

	}
	else if (m_CurAltarType == _ENUM_TYPE_NIMBLE)
	{
		sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(991).c_str(),addval);
		NFC_setLabelString(udVIEWCURSTRENGTEXT,m_pDebrisNode,buff);
		memset(buff,0,sizeof(buff));
		sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(992).c_str(),nextaddval);
		NFC_setLabelString(udVIEWNEXTSTRENGTEXT,m_pDebrisNode,buff);
	}
	else if (m_CurAltarType == _ENUM_TYPE_MENTALITY)
	{
		sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(993).c_str(),addval);
		NFC_setLabelString(udVIEWCURSTRENGTEXT,m_pDebrisNode,buff);
		memset(buff,0,sizeof(buff));
		sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(994).c_str(),nextaddval);
		NFC_setLabelString(udVIEWNEXTSTRENGTEXT,m_pDebrisNode,buff);
	}

	int MaxLevel = HEROALTARCONTROLDATAHANDLER->AllowMaxAltarLevel();

	if (MaxLevel <= level)
	{
		setLevelTop();
	}

}

void HeroAltarWindow::CallbackBtnEnable()
{
	m_isBAltarDebriBtn = true;
}

void HeroAltarWindow::_initProgressTimer()
{

	m_pProgress = (CProgressTimer *)NFC_getNode(udVIEWSCHEDULE1,m_pDebrisNode);
	m_pProgress->setDelegate(this);

	m_ViewHeroCurExp = HEROALTARCONTROLDATAHANDLER->m_TotemDataList[m_CurAltarType]->exp_;

	int max = HEROALTARCONTROLDATAHANDLER->ByLevelCheckMaxExp(m_ViewHerolevel);

	float frontpos = (float)(100.0*m_ViewHeroCurExp/max);

	m_pProgress->setRunSchedule(frontpos,frontpos,0);

}

void HeroAltarWindow::setLevelTop()
{
	int TopLevel = HEROALTARCONTROLDATAHANDLER->AllowMaxAltarLevel();
	int addval = HEROALTARCONTROLDATAHANDLER->ByLevelCheckAddValue_(TopLevel,m_CurAltarType);
	int i = m_CurAltarType*2;
	char buff[64] = {0};
	//当前级别
	sprintf(buff,"LV%d",TopLevel);
	NFC_setLabelString(udVIEWTITLELEVELTEXT,m_pDebrisNode,buff);
	memset(buff,0,sizeof(buff));
	//当前加成
	sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(989+i).c_str(),addval);
	NFC_setLabelString(udVIEWCURSTRENGTEXT,m_pDebrisNode,buff);
	memset(buff,0,sizeof(buff));
	//下一级显示
	sprintf(buff,SysLangDataManager::get_instance2()->GetSysLangById(6021).c_str());
	NFC_setLabelString(udVIEWNEXTSTRENGTEXT,m_pDebrisNode,buff);

	//当前进度条
	m_pProgress->setRunSchedule(0,0,0);
	//下一级是0
	ArrTopNextValue[m_CurAltarType] = 0;
}

void HeroAltarWindow::CallBack_NextLevel()
{
	m_ViewHerolevel++;
	CallbackTTF(m_ViewHerolevel);
}
void HeroAltarWindow::CallBack_RunFinish()
{
	CallbackBtnEnable();
}