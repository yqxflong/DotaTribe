//Name��	ServerInfoData
//Function����ֵ��صĿ�����
//Written By��lvyunlong

#include <cocos2d.h>
#include "../include/DOTATribeApp.h"
#include "../include/PayGoodsControlDataHandler.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/PayGoodsPacket.h"
#include "../include/IAPSystem.h"
#include "../include/LocalPlayerDataManager.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/MessageBoxWindow.h"
#include "../include/NFControlsManager.h"
#include "../include/NFToolController.h"
#include "../include/SysLangDataManager.h"


using namespace std;

PayGoodsData::PayGoodsData()
{
	goodsName_ = "";			//��Ʒ������
	goodsId_ = "";				//��Ʒ��Id	
	goodsRegisterId_ = "";		//��Ʒ������
	goodsPrice_ = 0;			//��Ʒ��Ǯ
	goodNumber_ = 0;			//��Ʒ����
	iconId_ = 0;				//��Ʒ��iconId
}
PayGoodsData::~PayGoodsData()
{
	
}

bool PayGoodsData::decodeTemplatePacketData(cobra_win::DPacket &packet)
{
	unsigned short tmp_len = 0;
	char * tmpChar = NULL;

	//��ȡ��Ʒ����
	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	goodsName_.assign(tmpChar);
	delete[] tmpChar;
	tmpChar=NULL;

	//��ȡ��Ʒ��Id
	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	goodsId_.assign(tmpChar);
	delete[] tmpChar;
	tmpChar=NULL;

	//��ȡ��Ʒ������
	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	goodsRegisterId_.assign(tmpChar);
	delete[] tmpChar;
	tmpChar=NULL;

	//��ȡ��Ʒ��Ǯ
	//������������int ����100
	int temp100price = 0;
	packet>>temp100price;
	float temp = ((float)temp100price)/100;
	goodsPrice_ = temp;
	//��ȡ��Ʒ����
	packet>>goodNumber_;
	//��ȡ��Ʒ��iconId
	packet>>iconId_;
	return true;
}

DoublePayData::DoublePayData()
{
	goodsRegisterId="";
	isDoublePay = 0;
}

DoublePayData::~DoublePayData()
{
	goodsRegisterId="";
	isDoublePay = 0;
}

bool DoublePayData::decodeTemplatePacketData(cobra_win::DPacket &packet)
{
	NFC_ParsePacketString(packet,goodsRegisterId);
	packet>>isDoublePay;
	return true;
}

PayGoodsControlDataHandler::PayGoodsControlDataHandler(){
	m_strPPOrderId = "";
	m_strPPGoodsId = "";
	m_strTempOrderld= "";
	m_GoodsCount = 0;
	m_CurVistorPayIndex = 0;
	m_isBInitmentEnv = false;
	m_isBPaylist = false;
	m_isBIAPCheck = false;
	m_isBIAPTick = false;
	m_IAPTickCount = 0;
	memset(m_ShowDoubleArray,0,sizeof(m_ShowDoubleArray));

}

PayGoodsControlDataHandler::~PayGoodsControlDataHandler(){
	ClearPayItemList();
}

void PayGoodsControlDataHandler::handlePacket(IPacket* packet){

}

bool PayGoodsControlDataHandler::init(){
	return true;
}

void PayGoodsControlDataHandler::onDestroy(){
	m_isBIAPCheck = false;
}

/*
	�����ֵ��ʯ�б���Ϣ
*/
void  PayGoodsControlDataHandler::ToServerRechargeListPacket(unsigned char channel)
{
#ifdef kSDK_CYOU_JBREAK_ENABEL
	CSPayItemListPacket packet(SDKLoginParam::_platform_cyou_jbreak_);
#else
    CSPayItemListPacket packet(channel);
#endif	
	packet.Send();
}

/*
	�����ֵȷ����Ϣ
*/
void  PayGoodsControlDataHandler::ToServerPaySurePacket(unsigned char channel,std::string iapid,std::string orderld,std::string transactReceipt)
{
#ifdef kSDK_CYOU_JBREAK_ENABEL
    CSPaySurePacket packet(SDKLoginParam::_platform_cyou_jbreak_,iapid,orderld,transactReceipt);
#else
    CSPaySurePacket packet(channel,iapid,orderld,transactReceipt);
#endif
	packet.Send();
}

PayGoodsData* PayGoodsControlDataHandler::ByRegisterIdFindGoodsData(std::string registerid)
{
	std::vector<PayGoodsData*>::iterator  posbegin = m_PayGoodsList.begin();
	std::vector<PayGoodsData*>::iterator  posend = m_PayGoodsList.end();
	for (posbegin;posbegin != posend;posbegin++)
	{
		if ((*posbegin)->goodsRegisterId_ == registerid)
		{
			return (*posbegin);
		}
	}
	return NULL;
}

void PayGoodsControlDataHandler::SureServerOrederBack(std::string strorderldTemp,unsigned char orderldstate)
{
	switch(orderldstate)
	{
	case _ENUM_STATE_PAYORDER_SUCCESS_: 
		//��������֤�ɹ�
		// ɾ��ϵͳ�����еĶ���
		{
			IAPSYSTEM->onVerifySuccess(strorderldTemp);
		}
		break;
	case _ENUM_STATE_PAYORDER_PAYMONEY_: 
		{
			IAPSYSTEM->onVerifyFailed(strorderldTemp,SysLangDataManager::get_instance2()->GetSysLangById(61));
		}
		break;
	case _ENUM_STATE_PAYORDER_FAIL_: 
		{
			IAPSYSTEM->onVerifyFailed(strorderldTemp,SysLangDataManager::get_instance2()->GetSysLangById(62));
		}
		break;
	}
}

