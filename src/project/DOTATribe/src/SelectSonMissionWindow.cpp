////////////////////////////////////////////////////////////////
//Name:	 SelectSonMissionWindow
//Auchor: 	xiaobo.wu
//Func:	 ѡ���ӹؿ�
//Maintainer: 	xiaobo.wu
//date:   2014/04/11
////////////////////////////////////////////////////////////////


#include "../include/SelectSonMissionWindow.h"
#include "../include/SysLangDataManager.h"
#include "../include/MissionDataHandler.h"
#include "../include/MissionPacket.h"
#include "../include/ResourceIDDataManager.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/SceneInfoDataManager.h"
#include "../include/ResourceIDDataManager.h"
#include "../include/HomeProcedure.h"
#include "../include/CSEnterTranscriptRequestPacket.h"
#include "../include/NetObjectTipsDataHandler.h"
#include "../include/ClientConstDataManager.h"
#include "../Include/UIViewDataManger.h"
#include "../include/LevelUpDataHandler.h"
#include "../include/CMenuItemSprite.h"
#include "../include/CPublicVarReader.h"
#include "../include/FullStarRewardPacket.h"
#include "../include/AskForAddEnergyPacket.h"
#include "../include/NFControlsManager.h"
#include "../include/SceneEffect.h"
#include "../include/PESWindow.h"
#include "../include/DTAwardBoard.h" 
#include "../include/GuideSystem.h"
#include "../include/WindowManager.h"
#include "../include/EventSystem.h"

using  namespace  cocos2d;
using namespace cocos2d::extension;

const int   nNormal_Reward_TID = 146;
const int   nFullStar_Reward_TID = 806;
const int   maxCellUnitCount = 4;
const int   nChallageLevel_TID = 25;
const int   nLeftChallegeCount_TID = 116;


SelectSonMissionWindow::SelectSonMissionWindow()
{
	m_WindowType = _TYPED_WINDOW_SELECTSONMISSION_;
	m_pCustomTable = NULL;
	m_bCanGetFullReward = false;
	m_nCellSize = cocos2d::CCSizeZero;
	m_pMissionInfoData = NULL;
	m_sMissionName = "";
	m_nMissionID = 0;
	m_nCustomID = 0; 
	m_nPlayerLevel = 0;
	m_nReNetReConverSID = -1;
	m_bDuringGuid = false;
	m_bHadGotFullReward = false; 
	m_bIsNeedAutoUp	= true;
	m_bIsNeedClearMemory = true;
	m_bIsReconverReNetSID = false;
	m_nMaxCanChallenegCID = 0;
	m_bIsJudgeFullAfterFight = false;

}

SelectSonMissionWindow::~SelectSonMissionWindow()
{ 
}

bool SelectSonMissionWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_SELECTSONMISSIONWINDOW_);
	RegisterEvent(_TYPE_EVENT_WILL_ENTER_ATHLETICS_, true);
	RegisterEvent(_TYPED_EVENT_HIDE_SELECTSONMISSIONWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_SELECTSONMISSIONWINDOW_, true); 
	RegisterEvent(_TYPED_EVENT_RESET_CHALLENGETIMES_, true);
	RegisterEvent(_TYPED_EVENT_REFRESH_UPDATEUI_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_UI_TEXT_, true);
	RegisterEvent(_TYPED_EVENT_GOTO_NEXTMISSION_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_REWARDBOX_, true);
	RegisterEvent(_TYPED_EVENT_RECONNECT_INGAME_NOTIFY, true);
	//����װ����ʾ�¼�
	EVENTSYSTEM->RegisterEventHandler(_TYPED_EVENT_SHOW_NEWEQUIPREMINDWINDOW_,Event_Handler);
	 
	 
	return IWindow::Init();
}

bool SelectSonMissionWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		CheckGuid();
		InitUILayout();
		
		return true;
	} 
	while (false);

	return false;
}

void SelectSonMissionWindow::Tick()
{
	IWindow::Tick();
}

void SelectSonMissionWindow::Destroy()
{  
	if(m_bIsNeedClearMemory)
	{
		//����ؿ����� 
		m_pMissionInfoData->setHistorySID(-1);
	}
	m_bIsReconverReNetSID = false;
	m_bIsNeedClearMemory = true;
	m_nPlayerLevel = 0;
	m_bDuringGuid = false;
	m_bCanGetFullReward = false;
	m_bHadGotFullReward = false;
	m_pMissionInfoData = NULL;
	m_sMissionName = "";
	m_nMissionID = 0;
	m_nCustomID = 0;
	m_nReNetReConverSID = -1;
	PushEvent(_TYPED_EVENT_HIDE_CHATWINDOW_);
	PushEvent(_TYPED_EVENT_HIDE_ROLESTATUSWINDOW_); 
	IWindow::Destroy();
}

	/*
		�¼�������
	*/
void SelectSonMissionWindow::Event_Handler(int iEventType, std::string owerData, std::list<std::string>& paramList){
	//չʾ����װ����֪ͨ
	SelectSonMissionWindow* win=(SelectSonMissionWindow*)WindowManager::get_instance2()->GetWindowByType(_TYPED_WINDOW_SELECTSONMISSION_);
	win->ShowNewGuide_2();
}

	/*
		��ʾ��������2
	*/
void SelectSonMissionWindow::ShowNewGuide_2(){
	//=============��һ�ص�5���ӹؿ�=================
	bool con1=MissionDataHandler::get_instance2()->getCurMissionID()==1;
	bool con2=m_nCustomID==6;
	if (con1&&con2)
	{
		if (ROLEINFODATAHANDLER->CheckNewFuncOPenGuide(GuideSystem::_TYPED_GUIDE_2_))
		{
			GuideSystem::get_instance2()->StartGuide4NewFunc(GuideSystem::_TYPED_GUIDE_2_);
			ROLEINFODATAHANDLER->ToServerFinishNewFunc(GuideSystem::_TYPED_GUIDE_2_);

			//����������ʾ�ļ�ͷ,����������2���ظ�
			m_bDuringGuid = true;
			ShowGuidArrowSkeleton(false);
		}
	} 
}

void SelectSonMissionWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if(iEventType == _TYPED_EVENT_SHOW_SELECTSONMISSIONWINDOW_ )
	{
		OnShowWindowEventHandler(paramList);
	}
	else if(iEventType == _TYPED_EVENT_HIDE_SELECTSONMISSIONWINDOW_)
	{  
		Destroy();
	}
	else if(iEventType == _TYPE_EVENT_WILL_ENTER_ATHLETICS_)
	{
		m_bIsNeedClearMemory = false;
		m_bIsJudgeFullAfterFight = true;
	}
	else if(iEventType == _TYPED_EVENT_RESET_CHALLENGETIMES_ || iEventType == _TYPED_EVENT_UPDATE_UI_TEXT_)
	{
		//��̬����ĳ��cell������
		cocos2d::extension::CCTableViewCell * customCell= m_pCustomTable->cellAtIndex(m_nCustomID-1);
		if(customCell)
		{  
		    SetTableCell(customCell,m_nCustomID-1);
		}   
		UpdateBtnStates();
		UpdateCostLabel();
		NFC_showCommunicationWating(false);
	}
	else if(iEventType == _TYPED_EVENT_UPDATE_REWARDBOX_)
	{
		if (m_pMissionInfoData)
		{
			m_pMissionInfoData->setCanGet3starReward(true);
			m_pMissionInfoData->setHasGetReward(true);
			MissionDataHandler::get_instance2()->setIsShowGetRewad(false);
			m_bHadGotFullReward = true ;
			UpdateUIWithData(false);
		    //ˢ�½���
		} 
		//to do 
		//����Ƿ�������ս������һ����ͼ 
		JudgeToNextMission();
	} 
	else if(iEventType == _TYPED_EVENT_GOTO_NEXTMISSION_)
	{
		MissionDataHandler::get_instance2()->JumpToAppointStates(m_pMissionInfoData->getMissionID()+1);	 
	}
	else if(iEventType == _TYPED_EVENT_UPDATE_SELECTSONMISSIONWINDOW_||_TYPED_EVENT_RECONNECT_INGAME_NOTIFY)
	{
		//����ȫ���� 
		m_bIsNeedAutoUp = false;
		m_bIsReconverReNetSID = true;
		UpdateUIWithData(false);
	}
	else if(iEventType == _TYPED_EVENT_REFRESH_UPDATEUI_)
	{
		//�����ڵȼ��仯
		if(m_nPlayerLevel != RoleInfoDataHandler::get_instance2()->m_pRIData->level_)
		{
			m_nPlayerLevel = RoleInfoDataHandler::get_instance2()->m_pRIData->level_;
			UpdateCustomView();
		}
	}
} 

void  SelectSonMissionWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{ 
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_CHATWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_ROLESTATUSWINDOW_,_to_event_param_(_TYPED_WINDOW_SELECTSONMISSION_));	
	//��ʾջ����������
	LevelUpDataHandler::get_instance2()->m_showFlag = true;
	if (!LevelUpDataHandler::get_instance2()->LevelUpDataList.empty())
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LEVELUPNORMALWINDOW_, _to_event_param_(m_WindowType));
	Show(true);

}

void  SelectSonMissionWindow::CommonSelectorHandler(cocos2d::CCObject * pSender)
{ 
	CMenuItemSprite * pMenuItem = (CMenuItemSprite *)pSender;
	if(pMenuItem)
	{
		switch(pMenuItem->getIDX())
		{
		case  _MISSION_BACK_HOME_BTN_:
			{
				EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_SELECTSONMISSIONWINDOW_);
				EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_,_to_event_param_(IProcedure::_TYPED_HOME_PROCEDURE_));
				break;
			}
		case _MISSION_BACK_CUSTOM_BTN_:
			{
				EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_SELECTSONMISSIONWINDOW_);
				EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_SELECTMISSIONWINDOW_);
				break;
			}
		case _MISSION_CHALLENEGE_BTN_:
			{ 
				NFC_showCommunicationWating(true); 
				CheckIsNeedAutoUp();
				CSEnterTranscriptRequestPacket  transcriptRequest(m_pMissionInfoData->getMissionID(),m_nCustomID);
				transcriptRequest.Send();
				//~~~~~��������~~~~~
				GUIDESYSTEM->PauseGuide();
				break;
			}
		case _MISSION_WIPE_BTN_:
			{
				if (m_nPlayerLevel >=ClientConstDataManager::get_instance2()->getValueByKey(CONST_KEY_MISSION_MASSACE_LEVEL))
				{
					CheckIsNeedAutoUp();
					NFC_showCommunicationWating(true);
					PushEvent(_TYPED_EVENT_SHOW_MASSACREWINDOW_);
				}
				else
				{
					std::string str=SysLangDataManager::get_instance2()->GetSysLangById(4029);
					NFC_showMessageBox(kDEFAULT,str);
				}
				break;
			}
		case _MISSION_CLEAR_BTN_:
			{
				CheckIsNeedAutoUp();
				C2SCleanChallengeTimesPacket packet(m_pMissionInfoData->getMissionID(),m_nCustomID);
				packet.Send();
				break;
			}
		case _MISSION_FULLSTAR_REWARD_BTN_:
			{
				C2SFullStarRewardPacket packet(m_pMissionInfoData->getMissionID());
				packet.Send();
				break;
			}
		default:
			break;
		}
	}
}
 
void SelectSonMissionWindow::InitUILayout()
{ 
	UIViewDataManager::get_instance2()->AutoCreateNodeByTable(UIViewDataManager::kSELECTSONMISSIONWINDOW,m_pRootNode);
	InitBindMenuSelector();
	SetTableView(); 
	UpdateUIWithData();
}

void SelectSonMissionWindow::InitBindMenuSelector()
{ 
	NFC_bindSelectorForBtn(_MISSION_BACK_HOME_BTN_,m_pRootNode,this,menu_selector(SelectSonMissionWindow::CommonSelectorHandler));
	NFC_bindSelectorForBtn(_MISSION_BACK_CUSTOM_BTN_,m_pRootNode,this,menu_selector(SelectSonMissionWindow::CommonSelectorHandler));
	NFC_bindSelectorForBtn(_MISSION_CHALLENEGE_BTN_,m_pRootNode,this,menu_selector(SelectSonMissionWindow::CommonSelectorHandler));
	NFC_bindSelectorForBtn(_MISSION_WIPE_BTN_,m_pRootNode,this,menu_selector(SelectSonMissionWindow::CommonSelectorHandler));
	NFC_bindSelectorForBtn(_MISSION_CLEAR_BTN_,m_pRootNode,this,menu_selector(SelectSonMissionWindow::CommonSelectorHandler));
	NFC_bindSelectorForBtn(_MISSION_FULLSTAR_REWARD_BTN_,m_pRootNode,this,menu_selector(SelectSonMissionWindow::CommonSelectorHandler));
   
}

