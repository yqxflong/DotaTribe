//Name：CSShopInfoPacket
//Function：c->s 请求商店物品
//Written By：lvyunlong
#include <cocos2d.h>
#include "../include/CSShopInfoPacket.h"
#include "../include/PacketTyper.h"
#include "../include/NetSystem.h"
#include <include/mem/MemNode.h>

/*
char m_head[2];
int  m_len;
short m_pn;
int m_serial;
*/

CSShopInfoPacket::CSShopInfoPacket(short shopId)
{
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	m_shopId = shopId;
	//最后获取长度
	m_len=GetPacketLength();
}

/*
得到数据包类型
*/
unsigned  int  CSShopInfoPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_SHOP_INFO_;
}

/*
得到数据包长度
*/
unsigned  int  CSShopInfoPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_shopId);
}

/*
读取字节流
*/
bool  CSShopInfoPacket::Read(char* pBuffer, unsigned int iLen)
{
	//不从服务器读取
	return true;
}

/*
发送字节流
*/
void  CSShopInfoPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_shopId);
	NETSYSTEM->SendPacket(pNode);
}


/************************************************************************/
/*    CSShopBuyItemPacket                                               */
/************************************************************************/

CSShopBuyItemPacket::CSShopBuyItemPacket(short shopId,short shopItemId,int itemcount)
{
	m_head[0]='Z';
	m_head[1]='R';
	m_pn=GetPacketType();
	
	m_shopId = shopId;
	m_shopItemId = shopItemId;
	m_itemcount = itemcount;
	
	//最后获取长度
	m_len=GetPacketLength();
}

/*
得到数据包类型
*/
unsigned  int  CSShopBuyItemPacket::GetPacketType()
{
	return _TYPED_PACKET_C2S_SHOP_BUY_;
}

/*
得到数据包长度
*/
unsigned  int  CSShopBuyItemPacket::GetPacketLength()
{
	return sizeof(m_head) + sizeof(m_pn) + sizeof(m_len) + sizeof(m_shopId) + sizeof(m_shopItemId) + sizeof(m_itemcount);
}

/*
读取字节流
*/
bool  CSShopBuyItemPacket::Read(char* pBuffer, unsigned int iLen)
{
	//不从服务器读取
	return true;
}

/*
发送字节流
*/
void  CSShopBuyItemPacket::Send()
{
	MemNode * pNode = NETSYSTEM->QueryMemNode(GetPacketLength());
	pNode->push(m_head, sizeof(m_head));
	pNode->push(m_len);
	pNode->push(m_pn);
	pNode->push(m_shopId);
	pNode->push(m_shopItemId);
	pNode->push(m_itemcount);
	NETSYSTEM->SendPacket(pNode);
}