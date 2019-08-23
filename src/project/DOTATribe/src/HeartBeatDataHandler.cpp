//Name:HeartBeatDataHandler
//Function:�����������ڼ��ͻ����Ƿ�Ͽ�����
//Author:fangjun
//Date:20130819
#include "../include/HeartBeatPacket.h"
#include "../include/DOTATribeApp.h"
#include "../include/NetSystem.h"
#include "../include/HeartBeatDataHandler.h"

HeartBeatDataHandler::HeartBeatDataHandler()
:CHECK_TICKCOUNT(DOTATribeApp::get_instance2()->GetFPS() * 30)
,NOREPLY_COUNT_MAX(2)
{
	m_iNoReplyCount = 0;
	m_bLost = false;
	m_iTickCount = 0;

// 	CHECK_TICKCOUNT = DOTATribeApp::get_instance2()->GetFPS() * 30;//ÿ30�뷢��һ������
// 
// 	NOREPLY_COUNT_MAX = 2;//�ܹ�2 * 30 = 2min

	m_bTickReplyFlag = false;
}
HeartBeatDataHandler::~HeartBeatDataHandler()
{
	m_iNoReplyCount = 0;
	m_bLost = false;
	m_iTickCount = 0;
}

int HeartBeatDataHandler::getNoReplyCount()
{
	return m_iNoReplyCount;
}

void HeartBeatDataHandler::setNoReplyCount(int count)
{
	m_iNoReplyCount = count;
}

void HeartBeatDataHandler::doTickCheckLogic()
{
	++m_iTickCount;

	if(m_bLost)
	{
		return;
	}
	
	if(m_iTickCount >= CHECK_TICKCOUNT)
	{
		if(m_bTickReplyFlag == false)
		{//false,��30����δ�յ��ظ�
			++m_iNoReplyCount;//δ�յ��ظ�����+1
			
			if(m_iNoReplyCount >= NOREPLY_COUNT_MAX)
			{
				m_bLost = true;
				NETSYSTEM->ClocsSocket();
			}

		}
		else
		{
			m_bTickReplyFlag = false;//����յ��ظ���־
		}
		this->ToServerChickOnline();
		m_iTickCount = 0;
	}
	
}


bool HeartBeatDataHandler::isLost()
{
	return m_bLost;
}

void HeartBeatDataHandler::setLostStatus(bool	status)
{
	m_bLost = status;
}

void HeartBeatDataHandler::resetAllCount()
{
	m_iNoReplyCount = 0;
	m_bLost = false;
	m_iTickCount = 0;
	m_bTickReplyFlag = false;
}

void HeartBeatDataHandler::ToServerChickOnline()
{
	CSHeartBeatPacket packet;
	packet.Send();
}

void HeartBeatDataHandler::decodePacketData(cobra_win::DPacket & packet)
{
	if(m_iNoReplyCount <= NOREPLY_COUNT_MAX)
	{
		m_iNoReplyCount = 0;
	}

	m_bTickReplyFlag = true;
}