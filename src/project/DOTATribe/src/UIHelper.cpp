//Name: UIHelper.h
//Function: 提供Lua使用UISystem中的部分功能接口
//Date: 20140313
//Author: fangjun

#include "../include/UIHelper.h"
#include "../include/UISystem.h"
#include "../include/UIViewDataManger.h"
#include "../include/DOTATribeApp.h"

BaseHelper * luaUIHelper::m_pHelper = NULL;
std::string luaUIHelper::m_sName = "";

luaUIHelper::luaUIHelper()
{
	m_pProvideNode = NULL;
}

luaUIHelper::~luaUIHelper()
{
	m_pProvideNode = NULL;
}

void luaUIHelper::SetProvideNode(CCNode * node)
{
	m_pProvideNode = node;
}

void luaUIHelper::BuildInstance(std::string name, BaseHelper * helper)
{
	m_pHelper = helper;
	m_sName = name;
}

void luaUIHelper::LoadViewFile()
{
	for(unsigned int i = 0; i < m_vRegisterViewFile.size(); ++i)
	{
		UIVIEWDATAMANAGER->registerFile(m_vRegisterViewFile[i].idx, m_vRegisterViewFile[i].filename, m_vRegisterViewFile[i].encryfilename);
	}
}

BaseHelper * luaUIHelper::LuaGetInstance()
{
	return m_pHelper;
}

std::string luaUIHelper::LuaGetInstanceName()
{
	return m_sName;
}

CCLayer * luaUIHelper::LuaGetUILayer()
{
	return UISYSTEM->GetUILayer();
}

CCNode * luaUIHelper::LuaGetProvideNode()
{
	CCNode * temp = m_pProvideNode;
	m_pProvideNode = NULL;

	return temp;
}

void luaUIHelper::LuaAutoCreateNodeByTable(int key, CCNode* parentNode)
{
	return UIVIEWDATAMANAGER->AutoCreateNodeByTable(key, parentNode);
}

void luaUIHelper::LuaRegisterViewFile(int idx, std::string filename, std::string Encyfilename)
{
	UIHelper_ViewFile a(idx, filename, Encyfilename);
	m_vRegisterViewFile.push_back(a);
}

void luaUIHelper::LuaForceClearAnimationCache()
{
	DOTATribeApp::get_instance2()->ForceClearAnimationCache();
}