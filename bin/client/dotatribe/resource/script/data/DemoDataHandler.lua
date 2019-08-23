--Name : IDataHelper.lua
--Function : 提供Lua系统数据保存的基类
--Author : fangjun
require "resource/script/packet/PacketHelper"
require "resource/script/event/EventHelper"
require "resource/script/event/EventTyper"
require "resource/script/data/IDataHandler"

local demoDataHandler = IDataHandler:New()


demoDataHandler.data = {decoded = false}

ii = 1

function demoDataHandler.data:decodePacketData()
	self.a = Call_PacketHelper():ReadByte()
	self.b = Call_PacketHelper():ReadShort()
	self.c = Call_PacketHelper():ReadInt()
	self.d = Call_PacketHelper():ReadString()
	self.decoded = true
end



function Call_DemoDataHandler()
	return demoDataHandler
end

function demoDataHandler:Init()

end

function demoDataHandler:Tick()
end

function demoDataHandler:Destroy()
end

function demoDataHandler:ToServerSendPacket()
	require "resource/script/packet/DemoPacket"

	Call_DemoPacket():PutData(12 + ii)
	Call_DemoPacket():PutData(345)
	Call_DemoPacket():PutData(67890)
	Call_DemoPacket():PutData("Hello World!")
	Call_DemoPacket():Send()

	ii = ii + 1
end

function demoDataHandler:ToClientGetReply()
	Call_EventHelper():PushEvent(EventTyper._TYPED_EVENT_DEMOWINDOW_REPLY_)

end



