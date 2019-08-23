//Name:TeamBattleDataHandler.h
//Function:��Ӹ�������
//Author:fangjun
//date:20130922

#ifndef _DOTATRIBE_TEAMBATTLE_DATAHANDLER_H_
#define _DOTATRIBE_TEAMBATTLE_DATAHANDLER_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>
#include <vector>
#include "../include/CSMapTable.h"
#include "../include/CPublicVarReader.h"
#include <string>
#include <cocos2d.h>

class TMercenaryItem
{
public:
	int playerId;
	int iconId;
	char quality;
	std::string skinName;
	//char enhanceLevel;
	int btlCapa;
	std::string playerName;
	int hirePrice;
	int pvpRank;
	short playerLevel;
	void decodePacketData(cobra_win::DPacket & packet);
};

class TMercenaryList
{
public:
	std::vector<TMercenaryItem *> mercenaryVector;
	TMercenaryList();
	~TMercenaryList();
	void destroyData();
	void decodePacketData(cobra_win::DPacket & packet);
};

class TSlaveItem
{
public:
	int playerId;
	int iconId;
	char quality;
	std::string skinName;
	//char enhanceLevel;
	int btlCapa;
	std::string playerName;
	short leftMinute;
	short playerLevel;
	void decodePacketData(cobra_win::DPacket & packet);
};

class TSlaveList
{
public:
	std::vector<TSlaveItem *> slaveVector;
	TSlaveList();
	~TSlaveList();
	void destroyData();
	void decodePacketData(cobra_win::DPacket & packet);
};

class TRewardItem
{
public:
	int iconId;
	unsigned char catogory;
	char quality;
	int templateId;
	TRewardItem()
	{
		iconId = 0;
		catogory = 0;
		quality = 0;
		templateId = 0;
	}
	void decodePacketData(cobra_win::DPacket & packet);
};


class TGateItem
{
public:
	char gateId;
	std::string gateName;
	int iconId;	//��ͼ
	unsigned short minLevel;
	IByte mIspreMappass; //0������ǰ��δͨ��  1��ǰ����ͨ��
	unsigned char nowStage;
	unsigned char maxStage;
	int totalPlayer;//��ǰ���ȵ��ܲ�������

	unsigned char rewardNeedVipLevel0;		//����0��Ҫvip�ȼ�
	int rewardCostJewel0;			//����0��Ҫ��ʯ����
	unsigned char rewardNeedVipLevel1;		//����1��Ҫvip�ȼ�
	int rewardCostJewel1;			//����1��Ҫ��ʯ����
	unsigned char rewardNeedVipLevel2;		//����2��Ҫvip�ȼ�
	int rewardCostJewel2;			//����2��Ҫ��ʯ����

	std::vector<TRewardItem *> rewardVector;

	bool canSelect;//�Ƿ���ѡ��
private:
	void destroyData();//����vector������
public:
	TGateItem();
	~TGateItem();
	void decodePacketData(cobra_win::DPacket & packet);
};

class TTeamBattleData
{
public:
	unsigned char challengeTimes;    //�Ѿ���ս����
	unsigned char maxChallengeTimes;//�ܹ�������ս����

	std::vector<TGateItem *> gateVector;
public:
	void destroyData();
public:
	TTeamBattleData();
	~TTeamBattleData();
	void decodePacketData(cobra_win::DPacket & packet);
};

class TTeamStageData//��ǰ�ؿ�����
{
public:
	unsigned char stageId;
	std::string stageName;
	void decodePacketData(cobra_win::DPacket & packet);
};

class TTeamListItem//ÿ����������
{
public:
	int teamId;
	int leaderPlayerId;//�ӳ�playerId
	std::string leaderName;
	char memberCount;//��ǰ��������
	void decodePacketData(cobra_win::DPacket & packet);
};

class TTeamListData//��������
{
public:
	std::vector<TTeamListItem *> teamVector;
public:
	void destroyData();
public:
	TTeamListData();
	~TTeamListData();
	void decodePacketData(cobra_win::DPacket & packet);

};

class TMyTeamMember//�ҵĶ����Ա
{
public:
	int index;//����,������ô洢
	char gameUnitType;//0��ң�3ū����4Ӷ��
	char isLeader;
	std::string markName;//����ϵ
	std::string skinName;//��������
	//char enhanceLevel;
	int btlCapacity;//ս��
	int iconId;
	char quality;
	std::string playerName;//�������
	int playerId;//���Id

	void decodePacketData(cobra_win::DPacket & packet);
};

