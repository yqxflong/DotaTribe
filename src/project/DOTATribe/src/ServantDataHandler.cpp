//Name:ServantDataHandler.cpp
//Function:�ʹ�
//Author:fangjun
//date:20131015

#include <cocos2d.h>
#include "../include/ServantDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/CPublicVarReader.h"
#include "../include/ServantPacket.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/ServantView.h"
#include "../include/PuCongWindow.h"
#include "../include/NFControlsManager.h"
#include "../include/NFToolController.h"

//ū���Ŀ���ȵĺ���
void SSFreeFriend::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>playerId;
	packet>>iconId;
	packet>>quality;
	unsigned short strlen = 0;
	char * str = NULL;
	packet>>strlen;//����
	str = new char[strlen+1];
	packet.read(str, strlen);
	str[strlen] = '\0';
	name.assign(str);
	delete[] str;
	str = NULL;
	packet.read(level);
	packet.read(btlCapa);
}

//ū�������Ϣ
SSSOSInfo::SSSOSInfo()
{
	leftSOSTime = 0;
	destroyData();
}
SSSOSInfo::~SSSOSInfo()
{
	leftSOSTime = 0;
	destroyData();
}
void SSSOSInfo::destroyData()
{
	for(unsigned int i = 0; i < freeFriendVector.size(); ++i)
	{
		if(freeFriendVector[i])
		{
			delete freeFriendVector[i];
			freeFriendVector[i] = NULL;
		}
	}
	freeFriendVector.clear();
}
void SSSOSInfo::decodePacketData(cobra_win::DPacket & packet)
{
	destroyData();
	packet>>leftSOSTime;
	char count = 0;
	packet>>count;
	SSFreeFriend * fri = NULL;
	for(char i = 0; i < count; ++i)
	{
		fri = new SSFreeFriend();
		fri->decodePacketData(packet);
		freeFriendVector.push_back(fri);
	}
}

//ū�����뻥������
void SSPlayInfo::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>leftPlayTimes;
	packet>>owerPlayerId;
	packet>>owerIconId;
	packet>>owerQuality;

	unsigned short strlen = 0;
	char * str = NULL;
	packet>>strlen;//����
	str = new char[strlen+1];
	packet.read(str, strlen);
	str[strlen] = '\0';
	owerName.assign(str);
	delete[] str;
	str = NULL;

	packet.read(owerLevel);
	packet>>owerBtlCapa;
}

SSRevoltInfo::SSRevoltInfo()
{
	destroyData();
}

void SSRevoltInfo::destroyData()
{
	leftRevoltTimes = 0;
}

void SSRevoltInfo::decodePacketData(cobra_win::DPacket & packet)
{
	destroyData();
	packet>>leftRevoltTimes;
	packet>>owerPlayerId;
	packet>>owerIconId;
	packet>>owerQuality;
	
	unsigned short strlen = 0;
	char * str = NULL;
	packet>>strlen;//����
	str = new char[strlen+1];
	packet.read(str, strlen);
	str[strlen] = '\0';
	owerName.assign(str);
	delete[] str;
	str = NULL;
	
	packet.read(owerLevel);
	packet>>owerBtlCapa;
	packet>>npcIconId;
	packet>>npcQuality;
	
	packet>>strlen;//����
	str = new char[strlen+1];
	packet.read(str, strlen);
	str[strlen] = '\0';
	npcName.assign(str);
	delete[] str;
	str = NULL;

	packet>>npcPrice;
}

void SMSlaveFriend::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>playerId;
	packet>>iconId;
	packet>>quality;

	unsigned short strlen = 0;
	char * str = NULL;
	packet>>strlen;
	str = new char[strlen+1];
	packet.read(str, strlen);
	str[strlen] = '\0';
	name.assign(str);
	delete[] str;
	str = NULL;

	packet>>strlen;
	str = new char[strlen+1];
	packet.read(str, strlen);
	str[strlen] = '\0';
	owerName.assign(str);
	delete[] str;
	str = NULL;

	packet>>owerBtlCapa;

}

//ū���������Ϣ
SMRescueInfo::SMRescueInfo()
{
	destroyData();
}
SMRescueInfo::~SMRescueInfo()
{
	destroyData();
}
void SMRescueInfo::destroyData()
{
	for(unsigned int i = 0; i < slaveFriendVector.size(); ++i)
	{
		if(slaveFriendVector[i])
		{
			delete slaveFriendVector[i];
			slaveFriendVector[i] = NULL;
		}
	}
	slaveFriendVector.clear();
}
void SMRescueInfo::decodePacketData(cobra_win::DPacket & packet)
{
	destroyData();
	packet>>leftRescueTimes;
	char count = 0;
	packet>>count;
	SMSlaveFriend * sf = NULL;
	for(char i = 0; i < count; ++i)
	{
		sf = new SMSlaveFriend();
		sf->decodePacketData(packet);
		slaveFriendVector.push_back(sf);
	}
}


