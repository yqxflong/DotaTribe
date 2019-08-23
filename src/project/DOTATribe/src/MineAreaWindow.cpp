//Name : MineAreaWindow
//Function : ��
//Author : ����
//Date: 20131128

#include "../include/MineAreaWindow.h"
#include "../include/EventTyper.h"
#include "../include/EventSystem.h"
#include "../include/UIViewDataManger.h"
#include "../include/CMenuItemSprite.h"
#include "../include/MiningDataHandler.h"
#include "../include/NFControlsManager.h"
#include "../include/SysLangDataManager.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/CProgressInnerBar.h"
#include "../include/FriendAddPacket.h"
#include "../include/RoleShapeDataManager.h"
#include "../include/RoleHeroSkinsDataHandler.h"
#include "../include/PuCongWindow.h"
#include "../include/EffectDataHandler.h"
#include "../include/VariableSystem.h"
#include "../include/TimeSystem.h"
#include "../include/NFAnimationController.h"

MineAreaWindow::MineAreaWindow()
	:m_iShowPage(0)
	,m_iDwarvenShowPage(0)
	,m_iDragonSelectOwner(0)
	,m_pDragonSelectOwner(NULL)
	,m_pSkeletonNode(NULL)	//Ӣ�۽�ɫ,��������
	,m_pAnimationPlayNode(NULL)//���Ŷ����ڵ�
	,m_pAnimationFileData(NULL)//��Ч�ļ�
	,m_pAnimation(NULL)//����
	,pAnimationAction(NULL)//�ظ����Ŷ���
	,m_pAnimationGrayLayer(NULL)
	,m_bHeroRun(false)
	,m_iRunTickTime(0)
	,m_iRunTickCount(0)
	,m_bBoxOpen(false)
	,m_iOpenTickTime(0)
	,m_pLieRenJiHuoAnimation0(NULL)
	,m_pLieRenJiHuoAnimation1(NULL)
	,m_pLieRenJiHuoAnimation2(NULL)
	,m_pLieRenJiHuoAnimation3(NULL)
	,m_pLieRenKaiQiAnimation(NULL)
	,m_iLieRenSelected(0)
{
	m_WindowType   = _TYPED_WINDOW_MINEAREA_WINDOW_;
	m_WindowZOrder = _TYPED_WINDOW_ZORDER_NORMAL_;
}

MineAreaWindow::~MineAreaWindow()
{
	m_pRoot = NULL;
}

bool    MineAreaWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_MINEAREAWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_MINEAREAWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_FADEOUT_MINEAREAWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_MINEAREAWINDOW_, true);

	RegisterEvent(_TYPED_EVENT_MINING_ENTERGOBLINAREA_GETDATA_, true);//����ؾ���������
	RegisterEvent(_TYPED_EVENT_MINING_STOPMINING_GETDATA_, true);//ֹͣ�ɿ�������
	RegisterEvent(_TYPED_EVENT_MINING_ENTERDWARVENAREA_GETDATA_, true);//���밫�˿�������
	RegisterEvent(_TYPED_EVENT_MINING_ENTERDRAGONAREA_GETDATA_, true);//���������������
	RegisterEvent(_TYPED_EVENT_MINING_STARTMINING_GETDATA_, true);//��ʼ�ɿ�ɹ�
	RegisterEvent(_TYPED_EVENT_MINING_ENTERHUNTMINING_GETDATA_, true);//����Ѱ����÷���
	RegisterEvent(_TYPED_EVENT_MINING_HUNTMININGRESULT_GETDATA_, true);//Ѱ���������
	RegisterEvent(_TYPED_EVENT_MINING_HUNTHELLOMONEY_GETDATA_, true);//���к���ý�Ǯ����
	RegisterEvent(_TYPED_EVENT_MINING_HUNTBUYMINERAL_GETDATA_, true);//ֱ�ӹ���Ѱ��ԭ��ķ���

	RegisterEvent(_TYPED_EVENT_MINING_HUNTASKFORFRIEND_GETDATA_, true);//����Ӻ��ѷ���

	RegisterEvent(_TYPED_EVENT_MINING_DWARVEN_LOOT_GETDATA_, true);//���˿�������λ����������
	RegisterEvent(_TYPED_EVENT_DWARVEN_PAGEINFO_REFRESH_CONFIRM_, true);//���˿�����Ϣ��ϸ������ȷ���¼�

	RegisterEvent(_TYPED_EVENT_BOSS_HUNT_LEFTTIME_, true);		//Ѱ��ʣ���������

	RegisterEvent(_TYPED_EVNET_HUNT_LIEREN_CHAKAN_GETDATA_, true);			//�鿴������ϸ��Ϣ����
	RegisterEvent(_TYPED_EVENT_HUNT_LIEREN_QIANGDUO_NO_GETDATA_, true);		//��������ĳ�����˷���
	RegisterEvent(_TYPED_EVENT_HUNT_LIEREN_QIANGDUO_NO_CONFIRM_, true);		//ȷ�Ϸ�������ĳ�����ˣ���ʾ�򷵻�

	return IWindow::Init();
}

bool    MineAreaWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		
		m_pRoot = m_pRootNode;
		m_pRoot->setAnchorPoint(CCPointZero);
		m_pRoot->setPosition(CCPointZero);
		return true;
	} 
	while (false);

	return false;
}

void    MineAreaWindow::Tick()
{
	_workTick();

	if(m_iShowPage == _PAGE_HUNTMINE_)
		_heroHuntRun();

	IWindow::Tick();
}

void    MineAreaWindow::Destroy()
{
	m_iBackWindow = 0;

	//m_iShowPage = 0;

	m_iDwarvenShowPage = 0;

	//m_iDragonSelectOwner = 0;

	m_pSkeletonNode = NULL;	//Ӣ�۽�ɫ,��������
	m_pAnimationPlayNode = NULL;//���Ŷ����ڵ�
	m_pAnimationFileData = NULL;//��Ч�ļ�
	m_pAnimation = NULL;//����
	pAnimationAction = NULL;//�ظ����Ŷ���
	m_pAnimationGrayLayer = NULL;
	m_bHeroRun = false;

	m_iRunTickCount = 0;

	m_bBoxOpen = false;
	m_iOpenTickTime = 0;

	m_pLieRenJiHuoAnimation0 = NULL;
	m_pLieRenJiHuoAnimation1 = NULL;
	m_pLieRenJiHuoAnimation2 = NULL;
	m_pLieRenJiHuoAnimation3 = NULL;
	m_pLieRenKaiQiAnimation = NULL;

	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_ROLESTATUSWINDOW_);

	IWindow::Destroy();
}


void MineAreaWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if(iEventType == _TYPED_EVENT_SHOW_MINEAREAWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if(iEventType == _TYPED_EVENT_HIDE_MINEAREAWINDOW_)
	{
		Destroy();
	}
	else if(iEventType == _TYPED_EVENT_FADEOUT_MINEAREAWINDOW_)
	{
		OnFadeoutWindowEventHandler(paramList);
	}
	else if(iEventType == _TYPED_EVENT_UPDATE_MINEAREAWINDOW_)
	{

	}
	else if(iEventType == _TYPED_EVENT_MINING_ENTERGOBLINAREA_GETDATA_)
	{
		Function_GetEnterGoblinData();
	}
	else if(iEventType == _TYPED_EVENT_MINING_STOPMINING_GETDATA_)
	{
		Function_GetStopMiningResult();
	}
	else if(iEventType == _TYPED_EVENT_MINING_ENTERDWARVENAREA_GETDATA_)
	{
		Function_GetEnterDwarvenData();
	}
	else if(iEventType == _TYPED_EVENT_MINING_ENTERDRAGONAREA_GETDATA_)
	{
		Function_GetEnterDragonData();
	}
	else if(iEventType == _TYPED_EVENT_MINING_STARTMINING_GETDATA_)
	{
		Function_GetStartMiningResult();
	}
	else if(iEventType == _TYPED_EVENT_MINING_ENTERHUNTMINING_GETDATA_)
	{
		Function_GetEnterHuntData();
	}
	else if(iEventType == _TYPED_EVENT_MINING_HUNTMININGRESULT_GETDATA_)
	{
		Function_GetHuntingResult();
	}
	else if(iEventType == _TYPED_EVENT_MINING_HUNTHELLOMONEY_GETDATA_)
	{
		Function_GetHelloFriendResult();
	}
	else if(iEventType == _TYPED_EVENT_MINING_HUNTBUYMINERAL_GETDATA_)
	{
		Function_GetBuyMinralResult();
	}
	else if(iEventType == _TYPED_EVENT_MINING_HUNTASKFORFRIEND_GETDATA_)
	{
		Function_GetAskFriendResult();
	}
	else if(iEventType == _TYPED_EVENT_MINING_DWARVEN_LOOT_GETDATA_)
	{
		Function_GetDwarvenLootResult();
	}
	else if(iEventType == _TYPED_EVENT_DWARVEN_PAGEINFO_REFRESH_CONFIRM_)
	{
		Function_GetDwarvenPageInfoChangedConfirm();
	}
	else if(iEventType == _TYPED_EVENT_BOSS_HUNT_LEFTTIME_)
	{
		int lefttime = atoi((*paramList.begin()).c_str());
		Function_HuntLeftTimeUpdate(lefttime);
	}
	else if(iEventType == _TYPED_EVNET_HUNT_LIEREN_CHAKAN_GETDATA_)
	{
		Function_HuntLieRenChaKan();
	}
	else if(iEventType == _TYPED_EVENT_HUNT_LIEREN_QIANGDUO_NO_GETDATA_)
	{
		Function_HuntLieRenQiangDuoNo();
	}
	else if(iEventType == _TYPED_EVENT_HUNT_LIEREN_QIANGDUO_NO_CONFIRM_)
	{
		MININGDATAHANDLER->ToServerQiangDuoLieRenNo(m_iLieRenSelected);
	}
}

void MineAreaWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	int page = 0;
	if(this->IsVisible())
	{
		page = m_iShowPage;
	}
	else
	{
		page = -1;
	}
	std::list<std::string>::iterator it = paramList.begin();
	if(paramList.size() > 0)
	{
		m_iShowPage = atoi((*it).c_str());
		if(page == m_iShowPage)
		{
			Show(true);
			return;
		}
	}
	if(paramList.size() > 1)
	{
		it++;
		m_iBackWindow = atoi((*it).c_str());
	}

	_initLayout();

	_mapBtn();
	
	_requestData();

	//_setPage();

	Show(true);
}


void MineAreaWindow::OnFadeoutWindowEventHandler(std::list<std::string>& paramList)
{


}


void MineAreaWindow::_initLayout()
{
	m_pRoot->removeAllChildrenWithCleanup(true);

	if(m_iShowPage == _PAGE_GOBLINAREA_)
	{
		PushEvent(_TYPED_EVENT_HIDE_ROLESTATUSWINDOW_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_CHATWINDOW_);
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kGOBLINAREAWINDOW, m_pRoot);
	}
	else if(m_iShowPage == _PAGE_DWARVENAREA_)
	{
		PushEvent(_TYPED_EVENT_HIDE_ROLESTATUSWINDOW_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_CHATWINDOW_);
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kDWARVENAREAWINDOW, m_pRoot);
	}
	else if(m_iShowPage == _PAGE_DRAGONAREA_)
	{
		PushEvent(_TYPED_EVENT_HIDE_ROLESTATUSWINDOW_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_CHATWINDOW_);
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kDRAGONAREAWINDOW, m_pRoot);
	}
	else if(m_iShowPage == _PAGE_HUNTMINE_)
	{
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kHUNTMININGWINDOW, m_pRoot);

		_showHuntTipPage(false);
		_showHuntTipPage2(false);
		_clearMonster();

		//��ʾ����״̬��
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_ROLESTATUSWINDOW_, _to_event_param_(_TYPED_WINDOW_MINEAREA_WINDOW_));
		//��ʾ���촰��
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_CHATWINDOW_);

		_initHuntHero();
		_initHuntMap();
	}

}

void MineAreaWindow::_setPage()
{
	//note : �˺����Ѳ��ٵ���
	if(m_iShowPage == _PAGE_GOBLINAREA_)
	{
		_setGoblinPage();
	}
	else if(m_iShowPage == _PAGE_DWARVENAREA_)
	{
		//��һ���ߵ�
		_setDwarvenPage();
	}
	else if(m_iShowPage == _PAGE_DRAGONAREA_)
	{
		_setDragonPage();
	}
	else if(m_iShowPage == _PAGE_HUNTMINE_)
	{
		_setHuntPage();
	}
}

void MineAreaWindow::_setGoblinPage()
{
	GoblinAreaData * data = MININGDATAHANDLER->m_pGoblinAreaData;
	if(data == NULL)
		return;
	
	char temp[512] = {0};

	if(data->workedTime >= 0)
	{//�ڲɿ�
		//�ȼ�
		NFC_setLabelStringInt(gSitLevel, m_pRoot, ROLEINFODATAHANDLER->m_pRIData->level_, true);
		//����
		NFC_setDTHeroQualiy(gSitQuality,m_pRoot,NFC_GetTeamHero()->getHeroQualiy());
		//ͷ��
		NFC_setDTHeroIcon(gSitQuality,m_pRoot,NFC_GetTeamHero()->getHeroIconID(),true);
		//����
		NFC_setLabelString(gSitNameValue, m_pRoot, ROLEINFODATAHANDLER->m_pRIData->name_, true);
		//ʱ��
		int sec = data->workedTime;
		sprintf(temp, "%02d:%02d:%02d", sec / 3600, (sec % 3600) / 60, (sec % 3600) % 60);
		NFC_setLabelString(gSitTimeValue, m_pRoot, temp, true);
		//�ۼƻ��
		NFC_setLabelStringInt(gSitTotalValue, m_pRoot, data->outPut, true);
		//��ť���ܺ���
		//���ڿ���ʾֹͣ�ɼ�
		CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(gStartStopBtn);
		CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(gStartStopBtn);
		item->setIDX(1);
		NFC_setLabelString(gStartStopLabel, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_STOP_MINING_), true);
	}
	else
	{//���ڲɿ�
		NFC_showNode(gSitLevel, m_pRoot, false);
		NFC_setDTHeroIconVisiable(gSitQuality,m_pRoot,false);
		NFC_setDTHeroQualiy(gSitQuality,m_pRoot,0);
		//NFC_setPicForCCSprite(gSitQuality, m_pRoot, varConfig::getCardNormalBGFilePath().c_str(), true);
		//NFC_showNode(gSitIcon, m_pRoot, false);
		NFC_showNode(gSitNameValue, m_pRoot, false);
		NFC_showNode(gSitTimeValue, m_pRoot, false);
		NFC_showNode(gSitTotalValue, m_pRoot, false);
		//��ť���ܺ���
		//�����ڿ���ʾ��ʼ�ɼ�
		CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(gStartStopBtn);
		CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(gStartStopBtn);
		item->setIDX(0);
		NFC_setLabelString(gStartStopLabel, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_START_MINING_), true);
	}
}

void MineAreaWindow::_setDwarvenPage()
{
	DwarvenAreaData * data = MININGDATAHANDLER->m_pDwarvenAreaData;
	if(data == NULL)
		return;

	char temp[512] = {0};

	//

	//ʣ���������
	sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_LEFT_QIANG_TIMES_).c_str(), data->leftLootMoney);
	NFC_setLabelString(dLeftTimeLabel, m_pRoot, temp, true);

	//����ҳ����ʾ��Ϣ
	//ҳ��
	sprintf(temp, "%d/%d", m_iDwarvenShowPage + 1, KUANGDONG_DWARVEN_PAGES);
	NFC_setLabelString(dPageLabel, m_pRoot, temp, true);
	//����λ��
	int index = m_iDwarvenShowPage * 4;
	
	for(int i = 0; i < 4; ++i, index ++)
	{
		DwarvenSitData * sit = data->sitData[index];
		if(sit->isNull > 0)
		{//û�����
			NFC_showNode(dSitLevel0 + i * 16, m_pRoot, false);//�ȼ�
			NFC_setDTHeroIconVisiable(dSitQuality0 + i * 16,m_pRoot,false);//ͷ��
			NFC_setDTHeroQualiy(dSitQuality0 + i * 16,m_pRoot,0);//����		
			//NFC_setPicForCCSprite(dSitQuality0 + i * 17, m_pRoot, varConfig::getCardNormalBGFilePath(), true);//����
			//NFC_showNode(dSitIcon0 + i * 17, m_pRoot, false);//ͷ��
			NFC_showNode(dSitMyTip0 + i * 16, m_pRoot, false);//�ҵı�־
			NFC_showNode(dSitNameValue0 + i * 16, m_pRoot, false);//����
			NFC_showNode(dSitTimeValue0 + i * 16, m_pRoot, false);//ʱ��
			NFC_showNode(dSitTotalValue0 + i * 16, m_pRoot, false);//�ۼƻ�þ���
			NFC_setLabelString(dStartStopLabel0 + i * 16, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_START_MINING_).c_str(), true);//��ť��ʾ����λ
			CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(dStartStopBtn0 + i * 16);
			CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(dStartStopBtn0 + i * 16);
			item->setIDX(0);
		}
		else
		{//�����,��Ҫ�ж����ǲ������Լ�
			NFC_setLabelStringInt(dSitLevel0 + i * 16, m_pRoot, sit->playerLevel, true);//�ȼ�
			NFC_setDTHeroIcon(dSitQuality0 + i * 16,m_pRoot,sit->heroIconId,true);//ͷ��
			NFC_setDTHeroQualiy(dSitQuality0 + i * 16,m_pRoot,sit->heroQuality);//����
			//NFC_setPicForCCSprite(dSitQuality0 + i * 17, m_pRoot, varConfig::getCardBGFilePath(sit->heroQuality), true);//����
			//NFC_setPicForCCSprite(dSitIcon0 + i * 17, m_pRoot, RESOURCEDAIDMANAGER->getDataByID(sit->heroIconId), true);//ͷ��
			//NFC_setPicScale(dSitIcon0 + i * 17, m_pRoot, CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f);
			NFC_setLabelString(dSitNameValue0 + i * 16, m_pRoot, sit->playerName, true);//����
			
			int sec = sit->workedTime;
			sprintf(temp, "%d:%d:%d", sec / 3600, (sec % 3600) / 60, (sec % 3600) % 60);
			NFC_setLabelString(dSitTimeValue0 + i * 16, m_pRoot, temp, true);//ʱ��
			NFC_setLabelStringInt(dSitTotalValue0 + i * 16, m_pRoot, sit->param, true);//�ۼƻ��/ս��


			if(sit->playerId == ROLEINFODATAHANDLER->m_pRIData->instanceId_)
			{//���Լ�,��ʾ�ۼƻ��,��ť��ʾֹͣ�ɿ�
				NFC_setLabelString(dSitTotal0 + i * 16, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_TOTALOUTPUT_LABEL), true);
				NFC_setLabelString(dStartStopLabel0 + i * 16, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_STOP_MINING_), true);
				NFC_showNode(dSitMyTip0 + i * 16, m_pRoot, true);//�ҵı�־

				CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(dStartStopBtn0 + i * 16);
				CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(dStartStopBtn0 + i * 16);
				item->setIDX(1);
			}
			else
			{//�����,��ʾ��ҵ�ս������ť��ʾ����λ
				NFC_setLabelString(dSitTotal0 + i * 16, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_CAPA_LABEL_), true);
				NFC_setLabelString(dStartStopLabel0 + i * 16, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_QIANGKUANGWEI_), true);
				NFC_showNode(dSitMyTip0 + i * 16, m_pRoot, false);//�ҵı�־

				CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(dStartStopBtn0 + i * 16);
				CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(dStartStopBtn0 + i * 16);
				item->setIDX(2);
			}

			
		}
	}

}

