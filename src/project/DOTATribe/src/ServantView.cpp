//Name ; ServantView.h
//Function：仆从系统
//Author : fangjun
//Date: 20131029

#include "../include/ServantView.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/LoggerSystem.h"
#include "../include/UIViewDataManger.h"
#include "../include/CPublicVarReader.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/CMenuItemSprite.h"
#include "../include/CSprite.h"
#include "../include/ServantDataHandler.h"
#include "../include/NFControlsManager.h"
#include "../include/SysLangDataManager.h"
#include "../include/ResourceIDDataManager.h"
#include "../include/IDStringDataManager.h"
#include "../include/TimeSystem.h"
#include "../include/MessageBoxWindow.h"

using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

ServantView::ServantView()
	:m_pRoot(NULL)
	,m_pViewRoot(NULL)
	,m_pLeftTable(NULL)
	,m_pRightTable(NULL)
	,m_iPageType(-1)
	,m_pSelectSubPage(NULL)
{

}

ServantView::~ServantView()
{

}

bool ServantView::onLoad()
{
	if(CCNode::init()){
		setPosition(CCPointZero);
		this->autorelease();

		_initLayout();

		SERVANTDATAHANDLER->m_iWillEnterAthletic = false;
		
		return true;
	}

	return false;
}

bool ServantView::onDestroy()
{
	m_pSelectSubPage = NULL;
	m_iPageType = -1;

	SERVANTDATAHANDLER->m_iWillEnterAthletic = false;

	this->removeAllChildrenWithCleanup(true);
	this->removeFromParentAndCleanup(true);

	return true;
}

bool ServantView::onTick()
{
	SlaveWorkTick();

	CatchCdTick();

	return true;
}

void ServantView::SlaveWorkTick()
{
	if(SERVANTDATAHANDLER->m_pSMPlayInfo)
	{
		long long nowtime = TimeSystem::get_instance2()->GetCurrentMicroSecond();
		long long during = nowtime - SERVANTDATAHANDLER->m_pSMPlayInfo->longTickBeginTime;
		int seconds = (int)(during / 1000000);
		if(seconds >= 1)
		{
			SERVANTDATAHANDLER->m_pSMPlayInfo->longTickBeginTime = nowtime;
			SMSlave * slave = NULL;
			for(int i = 0; i < USER_MAX_SLAVE; ++i)
			{
				slave = SERVANTDATAHANDLER->m_pSMPlayInfo->slaveVector[i];
				if(slave)
				{
					slave->workSeconds += seconds;
					slave->secondsCount += seconds;
					slave->chainCdLeftTime -= seconds;

					if(slave->secondsCount >= 60)
					{
						slave->makeExp += slave->expPerMin;
						slave->secondsCount = 0;
					}

					if(m_iPageType == _PAGE_TYPE_MASTER_1_)
					{
						//工作时间
						char temp[32] = {0};
						sprintf(temp, "%02d:%02d:%02d", slave->workSeconds / 3600, (slave->workSeconds % 3600) / 60, (slave->workSeconds % 3600) % 60);
						NFC_setLabelString(m1Slave0WorkTimesValue + i * 15, m_pViewRoot, temp, true);
						NFC_setLabelStringInt(m1Slave0ExpValue + i * 15, m_pViewRoot, slave->makeExp, true);
				
						//压榨倒计时
						if(SERVANTDATAHANDLER->m_pSMPlayInfo->leftPlayTimes > 0)
						{
							if(slave->chainCdLeftTime > 0)
							{
								char temp[32] = {0};
								sprintf(temp, "%02d:%02d", slave->chainCdLeftTime / 60, slave->chainCdLeftTime % 60);
								NFC_setLabelString(m1Slave0ChainLabel + i * 15, m_pViewRoot, temp, true);
								CCMenu * menu = (CCMenu *)m_pViewRoot->getChildByTag(m1Slave0ChainBtn + i * 15);
								CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(m1Slave0ChainBtn + i * 15);
								item->setEnabled(false);
							}
							else if(slave->chainCdLeftTime == 0 || slave->chainCdLeftTime == -1)
							{
								NFC_setLabelString(m1Slave0ChainLabel + i * 15, m_pViewRoot, SysLangDataManager::get_instance2()->GetSysLangById(948), true);
								CCMenu * menu = (CCMenu *)m_pViewRoot->getChildByTag(m1Slave0ChainBtn + i * 15);
								CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(m1Slave0ChainBtn + i * 15);
								item->setEnabled(true);
							}
						}
						
					}
				}
			}
		}

	}
}

void ServantView::CatchCdTick()
{
	SMCatchInfo * data = SERVANTDATAHANDLER->m_pSMCatchInfo;
	if(data)
	{//计算冷却时间
		long long nowtime = TimeSystem::get_instance2()->GetCurrentMicroSecond();
		long long during = nowtime - data->longTickBeginTime;
		int seconds = (int)(during / 1000000);
		if(seconds >= 1)
		{
			data->longTickBeginTime = nowtime;
			SMFightedPlayer * player = NULL;
			//仇人
			for(int i = 0; i < (int)data->winnerVector.size(); ++i)
			{
				player = data->winnerVector[i];
				if(player)
				{
					player->catchCdLeftTime -= seconds;

					//更新显示
					if(m_iPageType == _PAGE_TYPE_MASTER_0_)
					{
						if(player->catchCdLeftTime > 0)
						{
							char temp[32] = {0};
							sprintf(temp, "%02d:%02d", player->catchCdLeftTime / 60, player->catchCdLeftTime % 60);

							cocos2d::extension::CCTableViewCell * cell = m_pRightTable->cellAtIndex(i);
							if(cell)
							{
								NFC_setLabelString(mc0CatchBtnLabel, cell, temp, true);
								CCMenu * menu = (CCMenu *)cell->getChildByTag(mc0CatchBtn);
								CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(0);
								item->setEnabled(false);
							}
							
						}
						else if(player->catchCdLeftTime == 0 || player->catchCdLeftTime == -1)
						{
							cocos2d::extension::CCTableViewCell * cell = m_pRightTable->cellAtIndex(i);
							if(cell)
							{
								NFC_setLabelString(mc0CatchBtnLabel, cell, SysLangDataManager::get_instance2()->GetSysLangById(947), true);
								CCMenu * menu = (CCMenu *)cell->getChildByTag(mc0CatchBtn);
								CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(0);
								item->setEnabled(true);
							}
							
						}		
					
					}

				}

			}

			//手下败将
			for(int i = 0; i < (int)data->losserVector.size(); ++i)
			{
				player = data->losserVector[i];
				if(player)
				{
					player->catchCdLeftTime -= seconds;

					//更新显示
					if(m_iPageType == _PAGE_TYPE_MASTER_0_)
					{
						if(player->catchCdLeftTime > 0)
						{
							char temp[32] = {0};
							sprintf(temp, "%02d:%02d", player->catchCdLeftTime / 60, player->catchCdLeftTime % 60);

							cocos2d::extension::CCTableViewCell * cell = m_pLeftTable->cellAtIndex(i);
							if(cell)
							{
								NFC_setLabelString(mc0CatchBtnLabel, cell, temp, true);
								CCMenu * menu = (CCMenu *)cell->getChildByTag(mc0CatchBtn);
								CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(0);
								item->setEnabled(false);
							}
							
						}
						else if(player->catchCdLeftTime == 0 || player->catchCdLeftTime == -1)
						{
							cocos2d::extension::CCTableViewCell * cell = m_pLeftTable->cellAtIndex(i);
							if(cell)
							{
								NFC_setLabelString(mc0CatchBtnLabel, cell, SysLangDataManager::get_instance2()->GetSysLangById(947), true);
								CCMenu * menu = (CCMenu *)cell->getChildByTag(mc0CatchBtn);
								CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(0);
								item->setEnabled(true);
							}

						}		

					}

				}

			}
		}

	}

}

