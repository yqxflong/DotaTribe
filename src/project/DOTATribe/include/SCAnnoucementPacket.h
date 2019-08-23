#ifndef _DOTATRIBE_SCANNOUNCEMENT_H_
#define  _DOTATRIBE_SCANNOUNCEMENT_H_

//公共数据包

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
		得到数据包类型
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		得到数据包长度
	*/
	virtual  unsigned  int  GetPacketLength(){return 0;}

public:
	/*
		读取字节流
	*/
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	/*
		发送字节流
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
		获得数据包类型
	*/
	virtual  unsigned  int  GetPacketType();

public:
	/*
		数据包处理操作
	*/
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

 

#endif

