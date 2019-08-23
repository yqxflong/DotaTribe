// Name :		MassacreDataHandler.h
// Function:	ɨ������
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef   _DOTATRIBE_MASSACREDATAHANDLER_H
#define   _DOTATRIBE_MASSACREDATAHANDLER_H

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>
#include <vector>
#include <string>

struct ItemData
{
	std::string     itemName;
	unsigned char	itemCount;
	int				itemID;
	int				iconID;
	unsigned char	quality;
	unsigned char	isEquip;	//1��װ�� 0����װ�������Ե��ӣ�
};

struct MassacreData
{
	int     money;
	int		roleExp;
	int		shapeExp;
	unsigned char itemCount;
	std::vector<ItemData*> ItemDataList;
};

class MassacreDataHandler:public IDataHandler,public cobra_win::Singleton2<MassacreDataHandler>{
public:
	unsigned char MassacreCount;
	unsigned char EndType;//0�ɹ�, 1������, 2��������, 3ɨ����������, 4����ȼ�����
	std::vector<MassacreData*> MassacreDataList;
public:
	MassacreDataHandler();
	virtual ~MassacreDataHandler(){};
	virtual bool init();
	virtual void onDestroy();
	//
	void ToServerPacket(int missionid,int stateid);
	void decodePacketData(cobra_win::DPacket & packet);
	void AfterDecodePacket();
	bool getCanForceCloseState();
	void setToForceCloseInitState();
public:
	bool MassacreCanForceClose;
};
#endif