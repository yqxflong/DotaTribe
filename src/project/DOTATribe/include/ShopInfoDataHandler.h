//Name��	ServerInfoData
//Function���̵�
//��Packet��Ӧ
//Written By��lvyunlong

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
	std::vector<ShopInfoGoodsData*>	m_ShopGoodsBaselist;				//�̵���Ϣ����
public:
	ShopInfoDataHandler();
	virtual ~ShopInfoDataHandler();
	/*
		���յ���������ذ���ʱ���ô˺����Ѷ�Ӧ��������ת���ɶ�Ӧ�����ݽṹ
		����map�У�����֮����ڴ��е���ɾ�Ĳ�
	*/
	virtual void handlePacket(IPacket* packet);
	virtual bool init();
	virtual void onDestroy();
	/*
		�����̵���Ϣ
	*/
	void  ToServerShopInfoPacket();

	/*
		�����̵���Ϣ
	*/
	void  ToServerBuyItemPacket(short shopId,short shopItemId,int itemcount);
	/*
		����̵�����
	*/
	void  ClearShopInfoList();
};

#define SHOPINFODATAHANDLER	 ShopInfoDataHandler::get_instance2()

/************************************************************************/
/* ����̵����ݿ�����                                                    */
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
		���յ���������ذ���ʱ���ô˺����Ѷ�Ӧ��������ת���ɶ�Ӧ�����ݽṹ
		����map�У�����֮����ڴ��е���ɾ�Ĳ�
	*/
	virtual void handlePacket(IPacket* packet);
	virtual bool init();
	virtual void onDestroy();
	/*
		��������̵���Ϣ
	*/
	void  ToServerRandomShopInfoPacket();
	/*
		��������Ʒ
	*/
	void  ToServerBuyItemPacket(unsigned short goodsindex,int num);
	/*
		����̵�����
	*/
	void  ClearRandomShopInfoList();
	/*
		ˢ���̵���Ϣ����
	*/
	void RefreshRandomShop();

};
#define RANDOMSHOPDATAHANDLER	 RandomShopDataHandler::get_instance2()

#endif