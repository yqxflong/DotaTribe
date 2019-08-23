--Name : DataHelper.lua
--Function : 提供Lua系统数据访问接口
--Author : fangjun

dataHelper = {}
dataHelper.__index = dataHelper

dataHelperCXX = tolua.cast(DBHelper:LuaGetInstance(), DBHelper:LuaGetInstanceName())

function Call_DataHelper()
	return dataHelper
end

function dataHelper:GetSysLangById(id)
	return dataHelperCXX:LuaGetSysLangById(id)
end

function dataHelper:GetResourcePathById(id)
	return dataHelperCXX:LuaGetResourcePathByID(id)
end

function dataHelper:GetRoleInfoDataHandler()
	return dataHelperCXX:LuaGetRoleInfoDataHandler()
end

-- 飘字接口
function dataHelper:ShowFlowEffect(type, count, bjcount, iconid)
	return dataHelperCXX:LuaShowFlowEffect(type, count, bjcount, iconid)
end

