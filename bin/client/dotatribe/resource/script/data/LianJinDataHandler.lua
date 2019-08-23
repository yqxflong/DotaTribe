--Name : IDataHelper.lua
--Function : 提供Lua系统数据保存的基类
--Author : fangjun
require "resource/script/packet/PacketHelper"
require "resource/script/event/EventHelper"
require "resource/script/event/EventTyper"
require "resource/script/data/IDataHandler"

local lianjinDataHandler = IDataHandler:New()


lianjinDataHandler.enterData = {decoded = false, m_nActivityId = 0}

lianjinDataHandler.resultData = {decoded = false}

lianjinDataHandler.boardcastData = {contentTable = {"", "", ""}, decoded = false}

function lianjinDataHandler.enterData:decodePacketData()
	self.totalDay = Call_PacketHelper():ReadInt() -- 活动
	self.leftTime = Call_PacketHelper():ReadInt() -- 剩余时间
	self.haveChallenge = Call_PacketHelper():ReadByte() -- 剩余机会
	self.spentJewels = Call_PacketHelper():ReadInt() -- 当前需要花费的钻石数
	self.tickBeginTime = os.time() -- 计时开始时间
	self.decoded = true
end

function lianjinDataHandler.resultData:decodePacketData()
	self.getJewels = Call_PacketHelper():ReadInt() -- 获得钻石数
	self.decoded = true
end

function lianjinDataHandler.boardcastData.decodePacketData()
	self.contentTable[1] = Call_PacketHelper():ReadString()
	self.contentTable[2] = Call_PacketHelper():ReadString()
	self.contentTable[3] = Call_PacketHelper():ReadString()
end

function Call_LianJinDataHandler()
	return lianjinDataHandler
end

function lianjinDataHandler:Init()

end

function lianjinDataHandler:Tick()
end

function lianjinDataHandler:Destroy()
end

function lianjinDataHandler:ToServerEnterLianJin()
	require "resource/script/packet/LianJinPacket"
	Call_CSEnterLianJinPacket():PutData(self.enterData.m_nActivityId)
	Call_CSEnterLianJinPacket():Send()
end

function lianjinDataHandler:ToClientEnterLianJinResult()
	Call_EventHelper():PushEvent(EventTyper._TYPED_EVENT_LIANJINWINDOW_ENTER_RESULT_)
end

function lianjinDataHandler:ToServerStartLianJin()
	require "resource/script/packet/LianJinPacket"

	Call_CSStartLianJinPacket():Send()
end

function lianjinDataHandler:ToClientStartLianJinResult()
	Call_EventHelper():PushEvent(EventTyper._TYPED_EVENT_LIANJINWINDOW_START_RESULT_)
end

function lianjinDataHandler:ToServerSyncBrocasr()
	Call_EventHelper():PushEvent(EventTyper._TYPED_EVENT_LIANJINWINDOW_SYNC_BROADCAST_)
end


