//Name：	ShopGoodsBase
//Function	商店物品基类
//Written By：lvyunlong


#ifndef _DOTATRIBE_SHOPGOODS_BASE_H_
#define _DOTATRIBE_SHOPGOODS_BASE_H_

#include <include/mem/DPacket.h>
#include <string>
#include <vector>
#include "../include/CSMapTable.h"
using namespace std;

//class ShopTemplateBase; 
class ShopInfoGoodsData
{
public:
	ShopInfoGoodsData();
	~ShopInfoGoodsData();
public:
//	ShopTemplateBase* m_shopTemplateBase;
public:
	unsigned short shopItemId;				//商品ID
	std::string nameBase;			//名称
	std::string descriptionBase;	//描述
	int limit;						//可购买量  -1代表无限制
	int maxlimit;					// 最大可购买量  -1代表无限制
	unsigned char moneyType;					//货币类型：0 金币 1 钻石 2 声望  3 物品 
	int extemplateId ;
	int exchangeiconId;
	int price;						//原价
	unsigned char discountMoneyType;			// 打折货币类型：0 金币 1 钻石 2 声望 3 物品
	int distextemplateId ;
	int discountexiconId;
	int discount;					//打折后价: -1表示无折扣 
	unsigned char requireType;				//购买条件类型：0 无条件 1：角色等级 2：VIP等级
	unsigned char require;					//购买条件
	unsigned short multiPurchase;			//单次最大购买数量  1：不可批量购买 x>1:可批量购买
	unsigned char quality;					// 品质 
	int iconId;						// 图标ID
	unsigned char catogory_;		//物品类型
public:
	bool decodeTemplatePacketData(cobra_win::DPacket &packet);
};

/************************************************************************/
/* 随机商店信息基类                                                      */
/************************************************************************/
class RandomGoodsData
{
public:
	RandomGoodsData();
	~RandomGoodsData();
public:
	unsigned short goodsindex; //序号
	std::string strname;		//名字
	std::string strdescription;//描述
	int limit;	//限购次数
	unsigned char moneytype;//货币类型
	int templateId;//如果是兑换货币 货币的templateId
	int moneyiconId;		//如果是兑换货币 货币的iconId
	int price;		//价钱
	unsigned char quality;//品质
	int goodsiconId;	//商品的图标
	unsigned char type;//物品类型
public:
	bool decodeTemplatePacketData(cobra_win::DPacket &packet);
};

#endif