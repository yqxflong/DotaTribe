//Name��BagOtherObject
//Function������������Ʒ����
//				    ��Packet��Ӧ
//Written By����ǿ
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
* byte catogory ���� ��ͨ��Ʒ0��װ��1������Ӣ��2 <br>
* byte type ���� ҩƷ������Ʒ<br>
* int templateid ��Ʒģ��ID <br>
* String name ���� <br>
* String description ���� <br>
* short level ��Ʒ���� <br>
* byte quality Ʒ�� <br>
* int iconId ͼ��ID<br>
* short maxCount ���ѵ����� <br>
* byte canUse �Ƿ��ʹ�� 1���� 0������<br>
* int price ���ۼ۸� -1�������Գ���<br>
* int id ��ƷID<br>
*/

//�ϳ�������������
//��չ���ϳ�Ŀ��id���ϳ����������ѽ�Ǯ����Ҫ��Ʒid����Ҫ��������Ҫ��Ʒid����Ҫ����
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
	ObjectTemplate* template_;	//ģ��
	int id_;									// ��ƷID<br>

	//��ͨ��Ʒ��catogoryΪ0�����type��2��3�������Ǻϳɻ����䷽
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
		�뽫new��֮���dataװ���list����������ʱ������
	*/
	std::vector<BagOtherObject*> m_vecList;

	bool m_bHaveNewItem;//ӵ������Ʒ

	unsigned short m_bagMaxCount;//�˱����а���������������ѽ���
public:
	BagOtherObjectHandler();
	virtual ~BagOtherObjectHandler();
	/*
		���յ���������ذ���ʱ���ô˺����Ѷ�Ӧ��������ת���ɶ�Ӧ�����ݽṹ
		����map�У�����֮����ڴ��е���ɾ�Ĳ�
	*/
	virtual void handlePacket(IPacket* packet);
	virtual bool init();
	virtual void onDestroy();

	void ClearBagObjectList();

	//�ͷ�����ͨѶ��������Ʒ
	void saleObject(BagOtherObject * object, int num);

	//�ͷ�����ͨѶ��ʹ����Ʒ
	void useObject(BagOtherObject * object, int num);

public:
	int refreshChangeData(BagOtherObject * boo);//����ֵΪ����Ʒ�ڴ洢���е�λ��

	int setObjectCount(int index, int count);

	void refreshUI4DataChanged();

public:
	/*
		��ñ������ܹ��ϳɵ���������
	*/
	int getBagObjectCanComposeNum();

	/*
		���ݿɺϳɵ�id���ӱ������ҵ�����ɺϳɵ���Ʒ
	*/
	BagOtherObject * getBagObjectByCanIndex(int idx);

	/*
		�ҵ������Ʒλ�ڿɺϳ���Ʒ�еĵڼ���
		����1������Ʒ�б��е�λ��
		����2���Ƿ�������λ��
	*/

	int getIndexFromCanComposeList(int objectId, bool includeThisId);

	/*
		����index,��ñ����е���Ʒ,�ڶ�����Ϊ�����б��е�idx
	*/
	BagOtherObject * getBagObjectByIndex(int allindex, int & smallidx);

	/*
		��ȡĳ����Ʒ����Ʒ��������templateid����
	*/
	int getObjectCountByTemplateId(int id);


	BagOtherObject*  getObjectByTemplateId(int tid);

	/*
		���չ�������װ��
		1.Ʒ��	 2.�ȼ�		3.��ƷID
		װ���б�Ӣ��װ�����桢ϴ����
	*/
	void reorderBagObject();

};
#define BAGOTHEROBJECTHANDLER	 BagOtherObjectHandler::get_instance2()
#endif