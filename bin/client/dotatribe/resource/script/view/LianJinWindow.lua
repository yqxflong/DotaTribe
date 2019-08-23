--Name : IView.lua
--Function : 提供Lua页面基类和页面管理
--Author : fangjun

require "resource/script/view/IWindow"
require "resource/script/data/DataHelper"

local lianjinWindow = IWindow:New(WindowTyper._WINDOW_LIANJIN_)

lianjinWindow.m_pRollTable = {}

lianjinWindow.m_nNodeTag = {
	LianJinBg = 0,
	Tips0 = 1,
	Tips1 = 2,
	XianSpine = 3,
	BoardBg = 4,
	Roll0 = 5,
	Roll1 = 6,
	Roll2 = 7,
	Roll3 = 8,
	Roll4 = 9,
	Roll5 = 10,
	RollSpine0 = 11,
	RollSpine1 = 12,
	RollSpine2 = 13,
	RollSpine3 = 14,
	RollSpine4 = 15,
	RollSpine5 = 16,
	StarPatical = 17,
	KuangSpine = 18,
	BoardFrontBg = 19,
	UIKuangSpine = 20,
	LianJinBtn = 21,
	LianJinBtnLabel = 22,
	JewelBg = 23,
	JewelNum = 24,
	BoardCast0 = 25,
	BoardCast1 = 26,
	BoardCast2 = 27,
	NeedBg = 28,
	NeedValue = 29,
	NeedJewelIcon = 30,
}

-- 开始炼金按钮
lianjinWindow.m_pStartBtn = nil

-- 动画节点
lianjinWindow.m_pAnimationTable = {}

-- 动画播放结束状态
lianjinWindow.m_nAnimationState = 0
lianjinWindow.m_nAnimationDestState = 2 ^ 9 - 1

lianjinWindow.m_nActivityId = 0  -- 活动ID

function Call_LianJinWindow()
	require "resource/script/data/LianJinDataHandler"
	require "resource/script/packet/LianJinPacket"

	return lianjinWindow
end

function lianjinWindow:_initLayout()
	log("lianjinWindow:_initLayout()    begin")
	Call_UIHelper():AutoCreateNodeByTable(1002, self.m_pRootNode)

	--创建六个数字滚筒
	local boardbg = "resource/image/lianjin/ljdip.png"
	local picTemplate = "resource/image/lianjin/lj_%d.png"
	local roll = nil
	local rollMask = nil
	for i = 0, 5 do
		rollMask = tolua.cast(self.m_pRootNode:getChildByTag(self.m_nNodeTag.Roll0 + i), "MaskNode")
		log("  for i = " .. i)
		local viewData = rollMask:GetViewData()
		roll = RollingBoard:create(picTemplate, 10, boardbg, 0, 7.5 - i, nil, viewData.colorB_, viewData.width_, viewData.height_, viewData.posx_, viewData.posy_)
		table.insert(self.m_pRollTable, roll)
		--rollMask:addChild(roll)
		roll:setPosition(ccp(viewData.posx_ + viewData.width_ / 2, viewData.posy_ + viewData.height_ / 2))
		self.m_pRootNode:addChild(roll, rollMask:getZOrder())
	end

	-- 注册最后一个停止的滚动牌事件响应
	self.m_pRollTable[1]:RegisterCallBackScript(handler(self, self.On_Rolling_End_Callback))



	--local animation = NFC_getLoopFrameEffect(2057)
	--self.m_pRootNode:addChild(animation)
	--animation:setPosition(ccp(512, 360))


	log("lianjinWindow:_initLayout()    end")
end

function lianjinWindow:_mapBtn()
	log("lianjinWindow:_mapBtn    begin")
	local menu = tolua.cast(self.m_pRootNode:getChildByTag(self.m_nNodeTag.LianJinBtn), "CCMenu")
	local item = tolua.cast(menu:getChildByTag(0), "CMenuItemSprite")
	item:setTag(self.m_nNodeTag.LianJinBtn)
	item:registerScriptTapHandler(handler(self, self.On_Btn_Click))
	self.m_pStartBtn = item

	log("lianjinWindow:_mapBtn    end")
end

function lianjinWindow:Init()
	self:RegisterEvent(EventTyper._TYPED_EVENT_LIANJINWINDOW_SHOW_)
	self:RegisterEvent(EventTyper._TYPED_EVENT_LIANJINWINDOW_HIDE_, true)

	self:RegisterEvent(EventTyper._TYPED_EVENT_LIANJINWINDOW_ENTER_RESULT_, true)
	self:RegisterEvent(EventTyper._TYPED_EVENT_LIANJINWINDOW_START_RESULT_, true)
	--self:RegisterEvent(EventTyper._TYPED_EVENT_REFRESH_UPDATEUI_, true)
	self:RegisterEvent(EventTyper._TYPED_EVENT_LIANJINWINDOW_SYNC_BROADCAST_, true)

	return self.super.Init(self)

