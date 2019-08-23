//Name：VersionCheckPacket
//Function：版本检查包
//Written By：尹强

#ifndef _DOTATRIBE_VersionCheckPacket_H_
#define _DOTATRIBE_VersionCheckPacket_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include "../include/DotaPacket.h"
#include <string>

/************************************************************************/
/*获取版本信息	 			                                                                    */
/************************************************************************/
class CSQueryVersionPacket : public DotaPacket
{
public:
	CSQueryVersionPacket(std::string myVersion);
	virtual ~CSQueryVersionPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
};


/*
	接收版本信息
*/
class SCQueryVersionPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCQueryVersionPacket(){};
	virtual ~SCQueryVersionPacket(){};
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

class SCQueryVersionPacketFactory : public IPacketFactory
{
public:
	SCQueryVersionPacketFactory(){};
	virtual ~SCQueryVersionPacketFactory(){};

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