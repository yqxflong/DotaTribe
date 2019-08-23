--[[
	Name: MonthCardWindow.lua
	Function: 月卡窗口与逻辑
	Author: 邵兵
]]

require "resource/script/view/IWindow"
require "resource/script/data/MonthCardDataHandler"
require "resource/script/data/DataHelper"

local monthcardWindow = IWindow:New(WindowTyper._WINDOW_MONTHCARD_);

monthcardWindow.controls = {
	_MONTHCARD_BG_ 					= 1,
	_MONTHCARD_BACK_ 				= 2,
	_MONTHCARD_BACK_LABEL_ 			= 3,
	_MONTHCARD_BUY_30_				= 4,
	_MONTHCARD_BUY_30_LABEL_		= 5,
	_MONTHCARD_BUY_60_				= 6,
	_MONTHCARD_BUY_60_LABEL_		= 7,
	_MONTHCARD_30_LEFTDAY_LABEL_	= 8,
	_MONTHCARD_60_LEFTDAY_LABEL_	= 9,
	_MONTHCARD_INFO_TXT_LINE1_		= 10,
	_MONTHCARD_INFO_TXT_LINE2_		= 11,
	_ACTIVIEY_BG_					= 12,
	_ACTIVITY_SMALL_BG_				= 13,

};

monthcardWindow.cardType = {
	_MONTH_CARD_TYPE_30_ = 0,
	_MONTH_CARD_TYPE_60_ = 1,
};


monthcardWindow.GetBtn_30RMB = nil;					--购买按钮（30元）
monthcardWindow.GetBtn_60RMB = nil;					--购买按钮（60元）
monthcardWindow.GetBtnLabel_30RMB = nil;			--购买按钮Label（30元）
monthcardWindow.GetBtnLabel_60RMB = nil;			--购买按钮Label（60元）
monthcardWindow.LeftDayLabel_30RMB = nil;			--剩余N天（30元）
monthcardWindow.LeftDayLabel_60RMB = nil;			--剩余N天（60元）

function Call_MonthcardWindow()
	return monthcardWindow;
end

function monthcardWindow:Init()
	log("MonthCardWindow Init Begin");
	self:RegisterEvent(EventTyper._TYPED_EVENT_MONTHCARDWINDOW_SHOW_);
	self:RegisterEvent(EventTyper._TYPED_EVENT_MONTHCARDWINDOW_HIDE_,true);
	self:RegisterEvent(EventTyper._TYPED_EVENT_MONTHCARDWINDOW_UPDATE_,true);

	log("MonthCardWindow Init End");
	return self.super.Init(self);
end


function monthcardWindow:Load()
	log("MonthCardWindow Load Begin");
	if self.super.Load(self) == false then
		return false;
	end
	self:_initLayout();
	self:_mapBtn();
	self:_updateWindow();

	log("MonthCardWindow Load End");
	return true;
end

function monthcardWindow:Tick()
end

function monthcardWindow:Destroy()
	log("MonthCardWindow Destroy Begin");
	self.super.Destroy(self);
	log("MonthCardWindow Destroy End");
end

function monthcardWindow:OnEventHandler(eventType, paramTable)
	log("MonthCardWindow OnEventHandler Begin. EventType="..eventType);
	if eventType == EventTyper._TYPED_EVENT_MONTHCARDWINDOW_SHOW_ then
		self:Show(true);
	elseif eventType == EventTyper._TYPED_EVENT_MONTHCARDWINDOW_HIDE_ then
		self:Destroy();
	elseif eventType == EventTyper._TYPED_EVENT_MONTHCARDWINDOW_UPDATE_ then
		self:_updateWindow();
	end
	log("MonthCardWindow OnEventHandler End. EventType="..eventType);
end

function monthcardWindow:_initLayout()
	log("MonthCardWindow _initLayout Begin");
	Call_UIHelper():AutoCreateNodeByTable(1003,self.m_pRootNode);

	self.LeftDayLabel_30RMB = tolua.cast(
		self.m_pRootNode:getChildByTag(self.controls._MONTHCARD_30_LEFTDAY_LABEL_),"CCLabelTTF");
	
	self.LeftDayLabel_60RMB = tolua.cast(
		self.m_pRootNode:getChildByTag(self.controls._MONTHCARD_60_LEFTDAY_LABEL_),"CCLabelTTF");

	self.GetBtnLabel_30RMB = tolua.cast(
		self.m_pRootNode:getChildByTag(self.controls._MONTHCARD_BUY_30_LABEL_),"CCLabelTTF");

	self.GetBtnLabel_60RMB = tolua.cast(
		self.m_pRootNode:getChildByTag(self.controls._MONTHCARD_BUY_60_LABEL_),"CCLabelTTF");

	log("MonthCardWindow _initLayout End");

end

