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
		初始化
	*/
	virtual bool Init();

	/*
		更新
	*/
	virtual void Tick();

	/*
		销毁
	*/
	virtual void Destroy();

	/*
		消息处理器
	*/
	virtual Message * HandleMsg(Message messge);

public:
	//进入组队副本，选关卡
	void ToServerEnterTeamBattle();
	void ToClientEnterTeamBattleResult();

	//重置某个副本进度
	void ToServerResetGate();
	void ToClientResetGateResult();

	//进入组队，选队友
	void ToServerEnterTeamSelect();
	void ToClientEnterTeamSelectResult();

	//获得队伍列表
	void ToClientGetTeamList();

	//加入或者创建队伍
	void ToServerJoinTeam();
	void ToClientJoinTeamResult();//获得我的队伍信息

	//通知服务器离开选队伍界面，关闭队伍同步
	void ToServerStopTeamSync();

	//移除某个队员
	void ToServerRemoveMember(int playerId);
	void ToClientBeRemoved(char removedType);

	//重置某个副本进度
	void ToServerResetTeamBattle(unsigned char fubenId);
	void ToClientResetTeamBattle();

	//开始关卡
	void ToServerStartStage();

	//重设队伍出战顺序
	void ToServerReorderMyTeam(std::vector<int> & playerIdVec);
	void ToServerSwitchMemberPlace(int arg0, int arg1);

	//获取通关奖励
	void ToServerGateReward(char rewardTag);
	void ToClientGateRewardResult();

	//获取玩家信息
	void ToServerGetPlayerInfo(int playerid);

	//获取奴隶列表
	void ToServerGetSlaveList();
	void ToClientGetSlaveList();

	//获取佣兵列表
	void ToServerGetMercenaryList();
	void ToClientGetMercenaryList();

	//雇佣某个奴隶
	void ToServerRendSlave(int playerId);

	//雇佣某个佣兵
	void ToServerRendMercenary(int playerId);

};

#define TEAMBATTLEPRESENTER (TeamBattlePresenter::get_instance2())

#endif