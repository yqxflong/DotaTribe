//Name：BagOtherObject
//Function：背包其他物品数据
//				    与Packet对应
//Written By：尹强
#ifndef   _DOTATRIBE_BAGOTHEROBJECTHANDLER_H
#define   _DOTATRIBE_BAGOTHEROBJECTHANDLER_H

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <map>
#include <vector>
#include "../include/IBagData.h"
#include <include/mem/DPacket.h>
#include "../include/BagTemplateBaseHandler.h"
#include "../include/BagTemplateBase.h"

/*
* byte catogory 分类 普通物品0，装备1，外套英雄2 <br>
* byte type 类型 药品，任务品<br>
* int templateid 物品模板ID <br>
* String name 名称 <br>
* String description 描述 <br>
* short level 物品级别 <br>
* byte quality 品质 <br>
* int iconId 图标ID<br>
* short maxCount 最大堆叠数量 <br>
* byte canUse 是否可使用 1可用 0不可用<br>
* int price 出售价格 -1代表不可以出售<br>
* int id 物品ID<br>
*/

//合成所需其他数据
//扩展：合成目标id，合成数量，花费金钱，需要物品id，需要数量，需要物品id，需要数量
class ComposeDetail
{
public:
	BagTemplateBase * destObject_;
	unsigned short destCount_;
	int costMoney_;
	std::vector<BagTemplateBase *> needObjectList_;
	std::vector<unsigned short> needObjectNumList_;
public:
	ComposeDetail()
	{
		destObject_ = NULL;
		needObjectList_.clear();
		needObjectNumList_.clear();
	}
	virtual ~ComposeDetail()
	{
		if(destObject_ != NULL)
		{
			delete destObject_;
			destObject_ = NULL;
		}

		std::vector<BagTemplateBase *>::iterator it = needObjectList_.begin();
		std::vector<BagTemplateBase *>::iterator itend = needObjectList_.end();
		for(; it != itend; ++it)
		{
			delete *it;
			*it = NULL;
		}
		needObjectList_.clear();

		needObjectNumList_.clear();

	}
	void _addObject(BagTemplateBase * obj, int num)
	{
		needObjectList_.push_back(obj);
		needObjectNumList_.push_back(num);
	}

};


class BagOtherObject:public IBagData{
public:
	ObjectTemplate* template_;	//模板
	int id_;									// 物品ID<br>

	//普通物品，catogory为0，如果type是2和3，那他是合成或者配方
	ComposeDetail * composeDetail_;

	BagOtherObject(){
		template_=new ObjectTemplate();
		composeDetail_ = NULL;
		//composeDetail_ = new ComposeDetail();
	}

	BagOtherObject(ObjectTemplate * ot)
	{
		template_ = ot;
		composeDetail_ = NULL;
		//composeDetail_ = new ComposeDetail();
	}

	virtual ~BagOtherObject(){
		if(template_)
		{
			delete template_;
			template_ = NULL;
		}
		if(composeDetail_)
		{
			delete composeDetail_;
			composeDetail_ = NULL;
		}
	}

	BagOtherObject * __set(const BagOtherObject * obj);

	void decodePacketData(cobra_win::DPacket & packet);
};

class BagOtherObjectHandler:public IDataHandler,public cobra_win::Singleton2<BagOtherObjectHandler>{
public:
	/*
		请将new过之后的data装入该list，会在析构时候销毁
	*/
	std::vector<BagOtherObject*> m_vecList;

	bool m_bHaveNewItem;//拥有新物品

	unsigned short m_bagMaxCount;//此背包中包格最大数量，即已解锁
public:
	BagOtherObjectHandler();
	virtual ~BagOtherObjectHandler();
	/*
		当收到服务器相关包的时候，用此函数把对应包的数据转化成对应的数据结构
		存入map中，用于之后的内存中的增删改查
	*/
	virtual void handlePacket(IPacket* packet);
	virtual bool init();
	virtual void onDestroy();

	void ClearBagObjectList();

	//和服务器通讯，出售物品
	void saleObject(BagOtherObject * object, int num);

	//和服务器通讯，使用物品
	void useObject(BagOtherObject * object, int num);

public:
	int refreshChangeData(BagOtherObject * boo);//返回值为此物品在存储器中的位置

	int setObjectCount(int index, int count);

	void refreshUI4DataChanged();

public:
	/*
		获得背包中能够合成的物体总数
	*/
	int getBagObjectCanComposeNum();

	/*
		根据可合成的id，从背包中找到这个可合成的物品
	*/
	BagOtherObject * getBagObjectByCanIndex(int idx);

	/*
		找到这个物品位于可合成物品中的第几个
		参数1，在物品列表中的位置
		参数2，是否包含这个位置
	*/

	int getIndexFromCanComposeList(int objectId, bool includeThisId);

	/*
		根据index,获得背包中的物品,第二参数为传出列表中的idx
	*/
	BagOtherObject * getBagObjectByIndex(int allindex, int & smallidx);

	/*
		获取某种物品的物品个数，由templateid决定
	*/
	int getObjectCountByTemplateId(int id);


	BagOtherObject*  getObjectByTemplateId(int tid);

	/*
		按照规则排序装备
		1.品质	 2.等级		3.物品ID
		装备列表（英雄装备界面、洗炼）
	*/
	void reorderBagObject();

};
#define BAGOTHEROBJECTHANDLER	 BagOtherObjectHandler::get_instance2()
#endif