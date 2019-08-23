//Name:NetObjectTopsDataHandler.H
//Function:������Ʒtips���ݹ�����
//Author:fangjun
//date:20131014

#ifndef _DOTATRIBE_NETOBJECTTIPSWINDOW_DATAHANDLER_H_
#define _DOTATRIBE_NETOBJECTTIPSWINDOW_DATAHANDLER_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>
#include "../include/CSMapTable.h"
#include "../include/CPageScroll.h"
#include "../include/BagWindow.h"
#include <string>
#include <map>
#include "../include/BagOtherObjectHandler.h"


enum
{
	_ENUM_NETORCOMMONOBJECT_TYPE_ = 0,	//����tips��������tips
	_ENUM_WEAPONOBJECT_TYPE_,	//��������tips�������飩
};

class NetObjectTips
{
public:
	NetObjectTips();
	~NetObjectTips();
public:
	std::string name;
	short level;
	int price;
	std::string description;
	BagEquipData* pEquip_;
	bool isSalebtn_;
	int objectId;
	void decodePacketData(cobra_win::DPacket & packet);
};

class NetObjectTipsDataHandler: public IDataHandler, public cobra_win::Singleton2<NetObjectTipsDataHandler>{
public:
	NetObjectTips * m_pObjectTips;
	int m_templateId;
	std::map<int ,NetObjectTips*> m_NettipsList;
public:
	int m_iShowedTipsWindow;//��Ҫ��ʾtips��window

public:
	NetObjectTipsDataHandler();
	virtual ~NetObjectTipsDataHandler();
protected:

	virtual void handlePacket(IPacket* packet);

	virtual void onDestroy();

	virtual bool init();

public:
	void ToServerGetObjectTips(int templateId, int windowType);

	void ToClientGetObjectTips();
public:
	/*
		����������ϻ�õ�TIPS����
	*/
	void SaveQueryTipsData();
	/*
		��ֵ
	*/
	void AssignTipsData(NetObjectTips* lvalue,NetObjectTips* rvalue);
	/*
		�Ա����TIPS�������
	*/
	void ClearTipsDataList();
};

#define NETOBJECTTIPSDATAHANDLER (NetObjectTipsDataHandler::get_instance2())


#endif