#include "../include/NetDebuger.h"
#include "../include/TimeSystem.h"
#include "../include/NetDebugPacket.h"

NetDebuger::NetDebuger()
{
	m_DebugerType = _TYPED_DEBUGER_NET_;

	m_AllDownLoadBytes = 0;
	m_AllUpLoadBytes   = 0;

	m_fTime_Account_begin=0.0f;		//账号认证
	m_fTime_Account_end=0.0f;
	m_fTime_Login_begin=0.0f;			//登陆
	m_fTime_Login_end=0.0f;
	m_fTime_Role_begin=0.0f;			//角色列表
	m_fTime_Role_end=0.0f;
}

NetDebuger::~NetDebuger()
{

}

bool  NetDebuger::Init()
{
	return true;
}

void  NetDebuger::Tick()
{

}

void  NetDebuger::Destroy()
{

}

void NetDebuger::setAccount_Auth_Begin(){
	m_fTime_Account_begin=TimeSystem::get_instance2()->GetCurrentSecond();
}
void NetDebuger::setAccount_Auth_End(){
	m_fTime_Account_end=TimeSystem::get_instance2()->GetCurrentSecond();
}

void NetDebuger::setLogin_Begin(){
	m_fTime_Login_begin=TimeSystem::get_instance2()->GetCurrentSecond();
}
void NetDebuger::setLogin_End(){
	m_fTime_Login_end=TimeSystem::get_instance2()->GetCurrentSecond();
}

void NetDebuger::setRole_Begin(){
	m_fTime_Role_begin=TimeSystem::get_instance2()->GetCurrentSecond();
}
void NetDebuger::setRole_End(){
	m_fTime_Role_end=TimeSystem::get_instance2()->GetCurrentSecond();
}

//告诉服务器登陆debug信息
void NetDebuger::ToServer_LoginDebugInfo(){
	long long auth_during=m_fTime_Account_end-m_fTime_Account_begin;
	long long role_during=m_fTime_Role_end-m_fTime_Role_begin;
	long long login_during=m_fTime_Login_end-m_fTime_Login_begin;

	CSLoginDuringPacket packet(auth_during,role_during,login_during);
	packet.Send();
}
