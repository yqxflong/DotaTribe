//Name：BagEquipData
//Function：管理背包装备数据
//				    与Packet对应
//Written By：尹强
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
* if(装备)装备数据<br>
* { 
* byte type 类型 <br>
* int templateid 装备模板模板ID<br> 
* String name 名称 <br>
* String  description 描述<br> 
* short level 物品级别 <br>
* short maxLevel 最大级别 <br>
* byte quality 品质 <br>
* int iconId 图标ID <br>
* int iconBigId 大图标ID<br>
* int maxCount 最大堆叠数量 1<br> 
* int price 出售价格 -1代表不可以出售 <br>
===================================
* int id 装备ID<br> 
* short level 当前级别<br>
* int exp 当前经验<br>
* int maxexp 最大经验<br>
* Attributes属性 <br>
* byte attrCount 属性数量<br>
* for(attrCount){ 
* byte atttype 属性类型<br>
* int value 属性值<br>
* } <br>
* }<br>
*/


class BagEquipData:public IBagData{
public:
	EquipTemplate* template_;		//模板
	int id_;										//装备ID<br> 
	unsigned short level_;						    	 //当前级别<br>

	unsigned short levelMax_;							//最大等级，add 20131210

	int exp_;									// 当前经验<br>
	int maxexp_;								// 最大经验<br>

	unsigned char advanceLevel_;				//进阶等级，add 20131210
	unsigned char advanceLevelMax_;				//最大进阶等级，add 20131210

	int mainAttriValue;							//主属性值，（若主属性为攻击，则为最小攻击）
	int mainAttriValueMax;						//若主属性为攻击，则为最大攻击
	int equipScore_;						//装备评分<br>
	Attribute* attribute_;					//通用属性
	Attribute* attributeMAX_;					//通用属性最大值
	
	int RoleHeroindexEquip_;

	/*暂时不加
	unsigned short buffId_;			//特效ID <br>
	unsigned char buffLevel_;		//特效级别 <br>
	int buffIconId_;						//特效图标ID<br>
	std::string buffName_;			//特效名称 <br>
	std::string buffdescription_;			// 特效描述 <br>
	*/
	//Cache
	bool isEquiped_;	//是否装备

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
		请将new过之后的data装入该list，会在析构时候销毁
	*/
	std::vector<BagEquipData*> m_vecList;

	bool m_bHaveNewItem;//拥有新物品

	unsigned short m_bagMaxCount;//此背包中包格最大数量，即已解锁
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

	//先从身上找，没有再去背包找
	BagEquipData* getEquipByAllEquips(int id);

	//卖装备
	void saleObject(int equipId, int num);

	/*
	获取指定物品templateid的物品个数
	*/
	int getObjectCountByTemplateId(int tid);

	/*
		按照规则排序装备
		1.品质(低到高)	 2.等级		3.物品ID
		装备素材列表（装备升级素材）
	*/
	void reorderBagEquips_equiplvup_costcards();


	/*
		英雄装备专用排序
		1.type(小到大)  2.品质（大到小） 3.等级(大到小) 4.ID（大到小）
	*/
	void reorderEquipListForHeroEquip();

	/*
		装备强化专用排序
		1.品质（大到小）  2.type(小到大)   3.等级(大到小)
	*/
	void reorderEquipListForEquipStrengthen();

	/*
		排序 1.品质降序——2.进阶等级降序——3.ID升序
		获取装备重铸的装备列表
	*/
	std::vector<BagEquipData *>getRoleEquipsForEquipRecast();


public:
	static BagEquipDataHandler * LuaGetInstance(){
		return BagEquipDataHandler::get_instance2();
	}
};
#define BAGEQUIPDATAHANDLER	 BagEquipDataHandler::get_instance2()
#endif