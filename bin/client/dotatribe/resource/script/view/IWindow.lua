--Name : IView.lua
--Function : 提供Lua页面基类和页面管理
--Author : fangjun

require "resource/script/util/util_function"
require "resource/script/event/EventTyper"
require "resource/script/event/EventHelper"
require "resource/script/view/UIWindow"
require "resource/script/view/UIHelper"

IWindow = {}

IWindow.m_WindowType = 0
IWindow.m_WindowName = ""
IWindow.m_bModelWindow = false
IWindow.m_iWindowZOrder = 0
IWindow.m_bLoaded = false
IWindow.m_bShow = false
IWindow.m_pRootNode = nil
IWindow.m_bIsForceClearUnUseTex = false
IWindow.m_bIsForceClearAnimation = false
IWindow.m_iSoundOpenId = 0 -- 此页面打开音效
IWindow.m_iSoundCloseId = 0 -- 此页面关闭音效

-- 强推送事件列表(用于推送事件时)
IWindow.m_hardEventTable = {}

-- 窗口构造方法
function IWindow:New(windowType)
	local object = object or {}
	setmetatable(object, self)
	self.__index = self
	self.super = self

	object.m_WindowType = windowType
	return object
end


function IWindow:GetWindowType()
	return self.m_WindowType
end

function IWindow:GetWindowName()
	return self.m_WindowName
end

function IWindow:IsLoad()
	return self.m_bLoaded
end

function IWindow:GetRootNode()
	return self.m_pRootNode
end

function IWindow:Show(bshow)
	print("IWindow:Show   begin")
	if self.m_bShow ~= bshow then
		self.m_bShow = bshow
		if self.m_pRootNode ~= nil then
			if bshow == true then
				self.m_pRootNode:setVisible(true)
				-- 播放打开声音
				self:PlayOpenSound()
			else
				self.m_pRootNode:setVisible(false)
				--播放关闭声音
				self:PlayCloseSound()
			end
		end
	end
	print("IWindow:Show   end")
end

function IWindow:IsVisible()
	return self.m_bShow
end

function IWindow:GetPosition()
	if self.m_pRootNode ~= nil then
		return self.m_pRootNode:GetPosition()
	else
		return 0, 0
	end
end

function IWindow:SetPosition(x, y)
	if self.m_pRootNode ~= nil then
		self.m_pRootNode:SetPosition(x, y)
	end
end

function IWindow:RegisterEvent(eventId, bNotifyOnlyVisible)
	if bNotifyOnlyVisible == nil then
		table.insert(self.m_hardEventTable, eventId)

	end

	-- 调用EventHelper或者其他模块将事件注册进喜用eventsystem
	log("aaaa windowtype " .. eventId .. " windowtype " .. self.m_WindowType)
	Call_EventHelper():RegisterEvent(eventId, self.m_WindowType)
end

-- 消息处理，，此函数需要子类实现
function IWindow:OnEventHandler(eventId, paramTable)
end

function IWindow:PlayOpenSound()
	local id = "" .. self.m_iSoundOpenId

	-- 调用EventHelper Push机制将事件和参数推出
	Call_EventHelper():PushEvent(381, id)
end

function IWindow:PlayCloseSound()
	local id = "" .. self.m_iSoundCloseId

	-- 调用EventHelper Push机制将事件和参数推出
	Call_EventHelper():PushEvent(381, id)
end

function IWindow:IsHardEvent(eventId)
	for item in list_iter(self.m_hardEventTable) do
		log("Is hard Event  " .. eventId .. "..." .. item)

		if item == eventId then
			return true
		end
	end
	return false
end

function IWindow:Init()
	-- 需要从UIWindow.txt中获取数据进行配置
	log("IWindow:Init  begin")

	local uiwindowdata = Call_UIHelper():GetUIWindowData(self:GetWindowType())
	self.m_WindowName = uiwindowdata.name
	self.m_bModelWindow = uiwindowdata.isModel
	self.m_iWindowZOrder = uiwindowdata.ZOrder
	self.m_bLoaded = false
	self.m_bShow = false
	self.m_pRootNode = nil
	self.m_bIsForceClearUnUseTex = true
	self.m_bIsForceClearAnimation = true
	self.m_iSoundOpenId = uiwindowdata.openSound -- 此页面打开音效
	self.m_iSoundCloseId = uiwindowdata.closeSound -- 此页面关闭音效

	log("IWindow:Init  end")
end

function IWindow:Load()
	log("IWindow:Load   begin")
	self.m_pRootNode = CCNode:create()
	self.m_pRootNode:setPosition(ccp(0, 0))

	--self.m_pRootNode:setZOrder(self.m_iWindowZOrder)
	local layer = Call_UIHelper():GetUILayer()
	layer:addChild(self.m_pRootNode, self.m_iWindowZOrder)

	if self.m_bModelWindow then
		local director = CCDirector:sharedDirector()
		--director:getTouchDispatcher:addTargetedDelegate()
	end

	self.m_bLoaded = true

	log("IWindow:Load   end")

	log("Load UI Window, WindowType=" .. self:GetWindowType() .. ", WindowName=" .. self:GetWindowName())
	return true
end

function IWindow:Tick()

end

function IWindow:Destroy()
	log("IWindow:Destroy begin")

	self:PlayCloseSound()

	if self.m_pRootNode ~= nil then
		self.m_pRootNode:removeFromParentAndCleanup(true)
		--self.m_pRootNode:removeAllChildrenWithCleanup(true)
		--Call_UIHelper():removeChild(self.m_pRootNode, true)

		self.m_pRootNode = nil
	end

	self.m_bShow = false
	self.m_bLoaded = false

	if self.m_bIsForceClearAnimation == true then
		-- 强制清除动画,调用
		Call_UIHelper():ForceClearAnimationCache()
	end



	log("IWindow:Destroy end")

	log("UnLoad UI Window, WindowType=" .. self:GetWindowType() .. ", WindowName=" .. self:GetWindowName())
end


