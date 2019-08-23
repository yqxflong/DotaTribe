--Name : UIHelper.lua
--Function : 提供Lua页面基类和页面管理
--Author : fangjun

require "resource/script/util/util_function"
require "resource/script/view/UIWindow"

local uiHelper = {}
uiHelper.__index = uiHelper

log("============UIHelper:LuaGetInstanceName():"..luaUIHelper:LuaGetInstanceName())

local uiHelperCXX = tolua.cast(luaUIHelper:LuaGetInstance(), luaUIHelper:LuaGetInstanceName())

-- 获得Helper实例对象
function Call_UIHelper()
	return uiHelper
end

-- 获得根节点Layer
function uiHelper:GetUILayer()
	return uiHelperCXX:LuaGetUILayer()
end

-- 获得c++提供的绘制节点
function uiHelper:GetProvideNode()
	return uiHelperCXX:LuaGetProvideNode()
end

-- 注册需要加载的ll_xxx_layout.txt
function uiHelper:RegisterViewFile(idx, filename, encyfilename)
	return uiHelperCXX:LuaRegisterViewFile(idx, filename, encyfilename)
end

-- autocreate节点
function uiHelper:AutoCreateNodeByTable(key, parentNode)
	return uiHelperCXX:LuaAutoCreateNodeByTable(key, parentNode)
end

-- 强制清除动画缓存
function uiHelper:ForceClearAnimationCache()
	return uiHelperCXX:LuaForceClearAnimationCache()
end

function uiHelper:GetUIWindowData(windowType)
	return UIWindow[windowType]
end





