--Name : IView.lua
--Function : 提供Lua页面基类和页面管理
--Author : fangjun

require "resource/script/view/IWindow"

local demoWindow = IWindow:New(WindowTyper._WINDOW_DEMO_)

demoWindow.m_pLabelTTF = nil
demoWindow.m_pTableView = nil
demoWindow.m_pTableSize = nil
demoWindow.m_pTableSourceDelegate = nil

function Call_DemoWindow()
	return demoWindow
end

function demoWindow:tableCellSizeForIndex()
	demoWindow.m_pTableSourceDelegate.m_nCellSize = demoWindow.m_pTableSize -- 这步必须

end

function demoWindow:tableCellAtIndex(index)
	log("demoWindow:tableCellAtIndex  1  index:" .. index)
	local cell = demoWindow.m_pTableView:dequeueCell()
	if cell == nil then
		log("cell is nil")
		cell = CCTableViewCell:newOne()
		if cell == nil then
			log("cell still is nil")
		end
		cell:autorelease()
		-- 创建cell的表
		Call_UIHelper():AutoCreateNodeByTable(151, cell)
	end

	--设置cell


	demoWindow.m_pTableSourceDelegate.m_pCell = cell -- 这步必须
	log("demoWindow:tableCellAtIndex 2  index:" .. index)
end

function demoWindow:numberOfCellsInTableView()
	demoWindow.m_pTableSourceDelegate.m_nCellNumbers = 8 -- 这步必须
end

function demoWindow:scrollViewDidScroll()
	log("demoWindow:scrollViewDidScroll  did!")
end

function demoWindow:_initLayout()
	Call_UIHelper():AutoCreateNodeByTable(1000, self.m_pRootNode)

	local animation = NFC_getLoopFrameEffect(2057)
	self.m_pRootNode:addChild(animation)
	animation:setPosition(ccp(512, 360))

	self.m_pLabelTTF = tolua.cast(self.m_pRootNode:getChildByTag(5), "CCLabelTTF")

	-- CTableView
	self.m_pTableSize = self.m_pRootNode:getChildByTag(7):getContentSize()


	self.m_pTableView = tolua.cast(self.m_pRootNode:getChildByTag(6), "CTableView")
	self.m_pTableSourceDelegate = self.m_pTableView:getMyDelegate()
	self.m_pTableView:setDirection(kCCScrollViewDirectionVertical)
	self.m_pTableView:setTouchEnabled(true);
	self.m_pTableView:setVerticalFillOrder(kCCTableViewFillTopDown);
	self.m_pTableSourceDelegate:registerScript(demoWindow.tableCellSizeForIndex, demoWindow.tableCellAtIndex, demoWindow.numberOfCellsInTableView, demoWindow.scrollViewDidScroll)
	self.m_pTableView:reloadData()
end

function demoWindow:_mapBtn()
	log("demoWindow:_mapBtn    begin")
	local menu = tolua.cast(self.m_pRootNode:getChildByTag(2), "CCMenu")
	local item = tolua.cast(menu:getChildByTag(0), "CMenuItemSprite")
	item:setIDX(11)
	item:setTag(2)
	item:registerScriptTapHandler(handler(self, self.On_Btn_Click))

	menu = tolua.cast(self.m_pRootNode:getChildByTag(3), "CCMenu")
	item = tolua.cast(menu:getChildByTag(0), "CCMenuItem")
	item:setTag(3)
	item:registerScriptTapHandler(handler(self, self.On_Btn_Click))

	menu = tolua.cast(self.m_pRootNode:getChildByTag(4), "CCMenu")
	item = tolua.cast(menu:getChildByTag(0), "CCMenuItem")
	item:setTag(4)
	item:registerScriptTapHandler(handler(self, self.On_Btn_Click))

	log("demoWindow:_mapBtn    end")
end

function demoWindow:Init()
	self:RegisterEvent(EventTyper._TYPED_EVENT_DEMOWINDOW_SHOW_)
	self:RegisterEvent(EventTyper._TYPED_EVENT_DEMOWINDOW_HIDE_, true)

	self:RegisterEvent(EventTyper._TYPED_EVENT_DEMOWINDOW_REQUEST_, true)
	self:RegisterEvent(EventTyper._TYPED_EVENT_DEMOWINDOW_REPLY_, true)

	return self.super.Init(self)

end

function demoWindow:Load()
	log("demoWindow:Load    begin")
	if self.super.Load(self) == false then
		return false
	end

	self:_initLayout()

	self:_mapBtn()

	log("demoWindow:Load    end")

	return true
end

function demoWindow:Tick()

end

function demoWindow:Destroy()

	self.super.Destroy(self)
end

function demoWindow:OnEventHandler(eventType, paramTable)
		log("demoWindow:OnEventHandler    " .. eventType)
	if eventType == EventTyper._TYPED_EVENT_DEMOWINDOW_SHOW_ then
		log("demoWindow:OnEventHandler")
		self:Show(true)
	elseif eventType == EventTyper._TYPED_EVENT_DEMOWINDOW_HIDE_ then
		self:Destroy()
	elseif eventType == EventTyper._TYPED_EVENT_DEMOWINDOW_REPLY_ then
		self:Function_GetReply()
	end
end

function demoWindow:On_Btn_Click(itemTag, menuItem)
	local item = tolua.cast(menuItem, "CMenuItemSprite")
	local tag = item:getTag()
	tag = itemTag
	log("demoWindow:On_Btn_Click   tag:" .. tag)
	require "resource/script/data/DemoDataHandler"
	if tag == 2 then
		Call_DemoDataHandler():ToServerSendPacket()
	elseif tag == 3 then
		Call_EventHelper():PushEvent(EventTyper._TYPED_EVENT_DEMOWINDOW_HIDE_)
		--Call_EventHelper():PushEvent(56)
		Call_EventHelper():PushEvent(EventTyper._TYPED_EVENT_TESTWINDOW_SHOW_)
	elseif tag == 4 then
		NFC_showMessageBox(0, "我是一个C++ Programmer！叫阿卡卡卡卡卡撒打发水电费那三国骄傲IDS更好哈哦！阿斯顿发生大发！")
		--local sprite = tolua.cast(demoWindow.m_pRootNode:getChildByTag(1), "CCSprite")
		--require "resource/script/data/DataHelper"
		--local path = Call_DataHelper():GetResourcePathById(460)
		--sprite:setProperty("File", path)  --CCNode没有绑定这个方法
		--NFC_setPicForCCSprite(1, demoWindow.m_pRootNode, path)
	end

end

function demoWindow:Function_GetReply()
	log("demoWindow:Function_GetReply    begin")

	if self.m_pLabelTTF ~= nil then
		local da = Call_DemoDataHandler().data;
		local ttf = "=" .. da.a .. "=" .. da.b .. "=" .. da.c .. "=" .. da.d
		self.m_pLabelTTF:setString(ttf)

	end

	log("demoWindow:Function_GetReply    end")
end






