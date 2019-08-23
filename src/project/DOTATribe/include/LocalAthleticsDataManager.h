#ifndef _DOTATRIBE_LOCALATHLETICSDATA_MANAGER_H_
#define _DOTATRIBE_LOCALATHLETICSDATA_MANAGER_H_
////////////////////////////////////////////////////////////////
//Name:	 LocalAthleticDataManager
//Auchor: 	xiaobo.wu
//Func:	 本地缓存战斗序列管理器
//Maintainer: 	xiaobo.wu
//date:   2014/04/17
////////////////////////////////////////////////////////////////
  
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <map>
#include <list>
#include <vector>
#include <string>
#include <include/mem/EPacket.h>
#include <include/mem/DPacket.h>
#include <include/mem/MemNode.h>

using  namespace  cobra_win;


 
typedef struct _cache_buffer_
{
public:
	char *  m_pBuffer;
	size_t  m_nSize;
	int		m_nMapID;
	int		m_nStageID;
public:
	_cache_buffer_(cobra_win::DPacket & packet,int mapID,int stageID)
	{
		m_nMapID = mapID;
		m_nStageID = stageID;
		m_pBuffer = new char[packet.size()+1];
		memset(m_pBuffer,0,sizeof(m_pBuffer));
		memcpy(m_pBuffer,packet.get_packet_buff(),packet.size());
		m_nSize = packet.size();
	}
	_cache_buffer_(cobra_win::DPacket & packet,size_t size,int mapID,int stageID)
	{
		m_nMapID = mapID;
		m_nStageID = stageID;
		m_pBuffer = new char[packet.size()+1];
		memset(m_pBuffer,0,sizeof(m_pBuffer));
		packet.read(m_pBuffer,size);
		m_nSize = size;
	}
   ~_cache_buffer_()
   {
	   delete [] m_pBuffer;
	   m_pBuffer = NULL;
	   m_nSize = 0;
   }
}CacheBuffer,*PCacheBuffer;



class LocalAthleticsDataManager : public IDataManager, public cobra_win::Singleton2<LocalAthleticsDataManager>
{ 
private:
	bool			m_bIsNeedSaveToDisk;
	bool			m_bIsNeedAppendSave;
	std::string		m_lastLocalKey;
public:
	std::map<std::string,PCacheBuffer>	m_vSaveDataPacketVector;		
public: 
	LocalAthleticsDataManager(bool bLoadFromDB, bool bEncryption):IDataManager(bLoadFromDB, bEncryption){m_bIsNeedAppendSave=false;m_bIsNeedSaveToDisk=false;m_lastLocalKey="";};
	virtual ~LocalAthleticsDataManager(){};

	/*
		压入战斗信息 For 关卡战斗
	*/
	void  PushAthleticsDPacket(DPacket & packet,int mapID,int stageID);

	PCacheBuffer GetAthleticsDPacket(int mapID,int stageID);

	/*
		设置需要存盘
	*/
	void  SetNeedSaveToDisk(bool saveEnable);
	/*
		设置是否追加存盘
	*/
	void SetNeedAppendSave(bool	 appendSaveEnable);

public:
    /*
        获得对应数据管理器对应资源的名称（可为文件，也可以为数据库表名称）
    */
    virtual   std::string  GetName();
	/*
		得到对应的数据管理器内存占用大小
	*/
	virtual   unsigned int GetSize();
public:
	/*
        初始化数据管理器
    */
	virtual   bool   Init();
	/*
        数据管理器桢更新
    */
	virtual   void   Tick();
	/*
        销毁数据管理器
    */
	virtual   void   Destroy();
	/*
		重新加载数据管理器
	*/
	virtual   bool   Reload();
    
private:
    /*
        加载对应的资源文件
    */
    virtual   bool   LoadFromFile();
    /*
        加载对应的资源流信息
    */
    virtual   bool   LoadFromDB();

public:
	/*
		校验加载的数据(单行数据的有效性校验)
	*/
	virtual   bool   Varify(IData* pData);
	/*
		校验加载的数据(所有数据加载完之后进行的表与表关联性校验)
	*/ 
	virtual   bool   VarifyAfterLoadAll(); 
protected:
	/*
		创建指定的ItemData数据
	*/
	virtual   bool   LoadData(char* pBuffer, unsigned int iBufferLen);
private:
	/*
		加载文件
	*/
	char* LoadDBFile(std::string fileName, long& length);
	/*
		同步保存
	*/
	void  SaveToFile();

	/*
	    保持数据到数据包
	*/
	void  SaveDataToPacket(EPacket & packet);

	/*
		同步到初始状态(一般文件校验失败，则直接设置为初始状态)
	*/
	void  SynToInitialization();

private:
	/*
		加载存档文件
	*/
	bool  LoadFromFileA(char* pBuffer, unsigned int iBufferLen);

	/*
		从总数据包中解码
	*/
	bool  LocadDataFromDPacket(DPacket & packet);
    
private:
	friend   class   Singleton2<LocalAthleticsDataManager>;

};

 
#endif