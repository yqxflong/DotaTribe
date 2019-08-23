//Name:ServantDataHandler.h
//Function:�ʹ�ϵͳ����
//Author:fangjun
//date:20131015

#ifndef _DOTATRIBE_SERVANT_DATAHANDLER_H_
#define _DOTATRIBE_SERVANT_DATAHANDLER_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>
#include "../include/CSMapTable.h"
#include <vector>
#include <list>
#include <string>


//ū���Ŀ���ȵĺ���
class SSFreeFriend
{
public:
	int playerId;
	int iconId;
	char quality;
	std::string name;
	short level;
	int btlCapa;
	void decodePacketData(cobra_win::DPacket & packet);
};

//ū�������Ϣ
class SSSOSInfo
{
public:
	char leftSOSTime;//ʣ����������
	std::vector<SSFreeFriend *> freeFriendVector;//�������������б�
public:
	SSSOSInfo();
	~SSSOSInfo();
	void destroyData();//�����������
	void decodePacketData(cobra_win::DPacket & packet);
};

//ū������
class SNewsInfo
{
public:
	std::vector<std::string> newsVector;
public:
	SNewsInfo();
	~SNewsInfo();
	void destroyData();//�����������
	void decodePacketData(cobra_win::DPacket & packet);
};

//ū�����뻥������
class SSPlayInfo
{
public:
	char leftPlayTimes;
	int owerPlayerId;//ū��������Ϣ
	int owerIconId;
	char owerQuality;
	std::string owerName;
	short owerLevel;
	int owerBtlCapa;
	void decodePacketData(cobra_win::DPacket & packet);
};

//ū��������Ϣ
class SSRevoltInfo
{
public:
	char leftRevoltTimes;//ʣ�෴������
	//ū������Ϣ
	int owerPlayerId;
	int owerIconId;
	char owerQuality;
	std::string owerName;
	short owerLevel;
	int owerBtlCapa;
	//����NPC��Ϣ
	int npcIconId;
	char npcQuality;
	std::string npcName;
	int npcPrice;
public:
	SSRevoltInfo();
	void destroyData();
	void decodePacketData(cobra_win::DPacket & packet);
};

//ū�����Ĵ��������
class SMSlaveFriend
{
public:
	int playerId;
	int iconId;
	char quality;
	std::string name;
	std::string owerName;//�˺������˵�����
	int owerBtlCapa;//�˺������ε�ս��
	void decodePacketData(cobra_win::DPacket & packet);
};

//ū���������Ϣ
class SMRescueInfo
{
public:
	char leftRescueTimes;//ʣ���ȴ���
	std::vector<SMSlaveFriend *> slaveFriendVector;//���Ǵ���ȵĺ���
public:
	SMRescueInfo();
	~SMRescueInfo();
	void destroyData();//�����������
	void decodePacketData(cobra_win::DPacket & packet);
};

//ū����������Ϣ���ҵ�ū��
class SMSlave
{
public:
	int playerId;
	int iconId;
	char quality;
	std::string name;
	short level;
	int workSeconds;		//�ɻ�ʱ��,����
	int makeExp;			//��������
	int expPerMin;			//���Ӳ������飬��ū���ȼ��й�
	int secondsCount;		//����������Ӿ���ʱ�ļ���ֵ
	int chainCdLeftTime;	//������ȴʣ��ʱ��, ����
	void decodePacketData(cobra_win::DPacket & packet);
};

//ū����������Ϣ
class SMPlayInfo
{
public:
	char leftPlayTimes;//ʣ�໥������
	std::vector<SMSlave *> slaveVector;
	long long longTickBeginTime;//�������ǲ�������ȡ��
	int secondsCount;//���ڷ��Ӽ�ʱ
public:
	SMPlayInfo();
	~SMPlayInfo();
	void destroyData();//�����������
	void decodePacketData(cobra_win::DPacket & packet);
};

//ū����ץ����������°ܽ����߳����б�Ԫ
class SMFightedPlayer
{
public:
	int playerId;
	int iconId;
	char quality;
	std::string name;
	short level;
	char identity;//0���ɣ�1ū������2ū��
	int catchCdLeftTime;	//ץ����ȴʱ��ʣ��ʱ��

