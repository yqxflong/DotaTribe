//Name:HeartBeatDataHandler
//Function:�����������ڼ��ͻ����Ƿ�Ͽ�����
//Author:fangjun
//Date:20130819

#ifndef _DOTATRIBE_HEARTBEAT_DATAHANDLER_H_
#define _DOTATRIBE_HEARTBEAT_DATAHANDLER_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>

#define HEART_BEAT

class HeartBeatDataHandler : public IDataHandler, public cobra_win::Singleton2<HeartBeatDataHandler>{
private:
	int m_iNoReplyCount;	//�޻ظ�ͳ��
	bool m_bLost;			//�Ƿ����

	int m_iTickCount;		//Tick��ʱcount

	const int CHECK_TICKCOUNT;//�������TIck����������
	const int NOREPLY_COUNT_MAX;//����޻ظ����������رձ���socket

	bool m_bTickReplyFlag;	//�������ظ��ı�־��һ���ظ���Ϊtrue���´η���ʱ���˱�־λ�����Ϊfalse��Ĭ���ϴ�δ�յ��ظ�

public:
	HeartBeatDataHandler();
	virtual ~HeartBeatDataHandler();
	
	int getNoReplyCount();
	void setNoReplyCount(int count);

	void doTickCheckLogic();//NetSystem��Tick��������¼�

	bool isLost();//�Ƿ����
	void setLostStatus(bool	status);//���õ���״̬

	void resetAllCount();	//������������״̬

	void ToServerChickOnline();

public:
	void decodePacketData(cobra_win::DPacket & packet);

	
	virtual void handlePacket(IPacket* packet){};

	virtual void onDestroy(){};

	virtual bool init(){	return true;	};

};

#define HEARTBEATDATAHANDLER (HeartBeatDataHandler::get_instance2())

#endif