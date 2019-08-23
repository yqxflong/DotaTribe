//Name：SCAthleticsDataPacket
//Function：返回战斗数据
//Author:	Johny

#include  <cocos2d.h>
#include  "../include/SCAthleticsDataPacket.h"
#include  "../include/DOTATribeApp.h"
#include  "../include/LoggerSystem.h"
#include  "../include/IProcedure.h"
#include  "../include/PacketTyper.h"
#include  "../include/NetSystem.h"
#include  "../include/EventTyper.h"
#include  "../include/EventSystem.h"
#include  "../include/LoadingWindow.h"
#include  "../include/VariableSystem.h"
#include  "../include/LevelUpDataHandler.h"
#include   <include/mem/DPacket.h> 
#include  "../include/CSMapTable.h"
#include  "../include/AthleticProcedureDataHandler.h"
#include  "../include/RoleInfoDataHandler.h"
#include  "../include/CPublicVarReader.h" 
#include "../include/LocalAthleticsDataManager.h"


 
using  namespace  cobra_win; 

unsigned  int  SCAthleticsDataPacket::GetPacketType()
{
     return  _TYPED_PACKET_S2C_ATHLETICSDATA_;
}

unsigned  int  SCAthleticsDataPacket::GetPacketLength()
{
     return  sizeof(SCAthleticsDataPacket);
}


bool  SCAthleticsDataPacket::Read(char* pBuffer, unsigned int iLen)
{ 
 
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	packet>>m_serial;
	
    //这里需要进行协议序列号验证  to do 
	CCLOG("SCAthleticsDataPacket AthleticsSerialID:  <<<<<<<<<<<<%d>>>>>>>>>>>>>>",ROLEINFODATAHANDLER->getRoleCurAthleticsSerialID());
	 
	/*
	解析战斗数据包
	*/
	if(LoadAthleticsData(packet))
	return true;

	return false;
}


bool   SCAthleticsDataPacket::LoadAthleticsData(cobra_win::DPacket & packetData)
{
	do 
	{ 
		 ATHLETICPROCEDUREDATA->onDestroy();
		 ATHLETICPROCEDUREDATA->isUsingLocalDataReplace = false;
		 //战斗地图信息
		 if(ATHLETICPROCEDUREDATA->pAthleticsMapInfo!=NULL)
		 {
			ATHLETICPROCEDUREDATA->pAthleticsMapInfo->destroy();
			delete  ATHLETICPROCEDUREDATA->pAthleticsMapInfo;
			ATHLETICPROCEDUREDATA->pAthleticsMapInfo=NULL;
		 }
		 ATHLETICPROCEDUREDATA->pAthleticsMapInfo=new AthleticsMapInfo();
		 ATHLETICPROCEDUREDATA->pAthleticsMapInfo->decodePacketData(packetData);
    
	  
		 //战斗前人物信息包
		 if(ATHLETICPROCEDUREDATA->pPreAthleticsData!=NULL)
		 {
			 ATHLETICPROCEDUREDATA->pPreAthleticsData->destroy();
			 delete  ATHLETICPROCEDUREDATA->pPreAthleticsData;
			 ATHLETICPROCEDUREDATA->pPreAthleticsData=NULL;
		 }
		 ATHLETICPROCEDUREDATA->pPreAthleticsData=new PreAthleticsDataInfo();
		 ATHLETICPROCEDUREDATA->pPreAthleticsData->decodePacketData(packetData);

 
		 //全战斗过程信息数据
		 if(ATHLETICPROCEDUREDATA->pAthleticProData!=NULL)
		 {
			 ATHLETICPROCEDUREDATA->pAthleticProData->destroy();
			 delete  ATHLETICPROCEDUREDATA->pAthleticProData;
			 ATHLETICPROCEDUREDATA->pAthleticProData=NULL;
		 }
		 ATHLETICPROCEDUREDATA->pAthleticProData=new AthleticsProData();
		 ATHLETICPROCEDUREDATA->pAthleticProData->decodePacketData(packetData);

		 //全战斗结果信息数据
		 if(ATHLETICPROCEDUREDATA->pAthleticResultData!=NULL)
		 {
			 ATHLETICPROCEDUREDATA->pAthleticResultData->destroy();
			 delete  ATHLETICPROCEDUREDATA->pAthleticResultData;
			 ATHLETICPROCEDUREDATA->pAthleticResultData=NULL;
		 }
		 ATHLETICPROCEDUREDATA->pAthleticResultData=new AthleticsResultData();
		 ATHLETICPROCEDUREDATA->pAthleticResultData->decodePacketData(packetData);
		  		  
 
		 //战斗奖励信息数据
		 if(ATHLETICPROCEDUREDATA->pAthleticBaseReward!=NULL)
		 {
			 ATHLETICPROCEDUREDATA->pAthleticBaseReward->destroy();
			 delete  ATHLETICPROCEDUREDATA->pAthleticBaseReward;
			 ATHLETICPROCEDUREDATA->pAthleticBaseReward=NULL;
		 }

		 ATHLETICPROCEDUREDATA->pAthleticBaseReward=new AthleticsBaseReward();
		 ATHLETICPROCEDUREDATA->pAthleticBaseReward->decodePacketData(packetData);

		 
		 CheckLoadLocalAthleticsData();

		return  true;
	} while (false);

	return false;	 
}