void  SelectSonMissionWindow::SetTableView()
{ 
	CCNode* cc = m_pRootNode->getChildByTag(_MISSION_CUSTOM_CELL_);
	m_nCellSize = cc->getContentSize(); 
	m_pCustomTable =(cocos2d::extension::CCTableView *)m_pRootNode->getChildByTag(_MISSION_CUSTOM_TABLEVIEW_);
	m_pCustomTable->setDataSource(this);
	m_pCustomTable->setDelegate(this);
	m_pCustomTable->setDirection(cocos2d::extension::kCCScrollViewDirectionHorizontal);
	m_pCustomTable->setTouchEnabled(true);
	m_pCustomTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);  
}

void  SelectSonMissionWindow::RewardTipsInfoHandler(cocos2d::CCObject * pSender)
{ 
	CMenuItemSprite * pMenuItem = (CMenuItemSprite *)pSender;
	if(pMenuItem)
	{ 
		int attachCustomID = pMenuItem->getAttachData1();
		int attachRewardIndex = pMenuItem->getAttachData2();
		if(attachCustomID > m_nMaxCustomNum)
		{ 
			//���ǽ���Tips
			size_t  rewardCount = m_pMissionInfoData->getStarRewardDataList().size();
			if(attachRewardIndex < (int)rewardCount)
			{
				NETOBJECTTIPSDATAHANDLER->ToServerGetObjectTips(m_pMissionInfoData->getStarRewardDataList().at(attachRewardIndex)->rewardTemplateID, _TYPED_WINDOW_SELECTSONMISSION_);
			}
		}
		else
		{
			//��ͨ����Tips
			StatesInfoData * pStatesIndoData = m_pMissionInfoData->getStatesInfoDataList().at(attachCustomID-1);
			if(pStatesIndoData)
			{
				size_t  infoListSize = pStatesIndoData->getItemInfoDataList().size();
				if( attachRewardIndex < (int)infoListSize )
				{
					PRewardItemNode  pRewardItemNode = pStatesIndoData->getItemInfoDataList().at(attachRewardIndex); 
					NETOBJECTTIPSDATAHANDLER->ToServerGetObjectTips(pRewardItemNode->rewardTemplateID, _TYPED_WINDOW_SELECTSONMISSION_);
				} 
			} 
		}
	}
}


void  SelectSonMissionWindow::CustomCellEventHandler(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * pMenuItem =(CMenuItemSprite *)pSender;
	if(pMenuItem)
	{  
		int  attachParam = pMenuItem->getIDX();
		//�ж��Ƿ���Ը���ѡ��
		if(m_pMissionInfoData)
		{
			if(attachParam > m_nMaxCustomNum)
			{
				//������ʾ
				if(attachParam != m_nCustomID)
				{ 
					cocos2d::extension::CCTableViewCell * customCell= m_pCustomTable->cellAtIndex(m_nCustomID-1);
					if(customCell)
					{  
						NFC_setNodeVisable(_CUSTOM_HIGH_LIGHT_BG_,customCell,false);
						NFC_setNodeVisable(_CUSTOM_BATTLE_LOGO_BG_,customCell,false); 
					}  
					customCell= m_pCustomTable->cellAtIndex(attachParam-1);
					if(customCell)
					{
					    NFC_setNodeVisable(_CUSTOM_HIGH_LIGHT_BG_,customCell,true);
					} 
					m_nCustomID = attachParam;
					//������������ 
					UpdateRewardInfo();
					//������ս��ť״̬ 
					UpdateBtnStates();
					//������ս�����Լ�����������ʯ  
					UpdateCostLabel(); 
				}   
			}
			else
			{
				StatesInfoData  * pStatesInfoData = m_pMissionInfoData->getStatesInfoDataList().at(attachParam-1);
				if(pStatesInfoData&&pStatesInfoData->getCanChallenge())
				{
					//������ʾ
					if(attachParam != m_nCustomID)
					{ 
						cocos2d::extension::CCTableViewCell * customCell= m_pCustomTable->cellAtIndex(m_nCustomID-1);
						if(customCell)
						{  
							NFC_setNodeVisable(_CUSTOM_HIGH_LIGHT_BG_,customCell,false);
							NFC_setNodeVisable(_CUSTOM_BATTLE_LOGO_BG_,customCell,false); 
						}  
						customCell= m_pCustomTable->cellAtIndex(attachParam-1);
						if(customCell)
						{
							NFC_setNodeVisable(_CUSTOM_HIGH_LIGHT_BG_,customCell,true);
							NFC_setNodeVisable(_CUSTOM_BATTLE_LOGO_BG_,customCell,true); 
						} 
						m_nCustomID = attachParam;
						//������������ 
						UpdateRewardInfo();
						//������ս��ť״̬ 
						UpdateBtnStates();
						//������ս�����Լ�����������ʯ  
						UpdateCostLabel();  
					}   
				}
			}
		} 
		CCLOG("Attach Param : %d",attachParam);
	}
}


void  SelectSonMissionWindow::CreateTableCell(cocos2d::extension::CCTableViewCell * pTableCell)
{ 
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSELECTSONCELL,pTableCell);
}

