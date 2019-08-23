// Name :		NoticeGatewayPacket.h
// Function:	���ص�¼����������Ϣ��
// Author :		�۱�	
// Maintainer:  �۱� 


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
 * ��½���淵��<br>
 * byte styleCount;//��ʽ����
 * for(styleCount){
 *     int fontId; //��ʽ���
 *     int fontSize;//�����С
 *     String fontName;//��������
 *     String fontColor;//������ɫ
 * }
 * byte noticeCount;//��������
 * for(noticeCount){
 *     int titleStyleId;//�����ʽId
 *     String title;//��������
 *     int contentStyle;//�����ʽId
 *     String noticeContent;//��������
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
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketType();
	/*
		�õ����ݰ�����
	*/
	virtual  unsigned  int  GetPacketLength();

public:
		/*
		��ȡ�ֽ���
	*/
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	/*
		�����ֽ���
	*/
	virtual  void  Send(){};
};

class S2CNoticeGatewayPacketFactory: public IPacketFactory{
public:
	S2CNoticeGatewayPacketFactory(){};
	virtual ~S2CNoticeGatewayPacketFactory(){};

public:
	/*
		������ݰ�����
	*/
	virtual  unsigned  int  GetPacketType();

public:
	/*
		���ݰ��������
	*/
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};

#endif