#ifndef   _DOTATRIBE_CSHEROADVANCEPACKET_H_  
#define   _DOTATRIBE_CSHEROADVANCEPACKET_H_

/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  请求英雄进阶所需物品
//date:   2013/08/29
///////////////////////////////////////////////// 
#include "IPacket.h"
#include "PacketFactory.h"

class CSHeroAdvancedPacket : public IPacket
{ 
private:
	char  m_head[2];
	int   m_len;
	short m_pn;
	int   m_heroGroupId;
public:
	CSHeroAdvancedPacket(int heroGroupID);
	virtual ~CSHeroAdvancedPacket(){};

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


//////////////////////////////////////////////////////////////////////////
class SCHeroAdvancedPacket : public IPacket
{ 
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCHeroAdvancedPacket(){};
	virtual ~SCHeroAdvancedPacket(){};
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

class SCHeroAdvancedPacketFactory : public IPacketFactory
{
public:
	SCHeroAdvancedPacketFactory(){};
	virtual ~SCHeroAdvancedPacketFactory(){};
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
	 
	virtual  void  OnPostNotification();

}; 

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// 请求进阶英雄 验证

class CSHeroAdvanceVerifyPacket : public IPacket
{ 
private:
	char  m_head[2];
	int   m_len;
	short m_pn;
	int   m_heroGroupId;
public:
	CSHeroAdvanceVerifyPacket(int heroGroupID);
	virtual ~CSHeroAdvanceVerifyPacket(){};

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


//////////////////////////////////////////////////////////////////////////


class SCHeroAdvanceVerifyPacket : public IPacket
{ 
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCHeroAdvanceVerifyPacket(){};
	virtual ~SCHeroAdvanceVerifyPacket(){};
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

class SCHeroAdvanceVerifyPacketFactory : public IPacketFactory
{
public:
	SCHeroAdvanceVerifyPacketFactory(){};
	virtual ~SCHeroAdvanceVerifyPacketFactory(){};
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
	 
	virtual  void  OnPostNotification();

}; 
 

#endif