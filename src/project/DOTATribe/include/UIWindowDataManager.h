#ifndef  _DOTATRIBE_UIWINDOWDATAMANAGER_H_
#define  _DOTATRIBE_UIWINDOWDATAMANAGER_H_


#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <map>

#pragma pack(push, 1)
class UIWindowItemData : public IData
{
public:
	int  mWindowType;                          // 窗口类型
	char mWindowName[128];                     // 窗口名称
	int  mWindowZOrder;                        // 窗口Z-Order序列
	bool mIsModelWindow;                       // 是否模态窗口
	char mBGImageResourceName[128];            // 窗口背景图片plist打包资源名称(.plist)
	bool mIsBGImageReleaseWhenWindowDestroy;   // 是否窗口销毁时立即释放背景图片
	char mUIResourceName[128];                 // 窗口UI图片的plist打包资源名称(.plist)
	bool mIsUIImageReleaseWhenWindowDestroy;   // 是否窗口销毁时立即释放UI图片
	int  mSoundOpen;					       // 打开时音效ID
	int  mSoundClose;						   // 关闭时音效ID
public:
	UIWindowItemData();
	virtual ~UIWindowItemData();

public:
	/*
		解析数据
	*/
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};
#pragma pack(pop)


class UIWindowDataManager : public IDataManager, public cobra_win::Singleton2<UIWindowDataManager>
{
private:
	std::map<int, UIWindowItemData*> m_WindowList;

public:
	UIWindowDataManager(bool bLoadFromDB, bool bEncryption);
	virtual ~UIWindowDataManager();

public:
	/*
		根据窗口类型得到对应的信息
	*/
	UIWindowItemData* GetWindowByType(int type);
	/*
		得到UI窗口的个数
	*/
	unsigned  int     GetWindowNumber();
	/*
		得到指定位置的窗口信息
	*/
	UIWindowItemData* GetWindowByPos(unsigned int pos);

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
	friend   class   cobra_win::Singleton2<UIWindowDataManager>;
};


#endif
