--Name : IView.lua
--Function : 提供Lua页面基类和页面管理
--Author : fangjun

require "resource/script/view/IWindow"

local testWindow = IWindow:New(WindowTyper._WINDOW_TEST_)

testWindow.m_pLabelTTF = nil

function Call_TestWindow()
	return testWindow
end

function testWindow:_initLayout()
	Call_UIHelper():AutoCreateNodeByTable(1001, self.m_pRootNode)

	self.m_pLabelTTF = tolua.cast(self.m_pRootNode:getChildByTag(4), "CCLabelTTF")

end

function testWindow:_mapBtn()
	log("testWindow:_mapBtn    begin")
	local menu = tolua.cast(self.m_pRootNode:getChildByTag(2), "CCMenu")
	local item = tolua.cast(menu:getChildByTag(0), "CCMenuItem")
	item:setTag(2)
	item:registerScriptTapHandler(handler(self, self.On_Btn_Click))

	menu = tolua.cast(self.m_pRootNode:getChildByTag(3), "CCMenu")
	item = tolua.cast(menu:getChildByTag(0), "CCMenuItem")
	item:setTag(3)
	item:registerScriptTapHandler(handler(self, self.On_Btn_Click))

	log("testWindow:_mapBtn    end")
end

function testWindow:Init()
	self:RegisterEvent(EventTyper._TYPED_EVENT_TESTWINDOW_SHOW_)
	self:RegisterEvent(EventTyper._TYPED_EVENT_TESTWINDOW_HIDE_, true)

	self:RegisterEvent(EventTyper._TYPED_EVENT_DEMOWINDOW_REQUEST_, true)
	self:RegisterEvent(EventTyper._TYPED_EVENT_DEMOWINDOW_REPLY_, true)

	return self.super.Init(self)

end

function testWindow:Load()
	log("testWindow:Load    begin")

	if self.super.Load(self) == false then
		return false
	end

	self:_initLayout()

	self:_mapBtn()

	log("testWindow:Load    end")
	return true
end

function testWindow:Tick()

end

function testWindow:Destroy()

	self.super.Destroy(self)
end

function testWindow:OnEventHandler(eventType, paramTable)
		log("testWindow:OnEventHandler    " .. eventType)
	if eventType == EventTyper._TYPED_EVENT_TESTWINDOW_SHOW_ then
		log("testWindow:OnEventHandler")
		self:Show(true)
	elseif eventType == EventTyper._TYPED_EVENT_TESTWINDOW_HIDE_ then
		self:Destroy()
	elseif eventType == EventTyper._TYPED_EVENT_DEMOWINDOW_REPLY_ then
		self:Function_GetReply()
	end
end

function testWindow:On_Btn_Click(itemTag, menuItem)
	local item = tolua.cast(menuItem, "CCMenuItem")
	local tag = item:getTag()
	tag = itemTag
	log("testWindow:On_Btn_Click   tag:" .. tag)
	require "resource/script/data/DemoDataHandler"
	if tag == 2 then

		--[[require "resource/script/view/DemoWindow"

		if Call_DemoWindow():IsLoad() == true then
			log("9999999999999  demo true")
		else
			log("8888888888888  demo false")
		end

		if Call_TestWindow():IsLoad() == true then
			log("9999999999999  test true")
		else
			log("8888888888888  test false")
		end

		log("0000000=====demo==" .. Call_DemoWindow().m_WindowName)
		log("1111111=====test==" .. Call_TestWindow().m_WindowName)]]

		Call_DemoDataHandler():ToServerSendPacket()
	elseif tag == 3 then
		Call_EventHelper():PushEvent(EventTyper._TYPED_EVENT_TESTWINDOW_HIDE_)
		Call_EventHelper():PushEvent(56)
	end

end

function testWindow:Function_GetReply()
	log("testWindow:Function_GetReply    begin")

	if self.m_pLabelTTF ~= nil then
		local da = Call_DemoDataHandler().data;
		local ttf = "=" .. da.a .. "=" .. da.b .. "=" .. da.c .. "=" .. da.d
		self.m_pLabelTTF:setString(ttf)

	end

	log("testWindow:Function_GetReply    end")
end






