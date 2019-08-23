#include "../include/ShopGoodsBase.h"
#include "../include/CPublicVarReader.h"
#include "../include/NFToolController.h"

ShopInfoGoodsData::ShopInfoGoodsData()
{
	//m_shopTemplateBase = NULL;
	shopItemId = 0;			//��ƷID
	nameBase ="";			//����
	descriptionBase = "";	//����
	limit = 0;				//�ɹ�����  -1����������
	moneyType = 0;				//�������ͣ�0 ��� 1 ��ʯ 2 ���� 
	exchangeiconId = 0;
	//discountexchangeiconId = 0;
	price = 0;					//ԭ��
	discount = 0;				//���ۺ��: -1��ʾ���ۿ� 
	requireType= 0;			//�����������ͣ�0 ������ 1����ɫ�ȼ� 2��VIP�ȼ�
	require = 0;				//��������
	multiPurchase = 0;			//�������� 1 ���� 0 ������
};

ShopInfoGoodsData::~ShopInfoGoodsData()
{
	//m_shopTemplateBase = NULL;
	shopItemId = 0;			//��ƷID
	nameBase ="";			//����
	descriptionBase = "";	//����
	limit = 0;				//�ɹ�����  -1����������
	moneyType = 0;				//�������ͣ�0 ��� 1 ��ʯ 2 ����
	exchangeiconId = 0;
	//discountexchangeiconId = 0;
	price = 0;					//ԭ��
	discount = 0;				//���ۺ��: -1��ʾ���ۿ� 
	requireType= 0;			//�����������ͣ�0 ������ 1����ɫ�ȼ� 2��VIP�ȼ�
	require = 0;				//��������
	multiPurchase = 0;			//�������� 1 ���� 0 ������
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
/* ����̵���Ϣ����                                                      */
/************************************************************************/

RandomGoodsData::RandomGoodsData()
{
	goodsindex = 0; //���
	strname = "";		//����
	strdescription = "";//����
	limit = 0;	//�޹�����
	moneytype = 0;//��������
	templateId = 0;//����Ƕһ����� ���ҵ�templateId
	moneyiconId = 0;		//����Ƕһ����� ���ҵ�iconId
	price = 0;		//��Ǯ
	quality = 0;//Ʒ��
	goodsiconId = 0;	//��Ʒ��ͼ��
	type = 0;//��Ʒ����
}

RandomGoodsData::~RandomGoodsData()
{

}

bool RandomGoodsData::decodeTemplatePacketData(cobra_win::DPacket &packet)
{
	packet>>goodsindex; //���
	NFC_ParsePacketString(packet,strname);//����
	NFC_ParsePacketString(packet,strdescription);//����
	packet>>limit;	//�޹�����
	packet>>moneytype;//��������
	if (moneytype == _TYPE_EXCHANGE_ITEM_)
	{
		packet>>templateId;//����Ƕһ����� ���ҵ�templateId
		packet>>moneyiconId;		//����Ƕһ����� ���ҵ�iconId
	}
	packet>>price;		//��Ǯ
	packet>>quality;//Ʒ��
	packet>>goodsiconId;	//��Ʒ��ͼ��
	packet>>type;//��Ʒ����
	return true;
}