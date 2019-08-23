//Name��ServerListPacket
//Function������������б�
//Written By����ǿ

#ifndef  _PACKECT_ServerListPacket_H_
#define  _PACKECT_ServerListPacket_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>
#include "../include/DotaPacket.h"

class CSServerListPacket :public DotaPacket
{
public:
	CSServerListPacket(unsigned char channelID,std::string version);
	virtual ~CSServerListPacket(){};

public:
	virtual  unsigned  int  GetPacketType();
};

class SCServerListPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCServerListPacket(){};
	virtual ~SCServerListPacket(){};

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
private:
	inline void _readServerInfo(cobra_win::DPacket &packet);

};

class SCServerListPacketFactory : public IPacketFactory
{
public:
	SCServerListPacketFactory(){};
	virtual ~SCServerListPacketFactory(){};

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
};

#endif