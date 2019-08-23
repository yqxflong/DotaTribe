-- usage: (use instead of ant)
-- tolua++ "-L" "basic.lua" "-o" "../../cocos2dx_support/LuaDota.cpp" "Dota.pkg"

_is_functions = _is_functions or {}
_to_functions = _to_functions or {}
_push_functions = _push_functions or {}

local CCObjectTypes = {
}

-- register CCObject types
for i = 1, #CCObjectTypes do
    _push_functions[CCObjectTypes[i]] = "toluafix_pushusertype_ccobject"
end

-- register LUA_FUNCTION, LUA_TABLE, LUA_HANDLE type
_to_functions["LUA_FUNCTION"] = "toluafix_ref_function"
_is_functions["LUA_FUNCTION"] = "toluafix_isfunction"
_to_functions["LUA_TABLE"] = "toluafix_totable"
_is_functions["LUA_TABLE"] = "toluafix_istable"

local toWrite = {}
local currentString = ''
local out
local WRITE, OUTPUT = write, output

function output(s)
    out = _OUTPUT
    output = OUTPUT -- restore
    output(s)
end

function write(a)
    if out == _OUTPUT then
        currentString = currentString .. a
        if string.sub(currentString,-1) == '\n'  then
            toWrite[#toWrite+1] = currentString
            currentString = ''
        end
    else
        WRITE(a)
    end
end

function post_output_hook(package)
    local result = table.concat(toWrite)
    local function replace(pattern, replacement)
        local k = 0
        local nxt, currentString = 1, ''
        repeat
            local s, e = string.find(result, pattern, nxt, true)
            if e then
                currentString = currentString .. string.sub(result, nxt, s-1) .. replacement
                nxt = e + 1
                k = k + 1
            end
        until not e
        result = currentString..string.sub(result, nxt)
        if k == 0 then print('Pattern not replaced', pattern) end
    end

    replace([[#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"]],
      [[/****************************************************************************
 Copyright (c) 2011 Dota
 ****************************************************************************/

extern "C" {
#include "tolua_fix.h"
}

#include <map>
#include <string>
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

#include "LuaSystem.h"
#include "DBHelper.h"
#include "UIHelper.h"
#include "EventHelper.h"
#include "PacketHelper.h"
#include "CMenuItemSprite.h"

#include "ArtFontLabelBatchNode.h"
#include "AutoFadeOutLable.h"
#include "CAnimationSprite.h"
#include "CCardsStarProgress.h"
#include "CCDragNodeLayer.h"
#include "CCGrapSprite.h"
#include "CCornerNumIcon.h"
#include "CCRectClipNode.h"
#include "CCSignSprite.h"
#include "CDragSprite.h"
#include "CPageScroll.h"
#include "CPriorityLayerColor.h"
#include "CProgressInnerBar.h"
#include "CProgressTimer.h"
#include "CSelectedSprite.h"
#include "CSimpleActionSprite.h"
#include "CSprite.h"
#include "CTableView.h"
#include "CTeamIconProgress.h"
#include "CTimeLabel.h"
#include "CTouchSprite.h"
#include "FAnimationButton.h"
#include "GrapStarsProgress.h"
#include "MaskNode.h"
#include "MoveAnimation.h"
#include "PreCCMoveTo.h"
#include "ScaleSprite.h"
#include "SceneEffect.h"
#include "SingleTouchProtocol.h"
#include "UIBaseDialog.h"
#include "UITwoSideStretchNodeLayer.h"
#include "NFAnimationController.h"
#include "NFControlsManager.h"
#include "DTAwardBoard.h"
#include "DTEquipBoard.h"
#include "DTHeroIcon.h"
#include "DTRoleStatusBar.h"
#include "DTTimedGrayWindow.h"
#include "BlurSprite.h"
#include "RollingBoard.h"
#include "UIViewDataManger.h"
#include "RoleInfoDataHandler.h"


#include "RoleEquipDataHandler.h"
#include "BagEquipDataHandler.h"


using namespace cocos2d;
using namespace cocos2d::extension;
using namespace CocosDenshion;
using namespace std;]])

      replace([[/* Exported function */
TOLUA_API int  tolua_Dota_open (lua_State* tolua_S);]], [[]])

      replace([[*((LUA_FUNCTION*)]], [[(]])

      replace([[tolua_usertype(tolua_S,"LUA_FUNCTION");]], [[]])

      replace('\t', '    ')

    WRITE(result)
end
