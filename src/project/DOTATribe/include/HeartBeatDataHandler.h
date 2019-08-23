//Name:HeartBeatDataHandler
//Function:心跳包，用于检测客户端是否断开连接
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
	int m_iNoReplyCount;	//无回复统计
	bool m_bLost;			//是否掉线

	int m_iTickCount;		//Tick记时count

	const int CHECK_TICKCOUNT;//间隔多少TIck发送心跳包
	const int NOREPLY_COUNT_MAX;//最大无回复数，超过关闭本地socket

	bool m_bTickReplyFlag;	//心跳包回复的标志，一旦回复置为true，下次发送时检测此标志位，如果为false则默认上次未收到回复

public:
	HeartBeatDataHandler();
	virtual ~HeartBeatDataHandler();
	
	int getNoReplyCount();
	void setNoReplyCount(int count);

	void doTickCheckLogic();//NetSystem的Tick中做这个事件

	bool isLost();//是否掉线
	void setLostStatus(bool	status);//设置掉线状态

	void resetAllCount();	//重置所有心跳状态

	void ToServerChickOnline();

public:
	void decodePacketData(cobra_win::DPacket & packet);

	
	virtual void handlePacket(IPacket* packet){};

	virtual void onDestroy(){};

	virtual bool init(){	return true;	};

};

#define HEARTBEATDATAHANDLER (HeartBeatDataHandler::get_instance2())

#endif