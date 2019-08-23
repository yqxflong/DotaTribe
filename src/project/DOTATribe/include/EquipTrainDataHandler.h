//Name:EquipTrainDataHandler
//Function:װ��ϴ��
//Author:	fangjun
//Date:20130820

#ifndef _DOTATRIBE_EQUIPTRAIN_DATAHANDLER_H_
#define _DOTATRIBE_EQUIPTRAIN_DATAHANDLER_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>
#include "../include/BagEquipDataHandler.h"
#include <vector>
#include "../include/CSMapTable.h"

class AttributeLock{
public:
	int serial;
	int equipId;					//װ��Id
	unsigned char attributeIndex;	//��������

public:
	void decodePacketData(cobra_win::DPacket & packet);

};

class TrainData{
public:
	int equipId;
	Attribute attribute;		//ͨ������
	Attribute attributeMax;	//ͨ���������ֵ

	char moneyEnough;		//���Խ�����һ��ϴ��

public:
	void decodePacketData(cobra_win::DPacket & packet);

};

class EquipTrainDataHandler : public IDataHandler, public cobra_win::Singleton2<EquipTrainDataHandler>{
public:
	std::vector<int> m_vecEquipId;//���ӵ�е�װ����Id

	AttributeLock m_pLock;//�����ģ����յ���
	AttributeLock m_pUnLock;//���������յ���

	TrainData m_pTrainData;//װ��ϴ�����ݣ����յ���

	std::vector<int> m_vecEquipLockStatus;//װ�����������

	int m_iAttriPrice;//��������ϴ���۸�

	std::map<int, int> m_mapAttributeLockPosition;//��������λ�ö�Ӧ�㣬add at 20130830; ����keyΪ��id��valueΪ��Ʒ����index
	
	std::map<int, int> m_mapOneKeyTrainLastAttribute;//һ��ϴ�����ϴε�����
	std::map<int, int> m_mapOneKeyTrainLastAttributeMax;//һ��ϴ�����ϴε�����
	std::map<int, int> m_mapOneKeyAttributeLockPosition;//һ��ϴ�����ϴ������������Ե�λ�ö�Ӧ��

private:
	int m_iCurEquipId;	//��ǰѡ��ϴ����װ��

public:
	EquipTrainDataHandler();
	virtual ~EquipTrainDataHandler();

	int GetCurEquipId();

	void SetCurEquipId(int id);//�л���ǰװ��ʱ��Ҫ��װ������״̬���

public:
	void decodePacketData(cobra_win::DPacket & packet);


	virtual void handlePacket(IPacket* packet){};

	virtual void onDestroy(){};

	virtual bool init(){	return true;	};

public:

	//��������
	void ToServerLockAttribute(int serial, int equipId, int attriIndex);
	void ToClientLockAttributeResult();

	//��������
	void ToServerUnLockAttribute(int serial, int equipId, int attriIndex);
	void ToClientUnLockAttributeResult();
	
	//ϴ��
	void ToServerTrain(int equipId);
	void ToClientTrainResult();

	//���װ����״̬
	void ToServerGetAttributeLockStatus(int equipId);
	void ToClientGetAttributeLockStatusResult();

	//��õ�ǰװ������״̬
	void ToServerGetCurrentAttributeLockStatus();

	BagEquipData * GetEquipById(int id);

	BagEquipData * GetCurEquip();

	void AddLock(unsigned char index);

	void DeleteLock(unsigned char index);

	//ͨ����õ�ϴ������ı��ڴ���װ��������
	void ChangeEquipAttributeByTrainResult();

	//�ж�һ��װ���Ƿ��ܹ�����һ��ϴ��
	bool IsCurEquipCanOneKeyTrain();

	/*
		�������
	*/
	void ClearData();
};

#define EQUIPTRAINDATAHANDLER (EquipTrainDataHandler::get_instance2())

#endif