void ServantView::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	//此函数此处没用了，已无作用

	SERVANTDATAHANDLER->m_iWillEnterAthletic = false;

	if(paramList.size() > 0)
	{
		int page = 0;
		std::string str = *paramList.begin();
		sscanf(str.c_str(), "%d", &page);
		if(ROLEINFODATAHANDLER->m_pRIData->slaveIdentity_ == SERVANT_ID_SLAVE)
		{
			if(page == _PAGE_TYPE_SLAVE_0_ || page == _PAGE_TYPE_SLAVE_1_ || page == _PAGE_TYPE_SLAVE_2_)
			{
				m_iPageType = page;
			}
			else
			{
				m_iPageType = _PAGE_TYPE_SLAVE_0_;
			}
		}
		else
		{
			if(page == _PAGE_TYPE_MASTER_0_ || page == _PAGE_TYPE_MASTER_1_ || page == _PAGE_TYPE_MASTER_2_)
			{
				m_iPageType = page;
			}
			else
			{
				m_iPageType = _PAGE_TYPE_MASTER_0_;
			}
		}
		//请求对应界面的信息
		_requestShowPageData();

		//选中选中的分页标签
		_setSelectPageTab();

		//显示分页
		_showViewPage();
	}
}

void ServantView::AthleticBackShow()
{

}

void ServantView::_initLayout()
{
	m_pRoot = this;

	//创建主界面
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSERVANTWINDOW, m_pRoot);
	_mapMainPage();
	m_pViewRoot = m_pRoot->getChildByTag(mViewNode);

	int page = SERVANTDATAHANDLER->m_iLastStayPage;

	LOGGERSYSTEM->LogInfo("My identity is ---------------- [%d] ---------------", ROLEINFODATAHANDLER->m_pRIData->slaveIdentity_);

	if(ROLEINFODATAHANDLER->m_pRIData->slaveIdentity_ == SERVANT_ID_SLAVE)
	{
		if(page == _PAGE_TYPE_SLAVE_0_ || page == _PAGE_TYPE_SLAVE_1_ || page == _PAGE_TYPE_SLAVE_2_)
		{
			m_iPageType = page;
		}
		else
		{
			m_iPageType = _PAGE_TYPE_SLAVE_0_;
		}
	}
	else
	{
		if(page == _PAGE_TYPE_MASTER_0_ || page == _PAGE_TYPE_MASTER_1_ || page == _PAGE_TYPE_MASTER_2_)
		{
			m_iPageType = page;
		}
		else
		{
			m_iPageType = _PAGE_TYPE_MASTER_0_;
		}
	}

	//设置默认选中界面
	//_initDefaultPage();

	//请求对应界面的信息
	_requestShowPageData();

	//选中选中的分页标签
	_setSelectPageTab();

	//显示分页
	_showViewPage();
}

void ServantView::_mapMainPage()
{
	CCMenu * menu = NULL;
	CMenuItemSprite * item = NULL;
	for(int i = mPage0Btn; i <= mPage2Btn; i += 2)
	{
		menu = (CCMenu *)m_pRoot->getChildByTag(i);
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(i);
		item->setTarget(this, menu_selector(ServantView::On_MainPage_Btn_Click));
	}
}

void ServantView::_initDefaultPage()
{
	//根据本人的状态获得当前显示页面种类
	//选择选中页面的tab
	int idt = ROLEINFODATAHANDLER->m_pRIData->slaveIdentity_;
	if(idt == SERVANT_ID_SLAVE)
	{
		m_iPageType = _PAGE_TYPE_SLAVE_0_;
	}
	else
	{
		m_iPageType = _PAGE_TYPE_MASTER_0_;
	}
}

void ServantView::_setSelectPageTab()
{
	CCMenu * menu = NULL;
	CMenuItemSprite * item = NULL;

	if(m_iPageType == _PAGE_TYPE_MASTER_0_ || m_iPageType == _PAGE_TYPE_MASTER_1_ || m_iPageType == _PAGE_TYPE_MASTER_2_)
	{
		NFC_setLabelString(mPage0Label, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(940), true);
		NFC_setLabelString(mPage1Label, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(941), true);
		NFC_setLabelString(mPage2Label, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(942), true);
	}
	else
	{
		NFC_setLabelString(mPage0Label, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(943), true);
		NFC_setLabelString(mPage1Label, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(941), true);
		NFC_setLabelString(mPage2Label, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(944), true);

	}

	if(m_iPageType == _PAGE_TYPE_MASTER_0_ || m_iPageType == _PAGE_TYPE_SLAVE_0_)
	{
		//选中标签页0，并显示抓捕
		menu = (CCMenu *)m_pRoot->getChildByTag(mPage0Btn);
		item = (CMenuItemSprite *)menu->getChildByTag(mPage0Btn);
		if(m_pSelectSubPage != item)
		{
			if(m_pSelectSubPage)
			{
				m_pSelectSubPage->unselected();
			}
		}
		m_pSelectSubPage = item;
		m_pSelectSubPage->selected(true);
	}
	else if(m_iPageType == _PAGE_TYPE_MASTER_1_ || m_iPageType == _PAGE_TYPE_SLAVE_1_)
	{
		//选中标签页1，并显示互动
		menu = (CCMenu *)m_pRoot->getChildByTag(mPage1Btn);
		item = (CMenuItemSprite *)menu->getChildByTag(mPage1Btn);
		if(m_pSelectSubPage != item)
		{
			if(m_pSelectSubPage)
			{
				m_pSelectSubPage->unselected();
			}
			m_pSelectSubPage = item;
			m_pSelectSubPage->selected(true);
		}
	}
	else if(m_iPageType == _PAGE_TYPE_MASTER_2_ || m_iPageType == _PAGE_TYPE_SLAVE_2_)
	{
		//选中标签页2，并显示解救
		menu = (CCMenu *)m_pRoot->getChildByTag(mPage2Btn);
		item = (CMenuItemSprite *)menu->getChildByTag(mPage2Btn);
		if(m_pSelectSubPage != item)
		{
			if(m_pSelectSubPage)
			{
				m_pSelectSubPage->unselected();
			}
			m_pSelectSubPage = item;
			m_pSelectSubPage->selected(true);
		}
	}

}

void ServantView::_showViewPage()
{
	LOGGERSYSTEM->LogInfo("ServantView::_showViewPage  -- begin\n");
	//显示选中的页面
	switch(m_iPageType)
	{
	case _PAGE_TYPE_MASTER_0_ :_showMasterCatchPage(m_pViewRoot);	break;
	case _PAGE_TYPE_MASTER_1_ :_showMasterPlayPage(m_pViewRoot);	break;
	case _PAGE_TYPE_MASTER_2_ :_showMasterRescuePage(m_pViewRoot);	break;
	case _PAGE_TYPE_SLAVE_0_ :_showSlaveRevoltPage(m_pViewRoot);	break;
	case _PAGE_TYPE_SLAVE_1_ :_showSlavePlayPage(m_pViewRoot);		break;
	case _PAGE_TYPE_SLAVE_2_ :_showSlaveSOSPage(m_pViewRoot);		break;
	default:break;
	}
	LOGGERSYSTEM->LogInfo("ServantView::_showViewPage  -- end\n");
}


cocos2d::CCSize ServantView::cellSizeForTable(cocos2d::extension::CCTableView *table)
{
	if(m_iPageType == _PAGE_TYPE_MASTER_0_)
	{
		if(table == m_pLeftTable)
		{
			return m_szCELLLeft;
		}
		else
		{
			return m_szCELLRight;
		}
	}
	else
	{
		return m_szCELL;
	}
}

cocos2d::extension::CCTableViewCell* ServantView::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
	int tabletype = -1;
	if(table == m_pTable)
	{
		tabletype = _TABLE_TYPE_ONE_;
	}
	else if(table == m_pLeftTable)
	{
		tabletype = _TABLE_TYPE_LEFT_;
	}
	else if(table == m_pRightTable)
	{
		tabletype = _TABLE_TYPE_RIGHT_;
	}

	CCTableViewCell * cell = table->dequeueCell();
	if(cell == NULL)
	{
		cell = new CCTableViewCell();
		cell->autorelease();
		_createTableCell(cell, tabletype);
	}

	_setTableCell(cell, idx, tabletype);

	return cell;
}

