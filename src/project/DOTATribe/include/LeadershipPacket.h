//Name:LeadershipPacket
//Function: ���������
//Author:��ǿ

#ifndef _DOTATRIBE_LeadershipPacket_H_
#define _DOTATRIBE_LeadershipPacket_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>


/************************************************************************/
/*=====================ͳ������������=================
/************************************************************************/
class CSLeadershipLvupPacket : public IPacket
{
public:
	CSLeadershipLvupPacket();
	virtual ~CSLeadershipLvupPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

class SCLeadershipLvupPacket : public IPacket
{
public:
	SCLeadershipLvupPacket(){};
	virtual ~SCLeadershipLvupPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCLeadershipLvupPacketFactory : public IPacketFactory
{
public:
	SCLeadershipLvupPacketFactory(){};
	virtual ~SCLeadershipLvupPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

#endif