#include	 <cocos2d.h>
#include  "../include/S2CQAPacket.h"
#include  "../include/DOTATribeApp.h"
#include  "../include/LoggerSystem.h"
#include  "../include/IProcedure.h"
#include  "../include/PacketTyper.h"
#include  "../include/NetSystem.h"
#include  "../include/EventTyper.h"
#include  "../include/EventSystem.h"
#include   <include/mem/DPacket.h> 
#include  "../include/CSMapTable.h"
#include  "../include/AthleticProcedureDataHandler.h"
#include   "../include/QADataHandler.h"

using  namespace  cobra_win;

 
unsigned  int  S2CQAPacket::GetPacketType()
{
     return  _TYPEF_PACKET_S2C_COMMON_QA_SERVER_;
}

unsigned  int  S2CQAPacket::GetPacketLength()
{
     return  sizeof(S2CQAPacket);
}


bool  S2CQAPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;

	if(!LoadQAData(packet))
	return false;
	  
	return true;
}



bool  S2CQAPacket::LoadQAData(cobra_win::DPacket & packet)
{
	if(QADataHandler::get_instance2()!=NULL)
	{
		if(QADataHandler::get_instance2()->pQAdata!=NULL)
		{
			delete QADataHandler::get_instance2()->pQAdata;
			QADataHandler::get_instance2()->pQAdata=NULL;
		}
		  
		QADataHandler::get_instance2()->pQAdata=new QAData();
		QADataHandler::get_instance2()->pQAdata->decodePacketData(packet);

		return true;

	}

	return  false;
}
 
 

////////////////////////////////////////////////////////////////////////////////

unsigned  int  S2CQAPacketFactory::GetPacketType()
{
   	return _TYPEF_PACKET_S2C_COMMON_QA_SERVER_;
} 

bool  S2CQAPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CQAPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;
   
	OnFinishCallBackHandler();
	return true;
}


void S2CQAPacketFactory::OnFinishCallBackHandler()
{
   //发送接受到消息处理消息
   EventSystem::get_instance2()->PushEvent(_TYPED_EVENT_SHOW_TIPSWINDOW_) ;
}

 