void MineAreaWindow::_setDragonPage()
{
	DragonAreaData * data = MININGDATAHANDLER->m_pDragonAreaData;
	if(data == NULL)
		return;

	char temp[512] = {0};


	//����
	for(int i = 0; i < 4; ++i)
	{
		DragonOwnerData * owner = data->mineOwnerData[i];
		NFC_setDTHeroIcon(nOwnerQuality0 + i * 6,m_pRoot,owner->heroIconId,true);	//ͼ��
		NFC_setDTHeroQualiy(nOwnerQuality0 + i * 6,m_pRoot,owner->heroQuality);	//����
		//NFC_setPicForCCSprite(nOwnerQuality0 + i * 6, m_pRoot, varConfig::getCardBGFilePath(owner->heroQuality), true);	//����
		//NFC_setPicForCCSprite(nOwnerIcon0 + i * 6, m_pRoot, RESOURCEDAIDMANAGER->getDataByID(owner->heroIconId), true);	//ͼ��
		//NFC_setPicScale(nOwnerIcon0 + i * 6, m_pRoot, CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f);
		NFC_setLabelString(nOwnerName0 + i * 6, m_pRoot, owner->playerName, true);//����
		NFC_setLabelStringInt(nOwnerLv0 + i * 6, m_pRoot, owner->playerLevel, true);//�ȼ�
	}

	//ѡ��ѡ����m_iDragonSelectOwner��ӵ����
	CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(nOwnerBg0 + m_iDragonSelectOwner * 6);
	CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(nOwnerBg0 + m_iDragonSelectOwner * 6);
	item->selected(true);
	m_pDragonSelectOwner = item;
	//�Ҳ�
	_setDragonRightPart();
}

void MineAreaWindow::_setDragonRightPart()
{
	char temp[512] = {0};

	DragonAreaData * data = MININGDATAHANDLER->m_pDragonAreaData;
	if(data == NULL)
		return;

	DragonOwnerData * owner = data->mineOwnerData[m_iDragonSelectOwner];

	//����
	sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_OWNER_NAME_).c_str(), owner->playerName.c_str());
	NFC_setLabelString(nOwnerName, m_pRoot, temp, true);
	//ս��
	sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_OWNER_CAPA_).c_str(), owner->btlCapa);
	NFC_setLabelString(nOwnerCapa, m_pRoot, temp, true);
	
	if (owner->playerId == ROLEINFODATAHANDLER->m_pRIData->instanceId_ && !owner->isMining && MININGDATAHANDLER->m_isFBDragon)
	{
		MININGDATAHANDLER->ToServerStartMining(m_iShowPage, m_iDragonSelectOwner);
		MININGDATAHANDLER->m_isFBDragon = false;
	}


	if(owner->playerId == ROLEINFODATAHANDLER->m_pRIData->instanceId_)
	{//���ҵĺ���

		//sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_MINING_FRIEND_).c_str(), owner->miningFriendCount);
		//NFC_setLabelString(nOwnerDesc, m_pRoot, temp, true);//˵��
		//MININGDATAHANDLER->ToServerStartMining(m_iShowPage, m_iDragonSelectOwner);
		if(owner->isMining)
		{//���ڲɿ�
			//��ʾ�ҵ���Ϣ
			for(int i = nSitBg; i <= nSrartStopLabel; ++i)
			{
				NFC_showNode(i, m_pRoot, true);
			}
			for(int k = nOwnerCaiKuang; k <= nOwnerCaiKuangLabel; ++k)
			{
				NFC_showNode(k, m_pRoot, false);
			}
			for(int j = nOwnerTiaoZhan; j <= nOwnerJewelLabel; ++j)
			{
				NFC_showNode(j, m_pRoot, false);
			}

			NFC_setLabelStringInt(nSitLevel, m_pRoot, ROLEINFODATAHANDLER->m_pRIData->level_, true);//�ȼ�
			//NFC_setPicForCCSprite(nSitQuality, m_pRoot, varConfig::getCardBGFilePath(RoleHeroSkinsDataHandler::get_instance2()->GetCurHeroSkinItem()->getHeroQualiy()).c_str(), true);//����			
			//NFC_setPicForCCSprite(nSitIcon, m_pRoot, RESOURCEDAIDMANAGER->getDataByID(RoleHeroSkinsDataHandler::get_instance2()->GetCurHeroSkinItem()->getHeroIconID()).c_str(), true);//ͷ��
			//NFC_setPicScale(nSitIcon, m_pRoot, CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f);
			//ͷ��
			NFC_setDTHeroIcon(nSitIcon, m_pRoot, RoleHeroSkinsDataHandler::get_instance2()->GetCurHeroSkinItem()->getHeroIconID(), true);
			//Ʒ��
			NFC_setDTHeroQualiy(nSitIcon, m_pRoot, RoleHeroSkinsDataHandler::get_instance2()->GetCurHeroSkinItem()->getHeroQualiy());

			NFC_setLabelString(nSitNameValue, m_pRoot, ROLEINFODATAHANDLER->m_pRIData->name_, true);//����			
			int sec = owner->workedTime;
			sprintf(temp, "%d:%d:%d", sec / 3600, (sec % 3600) / 60, (sec % 3600) % 60);
			NFC_setLabelString(nSitTimeValue, m_pRoot, temp, true);//ʱ��			
			NFC_setLabelStringInt(nSitTotalValue, m_pRoot, owner->outPut, true);//�ۼƻ��
			NFC_setLabelString(nSrartStopLabel, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_STOP_MINING_).c_str(), true);//��ť��ʾ����λ

			CCMenu * menu_ = (CCMenu *)m_pRoot->getChildByTag(nStartStopBtn);
			CMenuItemSprite * item_ = (CMenuItemSprite *)menu_->getChildByTag(nStartStopBtn);
			item_->setIDX(1);
		}
		else
		{//���ڲɿ�
			for(int i = nSitBg; i <= nSrartStopLabel; ++i)
			{
				NFC_showNode(i, m_pRoot, false);
			}

			for(int j = nOwnerTiaoZhan; j <= nOwnerJewelLabel; ++j)
			{
				NFC_showNode(j, m_pRoot, false);
			}

			for(int k = nOwnerCaiKuang; k <= nOwnerCaiKuangLabel; ++k)
			{
				NFC_showNode(k, m_pRoot, true);
			}
		}
	}
	else
	{//���Ǻ��ѣ� ��ս����ʾ��ʯ��

		//sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_OWNER_NOT_FRIEND_).c_str(), owner->playerName.c_str());
		//NFC_setLabelString(nOwnerDesc, m_pRoot, temp, true);//˵��
		NFC_setLabelStringInt(nOwnerJewelLabel, m_pRoot, data->challengePrice, true);
		//��ʾ��ս��ؽ���
		for(int j = nOwnerTiaoZhan; j <= nOwnerJewelLabel; ++j)
		{
			NFC_showNode(j, m_pRoot, true);
		}

		for(int k = nOwnerCaiKuang; k <= nOwnerCaiKuangLabel; ++k)
		{
			NFC_showNode(k, m_pRoot, false);
		}

		//�����ҵ���Ϣ
		for(int i = nSitBg; i <= nSrartStopLabel; ++i)
		{
			NFC_showNode(i, m_pRoot, false);
		}
	}

}

void MineAreaWindow::_setHuntPage()
{
	//���õ�ǰҳ�����ʾ
	HuntData * data = MININGDATAHANDLER->m_pHuntData;

	if(data == NULL)
		return;

	//������
	CProgressInnerBar * bar = (CProgressInnerBar *)m_pRoot->getChildByTag(hProgress);
	float prog = (float)data->huntTimes / data->maxHuntTimes;
	bar->setPercent(prog);
	//����
	char temp[128] = {0};
	sprintf(temp, "%d/%d", data->huntTimes, data->maxHuntTimes);
	NFC_setLabelString(hProgressLabel, m_pRoot, temp, true);
	
	//˵��
	NFC_showNode(hDesc, m_pRoot, false);

}

