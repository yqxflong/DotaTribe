#ifndef  _DOTATRIBE_S2CARENAGIGPACKET_H_
#define  _DOTATRIBE_S2CARENAGIGPACKET_H_
 
#include "../include/PacketTyper.h"
#include <include/mem/DPacket.h> 
#include "../include/LoggerSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
using namespace cobra_win;

/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  ���������ؾ��������
//date:   2013/08/29
///////////////////////////////////////////////// 
 
#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>
 
class S2CArenaGifPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	S2CArenaGifPacket(){};
	virtual ~S2CArenaGifPacket(){};
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


	bool	 LoadArenaGifData(cobra_win::DPacket & packetData);

};

class S2CArenaGifPacketFactory : public IPacketFactory
{
public:
	S2CArenaGifPacketFactory(){};
	virtual ~S2CArenaGifPacketFactory(){};

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


	void   PostNotification();
};

 

#endif


