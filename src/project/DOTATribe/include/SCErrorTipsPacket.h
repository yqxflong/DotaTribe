#ifndef  _DOTATRIBE_SCERRORTIPSPACKET_H_
#define  _DOTATRIBE_SCERRORTIPSPACKET_H_
 
#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>
#include <string>

class SCErrorTipsPacket : public IPacket
{ 
private:
	char m_head[2];
	int  m_len;
	unsigned short m_pn;
	std::string  m_smsg;
public:
	SCErrorTipsPacket(){
		m_smsg="";
	};
	virtual ~SCErrorTipsPacket(){};

public:
	/*
		得到数据包类型
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		得到数据包长度
	*/
	virtual  unsigned  int  GetPacketLength();

    /*
	获得推送信息
	*/
	std::string  &  GetServerMessage();

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

class SCErrorTipsPacketFactory : public IPacketFactory
{
public:
	SCErrorTipsPacketFactory(){};
	virtual ~SCErrorTipsPacketFactory(){};

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

protected:
	void    PostNotification(SCErrorTipsPacket &packet);
};
#endif

