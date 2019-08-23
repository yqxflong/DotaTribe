--Name : IPacket.lua
--Function : 提供Lua中网络包类型基类
--Author : fangjun

require "resource/script/packet/IPacket"


local DemoPacket = IPacket:New(PacketTyper._TYPED_PACKET_DEMO_BEGIN_)

function Call_DemoPacket()
	return DemoPacket
end

function DemoPacket:Send()
	local helper = Call_PacketHelper()
	helper:BuildPacket(self.m_PacketType)

	helper:PutByte(self.m_ParamTable[1])
	helper:PutShort(self.m_ParamTable[2])
	helper:PutInt(self.m_ParamTable[3])
	helper:PutString(self.m_ParamTable[4])

	helper:SendPacket()
	self.m_ParamTable = {}
end

local DemoPacketReply = IPacket:New(PacketTyper._TYPED_PACKET_DEMO_END_)

function Call_DemoPacketReply()
	return DemoPacketReply
end

function DemoPacketReply:OnPacketHandler()
	require "resource/script/data/DemoDataHandler"
	Call_DemoDataHandler().data:decodePacketData()


	Call_DemoDataHandler():ToClientGetReply()

end