end

function lianjinWindow:Load()
	log("lianjinWindow:Load    begin")
	if self.super.Load(self) == false then
		return false
	end

	self:_initLayout()

	self:_initAnimation()

	self:_mapBtn()

	log("lianjinWindow:Load    end")

	return true
end

function lianjinWindow:Tick()
	-- 倒计时
	local enterData = Call_LianJinDataHandler().enterData
	if enterData.leftTime ~= nil then
		local nowtime = os.time()
		local during = nowtime - enterData.tickBeginTime
		if during > 0 then
			enterData.leftTime = enterData.leftTime - during
			enterData.tickBeginTime = nowtime
			if enterData.leftTime < 0 then
				enterData.leftTime = 0
			end
			local line1 = string.format(Call_DataHelper():GetSysLangById(2085)
				, enterData.leftTime / (24 * 3600), (enterData.leftTime % (24 * 3600)) / 3600, ((enterData.leftTime % (24 * 3600)) % 3600) / 60, ((enterData.leftTime % (24 * 3600)) % 3600) % 60)
			NFC_setLabelString(self.m_nNodeTag.Tips1, self.m_pRootNode, line1)
		end
	end

end

function lianjinWindow:Destroy()

	-- 销毁当前页面保存的table
	self.m_pRollTable = {}

	self.m_pStartBtn = nil

	self.m_pAnimationTable = {}

	self.m_pAnimationState = 0

	self.super.Destroy(self)
end

function lianjinWindow:OnEventHandler(eventType, paramTable)
	log("lianjinWindow:OnEventHandler    " .. eventType)
	if eventType == EventTyper._TYPED_EVENT_LIANJINWINDOW_SHOW_ then
		log("lianjinWindow:OnEventHandler    paramTable:" .. paramTable[1])
		self:Show(true)
		if table.getn(paramTable) > 0 then
			local activityId = tonumber(paramTable[1])
			Call_LianJinDataHandler().enterData.m_nActivityId = activityId
		end
	elseif eventType == EventTyper._TYPED_EVENT_LIANJINWINDOW_HIDE_ then
		self:Destroy()
	elseif eventType == EventTyper._TYPED_EVENT_LIANJINWINDOW_ENTER_RESULT_ then
		-- 收到进入炼金数据返回
		self:Function_GetEnterResult()
	elseif eventType == EventTyper._TYPED_EVENT_LIANJINWINDOW_START_RESULT_ then
		-- 收到炼金结果返回
		self:Function_GetLianJinResult()
	--[[elseif eventType == EventTyper._TYPED_EVENT_REFRESH_UPDATEUI_ then
		-- 界面钻石更新
		self:_setShowJewels()]]
	elseif eventType == EventTyper._TYPED_EVENT_LIANJINWINDOW_SYNC_BROADCAST_ then
		-- 收到广播的炼金消息
		self:_setBoardCast()
	end
end

function lianjinWindow:On_Btn_Click(itemTag, menuItem)
	log("lianjinWindow:On_Btn_Click   tag:" .. itemTag)
	if itemTag == self.m_nNodeTag.LianJinBtn then
		-- 炼金按钮置灰
		menuItem:setEnabled(false)

		-- 请求服务器炼金
		--require "resource/script/data/LianJinDataHandler"
		Call_LianJinDataHandler():ToServerStartLianJin()
	end
end

function lianjinWindow:Function_GetEnterResult()
	-- 获得当前页面信息
	self:_setPageInfo()

	NFC_showCommunicationWating(false)
end

function lianjinWindow:Function_GetLianJinResult()
	log("lianjinWindow:Function_GetLianJinResult()    begin")
	-- 移除需要钻石数显示的底板和状态
	for i = self.m_nNodeTag.NeedBg, self.m_nNodeTag.NeedJewelIcon do
		NFC_showNode(i, self.m_pRootNode, false)
	end


	-- 获得炼金结果
	local num = Call_LianJinDataHandler().resultData.getJewels
	-- 设置滚筒目标
	self.m_pRollTable[1]:SetResultNum(num / 100000)
	self.m_pRollTable[2]:SetResultNum((num / 10000) % 10)
	self.m_pRollTable[3]:SetResultNum((num / 1000) % 10)
	self.m_pRollTable[4]:SetResultNum((num / 100) % 10)
	self.m_pRollTable[5]:SetResultNum((num / 10) % 10)
	self.m_pRollTable[6]:SetResultNum((num / 1) % 10)
	
	-- 需要开始滚动
	for i = 1, 6 do
		local roll = self.m_pRollTable[i]
		roll:Run()
	end

	log("lianjinWindow:Function_GetLianJinResult()    begin")
