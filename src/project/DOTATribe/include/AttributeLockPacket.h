//Name:AttributeLockPacket
//Function: 属性锁定包
//Author:fangjun
//Date:20130821

#ifndef _DOTATRIBE_ATTRIBUTELOCKPACKET_H_
#define _DOTATRIBE_ATTRIBUTELOCKPACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class CSAttributeLockPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int serial;
	int equipId;
	int attriIndex;

public:
	CSAttributeLockPacket(int serial, int eqid, unsigned char attriIndex);
	virtual ~CSAttributeLockPacket();

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
	virtual  void  Send();
};



class SCAttributeLockResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;


public:
	SCAttributeLockResultPacket();
	virtual ~SCAttributeLockResultPacket();
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
	virtual  void  Send();
};

class SCAttributeLockResultPacketFactory : public IPacketFactory
{
public:
	SCAttributeLockResultPacketFactory();
	virtual ~SCAttributeLockResultPacketFactory();

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



class CSAttributeUnLockPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int serial;
	int equipId;
	unsigned char attriIndex;

public:
	CSAttributeUnLockPacket(int s, int eid, int index);

	virtual ~CSAttributeUnLockPacket();

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
	virtual  void  Send();
};



class SCAttributeUnLockResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;


public:
	SCAttributeUnLockResultPacket();
	virtual ~SCAttributeUnLockResultPacket();
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
	virtual  void  Send();
};

class SCAttributeUnLockResultPacketFactory : public IPacketFactory
{
public:
	SCAttributeUnLockResultPacketFactory();
	virtual ~SCAttributeUnLockResultPacketFactory();

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