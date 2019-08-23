-------------------- 一些公用方法
require "resource/script/util/define"

-- log打印
cclog = function(...)
    print(string.format(...))
end

-- 迭代器
function list_iter(_table)
    local i = 0
    local n = table.getn(_table)
    return function ()
        i = i + 1
        if i <= n then return _table[i] end
    end
end

-- 定时器
const_scheduler = CCDirector:sharedDirector():getScheduler()

-- 窗口
const_window_size = CCDirector:sharedDirector():getWinSize()

-- 字符串比较相等
function string_equal(dest, source)
	local len = string.len(dest)

	local i, j = string.find(dest, source)
	if i == 1 and j == len then
		return true
	end

	return false
end

-- log打印
function log(info)
    if SYSTEM_LOG_STATUS == true then
        print("[" .. os.date("%X", time) .. "]: ".. info)
    end
end

-- log Table
function logTable (sig,table)
    for k,v in ipairs(table) do 
        print('[' .. os.date('%X', time) .. ']: '.. sig .. ' = key: ' .. k .. ' value: ' .. v)
    end 
end

-- 用于包装方法
function handler(target, method)
    return function(...)
        return method(target, ...)
    end
end
