#ifndef _DOTATRIBE_SCANNOUNCEMENT_H_
#define  _DOTATRIBE_SCANNOUNCEMENT_H_

//�������ݰ�

#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>
 
class  SCAnnoucementPacket: public IPacket
{
public:
	char m_head[2];
	int  m_len;
	unsigned short m_pn;	 
public:
	SCAnnoucementPacket(){
	   m_len=0;
	   m_pn=0;
	   memset(m_head,0,sizeof(m_head));
	};
	virtual ~SCAnnoucementPacket(){};

public:
	/*
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketLength(){return 0;}

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


class  SCAnnoucementPacketFactory: public IPacketFactory
{
public:
	SCAnnoucementPacketFactory(){};
	virtual ~SCAnnoucementPacketFactory(){};
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

