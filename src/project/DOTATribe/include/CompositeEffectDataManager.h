#ifndef   _DOTATRIBE_COMPOSITEEFFECTDATAMANAGER_H_
#define   _DOTATRIBE_COMPOSITEEFFECTDATAMANAGER_H_

  
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)

#define   _MAX_EFFECT_NODE_COUNT_		 6 

 
enum
{
	_CompositeEffect_UnKonw_Type_=-1,
	_CompositeEffect_SoundEffect_Type_,
	_CompositeEffect_FrameAniamteEffect_Type_,
	_CompositeEffect_ParticleEffect_Type_,
	_CompositeEffect_SkeletonEffect_Type_,
	_CompositeEffect_ShakeEffect_Type_,
	_CompositeEffect_RoleEffect_Type_,
	_CompositeEffect_ScreenEffect_Type_,

};


typedef struct effectdata_tag
{
    int  effectType;
	int  effectID;
	float effectTriggerTime;
public:
	effectdata_tag()
	{
	    effectType=-1;
		effectID=-1;
		effectTriggerTime=0.0f;
	}
	effectdata_tag(const effectdata_tag & data)
	{
		effectType=data.effectType;
		effectID=data.effectID;
		effectTriggerTime=data.effectTriggerTime;
	}
}CEffectData,*PCEffectData;

class   CompositeEffectData : public IData
{
public:
   	  int    compositeEffectID;
	  int    soundEffectID;
	  float  soundEfefctTriggerTime;
	  int    compositeEffectCount;
	  std::vector<CEffectData> compositeEffectVec;
public:
	CompositeEffectData();
	~CompositeEffectData();
public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class CompositeEffectDataManager : public IDataManager, public cobra_win::Singleton2<CompositeEffectDataManager>
{
public:
	std::map<int, CompositeEffectData*>  m_compositeEffectMap;

public:
	CompositeEffectDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~CompositeEffectDataManager();

public:
	
    CompositeEffectData * GetCompositeEffectDataByID(int compositeEffectID);

	/*
		�õ���Ӧ�����ݹ���������
	*/
	virtual  std::string   GetName();
	/*
		�õ���Ӧ�����ݹ������ڴ�ռ�ô�С
	*/
	virtual  unsigned  int GetSize();

public:
	/*
		��ʼ�����ݹ�����
	*/
	virtual  bool  Init();
	/*
		���ݹ�����֡���´���
	*/
	virtual  void  Tick();
	/*
		�������ݹ�����
	*/
	virtual  void  Destroy();

public:
	/*
		У����ص�����(�������ݵ���Ч��У��)
	*/
	virtual  bool  Varify(IData* pData);
	/*
		У����ص�����(�������ݼ�����֮����еı���������У��)
	*/
	virtual  bool  VarifyAfterLoadAll();

protected:
	/*
		����ָ����ItemData����
	*/
	virtual  bool  LoadData(char* pBuffer, unsigned int iBufferLen);

private:
	friend   class   cobra_win::Singleton2<CompositeEffectDataManager>;

};
  
#endif