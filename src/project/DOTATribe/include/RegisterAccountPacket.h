#ifndef  _PACKECT_REGISTERACCOUNT_H_
#define  _PACKECT_REGISTERACCOUNT_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>

class C2SRegisterAccountPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;

	unsigned short m_szuserName;
	std::string	m_userName;

	unsigned short m_szuserPassWord;
	std::string	m_userPassWord;
	unsigned short m_szuserConfirmPassWord;
	std::string	m_userConfirmPassWord;




public:
	C2SRegisterAccountPacket(std::string userName,std::string userPassWord,std::string userConfirmPassWord);
	virtual ~C2SRegisterAccountPacket(){};

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
class S2CRegisterAccountPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int serial_;




public:
	S2CRegisterAccountPacket();
	virtual ~S2CRegisterAccountPacket();
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

class S2CRegisterAccountPacketFactory : public IPacketFactory
{
public:
	S2CRegisterAccountPacketFactory();
	virtual ~S2CRegisterAccountPacketFactory();

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
	static   void  OnS2CRegisterAccountPacketHandler(S2CRegisterAccountPacket* pPacket);
};

#endif