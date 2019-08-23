--Name : EventHelper.lua
--Function : 提供Lua系统的事件发送功能
--Author : fangjun
require "resource/script/util/util_function"

local eventHelper = {}
eventHelper.__index = eventHelper

-- c++辅助类对象
local eventHelperCXX = tolua.cast(EventHelper:LuaGetInstance(), EventHelper:LuaGetInstanceName())

function Call_EventHelper()
	return eventHelper
end

-- 注册事件，会在EventSystem的Init中集中注册
function eventHelper:RegisterEvent(eventId, ownerData)
	eventHelperCXX:LuaRegisterEvent(eventId, ownerData)
end	

function eventHelper:PushEvent(eventId)
	eventHelperCXX:LuaPushEvent(eventId)
end

function eventHelper:PushEvent(eventId, param0)
	eventHelperCXX:LuaPushEvent(eventId, param0)
end

function eventHelper:PushEvent(eventId, param0, param1)
	eventHelperCXX:LuaPushEvent(eventId, param0, param1)
end

function eventHelper:PushEvent(eventId, param0, param1, param2)
	eventHelperCXX:LuaPushEvent(eventId, param0, param1, param2)
end

function eventHelper:PushEvent2(eventId)
	eventHelperCXX:LuaPushEvent2(eventId)
end

function eventHelper:PushEvent2(eventId, param0)
	eventHelperCXX:LuaPushEvent2(eventId, param0)
end

function eventHelper:PushEvent2(eventId, param0, param1)
	eventHelperCXX:LuaPushEvent2(eventId, param0, param1)
end

function eventHelper:PushEvent2(eventId, param0, param1, param2)
	eventHelperCXX:LuaPushEvent2(eventId, param0, param1, param2)
end

