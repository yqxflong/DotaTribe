//Name：SCServerMessagePacket
//Function：s->c 服务器信息
//Author : 方骏

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
};

class SCServerMessagePacketFactory : public IPacketFactory
{
public:
	SCServerMessagePacketFactory(){};
	virtual ~SCServerMessagePacketFactory(){};

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

