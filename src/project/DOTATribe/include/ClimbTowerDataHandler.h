//Name:ClimbTowerDataHandler.h
//Function:����������
//Author:fangjun
//date:20130826


#ifndef _DOTATRIBE_CLIMBTOWER_DATAHANDLER_H_
#define _DOTATRIBE_CLIMBTOWER_DATAHANDLER_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>
#include <vector>
#include "../include/CSMapTable.h"
#include <string>

class TowerTodayReward
{
public:
	int type;					//���� 0:��Ʒ 1:��Ǯ 2: ���� 3:��ʯ 4:���� 5:����
	int iconId;
	unsigned char quality;
	int templateId;
	std::string name;
	short rewardFloor;			//��������
	unsigned short count;
	unsigned char status;		//״̬��0����ȡ��1����ȡ��2������
public:
	TowerTodayReward();
	void decodePacketData(cobra_win::DPacket & packet);
};

class TowerReward
{
public:
	int iconId;
	unsigned char quality;
	int templateId;
	std::string name;
	unsigned short rewardFloor;		//��������
	unsigned char status;			//״̬��0����ȡ��1����ȡ
public:
	void decodePacketData(cobra_win::DPacket & packet);
};

class TowerRewardData
{
public:
	short topFloor;		//�ҵ���óɼ� add by fangjun at 20140122
	int rank;			//�ҵ����� add by fangjun at 20140122
	short curFloor;		//��ǰ�ҵĲ���

	std::vector<TowerTodayReward *> todayRewardVector;	//���ս��� add by fangjun at 20140122
	std::vector<TowerReward *> towerRewardVector;		//���ս��� add by fangjun at 20140122
public:
	TowerRewardData();
	~TowerRewardData();
	void destroyData();
	void decodePacketData(cobra_win::DPacket & packet);
	TowerReward * getFirstUnOpenTowerReward();
};

class TowerFastFightResultItem
{
public:
	unsigned char result;	//ս�����
	short fightFloor;	//ս������
	int gotExp;				//��þ���
	int gotHonor;			//�������
	void decodePacketData(cobra_win::DPacket & packet);
};

class TowerFastFightResultData
{
public:
	std::vector<TowerFastFightResultItem *> resultData;
public:
	TowerFastFightResultData();
	~TowerFastFightResultData();
	void destroyData();
	void decodePacketData(cobra_win::DPacket & packet);
};

//�׶ν���Ԫ��
class TowerSkillItem{
public:
	int skillId;
	int iconId;
	TowerSkillItem()
	{
		skillId = 0;
		iconId = 0;
	}
	void decodePacketData(cobra_win::DPacket & packet);
};

class EnterData{
public:
	unsigned char entertype;//��ǰ�����ħ��״̬��0�״Σ�1���ٴ�
	//����Ϊ�״ν���
	short defaultfloor;//Ĭ��ѡ�в�
	unsigned char usedTimes;	//ʹ�ù��Ĵ���
	unsigned char maxTimes;		//����ʹ�ô���

	//����Ϊ�ٴν���
	short nowfloor;//��ǰ���ڲ���
	int gotmoney;//�ۼƻ�ý�Ǯ
	int gotexp;//�ۼƻ�þ���
	int nextmoney;//��һ���ý�Ǯ
	int nextexp;//��һ���þ���
	std::vector<TowerSkillItem *> skillData;//�Ƽ�����

	//����Ϊ�Լ�������
	int rankNum;	//������<0��Ϊ�������а���
	int honor;		//��õ���ҫ
	int jewelResetPrice;	//��ʯ���ü۸�
	int fastFightPrice;		//����ս���۸�

	char haveFloorReward;	//��δ��ȡ�Ĳ㼶����

	short leftChallengeTime;	//ʣ����ս���� add by fangjun at 20140122
public:
	EnterData()
	{
		defaultfloor = 0;
		usedTimes = 0;
		maxTimes = 0;
		nowfloor = 0;
		gotmoney = 0;
		gotexp = 0;
		nextmoney = 0;
		nextexp = 0;
		skillData.clear();
		rankNum = 0;
		honor = 0;
		jewelResetPrice = 0;
		fastFightPrice = 0;
		haveFloorReward = 0;
	}
	~EnterData();
public:
	void destroyData();
	void decodePacketData(cobra_win::DPacket & packet);
};

class TowerRankItem//�������а�ÿ������
{
public:
	int playerId;
	int iconId;
	std::string name;
	short level;
	int score;//����
	int floor;//����

	void decodePacketData(cobra_win::DPacket & packet);
};

class TowerRankList
{
public:
	std::vector<TowerRankItem *> rankVector;
public:
	void destroyData();		//��destroy�������ⲿ������ڴ�������������ݣ�����������������������ʱ���������
public:
	TowerRankList();
	~TowerRankList();
	void decodePacketData(cobra_win::DPacket & packet);
};


class ClimbTowerDataHandler : public IDataHandler, public cobra_win::Singleton2<ClimbTowerDataHandler>{
public:
	EnterData enterData;//��������

	int iCurFloor;			//���ﵱǰ���ڵĲ���
	int iPreFloor;			//����֮ǰ���ڵĲ���

	unsigned char fightResult;//1ʤ����0ʧ��

	TowerRankList * m_pRankList;//�������а�����

	TowerFastFightResultData * m_pFastFightResultData;//����ս�����

	TowerRewardData * m_pRewardData;

public:
	ClimbTowerDataHandler();
	virtual ~ClimbTowerDataHandler();

protected:

	virtual void handlePacket(IPacket* packet){};

	virtual void onDestroy();

	virtual bool init(){	return true;	};

public:

	//�����ħ��
	void ToServerEnterTower();
	void ToClientEnterTowerResult();

	//��ʼ���������жϼ��������
	void ToServerStartTower();
	void ToClientStartTowerResult();

	//��ս�ؿ�
	void ToServerChallengeTower();
	void ToClientChallengeTowerResult();

	//����������¼
	void ToServerResetTower();
	void ToClientResetTowerResult();

	//���а�
	void ToServerRankList();
	void ToClientRankListResult();

	//����ս��
	void ToServerFastFight();
	void ToClientFastFightWinResult();

	//��ʯ����
	void ToServerJewelReset();
	void ToClientJewelResetResult();

	//������ȥ�������
	void ToServerEnterReward();
	void ToClientEnterRewardResult();

	//��ȡ����
	void ToServerGetReward(char type, unsigned short floor);
	void ToClientGetRewardResult(char type, unsigned short floor);

	//������������
	void ToServerBuyClimbTowerTimes();
	void ToClientBuyClimbTowerTimesResult();

	//�����Ƿ�����Ѵ���
	//bool HasFreeTimes();

	//�����Ƿ��е��ߴ���
	//bool HasPayTimes();

};

#define CLIMBTOWERDATAHANDLER (ClimbTowerDataHandler::get_instance2())

#endif