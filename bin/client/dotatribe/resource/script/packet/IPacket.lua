--Name : IPacket.lua
--Function : 提供Lua中网络包类型基类
--Author : fangjun

require "resource/script/packet/PacketHelper"
require "resource/script/packet/PacketTyper"

IPacket = {
	m_PacketType = 0, -- 网络包类型
	m_ParamTable = {}
}

function IPacket:New(packetType)
	local object = object or {}
	setmetatable(object, self)
	self.__index = self

	object.m_PacketType = packetType
	return object
end

function IPacket:PutData(arg)
	table.insert(self.m_ParamTable, arg)
end


-- 获得网络包
function IPacket:GetPacketType()
	return self.m_PacketType
end

-- 解析网络包(需要被子类重载)
function IPacket:OnPacketHandler()
end

-- 发送这个包（需要被子类重载, 将在这个方法中完成包构建、参数压入、发送）
function IPacket:Send()
end

