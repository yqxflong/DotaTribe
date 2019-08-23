#ifndef _MVP_TEAMBATTLEPRESENTER_H_
#define _MVP_TEAMBATTLEPRESENTER_H_

#include "../include/BasePresenter.h"
#include "../include/Message.h"
#include <include/common/Singleton.h>
#include <vector>
#include <string>

class TeamBattlePresenter : public BasePresenter, public Handler, public cobra_win::Singleton2<TeamBattlePresenter>
{
private:
	int aaa;

public:
	TeamBattlePresenter();

	virtual ~TeamBattlePresenter();

	/*
		��ʼ��
	*/
	virtual bool Init();

	/*
		����
	*/
	virtual void Tick();

	/*
		����
	*/
	virtual void Destroy();

	/*
		��Ϣ������
	*/
	virtual Message * HandleMsg(Message messge);

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

#define TEAMBATTLEPRESENTER (TeamBattlePresenter::get_instance2())

#endif