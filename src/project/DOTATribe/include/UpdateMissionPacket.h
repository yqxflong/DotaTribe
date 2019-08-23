#ifndef  _PACKECT_UPDATEMISSION_H_
#define  _PACKECT_UPDATEMISSION_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

class C2SUpdateMissionPacket : public IPacket
{
	/*
		['Z''R'][n][1003][int���к�]
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

	 unsigned short mapId;									//ͨ�ص�ͼID
	 unsigned short stageId;								// ͨ�عؿ�ID
	 unsigned char  star;									//ͨ���Ǽ�<br>
	 unsigned short challengeTimes;							//ͨ�ش���<br>
	 unsigned char  hasNext;								//�Ƿ���Ҫ�·���һ����Ϣ
	 unsigned char  isOpenNewMap;							//�Ƿ����µ�ͼ 0�� 1��<br>
	 unsigned short openmapId;								//������ͼID<br>
	 unsigned short openstageId;							//�����ؿ�ID<br>

	
public:
	S2CUpdateMissionPacket();
	virtual ~S2CUpdateMissionPacket();

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
	virtual  void  Send();
};

class S2CUpdateMissionPacketFactory : public IPacketFactory
{
public:
	S2CUpdateMissionPacketFactory();
	virtual ~S2CUpdateMissionPacketFactory();

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

private:
	/*
		�߼����ݰ�����
	*/
	static   void  OnS2CUpdateMissionPacketHandler(S2CUpdateMissionPacket* pPacket);
};

#endif