#ifndef  _DOTATRIBE_C2SRESETROLESKILLS_PACKET_H_
#define  _DOTATRIBE_C2SRESETROLESKILLS_PACKET_H_

/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  请求重置技能
//date:   2013/08/29
///////////////////////////////////////////////// 

#include "IPacket.h"
#include "PacketFactory.h"

class C2SRestRoleSkillsPacket : public IPacket
{
 
private:
	char m_head[2];
	int  m_len;
	short m_pn; 
	unsigned char m_SkillIndex;
public:
	C2SRestRoleSkillsPacket(unsigned char index);
	virtual ~C2SRestRoleSkillsPacket(){};

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


#endif
