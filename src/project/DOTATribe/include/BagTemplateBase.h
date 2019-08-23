
#ifndef _DOTATRIBE_BAG_BASE_H_
#define _DOTATRIBE_BAG_BASE_H_


#include <include/mem/DPacket.h>
#include <string>
#include <vector>
using namespace std;

//���������б�����Ʒ��ģ����࣬����಻��ʵ��ֻ��Ϊ�ӿ�


class BagTemplateBase
{
public:
	unsigned char catogory_;		//����
	unsigned char type_;			//����
	int templateid_;				//��Ʒģ������
	std::string name_;				//����
	std::string description_;		//����
	unsigned short level_;			//��Ʒ����
	unsigned char quality_;			//Ʒ��
	int price_;						//���ۼ۸�-1���ɳ���
	unsigned char canUse_;		//�Ƿ��ʹ�� 1���� 0������<br>
public:
	BagTemplateBase()
	{
		level_ = 0;				//add at 2013-11-15,,by fangjun

	}

	virtual bool decodeTemplatePacketData(cobra_win::DPacket &packet) = 0;
};




//��ͨ��Ʒģ��
class ObjectTemplate:public BagTemplateBase{
public:
	//����ע�����ԣ��μ�BagTemplateBase
	//unsigned char catogory_;		//���� ��ͨ��Ʒ0��װ��1������Ӣ��2 <br>
	//unsigned char type_;				//���� ҩƷ�����䣬�ϳɣ��䷽������<br>
	//int templateid_;						//��Ʒģ��ID <br>
	//std::string name_;					//���� <br>
	//std::string description_;			//���� <br>
	//unsigned short level_;			//��Ʒ���� <br>
	//unsigned char quality_;			//Ʒ�� <br>
	int iconId_;							//ͼ��ID<br>
	unsigned short maxCount_;	//���ѵ����� <br>
	int sortIndex;				//����Id
	//int price_;								//���ۼ۸� -1�������Գ���<br>

	ObjectTemplate * __set(const ObjectTemplate * obj);
	virtual bool decodeTemplatePacketData(cobra_win::DPacket &packet);
};



/*
	װ��ģ��
*/

class EquipTemplate : public BagTemplateBase{
public:
	//����ע�����ԣ��μ�BagTemplateBase
	//unsigned char category_;		//����
	//unsigned char type_;			//���� <br>
	//int templateid_;					//װ��ģ��ģ��ID<br> 
	//std::string name_;				//���� <br>
	//std::string description_;		//����<br>
	//unsigned short level_;		//��Ʒ���� <br>
	unsigned short maxLevel_;		//��󼶱� <br>
	//unsigned char quality_;			//Ʒ�� <br>
	int iconId_;							//ͼ��ID <br>
	int iconBigId_;						//ͼ��ID <br>
	unsigned short maxCount_;						//���ѵ����� 1<br> 
	//int price_;								//���ۼ۸� -1�������Գ��� <br>
	unsigned char baseAttrType_;		//����������

	EquipTemplate * __set(const EquipTemplate * obj);
	virtual bool decodeTemplatePacketData(cobra_win::DPacket & packet);

};



/*
	����ģ��
*/

class SkinTemplate : public BagTemplateBase{
public:
	//����ע�����ԣ��μ�BagTemplateBase
	//unsigned char catogory_;				//���� ��ͨ��Ʒ0��װ��1������Ӣ��2 <br>
    //unsigned char type_;					//���� <br>
	//int templateid_;						//��Ʒģ��ID <br>
	//std::string name_;						//���� <br>
	//std::string  description_;				//���� <br>
	//unsigned char quality_;					//Ʒ�� <br>
	std::vector<int> iconid_;					//ͷ��ID1~3
	std::vector<int> shapeid_;					//����ID1~3
	unsigned short maxCount_;				//���ѵ����� 1 <br>
	//int price_;								//���ۼ۸� -1�������Գ��� <br>
	unsigned char maxEnhanceLevel_;			//����ǿ���ȼ�<br>
	unsigned char strConverRate_;					//����ת��<br>  //add 7.30
	unsigned char agiConverRate_;					//����ת��<br>  //add 7.30
	unsigned char intConverRate_;					//����ת��<br> //add 7.30
	unsigned char mianConverRate_;				//������ת��<br> //add 7.30
	int waaponid_;							//ר������ģ��ID <br>
	int weaponIconId_;						//ר������ͼ��ID<br>
	std::string  weaponname_;				//ר���������� <br>
	std::string weaponDesc_;			//ר���������� <br>
	unsigned short buffId_;					//��ЧID <br>
	unsigned char buffLevel_;				//��Ч���� <br>
	int buffIconId_;						//��ЧID<br>
	std::string buffName_;					//��Ч���� <br>
	std::string buffDesc_;			//��Ч���� <br>
	unsigned short skillId_;				//ר������ID <br>
	unsigned char skllLevel_;				//ר�����ܼ��� <br>
	std::string skillName_;					//ר����������<br>
	std::string skllDesc_;					//ר���������� <br>

	virtual bool decodeTemplatePacketData(cobra_win::DPacket & packet);

	SkinTemplate &operator =(const SkinTemplate& bb){
		catogory_=bb.catogory_;
		type_=bb.type_;
		templateid_=bb.templateid_;
		name_=bb.name_;
		description_=bb.description_;
		quality_=bb.quality_;
		iconid_=bb.iconid_;
		shapeid_=bb.shapeid_;
		maxCount_=bb.maxCount_;	
		price_=bb.price_;	
	    maxEnhanceLevel_=bb.maxEnhanceLevel_;
		strConverRate_=bb.strConverRate_;
	    agiConverRate_=bb.agiConverRate_;
		intConverRate_=bb.intConverRate_;
		mianConverRate_=bb.mianConverRate_;
		waaponid_=bb.waaponid_;
		weaponIconId_=bb.weaponIconId_;
		weaponname_=bb.weaponname_;
		weaponDesc_=bb.weaponDesc_;
		buffId_=bb.buffId_;
		buffLevel_=bb.buffLevel_;
		buffIconId_=bb.buffIconId_;
		buffName_=bb.buffName_;
		buffDesc_=bb.buffDesc_;	
		skillId_=bb.skillId_;
		skllLevel_=bb.skllLevel_;
		skillName_=bb.skillName_;
		skllDesc_=bb.skillName_;
		return *this;
	}
};




#endif