void MineAreaWindow::_setHuntTipPage()
{
	HuntResult * data = MININGDATAHANDLER->m_pHuntResult;
	if(data == NULL)
		return;

	char temp[512] = {0};

	//�жϽ������
	if(data->type == 0)
	{//����
		return;
	}
	else if(data->type == 1)
	{//���
		//ͷ��
		NFC_setDTHeroIcon(hTipIcon,m_pRoot,data->playerHeroIconId,true);
		NFC_setDTHeroQualiy(hTipIcon,m_pRoot,data->playerHeroQuality);

		//NFC_setPicForCCSprite(hTipIcon, m_pRoot, RESOURCEDAIDMANAGER->getDataByID(data->playerHeroIconId), true);
		//˵�Ļ�,12000--12003
		int id = rand() % 5 + _STRING_HUNT_SAYINGBEGIN_HUMAN_;
		NFC_setLabelString(hTipSay, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(id), true);
		//������˭
		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_HUNT_MEET_).c_str(), data->playerName.c_str(), data->playerBtlCapa);
		NFC_setLabelString(hTipMeet, m_pRoot, temp, true);
		//�Ӻ��ѣ����к�
		if(data->playerIsFriend > 0)
		{//���к�
			NFC_setLabelString(hTipBtn0Label, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_HUNT_HELLOFRIEND_), true);
			CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(hTipBtn0);
			CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(hTipBtn0);
			item->setIDX(0);
		}
		else
		{//�Ӻ���
			NFC_setLabelString(hTipBtn0Label, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_HUNT_ADDFRIEND_), true);

			CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(hTipBtn0);
			CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(hTipBtn0);
			item->setIDX(1);
		}
		//����
		NFC_setLabelString(hTipBtn1Label, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_HUNT_QIANGDUO_), true);
		//���ع���۸�
		NFC_showNode(hTipBuyMinralPrice, m_pRoot, false);
		NFC_showNode(hTipBuyMinralJewelPic, m_pRoot, false);
	}
	else if(data->type == 2)
	{//����
		NFC_setDTHeroIcon(hTipIcon,m_pRoot,data->orcHeroIconId,true);
		//NFC_setPicForCCSprite(hTipIcon, m_pRoot, RESOURCEDAIDMANAGER->getDataByID(data->orcHeroIconId), true);
		//˵�Ļ�,12000--12003
		int id = rand() % 5 + _STRING_HUNT_SAYINGBEGIN_NPC_;
		NFC_setLabelString(hTipSay, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(id), true);
		//������˭
		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_HUNT_MEET_).c_str(), data->orcName.c_str(), data->orcBtlCapa);
		NFC_setLabelString(hTipMeet, m_pRoot, temp, true);
		//����
		NFC_setLabelString(hTipBtn0Label, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_HUNT_QUZHU_), true);
		//�����ʯ
		NFC_setLabelString(hTipBtn1Label, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_HUNT_BUYMINRAL_), true);
		//�����ʯ�۸�
		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(_STRING_HUNT_BUYMINRALPRICE_).c_str(), data->orcBuyPrice);
		NFC_setLabelString(hTipBuyMinralPrice, m_pRoot, temp, true);
	}

}

void MineAreaWindow::_showHuntTipPage(bool show)
{
	for(int i = hGrey; i <= hTipBuyMinralJewelPic; ++i)
	{
		NFC_showNode(i, m_pRoot, show);
	}

// 	if(show == false)
// 	{
// 		MaskNode * node = (MaskNode *)m_pRoot->getChildByTag(hMonsterMask);
// 		node->removeAllChildrenWithCleanup(true);
// 
// 	}

}


void MineAreaWindow::_setHuntTipPage2()
{
	HuntLieRenInfo * data = MININGDATAHANDLER->m_pHuntLieRenData;

	if(data == NULL)
		return;

	//����
	NFC_setLabelString(hTipTitle2, m_pRoot, data->name, true);
	//�ȼ�˵��
	NFC_setLabelString(hTipLevelDesc2, m_pRoot, data->heroLevelDesc, true);
	//˵��
	NFC_setLabelString(hTipDesc2, m_pRoot, 2110 + m_iLieRenSelected, true);
	//�Ƿ񼤻���
	if(data->isActive > 0)
	{
		//��ʾ����
		NFC_setLabelString(hProability2, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(2116 + data->probability), true);

		//��������ʾ����װ������
		NFC_showNode(hTipNoLieRenLabel2, m_pRoot, false);
		NFC_showNode(hTipAwardBoard2, m_pRoot, true);
		NFC_showNode(hTipAwardName2, m_pRoot, true);

		DTAwardBoard * dtab = (DTAwardBoard *)m_pRoot->getChildByTag(hTipAwardBoard2);
		if(data->type == kDT_AWARD_OBJECT)
		{//��Ʒ
			dtab->ChangeObject(data->quality, data->iconId, data->count);
			dtab->setEnabled(true);
			dtab->setIDX(data->templateId);
		}
		else if(data->type == kDT_AWARD_MONEY)
		{//��Ǯ
			dtab->ChangeObject(_GOLD_QUALITY_RESID_, CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_GOLD), data->count);
			dtab->setEnabled(false);
			data->itemName = SysLangDataManager::get_instance2()->GetSysLangById(kDT_MONEY_TID);
		}
		else if(data->type == kDT_AWARD_EXP)
		{//����
			dtab->ChangeObject(_EXP_QUALITY_RESID_, CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_EXP), data->count);
			dtab->setEnabled(false);
			data->itemName = SysLangDataManager::get_instance2()->GetSysLangById(kDT_EXP_TID);
		}
		else if(data->type == kDT_AWARD_DIAMOND)
		{//��ʯ
			dtab->ChangeObject(_DIAMOND_QUALITY_RESID_, CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_DIAMOND), data->count);
			dtab->setEnabled(false);
			data->itemName = SysLangDataManager::get_instance2()->GetSysLangById(kDT_DIAMOND_TID);
		}
		else if(data->type == kDT_AWARD_PRESTIGE)
		{//����
			dtab->ChangeObject(_PREGIST_QUALITY_RESID_, CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_PRESTAGE), data->count);
			dtab->setEnabled(false);
			data->itemName = SysLangDataManager::get_instance2()->GetSysLangById(kDT_PRESTIGE_TID);
		}
		else if(data->type == kDT_AWARD_POWER)
		{//����
			dtab->ChangeObject(_POWER_QUALITY_RESID_, CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_ICON_ENG), data->count);
			dtab->setEnabled(false);
			data->itemName = SysLangDataManager::get_instance2()->GetSysLangById(kDT_POWER_TID);
		}
		//����
		NFC_setLabelString(hTipAwardName2, m_pRoot, data->itemName, true);

		//��ť״̬
		NFC_setEnabledForMenuItem(hTipNoBtn2, hTipNoBtn2, m_pRoot, true);
		NFC_setEnabledForMenuItem(hTipYesBtn2, hTipYesBtn2, m_pRoot, true);
	}
	else
	{	
		//��ʾ����
		NFC_showNode(hProability2, m_pRoot, false);
		//δ������ʾδ����ľ���
		NFC_setLabelString(hTipNoLieRenLabel2, m_pRoot, 2100 + m_iLieRenSelected, true);
		NFC_showNode(hTipAwardBoard2, m_pRoot, false);
		NFC_showNode(hTipAwardName2, m_pRoot, false);

		//��ť״̬
		NFC_setEnabledForMenuItem(hTipNoBtn2, hTipNoBtn2, m_pRoot, false);
		NFC_setEnabledForMenuItem(hTipYesBtn2, hTipYesBtn2, m_pRoot, false);
	}
	//��������
	char temp[128] = {0};
	if(data->isActive > 0)
		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(2109).c_str(), data->spentTili);
	else
		sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(2108).c_str(), data->spentTili);
	NFC_setLabelString(hTipSpentLabel2, m_pRoot, temp, true);
}

void MineAreaWindow::_showHuntTipPage2(bool show)
{
	for (int i = hGrey2; i <= hTipCloseBtn2; ++i)
	{
		NFC_showNode(i, m_pRoot, show);
	}
}

void MineAreaWindow::_clearMonster()
{
	MaskNode * node = (MaskNode *)m_pRoot->getChildByTag(hMonsterMask);
	node->removeAllChildrenWithCleanup(true);
}

void MineAreaWindow::_playHuntMeetAnimation()
{
	//������������
	HuntResult * data = MININGDATAHANDLER->m_pHuntResult;
	if(data == NULL)
		return;

	if(data->type == 0)
	{//����
		MaskNode * node = (MaskNode *)m_pRoot->getChildByTag(hMonsterMask);
		CCSprite * sp = CCSprite::create(PIC_HUNT_BOX_);
		sp->setAnchorPoint(CCPointZero);
		sp->setPosition(CCPointZero);
		node->addChild(sp, 0, 10);

		float time = CLIENTCONSTDATAMANGER->getValueByKey(HUNT_MINING_MOVETIME) / 1000.0f;
		float length = CLIENTCONSTDATAMANGER->getValueByKey(HUNT_MINING_MOVETIME) / 1000.0f * DOTATribeApp::get_instance2()->GetFPS() * 10;
		CCActionInterval * moveto = CCMoveTo::create(time, ccp(-length, sp->getPositionY()));
		CCCallFunc * funcall = CCCallFunc::create(this, callfunc_selector(MineAreaWindow::HuntAnimationCallBackFunction));
		CCFiniteTimeAction * seq = CCSequence::create(moveto, funcall, NULL);
		sp->runAction(seq);

	}
	else
	{//��Һ����˻����¼�
		MaskNode * node = (MaskNode *)m_pRoot->getChildByTag(hMonsterMask);
		int shapeId = 0;
		if(data->type == 1)
		{
			shapeId = data->playerHeroShapeId;
		}
		else if(data->type == 2)
		{
			shapeId = data->orcHeroShapeId;
		}
		else if(data->type == 3)
		{
			shapeId = data->lieRenShapeId;
		}

		if(shapeId == 0)
			return;

		RoleShapeData *pData = RoleShapeDataManager::get_instance2()->GetRoleShapeById(shapeId);
		CCSkeletonAnimation * skeletonNode = CCSkeletonAnimation::createWithFile(pData->mShapeAnimationFileDaiJi,pData->mShapeAnimationImage);
		skeletonNode->setRotationY(180);
		if(skeletonNode)
			skeletonNode->setAnimation("DaiJi", true); 
		skeletonNode->setAnchorPoint(CCPointZero);
		skeletonNode->setPosition(CCPointZero);
		node->addChild(skeletonNode);
		_addShadow(skeletonNode);
		float time = CLIENTCONSTDATAMANGER->getValueByKey(HUNT_MINING_MOVETIME) / 1000.0f;
		float length = CLIENTCONSTDATAMANGER->getValueByKey(HUNT_MINING_MOVETIME) / 1000.0f * DOTATribeApp::get_instance2()->GetFPS() * 10;
		CCActionInterval * moveto = CCMoveTo::create(time, ccp(-length, 0));
		CCCallFunc * funcall = CCCallFunc::create(this, callfunc_selector(MineAreaWindow::HuntAnimationCallBackFunction));
		CCFiniteTimeAction * seq = CCSequence::create(moveto, funcall, NULL);
		
		skeletonNode->runAction(seq);
	}

}

