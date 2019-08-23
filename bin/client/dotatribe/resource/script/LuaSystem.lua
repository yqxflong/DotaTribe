-- avoid memory leak
collectgarbage("setpause", 100) 
collectgarbage("setstepmul", 5000)

require "resource/script/util/util_function"
require "resource/script/view/WindowManager"
require "resource/script/packet/PacketManager"
require "resource/script/data/DataHandlerManager"

-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
    cclog("----------------------------------------")
    cclog("LUA ERROR: " .. tostring(msg) .. "\n")
    cclog(debug.traceback())
    cclog("----------------------------------------")
end

-- 创建lua层的luasystem
local luaSystem = {}
luaSystem.__index = luaSystem

local i = 0

-- 获得cxx层的luasystem
local LuaSystemCXX = LuaSystem:LuaGetInstance()

-- 获得luasystem
function Call_LuaSystem()
	return luaSystem
end

local InitTable = {}		-- 创建Lua环境中的Init表
local TickTable = {}		-- 创建Lua环境中的tick表
local DestroyTable = {}		-- 创建Lua环境中的Destroy表

-- 增加注册Init
local function RegisterInit(mhost, mfunc)
	table.insert(InitTable, {_host = mhost, _func = mfunc})
	return table.getn(InitTable)
end

-- 增加更新Tick
local function RegisterTick(mhost, mfunc)
	table.insert(TickTable, {_host = mhost, _func = mfunc})
	return table.getn(TickTable)
end

-- 增加销毁Destroy
local function RegisterDestroy(mhost, mfunc)
	table.insert(DestroyTable, {_host = mhost, _func = mfunc})
	return table.getn(DestroyTable)
end

-- 初始化
local function RunInit()
	for item in list_iter(InitTable) do
		item._func(item._host)
	end
end

-- 更新
local function RunTick()
	for item in list_iter(TickTable) do
		item._func(item._host)
	end
end

-- 销毁
local function RunDestroy()
	for item in list_iter(DestroyTable) do
		item._func(item._host)
	end
end


function luaSystem:Init(name)
	RunInit()
end

function luaSystem:Tick()
	-- 更新之前的注册
	RunTick()

	if i < 100 then
		print("lua tick   " .. i)
		i = i + 1
	end
end

function luaSystem:Destroy()
	-- 销毁之前的注册
	RunDestroy()


end


function luaSystem:OnEventHandler(eventName, eventId, ownerData, ...)
    local paramList = {}
    arg = {...}
    --获得事件传递参数
    for i, v in ipairs(arg) do
    	table.insert(paramList, v)
    end

	Call_WindowManager():OnEventHandler(eventId, ownerData, paramList)

end

function  luaSystem:OnPacketHandler(eventName)
	local pn = Call_PacketHelper():ReadPn()

	Call_PacketManager():OnPacketHandler(pn)

end

function main()
	-- 注册系统Init
	LuaSystemCXX:LuaRegisterInitScript(handler(luaSystem, luaSystem.Init))

	-- 注册系统tick
	LuaSystemCXX:LuaRegisterTickScript(handler(luaSystem, luaSystem.Tick))

	-- 注册系统destroy
	LuaSystemCXX:LuaRegisterDestroyScript(handler(luaSystem, luaSystem.Destroy))

	-- 注册系统事件处理器
	LuaSystemCXX:LuaRegisterOnEventHandlerScript(handler(luaSystem, luaSystem.OnEventHandler))

	-- 注册系统包解析器
	LuaSystemCXX:LuaRegisterOnPacketHandlerScript(handler(luaSystem, luaSystem.OnPacketHandler))


	-- 注册Lua层的系统模块
	RegisterInit(Call_WindowManager(), Call_WindowManager().Init)
	RegisterInit(Call_DataHandlerManager(), Call_DataHandlerManager().Init)
	RegisterInit(Call_PacketManager(), Call_PacketManager().Init)


	RegisterTick(Call_WindowManager(), Call_WindowManager().Tick)
	RegisterTick(Call_DataHandlerManager(), Call_DataHandlerManager().Tick)
	RegisterTick(Call_PacketManager(), Call_PacketManager().Tick)


	RegisterDestroy(Call_WindowManager(), Call_WindowManager().Destroy)
	RegisterDestroy(Call_DataHandlerManager(), Call_DataHandlerManager().Destroy)
	RegisterDestroy(Call_PacketManager(), Call_PacketManager().Destroy)

	log("what is that")

end

-- 开始入口
xpcall(main, __G__TRACKBACK__)


