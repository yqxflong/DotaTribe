//Name：	HeroAltarContrnlDataHandler
//Function：献祭相关的控制器
//Written By：lvyunlong
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

//图腾数据
class TotemData
{
public:
	TotemData();
	~TotemData();
public:
	int type_;			//图腾类型
	int level_;			//等级
	int exp_;			//当前经验值
	int addvalue_;		//实行增加值
	int maxExp_;		//满级经验值
	int nextValue_;		//下一级增加的属性值
public:
	bool decodeTemplatePacketData(cobra_win::DPacket &packet);
};

//献祭数据
class AltarData
{
public:
	AltarData();
	~AltarData();
public:
	int itemId_;			//物品Id
	int iconId_;			//图标Id
	int quality_;			//物品品质
	unsigned short expadd_;	//消耗一个 增加的经验值
	
public:
	bool decodeTemplatePacketData(cobra_win::DPacket &packet);
};

//献祭碎片数据
class DebrisData
{
public:
	DebrisData();
	~DebrisData();
public:
	int itemId_;			//物品Id
	int count_;				//物品的count
	int quality_;			//物品品质
public:
	bool decodeTemplatePacketData(cobra_win::DPacket &packet);
};

//献祭对应数据表
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
	std::vector<TotemData*>	m_TotemDataList;				//图腾信息列表
	std::vector<AltarData*>	m_AltarDataList;				//献祭信息列表
	std::vector<DebrisData*> m_DebrisDataList;				//碎片信息列表
	std::vector<DebrisData*> m_ClickDebriList;				//点击的碎片列表
public:
	std::map<int,AltarCheckData*> m_pCheckAltarTable;		//献祭查看属性值和最大经验值对应表
	bool m_BinitAltarTable;
public:
	int m_CurAltarTypeData;										//记录
public:
	HeroAltarControlDataHandler();
	virtual ~HeroAltarControlDataHandler();
	/*
		当收到服务器相关包的时候，用此函数把对应包的数据转化成对应的数据结构
		存入map中，用于之后的内存中的增删改查
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
		比较碎片经验
	* /
	bool compareAltarData(AltarData*& a,AltarData*& b);
	/ *
		对收到的碎片排序
	* /
	void SortDebris();*/
	/*
		请求图腾信息
	*/
	void ToServerInfoTotemData();
	/*
		请求献祭信息
	*/
	void ToServerInfoAltarData();
	/*
		请求碎片信息
	*/
	void ToServerInfoDebris(unsigned char type);
	/*
		请求献祭 每级最大经验的表 
	*/
	void ToServerCheckAltarTable();
	/*
		更新当前现有碎片
	*/
	void UpdateSoulDebris();
	/*
		清除零碎片数据
	*/
	void RemoveZeroSoulDebrisList();
	/*
		通过等级查找当前献祭表
	*/
	AltarCheckData* ByLevelCheckAltarTable(int lv);
	/*
		魂碎片的可升到的等级
	*/
	bool AltarDebriLater(int curlevel,int SumExp,int &altarlaterlevel,int &altarlaterexp);
	/*
		通过等级返回当前献祭经验最高值
	*/
	int ByLevelCheckMaxExp(int lv);
	/*
		通过等级返回当前献祭加成值
	*/
	int ByLevelCheckAddValue_(int lv,int type);
	/*
		查看当前献祭是否有5或6星碎片
	*/
	bool FindClickIsSoulDebri();
	/*
		准许献祭最高级别
	*/
	int AllowMaxAltarLevel();

	/*
		需要多少TpyeStone类型石头升到满级
	*/
	int NeedSoulStoneTopLevel(int tyte,int curlevel,int curExp);
};

#define HEROALTARCONTROLDATAHANDLER	 HeroAltarControlDataHandler::get_instance2()
#endif