void MineAreaWindow::_initHuntHero()
{
	//������������
	MaskNode * node = (MaskNode *)m_pRoot->getChildByTag(hHeroMask);
	const UIViewData &dd = node->GetViewData();
	if(m_pSkeletonNode) 
		m_pSkeletonNode->removeFromParentAndCleanup(true);
	unsigned short shapeID=RoleHeroSkinsDataHandler::get_instance2()->GetCurHeroSkinItem()->getHeroShapeID();
	assert(shapeID>=0);
	RoleShapeData *pData = RoleShapeDataManager::get_instance2()->GetRoleShapeById(shapeID);
	m_pSkeletonNode = CCSkeletonAnimation::createWithFile(pData->mShapeAnimationFileDaiJi,pData->mShapeAnimationImage); 
	m_pSkeletonNode->setScale(dd.scale_);
	if(m_pSkeletonNode)
		m_pSkeletonNode->setAnimation("DaiJi", true); 
	m_pSkeletonNode->setAnchorPoint(ccp(dd.anchorx_, dd.anchory_));
	m_pSkeletonNode->setPosition(CCPointZero);
	node->addChild(m_pSkeletonNode, 0, 0);
	_addShadow(node);
	m_iRunTickTime = CLIENTCONSTDATAMANGER->getValueByKey(HUNT_MINING_MOVETIME) * DOTATribeApp::get_instance2()->GetFPS() / 1000;//�ⲿ����Ϊ2200����,����Ϊ֡��
}

void MineAreaWindow::_initHuntMap()
{
	m_pHuntMap0 = m_pRoot->getChildByTag(hMap0);
	m_pHuntMap1 = m_pRoot->getChildByTag(hMap1);

	m_pHuntMap1->setPositionX(m_pHuntMap0->getPositionX() + m_pHuntMap0->getContentSize().width /*- 2*/);
}

void MineAreaWindow::_moveHuntMap()
{
	if(m_pHuntMap0)
		m_pHuntMap0->setPositionX(m_pHuntMap0->getPositionX() - 10.0f);

	if(m_pHuntMap1)
		m_pHuntMap1->setPositionX(m_pHuntMap1->getPositionX() - 10.0f);

	if(m_pHuntMap0->getPositionX() < 0 - m_pHuntMap0->getContentSize().width)
	{
		//��ͼ0�ŵ�����β��
		m_pHuntMap0->setPositionX(m_pHuntMap1->getPositionX() + m_pHuntMap1->getContentSize().width);
	}
	if(m_pHuntMap1->getPositionX() < 0 - m_pHuntMap1->getContentSize().width)
	{
		//��ͼ1�ŵ�����β��
		m_pHuntMap1->setPositionX(m_pHuntMap0->getPositionX() + m_pHuntMap0->getContentSize().width);
	}

}

void MineAreaWindow::_heroHuntRun()
{
	//������
	if(m_bHeroRun)
	{//��ʼ�ܵĹ����У������ڱ��ز����ܲ��Ķ�������ͼ������ƶ�
		m_iRunTickCount++;

		_moveHuntMap();

		if(m_iRunTickCount > m_iRunTickTime)
		{//�ܶ�����

			if(m_pSkeletonNode)
				m_pSkeletonNode->setAnimation("DaiJi", true); 

			if(m_iShowPage != _PAGE_HUNTMINE_)
				return;

			//���յ�Ѱ���������
			HuntResult * data = MININGDATAHANDLER->m_pHuntResult;
			if(data == NULL)
				return;

			//�ж������������
			if(data->type == 0)
			{//���䣬���Ŷ���
				_showHuntTipPage(false);
			}
			else if(data->type == 1 || data->type == 2)
			{//�ˣ�����
				_showHuntTipPage(true);
				_setHuntTipPage();
				//�Ƴ����ֲ�
				_removeGrayLayer();
			}
			else if(data->type == 3)
			{//����Ѱ���¼�
				//�����ŵ�ǰ�����¼��Ŀ�������
				int index = data->lieRenIndex;
				MaskNode * node = (MaskNode *)m_pRoot->getChildByTag(hLieRenMask0 + index);
				if(m_pLieRenKaiQiAnimation == NULL)
					m_pLieRenKaiQiAnimation = NFC_getUnLoopFrameEffect(node->GetViewData().colorR_, this);
				node->addChild(m_pLieRenKaiQiAnimation, 0, 0);
			}

			m_bHeroRun = false;
			m_iRunTickCount = 0;
		}
	}

	//���俪��״̬
	if(m_bBoxOpen)
	{
		m_iOpenTickTime++;
		if(m_iOpenTickTime >= 20)
		{
			m_iOpenTickTime = 0;
			m_bBoxOpen = false;

			MaskNode * node = (MaskNode *)m_pRoot->getChildByTag(hMonsterMask);
			node->removeAllChildrenWithCleanup(true);
			//�Ƴ����ֲ�
			_removeGrayLayer();
		}
	}
}

void MineAreaWindow::_workTick()
{
	if(MININGDATAHANDLER->m_pGoblinAreaData)
	{
		MININGDATAHANDLER->m_pGoblinAreaData->workTick();
		if(m_iShowPage == _PAGE_GOBLINAREA_)
		{
			if(MININGDATAHANDLER->m_pGoblinAreaData->workedTime > 0)
			{
				char temp[128] = {0};
				int sec = MININGDATAHANDLER->m_pGoblinAreaData->workedTime;
				sprintf(temp, "%02d:%02d:%02d", sec / 3600, (sec % 3600) / 60, (sec % 3600) % 60);
				NFC_setLabelString(gSitTimeValue, m_pRoot, temp, true);
				//�ۼƻ��
				NFC_setLabelStringInt(gSitTotalValue, m_pRoot, MININGDATAHANDLER->m_pGoblinAreaData->outPut, true);
			}
		}
	}

	if(MININGDATAHANDLER->m_pDwarvenAreaData)
	{
		int sz = MININGDATAHANDLER->m_pDwarvenAreaData->sitData.size();
		for(int i = 0; i < sz; ++i)
		{
			MININGDATAHANDLER->m_pDwarvenAreaData->sitData[i]->workTick();
		}

		if(m_iShowPage == _PAGE_DWARVENAREA_)
		{
			int index = m_iDwarvenShowPage * 4;
			for(int i = 0; i < 4; ++i, index ++)
			{
				DwarvenSitData * sit = MININGDATAHANDLER->m_pDwarvenAreaData->sitData[index];
				if(sit->isNull <= 0)
				{//û�����
					char temp[128] = {0};
					int sec = sit->workedTime;
					sprintf(temp, "%02d:%02d:%02d", sec / 3600, (sec % 3600) / 60, (sec % 3600) % 60);
					NFC_setLabelString(dSitTimeValue0 + i * 16, m_pRoot, temp, true);//ʱ��
					NFC_setLabelStringInt(dSitTotalValue0 + i * 16, m_pRoot, sit->param, true);//�ۼƻ��/ս��
				}
			}
		}
	}

	if(MININGDATAHANDLER->m_pDragonAreaData)
	{
		int sz = MININGDATAHANDLER->m_pDragonAreaData->mineOwnerData.size();
		for(int i = 0; i < sz; ++i)
		{
			MININGDATAHANDLER->m_pDragonAreaData->mineOwnerData[i]->workTick();
		}

		if(m_iShowPage == _PAGE_DRAGONAREA_)
		{
			if(MININGDATAHANDLER->m_pDragonAreaData->mineOwnerData[m_iDragonSelectOwner]->isMining > 0)
			{//�ڲɿ�,��ʾ�ɿ�����
				char temp[128] = {0};
				int sec = MININGDATAHANDLER->m_pDragonAreaData->mineOwnerData[m_iDragonSelectOwner]->workedTime;
				if(MININGDATAHANDLER->m_pMiningData != NULL)
				{
					int max_sec = MININGDATAHANDLER->m_pMiningData->mineArea[2]->maxMiningTime * 60 * 60;
					if(sec >= max_sec)
					{
						MININGDATAHANDLER->m_pDragonAreaData->mineOwnerData[m_iDragonSelectOwner]->isMining = 0;
						MININGDATAHANDLER->m_pDragonAreaData->mineOwnerData[m_iDragonSelectOwner]->workedTime = -1;
						_setDragonRightPart();
						return;
					}
				}
				sprintf(temp, "%02d:%02d:%02d", sec / 3600, (sec % 3600) / 60, (sec % 3600) % 60);
				NFC_setLabelString(nSitTimeValue, m_pRoot, temp, true);//ʱ��
				NFC_setLabelStringInt(nSitTotalValue, m_pRoot, MININGDATAHANDLER->m_pDragonAreaData->mineOwnerData[m_iDragonSelectOwner]->outPut, true);//�ۼƻ��/ս��
			}
		}
	}

}

