//Name:HeroSummonPacket
//Function: 英雄召唤相关协议
//Author:lvyunlong
//Date:20131205

#ifndef _DOTATRIBE_HEROSUMMONPACKET_H_
#define _DOTATRIBE_HEROSUMMONPACKET_H_

#include <include/mem/DPacket.h> 
#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

/************************************************************************/
/* 请求进入英雄召唤信息		                                            */
/************************************************************************/
class CSHeroSummonInfoPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSHeroSummonInfoPacket();
	virtual ~CSHeroSummonInfoPacket();

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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	/*
		发送字节流
	*/
	virtual  void  Send();
};


class SCHeroSummonInfoPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCHeroSummonInfoPacket(){};
	virtual ~SCHeroSummonInfoPacket(){};

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
private:
	inline void _readInfo(cobra_win::DPacket &packet);

};

class SCHeroSummonInfoPacketFactory : public IPacketFactory
{
public:
	SCHeroSummonInfoPacketFactory(){};
	virtual ~SCHeroSummonInfoPacketFactory(){};

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
/* 请求进行英雄召唤														*/
/************************************************************************/
class CSHeroSoulSummonPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	unsigned char m_type;
	unsigned char m_times;
	unsigned char m_freetype;
public:
	CSHeroSoulSummonPacket(unsigned char type,unsigned char times,unsigned char freetype);
	virtual ~CSHeroSoulSummonPacket();

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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	/*
		发送字节流
	*/
	virtual  void  Send();
};


class SCHeroSoulSummonPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCHeroSoulSummonPacket(){};
	virtual ~SCHeroSoulSummonPacket(){};

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
private:
	inline void _readInfo(cobra_win::DPacket &packet);

};

class SCHeroSoulSummonPacketFactory : public IPacketFactory
{
public:
	SCHeroSoulSummonPacketFactory(){};
	virtual ~SCHeroSoulSummonPacketFactory(){};

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
/* 十连抽获得英雄														*/
/************************************************************************/
class SCTenCallPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCTenCallPacket(){};
	virtual ~SCTenCallPacket(){};

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
private:
	inline void _readInfo(cobra_win::DPacket &packet);

};

class SCSCTenCallPacketFactory : public IPacketFactory
{
public:
	SCSCTenCallPacketFactory(){};
	virtual ~SCSCTenCallPacketFactory(){};

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
/* 使用物品获得英雄														*/
/************************************************************************/
class SCUserItemGainHeroPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCUserItemGainHeroPacket(){};
	virtual ~SCUserItemGainHeroPacket(){};

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
private:
	inline void _readInfo(cobra_win::DPacket &packet);

};

class SCUserItemGainHeroPacketFactory : public IPacketFactory
{
public:
	SCUserItemGainHeroPacketFactory(){};
	virtual ~SCUserItemGainHeroPacketFactory(){};

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