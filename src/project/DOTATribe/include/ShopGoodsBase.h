//Name��	ShopGoodsBase
//Function	�̵���Ʒ����
//Written By��lvyunlong


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
	unsigned short shopItemId;				//��ƷID
	std::string nameBase;			//����
	std::string descriptionBase;	//����
	int limit;						//�ɹ�����  -1����������
	int maxlimit;					// ���ɹ�����  -1����������
	unsigned char moneyType;					//�������ͣ�0 ��� 1 ��ʯ 2 ����  3 ��Ʒ 
	int extemplateId ;
	int exchangeiconId;
	int price;						//ԭ��
	unsigned char discountMoneyType;			// ���ۻ������ͣ�0 ��� 1 ��ʯ 2 ���� 3 ��Ʒ
	int distextemplateId ;
	int discountexiconId;
	int discount;					//���ۺ��: -1��ʾ���ۿ� 
	unsigned char requireType;				//�����������ͣ�0 ������ 1����ɫ�ȼ� 2��VIP�ȼ�
	unsigned char require;					//��������
	unsigned short multiPurchase;			//�������������  1�������������� x>1:����������
	unsigned char quality;					// Ʒ�� 
	int iconId;						// ͼ��ID
	unsigned char catogory_;		//��Ʒ����
public:
	bool decodeTemplatePacketData(cobra_win::DPacket &packet);
};

/************************************************************************/
/* ����̵���Ϣ����                                                      */
/************************************************************************/
class RandomGoodsData
{
public:
	RandomGoodsData();
	~RandomGoodsData();
public:
	unsigned short goodsindex; //���
	std::string strname;		//����
	std::string strdescription;//����
	int limit;	//�޹�����
	unsigned char moneytype;//��������
	int templateId;//����Ƕһ����� ���ҵ�templateId
	int moneyiconId;		//����Ƕһ����� ���ҵ�iconId
	int price;		//��Ǯ
	unsigned char quality;//Ʒ��
	int goodsiconId;	//��Ʒ��ͼ��
	unsigned char type;//��Ʒ����
public:
	bool decodeTemplatePacketData(cobra_win::DPacket &packet);
};

#endif