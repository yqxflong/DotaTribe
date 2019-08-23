// Name :		ChatPacket.h
// Function:	������Ϣ��
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _PACKECT_CHAT_H_
#define  _PACKECT_CHAT_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include <vector>
#include <string>

class C2SChatPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int���к�]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	unsigned char m_type;
	int m_id;
	unsigned short m_sztext;
	std::string m_text;




public:
	C2SChatPacket(int type,int id,std::string text);
	virtual ~C2SChatPacket(){};

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
class S2CChatPacket : public IPacket
{
	enum
	{
		_CHAR_DATA_UNKONW_TYPE_=-1,	   //δ֪��������
		_CHAR_DATA_WORLD_TYPE_,		   //��������
		_CHAR_DATA_PERSION_TYPE_,	   //˽������
		_CHAR_DATA_SYSTEM_TYPE_,	   //ϵͳ����
		_CHAR_DATA_ANNOUNCEMENT_TYPE_, //��������  //���޴����� 
	};
private:
	char				m_head[2];		 //Э��ͷ
	int					m_len;			 //���ݳ���
	unsigned short		m_pn;			 //Э��ID
	char				m_dataType;		 //��������
	//AnnoucementMemData  m_annouceData;   //��������  delete by xiaobo.wu
public:
	S2CChatPacket();
	virtual ~S2CChatPacket();
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

class S2CChatPacketFactory : public IPacketFactory
{
public:
	S2CChatPacketFactory();
	virtual ~S2CChatPacketFactory();

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
	static   void  OnS2CChatPacketHandler(S2CChatPacket* pPacket);
};

#endif