void  PayGoodsControlDataHandler::LocalPayIAPCheck()
{
	// ������Ķ������͸���������֤
	std::map<std::string, LocalPlayerDataManager::_LOCAL_PLAYER_UNVERIFY_IAP_>& myList = LocalPlayerDataManager::get_instance2()->GetUnVerifyIAPList();
	std::map<std::string, LocalPlayerDataManager::_LOCAL_PLAYER_UNVERIFY_IAP_>::iterator iter   = myList.begin();
	std::map<std::string, LocalPlayerDataManager::_LOCAL_PLAYER_UNVERIFY_IAP_>::iterator iter_e = myList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		LocalPlayerDataManager::_LOCAL_PLAYER_UNVERIFY_IAP_& temp = iter->second;

		// �жϵ�ǰ������Id�����Id�Ƿ�ƥ��
		std::string strCurServerId = _to_event_param_(SERVERINFODATAINFO->GetCurrentServerId());
		std::string strCurPlayerId = _to_event_param_(ROLEINFODATAHANDLER->m_pRIData->instanceId_);

		if (temp.mServerId == strCurServerId && temp.mPlayerId == strCurPlayerId)
		{
			//���ش��ڵ�δ��֤�Ķ����뵱ǰ���id���ڷ�����ƥ��
			// ���͸���������֤
			ToServerPaySurePacket(SERVERINFODATAINFO->Get_Channel_ID(),temp.mProductId,temp.mTransactionId,temp.mTransactionReceipt);
		}
	}
}

void PayGoodsControlDataHandler::TimeTickToServerIapCheck()
{
	if (m_isBIAPTick)
	{
		m_IAPTickCount++;
		if (m_IAPTickCount >900) //30��
		{
			m_IAPTickCount = 0;

			m_isBIAPTick = false;

			LocalPayIAPCheck();
		}
	}
}


void  PayGoodsControlDataHandler::ClearPayItemList()
{
	std::vector<PayGoodsData*>::iterator  posbegin = m_PayGoodsList.begin();
	std::vector<PayGoodsData*>::iterator  posend = m_PayGoodsList.end();
	for (posbegin;posbegin != posend;posbegin++)
	{
		if (*posbegin)
		{
			delete (*posbegin);
			(*posbegin) = NULL;
		}
	}
	m_PayGoodsList.clear();
}

/*
	����֧��������Ϣ
*/
void PayGoodsControlDataHandler::ToServerAdditionPayInfo()
{
	CSAndroidPayInfoPacket packet;
	packet.Send();
	NFC_showCommunicationWating(true);
}

/*
	��ȡ����֧����Ϣ
*/
bool PayGoodsControlDataHandler::ReadPayAddtionPacketData(cobra_win::DPacket &packet)
{
	unsigned char count = 0;
	packet>>count;
	m_AndroidPayStr.clear();
	for (int i = 0; i < count; i++)
	{
		std::string temp;
		NFC_ParsePacketString(packet,temp);
		m_AndroidPayStr.push_back(temp);
	}
	return true;
}

void PayGoodsControlDataHandler::ToServerDoublePayInfo()
{
#ifdef kSDK_CYOU_JBREAK_ENABEL
    CSDoublePayInfoPacket packet(SDKLoginParam::_platform_cyou_jbreak_);
#else
    CSDoublePayInfoPacket packet(SERVERINFODATAINFO->Get_Channel_ID());
#endif
    packet.Send();
    
    
}
	/*
		�����ֵ����˫������
	*/
void PayGoodsControlDataHandler::ReadDoublePayInfoData(cobra_win::DPacket &packet)
{
	unsigned char count = 0;
	packet>>count;
	std::vector<DoublePayData>  DoublePayList;			//����˫��������
	for (int i = 0; i < count; i++)
	{
		DoublePayData temp;
		temp.decodeTemplatePacketData(packet);
		DoublePayList.push_back(temp);
	}

	std::vector<PayGoodsData*>::iterator  posbegin = m_PayGoodsList.begin();
	std::vector<PayGoodsData*>::iterator  posend = m_PayGoodsList.end();
	int index = 0;
	memset(m_ShowDoubleArray,0,sizeof(m_ShowDoubleArray));
	for (posbegin;posbegin != posend;posbegin++)
	{
		if (*posbegin)
		{
			std::vector<DoublePayData>::iterator  pos_be = DoublePayList.begin();
			std::vector<DoublePayData>::iterator  pos_end = DoublePayList.end();
			for (pos_be;pos_be != pos_end;pos_be++)
			{
				if ((*posbegin)->goodsRegisterId_ == (*pos_be).goodsRegisterId)
				{
                    
					if ((*pos_be).isDoublePay == 1)
					{
						if (index == 1)
						{
							m_ShowDoubleArray[0] = 1;
						}
						else if (index == 3)
						{
							m_ShowDoubleArray[1] = 1;
						}
						else if (index == 5)
						{
							m_ShowDoubleArray[2] = 1;
						}
					}
				}
			}
		}
		index++;
	}
}