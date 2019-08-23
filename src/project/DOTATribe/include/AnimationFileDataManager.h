#ifndef  _DOTATRIBE_ANIMATIONFILEDATAMANAGER_H_
#define  _DOTATRIBE_ANIMATIONFILEDATAMANAGER_H_


#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)
class AnimationFileData : public IData
{
public:
	int	  mAnimationIndex;		  // 索引
	char  mAnimationName[128];    // 动画名称
	char  mAnimationPrefix[128];  // 动画名称前缀一般都是XXX_0.png
	int   mAnimationFrameCount;   // 动画帧个数
	float mAnimationIntervalTime; // 动画间隔时间
	char  mAnimationFileName[128];// 动画的pList文件名称
	float mAnimationScale;		  // 动画缩放系数
	int   mAnimationUISoundID;	  // 动画UI特效 音效ID

public:
	AnimationFileData();
	virtual ~AnimationFileData();

public:
	/*
		解析数据
	*/
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};
#pragma pack(pop)


class AnimationFileDataManager : public IDataManager, public cobra_win::Singleton2<AnimationFileDataManager>
{
public:
	std::map<int , AnimationFileData*> m_AnimationFileList;

public:
	AnimationFileDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~AnimationFileDataManager();

public:
	/*
		得到动画个数
	*/
	unsigned int GetAnimationNumber();
	/*
		得到指定位置的动画信息
	*/
	AnimationFileData* GetAnimationByIdx(unsigned int index);
	/*
		根据名称得到动画信息
	*/
	AnimationFileData* GetAnimationByName(std::string name);
	/*
	   根据索引获得动画所在Plist文件名称
	   */
	std::string      GetAnimationPlistNameByID(int animationID);	 
public:
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
	friend   class   cobra_win::Singleton2<AnimationFileDataManager>;
};


#endif
