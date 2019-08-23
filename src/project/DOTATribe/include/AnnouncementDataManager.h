#ifndef  _DOTATRIBE_ANNOUNCEMENTDATAMANAGET_H_
#define  _DOTATRIBE_ANNOUNCEMENTDATAMANAGET_H_
 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>

#pragma pack(push, 1)
class AnnouncementData : public IData
{
public:
     int   announcementStyleID;
	 int   announcementFontStyleID;
	 float announcementVisiableRightX;
	 float announcementVisiableLeftX;
	 float announcementVisiableY;
	 float announcemenrScrollSpeed;
	 float announcementIntervalTime;
	 short announcementRepeatCount;
public:
	AnnouncementData();
	virtual ~AnnouncementData();
public:
	/*
		解析数据
	*/
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};
#pragma pack(pop)


class AnnouncementDataManager : public IDataManager, public cobra_win::Singleton2<AnnouncementDataManager>
{
public:
	std::map<int , AnnouncementData*>   m_AnnouncementDataList;

public:
	AnnouncementDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~AnnouncementDataManager();

public:
	/*
		得到指定位置的动画信息
	*/
	AnnouncementData* GetAnnouncementDataByID(int announcementStyleID);
  
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
	friend   class   cobra_win::Singleton2<AnnouncementDataManager>;
};


#endif
