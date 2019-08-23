#include <cocos2d.h>
#include "../include/RegisterAccountPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>

#include <stdlib.h>
#include <iostream>
#include <include/mem/DPacket.h>
using namespace std;
using  namespace  cobra_win;


C2SRegisterAccountPacket::C2SRegisterAccountPacket(std::string userName,std::string userPassWord,std::string userConfirmPassWord){
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();


	m_szuserName=userName.length();
	m_userName=userName;

	m_szuserPassWord=userPassWord.length();
	m_userPassWord=userPassWord;

	m_szuserConfirmPassWord=userConfirmPassWord.length();
	m_userConfirmPassWord =userConfirmPassWord;

	//最后获取长度
	m_len=GetPacketLength();
};

unsigned  int  C2SRegisterAccountPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_REGISTERACCOUNT_;
}

unsigned  int  C2SRegisterAccountPacket::GetPacketLength()
{
	return sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_szuserName)+m_userName.length()+sizeof(m_szuserPassWord)+m_userPassWord.length()+sizeof(m_szuserConfirmPassWord)+m_userConfirmPassWord.length();
}
/*
	C->S不需要实现Read函数
*/
bool  C2SRegisterAccountPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SRegisterAccountPacket::Send()
{
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());

	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);

	pNode->push(m_szuserName);
	char* pName =const_cast<char*>(m_userName.c_str());
	pNode->push(pName,m_szuserName);

	pNode->push(m_szuserPassWord);
	char* pPassWord =const_cast<char*>(m_userPassWord.c_str());
	pNode->push(pPassWord,m_szuserPassWord);

	pNode->push(m_szuserConfirmPassWord);
	char* pConfirmPassWord =const_cast<char*>(m_userConfirmPassWord.c_str());
	pNode->push(pConfirmPassWord,m_szuserConfirmPassWord);
	
	NETSYSTEM->SendPacket(pNode);
}



//S2C
S2CRegisterAccountPacket::S2CRegisterAccountPacket()
{

}

S2CRegisterAccountPacket::~S2CRegisterAccountPacket()
{

}

unsigned  int  S2CRegisterAccountPacket::GetPacketType()
{
	return 0;
}

unsigned  int  S2CRegisterAccountPacket::GetPacketLength()
{
	return sizeof(int);
}

bool  S2CRegisterAccountPacket::Read(char* pBuffer, unsigned int iLen)
{
	DPacket packet(pBuffer, iLen);

	//packet>>m_LoginRet;
	packet.read(m_head,2);
	packet>>m_len;
	packet>>m_pn;
	packet>>serial_;

	////收场景信息

	return true;
}


void  S2CRegisterAccountPacket::Send(){
	//S->C不需要实现发包
}

//工厂
S2CRegisterAccountPacketFactory::S2CRegisterAccountPacketFactory()
{

}


S2CRegisterAccountPacketFactory::~S2CRegisterAccountPacketFactory()
{

}

unsigned  int S2CRegisterAccountPacketFactory::GetPacketType()
{
	return 0;
}

bool S2CRegisterAccountPacketFactory::OnPacketHandler(char* pBuffer, unsigned int iLen)
{
	S2CRegisterAccountPacket packet;
	if (!packet.Read(pBuffer, iLen))
		return false;

	OnS2CRegisterAccountPacketHandler(&packet);
	return true;
}	

void S2CRegisterAccountPacketFactory::OnS2CRegisterAccountPacketHandler(S2CRegisterAccountPacket* pPacket)
{

}