function monthcardWindow:_mapBtn()
	log("MonthCardWindow _mapBtn Begin");
	local menu = tolua.cast(self.m_pRootNode:getChildByTag(self.controls._MONTHCARD_BACK_),"CCMenu");
	local item = tolua.cast(menu:getChildByTag(0),"CMenuItemSprite");
	item:setTag(self.controls._MONTHCARD_BACK_);
	item:registerScriptTapHandler(handler(self,self.OnBtnClick));

	menu = tolua.cast(self.m_pRootNode:getChildByTag(self.controls._MONTHCARD_BUY_30_),"CCMenu");
	item = tolua.cast(menu:getChildByTag(0),"CMenuItemSprite");
	item:setTag(self.controls._MONTHCARD_BUY_30_);
	item:registerScriptTapHandler(handler(self,self.OnBtnClick));
	self.GetBtn_30RMB = item;

	menu = tolua.cast(self.m_pRootNode:getChildByTag(self.controls._MONTHCARD_BUY_60_),"CCMenu");
	item = tolua.cast(menu:getChildByTag(0),"CMenuItemSprite");
	item:setTag(self.controls._MONTHCARD_BUY_60_);
	item:registerScriptTapHandler(handler(self,self.OnBtnClick));
	self.GetBtn_60RMB = item;

	log("MonthCardWindow _mapBtn End");
end

function monthcardWindow:OnBtnClick(itemTag, menuItem)
	local item = menuItem;
	log("MonthCardWindow OnBtnClick Begin. ItemTag="..itemTag);
	if itemTag == self.controls._MONTHCARD_BACK_ then
		Call_EventHelper():PushEvent(EventTyper._TYPED_EVENT_MONTHCARDWINDOW_HIDE_);
		Call_EventHelper():PushEvent(56);
	elseif itemTag == self.controls._MONTHCARD_BUY_30_ then
		item = tolua.cast(menuItem,"CMenuItemSprite");
		if Call_MonthCardDataHandler().is_30MonthCardAvailable == false then
			log("Click Buy 30 RMB MonthCard. Dare it Success");

			Call_MonthCardDataHandler().is_30MonthCardAvailable = true;
			Call_MonthCardDataHandler()._30MonthCardLeftDays = 30;
			Call_MonthCardDataHandler().is_30MonthCardCanGet = true;

		else 		
			log("Click Get 30 RMB MonthCard. Dare it Success");

			if Call_MonthCardDataHandler().is_30MonthCardCanGet == true then
				Call_MonthCardDataHandler().is_30MonthCardCanGet = false;
				Call_MonthCardDataHandler()._30MonthCardLeftDays = Call_MonthCardDataHandler()._30MonthCardLeftDays - 1;
			end

		end
	elseif itemTag == self.controls._MONTHCARD_BUY_60_ then
		item = tolua.cast(menuItem,"CMenuItemSprite");
		if Call_MonthCardDataHandler().is_60MonthCardAvailable == false then
			log("Click Buy 60 RMB MonthCard. Dare it Success");

			Call_MonthCardDataHandler().is_60MonthCardAvailable = true;
			Call_MonthCardDataHandler()._60MonthCardLeftDays = 30;
			Call_MonthCardDataHandler().is_60MonthCardCanGet = true;

		else
			log("Click Get 60 RMB MonthCard. Dare it Success");

			if Call_MonthCardDataHandler().is_60MonthCardCanGet == true then
				Call_MonthCardDataHandler().is_60MonthCardCanGet = false;
				Call_MonthCardDataHandler()._60MonthCardLeftDays = Call_MonthCardDataHandler()._60MonthCardLeftDays - 1;

			end

		end

	end
	Call_EventHelper():PushEvent(EventTyper._TYPED_EVENT_MONTHCARDWINDOW_UPDATE_);
	log("MonthCardWindow OnBtnClick End");
end

function monthcardWindow:_updateWindow()
	if Call_MonthCardDataHandler().is_30MonthCardAvailable == true then
		self.LeftDayLabel_30RMB:setString(string.format(Call_DataHelper():GetSysLangById(5002),Call_MonthCardDataHandler()._30MonthCardLeftDays));
		if Call_MonthCardDataHandler().is_30MonthCardCanGet == true then
			self.GetBtn_30RMB:setEnabled(true);
			self.GetBtnLabel_30RMB:setString( Call_DataHelper():GetSysLangById(5005) );
		else
			self.GetBtn_30RMB:setEnabled(false);
			self.GetBtnLabel_30RMB:setString( Call_DataHelper():GetSysLangById(5006) );
		end
	else
		self.GetBtnLabel_30RMB:setString( Call_DataHelper():GetSysLangById(6011) );
		self.GetBtn_30RMB:setEnabled(true);
		self.LeftDayLabel_30RMB:setString(string.format(Call_DataHelper():GetSysLangById(5002),0));
	end

	if Call_MonthCardDataHandler().is_60MonthCardAvailable == true then
		self.LeftDayLabel_60RMB:setString(string.format("%d",Call_MonthCardDataHandler()._60MonthCardLeftDays));
		if Call_MonthCardDataHandler().is_60MonthCardCanGet == true then
			self.GetBtn_60RMB:setEnabled(true);
			self.GetBtnLabel_60RMB:setString( Call_DataHelper():GetSysLangById(5005) );
		else
			self.GetBtn_60RMB:setEnabled(false);
			self.GetBtnLabel_60RMB:setString( Call_DataHelper():GetSysLangById(5006) );
		end
	else
		self.GetBtnLabel_60RMB:setString( Call_DataHelper():GetSysLangById(6011) );
		self.GetBtn_60RMB:setEnabled(true);
		self.LeftDayLabel_60RMB:setString(string.format(Call_DataHelper():GetSysLangById(5002),0));
	end

end
