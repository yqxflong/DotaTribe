//Name:MiningDataHandler.h
//Function:�ڿ�
//Author:fangjun
//date:20131127

#ifndef _DOTATRIBE_MINING_DATAHANDLER_H_
#define _DOTATRIBE_MINING_DATAHANDLER_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>
#include "../include/CSMapTable.h"
#include <vector>
#include <string>

// Ѱ��������Ϣ
class HuntLieRenInfo
{
public:
	std::string name;
	unsigned short level;
	std::string heroLevelDesc;
	unsigned char spentTili;//��������
	unsigned char index;
	unsigned char isActive;//�Ƿ񼤻�

	unsigned char probability;//���ʣ���Ӧ�ͻ�������

	char type;		// ����		//0��Ʒ 1��Ǯ 2���� 3��ʯ 4���� 5����<br>
	int count;
	char catogory;
	int templateId;
	std::string itemName;
	char quality;
	int iconId;
public:
	void decodePacketData(cobra_win::DPacket & packet);
};

//���佱���б��俪������
class HuntBoxData
{
public:
	char type;		//Ʈ������,0��Ʒ��1��Ǯ��2����
	int count;		//����
	char critValue;	//����ֵ
	int itemIconId;	//type == 0ʱ
public:
	HuntBoxData();
	void decodePacketData(cobra_win::DPacket & packet);
};

//Ѱ�����
class HuntResult
{
public:
	bool needRespond;		//��Ҫ������

	char type;								//�������ͣ�0���䣬1��ң�2���ˣ�3�ᱦ�¼�
	
	//���佱��ʱ
	std::vector<HuntBoxData *> boxData;		//���佱������

	//���ʱ
	int playerId;
	char playerIsFriend;
	std::string playerName;
	unsigned short playerLevel;
	int playerHeroIconId;
	int playerHeroShapeId;//�ȸ趯��
	char playerHeroQuality;
	int playerBtlCapa;

	//����ʱ
	std::string orcName;
	unsigned short orcLevel;
	int orcHeroIconId;
	int orcHeroShapeId;//��������
	char orcHeroQuality;
	int orcBtlCapa;
	int orcBuyPrice;

	//�ᱦ�¼�
	unsigned char lieRenIndex;	//���˵�index
	int lieRenShapeId;			//���˵�shapeId

public:
	HuntResult();
	~HuntResult();
	void destroyData();
	void decodePackerData(cobra_win::DPacket & packet);
};

//Ѱ�������¼�״̬
class HuntLieRen
{
public:
	unsigned char index;
	std::string name;
	unsigned char isActive;	//0�ر�״̬��1����״̬
public:
	HuntLieRen();
	void decodePackerData(cobra_win::DPacket & packet);
};

//Ѱ����Ϣ
class HuntData
{
public:
	short huntTimes;		//ʣ��Ѱ������
	short maxHuntTimes;		//���Ѱ������
	std::vector<HuntLieRen *> lieRenVector;
public:
	HuntData();
	~HuntData();
	void destroyData();
	void decodePacketData(cobra_win::DPacket & packet);
};

//��������������Ϣ
class DragonOwnerData
{
public:
	char index;
	int playerId;
	std::string playerName;
	unsigned short playerLevel;
	int heroIconId;
	char heroQuality;
	int btlCapa;
	unsigned short miningFriendCount;	//�ڿ������
	unsigned short friendCount;			//�ܺ�����
	char isFriend;		//�������ҵĺ���
	char isMining;			//������������ɿ�
	int workedTime;		//�ۼ��ڿ�ʱ��
	long long tickBegin;
	int outPut;			//�ۼƻ�ý��
	int outPutPerMin;	//ÿ���Ӳ���
public:
	DragonOwnerData();
	void workTick();
	void decodePacketData(cobra_win::DPacket & packet);
};

//��������
class DragonAreaData
{
public:
	char challengePrice;	//��ս�۸�
	char slaveCount;		//��ǰū������
	char maxSlaveCount;		//���ū������
	unsigned short improve;			//���Ч�ʼӳɣ�*100��
	std::vector<DragonOwnerData *> mineOwnerData;	//������Ϣ
public:
	DragonAreaData();
	~DragonAreaData();
	void destroyData();
	void decodePackerData(cobra_win::DPacket & packet);
};

//���˿���λ��
class DwarvenSitData
{
public:
	char index;		//��λindex
	char isNull;	//�Ƿ������
	int playerId;	//����playerID�ж��Ƿ����Լ�
	std::string playerName;
	unsigned short playerLevel;
	int heroIconId;
	char heroQuality;	
	int workedTime;		//�ۼ��ڿ�ʱ��
	long long tickBegin;	//tick��ʱ��ʼ
	int param;			//�ۼƻ��/ս��
	int outPutPerMin;	//ÿ���Ӳ�����ֻ���Լ���
public:
	DwarvenSitData();
	void workTick();
	void decodePacketData(cobra_win::DPacket & packet);
};

//���˿���
class DwarvenAreaData
{
public:
	char slaveCount;		//��ǰū������
	char maxSlaveCount;		//���ū������
	unsigned short improve;			//���Ч�ʼӳɣ�*100��
	int leftLootMoney;		//@���󻨷�Ǯ��   
	std::vector<DwarvenSitData *> sitData;		//��λ��Ϣ
public:
	DwarvenAreaData();
	~DwarvenAreaData();
	void destroyData();
	void decodePackerData(cobra_win::DPacket & packet);
};