void MineAreaWindow::_addShadow(cocos2d::CCNode* node)
{
	//����Ӣ��Shadow���  ��ʱֱ��ʹ��ͼƬ����·��  ֮�����������  
	CCSprite* p = cocos2d::CCSprite::create();
	p->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(156));
	if(p)
	{ 
		p->setOpacity(160);
		node->addChild(p,1);
	}
}

//�������ֲ㣬������Ч��ʾʱ�����û����
void MineAreaWindow::_createGrayLayer()
{
	if(m_pAnimationGrayLayer)
	{
		return;
	}

	m_pAnimationGrayLayer = CPriorityLayerColor::create(ccc4(0,0,0,0),3000,2000,kPRIORITYLOW2);
	m_pAnimationGrayLayer->setAnchorPoint(ccp(0,0));
	m_pAnimationGrayLayer->setPosition(ccp(0,0));
	m_pRoot->addChild(m_pAnimationGrayLayer,10);
}

void MineAreaWindow::_removeGrayLayer()
{
	if(m_pAnimationGrayLayer)
		m_pAnimationGrayLayer->removeFromParentAndCleanup(true);
	m_pAnimationGrayLayer = NULL;
}

void MineAreaWindow::_mapBtn()
{
	CCMenu * menu = NULL;
	CMenuItemSprite * item = NULL;
	if(m_iShowPage == _PAGE_GOBLINAREA_)
	{
		menu = (CCMenu *)m_pRoot->getChildByTag(gStartStopBtn);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(gStartStopBtn);
		item->setTarget(this, menu_selector(MineAreaWindow::On_GoblinArea_Click));

		menu = (CCMenu *)m_pRoot->getChildByTag(gQuickBackHomeBtn);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(gQuickBackHomeBtn);
		item->setTarget(this, menu_selector(MineAreaWindow::On_GoblinArea_Click));

		menu = (CCMenu *)m_pRoot->getChildByTag(gBackUpBtn);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(gBackUpBtn);
		item->setTarget(this, menu_selector(MineAreaWindow::On_GoblinArea_Click));
	}
	else if(m_iShowPage == _PAGE_DWARVENAREA_)
	{
		menu = (CCMenu *)m_pRoot->getChildByTag(dLeftArrow);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(dLeftArrow);
		item->setTarget(this, menu_selector(MineAreaWindow::On_DwarvenArea_Click));

		menu = (CCMenu *)m_pRoot->getChildByTag(dRightArrow);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(dRightArrow);
		item->setTarget(this, menu_selector(MineAreaWindow::On_DwarvenArea_Click));

		menu = (CCMenu *)m_pRoot->getChildByTag(dQuickBackHomeBtn);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(dQuickBackHomeBtn);
		item->setTarget(this, menu_selector(MineAreaWindow::On_DwarvenArea_Click));

		menu = (CCMenu *)m_pRoot->getChildByTag(dBackUpBtn);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(dBackUpBtn);
		item->setTarget(this, menu_selector(MineAreaWindow::On_DwarvenArea_Click));

		for(int i = dStartStopBtn0; i <= dStartStopBtn3; i += 16)
		{
			//NFC_bindDTHeroCellSelectorAndAttahParam(i,i,m_pRoot,this, menu_selector(MineAreaWindow::On_DwarvenArea_Click),0,0);
			menu = (CCMenu *)m_pRoot->getChildByTag(i);
			item = (CMenuItemSprite *)menu->getChildByTag(0);
			item->setTag(i);
			item->setTarget(this, menu_selector(MineAreaWindow::On_DwarvenArea_Click));
		}

	}
	else if(m_iShowPage == _PAGE_DRAGONAREA_)
	{
		menu = (CCMenu *)m_pRoot->getChildByTag(nQuickBackHomeBtn);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(nQuickBackHomeBtn);
		item->setTarget(this, menu_selector(MineAreaWindow::On_DragonArea_Click));

		menu = (CCMenu *)m_pRoot->getChildByTag(nBackUpBtn);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(nBackUpBtn);
		item->setTarget(this, menu_selector(MineAreaWindow::On_DragonArea_Click));

		for(int i = nOwnerBg0; i <= nOwnerBg3; i += 6)
		{
			menu = (CCMenu *)m_pRoot->getChildByTag(i);
			item = (CMenuItemSprite *)menu->getChildByTag(0);
			item->setTag(i);
			item->setTarget(this, menu_selector(MineAreaWindow::On_DragonArea_Click));
		}

		menu = (CCMenu *)m_pRoot->getChildByTag(nOwnerTiaoZhan);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(nOwnerTiaoZhan);
		item->setTarget(this, menu_selector(MineAreaWindow::On_DragonArea_Click));

		menu = (CCMenu *)m_pRoot->getChildByTag(nStartStopBtn);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(nStartStopBtn);
		item->setTarget(this, menu_selector(MineAreaWindow::On_DragonArea_Click));
		
		menu = (CCMenu *)m_pRoot->getChildByTag(nOwnerCaiKuang);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(nOwnerCaiKuang);
		item->setTarget(this, menu_selector(MineAreaWindow::On_DragonArea_Click));

	}
	else if(m_iShowPage == _PAGE_HUNTMINE_)
	{
		menu = (CCMenu *)m_pRoot->getChildByTag(hHuntBtn);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(hHuntBtn);
		item->setTarget(this, menu_selector(MineAreaWindow::On_HuntMine_Click));
		
		menu = (CCMenu *)m_pRoot->getChildByTag(hQuickBackHomeBtn);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(hQuickBackHomeBtn);
		item->setTarget(this, menu_selector(MineAreaWindow::On_HuntMine_Click));

		menu = (CCMenu *)m_pRoot->getChildByTag(hBackUpBtn);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(hBackUpBtn);
		item->setTarget(this, menu_selector(MineAreaWindow::On_HuntMine_Click));

		menu = (CCMenu *)m_pRoot->getChildByTag(hTipBtn0);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(hTipBtn0);
		item->setTarget(this, menu_selector(MineAreaWindow::On_HuntMine_Click));

		menu = (CCMenu *)m_pRoot->getChildByTag(hTipBtn1);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(hTipBtn1);
		item->setTarget(this, menu_selector(MineAreaWindow::On_HuntMine_Click));

		for(int i = 0; i < 4; i++)
		{
			menu = (CCMenu *)m_pRoot->getChildByTag(hLieRen0 + i);
			item = (CMenuItemSprite *)menu->getChildByTag(0);
			item->setTag(hLieRen0 + i);
			item->setTarget(this, menu_selector(MineAreaWindow::On_HuntMine_Click));
		}
		menu = (CCMenu *)m_pRoot->getChildByTag(hTipNoBtn2);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(hTipNoBtn2);
		item->setTarget(this, menu_selector(MineAreaWindow::On_HuntMine_Click));

		menu = (CCMenu *)m_pRoot->getChildByTag(hTipYesBtn2);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(hTipYesBtn2);
		item->setTarget(this, menu_selector(MineAreaWindow::On_HuntMine_Click));

		menu = (CCMenu *)m_pRoot->getChildByTag(hTipCloseBtn2);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(hTipCloseBtn2);
		item->setTarget(this, menu_selector(MineAreaWindow::On_HuntMine_Click));


	}

}

void MineAreaWindow::_requestData()
{
	if(m_iShowPage == _PAGE_GOBLINAREA_)
	{
		MININGDATAHANDLER->ToServerEnterGoblinArea();
	}
	else if(m_iShowPage == _PAGE_DWARVENAREA_)
	{
		MININGDATAHANDLER->ToServerEnterDwarvenArea();
	}
	else if(m_iShowPage == _PAGE_DRAGONAREA_)
	{
		MININGDATAHANDLER->ToServerEnterDragonArea();
	}
	else if(m_iShowPage == _PAGE_HUNTMINE_)
	{
		MININGDATAHANDLER->ToServerEnterHuntMining();
	}
}

