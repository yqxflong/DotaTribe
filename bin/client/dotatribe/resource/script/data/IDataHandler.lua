--Name : IDataHelper.lua
--Function : 提供Lua系统数据保存的基类
--Author : fangjun

IDataHandler = {}

-- 实例化（继承时子类使用）
function IDataHandler:New(object)
	local object = object or {}
	setmetatable(object, self)
	self.__index = self
	return object
end

-- Init Destroy  供继承使用
function IDataHandler:Init()
end

function IDataHandler:Tick()
end

function IDataHandler:Destroy()
end




