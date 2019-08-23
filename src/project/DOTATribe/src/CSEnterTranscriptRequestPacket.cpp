//Name：CSEnterTranscriptRequestPacket
//Function：请求战斗数据
//Author:	Johny

#include <cocos2d.h>
#include   "../include/CSEnterTranscriptRequestPacket.h"
#include   "../include/PacketTyper.h"
#include   "../include/RoleInfoDataHandler.h"
#include   "../include/AthleticProcedureDataHandler.h"
#include   "../include/MissionDataHandler.h"

CSEnterTranscriptRequestPacket::CSEnterTranscriptRequestPacket(short mapID,short stageID)
{ 
	int serialID=ROLEINFODATAHANDLER->updateRoleAthleticsSerialID();
	PushData(serialID);
	PushData(mapID);
	PushData(stageID);


	if(AthleticProcedureDataHandler::get_instance2()!=NULL)
	{ 
		AthleticProcedureDataHandler::get_instance2()->preMapInfoData.preMapID=mapID;
		AthleticProcedureDataHandler::get_instance2()->preMapInfoData.preStageID=stageID;
		AthleticProcedureDataHandler::get_instance2()->preMapInfoData.preIsClear=false;
		StatesInfoData * pStateInfoData=MissionDataHandler::get_instance2()->GetStatesInfoInfo(mapID,stageID);
		if(pStateInfoData!=NULL&&pStateInfoData->getIsClear())
		{
			AthleticProcedureDataHandler::get_instance2()->preMapInfoData.preIsClear=true;
		}
	}  
}

unsigned  int  CSEnterTranscriptRequestPacket::GetPacketType()
{
   return _TYPED_PACKET_C2S_ENTER_TRANSCRIPT_ ;
}