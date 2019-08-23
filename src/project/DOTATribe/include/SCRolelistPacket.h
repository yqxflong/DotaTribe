//Name��SCRolelistPacket
//Function��s->c ��Ӧ��ɫ�б�
//Author : lvyunlong

#ifndef  _DOTATRIBE_SCROLELIST_H_
#define  _DOTATRIBE_SCROLELIST_H_


#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>
#include <vector>
#include <string>

class SCRolelistPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCRolelistPacket(){};
	virtual ~SCRolelistPacket(){};

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

};

class SCRolelistPacketFactory : public IPacketFactory
{
public:
	SCRolelistPacketFactory(){};
	virtual ~SCRolelistPacketFactory(){};

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

