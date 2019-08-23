#ifndef  _DOTATRIBE_C2SHEROSOULPACKT_H_
#define  _DOTATRIBE_C2SHEROSOULPACKT_H_
 
#include "IPacket.h"
#include "PacketFactory.h"
 
//////////////////////////////////////////////////////////////////////////
//  请求进入战魂激活 信息
//////////////////////////////////////////////////////////////////////////

class  C2SHeroSoulPacket : public IPacket
{ 
private:
	char  m_head[2];
	int   m_len;
	short m_pn; 
	int   m_nHeroUID; 
public:
	C2SHeroSoulPacket(int heroUID);
	virtual ~C2SHeroSoulPacket(){};

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
// 服务器返回 战魂激活信息
//////////////////////////////////////////////////////////////////////////

class S2CHeroSoulInfoPacket : public IPacket
{ 
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn; 
public:
	S2CHeroSoulInfoPacket(){};
	virtual ~S2CHeroSoulInfoPacket(){};

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

class S2CHeroSoulInfoPacketFactory : public IPacketFactory
{
public:
	S2CHeroSoulInfoPacketFactory(){};
	virtual ~S2CHeroSoulInfoPacketFactory(){}; 
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
// 请求挑战 战魂
//////////////////////////////////////////////////////////////////////////

class  C2SChallengeHeroSoul : public IPacket
{ 
private:
	char  m_head[2];
	int   m_len;
	short m_pn; 
	int   m_nSerial;;
	int   m_nHeroUID; 
public:
	C2SChallengeHeroSoul(int heroUID);
	virtual ~C2SChallengeHeroSoul(){};

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
// 请求激活 战魂
//////////////////////////////////////////////////////////////////////////
class  C2SActiveSoulePacket : public IPacket
{ 
private:
	char  m_head[2];
	int   m_len;
	short m_pn; 
	int   m_nHeroUID;  
public:
	C2SActiveSoulePacket(int heroUID);
	virtual ~C2SActiveSoulePacket(){}; 
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
// 服务器返回 激活 战魂后信息
////////////////////////////////////////////////////////////////////////// 

class S2CActiveHeroSoulPacket : public IPacket
{ 
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn; 
public:
	S2CActiveHeroSoulPacket(){};
	virtual ~S2CActiveHeroSoulPacket(){}; 
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

class S2CActiveHeroSoulPacketFactory : public IPacketFactory
{
public:
	S2CActiveHeroSoulPacketFactory(){};
	virtual ~S2CActiveHeroSoulPacketFactory(){}; 
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
 

