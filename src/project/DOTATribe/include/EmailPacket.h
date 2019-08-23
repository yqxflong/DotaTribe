//Name：EmailPacket
//Function：邮件相关包
//Written By：尹强

#ifndef _DOTATRIBE_EmailPacket_H_
#define _DOTATRIBE_EmailPacket_H_

#include "IPacket.h"
#include "DotaPacket.h"
#include "PacketFactory.h"
#include <iostream>
#include "../include/EmailDataHandler.h"

/************************************************************************/
/* 玩家邮件信息请求<br>				                                                        */
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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	/*
		发送字节流
	*/
	virtual  void  Send();
};
/************************************************************************/
/* 玩家邮件信息返回<br>				                                                        */
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

class SCEmailListPacketFactory : public IPacketFactory
{
public:
	SCEmailListPacketFactory(){};
	virtual ~SCEmailListPacketFactory(){};

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



/************************************************************************/
/* 发送邮件请求<br>																		  */
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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	/*
		发送字节流
	*/
	virtual  void  Send();
};

/*
	发送邮件反馈
*/
	/**
	 * 发送邮件返回<br>
	 * byte ret 0成功 1失败<br>
	 */

class SCEmailSendPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	unsigned char m_result;	//0成功 1失败<br>
public:
	SCEmailSendPacket(){};
	virtual ~SCEmailSendPacket(){};
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

class SCEmailSendPacketFactory : public IPacketFactory
{
public:
	SCEmailSendPacketFactory(){};
	virtual ~SCEmailSendPacketFactory(){};

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

/************************************************************************/
/* 提取邮件附件请求<br>																	  */
/************************************************************************/
  /**
   * 删除邮件请求<br>
  * int mailId 邮件ID<br>
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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	/*
		发送字节流
	*/
	virtual  void  Send();
};

/*
	提取邮件附件返回<br>
*/
class SCGetEmailAttPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	unsigned char m_result;	//0成功 1失败<br>
public:
	SCGetEmailAttPacket(){};
	virtual ~SCGetEmailAttPacket(){};
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

class SCGetEmailAttPacketFactory : public IPacketFactory
{
public:
	SCGetEmailAttPacketFactory(){};
	virtual ~SCGetEmailAttPacketFactory(){};

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

/************************************************************************/
/* 删除邮件请求<br>															  */
/************************************************************************/
        /**
         * 删除邮件请求<br>
         * int mailId 邮件ID<br>
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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	/*
		发送字节流
	*/
	virtual  void  Send();
};

/*
* 删除邮件请求返回 <br>
*/
class SCRemoveEmailPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
	unsigned char m_result;	//0成功 1失败<br>
public:
	SCRemoveEmailPacket(){};
	virtual ~SCRemoveEmailPacket(){};
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

class SCRemoveEmailPacketFactory : public IPacketFactory
{
public:
	SCRemoveEmailPacketFactory(){};
	virtual ~SCRemoveEmailPacketFactory(){};

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


/************************************************************************/
/* 查看邮件																*/
/************************************************************************/
/*
*	查看邮件请求
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
	virtual  bool  Read(char* pBuffer, unsigned int iLen){return true;};
	/*
		发送字节流
	*/
	virtual  void  Send();
};

/*
* 查看邮件返回结果 <br>
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

class SCCheckEmailPacketFactory : public IPacketFactory
{
public:
	SCCheckEmailPacketFactory(){};
	virtual ~SCCheckEmailPacketFactory(){};

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
		得到数据包类型
	*/
	virtual unsigned int GetPacketType();
	/*
		得到数据包长度
	*/
	virtual unsigned int GetPacketLength();
public:
	/*
		读取字节流
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
		获得数据包类型
	*/
	virtual unsigned int GetPacketType(); 
public:
	/*
		数据包处理操作
	*/
	virtual bool OnPacketHandler(char* pBuffer,unsigned int iLen);

};
#endif