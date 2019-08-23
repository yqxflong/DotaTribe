#ifndef  _DOTATRIBE_SOUNDDATAMANAGER_H_
#define  _DOTATRIBE_SOUNDDATAMANAGER_H_


#include "../include/IDataManager.h"
#include <include/common/Singleton.h>
#include <map>

#define   MAXPATH   256

class   SoundData: public IData
{
public:
	int	  id;							//实例id
	int   soundType;				    //声音类型
    int   soundID;					    //音频ID
	bool  soundIsCycle;				    //是否循环
	char  soundName[MAXPATH];	        //音频名称 (含路径)
	int	  soundVolume;				    //音频音量
public:
	SoundData();
	~SoundData();

public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};
 


class SoundDataManager : public IDataManager, public cobra_win::Singleton2<SoundDataManager>
{
public:
	std::map<int, SoundData*>  m_soundDataMap;

public:
	SoundDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~SoundDataManager();

public:
    SoundData * GetSoundData(int id);
	 
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
};
  
#endif
 