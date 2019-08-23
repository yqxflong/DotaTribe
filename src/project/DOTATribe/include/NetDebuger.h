#ifndef  _DOTATRIBE_NETDEBUGER_H_
#define  _DOTATRIBE_NETDEBUGER_H_


#include "IDebuger.h"

class NetDebuger : public IDebuger
{
protected:
	long long m_AllDownLoadBytes; // 总的下行字节数量
	long long m_AllUpLoadBytes;   // 总的上行字节数量

private:
	long long m_fTime_Account_begin;		//账号认证
	long long m_fTime_Account_end;
	long long m_fTime_Login_begin;			//登陆
	long long m_fTime_Login_end;
	long long m_fTime_Role_begin;			//角色列表
	long long m_fTime_Role_end;
public:
	NetDebuger();
	virtual ~NetDebuger();

public:
	//@标配
	virtual  bool  Init();
	virtual  void  Tick();
	virtual  void  Destroy();

//@Lua
public:
	void setAccount_Auth_Begin();
	void setAccount_Auth_End();

	void setLogin_Begin();
	void setLogin_End();

	void setRole_Begin();
	void setRole_End();

	//@告诉服务器登陆debug信息
	void ToServer_LoginDebugInfo();
};


#endif
