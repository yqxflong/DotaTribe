--Name : PacketManager.lua
--Function : 提供Lua网络包注册和管理页
--Author : fangjun

require "resource/script/packet/PacketHelper"

local packetManager = {}
packetManager.__index = packetManager

packetManager.packetTable = {}

function Call_PacketManager()
	return packetManager
end

function packetManager:Init()
	log("packetManager:Init     begin")

	-- 此处需要将所有接收Packet都进行注册
	require "resource/script/packet/DemoPacket"
	self:RegisterPacket(Call_DemoPacketReply()) -- 注册第5002条接收协议
	require "resource/script/packet/LianJinPacket"
	self:RegisterPacket(Call_SCEnterLianJinResultPacket())
	self:RegisterPacket(Call_SCStartLianJinResultPacket())




	log("packetManager:Init     end")
end

function packetManager:Tick()
	-- tick中不需要进行操作
end

function packetManager:Destroy()
	-- 不需要对包进行销毁

	-- 需要将包全部清空
	self.packetTable = {}

end


-- 注册接收网络包（用于之后收到包时的推送）
function packetManager:RegisterPacket(packet)
	table.insert(self.packetTable, packet)

	-- 注册于C++
	Call_PacketHelper():RegisterPacket(packet:GetPacketType())

end

-- 获得当前包类型的包对象
function packetManager:GetPacketObject(packetType)
	for item in list_iter(self.packetTable) do
		if item:GetPacketType() == packetType then
			return item
		end
	end

	return nil
end

-- 网络包的解析
function packetManager:OnPacketHandler(packetType)
	-- 此处推送到注册的网络包对象中进行解析
	if packetType > 0 then
		local obj = self:GetPacketObject(packetType)

		if obj ~= nil then
			obj:OnPacketHandler()
		end

	end
end

