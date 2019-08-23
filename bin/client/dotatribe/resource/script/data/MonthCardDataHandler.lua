--[[
	Name: MonthCardDataHandler.lua
	Function: 月卡相关数据及操作
	Author: 邵兵 
]]

require "resource/script/packet/PacketHelper"
require "resource/script/event/EventHelper"
require "resource/script/event/EventTyper"
require "resource/script/data/IDataHandler"

local monthcardDataHandler = IDataHandler:New();

monthcardDataHandler.is_30MonthCardAvailable = false;
monthcardDataHandler._30MonthCardLeftDays = 0;
monthcardDataHandler.is_30MonthCardCanGet = false;

monthcardDataHandler.is_60MonthCardAvailable = false;
monthcardDataHandler._60MonthCardLeftDays = 0;
monthcardDataHandler.is_60MonthCardCanGet = false;


function Call_MonthCardDataHandler()
	return monthcardDataHandler;
end

function monthcardDataHandler:Init()
end

function monthcardDataHandler:Tick()
end

function monthcardDataHandler:Destroy()
end


function monthcardDataHandler:QueryBuyMonthCard(_type)
	if _type == _MONTH_CARD_TYPE_30_ then
		--If the monthcard is already bought, return
		if Call_MonthCardDataHandler().is_30MonthCardAvailable == true then
			return;
		end
		---------Send Packet---------
		--
		-----------------------------
	elseif _type == _MONTH_CARD_TYPE_60_ then
		--If the monthcard is already bought, return
		if Call_MonthCardDataHandler().is_30MonthCardAvailable == true then
			return;
		end
		--------Send Packet---------
		--
		----------------------------
	end
end

function monthcardDataHandler:decodeBuyMonthcardPacket()

end

function monthcardDataHandler:AfterHandleBuyMonthcardPacket()

end

function monthcardDataHandler:QueryGetMonthCard(_type)
	if _type == _MONTH_CARD_TYPE_30_ then
		-- If today's Monthcard is already got, return
		if Call_MonthCardDataHandler().is_30MonthCardCanGet == false then
			return;
		end
		---------Send Packet---------
		--
		-----------------------------
	elseif _type == _MONTH_CARD_TYPE_60_ then
		-- If today's Monthcard is already got, return
		if Call_MonthCardDataHandler().is_60MonthCardCanGet == false then
			return;
		end
		---------Send Packet---------
		--
		-----------------------------
	end
end

function monthcardDataHandler:decodeGetMonthcardPacket()
	
end

function monthcardDataHandler:AfterHandleGetMonthcardPacket()

end

