//Name:EquipmentLvUpDataHandler.h
//Author:��ǿ
//Function:װ������������

#ifndef _DOTATRIBE_EQUIPMENTLVUPDATAHANDLER_H_
#define _DOTATRIBE_EQUIPMENTLVUPDATAHANDLER_H_


#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <map>
#include <vector>
#include "../include/BagEquipDataHandler.h"
#include "../include/RoleInfoDataHandler.h"

class EquipCardsStructure
{
public:
	BagEquipData* data;
	bool isSelected;
};

class EquipSwallowData
{
public:
	int equipId;					//װ��Id
	unsigned char swallowType;		//��������
	int addExp;						//���ɻ�þ���
	int useMoney;					//����

public:
	void decodePacket(cobra_win::DPacket & packet);
};

class EquipmentLvUpData
{
public:
	int level;						//װ���ȼ�
	int equipExp;				//װ������
	int equipMaxExp;			//װ�������
	int mainAttriMin;			//��������С
	int mainAttriMax;			//���������
	Attribute attribute;		//ͨ������
	Attribute attributeMax;		//ͨ���������ֵ
	unsigned short swallowCount;	//��������
	int	changeValue;				//ת����
	int	changeValueMax;				//���ת����
	std::vector<EquipSwallowData *>		swallowData;//��������
//2028

public:
	EquipmentLvUpData();
	~EquipmentLvUpData();

	void decodePacket(cobra_win::DPacket & packet);
};


class EquipmentLvUpDataHandler : public IDataHandler,public cobra_win::Singleton2<EquipmentLvUpDataHandler>
{
public:
	int selectedEquipId;

	BagEquipData selectEquip_StoreOnly;//��������������

	std::vector<int> vecEquipCostCard;	//�����ǽ����ģ����Ա��������ݣ�����new��delete
	
	std::vector<int> vecEquipCostMoney;

	int needMoneyAll;

	EquipmentLvUpData * equipLvUpData;

public:
	EquipmentLvUpDataHandler();
	virtual ~EquipmentLvUpDataHandler();

	virtual void handlePacket(IPacket* packet);

	/*
		���ٽӿ�
	*/
	virtual void onDestroy();

	/*
		�������
	*/
	void ClearData();
	/*
		��ʼ���ӿ�
	*/
	virtual bool init();

	/*
		���ѡ��Id��װ��
	*/
	BagEquipData * GetEquipById(int id);

	/*
		�ж�ѡ�еĿ������Ƿ�����ɫ����
	*/
	bool HasPurpleCard();
	/*
		�ж�ѡ�еĿ������Ƿ�����ɫ����
	*/
	bool HasOrangeCard();

	/*
		ѡ����ͷ�����ͨѶ��ȡ��ÿ����Ʒ���ѵĽ�Ǯ
	*/
	void toServerSelectCard();

	/*
		�������ͷ�����ͨѶ��ȡ�����ɽ��
	*/
	void toServerLvUp();

	/*
		�����洢����from�������ݿ�����to
	*/
	void CopyStore(BagEquipData * to,const BagEquipData * from);

	/*
		����֮����Ҫ�������Ľ����ֵ���ڴ�����Ӧװ����������
	*/
	void ChangeEquipInfoByLvUpResult();

	/*
		�������б���ȥ���Ե��Ŀ���
	*/
	void RemoveCardsFromCostList();

	/*
		����װ������������
	*/
	void HandleAfterEquipLvup();

	/*
		����Ƿ��������б���
	*/
	bool isInCostList(int equipID);

	/*
		����Ƿ��������б���
	*/
	bool isInMainList(int equipID);

	/*
		���cost�б��Ƿ�����װ����
	*/
	void checkCostList();

	/*
		��黨���Ƿ��㹻
	*/
	bool isMoneyEnough();
	//
	/*
		�������軨��
	*/
	void ResetMoney();
	/*
		��ʼ��װ�������ز��б�
	*/
	std::vector<EquipCardsStructure> GetEquipCostCardList();
	/*
		�����ĵȼ��Ƿ�������������
	*/
	bool IsMainCardMeetLevelCondition();
	/*
		��ȡ����
	*/
	BagEquipData* GetMainCard();
};

#define EQUIPMENTLVUPDATAHANDLER (EquipmentLvUpDataHandler::get_instance2())

#endif