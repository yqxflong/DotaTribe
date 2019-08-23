#ifndef   _DOTATRIBER_PARTICLEDATAMANAGER_H_
#define   _DOTATRIBER_PARTICLEDATAMANAGER_H_

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)

class   ParticleData : public IData
{
public:
     int   particleEffectID;		
	 short particleEffectPlayType;  //(0 粒子固有时间  1 绑定动作时间  2 持续时间)
	 int   particleEffectZOrder;
	 char  particleEffectFileName[128];
	 char  particleEffectBoneName[64];
	 float particleEffectXOffSet;
	 float particleEffectYOffSet;
	 float particleEffectAngleOffSet;
	 short particleEffectIsLocationFollow;
	 short particleEffectIsAngleFollow;
	 short particleEffectIsHangover;
	 short particleEffectIsBlendMode;	//是否启用混合模式
	 float particleEffectVarianceX;		//粒子X分布区间 -1 为读取Plist默认值
	 float particleEffectVarianceY;     //粒子Y分布区间 -1 为读取Plist默认值
	 bool  particleEffectIsBindBone; 
public:
	ParticleData();
	~ParticleData();

public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class ParticleDataManager : public IDataManager, public cobra_win::Singleton2<ParticleDataManager>
{
public:
	std::map<int, ParticleData*>  m_particleDataMap;

public:
	ParticleDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~ParticleDataManager();

public:
	
    ParticleData * GetParticleDataByID(int particleEffectID);

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
	friend   class   cobra_win::Singleton2<ParticleDataManager>;

};
  
#endif