//Name：LoginPakcet
//Function：登陆相关包
//Written By：尹强

#ifndef  _PACKECT_LoginPakcet_H_
#define  _PACKECT_LoginPakcet_H_

#include <cocos2d.h>
#include "../include/IPacket.h"
#include "../include/DotaPacket.h"
#include "../include/PacketFactory.h"
#include <string>
#include "../include/LocalPlayerDataManager.h"

//##########################客户端激活包##################//
/**
    * 客户端激活记录
    * string version;
    * int accountType 帐号类型 <br>
    * String deviceId 设备ID IOS:UUID Android:IMEI<br>
*/

class CSClientActivePacket : public DotaPacket
{
public:
	CSClientActivePacket(std::string version,int accType,std::string deviceID,std::string macAddr);
	virtual ~CSClientActivePacket(){};
public:
	virtual  unsigned  int  GetPacketType();
};



//#################平台登陆返回后发送登陆包################
/**
	 * 多平台登陆验证(字符串为空传"NULL")<br>
	 * String clientType 客户端操作系统平台: “IOS”，“ANDROID”或者“OTHER”<br>
	 * String deviceId 设备ID IOS:UUID Android:IMEI<br>
	 * byte channelId 平台: 0:畅游 1:91平台 2：Appstore<br>
	 * String deviceSystem 客户端操作系统版本<br>
	 * String MACAddress 机器MAC地址<br>
	 * String version 客户端版本号<br>
	 * String telecomOperator 电信运营商: 移动、联调、电信...<br>
	 * String AppendParam 附加参数<br>
	 * byte isHacked 是否越狱<br>
	 * 
	 * byte accountType 帐号类型  0：游客帐号  1：畅游帐号  2:91帐号<br>
	 * if(0 || 1)<br>
	 * {<br>
	 * 	String accountName 账号名称<br>
	 * 	String password 密码<br>
	 * }<br>
	 * if(2)<br>
	 * {<br>
	 * 	String uin 91Uin<br>
	 * 	String sessionId 91登录SDK获取<br>
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

	SDKLoginParam sdkParam;//平台登陆参数
	GameLoginParam gameParam;//游戏登陆参数

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

//#################平台登陆返回后发送登陆包################
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

class SCLoginPacketFactory : public IPacketFactory
{
public:
	SCLoginPacketFactory(){};
	virtual ~SCLoginPacketFactory(){};

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

//#################通知强行断开连接################
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

class SCForceDisConnectPacketFactory : public IPacketFactory
{
public:
	SCForceDisConnectPacketFactory(){};
	virtual ~SCForceDisConnectPacketFactory(){};

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

//#################登陆公告Request################
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

//#################登陆公告Resp################
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

class SCNoticePacketFactory : public IPacketFactory
{
public:
	SCNoticePacketFactory(){};
	virtual ~SCNoticePacketFactory(){};

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