void  SelectSonMissionWindow::SetTableCell(cocos2d::extension::CCTableViewCell * pTableCell,unsigned int cellIndex)
{    

	//��ʾ�����ӹؿ������Ϣ
	if(cellIndex+1 > (UShort)m_nMaxCustomNum)
	{ 
	    NFC_setNodeVisable(_CUSTOM_HIGH_LIGHT_BG_,pTableCell,false);
		NFC_setNodeVisable(_CUSTOM_BATTLE_LOGO_BG_,pTableCell,false);
		NFC_setNodeVisable(_CUSTOM_LOCK_BG_,pTableCell,false); 

		if(cellIndex == m_nCustomID-1)
		{ 
			NFC_setNodeVisable(_CUSTOM_HIGH_LIGHT_BG_,pTableCell,true);
		}

		//��ʾ���ǽ�����
	    MaskNode * pMaskNode = (MaskNode *)NFC_getNode(_CUSTOM_REWARD_NODE_,pTableCell);
		if(pMaskNode)
		{ 
			NFC_setNoramlImageByUIIndex(_CUSTOM_BG_,pTableCell,pMaskNode->GetViewData().filepath_);
			NFC_bindSelectotForCellBtn(_CUSTOM_BG_,cellIndex+1,pTableCell,this,menu_selector(SelectSonMissionWindow::CustomCellEventHandler)); 
		}
		//175
		NFC_setLabelString(_CUSTOM_NAME_,pTableCell,175,true);
		//��ʾ���ǵȼ� 
		UpdateCellStarNum(pTableCell,m_pMissionInfoData->getMissionStarNum());
		//��ʾ������Ŀ
		NFC_setLabelString(_CUSTOM_LEFT_LABEL_,pTableCell,4026,true); 
		char starLaberl[32] = {0};
		sprintf(starLaberl,"%d/%d",m_pMissionInfoData->getCurMissionStarNum(),m_pMissionInfoData->getCurMissionFullStarNum());
		NFC_setLabelString(_CUSTOM_VALUE_LABEL_,pTableCell,starLaberl,true);
		NFC_setLabelByFontID(_CUSTOM_LEFT_LABEL_,pTableCell,16);
		NFC_setLabelByFontID(_CUSTOM_VALUE_LABEL_,pTableCell,16);
		NFC_setNodeVisable(_CUSTOM_OPEN_LEVEL_LABEL_,pTableCell,false);
	}
	else
	{   
		//��ʾ��ͨ��
		//����ս����ǩ
		NFC_setNodeVisable(_CUSTOM_BATTLE_LOGO_BG_,pTableCell,false);
		//���ظ�����ǩ
		NFC_setNodeVisable(_CUSTOM_HIGH_LIGHT_BG_,pTableCell,false);

		if(cellIndex == m_nCustomID-1)
		{ 
			NFC_setNodeVisable(_CUSTOM_HIGH_LIGHT_BG_,pTableCell,true);
			NFC_setNodeVisable(_CUSTOM_BATTLE_LOGO_BG_,pTableCell,true);
		} 
		StatesInfoData *  pStatesInfoData = m_pMissionInfoData->getStatesInfoDataList().at(cellIndex);
		if(pStatesInfoData)
		{
			MaskNode * pMaskNode = (MaskNode *)NFC_getNode(_CUSTOM_ADPET_NODE_,pTableCell);
			if(pStatesInfoData->getIsBoss())
			{
				if(pMaskNode)
				{ 
					NFC_setNoramlImageByUIIndex(_CUSTOM_BG_,pTableCell,pMaskNode->GetViewData().filepath_);
				}
			}
			else
			{
				if(pMaskNode)
				{ 
					NFC_setNoramlImageByUIIndex(_CUSTOM_BG_,pTableCell,pMaskNode->GetViewData().filepath2_);
				}
			}
			NFC_bindSelectotForCellBtn(_CUSTOM_BG_,cellIndex+1,pTableCell,this,menu_selector(SelectSonMissionWindow::CustomCellEventHandler)); 
			NFC_setLabelString(_CUSTOM_NAME_,pTableCell,pStatesInfoData->getStatesName().c_str(),true);
			m_nPlayerLevel = RoleInfoDataHandler::get_instance2()->m_pRIData->level_;
			 
			if(pStatesInfoData->getChallengeLevel() > m_nPlayerLevel)
			{
				//��ʾ��ɫ�ȼ�
				NFC_setLabelStringInt(_CUSTOM_OPEN_LEVEL_LABEL_,pTableCell,pStatesInfoData->getChallengeLevel(),nChallageLevel_TID,true);
			} 
			else
			{ 
				NFC_setNodeVisable(_CUSTOM_OPEN_LEVEL_LABEL_,pTableCell,false);
			}
			if(pStatesInfoData->getCanChallenge())
			{
				NFC_setNodeVisable(_CUSTOM_LOCK_BG_,pTableCell,false);
				//��ʾ���� 
				UpdateCellStarNum(pTableCell,pStatesInfoData->getStarCount());
				//��ʾ����
				NFC_setLabelString(_CUSTOM_LEFT_LABEL_,pTableCell,nLeftChallegeCount_TID,true);
				char starLaberl[32] = {0};
				sprintf(starLaberl,"%d/%d",pStatesInfoData->getLastChallengeTimes(),pStatesInfoData->getMaxChallengeTimes());
				NFC_setLabelString(_CUSTOM_VALUE_LABEL_,pTableCell,starLaberl,true);  

				NFC_setLabelByFontID(_CUSTOM_VALUE_LABEL_,pTableCell,42);
				NFC_setLabelByFontID(_CUSTOM_LEFT_LABEL_,pTableCell,96);
				if(pStatesInfoData->getLastChallengeTimes()<=0)
				{
					NFC_setLabelByFontID(_CUSTOM_VALUE_LABEL_,pTableCell,105);
				}
			}
			else
			{ 
				//��ʾ����
				NFC_setNodeVisable(_CUSTOM_LOCK_BG_,pTableCell,true);
				NFC_setNodeVisable(_CUSTOM_STAR_0_,pTableCell,false);
				NFC_setNodeVisable(_CUSTOM_STAR_1_,pTableCell,false);
				NFC_setNodeVisable(_CUSTOM_STAR_2_,pTableCell,false);		
				NFC_setNodeVisable(_CUSTOM_LEFT_LABEL_,pTableCell,false);
				NFC_setNodeVisable(_CUSTOM_VALUE_LABEL_,pTableCell,false);
			} 
		} 
	} 
}
 
cocos2d::CCSize SelectSonMissionWindow::cellSizeForTable(cocos2d::extension::CCTableView *table)
{ 
	return   m_nCellSize;
}

cocos2d::extension::CCTableViewCell* SelectSonMissionWindow::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
	cocos2d::extension::CCTableViewCell * cell = table->dequeueCell();
	if(!cell)
	{
		cell = new cocos2d::extension::CCTableViewCell();
		cell->autorelease();
		CreateTableCell(cell);
	}
	SetTableCell(cell,idx);
	return cell;
}

 unsigned int SelectSonMissionWindow::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
 {
	 if(m_pMissionInfoData)
	 {
		 if(m_bHadGotFullReward)
		 {
			 return  m_pMissionInfoData->getStatesInfoDataList().size();
		 }
		 else
		 {
			 return  m_pMissionInfoData->getStatesInfoDataList().size()+1;
		 }
	 }
	 return 0;
 }
 

