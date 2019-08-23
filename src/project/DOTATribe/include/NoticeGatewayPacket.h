// Name :		NoticeGatewayPacket.h
// Function:	网关登录公告数据消息包
// Author :		邵兵	
// Maintainer:  邵兵 


#ifndef  _PACKECT_NOTICEGATEWAY_H_
#define  _PACKECT_NOTICEGATEWAY_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include "../include/DotaPacket.h"
#include <iostream>
#include <vector>
#include <string>

class C2SNoticeGatewayPacket: public DotaPacket{

public:
	C2SNoticeGatewayPacket();
	~C2SNoticeGatewayPacket();
public:
	virtual unsigned int GetPacketType();
public:
};


/**
 * <pre>
 * 登陆公告返回<br>
 * byte styleCount;//格式个数
 * for(styleCount){
 *     int fontId; //格式编号
 *     int fontSize;//字体大小
 *     String fontName;//字体名称
 *     String fontColor;//字体颜色
 * }
 * byte noticeCount;//公告数量
 * for(noticeCount){
 *     int titleStyleId;//标题格式Id
 *     String title;//标题文字
 *     int contentStyle;//公告格式Id
 *     String noticeContent;//公告文字
 * }
 * </pre>
 */

class S2CNoticeGatewayPacket: public IPacket{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	S2CNoticeGatewayPacket(){};
	virtual ~S2CNoticeGatewayPacket(){};
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

class S2CNoticeGatewayPacketFactory: public IPacketFactory{
public:
	S2CNoticeGatewayPacketFactory(){};
	virtual ~S2CNoticeGatewayPacketFactory(){};

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