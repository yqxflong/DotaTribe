#ifndef  _DOTATRIBE_S2CRESTROLESKILLSPACKET_H_
#define  _DOTATRIBE_S2CRESTROLESKILLSPACKET_H_
 
/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  服务器返回重置用户技能凹槽 
//date:   2013/09/17
///////////////////////////////////////////////// 

#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>

class   S2CRestRoleSkillsPacket : public IPacket
{ 
private:
	char m_head[2];
	int  m_len;
	unsigned short m_pn;
	
public:
	unsigned char  m_heroIndex;
	S2CRestRoleSkillsPacket(){};
	virtual ~S2CRestRoleSkillsPacket(){};

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
	 

	virtual  bool  readSkills(cobra_win::DPacket &packet);
	/*
		发送字节流
	*/
	virtual  void  Send(){};

};

class S2CRestRoleSkillsPacketFactory : public IPacketFactory
{
public:
	S2CRestRoleSkillsPacketFactory(){};
	virtual ~S2CRestRoleSkillsPacketFactory(){};

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
	void   OnFinishCallBackHandler(unsigned char index);
};
 
#endif

