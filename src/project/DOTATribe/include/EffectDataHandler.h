//Name�� EffectDataHandler
//Function��Ч��������
//Written By����ǿ

#ifndef   _DOTATRIBE_EffectDataHandler_H
#define   _DOTATRIBE_EffectDataHandler_H

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>
#include <list>
#include <string>
#include <vector>

enum{
	kEFFECT_OBJECT,	//��Ʒ
	kEFFECT_OBJECTBJ,	//��Ʒ����
	kEFFECT_NUM,	//��ֵ
	kEFFECT_NUMBJ,//��ֵ����
};

enum{
	kEFFECT_TYPE_OBJECT=0,			//��Ʒ
	kEFFECT_TYPE_MONEY,				//���
	kEFFECT_TYPE_EXP,						//����
	kEFFECT_TYPE_DIAMOND,	//��ʯ
	kEFFECT_TYPE_TL,		//����
	kEFFECT_TYPE_STR,		//����
	kEFFECT_TYPE_DEX,		//����
	kEFFECT_TYPE_INTEL,		//����
	kEFFECT_TYPE_PRESTAGE,	//����
	kEFFECT_TYPE_EXPLOIT,		//��ѫ
	kEFFECT_TYPE_HERO_EXP,		//hero Exp
	kEFFECT_TYPE_EQUIP_EXP,		//Equip Exp
	kEFFECT_TYPE_ATTR_MAXHP,					//���HP
	kEFFECT_TYPE_ATTR_MAXMP,					//���MP
	kEFFECT_TYPE_ATTR_SPEED,					//�ٶ�
	kEFFECT_TYPE_ATTR_MIN_ATTACK,			//��С������
	kEFFECT_TYPE_ATTR_MAX_ATTACK,		//��󹥻���
	kEFFECT_TYPE_ATTR_ARMOR,					//����
	kEFFECT_TYPE_ATTR_EXPOSEARMOR,			//�Ƽ�
	kEFFECT_TYPE_ATTR_HIT,				//����
	kEFFECT_TYPE_ATTR_DODGE,		//����
	kEFFECT_TYPE_ATTR_CRIT,			//����
	kEFFECT_TYPE_ATTR_UNCRIT,		//����
};


/*
	һ��Ч������
*/
class EffectData{
public:
//����
private:
	int type_;			//����
	int iconID_;		//��Ʒ����
	std::string iconKey_;		//��ֵ����
	int count_;		//��ֵ
	int bjcount_;	//���Ϊ���������ʾ����
//~~~~�����ȡ
public:
	std::string iconPath_;
	float animaTime_;
	float fadeoutStartTime_;	//��ʼ����ʱ��
	float beginPosY_;
	float endPosY_;
	float scale_;
	std::vector<int> vecFonts_;		//ÿ���ֶ�Ӧ������--��ֵ
	std::vector<int> vecFonts_BJ_;		//ÿ���ֶ�Ӧ������--��ֵ����
public:
	EffectData(int type,int iconID,const char* iconKey,int count,int bjcount){
		type_=type;
		iconID_=iconID;
		iconKey_=iconKey;
		count_=count;
		bjcount_=bjcount;
	}
	int getType()const{
		return type_;
	}
	int getIConID()const{
		return iconID_;
	}
	const char* getIConKey()const{
		return iconKey_.c_str();
	}
	int getCount()const{
		return count_;
	}
	int getBJCount()const{
		return bjcount_;
	}
};


class EffectDataHandler:public IDataHandler,public cobra_win::Singleton2<EffectDataHandler>{
public:
	std::list<EffectData*>	effectList_;
public:
	EffectDataHandler(){};
	virtual ~EffectDataHandler(){};
	virtual bool init();
	virtual void onDestroy();
private:
	inline void _registerEvent();
	inline void _unRegisterEvent();
	/*
		ͬ����ֵ
	*/
	void Effect_GetNum(int key,int count);
	/*
		ͬ����ֵ,����
	*/
	void Effect_GetNumBJ(int key,int count,int bjcount);
	/*
		ͬ����Ʒ
	*/
	void Effect_GetObject(int iconid,int count);
	/*
		ͬ����Ʒ����
	*/
	void Effect_GetObjectBJ(int iconid,int count,int bjcount);

	//ʹ�����delete��
	void pushToEffectList(EffectData* dd);
private:
	inline void _handleIcon(EffectData* dd);
	inline int _handleAnima(EffectData* dd);
	inline void _handleNum(EffectData* dd,int fonttype);
	inline void _handleBJ(EffectData* dd,int fonttype);
public:
	/*
		�������Է������İ�����ʵ��Ʈ��
	*/
	void decodePacketData(cobra_win::DPacket & packet);
	void HandleAfterOnePacket();

	/*
		ʵ��Ʈ�ֽӿ�
	*/
	void ShowFlowEffect(int type,int count,int bjcount,int itemiconid=0);

	//����EffectHandler
	void OpenEffectHandler();

	//�������Ч��
	static void ClearEffectList(int iEventType, std::string owerData, std::list<std::string>& paramList);
};
#define EFFECTDATAHANDLER	 EffectDataHandler::get_instance2()
#endif