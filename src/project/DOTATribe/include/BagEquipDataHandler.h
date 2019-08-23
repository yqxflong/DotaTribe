//Name��BagEquipData
//Function��������װ������
//				    ��Packet��Ӧ
//Written By����ǿ
#ifndef   _DOTATRIBE_BAGEQUIPDATAHANDLER_H
#define   _DOTATRIBE_BAGEQUIPDATAHANDLER_H

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <map>
#include <vector>
#include "../include/CSMapTable.h"
#include "../include/IBagData.h"
#include <string>
#include <include/mem/DPacket.h>
#include "../include/BagTemplateBaseHandler.h"
#include "../include/BagTemplateBase.h"

/*
* if(װ��)װ������<br>
* { 
* byte type ���� <br>
* int templateid װ��ģ��ģ��ID<br> 
* String name ���� <br>
* String  description ����<br> 
* short level ��Ʒ���� <br>
* short maxLevel ��󼶱� <br>
* byte quality Ʒ�� <br>
* int iconId ͼ��ID <br>
* int iconBigId ��ͼ��ID<br>
* int maxCount ���ѵ����� 1<br> 
* int price ���ۼ۸� -1�������Գ��� <br>
===================================
* int id װ��ID<br> 
* short level ��ǰ����<br>
* int exp ��ǰ����<br>
* int maxexp �����<br>
* Attributes���� <br>
* byte attrCount ��������<br>
* for(attrCount){ 
* byte atttype ��������<br>
* int value ����ֵ<br>
* } <br>
* }<br>
*/


class BagEquipData:public IBagData{
public:
	EquipTemplate* template_;		//ģ��
	int id_;										//װ��ID<br> 
	unsigned short level_;						    	 //��ǰ����<br>

	unsigned short levelMax_;							//���ȼ���add 20131210

	int exp_;									// ��ǰ����<br>
	int maxexp_;								// �����<br>

	unsigned char advanceLevel_;				//���׵ȼ���add 20131210
	unsigned char advanceLevelMax_;				//�����׵ȼ���add 20131210

	int mainAttriValue;							//������ֵ������������Ϊ��������Ϊ��С������
	int mainAttriValueMax;						//��������Ϊ��������Ϊ��󹥻�
	int equipScore_;						//װ������<br>
	Attribute* attribute_;					//ͨ������
	Attribute* attributeMAX_;					//ͨ���������ֵ
	
	int RoleHeroindexEquip_;

	/*��ʱ����
	unsigned short buffId_;			//��ЧID <br>
	unsigned char buffLevel_;		//��Ч���� <br>
	int buffIconId_;						//��Чͼ��ID<br>
	std::string buffName_;			//��Ч���� <br>
	std::string buffdescription_;			// ��Ч���� <br>
	*/
	//Cache
	bool isEquiped_;	//�Ƿ�װ��

	BagEquipData(){
		template_=new EquipTemplate();
		attribute_=new Attribute();
		attributeMAX_=new Attribute();
		isEquiped_=0;
		RoleHeroindexEquip_ = 0;
	}

	BagEquipData(EquipTemplate* et)
	{
		template_ = et;
		attribute_=new Attribute();
		attributeMAX_=new Attribute();
		isEquiped_=0;
		RoleHeroindexEquip_ = 0;
	}

	virtual ~BagEquipData(){
		assert(template_!=NULL);
		delete template_;
		assert(attribute_!=NULL);
		delete attribute_;
		assert(attributeMAX_!=NULL);
		delete attributeMAX_;
	}

	BagEquipData * __set(const BagEquipData * obj);

	void decodePacketData(cobra_win::DPacket & packet);

};


class BagEquipDataHandler:public IDataHandler,public cobra_win::Singleton2<BagEquipDataHandler>{
public:
	/*
		�뽫new��֮���dataװ���list����������ʱ������
	*/
	std::vector<BagEquipData*> m_vecList;

	bool m_bHaveNewItem;//ӵ������Ʒ

	unsigned short m_bagMaxCount;//�˱����а���������������ѽ���
	BagEquipData* m_BagEquipTipsData;
public:
	BagEquipDataHandler();
	virtual ~BagEquipDataHandler();

	virtual bool init();
	virtual void onDestroy();

	void ClearBagEquipList();

	int refreshChangeData(BagEquipData * bed);

	int setObjectCount(int index, int count);

	BagEquipData * getEquipById(int id);

	//�ȴ������ң�û����ȥ������
	BagEquipData* getEquipByAllEquips(int id);

	//��װ��
	void saleObject(int equipId, int num);

	/*
	��ȡָ����Ʒtemplateid����Ʒ����
	*/
	int getObjectCountByTemplateId(int tid);

	/*
		���չ�������װ��
		1.Ʒ��(�͵���)	 2.�ȼ�		3.��ƷID
		װ���ز��б�װ�������زģ�
	*/
	void reorderBagEquips_equiplvup_costcards();


	/*
		Ӣ��װ��ר������
		1.type(С����)  2.Ʒ�ʣ���С�� 3.�ȼ�(��С) 4.ID����С��
	*/
	void reorderEquipListForHeroEquip();

	/*
		װ��ǿ��ר������
		1.Ʒ�ʣ���С��  2.type(С����)   3.�ȼ�(��С)
	*/
	void reorderEquipListForEquipStrengthen();

	/*
		���� 1.Ʒ�ʽ��򡪡�2.���׵ȼ����򡪡�3.ID����
		��ȡװ��������װ���б�
	*/
	std::vector<BagEquipData *>getRoleEquipsForEquipRecast();


public:
	static BagEquipDataHandler * LuaGetInstance(){
		return BagEquipDataHandler::get_instance2();
	}
};
#define BAGEQUIPDATAHANDLER	 BagEquipDataHandler::get_instance2()
#endif