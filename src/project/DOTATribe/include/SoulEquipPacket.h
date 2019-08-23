#ifndef  _DOTATRIBE_SOULEQUIPPACKET_H_
#define  _DOTATRIBE_SOULEQUIPPACKET_H_ 
 
#include "IPacket.h"
#include "PacketFactory.h"
 
//////////////////////////////////////////////////////////////////////////
//  战魂开锁请求
//////////////////////////////////////////////////////////////////////////

class  C2SUnLockHeroSoulPacket : public IPacket
{ 
private:
	char  m_head[2];
	int   m_len;
	short m_pn; 
	char  m_uEquipIndex;
	unsigned char m_heroindex;
public:
	C2SUnLockHeroSoulPacket(char equipIndex,unsigned char heroindex);
	virtual ~C2SUnLockHeroSoulPacket(){}; 
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
// 服务器返回 解锁战魂索引
//////////////////////////////////////////////////////////////////////////

class S2CUnLockHeroSoulPacket : public IPacket
{ 
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn; 
public:
	S2CUnLockHeroSoulPacket(){};
	virtual ~S2CUnLockHeroSoulPacket(){};

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

class S2CUnLockHeroSoulPacketFactory : public IPacketFactory
{
public:
	S2CUnLockHeroSoulPacketFactory(){};
	virtual ~ S2CUnLockHeroSoulPacketFactory(){}; 
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

//////////////////////////////////////////////////////////////////////////
// 请求装备 战魂
//////////////////////////////////////////////////////////////////////////

class  C2SEquipHeroSoulPacket : public IPacket
{ 
private:
	char  m_head[2];
	int   m_len;
	short m_pn;  
	int   m_nHeroSoulBufferID; 
	unsigned char m_heroindex;
public:
	C2SEquipHeroSoulPacket(unsigned char heroindex,int heroSoulBufferID);
	virtual ~C2SEquipHeroSoulPacket(){};

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
//  服务器 装备战魂 返回
//////////////////////////////////////////////////////////////////////////
 
class S2CEquipHeroSoulPacket  : public IPacket
{ 
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn; 
public:
	S2CEquipHeroSoulPacket(){};
	virtual ~S2CEquipHeroSoulPacket(){};

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



class S2CEquipHeroSoulPacketFactory : public IPacketFactory
{
public:
	S2CEquipHeroSoulPacketFactory(){};
	virtual ~S2CEquipHeroSoulPacketFactory(){}; 
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

 
  
//////////////////////////////////////////////////////////////////////////
// 请求 卸载 战魂
//////////////////////////////////////////////////////////////////////////
class  C2SUnEquipHeroSoulPacket : public IPacket
{ 
private:
	char  m_head[2];
	int   m_len;
	short m_pn; 
	int   m_nHeroSoulBufferID;
	char  m_cEquipIndex;
	unsigned char m_HeroIndex;
public:
	C2SUnEquipHeroSoulPacket(unsigned char HeroIndex,int heroSoulBufferID,char equipIndex);
	virtual ~C2SUnEquipHeroSoulPacket(){}; 
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
// 服务器返回 卸载 英雄战魂
////////////////////////////////////////////////////////////////////////// 

class S2CUnEquipHeroSoulPacket : public IPacket
{ 
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn; 
public:
	S2CUnEquipHeroSoulPacket(){};
	virtual ~S2CUnEquipHeroSoulPacket(){}; 
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

class S2CUnEquipHeroSoulPacketFactory : public IPacketFactory
{
public:
	S2CUnEquipHeroSoulPacketFactory(){};
	virtual ~S2CUnEquipHeroSoulPacketFactory(){}; 
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