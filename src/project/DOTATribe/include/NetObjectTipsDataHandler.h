//Name:NetObjectTopsDataHandler.H
//Function:网络物品tips数据管理器
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
	_ENUM_NETORCOMMONOBJECT_TYPE_ = 0,	//网络tips或者特殊tips
	_ENUM_WEAPONOBJECT_TYPE_,	//特殊武器tips（经验珠）
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
	int m_iShowedTipsWindow;//需要显示tips的window

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
		保存从网络上获得的TIPS数据
	*/
	void SaveQueryTipsData();
	/*
		赋值
	*/
	void AssignTipsData(NetObjectTips* lvalue,NetObjectTips* rvalue);
	/*
		对保存的TIPS数据清空
	*/
	void ClearTipsDataList();
};

#define NETOBJECTTIPSDATAHANDLER (NetObjectTipsDataHandler::get_instance2())


#endif