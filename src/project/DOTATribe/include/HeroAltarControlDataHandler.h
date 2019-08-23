//Name��	HeroAltarContrnlDataHandler
//Function���׼���صĿ�����
//Written By��lvyunlong
//Date:20131202

#ifndef   _DOTATRIBE_HEROALTARCONTRILDATAHANDLER_H_
#define   _DOTATRIBE_HEROALTARCONTRILDATAHANDLER_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <map>
#include <vector>
#include <string>
#include <cocos2d.h>
#include "../include/VariableSystem.h"
#include <include/mem/DPacket.h>
using namespace std;

enum
{
	_ENUM_TYPE_STRENGTH = 0,
	_ENUM_TYPE_NIMBLE,
	_ENUM_TYPE_MENTALITY,
};

enum
{
	_ENUM_TYPE_DEBRIS_0 = 0,
	_ENUM_TYPE_DEBRIS_1,
	_ENUM_TYPE_DEBRIS_2,
	_ENUM_TYPE_DEBRIS_3,
	_ENUM_TYPE_DEBRIS_4,
	_ENUM_TYPE_DEBRIS_5,
};

//ͼ������
class TotemData
{
public:
	TotemData();
	~TotemData();
public:
	int type_;			//ͼ������
	int level_;			//�ȼ�
	int exp_;			//��ǰ����ֵ
	int addvalue_;		//ʵ������ֵ
	int maxExp_;		//��������ֵ
	int nextValue_;		//��һ�����ӵ�����ֵ
public:
	bool decodeTemplatePacketData(cobra_win::DPacket &packet);
};

//�׼�����
class AltarData
{
public:
	AltarData();
	~AltarData();
public:
	int itemId_;			//��ƷId
	int iconId_;			//ͼ��Id
	int quality_;			//��ƷƷ��
	unsigned short expadd_;	//����һ�� ���ӵľ���ֵ
	
public:
	bool decodeTemplatePacketData(cobra_win::DPacket &packet);
};

//�׼���Ƭ����
class DebrisData
{
public:
	DebrisData();
	~DebrisData();
public:
	int itemId_;			//��ƷId
	int count_;				//��Ʒ��count
	int quality_;			//��ƷƷ��
public:
	bool decodeTemplatePacketData(cobra_win::DPacket &packet);
};

//�׼���Ӧ���ݱ�
class AltarCheckData
{
public:
	AltarCheckData();
	~AltarCheckData();
public:
	unsigned short level_;
	unsigned short addNextvalue_[3];
	int	maxExp_;
public:
	bool decodeTemplatePacketData(cobra_win::DPacket &packet);
};

class HeroAltarControlDataHandler:public IDataHandler,public cobra_win::Singleton2<HeroAltarControlDataHandler>{

public:
	std::vector<TotemData*>	m_TotemDataList;				//ͼ����Ϣ�б�
	std::vector<AltarData*>	m_AltarDataList;				//�׼���Ϣ�б�
	std::vector<DebrisData*> m_DebrisDataList;				//��Ƭ��Ϣ�б�
	std::vector<DebrisData*> m_ClickDebriList;				//�������Ƭ�б�
public:
	std::map<int,AltarCheckData*> m_pCheckAltarTable;		//�׼��鿴����ֵ�������ֵ��Ӧ��
	bool m_BinitAltarTable;
public:
	int m_CurAltarTypeData;										//��¼
public:
	HeroAltarControlDataHandler();
	virtual ~HeroAltarControlDataHandler();
	/*
		���յ���������ذ���ʱ���ô˺����Ѷ�Ӧ��������ת���ɶ�Ӧ�����ݽṹ
		����map�У�����֮����ڴ��е���ɾ�Ĳ�
	*/
	virtual void handlePacket(IPacket* packet);
	virtual bool init();
	virtual void onDestroy();
public:
	void ClearTotemInfoList();
	void ClearAltarInfoList();
	void ClearDebrisInfoList();
	void ClearClickDebriList();
	void ClearCheckAltarInfoTable();
public:
/*
	/ *
		�Ƚ���Ƭ����
	* /
	bool compareAltarData(AltarData*& a,AltarData*& b);
	/ *
		���յ�����Ƭ����
	* /
	void SortDebris();*/
	/*
		����ͼ����Ϣ
	*/
	void ToServerInfoTotemData();
	/*
		�����׼���Ϣ
	*/
	void ToServerInfoAltarData();
	/*
		������Ƭ��Ϣ
	*/
	void ToServerInfoDebris(unsigned char type);
	/*
		�����׼� ÿ�������ı� 
	*/
	void ToServerCheckAltarTable();
	/*
		���µ�ǰ������Ƭ
	*/
	void UpdateSoulDebris();
	/*
		�������Ƭ����
	*/
	void RemoveZeroSoulDebrisList();
	/*
		ͨ���ȼ����ҵ�ǰ�׼���
	*/
	AltarCheckData* ByLevelCheckAltarTable(int lv);
	/*
		����Ƭ�Ŀ������ĵȼ�
	*/
	bool AltarDebriLater(int curlevel,int SumExp,int &altarlaterlevel,int &altarlaterexp);
	/*
		ͨ���ȼ����ص�ǰ�׼��������ֵ
	*/
	int ByLevelCheckMaxExp(int lv);
	/*
		ͨ���ȼ����ص�ǰ�׼��ӳ�ֵ
	*/
	int ByLevelCheckAddValue_(int lv,int type);
	/*
		�鿴��ǰ�׼��Ƿ���5��6����Ƭ
	*/
	bool FindClickIsSoulDebri();
	/*
		׼���׼���߼���
	*/
	int AllowMaxAltarLevel();

	/*
		��Ҫ����TpyeStone����ʯͷ��������
	*/
	int NeedSoulStoneTopLevel(int tyte,int curlevel,int curExp);
};

#define HEROALTARCONTROLDATAHANDLER	 HeroAltarControlDataHandler::get_instance2()
#endif