//Name��	ServerInfoData
//Function����ֵ��صĿ�����
//Written By��lvyunlong

#ifndef   _DOTATRIBE_PAYGOODSDATAHANDLER_H
#define   _DOTATRIBE_PAYGOODSDATAHANDLER_H

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <map>
#include <vector>
#include <string>
#include <cocos2d.h>
#include "../include/VariableSystem.h"
#include <include/mem/DPacket.h>
using namespace std;

enum
{
	_ENUM_STATE_PAYORDER_SUCCESS_ = 0,  //0: ��֤�ɹ�
	_ENUM_STATE_PAYORDER_PAYMONEY_,		//1���ö����Ѿ��ӹ�Ǯ
	_ENUM_STATE_PAYORDER_FAIL_,			//2��������֤ʧ��
	_ENUM_STATE_PAYORDER_PLATFORMRETRY_,//3��ƽ̨�����У�Ѻ������
	_ENUM_STATE_PAYORDER_SERVERRETRY_,	//4��ϵͳ��æ�����Ժ�����
};

class PayGoodsData
{
public:
	PayGoodsData();
	~PayGoodsData();
public:
	std::string goodsName_;			//��Ʒ������
	std::string goodsId_;			//��Ʒ��Id	
	std::string goodsRegisterId_;	//��Ʒע���ID���к�
	float goodsPrice_;				//��Ʒ��Ǯ
	int goodNumber_;				//��Ʒ����
	int iconId_;					//��Ʒ��iconId
public:
	bool decodeTemplatePacketData(cobra_win::DPacket &packet);
};

class DoublePayData
{
public:
	DoublePayData();
	~DoublePayData();
public:
	std::string goodsRegisterId;
	unsigned char isDoublePay;
	bool decodeTemplatePacketData(cobra_win::DPacket &packet);
};

class PayGoodsControlDataHandler:public IDataHandler,public cobra_win::Singleton2<PayGoodsControlDataHandler>{

public:
	bool m_isBIAPCheck;					//������Ϸ�Ƿ�鿴������ϷIAP����
	bool m_isBPaylist;					//��Ʒ�ѱ��Ƿ��յ�
	bool m_isBInitmentEnv;				//�Ƿ��ʼ����֧������
	int m_CurVistorPayIndex;			//�ο�Ҫ���IndexPay
	std::string m_strTempOrderld;		//ȷ�϶������������ض���
	unsigned char m_aSureOrderldState;	//ȷ�϶������������ض���״̬
	std::string m_strPPOrderId;			//����������PP����
	std::string m_strPPGoodsId;			//��Ӧ����������PP������ƷID
	unsigned char m_GoodsCount;
	//std::map<std::string ,int> 	m_OrderldList;				//������ֵ����
	std::vector<PayGoodsData*>	m_PayGoodsList;				//��ֵ��Ʒ�б�
	std::vector<std::string>	m_AndroidPayStr;
	int m_ShowDoubleArray[3];
	bool m_isBIAPTick;
	int m_IAPTickCount;
public:
	PayGoodsControlDataHandler();
	virtual ~PayGoodsControlDataHandler();
	/*
		���յ���������ذ���ʱ���ô˺����Ѷ�Ӧ��������ת���ɶ�Ӧ�����ݽṹ
		����map�У�����֮����ڴ��е���ɾ�Ĳ�
	*/
	virtual void handlePacket(IPacket* packet);
	virtual bool init();
	virtual void onDestroy();
	/*
		�����ֵ��ʯ�б���Ϣ
	*/
	void  ToServerRechargeListPacket(unsigned char channel);

	/*
		�����ֵȷ����Ϣ
	*/
	void  ToServerPaySurePacket(unsigned char channel,std::string iapid,std::string orderld,std::string transactReceipt);
	/*
		���󴴽�������ϢforPP
	*/
	void  ToServerCreatePPOrederPacket(std::string goodsid);

	/*
		ͨ��ע��id�ҵ���Ʒid
	*/
	PayGoodsData* ByRegisterIdFindGoodsData(std::string registerid);

	/*
		����ȷ�϶������������ز���	
	*/
	void SureServerOrederBack(std::string strorderldTemp,unsigned char orderldstate);
	/*
		������Ķ������͸���������֤
	*/
	void  LocalPayIAPCheck();
	/*
		SDK����֮��30�������������һ�ζ���
	*/
	void TimeTickToServerIapCheck();
	/*
		�����Ʒ�б�	
	*/
	void  ClearPayItemList();
	/*
		����֧��������Ϣ
	*/
	void ToServerAdditionPayInfo();
	/*
		��ȡ����֧����Ϣ
	*/
	bool ReadPayAddtionPacketData(cobra_win::DPacket &packet);
	/*
		�����ֵ����˫��
	*/
	void ToServerDoublePayInfo();
	/*
		�����ֵ����˫������
	*/
	void ReadDoublePayInfoData(cobra_win::DPacket &packet);
};

#define PAYGOODSCONTROLDATAHANDLER	 PayGoodsControlDataHandler::get_instance2()
#endif