end

function lianjinWindow:Function_GetBoardCast()
	-- 获得广播信息


end


function lianjinWindow:_setPageInfo()
	log("lianjinWindow:_setPageInfo()    begin")
	-- 设置当前页面的信息
	local enterData = Call_LianJinDataHandler().enterData
	-- 设置tips
	local line0 = string.format(Call_DataHelper():GetSysLangById(2084), enterData.totalDay, enterData.haveChallenge)
	NFC_setLabelString(self.m_nNodeTag.Tips0, self.m_pRootNode, line0)
	local line1 = string.format(Call_DataHelper():GetSysLangById(2085)
		, enterData.leftTime / (24 * 3600), (enterData.leftTime % (24 * 3600)) / 3600, ((enterData.leftTime % (24 * 3600)) % 3600) / 60, ((enterData.leftTime % (24 * 3600)) % 3600) % 60)
	NFC_setLabelString(self.m_nNodeTag.Tips1, self.m_pRootNode, line1)

	-- 设置当前需要花费的钻石数
	for i = self.m_nNodeTag.NeedBg, self.m_nNodeTag.NeedJewelIcon do
		NFC_showNode(i, self.m_pRootNode, true)
	end
	local needline = string.format(Call_DataHelper():GetSysLangById(2087), enterData.spentJewels)
	NFC_setLabelString(self.m_nNodeTag.NeedValue, self.m_pRootNode, needline)

	-- 设置滚筒清零
	-- 需要开始滚动
	for i = 1, 6 do
		local roll = self.m_pRollTable[i]
		roll:ResetZero()
	end

	-- 设置炼金按钮状态
	self:_setLianJinBtnState()

	--设置钻石数
	self:_setShowJewels()

	log("lianjinWindow:_setPageInfo()    end")
end

function lianjinWindow:_setLianJinBtnState()
	-- 设置炼金按钮状态
	local enterData = Call_LianJinDataHandler().enterData
	if enterData.haveChallenge > 0 then
		if self.m_pStartBtn ~= nil then
			self.m_pStartBtn:setEnabled(true)
		end
	else
		if self.m_pStartBtn ~= nil then
			self.m_pStartBtn:setEnabled(false)
		end
	end
end

function lianjinWindow:_setShowJewels()
	-- 设置当前钻石数
	local jewel = Call_DataHelper():GetRoleInfoDataHandler().m_pRIData.jewels_
	NFC_setLabelString(self.m_nNodeTag.JewelNum, self.m_pRootNode, jewel)
end

function lianjinWindow:_setBoardCast()
	-- 设置广播信息
	local bcd = Call_LianJinDataHandler().boardcastData
	NFC_setLabelString(self.m_nNodeTag.BoardCast0, self.m_pRootNode, bcd.contentTable[1])
	NFC_setLabelString(self.m_nNodeTag.BoardCast1, self.m_pRootNode, bcd.contentTable[2])
	NFC_setLabelString(self.m_nNodeTag.BoardCast2, self.m_pRootNode, bcd.contentTable[3])

end

function lianjinWindow:On_Rolling_End_Callback(functionName, tag, param)
	-- 滚动板结束滚动效果
	-- 滚动结束之后，需要增加一个特效
	self:_playAnimation()
end


