--Name : DataHandlerManager.lua
--Function : 提供Lua系统的数据系统的功能
--Author : fangjun

local dataHandlerManager = {}
dataHandlerManager.__index = dataHandlerManager

dataHandlerManager.dataHandlerTable = {}

function Call_DataHandlerManager()
	return dataHandlerManager
end

function dataHandlerManager:RegisterDataHandler(datahandler)
	table.insert(self.dataHandlerTable, datahandler)
end

function dataHandlerManager:Init()
	log("dataHandlerManager:Init   begin")

	-- 此处需要将所有datahandler注册
	require "resource/script/data/DemoDataHandler"
	self:RegisterDataHandler(Call_DemoDataHandler())
	require "resource/script/data/LianJinDataHandler"
	self:RegisterDataHandler(Call_LianJinDataHandler())
	require "resource/script/data/MonthCardDataHandler"
	self:RegisterDataHandler(Call_MonthCardDataHandler())





	for item in list_iter(self.dataHandlerTable) do
		item:Init()
	end

	log("dataHandlerManager:Init   end")
end

function dataHandlerManager:Tick()
	for item in list_iter(self.dataHandlerTable) do
		item:Tick()
	end
end

function dataHandlerManager:Destroy()
	for item in list_iter(self.dataHandlerTable) do
		item:Destroy()
	end
end