void SelectSonMissionWindow::scrollViewDidScroll(cocos2d::extension::CCScrollView* view)
{ 
	if(m_pCustomTable)
	{ 
		unsigned int  cellArraySize = numberOfCellsInTableView(NULL);
		cocos2d::extension::CCTableViewCell * pTableViewCell = m_pCustomTable->cellAtIndex(0); 
		NFC_setNodeVisable(_MISSION_LEFT_SKELETON_EFFECT_,m_pRootNode,pTableViewCell!=NULL? false:true); 
		pTableViewCell = m_pCustomTable->cellAtIndex(cellArraySize-1); 
		NFC_setNodeVisable(_MISSION_RIGHT_SKELETON_EFFECT_,m_pRootNode,pTableViewCell!=NULL? false:true); 
	}
}

void  SelectSonMissionWindow::UpdateCustomView()
{
	//ˢ���б� ��λ�ӹؿ�(�Ƿ���Ҫ��λ���ǽ���) 
	UpdateCustomCellView();
	//������������ 
	UpdateRewardInfo();
	//������ս��ť״̬ 
	UpdateBtnStates();
	//������ս�����Լ�����������ʯ  
	UpdateCostLabel();
}

  
void SelectSonMissionWindow::UpdateUIWithData(bool isNeedLocationFullStar/* =true */)
{
	//���°�����
	m_nMissionID = MissionDataHandler::get_instance2()->getCurMissionID();
	m_pMissionInfoData = MissionDataHandler::get_instance2()->GetMissionInfo(m_nMissionID);

	//����UI��Ϣ
	m_sMissionName = SceneInfoDataManager::get_instance2()->GetCustomNameByID(m_nMissionID);
	NFC_setLabelString(_MISSION_TITTLE_LABEL_,m_pRootNode,m_sMissionName.c_str());

	//���ܶ�λCustomID
	AnlayseInitCustomID();

	if(isNeedLocationFullStar)
	{
		m_bCanGetFullReward = MissionDataHandler::get_instance2()->CheckFullStarsReward();
		m_bHadGotFullReward = m_pMissionInfoData->getHasGetReward();

		if(m_bCanGetFullReward)
		{
			m_nCustomID = m_nMaxCustomNum+1;  //ǿ�ƶ�λ�����ǽ��� 
		}  

		if(m_bIsJudgeFullAfterFight)
		{
			m_bIsJudgeFullAfterFight = false;
			//�ж��Ƿ���Ҫ��λ��һ��
			// 1.ȫͨ�� 2. �Ѿ���ȡ �������� ���� ������ȡ ���ǽ��� 3 �¸����û��ս����¼
		    StatesInfoData * pStatesInfoData = m_pMissionInfoData->getStatesInfoDataList().at(m_nMaxCustomNum-1);
			if(pStatesInfoData&&pStatesInfoData->getIsClear()&&(!m_pMissionInfoData->getIsCanReward()||m_pMissionInfoData->getHasGetReward()))
			{  
				JudgeToNextMission();
			} 
		}
	}

	UpdateCustomView();
}

//ˢ�¹ؿ��б����
void  SelectSonMissionWindow::UpdateCustomCellView()
{ 
	//�����Ǽ򵥵�ˢ�� 
	int offSetValue = m_nCustomID/maxCellUnitCount; 
	if(offSetValue >=1)
	{ 
		int maxCustomValue = 0; 
		if(m_bHadGotFullReward)
		{
			maxCustomValue = m_nMaxCustomNum;
		}
	    else
		{
			maxCustomValue = m_nMaxCustomNum+1;
		}
		if(m_nCustomID > maxCustomValue-maxCellUnitCount)
		{
			NFC_refreshTableViewForH(m_pCustomTable,cocos2d::CCSizeMake((maxCustomValue-maxCellUnitCount)*m_nCellSize.width,0.0f));
		}
		else 
		{
			if(m_nCustomID%maxCellUnitCount>0)
			{
				NFC_refreshTableViewForH(m_pCustomTable,cocos2d::CCSizeMake(4*m_nCellSize.width*offSetValue,0.0f));
			}
			else
			{
				NFC_refreshTableViewForH(m_pCustomTable,cocos2d::CCSizeMake(4*m_nCellSize.width*(offSetValue-1),0.0f)); 
			} 
		}  
	}
	else
	{ 
		NFC_refreshTableViewForH(m_pCustomTable,cocos2d::CCSizeMake(0.0f,0.0f));
	} 
	
	scrollViewDidScroll(NULL);
}
 
