// Name :		LessResourceDataHandler.h
// Function:	��Դ��������
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef _DOTATRIBE_LessResourceDataHandler_H_
#define _DOTATRIBE_LessResourceDataHandler_H_

#include <include/common/Singleton.h>
#include <include/mem/DPacket.h>
#include "../include/IDataHandler.h"
#include "../include/CPublicVarReader.h" 
#include <vector>
#include <string>

struct DoingData
{
	unsigned char	isOpen;
	unsigned char   id;
public:
	DoingData()
	{
		isOpen = 0;
		id = 0;
	}
	void  decodePacketData(cobra_win::DPacket & packet)
	{
		packet.read(isOpen);
		packet.read(id);
	}
};

class LessResourceDataHandler : public IDataHandler, public cobra_win::Singleton2<LessResourceDataHandler>
{
private:
	//VIP��תö��
	enum
	{
		Type_None,
		Type_Vip,
	};
	enum
	{
		_LESS_UNKONW_TYPE_,			//δ֪��������
		_LESS_POWER_TYPE_,			//��������
		_LESS_TOWER_TYPE_,			//����������
		_LESS_ARENA_TYPE_,			//������������
		_LESS_TREASUREHUNT_TYPE_,	//Ѱ������
		_LESS_TEAM_TYPE_,			//Զ��Ѱ������
	};

public:
		IByte			type;				//��Դ���� 1������ 2���������� 3���������� 4��Ѱ������ 5���ż�����
		std::string		tips;				//������Դ������ʾ
		IByte			jumpID;				//��ת���� 0,���� 1��vip
		IByte			hasNext;			//�Ƿ���Ҫ
		int				itemId;				//��ƷID
		int				iconId;				//����ͼ��ID
		IByte			quality;			//��ƷƷ��
		std::string		name;				//��Ʒ����
		std::string		description;		//����
		UShort			leftCount;		    //��Ʒʣ����
		int				leftUseTime;		//ʣ��ʹ�ô���
		 
	std::vector<DoingData*> DoingDataList;
	LessResourceDataHandler();
	virtual ~LessResourceDataHandler();
	virtual void onDestroy();
	virtual bool init();
	void JumpToVIP();
public:
	void  decodePacketHandler(cobra_win::DPacket & packet);
protected:
	void  destroyMemData();
};

#endif