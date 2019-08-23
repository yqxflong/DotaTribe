//Name:PayGoodsPacket
//Function: 充值买物品的相关协议
//Author:lvyunlong
//Date:20131119

#ifndef _DOTATRIBE_PAYGOODSPACKET_H_
#define _DOTATRIBE_PAYGOODSPACKET_H_

#include <include/mem/DPacket.h> 
#include "IPacket.h"
#include "PacketFactory.h"
#include "../include/DotaPacket.h"
#include "../include/CPublicVarReader.h"
#include <iostream>


/************************************************************************/
/* 请求充值列表和返回	                                                    */
/************************************************************************/
class CSPayItemListPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	unsigned char m_ChannelId;
public:
	CSPayItemListPacket(unsigned char channel);
	virtual ~CSPayItemListPacket();

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


class SCPayItemListPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCPayItemListPacket(){};
	virtual ~SCPayItemListPacket(){};

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

class SCPayItemListPacketFactory : public IPacketFactory
{
public:
	SCPayItemListPacketFactory(){};
	virtual ~SCPayItemListPacketFactory(){};

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
/* 请求充值确认和充值确认结果返回											*/
/************************************************************************/
class CSPaySurePacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	unsigned char m_ChannelId;		//平台:  0:畅游  1:91平台  2:Appstore  3:SDk类型
	unsigned short sizegoodsiap;
	std::string m_striapid;			//见充值列表，由畅游billing分配 
	unsigned short sizeOrderld;
	std::string m_strOrderld;			//订单号，充值后第三方SDK返回给客户端
	unsigned short sizetransactReceipt;
	std::string m_strtransactReceipt;		//校验证书
public:
	CSPaySurePacket(unsigned char channel,std::string iapid,std::string orderld,std::string transactReceipt);
	virtual ~CSPaySurePacket();

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


class SCPaySurePacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCPaySurePacket(){};
	virtual ~SCPaySurePacket(){};

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

class SCPaySurePacketFactory : public IPacketFactory
{
public:
	SCPaySurePacketFactory(){};
	virtual ~SCPaySurePacketFactory(){};

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
/* Android专用购买时请求													*/
/************************************************************************/
class CSAndroidPayInfoPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSAndroidPayInfoPacket();
	virtual ~CSAndroidPayInfoPacket();
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


class SCAndroidPayInfoPacket : public IPacket
{

private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCAndroidPayInfoPacket(){};
	virtual ~SCAndroidPayInfoPacket(){};

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

class SCAndroidPayInfoPacketFactory : public IPacketFactory
{
public:
	SCAndroidPayInfoPacketFactory(){};
	virtual ~SCAndroidPayInfoPacketFactory(){};

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
/* 请求首充三档翻倍信息													*/
/************************************************************************/
class CSDoublePayInfoPacket : public DotaPacket
{
public:
	CSDoublePayInfoPacket(unsigned char channel);
	~CSDoublePayInfoPacket();
public:
	virtual  unsigned  int  GetPacketType();
};

class SCDoublePayInfoPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCDoublePayInfoPacket(){};
	virtual ~SCDoublePayInfoPacket(){};
public:
	virtual  unsigned  int  GetPacketType(){ return 1;};
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCSCDoublePayInfoPacketFactory : public IPacketFactory
{
public:
	SCSCDoublePayInfoPacketFactory(){};
	virtual ~SCSCDoublePayInfoPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};
#endif