void ServantView::_createTableCell(cocos2d::extension::CCTableViewCell* cell, int tableType)
{
	if(m_iPageType == _PAGE_TYPE_MASTER_0_)
	{
		//此处左右两侧的界面相同，故其中使用的节点也是相同的

		if(tableType == _TABLE_TYPE_LEFT_)
		{
			//左侧
			UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSERVANTMASTERPAGE0_CELL, cell);
		}
		else if(tableType == _TABLE_TYPE_RIGHT_)
		{
			//右侧
			UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSERVANTMASTERPAGE0_CELL, cell);
		}
	}
	else if(m_iPageType == _PAGE_TYPE_MASTER_1_)
	{
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSERVANT_MASTER_NEWS_CELL, cell);
	}
	else if(m_iPageType == _PAGE_TYPE_MASTER_2_)
	{
		if(tableType == _TABLE_TYPE_ONE_)
		{
			UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSERVANTMASTERPAGE2_CELL, cell);
		}
	}
	else if(m_iPageType == _PAGE_TYPE_SLAVE_1_)
	{
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSERVANT_SLAVE_NEWS_CELL, cell);
	}
	else if(m_iPageType == _PAGE_TYPE_SLAVE_2_)
	{
		if(tableType == _TABLE_TYPE_ONE_)
		{
			UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSERVANTSLAVEPAGE2_CELL, cell);
		}
	}
}

void ServantView::_setTableCell(cocos2d::extension::CCTableViewCell* cell,int idx, int tableType)
{
	CCMenu * menu = NULL;
	CMenuItemSprite * item = NULL;
	if(tableType == _TABLE_TYPE_ONE_)
	{
		if(m_iPageType == _PAGE_TYPE_MASTER_1_)
		{
			//设置奴隶主新闻
			unsigned int size = SERVANTDATAHANDLER->m_pSNewsInfo->newsVector.size();
			NFC_setLabelString(newsTTF, cell, SERVANTDATAHANDLER->m_pSNewsInfo->newsVector[size - 1 - idx], true);
		}
		else if(m_iPageType == _PAGE_TYPE_MASTER_2_)
		{
			SMSlaveFriend * fri = NULL;
			//设置待解救好友
			int index = idx * 2;
			if(index >= (int)SERVANTDATAHANDLER->m_pSMRescueInfo->slaveFriendVector.size())
			{
				for(int i = m2Cell0Bg; i <= m2Cell0RescueLabel; ++i)
				{
					NFC_showNode(i, cell, false);
				}
			}
			else
			{//设置当前好友状态
				fri = SERVANTDATAHANDLER->m_pSMRescueInfo->slaveFriendVector[index];
				NFC_showNode(m2Cell0Bg, cell, true);
				//Quality
				/*				NFC_setPicForCCSprite(m2Cell0Quality, cell, varConfig::getCardBGFilePath(fri->quality).c_str(), true);*/
				//icon
				NFC_setDTHeroIcon(m2Cell0Icon,cell,fri->iconId,true);
				//品质
				NFC_setDTHeroQualiy(m2Cell0Icon, cell, fri->quality);

				//NFC_setPicForCCSprite(m2Cell0Icon, cell, RESOURCEDAIDMANAGER->getDataByID(fri->iconId).c_str(), true);
				//NFC_setPicScale(m2Cell0Icon, cell, (float)(CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f));
				//name
				NFC_setLabelString(m2Cell0Name, cell, fri->name, true);
				//masterName
				NFC_setLabelString(m2Cell0MasterName, cell, fri->owerName, true);
				//masterBtl
				NFC_setLabelStringInt(m2Cell0MasterBtlValue, cell, fri->owerBtlCapa, true);

				//标定按钮
				menu = (CCMenu *)cell->getChildByTag(m2Cell0RescueBtn);
				menu->setVisible(true);
				item = (CMenuItemSprite *)menu->getChildByTag(0);
				item->setTarget(this, menu_selector(ServantView::On_MasterRescuePage_Btn_Click));
				item->setIDX(index);
			}

			++index;

			if(index >= (int)SERVANTDATAHANDLER->m_pSMRescueInfo->slaveFriendVector.size())
			{
				for(int i = m2Cell1Bg; i <= m2Cell1RescueLabel; ++i)
				{
					NFC_showNode(i, cell, false);
				}
			}
			else
			{//设置当前好友状态
				fri = SERVANTDATAHANDLER->m_pSMRescueInfo->slaveFriendVector[index];
				NFC_showNode(m2Cell1Bg, cell, true);
				//Quality
				/*				NFC_setPicForCCSprite(m2Cell1Quality, cell, varConfig::getCardBGFilePath(fri->quality).c_str(), true);*/
				//icon
				//NFC_setPicForCCSprite(m2Cell1Icon, cell, RESOURCEDAIDMANAGER->getDataByID(fri->iconId).c_str(), true);
				//NFC_setPicScale(m2Cell1Icon, cell, (float)(CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f));
				//头像
				NFC_setDTHeroIcon(m2Cell1Icon, cell, fri->iconId, true);
				//品质
				NFC_setDTHeroQualiy(m2Cell1Icon, cell, fri->quality);

				//name
				NFC_setLabelString(m2Cell1Name, cell, fri->name, true);
				//masterName
				NFC_setLabelString(m2Cell1MasterName, cell, fri->owerName, true);
				//masterBtl
				NFC_setLabelStringInt(m2Cell1MasterBtlValue, cell, fri->owerBtlCapa, true);

				//标定按钮
				menu = (CCMenu *)cell->getChildByTag(m2Cell1RescueBtn);
				menu->setVisible(true);
				item = (CMenuItemSprite *)menu->getChildByTag(0);
				item->setTarget(this, menu_selector(ServantView::On_MasterRescuePage_Btn_Click));
				item->setIDX(index);
			}
		}
		else if(m_iPageType == _PAGE_TYPE_SLAVE_1_)
		{
			//设置奴隶新闻
			unsigned int size = SERVANTDATAHANDLER->m_pSNewsInfo->newsVector.size();
			NFC_setLabelString(newsTTF, cell, SERVANTDATAHANDLER->m_pSNewsInfo->newsVector[size - 1 - idx], true);
		}
		else if(m_iPageType == _PAGE_TYPE_SLAVE_2_)
		{
			//设置可求助好友
			SSFreeFriend * fri = NULL;
			int index = idx * 2;
			if(index >= (int)SERVANTDATAHANDLER->m_pSSSOSInfo->freeFriendVector.size())
			{
				for(int i = s2Cell0Bg; i <= s2Cell0HelpLabel; ++i)
				{
					NFC_showNode(i, cell, false);
				}
			}
			else
			{//设置此行第一个
				fri = SERVANTDATAHANDLER->m_pSSSOSInfo->freeFriendVector[index];
				assert(fri != NULL);
				NFC_showNode(s2Cell0Bg, cell, true);
				/*				NFC_setPicForCCSprite(s2Cell0Quality, cell, varConfig::getCardBGFilePath(fri->quality).c_str(), true);*/
				//NFC_setPicForCCSprite(s2Cell0Icon, cell, RESOURCEDAIDMANAGER->getDataByID(fri->iconId).c_str(), true);
				//NFC_setPicScale(s2Cell0Icon, cell, (float)(CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f));
				//头像
				NFC_setDTHeroIcon(s2Cell0Icon, cell, fri->iconId, true);
				//品质
				NFC_setDTHeroQualiy(s2Cell0Icon, cell, fri->quality);

				NFC_setLabelString(s2Cell0Name, cell, fri->name, true);
				std::string str = SysLangDataManager::get_instance2()->GetSysLangById(612);
				char temp[32];
				sprintf(temp, str.c_str(), fri->level);
				NFC_setLabelString(s2Cell0Level, cell, temp, true);
				NFC_setLabelStringInt(s2Cell0BtlValue, cell, fri->btlCapa, true);

				//按钮
				menu = (CCMenu *)cell->getChildByTag(s2Cell0HelpBtn);
				item = (CMenuItemSprite *)menu->getChildByTag(0);
				menu->setVisible(true);
				item->setTarget(this, menu_selector(ServantView::On_SlaveSOSPage_Btn_Click));
				item->setIDX(index);
			}

			++index;

			if(index >= (int)SERVANTDATAHANDLER->m_pSSSOSInfo->freeFriendVector.size())
			{
				for(int i = s2Cell1Bg; i <= s2Cell1HelpLabel; ++i)
				{
					NFC_showNode(i, cell, false);
				}
			}
			else
			{
				fri = SERVANTDATAHANDLER->m_pSSSOSInfo->freeFriendVector[index];
				assert(fri != NULL);
				NFC_showNode(s2Cell1Bg, cell, true);
				/*				NFC_setPicForCCSprite(s2Cell1Quality, cell, varConfig::getCardBGFilePath(fri->quality).c_str(), true);*/
				//NFC_setPicForCCSprite(s2Cell1Icon, cell, RESOURCEDAIDMANAGER->getDataByID(fri->iconId).c_str(), true);
				//NFC_setPicScale(s2Cell1Icon, cell, (float)(CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f));
				//头像
				NFC_setDTHeroIcon(s2Cell1Icon, cell, fri->iconId, true);
				//品质
				NFC_setDTHeroQualiy(s2Cell1Icon, cell, fri->quality);

				NFC_setLabelString(s2Cell1Name, cell, fri->name, true);
				std::string str = SysLangDataManager::get_instance2()->GetSysLangById(612);
				char temp[32];
				sprintf(temp, str.c_str(), fri->level);
				NFC_setLabelString(s2Cell1Level, cell, temp, true);
				NFC_setLabelStringInt(s2Cell1BtlValue, cell, fri->btlCapa, true);

				//按钮
				menu = (CCMenu *)cell->getChildByTag(s2Cell1HelpBtn);
				item = (CMenuItemSprite *)menu->getChildByTag(0);
				menu->setVisible(true);
				item->setTarget(this, menu_selector(ServantView::On_SlaveSOSPage_Btn_Click));
				item->setIDX(index);
			}
		}
	}
	else if(tableType == _TABLE_TYPE_LEFT_)
	{
		if(m_iPageType == _PAGE_TYPE_MASTER_0_)
		{
			SMFightedPlayer * player = SERVANTDATAHANDLER->m_pSMCatchInfo->losserVector[idx];
			//头像
			NFC_setDTHeroIcon(mc0Icon,cell,player->iconId,true);
			//品质
			NFC_setDTHeroQualiy(mc0Icon, cell, player->quality);

			//NFC_setPicForCCSprite(mc0Icon, cell, RESOURCEDAIDMANAGER->getDataByID(player->iconId).c_str());
			//NFC_setPicScale(mc0Icon, cell, (float)(CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f));
			//质量
			/*			NFC_setPicForCCSprite(mc0Quality, cell, varConfig::getCardBGFilePath(player->quality).c_str());*/
			//name
			NFC_setLabelString(mc0Name, cell, player->name);
			//level
			std::string str = SysLangDataManager::get_instance2()->GetSysLangById(612);
			char temp[32];
			sprintf(temp, str.c_str(), player->level);
			NFC_setLabelString(mc0Level, cell, temp);
			//身份值
			NFC_setLabelString(mc0IdtValue, cell, IDStringDataManager::get_instance2()->GetIDStringByID(5, player->identity));
			//		
			//标定按钮
			menu = (CCMenu *)cell->getChildByTag(mc0CatchBtn);
			item = (CMenuItemSprite *)menu->getChildByTag(0);
			item->setTarget(this, menu_selector(ServantView::On_MasterCatchPage_Btn_Click));
			//item->setTag(0);
			item->setIDX(idx * 2 + 1);//奇数为左侧
			if(player->catchCdLeftTime > 0)
			{
				sprintf(temp, "%02d:%02d", player->catchCdLeftTime / 60, player->catchCdLeftTime % 60);
				NFC_setLabelString(mc0CatchBtnLabel, cell, temp, true);
				item->setEnabled(false);
			}
			else
			{
				NFC_setLabelString(mc0CatchBtnLabel, cell, SysLangDataManager::get_instance2()->GetSysLangById(947), true);
				item->setEnabled(true);
			}
		}
	}
	else if(tableType == _TABLE_TYPE_RIGHT_)
	{
		if(m_iPageType == _PAGE_TYPE_MASTER_0_)
		{
			SMFightedPlayer * player = SERVANTDATAHANDLER->m_pSMCatchInfo->winnerVector[idx];
			//头像
			NFC_setDTHeroIcon(mc0Icon,cell,player->iconId,true);
			//品质
			NFC_setDTHeroQualiy(mc0Icon, cell, player->quality);

			//NFC_setPicForCCSprite(mc0Icon, cell, RESOURCEDAIDMANAGER->getDataByID(player->iconId).c_str());
			//NFC_setPicScale(mc0Icon, cell, (float)(CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f));
			//质量
			/*			NFC_setPicForCCSprite(mc0Quality, cell, varConfig::getCardBGFilePath(player->quality).c_str());*/
			//name
			NFC_setLabelString(mc0Name, cell, player->name);
			//level
			std::string str = SysLangDataManager::get_instance2()->GetSysLangById(612);
			char temp[32];
			sprintf(temp, str.c_str(), player->level);
			NFC_setLabelString(mc0Level, cell, temp);
			//身份值
			NFC_setLabelString(mc0IdtValue, cell, IDStringDataManager::get_instance2()->GetIDStringByID(5, player->identity));
			//
			//标定按钮
			menu = (CCMenu *)cell->getChildByTag(mc0CatchBtn);
			item = (CMenuItemSprite *)menu->getChildByTag(0);
			item->setTarget(this, menu_selector(ServantView::On_MasterCatchPage_Btn_Click));
			//item->setTag(1);
			item->setIDX(idx * 2);//偶数为右侧
			if(player->catchCdLeftTime > 0)
			{
				sprintf(temp, "%02d:%02d", player->catchCdLeftTime / 60, player->catchCdLeftTime % 60);
				NFC_setLabelString(mc0CatchBtnLabel, cell, temp, true);
				item->setEnabled(false);
			}
			else
			{
				NFC_setLabelString(mc0CatchBtnLabel, cell, SysLangDataManager::get_instance2()->GetSysLangById(947), true);
				item->setEnabled(true);
			}
		}

	}

}