void MineAreaWindow::_setLieRenJiHuoAnimation()
{
	//���ݿ�ʼ�ɿ�ʱ�������ݣ����ù�������ѭ��������Ч
	HuntData * data = MININGDATAHANDLER->m_pHuntData;
	if(!data)
		return;
	if(data->lieRenVector.size() < 4)
		return;

	if(data->lieRenVector[0]->isActive > 0)
	{//װ�����˼�����Ч
		if(m_pLieRenJiHuoAnimation0 == NULL)
		{
			MaskNode * node = (MaskNode *)m_pRoot->getChildByTag(hLieRenMask0);
			m_pLieRenJiHuoAnimation0 = NFC_getLoopFrameEffect(node->GetViewData().colorG_);
			node->addChild(m_pLieRenJiHuoAnimation0, 0, 0);
		}
	}
	else
	{
		if(m_pLieRenJiHuoAnimation0)
		{
			m_pLieRenJiHuoAnimation0->removeFromParentAndCleanup(true);
			m_pLieRenJiHuoAnimation0 = NULL;
		}
	}
	if(data->lieRenVector[1]->isActive > 0)
	{//�������˼�����Ч
		if(m_pLieRenJiHuoAnimation1 == NULL)
		{
			MaskNode * node = (MaskNode *)m_pRoot->getChildByTag(hLieRenMask1);
			m_pLieRenJiHuoAnimation1 = NFC_getLoopFrameEffect(node->GetViewData().colorG_);
			node->addChild(m_pLieRenJiHuoAnimation1, 0, 0);
		}
	}
	else
	{
		if(m_pLieRenJiHuoAnimation1)
		{
			m_pLieRenJiHuoAnimation1->removeFromParentAndCleanup(true);
			m_pLieRenJiHuoAnimation1 = NULL;
		}
	}
	if(data->lieRenVector[2]->isActive > 0)
	{//��ʯ���˼�����Ч
		if(m_pLieRenJiHuoAnimation2 == NULL)
		{
			MaskNode * node = (MaskNode *)m_pRoot->getChildByTag(hLieRenMask2);
			m_pLieRenJiHuoAnimation2 = NFC_getLoopFrameEffect(node->GetViewData().colorG_);
			node->addChild(m_pLieRenJiHuoAnimation2, 0, 0);
		}
	}
	else
	{
		if(m_pLieRenJiHuoAnimation2)
		{
			m_pLieRenJiHuoAnimation2->removeFromParentAndCleanup(true);
			m_pLieRenJiHuoAnimation2 = NULL;
		}
	}
	if(data->lieRenVector[3]->isActive > 0)
	{//��Ӣ���˼�����Ч
		if(m_pLieRenJiHuoAnimation3 == NULL)
		{
			MaskNode * node = (MaskNode *)m_pRoot->getChildByTag(hLieRenMask3);
			m_pLieRenJiHuoAnimation3 = NFC_getLoopFrameEffect(node->GetViewData().colorG_);
			node->addChild(m_pLieRenJiHuoAnimation3, 0, 0);
		}
	}
	else
	{
		if(m_pLieRenJiHuoAnimation3)
		{
			m_pLieRenJiHuoAnimation3->removeFromParentAndCleanup(true);
			m_pLieRenJiHuoAnimation3 = NULL;
		}
	}

}

void MineAreaWindow::HuntAnimationCallBackFunction()
{
	MaskNode * node = (MaskNode *)m_pRoot->getChildByTag(hMonsterMask);

	HuntResult * data = MININGDATAHANDLER->m_pHuntResult;
	if(data == NULL)
		return;

	if(data->type == 0)
	{
		//˵��
		NFC_setLabelString(hDesc, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(2008), true);

		//�ѱ����\Ʈ��
		for(int i = 0; i < (int)data->boxData.size(); ++i)
		{
			HuntBoxData * box = data->boxData[i];
			EFFECTDATAHANDLER->ShowFlowEffect(box->type, box->count, box->critValue, box->itemIconId);
		}

		m_bBoxOpen = true;

		NFC_setPicForCCSprite(10, node, PIC_HUNT_BOX_OPEN, true);
	}
	else if(data->type == 1)
	{//������

	}
	else if(data->type == 2)
	{//��������
		//node->removeAllChildrenWithCleanup(true);
	}
	else if(data->type == 3)
	{
		node->removeAllChildrenWithCleanup(true);
	}

}

void  MineAreaWindow::EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr)
{
	if (animationNode == m_pLieRenKaiQiAnimation)
	{
		//�Ƴ����ֲ�
		_removeGrayLayer();
	
		m_pLieRenKaiQiAnimation->removeFromParentAndCleanup(true);
		m_pLieRenKaiQiAnimation = NULL;

		//�����������˿���״̬
		_setLieRenJiHuoAnimation();
	}
}

void MineAreaWindow::Function_GetEnterGoblinData()
{
	if(m_iShowPage == _PAGE_GOBLINAREA_)
		_setGoblinPage();
}

void MineAreaWindow::Function_GetEnterDwarvenData()
{
	if(m_iShowPage == _PAGE_DWARVENAREA_)
	{
		int index = MININGDATAHANDLER->PlayerinMineIndex();
		m_iDwarvenShowPage = index/4;
		if(m_iDwarvenShowPage == 0)
		{
			//���˸���ť��������ǵ�һҳ ��ť���ɰ� �Ұ�ť�ɰ�
			CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(dLeftArrow);
			CMenuItemSprite * item_ = (CMenuItemSprite *)menu->getChildByTag(dLeftArrow);
			item_->setEnabled(false);
			
			menu = (CCMenu *)m_pRoot->getChildByTag(dRightArrow);
			item_ = (CMenuItemSprite *)menu->getChildByTag(dRightArrow);
			item_->setEnabled(true);
		}	
		_setDwarvenPage();
	}
		
}

void MineAreaWindow::Function_GetEnterDragonData()
{
	if(m_iShowPage == _PAGE_DRAGONAREA_)
		_setDragonPage();
}

void MineAreaWindow::Function_GetEnterHuntData()
{
	if(m_iShowPage == _PAGE_HUNTMINE_)
	{
		_setHuntPage();
		//���˼���״̬
		_setLieRenJiHuoAnimation();

		if(MININGDATAHANDLER->m_pHuntResult != NULL && MININGDATAHANDLER->m_pHuntResult->needRespond == true)
		{//�����ǰ�����Ҫ��ʾ������ʾ�����幩��Ӧ
			_showHuntTipPage(true);
			_setHuntTipPage();
		}

		//�˴���Ҫ�ж��Ǵ���������ս������������ǣ��򵯳���ǰ�ϴ�ѡ�����˵���Ϣ

		if(MININGDATAHANDLER->m_bNeedOpenTipsPage2 == true)
		{
			MININGDATAHANDLER->m_bNeedOpenTipsPage2 = false;
			_showHuntTipPage2(true);
			_setHuntTipPage2();
		}
	}
}

void MineAreaWindow::Function_GetStopMiningResult()
{
	//�˴���Ҫ��Ӧҳ����д�����ǰ���ǽ��յ������ɿ���Ϣʱ����ҳ�����·�������ҳ������
	if(m_iShowPage == _PAGE_GOBLINAREA_)
	{
		MININGDATAHANDLER->ToServerEnterGoblinArea();
	}
	else if(m_iShowPage == _PAGE_DWARVENAREA_)
	{
		MININGDATAHANDLER->ToServerEnterDwarvenArea();
	}
	else if(m_iShowPage == _PAGE_DRAGONAREA_)
	{
		MININGDATAHANDLER->ToServerEnterDragonArea();
	}
	else
	{
		LOGGERSYSTEM->LogInfo("Function_GetStopMiningResult enter but i am in page [%d]", m_iShowPage);
	}


}

void MineAreaWindow::Function_GetStartMiningResult()
{
	//�˴���Ҫ��Ӧҳ����д���
	if(m_iShowPage == _PAGE_GOBLINAREA_)
	{
		MININGDATAHANDLER->ToServerEnterGoblinArea();
	}
	else if(m_iShowPage == _PAGE_DWARVENAREA_)
	{
		MININGDATAHANDLER->ToServerEnterDwarvenArea();
	}
	else if(m_iShowPage == _PAGE_DRAGONAREA_)
	{
		MININGDATAHANDLER->ToServerEnterDragonArea();
	}
	else
	{
		LOGGERSYSTEM->LogInfo("Function_GetStartMiningResult enter but i am in page [%d]", m_iShowPage);
	}

}

void MineAreaWindow::Function_GetHuntingResult()
{
// 	if(m_iShowPage != _PAGE_HUNTMINE_)
// 		return;
// 
// 	//���յ�Ѱ���������
// 	HuntResult * data = MININGDATAHANDLER->m_pHuntResult;
// 	if(data == NULL)
// 		return;
// 
// 	//�жϽ������
// 	if(data->type == 0)
// 	{//���䣬���Ŷ���
// 		_showHuntTipPage(false);
// 	}
// 	else
// 	{//�ˣ�����
// 		_showHuntTipPage(true);
// 		_setHuntTipPage();
// 	}

	_createGrayLayer();

	LOGGERSYSTEM->LogInfo("got result\n");

	MININGDATAHANDLER->m_pHuntData->huntTimes --;

	_setHuntPage();

	if(m_pSkeletonNode)
		m_pSkeletonNode->setAnimation("Pao-01", true); 

	m_bHeroRun = true;

	_playHuntMeetAnimation();
}

void MineAreaWindow::Function_GetHelloFriendResult()
{
	if(m_iShowPage != _PAGE_HUNTMINE_)
		return;
	//����������ʾ����
	_showHuntTipPage(false);
	_clearMonster();

}

void MineAreaWindow::Function_GetBuyMinralResult()
{
	if(m_iShowPage != _PAGE_HUNTMINE_)
		return;
	//����������ʾ����
	_showHuntTipPage(false);
	_clearMonster();

}

void MineAreaWindow::Function_GetAskFriendResult()
{
	if(m_iShowPage != _PAGE_HUNTMINE_)
		return;

	MININGDATAHANDLER->ToServerHuntHelloMoney();
}

void MineAreaWindow::Function_GetDwarvenLootResult()
{
	if(m_iShowPage != _PAGE_DWARVENAREA_)
		return;

	//��ʾ�Ի�����ʾ��ǰ��λû�����ڲɿ�����ȷ��ˢ�½���
	NFC_showMessageBoxSingle(kDWARVEN_PAGEINFOCHANGED, SysLangDataManager::get_instance2()->GetSysLangById(2043));

}

void MineAreaWindow::Function_GetDwarvenPageInfoChangedConfirm()
{
	if(m_iShowPage != _PAGE_DWARVENAREA_)
		return;
	//���������˿�������
	MININGDATAHANDLER->ToServerEnterDwarvenArea();
}

