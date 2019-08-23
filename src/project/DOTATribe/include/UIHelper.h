//Name: UIHelper.h
//Function: 提供Lua使用UISystem中的部分功能接口
//Date: 20140313
//Author: fangjun

#ifndef _LUA_UIHELPER_H_
#define _LUA_UIHELPER_H_

#include <cocos2d.h>
#include <cocos-ext.h>
#include <string>
#include <vector>
#include "../include/BaseHelper.h"
#include "../include/UIWindowDataManager.h"

using  namespace  cocos2d;
using  namespace  cocos2d::extension;

class UIHelper_ViewFile
{
public:
	int idx;
	std::string filename;
	std::string encryfilename;
public:
	UIHelper_ViewFile(int a, std::string b, std::string c)
	{
		idx = a;
		filename = b;
		encryfilename = c;
	}
};

class luaUIHelper : public BaseHelper
{
private:
	CCNode * m_pProvideNode;

	static BaseHelper * m_pHelper;
	static std::string m_sName;

public:
	std::vector<UIHelper_ViewFile> m_vRegisterViewFile;

public:
	luaUIHelper();
	virtual ~luaUIHelper();

public:
	void SetProvideNode(CCNode * node);

	virtual void BuildInstance(std::string name, BaseHelper * helper);

	//加载所有在Lua中注册的viewfile
	void LoadViewFile();

public:
	static BaseHelper * LuaGetInstance();

	static std::string LuaGetInstanceName();
	
	CCLayer * LuaGetUILayer();
	
	//此接口在使用第一次时就会销毁内部存储数据。
	CCNode * LuaGetProvideNode();

	void LuaAutoCreateNodeByTable(int key, CCNode* parentNode);

	void LuaRegisterViewFile(int idx, std::string filename, std::string Encyfilename);

	void LuaForceClearAnimationCache();
};


#endif
