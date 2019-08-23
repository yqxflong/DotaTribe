#ifndef  _PACKECT_REGISTERACCOUNT_H_
#define  _PACKECT_REGISTERACCOUNT_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>

class C2SRegisterAccountPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int���к�]
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
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketLength();

public:
	/*
		��ȡ�ֽ���
	*/
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	/*
		�����ֽ���
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
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketLength();

public:
	/*
		��ȡ�ֽ���
	*/
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	/*
		�����ֽ���
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
		������ݰ�����
	*/
	virtual  unsigned  int  GetPacketType();

public:
	/*
		���ݰ��������
	*/
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);

private:
	/*
		�߼����ݰ�����
	*/
	static   void  OnS2CRegisterAccountPacketHandler(S2CRegisterAccountPacket* pPacket);
};

#endif