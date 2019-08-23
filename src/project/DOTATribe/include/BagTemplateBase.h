
#ifndef _DOTATRIBE_BAG_BASE_H_
#define _DOTATRIBE_BAG_BASE_H_


#include <include/mem/DPacket.h>
#include <string>
#include <vector>
using namespace std;

//作用于所有背包物品的模版基类，这个类不再实现只作为接口


class BagTemplateBase
{
public:
	unsigned char catogory_;		//分类
	unsigned char type_;			//类型
	int templateid_;				//物品模版类型
	std::string name_;				//名称
	std::string description_;		//描述
	unsigned short level_;			//物品级别
	unsigned char quality_;			//品质
	int price_;						//出售价格，-1不可出售
	unsigned char canUse_;		//是否可使用 1可用 0不可用<br>
public:
	BagTemplateBase()
	{
		level_ = 0;				//add at 2013-11-15,,by fangjun

	}

	virtual bool decodeTemplatePacketData(cobra_win::DPacket &packet) = 0;
};




//普通物品模板
class ObjectTemplate:public BagTemplateBase{
public:
	//以下注释属性，参见BagTemplateBase
	//unsigned char catogory_;		//分类 普通物品0，装备1，外套英雄2 <br>
	//unsigned char type_;				//类型 药品，宝箱，合成，配方，其他<br>
	//int templateid_;						//物品模板ID <br>
	//std::string name_;					//名称 <br>
	//std::string description_;			//描述 <br>
	//unsigned short level_;			//物品级别 <br>
	//unsigned char quality_;			//品质 <br>
	int iconId_;							//图标ID<br>
	unsigned short maxCount_;	//最大堆叠数量 <br>
	int sortIndex;				//排序Id
	//int price_;								//出售价格 -1代表不可以出售<br>

	ObjectTemplate * __set(const ObjectTemplate * obj);
	virtual bool decodeTemplatePacketData(cobra_win::DPacket &packet);
};



/*
	装备模板
*/

class EquipTemplate : public BagTemplateBase{
public:
	//以下注释属性，参见BagTemplateBase
	//unsigned char category_;		//分类
	//unsigned char type_;			//类型 <br>
	//int templateid_;					//装备模板模板ID<br> 
	//std::string name_;				//名称 <br>
	//std::string description_;		//描述<br>
	//unsigned short level_;		//物品级别 <br>
	unsigned short maxLevel_;		//最大级别 <br>
	//unsigned char quality_;			//品质 <br>
	int iconId_;							//图标ID <br>
	int iconBigId_;						//图标ID <br>
	unsigned short maxCount_;						//最大堆叠数量 1<br> 
	//int price_;								//出售价格 -1代表不可以出售 <br>
	unsigned char baseAttrType_;		//主属性类型

	EquipTemplate * __set(const EquipTemplate * obj);
	virtual bool decodeTemplatePacketData(cobra_win::DPacket & packet);

};



/*
	外套模板
*/

class SkinTemplate : public BagTemplateBase{
public:
	//以下注释属性，参见BagTemplateBase
	//unsigned char catogory_;				//分类 普通物品0，装备1，外套英雄2 <br>
    //unsigned char type_;					//类型 <br>
	//int templateid_;						//物品模板ID <br>
	//std::string name_;						//名称 <br>
	//std::string  description_;				//描述 <br>
	//unsigned char quality_;					//品质 <br>
	std::vector<int> iconid_;					//头像ID1~3
	std::vector<int> shapeid_;					//形象ID1~3
	unsigned short maxCount_;				//最大堆叠数量 1 <br>
	//int price_;								//出售价格 -1代表不可以出售 <br>
	unsigned char maxEnhanceLevel_;			//最大可强化等级<br>
	unsigned char strConverRate_;					//力量转化<br>  //add 7.30
	unsigned char agiConverRate_;					//敏捷转化<br>  //add 7.30
	unsigned char intConverRate_;					//智力转化<br> //add 7.30
	unsigned char mianConverRate_;				//主属性转化<br> //add 7.30
	int waaponid_;							//专属武器模板ID <br>
	int weaponIconId_;						//专属武器图标ID<br>
	std::string  weaponname_;				//专属武器名称 <br>
	std::string weaponDesc_;			//专属武器描述 <br>
	unsigned short buffId_;					//特效ID <br>
	unsigned char buffLevel_;				//特效级别 <br>
	int buffIconId_;						//特效ID<br>
	std::string buffName_;					//特效名称 <br>
	std::string buffDesc_;			//特效描述 <br>
	unsigned short skillId_;				//专属技能ID <br>
	unsigned char skllLevel_;				//专属技能级别 <br>
	std::string skillName_;					//专属技能名称<br>
	std::string skllDesc_;					//专属技能描述 <br>

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
