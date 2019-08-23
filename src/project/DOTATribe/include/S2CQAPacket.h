#ifndef  _DOTATRIBE_S2CQAPACKET_H_
#define  _DOTATRIBE_S2CQAPACKET_H_

/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  QAPacket
//date:   2013/09/05
///////////////////////////////////////////////// 


#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include "../include/AthleticProcedureDataHandler.h"
#include  "../include/AthleticProcedureDataType.h"
#include <include/mem/DPacket.h>
 
class  S2CQAPacket: public IPacket
{
public:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int m_serial;			//战斗序列号

public:
	S2CQAPacket(){
		m_serial=0;
	};
	virtual ~S2CQAPacket(){};

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

	bool   LoadQAData(cobra_win::DPacket & packet);
private:

 
};

//////////////////////////////////////////////////////////////////////////

class  S2CQAPacketFactory: public IPacketFactory
{
public:
	S2CQAPacketFactory(){};
	virtual ~S2CQAPacketFactory(){};

public:
	/*
		获得数据包类型
	*/
	virtual  unsigned  int  GetPacketType();

public:
	/*
		数据包处理操作
	*/
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);

private: 
	void OnFinishCallBackHandler();
};

 




#endif