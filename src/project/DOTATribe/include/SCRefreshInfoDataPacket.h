//Name��SCRrefreshInfoDataPacket
//Function��s->c �����������ͬ����Ϣ
//Author : ����

#ifndef  _DOTATRIBE_SCREFRESHINFODATAPACKET_H_
#define  _DOTATRIBE_SCREFRESHINFODATAPACKET_H_


#include "IPacket.h"
#include "PacketFactory.h"
#include <include/mem/DPacket.h>

/**

         * ͬ���������<br>

         * byte count ����<br>

         * for(count){<br>

         * byte type ����<br>

         * ����(�������Ͷ�ȡ)<br>

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

	void SetAttributeData(int attriIndex, cobra_win::DPacket & packet);
};

class SCRefreshInfoDataPacketFactory : public IPacketFactory
{
public:
	SCRefreshInfoDataPacketFactory(){};
	virtual ~SCRefreshInfoDataPacketFactory(){};

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
	//�㲥ˢ�½�����Ϣ
	void notifyUIRefreshAffterPacketDecoded(const SCRefreshInfoDataPacket& packet);

};


#endif

