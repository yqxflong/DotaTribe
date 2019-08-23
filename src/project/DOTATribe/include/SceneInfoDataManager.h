


#ifndef   _DOTATRIBE_SCENEINFODATAMANAGER_H
#define   _DOTATRIBE_SCENEINFODATAMANAGER_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)

class   SceneInfoData: public IData
{
public:
	int  mId; 									//ID
	char mSceneInfoPicture[128];				//场景图片
	char mSceneInfoPicture_tab[128];			//场景小图
	char mSceneInfoPicture_mission[128];		//场景关卡小图
	char mSceneInfoPicture_mission_boss[128];	//BOSS关卡小图
	char mSceneInfoPicture_mission_reward[128];	//3星奖励小图
	int  mEffectId1; 							//特效1
	int  mEffectId2; 							//特效2
	int  mEffectId3; 							//特效3
	int  mSoundID;								//背景音乐ID
	int  mSceneName;							//场景名字
public:
	SceneInfoData();
	~SceneInfoData();

public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class SceneInfoDataManager: public IDataManager, public cobra_win::Singleton2<SceneInfoDataManager>
{
public:
	std::map<int, SceneInfoData*> m_SceneInfoDataList;

public:
	SceneInfoDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~SceneInfoDataManager();

public:
	/*
	获取关卡配置信息结点
	*/
    SceneInfoData * GetCustomPassDataByID(int customsPassUniqueId);

	/*
	获取关卡名称
	*/
	std::string     GetCustomNameByID(int missionID);

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
	friend   class   cobra_win::Singleton2<SceneInfoData>;

};
  
#endif