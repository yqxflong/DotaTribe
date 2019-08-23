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
		得到对应的数据管理器名称
	*/
	virtual  std::string   GetName();
	/*
		得到对应的数据管理器内存占用大小
	*/
	virtual  unsigned  int GetSize();

public:
	/*
		初始化数据管理器
	*/
	virtual  bool  Init();
	/*
		数据管理器帧更新处理
	*/
	virtual  void  Tick();
	/*
		销毁数据管理器
	*/
	virtual  void  Destroy();

public:
	/*
		校验加载的数据(单行数据的有效性校验)
	*/
	virtual  bool  Varify(IData* pData);
	/*
		校验加载的数据(所有数据加载完之后进行的表与表关联性校验)
	*/
	virtual  bool  VarifyAfterLoadAll();

protected:
	/*
		创建指定的ItemData数据
	*/
	virtual  bool  LoadData(char* pBuffer, unsigned int iBufferLen);

private:
	friend   class   cobra_win::Singleton2<CompositeEffectDataManager>;

};
  
#endif