unsigned int ServantView::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
	if(m_iPageType == _PAGE_TYPE_MASTER_0_)
	{
		if(table == m_pLeftTable)
		{
			if(SERVANTDATAHANDLER->m_pSMCatchInfo)
			{
				int sz = (int)SERVANTDATAHANDLER->m_pSMCatchInfo->losserVector.size();
				if(sz == 0)
					NFC_showNode(m0LeftNoTips, m_pViewRoot, true);
				else
					NFC_showNode(m0LeftNoTips, m_pViewRoot, false);

				return sz;
			}
			return 0;
		}
		else
		{
			if(SERVANTDATAHANDLER->m_pSMCatchInfo)
			{
				NFC_showNode(m0RightNoTips, m_pViewRoot, false);
				int sz = (int)SERVANTDATAHANDLER->m_pSMCatchInfo->winnerVector.size();
				if(sz == 0)
					NFC_showNode(m0RightNoTips, m_pViewRoot, true);
				else
					NFC_showNode(m0RightNoTips, m_pViewRoot, false);
				return sz;
			}
			return 0;
		}
	}
	else if(m_iPageType == _PAGE_TYPE_MASTER_1_)
	{
		if(SERVANTDATAHANDLER->m_pSNewsInfo)
			return SERVANTDATAHANDLER->m_pSNewsInfo->newsVector.size();
		return 0;
	}
	else if(m_iPageType == _PAGE_TYPE_MASTER_2_)
	{
		if(SERVANTDATAHANDLER->m_pSMRescueInfo)
		{
			int sz = (int)(SERVANTDATAHANDLER->m_pSMRescueInfo->slaveFriendVector.size() + 1) / 2;
			if(sz == 0)
			{
				NFC_showNode(m2VLine, m_pViewRoot, false);
				NFC_showNode(m2NoTips, m_pViewRoot, true);
			}
			else
			{
				NFC_showNode(m2VLine, m_pViewRoot, true);
				NFC_showNode(m2NoTips, m_pViewRoot, false);
			}
			return sz;
		}
		else
		{
			return 0;
		}
	}
	else if(m_iPageType == _PAGE_TYPE_SLAVE_1_)
	{
		if(SERVANTDATAHANDLER->m_pSNewsInfo)
			return SERVANTDATAHANDLER->m_pSNewsInfo->newsVector.size();
		return 0;
	}
	else if(m_iPageType == _PAGE_TYPE_SLAVE_2_)
	{
		if(SERVANTDATAHANDLER->m_pSSSOSInfo)
		{
			int sz = (int)(SERVANTDATAHANDLER->m_pSSSOSInfo->freeFriendVector.size() + 1) / 2;
			if(sz == 0)
			{
				NFC_showNode(s2vline, m_pViewRoot, false);
				NFC_showNode(s2NoTips, m_pViewRoot, true);
			}
			else
			{
				NFC_showNode(s2vline, m_pViewRoot, true);
				NFC_showNode(s2NoTips, m_pViewRoot, false);
			}
			return sz;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

void ServantView::_showMasterCatchPage(cocos2d::CCNode * parent)
{
	if(!parent)
		return;

	parent->removeAllChildrenWithCleanup(true);
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSERVANTMASTERPAGE0, parent);

	//tableview0
	m_pLeftTable = (CCTableView *)parent->getChildByTag(m0TableView0);
	CCNode* node=(CCNode*)parent->getChildByTag(m0Cell0);
	m_szCELLLeft=node->getContentSize();
	m_pLeftTable->setDataSource(this);
	m_pLeftTable->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pLeftTable->setTouchEnabled(true);
	m_pLeftTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
	NFC_refreshTableView(m_pLeftTable);

	//tableview1
	m_pRightTable = (CCTableView *)parent->getChildByTag(m0TableView1);
	node=(CCNode*)parent->getChildByTag(m0Cell1);
	m_szCELLRight=node->getContentSize();
	m_pRightTable->setDataSource(this);
	m_pRightTable->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pRightTable->setTouchEnabled(true);
	m_pRightTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
	NFC_refreshTableView(m_pRightTable);

}

void ServantView::_setMasterCatchPage()
{
	//更新主页面右上角显示文字
	NFC_setLabelString(mLeftTimesTTF, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(628));
	int times = 0;
	if(SERVANTDATAHANDLER->m_pSMCatchInfo)
		times = SERVANTDATAHANDLER->m_pSMCatchInfo->leftCatchTimes;
	NFC_setLabelString(mLeftTimesValue, m_pRoot, _to_event_param_(times));
}

void ServantView::_showMasterPlayPage(cocos2d::CCNode * parent)
{
	if(!parent)
		return;
	parent->removeAllChildrenWithCleanup(true);
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSERVANTMASTERPAGE1, parent);

	CCMenu * menu = NULL;
	CMenuItemSprite * item = NULL;

	for(int i = m1Slave0ChainBtn; i <= m1Slave2ChainBtn; i += 15)
	{
		menu = (CCMenu *)parent->getChildByTag(i);//调教
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTarget(this, menu_selector(ServantView::On_MasterPlayPage_Btn_Click));
		item->setTag(i);

		menu = (CCMenu *)parent->getChildByTag(i + 2);//压榨
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTarget(this, menu_selector(ServantView::On_MasterPlayPage_Btn_Click));
		item->setTag(i + 2);

		menu = (CCMenu *)parent->getChildByTag(i + 4);//释放
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTarget(this, menu_selector(ServantView::On_MasterPlayPage_Btn_Click));
		item->setTag(i + 4);

		menu = (CCMenu *)parent->getChildByTag(i + 6);//抓捕
		item = (CMenuItemSprite *)menu->getChildByTag(0);
		item->setTarget(this, menu_selector(ServantView::On_MasterPlayPage_Btn_Click));
		item->setTag(i + 6);
	}

	//tableview
	m_pTable = (CCTableView *)parent->getChildByTag(m1Table);
	CCNode* node=(CCNode*)parent->getChildByTag(m1Cell);
	m_szCELL=node->getContentSize();
	m_pTable->setDataSource(this);
	m_pTable->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pTable->setTouchEnabled(true);
	m_pTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
	NFC_refreshTableView(m_pTable);

	for(int j = m1Slave0Bg; j <= m1Slave2CatchBtn; ++j)
	{
		NFC_showNode(j, m_pViewRoot, false);
	}
}