class TMyTeamData//�ҵĶ�������
{
public:
	char isIamLeader;
	std::vector<TMyTeamMember *> memberVector;
public:
	void destroyData();//��destroy�������ⲿ������ڴ�������������ݣ�����������������������ʱ���������
public:
	TMyTeamData();
	~TMyTeamData();
	void decodePacketData(cobra_win::DPacket & packet);
};


/************************************************************************/
/* This is DataHandler                                                   */
/************************************************************************/

class TeamBattleDataHandler : public IDataHandler, public cobra_win::Singleton2<TeamBattleDataHandler>
{
public:
	int m_iStartGateIdx;//ѡ�и����ڸ����б��е�Idx
	int m_iMyTeamId;//�ҵĶ���Id

	bool m_bHaveGateReward;//��ǰ�и���ͨ�ؽ���

	bool m_bOneMsgIsCoolDowning;//��ӽ����һ��������ť�Ƿ�������ȴ
	long long m_lCoolDownTimeCount;//һ������ʱ�����

	TTeamBattleData * m_pTeamBattleData;	//��Ӹ����ĸ�������

	TTeamListData * m_pTeamListData;		//�����б�����

	TTeamStageData * m_pTeamStageData;		//��ǰ�ؿ���Ϣ

	TMyTeamData * m_pMyTeamData;			//�����ڶ�������

	TSlaveList * m_pSlaveList;				//�ҵ�ū���б�
	
	TMercenaryList * m_pMercenaryList;		//�ҿ����õ�Ӷ���б�

	cocos2d::CCPoint m_fOldGateTableOffset;		//��ӹؿ���ƫ������add in 2013-12-26
	float m_fOldGateTableWidth;			//��Ӹ����ؿ��Ŀ�ȣ�add in 2013-12-26

public:
	TeamBattleDataHandler();
	virtual ~TeamBattleDataHandler();

protected:

	virtual void handlePacket(IPacket* packet){};

	virtual void onDestroy();

	virtual bool init(){	return true;	};


public:
	//��������ڶ�������
	void ClearMyTeamData();

	//���ѡ�еĸ�����Ϣ
	TGateItem * GetSelectGateInfo();

	TGateItem * GetGateInfoById(int gateId);

	TGateItem * GetGateInfoByIdx(int gateIdx);

	int GetMaxCanStartGateIdx();

	//���������ڶ���
	void DestroyMyTeam();

	//��ȡ�ҵ�ǰ���ڶ���Ķӳ�playerId  add by fangjun @ 20140312
	int GetMyTeamLeaderId();

public:
	//������Ӹ�����ѡ�ؿ�
	void ToServerEnterTeamBattle();
	void ToClientEnterTeamBattleResult();

	//����ĳ����������
	void ToServerResetGate();
	void ToClientResetGateResult();

	//������ӣ�ѡ����
	void ToServerEnterTeamSelect();
	void ToClientEnterTeamSelectResult();

	//��ö����б�
	void ToClientGetTeamList();

	//������ߴ�������
	void ToServerJoinTeam();
	void ToClientJoinTeamResult();//����ҵĶ�����Ϣ

	//֪ͨ�������뿪ѡ������棬�رն���ͬ��
	void ToServerStopTeamSync();

	//�Ƴ�ĳ����Ա
	void ToServerRemoveMember(int playerId);
	void ToClientBeRemoved(char removedType);

	//����ĳ����������
	void ToServerResetTeamBattle(unsigned char fubenId);
	void ToClientResetTeamBattle();

	//��ʼ�ؿ�
	void ToServerStartStage();
	
	//��������ս˳��
	void ToServerReorderMyTeam(std::vector<int> & playerIdVec);
	void ToServerSwitchMemberPlace(int arg0, int arg1);

	//��ȡͨ�ؽ���
	void ToServerGateReward(char rewardTag);
	void ToClientGateRewardResult();

	//��ȡ�����Ϣ
	void ToServerGetPlayerInfo(int playerid);

	//��ȡū���б�
	void ToServerGetSlaveList();
	void ToClientGetSlaveList();

	//��ȡӶ���б�
	void ToServerGetMercenaryList();
	void ToClientGetMercenaryList();
	
	//��Ӷĳ��ū��
	void ToServerRendSlave(int playerId);

	//��Ӷĳ��Ӷ��
	void ToServerRendMercenary(int playerId);
};

#define TEAMBATTLEDATAHANDLER (TeamBattleDataHandler::get_instance2())

#endif