#ifndef  _DOTATRIBE_C2SAddChallengeCountPacket_H_
#define  _DOTATRIBE_C2SAddChallengeCountPacket_H_
 
/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  ��ȴʱ�����ݰ�
//date:   2013/08/30
///////////////////////////////////////////////// 

#include  "IPacket.h"
#include  "PacketFactory.h"
 
class C2SAddChallenegeCountPacket : public IPacket
{ 
private:
	char  m_head[2];
	int   m_len;
	short m_pn; 
public:
	C2SAddChallenegeCountPacket();
	virtual ~C2SAddChallenegeCountPacket(){};
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
 
#endif