void ServantView::_setMasterPlayPage()
{
	assert(SERVANTDATAHANDLER->m_pSMPlayInfo != NULL);

	//更新主页面右上角显示文字
	NFC_setLabelString(mLeftTimesTTF, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(629));
	int times = SERVANTDATAHANDLER->m_pSMPlayInfo->leftPlayTimes;
	NFC_setLabelString(mLeftTimesValue, m_pRoot, _to_event_param_(times));

	//设置显示的奴隶
	SMSlave * slave = NULL;
	for(int i = 0; i < USER_MAX_SLAVE; ++i)
	{
		slave = SERVANTDATAHANDLER->m_pSMPlayInfo->slaveVector[i];
		if(slave != NULL)
		{
			char temp[32] = "";
			//背景
			NFC_showNode(m1Slave0Bg + i * 15, m_pViewRoot, true);
			//质量图
			/*			NFC_setPicForCCSprite(m1Slave0Quality + i * 15, m_pViewRoot, varConfig::getCardBGFilePath(slave->quality).c_str(), true);*/
			//icon
			NFC_setDTHeroIcon(m1Slave0Icon + i * 15,m_pViewRoot,slave->iconId,true);
			//品质
			NFC_setDTHeroQualiy(m1Slave0Icon + i * 15, m_pViewRoot, slave->quality);

			//NFC_setPicForCCSprite(m1Slave0Icon + i * 15, m_pViewRoot, RESOURCEDAIDMANAGER->getDataByID(slave->iconId).c_str(), true);
			//NFC_setPicScale(m2Cell0Icon + i * 15, m_pViewRoot, (float)(CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f));
			//Name,
			NFC_setLabelString(m1Slave0Name + i * 15, m_pViewRoot, slave->name, true);
			//level
			sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(612).c_str(), slave->level);
			NFC_setLabelString(m1Slave0Level + i * 15, m_pViewRoot, temp, true);
			//worktime
			NFC_showNode(m1Slave0WorkTime + i * 15, m_pViewRoot, true);
			sprintf(temp, "%02d:%02d:%02d", slave->workSeconds / 3600, (slave->workSeconds % 3600) / 60, (slave->workSeconds % 3600) % 60);
			NFC_setLabelString(m1Slave0WorkTimesValue + i * 15, m_pViewRoot, temp, true);
			//产生经验
			NFC_showNode(m1Slave0Exp + i * 15, m_pViewRoot, true);
			NFC_setLabelStringInt(m1Slave0ExpValue + i * 15, m_pViewRoot, slave->makeExp, true);
			//调戏
			NFC_showNode(m1Slave0ChainBtn + i * 15, m_pViewRoot, true);
			NFC_showNode(m1Slave0ChainLabel + i * 15, m_pViewRoot, true);

			CCMenu * menu = (CCMenu *)m_pViewRoot->getChildByTag(m1Slave0ChainBtn + i * 15);
			CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(m1Slave0ChainBtn + i * 15);
			if(SERVANTDATAHANDLER->m_pSMPlayInfo->leftPlayTimes > 0)
			{
				if(slave->chainCdLeftTime > 0)
				{
					char temp[32] = {0};
					sprintf(temp, "%02d:%02d", slave->chainCdLeftTime / 60, slave->chainCdLeftTime % 60);
					NFC_setLabelString(m1Slave0ChainLabel + i * 15, m_pViewRoot, temp, true);
					item->setEnabled(false);

				}
				else if(slave->chainCdLeftTime == 0 || slave->chainCdLeftTime == -1)
				{
					NFC_setLabelString(m1Slave0ChainLabel + i * 15, m_pViewRoot, SysLangDataManager::get_instance2()->GetSysLangById(948), true);
					item->setEnabled(true);
				}

			}
			else
			{//灰色调教
				NFC_setLabelString(m1Slave0ChainLabel + i * 15, m_pViewRoot, SysLangDataManager::get_instance2()->GetSysLangById(948), true);
				item->setEnabled(false);
			}

			//释放
			NFC_showNode(m1Slave0ReleaseBtn + i * 15, m_pViewRoot, true);
			NFC_showNode(m1Slave0ReleaseLabel + i * 15, m_pViewRoot, true);
			//压榨
			bool visible = ROLEINFODATAHANDLER->m_pRIData->vipLevel_ >= CLIENTCONSTDATAMANGER->getValueByKey(VIP_NULI_PRESS_LEVEL) ? true : false;
			NFC_showNode(m1Slave0PressBtn + i * 15, m_pViewRoot, visible);
			NFC_showNode(m1Slave0PressLabel + i * 15, m_pViewRoot, visible);

			//调教按钮
			CCMenu * tmenu = (CCMenu *)m_pViewRoot->getChildByTag(m1Slave0ChainBtn + i * 15);
			CMenuItemSprite * titem = (CMenuItemSprite *)tmenu->getChildByTag(m1Slave0ChainBtn + i * 15);
			

			//抓捕按钮取消
			NFC_showNode(m1Slave0CatchBtn + i * 15, m_pViewRoot, false);
		}
		else
		{
			for(int j = m1Slave0Bg + i * 15; j < m1Slave0CatchBtn + i * 15; ++j)
			{
				NFC_showNode(j, m_pViewRoot, false);
			}
			NFC_showNode(m1Slave0CatchBtn + i * 15, m_pViewRoot, true);
		}
	}

}

