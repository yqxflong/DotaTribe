//Name：	ServerInfoData
//Function：服务器列表数据
//				    与Packet对应
//Written By：lvyunlong

#include <cocos2d.h>
#include "../include/ShopInfoDataHandler.h"
#include "../include/CSShopInfoPacket.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/NFControlsManager.h"
#include "../include/RandomShopPacket.h"
using namespace std;


ShopInfoDataHandler::ShopInfoDataHandler(){

	m_shopId = 0;
	m_shopItemId = 0;
	m_count = 0; 
	m_selledshopid = 0; 
	m_selledshopItemId = 0; 
	m_selledcount = 0; 
	m_isBshopsellupdate = false;
	m_isBshopinfoupdate = false;
	m_iShowArrow = false;
	
}

ShopInfoDataHandler::~ShopInfoDataHandler(){

}

void ShopInfoDataHandler::handlePacket(IPacket* packet){

}

bool ShopInfoDataHandler::init(){
	m_ShopGoodsBaselist.clear();
	return true;
}

void ShopInfoDataHandler::onDestroy(){

	ClearShopInfoList();
}

void  ShopInfoDataHandler::ToServerShopInfoPacket()
{
	CSShopInfoPacket packet(m_shopId);
	packet.Send();
	NFC_showCommunicationWating(true);
}

void  ShopInfoDataHandler::ToServerBuyItemPacket(short shopId,short shopItemId,int itemcount)
{
	CSShopBuyItemPacket packet(shopId,shopItemId,itemcount);
	packet.Send();
	NFC_showCommunicationWating(true);
}

void  ShopInfoDataHandler::ClearShopInfoList()
{
	std::vector<ShopInfoGoodsData*>::iterator  posbegin = m_ShopGoodsBaselist.begin();
	std::vector<ShopInfoGoodsData*>::iterator  posend = m_ShopGoodsBaselist.end();
	for (posbegin;posbegin!=posend;posbegin++)
	{
		CC_SAFE_DELETE((*posbegin));
	}
	m_ShopGoodsBaselist.clear();
}

/************************************************************************/
/* 随机商店数据控制器                                                    */
/************************************************************************/
RandomShopDataHandler::RandomShopDataHandler()
{
	leftSeconds_ = 0;
	leftItemCount_ = 0;
	refreshPrice_ = 0;
	m_isRandomTick = false;
	m_RandomInfoList.clear();
}

RandomShopDataHandler::~RandomShopDataHandler()
{

}

void RandomShopDataHandler::handlePacket(IPacket* packet)
{

}
bool RandomShopDataHandler::init()
{
	return true;
}
void RandomShopDataHandler::onDestroy()
{
	m_isRandomTick = false;
	ClearRandomShopInfoList();
}

/*
	请求商店信息
*/
void  RandomShopDataHandler::ToServerRandomShopInfoPacket()
{
	CSRandomShopInfoPacket packet;
	packet.Send();
	NFC_showCommunicationWating(true);
}

/*
	请求购买商品
*/
void  RandomShopDataHandler::ToServerBuyItemPacket(unsigned short goodsindex,int num)
{
	CSRandomShopBuyPacket packet(goodsindex,num);
	packet.Send();
	NFC_showCommunicationWating(true);

}
/*
	清除商店数据
*/
void  RandomShopDataHandler::ClearRandomShopInfoList()
{
	std::vector<RandomGoodsData*>::iterator  posbegin = m_RandomInfoList.begin();
	std::vector<RandomGoodsData*>::iterator  posend = m_RandomInfoList.end();
	for (posbegin;posbegin!=posend;posbegin++)
	{
		CC_SAFE_DELETE((*posbegin));
	}
	m_RandomInfoList.clear();
}

void RandomShopDataHandler::RefreshRandomShop()
{
	NFC_showCommunicationWating(true);
	CSRandomShopRefreshPacket packet;
	packet.Send();
}