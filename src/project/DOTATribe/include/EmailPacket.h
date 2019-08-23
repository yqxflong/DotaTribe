//Name��EmailPacket
//Function���ʼ���ذ�
//Written By����ǿ

#ifndef _DOTATRIBE_EmailPacket_H_
#define _DOTATRIBE_EmailPacket_H_

#include "IPacket.h"
#include "DotaPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include "../include/EmailDataHandler.h"

/************************************************************************/
/* ����ʼ���Ϣ����<br>				                                                        */
/************************************************************************/
class CSEmailListPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSEmailListPacket();
	virtual ~CSEmailListPacket(){};

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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	/*
		�����ֽ���
	*/
	virtual  void  Send();
};
/************************************************************************/
/* ����ʼ���Ϣ����<br>				                                                        */
/************************************************************************/
class SCEmailListPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;

public:
	SCEmailListPacket(){};
	virtual ~SCEmailListPacket(){};
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

class SCEmailListPacketFactory : public IPacketFactory
{
public:
	SCEmailListPacketFactory(){};
	virtual ~SCEmailListPacketFactory(){};

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



/************************************************************************/
/* �����ʼ�����<br>																		  */
/************************************************************************/

class CSEmailSendPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	EmailWriteData* m_dataEmailSend;
public:
	CSEmailSendPacket(EmailWriteData* emailData);
	virtual ~CSEmailSendPacket(){};

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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	/*
		�����ֽ���
	*/
	virtual  void  Send();
};

/*
	�����ʼ�����
*/
	/**
	 * �����ʼ�����<br>
	 * byte ret 0�ɹ� 1ʧ��<br>
	 */

class SCEmailSendPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	unsigned char m_result;	//0�ɹ� 1ʧ��<br>
public:
	SCEmailSendPacket(){};
	virtual ~SCEmailSendPacket(){};
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

class SCEmailSendPacketFactory : public IPacketFactory
{
public:
	SCEmailSendPacketFactory(){};
	virtual ~SCEmailSendPacketFactory(){};

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

/************************************************************************/
/* ��ȡ�ʼ���������<br>																	  */
/************************************************************************/
  /**
   * ɾ���ʼ�����<br>
  * int mailId �ʼ�ID<br>
 */

class CSGetEmailAttPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_nEmailID;
public:
	CSGetEmailAttPacket(int emailID);
	virtual ~CSGetEmailAttPacket(){};

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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	/*
		�����ֽ���
	*/
	virtual  void  Send();
};

/*
	��ȡ�ʼ���������<br>
*/
class SCGetEmailAttPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	unsigned char m_result;	//0�ɹ� 1ʧ��<br>
public:
	SCGetEmailAttPacket(){};
	virtual ~SCGetEmailAttPacket(){};
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

class SCGetEmailAttPacketFactory : public IPacketFactory
{
public:
	SCGetEmailAttPacketFactory(){};
	virtual ~SCGetEmailAttPacketFactory(){};

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

/************************************************************************/
/* ɾ���ʼ�����<br>															  */
/************************************************************************/
        /**
         * ɾ���ʼ�����<br>
         * int mailId �ʼ�ID<br>
         */

class CSRemoveEmailPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_nEmailID;
public:
	CSRemoveEmailPacket(int emailID);
	virtual ~CSRemoveEmailPacket(){};

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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	/*
		�����ֽ���
	*/
	virtual  void  Send();
};

/*
* ɾ���ʼ����󷵻� <br>
*/
class SCRemoveEmailPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	unsigned char m_result;	//0�ɹ� 1ʧ��<br>
public:
	SCRemoveEmailPacket(){};
	virtual ~SCRemoveEmailPacket(){};
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

class SCRemoveEmailPacketFactory : public IPacketFactory
{
public:
	SCRemoveEmailPacketFactory(){};
	virtual ~SCRemoveEmailPacketFactory(){};

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


/************************************************************************/
/* �鿴�ʼ�																*/
/************************************************************************/
/*
*	�鿴�ʼ�����
*/
class CSCheckEmailPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	int m_nEmailID;
public:
	CSCheckEmailPacket(int emailID);
	virtual ~CSCheckEmailPacket(){};

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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	/*
		�����ֽ���
	*/
	virtual  void  Send();
};

/*
* �鿴�ʼ����ؽ�� <br>
*/
class SCCheckEmailPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCCheckEmailPacket(){};
	virtual ~SCCheckEmailPacket(){};
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

class SCCheckEmailPacketFactory : public IPacketFactory
{
public:
	SCCheckEmailPacketFactory(){};
	virtual ~SCCheckEmailPacketFactory(){};

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

class CSGetAllMailPacket: public DotaPacket{
public:
	CSGetAllMailPacket();
	~CSGetAllMailPacket();
public:
	virtual unsigned int GetPacketType();
};

class SCGetAllMailPacket: public IPacket{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCGetAllMailPacket(){};
	~SCGetAllMailPacket(){};

public:
	/*
		�õ����ݰ�����
	*/
	virtual unsigned int GetPacketType();
	/*
		�õ����ݰ�����
	*/
	virtual unsigned int GetPacketLength();
public:
	/*
		��ȡ�ֽ���
	*/
	virtual bool Read(char* pBuffer,unsigned int iLen);

	virtual void Send(){};

};

class SCGetAllMailPacketFactory: public IPacket{
public:
	SCGetAllMailPacketFactory(){};
	~SCGetAllMailPacketFactory(){};
public:
	/*
		������ݰ�����
	*/
	virtual unsigned int GetPacketType(); 
public:
	/*
		���ݰ��������
	*/
	virtual bool OnPacketHandler(char* pBuffer,unsigned int iLen);

};
#endif