void ServantView::_showMasterRescuePage(cocos2d::CCNode * parent)
{
	if(!parent)
		return;
	parent->removeAllChildrenWithCleanup(true);
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSERVANTMASTERPAGE2, parent);

	//tableview
	m_pTable = (CCTableView *)parent->getChildByTag(m2Table);
	CCNode* node=(CCNode*)parent->getChildByTag(m2Cell);
	m_szCELL=node->getContentSize();
	m_pTable->setDataSource(this);
	m_pTable->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pTable->setTouchEnabled(true);
	m_pTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
	NFC_refreshTableView(m_pTable);

}

void ServantView::_setMasterRescuePage()
{
	//更新主页面右上角显示文字
	NFC_setLabelString(mLeftTimesTTF, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(630));
	int times = 0;
	if(SERVANTDATAHANDLER->m_pSMRescueInfo)
		times = SERVANTDATAHANDLER->m_pSMRescueInfo->leftRescueTimes;
	NFC_setLabelString(mLeftTimesValue, m_pRoot, _to_event_param_(times));
}

void ServantView::_showSlaveRevoltPage(cocos2d::CCNode * parent)
{//kSERVANTSLAVEPAGE0
	if(!parent)
		return;
	parent->removeAllChildrenWithCleanup(true);
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSERVANTSLAVEPAGE0, parent);

	CCMenu * menu = (CCMenu *)m_pViewRoot->getChildByTag(s0RevoltBtn);
	CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTarget(this, menu_selector(ServantView::On_SlaveRevoltPage_Btn_Click));
	item->setTag(s0RevoltBtn);
	menu = (CCMenu *)m_pViewRoot->getChildByTag(s0BribeBtn);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTarget(this, menu_selector(ServantView::On_SlaveRevoltPage_Btn_Click));
	item->setTag(s0BribeBtn);

	menu = (CCMenu *)m_pViewRoot->getChildByTag(s0BegHelp);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTarget(this, menu_selector(ServantView::On_SlaveRevoltPage_Btn_Click));
	item->setTag(s0BegHelp);

}

void ServantView::_setSlaveRevoltPage()
{
	assert(SERVANTDATAHANDLER->m_pSSRevoltInfo != NULL);
	//更新主页面右上角显示文字
	NFC_setLabelString(mLeftTimesTTF, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(631));
	int times = SERVANTDATAHANDLER->m_pSSRevoltInfo->leftRevoltTimes;
	NFC_setLabelString(mLeftTimesValue, m_pRoot, _to_event_param_(times));

	SSRevoltInfo * info = SERVANTDATAHANDLER->m_pSSRevoltInfo;

	//主人
	/*	NFC_setPicForCCSprite(s0OwnerQuality, m_pViewRoot, varConfig::getCardBGFilePath(info->owerQuality).c_str(), true);*/
	//NFC_setPicForCCSprite(s0OwnerIcon, m_pViewRoot, RESOURCEDAIDMANAGER->getDataByID(info->owerIconId).c_str(), true);
	//NFC_setPicScale(s0OwnerIcon, m_pViewRoot, (float)(CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f));
	//头像
	NFC_setDTHeroIcon(s0OwnerIcon, m_pViewRoot, info->owerIconId, true);
	//品质
	NFC_setDTHeroQualiy(s0OwnerIcon, m_pViewRoot, info->owerQuality);

	NFC_setLabelString(s0OwnerName, m_pViewRoot, info->owerName, true);
	char temp[32] = {0};
	sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(612).c_str(), info->owerLevel, true);
	NFC_setLabelString(s0OwnerLevel, m_pViewRoot, temp, true);
	NFC_setLabelStringInt(s0OwnerBtlValue, m_pViewRoot, info->owerBtlCapa, true);
	//NCP
	/*	NFC_setPicForCCSprite(s0NpcQuality, m_pViewRoot, varConfig::getCardBGFilePath(info->npcQuality).c_str(), true);*/
	//NFC_setPicForCCSprite(s0NpcIcon, m_pViewRoot, RESOURCEDAIDMANAGER->getDataByID(info->npcIconId).c_str(), true);
	//NFC_setPicScale(s0NpcIcon, m_pViewRoot, (float)(CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f));
	//头像
	NFC_setDTHeroIcon(s0NpcIcon, m_pViewRoot, info->npcIconId, true);
	//品质
	NFC_setDTHeroQualiy(s0NpcIcon, m_pViewRoot, info->owerQuality);

	NFC_setLabelString(s0NpcName, m_pViewRoot, info->npcName, true);
	NFC_setLabelStringInt(s0NpcPriceValue, m_pViewRoot, info->npcPrice);
}

void ServantView::_showSlavePlayPage(cocos2d::CCNode * parent)
{//kSERVANTSLAVEPAGE1
	if(!parent)
		return;
	parent->removeAllChildrenWithCleanup(true);
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSERVANTSLAVEPAGE1, parent);

	CCMenu * menu = (CCMenu *)m_pViewRoot->getChildByTag(s1PlayBtn);
	CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(s1PlayBtn);
	item->setTarget(this, menu_selector(ServantView::On_SlavePlayPage_Btn_Click));

	//tableview
	m_pTable = (CCTableView *)parent->getChildByTag(s1Table);
	CCNode* node=(CCNode*)parent->getChildByTag(s1Cell);
	m_szCELL=node->getContentSize();
	m_pTable->setDataSource(this);
	m_pTable->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pTable->setTouchEnabled(true);
	m_pTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
	NFC_refreshTableView(m_pTable);

}

void ServantView::_setSlavePlayPage()
{
	assert(SERVANTDATAHANDLER->m_pSSPlayInfo != NULL);
	//更新主页面右上角显示文字
	NFC_setLabelString(mLeftTimesTTF, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(629));
	int times = SERVANTDATAHANDLER->m_pSSPlayInfo->leftPlayTimes;
	NFC_setLabelString(mLeftTimesValue, m_pRoot, _to_event_param_(times));

	SSPlayInfo * play = SERVANTDATAHANDLER->m_pSSPlayInfo;
	//设置主人
	/*	NFC_setPicForCCSprite(s1Owner, m_pViewRoot, varConfig::getCardBGFilePath(play->owerQuality).c_str(), true);*/
	//NFC_setPicForCCSprite(s1OwnerIcon, m_pViewRoot, RESOURCEDAIDMANAGER->getDataByID(play->owerIconId).c_str(), true);
	//NFC_setPicScale(s1OwnerIcon, m_pViewRoot, (float)(CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f));
	//头像
	NFC_setDTHeroIcon(s1OwnerIcon, m_pViewRoot, play->owerIconId, true);
	//品质
	NFC_setDTHeroQualiy(s1OwnerIcon, m_pViewRoot, play->owerQuality);

	NFC_setLabelString(s1OwnerName, m_pViewRoot, play->owerName, true);
	char temp[32] = {0};
	sprintf(temp, SysLangDataManager::get_instance2()->GetSysLangById(612).c_str(), play->owerLevel, true);
	NFC_setLabelString(s1OwnerLevel, m_pViewRoot, temp, true);

	//互动按钮
	CCMenu * hmenu = (CCMenu *)m_pViewRoot->getChildByTag(s1PlayBtn);
	CMenuItemSprite * hitem = (CMenuItemSprite *)hmenu->getChildByTag(s1PlayBtn);
	if(SERVANTDATAHANDLER->m_pSSPlayInfo->leftPlayTimes > 0)
	{
		hitem->setEnabled(true);
	}
	else
	{
		hitem->setEnabled(false);
	}

}