//ˢ�½�����Ϣ����
void  SelectSonMissionWindow::UpdateRewardInfo()
{  
	if(m_pMissionInfoData)
	{ 
		size_t  rewardCount = 0;
		int		rewardTagArray[] ={_MISSION_REWARD_ITEM_0_,_MISSION_REWARD_ITEM_1_,_MISSION_REWARD_ITEM_2_};
		if(m_nCustomID > m_nMaxCustomNum)
		{
			//��ʾ���ǽ��� 
			NFC_setNodeVisable(_MISSION_REWARD_EXP_IMAGE_,m_pRootNode,false);
			NFC_setNodeVisable(_MISSION_REWARD_EXP_VALUE_,m_pRootNode,false);
			NFC_setNodeVisable(_MISSION_REWARD_MONEY_IMAGE_,m_pRootNode,false);
			NFC_setNodeVisable(_MISSION_REWARD_MONEY_VALUE_,m_pRootNode,false);
			NFC_setNodeVisable(_MISSION_REWARD_MONEY_VALUE_,m_pRootNode,false); 
			NFC_setLabelString(_MISSION_REWARD_LABEL_,m_pRootNode,nFullStar_Reward_TID,true);  
			NFC_setNodeVisable(_MISSION_PERHAPS_REWARD_LABEL_,m_pRootNode,false);

			rewardCount = m_pMissionInfoData->getStarRewardDataList().size();
	
			COMMON_BEIGIN_ARRAY(size_t,3)
				if(index < rewardCount) 
				{
					PRewardItemNode pRewardItem = m_pMissionInfoData->getStarRewardDataList().at(index);
					UpdateRewardInfoWithData(pRewardItem,rewardTagArray[index],m_nMaxCustomNum+1,index);
				}
				else
				{
					NFC_setNodeVisable(rewardTagArray[index],m_pRootNode,false);
				}
			COMMON_END_ARRAY 
		}
		else if(m_nCustomID <= m_nMaxCustomNum)
		{
			//��ʾһ�㽱������
			//���� ��ҽ��� 
			StatesInfoData * pCustomInfoData = m_pMissionInfoData->getStatesInfoDataList().at(m_nCustomID-1);
			if(pCustomInfoData)
			{
				NFC_setLabelStringInt(_MISSION_REWARD_EXP_VALUE_,m_pRootNode,pCustomInfoData->getExp(),true);
				NFC_setLabelStringInt(_MISSION_REWARD_MONEY_VALUE_,m_pRootNode,pCustomInfoData->getMoney(),true);

				NFC_setNodeVisable(_MISSION_REWARD_EXP_IMAGE_,m_pRootNode,true);
				NFC_setNodeVisable(_MISSION_REWARD_MONEY_IMAGE_,m_pRootNode,true);  
				NFC_setLabelString(_MISSION_REWARD_LABEL_,m_pRootNode,146,true);
				NFC_setNodeVisable(_MISSION_PERHAPS_REWARD_LABEL_,m_pRootNode,true);
				   
				rewardCount = pCustomInfoData->getItemInfoDataList().size();
				COMMON_BEIGIN_ARRAY(size_t,3)
					if(index < rewardCount)
					{
						PRewardItemNode pRewardItem = pCustomInfoData->getItemInfoDataList().at(index);
						UpdateRewardInfoWithData(pRewardItem,rewardTagArray[index],m_nCustomID,index);
					}
					else
					{
						NFC_setNodeVisable(rewardTagArray[index],m_pRootNode,false);
					}
				COMMON_END_ARRAY 
			} 
		}
	}
}
//ˢ�°�ť״̬
void  SelectSonMissionWindow::UpdateBtnStates()
{
	//��ť״̬ 1. ��ս	2. ɨ�� ��ս   3 ɨ�� ���	 4. ��ȡ
	if(m_nCustomID > m_nMaxCustomNum)
	{
		//��ʾ��ť���� ��ʾ��ť��Ч
		NFC_setNodeVisable(_MISSION_CHALLENEGE_BTN_,m_pRootNode,false);
		NFC_setNodeVisable(_MISSION_CHALLENEGE_LABEL_,m_pRootNode,false);
		NFC_setNodeVisable(_MISSION_WIPE_BTN_,m_pRootNode,false);
		NFC_setNodeVisable(_MISSION_WIPE_LABEL_,m_pRootNode,false);
		NFC_setNodeVisable(_MISSION_WIPE_LABEL_,m_pRootNode,false);
		NFC_setNodeVisable(_MISSION_CLEAR_BTN_,m_pRootNode,false);
		NFC_setNodeVisable(_MISSION_CLEAR_LABEL_,m_pRootNode,false); 
		NFC_setNodeVisable(_MISSION_FULLSTAR_REWARD_BTN_,m_pRootNode,true);
		NFC_setNodeVisable(_MISSION_FULLSTAR_REWARD_LABEL_,m_pRootNode,true);
		NFC_setNodeVisable(_MISSION_COST_POWER_LABEL_,m_pRootNode,false);
		NFC_setNodeVisable(_MISSION_RESER_JEWEL_IMAGE_,m_pRootNode,false); 
		NFC_bindSelectorForBtn(_MISSION_FULLSTAR_REWARD_BTN_,m_pRootNode,this,menu_selector(SelectSonMissionWindow::CommonSelectorHandler));
		//��ʾ���ǽ��� ��ť״̬
		if(m_bCanGetFullReward)
		{
			
			NFC_setMenuEnable(_MISSION_FULLSTAR_REWARD_BTN_,m_pRootNode,true);
			NFC_setNodeVisable(_MISSION_RIGHT_BTN_EFFECT_,m_pRootNode,true);  //���Ű�ť��Ч
			//��ʾ��ͷ��ǩ
			ShowGuidArrowSkeleton(true);
			
		}
		else
		{ 
			ShowGuidArrowSkeleton(false);
			NFC_setMenuEnable(_MISSION_FULLSTAR_REWARD_BTN_,m_pRootNode,false);
			NFC_setNodeVisable(_MISSION_RIGHT_BTN_EFFECT_,m_pRootNode,false);  //�رհ�ť��Ч
			//���ð�ť
		} 
	}
	else
	{
		//��ʾ ���������
		 StatesInfoData *  pStatesInfoData = m_pMissionInfoData->getStatesInfoDataList().at(m_nCustomID-1);
		 if(pStatesInfoData)
		 {
			 NFC_setNodeVisable(_MISSION_WIPE_BTN_,m_pRootNode,false);
			 NFC_setNodeVisable(_MISSION_WIPE_LABEL_,m_pRootNode,false);
			 NFC_setNodeVisable(_MISSION_CLEAR_BTN_,m_pRootNode,false);
			 NFC_setNodeVisable(_MISSION_CLEAR_LABEL_,m_pRootNode,false);
			 NFC_setNodeVisable(_MISSION_FULLSTAR_REWARD_BTN_,m_pRootNode,false);
			 NFC_setNodeVisable(_MISSION_FULLSTAR_REWARD_LABEL_,m_pRootNode,false);
			 NFC_setNodeVisable(_MISSION_CHALLENEGE_BTN_,m_pRootNode,false); 
			 NFC_setNodeVisable(_MISSION_CHALLENEGE_LABEL_,m_pRootNode,false); 
			 NFC_setNodeVisable(_MISSION_RIGHT_BTN_EFFECT_,m_pRootNode,false); 
			 ShowGuidArrowSkeleton(true);

			 if(pStatesInfoData->getIsClear())
			 {
				 NFC_setNodeVisable(_MISSION_WIPE_BTN_,m_pRootNode,true);
				 NFC_setNodeVisable(_MISSION_WIPE_LABEL_,m_pRootNode,true);
				 if( pStatesInfoData->getLastChallengeTimes() <= 0)
				 NFC_setMenuEnable(_MISSION_WIPE_BTN_,m_pRootNode,false);
				 else
				 NFC_setMenuEnable(_MISSION_WIPE_BTN_,m_pRootNode,true);
				 //�Ƿ����ɨ��

				ShowGuidArrowSkeleton(false);
			 }  
			 CCLOG("Challenege Level : %d",pStatesInfoData->getChallengeLevel());
			 if(pStatesInfoData->getCanChallenge() && pStatesInfoData->getChallengeLevel() <= m_nPlayerLevel)
			 {   
				 //�ж�ʣ������Ƿ�����
				 if(pStatesInfoData->getLastChallengeTimes() <= 0)
				 {
					 if(pStatesInfoData->getIsBoss())
					 {
						 //��ʾ���������ť
						 NFC_setNodeVisable(_MISSION_CLEAR_BTN_,m_pRootNode,true); 
						 NFC_setNodeVisable(_MISSION_CLEAR_LABEL_,m_pRootNode,true);
					 }
					 else
					 {
						 //��ֹ��ť
						 NFC_setNodeVisable(_MISSION_CHALLENEGE_BTN_,m_pRootNode,true);
						 NFC_setNodeVisable(_MISSION_CHALLENEGE_LABEL_,m_pRootNode,true);
						 NFC_setMenuEnable(_MISSION_CHALLENEGE_BTN_,m_pRootNode,false);
					 }
				 }
				 else
				 {
					 //������ս��ť
					 NFC_setNodeVisable(_MISSION_CHALLENEGE_BTN_,m_pRootNode,true);
					 NFC_setNodeVisable(_MISSION_CHALLENEGE_LABEL_,m_pRootNode,true);
					 NFC_setMenuEnable(_MISSION_CHALLENEGE_BTN_,m_pRootNode,true);
				 } 
			 }
			 else 
			 {  
				 if(pStatesInfoData->getLastChallengeTimes()<=0&&pStatesInfoData->getIsBoss())
				 {
					 //��ʾ���������ť
					 NFC_setNodeVisable(_MISSION_CLEAR_BTN_,m_pRootNode,true); 
					 NFC_setNodeVisable(_MISSION_CLEAR_LABEL_,m_pRootNode,true); 
				 }
				 else
				 {
					 //��ʾ������ս��ť
					 NFC_setNodeVisable(_MISSION_CHALLENEGE_BTN_,m_pRootNode,true);
					 NFC_setNodeVisable(_MISSION_CHALLENEGE_LABEL_,m_pRootNode,true);
					 NFC_setMenuEnable(_MISSION_CHALLENEGE_BTN_,m_pRootNode,false);
				 }
			 } 
		 } 
	}  
}

