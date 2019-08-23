#ifndef   _DOTATRIBE_BULLETDATAMANAGER_H
#define   _DOTATRIBE_BULLETDATAMANAGER_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)

class   BulletData: public IData
{
public:
	  int    bulletItemID_;					 //子弹ID
	  float  bulletStartRelativelyXPos_;     //子弹初始相对位置
      float  bulletStartRelativelyYPos_;     //子弹初始相对位置
	  int    bulletAnimationID;              //子弹动画ID
	  int    bulletAnimationInterval_;       //子弹动画帧间隔
	  float  bulletMoveSpeed_;               //子弹移动速度
	  float  bulletEndRelativelyXPos_;       //子弹结束时相对位置
	  float  bulletEndRelativelyYPos_;       //子弹结束时候相对位置
	  char   bulletExplosionName[128];       //子弹爆炸的动画
	  float  bulletExplosionInterval_;       //子弹爆炸帧的间隔
	 
public:
	BulletData();
	~BulletData();

public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class BulletDataManager : public IDataManager, public cobra_win::Singleton2<BulletDataManager>
{
public:
	std::map<int, BulletData*>  m_bulletMapList;

public:
	BulletDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~BulletDataManager();

public:
	
    BulletData * GetBulletDataByID(int skillItemID);

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
	friend   class   cobra_win::Singleton2<BulletDataManager>;

};
  
#endif