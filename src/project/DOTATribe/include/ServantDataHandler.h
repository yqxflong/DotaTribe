//Name:ServantDataHandler.h
//Function:仆从系统数据
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


//奴隶的可求救的好友
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

//奴隶求救信息
class SSSOSInfo
{
public:
	char leftSOSTime;//剩余求助次数
	std::vector<SSFreeFriend *> freeFriendVector;//可以求助朋友列表
public:
	SSSOSInfo();
	~SSSOSInfo();
	void destroyData();//用于清空数据
	void decodePacketData(cobra_win::DPacket & packet);
};

//奴隶新闻
class SNewsInfo
{
public:
	std::vector<std::string> newsVector;
public:
	SNewsInfo();
	~SNewsInfo();
	void destroyData();//用于清空数据
	void decodePacketData(cobra_win::DPacket & packet);
};

//奴隶进入互动数据
class SSPlayInfo
{
public:
	char leftPlayTimes;
	int owerPlayerId;//奴隶主的信息
	int owerIconId;
	char owerQuality;
	std::string owerName;
	short owerLevel;
	int owerBtlCapa;
	void decodePacketData(cobra_win::DPacket & packet);
};

//奴隶反抗信息
class SSRevoltInfo
{
public:
	char leftRevoltTimes;//剩余反抗次数
	//奴隶主信息
	int owerPlayerId;
	int owerIconId;
	char owerQuality;
	std::string owerName;
	short owerLevel;
	int owerBtlCapa;
	//看守NPC信息
	int npcIconId;
	char npcQuality;
	std::string npcName;
	int npcPrice;
public:
	SSRevoltInfo();
	void destroyData();
	void decodePacketData(cobra_win::DPacket & packet);
};

//奴隶主的待解救朋友
class SMSlaveFriend
{
public:
	int playerId;
	int iconId;
	char quality;
	std::string name;
	std::string owerName;//此好友主人的名字
	int owerBtlCapa;//此好友主任的战力
	void decodePacketData(cobra_win::DPacket & packet);
};

//奴隶主解救信息
class SMRescueInfo
{
public:
	char leftRescueTimes;//剩余解救次数
	std::vector<SMSlaveFriend *> slaveFriendVector;//我是待解救的好友
public:
	SMRescueInfo();
	~SMRescueInfo();
	void destroyData();//用于清空数据
	void decodePacketData(cobra_win::DPacket & packet);
};

//奴隶主交互信息中我的奴隶
class SMSlave
{
public:
	int playerId;
	int iconId;
	char quality;
	std::string name;
	short level;
	int workSeconds;		//干活时间,秒数
	int makeExp;			//产出经验
	int expPerMin;			//分钟产出经验，和奴隶等级有关
	int secondsCount;		//计算分钟增加经验时的计数值
	int chainCdLeftTime;	//调教冷却剩余时间, 秒数
	void decodePacketData(cobra_win::DPacket & packet);
};

//奴隶主交互信息
class SMPlayInfo
{
public:
	char leftPlayTimes;//剩余互动次数
	std::vector<SMSlave *> slaveVector;
	long long longTickBeginTime;//此数据是不用来读取的
	int secondsCount;//用于分钟计时
public:
	SMPlayInfo();
	~SMPlayInfo();
	void destroyData();//用于清空数据
	void decodePacketData(cobra_win::DPacket & packet);
};

//奴隶主抓捕界面的手下败将或者仇人列表单元
class SMFightedPlayer
{
public:
	int playerId;
	int iconId;
	char quality;
	std::string name;
	short level;
	char identity;//0自由，1奴隶主，2奴隶
	int catchCdLeftTime;	//抓捕冷却时间剩余时间

	void decodePacketData(cobra_win::DPacket & packet);
};

//奴隶主进入抓捕奴隶界面信息
class SMCatchInfo
{
public:
	char leftCatchTimes;//剩余抓捕数量
	std::vector<SMFightedPlayer *> losserVector;//手下败将列表
	std::vector<SMFightedPlayer *> winnerVector;//仇人列表
	long long longTickBeginTime;//此数据是不用来读取的
public:
	SMCatchInfo();
	~SMCatchInfo();
	void destroyData();//用于清空数据
	void decodePacketData(cobra_win::DPacket & packet);
};




/************************************************************************/
/* This is DataHandler                                                  */
/************************************************************************/

class ServantDataHandler : public IDataHandler, public cobra_win::Singleton2<ServantDataHandler>
{
public:
	enum{
		_PLAY_FUNC_RELEASE_ = 0,	//释放
		_PLAY_FUNC_CHAIN_	= 1,	//调教
		_PLAY_FUNC_PRESS_	= 2,	//压榨
	};
public:
	//奴隶主或者自由身状态信息
	SMCatchInfo * m_pSMCatchInfo;		//奴隶主进入抓捕信息//constructor
	SMPlayInfo * m_pSMPlayInfo;					//奴隶主互动信息
	SMRescueInfo * m_pSMRescueInfo;				//奴隶主解救信息
	
	//奴隶状态信息
	SSRevoltInfo * m_pSSRevoltInfo;				//奴隶进入反抗界面信息//constructor
	SSPlayInfo * m_pSSPlayInfo;					//奴隶互动信息
	SSSOSInfo * m_pSSSOSInfo;					//奴隶求助信息

	SNewsInfo * m_pSNewsInfo;					//新闻信息//constructor//持久的，不会接受重新生成，短线重连时需要destroy
	
	int m_iLastStayPage;//进入游戏前上一次所在页面
	bool m_iWillEnterAthletic;//标志仆从界面将要进入战斗

public:
	ServantDataHandler();
	virtual ~ServantDataHandler();

protected:

	virtual void handlePacket(IPacket* packet){};

	virtual void onDestroy();

	virtual bool init(){	return true;	};

public:
	/*
		战斗结束后判断状态以及需要显示的页面和功能
	*/
	void OnAthleticEnd(short stageId, bool iswin);

public:
	//界面进入抓捕奴隶
	void ToServerMasterEnterCatch();
	void ToClientMasterEnterCatchResult();

	//抓捕奴隶
	void ToServerMasterCatch(int playerId);

	//进入互动奴隶主界面
	void ToServerMasterEnterPlay();
	void ToClientMasterEnterPlayResult();

	//奴隶主互动
	void ToServerMasterPlay(char playType, char index);
	void ToClientMasterPlayResult(char playType, char index, int cdLeftTime);

	//奴隶主新闻来了
	void ToClientMasterNewsCome();

	//进入奴隶主解救
	void ToServerMasterEnterRescue();
	void ToClientMasterEnterRescueResult();

	//奴隶主解救玩家
	void ToServerMasterRescue(int playerId);

	//界面进入奴隶反抗
	void ToServerSlaveEnterRevolt();
	void ToClientSlaveEnterRevoltResult();

	//奴隶反抗
	void ToServerSlaveRevolt();

	//奴隶贿赂
	void ToServerSlaveBribe();
	void ToClientSlaveBribeResult();

	//进入奴隶互动界面
	void ToServerSlaveEnterPlay();
	void ToClientSlaveEnterPlayResult();

	//奴隶互动
	void ToServerSlavePlay();
	void ToClientSlavePlayResult();

	//奴隶新闻来了
	void ToClientSlaveNewsCome();

	//进入奴隶求救界面
	void ToServerSlaveEnterSOS();
	void ToClientSlaveEnterSOSResult();

	//奴隶求救好友
	void ToServerSlaveSos(int playerId);

};

#define SERVANTDATAHANDLER (ServantDataHandler::get_instance2())

#endif