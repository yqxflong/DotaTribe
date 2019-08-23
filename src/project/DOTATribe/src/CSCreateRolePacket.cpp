//Name��CSCreateRolePacket
//Function��c->s ������ɫ
//Written By����ǿ
#include <cocos2d.h>
#include "../include/CSCreateRolePacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>
#include "../include/LoggerSystem.h"

#include <stdlib.h>
#include <iostream>
using namespace std;
using  namespace  cobra_win;


CSCreateRolePacket::CSCreateRolePacket(int serialnum,std::string accountname,int heroid,std::string rolename){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_serial=serialnum;
	
	//stringǰ��string�ĳ���
	m_szaccountName=accountname.length();
	m_accountName=accountname;
	m_heroid=heroid;
	//stringǰ��string�ĳ���
	m_szrolename=rolename.length();
	m_rolename=rolename;
	//����ȡ����
	m_len=GetPacketLength();
}

unsigned  int  CSCreateRolePacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_CREATEROLE_;
}

unsigned  int  CSCreateRolePacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_serial)+sizeof(m_szaccountName)+sizeof(m_heroid)+sizeof(m_szrolename)+m_rolename.length()+ m_accountName.length();
}
/*
	C->S����Ҫʵ��Read����
*/
bool  CSCreateRolePacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  CSCreateRolePacket::Send()
{
	LOGGERSYSTEM->LogInfo("=======CSCreateRolePacket::Send=======");
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_serial);
	pNode->push(m_szaccountName);
	char* p =const_cast<char*>(m_accountName.c_str());
	pNode->push(p,m_szaccountName);
	pNode->push(m_heroid);
	pNode->push(m_szrolename);
	p =const_cast<char*>(m_rolename.c_str());
	pNode->push(p,m_szrolename);
	NETSYSTEM->SendPacket(pNode);
}