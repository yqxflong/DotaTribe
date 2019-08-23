//Name:HeroAltarPacket
//Function: 英雄献祭相关协议
//Author:lvyunlong
//Date:20131202

#ifndef _DOTATRIBE_HEROALTARPACKET_H_
#define _DOTATRIBE_HEROALTARPACKET_H_

#include <include/mem/DPacket.h> 
#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

/************************************************************************/
/* 请求祭坛信息		                                                    */
/************************************************************************/
class CSHeroTotemInfoPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSHeroTotemInfoPacket();
	virtual ~CSHeroTotemInfoPacket();

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


class SCHeroTotemInfoPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCHeroTotemInfoPacket(){};
	virtual ~SCHeroTotemInfoPacket(){};

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

class SCHeroTotemInfoPacketFactory : public IPacketFactory
{
public:
	SCHeroTotemInfoPacketFactory(){};
	virtual ~SCHeroTotemInfoPacketFactory(){};

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
/* 请求献祭信息和服务器返回献祭信息										*/
/************************************************************************/
class CSHeroAltarInfoPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSHeroAltarInfoPacket();
	virtual ~CSHeroAltarInfoPacket();

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


class SCHeroAltarInfoPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCHeroAltarInfoPacket(){};
	virtual ~SCHeroAltarInfoPacket(){};

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

class SCHeroAltarInfoPacketFactory : public IPacketFactory
{
public:
	SCHeroAltarInfoPacketFactory(){};
	virtual ~SCHeroAltarInfoPacketFactory(){};

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
/* 客户端发送献祭碎片信息和服务器返回碎片献祭结果信息						*/
/************************************************************************/
class CSHeroDebrisAltarPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	unsigned char m_type;
	unsigned char m_count;
public:
	CSHeroDebrisAltarPacket(unsigned char type,unsigned char count);
	virtual ~CSHeroDebrisAltarPacket();

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


class SCHeroDebrisAltarPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCHeroDebrisAltarPacket(){};
	virtual ~SCHeroDebrisAltarPacket(){};

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

class SCHeroDebrisAltarPacketFactory : public IPacketFactory
{
public:
	SCHeroDebrisAltarPacketFactory(){};
	virtual ~SCHeroDebrisAltarPacketFactory(){};

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
/* 请求献祭 每级最大经验的表/player/xianji.xlsx<br>						*/
/************************************************************************/
class CSAltarCheckInfoTablePacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSAltarCheckInfoTablePacket();
	virtual ~CSAltarCheckInfoTablePacket();

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


class SCAltarCheckInfoTablePacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCAltarCheckInfoTablePacket(){};
	virtual ~SCAltarCheckInfoTablePacket(){};

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

class SCAltarCheckInfoTablePacketFactory : public IPacketFactory
{
public:
	SCAltarCheckInfoTablePacketFactory(){};
	virtual ~SCAltarCheckInfoTablePacketFactory(){};

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