//�ؾ�����
class GoblinAreaData
{
public:
	char slaveCount;		//��ǰū������
	char maxSlaveCount;		//���ū������
	unsigned short improve;			//���Ч�ʼӳɣ�*100��
	int workedTime;		//�ۼ��ڿ�ʱ��,��,<0ʱ��ʾ�����ڿ�
	long long tickBegin;	//tick��ʱ��ʼ
	int outPut;			//�ۼƲ���
	int outPutPerMin;	//ÿ���Ӳ���
public:
	GoblinAreaData();
	void workTick();
	void decodePacketData(cobra_win::DPacket & packet);
};


//������Ϣ
class MineAreaData
{
public:
	char areaType;			//��������,0,1,2
	char maxMiningTime;		//���ɼ�ʱ��
	int outPut;				//��Ҳ���
	unsigned char isMining;	//1 �ǲɼ� 0�ǲ��ɼ�
public:
	MineAreaData();
	void decodePacketData(cobra_win::DPacket & packet);
};

//�ڿ���������Ϣ
class MiningData
{
public:
	std::string mineDesc;		//��������
	std::vector<MineAreaData *> mineArea;	//������Ϣ
	short leftHuntTimes;			//ʣ��ɼ�����
	short maxHuntTimes;			//���ɼ�����
	char lookCd;				//Ѱ������������ȴʱ��
public:
	MiningData();
	~MiningData();
	void destroyData();
	void decodePackerData(cobra_win::DPacket & packet);
};


/************************************************************************/
/* This is DataHandler                                                  */
/************************************************************************/

class MiningDataHandler : public IDataHandler, public cobra_win::Singleton2<MiningDataHandler>
{
public:
	MiningData * m_pMiningData;		//�ڿ�����������
	GoblinAreaData * m_pGoblinAreaData;				//�ؾ���������
	DwarvenAreaData * m_pDwarvenAreaData;			//���˿�������
	DragonAreaData * m_pDragonAreaData;				//������������
	
	HuntData * m_pHuntData;							//Ѱ��������Ϣ
	HuntResult * m_pHuntResult;						//Ѱ�����
	HuntLieRenInfo * m_pHuntLieRenData;				//Ѱ��������ϸ��Ϣ

public:
	int m_iFightType;//ս������
	int m_iBackArea;//ս����Ӧ�û��˵���ҳ��
public:
	bool m_isFBDragon;	//�ǵ�һ����ս����

public:
	bool m_bNeedOpenTipsPage2;//��Ҫ��Ѱ�����˶Ի���
public:
	MiningDataHandler();
	virtual ~MiningDataHandler();

protected:

	virtual void handlePacket(IPacket* packet){};

	virtual void onDestroy();

	virtual bool init(){	return true;	};

public:
	void OnAthleticEnd(int type, bool win);

	//��Ѱ��ս�������ص�
	void OnHuntLieRenQiangDuoAthleticEnd(bool qiangduoWin);

public:
	//����ɿ�
	void ToServerEnterMining();
	void ToClientEnterMiningResult();

	//����ؾ�����
	void ToServerEnterGoblinArea();
	void ToClientEnterGoblinAreaResult();

	//�����ɼ�
	void ToServerStopMining();
	void ToClientStopMiningResult();

	//���밫�˿���
	void ToServerEnterDwarvenArea();
	void ToClientEnterDwarvenAreaResult();

	//���˿�������λ,�����ս��
	void ToServerDwarvenLoot(char index);
	void ToClientDwarvenLootResult();

	//������˿���
	void ToServerEnterDragonArea();
	void ToClientEnterDragonAreaResult();

	//��ս���˿����Ŀ���,�����ս��
	void ToServerDragonChallengeOwner(char index);
	
	//��ʼ�ɿ�,type.1�ؾ���2���ˣ�3���ˣ���index.���ڿ���λ��
	void ToServerStartMining(char type, char index);
	void ToClientStartMiningResult(char type, char index);

	//����Ѱ��
	void ToServerEnterHuntMining();
	void ToClientEnterHuntMiningResult();

	//Ѱ��
	void ToServerHuntMining();
	void ToClientHuntMiningResult();

	//���ᡢ����,�����ս��
	void ToServerHuntGrab();

	//�Ӻ��ѣ����к�����Ǯ
	void ToServerHuntHelloMoney();
	void ToClientHuntHelloMoneyResult();

	//����Ӻ��Ѻ󷵻�
	void ToClientAskFriendResult();

	//������ʯֱ������Ʒ
	void ToServerHuntBuyMineral();
	void ToClientHuntBuyMineralResult();

	//����Ѱ������
	void ToServerBuyHuntTimes();
	void ToClientBuyHuntTimesResult();

	//����鿴������Ϣ
	void ToServerChaKanLieRen(unsigned char index);
	void ToClientChaKanLieRenResult();

	//������������
	void ToServerQiangDuoLieRenNo(unsigned char index);
	void ToClientQiangDuoLieRenNoResult(unsigned char index);

	//��ʼ��������
	void ToServerQiangDuoLieRenYes(unsigned char index);

	/*
		�ж�����Ƿ��ڸÿ���λ��  ���ڷ���0
	*/	
	int PlayerinMineIndex();
};

#define MININGDATAHANDLER (MiningDataHandler::get_instance2())

#endif