SNewsInfo::SNewsInfo()
{
	destroyData();
}
SNewsInfo::~SNewsInfo()
{
	destroyData();
}
void SNewsInfo::destroyData()
{
	newsVector.clear();
}
void SNewsInfo::decodePacketData(cobra_win::DPacket & packet)
{
	char count = 0;
	packet>>count;
	for(char i = 0; i < count; ++i)
	{
		std::string news = "";

		NFC_ParsePacketString(packet, news);

		newsVector.push_back(news);
	}
}

//ū����������Ϣ���ҵ�ū��
void SMSlave::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>playerId;
	packet>>iconId;
	packet>>quality;

	unsigned short strlen = 0;
	char * str = NULL;
	packet>>strlen;
	str = new char[strlen+1];
	packet.read(str, strlen);
	str[strlen] = '\0';
	name.assign(str);
	delete[] str;
	str = NULL;

	packet.read(level);
	packet.read(workSeconds);
	packet>>makeExp;
	packet>>expPerMin;

	packet>>chainCdLeftTime;

	secondsCount = (workSeconds % 3600) % 60;
}


//ū����������Ϣ
SMPlayInfo::SMPlayInfo()
{
	destroyData();
}
SMPlayInfo::~SMPlayInfo()
{
	destroyData();
}
void SMPlayInfo::destroyData()
{
	for(unsigned int i = 0; i < slaveVector.size(); ++i)
	{
		if(slaveVector[i])
		{
			delete slaveVector[i];
			slaveVector[i] = NULL;
		}
	}
	slaveVector.clear();
}
void SMPlayInfo::decodePacketData(cobra_win::DPacket & packet)
{
	destroyData();
	packet>>leftPlayTimes;
	SMSlave * slave = NULL;
	char have;
	for(int i = 0; i < USER_MAX_SLAVE; ++i)
	{
		packet>>have;
		if(have > 0)
		{
			slave = new SMSlave();
			slave->decodePacketData(packet);
		}
		else
		{
			slave = NULL;
		}
		slaveVector.push_back(slave);
	}
}

//ū����ץ����������°ܽ����߳����б�Ԫ
void SMFightedPlayer::decodePacketData(cobra_win::DPacket & packet)
{
	packet>>playerId;
	packet>>iconId;
	packet>>quality;

	unsigned short strlen = 0;
	char * str = NULL;
	packet>>strlen;
	str = new char[strlen+1];
	packet.read(str, strlen);
	str[strlen] = '\0';
	name.assign(str);
	delete[] str;
	str = NULL;

	packet.read(level);
	packet>>identity;
	packet>>catchCdLeftTime;
}

//ū��������ץ��ū��������Ϣ
SMCatchInfo::SMCatchInfo()
{
	destroyData();
	leftCatchTimes = 0;
}
SMCatchInfo::~SMCatchInfo()
{
	destroyData();
}
void SMCatchInfo::destroyData()
{
	for(unsigned int i = 0; i < losserVector.size(); ++i)
	{
		if(losserVector[i])
		{
			delete losserVector[i];
			losserVector[i] = NULL;
		}
	}
	losserVector.clear();
	for(unsigned int i = 0; i < winnerVector.size(); ++i)
	{
		if(winnerVector[i])
		{
			delete winnerVector[i];
			winnerVector[i] = NULL;
		}
	}
	winnerVector.clear();
}
void SMCatchInfo::decodePacketData(cobra_win::DPacket & packet)
{
	destroyData();
	char count = 0;
	SMFightedPlayer * player = NULL;
	packet>>leftCatchTimes;
	packet>>count;
	for(char i = 0; i < count; ++i)
	{
		player = new SMFightedPlayer();
		player->decodePacketData(packet);
		losserVector.push_back(player);
	}
	packet>>count;
	for(char i = 0; i < count; ++i)
	{
		player = new SMFightedPlayer();
		player->decodePacketData(packet);
		winnerVector.push_back(player);
	}
}



