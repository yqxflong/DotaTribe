//Name��SCServerMessagePacket
//Function��s->c ��������Ϣ
//Author : ����

#ifndef  _DOTATRIBE_SCSERVERMESSAGEPACKET_H_
#define  _DOTATRIBE_SCSERVERMESSAGEPACKET_H_


#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>



class SCServerMessagePacket : public IPacket
{
public:
	std::string strMessage_;
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCServerMessagePacket(){};
	virtual ~SCServerMessagePacket(){};

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

class SCServerMessagePacketFactory : public IPacketFactory
{
public:
	SCServerMessagePacketFactory(){};
	virtual ~SCServerMessagePacketFactory(){};

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

