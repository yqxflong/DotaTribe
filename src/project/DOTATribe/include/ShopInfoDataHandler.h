//Name：	ServerInfoData
//Function：商店
//与Packet对应
//Written By：lvyunlong

#ifndef   _DOTATRIBE_SHOPINFODATAHANDLER_H
#define   _DOTATRIBE_SHOPINFODATAHANDLER_H

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <map>
#include <vector>
#include <string>
#include <cocos2d.h>
#include "../include/VariableSystem.h"
#include "../include/ShopGoodsBase.h"


class ShopInfoDataHandler:public IDataHandler,public cobra_win::Singleton2<ShopInfoDataHandler>{

public:
	bool m_iShowArrow;
	bool m_isBshopinfoupdate;
	bool m_isBshopsellupdate;
	unsigned short m_shopId; 
	unsigned short m_shopItemId; 
	unsigned short m_count;
	unsigned short m_selledshopid;
	unsigned short m_selledshopItemId;
	int m_selledcount;	
	std::vector<ShopInfoGoodsData*>	m_ShopGoodsBaselist;				//商店信息链表
public:
	ShopInfoDataHandler();
	virtual ~ShopInfoDataHandler();
	/*
		当收到服务器相关包的时候，用此函数把对应包的数据转化成对应的数据结构
		存入map中，用于之后的内存中的增删改查
	*/
	virtual void handlePacket(IPacket* packet);
	virtual bool init();
	virtual void onDestroy();
	/*
		请求商店信息
	*/
	void  ToServerShopInfoPacket();

	/*
		请求商店信息
	*/
	void  ToServerBuyItemPacket(short shopId,short shopItemId,int itemcount);
	/*
		清除商店数据
	*/
	void  ClearShopInfoList();
};

#define SHOPINFODATAHANDLER	 ShopInfoDataHandler::get_instance2()

/************************************************************************/
/* 随机商店数据控制器                                                    */
/************************************************************************/
class RandomShopDataHandler:public IDataHandler,public cobra_win::Singleton2<RandomShopDataHandler>
{
public:
	bool m_isRandomTick;
	unsigned short m_selledshopItemId;
	int m_selledcount;	
	int m_count;
	int leftSeconds_;
	int leftItemCount_;
	int refreshPrice_;
	std::vector<RandomGoodsData*> m_RandomInfoList;
public:
	RandomShopDataHandler();
	virtual ~RandomShopDataHandler();
public:
	/*
		当收到服务器相关包的时候，用此函数把对应包的数据转化成对应的数据结构
		存入map中，用于之后的内存中的增删改查
	*/
	virtual void handlePacket(IPacket* packet);
	virtual bool init();
	virtual void onDestroy();
	/*
		请求随机商店信息
	*/
	void  ToServerRandomShopInfoPacket();
	/*
		请求购买商品
	*/
	void  ToServerBuyItemPacket(unsigned short goodsindex,int num);
	/*
		清除商店数据
	*/
	void  ClearRandomShopInfoList();
	/*
		刷新商店信息请求
	*/
	void RefreshRandomShop();

};
#define RANDOMSHOPDATAHANDLER	 RandomShopDataHandler::get_instance2()

#endif