bool	SCAthleticsDataPacket::CheckLoadLocalAthleticsData()
{  
 
	//return true;
	
	
		//判断是否需要替换
		if(AthleticProcedureDataHandler::get_instance2()->athleticsBattleType==_ATHLETICS_CUSTOMS_BATTLE_TYPE_)
		{
			//判断是否能够替换 
			PCustomsMapInfo mapInfo = (PCustomsMapInfo)ATHLETICPROCEDUREDATA->pAthleticsMapInfo->mapInfoData;

			if((mapInfo->mapID==getWillReplaceMapID1()&&mapInfo->stageID==getWillReplaceStageID1())||(mapInfo->mapID==getWillReplaceMapID2()&&mapInfo->stageID==getWillReplaceStageID2()))
			{  
				//开始替换 
				PCacheBuffer  pCacheBuffer = LocalAthleticsDataManager::get_instance2()->GetAthleticsDPacket(mapInfo->mapID,mapInfo->stageID);
				if(pCacheBuffer)
				{  
					ATHLETICPROCEDUREDATA->isUsingLocalDataReplace = true;
					DPacket packetData(pCacheBuffer->m_pBuffer,pCacheBuffer->m_nSize);
					packetData.read(m_head,2);
					packetData>>m_len;
					packetData>>m_pn;
					packetData>>m_serial;

					ATHLETICPROCEDUREDATA->onDestroy();
					//战斗地图信息
					if(ATHLETICPROCEDUREDATA->pAthleticsMapInfo!=NULL)
					{
						ATHLETICPROCEDUREDATA->pAthleticsMapInfo->destroy();
						delete  ATHLETICPROCEDUREDATA->pAthleticsMapInfo;
						ATHLETICPROCEDUREDATA->pAthleticsMapInfo=NULL;
					}
					ATHLETICPROCEDUREDATA->pAthleticsMapInfo=new AthleticsMapInfo();
					ATHLETICPROCEDUREDATA->isDuriningLocal = true;
					ATHLETICPROCEDUREDATA->pAthleticsMapInfo->decodePacketData(packetData);
					ATHLETICPROCEDUREDATA->isDuriningLocal = false;


					//战斗前人物信息包
					if(ATHLETICPROCEDUREDATA->pPreAthleticsData!=NULL)
					{
						ATHLETICPROCEDUREDATA->pPreAthleticsData->destroy();
						delete  ATHLETICPROCEDUREDATA->pPreAthleticsData;
						ATHLETICPROCEDUREDATA->pPreAthleticsData=NULL;
					}
					ATHLETICPROCEDUREDATA->pPreAthleticsData=new PreAthleticsDataInfo();
					ATHLETICPROCEDUREDATA->pPreAthleticsData->decodePacketData(packetData);


					//全战斗过程信息数据
					if(ATHLETICPROCEDUREDATA->pAthleticProData!=NULL)
					{
						ATHLETICPROCEDUREDATA->pAthleticProData->destroy();
						delete  ATHLETICPROCEDUREDATA->pAthleticProData;
						ATHLETICPROCEDUREDATA->pAthleticProData=NULL;
					}
					ATHLETICPROCEDUREDATA->pAthleticProData=new AthleticsProData();
					ATHLETICPROCEDUREDATA->pAthleticProData->decodePacketData(packetData);

					//全战斗结果信息数据
					if(ATHLETICPROCEDUREDATA->pAthleticResultData!=NULL)
					{
						ATHLETICPROCEDUREDATA->pAthleticResultData->destroy();
						delete  ATHLETICPROCEDUREDATA->pAthleticResultData;
						ATHLETICPROCEDUREDATA->pAthleticResultData=NULL;
					}
					ATHLETICPROCEDUREDATA->pAthleticResultData=new AthleticsResultData();
					ATHLETICPROCEDUREDATA->pAthleticResultData->decodePacketData(packetData);

				} 
			}  
		} 
	return true;
}


