--Name : PacketHelper.lua
--Function : 提供Lua中网络的方法封装
--Author : fangjun

packetHelper = {}
packetHelper.__index = packetHelper

packetHelperCXX = tolua.cast(PacketHelper:LuaGetInstance(), PacketHelper:LuaGetInstanceName())


function Call_PacketHelper()
	return packetHelper
end

function packetHelper:RegisterPacket(packetType)
	return packetHelperCXX:LuaRegisterPacket(packetType)
end

function packetHelper:BuildPacket(packetType)
	return packetHelperCXX:LuaBuildPacket(packetType)
end

function packetHelper:PutByte(arg)
	return packetHelperCXX:LuaPutByte(arg)
end

function packetHelper:PutShort(arg)
	return packetHelperCXX:LuaPutShort(arg)
end

function packetHelper:PutInt(arg)
	return packetHelperCXX:LuaPutInt(arg)
end

function packetHelper:PutString(arg)
	return packetHelperCXX:LuaPutString(arg)
end

function packetHelper:SendPacket()
	return packetHelperCXX:LuaSendPacket()
end

function packetHelper:ReadPn()
	return packetHelperCXX:LuaReadPn()
end

function packetHelper:ReadByte()
	return packetHelperCXX:LuaReadByte()
end

function packetHelper:ReadShort()
	return packetHelperCXX:LuaReadShort()
end

function packetHelper:ReadInt()
	return packetHelperCXX:LuaReadInt()
end

function packetHelper:ReadString()
	return packetHelperCXX:LuaReadString()
end

