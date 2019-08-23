#include "../include/ShopGoodsBase.h"
#include "../include/CPublicVarReader.h"
#include "../include/NFToolController.h"

ShopInfoGoodsData::ShopInfoGoodsData()
{
	//m_shopTemplateBase = NULL;
	shopItemId = 0;			//商品ID
	nameBase ="";			//名称
	descriptionBase = "";	//描述
	limit = 0;				//可购买量  -1代表无限制
	moneyType = 0;				//货币类型：0 金币 1 钻石 2 声望 
	exchangeiconId = 0;
	//discountexchangeiconId = 0;
	price = 0;					//原价
	discount = 0;				//打折后价: -1表示无折扣 
	requireType= 0;			//购买条件类型：0 无条件 1：角色等级 2：VIP等级
	require = 0;				//购买条件
	multiPurchase = 0;			//批量购买： 1 可以 0 不可以
};

ShopInfoGoodsData::~ShopInfoGoodsData()
{
	//m_shopTemplateBase = NULL;
	shopItemId = 0;			//商品ID
	nameBase ="";			//名称
	descriptionBase = "";	//描述
	limit = 0;				//可购买量  -1代表无限制
	moneyType = 0;				//货币类型：0 金币 1 钻石 2 声望
	exchangeiconId = 0;
	//discountexchangeiconId = 0;
	price = 0;					//原价
	discount = 0;				//打折后价: -1表示无折扣 
	requireType= 0;			//购买条件类型：0 无条件 1：角色等级 2：VIP等级
	require = 0;				//购买条件
	multiPurchase = 0;			//批量购买： 1 可以 0 不可以
};

bool ShopInfoGoodsData::decodeTemplatePacketData(cobra_win::DPacket &packet)
{
	packet>>shopItemId;	

	unsigned short tmp_len;
	packet>>tmp_len;
	char * tmpChar = NULL;

	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	nameBase.assign(tmpChar);
	delete[] tmpChar;
	tmpChar=NULL;
	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	descriptionBase.assign(tmpChar);
	delete[] tmpChar;
	tmpChar=NULL;

	packet>>limit;			
	packet>>maxlimit;		
	packet>>moneyType;	
	if (moneyType == 3)
	{
		packet>>extemplateId;
		packet>>exchangeiconId;
	}
	packet>>price;
	packet>>discountMoneyType;
	if (discountMoneyType == 3)
	{
		packet>>distextemplateId;
		packet>>discountexiconId;
	}
	packet>>discount;				
	packet>>requireType;		
	packet>>require;			
	packet>>multiPurchase;
	packet>>quality;				
	packet>>iconId;		
	packet>>catogory_;

	return true;
}

/************************************************************************/
/* 随机商店信息基类                                                      */
/************************************************************************/

RandomGoodsData::RandomGoodsData()
{
	goodsindex = 0; //序号
	strname = "";		//名字
	strdescription = "";//描述
	limit = 0;	//限购次数
	moneytype = 0;//货币类型
	templateId = 0;//如果是兑换货币 货币的templateId
	moneyiconId = 0;		//如果是兑换货币 货币的iconId
	price = 0;		//价钱
	quality = 0;//品质
	goodsiconId = 0;	//商品的图标
	type = 0;//物品类型
}

RandomGoodsData::~RandomGoodsData()
{

}

bool RandomGoodsData::decodeTemplatePacketData(cobra_win::DPacket &packet)
{
	packet>>goodsindex; //序号
	NFC_ParsePacketString(packet,strname);//名字
	NFC_ParsePacketString(packet,strdescription);//描述
	packet>>limit;	//限购次数
	packet>>moneytype;//货币类型
	if (moneytype == _TYPE_EXCHANGE_ITEM_)
	{
		packet>>templateId;//如果是兑换货币 货币的templateId
		packet>>moneyiconId;		//如果是兑换货币 货币的iconId
	}
	packet>>price;		//价钱
	packet>>quality;//品质
	packet>>goodsiconId;	//商品的图标
	packet>>type;//物品类型
	return true;
}