
#include <cocos2d.h>
#include "../include/C2SQAReceiptPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>
#include <include/mem/EPacket.h>
#include "../include/LoggerSystem.h"
#include "../include/QADataHandler.h"

#include <stdlib.h>
#include <iostream>
using namespace std;
using  namespace  cobra_win;


C2SQAReceiptPacket::C2SQAReceiptPacket(char qaSelect) {
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_qaSelect=qaSelect;
	m_len=GetPacketLength();
};

unsigned  int  C2SQAReceiptPacket::GetPacketType()
{
	return _TYPEF_PACLET_C2S_COMMON_QA_CLIENT_;
}

unsigned  int  C2SQAReceiptPacket::GetPacketLength()
{
	unsigned int  packetLengt=sizeof(m_head)+sizeof(m_len)+sizeof(m_pn)+sizeof(m_qaType)+sizeof(m_qaSelect)+sizeof(m_paramCount);
	m_qaType=QADataHandler::get_instance2()->pQAdata->qatype;
	m_paramCount=QADataHandler::get_instance2()->pQAdata->paramCount;
	for(short paramIndex=0;paramIndex<m_paramCount;paramIndex++)
	{
		packetLengt+=sizeof(short);
		packetLengt+=QADataHandler::get_instance2()->pQAdata->paramVec.at(paramIndex).length();
	}
	return packetLengt;
}
/*
	C->S不需要实现Read函数
*/
bool  C2SQAReceiptPacket::Read(char* pBuffer, unsigned int iLen)
{
	return true;
}

void  C2SQAReceiptPacket::Send()
{  
	MemNode* pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	char * p=NULL;
	pNode->push(m_head,sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_qaType);
	pNode->push(m_qaSelect); 
	pNode->push(m_paramCount); 
	unsigned short strlength=0;
	for(short paramIndex=0;paramIndex<m_paramCount;paramIndex++)
	{
		strlength=QADataHandler::get_instance2()->pQAdata->paramVec.at(paramIndex).length();
		pNode->push(strlength);
		p=const_cast<char *>(QADataHandler::get_instance2()->pQAdata->paramVec.at(paramIndex).c_str());
		pNode->push(p,strlength);
	} 
	NETSYSTEM->SendPacket(pNode);
}