	void decodePacketData(cobra_win::DPacket & packet);
};

//ū��������ץ��ū��������Ϣ
class SMCatchInfo
{
public:
	char leftCatchTimes;//ʣ��ץ������
	std::vector<SMFightedPlayer *> losserVector;//���°ܽ��б�
	std::vector<SMFightedPlayer *> winnerVector;//�����б�
	long long longTickBeginTime;//�������ǲ�������ȡ��
public:
	SMCatchInfo();
	~SMCatchInfo();
	void destroyData();//�����������
	void decodePacketData(cobra_win::DPacket & packet);
};




/************************************************************************/
/* This is DataHandler                                                  */
/************************************************************************/

class ServantDataHandler : public IDataHandler, public cobra_win::Singleton2<ServantDataHandler>
{
public:
	enum{
		_PLAY_FUNC_RELEASE_ = 0,	//�ͷ�
		_PLAY_FUNC_CHAIN_	= 1,	//����
		_PLAY_FUNC_PRESS_	= 2,	//ѹե
	};
public:
	//ū��������������״̬��Ϣ
	SMCatchInfo * m_pSMCatchInfo;		//ū��������ץ����Ϣ//constructor
	SMPlayInfo * m_pSMPlayInfo;					//ū����������Ϣ
	SMRescueInfo * m_pSMRescueInfo;				//ū���������Ϣ
	
	//ū��״̬��Ϣ
	SSRevoltInfo * m_pSSRevoltInfo;				//ū�����뷴��������Ϣ//constructor
	SSPlayInfo * m_pSSPlayInfo;					//ū��������Ϣ
	SSSOSInfo * m_pSSSOSInfo;					//ū��������Ϣ

	SNewsInfo * m_pSNewsInfo;					//������Ϣ//constructor//�־õģ���������������ɣ���������ʱ��Ҫdestroy
	
	int m_iLastStayPage;//������Ϸǰ��һ������ҳ��
	bool m_iWillEnterAthletic;//��־�ʹӽ��潫Ҫ����ս��

public:
	ServantDataHandler();
	virtual ~ServantDataHandler();

protected:

	virtual void handlePacket(IPacket* packet){};

	virtual void onDestroy();

	virtual bool init(){	return true;	};

public:
	/*
		ս���������ж�״̬�Լ���Ҫ��ʾ��ҳ��͹���
	*/
	void OnAthleticEnd(short stageId, bool iswin);

public:
	//�������ץ��ū��
	void ToServerMasterEnterCatch();
	void ToClientMasterEnterCatchResult();

	//ץ��ū��
	void ToServerMasterCatch(int playerId);

	//���뻥��ū��������
	void ToServerMasterEnterPlay();
	void ToClientMasterEnterPlayResult();

	//ū��������
	void ToServerMasterPlay(char playType, char index);
	void ToClientMasterPlayResult(char playType, char index, int cdLeftTime);

	//ū������������
	void ToClientMasterNewsCome();

	//����ū�������
	void ToServerMasterEnterRescue();
	void ToClientMasterEnterRescueResult();

	//ū����������
	void ToServerMasterRescue(int playerId);

	//�������ū������
	void ToServerSlaveEnterRevolt();
	void ToClientSlaveEnterRevoltResult();

	//ū������
	void ToServerSlaveRevolt();

	//ū����¸
	void ToServerSlaveBribe();
	void ToClientSlaveBribeResult();

	//����ū����������
	void ToServerSlaveEnterPlay();
	void ToClientSlaveEnterPlayResult();

	//ū������
	void ToServerSlavePlay();
	void ToClientSlavePlayResult();

	//ū����������
	void ToClientSlaveNewsCome();

	//����ū����Ƚ���
	void ToServerSlaveEnterSOS();
	void ToClientSlaveEnterSOSResult();

	//ū����Ⱥ���
	void ToServerSlaveSos(int playerId);

};

#define SERVANTDATAHANDLER (ServantDataHandler::get_instance2())

#endif