-- 初始化动画节点
function lianjinWindow:_initAnimation()
	-- xian 动画Spine
	self.m_pAnimationTable.XianSpine = tolua.cast(self.m_pRootNode:getChildByTag(self.m_nNodeTag.XianSpine), "CCSkeletonAnimation")
	self.m_pAnimationTable.XianSpine:registerScriptEventDelegate(handler(self, self.On_SpineAnimation_Callback))
	-- 六个卡牌spine
	self.m_pAnimationTable.RollSpine0 = tolua.cast(self.m_pRootNode:getChildByTag(self.m_nNodeTag.RollSpine0), "CCSkeletonAnimation")
	self.m_pAnimationTable.RollSpine0:registerScriptEventDelegate(handler(self, self.On_SpineAnimation_Callback))
	self.m_pAnimationTable.RollSpine1 = tolua.cast(self.m_pRootNode:getChildByTag(self.m_nNodeTag.RollSpine1), "CCSkeletonAnimation")
	self.m_pAnimationTable.RollSpine1:registerScriptEventDelegate(handler(self, self.On_SpineAnimation_Callback))
	self.m_pAnimationTable.RollSpine2 = tolua.cast(self.m_pRootNode:getChildByTag(self.m_nNodeTag.RollSpine2), "CCSkeletonAnimation")
	self.m_pAnimationTable.RollSpine2:registerScriptEventDelegate(handler(self, self.On_SpineAnimation_Callback))
	self.m_pAnimationTable.RollSpine3 = tolua.cast(self.m_pRootNode:getChildByTag(self.m_nNodeTag.RollSpine3), "CCSkeletonAnimation")
	self.m_pAnimationTable.RollSpine3:registerScriptEventDelegate(handler(self, self.On_SpineAnimation_Callback))
	self.m_pAnimationTable.RollSpine4 = tolua.cast(self.m_pRootNode:getChildByTag(self.m_nNodeTag.RollSpine4), "CCSkeletonAnimation")
	self.m_pAnimationTable.RollSpine4:registerScriptEventDelegate(handler(self, self.On_SpineAnimation_Callback))
	self.m_pAnimationTable.RollSpine5 = tolua.cast(self.m_pRootNode:getChildByTag(self.m_nNodeTag.RollSpine5), "CCSkeletonAnimation")
	self.m_pAnimationTable.RollSpine5:registerScriptEventDelegate(handler(self, self.On_SpineAnimation_Callback))
	-- lianjinstar 粒子 面具节点
	self.m_pAnimationTable.StarPaticalMask = tolua.cast(self.m_pRootNode:getChildByTag(self.m_nNodeTag.StarPatical), "MaskNode")
	-- kuang 动画spine
	self.m_pAnimationTable.KuangSpine = tolua.cast(self.m_pRootNode:getChildByTag(self.m_nNodeTag.KuangSpine), "CCSkeletonAnimation")
	self.m_pAnimationTable.KuangSpine:registerScriptEventDelegate(handler(self, self.On_SpineAnimation_Callback))
	-- ui 动画spine
	self.m_pAnimationTable.UIKuangSpine = tolua.cast(self.m_pRootNode:getChildByTag(self.m_nNodeTag.UIKuangSpine), "CCSkeletonAnimation")
	self.m_pAnimationTable.UIKuangSpine:registerScriptEventDelegate(handler(self, self.On_SpineAnimation_Callback))
end

function lianjinWindow:_playAnimation()

	self.m_nAnimationState = 0

	-- xian 动画Spine
	self.m_pAnimationTable.XianSpine:setAnimation("xian", false, 0)
	self.m_pAnimationTable.XianSpine:setVisible(true)
	-- 六个卡牌spine
	self.m_pAnimationTable.RollSpine0:setAnimation("cardglow", false, 1)
	self.m_pAnimationTable.RollSpine0:setVisible(true)
	self.m_pAnimationTable.RollSpine1:setAnimation("cardglow", false, 2)
	self.m_pAnimationTable.RollSpine1:setVisible(true)
	self.m_pAnimationTable.RollSpine2:setAnimation("cardglow", false, 3)
	self.m_pAnimationTable.RollSpine2:setVisible(true)
	self.m_pAnimationTable.RollSpine3:setAnimation("cardglow", false, 4)
	self.m_pAnimationTable.RollSpine3:setVisible(true)
	self.m_pAnimationTable.RollSpine4:setAnimation("cardglow", false, 5)
	self.m_pAnimationTable.RollSpine4:setVisible(true)
	self.m_pAnimationTable.RollSpine5:setAnimation("cardglow", false, 6)
	self.m_pAnimationTable.RollSpine5:setVisible(true)
	-- lianjinstar 粒子 面具节点
	local particelEffectId = self.m_pAnimationTable.StarPaticalMask:GetViewData().colorR_
	local star = NFC_getParticelEffect(particelEffectId, false)
	self.m_pAnimationTable.StarPaticalMask:addChild(star)
	-- kuang 动画spine
	self.m_pAnimationTable.KuangSpine:setAnimation("kuang", false, 7)
	self.m_pAnimationTable.KuangSpine:setVisible(true)
	-- ui 动画spine
	self.m_pAnimationTable.UIKuangSpine:setAnimation("uiglow", false, 8)
	self.m_pAnimationTable.UIKuangSpine:setVisible(true)

end

function lianjinWindow:On_SpineAnimation_Callback(functionName, eventId, animationId, object)
	-- 将当前的动画隐藏
	--local spine = tolua.cast(object, "CCNode")
	local spine = object
	if spine:isVisible() == false then
		
		return
	end

	spine:setVisible(false)

	-- 判断所有动画播放完成后请求当前页面的数据信息
	self.m_nAnimationState = self.m_nAnimationState + (2 ^ tonumber(animationId))

	if(self.m_nAnimationState == self.m_nAnimationDestState) then
		self.m_nAnimationState = 0
		-- 开始飘钻石
		local num = Call_LianJinDataHandler().resultData.getJewels
		Call_DataHelper():ShowFlowEffect(3, num, 1, 0)
		-- 重新请求此页面上部分数据
		Call_LianJinDataHandler():ToServerEnterLianJin()
	end
end
