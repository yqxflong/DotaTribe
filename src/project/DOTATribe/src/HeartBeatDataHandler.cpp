//Name:HeartBeatDataHandler
//Function:心跳包，用于检测客户端是否断开连接
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

// 	CHECK_TICKCOUNT = DOTATribeApp::get_instance2()->GetFPS() * 30;//每30秒发送一次心跳
// 
// 	NOREPLY_COUNT_MAX = 2;//总共2 * 30 = 2min

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
		{//false,此30秒内未收到回复
			++m_iNoReplyCount;//未收到回复计数+1
			
			if(m_iNoReplyCount >= NOREPLY_COUNT_MAX)
			{
				m_bLost = true;
				NETSYSTEM->ClocsSocket();
			}

		}
		else
		{
			m_bTickReplyFlag = false;//清除收到回复标志
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