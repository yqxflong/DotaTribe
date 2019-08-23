--Name : windowManager.lua
--Function : 提供Lua页面基类和页面管理
--Author : fangjun

require "resource/script/util/util_function"
-- require "resource/script/view/IWindow"
require "resource/script/view/DemoWindow"
require "resource/script/view/TestWindow"
require "resource/script/view/LianJinWindow"
require "resource/script/view/MonthCardWindow"

local windowManager = {}
windowManager.__index = windowManager

-- 用于管理view
windowManager.windowTable = {}


-- 获得对象
function Call_WindowManager()
	return windowManager
end

-- 初始化
function windowManager:Init()
	log("windowManager:Init begin")

	-- 注册需要加载的UIVIewDataManager对象(即ll_xxx_layout.txt)
	for file in list_iter(ViewFile) do
		Call_UIHelper():RegisterViewFile(file.id, file.path, file.name)
	end


	-- 注册各个页面实例(请完成各个页面之后再此处注册你的页面)
	self:RegisterWindow(Call_DemoWindow())
	self:RegisterWindow(Call_TestWindow())
	self:RegisterWindow(Call_LianJinWindow())
	self:RegisterWindow(Call_MonthcardWindow())







	for item in list_iter(self.windowTable) do
		item:Init()
	end
	log("windowManager:Init end")	
end

-- 更新
function windowManager:Tick()
	
	-- 更新各个窗口
	for item in list_iter(self.windowTable) do
		local load = item:IsLoad()
		if load == true then
			item:Tick()
		end
	end

end

-- 销毁
function windowManager:Destroy()

	-- 销毁各个窗口
	for item in list_iter(self.windowTable) do
		local load = item:IsLoad()
		if load == true then
			item:Destroy()
		end
	end
end

-- 事件传递，从windowManager中派发到各个子窗口(依据窗口注册事件是否为强响应事件。如果是强响应事件并且未加载，需要先加载页面，否则不处理这个事件)
function windowManager:OnEventHandler(eventType, ownerData, paramTable)
	log("windowManager:OnEventHandler   begin    ownerData:" .. ownerData)

	for item in list_iter(self.windowTable) do
		local tp = "" .. item:GetWindowType()
		if string_equal(tp, ownerData) == true then -- m_WindowType == ownerData
			if item:IsLoad() == false then
				if item:IsHardEvent(eventType) == true then
					item:Load()
				else
					return
				end
			end
			item:OnEventHandler(eventType, paramTable)
			break
		end
	end

	log("windowManager:OnEventHandler   end")
end

function windowManager:RegisterWindow(mWindow)
	table.insert(self.windowTable, mWindow)
	return table.getn(self.windowTable)
end