ServantDataHandler::ServantDataHandler()
{
	m_pSMCatchInfo = new SMCatchInfo();
	m_pSMPlayInfo = NULL;
	m_pSMRescueInfo = NULL;

	m_pSSRevoltInfo = new SSRevoltInfo();
	m_pSSPlayInfo = NULL;
	m_pSSSOSInfo = NULL;

	m_pSNewsInfo = new SNewsInfo();//

	m_iLastStayPage = 0;
	m_iWillEnterAthletic = false;
}

ServantDataHandler::~ServantDataHandler()
{
	if(m_pSMCatchInfo)
	{
		delete m_pSMCatchInfo;
		m_pSMCatchInfo = NULL;
	}
	if(m_pSMPlayInfo)
	{
		delete m_pSMPlayInfo;
		m_pSMPlayInfo = NULL;
	}
	if(m_pSMRescueInfo)
	{
		delete m_pSMRescueInfo;
		m_pSMRescueInfo = NULL;
	}
	if(m_pSSRevoltInfo)
	{
		delete m_pSSRevoltInfo;
		m_pSSRevoltInfo = NULL;
	}
	if(m_pSSPlayInfo)
	{
		delete m_pSSPlayInfo;
		m_pSSPlayInfo = NULL;
	}
	if(m_pSSSOSInfo)
	{
		delete m_pSSSOSInfo;
		m_pSSSOSInfo = NULL;
	}

	if(m_pSNewsInfo)
	{
		delete m_pSNewsInfo;
		m_pSNewsInfo = NULL;
	}

}

void ServantDataHandler::onDestroy()
{
	m_iLastStayPage = 0;
	m_iWillEnterAthletic = false;

	if(m_pSMCatchInfo)
	{
		m_pSMCatchInfo->destroyData();
	}
	if(m_pSMPlayInfo)
	{
		delete m_pSMPlayInfo;
		m_pSMPlayInfo = NULL;
	}
	if(m_pSMRescueInfo)
	{
		delete m_pSMRescueInfo;
		m_pSMRescueInfo = NULL;
	}
	if(m_pSSRevoltInfo)
	{
		m_pSSRevoltInfo->destroyData();
	}
	if(m_pSSPlayInfo)
	{
		delete m_pSSPlayInfo;
		m_pSSPlayInfo = NULL;
	}
	if(m_pSNewsInfo)
	{
		m_pSNewsInfo->destroyData();
	}
	if(m_pSSSOSInfo)
	{
		delete m_pSSSOSInfo;
		m_pSSSOSInfo = NULL;
	}
}

void ServantDataHandler::OnAthleticEnd(short stageId, bool iswin)
{
	//�ص��ʹӽ��棬0���ʹӷ�ҳ
	EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_PUCONGWINDOW_, _to_event_param_(PuCongWindow::HLW_SERVANT));


}

void ServantDataHandler::ToServerMasterEnterCatch()
{
	CSMasterEnterCatchPacket packet;
	packet.Send();

	NFC_showCommunicationWating(true);
}

void ServantDataHandler::ToClientMasterEnterCatchResult()
{
	//�յ�����ץ��������
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SERVANT_MASTER_ENTERCATCH_GETDATA_);

	NFC_showCommunicationWating(false);
}

//ץ��ū��
void ServantDataHandler::ToServerMasterCatch(int playerId)
{
	CSMasterCatchPacket packet(ROLEINFODATAHANDLER->updateRoleAthleticsSerialID(), playerId);
	packet.Send();

	NFC_showCommunicationWating(true);

	m_iWillEnterAthletic = true;
}

//���뻥��ū��������
void ServantDataHandler::ToServerMasterEnterPlay()
{
	CSMasterEnterPlayPacket packet;
	packet.Send();

	NFC_showCommunicationWating(true);
}

void ServantDataHandler::ToClientMasterEnterPlayResult()
{
	//�յ��˻�����������
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SERVANT_MASTER_ENTERPLAY_GETDATA_);

	NFC_showCommunicationWating(false);
}

//ū��������
void ServantDataHandler::ToServerMasterPlay(char playType, char index)
{
	CSMasterPlayPacket packet(playType, index);
	packet.Send();

	NFC_showCommunicationWating(true);
}

