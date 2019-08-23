//Name:ServantPacket
//Function: �ʹ�ϵͳ��
//Author:����
//Date:20131015

#ifndef _DOTATRIBE_SERVANTPACKET_H_
#define _DOTATRIBE_SERVANTPACKET_H_

#include "IPacket.h"
#include "PacketFactory.h"
#include <iostream>

/************************************************************************/
/* ū����ץ��     2113                                                      */
/************************************************************************/
class CSMasterCatchPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_serialId;
	int m_iPlayerId;
public:
	CSMasterCatchPacket(int serialId, int playerId);
	virtual ~CSMasterCatchPacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

/************************************************************************/
/* ū��������ץ��        2115,2116                                           */
/************************************************************************/
class CSMasterEnterCatchPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSMasterEnterCatchPacket();
	virtual ~CSMasterEnterCatchPacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

class SCMasterEnterCatchResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCMasterEnterCatchResultPacket(){};
	virtual ~SCMasterEnterCatchResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCMasterEnterCatchResultPacketFactory : public IPacketFactory
{
public:
	SCMasterEnterCatchResultPacketFactory(){};
	virtual ~SCMasterEnterCatchResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


/************************************************************************/
/* ū�������뻥��      2117,2118                                                 */
/************************************************************************/
class CSMasterEnterPlayPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSMasterEnterPlayPacket();
	virtual ~CSMasterEnterPlayPacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

class SCMasterEnterPlayResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCMasterEnterPlayResultPacket(){};
	virtual ~SCMasterEnterPlayResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCMasterEnterPlayResultPacketFactory : public IPacketFactory
{
public:
	SCMasterEnterPlayResultPacketFactory(){};
	virtual ~SCMasterEnterPlayResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


/************************************************************************/
/* ū��������      2119,2120                                                 */
/************************************************************************/
class CSMasterPlayPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	char m_cType;//�������ͣ�0�ͷţ�1���̣�2ѹե
	char m_cIndex;//ū������λ��
public:
	CSMasterPlayPacket(char type, char index);
	virtual ~CSMasterPlayPacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

class SCMasterPlayResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCMasterPlayResultPacket(){};
	virtual ~SCMasterPlayResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCMasterPlayResultPacketFactory : public IPacketFactory
{
public:
	SCMasterPlayResultPacketFactory(){};
	virtual ~SCMasterPlayResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


/************************************************************************/
/* ū������������      2122                                                 */
/************************************************************************/
class SCMasterNewsPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCMasterNewsPacket(){};
	virtual ~SCMasterNewsPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCMasterNewsPacketFactory : public IPacketFactory
{
public:
	SCMasterNewsPacketFactory(){};
	virtual ~SCMasterNewsPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


/************************************************************************/
/* ū����������      2123,2124                                            */
/************************************************************************/
class CSMasterEnterRescuePacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSMasterEnterRescuePacket();
	virtual ~CSMasterEnterRescuePacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

class SCMasterEnterRescueResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCMasterEnterRescueResultPacket(){};
	virtual ~SCMasterEnterRescueResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCMasterEnterRescueResultPacketFactory : public IPacketFactory
{
public:
	SCMasterEnterRescueResultPacketFactory(){};
	virtual ~SCMasterEnterRescueResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


/************************************************************************/
/* ū������Ⱥ���      2125                                          */
/************************************************************************/
class CSMasterRescuePacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_serialId;
	int m_iPlayerId;
public:
	CSMasterRescuePacket(int serialId, int playerId);
	virtual ~CSMasterRescuePacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};


/************************************************************************/
/* ū�����뷴��      2127,2128                                            */
/************************************************************************/
class CSSlaveEnterRevoltPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSSlaveEnterRevoltPacket();
	virtual ~CSSlaveEnterRevoltPacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

class SCSlaveEnterRevoltResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCSlaveEnterRevoltResultPacket(){};
	virtual ~SCSlaveEnterRevoltResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCSlaveEnterRevoltResultPacketFactory : public IPacketFactory
{
public:
	SCSlaveEnterRevoltResultPacketFactory(){};
	virtual ~SCSlaveEnterRevoltResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


/************************************************************************/
/* ū����¸      2129,2130                                            */
/************************************************************************/
class CSSlaveBribePacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSSlaveBribePacket();
	virtual ~CSSlaveBribePacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

class SCSlaveBribeResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCSlaveBribeResultPacket(){};
	virtual ~SCSlaveBribeResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCSlaveBribeResultPacketFactory : public IPacketFactory
{
public:
	SCSlaveBribeResultPacketFactory(){};
	virtual ~SCSlaveBribeResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


/************************************************************************/
/* ū������      2131	                                            */
/************************************************************************/
class CSSlaveRevoltPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_serialId;
public:
	CSSlaveRevoltPacket(int serialId);
	virtual ~CSSlaveRevoltPacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};


/************************************************************************/
/* ū�����뻥��      2141,2142                                            */
/************************************************************************/
class CSSlaveEnterPlayPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSSlaveEnterPlayPacket();
	virtual ~CSSlaveEnterPlayPacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

class SCSlaveEnterPlayResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCSlaveEnterPlayResultPacket(){};
	virtual ~SCSlaveEnterPlayResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCSlaveEnterPlayResultPacketFactory : public IPacketFactory
{
public:
	SCSlaveEnterPlayResultPacketFactory(){};
	virtual ~SCSlaveEnterPlayResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


/************************************************************************/
/* ū������      2133,2134                                            */
/************************************************************************/
class CSSlavePlayPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSSlavePlayPacket();
	virtual ~CSSlavePlayPacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

class SCSlavePlayResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCSlavePlayResultPacket(){};
	virtual ~SCSlavePlayResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCSlavePlayResultPacketFactory : public IPacketFactory
{
public:
	SCSlavePlayResultPacketFactory(){};
	virtual ~SCSlavePlayResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


/************************************************************************/
/* ū����������      2136		                                        */
/************************************************************************/
class SCSlaveNewsPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCSlaveNewsPacket(){};
	virtual ~SCSlaveNewsPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCSlaveNewsPacketFactory : public IPacketFactory
{
public:
	SCSlaveNewsPacketFactory(){};
	virtual ~SCSlaveNewsPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


/************************************************************************/
/* ū���������      2137,2138                                            */
/************************************************************************/
class CSSlaveEnterSOSPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSSlaveEnterSOSPacket();
	virtual ~CSSlaveEnterSOSPacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};

class SCSlaveEnterSOSResultPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCSlaveEnterSOSResultPacket(){};
	virtual ~SCSlaveEnterSOSResultPacket(){};
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength(){return 1;};
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen);
	virtual  void  Send(){};
};

class SCSlaveEnterSOSResultPacketFactory : public IPacketFactory
{
public:
	SCSlaveEnterSOSResultPacketFactory(){};
	virtual ~SCSlaveEnterSOSResultPacketFactory(){};
public:
	virtual  unsigned  int  GetPacketType();
public:
	virtual  bool  OnPacketHandler(char* pBuffer, unsigned int iLen);
};


/************************************************************************/
/* ū����Ⱥ���      2139                                            */
/************************************************************************/
class CSSlaveSOSPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_serialId;
	int m_iPlayerId;
public:
	CSSlaveSOSPacket(int serialId, int playerId);
	virtual ~CSSlaveSOSPacket();
public:
	virtual  unsigned  int  GetPacketType();
	virtual  unsigned  int  GetPacketLength();
public:
	virtual  bool  Read(char* pBuffer, unsigned int iLen){	return true;	};
	virtual  void  Send();
};


#endif