//ˢ�»�������
void  SelectSonMissionWindow::UpdateCostLabel()
{ 
	//1. ��ʾ��������  2.��ʾ����������ʯ�� 3. ʲô������ʾ
	if( m_nCustomID > m_nMaxCustomNum )
	{
		NFC_setNodeVisable(_MISSION_COST_POWER_LABEL_,m_pRootNode,false);
		NFC_setNodeVisable(_MISSION_RESER_JEWEL_IMAGE_,m_pRootNode,false);
	}
	else
	{
		StatesInfoData * pStatesInfoData = m_pMissionInfoData->getStatesInfoDataList().at(m_nCustomID-1);
		if(pStatesInfoData->getLastChallengeTimes()<=0&&pStatesInfoData->getIsBoss())
		{   
			//��ʾ������ʯ��
			char dimondStr[16]={0};
			sprintf(dimondStr,"%d",pStatesInfoData->getClearNeedDiamondNum());
			NFC_setLabelString(_MISSION_COST_POWER_LABEL_,m_pRootNode,dimondStr,true);
			NFC_setNodeVisable(_MISSION_RESER_JEWEL_IMAGE_,m_pRootNode,true);
		}
		else
		{
			//��ʾ����������
			NFC_setNodeVisable(_MISSION_RESER_JEWEL_IMAGE_,m_pRootNode,false);
			NFC_setLabelStringInt(_MISSION_COST_POWER_LABEL_,m_pRootNode,pStatesInfoData->getCostTL(),135,true);
		}
	} 
}
 
void SelectSonMissionWindow::CheckGuid()
{
	int missionID=MissionDataHandler::get_instance2()->getCurMissionID();
	int sonmissionID=MissionDataHandler::get_instance2()->getCurStatesID();
	if (missionID==1&&sonmissionID<=2)
	{ 
		//��������ѩ��
		if (!GUIDESYSTEM->isPaused())
		{
			if(sonmissionID<2&&GUIDESYSTEM->IsNeedGuide())
				m_bDuringGuid = true;
			GUIDESYSTEM->Next();
		}
	}
}

void  SelectSonMissionWindow::UpdateRewardInfoWithData(PRewardItemNode pRewardItemNode,int ItemUIInidex,int customID,int interIndex)
{
	if(pRewardItemNode)
	{  
		DTAwardBoard* award = (DTAwardBoard*)m_pRootNode->getChildByTag(ItemUIInidex);
		NFC_setNodeVisable(ItemUIInidex,m_pRootNode,true);
		int quality = -1;
		int iconid = -1;
		bool isEnabled=false;
		switch (pRewardItemNode->rewardItemType)
		{
		case  kDT_AWARD_OBJECT:
			{     
				quality = pRewardItemNode->rewardQuality;
				iconid =  pRewardItemNode->rewardIconID;
				isEnabled=true; 
				break;
			}
		case   kDT_AWARD_MONEY:
			{   
				quality=_GOLD_QUALITY_RESID_;
				iconid=_GOLD_ICON_RESID_; 
				break;
			}
		case  kDT_AWARD_EXP:
			{
				quality=_EXP_QUALITY_RESID_;
				iconid=_EXP_ICON_RESID_; 
				break;
			}
		case  kDT_AWARD_DIAMOND:
			{
				quality=_DIAMOND_QUALITY_RESID_;
				iconid=_DIAMOND_ICON_RESID_; 
				break;
			}
		case kDT_AWARD_PRESTIGE:
			{
				quality=_PREGIST_QUALITY_RESID_;
				iconid=_PREGIST_ICON_RESID_; 
				break;
			}
		case kDT_AWARD_POWER:
			{
				quality=_POWER_QUALITY_RESID_;
				iconid=_POWER_ICON_RESID_; 
				break;
			}
		default:
			break;
		} 
		if(isEnabled)
		{ 
			award->setAttachParam(customID,interIndex);
			award->setTarget(this,menu_selector(SelectSonMissionWindow::RewardTipsInfoHandler));
		}
		award->ChangeObject(quality,iconid,pRewardItemNode->rewardItemCount);
		award->setEnabled(isEnabled);
	}
}



