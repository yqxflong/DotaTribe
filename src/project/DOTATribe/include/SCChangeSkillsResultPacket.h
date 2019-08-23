 #ifndef   _DOTATRIBE_SCCHANGESKILLSRESULT_H_
#define    _DOTATRIBE_SCCHANGESKILLSRESULT_H_

/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:    选择技能返回数据
//date:   2013/07/22
///////////////////////////////////////////////// 

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include "../include/RoleSkillsDataHandler.h"
#include <include/mem/DPacket.h>


 
class  SCChangeSkillsResultPacket: public IPacket
{
public:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	int m_serial;
    unsigned char m_heroIndex;
    
public:
	SCChangeSkillsResultPacket()
	{ 
	};
	virtual ~SCChangeSkillsResultPacket(){};

public:
	/*
		得到数据包类型
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		得到数据包长度
	*/
	virtual  unsigned  int  GetPacketLength();

 
	bool  CheckSkillsDataValid();

 
	std::vector<PSkillNotoch>  &  GetUserEquipSkillVec();


    bool  UpdateLocalSkillsData(cobra_win::DPacket & packetData);


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

};

//////////////////////////////////////////////////////////////////////////

class  SCChangeSkillsResultPacketFactory: public IPacketFactory
{
public:
	SCChangeSkillsResultPacketFactory(){};
	virtual ~SCChangeSkillsResultPacketFactory(){};

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
 
	virtual  void  PostNotification();
 
};

 
#endif