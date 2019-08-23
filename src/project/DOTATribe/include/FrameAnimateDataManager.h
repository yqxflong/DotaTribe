#ifndef   _DOTATRIBE_FRAMEANIMATEDATAMANAGER_H_
#define   _DOTATRIBE_FRAMEANIMATEDATAMANAGER_H_
 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)


  
class   FrameAnimateData : public IData
{
public:
    int   frameAnimateEffectID;					//帧动画 特效配置ID
	short frameAnimateEffectPlayType;			//帧动画 特效播放方式
	int   frameAnimateEffectZOrder;				//帧动画 特效ZOrder层级
	int   frameAnimateEffectAnimationID;		//帧动画 特效播放动画ID
	char  frameAnimateEffectBoneName[64];		//帧动画 特效播放绑定骨骼名称
	float frameAnimateEffectXOffSet;			//帧动画 特效播放X偏移
	float frameAnimateEffectYOffSet;			//帧动画 特效播放Y偏移
	float frameAnimateEffectAngleOffSet;		//帧动画 角度偏移
	short frameAnimateIsLocationFollow;			//帧动画	 是否位置跟随
	short frameAnimateIsAngleFollow;			//帧特效 角度跟随
	bool  frameAnimateIsBoneBindEffect;			//帧动画 是否为骨骼特效
public:
	FrameAnimateData();
	~FrameAnimateData();
public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class  FrameAnimateDataManager : public IDataManager, public cobra_win::Singleton2<FrameAnimateDataManager>
{
public:
	std::map<int, FrameAnimateData*>  m_frameAnimateDataMap;

public:
	FrameAnimateDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~FrameAnimateDataManager();

public:
	
    FrameAnimateData * GetFrameAnimateDataByID(int frameAniamtionEffectID);

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
	friend   class   cobra_win::Singleton2<FrameAnimateDataManager>;

};
  
#endif