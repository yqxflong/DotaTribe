--Name : UIWindow.lua
--Function : 提供窗口类型枚举
--Author : fangjun

WindowTyper = {
	_WINDOW_UNKNOW_ = 0,
	_WINDOW_DEMO_ = 1,
	_WINDOW_TEST_ = 2,
	_WINDOW_LIANJIN_ = 3, -- 炼金
	_WINDOW_MONTHCARD_ = 4

}


UIWindow = {
	{type = 1, name = "DemoWindow", isModel = false, ZOrder = 1, openSound = -1, closeSound = -1},
	{type = 2, name = "TestWindow", isModel = false, ZOrder = 1, openSound = -1, closeSound = -1},
	{type = 3, name = "LianJinWindow", isModel = false, ZOrder = 3, openSound = -1, closeSound = -1},
	{type = 4, name = "MonthCardWindow", isModel = false, ZOrder = 1, openSound = -1, closeSound = -1},
}

ViewFile = {
	{id = 1000, path = "resource/layout/ll_luatestwindow_layout.txt", name = "ll_luatestwindow_layout"},
	{id = 1001, path = "resource/layout/ll_luatestwindow2_layout.txt", name = "ll_luatestwindow2_layout"},
	{id = 1002, path = "resource/layout/ll_lianjinactivity_layout.txt", name = "ll_lianjinactivity_layout"},
	{id = 1003, path = "resource/layout/ll_luamonthcardwindow_layout.txt", name = "ll_luamonthcardwindow_layout"},
}