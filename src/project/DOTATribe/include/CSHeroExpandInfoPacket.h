#ifndef  _DOTATRIBE_CSHEROEXPANDINFOPACKET_H_
#define  _DOTATRIBE_CSHEROEXPANDINFOPACKET_H_

/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  请求英雄外套信息
//date:   2013/08/29
///////////////////////////////////////////////// 
#include "DotaPacket.h"
#include "PacketFactory.h"

class CSHeroExpandInfoPacket : public IPacket
{ 
private:
	char  m_head[2];
	int   m_len;
	short m_pn;
	int   m_nHeroUniqueID;
public:
	CSHeroExpandInfoPacket(int heroUniqueID);
	virtual ~CSHeroExpandInfoPacket(){};

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



class SCHeroExpandInfoPacket : public IPacket
{ 
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCHeroExpandInfoPacket(){};
	virtual ~SCHeroExpandInfoPacket(){};

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

class SCHeroExpandInfoPacketFactory : public IPacketFactory
{
public:
	SCHeroExpandInfoPacketFactory(){};
	virtual ~SCHeroExpandInfoPacketFactory(){};

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
	 
	virtual  void  OnPostNotification(bool isSynSuccess);

}; 

//////////////////////////////////////////////////////////////////////////
//更换新的英雄 请求
 
class CSReplaceHeroRequestPacket : public DotaPacket
{ 
public:
	CSReplaceHeroRequestPacket(int heroUniqueID,unsigned char heroPos);
	virtual ~CSReplaceHeroRequestPacket(){};

public:
	virtual  unsigned  int  GetPacketType();
};

//////////////////////////////////////////////////////////////////////////
//更换英雄  回应

class SCReplaceHeroPacket : public IPacket
{ 
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCReplaceHeroPacket(){};
	virtual ~SCReplaceHeroPacket(){};

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


class SCReplaceHeroPacketFactory : public IPacketFactory
{
public:
	SCReplaceHeroPacketFactory(){};
	virtual ~SCReplaceHeroPacketFactory(){};

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
	 
	virtual  void  OnPostNotification(bool isSynSuccess);

}; 



#endif