void ServantView::_showSlaveSOSPage(cocos2d::CCNode * parent)
{
	if(!parent)
		return;
	parent->removeAllChildrenWithCleanup(true);
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSERVANTSLAVEPAGE2, parent);

	//tableview
	m_pTable = (CCTableView *)parent->getChildByTag(s2Table);
	CCNode* node=(CCNode*)parent->getChildByTag(s2Cell);
	m_szCELL=node->getContentSize();
	m_pTable->setDataSource(this);
	m_pTable->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pTable->setTouchEnabled(true);
	m_pTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
	NFC_refreshTableView(m_pTable);
}

void ServantView::_setSlaveSOSPage()
{
	assert(SERVANTDATAHANDLER->m_pSSSOSInfo != NULL);
	//更新主页面右上角显示文字
	NFC_setLabelString(mLeftTimesTTF, m_pRoot, SysLangDataManager::get_instance2()->GetSysLangById(632));
	int times = SERVANTDATAHANDLER->m_pSSSOSInfo->leftSOSTime;
	NFC_setLabelString(mLeftTimesValue, m_pRoot, _to_event_param_(times));

}

void ServantView::_requestShowPageData()
{
	if(m_iPageType == _PAGE_TYPE_MASTER_0_)
		SERVANTDATAHANDLER->ToServerMasterEnterCatch();
	else if(m_iPageType == _PAGE_TYPE_MASTER_1_)
		SERVANTDATAHANDLER->ToServerMasterEnterPlay();
	else if(m_iPageType == _PAGE_TYPE_MASTER_2_)
		SERVANTDATAHANDLER->ToServerMasterEnterRescue();
	else if(m_iPageType == _PAGE_TYPE_SLAVE_0_)
		SERVANTDATAHANDLER->ToServerSlaveEnterRevolt();
	else if(m_iPageType == _PAGE_TYPE_SLAVE_1_)
		SERVANTDATAHANDLER->ToServerSlaveEnterPlay();
	else if(m_iPageType == _PAGE_TYPE_SLAVE_2_)
		SERVANTDATAHANDLER->ToServerSlaveEnterSOS();
}

void ServantView::On_MainPage_Btn_Click(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int tag = item->getTag();
	int idt = ROLEINFODATAHANDLER->m_pRIData->slaveIdentity_;

	bool reselect = false;//是否是已在这个页面重复选择
	if(tag == mPage0Btn)
	{
		if(idt == SERVANT_ID_SLAVE)
		{
			if(m_iPageType == _PAGE_TYPE_SLAVE_0_)
			{
				reselect = true;
			}
			m_iPageType = _PAGE_TYPE_SLAVE_0_;
		}
		else
		{
			if(m_iPageType == _PAGE_TYPE_MASTER_0_)
			{
				reselect = true;
			}
			m_iPageType = _PAGE_TYPE_MASTER_0_;
		}
	}
	else if(tag == mPage1Btn)
	{
		if(idt == SERVANT_ID_SLAVE)
		{
			if(m_iPageType == _PAGE_TYPE_SLAVE_1_)
			{
				reselect = true;
			}
			m_iPageType = _PAGE_TYPE_SLAVE_1_;
		}
		else
		{
			if(m_iPageType == _PAGE_TYPE_MASTER_1_)
			{
				reselect = true;
			}
			m_iPageType = _PAGE_TYPE_MASTER_1_;
		}
	}
	else if(tag == mPage2Btn)
	{
		if(idt == SERVANT_ID_SLAVE)
		{
			if(m_iPageType == _PAGE_TYPE_SLAVE_2_)
			{
				reselect = true;
			}
			m_iPageType = _PAGE_TYPE_SLAVE_2_;
		}
		else
		{
			if(m_iPageType == _PAGE_TYPE_MASTER_2_)
			{
				reselect = true;
			}
			m_iPageType = _PAGE_TYPE_MASTER_2_;
		}
	}

	//请求对应页面需要的信息，显示页面，切换选中标签
	if(reselect == false)
	{
		SERVANTDATAHANDLER->m_iLastStayPage = m_iPageType;
		_requestShowPageData();
		_showViewPage();
		_setSelectPageTab();
	}

}

void ServantView::On_MasterCatchPage_Btn_Click(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int idx = item->getIDX();
	if(idx % 2 == 1)//奇数为左侧手下败将
	{
		//左侧列表,从自己的输家中获得
		SMFightedPlayer * player = SERVANTDATAHANDLER->m_pSMCatchInfo->losserVector[(idx - 1) / 2];
		if(SERVANTDATAHANDLER->m_pSMCatchInfo->leftCatchTimes > 0)
		{
			SERVANTDATAHANDLER->ToServerMasterCatch(player->playerId);
		}
		else
		{
			NFC_showErrorTips_2(SysLangDataManager::get_instance2()->GetSysLangById(_MESSAGE_CATCH_FUNCTION_DOWN_));
		}
	}
	else//偶数为右侧赢家
	{
		//右侧列表，从自己的赢家中获得
		SMFightedPlayer * player = SERVANTDATAHANDLER->m_pSMCatchInfo->winnerVector[idx / 2];
		if(SERVANTDATAHANDLER->m_pSMCatchInfo->leftCatchTimes > 0)
		{
			SERVANTDATAHANDLER->ToServerMasterCatch(player->playerId);
		}
		else
		{
			NFC_showErrorTips_2(SysLangDataManager::get_instance2()->GetSysLangById(_MESSAGE_CATCH_FUNCTION_DOWN_));
		}
	}
}

void ServantView::On_MasterPlayPage_Btn_Click(cocos2d::CCObject * pSender)
{
	LOGGERSYSTEM->LogInfo("ServantView::On_MasterPlayPage_Btn_Click --- begin\n");
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int tag = item->getTag();
	if(tag == m1Slave0ChainBtn || tag == m1Slave1ChainBtn || tag == m1Slave2ChainBtn)
	{//调戏
		if(SERVANTDATAHANDLER->m_pSMPlayInfo->leftPlayTimes > 0)
		{
			if(tag == m1Slave0ChainBtn)
			{
				SERVANTDATAHANDLER->ToServerMasterPlay((char)ServantDataHandler::_PLAY_FUNC_CHAIN_, 0);
			}
			else if(tag == m1Slave1ChainBtn)
			{
				SERVANTDATAHANDLER->ToServerMasterPlay((char)ServantDataHandler::_PLAY_FUNC_CHAIN_, 1);
			}
			else if(tag == m1Slave2ChainBtn)
			{
				SERVANTDATAHANDLER->ToServerMasterPlay((char)ServantDataHandler::_PLAY_FUNC_CHAIN_, 2);
			}
		}
		else
		{
			NFC_showErrorTips_2(SysLangDataManager::get_instance2()->GetSysLangById(_MESSAGE_PLAY_FUNCTION_DOWN_));
		}
	}
	else if(tag == m1Slave0PressBtn || tag == m1Slave1PressBtn || tag == m1Slave2PressBtn)
	{//压榨
		if(tag == m1Slave0PressBtn)
		{
			SERVANTDATAHANDLER->ToServerMasterPlay((char)ServantDataHandler::_PLAY_FUNC_PRESS_, 0);
		}
		else if(tag == m1Slave1PressBtn)
		{
			SERVANTDATAHANDLER->ToServerMasterPlay((char)ServantDataHandler::_PLAY_FUNC_PRESS_, 1);
		}
		else if(tag == m1Slave2PressBtn)
		{
			SERVANTDATAHANDLER->ToServerMasterPlay((char)ServantDataHandler::_PLAY_FUNC_PRESS_, 2);
		}
	}
	else if(tag == m1Slave0ReleaseBtn || tag == m1Slave1ReleaseBtn || tag == m1Slave2ReleaseBtn)
	{//释放
		if(tag == m1Slave0ReleaseBtn)
		{
			SERVANTDATAHANDLER->ToServerMasterPlay((char)ServantDataHandler::_PLAY_FUNC_RELEASE_, 0);
		}
		else if(tag == m1Slave1ReleaseBtn)
		{
			SERVANTDATAHANDLER->ToServerMasterPlay((char)ServantDataHandler::_PLAY_FUNC_RELEASE_, 1);
		}
		else if(tag == m1Slave2ReleaseBtn)
		{
			SERVANTDATAHANDLER->ToServerMasterPlay((char)ServantDataHandler::_PLAY_FUNC_RELEASE_, 2);
		}
	}
	else if(tag == m1Slave0CatchBtn || tag == m1Slave1CatchBtn || tag == m1Slave2CatchBtn)
	{//抓捕
		m_iPageType = _PAGE_TYPE_MASTER_0_;

		_requestShowPageData();

		//选中选中的分页标签
		_setSelectPageTab();

		//显示分页
		_showViewPage();
	}

	LOGGERSYSTEM->LogInfo("ServantView::On_MasterPlayPage_Btn_Click --- end\n");
}

