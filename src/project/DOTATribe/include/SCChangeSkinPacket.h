//Name：SCRoleInfoPacket
//Function：s->c 更换外套后，角色信息
//Written By：尹强

#ifndef  _DOTATRIBE_SCCHANGESKINPACKET_H_
#define  _DOTATRIBE_SCCHANGESKINPACKET_H_


#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>

class SCChangeSkinPacket : public IPacket
{
/*
* 失败 ['Z''R'][n][2006][int序列号][int -1][string failureInfo]
* 成功 ['Z''R'][n][2006][int序列号][int  1][int count]{[byte type][int attrvalue]}
*/
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int m_serial;
	int m_resultid;

public:
	SCChangeSkinPacket(){};
	virtual ~SCChangeSkinPacket(){};

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
private:
	inline void _readFailPacket(cobra_win::DPacket &packet);
	inline void _readSuccessPacket(cobra_win::DPacket &packet);
};

class SCChangeSkinPacketFactory : public IPacketFactory
{
public:
	SCChangeSkinPacketFactory(){};
	virtual ~SCChangeSkinPacketFactory(){};

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
	static   void  OnSCChangeSkinPacketHandler(SCChangeSkinPacket* pPacket);
};


#endif

