//Name:EquipStrengthenDataHandler.h
//Author:��ǿ
//Function:װ��ǿ��

#ifndef _DOTATRIBE_EquipStrengthenDataHandler_H_
#define _DOTATRIBE_EquipStrengthenDataHandler_H_


#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <vector>

class BagEquipData;
class EquipStrengthenDataHandler : public IDataHandler,public cobra_win::Singleton2<EquipStrengthenDataHandler>
{
public:
	std::vector<BagEquipData*> RoleEquipList_;	//����װ�����б�
	std::vector<BagEquipData*> EquipList_;	//�������Ϻͱ�����װ��
	int m_HeroIndex;
public:
	EquipStrengthenDataHandler();
	virtual ~EquipStrengthenDataHandler(){};
	/*
		���ٽӿ�
	*/
	virtual void onDestroy();
	/*
		��ʼ���ӿ�
	*/
	virtual bool init();

	/*
		����װ��forװ������
	*/
	void LoadEquipList_EquipLvUp(int heroindex = 0);

	/*
		����װ��forװ������
	*/
	void LoadEquipList_Progress(int heroindex = 0);
	/*
		����װ��forװ��ϴ��
	*/
	void LoadEquipList_Train(int heroindex = 0);

	/*
	   ����װ��forװ���ֽ�
	*/
	void LoadEquipList_Recast();

	/*
		�������
	*/
	void ClearEquipList();

	/*
		�Ƿ���ڸ�װ��
		#��װ��
	*/
	bool CheckTheEquipExisted_RoleEquip(int equipID);

	/*
		�Ƿ���ڸ�װ��
		#ȫ��װ��
	*/
	bool CheckTheEquipExisted_All(int equipID);
private:
	inline void _loadBagEquipsToVec(std::vector<BagEquipData*>& vec);
	inline void _removeWhiteCard(std::vector<BagEquipData*>& vec);
	inline void _removeMaxAdvancedCard(std::vector<BagEquipData*>& vec);
	inline void _removeMaxLvCard(std::vector<BagEquipData*>& vec);
	inline void _removeExpBall(std::vector<BagEquipData*>& vec);
	//װ������ר��
	inline void _removeCardInCostList(std::vector<BagEquipData*>& vec);
};

#endif