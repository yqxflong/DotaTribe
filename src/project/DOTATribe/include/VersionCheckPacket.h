//Name��VersionCheckPacket
//Function���汾����
//Written By����ǿ

#ifndef _DOTATRIBE_VersionCheckPacket_H_
#define _DOTATRIBE_VersionCheckPacket_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include "../include/DotaPacket.h"
#include <string>

/************************************************************************/
/*��ȡ�汾��Ϣ	 			                                                                    */
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
	���հ汾��Ϣ
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

class SCQueryVersionPacketFactory : public IPacketFactory
{
public:
	SCQueryVersionPacketFactory(){};
	virtual ~SCQueryVersionPacketFactory(){};

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