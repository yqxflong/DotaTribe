#ifndef   _DOTATRIBE_SKILLEFFECTDATAMANAGER_H
#define   _DOTATRIBE_SKILLEFFECTDATAMANAGER_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)

class   SkillEffectData : public IData
{
public:
   	  int    skillEffectItemID;					    //特效ID
	  short  skillEffectZOrder;						//特效的层级
	  short  skillEffecIsLoop;						//特效是否循环
	  float  skillEffectSoundTriggerTime;			//特效音效触发时间	   单位为MS
	  int    skillEffectSoundID;					//特效的音效ID
	  short  skillEffectAnchorPoint;				//特效的相对锚点
	  float  skillEffectXOffSet;					//特效的X轴偏移
	  float  skillEffectYOffSet;					//特效的Y轴偏移
	  short  skillEffectIsFollow;					//特效是否伴随
	  float  skillEffectRoleEffectTime;				//特效伴随角色的效果触发时间点  单位MS
	  int    skillEffectRoleEffectID;				//特效角色效果ID
	  int	 skillEffectAnimationID;				//特效动画ID
	  float  skillEffectShakeTriggerTime;			//特效震动触发时间点   单位MS
	  int    skillEffectShakeID;					//特效震动ID
public:
	SkillEffectData();
	~SkillEffectData();

public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class SkillEffectDataManager : public IDataManager, public cobra_win::Singleton2<SkillEffectDataManager>
{
public:
	std::map<int, SkillEffectData*>  m_skillEffectMapList_;

public:
	SkillEffectDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~SkillEffectDataManager();

public:
	
    SkillEffectData * GetSkillEffectByID(int skillItemID);

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
	friend   class   cobra_win::Singleton2<SkillEffectDataManager>;

};
  
#endif