void ServantView::On_MasterRescuePage_Btn_Click(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int idx = item->getIDX();
	if(idx < (int)SERVANTDATAHANDLER->m_pSMRescueInfo->slaveFriendVector.size())
	{
		SMSlaveFriend * fri = SERVANTDATAHANDLER->m_pSMRescueInfo->slaveFriendVector[idx];
		if(SERVANTDATAHANDLER->m_pSMRescueInfo->leftRescueTimes > 0)
		{
			SERVANTDATAHANDLER->ToServerMasterRescue(fri->playerId);
		}
		else
		{
			NFC_showErrorTips_2(SysLangDataManager::get_instance2()->GetSysLangById(_MESSAGE_RESCUE_FUNCTION_DOWN_));
		}
	}
}

void ServantView::On_SlaveRevoltPage_Btn_Click(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int tag = item->getTag();
	if(tag == s0RevoltBtn)
	{
		if(SERVANTDATAHANDLER->m_pSSRevoltInfo->leftRevoltTimes > 0)
		{
			SERVANTDATAHANDLER->ToServerSlaveRevolt();
		}
		else
		{
			NFC_showErrorTips_2(SysLangDataManager::get_instance2()->GetSysLangById(_MESSAGE_REVOLT_FUNCTION_DOWN_));
		}
	}
	else if(tag == s0BribeBtn)
	{
		if(SERVANTDATAHANDLER->m_pSSRevoltInfo->leftRevoltTimes > 0)
		{
			SERVANTDATAHANDLER->ToServerSlaveBribe();
		}
		else
		{
			NFC_showErrorTips_2(SysLangDataManager::get_instance2()->GetSysLangById(_MESSAGE_REVOLT_FUNCTION_DOWN_));
		}
	}
	else if(tag == s0BegHelp)
	{
		//转到求助界面
		m_iPageType = _PAGE_TYPE_SLAVE_2_;

		_requestShowPageData();

		//选中选中的分页标签
		_setSelectPageTab();

		//显示分页
		_showViewPage();
	}
}

void ServantView::On_SlavePlayPage_Btn_Click(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int tag = item->getTag();
	if(tag == s1PlayBtn)
	{
		if(SERVANTDATAHANDLER->m_pSSPlayInfo->leftPlayTimes > 0)
		{
			SERVANTDATAHANDLER->ToServerSlavePlay();
		}
		else
		{
			NFC_showErrorTips_2(SysLangDataManager::get_instance2()->GetSysLangById(_MESSAGE_PLAY_FUNCTION_DOWN_));
		}
	}
}

void ServantView::On_SlaveSOSPage_Btn_Click(cocos2d::CCObject * pSender)
{
	CMenuItemSprite * item = (CMenuItemSprite *)pSender;
	int index = item->getIDX();

	if(index < (int)SERVANTDATAHANDLER->m_pSSSOSInfo->freeFriendVector.size())
	{
		SSFreeFriend * fri = SERVANTDATAHANDLER->m_pSSSOSInfo->freeFriendVector[index];
		if(!fri)
			return;
		if(SERVANTDATAHANDLER->m_pSSSOSInfo->leftSOSTime > 0)
		{
			SERVANTDATAHANDLER->ToServerSlaveSos(fri->playerId);
		}
		else
		{
			NFC_showErrorTips_2(SysLangDataManager::get_instance2()->GetSysLangById(_MESSAGE_SOS_FUNCTION_DOWN_));
		}
	}
}

void ServantView::Function_GetMasterEnterCatchData()
{
	if(m_iPageType == _PAGE_TYPE_MASTER_0_)
	{
		NFC_refreshTableView(m_pLeftTable);
		NFC_refreshTableView(m_pRightTable);
		_setMasterCatchPage();
	}
}

void ServantView::Function_GetMasterEnterPlayData()
{
	if(m_iPageType == _PAGE_TYPE_MASTER_1_)
	{
		_setMasterPlayPage();
	}
}

void ServantView::Function_GetMasterPlaySuccess()
{
	if(m_iPageType == _PAGE_TYPE_MASTER_1_)
	{
		_setMasterPlayPage();
	}
}

void ServantView::Function_GetMasterNews()
{

	if(m_iPageType == _PAGE_TYPE_MASTER_1_)
	{
		NFC_refreshTableView(m_pTable);
	}
}

void ServantView::Function_GetMasterEnterResceuData()
{
	if(m_iPageType == _PAGE_TYPE_MASTER_2_)
	{
		_setMasterRescuePage();
		NFC_refreshTableView(m_pTable);
	}
}

void ServantView::Function_GetSlaveEnterRevoltData()
{
	if(m_iPageType == _PAGE_TYPE_SLAVE_0_)
	{
		_setSlaveRevoltPage();
	}
}

void ServantView::Function_GetSlaveBribeSuccess()
{

}

void ServantView::Function_GetSlaveEnterPlayData()
{
	if(m_iPageType == _PAGE_TYPE_SLAVE_1_)
	{
		_setSlavePlayPage();
	}

}

void ServantView::Function_GetSlavePlaySuccess()
{
	if(m_iPageType == _PAGE_TYPE_SLAVE_1_)
	{
		_setSlavePlayPage();
	}
}

void ServantView::Function_GetSlaveNews()
{
	if(m_iPageType == _PAGE_TYPE_SLAVE_1_)
	{
		NFC_refreshTableView(m_pTable);
	}
}

void ServantView::Function_GetSlaveEnterSOSData()
{
	if(m_iPageType == _PAGE_TYPE_SLAVE_2_)
	{
		_setSlaveSOSPage();
		NFC_refreshTableView(m_pTable);
	}
}

void ServantView::Function_ConfirmIdentityChanged()
{
	if(ROLEINFODATAHANDLER->m_pRIData->slaveIdentity_ == SERVANT_ID_SLAVE)
	{
		m_iPageType = _PAGE_TYPE_SLAVE_0_;
	}
	else
	{
		m_iPageType = _PAGE_TYPE_MASTER_0_;
	}

	//请求对应界面的信息
	_requestShowPageData();

	//选中选中的分页标签
	_setSelectPageTab();

	//显示分页
	_showViewPage();
}

void ServantView::Function_IdentityChanged(std::list<std::string> & paramList)
{
	//如果即将进入战斗界面，那么不弹出身份转换提示
	if(SERVANTDATAHANDLER->m_iWillEnterAthletic)
		return;

	//如果保持在这个界面需要弹出身份转换提示
	if(paramList.size() == 2)
	{
		std::list<std::string>::iterator it = paramList.begin();
		int oldidt(0), newidt(0);
		oldidt = atoi((*it).c_str());
		it++;
		newidt = atoi((*it).c_str());
		if(oldidt == SERVANT_ID_MASTER)
		{
			if(newidt == SERVANT_ID_SLAVE)
			{
				NFC_showMessageBoxSingle(kSERVANTIDENTITYCHANGED, SysLangDataManager::get_instance2()->GetSysLangById(_MESSAGE_IDENTITY_CHANGED_TO_SLAVE_));
			}
		}
		else if(oldidt == SERVANT_ID_FREE)
		{
			if(newidt == SERVANT_ID_SLAVE)
			{
				NFC_showMessageBoxSingle(kSERVANTIDENTITYCHANGED, SysLangDataManager::get_instance2()->GetSysLangById(_MESSAGE_IDENTITY_CHANGED_TO_SLAVE_));
			}
		}
		else if(oldidt == SERVANT_ID_SLAVE)
		{
			if(newidt == SERVANT_ID_FREE)
			{
				NFC_showMessageBoxSingle(kSERVANTIDENTITYCHANGED, SysLangDataManager::get_instance2()->GetSysLangById(_MESSAGE_IDENTITI_CHANGED_TO_FREE_));
			}
		}
	}
}

void ServantView::Function_OnClose()
{
	SERVANTDATAHANDLER->m_iLastStayPage = -1;//如果是正常退出的话，就不存储上次的页面了
}