void MineAreaWindow::Function_HuntLeftTimeUpdate(int lefttime)
{
	if(m_iShowPage != _PAGE_HUNTMINE_)
		return;

	//����ҳ����ʾ

	if(MININGDATAHANDLER->m_pHuntData)
		MININGDATAHANDLER->m_pHuntData->huntTimes = lefttime;

	_setHuntPage();
}

void MineAreaWindow::Function_HuntLieRenChaKan()
{
	_showHuntTipPage2(true);
	_setHuntTipPage2();
}

void MineAreaWindow::Function_HuntLieRenQiangDuoNo()
{
	_showHuntTipPage2(false);
	_setLieRenJiHuoAnimation();
}

void MineAreaWindow::On_GoblinArea_Click(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int tag = item->getTag();

	if(tag == gStartStopBtn)
	{//��ʼ�����ɿ�
		BTN_INTERVAL("GOBLIN_STARTSTOP_CLICK",_COMMON_BTN_CLICK_INTERVAL_SMALL);

		int idx = item->getIDX();
		if(idx == 0)
		{//Ҫ�ɿ�
			MININGDATAHANDLER->ToServerStartMining(m_iShowPage, 0);
		}
		else if(idx == 1)
		{//Ҫֹͣ�ɿ�
			MININGDATAHANDLER->ToServerStopMining();
		}
	}
	else if(tag == gQuickBackHomeBtn)
	{//���ٻس�
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_MINEAREAWINDOW_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
	}
	else if(tag == gBackUpBtn)
	{//�����ϲ㴰��
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_MINEAREAWINDOW_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_PUCONGWINDOW_, _to_event_param_(PuCongWindow::HLW_MINING));
	}

}

void MineAreaWindow::On_DwarvenArea_Click(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int tag = item->getTag();

	if(tag == dQuickBackHomeBtn)
	{//���ٻس�
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_MINEAREAWINDOW_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
	}
	else if(tag == dBackUpBtn)
	{//�����ϲ㴰��
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_MINEAREAWINDOW_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_PUCONGWINDOW_, _to_event_param_(PuCongWindow::HLW_MINING));
	}
	else if(tag == dStartStopBtn0 || tag == dStartStopBtn1 || tag == dStartStopBtn2 || tag == dStartStopBtn3)
	{//��ʼ�����ɼ�
		BTN_INTERVAL("DWARVEN_STARTSTOP_CLICK",_COMMON_BTN_CLICK_INTERVAL_SMALL);

		int idx = (tag - dStartStopBtn0) / 16 + 4 * m_iDwarvenShowPage;
		if(item->getIDX() == 0)
		{//��ʼ�ɿ�
			MININGDATAHANDLER->ToServerStartMining(_PAGE_DWARVENAREA_, idx);
		}
		else if(item->getIDX() == 1)
		{//ֹͣ�ɿ�
			MININGDATAHANDLER->ToServerStopMining();
		}
		else if(item->getIDX() == 2)
		{//����λ
			MININGDATAHANDLER->ToServerDwarvenLoot(idx);
		}
	}
	else if(tag == dLeftArrow)
	{//����ҳ
		if(m_iDwarvenShowPage > 0)
		{
			m_iDwarvenShowPage--;
			_setDwarvenPage();

			CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(dRightArrow);
			CMenuItemSprite * item_ = (CMenuItemSprite *)menu->getChildByTag(dRightArrow);
			item_->setEnabled(true);
		}
		if(m_iDwarvenShowPage == 0)
			item->setEnabled(false);
	}
	else if(tag == dRightArrow)
	{//���ҷ�ҳ
		if(m_iDwarvenShowPage < KUANGDONG_DWARVEN_PAGES - 1)
		{
			m_iDwarvenShowPage++;
			_setDwarvenPage();

			CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(dLeftArrow);
			CMenuItemSprite * item_ = (CMenuItemSprite *)menu->getChildByTag(dLeftArrow);
			item_->setEnabled(true);
		}
		if(m_iDwarvenShowPage == KUANGDONG_DWARVEN_PAGES - 1)
			item->setEnabled(false);
	}

}

void MineAreaWindow::On_DragonArea_Click(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int tag = item->getTag();

	if(tag == nQuickBackHomeBtn)
	{//���ٻس�
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_MINEAREAWINDOW_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
	}
	else if(tag == nBackUpBtn)
	{//�����ϲ㴰��
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_MINEAREAWINDOW_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_PUCONGWINDOW_, _to_event_param_(PuCongWindow::HLW_MINING));
	}
	else if(tag == nOwnerBg0 || tag == nOwnerBg1 || tag == nOwnerBg2 || tag == nOwnerBg3)
	{//��ʾ�Ҳ�
		if(m_pDragonSelectOwner)
			m_pDragonSelectOwner->unselected();

		m_pDragonSelectOwner = item;
		m_pDragonSelectOwner->selected(true);

		m_iDragonSelectOwner = (tag - nOwnerBg0) / 6;

		_setDragonRightPart();
	}
	else if(tag == nOwnerTiaoZhan)
	{//��ս
		BTN_INTERVAL("DRAGON_TIAOZHAN_CLICK",_COMMON_BTN_CLICK_INTERVAL_SMALL);

		MININGDATAHANDLER->ToServerDragonChallengeOwner(m_iDragonSelectOwner);
	}
	else if(tag == nOwnerCaiKuang)
	{//�Ǻ��ѣ��������²ɿ�
		BTN_INTERVAL("DRAGON_CAIKUANG_CLICK",_COMMON_BTN_CLICK_INTERVAL_SMALL);

		MININGDATAHANDLER->ToServerStartMining(m_iShowPage, m_iDragonSelectOwner);
	}
	else if(tag == nStartStopBtn)
	{//��ʼ����ֹͣ�ڿ�û�п�ʼ��״̬
		BTN_INTERVAL("DRAGON_STARTSTOP_CLICK",_COMMON_BTN_CLICK_INTERVAL_SMALL);

		if(item->getIDX() == 0)
			MININGDATAHANDLER->ToServerStartMining(_PAGE_DRAGONAREA_, m_iDragonSelectOwner);
		else if(item->getIDX() == 1)
			MININGDATAHANDLER->ToServerStopMining();
	}
}

void MineAreaWindow::On_HuntMine_Click(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int tag = item->getTag();
	
	if(tag == hHuntBtn)
	{//��ʼѰ��
		BTN_INTERVAL("HuntMine_StartHunt", _COMMON_BTN_CLICK_INTERVAL_);
		LOGGERSYSTEM->LogInfo("hunt hunt\n");
		MININGDATAHANDLER->ToServerHuntMining();
	}
	else if(tag == hQuickBackHomeBtn)
	{//���ٻس�
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_MINEAREAWINDOW_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
	}
	else if(tag == hBackUpBtn)
	{//�����ϲ㴰��
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_MINEAREAWINDOW_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_PUCONGWINDOW_, _to_event_param_(PuCongWindow::HLW_HUNT));
	}
	else if(tag == hTipBtn0)
	{
		MININGDATAHANDLER->m_pHuntResult->needRespond = false;
		if(MININGDATAHANDLER->m_pHuntResult->type == 1)
		{//�������
			if(item->getIDX() == 0)
			{//���к�
				MININGDATAHANDLER->ToServerHuntHelloMoney();
			}
			else if(item->getIDX() == 1)
			{//�Ӻ���
				C2SFriendAddPacket packet(MININGDATAHANDLER->m_pHuntResult->playerId);
				packet.Send();
				//�Ӻ���֮��������ȡ����
				MININGDATAHANDLER->ToServerHuntHelloMoney();
			}
		}
		else if(MININGDATAHANDLER->m_pHuntResult->type == 2)
		{//����Ұ��,����
			MININGDATAHANDLER->ToServerHuntGrab();
		}
	}
	else if(tag == hTipBtn1)
	{
		MININGDATAHANDLER->m_pHuntResult->needRespond = false;
		if(MININGDATAHANDLER->m_pHuntResult->type == 1)
		{//������ң�����
			MININGDATAHANDLER->ToServerHuntGrab();
		}
		else if(MININGDATAHANDLER->m_pHuntResult->type == 2)
		{//����Ұ��
			MININGDATAHANDLER->ToServerHuntBuyMineral();
		}
		
	}
	else if(tag == hLieRen0 || tag == hLieRen1 || tag == hLieRen2 || tag == hLieRen3)
	{//��������˰�ť
		//����������ϸ��Ϣ
		m_iLieRenSelected = tag - hLieRen0;
		MININGDATAHANDLER->ToServerChaKanLieRen(m_iLieRenSelected);
	}
	else if(tag == hTipNoBtn2)
	{//��������
		//������ʾ��
		//NFC_showMessageBox(kKUANGDONG_HUNT_LIEREN_NO, SysLangDataManager::get_instance2()->GetSysLangById(2099));		
		NFC_showMessageBox(SysLangDataManager::get_instance2()->GetSysLangById(2099), _TYPED_EVENT_HUNT_LIEREN_QIANGDUO_NO_CONFIRM_);
	}
	else if(tag == hTipYesBtn2)
	{//����
		MININGDATAHANDLER->ToServerQiangDuoLieRenYes(m_iLieRenSelected);
	}
	else if(tag == hTipCloseBtn2)
	{//�ر�������ϸ��Ϣ����
		_showHuntTipPage2(false);
	}
}


void MineAreaWindow::On_Help(cocos2d::CCObject* pSender)
{

}

