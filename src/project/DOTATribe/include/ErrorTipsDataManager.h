#ifndef  _DOTATRIBE_ERROETIPSDATAMANAGER_H
#define  _DOTATRIBE_ERROETIPSDATAMANAGER_H
 
#include "../include/IDataManager.h"
#include <include/common/Singleton.h>
#include <map> 

class   ErrorTipsData: public IData
{
public:
	int    errorFontStyleID;				//字体ID
	char   errorBackImageFilePath[128];		//字体背景图片路径
	float  errorWidth;						//字体宽度
	float  errorHeight;						//字体高度
	float  errorAnchorX;					//字体锚点X
	float  errorAnchorY;					//字体锚点Y
	float  errorRelateY;					//字体响度屏幕Y的0.5的高度
	float  errorAddHeight;					//递增式高度
	int    errorMaxLevel;					//最大递增数
	float  errorDurationTime;				//持续时间
	float  errorFadeOutTime;				//渐隐触发时间
public:
	ErrorTipsData();
	~ErrorTipsData();

public:
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};
 


class ErrorTipsDataManager : public IDataManager, public cobra_win::Singleton2<ErrorTipsDataManager>
{
protected: 
	ErrorTipsData  *   m_pErrorTipsData;
public:
	ErrorTipsDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~ErrorTipsDataManager();

public: 
	/*
	获取错误提示数据
	*/
	ErrorTipsData *  GetErrorTipsData(); 
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
 