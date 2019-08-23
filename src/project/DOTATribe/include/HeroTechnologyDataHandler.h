// Name :		HeroTechnologyDataHandler.h
// Function:	��������
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef   _DOTATRIBE_HEROTECHNOLOGYDATAHANDLER_H
#define   _DOTATRIBE_HEROTECHNOLOGYDATAHANDLER_H

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <map>
#include <vector>
#include <string>

struct HeroTechnology
{
	int Tag;
	unsigned char id;						//�Ƽ�ģ��id<br>
	std::string name;						//�Ƽ�����<br>
	int icon;								//�Ƽ�ͼ��<br>
	int costPoints;							//��������Ƽ�����<br>
	unsigned short level;					//�Ƽ��ȼ�<br>
	unsigned char attriType;				//Ӱ����������<br>
	unsigned short addValue;				//Ӱ��������ֵ<br>
	unsigned short nextLevelAddValue;		//��һ��Ӱ��������ֵ -1��ʾ�Ѿ�������<br>
};

class HeroTechnologyDataHandler:public IDataHandler,public cobra_win::Singleton2<HeroTechnologyDataHandler>{
public:

	int score;								//�Ƽ�����<br>
	unsigned short maxLevel;				//���Ƽ��ȼ�����<br>
	unsigned char count;					//�Ƽ�����<br>

	unsigned char TechnologyID;				//�Ƽ�ID
	int TechnologyNeedTime;					//�Ƽ�����ʱ��

	float Lasttime;							//��һ��ʱ��
	bool IsAsk;
	bool IsFirstAsk;
	int UpdateTechnologyID;					//�Ƽ�ID
	int	UpdateTechnologyTime;				//�Ƽ�ʱ��


	unsigned char m_free_pray_times;		//�����Ը����
	int	m_pray_cost;						//��Ը����
	std::vector<HeroTechnology*> HeroTechnologyList;
	float m_View_PosY;
	int m_TabNum;
	int m_ReturnWindow;
	int m_HideWindow;
	int m_ReturnTabNum;
public:
	HeroTechnologyDataHandler();
	virtual ~HeroTechnologyDataHandler();
	HeroTechnology* GetTechnologyByID(int id);
	virtual void handlePacket(IPacket* packet);
	virtual bool init();
	virtual void onDestroy();
};
#endif