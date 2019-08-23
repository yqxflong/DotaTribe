#ifndef  _PACKECT_UPDATEMISSION_H_
#define  _PACKECT_UPDATEMISSION_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class C2SUpdateMissionPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int序列号]
	*/
private:
	char m_head[2];
	int  m_len;
	short m_pn;
    int m_serial;

public:
	C2SUpdateMissionPacket(int serialnum);
	virtual ~C2SUpdateMissionPacket(){};

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
class S2CUpdateMissionPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int serial_;

	 unsigned short mapId;									//通关地图ID
	 unsigned short stageId;								// 通关关卡ID
	 unsigned char  star;									//通关星级<br>
	 unsigned short challengeTimes;							//通关次数<br>
	 unsigned char  hasNext;								//是否需要下发下一关信息
	 unsigned char  isOpenNewMap;							//是否开启新地图 0否 1是<br>
	 unsigned short openmapId;								//开启地图ID<br>
	 unsigned short openstageId;							//开启关卡ID<br>

	
public:
	S2CUpdateMissionPacket();
	virtual ~S2CUpdateMissionPacket();

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

class S2CUpdateMissionPacketFactory : public IPacketFactory
{
public:
	S2CUpdateMissionPacketFactory();
	virtual ~S2CUpdateMissionPacketFactory();

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
	static   void  OnS2CUpdateMissionPacketHandler(S2CUpdateMissionPacket* pPacket);
};

#endif