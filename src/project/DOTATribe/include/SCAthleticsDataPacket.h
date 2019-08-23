//Name：SCAthleticsDataPacket
//Function：返回战斗数据
//Author:	Johny

#ifndef   _DOTATRIBE_SCATHLETICSDATAPACKET_H_
#define   _DOTATRIBE_SCATHLETICSDATAPACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include "../include/AthleticProcedureDataHandler.h"
#include  "../include/AthleticProcedureDataType.h"
#include <include/mem/DPacket.h>

#define  FOR_EACH_ATHLETICSUNIT_BEGIN(athleticsCount)    for(short athleticsIndex=0;athleticsIndex<athleticsCount;athleticsIndex++) {

#define  FOR_EACH_ATHLETICSUNIT_END						  }


class  SCAthleticsDataPacket: public IPacket
{
public:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int m_serial;			//战斗序列号

public:
	SCAthleticsDataPacket(){
		m_serial=0;
	};
	virtual ~SCAthleticsDataPacket(){};

public:
	/*
		得到数据包类型
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		得到数据包长度
	*/
	virtual  unsigned  int  GetPacketLength();

public:
	/*
		读取字节流
	*/
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	/*
		发送字节流
	*/
	virtual  void  Send(){};
private:

	/*
	 进入数据包解析流程
	*/
    bool   LoadAthleticsData(cobra_win::DPacket & packetData);

	/*
	进入缓存替换解析流程
	*/
	bool   CheckLoadLocalAthleticsData();
 
};

//////////////////////////////////////////////////////////////////////////

class  SCAthleticsDataPacketFactory: public IPacketFactory
{
public:
	SCAthleticsDataPacketFactory(){};
	virtual ~SCAthleticsDataPacketFactory(){};

public:
	/*
		获得数据包类型
	*/
	virtual  unsigned  int  GetPacketType();

	/*
	判断当前流程是否为战斗流程
	*/
	bool		IsCurAthleticsProcedure();
public:
	/*
		数据包处理操作
	*/
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);

private:
	void   OnLoadDataFinishCallBackHandler();
};

 



#endif