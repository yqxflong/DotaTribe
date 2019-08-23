//Name�� RoleEquipDataHandler
//Function������Ӣ�۵�װ��
//Author��Johny

#ifndef   _DOTATRIBE_ROLEEQUIPDATAHANDLER_H
#define   _DOTATRIBE_ROLEEQUIPDATAHANDLER_H

#include "../include/IDataHandler.h"
#include "../include/BagEquipDataHandler.h"
#include <map>
#include <cocos2d.h>


class RoleEquipData{
public:
	unsigned char index_;						//װ������λ��<br>
	unsigned char hasEquip_;					//0�� 1��<br>
	BagEquipData* equipdata_;				//װ������
	RoleEquipData(){
		equipdata_=0;
	}

	RoleEquipData(BagEquipData * bed)
	{
		equipdata_ = bed;
		equipdata_->isEquiped_ = 1;
	}

	virtual ~RoleEquipData(){
		if (!equipdata_)return;
		delete equipdata_;
	}

	void refreshEquipData(BagEquipData * bed);
};

class RoleEquipDataHandler:public IDataHandler{
private:
	int m_offequip_type;
public:
	std::map<int,RoleEquipData*> m_mapEquipList;
	int HeroEquip_Tab_IsSelected;	//Ӣ��װ�����棬����ѡ�е�ҳǩ
public:
	RoleEquipDataHandler();
	virtual ~RoleEquipDataHandler(){};

	virtual bool init();
	virtual void onDestroy();

	void decodePacketData(cobra_win::DPacket & packet);

	BagEquipData * getEquipById(int id);

	BagEquipData * getEquipByType(int etype);

	//������е�����װ��
	std::vector<BagEquipData*> getRoleEquips();

	/*
		���չ�������װ��
		Type	
	*/
	std::vector<BagEquipData*> getRoleEquipsByType();

	/*
		����ǿ��װ��ר��
		1.Ʒ�ʣ���С��  2.type(С����)   3.�ȼ�(��С)
	*/
	std::vector<BagEquipData*> getRoleEquipsForStrengthen();
	 
	/*
		��ȡһ��Ĭ�ϵ�����װ��
	*/
	BagEquipData* GetDefaultRoleEquip_EquipLvup();

	/*
		����Ƿ��п���������װ��
	*/
	bool CheckAllRoleEquipsCanTopup();

public:
	//begin:жװ�����
	void OffEquip_Request(int equipid,int heroPos);
	void decodePacketData_OffEquip(cobra_win::DPacket & packet);
	void HanldeAfterOffEquip();
	void OffEquip_Local(int equipType);
	//end

	//begin:����װ��
	void ChangeEquip_Request(int equipid,int heroPos);
	void decodePacketData_ChangeEquip(cobra_win::DPacket & packet);
	void HanldeAfterChangeEquip();
	//end
};

#endif