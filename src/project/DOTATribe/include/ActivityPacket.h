// Name :		ActivityPacket.h
// Function:	活动数据消息包
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_ACTIVITY_H_
#define  _PACKECT_ACTIVITY_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>
#include <string>

class C2SActivityPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	unsigned short m_type;

public:
	C2SActivityPacket();
	virtual ~C2SActivityPacket(){};

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



//S2C
class S2CActivityPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;



public:
	S2CActivityPacket();
	virtual ~S2CActivityPacket();
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

class S2CActivityPacketFactory : public IPacketFactory
{
public:
	S2CActivityPacketFactory();
	virtual ~S2CActivityPacketFactory();

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

private:
	/*
		逻辑数据包处理
	*/
	static   void  OnS2CActivityPacketHandler(S2CActivityPacket* pPacket);
};


/************************************************************************/
/*====================选择活动=================
/************************************************************************/
class C2SChioseActivityPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_index;

public:
	C2SChioseActivityPacket(int index);
	virtual ~C2SChioseActivityPacket(){};

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

/************************************************************************/
/*=====================泡温泉=================
/************************************************************************/
class C2SInSpringPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_index;
public:
	C2SInSpringPacket();
	virtual ~C2SInSpringPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send();
};

//S2C
class S2CInSpringPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;



public:
	S2CInSpringPacket();
	virtual ~S2CInSpringPacket();
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

class S2CInSpringPacketFactory : public IPacketFactory
{
public:
	S2CInSpringPacketFactory();
	virtual ~S2CInSpringPacketFactory();

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

private:
	/*
		逻辑数据包处理
	*/
	static   void  OnS2CInSpringPacketHandler(S2CInSpringPacket* pPacket);
};

/************************************************************************/
/* 领取温泉奖励返回                                                      */
/************************************************************************/
class S2CSpringRewardPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn; 
public:
	S2CSpringRewardPacket();
	virtual ~S2CSpringRewardPacket();
public:
	/*
		得到数据包类型
	*/
	virtual  unsigned  int  GetPacketType(){return 1;}
	/*
		得到数据包长度
	*/
	virtual  unsigned  int  GetPacketLength(){return 1;}

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
 
class S2CSpringRewardPacketFactory : public IPacketFactory
{
public:
	S2CSpringRewardPacketFactory();
	virtual ~S2CSpringRewardPacketFactory();

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
/*====================升级奖励=================
/************************************************************************/
  
//S2C
class S2CLevelUpRewardInfoPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn; 
public:
	S2CLevelUpRewardInfoPacket();
	virtual ~S2CLevelUpRewardInfoPacket();
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
 
class S2CLevelUpRewardInfoPacketFactory : public IPacketFactory
{
public:
	S2CLevelUpRewardInfoPacketFactory();
	virtual ~S2CLevelUpRewardInfoPacketFactory();

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

private: 
	/*
	  事件通知
	*/
	void  S2CPacketNotification();
};

//请求领取升级奖励
class  C2SGetLevelUpRewardPacket : public IPacket
{
private:
	char  m_head[2];
	int   m_len;
	short m_pn;
	int	  m_nRewardLevel;
public:
	C2SGetLevelUpRewardPacket(int rewardLevel);
	virtual ~C2SGetLevelUpRewardPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send();
};
 
//S2C
class  S2CLevelUpRewardRecepitPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn; 
public:
	S2CLevelUpRewardRecepitPacket();
	virtual ~S2CLevelUpRewardRecepitPacket();
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


class S2CLevelUpRewardRecepitPacketFactory : public IPacketFactory
{
public:
	S2CLevelUpRewardRecepitPacketFactory();
	virtual ~S2CLevelUpRewardRecepitPacketFactory();

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

private: 
	/*
	  事件通知
	*/
	void  S2CPacketNotification();
};

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// 兑换活动数据包
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// 返回申请数据包
////////////////////////////////////////////////////////////////////////// 
//S2C
class  S2CExchangeInfoPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn; 
public:
	S2CExchangeInfoPacket();
	virtual ~S2CExchangeInfoPacket();
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


class S2CExchangeInfoPacketFactory : public IPacketFactory
{
public:
	S2CExchangeInfoPacketFactory();
	virtual ~S2CExchangeInfoPacketFactory();

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

private: 
	/*
	  事件通知
	*/
	void  S2CPacketNotification();
};

//////////////////////////////////////////////////////////////////////////
//     客户端发起兑换请求
//////////////////////////////////////////////////////////////////////////
class  C2SExchangeExchangePacket : public IPacket
{
private:
	char  m_head[2];
	int   m_len;
	short m_pn;
	short m_nActivityID;
	short m_nExchangeID;
public:
	C2SExchangeExchangePacket(short activityID,short exchangeID);
	virtual ~C2SExchangeExchangePacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send();
};
 
//////////////////////////////////////////////////////////////////////////
//     服务器返回成功兑换回执
//////////////////////////////////////////////////////////////////////////

//S2C
class  S2CExchangeExchangePacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn; 
public:
	S2CExchangeExchangePacket();
	virtual ~S2CExchangeExchangePacket();
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


class S2CExchangeExchangePacketFactory : public IPacketFactory
{
public:
	S2CExchangeExchangePacketFactory();
	virtual ~S2CExchangeExchangePacketFactory();

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

private: 
	/*
	  事件通知
	*/
	void  S2CPacketNotification();
}; 

#endif
