#ifndef  _DOTATRIBE_WINDOWMANAGER_H_
#define  _DOTATRIBE_WINDOWMANAGER_H_


#include <include/common/Singleton.h>
#include <string>
#include <list>
#include <map>
using  namespace  cobra_win;

class IWindow;
class WindowManager : public cobra_win::Singleton2<WindowManager>
{
public:
	std::map<int, IWindow*> m_WindowList;

public:
	WindowManager();
	virtual ~WindowManager();

public:
	/*
		根据指定的Layout名称得到对应的UI窗口
	*/
	IWindow* GetWindowByType(int iWindowType);
	/*
		判断指定窗口是否显示
	*/
	bool     IsWindowVisible(int iWindowType);
	/*
		判断指定窗口是否已经加载 
	*/
	bool     IsWindowLoad(int iWindowType);

	/*
		隐藏所有UI窗口
	*/
	void     HideAllWindow(bool bVisible);
	/*
		得到UI窗口个数
	*/
	size_t   GetWindowCount();
	/*
		得到指定索引的UI窗口
	*/
	IWindow* GetWindowByIndex(size_t iIndex);

	/*
		销毁所有窗口
	*/
	void DestroyAllWindow();
	/*
		销毁所有可视窗口
	*/
	void DestroyAllVisibleWindow();
	/*
		销毁所有可视窗口除了某一窗口
	*/
	void DestroyAllVisibleWindow(int iType);

public:
	/*
		获得所有窗口列表
	*/
	std::map<int, IWindow*>& GetWindowList();

public:
	/*
		初始化UI窗口管理器
	*/
	bool     Init();
	/*
		逻辑桢更新
	*/
	void     Tick();
	/*
		销毁UI窗口管理器
	*/
	void     Destroy();

public:
	/*
		版本更新事件响应处理函数（需要重新加载必要的资源）
	*/
	static   void    OnVersionUpdateFinishedEventHandler(int iEventType, std::string owerData, std::list<std::string>& paramList);

private:
	friend  class  cobra_win::Singleton2<WindowManager>;
};

#define  WINDOWMANAGER  (WindowManager::get_instance2())


#endif