void ServantDataHandler::ToClientMasterPlayResult(char playType, char index, int cdLeftTime)
{
	//�յ��˻����ɹ�����
	if(playType == _PLAY_FUNC_RELEASE_ || playType == _PLAY_FUNC_PRESS_)
	{//�����ѹե�����ͷţ���ǰū����Ҫɾ��
		delete m_pSMPlayInfo->slaveVector[index];
		m_pSMPlayInfo->slaveVector[index] = NULL;
	}
	else
	{//��Ϸ
		m_pSMPlayInfo->leftPlayTimes--;
		m_pSMPlayInfo->slaveVector[index]->chainCdLeftTime = cdLeftTime;
	}

	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SERVANT_MASTER_PLAYSUCCESS_GETDATA_, _to_event_param_(playType), _to_event_param_(index));

	NFC_showCommunicationWating(false);
}

void ServantDataHandler::ToClientMasterNewsCome()
{
	//���յ�ū�����µ�����
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SERVANT_MASTER_NEWS_COME_);
}

//����ū�������
void ServantDataHandler::ToServerMasterEnterRescue()
{
	CSMasterEnterRescuePacket packet;
	packet.Send();

	NFC_showCommunicationWating(true);
}

void ServantDataHandler::ToClientMasterEnterRescueResult()
{
	//�յ�����������
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SERVANT_MASTER_ENTERRESCUE_GETDATA_);

	NFC_showCommunicationWating(false);
}

//ū����������
void ServantDataHandler::ToServerMasterRescue(int playerId)
{
	CSMasterRescuePacket packet(ROLEINFODATAHANDLER->updateRoleAthleticsSerialID(), playerId);
	packet.Send();

	NFC_showCommunicationWating(true);

	m_iWillEnterAthletic = true;
}

//�������ū������
void ServantDataHandler::ToServerSlaveEnterRevolt()
{
	CSSlaveEnterRevoltPacket packet;
	packet.Send();

	NFC_showCommunicationWating(true);
}

void ServantDataHandler::ToClientSlaveEnterRevoltResult()
{
	//�յ����뷴����������
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SERVANT_SLAVE_ENTERREVOLT_GETDATA_);

	NFC_showCommunicationWating(false);
}

//ū������
void ServantDataHandler::ToServerSlaveRevolt()
{
	CSSlaveRevoltPacket packet(ROLEINFODATAHANDLER->updateRoleAthleticsSerialID());
	packet.Send();

	NFC_showCommunicationWating(true);
	
	m_iWillEnterAthletic = true;
}

//ū����¸
void ServantDataHandler::ToServerSlaveBribe()
{
	CSSlaveBribePacket packet;
	packet.Send();

	NFC_showCommunicationWating(true);
}

void ServantDataHandler::ToClientSlaveBribeResult()
{
	//�յ���¸�ɹ���Ϣ
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SERVANT_SLAVE_BRIBESUCCESS_GETDATA_);

	NFC_showCommunicationWating(false);

	//��¸�ɹ���ū��Ӧ�ñ������������Ҫ�������ץ��������Ϣ
	ToServerMasterEnterCatch();

}

//����ū����������
void ServantDataHandler::ToServerSlaveEnterPlay()
{
	CSSlaveEnterPlayPacket packet;
	packet.Send();

	NFC_showCommunicationWating(true);
}

void ServantDataHandler::ToClientSlaveEnterPlayResult()
{
	//�յ�������������
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SERVANT_SLAVE_ENTERPLAY_GETDATA_);

	NFC_showCommunicationWating(false);
}

//ū������
void ServantDataHandler::ToServerSlavePlay()
{
	CSSlavePlayPacket packet;
	packet.Send();

	NFC_showCommunicationWating(true);
}

void ServantDataHandler::ToClientSlavePlayResult()
{
	m_pSSPlayInfo->leftPlayTimes--;

	//���ū�������ɹ�
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SERVANT_SLAVE_PLAYSUCCESS_GETDATA_);

	NFC_showCommunicationWating(false);
}

void ServantDataHandler::ToClientSlaveNewsCome()
{
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SERVANT_SLAVE_NEWS_COME_);
}

//����ū����Ƚ���
void ServantDataHandler::ToServerSlaveEnterSOS()
{
	CSSlaveEnterSOSPacket packet;
	packet.Send();

	NFC_showCommunicationWating(true);
}

void ServantDataHandler::ToClientSlaveEnterSOSResult()
{
	//��ý�����Ƚ��
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SERVANT_SLAVE_ENTERSOS_GETDATA_);

	NFC_showCommunicationWating(false);
}

//ū����Ⱥ���
void ServantDataHandler::ToServerSlaveSos(int playerId)
{
	CSSlaveSOSPacket packet(ROLEINFODATAHANDLER->updateRoleAthleticsSerialID(), playerId);
	packet.Send();

	NFC_showCommunicationWating(true);

	m_iWillEnterAthletic = true;
}
