#ifndef   _DOTATRIBE_NUMBERBUFFERDATAMANGER_H
#define   _DOTATRIBE_NUMBERBUFFERDATAMANGER_H

 
 
#include  <include/common/Singleton.h>
#include  "IDataManager.h"
#include  <cocos2d.h>
#include  <string>
#include  <map>

#pragma pack(push, 1)

class   NumberBufferData: public IData
{
public:
	  int    numberBufferFormatID;					 //数字Buffer格式ID
	  int    numberBufferFontType;					 //数字字体库ID
	  float  numberBufferScale;						 //数字Buffer的初始缩放比例
	  float  numberBufferMaxScale;					 //数字Buffer的最大缩放比例		 
	  float  numberBufferScaleDurationTime;			 //数字Buffer的缩放时间
	  float  numberBufferInitHeigh;					 //数字Buffer的初始高度
	  float  numberBufferEndHeigh;					 //数值Buffer的结束高度
	  float  numberBufferDurationTime;				 //数值Buffer的持续时间			    //单位MS
	  float  numberBufferTriggerFadeOutTime;		 //数值Buffer的开始逐渐消失时间点    //单位MS
	  bool   numberBufferIsNeedScale;				 //数字Buffer是否需要缩放
public:
	NumberBufferData();
	~NumberBufferData();
public:
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class  NumberBufferDataManager: public IDataManager, public cobra_win::Singleton2<NumberBufferDataManager>
{
public:
	std::map<int, NumberBufferData*>  m_numberBufferMapList;

public:
	NumberBufferDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~NumberBufferDataManager();

public:
	
    NumberBufferData * GetNumberBufferDataByID(int numberBufferID);

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
	friend   class   cobra_win::Singleton2<NumberBufferDataManager>;

};








#endif 