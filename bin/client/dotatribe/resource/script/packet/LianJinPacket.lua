--Name : IPacket.lua
--Function : 提供Lua中网络包类型基类
--Author : fangjun

require "resource/script/packet/IPacket"

-- 请求进入炼金数据
local CSEnterLianJinPacket = IPacket:New(PacketTyper._TYPED_PACKET_LIANJIN_ENTER_)
function Call_CSEnterLianJinPacket()
	return CSEnterLianJinPacket
end

function CSEnterLianJinPacket:Send()
	local helper = Call_PacketHelper()
	helper:BuildPacket(self.m_PacketType)
	helper:PutShort(self.m_ParamTable[1])
	helper:SendPacket()
	self.m_ParamTable = {}
end

-- 进入炼金数据返回
local SCEnterLianJinResultPacket = IPacket:New(PacketTyper._TYPED_PACKET_LIANJIN_ENTERRESULT_)

function Call_SCEnterLianJinResultPacket()
	return SCEnterLianJinResultPacket
end

function SCEnterLianJinResultPacket:OnPacketHandler()
	log("接收到包   SCEnterLianJinResultPacket:OnPacketHandler()")
	require "resource/script/data/LianJinDataHandler"
	Call_LianJinDataHandler().enterData:decodePacketData()

	Call_LianJinDataHandler():ToClientEnterLianJinResult()
end


-- 请求炼金
local CSStartLianJinPacket = IPacket:New(PacketTyper._TYPED_PACKET_LIANJIN_START_)

function Call_CSStartLianJinPacket()
	return CSStartLianJinPacket
end

function CSStartLianJinPacket:Send()
	local helper = Call_PacketHelper()
	helper:BuildPacket(self.m_PacketType)

	helper:SendPacket()
	self.m_ParamTable = {}
end

-- 炼金结果返回
local SCStartLianJinResultPacket = IPacket:New(PacketTyper._TYPED_PACKET_LIANJIN_STARTRESULT_)

function Call_SCStartLianJinResultPacket()
	return SCStartLianJinResultPacket
end

function SCStartLianJinResultPacket:OnPacketHandler()
	log("接收到包   SCStartLianJinResultPacket:OnPacketHandler()")
	-- 解析数据
	require "resource/script/data/LianJinDataHandler"
	Call_LianJinDataHandler().resultData:decodePacketData()

	Call_LianJinDataHandler():ToClientStartLianJinResult()
end
