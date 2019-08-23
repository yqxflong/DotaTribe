//Name��LoginPakcet
//Function����½��ذ�
//Written By����ǿ

#ifndef  _PACKECT_LoginPakcet_H_
#define  _PACKECT_LoginPakcet_H_

#include <cocos2d.h>
#include "../include/IPacket.h"
#include "../include/DotaPacket.h"
#include "../include/PacketFactory.h"
#include <string>
#include "../include/LocalPlayerDataManager.h"

//##########################�ͻ��˼����##################//
/**
    * �ͻ��˼����¼
    * string version;
    * int accountType �ʺ����� <br>
    * String deviceId �豸ID IOS:UUID Android:IMEI<br>
*/

class CSClientActivePacket : public DotaPacket
{
public:
	CSClientActivePacket(std::string version,int accType,std::string deviceID,std::string macAddr);
	virtual ~CSClientActivePacket(){};
public:
	virtual  unsigned  int  GetPacketType();
};



//#################ƽ̨��½���غ��͵�½��################
/**
	 * ��ƽ̨��½��֤(�ַ���Ϊ�մ�"NULL")<br>
	 * String clientType �ͻ��˲���ϵͳƽ̨: ��IOS������ANDROID�����ߡ�OTHER��<br>
	 * String deviceId �豸ID IOS:UUID Android:IMEI<br>
	 * byte channelId ƽ̨: 0:���� 1:91ƽ̨ 2��Appstore<br>
	 * String deviceSystem �ͻ��˲���ϵͳ�汾<br>
	 * String MACAddress ����MAC��ַ<br>
	 * String version �ͻ��˰汾��<br>
	 * String telecomOperator ������Ӫ��: �ƶ�������������...<br>
	 * String AppendParam ���Ӳ���<br>
	 * byte isHacked �Ƿ�Խ��<br>
	 * 
	 * byte accountType �ʺ�����  0���ο��ʺ�  1�������ʺ�  2:91�ʺ�<br>
	 * if(0 || 1)<br>
	 * {<br>
	 * 	String accountName �˺�����<br>
	 * 	String password ����<br>
	 * }<br>
	 * if(2)<br>
	 * {<br>
	 * 	String uin 91Uin<br>
	 * 	String sessionId 91��¼SDK��ȡ<br>
	 * }<br>
	 */
struct LoginParams{
	std::string clientType_;
	std::string deviceId_;
	unsigned char channelId_;
	std::string deviceSystem_;
	std::string MACAddress_;
	std::string version_;
	std::string telecomOperator_;
	std::string AppendParam_;
	unsigned char isHacked_;

	SDKLoginParam sdkParam;//ƽ̨��½����
	GameLoginParam gameParam;//��Ϸ��½����

	LoginParams(){
		clientType_="NULL";
		deviceId_="NULL";
		channelId_=0;
		deviceSystem_="NULL";
		MACAddress_="NULL";
		version_="NULL";
		telecomOperator_="NULL";
		AppendParam_="NULL";
		isHacked_=0;
		
	}
};

//
class CSLoginPacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
	LoginParams m_Params;
public:
	CSLoginPacket(LoginParams params);
	virtual ~CSLoginPacket(){};
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

//#################ƽ̨��½���غ��͵�½��################
class SCLoginPacket : public IPacket
{
public:
	unsigned char result_;
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCLoginPacket(){};
	virtual ~SCLoginPacket(){};
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

class SCLoginPacketFactory : public IPacketFactory
{
public:
	SCLoginPacketFactory(){};
	virtual ~SCLoginPacketFactory(){};

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

//#################֪ͨǿ�жϿ�����################
class SCForceDisConnectPacket : public IPacket
{
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCForceDisConnectPacket(){};
	virtual ~SCForceDisConnectPacket(){};

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

class SCForceDisConnectPacketFactory : public IPacketFactory
{
public:
	SCForceDisConnectPacketFactory(){};
	virtual ~SCForceDisConnectPacketFactory(){};

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

//#################��½����Request################
class CSNoticePacket : public IPacket
{
private:
	char m_head[2];
	int  m_len;
	short m_pn;
public:
	CSNoticePacket();
	virtual ~CSNoticePacket(){};

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

//#################��½����Resp################
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
class SCNoticePacket : public IPacket
{
public:
	std::map<int,std::string> m_FontstyleMap;

	std::string content_;
private:
	char m_head[2];
	int m_len;
	unsigned short m_pn;
public:
	SCNoticePacket(){};
	virtual ~SCNoticePacket(){};

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

class SCNoticePacketFactory : public IPacketFactory
{
public:
	SCNoticePacketFactory(){};
	virtual ~SCNoticePacketFactory(){};

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