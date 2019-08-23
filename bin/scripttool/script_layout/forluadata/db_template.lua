-- Filename: <FILENAME>.lua
-- Author: auto-created by XmlToScript tool.
-- Function: it`s auto-created by XmlToScript tool.

module("<FILENAME>", package.seeall)

<KEYNOTES>

keys = {
	<VAR_KEY>
}

<TABLENAME> = {
	<VAR_TABLE>
}

local mt = {}
mt.__index = function (table, key)
	for i = 1, #keys do
		if (keys[i] == key) then
			return table[i]
		end
	end
	
end

function getDataById(key_id)
	local id_data = Item_feed["id_" .. key_id]
	if id_data == nil then
		return nil
	end
	if getmetatable(id_data) ~= nil then
		return id_data
	end
	setmetatable(id_data, mt)

	return id_data
end

function getArrDataByField(fieldName, fieldValue)
	local arrData = {}
	local fieldNo = 1
	for i=1, #keys do
		if keys[i] == fieldName then
			fieldNo = i
			break
		end
	end
	for k, v in pairs(Item_feed) do
		if v[fieldNo] == fieldValue then
			setmetatable (v, mt)
			arrData[#arrData+1] = v
		end
	end

	return arrData
end

function release()
	_G["<FILENAME>"] = nil
	package.loaded["<FILENAME>"] = nil
	package.loaded["db/<FILENAME>"] = nil
end