void  SelectSonMissionWindow::UpdateCellStarNum(cocos2d::extension::CCTableViewCell * pTableCell,IByte starNum)
{ 
	if(pTableCell)
	{
		switch(starNum)
		{
		case  0:
			{
				NFC_changeImageForCSprite(_CUSTOM_STAR_0_,pTableCell,1);
				NFC_changeImageForCSprite(_CUSTOM_STAR_1_,pTableCell,1);
				NFC_changeImageForCSprite(_CUSTOM_STAR_2_,pTableCell,1);
				break;
			}
		case 1:
			{
				NFC_changeImageForCSprite(_CUSTOM_STAR_0_,pTableCell,0);
				NFC_changeImageForCSprite(_CUSTOM_STAR_1_,pTableCell,1);
				NFC_changeImageForCSprite(_CUSTOM_STAR_2_,pTableCell,1);
				break;
			}
		case 2:
			{ 
				NFC_changeImageForCSprite(_CUSTOM_STAR_0_,pTableCell,0);
				NFC_changeImageForCSprite(_CUSTOM_STAR_1_,pTableCell,0);
				NFC_changeImageForCSprite(_CUSTOM_STAR_2_,pTableCell,1);
				break;
			}
		case  3:
			{
				NFC_changeImageForCSprite(_CUSTOM_STAR_0_,pTableCell,0);
				NFC_changeImageForCSprite(_CUSTOM_STAR_1_,pTableCell,0);
				NFC_changeImageForCSprite(_CUSTOM_STAR_2_,pTableCell,0);
				break;
			}
		default:
			{ 
				NFC_changeImageForCSprite(_CUSTOM_STAR_0_,pTableCell,1);
				NFC_changeImageForCSprite(_CUSTOM_STAR_1_,pTableCell,1);
				NFC_changeImageForCSprite(_CUSTOM_STAR_2_,pTableCell,1);
				break;
			}
		} 
	}
}


void  SelectSonMissionWindow::ShowGuidArrowSkeleton(bool showEnable)
{
	if(!showEnable)
	{
		NFC_setNodeVisable(_MISSION_ARROW_GUID_SKELETON_,m_pRootNode,false);
	}
	else
	{
		if(m_bDuringGuid)
		{
			NFC_setNodeVisable(_MISSION_ARROW_GUID_SKELETON_,m_pRootNode,false);
		}
		else
		{
			NFC_setNodeVisable(_MISSION_ARROW_GUID_SKELETON_,m_pRootNode,true);
		}
	} 
}

void SelectSonMissionWindow::AnlayseInitCustomID()
{
	m_nPlayerLevel = RoleInfoDataHandler::get_instance2()->m_pRIData->level_; 
	 
	m_nMaxCustomNum = m_pMissionInfoData->getStatesInfoDataList().size(); 
	m_nMaxCanChallenegCID = m_pMissionInfoData->getCurStatesID();

	if(MissionDataHandler::get_instance2()->getIsForceLocationCustom())
	{
		m_nCustomID = MissionDataHandler::get_instance2()->getCurStatesID(); 
		if(m_nCustomID > m_nMaxCanChallenegCID)
		m_nCustomID = m_nMaxCanChallenegCID;
		MissionDataHandler::get_instance2()->setIsForceLocationCustom(false);
	} 
	else
	{
		//��ǿ�ƶ�λ
		if(m_bIsNeedAutoUp)
		{
			m_nCustomID =  m_nMaxCanChallenegCID;
		}
		else
		{
			if(m_pMissionInfoData->getHistorySID()!=-1)
			{
				m_nCustomID = m_pMissionInfoData->getHistorySID(); 
			}
			else
			{
				if(m_bIsReconverReNetSID)
				{
					m_bIsReconverReNetSID = false;
					m_nCustomID = m_nReNetReConverSID;
				}
				else
				m_nCustomID = m_nMaxCanChallenegCID;
			}  
		}  
	} 

	if(m_nCustomID > m_nMaxCanChallenegCID)
	m_nCustomID = m_nMaxCanChallenegCID;

	if(m_nCustomID <= 0)
	m_nCustomID = 1; 

	CheckIsNeedAutoUp();
}
 

void  SelectSonMissionWindow::CheckIsNeedAutoUp()
{
	if(m_nCustomID <= m_nMaxCustomNum)
	{
		MissionDataHandler::get_instance2()->setCurStatesID(m_nCustomID); 
		m_pMissionInfoData->setHistorySID(m_nCustomID);
		m_nReNetReConverSID = m_nCustomID;
	}
	else
	{ 
		MissionDataHandler::get_instance2()->setCurStatesID(m_nMaxCustomNum); 
		m_pMissionInfoData->setHistorySID(m_nMaxCustomNum);
		m_nReNetReConverSID = m_nMaxCustomNum;
	}  
	if(m_nCustomID+1<=m_nMaxCustomNum)
	{
		//�ж��Ƿ���Ҫ�Զ�����
		StatesInfoData * pNextStatesInfo = m_pMissionInfoData->getStatesInfoDataList().at(m_nCustomID);
		if(pNextStatesInfo->getIsClear())
		{
			m_bIsNeedAutoUp = false;
		}
		else
		{
			m_bIsNeedAutoUp = true;
		}
	} 
	else
	{
		m_bIsNeedAutoUp = false;
	}
}

void   SelectSonMissionWindow::JudgeToNextMission()
{
	if (MissionDataHandler::get_instance2()->CheckIsNeedJumpNextMisson())
	{
		//��ʾ��ʾ�� ����ϲ��ͨ����%s���Ƿ�����������һ�ؿ�����
		char temp[128]="";
		std::string   sceneName = SceneInfoDataManager::get_instance2()->GetCustomNameByID(m_pMissionInfoData->getMissionID());
		sprintf(temp,SysLangDataManager::get_instance2()->GetSysLangById(4028).c_str(),sceneName.c_str());
		NFC_showMessageBox(kMISSION_GOTONEXTMAP,temp);
		MissionDataHandler::get_instance2()->setIsNeedJump(false);
	}  
}
