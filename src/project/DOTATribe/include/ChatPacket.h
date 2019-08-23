// Name :		ChatPacket.h
// Function:	聊天消息包
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
		['Z''R'][n][1003][int序列号]
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
class S2CChatPacket : public IPacket
{
	enum
	{
		_CHAR_DATA_UNKONW_TYPE_=-1,	   //未知数据类型
		_CHAR_DATA_WORLD_TYPE_,		   //世界数据
		_CHAR_DATA_PERSION_TYPE_,	   //私聊数据
		_CHAR_DATA_SYSTEM_TYPE_,	   //系统数据
		_CHAR_DATA_ANNOUNCEMENT_TYPE_, //公告数据  //暂无此类型 
	};
private:
	char				m_head[2];		 //协议头
	int					m_len;			 //数据长度
	unsigned short		m_pn;			 //协议ID
	char				m_dataType;		 //数据类型
	//AnnoucementMemData  m_annouceData;   //公告数据  delete by xiaobo.wu
public:
	S2CChatPacket();
	virtual ~S2CChatPacket();
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

class S2CChatPacketFactory : public IPacketFactory
{
public:
	S2CChatPacketFactory();
	virtual ~S2CChatPacketFactory();

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
	static   void  OnS2CChatPacketHandler(S2CChatPacket* pPacket);
};

#endif