//Name:BoseScoreDataHandler.h
//Function:Boss����ϵͳ
//Author:fangjun
//date:20140215


#ifndef _DOTATRIBE_BOSSSCORE_DATAHANDLER_H_
#define _DOTATRIBE_BOSSSCORE_DATAHANDLER_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>
#include <vector>
#include <string>

//���ֽ�����Ʒ��Ԫ
class BSScoreRewardItem
{
public:
	char index;
	int minScore;
	char type;				//0��Ʒ 1��Ǯ 2���� 3��ʯ 4���� 5����<br>
	int count;
	char catogory;
	int templateId;
	std::string name;
	char quality;
	int iconId;
	unsigned char status;		//״̬��0����ȡ��1����ȡ��2������
public:
	void decodePacketData(cobra_win::DPacket & packet);
};

//����������Ʒ��Ԫ
class BSRankRewardItem
{
public:
	char type;				//0��Ʒ 1��Ǯ 2���� 3��ʯ 4���� 5����<br>
	int count;
	char catogory;
	int templateId;
	std::string name;
	char quality;
	int iconId;
public:
	void decodePacketData(cobra_win::DPacket & packet);
};

//����������Ϣ
class BSRewardData
{
public:
	int maxScore;
	short rank;
	std::vector<BSScoreRewardItem *> scoreRewardVector;//���ֽ���
	int leftDrawSeconds;	//ʣ����ȡʱ��
	long long tickBeginTime;
	std::vector<BSRankRewardItem * > rankRewardVector;//��������
public:
	BSRewardData();
	~BSRewardData();
	void destroyData();
	void decodePacketData(cobra_win::DPacket & packet);

};

//���а�ÿ����Ϣ
class BSRankItem
{
public:
	int playerId;
	int iconId;
	std::string name;
	int score;
	short rank;
	short level;
public:
	void decodePacketData(cobra_win::DPacket & packet);
};

//���а��������
class BSRankList
{
public:
	std::vector<BSRankItem *> rankVector;
public:
	BSRankList();
	~BSRankList();
	void destroyData();
	void decodePacketData(cobra_win::DPacket & packet);
};

class BSBossInfo
{
public:
	char quality;
	int iconId;
public:
	void decodePacketData(cobra_win::DPacket & packet);
};

//boss���ֽ�������
class BSBossScoreData
{
public:
	std::string description;
	char status;
	int leftSeconds;
	long long tickBeginTime;
	std::vector<BSBossInfo *> bossVector;
	int maxScore;
	short rank;
	short leftFreeTimes;
	short leftChallengeItemCount;
	short challengePrice;
	std::vector<std::string> nameVector;
	std::vector<int> scoreVector;
	char hasReward;
public:
	BSBossScoreData();
	~BSBossScoreData();
	void destroyData();
	void decodePacketData(cobra_win::DPacket & packet);

};

class BossScoreDataHandler : public IDataHandler, public cobra_win::Singleton2<BossScoreDataHandler>{
public:
	int m_iFreeTimesSync;//ͬ����õ���Ѵ���ֵ��������ҳ��Ǳ�չʾ

	BSBossScoreData * m_pBossScoreData;
	BSRankList * m_pRankList;
	BSRewardData * m_pRewardData;

public:
	BossScoreDataHandler();
	virtual ~BossScoreDataHandler();

protected:

	virtual void handlePacket(IPacket* packet){};

	virtual void onDestroy();

	virtual bool init(){	return true;	};
public:
	//ս������
	void OnAthleticEnd(int stageID, bool win);

public:
	//��������boss
	void ToServerEnterBoss();
	void ToClientEnterBossResult();

	//�������а�
	void ToServerEnterRank();
	void ToClientEnterRankResult();

	//���뱦�佱��
	void ToServerEnterReward();
	void ToClientEnterRewardResult();

	//��ʼ��ս
	void ToServerChallenge();
	
	//��ȡ����
	void ToServerGetReward(char type, char index);
	void ToClientGetRewardResult(char type, char index);



};

#define BOSSSCOREDATAHANDLER (BossScoreDataHandler::get_instance2())

#endif