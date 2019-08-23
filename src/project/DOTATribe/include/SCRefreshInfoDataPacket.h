//Name：SCRrefreshInfoDataPacket
//Function：s->c 被动与服务器同步信息
//Author : 方骏

#ifndef  _DOTATRIBE_SCREFRESHINFODATAPACKET_H_
#define  _DOTATRIBE_SCREFRESHINFODATAPACKET_H_


#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>

/**

         * 同步玩家数据<br>

         * byte count 数量<br>

         * for(count){<br>

         * byte type 类型<br>

         * 数据(根据类型读取)<br>

         * }<br>

         */
        //public static final short DATASYNC_SERVER = 1018;


class SCRefreshInfoDataPacket : public IPacket
{
public:
	bool needRefreshBagEquip_;
	bool needRefreshRoleEquip_;
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCRefreshInfoDataPacket():needRefreshBagEquip_(false),needRefreshRoleEquip_(false){};
	virtual ~SCRefreshInfoDataPacket(){};

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

	void SetAttributeData(int attriIndex, cobra_win::DPacket & packet);
};

class SCRefreshInfoDataPacketFactory : public IPacketFactory
{
public:
	SCRefreshInfoDataPacketFactory(){};
	virtual ~SCRefreshInfoDataPacketFactory(){};

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
	//广播刷新界面消息
	void notifyUIRefreshAffterPacketDecoded(const SCRefreshInfoDataPacket& packet);

};


#endif