////////////////////////////////////////////////////////////////////////////////

unsigned  int  SCAthleticsDataPacketFactory::GetPacketType()
{
   	return _TYPED_PACKET_S2C_ATHLETICSDATA_;
} 

bool  SCAthleticsDataPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	SCAthleticsDataPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
 
	//如果是普通战斗的话，立刻进入战斗界面，如果是爬塔，由爬塔负责何时进入战斗
	int type = AthleticProcedureDataHandler::get_instance2()->athleticsBattleType;
	bool isReTryBattle=AthleticProcedureDataHandler::get_instance2()->isReTryBattle;
	if(type == _ATHLETICS_CUSTOMS_BATTLE_TYPE_ || type == _ATHLETICS_ARENA_BATTLE_TYPE_
		|| type == _ATHLETICS_SERVANT_BATTLE_TYPE_ || type == _ATHLETICS_FRIEND_BATTLE_TYPE_
		|| type == _ATHLETICS_KUANGDONG_BATTLE_TYPE_ || type == _ATHLETICS_CHALLENEGE_HEROSOUL_TYPE_
		|| type == _ATHLETICS_BOSSSCORE_BATTLE_TYPE_ || type == _ATHLETICS_KUANGDONG_HUNTLIEREN_TYPE_
		|| isReTryBattle)
	{
		//Post战斗数据加载完成通知
		OnLoadDataFinishCallBackHandler();
	}
	else if(type == _ATHLETICS_CLIMPTOWER_BATTLE_TYPE_)
	{//告知塔界面，接收到数据，人物可以跑了
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_CHALLENGETOWER_RUNHERO_);
	}
	else if(type == _ATHLETICS_TEAM_BATTLE_TYPE_)
	{ 
		char athleticsProcedure[8]={0};
		if(!IsCurAthleticsProcedure())
			sprintf(athleticsProcedure,"%d",IProcedure::_TYPED_ATHLETICS_PROCEDURE_);
		else
			sprintf(athleticsProcedure,"%d",LoadingWindow::_RESTART_ATHLETICS_PROCEDURE_);
		EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_HIDE_TEAMSELECTWINDOW_);
		SET_WEAK_TIPS_SYSTEM(true)
		LevelUpDataHandler::get_instance2()->m_showFlag=false;
		EventSystem::get_instance2()->PushEvent(_TYPE_EVENT_WILL_ENTER_ATHLETICS_);
		EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_,athleticsProcedure);
	}

	return true;
}


void   SCAthleticsDataPacketFactory::OnLoadDataFinishCallBackHandler()
{  
	char athleticsProcedure[8]={0};
	if(!IsCurAthleticsProcedure())
	sprintf(athleticsProcedure,"%d",IProcedure::_TYPED_ATHLETICS_PROCEDURE_);
	else
	sprintf(athleticsProcedure,"%d",LoadingWindow::_RESTART_ATHLETICS_PROCEDURE_);

	LevelUpDataHandler::get_instance2()->m_showFlag=false;
	SET_WEAK_TIPS_SYSTEM(true)
	EventSystem::get_instance2()->PushEvent(_TYPE_EVENT_WILL_ENTER_ATHLETICS_);
	EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_SHOW_LOADINGWINDOW_,athleticsProcedure);

}

bool	SCAthleticsDataPacketFactory::IsCurAthleticsProcedure()
{
	if(DOTATribeApp::get_instance2()->GetActiveProcedure()->GetType()==IProcedure::_TYPED_ATHLETICS_PROCEDURE_)
		return true;

	return false;
}


