//Name:EquipTrainPacket
//Function: 属性锁定包
//Author:fangjun
//Date:20130821

#ifndef _DOTATRIBE_EQUIPTRAINPACKET_H_
#define _DOTATRIBE_EQUIPTRAINPACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

/************************************************************************/
/* 获取装备的所有锁状态                                                                     */
/************************************************************************/
class CSEquipTrainGetLockStatus : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int equipId;
public:
	CSEquipTrainGetLockStatus(int eqid);
	virtual ~CSEquipTrainGetLockStatus();

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
class SCEquipTrainGetLockStatusResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCEquipTrainGetLockStatusResultPacket();
	virtual ~SCEquipTrainGetLockStatusResultPacket();
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

class SCEquipTrainGetLockStatusResultPacketFactory : public IPacketFactory
{
public:
	SCEquipTrainGetLockStatusResultPacketFactory();
	virtual ~SCEquipTrainGetLockStatusResultPacketFactory();

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



/************************************************************************/
/* 洗练                                                                     */
/************************************************************************/


class CSEquipTrainPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int equipId;

public:
	CSEquipTrainPacket(int eqid);
	virtual ~CSEquipTrainPacket();

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


class SCEquipTrainResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCEquipTrainResultPacket();
	virtual ~SCEquipTrainResultPacket();
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

class SCEquipTrainResultPacketFactory : public IPacketFactory
{
public:
	SCEquipTrainResultPacketFactory();
	virtual ~SCEquipTrainResultPacketFactory();

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