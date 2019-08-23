#ifndef  _DOTATRIBE_S2CARENARANKPACKET_H_
#define  _DOTATRIBE_S2CARENARANKPACKET_H_
 
#include "../include/PacketTyper.h"
#include <include/mem/DPacket.h> 
#include "../include/LoggerSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
using namespace cobra_win;

/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  ���������ؾ��������а�����
//date:   2013/08/29
///////////////////////////////////////////////// 
 
#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>
 

class S2CArenaRankPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int serial;

public:
	S2CArenaRankPacket(){};
	virtual ~S2CArenaRankPacket(){};
public:
	/*
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketLength();

public:
	/*
		��ȡ�ֽ���
	*/
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	/*
		�����ֽ���
	*/
	virtual  void  Send(){}; 

	bool	 LoadArenaRankData(cobra_win::DPacket & packetData);

};

class S2CArenaRankPacketFactory : public IPacketFactory
{
public:
	S2CArenaRankPacketFactory(){};
	virtual ~S2CArenaRankPacketFactory(){};

public:
	/*
		������ݰ�����
	*/
	virtual  unsigned  int  GetPacketType();

public:
	/*
		���ݰ��������
	*/
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);


	void   PostShowRankWindowNotification();
};

 

#endif


