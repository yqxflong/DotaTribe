/*
** Lua binding: Dota
** Generated automatically by tolua++-1.0.92 on 07/07/14 14:12:08.
*/

/****************************************************************************
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
using namespace std;



#include "LuaDota.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_CPriorityLayerColor (lua_State* tolua_S)
{
 CPriorityLayerColor* self = (CPriorityLayerColor*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_AutoDelayAnimation (lua_State* tolua_S)
{
 AutoDelayAnimation* self = (AutoDelayAnimation*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CCornerNumIcon (lua_State* tolua_S)
{
 CCornerNumIcon* self = (CCornerNumIcon*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CCSignSprite (lua_State* tolua_S)
{
 CCSignSprite* self = (CCSignSprite*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_ArtFontLabelBatchNode (lua_State* tolua_S)
{
 ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CMenuItemSprite (lua_State* tolua_S)
{
 CMenuItemSprite* self = (CMenuItemSprite*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_MoveAnimation (lua_State* tolua_S)
{
 MoveAnimation* self = (MoveAnimation*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CProgressInnerBar (lua_State* tolua_S)
{
 CProgressInnerBar* self = (CProgressInnerBar*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CCardsStarProgress (lua_State* tolua_S)
{
 CCardsStarProgress* self = (CCardsStarProgress*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CDragSprite (lua_State* tolua_S)
{
 CDragSprite* self = (CDragSprite*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_GLubyte (lua_State* tolua_S)
{
 GLubyte* self = (GLubyte*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CTableView (lua_State* tolua_S)
{
 CTableView* self = (CTableView*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CMapScrollView (lua_State* tolua_S)
{
 CMapScrollView* self = (CMapScrollView*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_DTTimedGrayWindow (lua_State* tolua_S)
{
 DTTimedGrayWindow* self = (DTTimedGrayWindow*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_AutoFadeOutLabelManager (lua_State* tolua_S)
{
 AutoFadeOutLabelManager* self = (AutoFadeOutLabelManager*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CCRectClipNode (lua_State* tolua_S)
{
 CCRectClipNode* self = (CCRectClipNode*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_RoleInfoDataHandler (lua_State* tolua_S)
{
 RoleInfoDataHandler* self = (RoleInfoDataHandler*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CCRect (lua_State* tolua_S)
{
 CCRect* self = (CCRect*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CTouchSprite (lua_State* tolua_S)
{
 CTouchSprite* self = (CTouchSprite*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CAnimationSprite (lua_State* tolua_S)
{
 CAnimationSprite* self = (CAnimationSprite*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_SceneEffect (lua_State* tolua_S)
{
 SceneEffect* self = (SceneEffect*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_std__vector_BagEquipData__ (lua_State* tolua_S)
{
 std::vector<BagEquipData*>* self = (std::vector<BagEquipData*>*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CCSize (lua_State* tolua_S)
{
 CCSize* self = (CCSize*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_UITowSideStretchNodeLayer (lua_State* tolua_S)
{
 UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_PlayerStatus (lua_State* tolua_S)
{
 PlayerStatus* self = (PlayerStatus*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CCDragNodeLayer (lua_State* tolua_S)
{
 CCDragNodeLayer* self = (CCDragNodeLayer*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_DTRoleStatusBar (lua_State* tolua_S)
{
 DTRoleStatusBar* self = (DTRoleStatusBar*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_DTEquipBoard (lua_State* tolua_S)
{
 DTEquipBoard* self = (DTEquipBoard*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_DTAwardBoard (lua_State* tolua_S)
{
 DTAwardBoard* self = (DTAwardBoard*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_UIBaseDialog (lua_State* tolua_S)
{
 UIBaseDialog* self = (UIBaseDialog*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_FAnimationButton (lua_State* tolua_S)
{
 FAnimationButton* self = (FAnimationButton*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CCPoint (lua_State* tolua_S)
{
 CCPoint* self = (CCPoint*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CScrollView (lua_State* tolua_S)
{
 CScrollView* self = (CScrollView*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_SignSpriteType (lua_State* tolua_S)
{
 SignSpriteType* self = (SignSpriteType*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_GrapStarsProgress (lua_State* tolua_S)
{
 GrapStarsProgress* self = (GrapStarsProgress*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_SingleTouchProtocol (lua_State* tolua_S)
{
 SingleTouchProtocol* self = (SingleTouchProtocol*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CCGrapSprite (lua_State* tolua_S)
{
 CCGrapSprite* self = (CCGrapSprite*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CTeamIconProgress (lua_State* tolua_S)
{
 CTeamIconProgress* self = (CTeamIconProgress*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CSpriteInSprite (lua_State* tolua_S)
{
 CSpriteInSprite* self = (CSpriteInSprite*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CProgressTimer (lua_State* tolua_S)
{
 CProgressTimer* self = (CProgressTimer*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CTitleSprite (lua_State* tolua_S)
{
 CTitleSprite* self = (CTitleSprite*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CPageScroll (lua_State* tolua_S)
{
 CPageScroll* self = (CPageScroll*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_FAPriorityMenu (lua_State* tolua_S)
{
 FAPriorityMenu* self = (FAPriorityMenu*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CLabelButtonItem (lua_State* tolua_S)
{
 CLabelButtonItem* self = (CLabelButtonItem*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CPriorityLayerColor");
 tolua_usertype(tolua_S,"CCSignSprite");
 tolua_usertype(tolua_S,"RollingBoard");
 tolua_usertype(tolua_S,"MoveAnimation");
 tolua_usertype(tolua_S,"MaskNode");
 tolua_usertype(tolua_S,"SkinTemplate");
 tolua_usertype(tolua_S,"UIBaseDialogProtory");
 tolua_usertype(tolua_S,"CSpriteSelected");
 tolua_usertype(tolua_S,"CTitleSprite");
 tolua_usertype(tolua_S,"std::vector<CCSignSprite*>");
 tolua_usertype(tolua_S,"CCDragNodeLayer");
 tolua_usertype(tolua_S,"CCDelayTime");
 tolua_usertype(tolua_S,"CPageScrollDelegate");
 tolua_usertype(tolua_S,"CSelectedSprite");
 tolua_usertype(tolua_S,"CScrollView");
 tolua_usertype(tolua_S,"CCTargetedTouchDelegate");
 tolua_usertype(tolua_S,"BagEquipDataHandler");
 tolua_usertype(tolua_S,"CCScale9Sprite");
 tolua_usertype(tolua_S,"CCMoveTo");
 tolua_usertype(tolua_S,"CCSprite");
 tolua_usertype(tolua_S,"CCImmovableMenu");
 tolua_usertype(tolua_S,"CPageScroll");
 tolua_usertype(tolua_S,"FAPriorityMenu");
 tolua_usertype(tolua_S,"CCTexture2D");
 tolua_usertype(tolua_S,"CCTouch");
 tolua_usertype(tolua_S,"CCParticleSystemQuad");
 tolua_usertype(tolua_S,"CCMenu");
 tolua_usertype(tolua_S,"CCardsStarProgress");
 tolua_usertype(tolua_S,"BaseObject");
 tolua_usertype(tolua_S,"FAnimationButton");
 tolua_usertype(tolua_S,"CCLayerColor");
 tolua_usertype(tolua_S,"UIBaseDialog");
 tolua_usertype(tolua_S,"CSprite");
 tolua_usertype(tolua_S,"FrameAnimationDelegate");
 tolua_usertype(tolua_S,"DTTimedGrayWindow");
 tolua_usertype(tolua_S,"CDragSpriteDelegate");
 tolua_usertype(tolua_S,"RoleInfoDataHandler");
 tolua_usertype(tolua_S,"CCRect");
 tolua_usertype(tolua_S,"BlurSprite");
 tolua_usertype(tolua_S,"EventHelper");
 tolua_usertype(tolua_S,"SceneEffect");
 tolua_usertype(tolua_S,"MoveAnimationCallBackProtocol");
 tolua_usertype(tolua_S,"CCLayerMask");
 tolua_usertype(tolua_S,"UITowSideStretchNodeLayer");
 tolua_usertype(tolua_S,"std::vector<float>");
 tolua_usertype(tolua_S,"DTAwardBoard");
 tolua_usertype(tolua_S,"RoleInfoData");
 tolua_usertype(tolua_S,"CCZone");
 tolua_usertype(tolua_S,"CCRGBAProtocol");
 tolua_usertype(tolua_S,"RoleEquipDataHandler");
 tolua_usertype(tolua_S,"CProgressTimer");
 tolua_usertype(tolua_S,"AutoDelayAnimation");
 tolua_usertype(tolua_S,"DTEquipBoardDelegate");
 tolua_usertype(tolua_S,"ArtFontLabelBatchNode");
 tolua_usertype(tolua_S,"CCFiniteTimeAction");
 tolua_usertype(tolua_S,"CProgressInnerBar");
 tolua_usertype(tolua_S,"EquipTemplate");
 tolua_usertype(tolua_S,"CCNode");
 tolua_usertype(tolua_S,"Attribute");
 tolua_usertype(tolua_S,"UIViewData");
 tolua_usertype(tolua_S,"GLubyte");
 tolua_usertype(tolua_S,"CTableView");
 tolua_usertype(tolua_S,"PreCCMoveTo");
 tolua_usertype(tolua_S,"std::vector<std::string>");
 tolua_usertype(tolua_S,"ccColor3B");
 tolua_usertype(tolua_S,"PCallBackVec");
 tolua_usertype(tolua_S,"IString");
 tolua_usertype(tolua_S,"CCTableView");
 tolua_usertype(tolua_S,"CTouchSprite");
 tolua_usertype(tolua_S,"ObjectTemplate");
 tolua_usertype(tolua_S,"CCMenuItemSprite");
 tolua_usertype(tolua_S,"PCallBack_Node");
 tolua_usertype(tolua_S,"CProgressTimerDelegate");
 tolua_usertype(tolua_S,"PlayerStatus");
 tolua_usertype(tolua_S,"AutoDelayProtocol");
 tolua_usertype(tolua_S,"CImmovableMenu");
 tolua_usertype(tolua_S,"IByte");
 tolua_usertype(tolua_S,"SingleTouchProtocol");
 tolua_usertype(tolua_S,"std::vector<BagEquipData*>");
 tolua_usertype(tolua_S,"std::map<int,RoleEquipData*>");
 tolua_usertype(tolua_S,"CSpriteInSprite");
 tolua_usertype(tolua_S,"CSimpleActionSprite");
 tolua_usertype(tolua_S,"RoleEquipData");
 tolua_usertype(tolua_S,"DTEquipBoard");
 tolua_usertype(tolua_S,"cobra_win::Singleton2<BagEquipDataHandler>");
 tolua_usertype(tolua_S,"AnimationEffectCallBackProtocol");
 tolua_usertype(tolua_S,"CCPoint");
 tolua_usertype(tolua_S,"std::vector<int>");
 tolua_usertype(tolua_S,"CCLayer");
 tolua_usertype(tolua_S,"CCornerNumIcon");
 tolua_usertype(tolua_S,"IBagData");
 tolua_usertype(tolua_S,"CTabImmovableMenu");
 tolua_usertype(tolua_S,"GLfloat");
 tolua_usertype(tolua_S,"CMenuItemSprite");
 tolua_usertype(tolua_S,"BagEquipData");
 tolua_usertype(tolua_S,"BagTemplateBase");
 tolua_usertype(tolua_S,"IDataHandler");
 tolua_usertype(tolua_S,"CCScrollView");
 tolua_usertype(tolua_S,"ccColor4B");
 tolua_usertype(tolua_S,"CCProgressTimer");
 tolua_usertype(tolua_S,"CTeamIconProgress");
 tolua_usertype(tolua_S,"cobra_win::Singleton2<RoleInfoDataHandler>");
 tolua_usertype(tolua_S,"UShort");
 tolua_usertype(tolua_S,"DTRoleStatusBar");
 tolua_usertype(tolua_S,"CCEvent");
 tolua_usertype(tolua_S,"IData");
 tolua_usertype(tolua_S,"CTimeLabel");
 tolua_usertype(tolua_S,"ScaleSprite");
 tolua_usertype(tolua_S,"CCGrapSprite");
 tolua_usertype(tolua_S,"CMapScrollView");
 tolua_usertype(tolua_S,"CCTableViewCell");
 tolua_usertype(tolua_S,"CTimerEventProtocol");
 tolua_usertype(tolua_S,"CCTableViewDataSource");
 tolua_usertype(tolua_S,"CCRectClipNode");
 
 tolua_usertype(tolua_S,"CCObject");
 tolua_usertype(tolua_S,"CPriorityMenu");
 tolua_usertype(tolua_S,"DTRoleStatusBarDelegate");
 tolua_usertype(tolua_S,"FrameAnimationNode");
 tolua_usertype(tolua_S,"DTHeroIcon");
 tolua_usertype(tolua_S,"CPriorityLayerColorDelegate");
 tolua_usertype(tolua_S,"TableViewSourceDelegate");
 tolua_usertype(tolua_S,"CCMenuItem");
 tolua_usertype(tolua_S,"IWindow");
 tolua_usertype(tolua_S,"AutoFadeOutLabelManager");
 tolua_usertype(tolua_S,"CallFunctionProtocol");
 tolua_usertype(tolua_S,"BaseHelper");
 tolua_usertype(tolua_S,"CCSkeletonAnimation");
 tolua_usertype(tolua_S,"CCSize");
 tolua_usertype(tolua_S,"DBHelper");
 tolua_usertype(tolua_S,"SEL_MenuHandler");
 tolua_usertype(tolua_S,"VariableSpeedSequenceAction");
 tolua_usertype(tolua_S,"ErrorTipsData");
 tolua_usertype(tolua_S,"cobra_win::DPacket");
 tolua_usertype(tolua_S,"CTouchSpriteDelegate");
 tolua_usertype(tolua_S,"CCLabelTTF");
 tolua_usertype(tolua_S,"PreCCMoveBy");
 tolua_usertype(tolua_S,"CCActionInterval");
 tolua_usertype(tolua_S,"CCDragLayerProtocol");
 tolua_usertype(tolua_S,"std::list<std::string>");
 tolua_usertype(tolua_S,"CCTableViewDelegate");
 tolua_usertype(tolua_S,"SignSpriteType");
 tolua_usertype(tolua_S,"PacketHelper");
 tolua_usertype(tolua_S,"GrapStarsProgress");
 tolua_usertype(tolua_S,"CDragSprite");
 tolua_usertype(tolua_S,"LuaSystem");
 tolua_usertype(tolua_S,"luaUIHelper");
 tolua_usertype(tolua_S,"CAnimationSprite");
 tolua_usertype(tolua_S,"CTabMenu");
 tolua_usertype(tolua_S,"CLabelButtonItem");
}

/* method: LuaGetInstance of class  luaUIHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_luaUIHelper_LuaGetInstance00
static int tolua_Dota_luaUIHelper_LuaGetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"luaUIHelper",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   BaseHelper* tolua_ret = (BaseHelper*)  luaUIHelper::LuaGetInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BaseHelper");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaGetInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaGetInstanceName of class  luaUIHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_luaUIHelper_LuaGetInstanceName00
static int tolua_Dota_luaUIHelper_LuaGetInstanceName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"luaUIHelper",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::string tolua_ret = (std::string)  luaUIHelper::LuaGetInstanceName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaGetInstanceName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaGetUILayer of class  luaUIHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_luaUIHelper_LuaGetUILayer00
static int tolua_Dota_luaUIHelper_LuaGetUILayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"luaUIHelper",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  luaUIHelper* self = (luaUIHelper*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaGetUILayer'", NULL);
#endif
  {
   CCLayer* tolua_ret = (CCLayer*)  self->LuaGetUILayer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCLayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaGetUILayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaGetProvideNode of class  luaUIHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_luaUIHelper_LuaGetProvideNode00
static int tolua_Dota_luaUIHelper_LuaGetProvideNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"luaUIHelper",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  luaUIHelper* self = (luaUIHelper*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaGetProvideNode'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->LuaGetProvideNode();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaGetProvideNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaAutoCreateNodeByTable of class  luaUIHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_luaUIHelper_LuaAutoCreateNodeByTable00
static int tolua_Dota_luaUIHelper_LuaAutoCreateNodeByTable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"luaUIHelper",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  luaUIHelper* self = (luaUIHelper*)  tolua_tousertype(tolua_S,1,0);
  int key = ((int)  tolua_tonumber(tolua_S,2,0));
  CCNode* parentNode = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaAutoCreateNodeByTable'", NULL);
#endif
  {
   self->LuaAutoCreateNodeByTable(key,parentNode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaAutoCreateNodeByTable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaRegisterViewFile of class  luaUIHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_luaUIHelper_LuaRegisterViewFile00
static int tolua_Dota_luaUIHelper_LuaRegisterViewFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"luaUIHelper",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  luaUIHelper* self = (luaUIHelper*)  tolua_tousertype(tolua_S,1,0);
  int idx = ((int)  tolua_tonumber(tolua_S,2,0));
  std::string filename = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  std::string Encyfilename = ((std::string)  tolua_tocppstring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaRegisterViewFile'", NULL);
#endif
  {
   self->LuaRegisterViewFile(idx,filename,Encyfilename);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaRegisterViewFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaForceClearAnimationCache of class  luaUIHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_luaUIHelper_LuaForceClearAnimationCache00
static int tolua_Dota_luaUIHelper_LuaForceClearAnimationCache00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"luaUIHelper",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  luaUIHelper* self = (luaUIHelper*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaForceClearAnimationCache'", NULL);
#endif
  {
   self->LuaForceClearAnimationCache();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaForceClearAnimationCache'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaGetInstance of class  LuaSystem */
#ifndef TOLUA_DISABLE_tolua_Dota_LuaSystem_LuaGetInstance00
static int tolua_Dota_LuaSystem_LuaGetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   LuaSystem* tolua_ret = (LuaSystem*)  LuaSystem::LuaGetInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LuaSystem");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaGetInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaGetInstanceName of class  LuaSystem */
#ifndef TOLUA_DISABLE_tolua_Dota_LuaSystem_LuaGetInstanceName00
static int tolua_Dota_LuaSystem_LuaGetInstanceName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"LuaSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::string tolua_ret = (std::string)  LuaSystem::LuaGetInstanceName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaGetInstanceName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaRegisterInitScript of class  LuaSystem */
#ifndef TOLUA_DISABLE_tolua_Dota_LuaSystem_LuaRegisterInitScript00
static int tolua_Dota_LuaSystem_LuaRegisterInitScript00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaSystem",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LuaSystem* self = (LuaSystem*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION nHandler = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaRegisterInitScript'", NULL);
#endif
  {
   self->LuaRegisterInitScript(nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaRegisterInitScript'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaRegisterTickScript of class  LuaSystem */
#ifndef TOLUA_DISABLE_tolua_Dota_LuaSystem_LuaRegisterTickScript00
static int tolua_Dota_LuaSystem_LuaRegisterTickScript00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaSystem",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LuaSystem* self = (LuaSystem*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION nHandler = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaRegisterTickScript'", NULL);
#endif
  {
   self->LuaRegisterTickScript(nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaRegisterTickScript'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaRegisterDestroyScript of class  LuaSystem */
#ifndef TOLUA_DISABLE_tolua_Dota_LuaSystem_LuaRegisterDestroyScript00
static int tolua_Dota_LuaSystem_LuaRegisterDestroyScript00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaSystem",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LuaSystem* self = (LuaSystem*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION nHandler = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaRegisterDestroyScript'", NULL);
#endif
  {
   self->LuaRegisterDestroyScript(nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaRegisterDestroyScript'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaRegisterOnEventHandlerScript of class  LuaSystem */
#ifndef TOLUA_DISABLE_tolua_Dota_LuaSystem_LuaRegisterOnEventHandlerScript00
static int tolua_Dota_LuaSystem_LuaRegisterOnEventHandlerScript00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaSystem",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LuaSystem* self = (LuaSystem*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION nHandler = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaRegisterOnEventHandlerScript'", NULL);
#endif
  {
   self->LuaRegisterOnEventHandlerScript(nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaRegisterOnEventHandlerScript'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaRegisterOnPacketHandlerScript of class  LuaSystem */
#ifndef TOLUA_DISABLE_tolua_Dota_LuaSystem_LuaRegisterOnPacketHandlerScript00
static int tolua_Dota_LuaSystem_LuaRegisterOnPacketHandlerScript00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LuaSystem",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LuaSystem* self = (LuaSystem*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION nHandler = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaRegisterOnPacketHandlerScript'", NULL);
#endif
  {
   self->LuaRegisterOnPacketHandlerScript(nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaRegisterOnPacketHandlerScript'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaGetInstance of class  EventHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_EventHelper_LuaGetInstance00
static int tolua_Dota_EventHelper_LuaGetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EventHelper",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   BaseHelper* tolua_ret = (BaseHelper*)  EventHelper::LuaGetInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BaseHelper");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaGetInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaGetInstanceName of class  EventHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_EventHelper_LuaGetInstanceName00
static int tolua_Dota_EventHelper_LuaGetInstanceName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EventHelper",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::string tolua_ret = (std::string)  EventHelper::LuaGetInstanceName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaGetInstanceName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaRegisterEvent of class  EventHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_EventHelper_LuaRegisterEvent00
static int tolua_Dota_EventHelper_LuaRegisterEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EventHelper",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EventHelper* self = (EventHelper*)  tolua_tousertype(tolua_S,1,0);
  int eventId = ((int)  tolua_tonumber(tolua_S,2,0));
  std::string ownerData = ((std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaRegisterEvent'", NULL);
#endif
  {
   self->LuaRegisterEvent(eventId,ownerData);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaRegisterEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaPushEvent of class  EventHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_EventHelper_LuaPushEvent00
static int tolua_Dota_EventHelper_LuaPushEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EventHelper",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EventHelper* self = (EventHelper*)  tolua_tousertype(tolua_S,1,0);
  int eventId = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaPushEvent'", NULL);
#endif
  {
   self->LuaPushEvent(eventId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaPushEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaPushEvent of class  EventHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_EventHelper_LuaPushEvent01
static int tolua_Dota_EventHelper_LuaPushEvent01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EventHelper",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  EventHelper* self = (EventHelper*)  tolua_tousertype(tolua_S,1,0);
  int eventId = ((int)  tolua_tonumber(tolua_S,2,0));
  std::string param0 = ((std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaPushEvent'", NULL);
#endif
  {
   self->LuaPushEvent(eventId,param0);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Dota_EventHelper_LuaPushEvent00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaPushEvent of class  EventHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_EventHelper_LuaPushEvent02
static int tolua_Dota_EventHelper_LuaPushEvent02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EventHelper",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  EventHelper* self = (EventHelper*)  tolua_tousertype(tolua_S,1,0);
  int eventId = ((int)  tolua_tonumber(tolua_S,2,0));
  std::string param0 = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  std::string param1 = ((std::string)  tolua_tocppstring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaPushEvent'", NULL);
#endif
  {
   self->LuaPushEvent(eventId,param0,param1);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Dota_EventHelper_LuaPushEvent01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaPushEvent of class  EventHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_EventHelper_LuaPushEvent03
static int tolua_Dota_EventHelper_LuaPushEvent03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EventHelper",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  EventHelper* self = (EventHelper*)  tolua_tousertype(tolua_S,1,0);
  int eventId = ((int)  tolua_tonumber(tolua_S,2,0));
  std::string param0 = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  std::string param1 = ((std::string)  tolua_tocppstring(tolua_S,4,0));
  std::string param2 = ((std::string)  tolua_tocppstring(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaPushEvent'", NULL);
#endif
  {
   self->LuaPushEvent(eventId,param0,param1,param2);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Dota_EventHelper_LuaPushEvent02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaPushEvent2 of class  EventHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_EventHelper_LuaPushEvent200
static int tolua_Dota_EventHelper_LuaPushEvent200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EventHelper",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EventHelper* self = (EventHelper*)  tolua_tousertype(tolua_S,1,0);
  int eventId = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaPushEvent2'", NULL);
#endif
  {
   self->LuaPushEvent2(eventId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaPushEvent2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaPushEvent2 of class  EventHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_EventHelper_LuaPushEvent201
static int tolua_Dota_EventHelper_LuaPushEvent201(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EventHelper",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  EventHelper* self = (EventHelper*)  tolua_tousertype(tolua_S,1,0);
  int eventId = ((int)  tolua_tonumber(tolua_S,2,0));
  std::string param0 = ((std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaPushEvent2'", NULL);
#endif
  {
   self->LuaPushEvent2(eventId,param0);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Dota_EventHelper_LuaPushEvent200(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaPushEvent2 of class  EventHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_EventHelper_LuaPushEvent202
static int tolua_Dota_EventHelper_LuaPushEvent202(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EventHelper",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  EventHelper* self = (EventHelper*)  tolua_tousertype(tolua_S,1,0);
  int eventId = ((int)  tolua_tonumber(tolua_S,2,0));
  std::string param0 = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  std::string param1 = ((std::string)  tolua_tocppstring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaPushEvent2'", NULL);
#endif
  {
   self->LuaPushEvent2(eventId,param0,param1);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Dota_EventHelper_LuaPushEvent201(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaPushEvent2 of class  EventHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_EventHelper_LuaPushEvent203
static int tolua_Dota_EventHelper_LuaPushEvent203(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EventHelper",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  EventHelper* self = (EventHelper*)  tolua_tousertype(tolua_S,1,0);
  int eventId = ((int)  tolua_tonumber(tolua_S,2,0));
  std::string param0 = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  std::string param1 = ((std::string)  tolua_tocppstring(tolua_S,4,0));
  std::string param2 = ((std::string)  tolua_tocppstring(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaPushEvent2'", NULL);
#endif
  {
   self->LuaPushEvent2(eventId,param0,param1,param2);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Dota_EventHelper_LuaPushEvent202(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaGetInstance of class  PacketHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_PacketHelper_LuaGetInstance00
static int tolua_Dota_PacketHelper_LuaGetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PacketHelper",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   BaseHelper* tolua_ret = (BaseHelper*)  PacketHelper::LuaGetInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BaseHelper");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaGetInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaGetInstanceName of class  PacketHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_PacketHelper_LuaGetInstanceName00
static int tolua_Dota_PacketHelper_LuaGetInstanceName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PacketHelper",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::string tolua_ret = (std::string)  PacketHelper::LuaGetInstanceName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaGetInstanceName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaRegisterPacket of class  PacketHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_PacketHelper_LuaRegisterPacket00
static int tolua_Dota_PacketHelper_LuaRegisterPacket00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PacketHelper",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PacketHelper* self = (PacketHelper*)  tolua_tousertype(tolua_S,1,0);
  int packetType = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaRegisterPacket'", NULL);
#endif
  {
   self->LuaRegisterPacket(packetType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaRegisterPacket'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaBuildPacket of class  PacketHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_PacketHelper_LuaBuildPacket00
static int tolua_Dota_PacketHelper_LuaBuildPacket00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PacketHelper",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PacketHelper* self = (PacketHelper*)  tolua_tousertype(tolua_S,1,0);
  int packetType = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaBuildPacket'", NULL);
#endif
  {
   self->LuaBuildPacket(packetType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaBuildPacket'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaPutByte of class  PacketHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_PacketHelper_LuaPutByte00
static int tolua_Dota_PacketHelper_LuaPutByte00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PacketHelper",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PacketHelper* self = (PacketHelper*)  tolua_tousertype(tolua_S,1,0);
  char param = ((char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaPutByte'", NULL);
#endif
  {
   self->LuaPutByte(param);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaPutByte'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaPutShort of class  PacketHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_PacketHelper_LuaPutShort00
static int tolua_Dota_PacketHelper_LuaPutShort00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PacketHelper",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PacketHelper* self = (PacketHelper*)  tolua_tousertype(tolua_S,1,0);
  short param = ((short)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaPutShort'", NULL);
#endif
  {
   self->LuaPutShort(param);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaPutShort'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaPutInt of class  PacketHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_PacketHelper_LuaPutInt00
static int tolua_Dota_PacketHelper_LuaPutInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PacketHelper",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PacketHelper* self = (PacketHelper*)  tolua_tousertype(tolua_S,1,0);
  int param = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaPutInt'", NULL);
#endif
  {
   self->LuaPutInt(param);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaPutInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaPutString of class  PacketHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_PacketHelper_LuaPutString00
static int tolua_Dota_PacketHelper_LuaPutString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PacketHelper",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PacketHelper* self = (PacketHelper*)  tolua_tousertype(tolua_S,1,0);
  std::string param = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaPutString'", NULL);
#endif
  {
   self->LuaPutString(param);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaPutString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaSendPacket of class  PacketHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_PacketHelper_LuaSendPacket00
static int tolua_Dota_PacketHelper_LuaSendPacket00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PacketHelper",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PacketHelper* self = (PacketHelper*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaSendPacket'", NULL);
#endif
  {
   self->LuaSendPacket();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaSendPacket'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaReadPn of class  PacketHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_PacketHelper_LuaReadPn00
static int tolua_Dota_PacketHelper_LuaReadPn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PacketHelper",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PacketHelper* self = (PacketHelper*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaReadPn'", NULL);
#endif
  {
   int tolua_ret = (int)  self->LuaReadPn();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaReadPn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaReadShort of class  PacketHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_PacketHelper_LuaReadShort00
static int tolua_Dota_PacketHelper_LuaReadShort00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PacketHelper",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PacketHelper* self = (PacketHelper*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaReadShort'", NULL);
#endif
  {
   short tolua_ret = (short)  self->LuaReadShort();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaReadShort'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaReadByte of class  PacketHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_PacketHelper_LuaReadByte00
static int tolua_Dota_PacketHelper_LuaReadByte00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PacketHelper",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PacketHelper* self = (PacketHelper*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaReadByte'", NULL);
#endif
  {
   char tolua_ret = (char)  self->LuaReadByte();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaReadByte'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaReadInt of class  PacketHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_PacketHelper_LuaReadInt00
static int tolua_Dota_PacketHelper_LuaReadInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PacketHelper",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PacketHelper* self = (PacketHelper*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaReadInt'", NULL);
#endif
  {
   int tolua_ret = (int)  self->LuaReadInt();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaReadInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaReadString of class  PacketHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_PacketHelper_LuaReadString00
static int tolua_Dota_PacketHelper_LuaReadString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PacketHelper",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PacketHelper* self = (PacketHelper*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaReadString'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->LuaReadString();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaReadString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaGetInstance of class  DBHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_DBHelper_LuaGetInstance00
static int tolua_Dota_DBHelper_LuaGetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DBHelper",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   BaseHelper* tolua_ret = (BaseHelper*)  DBHelper::LuaGetInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BaseHelper");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaGetInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaGetInstanceName of class  DBHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_DBHelper_LuaGetInstanceName00
static int tolua_Dota_DBHelper_LuaGetInstanceName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DBHelper",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::string tolua_ret = (std::string)  DBHelper::LuaGetInstanceName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaGetInstanceName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaGetSysLangById of class  DBHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_DBHelper_LuaGetSysLangById00
static int tolua_Dota_DBHelper_LuaGetSysLangById00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DBHelper",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DBHelper* self = (DBHelper*)  tolua_tousertype(tolua_S,1,0);
  int langId = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaGetSysLangById'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->LuaGetSysLangById(langId);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaGetSysLangById'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaGetResourcePathByID of class  DBHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_DBHelper_LuaGetResourcePathByID00
static int tolua_Dota_DBHelper_LuaGetResourcePathByID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DBHelper",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DBHelper* self = (DBHelper*)  tolua_tousertype(tolua_S,1,0);
  int idx = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaGetResourcePathByID'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->LuaGetResourcePathByID(idx);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaGetResourcePathByID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaGetRoleInfoDataHandler of class  DBHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_DBHelper_LuaGetRoleInfoDataHandler00
static int tolua_Dota_DBHelper_LuaGetRoleInfoDataHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DBHelper",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DBHelper* self = (DBHelper*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaGetRoleInfoDataHandler'", NULL);
#endif
  {
   RoleInfoDataHandler* tolua_ret = (RoleInfoDataHandler*)  self->LuaGetRoleInfoDataHandler();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"RoleInfoDataHandler");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaGetRoleInfoDataHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaShowFlowEffect of class  DBHelper */
#ifndef TOLUA_DISABLE_tolua_Dota_DBHelper_LuaShowFlowEffect00
static int tolua_Dota_DBHelper_LuaShowFlowEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DBHelper",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DBHelper* self = (DBHelper*)  tolua_tousertype(tolua_S,1,0);
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  int count = ((int)  tolua_tonumber(tolua_S,3,0));
  int bjcount = ((int)  tolua_tonumber(tolua_S,4,0));
  int itemiconid = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LuaShowFlowEffect'", NULL);
#endif
  {
   self->LuaShowFlowEffect(type,count,bjcount,itemiconid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaShowFlowEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_new00
static int tolua_Dota_CMenuItemSprite_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CMenuItemSprite* tolua_ret = (CMenuItemSprite*)  Mtolua_new((CMenuItemSprite)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMenuItemSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_new00_local
static int tolua_Dota_CMenuItemSprite_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CMenuItemSprite* tolua_ret = (CMenuItemSprite*)  Mtolua_new((CMenuItemSprite)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMenuItemSprite");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_delete00
static int tolua_Dota_CMenuItemSprite_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMenuItemSprite* self = (CMenuItemSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_create00
static int tolua_Dota_CMenuItemSprite_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CMenuItemSprite* tolua_ret = (CMenuItemSprite*)  CMenuItemSprite::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMenuItemSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_init00
static int tolua_Dota_CMenuItemSprite_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMenuItemSprite* self = (CMenuItemSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_create01
static int tolua_Dota_CMenuItemSprite_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"SEL_MenuHandler",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCNode* normalSprite = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  CCNode* selectedSprite = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
  CCObject* target = ((CCObject*)  tolua_tousertype(tolua_S,4,0));
  SEL_MenuHandler selector = *((SEL_MenuHandler*)  tolua_tousertype(tolua_S,5,0));
  {
   CMenuItemSprite* tolua_ret = (CMenuItemSprite*)  CMenuItemSprite::create(normalSprite,selectedSprite,target,selector);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMenuItemSprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Dota_CMenuItemSprite_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithNormalSprite of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_initWithNormalSprite00
static int tolua_Dota_CMenuItemSprite_initWithNormalSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"CCObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,6,&tolua_err) || !tolua_isusertype(tolua_S,6,"SEL_MenuHandler",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMenuItemSprite* self = (CMenuItemSprite*)  tolua_tousertype(tolua_S,1,0);
  CCNode* normalSprite = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  CCNode* selectedSprite = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
  CCNode* disabledSprite = ((CCNode*)  tolua_tousertype(tolua_S,4,0));
  CCObject* target = ((CCObject*)  tolua_tousertype(tolua_S,5,0));
  SEL_MenuHandler selector = *((SEL_MenuHandler*)  tolua_tousertype(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithNormalSprite'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithNormalSprite(normalSprite,selectedSprite,disabledSprite,target,selector);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithNormalSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_create02
static int tolua_Dota_CMenuItemSprite_create02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"SEL_MenuHandler",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* nor = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* sel = ((const char*)  tolua_tostring(tolua_S,3,0));
  CCObject* target = ((CCObject*)  tolua_tousertype(tolua_S,4,0));
  SEL_MenuHandler selector = *((SEL_MenuHandler*)  tolua_tousertype(tolua_S,5,0));
  {
   CMenuItemSprite* tolua_ret = (CMenuItemSprite*)  CMenuItemSprite::create(nor,sel,target,selector);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMenuItemSprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Dota_CMenuItemSprite_create01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithNormalImage of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_initWithNormalImage00
static int tolua_Dota_CMenuItemSprite_initWithNormalImage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"SEL_MenuHandler",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMenuItemSprite* self = (CMenuItemSprite*)  tolua_tousertype(tolua_S,1,0);
  const char* nor = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* sel = ((const char*)  tolua_tostring(tolua_S,3,0));
  CCObject* target = ((CCObject*)  tolua_tousertype(tolua_S,4,0));
  SEL_MenuHandler selector = *((SEL_MenuHandler*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithNormalImage'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithNormalImage(nor,sel,target,selector);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithNormalImage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_create03
static int tolua_Dota_CMenuItemSprite_create03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"SEL_MenuHandler",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* nor = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCObject* target = ((CCObject*)  tolua_tousertype(tolua_S,3,0));
  SEL_MenuHandler selector = *((SEL_MenuHandler*)  tolua_tousertype(tolua_S,4,0));
  {
   CMenuItemSprite* tolua_ret = (CMenuItemSprite*)  CMenuItemSprite::create(nor,target,selector);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMenuItemSprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Dota_CMenuItemSprite_create02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithNormalImage of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_initWithNormalImage01
static int tolua_Dota_CMenuItemSprite_initWithNormalImage01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"SEL_MenuHandler",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CMenuItemSprite* self = (CMenuItemSprite*)  tolua_tousertype(tolua_S,1,0);
  const char* nor = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCObject* target = ((CCObject*)  tolua_tousertype(tolua_S,3,0));
  SEL_MenuHandler selector = *((SEL_MenuHandler*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithNormalImage'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithNormalImage(nor,target,selector);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Dota_CMenuItemSprite_initWithNormalImage00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithCompositeSelectedImage of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_createWithCompositeSelectedImage00
static int tolua_Dota_CMenuItemSprite_createWithCompositeSelectedImage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* selImage = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* norImage = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   CMenuItemSprite* tolua_ret = (CMenuItemSprite*)  CMenuItemSprite::createWithCompositeSelectedImage(selImage,norImage);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMenuItemSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createWithCompositeSelectedImage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithCompositeSelectedImage of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_initWithCompositeSelectedImage00
static int tolua_Dota_CMenuItemSprite_initWithCompositeSelectedImage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMenuItemSprite* self = (CMenuItemSprite*)  tolua_tousertype(tolua_S,1,0);
  const char* selImage = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* norImage = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithCompositeSelectedImage'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithCompositeSelectedImage(selImage,norImage);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithCompositeSelectedImage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSelectedType of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_setSelectedType00
static int tolua_Dota_CMenuItemSprite_setSelectedType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMenuItemSprite* self = (CMenuItemSprite*)  tolua_tousertype(tolua_S,1,0);
  unsigned int type = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSelectedType'", NULL);
#endif
  {
   self->setSelectedType(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSelectedType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIDX of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_setIDX00
static int tolua_Dota_CMenuItemSprite_setIDX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMenuItemSprite* self = (CMenuItemSprite*)  tolua_tousertype(tolua_S,1,0);
  unsigned int idx = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIDX'", NULL);
#endif
  {
   self->setIDX(idx);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIDX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIDX of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_getIDX00
static int tolua_Dota_CMenuItemSprite_getIDX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMenuItemSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMenuItemSprite* self = (const CMenuItemSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIDX'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->getIDX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIDX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIsSelected of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_setIsSelected00
static int tolua_Dota_CMenuItemSprite_setIsSelected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMenuItemSprite* self = (CMenuItemSprite*)  tolua_tousertype(tolua_S,1,0);
  bool sel = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIsSelected'", NULL);
#endif
  {
   self->setIsSelected(sel);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIsSelected'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIsSeleted of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_getIsSeleted00
static int tolua_Dota_CMenuItemSprite_getIsSeleted00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMenuItemSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMenuItemSprite* self = (const CMenuItemSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIsSeleted'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getIsSeleted();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIsSeleted'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSoundID of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_setSoundID00
static int tolua_Dota_CMenuItemSprite_setSoundID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMenuItemSprite* self = (CMenuItemSprite*)  tolua_tousertype(tolua_S,1,0);
  int soundid = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSoundID'", NULL);
#endif
  {
   self->setSoundID(soundid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSoundID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAttachData1 of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_setAttachData100
static int tolua_Dota_CMenuItemSprite_setAttachData100(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMenuItemSprite* self = (CMenuItemSprite*)  tolua_tousertype(tolua_S,1,0);
  int attachData = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAttachData1'", NULL);
#endif
  {
   self->setAttachData1(attachData);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAttachData1'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAttachData1 of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_getAttachData100
static int tolua_Dota_CMenuItemSprite_getAttachData100(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMenuItemSprite* self = (CMenuItemSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAttachData1'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getAttachData1();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAttachData1'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAttachData2 of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_setAttachData200
static int tolua_Dota_CMenuItemSprite_setAttachData200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMenuItemSprite* self = (CMenuItemSprite*)  tolua_tousertype(tolua_S,1,0);
  int attachData = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAttachData2'", NULL);
#endif
  {
   self->setAttachData2(attachData);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAttachData2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAttachData2 of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_getAttachData200
static int tolua_Dota_CMenuItemSprite_getAttachData200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMenuItemSprite* self = (CMenuItemSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAttachData2'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getAttachData2();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAttachData2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setNormalImageAndRelocation of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_setNormalImageAndRelocation00
static int tolua_Dota_CMenuItemSprite_setNormalImageAndRelocation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMenuItemSprite* self = (CMenuItemSprite*)  tolua_tousertype(tolua_S,1,0);
  CCNode* nor = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setNormalImageAndRelocation'", NULL);
#endif
  {
   self->setNormalImageAndRelocation(nor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setNormalImageAndRelocation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PlaySound of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_PlaySound00
static int tolua_Dota_CMenuItemSprite_PlaySound00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMenuItemSprite* self = (CMenuItemSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PlaySound'", NULL);
#endif
  {
   self->PlaySound();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PlaySound'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Selected_Event of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_Selected_Event00
static int tolua_Dota_CMenuItemSprite_Selected_Event00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMenuItemSprite* self = (CMenuItemSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Selected_Event'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Selected_Event();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Selected_Event'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UnSelected_Event of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_UnSelected_Event00
static int tolua_Dota_CMenuItemSprite_UnSelected_Event00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMenuItemSprite* self = (CMenuItemSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UnSelected_Event'", NULL);
#endif
  {
   self->UnSelected_Event();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UnSelected_Event'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UnSelected_Event_Active of class  CMenuItemSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CMenuItemSprite_UnSelected_Event_Active00
static int tolua_Dota_CMenuItemSprite_UnSelected_Event_Active00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMenuItemSprite* self = (CMenuItemSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UnSelected_Event_Active'", NULL);
#endif
  {
   self->UnSelected_Event_Active();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UnSelected_Event_Active'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CLabelButtonItem */
#ifndef TOLUA_DISABLE_tolua_Dota_CLabelButtonItem_new00
static int tolua_Dota_CLabelButtonItem_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CLabelButtonItem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CLabelButtonItem* tolua_ret = (CLabelButtonItem*)  Mtolua_new((CLabelButtonItem)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CLabelButtonItem");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CLabelButtonItem */
#ifndef TOLUA_DISABLE_tolua_Dota_CLabelButtonItem_new00_local
static int tolua_Dota_CLabelButtonItem_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CLabelButtonItem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CLabelButtonItem* tolua_ret = (CLabelButtonItem*)  Mtolua_new((CLabelButtonItem)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CLabelButtonItem");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CLabelButtonItem */
#ifndef TOLUA_DISABLE_tolua_Dota_CLabelButtonItem_delete00
static int tolua_Dota_CLabelButtonItem_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CLabelButtonItem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CLabelButtonItem* self = (CLabelButtonItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CLabelButtonItem */
#ifndef TOLUA_DISABLE_tolua_Dota_CLabelButtonItem_create00
static int tolua_Dota_CLabelButtonItem_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CLabelButtonItem",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCLabelTTF",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* normalSprite = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  CCNode* selectedSprite = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
  CCLabelTTF* lb = ((CCLabelTTF*)  tolua_tousertype(tolua_S,4,0));
  {
   CLabelButtonItem* tolua_ret = (CLabelButtonItem*)  CLabelButtonItem::create(normalSprite,selectedSprite,lb);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CLabelButtonItem");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CLabelButtonItem */
#ifndef TOLUA_DISABLE_tolua_Dota_CLabelButtonItem_init00
static int tolua_Dota_CLabelButtonItem_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CLabelButtonItem",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCLabelTTF",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CLabelButtonItem* self = (CLabelButtonItem*)  tolua_tousertype(tolua_S,1,0);
  CCNode* normalSprite = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  CCNode* selectedSprite = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
  CCLabelTTF* lb = ((CCLabelTTF*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(normalSprite,selectedSprite,lb);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLabelString of class  CLabelButtonItem */
#ifndef TOLUA_DISABLE_tolua_Dota_CLabelButtonItem_GetLabelString00
static int tolua_Dota_CLabelButtonItem_GetLabelString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CLabelButtonItem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CLabelButtonItem* self = (CLabelButtonItem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLabelString'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->GetLabelString();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLabelString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLabelString of class  CLabelButtonItem */
#ifndef TOLUA_DISABLE_tolua_Dota_CLabelButtonItem_SetLabelString00
static int tolua_Dota_CLabelButtonItem_SetLabelString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CLabelButtonItem",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CLabelButtonItem* self = (CLabelButtonItem*)  tolua_tousertype(tolua_S,1,0);
  const char* txt = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLabelString'", NULL);
#endif
  {
   self->SetLabelString(txt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLabelString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CPriorityMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_CPriorityMenu_create00
static int tolua_Dota_CPriorityMenu_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CPriorityMenu",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int priority = ((int)  tolua_tonumber(tolua_S,2,0));
  bool swallow = ((bool)  tolua_toboolean(tolua_S,3,true));
  {
   CPriorityMenu* tolua_ret = (CPriorityMenu*)  CPriorityMenu::create(priority,swallow);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CPriorityMenu");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CPriorityMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_CPriorityMenu_init00
static int tolua_Dota_CPriorityMenu_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CPriorityMenu",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CPriorityMenu* self = (CPriorityMenu*)  tolua_tousertype(tolua_S,1,0);
  int priority = ((int)  tolua_tonumber(tolua_S,2,0));
  bool swallow = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(priority,swallow);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerWithTouchDispatcher of class  CPriorityMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_CPriorityMenu_registerWithTouchDispatcher00
static int tolua_Dota_CPriorityMenu_registerWithTouchDispatcher00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CPriorityMenu",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CPriorityMenu* self = (CPriorityMenu*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerWithTouchDispatcher'", NULL);
#endif
  {
   self->registerWithTouchDispatcher();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerWithTouchDispatcher'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchBegan of class  CPriorityMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_CPriorityMenu_ccTouchBegan00
static int tolua_Dota_CPriorityMenu_ccTouchBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CPriorityMenu",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CPriorityMenu* self = (CPriorityMenu*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* event = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchBegan'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ccTouchBegan(touch,event);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchBegan'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchEnded of class  CPriorityMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_CPriorityMenu_ccTouchEnded00
static int tolua_Dota_CPriorityMenu_ccTouchEnded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CPriorityMenu",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CPriorityMenu* self = (CPriorityMenu*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* event = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchEnded'", NULL);
#endif
  {
   self->ccTouchEnded(touch,event);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchEnded'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchMoved of class  CPriorityMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_CPriorityMenu_ccTouchMoved00
static int tolua_Dota_CPriorityMenu_ccTouchMoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CPriorityMenu",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CPriorityMenu* self = (CPriorityMenu*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* event = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchMoved'", NULL);
#endif
  {
   self->ccTouchMoved(touch,event);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchMoved'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchCancelled of class  CPriorityMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_CPriorityMenu_ccTouchCancelled00
static int tolua_Dota_CPriorityMenu_ccTouchCancelled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CPriorityMenu",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CPriorityMenu* self = (CPriorityMenu*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* event = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchCancelled'", NULL);
#endif
  {
   self->ccTouchCancelled(touch,event);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchCancelled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CTabMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_CTabMenu_create00
static int tolua_Dota_CTabMenu_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CTabMenu",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int priority = ((int)  tolua_tonumber(tolua_S,2,0));
  bool swallow = ((bool)  tolua_toboolean(tolua_S,3,true));
  {
   CTabMenu* tolua_ret = (CTabMenu*)  CTabMenu::create(priority,swallow);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTabMenu");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CTabMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_CTabMenu_init00
static int tolua_Dota_CTabMenu_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTabMenu",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTabMenu* self = (CTabMenu*)  tolua_tousertype(tolua_S,1,0);
  int priority = ((int)  tolua_tonumber(tolua_S,2,0));
  bool swallow = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(priority,swallow);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerWithTouchDispatcher of class  CTabMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_CTabMenu_registerWithTouchDispatcher00
static int tolua_Dota_CTabMenu_registerWithTouchDispatcher00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTabMenu",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTabMenu* self = (CTabMenu*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerWithTouchDispatcher'", NULL);
#endif
  {
   self->registerWithTouchDispatcher();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerWithTouchDispatcher'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchBegan of class  CTabMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_CTabMenu_ccTouchBegan00
static int tolua_Dota_CTabMenu_ccTouchBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTabMenu",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTabMenu* self = (CTabMenu*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* event = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchBegan'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ccTouchBegan(touch,event);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchBegan'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchEnded of class  CTabMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_CTabMenu_ccTouchEnded00
static int tolua_Dota_CTabMenu_ccTouchEnded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTabMenu",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTabMenu* self = (CTabMenu*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* event = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchEnded'", NULL);
#endif
  {
   self->ccTouchEnded(touch,event);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchEnded'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchMoved of class  CTabMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_CTabMenu_ccTouchMoved00
static int tolua_Dota_CTabMenu_ccTouchMoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTabMenu",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTabMenu* self = (CTabMenu*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* event = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchMoved'", NULL);
#endif
  {
   self->ccTouchMoved(touch,event);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchMoved'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CImmovableMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_CImmovableMenu_create00
static int tolua_Dota_CImmovableMenu_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CImmovableMenu",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int priority = ((int)  tolua_tonumber(tolua_S,2,0));
  bool swallow = ((bool)  tolua_toboolean(tolua_S,3,false));
  {
   CImmovableMenu* tolua_ret = (CImmovableMenu*)  CImmovableMenu::create(priority,swallow);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CImmovableMenu");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CImmovableMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_CImmovableMenu_init00
static int tolua_Dota_CImmovableMenu_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CImmovableMenu",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CImmovableMenu* self = (CImmovableMenu*)  tolua_tousertype(tolua_S,1,0);
  int priority = ((int)  tolua_tonumber(tolua_S,2,0));
  bool swallow = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(priority,swallow);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerWithTouchDispatcher of class  CImmovableMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_CImmovableMenu_registerWithTouchDispatcher00
static int tolua_Dota_CImmovableMenu_registerWithTouchDispatcher00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CImmovableMenu",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CImmovableMenu* self = (CImmovableMenu*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerWithTouchDispatcher'", NULL);
#endif
  {
   self->registerWithTouchDispatcher();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerWithTouchDispatcher'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchBegan of class  CImmovableMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_CImmovableMenu_ccTouchBegan00
static int tolua_Dota_CImmovableMenu_ccTouchBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CImmovableMenu",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CImmovableMenu* self = (CImmovableMenu*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* event = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchBegan'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ccTouchBegan(touch,event);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchBegan'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CTabImmovableMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_CTabImmovableMenu_create00
static int tolua_Dota_CTabImmovableMenu_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CTabImmovableMenu",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int priority = ((int)  tolua_tonumber(tolua_S,2,0));
  bool swallow = ((bool)  tolua_toboolean(tolua_S,3,false));
  {
   CTabImmovableMenu* tolua_ret = (CTabImmovableMenu*)  CTabImmovableMenu::create(priority,swallow);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTabImmovableMenu");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CTabImmovableMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_CTabImmovableMenu_init00
static int tolua_Dota_CTabImmovableMenu_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTabImmovableMenu",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTabImmovableMenu* self = (CTabImmovableMenu*)  tolua_tousertype(tolua_S,1,0);
  int priority = ((int)  tolua_tonumber(tolua_S,2,0));
  bool swallow = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(priority,swallow);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchBegan of class  CTabImmovableMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_CTabImmovableMenu_ccTouchBegan00
static int tolua_Dota_CTabImmovableMenu_ccTouchBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTabImmovableMenu",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTabImmovableMenu* self = (CTabImmovableMenu*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* event = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchBegan'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ccTouchBegan(touch,event);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchBegan'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchEnded of class  CTabImmovableMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_CTabImmovableMenu_ccTouchEnded00
static int tolua_Dota_CTabImmovableMenu_ccTouchEnded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTabImmovableMenu",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTabImmovableMenu* self = (CTabImmovableMenu*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* event = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchEnded'", NULL);
#endif
  {
   self->ccTouchEnded(touch,event);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchEnded'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchMoved of class  CTabImmovableMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_CTabImmovableMenu_ccTouchMoved00
static int tolua_Dota_CTabImmovableMenu_ccTouchMoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTabImmovableMenu",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTabImmovableMenu* self = (CTabImmovableMenu*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* event = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchMoved'", NULL);
#endif
  {
   self->ccTouchMoved(touch,event);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchMoved'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_new00
static int tolua_Dota_ArtFontLabelBatchNode_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ArtFontLabelBatchNode* tolua_ret = (ArtFontLabelBatchNode*)  Mtolua_new((ArtFontLabelBatchNode)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ArtFontLabelBatchNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_new00_local
static int tolua_Dota_ArtFontLabelBatchNode_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ArtFontLabelBatchNode* tolua_ret = (ArtFontLabelBatchNode*)  Mtolua_new((ArtFontLabelBatchNode)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ArtFontLabelBatchNode");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_delete00
static int tolua_Dota_ArtFontLabelBatchNode_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateArtFontWithArray of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_CreateArtFontWithArray00
static int tolua_Dota_ArtFontLabelBatchNode_CreateArtFontWithArray00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"std::vector<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::vector<int>* fontArray = ((std::vector<int>*)  tolua_tousertype(tolua_S,2,0));
  {
   ArtFontLabelBatchNode* tolua_ret = (ArtFontLabelBatchNode*)  ArtFontLabelBatchNode::CreateArtFontWithArray(*fontArray);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ArtFontLabelBatchNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateArtFontWithArray'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InitNumberLabelBatchNode of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_InitNumberLabelBatchNode00
static int tolua_Dota_ArtFontLabelBatchNode_InitNumberLabelBatchNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"std::vector<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
  std::vector<int>* fontArray = ((std::vector<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InitNumberLabelBatchNode'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->InitNumberLabelBatchNode(*fontArray);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InitNumberLabelBatchNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLabelWithArray of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_SetLabelWithArray00
static int tolua_Dota_ArtFontLabelBatchNode_SetLabelWithArray00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"std::vector<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
  std::vector<int>* fontArray = ((std::vector<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLabelWithArray'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetLabelWithArray(*fontArray);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLabelWithArray'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAnchorPoint of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_SetAnchorPoint00
static int tolua_Dota_ArtFontLabelBatchNode_SetAnchorPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
  CCPoint anchorPositon = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAnchorPoint'", NULL);
#endif
  {
   self->SetAnchorPoint(anchorPositon);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAnchorPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPosition of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_SetPosition00
static int tolua_Dota_ArtFontLabelBatchNode_SetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
  CCPoint position = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPosition'", NULL);
#endif
  {
   self->SetPosition(position);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetScale of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_SetScale00
static int tolua_Dota_ArtFontLabelBatchNode_SetScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
  float fscale = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetScale'", NULL);
#endif
  {
   self->SetScale(fscale);
   tolua_pushnumber(tolua_S,(lua_Number)fscale);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLabelTotalWidth of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_GetLabelTotalWidth00
static int tolua_Dota_ArtFontLabelBatchNode_GetLabelTotalWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLabelTotalWidth'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetLabelTotalWidth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLabelTotalWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAnchorPosition of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_GetAnchorPosition00
static int tolua_Dota_ArtFontLabelBatchNode_GetAnchorPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAnchorPosition'", NULL);
#endif
  {
   CCPoint tolua_ret = (CCPoint)  self->GetAnchorPosition();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAnchorPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPosition of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_GetPosition00
static int tolua_Dota_ArtFontLabelBatchNode_GetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPosition'", NULL);
#endif
  {
   CCPoint tolua_ret = (CCPoint)  self->GetPosition();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setColor of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_setColor00
static int tolua_Dota_ArtFontLabelBatchNode_setColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setColor'", NULL);
#endif
  {
   self->setColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getColor of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_getColor00
static int tolua_Dota_ArtFontLabelBatchNode_getColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getColor'", NULL);
#endif
  {
   const ccColor3B& tolua_ret = (const ccColor3B&)  self->getColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const ccColor3B");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getOpacity of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_getOpacity00
static int tolua_Dota_ArtFontLabelBatchNode_getOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getOpacity'", NULL);
#endif
  {
   GLubyte tolua_ret = (GLubyte)  self->getOpacity();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((GLubyte)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"GLubyte");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(GLubyte));
     tolua_pushusertype(tolua_S,tolua_obj,"GLubyte");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setOpacity of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_setOpacity00
static int tolua_Dota_ArtFontLabelBatchNode_setOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLubyte",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
  GLubyte opacity = *((GLubyte*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setOpacity'", NULL);
#endif
  {
   self->setOpacity(opacity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setOpacityModifyRGB of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_setOpacityModifyRGB00
static int tolua_Dota_ArtFontLabelBatchNode_setOpacityModifyRGB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
  bool bValue = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setOpacityModifyRGB'", NULL);
#endif
  {
   self->setOpacityModifyRGB(bValue);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setOpacityModifyRGB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isOpacityModifyRGB of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_isOpacityModifyRGB00
static int tolua_Dota_ArtFontLabelBatchNode_isOpacityModifyRGB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isOpacityModifyRGB'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isOpacityModifyRGB();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isOpacityModifyRGB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isCascadeColorEnabled of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_isCascadeColorEnabled00
static int tolua_Dota_ArtFontLabelBatchNode_isCascadeColorEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isCascadeColorEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isCascadeColorEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isCascadeColorEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCascadeColorEnabled of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_setCascadeColorEnabled00
static int tolua_Dota_ArtFontLabelBatchNode_setCascadeColorEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
  bool cascadeColorEnabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCascadeColorEnabled'", NULL);
#endif
  {
   self->setCascadeColorEnabled(cascadeColorEnabled);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCascadeColorEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateDisplayedColor of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_updateDisplayedColor00
static int tolua_Dota_ArtFontLabelBatchNode_updateDisplayedColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateDisplayedColor'", NULL);
#endif
  {
   self->updateDisplayedColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateDisplayedColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isCascadeOpacityEnabled of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_isCascadeOpacityEnabled00
static int tolua_Dota_ArtFontLabelBatchNode_isCascadeOpacityEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isCascadeOpacityEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isCascadeOpacityEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isCascadeOpacityEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCascadeOpacityEnabled of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_setCascadeOpacityEnabled00
static int tolua_Dota_ArtFontLabelBatchNode_setCascadeOpacityEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
  bool cascadeOpacityEnabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCascadeOpacityEnabled'", NULL);
#endif
  {
   self->setCascadeOpacityEnabled(cascadeOpacityEnabled);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCascadeOpacityEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateDisplayedOpacity of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_updateDisplayedOpacity00
static int tolua_Dota_ArtFontLabelBatchNode_updateDisplayedOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLubyte",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
  GLubyte opacity = *((GLubyte*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateDisplayedOpacity'", NULL);
#endif
  {
   self->updateDisplayedOpacity(opacity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateDisplayedOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDisplayedColor of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_getDisplayedColor00
static int tolua_Dota_ArtFontLabelBatchNode_getDisplayedColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDisplayedColor'", NULL);
#endif
  {
   const ccColor3B& tolua_ret = (const ccColor3B&)  self->getDisplayedColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const ccColor3B");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDisplayedColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDisplayedOpacity of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_getDisplayedOpacity00
static int tolua_Dota_ArtFontLabelBatchNode_getDisplayedOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDisplayedOpacity'", NULL);
#endif
  {
   GLubyte tolua_ret = (GLubyte)  self->getDisplayedOpacity();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((GLubyte)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"GLubyte");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(GLubyte));
     tolua_pushusertype(tolua_S,tolua_obj,"GLubyte");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDisplayedOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVisible of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_SetVisible00
static int tolua_Dota_ArtFontLabelBatchNode_SetVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
  bool isVisible = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVisible'", NULL);
#endif
  {
   self->SetVisible(isVisible);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVisible of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_GetVisible00
static int tolua_Dota_ArtFontLabelBatchNode_GetVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVisible'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetVisible();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBatchNodeLabel of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_GetBatchNodeLabel00
static int tolua_Dota_ArtFontLabelBatchNode_GetBatchNodeLabel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBatchNodeLabel'", NULL);
#endif
  {
   CCSprite* tolua_ret = (CCSprite*)  self->GetBatchNodeLabel();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBatchNodeLabel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Init of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_Init00
static int tolua_Dota_ArtFontLabelBatchNode_Init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Init'", NULL);
#endif
  {
   self->Init();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Destroy of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_Destroy00
static int tolua_Dota_ArtFontLabelBatchNode_Destroy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Destroy'", NULL);
#endif
  {
   self->Destroy();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Destroy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnCommandHanlder of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_Dota_ArtFontLabelBatchNode_OnCommandHanlder00
static int tolua_Dota_ArtFontLabelBatchNode_OnCommandHanlder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ArtFontLabelBatchNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
  int EventTypeID = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnCommandHanlder'", NULL);
#endif
  {
   self->OnCommandHanlder(EventTypeID);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnCommandHanlder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCRGBAProtocol__ of class  ArtFontLabelBatchNode */
#ifndef TOLUA_DISABLE_tolua_get_ArtFontLabelBatchNode___CCRGBAProtocol__
static int tolua_get_ArtFontLabelBatchNode___CCRGBAProtocol__(lua_State* tolua_S)
{
  ArtFontLabelBatchNode* self = (ArtFontLabelBatchNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCRGBAProtocol__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCRGBAProtocol*>(self), "CCRGBAProtocol");
#else
   tolua_pushusertype(tolua_S,(void*)((CCRGBAProtocol*)self), "CCRGBAProtocol");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: autoDelayEventHandler of class  AutoDelayProtocol */
#ifndef TOLUA_DISABLE_tolua_Dota_AutoDelayProtocol_autoDelayEventHandler00
static int tolua_Dota_AutoDelayProtocol_autoDelayEventHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AutoDelayProtocol",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AutoDelayProtocol* self = (AutoDelayProtocol*)  tolua_tousertype(tolua_S,1,0);
  int eventType = ((int)  tolua_tonumber(tolua_S,2,0));
  void* pSender = ((void*)  tolua_touserdata(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'autoDelayEventHandler'", NULL);
#endif
  {
   self->autoDelayEventHandler(eventType,pSender);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'autoDelayEventHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  AutoDelayAnimation */
#ifndef TOLUA_DISABLE_tolua_Dota_AutoDelayAnimation_create00
static int tolua_Dota_AutoDelayAnimation_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AutoDelayAnimation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"AutoDelayProtocol",1,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"PCallBackVec",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float d = ((float)  tolua_tonumber(tolua_S,2,0));
  AutoDelayProtocol* pDelegate = ((AutoDelayProtocol*)  tolua_tousertype(tolua_S,3,NULL));
  PCallBackVec pCallBackVec = *((PCallBackVec*)  tolua_tousertype(tolua_S,4,0));
  {
   AutoDelayAnimation* tolua_ret = (AutoDelayAnimation*)  AutoDelayAnimation::create(d,pDelegate,pCallBackVec);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AutoDelayAnimation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initDuration of class  AutoDelayAnimation */
#ifndef TOLUA_DISABLE_tolua_Dota_AutoDelayAnimation_initDuration00
static int tolua_Dota_AutoDelayAnimation_initDuration00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AutoDelayAnimation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"AutoDelayProtocol",1,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"PCallBackVec",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AutoDelayAnimation* self = (AutoDelayAnimation*)  tolua_tousertype(tolua_S,1,0);
  float d = ((float)  tolua_tonumber(tolua_S,2,0));
  AutoDelayProtocol* pDelegate = ((AutoDelayProtocol*)  tolua_tousertype(tolua_S,3,NULL));
  PCallBackVec pCallBackVec = *((PCallBackVec*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initDuration'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initDuration(d,pDelegate,pCallBackVec);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initDuration'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSpeedScale of class  AutoDelayAnimation */
#ifndef TOLUA_DISABLE_tolua_Dota_AutoDelayAnimation_setSpeedScale00
static int tolua_Dota_AutoDelayAnimation_setSpeedScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AutoDelayAnimation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AutoDelayAnimation* self = (AutoDelayAnimation*)  tolua_tousertype(tolua_S,1,0);
  float speedScale = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSpeedScale'", NULL);
#endif
  {
   self->setSpeedScale(speedScale);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSpeedScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  AutoDelayAnimation */
#ifndef TOLUA_DISABLE_tolua_Dota_AutoDelayAnimation_delete00
static int tolua_Dota_AutoDelayAnimation_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AutoDelayAnimation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AutoDelayAnimation* self = (AutoDelayAnimation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  AutoFadeOutLabelManager */
#ifndef TOLUA_DISABLE_tolua_Dota_AutoFadeOutLabelManager_new00
static int tolua_Dota_AutoFadeOutLabelManager_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AutoFadeOutLabelManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   AutoFadeOutLabelManager* tolua_ret = (AutoFadeOutLabelManager*)  Mtolua_new((AutoFadeOutLabelManager)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AutoFadeOutLabelManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  AutoFadeOutLabelManager */
#ifndef TOLUA_DISABLE_tolua_Dota_AutoFadeOutLabelManager_new00_local
static int tolua_Dota_AutoFadeOutLabelManager_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AutoFadeOutLabelManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   AutoFadeOutLabelManager* tolua_ret = (AutoFadeOutLabelManager*)  Mtolua_new((AutoFadeOutLabelManager)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AutoFadeOutLabelManager");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  AutoFadeOutLabelManager */
#ifndef TOLUA_DISABLE_tolua_Dota_AutoFadeOutLabelManager_delete00
static int tolua_Dota_AutoFadeOutLabelManager_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AutoFadeOutLabelManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AutoFadeOutLabelManager* self = (AutoFadeOutLabelManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateAutoFadeOutLabelManager of class  AutoFadeOutLabelManager */
#ifndef TOLUA_DISABLE_tolua_Dota_AutoFadeOutLabelManager_CreateAutoFadeOutLabelManager00
static int tolua_Dota_AutoFadeOutLabelManager_CreateAutoFadeOutLabelManager00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AutoFadeOutLabelManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* pParent = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int lableIndex = ((int)  tolua_tonumber(tolua_S,3,0));
  std::string message = ((std::string)  tolua_tocppstring(tolua_S,4,0));
  {
   AutoFadeOutLabelManager* tolua_ret = (AutoFadeOutLabelManager*)  AutoFadeOutLabelManager::CreateAutoFadeOutLabelManager(pParent,lableIndex,message);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AutoFadeOutLabelManager");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateAutoFadeOutLabelManager'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: autoDelayEventHandler of class  AutoFadeOutLabelManager */
#ifndef TOLUA_DISABLE_tolua_Dota_AutoFadeOutLabelManager_autoDelayEventHandler00
static int tolua_Dota_AutoFadeOutLabelManager_autoDelayEventHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AutoFadeOutLabelManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AutoFadeOutLabelManager* self = (AutoFadeOutLabelManager*)  tolua_tousertype(tolua_S,1,0);
  int eventType = ((int)  tolua_tonumber(tolua_S,2,0));
  void* pSender = ((void*)  tolua_touserdata(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'autoDelayEventHandler'", NULL);
#endif
  {
   self->autoDelayEventHandler(eventType,pSender);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'autoDelayEventHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPosition of class  AutoFadeOutLabelManager */
#ifndef TOLUA_DISABLE_tolua_Dota_AutoFadeOutLabelManager_SetPosition00
static int tolua_Dota_AutoFadeOutLabelManager_SetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AutoFadeOutLabelManager",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AutoFadeOutLabelManager* self = (AutoFadeOutLabelManager*)  tolua_tousertype(tolua_S,1,0);
  CCPoint position = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPosition'", NULL);
#endif
  {
   self->SetPosition(position);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddParent of class  AutoFadeOutLabelManager */
#ifndef TOLUA_DISABLE_tolua_Dota_AutoFadeOutLabelManager_AddParent00
static int tolua_Dota_AutoFadeOutLabelManager_AddParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AutoFadeOutLabelManager",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AutoFadeOutLabelManager* self = (AutoFadeOutLabelManager*)  tolua_tousertype(tolua_S,1,0);
  CCNode* pParent = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddParent'", NULL);
#endif
  {
   self->AddParent(pParent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Destroy of class  AutoFadeOutLabelManager */
#ifndef TOLUA_DISABLE_tolua_Dota_AutoFadeOutLabelManager_Destroy00
static int tolua_Dota_AutoFadeOutLabelManager_Destroy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AutoFadeOutLabelManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AutoFadeOutLabelManager* self = (AutoFadeOutLabelManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Destroy'", NULL);
#endif
  {
   self->Destroy();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Destroy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetIsValid of class  AutoFadeOutLabelManager */
#ifndef TOLUA_DISABLE_tolua_Dota_AutoFadeOutLabelManager_GetIsValid00
static int tolua_Dota_AutoFadeOutLabelManager_GetIsValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AutoFadeOutLabelManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AutoFadeOutLabelManager* self = (AutoFadeOutLabelManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetIsValid'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetIsValid();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetIsValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetIndex of class  AutoFadeOutLabelManager */
#ifndef TOLUA_DISABLE_tolua_Dota_AutoFadeOutLabelManager_SetIndex00
static int tolua_Dota_AutoFadeOutLabelManager_SetIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AutoFadeOutLabelManager",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AutoFadeOutLabelManager* self = (AutoFadeOutLabelManager*)  tolua_tousertype(tolua_S,1,0);
  int layoutIndex = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetIndex'", NULL);
#endif
  {
   self->SetIndex(layoutIndex);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetIndex of class  AutoFadeOutLabelManager */
#ifndef TOLUA_DISABLE_tolua_Dota_AutoFadeOutLabelManager_GetIndex00
static int tolua_Dota_AutoFadeOutLabelManager_GetIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AutoFadeOutLabelManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AutoFadeOutLabelManager* self = (AutoFadeOutLabelManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetIndex'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetIndex();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CAnimationSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CAnimationSprite_new00
static int tolua_Dota_CAnimationSprite_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CAnimationSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CAnimationSprite* tolua_ret = (CAnimationSprite*)  Mtolua_new((CAnimationSprite)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CAnimationSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CAnimationSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CAnimationSprite_new00_local
static int tolua_Dota_CAnimationSprite_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CAnimationSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CAnimationSprite* tolua_ret = (CAnimationSprite*)  Mtolua_new((CAnimationSprite)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CAnimationSprite");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CAnimationSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CAnimationSprite_delete00
static int tolua_Dota_CAnimationSprite_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CAnimationSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CAnimationSprite* self = (CAnimationSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createAnimationSpriteByID of class  CAnimationSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CAnimationSprite_createAnimationSpriteByID00
static int tolua_Dota_CAnimationSprite_createAnimationSpriteByID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CAnimationSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"AnimationEffectCallBackProtocol",1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int aniamtionID = ((int)  tolua_tonumber(tolua_S,2,0));
  bool isLoopEffect = ((bool)  tolua_toboolean(tolua_S,3,false));
  AnimationEffectCallBackProtocol* pDelegate = ((AnimationEffectCallBackProtocol*)  tolua_tousertype(tolua_S,4,NULL));
  {
   CAnimationSprite* tolua_ret = (CAnimationSprite*)  CAnimationSprite::createAnimationSpriteByID(aniamtionID,isLoopEffect,pDelegate);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CAnimationSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createAnimationSpriteByID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: EffectCallBackEventHandler of class  CAnimationSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CAnimationSprite_EffectCallBackEventHandler00
static int tolua_Dota_CAnimationSprite_EffectCallBackEventHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CAnimationSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"PCallBack_Node",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CAnimationSprite* self = (CAnimationSprite*)  tolua_tousertype(tolua_S,1,0);
  int eventType = ((int)  tolua_tonumber(tolua_S,2,0));
  CCNode* animationNode = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
  PCallBack_Node ptr = *((PCallBack_Node*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'EffectCallBackEventHandler'", NULL);
#endif
  {
   self->EffectCallBackEventHandler(eventType,animationNode,ptr);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EffectCallBackEventHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RegisterEventHandler of class  CAnimationSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CAnimationSprite_RegisterEventHandler00
static int tolua_Dota_CAnimationSprite_RegisterEventHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CAnimationSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"AnimationEffectCallBackProtocol",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CAnimationSprite* self = (CAnimationSprite*)  tolua_tousertype(tolua_S,1,0);
  AnimationEffectCallBackProtocol* pDelegate = ((AnimationEffectCallBackProtocol*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RegisterEventHandler'", NULL);
#endif
  {
   self->RegisterEventHandler(pDelegate);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RegisterEventHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PlayEffect of class  CAnimationSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CAnimationSprite_PlayEffect00
static int tolua_Dota_CAnimationSprite_PlayEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CAnimationSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CAnimationSprite* self = (CAnimationSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PlayEffect'", NULL);
#endif
  {
   self->PlayEffect();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PlayEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: StopEffect of class  CAnimationSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CAnimationSprite_StopEffect00
static int tolua_Dota_CAnimationSprite_StopEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CAnimationSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CAnimationSprite* self = (CAnimationSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StopEffect'", NULL);
#endif
  {
   self->StopEffect();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StopEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAnimationID of class  CAnimationSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CAnimationSprite_SetAnimationID00
static int tolua_Dota_CAnimationSprite_SetAnimationID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CAnimationSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CAnimationSprite* self = (CAnimationSprite*)  tolua_tousertype(tolua_S,1,0);
  int animationID = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAnimationID'", NULL);
#endif
  {
   self->SetAnimationID(animationID);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAnimationID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVisible of class  CAnimationSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CAnimationSprite_setVisible00
static int tolua_Dota_CAnimationSprite_setVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CAnimationSprite",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CAnimationSprite* self = (CAnimationSprite*)  tolua_tousertype(tolua_S,1,0);
  bool bVisible = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVisible'", NULL);
#endif
  {
   self->setVisible(bVisible);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetIsUnLoopEffect of class  CAnimationSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CAnimationSprite_SetIsUnLoopEffect00
static int tolua_Dota_CAnimationSprite_SetIsUnLoopEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CAnimationSprite",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CAnimationSprite* self = (CAnimationSprite*)  tolua_tousertype(tolua_S,1,0);
  bool loopEnable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetIsUnLoopEffect'", NULL);
#endif
  {
   self->SetIsUnLoopEffect(loopEnable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetIsUnLoopEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __AnimationEffectCallBackProtocol__ of class  CAnimationSprite */
#ifndef TOLUA_DISABLE_tolua_get_CAnimationSprite___AnimationEffectCallBackProtocol__
static int tolua_get_CAnimationSprite___AnimationEffectCallBackProtocol__(lua_State* tolua_S)
{
  CAnimationSprite* self = (CAnimationSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__AnimationEffectCallBackProtocol__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<AnimationEffectCallBackProtocol*>(self), "AnimationEffectCallBackProtocol");
#else
   tolua_pushusertype(tolua_S,(void*)((AnimationEffectCallBackProtocol*)self), "AnimationEffectCallBackProtocol");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CCardsStarProgress */
#ifndef TOLUA_DISABLE_tolua_Dota_CCardsStarProgress_new00
static int tolua_Dota_CCardsStarProgress_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCardsStarProgress",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCardsStarProgress* tolua_ret = (CCardsStarProgress*)  Mtolua_new((CCardsStarProgress)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCardsStarProgress");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCardsStarProgress */
#ifndef TOLUA_DISABLE_tolua_Dota_CCardsStarProgress_new00_local
static int tolua_Dota_CCardsStarProgress_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCardsStarProgress",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCardsStarProgress* tolua_ret = (CCardsStarProgress*)  Mtolua_new((CCardsStarProgress)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCardsStarProgress");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CCardsStarProgress */
#ifndef TOLUA_DISABLE_tolua_Dota_CCardsStarProgress_delete00
static int tolua_Dota_CCardsStarProgress_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCardsStarProgress",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCardsStarProgress* self = (CCardsStarProgress*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCardsStarProgress */
#ifndef TOLUA_DISABLE_tolua_Dota_CCardsStarProgress_create00
static int tolua_Dota_CCardsStarProgress_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCardsStarProgress",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string normalName = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  std::string advanceName = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  int maxcount = ((int)  tolua_tonumber(tolua_S,4,0));
  float space = ((float)  tolua_tonumber(tolua_S,5,0));
  {
   CCardsStarProgress* tolua_ret = (CCardsStarProgress*)  CCardsStarProgress::create(normalName,advanceName,maxcount,space);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCardsStarProgress");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CCardsStarProgress */
#ifndef TOLUA_DISABLE_tolua_Dota_CCardsStarProgress_init00
static int tolua_Dota_CCardsStarProgress_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCardsStarProgress",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCardsStarProgress* self = (CCardsStarProgress*)  tolua_tousertype(tolua_S,1,0);
  std::string normalName = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  std::string advanceName = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  int maxcount = ((int)  tolua_tonumber(tolua_S,4,0));
  float space = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(normalName,advanceName,maxcount,space);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCurcount of class  CCardsStarProgress */
#ifndef TOLUA_DISABLE_tolua_Dota_CCardsStarProgress_SetCurcount00
static int tolua_Dota_CCardsStarProgress_SetCurcount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCardsStarProgress",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCardsStarProgress* self = (CCardsStarProgress*)  tolua_tousertype(tolua_S,1,0);
  int curcount = ((int)  tolua_tonumber(tolua_S,2,0));
  int advanceCount = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCurcount'", NULL);
#endif
  {
   self->SetCurcount(curcount,advanceCount);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCurcount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delegateDragEndEventHandler of class  CCDragLayerProtocol */
#ifndef TOLUA_DISABLE_tolua_Dota_CCDragLayerProtocol_delegateDragEndEventHandler00
static int tolua_Dota_CCDragLayerProtocol_delegateDragEndEventHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragLayerProtocol",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCSignSprite",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragLayerProtocol* self = (CCDragLayerProtocol*)  tolua_tousertype(tolua_S,1,0);
  int eventType = ((int)  tolua_tonumber(tolua_S,2,0));
  CCSignSprite* pSignSprite = ((CCSignSprite*)  tolua_tousertype(tolua_S,3,0));
  CCPoint* touchPoint = ((CCPoint*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delegateDragEndEventHandler'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->delegateDragEndEventHandler(eventType,pSignSprite,*touchPoint);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delegateDragEndEventHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CCDragNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_CCDragNodeLayer_new00
static int tolua_Dota_CCDragNodeLayer_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDragNodeLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCDragNodeLayer* tolua_ret = (CCDragNodeLayer*)  Mtolua_new((CCDragNodeLayer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDragNodeLayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCDragNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_CCDragNodeLayer_new00_local
static int tolua_Dota_CCDragNodeLayer_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDragNodeLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCDragNodeLayer* tolua_ret = (CCDragNodeLayer*)  Mtolua_new((CCDragNodeLayer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDragNodeLayer");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CCDragNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_CCDragNodeLayer_delete00
static int tolua_Dota_CCDragNodeLayer_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragNodeLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragNodeLayer* self = (CCDragNodeLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createDragNodeLayer of class  CCDragNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_CCDragNodeLayer_createDragNodeLayer00
static int tolua_Dota_CCDragNodeLayer_createDragNodeLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDragNodeLayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCDragLayerProtocol",1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragLayerProtocol* pDrageDelegte = ((CCDragLayerProtocol*)  tolua_tousertype(tolua_S,2,NULL));
  {
   CCDragNodeLayer* tolua_ret = (CCDragNodeLayer*)  CCDragNodeLayer::createDragNodeLayer(pDrageDelegte);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCDragNodeLayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createDragNodeLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onEnter of class  CCDragNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_CCDragNodeLayer_onEnter00
static int tolua_Dota_CCDragNodeLayer_onEnter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragNodeLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragNodeLayer* self = (CCDragNodeLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onEnter'", NULL);
#endif
  {
   self->onEnter();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onEnter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onExit of class  CCDragNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_CCDragNodeLayer_onExit00
static int tolua_Dota_CCDragNodeLayer_onExit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragNodeLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragNodeLayer* self = (CCDragNodeLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onExit'", NULL);
#endif
  {
   self->onExit();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onExit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addSignSpriteVector of class  CCDragNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_CCDragNodeLayer_addSignSpriteVector00
static int tolua_Dota_CCDragNodeLayer_addSignSpriteVector00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragNodeLayer",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"std::vector<CCSignSprite*>",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragNodeLayer* self = (CCDragNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  std::vector<CCSignSprite*> signSpriteVec = *((std::vector<CCSignSprite*>*)  tolua_tousertype(tolua_S,2,0));
  int zOrder = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addSignSpriteVector'", NULL);
#endif
  {
   self->addSignSpriteVector(signSpriteVec,zOrder);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addSignSpriteVector'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addTargetSignSprite of class  CCDragNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_CCDragNodeLayer_addTargetSignSprite00
static int tolua_Dota_CCDragNodeLayer_addTargetSignSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragNodeLayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSignSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragNodeLayer* self = (CCDragNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  CCSignSprite* pSignSprite = ((CCSignSprite*)  tolua_tousertype(tolua_S,2,0));
  int zOrder = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addTargetSignSprite'", NULL);
#endif
  {
   self->addTargetSignSprite(pSignSprite,zOrder);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addTargetSignSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeTargetSignSpriteWithID of class  CCDragNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_CCDragNodeLayer_removeTargetSignSpriteWithID00
static int tolua_Dota_CCDragNodeLayer_removeTargetSignSpriteWithID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragNodeLayer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragNodeLayer* self = (CCDragNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  int signSpriteUniqueID = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeTargetSignSpriteWithID'", NULL);
#endif
  {
   self->removeTargetSignSpriteWithID(signSpriteUniqueID);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeTargetSignSpriteWithID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addOtherAttachSprite of class  CCDragNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_CCDragNodeLayer_addOtherAttachSprite00
static int tolua_Dota_CCDragNodeLayer_addOtherAttachSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragNodeLayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragNodeLayer* self = (CCDragNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  CCSprite* pAttachSprite = ((CCSprite*)  tolua_tousertype(tolua_S,2,0));
  int zOrder = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addOtherAttachSprite'", NULL);
#endif
  {
   self->addOtherAttachSprite(pAttachSprite,zOrder);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addOtherAttachSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addTargetAttachSprite of class  CCDragNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_CCDragNodeLayer_addTargetAttachSprite00
static int tolua_Dota_CCDragNodeLayer_addTargetAttachSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragNodeLayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragNodeLayer* self = (CCDragNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  CCSprite* pTargetAttachSprite = ((CCSprite*)  tolua_tousertype(tolua_S,2,0));
  int zOrder = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addTargetAttachSprite'", NULL);
#endif
  {
   self->addTargetAttachSprite(pTargetAttachSprite,zOrder);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addTargetAttachSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllTargetSignSprites of class  CCDragNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_CCDragNodeLayer_removeAllTargetSignSprites00
static int tolua_Dota_CCDragNodeLayer_removeAllTargetSignSprites00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragNodeLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragNodeLayer* self = (CCDragNodeLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllTargetSignSprites'", NULL);
#endif
  {
   self->removeAllTargetSignSprites();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllTargetSignSprites'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllOtherAttachSprite of class  CCDragNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_CCDragNodeLayer_removeAllOtherAttachSprite00
static int tolua_Dota_CCDragNodeLayer_removeAllOtherAttachSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragNodeLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragNodeLayer* self = (CCDragNodeLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllOtherAttachSprite'", NULL);
#endif
  {
   self->removeAllOtherAttachSprite();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllOtherAttachSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllTargetAttachSprite of class  CCDragNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_CCDragNodeLayer_removeAllTargetAttachSprite00
static int tolua_Dota_CCDragNodeLayer_removeAllTargetAttachSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragNodeLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragNodeLayer* self = (CCDragNodeLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllTargetAttachSprite'", NULL);
#endif
  {
   self->removeAllTargetAttachSprite();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllTargetAttachSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeAllData of class  CCDragNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_CCDragNodeLayer_removeAllData00
static int tolua_Dota_CCDragNodeLayer_removeAllData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragNodeLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragNodeLayer* self = (CCDragNodeLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeAllData'", NULL);
#endif
  {
   self->removeAllData();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeAllData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchBegan of class  CCDragNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_CCDragNodeLayer_ccTouchBegan00
static int tolua_Dota_CCDragNodeLayer_ccTouchBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragNodeLayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragNodeLayer* self = (CCDragNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* pTouch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchBegan'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ccTouchBegan(pTouch,pEvent);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchBegan'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchMoved of class  CCDragNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_CCDragNodeLayer_ccTouchMoved00
static int tolua_Dota_CCDragNodeLayer_ccTouchMoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragNodeLayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragNodeLayer* self = (CCDragNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* pTouch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchMoved'", NULL);
#endif
  {
   self->ccTouchMoved(pTouch,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchMoved'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchEnded of class  CCDragNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_CCDragNodeLayer_ccTouchEnded00
static int tolua_Dota_CCDragNodeLayer_ccTouchEnded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragNodeLayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragNodeLayer* self = (CCDragNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* pTouch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchEnded'", NULL);
#endif
  {
   self->ccTouchEnded(pTouch,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchEnded'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchCancelled of class  CCDragNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_CCDragNodeLayer_ccTouchCancelled00
static int tolua_Dota_CCDragNodeLayer_ccTouchCancelled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragNodeLayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragNodeLayer* self = (CCDragNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* pTouch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchCancelled'", NULL);
#endif
  {
   self->ccTouchCancelled(pTouch,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchCancelled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearAllSignTouchArray of class  CCDragNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_CCDragNodeLayer_clearAllSignTouchArray00
static int tolua_Dota_CCDragNodeLayer_clearAllSignTouchArray00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragNodeLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragNodeLayer* self = (CCDragNodeLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearAllSignTouchArray'", NULL);
#endif
  {
   self->clearAllSignTouchArray();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearAllSignTouchArray'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDragLayerTouchEnable of class  CCDragNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_CCDragNodeLayer_setDragLayerTouchEnable00
static int tolua_Dota_CCDragNodeLayer_setDragLayerTouchEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragNodeLayer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragNodeLayer* self = (CCDragNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  bool touchEnable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDragLayerTouchEnable'", NULL);
#endif
  {
   self->setDragLayerTouchEnable(touchEnable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDragLayerTouchEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDragLayerTouchPriority of class  CCDragNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_CCDragNodeLayer_setDragLayerTouchPriority00
static int tolua_Dota_CCDragNodeLayer_setDragLayerTouchPriority00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragNodeLayer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragNodeLayer* self = (CCDragNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  int touchPriority = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDragLayerTouchPriority'", NULL);
#endif
  {
   self->setDragLayerTouchPriority(touchPriority);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDragLayerTouchPriority'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDragLayerTouchEnabel of class  CCDragNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_CCDragNodeLayer_getDragLayerTouchEnabel00
static int tolua_Dota_CCDragNodeLayer_getDragLayerTouchEnabel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragNodeLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragNodeLayer* self = (CCDragNodeLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDragLayerTouchEnabel'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getDragLayerTouchEnabel();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDragLayerTouchEnabel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDefaultTargetSegmentHeight of class  CCDragNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_CCDragNodeLayer_setDefaultTargetSegmentHeight00
static int tolua_Dota_CCDragNodeLayer_setDefaultTargetSegmentHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragNodeLayer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragNodeLayer* self = (CCDragNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  float targetSegmentHeigh = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDefaultTargetSegmentHeight'", NULL);
#endif
  {
   self->setDefaultTargetSegmentHeight(targetSegmentHeigh);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDefaultTargetSegmentHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDragEventDelegate of class  CCDragNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_CCDragNodeLayer_setDragEventDelegate00
static int tolua_Dota_CCDragNodeLayer_setDragEventDelegate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDragNodeLayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCDragLayerProtocol",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDragNodeLayer* self = (CCDragNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  CCDragLayerProtocol* pDrageDelegte = ((CCDragLayerProtocol*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDragEventDelegate'", NULL);
#endif
  {
   self->setDragEventDelegate(pDrageDelegte);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDragEventDelegate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CCGrapSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CCGrapSprite_new00
static int tolua_Dota_CCGrapSprite_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCGrapSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCGrapSprite* tolua_ret = (CCGrapSprite*)  Mtolua_new((CCGrapSprite)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCGrapSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCGrapSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CCGrapSprite_new00_local
static int tolua_Dota_CCGrapSprite_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCGrapSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCGrapSprite* tolua_ret = (CCGrapSprite*)  Mtolua_new((CCGrapSprite)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCGrapSprite");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CCGrapSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CCGrapSprite_delete00
static int tolua_Dota_CCGrapSprite_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCGrapSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCGrapSprite* self = (CCGrapSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createGrapSpriteWithFileName of class  CCGrapSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CCGrapSprite_createGrapSpriteWithFileName00
static int tolua_Dota_CCGrapSprite_createGrapSpriteWithFileName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCGrapSprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string pszFileName = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  bool isGrapSprite = ((bool)  tolua_toboolean(tolua_S,3,0));
  {
   CCGrapSprite* tolua_ret = (CCGrapSprite*)  CCGrapSprite::createGrapSpriteWithFileName(pszFileName,isGrapSprite);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCGrapSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createGrapSpriteWithFileName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createGrapSpriteWithFrameName of class  CCGrapSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CCGrapSprite_createGrapSpriteWithFrameName00
static int tolua_Dota_CCGrapSprite_createGrapSpriteWithFrameName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCGrapSprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string frameNames = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  bool isGrapSprite = ((bool)  tolua_toboolean(tolua_S,3,0));
  {
   CCGrapSprite* tolua_ret = (CCGrapSprite*)  CCGrapSprite::createGrapSpriteWithFrameName(frameNames,isGrapSprite);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCGrapSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createGrapSpriteWithFrameName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithTexture of class  CCGrapSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CCGrapSprite_initWithTexture00
static int tolua_Dota_CCGrapSprite_initWithTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCGrapSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTexture2D",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCGrapSprite* self = (CCGrapSprite*)  tolua_tousertype(tolua_S,1,0);
  CCTexture2D* texture = ((CCTexture2D*)  tolua_tousertype(tolua_S,2,0));
  const CCRect* rect = ((const CCRect*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithTexture'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithTexture(texture,*rect);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: draw of class  CCGrapSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CCGrapSprite_draw00
static int tolua_Dota_CCGrapSprite_draw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCGrapSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCGrapSprite* self = (CCGrapSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'draw'", NULL);
#endif
  {
   self->draw();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'draw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initProgram of class  CCGrapSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CCGrapSprite_initProgram00
static int tolua_Dota_CCGrapSprite_initProgram00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCGrapSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCGrapSprite* self = (CCGrapSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initProgram'", NULL);
#endif
  {
   self->initProgram();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initProgram'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: listenBackToForeground of class  CCGrapSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CCGrapSprite_listenBackToForeground00
static int tolua_Dota_CCGrapSprite_listenBackToForeground00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCGrapSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCGrapSprite* self = (CCGrapSprite*)  tolua_tousertype(tolua_S,1,0);
  CCObject* obj = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'listenBackToForeground'", NULL);
#endif
  {
   self->listenBackToForeground(obj);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'listenBackToForeground'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setGrapTexture of class  CCGrapSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CCGrapSprite_setGrapTexture00
static int tolua_Dota_CCGrapSprite_setGrapTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCGrapSprite",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCGrapSprite* self = (CCGrapSprite*)  tolua_tousertype(tolua_S,1,0);
  bool isGrapEnable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setGrapTexture'", NULL);
#endif
  {
   self->setGrapTexture(isGrapEnable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setGrapTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setProperty of class  CCGrapSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CCGrapSprite_setProperty00
static int tolua_Dota_CCGrapSprite_setProperty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCGrapSprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCGrapSprite* self = (CCGrapSprite*)  tolua_tousertype(tolua_S,1,0);
  std::string nameType = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  std::string textureName = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  bool isGrapTexture = ((bool)  tolua_toboolean(tolua_S,4,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setProperty'", NULL);
#endif
  {
   self->setProperty(nameType,textureName,isGrapTexture);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setProperty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CCornerNumIcon */
#ifndef TOLUA_DISABLE_tolua_Dota_CCornerNumIcon_new00
static int tolua_Dota_CCornerNumIcon_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCornerNumIcon",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCornerNumIcon* tolua_ret = (CCornerNumIcon*)  Mtolua_new((CCornerNumIcon)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCornerNumIcon");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCornerNumIcon */
#ifndef TOLUA_DISABLE_tolua_Dota_CCornerNumIcon_new00_local
static int tolua_Dota_CCornerNumIcon_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCornerNumIcon",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCornerNumIcon* tolua_ret = (CCornerNumIcon*)  Mtolua_new((CCornerNumIcon)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCornerNumIcon");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CCornerNumIcon */
#ifndef TOLUA_DISABLE_tolua_Dota_CCornerNumIcon_delete00
static int tolua_Dota_CCornerNumIcon_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCornerNumIcon",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCornerNumIcon* self = (CCornerNumIcon*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCornerNumIcon */
#ifndef TOLUA_DISABLE_tolua_Dota_CCornerNumIcon_create00
static int tolua_Dota_CCornerNumIcon_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCornerNumIcon",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* file1 = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* file2 = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* file3 = ((const char*)  tolua_tostring(tolua_S,4,0));
  {
   CCornerNumIcon* tolua_ret = (CCornerNumIcon*)  CCornerNumIcon::create(file1,file2,file3);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCornerNumIcon");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CCornerNumIcon */
#ifndef TOLUA_DISABLE_tolua_Dota_CCornerNumIcon_init00
static int tolua_Dota_CCornerNumIcon_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCornerNumIcon",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCornerNumIcon* self = (CCornerNumIcon*)  tolua_tousertype(tolua_S,1,0);
  const char* file1 = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* file2 = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* file3 = ((const char*)  tolua_tostring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(file1,file2,file3);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setNum of class  CCornerNumIcon */
#ifndef TOLUA_DISABLE_tolua_Dota_CCornerNumIcon_setNum00
static int tolua_Dota_CCornerNumIcon_setNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCornerNumIcon",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCornerNumIcon* self = (CCornerNumIcon*)  tolua_tousertype(tolua_S,1,0);
  unsigned int num = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setNum'", NULL);
#endif
  {
   self->setNum(num);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNumLabel of class  CCornerNumIcon */
#ifndef TOLUA_DISABLE_tolua_Dota_CCornerNumIcon_getNumLabel00
static int tolua_Dota_CCornerNumIcon_getNumLabel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCornerNumIcon",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCornerNumIcon* self = (CCornerNumIcon*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNumLabel'", NULL);
#endif
  {
   CCLabelTTF* tolua_ret = (CCLabelTTF*)  self->getNumLabel();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCLabelTTF");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNumLabel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setShow of class  CCornerNumIcon */
#ifndef TOLUA_DISABLE_tolua_Dota_CCornerNumIcon_setShow00
static int tolua_Dota_CCornerNumIcon_setShow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCornerNumIcon",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCornerNumIcon* self = (CCornerNumIcon*)  tolua_tousertype(tolua_S,1,0);
  bool isshow = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setShow'", NULL);
#endif
  {
   self->setShow(isshow);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setShow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CCRectClipNode */
#ifndef TOLUA_DISABLE_tolua_Dota_CCRectClipNode_new00
static int tolua_Dota_CCRectClipNode_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCRectClipNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCRectClipNode* tolua_ret = (CCRectClipNode*)  Mtolua_new((CCRectClipNode)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCRectClipNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCRectClipNode */
#ifndef TOLUA_DISABLE_tolua_Dota_CCRectClipNode_new00_local
static int tolua_Dota_CCRectClipNode_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCRectClipNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCRectClipNode* tolua_ret = (CCRectClipNode*)  Mtolua_new((CCRectClipNode)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCRectClipNode");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CCRectClipNode */
#ifndef TOLUA_DISABLE_tolua_Dota_CCRectClipNode_delete00
static int tolua_Dota_CCRectClipNode_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCRectClipNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCRectClipNode* self = (CCRectClipNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CCRectClipNode */
#ifndef TOLUA_DISABLE_tolua_Dota_CCRectClipNode_init00
static int tolua_Dota_CCRectClipNode_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCRectClipNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCRectClipNode* self = (CCRectClipNode*)  tolua_tousertype(tolua_S,1,0);
  CCRect drawRect = *((CCRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(drawRect);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCRectClipNode */
#ifndef TOLUA_DISABLE_tolua_Dota_CCRectClipNode_create00
static int tolua_Dota_CCRectClipNode_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCRectClipNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCRect drawRect = *((CCRect*)  tolua_tousertype(tolua_S,2,0));
  {
   CCRectClipNode* tolua_ret = (CCRectClipNode*)  CCRectClipNode::create(drawRect);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCRectClipNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: visit of class  CCRectClipNode */
#ifndef TOLUA_DISABLE_tolua_Dota_CCRectClipNode_visit00
static int tolua_Dota_CCRectClipNode_visit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCRectClipNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCRectClipNode* self = (CCRectClipNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'visit'", NULL);
#endif
  {
   self->visit();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'visit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CCSignSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CCSignSprite_new00
static int tolua_Dota_CCSignSprite_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCSignSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCSignSprite* tolua_ret = (CCSignSprite*)  Mtolua_new((CCSignSprite)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSignSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CCSignSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CCSignSprite_new00_local
static int tolua_Dota_CCSignSprite_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCSignSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCSignSprite* tolua_ret = (CCSignSprite*)  Mtolua_new((CCSignSprite)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSignSprite");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CCSignSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CCSignSprite_delete00
static int tolua_Dota_CCSignSprite_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSignSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSignSprite* self = (CCSignSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createCCSignSpriteWithFile of class  CCSignSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CCSignSprite_createCCSignSpriteWithFile00
static int tolua_Dota_CCSignSprite_createCCSignSpriteWithFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCSignSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"SignSpriteType",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int signUniqueID = ((int)  tolua_tonumber(tolua_S,2,0));
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,3,0));
  SignSpriteType nodeType = *((SignSpriteType*)  tolua_tousertype(tolua_S,4,0));
  bool isMoveEnable = ((bool)  tolua_toboolean(tolua_S,5,true));
  {
   CCSignSprite* tolua_ret = (CCSignSprite*)  CCSignSprite::createCCSignSpriteWithFile(signUniqueID,fileName,nodeType,isMoveEnable);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSignSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createCCSignSpriteWithFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createCCSignSpriteWithFrameName of class  CCSignSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CCSignSprite_createCCSignSpriteWithFrameName00
static int tolua_Dota_CCSignSprite_createCCSignSpriteWithFrameName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCSignSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"SignSpriteType",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int signUniqueID = ((int)  tolua_tonumber(tolua_S,2,0));
  const char* frameName = ((const char*)  tolua_tostring(tolua_S,3,0));
  SignSpriteType nodeType = *((SignSpriteType*)  tolua_tousertype(tolua_S,4,0));
  bool isMoveEnable = ((bool)  tolua_toboolean(tolua_S,5,true));
  {
   CCSignSprite* tolua_ret = (CCSignSprite*)  CCSignSprite::createCCSignSpriteWithFrameName(signUniqueID,frameName,nodeType,isMoveEnable);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSignSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createCCSignSpriteWithFrameName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInitPosition of class  CCSignSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CCSignSprite_setInitPosition00
static int tolua_Dota_CCSignSprite_setInitPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSignSprite",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSignSprite* self = (CCSignSprite*)  tolua_tousertype(tolua_S,1,0);
  CCPoint initPosition = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInitPosition'", NULL);
#endif
  {
   self->setInitPosition(initPosition);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInitPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInitPosition of class  CCSignSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CCSignSprite_getInitPosition00
static int tolua_Dota_CCSignSprite_getInitPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSignSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSignSprite* self = (CCSignSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getInitPosition'", NULL);
#endif
  {
   CCPoint tolua_ret = (CCPoint)  self->getInitPosition();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInitPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDragNodeType of class  CCSignSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CCSignSprite_getDragNodeType00
static int tolua_Dota_CCSignSprite_getDragNodeType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSignSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSignSprite* self = (CCSignSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDragNodeType'", NULL);
#endif
  {
   SignSpriteType tolua_ret = (SignSpriteType)  self->getDragNodeType();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((SignSpriteType)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"SignSpriteType");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(SignSpriteType));
     tolua_pushusertype(tolua_S,tolua_obj,"SignSpriteType");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDragNodeType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDragEnable of class  CCSignSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CCSignSprite_getDragEnable00
static int tolua_Dota_CCSignSprite_getDragEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSignSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSignSprite* self = (CCSignSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getDragEnable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getDragEnable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDragEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDragEnable of class  CCSignSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CCSignSprite_setDragEnable00
static int tolua_Dota_CCSignSprite_setDragEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSignSprite",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSignSprite* self = (CCSignSprite*)  tolua_tousertype(tolua_S,1,0);
  bool bDrageEnable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDragEnable'", NULL);
#endif
  {
   self->setDragEnable(bDrageEnable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDragEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: forceToInitPosition of class  CCSignSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CCSignSprite_forceToInitPosition00
static int tolua_Dota_CCSignSprite_forceToInitPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSignSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSignSprite* self = (CCSignSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'forceToInitPosition'", NULL);
#endif
  {
   self->forceToInitPosition();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'forceToInitPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkIsCoverWithRect of class  CCSignSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CCSignSprite_checkIsCoverWithRect00
static int tolua_Dota_CCSignSprite_checkIsCoverWithRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSignSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSignSprite* self = (CCSignSprite*)  tolua_tousertype(tolua_S,1,0);
  float targetleft = ((float)  tolua_tonumber(tolua_S,2,0));
  float targetright = ((float)  tolua_tonumber(tolua_S,3,0));
  float targettop = ((float)  tolua_tonumber(tolua_S,4,0));
  float targetbottom = ((float)  tolua_tonumber(tolua_S,5,0));
  float offWidth = ((float)  tolua_tonumber(tolua_S,6,65.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'checkIsCoverWithRect'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->checkIsCoverWithRect(targetleft,targetright,targettop,targetbottom,offWidth);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'checkIsCoverWithRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __SingleTouchProtocol__ of class  CCSignSprite */
#ifndef TOLUA_DISABLE_tolua_get_CCSignSprite___SingleTouchProtocol__
static int tolua_get_CCSignSprite___SingleTouchProtocol__(lua_State* tolua_S)
{
  CCSignSprite* self = (CCSignSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__SingleTouchProtocol__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<SingleTouchProtocol*>(self), "SingleTouchProtocol");
#else
   tolua_pushusertype(tolua_S,(void*)((SingleTouchProtocol*)self), "SingleTouchProtocol");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: clickEvent of class  CDragSpriteDelegate */
#ifndef TOLUA_DISABLE_tolua_Dota_CDragSpriteDelegate_clickEvent00
static int tolua_Dota_CDragSpriteDelegate_clickEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDragSpriteDelegate",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDragSpriteDelegate* self = (CDragSpriteDelegate*)  tolua_tousertype(tolua_S,1,0);
  int idx = ((int)  tolua_tonumber(tolua_S,2,0));
  int type = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clickEvent'", NULL);
#endif
  {
   self->clickEvent(idx,type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clickEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: containsTheCopy of class  CDragSpriteDelegate */
#ifndef TOLUA_DISABLE_tolua_Dota_CDragSpriteDelegate_containsTheCopy00
static int tolua_Dota_CDragSpriteDelegate_containsTheCopy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDragSpriteDelegate",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDragSpriteDelegate* self = (CDragSpriteDelegate*)  tolua_tousertype(tolua_S,1,0);
  CCSprite* copy = ((CCSprite*)  tolua_tousertype(tolua_S,2,0));
  int type = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'containsTheCopy'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->containsTheCopy(copy,type);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'containsTheCopy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CDragSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CDragSprite_new00
static int tolua_Dota_CDragSprite_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CDragSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CDragSprite* tolua_ret = (CDragSprite*)  Mtolua_new((CDragSprite)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CDragSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CDragSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CDragSprite_new00_local
static int tolua_Dota_CDragSprite_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CDragSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CDragSprite* tolua_ret = (CDragSprite*)  Mtolua_new((CDragSprite)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CDragSprite");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CDragSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CDragSprite_delete00
static int tolua_Dota_CDragSprite_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDragSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDragSprite* self = (CDragSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CDragSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CDragSprite_create00
static int tolua_Dota_CDragSprite_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CDragSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CDragSpriteDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCNode* copyroot = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
  CDragSpriteDelegate* delegate = ((CDragSpriteDelegate*)  tolua_tousertype(tolua_S,4,0));
  {
   CDragSprite* tolua_ret = (CDragSprite*)  CDragSprite::create(filename,copyroot,delegate);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CDragSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithFile of class  CDragSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CDragSprite_initWithFile00
static int tolua_Dota_CDragSprite_initWithFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDragSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CDragSpriteDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDragSprite* self = (CDragSprite*)  tolua_tousertype(tolua_S,1,0);
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCNode* copyroot = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
  CDragSpriteDelegate* delegate = ((CDragSpriteDelegate*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithFile(filename,copyroot,delegate);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CDragSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CDragSprite_create01
static int tolua_Dota_CDragSprite_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CDragSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTexture2D",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CDragSpriteDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCTexture2D* texture = ((CCTexture2D*)  tolua_tousertype(tolua_S,2,0));
  CCNode* copyroot = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
  CDragSpriteDelegate* delegate = ((CDragSpriteDelegate*)  tolua_tousertype(tolua_S,4,0));
  {
   CDragSprite* tolua_ret = (CDragSprite*)  CDragSprite::create(texture,copyroot,delegate);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CDragSprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Dota_CDragSprite_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithTexture of class  CDragSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CDragSprite_initWithTexture00
static int tolua_Dota_CDragSprite_initWithTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDragSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTexture2D",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CDragSpriteDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDragSprite* self = (CDragSprite*)  tolua_tousertype(tolua_S,1,0);
  CCTexture2D* texture = ((CCTexture2D*)  tolua_tousertype(tolua_S,2,0));
  CCNode* copyroot = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
  CDragSpriteDelegate* delegate = ((CDragSpriteDelegate*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithTexture'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithTexture(texture,copyroot,delegate);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDelegate of class  CDragSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CDragSprite_setDelegate00
static int tolua_Dota_CDragSprite_setDelegate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDragSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CDragSpriteDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDragSprite* self = (CDragSprite*)  tolua_tousertype(tolua_S,1,0);
  CDragSpriteDelegate* delegate = ((CDragSpriteDelegate*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDelegate'", NULL);
#endif
  {
   self->setDelegate(delegate);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDelegate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isDragEabled of class  CDragSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CDragSprite_isDragEabled00
static int tolua_Dota_CDragSprite_isDragEabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDragSprite",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDragSprite* self = (CDragSprite*)  tolua_tousertype(tolua_S,1,0);
  bool eabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isDragEabled'", NULL);
#endif
  {
   self->isDragEabled(eabled);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isDragEabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isDragEabled of class  CDragSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CDragSprite_isDragEabled01
static int tolua_Dota_CDragSprite_isDragEabled01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CDragSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CDragSprite* self = (const CDragSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isDragEabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isDragEabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Dota_CDragSprite_isDragEabled00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: copyzOrder of class  CDragSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CDragSprite_copyzOrder00
static int tolua_Dota_CDragSprite_copyzOrder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDragSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDragSprite* self = (CDragSprite*)  tolua_tousertype(tolua_S,1,0);
  short zOrder = ((short)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'copyzOrder'", NULL);
#endif
  {
   self->copyzOrder(zOrder);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'copyzOrder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: copyzOrder of class  CDragSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CDragSprite_copyzOrder01
static int tolua_Dota_CDragSprite_copyzOrder01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CDragSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CDragSprite* self = (const CDragSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'copyzOrder'", NULL);
#endif
  {
   int tolua_ret = (int)  self->copyzOrder();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Dota_CDragSprite_copyzOrder00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: dragType of class  CDragSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CDragSprite_dragType00
static int tolua_Dota_CDragSprite_dragType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDragSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDragSprite* self = (CDragSprite*)  tolua_tousertype(tolua_S,1,0);
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dragType'", NULL);
#endif
  {
   self->dragType(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dragType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dragType of class  CDragSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CDragSprite_dragType01
static int tolua_Dota_CDragSprite_dragType01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CDragSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CDragSprite* self = (const CDragSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dragType'", NULL);
#endif
  {
   int tolua_ret = (int)  self->dragType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Dota_CDragSprite_dragType00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIDX of class  CDragSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CDragSprite_setIDX00
static int tolua_Dota_CDragSprite_setIDX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CDragSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CDragSprite* self = (CDragSprite*)  tolua_tousertype(tolua_S,1,0);
  int idx = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIDX'", NULL);
#endif
  {
   self->setIDX(idx);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIDX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIDX of class  CDragSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CDragSprite_getIDX00
static int tolua_Dota_CDragSprite_getIDX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CDragSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CDragSprite* self = (const CDragSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIDX'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getIDX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIDX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCTargetedTouchDelegate__ of class  CDragSprite */
#ifndef TOLUA_DISABLE_tolua_get_CDragSprite___CCTargetedTouchDelegate__
static int tolua_get_CDragSprite___CCTargetedTouchDelegate__(lua_State* tolua_S)
{
  CDragSprite* self = (CDragSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCTargetedTouchDelegate__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCTargetedTouchDelegate*>(self), "CCTargetedTouchDelegate");
#else
   tolua_pushusertype(tolua_S,(void*)((CCTargetedTouchDelegate*)self), "CCTargetedTouchDelegate");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: changePage of class  CPageScrollDelegate */
#ifndef TOLUA_DISABLE_tolua_Dota_CPageScrollDelegate_changePage00
static int tolua_Dota_CPageScrollDelegate_changePage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CPageScrollDelegate",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CPageScrollDelegate* self = (CPageScrollDelegate*)  tolua_tousertype(tolua_S,1,0);
  int idx = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'changePage'", NULL);
#endif
  {
   self->changePage(idx);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changePage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CPageScroll */
#ifndef TOLUA_DISABLE_tolua_Dota_CPageScroll_new00
static int tolua_Dota_CPageScroll_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CPageScroll",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CPageScroll* tolua_ret = (CPageScroll*)  Mtolua_new((CPageScroll)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CPageScroll");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CPageScroll */
#ifndef TOLUA_DISABLE_tolua_Dota_CPageScroll_new00_local
static int tolua_Dota_CPageScroll_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CPageScroll",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CPageScroll* tolua_ret = (CPageScroll*)  Mtolua_new((CPageScroll)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CPageScroll");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CPageScroll */
#ifndef TOLUA_DISABLE_tolua_Dota_CPageScroll_delete00
static int tolua_Dota_CPageScroll_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CPageScroll",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CPageScroll* self = (CPageScroll*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CPageScroll */
#ifndef TOLUA_DISABLE_tolua_Dota_CPageScroll_create00
static int tolua_Dota_CPageScroll_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CPageScroll",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CPageScrollDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCSize* viewsz = ((const CCSize*)  tolua_tousertype(tolua_S,2,0));
  int pagecount = ((int)  tolua_tonumber(tolua_S,3,0));
  CPageScrollDelegate* delegate = ((CPageScrollDelegate*)  tolua_tousertype(tolua_S,4,0));
  {
   CPageScroll* tolua_ret = (CPageScroll*)  CPageScroll::create(*viewsz,pagecount,delegate);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CPageScroll");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CPageScroll */
#ifndef TOLUA_DISABLE_tolua_Dota_CPageScroll_init00
static int tolua_Dota_CPageScroll_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CPageScroll",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CPageScrollDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CPageScroll* self = (CPageScroll*)  tolua_tousertype(tolua_S,1,0);
  const CCSize* viewsz = ((const CCSize*)  tolua_tousertype(tolua_S,2,0));
  int pagecount = ((int)  tolua_tonumber(tolua_S,3,0));
  CPageScrollDelegate* delegate = ((CPageScrollDelegate*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(*viewsz,pagecount,delegate);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContainer of class  CPageScroll */
#ifndef TOLUA_DISABLE_tolua_Dota_CPageScroll_getContainer00
static int tolua_Dota_CPageScroll_getContainer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CPageScroll",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CPageScroll* self = (const CPageScroll*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContainer'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getContainer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getContainer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isTouchInArea of class  CPageScroll */
#ifndef TOLUA_DISABLE_tolua_Dota_CPageScroll_isTouchInArea00
static int tolua_Dota_CPageScroll_isTouchInArea00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CPageScroll",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CPageScroll* self = (CPageScroll*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isTouchInArea'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isTouchInArea();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isTouchInArea'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: moveToPage of class  CPageScroll */
#ifndef TOLUA_DISABLE_tolua_Dota_CPageScroll_moveToPage00
static int tolua_Dota_CPageScroll_moveToPage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CPageScroll",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CPageScroll* self = (CPageScroll*)  tolua_tousertype(tolua_S,1,0);
  int page = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'moveToPage'", NULL);
#endif
  {
   self->moveToPage(page);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'moveToPage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CPriorityLayerColor */
#ifndef TOLUA_DISABLE_tolua_Dota_CPriorityLayerColor_new00
static int tolua_Dota_CPriorityLayerColor_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CPriorityLayerColor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CPriorityLayerColor* tolua_ret = (CPriorityLayerColor*)  Mtolua_new((CPriorityLayerColor)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CPriorityLayerColor");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CPriorityLayerColor */
#ifndef TOLUA_DISABLE_tolua_Dota_CPriorityLayerColor_new00_local
static int tolua_Dota_CPriorityLayerColor_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CPriorityLayerColor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CPriorityLayerColor* tolua_ret = (CPriorityLayerColor*)  Mtolua_new((CPriorityLayerColor)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CPriorityLayerColor");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CPriorityLayerColor */
#ifndef TOLUA_DISABLE_tolua_Dota_CPriorityLayerColor_delete00
static int tolua_Dota_CPriorityLayerColor_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CPriorityLayerColor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CPriorityLayerColor* self = (CPriorityLayerColor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CPriorityLayerColor */
#ifndef TOLUA_DISABLE_tolua_Dota_CPriorityLayerColor_create00
static int tolua_Dota_CPriorityLayerColor_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CPriorityLayerColor",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor4B",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"GLfloat",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"GLfloat",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ccColor4B* color = ((const ccColor4B*)  tolua_tousertype(tolua_S,2,0));
  GLfloat width = *((GLfloat*)  tolua_tousertype(tolua_S,3,0));
  GLfloat height = *((GLfloat*)  tolua_tousertype(tolua_S,4,0));
  int priority = ((int)  tolua_tonumber(tolua_S,5,0));
  {
   CPriorityLayerColor* tolua_ret = (CPriorityLayerColor*)  CPriorityLayerColor::create(*color,width,height,priority);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CPriorityLayerColor");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithColor of class  CPriorityLayerColor */
#ifndef TOLUA_DISABLE_tolua_Dota_CPriorityLayerColor_initWithColor00
static int tolua_Dota_CPriorityLayerColor_initWithColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CPriorityLayerColor",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor4B",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"GLfloat",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"GLfloat",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CPriorityLayerColor* self = (CPriorityLayerColor*)  tolua_tousertype(tolua_S,1,0);
  const ccColor4B* color = ((const ccColor4B*)  tolua_tousertype(tolua_S,2,0));
  GLfloat width = *((GLfloat*)  tolua_tousertype(tolua_S,3,0));
  GLfloat height = *((GLfloat*)  tolua_tousertype(tolua_S,4,0));
  int priority = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithColor'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithColor(*color,width,height,priority);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDelegate of class  CPriorityLayerColor */
#ifndef TOLUA_DISABLE_tolua_Dota_CPriorityLayerColor_setDelegate00
static int tolua_Dota_CPriorityLayerColor_setDelegate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CPriorityLayerColor",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CPriorityLayerColorDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CPriorityLayerColor* self = (CPriorityLayerColor*)  tolua_tousertype(tolua_S,1,0);
  CPriorityLayerColorDelegate* del = ((CPriorityLayerColorDelegate*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDelegate'", NULL);
#endif
  {
   self->setDelegate(del);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDelegate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIDX of class  CPriorityLayerColor */
#ifndef TOLUA_DISABLE_tolua_Dota_CPriorityLayerColor_setIDX00
static int tolua_Dota_CPriorityLayerColor_setIDX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CPriorityLayerColor",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CPriorityLayerColor* self = (CPriorityLayerColor*)  tolua_tousertype(tolua_S,1,0);
  int idx = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIDX'", NULL);
#endif
  {
   self->setIDX(idx);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIDX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIDX of class  CPriorityLayerColor */
#ifndef TOLUA_DISABLE_tolua_Dota_CPriorityLayerColor_getIDX00
static int tolua_Dota_CPriorityLayerColor_getIDX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CPriorityLayerColor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CPriorityLayerColor* self = (const CPriorityLayerColor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIDX'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getIDX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIDX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: touchEvent of class  CPriorityLayerColorDelegate */
#ifndef TOLUA_DISABLE_tolua_Dota_CPriorityLayerColorDelegate_touchEvent00
static int tolua_Dota_CPriorityLayerColorDelegate_touchEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CPriorityLayerColorDelegate",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CPriorityLayerColor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CPriorityLayerColorDelegate* self = (CPriorityLayerColorDelegate*)  tolua_tousertype(tolua_S,1,0);
  CPriorityLayerColor* pLayerColor = ((CPriorityLayerColor*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'touchEvent'", NULL);
#endif
  {
   self->touchEvent(pLayerColor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'touchEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CProgressInnerBar */
#ifndef TOLUA_DISABLE_tolua_Dota_CProgressInnerBar_new00
static int tolua_Dota_CProgressInnerBar_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CProgressInnerBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CProgressInnerBar* tolua_ret = (CProgressInnerBar*)  Mtolua_new((CProgressInnerBar)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CProgressInnerBar");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CProgressInnerBar */
#ifndef TOLUA_DISABLE_tolua_Dota_CProgressInnerBar_new00_local
static int tolua_Dota_CProgressInnerBar_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CProgressInnerBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CProgressInnerBar* tolua_ret = (CProgressInnerBar*)  Mtolua_new((CProgressInnerBar)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CProgressInnerBar");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CProgressInnerBar */
#ifndef TOLUA_DISABLE_tolua_Dota_CProgressInnerBar_delete00
static int tolua_Dota_CProgressInnerBar_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CProgressInnerBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CProgressInnerBar* self = (CProgressInnerBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CProgressInnerBar */
#ifndef TOLUA_DISABLE_tolua_Dota_CProgressInnerBar_create00
static int tolua_Dota_CProgressInnerBar_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CProgressInnerBar",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* pszFileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   CProgressInnerBar* tolua_ret = (CProgressInnerBar*)  CProgressInnerBar::create(pszFileName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CProgressInnerBar");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CProgressInnerBar */
#ifndef TOLUA_DISABLE_tolua_Dota_CProgressInnerBar_init00
static int tolua_Dota_CProgressInnerBar_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CProgressInnerBar",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CProgressInnerBar* self = (CProgressInnerBar*)  tolua_tousertype(tolua_S,1,0);
  const char* pszFileName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(pszFileName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPercent of class  CProgressInnerBar */
#ifndef TOLUA_DISABLE_tolua_Dota_CProgressInnerBar_setPercent00
static int tolua_Dota_CProgressInnerBar_setPercent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CProgressInnerBar",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CProgressInnerBar* self = (CProgressInnerBar*)  tolua_tousertype(tolua_S,1,0);
  float percent = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPercent'", NULL);
#endif
  {
   self->setPercent(percent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPercent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPercent of class  CProgressInnerBar */
#ifndef TOLUA_DISABLE_tolua_Dota_CProgressInnerBar_getPercent00
static int tolua_Dota_CProgressInnerBar_getPercent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CProgressInnerBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CProgressInnerBar* self = (const CProgressInnerBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPercent'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getPercent();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPercent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CallBack_NextLevel of class  CProgressTimerDelegate */
#ifndef TOLUA_DISABLE_tolua_Dota_CProgressTimerDelegate_CallBack_NextLevel00
static int tolua_Dota_CProgressTimerDelegate_CallBack_NextLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CProgressTimerDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CProgressTimerDelegate* self = (CProgressTimerDelegate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CallBack_NextLevel'", NULL);
#endif
  {
   self->CallBack_NextLevel();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CallBack_NextLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CallBack_RunFinish of class  CProgressTimerDelegate */
#ifndef TOLUA_DISABLE_tolua_Dota_CProgressTimerDelegate_CallBack_RunFinish00
static int tolua_Dota_CProgressTimerDelegate_CallBack_RunFinish00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CProgressTimerDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CProgressTimerDelegate* self = (CProgressTimerDelegate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CallBack_RunFinish'", NULL);
#endif
  {
   self->CallBack_RunFinish();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CallBack_RunFinish'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CProgressTimer */
#ifndef TOLUA_DISABLE_tolua_Dota_CProgressTimer_new00
static int tolua_Dota_CProgressTimer_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CProgressTimer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CProgressTimer* tolua_ret = (CProgressTimer*)  Mtolua_new((CProgressTimer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CProgressTimer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CProgressTimer */
#ifndef TOLUA_DISABLE_tolua_Dota_CProgressTimer_new00_local
static int tolua_Dota_CProgressTimer_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CProgressTimer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CProgressTimer* tolua_ret = (CProgressTimer*)  Mtolua_new((CProgressTimer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CProgressTimer");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CProgressTimer */
#ifndef TOLUA_DISABLE_tolua_Dota_CProgressTimer_new01
static int tolua_Dota_CProgressTimer_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CProgressTimer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  {
   CProgressTimer* tolua_ret = (CProgressTimer*)  Mtolua_new((CProgressTimer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CProgressTimer");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Dota_CProgressTimer_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CProgressTimer */
#ifndef TOLUA_DISABLE_tolua_Dota_CProgressTimer_new01_local
static int tolua_Dota_CProgressTimer_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CProgressTimer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  {
   CProgressTimer* tolua_ret = (CProgressTimer*)  Mtolua_new((CProgressTimer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CProgressTimer");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Dota_CProgressTimer_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CProgressTimer */
#ifndef TOLUA_DISABLE_tolua_Dota_CProgressTimer_create00
static int tolua_Dota_CProgressTimer_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CProgressTimer",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* pszFileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  float time = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   CProgressTimer* tolua_ret = (CProgressTimer*)  CProgressTimer::create(pszFileName,time);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CProgressTimer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CProgressTimer */
#ifndef TOLUA_DISABLE_tolua_Dota_CProgressTimer_init00
static int tolua_Dota_CProgressTimer_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CProgressTimer",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CProgressTimer* self = (CProgressTimer*)  tolua_tousertype(tolua_S,1,0);
  const char* pszFileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  float time = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(pszFileName,time);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRunSchedule of class  CProgressTimer */
#ifndef TOLUA_DISABLE_tolua_Dota_CProgressTimer_setRunSchedule00
static int tolua_Dota_CProgressTimer_setRunSchedule00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CProgressTimer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CProgressTimer* self = (CProgressTimer*)  tolua_tousertype(tolua_S,1,0);
  float posbegin = ((float)  tolua_tonumber(tolua_S,2,0));
  float posend = ((float)  tolua_tonumber(tolua_S,3,0));
  int times = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRunSchedule'", NULL);
#endif
  {
   self->setRunSchedule(posbegin,posend,times);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRunSchedule'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RunFinish of class  CProgressTimer */
#ifndef TOLUA_DISABLE_tolua_Dota_CProgressTimer_RunFinish00
static int tolua_Dota_CProgressTimer_RunFinish00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CProgressTimer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CProgressTimer* self = (CProgressTimer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RunFinish'", NULL);
#endif
  {
   self->RunFinish();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RunFinish'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NextLevel of class  CProgressTimer */
#ifndef TOLUA_DISABLE_tolua_Dota_CProgressTimer_NextLevel00
static int tolua_Dota_CProgressTimer_NextLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CProgressTimer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CProgressTimer* self = (CProgressTimer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NextLevel'", NULL);
#endif
  {
   self->NextLevel();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NextLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDelegate of class  CProgressTimer */
#ifndef TOLUA_DISABLE_tolua_Dota_CProgressTimer_setDelegate00
static int tolua_Dota_CProgressTimer_setDelegate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CProgressTimer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CProgressTimerDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CProgressTimer* self = (CProgressTimer*)  tolua_tousertype(tolua_S,1,0);
  CProgressTimerDelegate* Delegate = ((CProgressTimerDelegate*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDelegate'", NULL);
#endif
  {
   self->setDelegate(Delegate);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDelegate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CSpriteSelected */
#ifndef TOLUA_DISABLE_tolua_Dota_CSpriteSelected_create00
static int tolua_Dota_CSpriteSelected_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CSpriteSelected",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* selFile = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* norFile = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   CSpriteSelected* tolua_ret = (CSpriteSelected*)  CSpriteSelected::create(selFile,norFile);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSpriteSelected");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithFile of class  CSpriteSelected */
#ifndef TOLUA_DISABLE_tolua_Dota_CSpriteSelected_initWithFile00
static int tolua_Dota_CSpriteSelected_initWithFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSpriteSelected",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSpriteSelected* self = (CSpriteSelected*)  tolua_tousertype(tolua_S,1,0);
  const char* selFile = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* norFile = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithFile(selFile,norFile);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CSelectedSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CSelectedSprite_create00
static int tolua_Dota_CSelectedSprite_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CSelectedSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const CCSize",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* selFile = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* norFile = ((const char*)  tolua_tostring(tolua_S,3,0));
  const CCSize* sz_sel = ((const CCSize*)  tolua_tousertype(tolua_S,4,0));
  const CCSize* sz_nor = ((const CCSize*)  tolua_tousertype(tolua_S,5,0));
  {
   CSelectedSprite* tolua_ret = (CSelectedSprite*)  CSelectedSprite::create(selFile,norFile,*sz_sel,*sz_nor);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSelectedSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithFile of class  CSelectedSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CSelectedSprite_initWithFile00
static int tolua_Dota_CSelectedSprite_initWithFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSelectedSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const CCSize",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSelectedSprite* self = (CSelectedSprite*)  tolua_tousertype(tolua_S,1,0);
  const char* selFile = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* norFile = ((const char*)  tolua_tostring(tolua_S,3,0));
  const CCSize* sz_sel = ((const CCSize*)  tolua_tousertype(tolua_S,4,0));
  const CCSize* sz_nor = ((const CCSize*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithFile(selFile,norFile,*sz_sel,*sz_nor);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CSimpleActionSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CSimpleActionSprite_create00
static int tolua_Dota_CSimpleActionSprite_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CSimpleActionSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"std::vector<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int actionType = ((int)  tolua_tonumber(tolua_S,2,0));
  std::vector<float> attachParam = *((std::vector<float>*)  tolua_tousertype(tolua_S,3,0));
  {
   CSimpleActionSprite* tolua_ret = (CSimpleActionSprite*)  CSimpleActionSprite::create(actionType,attachParam);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSimpleActionSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PlayAction of class  CSimpleActionSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CSimpleActionSprite_PlayAction00
static int tolua_Dota_CSimpleActionSprite_PlayAction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSimpleActionSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSimpleActionSprite* self = (CSimpleActionSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PlayAction'", NULL);
#endif
  {
   self->PlayAction();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PlayAction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: StopAction of class  CSimpleActionSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CSimpleActionSprite_StopAction00
static int tolua_Dota_CSimpleActionSprite_StopAction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSimpleActionSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSimpleActionSprite* self = (CSimpleActionSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StopAction'", NULL);
#endif
  {
   self->StopAction();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StopAction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetInitPosition of class  CSimpleActionSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CSimpleActionSprite_SetInitPosition00
static int tolua_Dota_CSimpleActionSprite_SetInitPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSimpleActionSprite",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSimpleActionSprite* self = (CSimpleActionSprite*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* position = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetInitPosition'", NULL);
#endif
  {
   self->SetInitPosition(*position);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetInitPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addChild of class  CSimpleActionSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CSimpleActionSprite_addChild00
static int tolua_Dota_CSimpleActionSprite_addChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSimpleActionSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSimpleActionSprite* self = (CSimpleActionSprite*)  tolua_tousertype(tolua_S,1,0);
  CCNode* pChild = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addChild'", NULL);
#endif
  {
   self->addChild(pChild);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CSprite_create00
static int tolua_Dota_CSprite_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filepath = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   CSprite* tolua_ret = (CSprite*)  CSprite::create(filepath);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CSprite_init00
static int tolua_Dota_CSprite_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSprite* self = (CSprite*)  tolua_tousertype(tolua_S,1,0);
  const char* filepath = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(filepath);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFilePath1 of class  CSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CSprite_setFilePath100
static int tolua_Dota_CSprite_setFilePath100(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSprite* self = (CSprite*)  tolua_tousertype(tolua_S,1,0);
  const char* fp = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFilePath1'", NULL);
#endif
  {
   self->setFilePath1(fp);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFilePath1'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFilePath2 of class  CSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CSprite_setFilePath200
static int tolua_Dota_CSprite_setFilePath200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSprite* self = (CSprite*)  tolua_tousertype(tolua_S,1,0);
  const char* fp = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFilePath2'", NULL);
#endif
  {
   self->setFilePath2(fp);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFilePath2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFilePath3 of class  CSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CSprite_setFilePath300
static int tolua_Dota_CSprite_setFilePath300(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSprite* self = (CSprite*)  tolua_tousertype(tolua_S,1,0);
  const char* fp = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFilePath3'", NULL);
#endif
  {
   self->setFilePath3(fp);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFilePath3'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNowShowFileIndex of class  CSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CSprite_getNowShowFileIndex00
static int tolua_Dota_CSprite_getNowShowFileIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSprite* self = (CSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNowShowFileIndex'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getNowShowFileIndex();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNowShowFileIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: changeToImage1 of class  CSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CSprite_changeToImage100
static int tolua_Dota_CSprite_changeToImage100(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSprite* self = (CSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'changeToImage1'", NULL);
#endif
  {
   self->changeToImage1();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeToImage1'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: changeToImage2 of class  CSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CSprite_changeToImage200
static int tolua_Dota_CSprite_changeToImage200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSprite* self = (CSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'changeToImage2'", NULL);
#endif
  {
   self->changeToImage2();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeToImage2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: changeToImage3 of class  CSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CSprite_changeToImage300
static int tolua_Dota_CSprite_changeToImage300(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSprite* self = (CSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'changeToImage3'", NULL);
#endif
  {
   self->changeToImage3();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'changeToImage3'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hasImage1 of class  CSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CSprite_hasImage100
static int tolua_Dota_CSprite_hasImage100(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSprite* self = (CSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hasImage1'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->hasImage1();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hasImage1'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hasImage2 of class  CSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CSprite_hasImage200
static int tolua_Dota_CSprite_hasImage200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSprite* self = (CSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hasImage2'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->hasImage2();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hasImage2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hasImage3 of class  CSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CSprite_hasImage300
static int tolua_Dota_CSprite_hasImage300(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSprite* self = (CSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hasImage3'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->hasImage3();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hasImage3'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CTitleSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CTitleSprite_new00
static int tolua_Dota_CTitleSprite_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CTitleSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CTitleSprite* tolua_ret = (CTitleSprite*)  Mtolua_new((CTitleSprite)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTitleSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CTitleSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CTitleSprite_new00_local
static int tolua_Dota_CTitleSprite_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CTitleSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CTitleSprite* tolua_ret = (CTitleSprite*)  Mtolua_new((CTitleSprite)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTitleSprite");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CTitleSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CTitleSprite_create00
static int tolua_Dota_CTitleSprite_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CTitleSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCLabelTTF",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filepath = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCLabelTTF* label = ((CCLabelTTF*)  tolua_tousertype(tolua_S,3,0));
  {
   CTitleSprite* tolua_ret = (CTitleSprite*)  CTitleSprite::create(filepath,label);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTitleSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CTitleSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CTitleSprite_init00
static int tolua_Dota_CTitleSprite_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTitleSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCLabelTTF",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTitleSprite* self = (CTitleSprite*)  tolua_tousertype(tolua_S,1,0);
  const char* filepath = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCLabelTTF* label = ((CCLabelTTF*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(filepath,label);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLabelString of class  CTitleSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CTitleSprite_SetLabelString00
static int tolua_Dota_CTitleSprite_SetLabelString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTitleSprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTitleSprite* self = (CTitleSprite*)  tolua_tousertype(tolua_S,1,0);
  std::string text = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLabelString'", NULL);
#endif
  {
   self->SetLabelString(text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLabelString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CSpriteInSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CSpriteInSprite_new00
static int tolua_Dota_CSpriteInSprite_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CSpriteInSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CSpriteInSprite* tolua_ret = (CSpriteInSprite*)  Mtolua_new((CSpriteInSprite)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSpriteInSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CSpriteInSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CSpriteInSprite_new00_local
static int tolua_Dota_CSpriteInSprite_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CSpriteInSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CSpriteInSprite* tolua_ret = (CSpriteInSprite*)  Mtolua_new((CSpriteInSprite)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSpriteInSprite");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CSpriteInSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CSpriteInSprite_create00
static int tolua_Dota_CSpriteInSprite_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CSpriteInSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* OutterFilePath = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCSprite* innerSprite = ((CCSprite*)  tolua_tousertype(tolua_S,3,0));
  {
   CSpriteInSprite* tolua_ret = (CSpriteInSprite*)  CSpriteInSprite::create(OutterFilePath,innerSprite);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSpriteInSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CSpriteInSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CSpriteInSprite_init00
static int tolua_Dota_CSpriteInSprite_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSpriteInSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSpriteInSprite* self = (CSpriteInSprite*)  tolua_tousertype(tolua_S,1,0);
  const char* OutterFilePath = ((const char*)  tolua_tostring(tolua_S,2,0));
  CCSprite* innerSprite = ((CCSprite*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(OutterFilePath,innerSprite);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ChangeInnerImage of class  CSpriteInSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CSpriteInSprite_ChangeInnerImage00
static int tolua_Dota_CSpriteInSprite_ChangeInnerImage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSpriteInSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSpriteInSprite* self = (CSpriteInSprite*)  tolua_tousertype(tolua_S,1,0);
  const char* file = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ChangeInnerImage'", NULL);
#endif
  {
   self->ChangeInnerImage(file);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ChangeInnerImage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ChangeOutterImage of class  CSpriteInSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CSpriteInSprite_ChangeOutterImage00
static int tolua_Dota_CSpriteInSprite_ChangeOutterImage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CSpriteInSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CSpriteInSprite* self = (CSpriteInSprite*)  tolua_tousertype(tolua_S,1,0);
  const char* file = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ChangeOutterImage'", NULL);
#endif
  {
   self->ChangeOutterImage(file);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ChangeOutterImage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_pCell of class  TableViewSourceDelegate */
#ifndef TOLUA_DISABLE_tolua_get_TableViewSourceDelegate_m_pCell_ptr
static int tolua_get_TableViewSourceDelegate_m_pCell_ptr(lua_State* tolua_S)
{
  TableViewSourceDelegate* self = (TableViewSourceDelegate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_pCell'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->m_pCell,"CCTableViewCell");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_pCell of class  TableViewSourceDelegate */
#ifndef TOLUA_DISABLE_tolua_set_TableViewSourceDelegate_m_pCell_ptr
static int tolua_set_TableViewSourceDelegate_m_pCell_ptr(lua_State* tolua_S)
{
  TableViewSourceDelegate* self = (TableViewSourceDelegate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_pCell'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCTableViewCell",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_pCell = ((CCTableViewCell*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_nCellSize of class  TableViewSourceDelegate */
#ifndef TOLUA_DISABLE_tolua_get_TableViewSourceDelegate_m_nCellSize
static int tolua_get_TableViewSourceDelegate_m_nCellSize(lua_State* tolua_S)
{
  TableViewSourceDelegate* self = (TableViewSourceDelegate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_nCellSize'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->m_nCellSize,"CCSize");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_nCellSize of class  TableViewSourceDelegate */
#ifndef TOLUA_DISABLE_tolua_set_TableViewSourceDelegate_m_nCellSize
static int tolua_set_TableViewSourceDelegate_m_nCellSize(lua_State* tolua_S)
{
  TableViewSourceDelegate* self = (TableViewSourceDelegate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_nCellSize'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCSize",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_nCellSize = *((CCSize*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_nCellNumbers of class  TableViewSourceDelegate */
#ifndef TOLUA_DISABLE_tolua_get_TableViewSourceDelegate_m_nCellNumbers
static int tolua_get_TableViewSourceDelegate_m_nCellNumbers(lua_State* tolua_S)
{
  TableViewSourceDelegate* self = (TableViewSourceDelegate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_nCellNumbers'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_nCellNumbers);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_nCellNumbers of class  TableViewSourceDelegate */
#ifndef TOLUA_DISABLE_tolua_set_TableViewSourceDelegate_m_nCellNumbers
static int tolua_set_TableViewSourceDelegate_m_nCellNumbers(lua_State* tolua_S)
{
  TableViewSourceDelegate* self = (TableViewSourceDelegate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_nCellNumbers'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_nCellNumbers = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: tableCellSizeForIndex of class  TableViewSourceDelegate */
#ifndef TOLUA_DISABLE_tolua_Dota_TableViewSourceDelegate_tableCellSizeForIndex00
static int tolua_Dota_TableViewSourceDelegate_tableCellSizeForIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TableViewSourceDelegate",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTableView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TableViewSourceDelegate* self = (TableViewSourceDelegate*)  tolua_tousertype(tolua_S,1,0);
  CCTableView* table = ((CCTableView*)  tolua_tousertype(tolua_S,2,0));
  unsigned int idx = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tableCellSizeForIndex'", NULL);
#endif
  {
   CCSize tolua_ret = (CCSize)  self->tableCellSizeForIndex(table,idx);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCSize)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCSize));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tableCellSizeForIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: tableCellAtIndex of class  TableViewSourceDelegate */
#ifndef TOLUA_DISABLE_tolua_Dota_TableViewSourceDelegate_tableCellAtIndex00
static int tolua_Dota_TableViewSourceDelegate_tableCellAtIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TableViewSourceDelegate",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTableView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TableViewSourceDelegate* self = (TableViewSourceDelegate*)  tolua_tousertype(tolua_S,1,0);
  CCTableView* table = ((CCTableView*)  tolua_tousertype(tolua_S,2,0));
  unsigned int idx = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'tableCellAtIndex'", NULL);
#endif
  {
   CCTableViewCell* tolua_ret = (CCTableViewCell*)  self->tableCellAtIndex(table,idx);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCTableViewCell");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'tableCellAtIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: numberOfCellsInTableView of class  TableViewSourceDelegate */
#ifndef TOLUA_DISABLE_tolua_Dota_TableViewSourceDelegate_numberOfCellsInTableView00
static int tolua_Dota_TableViewSourceDelegate_numberOfCellsInTableView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TableViewSourceDelegate",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTableView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TableViewSourceDelegate* self = (TableViewSourceDelegate*)  tolua_tousertype(tolua_S,1,0);
  CCTableView* table = ((CCTableView*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'numberOfCellsInTableView'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->numberOfCellsInTableView(table);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'numberOfCellsInTableView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: scrollViewDidScroll of class  TableViewSourceDelegate */
#ifndef TOLUA_DISABLE_tolua_Dota_TableViewSourceDelegate_scrollViewDidScroll00
static int tolua_Dota_TableViewSourceDelegate_scrollViewDidScroll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TableViewSourceDelegate",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TableViewSourceDelegate* self = (TableViewSourceDelegate*)  tolua_tousertype(tolua_S,1,0);
  CCScrollView* view = ((CCScrollView*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'scrollViewDidScroll'", NULL);
#endif
  {
   self->scrollViewDidScroll(view);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'scrollViewDidScroll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerScript of class  TableViewSourceDelegate */
#ifndef TOLUA_DISABLE_tolua_Dota_TableViewSourceDelegate_registerScript00
static int tolua_Dota_TableViewSourceDelegate_registerScript00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TableViewSourceDelegate",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !toluafix_isfunction(tolua_S,4,"LUA_FUNCTION",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !toluafix_isfunction(tolua_S,5,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TableViewSourceDelegate* self = (TableViewSourceDelegate*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION cellSizeForIndex = (  toluafix_ref_function(tolua_S,2,0));
  LUA_FUNCTION tableCellAtIndex = (  toluafix_ref_function(tolua_S,3,0));
  LUA_FUNCTION numberOfCellsInTableView = (  toluafix_ref_function(tolua_S,4,0));
  LUA_FUNCTION scrollViewDidScroll = (  toluafix_ref_function(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerScript'", NULL);
#endif
  {
   self->registerScript(cellSizeForIndex,tableCellAtIndex,numberOfCellsInTableView,scrollViewDidScroll);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerScript'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCTableViewDelegate__ of class  TableViewSourceDelegate */
#ifndef TOLUA_DISABLE_tolua_get_TableViewSourceDelegate___CCTableViewDelegate__
static int tolua_get_TableViewSourceDelegate___CCTableViewDelegate__(lua_State* tolua_S)
{
  TableViewSourceDelegate* self = (TableViewSourceDelegate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCTableViewDelegate__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCTableViewDelegate*>(self), "CCTableViewDelegate");
#else
   tolua_pushusertype(tolua_S,(void*)((CCTableViewDelegate*)self), "CCTableViewDelegate");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CTableView */
#ifndef TOLUA_DISABLE_tolua_Dota_CTableView_new00
static int tolua_Dota_CTableView_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CTableView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CTableView* tolua_ret = (CTableView*)  Mtolua_new((CTableView)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTableView");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CTableView */
#ifndef TOLUA_DISABLE_tolua_Dota_CTableView_new00_local
static int tolua_Dota_CTableView_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CTableView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CTableView* tolua_ret = (CTableView*)  Mtolua_new((CTableView)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTableView");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CTableView */
#ifndef TOLUA_DISABLE_tolua_Dota_CTableView_delete00
static int tolua_Dota_CTableView_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTableView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTableView* self = (CTableView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CTableView */
#ifndef TOLUA_DISABLE_tolua_Dota_CTableView_create00
static int tolua_Dota_CTableView_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CTableView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTableViewDataSource",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCSize",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableViewDataSource* dataSource = ((CCTableViewDataSource*)  tolua_tousertype(tolua_S,2,0));
  CCSize size = *((CCSize*)  tolua_tousertype(tolua_S,3,0));
  int priority = ((int)  tolua_tonumber(tolua_S,4,0));
  bool swallow = ((bool)  tolua_toboolean(tolua_S,5,true));
  {
   CTableView* tolua_ret = (CTableView*)  CTableView::create(dataSource,size,priority,swallow);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTableView");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CTableView */
#ifndef TOLUA_DISABLE_tolua_Dota_CTableView_init00
static int tolua_Dota_CTableView_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTableView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTableViewDataSource",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCSize",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTableView* self = (CTableView*)  tolua_tousertype(tolua_S,1,0);
  CCTableViewDataSource* dataSource = ((CCTableViewDataSource*)  tolua_tousertype(tolua_S,2,0));
  CCSize size = *((CCSize*)  tolua_tousertype(tolua_S,3,0));
  int priority = ((int)  tolua_tonumber(tolua_S,4,0));
  bool swallow = ((bool)  tolua_toboolean(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(dataSource,size,priority,swallow);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerWithTouchDispatcher of class  CTableView */
#ifndef TOLUA_DISABLE_tolua_Dota_CTableView_registerWithTouchDispatcher00
static int tolua_Dota_CTableView_registerWithTouchDispatcher00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTableView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTableView* self = (CTableView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerWithTouchDispatcher'", NULL);
#endif
  {
   self->registerWithTouchDispatcher();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerWithTouchDispatcher'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPriority of class  CTableView */
#ifndef TOLUA_DISABLE_tolua_Dota_CTableView_getPriority00
static int tolua_Dota_CTableView_getPriority00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CTableView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CTableView* self = (const CTableView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPriority'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getPriority();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPriority'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMyDelegate of class  CTableView */
#ifndef TOLUA_DISABLE_tolua_Dota_CTableView_getMyDelegate00
static int tolua_Dota_CTableView_getMyDelegate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTableView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTableView* self = (CTableView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMyDelegate'", NULL);
#endif
  {
   TableViewSourceDelegate* tolua_ret = (TableViewSourceDelegate*)  self->getMyDelegate();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TableViewSourceDelegate");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMyDelegate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CScrollView */
#ifndef TOLUA_DISABLE_tolua_Dota_CScrollView_new00
static int tolua_Dota_CScrollView_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CScrollView* tolua_ret = (CScrollView*)  Mtolua_new((CScrollView)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CScrollView");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CScrollView */
#ifndef TOLUA_DISABLE_tolua_Dota_CScrollView_new00_local
static int tolua_Dota_CScrollView_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CScrollView* tolua_ret = (CScrollView*)  Mtolua_new((CScrollView)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CScrollView");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CScrollView */
#ifndef TOLUA_DISABLE_tolua_Dota_CScrollView_delete00
static int tolua_Dota_CScrollView_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CScrollView* self = (CScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CScrollView */
#ifndef TOLUA_DISABLE_tolua_Dota_CScrollView_create00
static int tolua_Dota_CScrollView_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int priority = ((int)  tolua_tonumber(tolua_S,2,0));
  bool swallow = ((bool)  tolua_toboolean(tolua_S,3,true));
  {
   CScrollView* tolua_ret = (CScrollView*)  CScrollView::create(priority,swallow);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CScrollView");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  CScrollView */
#ifndef TOLUA_DISABLE_tolua_Dota_CScrollView_init00
static int tolua_Dota_CScrollView_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CScrollView* self = (CScrollView*)  tolua_tousertype(tolua_S,1,0);
  int priority = ((int)  tolua_tonumber(tolua_S,2,0));
  bool swallow = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(priority,swallow);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerWithTouchDispatcher of class  CScrollView */
#ifndef TOLUA_DISABLE_tolua_Dota_CScrollView_registerWithTouchDispatcher00
static int tolua_Dota_CScrollView_registerWithTouchDispatcher00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CScrollView* self = (CScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerWithTouchDispatcher'", NULL);
#endif
  {
   self->registerWithTouchDispatcher();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerWithTouchDispatcher'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPriority of class  CScrollView */
#ifndef TOLUA_DISABLE_tolua_Dota_CScrollView_getPriority00
static int tolua_Dota_CScrollView_getPriority00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CScrollView* self = (const CScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPriority'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getPriority();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPriority'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addText of class  CScrollView */
#ifndef TOLUA_DISABLE_tolua_Dota_CScrollView_addText00
static int tolua_Dota_CScrollView_addText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CScrollView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CScrollView* self = (CScrollView*)  tolua_tousertype(tolua_S,1,0);
  CCNode* content = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addText'", NULL);
#endif
  {
   self->addText(content);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resizeContent of class  CScrollView */
#ifndef TOLUA_DISABLE_tolua_Dota_CScrollView_resizeContent00
static int tolua_Dota_CScrollView_resizeContent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CScrollView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CScrollView* self = (CScrollView*)  tolua_tousertype(tolua_S,1,0);
  CCNode* content = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resizeContent'", NULL);
#endif
  {
   self->resizeContent(content);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resizeContent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CMapScrollView */
#ifndef TOLUA_DISABLE_tolua_Dota_CMapScrollView_new00
static int tolua_Dota_CMapScrollView_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMapScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CMapScrollView* tolua_ret = (CMapScrollView*)  Mtolua_new((CMapScrollView)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMapScrollView");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CMapScrollView */
#ifndef TOLUA_DISABLE_tolua_Dota_CMapScrollView_new00_local
static int tolua_Dota_CMapScrollView_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMapScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CMapScrollView* tolua_ret = (CMapScrollView*)  Mtolua_new((CMapScrollView)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMapScrollView");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CMapScrollView */
#ifndef TOLUA_DISABLE_tolua_Dota_CMapScrollView_delete00
static int tolua_Dota_CMapScrollView_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMapScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMapScrollView* self = (CMapScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CMapScrollView */
#ifndef TOLUA_DISABLE_tolua_Dota_CMapScrollView_create00
static int tolua_Dota_CMapScrollView_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CMapScrollView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCSize* sz = ((const CCSize*)  tolua_tousertype(tolua_S,2,0));
  int priority = ((int)  tolua_tonumber(tolua_S,3,0));
  bool swallow = ((bool)  tolua_toboolean(tolua_S,4,true));
  {
   CMapScrollView* tolua_ret = (CMapScrollView*)  CMapScrollView::create(*sz,priority,swallow);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMapScrollView");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithViewSize of class  CMapScrollView */
#ifndef TOLUA_DISABLE_tolua_Dota_CMapScrollView_initWithViewSize00
static int tolua_Dota_CMapScrollView_initWithViewSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMapScrollView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCSize",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMapScrollView* self = (CMapScrollView*)  tolua_tousertype(tolua_S,1,0);
  const CCSize* sz = ((const CCSize*)  tolua_tousertype(tolua_S,2,0));
  int priority = ((int)  tolua_tonumber(tolua_S,3,0));
  bool swallow = ((bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithViewSize'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithViewSize(*sz,priority,swallow);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithViewSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerWithTouchDispatcher of class  CMapScrollView */
#ifndef TOLUA_DISABLE_tolua_Dota_CMapScrollView_registerWithTouchDispatcher00
static int tolua_Dota_CMapScrollView_registerWithTouchDispatcher00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMapScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMapScrollView* self = (CMapScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerWithTouchDispatcher'", NULL);
#endif
  {
   self->registerWithTouchDispatcher();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerWithTouchDispatcher'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPriority of class  CMapScrollView */
#ifndef TOLUA_DISABLE_tolua_Dota_CMapScrollView_getPriority00
static int tolua_Dota_CMapScrollView_getPriority00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CMapScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CMapScrollView* self = (const CMapScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPriority'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getPriority();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPriority'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getChildByTag of class  CMapScrollView */
#ifndef TOLUA_DISABLE_tolua_Dota_CMapScrollView_getChildByTag00
static int tolua_Dota_CMapScrollView_getChildByTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMapScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMapScrollView* self = (CMapScrollView*)  tolua_tousertype(tolua_S,1,0);
  int aTag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getChildByTag'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getChildByTag(aTag);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getChildByTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CTeamIconProgress */
#ifndef TOLUA_DISABLE_tolua_Dota_CTeamIconProgress_new00
static int tolua_Dota_CTeamIconProgress_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CTeamIconProgress",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CTeamIconProgress* tolua_ret = (CTeamIconProgress*)  Mtolua_new((CTeamIconProgress)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTeamIconProgress");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CTeamIconProgress */
#ifndef TOLUA_DISABLE_tolua_Dota_CTeamIconProgress_new00_local
static int tolua_Dota_CTeamIconProgress_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CTeamIconProgress",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CTeamIconProgress* tolua_ret = (CTeamIconProgress*)  Mtolua_new((CTeamIconProgress)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTeamIconProgress");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CTeamIconProgress */
#ifndef TOLUA_DISABLE_tolua_Dota_CTeamIconProgress_delete00
static int tolua_Dota_CTeamIconProgress_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTeamIconProgress",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTeamIconProgress* self = (CTeamIconProgress*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createTeamIconProgress of class  CTeamIconProgress */
#ifndef TOLUA_DISABLE_tolua_Dota_CTeamIconProgress_createTeamIconProgress00
static int tolua_Dota_CTeamIconProgress_createTeamIconProgress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CTeamIconProgress",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string normalFile = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  std::string grapFile = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  float finterDistance = ((float)  tolua_tonumber(tolua_S,4,0));
  bool isFlipX = ((bool)  tolua_toboolean(tolua_S,5,false));
  int defualtCount = ((int)  tolua_tonumber(tolua_S,6,3));
  {
   CTeamIconProgress* tolua_ret = (CTeamIconProgress*)  CTeamIconProgress::createTeamIconProgress(normalFile,grapFile,finterDistance,isFlipX,defualtCount);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTeamIconProgress");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createTeamIconProgress'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resetProgress of class  CTeamIconProgress */
#ifndef TOLUA_DISABLE_tolua_Dota_CTeamIconProgress_resetProgress00
static int tolua_Dota_CTeamIconProgress_resetProgress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTeamIconProgress",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTeamIconProgress* self = (CTeamIconProgress*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resetProgress'", NULL);
#endif
  {
   self->resetProgress();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resetProgress'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reduceActiveCount of class  CTeamIconProgress */
#ifndef TOLUA_DISABLE_tolua_Dota_CTeamIconProgress_reduceActiveCount00
static int tolua_Dota_CTeamIconProgress_reduceActiveCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTeamIconProgress",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTeamIconProgress* self = (CTeamIconProgress*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reduceActiveCount'", NULL);
#endif
  {
   self->reduceActiveCount();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reduceActiveCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setActiveCount of class  CTeamIconProgress */
#ifndef TOLUA_DISABLE_tolua_Dota_CTeamIconProgress_setActiveCount00
static int tolua_Dota_CTeamIconProgress_setActiveCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTeamIconProgress",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTeamIconProgress* self = (CTeamIconProgress*)  tolua_tousertype(tolua_S,1,0);
  int activeCount = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setActiveCount'", NULL);
#endif
  {
   self->setActiveCount(activeCount);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setActiveCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unActiveAllProgress of class  CTeamIconProgress */
#ifndef TOLUA_DISABLE_tolua_Dota_CTeamIconProgress_unActiveAllProgress00
static int tolua_Dota_CTeamIconProgress_unActiveAllProgress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTeamIconProgress",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTeamIconProgress* self = (CTeamIconProgress*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unActiveAllProgress'", NULL);
#endif
  {
   self->unActiveAllProgress();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unActiveAllProgress'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TimerEventHandler of class  CTimerEventProtocol */
#ifndef TOLUA_DISABLE_tolua_Dota_CTimerEventProtocol_TimerEventHandler00
static int tolua_Dota_CTimerEventProtocol_TimerEventHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTimerEventProtocol",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTimerEventProtocol* self = (CTimerEventProtocol*)  tolua_tousertype(tolua_S,1,0);
  int eventType = ((int)  tolua_tonumber(tolua_S,2,0));
  std::string attachParam = ((std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TimerEventHandler'", NULL);
#endif
  {
   self->TimerEventHandler(eventType,attachParam);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TimerEventHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateWithTimeType of class  CTimeLabel */
#ifndef TOLUA_DISABLE_tolua_Dota_CTimeLabel_CreateWithTimeType00
static int tolua_Dota_CTimeLabel_CreateWithTimeType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CTimeLabel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"IByte",0,&tolua_err)) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IByte timeType = *((IByte*)  tolua_tousertype(tolua_S,2,0));
  std::string formatTemplate = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  {
   CTimeLabel* tolua_ret = (CTimeLabel*)  CTimeLabel::CreateWithTimeType(timeType,formatTemplate);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTimeLabel");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateWithTimeType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateWithTimeType of class  CTimeLabel */
#ifndef TOLUA_DISABLE_tolua_Dota_CTimeLabel_CreateWithTimeType01
static int tolua_Dota_CTimeLabel_CreateWithTimeType01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CTimeLabel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"IByte",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  IByte timeType = *((IByte*)  tolua_tousertype(tolua_S,2,0));
  {
   CTimeLabel* tolua_ret = (CTimeLabel*)  CTimeLabel::CreateWithTimeType(timeType);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTimeLabel");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Dota_CTimeLabel_CreateWithTimeType00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: StartTimer of class  CTimeLabel */
#ifndef TOLUA_DISABLE_tolua_Dota_CTimeLabel_StartTimer00
static int tolua_Dota_CTimeLabel_StartTimer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTimeLabel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTimeLabel* self = (CTimeLabel*)  tolua_tousertype(tolua_S,1,0);
  int distanceTime = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StartTimer'", NULL);
#endif
  {
   self->StartTimer(distanceTime);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StartTimer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: StartTimer of class  CTimeLabel */
#ifndef TOLUA_DISABLE_tolua_Dota_CTimeLabel_StartTimer01
static int tolua_Dota_CTimeLabel_StartTimer01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTimeLabel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CTimeLabel* self = (CTimeLabel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StartTimer'", NULL);
#endif
  {
   self->StartTimer();
  }
 }
 return 0;
tolua_lerror:
 return tolua_Dota_CTimeLabel_StartTimer00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: StartActivityMiniteTimer of class  CTimeLabel */
#ifndef TOLUA_DISABLE_tolua_Dota_CTimeLabel_StartActivityMiniteTimer00
static int tolua_Dota_CTimeLabel_StartActivityMiniteTimer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTimeLabel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTimeLabel* self = (CTimeLabel*)  tolua_tousertype(tolua_S,1,0);
  int minuteDistance = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StartActivityMiniteTimer'", NULL);
#endif
  {
   self->StartActivityMiniteTimer(minuteDistance);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StartActivityMiniteTimer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: StopTimer of class  CTimeLabel */
#ifndef TOLUA_DISABLE_tolua_Dota_CTimeLabel_StopTimer00
static int tolua_Dota_CTimeLabel_StopTimer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTimeLabel",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTimeLabel* self = (CTimeLabel*)  tolua_tousertype(tolua_S,1,0);
  bool bToInit = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StopTimer'", NULL);
#endif
  {
   self->StopTimer(bToInit);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StopTimer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rangeTouched of class  CTouchSpriteDelegate */
#ifndef TOLUA_DISABLE_tolua_Dota_CTouchSpriteDelegate_rangeTouched00
static int tolua_Dota_CTouchSpriteDelegate_rangeTouched00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTouchSpriteDelegate",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTouchSpriteDelegate* self = (CTouchSpriteDelegate*)  tolua_tousertype(tolua_S,1,0);
  CCObject* pSender = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rangeTouched'", NULL);
#endif
  {
   self->rangeTouched(pSender);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rangeTouched'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  CTouchSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CTouchSprite_new00
static int tolua_Dota_CTouchSprite_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CTouchSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CTouchSprite* tolua_ret = (CTouchSprite*)  Mtolua_new((CTouchSprite)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTouchSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  CTouchSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CTouchSprite_new00_local
static int tolua_Dota_CTouchSprite_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CTouchSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CTouchSprite* tolua_ret = (CTouchSprite*)  Mtolua_new((CTouchSprite)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTouchSprite");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  CTouchSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CTouchSprite_delete00
static int tolua_Dota_CTouchSprite_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTouchSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTouchSprite* self = (CTouchSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CTouchSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CTouchSprite_create00
static int tolua_Dota_CTouchSprite_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CTouchSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CTouchSpriteDelegate",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  CTouchSpriteDelegate* delegate = ((CTouchSpriteDelegate*)  tolua_tousertype(tolua_S,3,0));
  int priority = ((int)  tolua_tonumber(tolua_S,4,0));
  bool swallow = ((bool)  tolua_toboolean(tolua_S,5,true));
  {
   CTouchSprite* tolua_ret = (CTouchSprite*)  CTouchSprite::create(filename,delegate,priority,swallow);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CTouchSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithFile of class  CTouchSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CTouchSprite_initWithFile00
static int tolua_Dota_CTouchSprite_initWithFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTouchSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CTouchSpriteDelegate",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTouchSprite* self = (CTouchSprite*)  tolua_tousertype(tolua_S,1,0);
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  CTouchSpriteDelegate* delegate = ((CTouchSpriteDelegate*)  tolua_tousertype(tolua_S,3,0));
  int priority = ((int)  tolua_tonumber(tolua_S,4,0));
  bool swallow = ((bool)  tolua_toboolean(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithFile'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithFile(filename,delegate,priority,swallow);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDelegate of class  CTouchSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CTouchSprite_setDelegate00
static int tolua_Dota_CTouchSprite_setDelegate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTouchSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CTouchSpriteDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTouchSprite* self = (CTouchSprite*)  tolua_tousertype(tolua_S,1,0);
  CTouchSpriteDelegate* del = ((CTouchSpriteDelegate*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDelegate'", NULL);
#endif
  {
   self->setDelegate(del);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDelegate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIDX of class  CTouchSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CTouchSprite_setIDX00
static int tolua_Dota_CTouchSprite_setIDX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTouchSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTouchSprite* self = (CTouchSprite*)  tolua_tousertype(tolua_S,1,0);
  int idx = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIDX'", NULL);
#endif
  {
   self->setIDX(idx);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIDX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIDX of class  CTouchSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CTouchSprite_getIDX00
static int tolua_Dota_CTouchSprite_getIDX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CTouchSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CTouchSprite* self = (const CTouchSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIDX'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getIDX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIDX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSoundID of class  CTouchSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_CTouchSprite_setSoundID00
static int tolua_Dota_CTouchSprite_setSoundID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CTouchSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CTouchSprite* self = (CTouchSprite*)  tolua_tousertype(tolua_S,1,0);
  int soundid = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSoundID'", NULL);
#endif
  {
   self->setSoundID(soundid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSoundID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCTargetedTouchDelegate__ of class  CTouchSprite */
#ifndef TOLUA_DISABLE_tolua_get_CTouchSprite___CCTargetedTouchDelegate__
static int tolua_get_CTouchSprite___CCTargetedTouchDelegate__(lua_State* tolua_S)
{
  CTouchSprite* self = (CTouchSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCTargetedTouchDelegate__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCTargetedTouchDelegate*>(self), "CCTargetedTouchDelegate");
#else
   tolua_pushusertype(tolua_S,(void*)((CCTargetedTouchDelegate*)self), "CCTargetedTouchDelegate");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  FAnimationButton */
#ifndef TOLUA_DISABLE_tolua_Dota_FAnimationButton_new00
static int tolua_Dota_FAnimationButton_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"FAnimationButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   FAnimationButton* tolua_ret = (FAnimationButton*)  Mtolua_new((FAnimationButton)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"FAnimationButton");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  FAnimationButton */
#ifndef TOLUA_DISABLE_tolua_Dota_FAnimationButton_new00_local
static int tolua_Dota_FAnimationButton_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"FAnimationButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   FAnimationButton* tolua_ret = (FAnimationButton*)  Mtolua_new((FAnimationButton)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"FAnimationButton");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  FAnimationButton */
#ifndef TOLUA_DISABLE_tolua_Dota_FAnimationButton_delete00
static int tolua_Dota_FAnimationButton_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FAnimationButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FAnimationButton* self = (FAnimationButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  FAnimationButton */
#ifndef TOLUA_DISABLE_tolua_Dota_FAnimationButton_create00
static int tolua_Dota_FAnimationButton_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"FAnimationButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"SEL_MenuHandler",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* normalSprite = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  CCNode* selectedSprite = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
  CCObject* target = ((CCObject*)  tolua_tousertype(tolua_S,4,0));
  SEL_MenuHandler selector = *((SEL_MenuHandler*)  tolua_tousertype(tolua_S,5,0));
  {
   FAnimationButton* tolua_ret = (FAnimationButton*)  FAnimationButton::create(normalSprite,selectedSprite,target,selector);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"FAnimationButton");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithNormalSprite of class  FAnimationButton */
#ifndef TOLUA_DISABLE_tolua_Dota_FAnimationButton_initWithNormalSprite00
static int tolua_Dota_FAnimationButton_initWithNormalSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FAnimationButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"CCObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,6,&tolua_err) || !tolua_isusertype(tolua_S,6,"SEL_MenuHandler",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FAnimationButton* self = (FAnimationButton*)  tolua_tousertype(tolua_S,1,0);
  CCNode* normalSprite = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  CCNode* selectedSprite = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
  CCNode* disabledSprite = ((CCNode*)  tolua_tousertype(tolua_S,4,0));
  CCObject* target = ((CCObject*)  tolua_tousertype(tolua_S,5,0));
  SEL_MenuHandler selector = *((SEL_MenuHandler*)  tolua_tousertype(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithNormalSprite'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithNormalSprite(normalSprite,selectedSprite,disabledSprite,target,selector);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithNormalSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  FAnimationButton */
#ifndef TOLUA_DISABLE_tolua_Dota_FAnimationButton_create01
static int tolua_Dota_FAnimationButton_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"FAnimationButton",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"SEL_MenuHandler",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* nor = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* sel = ((const char*)  tolua_tostring(tolua_S,3,0));
  CCObject* target = ((CCObject*)  tolua_tousertype(tolua_S,4,0));
  SEL_MenuHandler selector = *((SEL_MenuHandler*)  tolua_tousertype(tolua_S,5,0));
  {
   FAnimationButton* tolua_ret = (FAnimationButton*)  FAnimationButton::create(nor,sel,target,selector);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"FAnimationButton");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Dota_FAnimationButton_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithNormalImage of class  FAnimationButton */
#ifndef TOLUA_DISABLE_tolua_Dota_FAnimationButton_initWithNormalImage00
static int tolua_Dota_FAnimationButton_initWithNormalImage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FAnimationButton",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"SEL_MenuHandler",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FAnimationButton* self = (FAnimationButton*)  tolua_tousertype(tolua_S,1,0);
  const char* nor = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* sel = ((const char*)  tolua_tostring(tolua_S,3,0));
  CCObject* target = ((CCObject*)  tolua_tousertype(tolua_S,4,0));
  SEL_MenuHandler selector = *((SEL_MenuHandler*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithNormalImage'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithNormalImage(nor,sel,target,selector);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithNormalImage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIDX of class  FAnimationButton */
#ifndef TOLUA_DISABLE_tolua_Dota_FAnimationButton_setIDX00
static int tolua_Dota_FAnimationButton_setIDX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FAnimationButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FAnimationButton* self = (FAnimationButton*)  tolua_tousertype(tolua_S,1,0);
  unsigned int idx = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIDX'", NULL);
#endif
  {
   self->setIDX(idx);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIDX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIDX of class  FAnimationButton */
#ifndef TOLUA_DISABLE_tolua_Dota_FAnimationButton_getIDX00
static int tolua_Dota_FAnimationButton_getIDX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const FAnimationButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const FAnimationButton* self = (const FAnimationButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIDX'", NULL);
#endif
  {
   unsigned int tolua_ret = (unsigned int)  self->getIDX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIDX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSoundID of class  FAnimationButton */
#ifndef TOLUA_DISABLE_tolua_Dota_FAnimationButton_setSoundID00
static int tolua_Dota_FAnimationButton_setSoundID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FAnimationButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FAnimationButton* self = (FAnimationButton*)  tolua_tousertype(tolua_S,1,0);
  int soundid = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSoundID'", NULL);
#endif
  {
   self->setSoundID(soundid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSoundID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnimationId of class  FAnimationButton */
#ifndef TOLUA_DISABLE_tolua_Dota_FAnimationButton_setAnimationId00
static int tolua_Dota_FAnimationButton_setAnimationId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FAnimationButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FAnimationButton* self = (FAnimationButton*)  tolua_tousertype(tolua_S,1,0);
  int animationId = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnimationId'", NULL);
#endif
  {
   self->setAnimationId(animationId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnimationId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnimationPos of class  FAnimationButton */
#ifndef TOLUA_DISABLE_tolua_Dota_FAnimationButton_setAnimationPos00
static int tolua_Dota_FAnimationButton_setAnimationPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FAnimationButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FAnimationButton* self = (FAnimationButton*)  tolua_tousertype(tolua_S,1,0);
  float posx = ((float)  tolua_tonumber(tolua_S,2,0));
  float posy = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnimationPos'", NULL);
#endif
  {
   self->setAnimationPos(posx,posy);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnimationPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnimationCallBack of class  FAnimationButton */
#ifndef TOLUA_DISABLE_tolua_Dota_FAnimationButton_setAnimationCallBack00
static int tolua_Dota_FAnimationButton_setAnimationCallBack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FAnimationButton",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"AnimationEffectCallBackProtocol",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FAnimationButton* self = (FAnimationButton*)  tolua_tousertype(tolua_S,1,0);
  AnimationEffectCallBackProtocol* callbackObject = ((AnimationEffectCallBackProtocol*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnimationCallBack'", NULL);
#endif
  {
   self->setAnimationCallBack(callbackObject);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnimationCallBack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: EffectCallBackEventHandler of class  FAnimationButton */
#ifndef TOLUA_DISABLE_tolua_Dota_FAnimationButton_EffectCallBackEventHandler00
static int tolua_Dota_FAnimationButton_EffectCallBackEventHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FAnimationButton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"PCallBack_Node",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FAnimationButton* self = (FAnimationButton*)  tolua_tousertype(tolua_S,1,0);
  int eventType = ((int)  tolua_tonumber(tolua_S,2,0));
  CCNode* animationNode = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
  PCallBack_Node ptr = *((PCallBack_Node*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'EffectCallBackEventHandler'", NULL);
#endif
  {
   self->EffectCallBackEventHandler(eventType,animationNode,ptr);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EffectCallBackEventHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PlayAnimation of class  FAnimationButton */
#ifndef TOLUA_DISABLE_tolua_Dota_FAnimationButton_PlayAnimation00
static int tolua_Dota_FAnimationButton_PlayAnimation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FAnimationButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FAnimationButton* self = (FAnimationButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PlayAnimation'", NULL);
#endif
  {
   self->PlayAnimation();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PlayAnimation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: StopAnimation of class  FAnimationButton */
#ifndef TOLUA_DISABLE_tolua_Dota_FAnimationButton_StopAnimation00
static int tolua_Dota_FAnimationButton_StopAnimation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FAnimationButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FAnimationButton* self = (FAnimationButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StopAnimation'", NULL);
#endif
  {
   self->StopAnimation();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StopAnimation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PlayTouchSound of class  FAnimationButton */
#ifndef TOLUA_DISABLE_tolua_Dota_FAnimationButton_PlayTouchSound00
static int tolua_Dota_FAnimationButton_PlayTouchSound00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FAnimationButton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FAnimationButton* self = (FAnimationButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PlayTouchSound'", NULL);
#endif
  {
   self->PlayTouchSound();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PlayTouchSound'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __AnimationEffectCallBackProtocol__ of class  FAnimationButton */
#ifndef TOLUA_DISABLE_tolua_get_FAnimationButton___AnimationEffectCallBackProtocol__
static int tolua_get_FAnimationButton___AnimationEffectCallBackProtocol__(lua_State* tolua_S)
{
  FAnimationButton* self = (FAnimationButton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__AnimationEffectCallBackProtocol__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<AnimationEffectCallBackProtocol*>(self), "AnimationEffectCallBackProtocol");
#else
   tolua_pushusertype(tolua_S,(void*)((AnimationEffectCallBackProtocol*)self), "AnimationEffectCallBackProtocol");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  FAPriorityMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_FAPriorityMenu_new00
static int tolua_Dota_FAPriorityMenu_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"FAPriorityMenu",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   FAPriorityMenu* tolua_ret = (FAPriorityMenu*)  Mtolua_new((FAPriorityMenu)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"FAPriorityMenu");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  FAPriorityMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_FAPriorityMenu_new00_local
static int tolua_Dota_FAPriorityMenu_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"FAPriorityMenu",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   FAPriorityMenu* tolua_ret = (FAPriorityMenu*)  Mtolua_new((FAPriorityMenu)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"FAPriorityMenu");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  FAPriorityMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_FAPriorityMenu_create00
static int tolua_Dota_FAPriorityMenu_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"FAPriorityMenu",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int priority = ((int)  tolua_tonumber(tolua_S,2,0));
  bool swallow = ((bool)  tolua_toboolean(tolua_S,3,true));
  {
   FAPriorityMenu* tolua_ret = (FAPriorityMenu*)  FAPriorityMenu::create(priority,swallow);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"FAPriorityMenu");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  FAPriorityMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_FAPriorityMenu_init00
static int tolua_Dota_FAPriorityMenu_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FAPriorityMenu",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FAPriorityMenu* self = (FAPriorityMenu*)  tolua_tousertype(tolua_S,1,0);
  int priority = ((int)  tolua_tonumber(tolua_S,2,0));
  bool swallow = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(priority,swallow);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerWithTouchDispatcher of class  FAPriorityMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_FAPriorityMenu_registerWithTouchDispatcher00
static int tolua_Dota_FAPriorityMenu_registerWithTouchDispatcher00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FAPriorityMenu",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FAPriorityMenu* self = (FAPriorityMenu*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerWithTouchDispatcher'", NULL);
#endif
  {
   self->registerWithTouchDispatcher();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerWithTouchDispatcher'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchBegan of class  FAPriorityMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_FAPriorityMenu_ccTouchBegan00
static int tolua_Dota_FAPriorityMenu_ccTouchBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FAPriorityMenu",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FAPriorityMenu* self = (FAPriorityMenu*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* event = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchBegan'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ccTouchBegan(touch,event);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchBegan'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchEnded of class  FAPriorityMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_FAPriorityMenu_ccTouchEnded00
static int tolua_Dota_FAPriorityMenu_ccTouchEnded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FAPriorityMenu",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FAPriorityMenu* self = (FAPriorityMenu*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* event = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchEnded'", NULL);
#endif
  {
   self->ccTouchEnded(touch,event);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchEnded'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchMoved of class  FAPriorityMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_FAPriorityMenu_ccTouchMoved00
static int tolua_Dota_FAPriorityMenu_ccTouchMoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FAPriorityMenu",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FAPriorityMenu* self = (FAPriorityMenu*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* event = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchMoved'", NULL);
#endif
  {
   self->ccTouchMoved(touch,event);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchMoved'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchCancelled of class  FAPriorityMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_FAPriorityMenu_ccTouchCancelled00
static int tolua_Dota_FAPriorityMenu_ccTouchCancelled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FAPriorityMenu",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FAPriorityMenu* self = (FAPriorityMenu*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* event = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchCancelled'", NULL);
#endif
  {
   self->ccTouchCancelled(touch,event);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchCancelled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTreatAsTabMenu of class  FAPriorityMenu */
#ifndef TOLUA_DISABLE_tolua_Dota_FAPriorityMenu_SetTreatAsTabMenu00
static int tolua_Dota_FAPriorityMenu_SetTreatAsTabMenu00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FAPriorityMenu",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FAPriorityMenu* self = (FAPriorityMenu*)  tolua_tousertype(tolua_S,1,0);
  bool treat = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTreatAsTabMenu'", NULL);
#endif
  {
   self->SetTreatAsTabMenu(treat);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTreatAsTabMenu'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FrameAnimationIntercept of class  FrameAnimationDelegate */
#ifndef TOLUA_DISABLE_tolua_Dota_FrameAnimationDelegate_FrameAnimationIntercept00
static int tolua_Dota_FrameAnimationDelegate_FrameAnimationIntercept00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FrameAnimationDelegate",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FrameAnimationDelegate* self = (FrameAnimationDelegate*)  tolua_tousertype(tolua_S,1,0);
  int frameId = ((int)  tolua_tonumber(tolua_S,2,0));
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FrameAnimationIntercept'", NULL);
#endif
  {
   self->FrameAnimationIntercept(frameId,node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FrameAnimationIntercept'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  FrameAnimationNode */
#ifndef TOLUA_DISABLE_tolua_Dota_FrameAnimationNode_create00
static int tolua_Dota_FrameAnimationNode_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"FrameAnimationNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int totalFrames = ((int)  tolua_tonumber(tolua_S,2,0));
  int fpsInAnimation = ((int)  tolua_tonumber(tolua_S,3,0));
  int fpsInGame = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   FrameAnimationNode* tolua_ret = (FrameAnimationNode*)  FrameAnimationNode::create(totalFrames,fpsInAnimation,fpsInGame);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"FrameAnimationNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InsertFrameIntercept of class  FrameAnimationNode */
#ifndef TOLUA_DISABLE_tolua_Dota_FrameAnimationNode_InsertFrameIntercept00
static int tolua_Dota_FrameAnimationNode_InsertFrameIntercept00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FrameAnimationNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FrameAnimationNode* self = (FrameAnimationNode*)  tolua_tousertype(tolua_S,1,0);
  int frameId = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InsertFrameIntercept'", NULL);
#endif
  {
   self->InsertFrameIntercept(frameId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InsertFrameIntercept'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ClearAllIntercepts of class  FrameAnimationNode */
#ifndef TOLUA_DISABLE_tolua_Dota_FrameAnimationNode_ClearAllIntercepts00
static int tolua_Dota_FrameAnimationNode_ClearAllIntercepts00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FrameAnimationNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FrameAnimationNode* self = (FrameAnimationNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ClearAllIntercepts'", NULL);
#endif
  {
   self->ClearAllIntercepts();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ClearAllIntercepts'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddDelegate of class  FrameAnimationNode */
#ifndef TOLUA_DISABLE_tolua_Dota_FrameAnimationNode_AddDelegate00
static int tolua_Dota_FrameAnimationNode_AddDelegate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FrameAnimationNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"FrameAnimationDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FrameAnimationNode* self = (FrameAnimationNode*)  tolua_tousertype(tolua_S,1,0);
  FrameAnimationDelegate* dlg = ((FrameAnimationDelegate*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddDelegate'", NULL);
#endif
  {
   self->AddDelegate(dlg);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddDelegate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Tick of class  FrameAnimationNode */
#ifndef TOLUA_DISABLE_tolua_Dota_FrameAnimationNode_Tick00
static int tolua_Dota_FrameAnimationNode_Tick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FrameAnimationNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FrameAnimationNode* self = (FrameAnimationNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Tick'", NULL);
#endif
  {
   self->Tick();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Tick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Start of class  FrameAnimationNode */
#ifndef TOLUA_DISABLE_tolua_Dota_FrameAnimationNode_Start00
static int tolua_Dota_FrameAnimationNode_Start00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FrameAnimationNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FrameAnimationNode* self = (FrameAnimationNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Start'", NULL);
#endif
  {
   self->Start();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Start'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  GrapStarsProgress */
#ifndef TOLUA_DISABLE_tolua_Dota_GrapStarsProgress_new00
static int tolua_Dota_GrapStarsProgress_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GrapStarsProgress",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GrapStarsProgress* tolua_ret = (GrapStarsProgress*)  Mtolua_new((GrapStarsProgress)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GrapStarsProgress");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  GrapStarsProgress */
#ifndef TOLUA_DISABLE_tolua_Dota_GrapStarsProgress_new00_local
static int tolua_Dota_GrapStarsProgress_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GrapStarsProgress",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   GrapStarsProgress* tolua_ret = (GrapStarsProgress*)  Mtolua_new((GrapStarsProgress)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GrapStarsProgress");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  GrapStarsProgress */
#ifndef TOLUA_DISABLE_tolua_Dota_GrapStarsProgress_delete00
static int tolua_Dota_GrapStarsProgress_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GrapStarsProgress",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GrapStarsProgress* self = (GrapStarsProgress*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createGrapStarsProgress of class  GrapStarsProgress */
#ifndef TOLUA_DISABLE_tolua_Dota_GrapStarsProgress_createGrapStarsProgress00
static int tolua_Dota_GrapStarsProgress_createGrapStarsProgress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"GrapStarsProgress",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int maxStarsCount = ((int)  tolua_tonumber(tolua_S,2,0));
  int activeCount = ((int)  tolua_tonumber(tolua_S,3,0));
  float fSpace = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   GrapStarsProgress* tolua_ret = (GrapStarsProgress*)  GrapStarsProgress::createGrapStarsProgress(maxStarsCount,activeCount,fSpace);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"GrapStarsProgress");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createGrapStarsProgress'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initGrapStarsProgress of class  GrapStarsProgress */
#ifndef TOLUA_DISABLE_tolua_Dota_GrapStarsProgress_initGrapStarsProgress00
static int tolua_Dota_GrapStarsProgress_initGrapStarsProgress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GrapStarsProgress",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GrapStarsProgress* self = (GrapStarsProgress*)  tolua_tousertype(tolua_S,1,0);
  int maxStarsCount = ((int)  tolua_tonumber(tolua_S,2,0));
  int activeCount = ((int)  tolua_tonumber(tolua_S,3,0));
  float fSpace = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initGrapStarsProgress'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initGrapStarsProgress(maxStarsCount,activeCount,fSpace);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initGrapStarsProgress'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setStars of class  GrapStarsProgress */
#ifndef TOLUA_DISABLE_tolua_Dota_GrapStarsProgress_setStars00
static int tolua_Dota_GrapStarsProgress_setStars00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GrapStarsProgress",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  GrapStarsProgress* self = (GrapStarsProgress*)  tolua_tousertype(tolua_S,1,0);
  int maxStarsCount = ((int)  tolua_tonumber(tolua_S,2,0));
  int activeCount = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setStars'", NULL);
#endif
  {
   self->setStars(maxStarsCount,activeCount);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setStars'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setStars of class  GrapStarsProgress */
#ifndef TOLUA_DISABLE_tolua_Dota_GrapStarsProgress_setStars01
static int tolua_Dota_GrapStarsProgress_setStars01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"GrapStarsProgress",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  GrapStarsProgress* self = (GrapStarsProgress*)  tolua_tousertype(tolua_S,1,0);
  int activeCount = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setStars'", NULL);
#endif
  {
   self->setStars(activeCount);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Dota_GrapStarsProgress_setStars00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  MaskNode */
#ifndef TOLUA_DISABLE_tolua_Dota_MaskNode_init00
static int tolua_Dota_MaskNode_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MaskNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MaskNode* self = (MaskNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setViewData of class  MaskNode */
#ifndef TOLUA_DISABLE_tolua_Dota_MaskNode_setViewData00
static int tolua_Dota_MaskNode_setViewData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MaskNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIViewData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MaskNode* self = (MaskNode*)  tolua_tousertype(tolua_S,1,0);
  UIViewData* data = ((UIViewData*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setViewData'", NULL);
#endif
  {
   self->setViewData(data);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setViewData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetViewData of class  MaskNode */
#ifndef TOLUA_DISABLE_tolua_Dota_MaskNode_GetViewData00
static int tolua_Dota_MaskNode_GetViewData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MaskNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MaskNode* self = (MaskNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetViewData'", NULL);
#endif
  {
   const UIViewData& tolua_ret = (const UIViewData&)  self->GetViewData();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const UIViewData");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetViewData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetViewPData of class  MaskNode */
#ifndef TOLUA_DISABLE_tolua_Dota_MaskNode_GetViewPData00
static int tolua_Dota_MaskNode_GetViewPData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MaskNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MaskNode* self = (MaskNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetViewPData'", NULL);
#endif
  {
   UIViewData* tolua_ret = (UIViewData*)  self->GetViewPData();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIViewData");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetViewPData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CallBackEventProtocol of class  MoveAnimationCallBackProtocol */
#ifndef TOLUA_DISABLE_tolua_Dota_MoveAnimationCallBackProtocol_CallBackEventProtocol00
static int tolua_Dota_MoveAnimationCallBackProtocol_CallBackEventProtocol00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MoveAnimationCallBackProtocol",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MoveAnimationCallBackProtocol* self = (MoveAnimationCallBackProtocol*)  tolua_tousertype(tolua_S,1,0);
  int eventType = ((int)  tolua_tonumber(tolua_S,2,0));
  void* ptrParam = ((void*)  tolua_touserdata(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CallBackEventProtocol'", NULL);
#endif
  {
   self->CallBackEventProtocol(eventType,ptrParam);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CallBackEventProtocol'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithDuration of class  MoveAnimation */
#ifndef TOLUA_DISABLE_tolua_Dota_MoveAnimation_initWithDuration00
static int tolua_Dota_MoveAnimation_initWithDuration00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MoveAnimation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"PCallBackVec",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MoveAnimation* self = (MoveAnimation*)  tolua_tousertype(tolua_S,1,0);
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  const CCPoint* position = ((const CCPoint*)  tolua_tousertype(tolua_S,3,0));
  PCallBackVec pCallBackVec = *((PCallBackVec*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithDuration'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithDuration(duration,*position,pCallBackVec);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithDuration'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  MoveAnimation */
#ifndef TOLUA_DISABLE_tolua_Dota_MoveAnimation_delete00
static int tolua_Dota_MoveAnimation_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MoveAnimation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MoveAnimation* self = (MoveAnimation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: destroy of class  MoveAnimation */
#ifndef TOLUA_DISABLE_tolua_Dota_MoveAnimation_destroy00
static int tolua_Dota_MoveAnimation_destroy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MoveAnimation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MoveAnimation* self = (MoveAnimation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'destroy'", NULL);
#endif
  {
   self->destroy();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'destroy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: copyWithZone of class  MoveAnimation */
#ifndef TOLUA_DISABLE_tolua_Dota_MoveAnimation_copyWithZone00
static int tolua_Dota_MoveAnimation_copyWithZone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MoveAnimation",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCZone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MoveAnimation* self = (MoveAnimation*)  tolua_tousertype(tolua_S,1,0);
  CCZone* pZone = ((CCZone*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'copyWithZone'", NULL);
#endif
  {
   CCObject* tolua_ret = (CCObject*)  self->copyWithZone(pZone);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'copyWithZone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: startWithTarget of class  MoveAnimation */
#ifndef TOLUA_DISABLE_tolua_Dota_MoveAnimation_startWithTarget00
static int tolua_Dota_MoveAnimation_startWithTarget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MoveAnimation",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MoveAnimation* self = (MoveAnimation*)  tolua_tousertype(tolua_S,1,0);
  CCNode* pTarget = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'startWithTarget'", NULL);
#endif
  {
   self->startWithTarget(pTarget);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'startWithTarget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  MoveAnimation */
#ifndef TOLUA_DISABLE_tolua_Dota_MoveAnimation_update00
static int tolua_Dota_MoveAnimation_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MoveAnimation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MoveAnimation* self = (MoveAnimation*)  tolua_tousertype(tolua_S,1,0);
  float time = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update(time);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateAnimatioSpeedScale of class  MoveAnimation */
#ifndef TOLUA_DISABLE_tolua_Dota_MoveAnimation_updateAnimatioSpeedScale00
static int tolua_Dota_MoveAnimation_updateAnimatioSpeedScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MoveAnimation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MoveAnimation* self = (MoveAnimation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateAnimatioSpeedScale'", NULL);
#endif
  {
   self->updateAnimatioSpeedScale();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateAnimatioSpeedScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSpeedScale of class  MoveAnimation */
#ifndef TOLUA_DISABLE_tolua_Dota_MoveAnimation_setSpeedScale00
static int tolua_Dota_MoveAnimation_setSpeedScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"MoveAnimation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  MoveAnimation* self = (MoveAnimation*)  tolua_tousertype(tolua_S,1,0);
  float speedScale = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSpeedScale'", NULL);
#endif
  {
   self->setSpeedScale(speedScale);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSpeedScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  MoveAnimation */
#ifndef TOLUA_DISABLE_tolua_Dota_MoveAnimation_create00
static int tolua_Dota_MoveAnimation_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"MoveAnimation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"PCallBackVec",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  const CCPoint* position = ((const CCPoint*)  tolua_tousertype(tolua_S,3,0));
  PCallBackVec pCallBackVec = *((PCallBackVec*)  tolua_tousertype(tolua_S,4,0));
  {
   MoveAnimation* tolua_ret = (MoveAnimation*)  MoveAnimation::create(duration,*position,pCallBackVec);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"MoveAnimation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithDuration of class  PreCCMoveTo */
#ifndef TOLUA_DISABLE_tolua_Dota_PreCCMoveTo_initWithDuration00
static int tolua_Dota_PreCCMoveTo_initWithDuration00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PreCCMoveTo",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PreCCMoveTo* self = (PreCCMoveTo*)  tolua_tousertype(tolua_S,1,0);
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  const CCPoint* position = ((const CCPoint*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithDuration'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithDuration(duration,*position);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithDuration'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: copyWithZone of class  PreCCMoveTo */
#ifndef TOLUA_DISABLE_tolua_Dota_PreCCMoveTo_copyWithZone00
static int tolua_Dota_PreCCMoveTo_copyWithZone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PreCCMoveTo",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCZone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PreCCMoveTo* self = (PreCCMoveTo*)  tolua_tousertype(tolua_S,1,0);
  CCZone* pZone = ((CCZone*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'copyWithZone'", NULL);
#endif
  {
   CCObject* tolua_ret = (CCObject*)  self->copyWithZone(pZone);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCObject");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'copyWithZone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: startWithTarget of class  PreCCMoveTo */
#ifndef TOLUA_DISABLE_tolua_Dota_PreCCMoveTo_startWithTarget00
static int tolua_Dota_PreCCMoveTo_startWithTarget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PreCCMoveTo",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PreCCMoveTo* self = (PreCCMoveTo*)  tolua_tousertype(tolua_S,1,0);
  CCNode* pTarget = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'startWithTarget'", NULL);
#endif
  {
   self->startWithTarget(pTarget);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'startWithTarget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  PreCCMoveTo */
#ifndef TOLUA_DISABLE_tolua_Dota_PreCCMoveTo_update00
static int tolua_Dota_PreCCMoveTo_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PreCCMoveTo",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PreCCMoveTo* self = (PreCCMoveTo*)  tolua_tousertype(tolua_S,1,0);
  float time = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update(time);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  PreCCMoveTo */
#ifndef TOLUA_DISABLE_tolua_Dota_PreCCMoveTo_create00
static int tolua_Dota_PreCCMoveTo_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PreCCMoveTo",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  const CCPoint* position = ((const CCPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   PreCCMoveTo* tolua_ret = (PreCCMoveTo*)  PreCCMoveTo::create(duration,*position);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PreCCMoveTo");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithDuration of class  PreCCMoveBy */
#ifndef TOLUA_DISABLE_tolua_Dota_PreCCMoveBy_initWithDuration00
static int tolua_Dota_PreCCMoveBy_initWithDuration00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PreCCMoveBy",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PreCCMoveBy* self = (PreCCMoveBy*)  tolua_tousertype(tolua_S,1,0);
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  const CCPoint* position = ((const CCPoint*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithDuration'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithDuration(duration,*position);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithDuration'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: startWithTarget of class  PreCCMoveBy */
#ifndef TOLUA_DISABLE_tolua_Dota_PreCCMoveBy_startWithTarget00
static int tolua_Dota_PreCCMoveBy_startWithTarget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PreCCMoveBy",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PreCCMoveBy* self = (PreCCMoveBy*)  tolua_tousertype(tolua_S,1,0);
  CCNode* pTarget = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'startWithTarget'", NULL);
#endif
  {
   self->startWithTarget(pTarget);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'startWithTarget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: reverse of class  PreCCMoveBy */
#ifndef TOLUA_DISABLE_tolua_Dota_PreCCMoveBy_reverse00
static int tolua_Dota_PreCCMoveBy_reverse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PreCCMoveBy",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PreCCMoveBy* self = (PreCCMoveBy*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'reverse'", NULL);
#endif
  {
   CCActionInterval* tolua_ret = (CCActionInterval*)  self->reverse();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCActionInterval");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'reverse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  PreCCMoveBy */
#ifndef TOLUA_DISABLE_tolua_Dota_PreCCMoveBy_create00
static int tolua_Dota_PreCCMoveBy_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PreCCMoveBy",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  const CCPoint* position = ((const CCPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   PreCCMoveBy* tolua_ret = (PreCCMoveBy*)  PreCCMoveBy::create(duration,*position);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PreCCMoveBy");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  ScaleSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_ScaleSprite_create00
static int tolua_Dota_ScaleSprite_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ScaleSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filepath = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   ScaleSprite* tolua_ret = (ScaleSprite*)  ScaleSprite::create(filepath);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ScaleSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  ScaleSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_ScaleSprite_init00
static int tolua_Dota_ScaleSprite_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScaleSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScaleSprite* self = (ScaleSprite*)  tolua_tousertype(tolua_S,1,0);
  const char* filepath = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(filepath);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  SceneEffect */
#ifndef TOLUA_DISABLE_tolua_Dota_SceneEffect_new00
static int tolua_Dota_SceneEffect_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SceneEffect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SceneEffect* tolua_ret = (SceneEffect*)  Mtolua_new((SceneEffect)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SceneEffect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  SceneEffect */
#ifndef TOLUA_DISABLE_tolua_Dota_SceneEffect_new00_local
static int tolua_Dota_SceneEffect_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SceneEffect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SceneEffect* tolua_ret = (SceneEffect*)  Mtolua_new((SceneEffect)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SceneEffect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  SceneEffect */
#ifndef TOLUA_DISABLE_tolua_Dota_SceneEffect_delete00
static int tolua_Dota_SceneEffect_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SceneEffect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SceneEffect* self = (SceneEffect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithEffectID of class  SceneEffect */
#ifndef TOLUA_DISABLE_tolua_Dota_SceneEffect_createWithEffectID00
static int tolua_Dota_SceneEffect_createWithEffectID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SceneEffect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int effectID = ((int)  tolua_tonumber(tolua_S,2,0));
  float delay = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   SceneEffect* tolua_ret = (SceneEffect*)  SceneEffect::createWithEffectID(effectID,delay);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SceneEffect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createWithEffectID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithEffectID of class  SceneEffect */
#ifndef TOLUA_DISABLE_tolua_Dota_SceneEffect_initWithEffectID00
static int tolua_Dota_SceneEffect_initWithEffectID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SceneEffect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SceneEffect* self = (SceneEffect*)  tolua_tousertype(tolua_S,1,0);
  int effectID = ((int)  tolua_tonumber(tolua_S,2,0));
  float delay = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithEffectID'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithEffectID(effectID,delay);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithEffectID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clone of class  SceneEffect */
#ifndef TOLUA_DISABLE_tolua_Dota_SceneEffect_clone00
static int tolua_Dota_SceneEffect_clone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SceneEffect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SceneEffect* self = (SceneEffect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clone'", NULL);
#endif
  {
   SceneEffect* tolua_ret = (SceneEffect*)  self->clone();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SceneEffect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ReplayAction of class  SceneEffect */
#ifndef TOLUA_DISABLE_tolua_Dota_SceneEffect_ReplayAction00
static int tolua_Dota_SceneEffect_ReplayAction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SceneEffect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SceneEffect* self = (SceneEffect*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ReplayAction'", NULL);
#endif
  {
   self->ReplayAction();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReplayAction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  SingleTouchProtocol */
#ifndef TOLUA_DISABLE_tolua_Dota_SingleTouchProtocol_new00
static int tolua_Dota_SingleTouchProtocol_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SingleTouchProtocol",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SingleTouchProtocol* tolua_ret = (SingleTouchProtocol*)  Mtolua_new((SingleTouchProtocol)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SingleTouchProtocol");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  SingleTouchProtocol */
#ifndef TOLUA_DISABLE_tolua_Dota_SingleTouchProtocol_new00_local
static int tolua_Dota_SingleTouchProtocol_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SingleTouchProtocol",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SingleTouchProtocol* tolua_ret = (SingleTouchProtocol*)  Mtolua_new((SingleTouchProtocol)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SingleTouchProtocol");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  SingleTouchProtocol */
#ifndef TOLUA_DISABLE_tolua_Dota_SingleTouchProtocol_delete00
static int tolua_Dota_SingleTouchProtocol_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SingleTouchProtocol",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SingleTouchProtocol* self = (SingleTouchProtocol*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkRowRank of class  SingleTouchProtocol */
#ifndef TOLUA_DISABLE_tolua_Dota_SingleTouchProtocol_checkRowRank00
static int tolua_Dota_SingleTouchProtocol_checkRowRank00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SingleTouchProtocol",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SingleTouchProtocol* self = (SingleTouchProtocol*)  tolua_tousertype(tolua_S,1,0);
  float touchYPos = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'checkRowRank'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->checkRowRank(touchYPos);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'checkRowRank'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkColumnRank of class  SingleTouchProtocol */
#ifndef TOLUA_DISABLE_tolua_Dota_SingleTouchProtocol_checkColumnRank00
static int tolua_Dota_SingleTouchProtocol_checkColumnRank00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SingleTouchProtocol",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SingleTouchProtocol* self = (SingleTouchProtocol*)  tolua_tousertype(tolua_S,1,0);
  float touchXPos = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'checkColumnRank'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->checkColumnRank(touchXPos);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'checkColumnRank'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: checkIsContainTouch of class  SingleTouchProtocol */
#ifndef TOLUA_DISABLE_tolua_Dota_SingleTouchProtocol_checkIsContainTouch00
static int tolua_Dota_SingleTouchProtocol_checkIsContainTouch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SingleTouchProtocol",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SingleTouchProtocol* self = (SingleTouchProtocol*)  tolua_tousertype(tolua_S,1,0);
  CCPoint* touchPos = ((CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'checkIsContainTouch'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->checkIsContainTouch(*touchPos);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'checkIsContainTouch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSingleTouchUniqueID of class  SingleTouchProtocol */
#ifndef TOLUA_DISABLE_tolua_Dota_SingleTouchProtocol_setSingleTouchUniqueID00
static int tolua_Dota_SingleTouchProtocol_setSingleTouchUniqueID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SingleTouchProtocol",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SingleTouchProtocol* self = (SingleTouchProtocol*)  tolua_tousertype(tolua_S,1,0);
  int singleTouchID = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSingleTouchUniqueID'", NULL);
#endif
  {
   self->setSingleTouchUniqueID(singleTouchID);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSingleTouchUniqueID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setExpendTouchSize of class  SingleTouchProtocol */
#ifndef TOLUA_DISABLE_tolua_Dota_SingleTouchProtocol_setExpendTouchSize00
static int tolua_Dota_SingleTouchProtocol_setExpendTouchSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SingleTouchProtocol",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SingleTouchProtocol* self = (SingleTouchProtocol*)  tolua_tousertype(tolua_S,1,0);
  float touchExpendWidth = ((float)  tolua_tonumber(tolua_S,2,0));
  float touchExpendHeight = ((float)  tolua_tonumber(tolua_S,3,0.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setExpendTouchSize'", NULL);
#endif
  {
   self->setExpendTouchSize(touchExpendWidth,touchExpendHeight);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setExpendTouchSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getExpendTouchSize of class  SingleTouchProtocol */
#ifndef TOLUA_DISABLE_tolua_Dota_SingleTouchProtocol_getExpendTouchSize00
static int tolua_Dota_SingleTouchProtocol_getExpendTouchSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SingleTouchProtocol",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SingleTouchProtocol* self = (SingleTouchProtocol*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getExpendTouchSize'", NULL);
#endif
  {
   CCSize tolua_ret = (CCSize)  self->getExpendTouchSize();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCSize)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCSize));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getExpendTouchSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSingleTouchUniqueID of class  SingleTouchProtocol */
#ifndef TOLUA_DISABLE_tolua_Dota_SingleTouchProtocol_getSingleTouchUniqueID00
static int tolua_Dota_SingleTouchProtocol_getSingleTouchUniqueID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SingleTouchProtocol",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SingleTouchProtocol* self = (SingleTouchProtocol*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSingleTouchUniqueID'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getSingleTouchUniqueID();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSingleTouchUniqueID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: BaseDialogCallBackHandler of class  UIBaseDialogProtory */
#ifndef TOLUA_DISABLE_tolua_Dota_UIBaseDialogProtory_BaseDialogCallBackHandler00
static int tolua_Dota_UIBaseDialogProtory_BaseDialogCallBackHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIBaseDialogProtory",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIBaseDialogProtory* self = (UIBaseDialogProtory*)  tolua_tousertype(tolua_S,1,0);
  int eventType = ((int)  tolua_tonumber(tolua_S,2,0));
  void* ptr = ((void*)  tolua_touserdata(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BaseDialogCallBackHandler'", NULL);
#endif
  {
   self->BaseDialogCallBackHandler(eventType,ptr);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BaseDialogCallBackHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UIBaseDialog */
#ifndef TOLUA_DISABLE_tolua_Dota_UIBaseDialog_new00
static int tolua_Dota_UIBaseDialog_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIBaseDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIBaseDialog* tolua_ret = (UIBaseDialog*)  Mtolua_new((UIBaseDialog)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIBaseDialog");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  UIBaseDialog */
#ifndef TOLUA_DISABLE_tolua_Dota_UIBaseDialog_new00_local
static int tolua_Dota_UIBaseDialog_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIBaseDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UIBaseDialog* tolua_ret = (UIBaseDialog*)  Mtolua_new((UIBaseDialog)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIBaseDialog");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  UIBaseDialog */
#ifndef TOLUA_DISABLE_tolua_Dota_UIBaseDialog_delete00
static int tolua_Dota_UIBaseDialog_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIBaseDialog",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIBaseDialog* self = (UIBaseDialog*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createUIBaseDialog of class  UIBaseDialog */
#ifndef TOLUA_DISABLE_tolua_Dota_UIBaseDialog_createUIBaseDialog00
static int tolua_Dota_UIBaseDialog_createUIBaseDialog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UIBaseDialog",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int priority = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   UIBaseDialog* tolua_ret = (UIBaseDialog*)  UIBaseDialog::createUIBaseDialog(priority);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIBaseDialog");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createUIBaseDialog'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTouchUnCloseRect of class  UIBaseDialog */
#ifndef TOLUA_DISABLE_tolua_Dota_UIBaseDialog_setTouchUnCloseRect00
static int tolua_Dota_UIBaseDialog_setTouchUnCloseRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIBaseDialog",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIBaseDialog* self = (UIBaseDialog*)  tolua_tousertype(tolua_S,1,0);
  CCRect rect = *((CCRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTouchUnCloseRect'", NULL);
#endif
  {
   self->setTouchUnCloseRect(rect);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTouchUnCloseRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDelegatePrototy of class  UIBaseDialog */
#ifndef TOLUA_DISABLE_tolua_Dota_UIBaseDialog_setDelegatePrototy00
static int tolua_Dota_UIBaseDialog_setDelegatePrototy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIBaseDialog",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIBaseDialogProtory",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIBaseDialog* self = (UIBaseDialog*)  tolua_tousertype(tolua_S,1,0);
  UIBaseDialogProtory* delegatePtr = ((UIBaseDialogProtory*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDelegatePrototy'", NULL);
#endif
  {
   self->setDelegatePrototy(delegatePtr);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDelegatePrototy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_new00
static int tolua_Dota_UITowSideStretchNodeLayer_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UITowSideStretchNodeLayer* tolua_ret = (UITowSideStretchNodeLayer*)  Mtolua_new((UITowSideStretchNodeLayer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UITowSideStretchNodeLayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_new00_local
static int tolua_Dota_UITowSideStretchNodeLayer_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   UITowSideStretchNodeLayer* tolua_ret = (UITowSideStretchNodeLayer*)  Mtolua_new((UITowSideStretchNodeLayer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UITowSideStretchNodeLayer");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_delete00
static int tolua_Dota_UITowSideStretchNodeLayer_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createTowSideStretchLayer of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_createTowSideStretchLayer00
static int tolua_Dota_UITowSideStretchNodeLayer_createTowSideStretchLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",1,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCNode",1,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCNode",1,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"CCNode",1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* leftNormalNode = ((CCNode*)  tolua_tousertype(tolua_S,2,NULL));
  CCNode* leftSelectedNode = ((CCNode*)  tolua_tousertype(tolua_S,3,NULL));
  CCNode* rightNormalNode = ((CCNode*)  tolua_tousertype(tolua_S,4,NULL));
  CCNode* rightSelectedNode = ((CCNode*)  tolua_tousertype(tolua_S,5,NULL));
  {
   UITowSideStretchNodeLayer* tolua_ret = (UITowSideStretchNodeLayer*)  UITowSideStretchNodeLayer::createTowSideStretchLayer(leftNormalNode,leftSelectedNode,rightNormalNode,rightSelectedNode);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UITowSideStretchNodeLayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createTowSideStretchLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onEnter of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_onEnter00
static int tolua_Dota_UITowSideStretchNodeLayer_onEnter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onEnter'", NULL);
#endif
  {
   self->onEnter();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onEnter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onExit of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_onExit00
static int tolua_Dota_UITowSideStretchNodeLayer_onExit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onExit'", NULL);
#endif
  {
   self->onExit();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onExit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchBegan of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_ccTouchBegan00
static int tolua_Dota_UITowSideStretchNodeLayer_ccTouchBegan00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* pTouch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchBegan'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ccTouchBegan(pTouch,pEvent);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchBegan'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchMoved of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_ccTouchMoved00
static int tolua_Dota_UITowSideStretchNodeLayer_ccTouchMoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* pTouch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchMoved'", NULL);
#endif
  {
   self->ccTouchMoved(pTouch,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchMoved'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ccTouchEnded of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_ccTouchEnded00
static int tolua_Dota_UITowSideStretchNodeLayer_ccTouchEnded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCEvent",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* pTouch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
  CCEvent* pEvent = ((CCEvent*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ccTouchEnded'", NULL);
#endif
  {
   self->ccTouchEnded(pTouch,pEvent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ccTouchEnded'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onShowUnfoldNode of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_onShowUnfoldNode00
static int tolua_Dota_UITowSideStretchNodeLayer_onShowUnfoldNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  bool isLeft = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onShowUnfoldNode'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->onShowUnfoldNode(isLeft);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onShowUnfoldNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onShowShrinkNode of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_onShowShrinkNode00
static int tolua_Dota_UITowSideStretchNodeLayer_onShowShrinkNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  bool isLeft = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onShowShrinkNode'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->onShowShrinkNode(isLeft);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onShowShrinkNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLeftScreenRect of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_getLeftScreenRect00
static int tolua_Dota_UITowSideStretchNodeLayer_getLeftScreenRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLeftScreenRect'", NULL);
#endif
  {
   CCRect tolua_ret = (CCRect)  self->getLeftScreenRect();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCRect)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCRect));
     tolua_pushusertype(tolua_S,tolua_obj,"CCRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLeftScreenRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRightScreenRect of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_getRightScreenRect00
static int tolua_Dota_UITowSideStretchNodeLayer_getRightScreenRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRightScreenRect'", NULL);
#endif
  {
   CCRect tolua_ret = (CCRect)  self->getRightScreenRect();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCRect)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCRect));
     tolua_pushusertype(tolua_S,tolua_obj,"CCRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRightScreenRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: containTouchOnLeftRect of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_containTouchOnLeftRect00
static int tolua_Dota_UITowSideStretchNodeLayer_containTouchOnLeftRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* pTouch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'containTouchOnLeftRect'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->containTouchOnLeftRect(pTouch);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'containTouchOnLeftRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: containTouchOnRightRect of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_containTouchOnRightRect00
static int tolua_Dota_UITowSideStretchNodeLayer_containTouchOnRightRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  CCTouch* pTouch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'containTouchOnRightRect'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->containTouchOnRightRect(pTouch);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'containTouchOnRightRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLeftNormalNode of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_setLeftNormalNode00
static int tolua_Dota_UITowSideStretchNodeLayer_setLeftNormalNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  CCNode* leftNormal = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLeftNormalNode'", NULL);
#endif
  {
   self->setLeftNormalNode(leftNormal);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLeftNormalNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setleftSelectNode of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_setleftSelectNode00
static int tolua_Dota_UITowSideStretchNodeLayer_setleftSelectNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  CCNode* leftSelected = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setleftSelectNode'", NULL);
#endif
  {
   self->setleftSelectNode(leftSelected);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setleftSelectNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRightNormalNode of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_setRightNormalNode00
static int tolua_Dota_UITowSideStretchNodeLayer_setRightNormalNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  CCNode* rightNormal = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRightNormalNode'", NULL);
#endif
  {
   self->setRightNormalNode(rightNormal);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRightNormalNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRightSelectNode of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_setRightSelectNode00
static int tolua_Dota_UITowSideStretchNodeLayer_setRightSelectNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  CCNode* rightSelected = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRightSelectNode'", NULL);
#endif
  {
   self->setRightSelectNode(rightSelected);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRightSelectNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setStretchTime of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_setStretchTime00
static int tolua_Dota_UITowSideStretchNodeLayer_setStretchTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  float stretchTime = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setStretchTime'", NULL);
#endif
  {
   self->setStretchTime(stretchTime);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setStretchTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTouchEnable of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_setTouchEnable00
static int tolua_Dota_UITowSideStretchNodeLayer_setTouchEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  bool touchEnable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTouchEnable'", NULL);
#endif
  {
   self->setTouchEnable(touchEnable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTouchEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTouchPriority of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_setTouchPriority00
static int tolua_Dota_UITowSideStretchNodeLayer_setTouchPriority00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  int touchPriority = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTouchPriority'", NULL);
#endif
  {
   self->setTouchPriority(touchPriority);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTouchPriority'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setNormalAndSelectWith of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_setNormalAndSelectWith00
static int tolua_Dota_UITowSideStretchNodeLayer_setNormalAndSelectWith00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  float normalWidth = ((float)  tolua_tonumber(tolua_S,2,0));
  float selectWidth = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setNormalAndSelectWith'", NULL);
#endif
  {
   self->setNormalAndSelectWith(normalWidth,selectWidth);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setNormalAndSelectWith'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setNormalAndSelectYPos of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_setNormalAndSelectYPos00
static int tolua_Dota_UITowSideStretchNodeLayer_setNormalAndSelectYPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
  float normalYPos = ((float)  tolua_tonumber(tolua_S,2,0));
  float selectYPos = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setNormalAndSelectYPos'", NULL);
#endif
  {
   self->setNormalAndSelectYPos(normalYPos,selectYPos);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setNormalAndSelectYPos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLeftNormalNode of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_getLeftNormalNode00
static int tolua_Dota_UITowSideStretchNodeLayer_getLeftNormalNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLeftNormalNode'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getLeftNormalNode();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLeftNormalNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getleftSelectNode of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_getleftSelectNode00
static int tolua_Dota_UITowSideStretchNodeLayer_getleftSelectNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getleftSelectNode'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getleftSelectNode();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getleftSelectNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRightNormalNode of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_getRightNormalNode00
static int tolua_Dota_UITowSideStretchNodeLayer_getRightNormalNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRightNormalNode'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getRightNormalNode();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRightNormalNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRightSelectedNode of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_getRightSelectedNode00
static int tolua_Dota_UITowSideStretchNodeLayer_getRightSelectedNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRightSelectedNode'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getRightSelectedNode();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRightSelectedNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStretchTime of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_getStretchTime00
static int tolua_Dota_UITowSideStretchNodeLayer_getStretchTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStretchTime'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getStretchTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStretchTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTouchEnable of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_getTouchEnable00
static int tolua_Dota_UITowSideStretchNodeLayer_getTouchEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTouchEnable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->getTouchEnable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTouchEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTouchPriority of class  UITowSideStretchNodeLayer */
#ifndef TOLUA_DISABLE_tolua_Dota_UITowSideStretchNodeLayer_getTouchPriority00
static int tolua_Dota_UITowSideStretchNodeLayer_getTouchPriority00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UITowSideStretchNodeLayer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UITowSideStretchNodeLayer* self = (UITowSideStretchNodeLayer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTouchPriority'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getTouchPriority();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTouchPriority'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_getLoopFrameEffect */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_getLoopFrameEffect00
static int tolua_Dota_NFC_getLoopFrameEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int animationID = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   CCSprite* tolua_ret = (CCSprite*)  NFC_getLoopFrameEffect(animationID);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_getLoopFrameEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_getUnLoopFrameEffect */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_getUnLoopFrameEffect00
static int tolua_Dota_NFC_getUnLoopFrameEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int animationID = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   CCSprite* tolua_ret = (CCSprite*)  NFC_getUnLoopFrameEffect(animationID);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_getUnLoopFrameEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_getUnLoopFrameEffect */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_getUnLoopFrameEffect01
static int tolua_Dota_NFC_getUnLoopFrameEffect01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"AnimationEffectCallBackProtocol",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int animationID = ((int)  tolua_tonumber(tolua_S,1,0));
  AnimationEffectCallBackProtocol* pDelegate = ((AnimationEffectCallBackProtocol*)  tolua_tousertype(tolua_S,2,0));
  {
   CCSprite* tolua_ret = (CCSprite*)  NFC_getUnLoopFrameEffect(animationID,pDelegate);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Dota_NFC_getUnLoopFrameEffect00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_getUnLoopFrameEffect */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_getUnLoopFrameEffect02
static int tolua_Dota_NFC_getUnLoopFrameEffect02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"AnimationEffectCallBackProtocol",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int animationID = ((int)  tolua_tonumber(tolua_S,1,0));
  AnimationEffectCallBackProtocol* pDelegate = ((AnimationEffectCallBackProtocol*)  tolua_tousertype(tolua_S,2,0));
  float callTime = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   CCSprite* tolua_ret = (CCSprite*)  NFC_getUnLoopFrameEffect(animationID,pDelegate,callTime);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Dota_NFC_getUnLoopFrameEffect01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_getUnLoopFrameEffect */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_getUnLoopFrameEffect03
static int tolua_Dota_NFC_getUnLoopFrameEffect03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"AnimationEffectCallBackProtocol",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int animationID = ((int)  tolua_tonumber(tolua_S,1,0));
  AnimationEffectCallBackProtocol* pDelegate = ((AnimationEffectCallBackProtocol*)  tolua_tousertype(tolua_S,2,0));
  float callTime1 = ((float)  tolua_tonumber(tolua_S,3,0));
  float callTime2 = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   CCSprite* tolua_ret = (CCSprite*)  NFC_getUnLoopFrameEffect(animationID,pDelegate,callTime1,callTime2);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Dota_NFC_getUnLoopFrameEffect02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_getAnimationSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_getAnimationSprite00
static int tolua_Dota_NFC_getAnimationSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"AnimationEffectCallBackProtocol",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int animationID = ((int)  tolua_tonumber(tolua_S,1,0));
  bool isLoopEffect = ((bool)  tolua_toboolean(tolua_S,2,0));
  bool isPlayEffectAddParent = ((bool)  tolua_toboolean(tolua_S,3,0));
  AnimationEffectCallBackProtocol* pDelegate = ((AnimationEffectCallBackProtocol*)  tolua_tousertype(tolua_S,4,0));
  {
   CAnimationSprite* tolua_ret = (CAnimationSprite*)  NFC_getAnimationSprite(animationID,isLoopEffect,isPlayEffectAddParent,pDelegate);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CAnimationSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_getAnimationSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_PlayEffet */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_PlayEffet00
static int tolua_Dota_NFC_PlayEffet00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int uiIndex = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* pParent = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  bool isPlayEffect = ((bool)  tolua_toboolean(tolua_S,3,0));
  {
   NFC_PlayEffet(uiIndex,pParent,isPlayEffect);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_PlayEffet'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_skeletonTransparentAction */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_skeletonTransparentAction00
static int tolua_Dota_NFC_skeletonTransparentAction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSkeletonAnimation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSkeletonAnimation* pSkeletonAnimation = ((CCSkeletonAnimation*)  tolua_tousertype(tolua_S,1,0));
  float actionTime = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   NFC_skeletonTransparentAction(pSkeletonAnimation,actionTime);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_skeletonTransparentAction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_getParticelEffect */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_getParticelEffect00
static int tolua_Dota_NFC_getParticelEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int paticelEffectID = ((int)  tolua_tonumber(tolua_S,1,0));
  bool isLoop = ((bool)  tolua_toboolean(tolua_S,2,0));
  {
   CCParticleSystemQuad* tolua_ret = (CCParticleSystemQuad*)  NFC_getParticelEffect(paticelEffectID,isLoop);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCParticleSystemQuad");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_getParticelEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_getVariableSpeedAction */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_getVariableSpeedAction00
static int tolua_Dota_NFC_getVariableSpeedAction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCFiniteTimeAction",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCFiniteTimeAction",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCFiniteTimeAction* pAction1 = ((CCFiniteTimeAction*)  tolua_tousertype(tolua_S,1,0));
  CCFiniteTimeAction* pAction2 = ((CCFiniteTimeAction*)  tolua_tousertype(tolua_S,2,0));
  float initSpeedScale = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   VariableSpeedSequenceAction* tolua_ret = (VariableSpeedSequenceAction*)  NFC_getVariableSpeedAction(pAction1,pAction2,initSpeedScale);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"VariableSpeedSequenceAction");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_getVariableSpeedAction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_getTransimissionDelayComAction */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_getTransimissionDelayComAction00
static int tolua_Dota_NFC_getTransimissionDelayComAction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CallFunctionProtocol",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float delayTime = ((float)  tolua_tonumber(tolua_S,1,0));
  float initSpeedScale = ((float)  tolua_tonumber(tolua_S,2,0));
  CallFunctionProtocol* pDelegate = ((CallFunctionProtocol*)  tolua_tousertype(tolua_S,3,0));
  int eventType = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   VariableSpeedSequenceAction* tolua_ret = (VariableSpeedSequenceAction*)  NFC_getTransimissionDelayComAction(delayTime,initSpeedScale,pDelegate,eventType);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"VariableSpeedSequenceAction");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_getTransimissionDelayComAction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_getTransimissionMoveComAction */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_getTransimissionMoveComAction00
static int tolua_Dota_NFC_getTransimissionMoveComAction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCPoint",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,4,"CallFunctionProtocol",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float delayTime = ((float)  tolua_tonumber(tolua_S,1,0));
  float initSpeedScale = ((float)  tolua_tonumber(tolua_S,2,0));
  CCPoint* endPoint = ((CCPoint*)  tolua_tousertype(tolua_S,3,0));
  CallFunctionProtocol* pDelegate = ((CallFunctionProtocol*)  tolua_tousertype(tolua_S,4,0));
  int eventType = ((int)  tolua_tonumber(tolua_S,5,0));
  {
   VariableSpeedSequenceAction* tolua_ret = (VariableSpeedSequenceAction*)  NFC_getTransimissionMoveComAction(delayTime,initSpeedScale,*endPoint,pDelegate,eventType);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"VariableSpeedSequenceAction");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_getTransimissionMoveComAction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_getSimpleActionSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_getSimpleActionSprite00
static int tolua_Dota_NFC_getSimpleActionSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"std::vector<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int actionType = ((int)  tolua_tonumber(tolua_S,1,0));
  std::vector<float> attachParam = *((std::vector<float>*)  tolua_tousertype(tolua_S,2,0));
  {
   CSimpleActionSprite* tolua_ret = (CSimpleActionSprite*)  NFC_getSimpleActionSprite(actionType,attachParam);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSimpleActionSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_getSimpleActionSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_getSimpleActionSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_getSimpleActionSprite01
static int tolua_Dota_NFC_getSimpleActionSprite01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"std::vector<float>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,1,0));
  int actionType = ((int)  tolua_tonumber(tolua_S,2,0));
  std::vector<float> attachParam = *((std::vector<float>*)  tolua_tousertype(tolua_S,3,0));
  {
   CSimpleActionSprite* tolua_ret = (CSimpleActionSprite*)  NFC_getSimpleActionSprite(fileName,actionType,attachParam);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CSimpleActionSprite");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Dota_NFC_getSimpleActionSprite00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_Action_scaleIn */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_Action_scaleIn00
static int tolua_Dota_NFC_Action_scaleIn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* actionNode = ((CCNode*)  tolua_tousertype(tolua_S,1,0));
  {
   NFC_Action_scaleIn(actionNode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_Action_scaleIn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_Action_scaleIn */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_Action_scaleIn01
static int tolua_Dota_NFC_Action_scaleIn01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCNode* actionNode = ((CCNode*)  tolua_tousertype(tolua_S,1,0));
  std::string param1 = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  std::string param2 = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  std::string param3 = ((std::string)  tolua_tocppstring(tolua_S,4,0));
  {
   NFC_Action_scaleIn(actionNode,param1,param2,param3);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Dota_NFC_Action_scaleIn00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_Action_fallDown */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_Action_fallDown00
static int tolua_Dota_NFC_Action_fallDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* actionNode = ((CCNode*)  tolua_tousertype(tolua_S,1,0));
  {
   NFC_Action_fallDown(actionNode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_Action_fallDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_Action_MoveAndReverse */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_Action_MoveAndReverse00
static int tolua_Dota_NFC_Action_MoveAndReverse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CCPoint",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* actionNode = ((CCNode*)  tolua_tousertype(tolua_S,1,0));
  float during = ((float)  tolua_tonumber(tolua_S,2,0));
  const CCPoint* deltaPosition = ((const CCPoint*)  tolua_tousertype(tolua_S,3,0));
  bool forever = ((bool)  tolua_toboolean(tolua_S,4,0));
  {
   NFC_Action_MoveAndReverse(actionNode,during,*deltaPosition,forever);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_Action_MoveAndReverse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_Action_FadeInAndReverse */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_Action_FadeInAndReverse00
static int tolua_Dota_NFC_Action_FadeInAndReverse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* actionNode = ((CCNode*)  tolua_tousertype(tolua_S,1,0));
  float during = ((float)  tolua_tonumber(tolua_S,2,0));
  bool forever = ((bool)  tolua_toboolean(tolua_S,3,0));
  {
   NFC_Action_FadeInAndReverse(actionNode,during,forever);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_Action_FadeInAndReverse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_quitGame */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_quitGame00
static int tolua_Dota_NFC_quitGame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   NFC_quitGame();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_quitGame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_playSoundByID */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_playSoundByID00
static int tolua_Dota_NFC_playSoundByID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int soundid = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   NFC_playSoundByID(soundid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_playSoundByID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_showErrorTips */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_showErrorTips00
static int tolua_Dota_NFC_showErrorTips00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   NFC_showErrorTips();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_showErrorTips'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_showErrorTips */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_showErrorTips01
static int tolua_Dota_NFC_showErrorTips01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_iscppstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  std::string text = ((std::string)  tolua_tocppstring(tolua_S,1,0));
  {
   NFC_showErrorTips(text);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Dota_NFC_showErrorTips00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_showErrorTips_2 */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_showErrorTips_200
static int tolua_Dota_NFC_showErrorTips_200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_iscppstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string text = ((std::string)  tolua_tocppstring(tolua_S,1,0));
  {
   NFC_showErrorTips_2(text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_showErrorTips_2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_showCommunicationWating */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_showCommunicationWating00
static int tolua_Dota_NFC_showCommunicationWating00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isboolean(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  bool isshow = ((bool)  tolua_toboolean(tolua_S,1,0));
  {
   NFC_showCommunicationWating(isshow);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_showCommunicationWating'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_showCommunicationWating_2 */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_showCommunicationWating_200
static int tolua_Dota_NFC_showCommunicationWating_200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isboolean(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  bool isshow = ((bool)  tolua_toboolean(tolua_S,1,0));
  {
   NFC_showCommunicationWating_2(isshow);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_showCommunicationWating_2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_showMessageBox */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_showMessageBox00
static int tolua_Dota_NFC_showMessageBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int type = ((int)  tolua_tonumber(tolua_S,1,0));
  std::string text = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   NFC_showMessageBox(type,text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_showMessageBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_getFileFromResourceID */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_getFileFromResourceID00
static int tolua_Dota_NFC_getFileFromResourceID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int iconID = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   std::string tolua_ret = (std::string)  NFC_getFileFromResourceID(iconID);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_getFileFromResourceID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_getIDStringFromTag */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_getIDStringFromTag00
static int tolua_Dota_NFC_getIDStringFromTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int tag = ((int)  tolua_tonumber(tolua_S,1,0));
  int subTag = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   std::string tolua_ret = (std::string)  NFC_getIDStringFromTag(tag,subTag);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_getIDStringFromTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_getValueFromClientConst */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_getValueFromClientConst00
static int tolua_Dota_NFC_getValueFromClientConst00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_iscppstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string key = ((std::string)  tolua_tocppstring(tolua_S,1,0));
  {
   int tolua_ret = (int)  NFC_getValueFromClientConst(key);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_getValueFromClientConst'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_showMessageBoxSingle */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_showMessageBoxSingle00
static int tolua_Dota_NFC_showMessageBoxSingle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int type = ((int)  tolua_tonumber(tolua_S,1,0));
  std::string text = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   NFC_showMessageBoxSingle(type,text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_showMessageBoxSingle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_showNormalMsgBySYID */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_showNormalMsgBySYID00
static int tolua_Dota_NFC_showNormalMsgBySYID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int resourceID = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   NFC_showNormalMsgBySYID(resourceID);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_showNormalMsgBySYID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_getNode */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_getNode00
static int tolua_Dota_NFC_getNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int key = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* root = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  {
   CCNode* tolua_ret = (CCNode*)  NFC_getNode(key,root);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_getNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_showNode */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_showNode00
static int tolua_Dota_NFC_showNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int key = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* root = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  bool isShow = ((bool)  tolua_toboolean(tolua_S,3,0));
  {
   NFC_showNode(key,root,isShow);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_showNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setScale */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setScale00
static int tolua_Dota_NFC_setScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int key = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* root = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  float scale = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   NFC_setScale(key,root,scale);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setCardsStarLevel */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setCardsStarLevel00
static int tolua_Dota_NFC_setCardsStarLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int key = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* root = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int count = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   NFC_setCardsStarLevel(key,root,count);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setCardsStarLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setCardsStarAdvance */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setCardsStarAdvance00
static int tolua_Dota_NFC_setCardsStarAdvance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int key = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* root = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int advanceCount = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   NFC_setCardsStarAdvance(key,root,advanceCount);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setCardsStarAdvance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setCornerNum */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setCornerNum00
static int tolua_Dota_NFC_setCornerNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int key = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* root = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int count = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   NFC_setCornerNum(key,root,count);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setCornerNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setLabelString */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setLabelString00
static int tolua_Dota_NFC_setLabelString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int key = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* root = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  std::string txt = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  {
   NFC_setLabelString(key,root,txt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setLabelString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setLabelString */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setLabelString01
static int tolua_Dota_NFC_setLabelString01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int key = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* root = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  std::string txt = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  bool visible = ((bool)  tolua_toboolean(tolua_S,4,0));
  {
   NFC_setLabelString(key,root,txt,visible);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Dota_NFC_setLabelString00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setLabelString */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setLabelString02
static int tolua_Dota_NFC_setLabelString02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLabelTTF",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCLabelTTF* cc = ((CCLabelTTF*)  tolua_tousertype(tolua_S,1,0));
  std::string txt = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   NFC_setLabelString(cc,txt);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Dota_NFC_setLabelString01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setLabelStringInt */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setLabelStringInt00
static int tolua_Dota_NFC_setLabelStringInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int key = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* root = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int num = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   NFC_setLabelStringInt(key,root,num);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setLabelStringInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setLabelStringInt */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setLabelStringInt01
static int tolua_Dota_NFC_setLabelStringInt01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int key = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* root = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int num = ((int)  tolua_tonumber(tolua_S,3,0));
  bool visible = ((bool)  tolua_toboolean(tolua_S,4,0));
  {
   NFC_setLabelStringInt(key,root,num,visible);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Dota_NFC_setLabelStringInt00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setLabelStringInt */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setLabelStringInt02
static int tolua_Dota_NFC_setLabelStringInt02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int key = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* root = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int num = ((int)  tolua_tonumber(tolua_S,3,0));
  int sysTxtID = ((int)  tolua_tonumber(tolua_S,4,0));
  bool visible = ((bool)  tolua_toboolean(tolua_S,5,0));
  {
   NFC_setLabelStringInt(key,root,num,sysTxtID,visible);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Dota_NFC_setLabelStringInt01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setLabelStringInt */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setLabelStringInt03
static int tolua_Dota_NFC_setLabelStringInt03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLabelTTF",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCLabelTTF* cc = ((CCLabelTTF*)  tolua_tousertype(tolua_S,1,0));
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   NFC_setLabelStringInt(cc,num);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Dota_NFC_setLabelStringInt02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setLabelColor */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setLabelColor00
static int tolua_Dota_NFC_setLabelColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int key = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* root = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,3,0));
  {
   NFC_setLabelColor(key,root,*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setLabelColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setLabelColor */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setLabelColor01
static int tolua_Dota_NFC_setLabelColor01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLabelTTF",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCLabelTTF* root = ((CCLabelTTF*)  tolua_tousertype(tolua_S,1,0));
  const ccColor3B* color = ((const ccColor3B*)  tolua_tousertype(tolua_S,2,0));
  {
   NFC_setLabelColor(root,*color);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Dota_NFC_setLabelColor00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setLabelByFontStyleID */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setLabelByFontStyleID00
static int tolua_Dota_NFC_setLabelByFontStyleID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCLabelTTF",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCLabelTTF* cc = ((CCLabelTTF*)  tolua_tousertype(tolua_S,1,0));
  int fontstyleID = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   NFC_setLabelByFontStyleID(cc,fontstyleID);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setLabelByFontStyleID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setLabelByFontID */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setLabelByFontID00
static int tolua_Dota_NFC_setLabelByFontID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int uiIndex = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* pRoot = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int fontstyleID = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   NFC_setLabelByFontID(uiIndex,pRoot,fontstyleID);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setLabelByFontID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setActionSpriteEnable */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setActionSpriteEnable00
static int tolua_Dota_NFC_setActionSpriteEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int uiIndex = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* pRoot = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  bool isEnable = ((bool)  tolua_toboolean(tolua_S,3,0));
  {
   NFC_setActionSpriteEnable(uiIndex,pRoot,isEnable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setActionSpriteEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setCProgressInnerBar */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setCProgressInnerBar00
static int tolua_Dota_NFC_setCProgressInnerBar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int barUIIndex = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* pParent = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  float fPercent = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   NFC_setCProgressInnerBar(barUIIndex,pParent,fPercent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setCProgressInnerBar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_resumeActionsForSceneSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_resumeActionsForSceneSprite00
static int tolua_Dota_NFC_resumeActionsForSceneSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int key = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* root = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  {
   NFC_resumeActionsForSceneSprite(key,root);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_resumeActionsForSceneSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_getArtFontLabel */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_getArtFontLabel00
static int tolua_Dota_NFC_getArtFontLabel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int type = ((int)  tolua_tonumber(tolua_S,1,0));
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   CCNode* tolua_ret = (CCNode*)  NFC_getArtFontLabel(type,num);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_getArtFontLabel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_getRichTextCSSByFontStyleID */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_getRichTextCSSByFontStyleID00
static int tolua_Dota_NFC_getRichTextCSSByFontStyleID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int fontstyleID = ((int)  tolua_tonumber(tolua_S,1,0));
  std::string formatStr = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   std::string tolua_ret = (std::string)  NFC_getRichTextCSSByFontStyleID(fontstyleID,formatStr);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_getRichTextCSSByFontStyleID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_bindSelectorForBtn */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_bindSelectorForBtn00
static int tolua_Dota_NFC_bindSelectorForBtn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"SEL_MenuHandler",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int btnUIIndex = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* pParent = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  CCNode* pDelegate = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
  SEL_MenuHandler pSelector = *((SEL_MenuHandler*)  tolua_tousertype(tolua_S,4,0));
  {
   NFC_bindSelectorForBtn(btnUIIndex,pParent,pDelegate,pSelector);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_bindSelectorForBtn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_bindSelectorForDTHeroIcon */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_bindSelectorForDTHeroIcon00
static int tolua_Dota_NFC_bindSelectorForDTHeroIcon00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"SEL_MenuHandler",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int btnUIIndex = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* pParent = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  CCNode* pDelegate = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
  SEL_MenuHandler pSelector = *((SEL_MenuHandler*)  tolua_tousertype(tolua_S,4,0));
  {
   NFC_bindSelectorForDTHeroIcon(btnUIIndex,pParent,pDelegate,pSelector);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_bindSelectorForDTHeroIcon'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_bindSelectorForCellDTHeroIcon */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_bindSelectorForCellDTHeroIcon00
static int tolua_Dota_NFC_bindSelectorForCellDTHeroIcon00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"SEL_MenuHandler",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int btnUIIndex = ((int)  tolua_tonumber(tolua_S,1,0));
  int cellIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  CCNode* pParent = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
  CCNode* pDelegate = ((CCNode*)  tolua_tousertype(tolua_S,4,0));
  SEL_MenuHandler pSelector = *((SEL_MenuHandler*)  tolua_tousertype(tolua_S,5,0));
  {
   NFC_bindSelectorForCellDTHeroIcon(btnUIIndex,cellIndex,pParent,pDelegate,pSelector);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_bindSelectorForCellDTHeroIcon'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_bindSelectotForCellBtn */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_bindSelectotForCellBtn00
static int tolua_Dota_NFC_bindSelectotForCellBtn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"SEL_MenuHandler",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int btnUIIndex = ((int)  tolua_tonumber(tolua_S,1,0));
  int cellIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  CCNode* pParent = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
  CCNode* pDelegate = ((CCNode*)  tolua_tousertype(tolua_S,4,0));
  SEL_MenuHandler pSelector = *((SEL_MenuHandler*)  tolua_tousertype(tolua_S,5,0));
  {
   NFC_bindSelectotForCellBtn(btnUIIndex,cellIndex,pParent,pDelegate,pSelector);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_bindSelectotForCellBtn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_bindSelectorForTouchSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_bindSelectorForTouchSprite00
static int tolua_Dota_NFC_bindSelectorForTouchSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CTouchSpriteDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int btnUIIndex = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* pParent = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  CTouchSpriteDelegate* pDelegate = ((CTouchSpriteDelegate*)  tolua_tousertype(tolua_S,3,0));
  {
   NFC_bindSelectorForTouchSprite(btnUIIndex,pParent,pDelegate);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_bindSelectorForTouchSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_bindMenuSpriteAttachParams */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_bindMenuSpriteAttachParams00
static int tolua_Dota_NFC_bindMenuSpriteAttachParams00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,6,&tolua_err) || !tolua_isusertype(tolua_S,6,"SEL_MenuHandler",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int btnUIIndex = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* pParant = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int attachPatam1 = ((int)  tolua_tonumber(tolua_S,3,0));
  int attachParam2 = ((int)  tolua_tonumber(tolua_S,4,0));
  CCNode* pDelegate = ((CCNode*)  tolua_tousertype(tolua_S,5,0));
  SEL_MenuHandler pSelector = *((SEL_MenuHandler*)  tolua_tousertype(tolua_S,6,0));
  {
   NFC_bindMenuSpriteAttachParams(btnUIIndex,pParant,attachPatam1,attachParam2,pDelegate,pSelector);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_bindMenuSpriteAttachParams'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setMenuSpriteAttachParam */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setMenuSpriteAttachParam00
static int tolua_Dota_NFC_setMenuSpriteAttachParam00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int uiIndex = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* pParant = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int attachParam1 = ((int)  tolua_tonumber(tolua_S,3,0));
  int attachParam2 = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   NFC_setMenuSpriteAttachParam(uiIndex,pParant,attachParam1,attachParam2);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setMenuSpriteAttachParam'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setTabMenuState */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setTabMenuState00
static int tolua_Dota_NFC_setTabMenuState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int tabUIIndex = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* pParent = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  bool isSelectAble = ((bool)  tolua_toboolean(tolua_S,3,0));
  {
   NFC_setTabMenuState(tabUIIndex,pParent,isSelectAble);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setTabMenuState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setMenuEnable */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setMenuEnable00
static int tolua_Dota_NFC_setMenuEnable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int uiIndex = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* pParent = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  bool isEnable = ((bool)  tolua_toboolean(tolua_S,3,0));
  {
   NFC_setMenuEnable(uiIndex,pParent,isEnable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setMenuEnable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setNodeVisable */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setNodeVisable00
static int tolua_Dota_NFC_setNodeVisable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int btnUIIndex = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* pParent = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  bool isVisiable = ((bool)  tolua_toboolean(tolua_S,3,0));
  {
   NFC_setNodeVisable(btnUIIndex,pParent,isVisiable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setNodeVisable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setTimeLabel */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setTimeLabel00
static int tolua_Dota_NFC_setTimeLabel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CTimerEventProtocol",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int uiIndex = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* pParent = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  CTimerEventProtocol* pDelegate = ((CTimerEventProtocol*)  tolua_tousertype(tolua_S,3,0));
  int timeDistance = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   NFC_setTimeLabel(uiIndex,pParent,pDelegate,timeDistance);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setTimeLabel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_createLabelByViewData */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_createLabelByViewData00
static int tolua_Dota_NFC_createLabelByViewData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const UIViewData",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* parentNode = ((CCNode*)  tolua_tousertype(tolua_S,1,0));
  const UIViewData* dd = ((const UIViewData*)  tolua_tousertype(tolua_S,2,0));
  {
   CCLabelTTF* tolua_ret = (CCLabelTTF*)  NFC_createLabelByViewData(parentNode,*dd);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCLabelTTF");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_createLabelByViewData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_createLabelMutilineByViewData */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_createLabelMutilineByViewData00
static int tolua_Dota_NFC_createLabelMutilineByViewData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const UIViewData",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* parentNode = ((CCNode*)  tolua_tousertype(tolua_S,1,0));
  const UIViewData* dd = ((const UIViewData*)  tolua_tousertype(tolua_S,2,0));
  {
   CCLabelTTF* tolua_ret = (CCLabelTTF*)  NFC_createLabelMutilineByViewData(parentNode,*dd);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCLabelTTF");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_createLabelMutilineByViewData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_getHeightOfLabel */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_getHeightOfLabel00
static int tolua_Dota_NFC_getHeightOfLabel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float maxwidth = ((float)  tolua_tonumber(tolua_S,1,0));
  std::string txt = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   float tolua_ret = (float)  NFC_getHeightOfLabel(maxwidth,txt);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_getHeightOfLabel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_refreshTableView */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_refreshTableView00
static int tolua_Dota_NFC_refreshTableView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableView* tb = ((CCTableView*)  tolua_tousertype(tolua_S,1,0));
  {
   NFC_refreshTableView(tb);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_refreshTableView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setOffsetForTableView */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setOffsetForTableView00
static int tolua_Dota_NFC_setOffsetForTableView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableView* tb = ((CCTableView*)  tolua_tousertype(tolua_S,1,0));
  const CCPoint* offset = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
  {
   NFC_setOffsetForTableView(tb,*offset);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setOffsetForTableView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_refreshTableViewAndSetOldOffset */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_refreshTableViewAndSetOldOffset00
static int tolua_Dota_NFC_refreshTableViewAndSetOldOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCTableView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCTableView* tb = ((CCTableView*)  tolua_tousertype(tolua_S,1,0));
  {
   NFC_refreshTableViewAndSetOldOffset(tb);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_refreshTableViewAndSetOldOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_refreshScrollView */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_refreshScrollView00
static int tolua_Dota_NFC_refreshScrollView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCScrollView* ss = ((CCScrollView*)  tolua_tousertype(tolua_S,1,0));
  {
   NFC_refreshScrollView(ss);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_refreshScrollView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setPicForCCSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setPicForCCSprite00
static int tolua_Dota_NFC_setPicForCCSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int key = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* root = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  const char* file = ((const char*)  tolua_tostring(tolua_S,3,0));
  bool visible = ((bool)  tolua_toboolean(tolua_S,4,0));
  {
   NFC_setPicForCCSprite(key,root,file,visible);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setPicForCCSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setPicForCCSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setPicForCCSprite01
static int tolua_Dota_NFC_setPicForCCSprite01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int key = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* root = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  const char* file = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   NFC_setPicForCCSprite(key,root,file);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Dota_NFC_setPicForCCSprite00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setPicForCCSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setPicForCCSprite02
static int tolua_Dota_NFC_setPicForCCSprite02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int key = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* root = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  std::string file = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  bool visable = ((bool)  tolua_toboolean(tolua_S,4,0));
  {
   NFC_setPicForCCSprite(key,root,file,visable);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Dota_NFC_setPicForCCSprite01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setPicForCCSprite_2 */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setPicForCCSprite_200
static int tolua_Dota_NFC_setPicForCCSprite_200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSprite* cc = ((CCSprite*)  tolua_tousertype(tolua_S,1,0));
  const char* file = ((const char*)  tolua_tostring(tolua_S,2,0));
  bool visible = ((bool)  tolua_toboolean(tolua_S,3,true));
  {
   NFC_setPicForCCSprite_2(cc,file,visible);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setPicForCCSprite_2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setPicScale */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setPicScale00
static int tolua_Dota_NFC_setPicScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int tag = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* parent = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  float scale = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   NFC_setPicScale(tag,parent,scale);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setPicScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_getHeightOfSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_getHeightOfSprite00
static int tolua_Dota_NFC_getHeightOfSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* file = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   float tolua_ret = (float)  NFC_getHeightOfSprite(file);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_getHeightOfSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setSpriteFlipX */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setSpriteFlipX00
static int tolua_Dota_NFC_setSpriteFlipX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int UIIndex = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* pParent = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  bool isFlipX = ((bool)  tolua_toboolean(tolua_S,3,0));
  {
   NFC_setSpriteFlipX(UIIndex,pParent,isFlipX);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setSpriteFlipX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setSpriteFlipY */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setSpriteFlipY00
static int tolua_Dota_NFC_setSpriteFlipY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int UIIndex = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* pParent = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  bool isFlipY = ((bool)  tolua_toboolean(tolua_S,3,0));
  {
   NFC_setSpriteFlipY(UIIndex,pParent,isFlipY);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setSpriteFlipY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_createSpriteByViewData */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_createSpriteByViewData00
static int tolua_Dota_NFC_createSpriteByViewData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const UIViewData",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* parentNode = ((CCNode*)  tolua_tousertype(tolua_S,1,0));
  const UIViewData* dd = ((const UIViewData*)  tolua_tousertype(tolua_S,2,0));
  {
   CCSprite* tolua_ret = (CCSprite*)  NFC_createSpriteByViewData(parentNode,*dd);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_createSpriteByViewData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_getSizeFromSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_getSizeFromSprite00
static int tolua_Dota_NFC_getSizeFromSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int key = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* root = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  {
   const CCSize& tolua_ret = (const CCSize&)  NFC_getSizeFromSprite(key,root);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_getSizeFromSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_changeImageForCSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_changeImageForCSprite00
static int tolua_Dota_NFC_changeImageForCSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int key = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* root = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  unsigned int idx = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  {
   NFC_changeImageForCSprite(key,root,idx);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_changeImageForCSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setSpriteColor */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setSpriteColor00
static int tolua_Dota_NFC_setSpriteColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int uiIndex = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* pRoot = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  ccColor3B* color = ((ccColor3B*)  tolua_tousertype(tolua_S,3,0));
  {
   NFC_setSpriteColor(uiIndex,pRoot,*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setSpriteColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setGrapSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setGrapSprite00
static int tolua_Dota_NFC_setGrapSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int uiIndex = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* pRoot = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  bool isGrapEnable = ((bool)  tolua_toboolean(tolua_S,3,0));
  {
   NFC_setGrapSprite(uiIndex,pRoot,isGrapEnable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setGrapSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setEnabledForMenuItem */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setEnabledForMenuItem00
static int tolua_Dota_NFC_setEnabledForMenuItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int key = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* root = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  bool isEnabled = ((bool)  tolua_toboolean(tolua_S,3,0));
  {
   NFC_setEnabledForMenuItem(key,root,isEnabled);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setEnabledForMenuItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setEnabledForMenuItem */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setEnabledForMenuItem01
static int tolua_Dota_NFC_setEnabledForMenuItem01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int menutag = ((int)  tolua_tonumber(tolua_S,1,0));
  int itemtag = ((int)  tolua_tonumber(tolua_S,2,0));
  CCNode* parent = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
  bool enable = ((bool)  tolua_toboolean(tolua_S,4,0));
  {
   NFC_setEnabledForMenuItem(menutag,itemtag,parent,enable);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Dota_NFC_setEnabledForMenuItem00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_getMenuItem */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_getMenuItem00
static int tolua_Dota_NFC_getMenuItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int key = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* root = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  {
   CCMenuItem* tolua_ret = (CCMenuItem*)  NFC_getMenuItem(key,root);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCMenuItem");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_getMenuItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_createCLabelButtonByViewData */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_createCLabelButtonByViewData00
static int tolua_Dota_NFC_createCLabelButtonByViewData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const UIViewData",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* parentNode = ((CCNode*)  tolua_tousertype(tolua_S,1,0));
  const UIViewData* dd = ((const UIViewData*)  tolua_tousertype(tolua_S,2,0));
  {
   CLabelButtonItem* tolua_ret = (CLabelButtonItem*)  NFC_createCLabelButtonByViewData(parentNode,*dd);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CLabelButtonItem");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_createCLabelButtonByViewData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_createMenuItemByViewData */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_createMenuItemByViewData00
static int tolua_Dota_NFC_createMenuItemByViewData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const UIViewData",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* parentNode = ((CCNode*)  tolua_tousertype(tolua_S,1,0));
  const UIViewData* dd = ((const UIViewData*)  tolua_tousertype(tolua_S,2,0));
  {
   CMenuItemSprite* tolua_ret = (CMenuItemSprite*)  NFC_createMenuItemByViewData(parentNode,*dd);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CMenuItemSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_createMenuItemByViewData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setNormalImageForMenuItem */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setNormalImageForMenuItem00
static int tolua_Dota_NFC_setNormalImageForMenuItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CMenuItemSprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CMenuItemSprite* cc = ((CMenuItemSprite*)  tolua_tousertype(tolua_S,1,0));
  std::string filepath = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   NFC_setNormalImageForMenuItem(cc,filepath);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setNormalImageForMenuItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setNoramlImageByUIIndex */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setNoramlImageByUIIndex00
static int tolua_Dota_NFC_setNoramlImageByUIIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int uiIndex = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* pRoot = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  std::string fileName = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  {
   NFC_setNoramlImageByUIIndex(uiIndex,pRoot,fileName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setNoramlImageByUIIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setSelectedImageForMenuItem */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setSelectedImageForMenuItem00
static int tolua_Dota_NFC_setSelectedImageForMenuItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCMenuItemSprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCMenuItemSprite* cc = ((CCMenuItemSprite*)  tolua_tousertype(tolua_S,1,0));
  std::string filepath = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   NFC_setSelectedImageForMenuItem(cc,filepath);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setSelectedImageForMenuItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setDisabledImageForMenuItem */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setDisabledImageForMenuItem00
static int tolua_Dota_NFC_setDisabledImageForMenuItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCMenuItemSprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCMenuItemSprite* cc = ((CCMenuItemSprite*)  tolua_tousertype(tolua_S,1,0));
  std::string filepath = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   NFC_setDisabledImageForMenuItem(cc,filepath);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setDisabledImageForMenuItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_getMenuItemSpriteSI */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_getMenuItemSpriteSI00
static int tolua_Dota_NFC_getMenuItemSpriteSI00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"UIViewData",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* parentNode = ((CCNode*)  tolua_tousertype(tolua_S,1,0));
  UIViewData dd = *((UIViewData*)  tolua_tousertype(tolua_S,2,0));
  {
   NFC_getMenuItemSpriteSI(parentNode,dd);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_getMenuItemSpriteSI'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setProgressForCProgressInnerBar */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setProgressForCProgressInnerBar00
static int tolua_Dota_NFC_setProgressForCProgressInnerBar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int key = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* root = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  float percent = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   NFC_setProgressForCProgressInnerBar(key,root,percent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setProgressForCProgressInnerBar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_createGuideArrow */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_createGuideArrow00
static int tolua_Dota_NFC_createGuideArrow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCSkeletonAnimation* tolua_ret = (CCSkeletonAnimation*)  NFC_createGuideArrow();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"CCSkeletonAnimation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_createGuideArrow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_createDTAwardBoardByViewData */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_createDTAwardBoardByViewData00
static int tolua_Dota_NFC_createDTAwardBoardByViewData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const UIViewData",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* parentNode = ((CCNode*)  tolua_tousertype(tolua_S,1,0));
  const UIViewData* dd = ((const UIViewData*)  tolua_tousertype(tolua_S,2,0));
  {
   DTAwardBoard* tolua_ret = (DTAwardBoard*)  NFC_createDTAwardBoardByViewData(parentNode,*dd);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DTAwardBoard");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_createDTAwardBoardByViewData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setDTHeroIcon */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setDTHeroIcon00
static int tolua_Dota_NFC_setDTHeroIcon00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int uiIndex = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* pParent = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int IconID = ((int)  tolua_tonumber(tolua_S,3,0));
  bool isVisiable = ((bool)  tolua_toboolean(tolua_S,4,0));
  {
   NFC_setDTHeroIcon(uiIndex,pParent,IconID,isVisiable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setDTHeroIcon'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setDTHeroIconVisiable */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setDTHeroIconVisiable00
static int tolua_Dota_NFC_setDTHeroIconVisiable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int uiIndex = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* pParent = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  bool isVisiable = ((bool)  tolua_toboolean(tolua_S,3,0));
  {
   NFC_setDTHeroIconVisiable(uiIndex,pParent,isVisiable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setDTHeroIconVisiable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_bindDTHeroCellSelectorAndAttahParam */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_bindDTHeroCellSelectorAndAttahParam00
static int tolua_Dota_NFC_bindDTHeroCellSelectorAndAttahParam00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"SEL_MenuHandler",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int uiIndex = ((int)  tolua_tonumber(tolua_S,1,0));
  int cellIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  CCNode* pParent = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
  CCNode* pDelegate = ((CCNode*)  tolua_tousertype(tolua_S,4,0));
  SEL_MenuHandler pSelector = *((SEL_MenuHandler*)  tolua_tousertype(tolua_S,5,0));
  int attachParam1 = ((int)  tolua_tonumber(tolua_S,6,0));
  int attachParam2 = ((int)  tolua_tonumber(tolua_S,7,0));
  {
   NFC_bindDTHeroCellSelectorAndAttahParam(uiIndex,cellIndex,pParent,pDelegate,pSelector,attachParam1,attachParam2);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_bindDTHeroCellSelectorAndAttahParam'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setDTHeroQualiy */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setDTHeroQualiy00
static int tolua_Dota_NFC_setDTHeroQualiy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int uiIndex = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* pParent = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int quality = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   NFC_setDTHeroQualiy(uiIndex,pParent,quality);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setDTHeroQualiy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NFC_setDTHeroColor */
#ifndef TOLUA_DISABLE_tolua_Dota_NFC_setDTHeroColor00
static int tolua_Dota_NFC_setDTHeroColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int uiIndex = ((int)  tolua_tonumber(tolua_S,1,0));
  CCNode* pParent = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  const ccColor3B* color3 = ((const ccColor3B*)  tolua_tousertype(tolua_S,3,0));
  {
   NFC_setDTHeroColor(uiIndex,pParent,*color3);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NFC_setDTHeroColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  DTAwardBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_DTAwardBoard_new00
static int tolua_Dota_DTAwardBoard_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DTAwardBoard",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DTAwardBoard* tolua_ret = (DTAwardBoard*)  Mtolua_new((DTAwardBoard)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DTAwardBoard");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  DTAwardBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_DTAwardBoard_new00_local
static int tolua_Dota_DTAwardBoard_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DTAwardBoard",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DTAwardBoard* tolua_ret = (DTAwardBoard*)  Mtolua_new((DTAwardBoard)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DTAwardBoard");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  DTAwardBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_DTAwardBoard_delete00
static int tolua_Dota_DTAwardBoard_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTAwardBoard",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTAwardBoard* self = (DTAwardBoard*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  DTAwardBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_DTAwardBoard_create00
static int tolua_Dota_DTAwardBoard_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DTAwardBoard",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCLabelTTF",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSprite* numBg = ((CCSprite*)  tolua_tousertype(tolua_S,2,0));
  CCLabelTTF* num = ((CCLabelTTF*)  tolua_tousertype(tolua_S,3,0));
  int priority = ((int)  tolua_tonumber(tolua_S,4,0));
  bool swallow = ((bool)  tolua_toboolean(tolua_S,5,true));
  {
   DTAwardBoard* tolua_ret = (DTAwardBoard*)  DTAwardBoard::create(numBg,num,priority,swallow);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DTAwardBoard");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  DTAwardBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_DTAwardBoard_init00
static int tolua_Dota_DTAwardBoard_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTAwardBoard",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCLabelTTF",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTAwardBoard* self = (DTAwardBoard*)  tolua_tousertype(tolua_S,1,0);
  CCSprite* numBg = ((CCSprite*)  tolua_tousertype(tolua_S,2,0));
  CCLabelTTF* num = ((CCLabelTTF*)  tolua_tousertype(tolua_S,3,0));
  int priority = ((int)  tolua_tonumber(tolua_S,4,0));
  bool swallow = ((bool)  tolua_toboolean(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(numBg,num,priority,swallow);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ChangeObject of class  DTAwardBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_DTAwardBoard_ChangeObject00
static int tolua_Dota_DTAwardBoard_ChangeObject00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTAwardBoard",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTAwardBoard* self = (DTAwardBoard*)  tolua_tousertype(tolua_S,1,0);
  int quality = ((int)  tolua_tonumber(tolua_S,2,-1));
  int iconid = ((int)  tolua_tonumber(tolua_S,3,-1));
  int num = ((int)  tolua_tonumber(tolua_S,4,-1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ChangeObject'", NULL);
#endif
  {
   self->ChangeObject(quality,iconid,num);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ChangeObject'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTarget of class  DTAwardBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_DTAwardBoard_setTarget00
static int tolua_Dota_DTAwardBoard_setTarget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTAwardBoard",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"SEL_MenuHandler",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTAwardBoard* self = (DTAwardBoard*)  tolua_tousertype(tolua_S,1,0);
  CCObject* rec = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
  SEL_MenuHandler selector = *((SEL_MenuHandler*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTarget'", NULL);
#endif
  {
   self->setTarget(rec,selector);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTarget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setTag of class  DTAwardBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_DTAwardBoard_setTag00
static int tolua_Dota_DTAwardBoard_setTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTAwardBoard",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTAwardBoard* self = (DTAwardBoard*)  tolua_tousertype(tolua_S,1,0);
  int nTag = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTag'", NULL);
#endif
  {
   self->setTag(nTag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIDX of class  DTAwardBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_DTAwardBoard_setIDX00
static int tolua_Dota_DTAwardBoard_setIDX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTAwardBoard",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTAwardBoard* self = (DTAwardBoard*)  tolua_tousertype(tolua_S,1,0);
  int idx = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIDX'", NULL);
#endif
  {
   self->setIDX(idx);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIDX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAttachParam of class  DTAwardBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_DTAwardBoard_setAttachParam00
static int tolua_Dota_DTAwardBoard_setAttachParam00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTAwardBoard",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTAwardBoard* self = (DTAwardBoard*)  tolua_tousertype(tolua_S,1,0);
  int attachParam1 = ((int)  tolua_tonumber(tolua_S,2,0));
  int attachParam2 = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAttachParam'", NULL);
#endif
  {
   self->setAttachParam(attachParam1,attachParam2);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAttachParam'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIDX of class  DTAwardBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_DTAwardBoard_getIDX00
static int tolua_Dota_DTAwardBoard_getIDX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DTAwardBoard",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DTAwardBoard* self = (const DTAwardBoard*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIDX'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getIDX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIDX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setContentScale of class  DTAwardBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_DTAwardBoard_setContentScale00
static int tolua_Dota_DTAwardBoard_setContentScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTAwardBoard",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTAwardBoard* self = (DTAwardBoard*)  tolua_tousertype(tolua_S,1,0);
  float times = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setContentScale'", NULL);
#endif
  {
   self->setContentScale(times);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setContentScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContentScale of class  DTAwardBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_DTAwardBoard_getContentScale00
static int tolua_Dota_DTAwardBoard_getContentScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTAwardBoard",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTAwardBoard* self = (DTAwardBoard*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContentScale'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getContentScale();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getContentScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getContentSize of class  DTAwardBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_DTAwardBoard_getContentSize00
static int tolua_Dota_DTAwardBoard_getContentSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DTAwardBoard",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DTAwardBoard* self = (const DTAwardBoard*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getContentSize'", NULL);
#endif
  {
   const CCSize& tolua_ret = (const CCSize&)  self->getContentSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCSize");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getContentSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPosition of class  DTAwardBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_DTAwardBoard_setPosition00
static int tolua_Dota_DTAwardBoard_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTAwardBoard",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTAwardBoard* self = (DTAwardBoard*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* newPosition = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
  {
   self->setPosition(*newPosition);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEnabled of class  DTAwardBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_DTAwardBoard_setEnabled00
static int tolua_Dota_DTAwardBoard_setEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTAwardBoard",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTAwardBoard* self = (DTAwardBoard*)  tolua_tousertype(tolua_S,1,0);
  bool bEnabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEnabled'", NULL);
#endif
  {
   self->setEnabled(bEnabled);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDisabled of class  DTAwardBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_DTAwardBoard_setDisabled00
static int tolua_Dota_DTAwardBoard_setDisabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTAwardBoard",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTAwardBoard* self = (DTAwardBoard*)  tolua_tousertype(tolua_S,1,0);
  bool bDisabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDisabled'", NULL);
#endif
  {
   self->setDisabled(bDisabled);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDisabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CallBack_ClickEquip of class  DTEquipBoardDelegate */
#ifndef TOLUA_DISABLE_tolua_Dota_DTEquipBoardDelegate_CallBack_ClickEquip00
static int tolua_Dota_DTEquipBoardDelegate_CallBack_ClickEquip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTEquipBoardDelegate",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTEquipBoardDelegate* self = (DTEquipBoardDelegate*)  tolua_tousertype(tolua_S,1,0);
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  int equipID = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CallBack_ClickEquip'", NULL);
#endif
  {
   self->CallBack_ClickEquip(type,equipID);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CallBack_ClickEquip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  DTEquipBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_DTEquipBoard_new00
static int tolua_Dota_DTEquipBoard_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DTEquipBoard",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DTEquipBoard* tolua_ret = (DTEquipBoard*)  Mtolua_new((DTEquipBoard)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DTEquipBoard");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  DTEquipBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_DTEquipBoard_new00_local
static int tolua_Dota_DTEquipBoard_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DTEquipBoard",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DTEquipBoard* tolua_ret = (DTEquipBoard*)  Mtolua_new((DTEquipBoard)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DTEquipBoard");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  DTEquipBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_DTEquipBoard_delete00
static int tolua_Dota_DTEquipBoard_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTEquipBoard",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTEquipBoard* self = (DTEquipBoard*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  DTEquipBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_DTEquipBoard_create00
static int tolua_Dota_DTEquipBoard_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DTEquipBoard",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCLabelTTF",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCSprite* hint = ((CCSprite*)  tolua_tousertype(tolua_S,2,0));
  CCSprite* corner = ((CCSprite*)  tolua_tousertype(tolua_S,3,0));
  CCLabelTTF* num = ((CCLabelTTF*)  tolua_tousertype(tolua_S,4,0));
  {
   DTEquipBoard* tolua_ret = (DTEquipBoard*)  DTEquipBoard::create(hint,corner,num);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DTEquipBoard");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  DTEquipBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_DTEquipBoard_init00
static int tolua_Dota_DTEquipBoard_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTEquipBoard",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCLabelTTF",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTEquipBoard* self = (DTEquipBoard*)  tolua_tousertype(tolua_S,1,0);
  CCSprite* hint = ((CCSprite*)  tolua_tousertype(tolua_S,2,0));
  CCSprite* corner = ((CCSprite*)  tolua_tousertype(tolua_S,3,0));
  CCLabelTTF* num = ((CCLabelTTF*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(hint,corner,num);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetEquip of class  DTEquipBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_DTEquipBoard_SetEquip00
static int tolua_Dota_DTEquipBoard_SetEquip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTEquipBoard",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"BagEquipData",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"DTEquipBoardDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTEquipBoard* self = (DTEquipBoard*)  tolua_tousertype(tolua_S,1,0);
  int type = ((int)  tolua_tonumber(tolua_S,2,0));
  BagEquipData* equip = ((BagEquipData*)  tolua_tousertype(tolua_S,3,0));
  DTEquipBoardDelegate* pDel = ((DTEquipBoardDelegate*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetEquip'", NULL);
#endif
  {
   self->SetEquip(type,equip,pDel);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetEquip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveEquip of class  DTEquipBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_DTEquipBoard_RemoveEquip00
static int tolua_Dota_DTEquipBoard_RemoveEquip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTEquipBoard",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTEquipBoard* self = (DTEquipBoard*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveEquip'", NULL);
#endif
  {
   self->RemoveEquip();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveEquip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPosition of class  DTEquipBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_DTEquipBoard_setPosition00
static int tolua_Dota_DTEquipBoard_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTEquipBoard",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTEquipBoard* self = (DTEquipBoard*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* newPosition = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
  {
   self->setPosition(*newPosition);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createHeroIcon of class  DTHeroIcon */
#ifndef TOLUA_DISABLE_tolua_Dota_DTHeroIcon_createHeroIcon00
static int tolua_Dota_DTHeroIcon_createHeroIcon00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DTHeroIcon",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int iconID = ((int)  tolua_tonumber(tolua_S,2,0));
  int qualiy = ((int)  tolua_tonumber(tolua_S,3,0));
  bool isLargeIcon = ((bool)  tolua_toboolean(tolua_S,4,0));
  int touchPrioty = ((int)  tolua_tonumber(tolua_S,5,0));
  {
   DTHeroIcon* tolua_ret = (DTHeroIcon*)  DTHeroIcon::createHeroIcon(iconID,qualiy,isLargeIcon,touchPrioty);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DTHeroIcon");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createHeroIcon'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setHeroIconID of class  DTHeroIcon */
#ifndef TOLUA_DISABLE_tolua_Dota_DTHeroIcon_setHeroIconID00
static int tolua_Dota_DTHeroIcon_setHeroIconID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTHeroIcon",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTHeroIcon* self = (DTHeroIcon*)  tolua_tousertype(tolua_S,1,0);
  int heroIconID = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setHeroIconID'", NULL);
#endif
  {
   self->setHeroIconID(heroIconID);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setHeroIconID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setHeroIconVisable of class  DTHeroIcon */
#ifndef TOLUA_DISABLE_tolua_Dota_DTHeroIcon_setHeroIconVisable00
static int tolua_Dota_DTHeroIcon_setHeroIconVisable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTHeroIcon",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTHeroIcon* self = (DTHeroIcon*)  tolua_tousertype(tolua_S,1,0);
  bool isVisiable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setHeroIconVisable'", NULL);
#endif
  {
   self->setHeroIconVisable(isVisiable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setHeroIconVisable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setHeroQualiy of class  DTHeroIcon */
#ifndef TOLUA_DISABLE_tolua_Dota_DTHeroIcon_setHeroQualiy00
static int tolua_Dota_DTHeroIcon_setHeroQualiy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTHeroIcon",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTHeroIcon* self = (DTHeroIcon*)  tolua_tousertype(tolua_S,1,0);
  int heroQualiy = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setHeroQualiy'", NULL);
#endif
  {
   self->setHeroQualiy(heroQualiy);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setHeroQualiy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIconScale of class  DTHeroIcon */
#ifndef TOLUA_DISABLE_tolua_Dota_DTHeroIcon_setIconScale00
static int tolua_Dota_DTHeroIcon_setIconScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTHeroIcon",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTHeroIcon* self = (DTHeroIcon*)  tolua_tousertype(tolua_S,1,0);
  float scale = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIconScale'", NULL);
#endif
  {
   self->setIconScale(scale);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIconScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setIconColor of class  DTHeroIcon */
#ifndef TOLUA_DISABLE_tolua_Dota_DTHeroIcon_setIconColor00
static int tolua_Dota_DTHeroIcon_setIconColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTHeroIcon",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor3B",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTHeroIcon* self = (DTHeroIcon*)  tolua_tousertype(tolua_S,1,0);
  const ccColor3B* color3 = ((const ccColor3B*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setIconColor'", NULL);
#endif
  {
   self->setIconColor(*color3);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setIconColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setHeroAttachParam of class  DTHeroIcon */
#ifndef TOLUA_DISABLE_tolua_Dota_DTHeroIcon_setHeroAttachParam00
static int tolua_Dota_DTHeroIcon_setHeroAttachParam00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTHeroIcon",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTHeroIcon* self = (DTHeroIcon*)  tolua_tousertype(tolua_S,1,0);
  int attachParam1 = ((int)  tolua_tonumber(tolua_S,2,0));
  int attachParam2 = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setHeroAttachParam'", NULL);
#endif
  {
   self->setHeroAttachParam(attachParam1,attachParam2);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setHeroAttachParam'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPosition of class  DTHeroIcon */
#ifndef TOLUA_DISABLE_tolua_Dota_DTHeroIcon_setPosition00
static int tolua_Dota_DTHeroIcon_setPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTHeroIcon",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTHeroIcon* self = (DTHeroIcon*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* position = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPosition'", NULL);
#endif
  {
   self->setPosition(*position);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPosition of class  DTHeroIcon */
#ifndef TOLUA_DISABLE_tolua_Dota_DTHeroIcon_getPosition00
static int tolua_Dota_DTHeroIcon_getPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTHeroIcon",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTHeroIcon* self = (DTHeroIcon*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPosition'", NULL);
#endif
  {
   const CCPoint& tolua_ret = (const CCPoint&)  self->getPosition();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMenuSelector of class  DTHeroIcon */
#ifndef TOLUA_DISABLE_tolua_Dota_DTHeroIcon_setMenuSelector00
static int tolua_Dota_DTHeroIcon_setMenuSelector00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTHeroIcon",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"SEL_MenuHandler",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTHeroIcon* self = (DTHeroIcon*)  tolua_tousertype(tolua_S,1,0);
  int uiIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  CCNode* pDelegate = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
  SEL_MenuHandler pSelector = *((SEL_MenuHandler*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMenuSelector'", NULL);
#endif
  {
   self->setMenuSelector(uiIndex,pDelegate,pSelector);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMenuSelector'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AvatarClickEvent of class  DTRoleStatusBarDelegate */
#ifndef TOLUA_DISABLE_tolua_Dota_DTRoleStatusBarDelegate_AvatarClickEvent00
static int tolua_Dota_DTRoleStatusBarDelegate_AvatarClickEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTRoleStatusBarDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTRoleStatusBarDelegate* self = (DTRoleStatusBarDelegate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AvatarClickEvent'", NULL);
#endif
  {
   self->AvatarClickEvent();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AvatarClickEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SkillClickEvent of class  DTRoleStatusBarDelegate */
#ifndef TOLUA_DISABLE_tolua_Dota_DTRoleStatusBarDelegate_SkillClickEvent00
static int tolua_Dota_DTRoleStatusBarDelegate_SkillClickEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTRoleStatusBarDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTRoleStatusBarDelegate* self = (DTRoleStatusBarDelegate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SkillClickEvent'", NULL);
#endif
  {
   self->SkillClickEvent();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SkillClickEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddTLClickEvent of class  DTRoleStatusBarDelegate */
#ifndef TOLUA_DISABLE_tolua_Dota_DTRoleStatusBarDelegate_AddTLClickEvent00
static int tolua_Dota_DTRoleStatusBarDelegate_AddTLClickEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTRoleStatusBarDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTRoleStatusBarDelegate* self = (DTRoleStatusBarDelegate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddTLClickEvent'", NULL);
#endif
  {
   self->AddTLClickEvent();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddTLClickEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  DTRoleStatusBar */
#ifndef TOLUA_DISABLE_tolua_Dota_DTRoleStatusBar_new00
static int tolua_Dota_DTRoleStatusBar_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DTRoleStatusBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DTRoleStatusBar* tolua_ret = (DTRoleStatusBar*)  Mtolua_new((DTRoleStatusBar)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DTRoleStatusBar");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  DTRoleStatusBar */
#ifndef TOLUA_DISABLE_tolua_Dota_DTRoleStatusBar_new00_local
static int tolua_Dota_DTRoleStatusBar_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DTRoleStatusBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DTRoleStatusBar* tolua_ret = (DTRoleStatusBar*)  Mtolua_new((DTRoleStatusBar)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DTRoleStatusBar");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  DTRoleStatusBar */
#ifndef TOLUA_DISABLE_tolua_Dota_DTRoleStatusBar_delete00
static int tolua_Dota_DTRoleStatusBar_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTRoleStatusBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTRoleStatusBar* self = (DTRoleStatusBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  DTRoleStatusBar */
#ifndef TOLUA_DISABLE_tolua_Dota_DTRoleStatusBar_create00
static int tolua_Dota_DTRoleStatusBar_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DTRoleStatusBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DTRoleStatusBar* tolua_ret = (DTRoleStatusBar*)  DTRoleStatusBar::create();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DTRoleStatusBar");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  DTRoleStatusBar */
#ifndef TOLUA_DISABLE_tolua_Dota_DTRoleStatusBar_init00
static int tolua_Dota_DTRoleStatusBar_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTRoleStatusBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTRoleStatusBar* self = (DTRoleStatusBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDelegate of class  DTRoleStatusBar */
#ifndef TOLUA_DISABLE_tolua_Dota_DTRoleStatusBar_setDelegate00
static int tolua_Dota_DTRoleStatusBar_setDelegate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTRoleStatusBar",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"DTRoleStatusBarDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTRoleStatusBar* self = (DTRoleStatusBar*)  tolua_tousertype(tolua_S,1,0);
  DTRoleStatusBarDelegate* pDel = ((DTRoleStatusBarDelegate*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDelegate'", NULL);
#endif
  {
   self->setDelegate(pDel);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDelegate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Tick of class  DTRoleStatusBar */
#ifndef TOLUA_DISABLE_tolua_Dota_DTRoleStatusBar_Tick00
static int tolua_Dota_DTRoleStatusBar_Tick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTRoleStatusBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTRoleStatusBar* self = (DTRoleStatusBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Tick'", NULL);
#endif
  {
   self->Tick();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Tick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Tick_Battle of class  DTRoleStatusBar */
#ifndef TOLUA_DISABLE_tolua_Dota_DTRoleStatusBar_Tick_Battle00
static int tolua_Dota_DTRoleStatusBar_Tick_Battle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTRoleStatusBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTRoleStatusBar* self = (DTRoleStatusBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Tick_Battle'", NULL);
#endif
  {
   self->Tick_Battle();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Tick_Battle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Refresh of class  DTRoleStatusBar */
#ifndef TOLUA_DISABLE_tolua_Dota_DTRoleStatusBar_Refresh00
static int tolua_Dota_DTRoleStatusBar_Refresh00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTRoleStatusBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTRoleStatusBar* self = (DTRoleStatusBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Refresh'", NULL);
#endif
  {
   self->Refresh();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Refresh'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ResetPropertyByNode of class  DTRoleStatusBar */
#ifndef TOLUA_DISABLE_tolua_Dota_DTRoleStatusBar_ResetPropertyByNode00
static int tolua_Dota_DTRoleStatusBar_ResetPropertyByNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTRoleStatusBar",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTRoleStatusBar* self = (DTRoleStatusBar*)  tolua_tousertype(tolua_S,1,0);
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ResetPropertyByNode'", NULL);
#endif
  {
   self->ResetPropertyByNode(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ResetPropertyByNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  DTTimedGrayWindow */
#ifndef TOLUA_DISABLE_tolua_Dota_DTTimedGrayWindow_new00
static int tolua_Dota_DTTimedGrayWindow_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DTTimedGrayWindow",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DTTimedGrayWindow* tolua_ret = (DTTimedGrayWindow*)  Mtolua_new((DTTimedGrayWindow)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DTTimedGrayWindow");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  DTTimedGrayWindow */
#ifndef TOLUA_DISABLE_tolua_Dota_DTTimedGrayWindow_new00_local
static int tolua_Dota_DTTimedGrayWindow_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"DTTimedGrayWindow",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   DTTimedGrayWindow* tolua_ret = (DTTimedGrayWindow*)  Mtolua_new((DTTimedGrayWindow)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DTTimedGrayWindow");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  DTTimedGrayWindow */
#ifndef TOLUA_DISABLE_tolua_Dota_DTTimedGrayWindow_delete00
static int tolua_Dota_DTTimedGrayWindow_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTTimedGrayWindow",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTTimedGrayWindow* self = (DTTimedGrayWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Init of class  DTTimedGrayWindow */
#ifndef TOLUA_DISABLE_tolua_Dota_DTTimedGrayWindow_Init00
static int tolua_Dota_DTTimedGrayWindow_Init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTTimedGrayWindow",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTTimedGrayWindow* self = (DTTimedGrayWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Init();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Load of class  DTTimedGrayWindow */
#ifndef TOLUA_DISABLE_tolua_Dota_DTTimedGrayWindow_Load00
static int tolua_Dota_DTTimedGrayWindow_Load00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTTimedGrayWindow",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTTimedGrayWindow* self = (DTTimedGrayWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Load'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Load();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Load'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Tick of class  DTTimedGrayWindow */
#ifndef TOLUA_DISABLE_tolua_Dota_DTTimedGrayWindow_Tick00
static int tolua_Dota_DTTimedGrayWindow_Tick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTTimedGrayWindow",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTTimedGrayWindow* self = (DTTimedGrayWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Tick'", NULL);
#endif
  {
   self->Tick();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Tick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Destroy of class  DTTimedGrayWindow */
#ifndef TOLUA_DISABLE_tolua_Dota_DTTimedGrayWindow_Destroy00
static int tolua_Dota_DTTimedGrayWindow_Destroy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTTimedGrayWindow",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTTimedGrayWindow* self = (DTTimedGrayWindow*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Destroy'", NULL);
#endif
  {
   self->Destroy();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Destroy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnEventHandler of class  DTTimedGrayWindow */
#ifndef TOLUA_DISABLE_tolua_Dota_DTTimedGrayWindow_OnEventHandler00
static int tolua_Dota_DTTimedGrayWindow_OnEventHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DTTimedGrayWindow",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"std::list<std::string>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DTTimedGrayWindow* self = (DTTimedGrayWindow*)  tolua_tousertype(tolua_S,1,0);
  int iEventType = ((int)  tolua_tonumber(tolua_S,2,0));
  std::list<std::string>* paramList = ((std::list<std::string>*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnEventHandler'", NULL);
#endif
  {
   self->OnEventHandler(iEventType,*paramList);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnEventHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBlurSize of class  BlurSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_BlurSprite_setBlurSize00
static int tolua_Dota_BlurSprite_setBlurSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BlurSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BlurSprite* self = (BlurSprite*)  tolua_tousertype(tolua_S,1,0);
  float size = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBlurSize'", NULL);
#endif
  {
   self->setBlurSize(size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBlurSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  BlurSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_BlurSprite_create00
static int tolua_Dota_BlurSprite_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BlurSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* pszFileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  std::string fshfilepath = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  {
   BlurSprite* tolua_ret = (BlurSprite*)  BlurSprite::create(pszFileName,fshfilepath);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BlurSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initWithTexture of class  BlurSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_BlurSprite_initWithTexture00
static int tolua_Dota_BlurSprite_initWithTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BlurSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCTexture2D",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BlurSprite* self = (BlurSprite*)  tolua_tousertype(tolua_S,1,0);
  CCTexture2D* texture = ((CCTexture2D*)  tolua_tousertype(tolua_S,2,0));
  const CCRect* rect = ((const CCRect*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initWithTexture'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->initWithTexture(texture,*rect);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initWithTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: draw of class  BlurSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_BlurSprite_draw00
static int tolua_Dota_BlurSprite_draw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BlurSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BlurSprite* self = (BlurSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'draw'", NULL);
#endif
  {
   self->draw();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'draw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initProgram of class  BlurSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_BlurSprite_initProgram00
static int tolua_Dota_BlurSprite_initProgram00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BlurSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BlurSprite* self = (BlurSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initProgram'", NULL);
#endif
  {
   self->initProgram();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initProgram'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: listenBackToForeground of class  BlurSprite */
#ifndef TOLUA_DISABLE_tolua_Dota_BlurSprite_listenBackToForeground00
static int tolua_Dota_BlurSprite_listenBackToForeground00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BlurSprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCObject",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BlurSprite* self = (BlurSprite*)  tolua_tousertype(tolua_S,1,0);
  CCObject* obj = ((CCObject*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'listenBackToForeground'", NULL);
#endif
  {
   self->listenBackToForeground(obj);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'listenBackToForeground'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  RollingBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_RollingBoard_create00
static int tolua_Dota_RollingBoard_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RollingBoard",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,7,"AnimationEffectCallBackProtocol",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,12,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,13,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string numPathTemplate = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  int picNum = ((int)  tolua_tonumber(tolua_S,3,0));
  std::string boardPath = ((std::string)  tolua_tocppstring(tolua_S,4,0));
  int resultNumber = ((int)  tolua_tonumber(tolua_S,5,0));
  float duringTime = ((float)  tolua_tonumber(tolua_S,6,0));
  AnimationEffectCallBackProtocol* pDelegate = ((AnimationEffectCallBackProtocol*)  tolua_tousertype(tolua_S,7,0));
  float distance = ((float)  tolua_tonumber(tolua_S,8,0));
  float w = ((float)  tolua_tonumber(tolua_S,9,0));
  float h = ((float)  tolua_tonumber(tolua_S,10,0));
  float rpx = ((float)  tolua_tonumber(tolua_S,11,0));
  float rpy = ((float)  tolua_tonumber(tolua_S,12,0));
  {
   RollingBoard* tolua_ret = (RollingBoard*)  RollingBoard::create(numPathTemplate,picNum,boardPath,resultNumber,duringTime,pDelegate,distance,w,h,rpx,rpy);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"RollingBoard");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  RollingBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_RollingBoard_init00
static int tolua_Dota_RollingBoard_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RollingBoard",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"std::vector<std::string>",0,&tolua_err)) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,6,"AnimationEffectCallBackProtocol",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,9,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,10,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,12,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RollingBoard* self = (RollingBoard*)  tolua_tousertype(tolua_S,1,0);
  std::vector<std::string> filePath = *((std::vector<std::string>*)  tolua_tousertype(tolua_S,2,0));
  std::string boardPath = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  int resultNumber = ((int)  tolua_tonumber(tolua_S,4,0));
  float duringTime = ((float)  tolua_tonumber(tolua_S,5,0));
  AnimationEffectCallBackProtocol* pDelegate = ((AnimationEffectCallBackProtocol*)  tolua_tousertype(tolua_S,6,0));
  float distance = ((float)  tolua_tonumber(tolua_S,7,0));
  float w = ((float)  tolua_tonumber(tolua_S,8,0));
  float h = ((float)  tolua_tonumber(tolua_S,9,0));
  float rpx = ((float)  tolua_tonumber(tolua_S,10,0));
  float rpy = ((float)  tolua_tonumber(tolua_S,11,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init(filePath,boardPath,resultNumber,duringTime,pDelegate,distance,w,h,rpx,rpy);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RegisterCallBackScript of class  RollingBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_RollingBoard_RegisterCallBackScript00
static int tolua_Dota_RollingBoard_RegisterCallBackScript00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RollingBoard",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RollingBoard* self = (RollingBoard*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION nScript = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RegisterCallBackScript'", NULL);
#endif
  {
   self->RegisterCallBackScript(nScript);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RegisterCallBackScript'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetResultNum of class  RollingBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_RollingBoard_SetResultNum00
static int tolua_Dota_RollingBoard_SetResultNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RollingBoard",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RollingBoard* self = (RollingBoard*)  tolua_tousertype(tolua_S,1,0);
  int number = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetResultNum'", NULL);
#endif
  {
   self->SetResultNum(number);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetResultNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Run of class  RollingBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_RollingBoard_Run00
static int tolua_Dota_RollingBoard_Run00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RollingBoard",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RollingBoard* self = (RollingBoard*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Run'", NULL);
#endif
  {
   self->Run();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Run'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Stop of class  RollingBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_RollingBoard_Stop00
static int tolua_Dota_RollingBoard_Stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RollingBoard",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RollingBoard* self = (RollingBoard*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Stop'", NULL);
#endif
  {
   self->Stop();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Stop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ResetZero of class  RollingBoard */
#ifndef TOLUA_DISABLE_tolua_Dota_RollingBoard_ResetZero00
static int tolua_Dota_RollingBoard_ResetZero00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RollingBoard",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RollingBoard* self = (RollingBoard*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ResetZero'", NULL);
#endif
  {
   self->ResetZero();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ResetZero'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: idx_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_get_UIViewData_idx_
static int tolua_get_UIViewData_idx_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'idx_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->idx_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: idx_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_set_UIViewData_idx_
static int tolua_set_UIViewData_idx_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'idx_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->idx_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: hide_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_get_UIViewData_hide_
static int tolua_get_UIViewData_hide_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hide_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->hide_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: hide_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_set_UIViewData_hide_
static int tolua_set_UIViewData_hide_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hide_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->hide_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: zorder_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_get_UIViewData_zorder_
static int tolua_get_UIViewData_zorder_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'zorder_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->zorder_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: zorder_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_set_UIViewData_zorder_
static int tolua_set_UIViewData_zorder_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'zorder_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->zorder_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: scale_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_get_UIViewData_scale_
static int tolua_get_UIViewData_scale_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scale_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->scale_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: scale_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_set_UIViewData_scale_
static int tolua_set_UIViewData_scale_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scale_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->scale_ = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: rotation_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_get_UIViewData_rotation_
static int tolua_get_UIViewData_rotation_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rotation_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->rotation_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: rotation_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_set_UIViewData_rotation_
static int tolua_set_UIViewData_rotation_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rotation_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->rotation_ = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: class_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_get_UIViewData_class_
static int tolua_get_UIViewData_class_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'class_'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->class_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: class_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_set_UIViewData_class_
static int tolua_set_UIViewData_class_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'class_'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->class_,(const char*)tolua_tostring(tolua_S,2,0),128-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: touchpriority_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_get_UIViewData_touchpriority_
static int tolua_get_UIViewData_touchpriority_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'touchpriority_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->touchpriority_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: touchpriority_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_set_UIViewData_touchpriority_
static int tolua_set_UIViewData_touchpriority_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'touchpriority_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->touchpriority_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: swallow_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_get_UIViewData_swallow_
static int tolua_get_UIViewData_swallow_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'swallow_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->swallow_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: swallow_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_set_UIViewData_swallow_
static int tolua_set_UIViewData_swallow_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'swallow_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->swallow_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_nFontStyleID of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_get_UIViewData_m_nFontStyleID
static int tolua_get_UIViewData_m_nFontStyleID(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_nFontStyleID'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->m_nFontStyleID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_nFontStyleID of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_set_UIViewData_m_nFontStyleID
static int tolua_set_UIViewData_m_nFontStyleID(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_nFontStyleID'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_nFontStyleID = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: labelstring_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_get_UIViewData_labelstring_
static int tolua_get_UIViewData_labelstring_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'labelstring_'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->labelstring_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: labelstring_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_set_UIViewData_labelstring_
static int tolua_set_UIViewData_labelstring_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'labelstring_'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->labelstring_ = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fontname_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_get_UIViewData_fontname_
static int tolua_get_UIViewData_fontname_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fontname_'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->fontname_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fontname_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_set_UIViewData_fontname_
static int tolua_set_UIViewData_fontname_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fontname_'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->fontname_,(const char*)tolua_tostring(tolua_S,2,0),128-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fontsize_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_get_UIViewData_fontsize_
static int tolua_get_UIViewData_fontsize_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fontsize_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->fontsize_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fontsize_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_set_UIViewData_fontsize_
static int tolua_set_UIViewData_fontsize_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fontsize_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->fontsize_ = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: colorR_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_get_UIViewData_colorR_
static int tolua_get_UIViewData_colorR_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'colorR_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->colorR_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: colorR_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_set_UIViewData_colorR_
static int tolua_set_UIViewData_colorR_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'colorR_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->colorR_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: colorG_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_get_UIViewData_colorG_
static int tolua_get_UIViewData_colorG_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'colorG_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->colorG_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: colorG_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_set_UIViewData_colorG_
static int tolua_set_UIViewData_colorG_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'colorG_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->colorG_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: colorB_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_get_UIViewData_colorB_
static int tolua_get_UIViewData_colorB_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'colorB_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->colorB_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: colorB_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_set_UIViewData_colorB_
static int tolua_set_UIViewData_colorB_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'colorB_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->colorB_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: alpha_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_get_UIViewData_alpha_
static int tolua_get_UIViewData_alpha_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'alpha_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->alpha_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: alpha_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_set_UIViewData_alpha_
static int tolua_set_UIViewData_alpha_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'alpha_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->alpha_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: filepath_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_get_UIViewData_filepath_
static int tolua_get_UIViewData_filepath_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'filepath_'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->filepath_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: filepath_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_set_UIViewData_filepath_
static int tolua_set_UIViewData_filepath_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'filepath_'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->filepath_,(const char*)tolua_tostring(tolua_S,2,0),128-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: filepath2_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_get_UIViewData_filepath2_
static int tolua_get_UIViewData_filepath2_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'filepath2_'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->filepath2_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: filepath2_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_set_UIViewData_filepath2_
static int tolua_set_UIViewData_filepath2_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'filepath2_'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->filepath2_,(const char*)tolua_tostring(tolua_S,2,0),128-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: filepath3_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_get_UIViewData_filepath3_
static int tolua_get_UIViewData_filepath3_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'filepath3_'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->filepath3_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: filepath3_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_set_UIViewData_filepath3_
static int tolua_set_UIViewData_filepath3_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'filepath3_'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->filepath3_,(const char*)tolua_tostring(tolua_S,2,0),128-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: width_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_get_UIViewData_width_
static int tolua_get_UIViewData_width_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'width_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->width_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: width_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_set_UIViewData_width_
static int tolua_set_UIViewData_width_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'width_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->width_ = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: height_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_get_UIViewData_height_
static int tolua_get_UIViewData_height_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'height_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->height_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: height_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_set_UIViewData_height_
static int tolua_set_UIViewData_height_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'height_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->height_ = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: anchorx_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_get_UIViewData_anchorx_
static int tolua_get_UIViewData_anchorx_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'anchorx_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->anchorx_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: anchorx_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_set_UIViewData_anchorx_
static int tolua_set_UIViewData_anchorx_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'anchorx_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->anchorx_ = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: anchory_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_get_UIViewData_anchory_
static int tolua_get_UIViewData_anchory_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'anchory_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->anchory_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: anchory_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_set_UIViewData_anchory_
static int tolua_set_UIViewData_anchory_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'anchory_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->anchory_ = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: posx_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_get_UIViewData_posx_
static int tolua_get_UIViewData_posx_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'posx_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->posx_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: posx_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_set_UIViewData_posx_
static int tolua_set_UIViewData_posx_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'posx_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->posx_ = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: posy_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_get_UIViewData_posy_
static int tolua_get_UIViewData_posy_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'posy_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->posy_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: posy_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_set_UIViewData_posy_
static int tolua_set_UIViewData_posy_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'posy_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->posy_ = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: soundid_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_get_UIViewData_soundid_
static int tolua_get_UIViewData_soundid_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'soundid_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->soundid_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: soundid_ of class  UIViewData */
#ifndef TOLUA_DISABLE_tolua_set_UIViewData_soundid_
static int tolua_set_UIViewData_soundid_(lua_State* tolua_S)
{
  UIViewData* self = (UIViewData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'soundid_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->soundid_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: instanceId_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_instanceId_
static int tolua_get_RoleInfoData_instanceId_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'instanceId_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->instanceId_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: instanceId_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_instanceId_
static int tolua_set_RoleInfoData_instanceId_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'instanceId_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->instanceId_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: name_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_name_
static int tolua_get_RoleInfoData_name_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->name_,"IString");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: name_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_name_
static int tolua_set_RoleInfoData_name_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"IString",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->name_ = *((IString*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: level_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_level_
static int tolua_get_RoleInfoData_level_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'level_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->level_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: level_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_level_
static int tolua_set_RoleInfoData_level_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'level_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->level_ = ((short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: exp_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_exp_
static int tolua_get_RoleInfoData_exp_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'exp_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->exp_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: exp_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_exp_
static int tolua_set_RoleInfoData_exp_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'exp_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->exp_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maxExp_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_maxExp_
static int tolua_get_RoleInfoData_maxExp_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxExp_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->maxExp_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: maxExp_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_maxExp_
static int tolua_set_RoleInfoData_maxExp_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxExp_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->maxExp_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: vitality_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_vitality_
static int tolua_get_RoleInfoData_vitality_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'vitality_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->vitality_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: vitality_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_vitality_
static int tolua_set_RoleInfoData_vitality_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'vitality_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->vitality_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maxVitality_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_maxVitality_
static int tolua_get_RoleInfoData_maxVitality_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxVitality_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->maxVitality_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: maxVitality_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_maxVitality_
static int tolua_set_RoleInfoData_maxVitality_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxVitality_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->maxVitality_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: jewels_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_jewels_
static int tolua_get_RoleInfoData_jewels_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'jewels_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->jewels_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: jewels_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_jewels_
static int tolua_set_RoleInfoData_jewels_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'jewels_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->jewels_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: money_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_money_
static int tolua_get_RoleInfoData_money_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'money_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->money_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: money_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_money_
static int tolua_set_RoleInfoData_money_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'money_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->money_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: vipLevel_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_vipLevel_
static int tolua_get_RoleInfoData_vipLevel_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'vipLevel_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->vipLevel_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: vipLevel_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_vipLevel_
static int tolua_set_RoleInfoData_vipLevel_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'vipLevel_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->vipLevel_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: btlCapacity_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_btlCapacity_
static int tolua_get_RoleInfoData_btlCapacity_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'btlCapacity_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->btlCapacity_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: btlCapacity_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_btlCapacity_
static int tolua_set_RoleInfoData_btlCapacity_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'btlCapacity_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->btlCapacity_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: prestige_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_prestige_
static int tolua_get_RoleInfoData_prestige_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'prestige_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->prestige_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: prestige_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_prestige_
static int tolua_set_RoleInfoData_prestige_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'prestige_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->prestige_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: heroLevel_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_heroLevel_
static int tolua_get_RoleInfoData_heroLevel_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'heroLevel_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->heroLevel_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: heroLevel_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_heroLevel_
static int tolua_set_RoleInfoData_heroLevel_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'heroLevel_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->heroLevel_ = ((short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE


/* get function: honorLevel_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_honorLevel_
static int tolua_get_RoleInfoData_honorLevel_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'honorLevel_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->honorLevel_,"UShort");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: honorLevel_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_honorLevel_
static int tolua_set_RoleInfoData_honorLevel_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'honorLevel_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"UShort",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->honorLevel_ = *((UShort*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: honorExp_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_honorExp_
static int tolua_get_RoleInfoData_honorExp_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'honorExp_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->honorExp_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: honorExp_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_honorExp_
static int tolua_set_RoleInfoData_honorExp_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'honorExp_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->honorExp_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: honorMaxExp_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_honorMaxExp_
static int tolua_get_RoleInfoData_honorMaxExp_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'honorMaxExp_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->honorMaxExp_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: honorMaxExp_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_honorMaxExp_
static int tolua_set_RoleInfoData_honorMaxExp_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'honorMaxExp_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->honorMaxExp_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mapId_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_mapId_
static int tolua_get_RoleInfoData_mapId_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mapId_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->mapId_,"UShort");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mapId_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_mapId_
static int tolua_set_RoleInfoData_mapId_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mapId_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"UShort",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mapId_ = *((UShort*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: stageId_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_stageId_
static int tolua_get_RoleInfoData_stageId_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'stageId_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->stageId_,"UShort");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: stageId_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_stageId_
static int tolua_set_RoleInfoData_stageId_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'stageId_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"UShort",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->stageId_ = *((UShort*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: pvpRank_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_pvpRank_
static int tolua_get_RoleInfoData_pvpRank_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pvpRank_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->pvpRank_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: pvpRank_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_pvpRank_
static int tolua_set_RoleInfoData_pvpRank_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pvpRank_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->pvpRank_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: guideStep_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_guideStep_
static int tolua_get_RoleInfoData_guideStep_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'guideStep_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->guideStep_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: guideStep_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_guideStep_
static int tolua_set_RoleInfoData_guideStep_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'guideStep_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->guideStep_ = ((short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: functionGuide_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_functionGuide_
static int tolua_get_RoleInfoData_functionGuide_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'functionGuide_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->functionGuide_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: functionGuide_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_functionGuide_
static int tolua_set_RoleInfoData_functionGuide_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'functionGuide_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->functionGuide_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: finishTaskCounts_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_finishTaskCounts_
static int tolua_get_RoleInfoData_finishTaskCounts_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'finishTaskCounts_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->finishTaskCounts_,"IByte");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: finishTaskCounts_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_finishTaskCounts_
static int tolua_set_RoleInfoData_finishTaskCounts_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'finishTaskCounts_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"IByte",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->finishTaskCounts_ = *((IByte*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: unReadEmailCounts_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_unReadEmailCounts_
static int tolua_get_RoleInfoData_unReadEmailCounts_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'unReadEmailCounts_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->unReadEmailCounts_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: unReadEmailCounts_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_unReadEmailCounts_
static int tolua_set_RoleInfoData_unReadEmailCounts_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'unReadEmailCounts_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->unReadEmailCounts_ = ((short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: leftFreeRevenueCount_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_leftFreeRevenueCount_
static int tolua_get_RoleInfoData_leftFreeRevenueCount_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'leftFreeRevenueCount_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->leftFreeRevenueCount_,"IByte");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: leftFreeRevenueCount_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_leftFreeRevenueCount_
static int tolua_set_RoleInfoData_leftFreeRevenueCount_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'leftFreeRevenueCount_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"IByte",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->leftFreeRevenueCount_ = *((IByte*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: shopTipsNum_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_shopTipsNum_
static int tolua_get_RoleInfoData_shopTipsNum_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'shopTipsNum_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->shopTipsNum_,"IByte");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: shopTipsNum_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_shopTipsNum_
static int tolua_set_RoleInfoData_shopTipsNum_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'shopTipsNum_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"IByte",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->shopTipsNum_ = *((IByte*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: heroCapaScore_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_heroCapaScore_
static int tolua_get_RoleInfoData_heroCapaScore_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'heroCapaScore_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->heroCapaScore_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: heroCapaScore_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_heroCapaScore_
static int tolua_set_RoleInfoData_heroCapaScore_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'heroCapaScore_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->heroCapaScore_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: equipCapaScore_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_equipCapaScore_
static int tolua_get_RoleInfoData_equipCapaScore_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'equipCapaScore_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->equipCapaScore_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: equipCapaScore_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_equipCapaScore_
static int tolua_set_RoleInfoData_equipCapaScore_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'equipCapaScore_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->equipCapaScore_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: slaveIdentity_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_slaveIdentity_
static int tolua_get_RoleInfoData_slaveIdentity_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'slaveIdentity_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->slaveIdentity_,"IByte");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: slaveIdentity_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_slaveIdentity_
static int tolua_set_RoleInfoData_slaveIdentity_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'slaveIdentity_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"IByte",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->slaveIdentity_ = *((IByte*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: applyforFriendNum_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_applyforFriendNum_
static int tolua_get_RoleInfoData_applyforFriendNum_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'applyforFriendNum_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->applyforFriendNum_,"IByte");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: applyforFriendNum_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_applyforFriendNum_
static int tolua_set_RoleInfoData_applyforFriendNum_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'applyforFriendNum_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"IByte",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->applyforFriendNum_ = *((IByte*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: rewardprompt_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_rewardprompt_
static int tolua_get_RoleInfoData_rewardprompt_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rewardprompt_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->rewardprompt_,"IByte");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: rewardprompt_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_rewardprompt_
static int tolua_set_RoleInfoData_rewardprompt_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rewardprompt_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"IByte",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->rewardprompt_ = *((IByte*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: activityprompt_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_activityprompt_
static int tolua_get_RoleInfoData_activityprompt_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'activityprompt_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->activityprompt_,"IByte");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: activityprompt_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_activityprompt_
static int tolua_set_RoleInfoData_activityprompt_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'activityprompt_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"IByte",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->activityprompt_ = *((IByte*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mineralempty_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_mineralempty_
static int tolua_get_RoleInfoData_mineralempty_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mineralempty_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->mineralempty_,"IByte");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mineralempty_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_mineralempty_
static int tolua_set_RoleInfoData_mineralempty_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mineralempty_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"IByte",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mineralempty_ = *((IByte*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: freesupplica_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_freesupplica_
static int tolua_get_RoleInfoData_freesupplica_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'freesupplica_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->freesupplica_,"IByte");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: freesupplica_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_freesupplica_
static int tolua_set_RoleInfoData_freesupplica_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'freesupplica_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"IByte",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->freesupplica_ = *((IByte*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: vipreward_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_vipreward_
static int tolua_get_RoleInfoData_vipreward_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'vipreward_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->vipreward_,"IByte");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: vipreward_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_vipreward_
static int tolua_set_RoleInfoData_vipreward_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'vipreward_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"IByte",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->vipreward_ = *((IByte*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bossCanPlay_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_bossCanPlay_
static int tolua_get_RoleInfoData_bossCanPlay_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bossCanPlay_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->bossCanPlay_,"IByte");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bossCanPlay_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_bossCanPlay_
static int tolua_set_RoleInfoData_bossCanPlay_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bossCanPlay_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"IByte",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bossCanPlay_ = *((IByte*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: arena_awardCanReceive_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_arena_awardCanReceive_
static int tolua_get_RoleInfoData_arena_awardCanReceive_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'arena_awardCanReceive_'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->arena_awardCanReceive_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: arena_awardCanReceive_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_arena_awardCanReceive_
static int tolua_set_RoleInfoData_arena_awardCanReceive_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'arena_awardCanReceive_'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->arena_awardCanReceive_ = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: freesummon_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_freesummon_
static int tolua_get_RoleInfoData_freesummon_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'freesummon_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->freesummon_,"IByte");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: freesummon_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_freesummon_
static int tolua_set_RoleInfoData_freesummon_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'freesummon_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"IByte",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->freesummon_ = *((IByte*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: hasrefreshshop_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_hasrefreshshop_
static int tolua_get_RoleInfoData_hasrefreshshop_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hasrefreshshop_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->hasrefreshshop_,"IByte");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: hasrefreshshop_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_hasrefreshshop_
static int tolua_set_RoleInfoData_hasrefreshshop_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hasrefreshshop_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"IByte",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->hasrefreshshop_ = *((IByte*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: attribute_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_attribute__ptr
static int tolua_get_RoleInfoData_attribute__ptr(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attribute_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->attribute_,"Attribute");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: attribute_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_attribute__ptr
static int tolua_set_RoleInfoData_attribute__ptr(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attribute_'",NULL);
  if (!tolua_isusertype(tolua_S,2,"Attribute",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->attribute_ = ((Attribute*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: isFastAthleticSpeed of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_isFastAthleticSpeed
static int tolua_get_RoleInfoData_isFastAthleticSpeed(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'isFastAthleticSpeed'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isFastAthleticSpeed);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: isFastAthleticSpeed of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_isFastAthleticSpeed
static int tolua_set_RoleInfoData_isFastAthleticSpeed(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'isFastAthleticSpeed'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->isFastAthleticSpeed = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: athleticsSerialID_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_athleticsSerialID_
static int tolua_get_RoleInfoData_athleticsSerialID_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'athleticsSerialID_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->athleticsSerialID_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: athleticsSerialID_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_athleticsSerialID_
static int tolua_set_RoleInfoData_athleticsSerialID_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'athleticsSerialID_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->athleticsSerialID_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bHadNewHeroTips of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_bHadNewHeroTips
static int tolua_get_RoleInfoData_bHadNewHeroTips(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bHadNewHeroTips'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->bHadNewHeroTips);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bHadNewHeroTips of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_bHadNewHeroTips
static int tolua_set_RoleInfoData_bHadNewHeroTips(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bHadNewHeroTips'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bHadNewHeroTips = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: accumuRechNum of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_accumuRechNum
static int tolua_get_RoleInfoData_accumuRechNum(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'accumuRechNum'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->accumuRechNum);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: accumuRechNum of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_accumuRechNum
static int tolua_set_RoleInfoData_accumuRechNum(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'accumuRechNum'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->accumuRechNum = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: multiExp_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_multiExp_
static int tolua_get_RoleInfoData_multiExp_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'multiExp_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->multiExp_,"UShort");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: multiExp_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_multiExp_
static int tolua_set_RoleInfoData_multiExp_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'multiExp_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"UShort",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->multiExp_ = *((UShort*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: multiMoney_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoData_multiMoney_
static int tolua_get_RoleInfoData_multiMoney_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'multiMoney_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->multiMoney_,"UShort");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: multiMoney_ of class  RoleInfoData */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoData_multiMoney_
static int tolua_set_RoleInfoData_multiMoney_(lua_State* tolua_S)
{
  RoleInfoData* self = (RoleInfoData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'multiMoney_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"UShort",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->multiMoney_ = *((UShort*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: _home_more_isopen of class  PlayerStatus */
#ifndef TOLUA_DISABLE_tolua_get_PlayerStatus__home_more_isopen
static int tolua_get_PlayerStatus__home_more_isopen(lua_State* tolua_S)
{
  PlayerStatus* self = (PlayerStatus*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_home_more_isopen'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->_home_more_isopen);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: _home_more_isopen of class  PlayerStatus */
#ifndef TOLUA_DISABLE_tolua_set_PlayerStatus__home_more_isopen
static int tolua_set_PlayerStatus__home_more_isopen(lua_State* tolua_S)
{
  PlayerStatus* self = (PlayerStatus*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '_home_more_isopen'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->_home_more_isopen = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  PlayerStatus */
#ifndef TOLUA_DISABLE_tolua_Dota_PlayerStatus_new00
static int tolua_Dota_PlayerStatus_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlayerStatus",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PlayerStatus* tolua_ret = (PlayerStatus*)  Mtolua_new((PlayerStatus)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerStatus");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  PlayerStatus */
#ifndef TOLUA_DISABLE_tolua_Dota_PlayerStatus_new00_local
static int tolua_Dota_PlayerStatus_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlayerStatus",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PlayerStatus* tolua_ret = (PlayerStatus*)  Mtolua_new((PlayerStatus)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PlayerStatus");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ResetStatus of class  PlayerStatus */
#ifndef TOLUA_DISABLE_tolua_Dota_PlayerStatus_ResetStatus00
static int tolua_Dota_PlayerStatus_ResetStatus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PlayerStatus",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PlayerStatus* self = (PlayerStatus*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ResetStatus'", NULL);
#endif
  {
   self->ResetStatus();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ResetStatus'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: playerstatus_ of class  RoleInfoDataHandler */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoDataHandler_playerstatus__ptr
static int tolua_get_RoleInfoDataHandler_playerstatus__ptr(lua_State* tolua_S)
{
  RoleInfoDataHandler* self = (RoleInfoDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'playerstatus_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->playerstatus_,"PlayerStatus");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: playerstatus_ of class  RoleInfoDataHandler */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoDataHandler_playerstatus__ptr
static int tolua_set_RoleInfoDataHandler_playerstatus__ptr(lua_State* tolua_S)
{
  RoleInfoDataHandler* self = (RoleInfoDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'playerstatus_'",NULL);
  if (!tolua_isusertype(tolua_S,2,"PlayerStatus",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->playerstatus_ = ((PlayerStatus*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_pRIData of class  RoleInfoDataHandler */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoDataHandler_m_pRIData_ptr
static int tolua_get_RoleInfoDataHandler_m_pRIData_ptr(lua_State* tolua_S)
{
  RoleInfoDataHandler* self = (RoleInfoDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_pRIData'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->m_pRIData,"RoleInfoData");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_pRIData of class  RoleInfoDataHandler */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoDataHandler_m_pRIData_ptr
static int tolua_set_RoleInfoDataHandler_m_pRIData_ptr(lua_State* tolua_S)
{
  RoleInfoDataHandler* self = (RoleInfoDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_pRIData'",NULL);
  if (!tolua_isusertype(tolua_S,2,"RoleInfoData",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_pRIData = ((RoleInfoData*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: isLock of class  RoleInfoDataHandler */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoDataHandler_isLock
static int tolua_get_RoleInfoDataHandler_isLock(lua_State* tolua_S)
{
  RoleInfoDataHandler* self = (RoleInfoDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'isLock'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isLock);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: isLock of class  RoleInfoDataHandler */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoDataHandler_isLock
static int tolua_set_RoleInfoDataHandler_isLock(lua_State* tolua_S)
{
  RoleInfoDataHandler* self = (RoleInfoDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'isLock'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->isLock = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: isUpdateCapacity_ of class  RoleInfoDataHandler */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoDataHandler_isUpdateCapacity_
static int tolua_get_RoleInfoDataHandler_isUpdateCapacity_(lua_State* tolua_S)
{
  RoleInfoDataHandler* self = (RoleInfoDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'isUpdateCapacity_'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isUpdateCapacity_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: isUpdateCapacity_ of class  RoleInfoDataHandler */
#ifndef TOLUA_DISABLE_tolua_set_RoleInfoDataHandler_isUpdateCapacity_
static int tolua_set_RoleInfoDataHandler_isUpdateCapacity_(lua_State* tolua_S)
{
  RoleInfoDataHandler* self = (RoleInfoDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'isUpdateCapacity_'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->isUpdateCapacity_ = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  RoleInfoDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleInfoDataHandler_new00
static int tolua_Dota_RoleInfoDataHandler_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RoleInfoDataHandler",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   RoleInfoDataHandler* tolua_ret = (RoleInfoDataHandler*)  Mtolua_new((RoleInfoDataHandler)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"RoleInfoDataHandler");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  RoleInfoDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleInfoDataHandler_new00_local
static int tolua_Dota_RoleInfoDataHandler_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RoleInfoDataHandler",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   RoleInfoDataHandler* tolua_ret = (RoleInfoDataHandler*)  Mtolua_new((RoleInfoDataHandler)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"RoleInfoDataHandler");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  RoleInfoDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleInfoDataHandler_delete00
static int tolua_Dota_RoleInfoDataHandler_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RoleInfoDataHandler",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RoleInfoDataHandler* self = (RoleInfoDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  RoleInfoDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleInfoDataHandler_init00
static int tolua_Dota_RoleInfoDataHandler_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RoleInfoDataHandler",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RoleInfoDataHandler* self = (RoleInfoDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onDestroy of class  RoleInfoDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleInfoDataHandler_onDestroy00
static int tolua_Dota_RoleInfoDataHandler_onDestroy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RoleInfoDataHandler",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RoleInfoDataHandler* self = (RoleInfoDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onDestroy'", NULL);
#endif
  {
   self->onDestroy();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onDestroy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateRoleAthleticsSerialID of class  RoleInfoDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleInfoDataHandler_updateRoleAthleticsSerialID00
static int tolua_Dota_RoleInfoDataHandler_updateRoleAthleticsSerialID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RoleInfoDataHandler",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RoleInfoDataHandler* self = (RoleInfoDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateRoleAthleticsSerialID'", NULL);
#endif
  {
   int tolua_ret = (int)  self->updateRoleAthleticsSerialID();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateRoleAthleticsSerialID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRoleCurAthleticsSerialID of class  RoleInfoDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleInfoDataHandler_getRoleCurAthleticsSerialID00
static int tolua_Dota_RoleInfoDataHandler_getRoleCurAthleticsSerialID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RoleInfoDataHandler",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RoleInfoDataHandler* self = (RoleInfoDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRoleCurAthleticsSerialID'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getRoleCurAthleticsSerialID();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRoleCurAthleticsSerialID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: decodePacketData of class  RoleInfoDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleInfoDataHandler_decodePacketData00
static int tolua_Dota_RoleInfoDataHandler_decodePacketData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RoleInfoDataHandler",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"cobra_win::DPacket",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RoleInfoDataHandler* self = (RoleInfoDataHandler*)  tolua_tousertype(tolua_S,1,0);
  cobra_win::DPacket* packet = ((cobra_win::DPacket*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'decodePacketData'", NULL);
#endif
  {
   self->decodePacketData(*packet);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'decodePacketData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isOpenScene of class  RoleInfoDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleInfoDataHandler_isOpenScene00
static int tolua_Dota_RoleInfoDataHandler_isOpenScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RoleInfoDataHandler",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RoleInfoDataHandler* self = (RoleInfoDataHandler*)  tolua_tousertype(tolua_S,1,0);
  int limitLv = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isOpenScene'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isOpenScene(limitLv);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isOpenScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CheckNewFuncOPenGuide of class  RoleInfoDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleInfoDataHandler_CheckNewFuncOPenGuide00
static int tolua_Dota_RoleInfoDataHandler_CheckNewFuncOPenGuide00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RoleInfoDataHandler",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RoleInfoDataHandler* self = (RoleInfoDataHandler*)  tolua_tousertype(tolua_S,1,0);
  int ModuleID = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CheckNewFuncOPenGuide'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->CheckNewFuncOPenGuide(ModuleID);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CheckNewFuncOPenGuide'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ToServerFinishNewFunc of class  RoleInfoDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleInfoDataHandler_ToServerFinishNewFunc00
static int tolua_Dota_RoleInfoDataHandler_ToServerFinishNewFunc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RoleInfoDataHandler",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RoleInfoDataHandler* self = (RoleInfoDataHandler*)  tolua_tousertype(tolua_S,1,0);
  int ModuleID = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ToServerFinishNewFunc'", NULL);
#endif
  {
   self->ToServerFinishNewFunc(ModuleID);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ToServerFinishNewFunc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddTL_Request of class  RoleInfoDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleInfoDataHandler_AddTL_Request00
static int tolua_Dota_RoleInfoDataHandler_AddTL_Request00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RoleInfoDataHandler",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RoleInfoDataHandler* self = (RoleInfoDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddTL_Request'", NULL);
#endif
  {
   self->AddTL_Request();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddTL_Request'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRestTimeToFullTL of class  RoleInfoDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleInfoDataHandler_GetRestTimeToFullTL00
static int tolua_Dota_RoleInfoDataHandler_GetRestTimeToFullTL00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RoleInfoDataHandler",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RoleInfoDataHandler* self = (RoleInfoDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRestTimeToFullTL'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetRestTimeToFullTL();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRestTimeToFullTL'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaGetInstance of class  RoleInfoDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleInfoDataHandler_LuaGetInstance00
static int tolua_Dota_RoleInfoDataHandler_LuaGetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"RoleInfoDataHandler",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   RoleInfoDataHandler* tolua_ret = (RoleInfoDataHandler*)  RoleInfoDataHandler::LuaGetInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"RoleInfoDataHandler");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaGetInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __cobra_win of class  RoleInfoDataHandler */
#ifndef TOLUA_DISABLE_tolua_get_RoleInfoDataHandler___cobra_win__Singleton2_RoleInfoDataHandler___
static int tolua_get_RoleInfoDataHandler___cobra_win__Singleton2_RoleInfoDataHandler___(lua_State* tolua_S)
{
  RoleInfoDataHandler* self = (RoleInfoDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__cobra_win'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<cobra_win::Singleton2<RoleInfoDataHandler>*>(self), "cobra_win::Singleton2<RoleInfoDataHandler>");
#else
   tolua_pushusertype(tolua_S,(void*)((cobra_win::Singleton2<RoleInfoDataHandler>*)self), "cobra_win::Singleton2<RoleInfoDataHandler>");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: RegisterLuaHandler1 of class  IDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_IDataHandler_RegisterLuaHandler100
static int tolua_Dota_IDataHandler_RegisterLuaHandler100(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IDataHandler",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IDataHandler* self = (IDataHandler*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION nHandler = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RegisterLuaHandler1'", NULL);
#endif
  {
   self->RegisterLuaHandler1(nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RegisterLuaHandler1'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RegisterLuaHandler2 of class  IDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_IDataHandler_RegisterLuaHandler200
static int tolua_Dota_IDataHandler_RegisterLuaHandler200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IDataHandler",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IDataHandler* self = (IDataHandler*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION nHandler = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RegisterLuaHandler2'", NULL);
#endif
  {
   self->RegisterLuaHandler2(nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RegisterLuaHandler2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RegisterLuaHandler3 of class  IDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_IDataHandler_RegisterLuaHandler300
static int tolua_Dota_IDataHandler_RegisterLuaHandler300(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IDataHandler",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IDataHandler* self = (IDataHandler*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION nHandler = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RegisterLuaHandler3'", NULL);
#endif
  {
   self->RegisterLuaHandler3(nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RegisterLuaHandler3'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RegisterLuaHandler4 of class  IDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_IDataHandler_RegisterLuaHandler400
static int tolua_Dota_IDataHandler_RegisterLuaHandler400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IDataHandler",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IDataHandler* self = (IDataHandler*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION nHandler = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RegisterLuaHandler4'", NULL);
#endif
  {
   self->RegisterLuaHandler4(nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RegisterLuaHandler4'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RegisterLuaHandler5 of class  IDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_IDataHandler_RegisterLuaHandler500
static int tolua_Dota_IDataHandler_RegisterLuaHandler500(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IDataHandler",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IDataHandler* self = (IDataHandler*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION nHandler = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RegisterLuaHandler5'", NULL);
#endif
  {
   self->RegisterLuaHandler5(nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RegisterLuaHandler5'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RegisterLuaHandler6 of class  IDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_IDataHandler_RegisterLuaHandler600
static int tolua_Dota_IDataHandler_RegisterLuaHandler600(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IDataHandler",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IDataHandler* self = (IDataHandler*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION nHandler = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RegisterLuaHandler6'", NULL);
#endif
  {
   self->RegisterLuaHandler6(nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RegisterLuaHandler6'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RegisterLuaHandler7 of class  IDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_IDataHandler_RegisterLuaHandler700
static int tolua_Dota_IDataHandler_RegisterLuaHandler700(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IDataHandler",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IDataHandler* self = (IDataHandler*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION nHandler = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RegisterLuaHandler7'", NULL);
#endif
  {
   self->RegisterLuaHandler7(nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RegisterLuaHandler7'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RegisterLuaHandler8 of class  IDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_IDataHandler_RegisterLuaHandler800
static int tolua_Dota_IDataHandler_RegisterLuaHandler800(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IDataHandler",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IDataHandler* self = (IDataHandler*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION nHandler = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RegisterLuaHandler8'", NULL);
#endif
  {
   self->RegisterLuaHandler8(nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RegisterLuaHandler8'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RegisterLuaHandler9 of class  IDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_IDataHandler_RegisterLuaHandler900
static int tolua_Dota_IDataHandler_RegisterLuaHandler900(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IDataHandler",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IDataHandler* self = (IDataHandler*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION nHandler = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RegisterLuaHandler9'", NULL);
#endif
  {
   self->RegisterLuaHandler9(nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RegisterLuaHandler9'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RegisterLuaHandler10 of class  IDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_IDataHandler_RegisterLuaHandler1000
static int tolua_Dota_IDataHandler_RegisterLuaHandler1000(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IDataHandler",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IDataHandler* self = (IDataHandler*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION nHandler = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RegisterLuaHandler10'", NULL);
#endif
  {
   self->RegisterLuaHandler10(nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RegisterLuaHandler10'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PushInt_LuaFunc_Result of class  IDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_IDataHandler_PushInt_LuaFunc_Result00
static int tolua_Dota_IDataHandler_PushInt_LuaFunc_Result00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IDataHandler",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IDataHandler* self = (IDataHandler*)  tolua_tousertype(tolua_S,1,0);
  int ret = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PushInt_LuaFunc_Result'", NULL);
#endif
  {
   self->PushInt_LuaFunc_Result(ret);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PushInt_LuaFunc_Result'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: catogory_ of class  BagTemplateBase */
#ifndef TOLUA_DISABLE_tolua_get_BagTemplateBase_unsigned_catogory_
static int tolua_get_BagTemplateBase_unsigned_catogory_(lua_State* tolua_S)
{
  BagTemplateBase* self = (BagTemplateBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'catogory_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->catogory_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: catogory_ of class  BagTemplateBase */
#ifndef TOLUA_DISABLE_tolua_set_BagTemplateBase_unsigned_catogory_
static int tolua_set_BagTemplateBase_unsigned_catogory_(lua_State* tolua_S)
{
  BagTemplateBase* self = (BagTemplateBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'catogory_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->catogory_ = ((unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type_ of class  BagTemplateBase */
#ifndef TOLUA_DISABLE_tolua_get_BagTemplateBase_unsigned_type_
static int tolua_get_BagTemplateBase_unsigned_type_(lua_State* tolua_S)
{
  BagTemplateBase* self = (BagTemplateBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->type_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type_ of class  BagTemplateBase */
#ifndef TOLUA_DISABLE_tolua_set_BagTemplateBase_unsigned_type_
static int tolua_set_BagTemplateBase_unsigned_type_(lua_State* tolua_S)
{
  BagTemplateBase* self = (BagTemplateBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->type_ = ((unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: templateid_ of class  BagTemplateBase */
#ifndef TOLUA_DISABLE_tolua_get_BagTemplateBase_templateid_
static int tolua_get_BagTemplateBase_templateid_(lua_State* tolua_S)
{
  BagTemplateBase* self = (BagTemplateBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'templateid_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->templateid_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: templateid_ of class  BagTemplateBase */
#ifndef TOLUA_DISABLE_tolua_set_BagTemplateBase_templateid_
static int tolua_set_BagTemplateBase_templateid_(lua_State* tolua_S)
{
  BagTemplateBase* self = (BagTemplateBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'templateid_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->templateid_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: name_ of class  BagTemplateBase */
#ifndef TOLUA_DISABLE_tolua_get_BagTemplateBase_name_
static int tolua_get_BagTemplateBase_name_(lua_State* tolua_S)
{
  BagTemplateBase* self = (BagTemplateBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name_'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->name_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: name_ of class  BagTemplateBase */
#ifndef TOLUA_DISABLE_tolua_set_BagTemplateBase_name_
static int tolua_set_BagTemplateBase_name_(lua_State* tolua_S)
{
  BagTemplateBase* self = (BagTemplateBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name_'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->name_ = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: description_ of class  BagTemplateBase */
#ifndef TOLUA_DISABLE_tolua_get_BagTemplateBase_description_
static int tolua_get_BagTemplateBase_description_(lua_State* tolua_S)
{
  BagTemplateBase* self = (BagTemplateBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'description_'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->description_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: description_ of class  BagTemplateBase */
#ifndef TOLUA_DISABLE_tolua_set_BagTemplateBase_description_
static int tolua_set_BagTemplateBase_description_(lua_State* tolua_S)
{
  BagTemplateBase* self = (BagTemplateBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'description_'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->description_ = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: level_ of class  BagTemplateBase */
#ifndef TOLUA_DISABLE_tolua_get_BagTemplateBase_unsigned_level_
static int tolua_get_BagTemplateBase_unsigned_level_(lua_State* tolua_S)
{
  BagTemplateBase* self = (BagTemplateBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'level_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->level_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: level_ of class  BagTemplateBase */
#ifndef TOLUA_DISABLE_tolua_set_BagTemplateBase_unsigned_level_
static int tolua_set_BagTemplateBase_unsigned_level_(lua_State* tolua_S)
{
  BagTemplateBase* self = (BagTemplateBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'level_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->level_ = ((unsigned short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: quality_ of class  BagTemplateBase */
#ifndef TOLUA_DISABLE_tolua_get_BagTemplateBase_unsigned_quality_
static int tolua_get_BagTemplateBase_unsigned_quality_(lua_State* tolua_S)
{
  BagTemplateBase* self = (BagTemplateBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'quality_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->quality_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: quality_ of class  BagTemplateBase */
#ifndef TOLUA_DISABLE_tolua_set_BagTemplateBase_unsigned_quality_
static int tolua_set_BagTemplateBase_unsigned_quality_(lua_State* tolua_S)
{
  BagTemplateBase* self = (BagTemplateBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'quality_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->quality_ = ((unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: price_ of class  BagTemplateBase */
#ifndef TOLUA_DISABLE_tolua_get_BagTemplateBase_price_
static int tolua_get_BagTemplateBase_price_(lua_State* tolua_S)
{
  BagTemplateBase* self = (BagTemplateBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'price_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->price_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: price_ of class  BagTemplateBase */
#ifndef TOLUA_DISABLE_tolua_set_BagTemplateBase_price_
static int tolua_set_BagTemplateBase_price_(lua_State* tolua_S)
{
  BagTemplateBase* self = (BagTemplateBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'price_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->price_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: canUse_ of class  BagTemplateBase */
#ifndef TOLUA_DISABLE_tolua_get_BagTemplateBase_unsigned_canUse_
static int tolua_get_BagTemplateBase_unsigned_canUse_(lua_State* tolua_S)
{
  BagTemplateBase* self = (BagTemplateBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'canUse_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->canUse_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: canUse_ of class  BagTemplateBase */
#ifndef TOLUA_DISABLE_tolua_set_BagTemplateBase_unsigned_canUse_
static int tolua_set_BagTemplateBase_unsigned_canUse_(lua_State* tolua_S)
{
  BagTemplateBase* self = (BagTemplateBase*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'canUse_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->canUse_ = ((unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iconId_ of class  ObjectTemplate */
#ifndef TOLUA_DISABLE_tolua_get_ObjectTemplate_iconId_
static int tolua_get_ObjectTemplate_iconId_(lua_State* tolua_S)
{
  ObjectTemplate* self = (ObjectTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iconId_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iconId_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iconId_ of class  ObjectTemplate */
#ifndef TOLUA_DISABLE_tolua_set_ObjectTemplate_iconId_
static int tolua_set_ObjectTemplate_iconId_(lua_State* tolua_S)
{
  ObjectTemplate* self = (ObjectTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iconId_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iconId_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maxCount_ of class  ObjectTemplate */
#ifndef TOLUA_DISABLE_tolua_get_ObjectTemplate_unsigned_maxCount_
static int tolua_get_ObjectTemplate_unsigned_maxCount_(lua_State* tolua_S)
{
  ObjectTemplate* self = (ObjectTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxCount_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->maxCount_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: maxCount_ of class  ObjectTemplate */
#ifndef TOLUA_DISABLE_tolua_set_ObjectTemplate_unsigned_maxCount_
static int tolua_set_ObjectTemplate_unsigned_maxCount_(lua_State* tolua_S)
{
  ObjectTemplate* self = (ObjectTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxCount_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->maxCount_ = ((unsigned short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: sortIndex of class  ObjectTemplate */
#ifndef TOLUA_DISABLE_tolua_get_ObjectTemplate_sortIndex
static int tolua_get_ObjectTemplate_sortIndex(lua_State* tolua_S)
{
  ObjectTemplate* self = (ObjectTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sortIndex'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->sortIndex);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: sortIndex of class  ObjectTemplate */
#ifndef TOLUA_DISABLE_tolua_set_ObjectTemplate_sortIndex
static int tolua_set_ObjectTemplate_sortIndex(lua_State* tolua_S)
{
  ObjectTemplate* self = (ObjectTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sortIndex'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->sortIndex = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maxLevel_ of class  EquipTemplate */
#ifndef TOLUA_DISABLE_tolua_get_EquipTemplate_unsigned_maxLevel_
static int tolua_get_EquipTemplate_unsigned_maxLevel_(lua_State* tolua_S)
{
  EquipTemplate* self = (EquipTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxLevel_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->maxLevel_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: maxLevel_ of class  EquipTemplate */
#ifndef TOLUA_DISABLE_tolua_set_EquipTemplate_unsigned_maxLevel_
static int tolua_set_EquipTemplate_unsigned_maxLevel_(lua_State* tolua_S)
{
  EquipTemplate* self = (EquipTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxLevel_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->maxLevel_ = ((unsigned short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iconId_ of class  EquipTemplate */
#ifndef TOLUA_DISABLE_tolua_get_EquipTemplate_iconId_
static int tolua_get_EquipTemplate_iconId_(lua_State* tolua_S)
{
  EquipTemplate* self = (EquipTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iconId_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iconId_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iconId_ of class  EquipTemplate */
#ifndef TOLUA_DISABLE_tolua_set_EquipTemplate_iconId_
static int tolua_set_EquipTemplate_iconId_(lua_State* tolua_S)
{
  EquipTemplate* self = (EquipTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iconId_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iconId_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iconBigId_ of class  EquipTemplate */
#ifndef TOLUA_DISABLE_tolua_get_EquipTemplate_iconBigId_
static int tolua_get_EquipTemplate_iconBigId_(lua_State* tolua_S)
{
  EquipTemplate* self = (EquipTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iconBigId_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->iconBigId_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iconBigId_ of class  EquipTemplate */
#ifndef TOLUA_DISABLE_tolua_set_EquipTemplate_iconBigId_
static int tolua_set_EquipTemplate_iconBigId_(lua_State* tolua_S)
{
  EquipTemplate* self = (EquipTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iconBigId_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iconBigId_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maxCount_ of class  EquipTemplate */
#ifndef TOLUA_DISABLE_tolua_get_EquipTemplate_unsigned_maxCount_
static int tolua_get_EquipTemplate_unsigned_maxCount_(lua_State* tolua_S)
{
  EquipTemplate* self = (EquipTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxCount_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->maxCount_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: maxCount_ of class  EquipTemplate */
#ifndef TOLUA_DISABLE_tolua_set_EquipTemplate_unsigned_maxCount_
static int tolua_set_EquipTemplate_unsigned_maxCount_(lua_State* tolua_S)
{
  EquipTemplate* self = (EquipTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxCount_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->maxCount_ = ((unsigned short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: baseAttrType_ of class  EquipTemplate */
#ifndef TOLUA_DISABLE_tolua_get_EquipTemplate_unsigned_baseAttrType_
static int tolua_get_EquipTemplate_unsigned_baseAttrType_(lua_State* tolua_S)
{
  EquipTemplate* self = (EquipTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseAttrType_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->baseAttrType_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: baseAttrType_ of class  EquipTemplate */
#ifndef TOLUA_DISABLE_tolua_set_EquipTemplate_unsigned_baseAttrType_
static int tolua_set_EquipTemplate_unsigned_baseAttrType_(lua_State* tolua_S)
{
  EquipTemplate* self = (EquipTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'baseAttrType_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->baseAttrType_ = ((unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: iconid_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_get_SkinTemplate_iconid_
static int tolua_get_SkinTemplate_iconid_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iconid_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->iconid_,"std::vector<int>");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: iconid_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_set_SkinTemplate_iconid_
static int tolua_set_SkinTemplate_iconid_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'iconid_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"std::vector<int>",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->iconid_ = *((std::vector<int>*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: shapeid_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_get_SkinTemplate_shapeid_
static int tolua_get_SkinTemplate_shapeid_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'shapeid_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->shapeid_,"std::vector<int>");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: shapeid_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_set_SkinTemplate_shapeid_
static int tolua_set_SkinTemplate_shapeid_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'shapeid_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"std::vector<int>",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->shapeid_ = *((std::vector<int>*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maxCount_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_get_SkinTemplate_unsigned_maxCount_
static int tolua_get_SkinTemplate_unsigned_maxCount_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxCount_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->maxCount_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: maxCount_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_set_SkinTemplate_unsigned_maxCount_
static int tolua_set_SkinTemplate_unsigned_maxCount_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxCount_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->maxCount_ = ((unsigned short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maxEnhanceLevel_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_get_SkinTemplate_unsigned_maxEnhanceLevel_
static int tolua_get_SkinTemplate_unsigned_maxEnhanceLevel_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxEnhanceLevel_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->maxEnhanceLevel_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: maxEnhanceLevel_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_set_SkinTemplate_unsigned_maxEnhanceLevel_
static int tolua_set_SkinTemplate_unsigned_maxEnhanceLevel_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxEnhanceLevel_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->maxEnhanceLevel_ = ((unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: strConverRate_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_get_SkinTemplate_unsigned_strConverRate_
static int tolua_get_SkinTemplate_unsigned_strConverRate_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'strConverRate_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->strConverRate_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: strConverRate_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_set_SkinTemplate_unsigned_strConverRate_
static int tolua_set_SkinTemplate_unsigned_strConverRate_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'strConverRate_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->strConverRate_ = ((unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: agiConverRate_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_get_SkinTemplate_unsigned_agiConverRate_
static int tolua_get_SkinTemplate_unsigned_agiConverRate_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'agiConverRate_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->agiConverRate_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: agiConverRate_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_set_SkinTemplate_unsigned_agiConverRate_
static int tolua_set_SkinTemplate_unsigned_agiConverRate_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'agiConverRate_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->agiConverRate_ = ((unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: intConverRate_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_get_SkinTemplate_unsigned_intConverRate_
static int tolua_get_SkinTemplate_unsigned_intConverRate_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'intConverRate_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->intConverRate_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: intConverRate_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_set_SkinTemplate_unsigned_intConverRate_
static int tolua_set_SkinTemplate_unsigned_intConverRate_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'intConverRate_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->intConverRate_ = ((unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mianConverRate_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_get_SkinTemplate_unsigned_mianConverRate_
static int tolua_get_SkinTemplate_unsigned_mianConverRate_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mianConverRate_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->mianConverRate_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mianConverRate_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_set_SkinTemplate_unsigned_mianConverRate_
static int tolua_set_SkinTemplate_unsigned_mianConverRate_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mianConverRate_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mianConverRate_ = ((unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: waaponid_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_get_SkinTemplate_waaponid_
static int tolua_get_SkinTemplate_waaponid_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'waaponid_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->waaponid_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: waaponid_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_set_SkinTemplate_waaponid_
static int tolua_set_SkinTemplate_waaponid_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'waaponid_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->waaponid_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: weaponIconId_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_get_SkinTemplate_weaponIconId_
static int tolua_get_SkinTemplate_weaponIconId_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'weaponIconId_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->weaponIconId_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: weaponIconId_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_set_SkinTemplate_weaponIconId_
static int tolua_set_SkinTemplate_weaponIconId_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'weaponIconId_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->weaponIconId_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: weaponname_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_get_SkinTemplate_weaponname_
static int tolua_get_SkinTemplate_weaponname_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'weaponname_'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->weaponname_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: weaponname_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_set_SkinTemplate_weaponname_
static int tolua_set_SkinTemplate_weaponname_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'weaponname_'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->weaponname_ = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: weaponDesc_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_get_SkinTemplate_weaponDesc_
static int tolua_get_SkinTemplate_weaponDesc_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'weaponDesc_'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->weaponDesc_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: weaponDesc_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_set_SkinTemplate_weaponDesc_
static int tolua_set_SkinTemplate_weaponDesc_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'weaponDesc_'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->weaponDesc_ = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: buffId_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_get_SkinTemplate_unsigned_buffId_
static int tolua_get_SkinTemplate_unsigned_buffId_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'buffId_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->buffId_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: buffId_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_set_SkinTemplate_unsigned_buffId_
static int tolua_set_SkinTemplate_unsigned_buffId_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'buffId_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->buffId_ = ((unsigned short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: buffLevel_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_get_SkinTemplate_unsigned_buffLevel_
static int tolua_get_SkinTemplate_unsigned_buffLevel_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'buffLevel_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->buffLevel_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: buffLevel_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_set_SkinTemplate_unsigned_buffLevel_
static int tolua_set_SkinTemplate_unsigned_buffLevel_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'buffLevel_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->buffLevel_ = ((unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: buffIconId_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_get_SkinTemplate_buffIconId_
static int tolua_get_SkinTemplate_buffIconId_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'buffIconId_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->buffIconId_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: buffIconId_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_set_SkinTemplate_buffIconId_
static int tolua_set_SkinTemplate_buffIconId_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'buffIconId_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->buffIconId_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: buffName_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_get_SkinTemplate_buffName_
static int tolua_get_SkinTemplate_buffName_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'buffName_'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->buffName_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: buffName_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_set_SkinTemplate_buffName_
static int tolua_set_SkinTemplate_buffName_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'buffName_'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->buffName_ = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: buffDesc_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_get_SkinTemplate_buffDesc_
static int tolua_get_SkinTemplate_buffDesc_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'buffDesc_'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->buffDesc_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: buffDesc_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_set_SkinTemplate_buffDesc_
static int tolua_set_SkinTemplate_buffDesc_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'buffDesc_'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->buffDesc_ = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: skillId_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_get_SkinTemplate_unsigned_skillId_
static int tolua_get_SkinTemplate_unsigned_skillId_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skillId_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->skillId_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: skillId_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_set_SkinTemplate_unsigned_skillId_
static int tolua_set_SkinTemplate_unsigned_skillId_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skillId_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->skillId_ = ((unsigned short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: skllLevel_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_get_SkinTemplate_unsigned_skllLevel_
static int tolua_get_SkinTemplate_unsigned_skllLevel_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skllLevel_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->skllLevel_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: skllLevel_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_set_SkinTemplate_unsigned_skllLevel_
static int tolua_set_SkinTemplate_unsigned_skllLevel_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skllLevel_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->skllLevel_ = ((unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: skillName_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_get_SkinTemplate_skillName_
static int tolua_get_SkinTemplate_skillName_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skillName_'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->skillName_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: skillName_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_set_SkinTemplate_skillName_
static int tolua_set_SkinTemplate_skillName_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skillName_'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->skillName_ = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: skllDesc_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_get_SkinTemplate_skllDesc_
static int tolua_get_SkinTemplate_skllDesc_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skllDesc_'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->skllDesc_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: skllDesc_ of class  SkinTemplate */
#ifndef TOLUA_DISABLE_tolua_set_SkinTemplate_skllDesc_
static int tolua_set_SkinTemplate_skllDesc_(lua_State* tolua_S)
{
  SkinTemplate* self = (SkinTemplate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'skllDesc_'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->skllDesc_ = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: template_ of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_get_BagEquipData_template__ptr
static int tolua_get_BagEquipData_template__ptr(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'template_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->template_,"EquipTemplate");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: template_ of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_set_BagEquipData_template__ptr
static int tolua_set_BagEquipData_template__ptr(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'template_'",NULL);
  if (!tolua_isusertype(tolua_S,2,"EquipTemplate",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->template_ = ((EquipTemplate*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: id_ of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_get_BagEquipData_id_
static int tolua_get_BagEquipData_id_(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'id_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->id_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: id_ of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_set_BagEquipData_id_
static int tolua_set_BagEquipData_id_(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'id_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->id_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: level_ of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_get_BagEquipData_unsigned_level_
static int tolua_get_BagEquipData_unsigned_level_(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'level_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->level_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: level_ of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_set_BagEquipData_unsigned_level_
static int tolua_set_BagEquipData_unsigned_level_(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'level_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->level_ = ((unsigned short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: levelMax_ of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_get_BagEquipData_unsigned_levelMax_
static int tolua_get_BagEquipData_unsigned_levelMax_(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'levelMax_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->levelMax_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: levelMax_ of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_set_BagEquipData_unsigned_levelMax_
static int tolua_set_BagEquipData_unsigned_levelMax_(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'levelMax_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->levelMax_ = ((unsigned short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: exp_ of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_get_BagEquipData_exp_
static int tolua_get_BagEquipData_exp_(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'exp_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->exp_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: exp_ of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_set_BagEquipData_exp_
static int tolua_set_BagEquipData_exp_(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'exp_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->exp_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maxexp_ of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_get_BagEquipData_maxexp_
static int tolua_get_BagEquipData_maxexp_(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxexp_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->maxexp_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: maxexp_ of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_set_BagEquipData_maxexp_
static int tolua_set_BagEquipData_maxexp_(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxexp_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->maxexp_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: advanceLevel_ of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_get_BagEquipData_unsigned_advanceLevel_
static int tolua_get_BagEquipData_unsigned_advanceLevel_(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'advanceLevel_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->advanceLevel_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: advanceLevel_ of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_set_BagEquipData_unsigned_advanceLevel_
static int tolua_set_BagEquipData_unsigned_advanceLevel_(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'advanceLevel_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->advanceLevel_ = ((unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: advanceLevelMax_ of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_get_BagEquipData_unsigned_advanceLevelMax_
static int tolua_get_BagEquipData_unsigned_advanceLevelMax_(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'advanceLevelMax_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->advanceLevelMax_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: advanceLevelMax_ of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_set_BagEquipData_unsigned_advanceLevelMax_
static int tolua_set_BagEquipData_unsigned_advanceLevelMax_(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'advanceLevelMax_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->advanceLevelMax_ = ((unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mainAttriValue of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_get_BagEquipData_mainAttriValue
static int tolua_get_BagEquipData_mainAttriValue(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mainAttriValue'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->mainAttriValue);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mainAttriValue of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_set_BagEquipData_mainAttriValue
static int tolua_set_BagEquipData_mainAttriValue(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mainAttriValue'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mainAttriValue = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mainAttriValueMax of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_get_BagEquipData_mainAttriValueMax
static int tolua_get_BagEquipData_mainAttriValueMax(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mainAttriValueMax'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->mainAttriValueMax);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mainAttriValueMax of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_set_BagEquipData_mainAttriValueMax
static int tolua_set_BagEquipData_mainAttriValueMax(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mainAttriValueMax'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mainAttriValueMax = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: equipScore_ of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_get_BagEquipData_equipScore_
static int tolua_get_BagEquipData_equipScore_(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'equipScore_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->equipScore_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: equipScore_ of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_set_BagEquipData_equipScore_
static int tolua_set_BagEquipData_equipScore_(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'equipScore_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->equipScore_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: attribute_ of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_get_BagEquipData_attribute__ptr
static int tolua_get_BagEquipData_attribute__ptr(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attribute_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->attribute_,"Attribute");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: attribute_ of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_set_BagEquipData_attribute__ptr
static int tolua_set_BagEquipData_attribute__ptr(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attribute_'",NULL);
  if (!tolua_isusertype(tolua_S,2,"Attribute",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->attribute_ = ((Attribute*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: attributeMAX_ of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_get_BagEquipData_attributeMAX__ptr
static int tolua_get_BagEquipData_attributeMAX__ptr(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attributeMAX_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->attributeMAX_,"Attribute");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: attributeMAX_ of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_set_BagEquipData_attributeMAX__ptr
static int tolua_set_BagEquipData_attributeMAX__ptr(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'attributeMAX_'",NULL);
  if (!tolua_isusertype(tolua_S,2,"Attribute",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->attributeMAX_ = ((Attribute*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: isEquiped_ of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_get_BagEquipData_isEquiped_
static int tolua_get_BagEquipData_isEquiped_(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'isEquiped_'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isEquiped_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: isEquiped_ of class  BagEquipData */
#ifndef TOLUA_DISABLE_tolua_set_BagEquipData_isEquiped_
static int tolua_set_BagEquipData_isEquiped_(lua_State* tolua_S)
{
  BagEquipData* self = (BagEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'isEquiped_'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->isEquiped_ = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: LuaGetInstance of class  BagEquipDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_BagEquipDataHandler_LuaGetInstance00
static int tolua_Dota_BagEquipDataHandler_LuaGetInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"BagEquipDataHandler",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   BagEquipDataHandler* tolua_ret = (BagEquipDataHandler*)  BagEquipDataHandler::LuaGetInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BagEquipDataHandler");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LuaGetInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __cobra_win of class  BagEquipDataHandler */
#ifndef TOLUA_DISABLE_tolua_get_BagEquipDataHandler___cobra_win__Singleton2_BagEquipDataHandler___
static int tolua_get_BagEquipDataHandler___cobra_win__Singleton2_BagEquipDataHandler___(lua_State* tolua_S)
{
  BagEquipDataHandler* self = (BagEquipDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__cobra_win'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<cobra_win::Singleton2<BagEquipDataHandler>*>(self), "cobra_win::Singleton2<BagEquipDataHandler>");
#else
   tolua_pushusertype(tolua_S,(void*)((cobra_win::Singleton2<BagEquipDataHandler>*)self), "cobra_win::Singleton2<BagEquipDataHandler>");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: index_ of class  RoleEquipData */
#ifndef TOLUA_DISABLE_tolua_get_RoleEquipData_unsigned_index_
static int tolua_get_RoleEquipData_unsigned_index_(lua_State* tolua_S)
{
  RoleEquipData* self = (RoleEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'index_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->index_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: index_ of class  RoleEquipData */
#ifndef TOLUA_DISABLE_tolua_set_RoleEquipData_unsigned_index_
static int tolua_set_RoleEquipData_unsigned_index_(lua_State* tolua_S)
{
  RoleEquipData* self = (RoleEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'index_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->index_ = ((unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: hasEquip_ of class  RoleEquipData */
#ifndef TOLUA_DISABLE_tolua_get_RoleEquipData_unsigned_hasEquip_
static int tolua_get_RoleEquipData_unsigned_hasEquip_(lua_State* tolua_S)
{
  RoleEquipData* self = (RoleEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hasEquip_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->hasEquip_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: hasEquip_ of class  RoleEquipData */
#ifndef TOLUA_DISABLE_tolua_set_RoleEquipData_unsigned_hasEquip_
static int tolua_set_RoleEquipData_unsigned_hasEquip_(lua_State* tolua_S)
{
  RoleEquipData* self = (RoleEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hasEquip_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->hasEquip_ = ((unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: equipdata_ of class  RoleEquipData */
#ifndef TOLUA_DISABLE_tolua_get_RoleEquipData_equipdata__ptr
static int tolua_get_RoleEquipData_equipdata__ptr(lua_State* tolua_S)
{
  RoleEquipData* self = (RoleEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'equipdata_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->equipdata_,"BagEquipData");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: equipdata_ of class  RoleEquipData */
#ifndef TOLUA_DISABLE_tolua_set_RoleEquipData_equipdata__ptr
static int tolua_set_RoleEquipData_equipdata__ptr(lua_State* tolua_S)
{
  RoleEquipData* self = (RoleEquipData*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'equipdata_'",NULL);
  if (!tolua_isusertype(tolua_S,2,"BagEquipData",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->equipdata_ = ((BagEquipData*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_mapEquipList of class  RoleEquipDataHandler */
#ifndef TOLUA_DISABLE_tolua_get_RoleEquipDataHandler_m_mapEquipList
static int tolua_get_RoleEquipDataHandler_m_mapEquipList(lua_State* tolua_S)
{
  RoleEquipDataHandler* self = (RoleEquipDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_mapEquipList'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->m_mapEquipList,"std::map<int,RoleEquipData*>");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_mapEquipList of class  RoleEquipDataHandler */
#ifndef TOLUA_DISABLE_tolua_set_RoleEquipDataHandler_m_mapEquipList
static int tolua_set_RoleEquipDataHandler_m_mapEquipList(lua_State* tolua_S)
{
  RoleEquipDataHandler* self = (RoleEquipDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_mapEquipList'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"std::map<int,RoleEquipData*>",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_mapEquipList = *((std::map<int,RoleEquipData*>*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: HeroEquip_Tab_IsSelected of class  RoleEquipDataHandler */
#ifndef TOLUA_DISABLE_tolua_get_RoleEquipDataHandler_HeroEquip_Tab_IsSelected
static int tolua_get_RoleEquipDataHandler_HeroEquip_Tab_IsSelected(lua_State* tolua_S)
{
  RoleEquipDataHandler* self = (RoleEquipDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'HeroEquip_Tab_IsSelected'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->HeroEquip_Tab_IsSelected);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: HeroEquip_Tab_IsSelected of class  RoleEquipDataHandler */
#ifndef TOLUA_DISABLE_tolua_set_RoleEquipDataHandler_HeroEquip_Tab_IsSelected
static int tolua_set_RoleEquipDataHandler_HeroEquip_Tab_IsSelected(lua_State* tolua_S)
{
  RoleEquipDataHandler* self = (RoleEquipDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'HeroEquip_Tab_IsSelected'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->HeroEquip_Tab_IsSelected = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEquipById of class  RoleEquipDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleEquipDataHandler_getEquipById00
static int tolua_Dota_RoleEquipDataHandler_getEquipById00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RoleEquipDataHandler",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RoleEquipDataHandler* self = (RoleEquipDataHandler*)  tolua_tousertype(tolua_S,1,0);
  int id = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEquipById'", NULL);
#endif
  {
   BagEquipData* tolua_ret = (BagEquipData*)  self->getEquipById(id);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BagEquipData");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEquipById'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getEquipByType of class  RoleEquipDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleEquipDataHandler_getEquipByType00
static int tolua_Dota_RoleEquipDataHandler_getEquipByType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RoleEquipDataHandler",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RoleEquipDataHandler* self = (RoleEquipDataHandler*)  tolua_tousertype(tolua_S,1,0);
  int etype = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getEquipByType'", NULL);
#endif
  {
   BagEquipData* tolua_ret = (BagEquipData*)  self->getEquipByType(etype);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BagEquipData");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getEquipByType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRoleEquips of class  RoleEquipDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleEquipDataHandler_getRoleEquips00
static int tolua_Dota_RoleEquipDataHandler_getRoleEquips00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RoleEquipDataHandler",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RoleEquipDataHandler* self = (RoleEquipDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRoleEquips'", NULL);
#endif
  {
   std::vector<BagEquipData*> tolua_ret = (std::vector<BagEquipData*>)  self->getRoleEquips();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((std::vector<BagEquipData*>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"std::vector<BagEquipData*>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(std::vector<BagEquipData*>));
     tolua_pushusertype(tolua_S,tolua_obj,"std::vector<BagEquipData*>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRoleEquips'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRoleEquipsByType of class  RoleEquipDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleEquipDataHandler_getRoleEquipsByType00
static int tolua_Dota_RoleEquipDataHandler_getRoleEquipsByType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RoleEquipDataHandler",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RoleEquipDataHandler* self = (RoleEquipDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRoleEquipsByType'", NULL);
#endif
  {
   std::vector<BagEquipData*> tolua_ret = (std::vector<BagEquipData*>)  self->getRoleEquipsByType();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((std::vector<BagEquipData*>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"std::vector<BagEquipData*>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(std::vector<BagEquipData*>));
     tolua_pushusertype(tolua_S,tolua_obj,"std::vector<BagEquipData*>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRoleEquipsByType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getRoleEquipsForStrengthen of class  RoleEquipDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleEquipDataHandler_getRoleEquipsForStrengthen00
static int tolua_Dota_RoleEquipDataHandler_getRoleEquipsForStrengthen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RoleEquipDataHandler",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RoleEquipDataHandler* self = (RoleEquipDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getRoleEquipsForStrengthen'", NULL);
#endif
  {
   std::vector<BagEquipData*> tolua_ret = (std::vector<BagEquipData*>)  self->getRoleEquipsForStrengthen();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((std::vector<BagEquipData*>)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"std::vector<BagEquipData*>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(std::vector<BagEquipData*>));
     tolua_pushusertype(tolua_S,tolua_obj,"std::vector<BagEquipData*>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getRoleEquipsForStrengthen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDefaultRoleEquip_EquipLvup of class  RoleEquipDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleEquipDataHandler_GetDefaultRoleEquip_EquipLvup00
static int tolua_Dota_RoleEquipDataHandler_GetDefaultRoleEquip_EquipLvup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RoleEquipDataHandler",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RoleEquipDataHandler* self = (RoleEquipDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDefaultRoleEquip_EquipLvup'", NULL);
#endif
  {
   BagEquipData* tolua_ret = (BagEquipData*)  self->GetDefaultRoleEquip_EquipLvup();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BagEquipData");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDefaultRoleEquip_EquipLvup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CheckAllRoleEquipsCanTopup of class  RoleEquipDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleEquipDataHandler_CheckAllRoleEquipsCanTopup00
static int tolua_Dota_RoleEquipDataHandler_CheckAllRoleEquipsCanTopup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RoleEquipDataHandler",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RoleEquipDataHandler* self = (RoleEquipDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CheckAllRoleEquipsCanTopup'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->CheckAllRoleEquipsCanTopup();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CheckAllRoleEquipsCanTopup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OffEquip_Request of class  RoleEquipDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleEquipDataHandler_OffEquip_Request00
static int tolua_Dota_RoleEquipDataHandler_OffEquip_Request00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RoleEquipDataHandler",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RoleEquipDataHandler* self = (RoleEquipDataHandler*)  tolua_tousertype(tolua_S,1,0);
  int equipid = ((int)  tolua_tonumber(tolua_S,2,0));
  int heroPos = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OffEquip_Request'", NULL);
#endif
  {
   self->OffEquip_Request(equipid,heroPos);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OffEquip_Request'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: decodePacketData_OffEquip of class  RoleEquipDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleEquipDataHandler_decodePacketData_OffEquip00
static int tolua_Dota_RoleEquipDataHandler_decodePacketData_OffEquip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RoleEquipDataHandler",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"cobra_win::DPacket",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RoleEquipDataHandler* self = (RoleEquipDataHandler*)  tolua_tousertype(tolua_S,1,0);
  cobra_win::DPacket* packet = ((cobra_win::DPacket*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'decodePacketData_OffEquip'", NULL);
#endif
  {
   self->decodePacketData_OffEquip(*packet);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'decodePacketData_OffEquip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HanldeAfterOffEquip of class  RoleEquipDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleEquipDataHandler_HanldeAfterOffEquip00
static int tolua_Dota_RoleEquipDataHandler_HanldeAfterOffEquip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RoleEquipDataHandler",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RoleEquipDataHandler* self = (RoleEquipDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HanldeAfterOffEquip'", NULL);
#endif
  {
   self->HanldeAfterOffEquip();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HanldeAfterOffEquip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OffEquip_Local of class  RoleEquipDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleEquipDataHandler_OffEquip_Local00
static int tolua_Dota_RoleEquipDataHandler_OffEquip_Local00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RoleEquipDataHandler",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RoleEquipDataHandler* self = (RoleEquipDataHandler*)  tolua_tousertype(tolua_S,1,0);
  int equipType = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OffEquip_Local'", NULL);
#endif
  {
   self->OffEquip_Local(equipType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OffEquip_Local'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ChangeEquip_Request of class  RoleEquipDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleEquipDataHandler_ChangeEquip_Request00
static int tolua_Dota_RoleEquipDataHandler_ChangeEquip_Request00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RoleEquipDataHandler",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RoleEquipDataHandler* self = (RoleEquipDataHandler*)  tolua_tousertype(tolua_S,1,0);
  int equipid = ((int)  tolua_tonumber(tolua_S,2,0));
  int heroPos = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ChangeEquip_Request'", NULL);
#endif
  {
   self->ChangeEquip_Request(equipid,heroPos);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ChangeEquip_Request'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: decodePacketData_ChangeEquip of class  RoleEquipDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleEquipDataHandler_decodePacketData_ChangeEquip00
static int tolua_Dota_RoleEquipDataHandler_decodePacketData_ChangeEquip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RoleEquipDataHandler",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"cobra_win::DPacket",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RoleEquipDataHandler* self = (RoleEquipDataHandler*)  tolua_tousertype(tolua_S,1,0);
  cobra_win::DPacket* packet = ((cobra_win::DPacket*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'decodePacketData_ChangeEquip'", NULL);
#endif
  {
   self->decodePacketData_ChangeEquip(*packet);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'decodePacketData_ChangeEquip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HanldeAfterChangeEquip of class  RoleEquipDataHandler */
#ifndef TOLUA_DISABLE_tolua_Dota_RoleEquipDataHandler_HanldeAfterChangeEquip00
static int tolua_Dota_RoleEquipDataHandler_HanldeAfterChangeEquip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RoleEquipDataHandler",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RoleEquipDataHandler* self = (RoleEquipDataHandler*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HanldeAfterChangeEquip'", NULL);
#endif
  {
   self->HanldeAfterChangeEquip();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HanldeAfterChangeEquip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_Dota_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"luaUIHelper","luaUIHelper","",NULL);
  tolua_beginmodule(tolua_S,"luaUIHelper");
   tolua_function(tolua_S,"LuaGetInstance",tolua_Dota_luaUIHelper_LuaGetInstance00);
   tolua_function(tolua_S,"LuaGetInstanceName",tolua_Dota_luaUIHelper_LuaGetInstanceName00);
   tolua_function(tolua_S,"LuaGetUILayer",tolua_Dota_luaUIHelper_LuaGetUILayer00);
   tolua_function(tolua_S,"LuaGetProvideNode",tolua_Dota_luaUIHelper_LuaGetProvideNode00);
   tolua_function(tolua_S,"LuaAutoCreateNodeByTable",tolua_Dota_luaUIHelper_LuaAutoCreateNodeByTable00);
   tolua_function(tolua_S,"LuaRegisterViewFile",tolua_Dota_luaUIHelper_LuaRegisterViewFile00);
   tolua_function(tolua_S,"LuaForceClearAnimationCache",tolua_Dota_luaUIHelper_LuaForceClearAnimationCache00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"LuaSystem","LuaSystem","",NULL);
  tolua_beginmodule(tolua_S,"LuaSystem");
   tolua_function(tolua_S,"LuaGetInstance",tolua_Dota_LuaSystem_LuaGetInstance00);
   tolua_function(tolua_S,"LuaGetInstanceName",tolua_Dota_LuaSystem_LuaGetInstanceName00);
   tolua_function(tolua_S,"LuaRegisterInitScript",tolua_Dota_LuaSystem_LuaRegisterInitScript00);
   tolua_function(tolua_S,"LuaRegisterTickScript",tolua_Dota_LuaSystem_LuaRegisterTickScript00);
   tolua_function(tolua_S,"LuaRegisterDestroyScript",tolua_Dota_LuaSystem_LuaRegisterDestroyScript00);
   tolua_function(tolua_S,"LuaRegisterOnEventHandlerScript",tolua_Dota_LuaSystem_LuaRegisterOnEventHandlerScript00);
   tolua_function(tolua_S,"LuaRegisterOnPacketHandlerScript",tolua_Dota_LuaSystem_LuaRegisterOnPacketHandlerScript00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"EventHelper","EventHelper","",NULL);
  tolua_beginmodule(tolua_S,"EventHelper");
   tolua_function(tolua_S,"LuaGetInstance",tolua_Dota_EventHelper_LuaGetInstance00);
   tolua_function(tolua_S,"LuaGetInstanceName",tolua_Dota_EventHelper_LuaGetInstanceName00);
   tolua_function(tolua_S,"LuaRegisterEvent",tolua_Dota_EventHelper_LuaRegisterEvent00);
   tolua_function(tolua_S,"LuaPushEvent",tolua_Dota_EventHelper_LuaPushEvent00);
   tolua_function(tolua_S,"LuaPushEvent",tolua_Dota_EventHelper_LuaPushEvent01);
   tolua_function(tolua_S,"LuaPushEvent",tolua_Dota_EventHelper_LuaPushEvent02);
   tolua_function(tolua_S,"LuaPushEvent",tolua_Dota_EventHelper_LuaPushEvent03);
   tolua_function(tolua_S,"LuaPushEvent2",tolua_Dota_EventHelper_LuaPushEvent200);
   tolua_function(tolua_S,"LuaPushEvent2",tolua_Dota_EventHelper_LuaPushEvent201);
   tolua_function(tolua_S,"LuaPushEvent2",tolua_Dota_EventHelper_LuaPushEvent202);
   tolua_function(tolua_S,"LuaPushEvent2",tolua_Dota_EventHelper_LuaPushEvent203);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PacketHelper","PacketHelper","",NULL);
  tolua_beginmodule(tolua_S,"PacketHelper");
   tolua_function(tolua_S,"LuaGetInstance",tolua_Dota_PacketHelper_LuaGetInstance00);
   tolua_function(tolua_S,"LuaGetInstanceName",tolua_Dota_PacketHelper_LuaGetInstanceName00);
   tolua_function(tolua_S,"LuaRegisterPacket",tolua_Dota_PacketHelper_LuaRegisterPacket00);
   tolua_function(tolua_S,"LuaBuildPacket",tolua_Dota_PacketHelper_LuaBuildPacket00);
   tolua_function(tolua_S,"LuaPutByte",tolua_Dota_PacketHelper_LuaPutByte00);
   tolua_function(tolua_S,"LuaPutShort",tolua_Dota_PacketHelper_LuaPutShort00);
   tolua_function(tolua_S,"LuaPutInt",tolua_Dota_PacketHelper_LuaPutInt00);
   tolua_function(tolua_S,"LuaPutString",tolua_Dota_PacketHelper_LuaPutString00);
   tolua_function(tolua_S,"LuaSendPacket",tolua_Dota_PacketHelper_LuaSendPacket00);
   tolua_function(tolua_S,"LuaReadPn",tolua_Dota_PacketHelper_LuaReadPn00);
   tolua_function(tolua_S,"LuaReadShort",tolua_Dota_PacketHelper_LuaReadShort00);
   tolua_function(tolua_S,"LuaReadByte",tolua_Dota_PacketHelper_LuaReadByte00);
   tolua_function(tolua_S,"LuaReadInt",tolua_Dota_PacketHelper_LuaReadInt00);
   tolua_function(tolua_S,"LuaReadString",tolua_Dota_PacketHelper_LuaReadString00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"DBHelper","DBHelper","",NULL);
  tolua_beginmodule(tolua_S,"DBHelper");
   tolua_function(tolua_S,"LuaGetInstance",tolua_Dota_DBHelper_LuaGetInstance00);
   tolua_function(tolua_S,"LuaGetInstanceName",tolua_Dota_DBHelper_LuaGetInstanceName00);
   tolua_function(tolua_S,"LuaGetSysLangById",tolua_Dota_DBHelper_LuaGetSysLangById00);
   tolua_function(tolua_S,"LuaGetResourcePathByID",tolua_Dota_DBHelper_LuaGetResourcePathByID00);
   tolua_function(tolua_S,"LuaGetRoleInfoDataHandler",tolua_Dota_DBHelper_LuaGetRoleInfoDataHandler00);
   tolua_function(tolua_S,"LuaShowFlowEffect",tolua_Dota_DBHelper_LuaShowFlowEffect00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CMenuItemSprite","CMenuItemSprite","CCMenuItemSprite",tolua_collect_CMenuItemSprite);
  #else
  tolua_cclass(tolua_S,"CMenuItemSprite","CMenuItemSprite","CCMenuItemSprite",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CMenuItemSprite");
   tolua_function(tolua_S,"new",tolua_Dota_CMenuItemSprite_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_CMenuItemSprite_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_CMenuItemSprite_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_CMenuItemSprite_delete00);
   tolua_function(tolua_S,"create",tolua_Dota_CMenuItemSprite_create00);
   tolua_function(tolua_S,"init",tolua_Dota_CMenuItemSprite_init00);
   tolua_function(tolua_S,"create",tolua_Dota_CMenuItemSprite_create01);
   tolua_function(tolua_S,"initWithNormalSprite",tolua_Dota_CMenuItemSprite_initWithNormalSprite00);
   tolua_function(tolua_S,"create",tolua_Dota_CMenuItemSprite_create02);
   tolua_function(tolua_S,"initWithNormalImage",tolua_Dota_CMenuItemSprite_initWithNormalImage00);
   tolua_function(tolua_S,"create",tolua_Dota_CMenuItemSprite_create03);
   tolua_function(tolua_S,"initWithNormalImage",tolua_Dota_CMenuItemSprite_initWithNormalImage01);
   tolua_function(tolua_S,"createWithCompositeSelectedImage",tolua_Dota_CMenuItemSprite_createWithCompositeSelectedImage00);
   tolua_function(tolua_S,"initWithCompositeSelectedImage",tolua_Dota_CMenuItemSprite_initWithCompositeSelectedImage00);
   tolua_function(tolua_S,"setSelectedType",tolua_Dota_CMenuItemSprite_setSelectedType00);
   tolua_function(tolua_S,"setIDX",tolua_Dota_CMenuItemSprite_setIDX00);
   tolua_function(tolua_S,"getIDX",tolua_Dota_CMenuItemSprite_getIDX00);
   tolua_function(tolua_S,"setIsSelected",tolua_Dota_CMenuItemSprite_setIsSelected00);
   tolua_function(tolua_S,"getIsSeleted",tolua_Dota_CMenuItemSprite_getIsSeleted00);
   tolua_function(tolua_S,"setSoundID",tolua_Dota_CMenuItemSprite_setSoundID00);
   tolua_function(tolua_S,"setAttachData1",tolua_Dota_CMenuItemSprite_setAttachData100);
   tolua_function(tolua_S,"getAttachData1",tolua_Dota_CMenuItemSprite_getAttachData100);
   tolua_function(tolua_S,"setAttachData2",tolua_Dota_CMenuItemSprite_setAttachData200);
   tolua_function(tolua_S,"getAttachData2",tolua_Dota_CMenuItemSprite_getAttachData200);
   tolua_function(tolua_S,"setNormalImageAndRelocation",tolua_Dota_CMenuItemSprite_setNormalImageAndRelocation00);
   tolua_function(tolua_S,"PlaySound",tolua_Dota_CMenuItemSprite_PlaySound00);
   tolua_function(tolua_S,"Selected_Event",tolua_Dota_CMenuItemSprite_Selected_Event00);
   tolua_function(tolua_S,"UnSelected_Event",tolua_Dota_CMenuItemSprite_UnSelected_Event00);
   tolua_function(tolua_S,"UnSelected_Event_Active",tolua_Dota_CMenuItemSprite_UnSelected_Event_Active00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CLabelButtonItem","CLabelButtonItem","CMenuItemSprite",tolua_collect_CLabelButtonItem);
  #else
  tolua_cclass(tolua_S,"CLabelButtonItem","CLabelButtonItem","CMenuItemSprite",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CLabelButtonItem");
   tolua_function(tolua_S,"new",tolua_Dota_CLabelButtonItem_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_CLabelButtonItem_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_CLabelButtonItem_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_CLabelButtonItem_delete00);
   tolua_function(tolua_S,"create",tolua_Dota_CLabelButtonItem_create00);
   tolua_function(tolua_S,"init",tolua_Dota_CLabelButtonItem_init00);
   tolua_function(tolua_S,"GetLabelString",tolua_Dota_CLabelButtonItem_GetLabelString00);
   tolua_function(tolua_S,"SetLabelString",tolua_Dota_CLabelButtonItem_SetLabelString00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CPriorityMenu","CPriorityMenu","CCMenu",NULL);
  tolua_beginmodule(tolua_S,"CPriorityMenu");
   tolua_function(tolua_S,"create",tolua_Dota_CPriorityMenu_create00);
   tolua_function(tolua_S,"init",tolua_Dota_CPriorityMenu_init00);
   tolua_function(tolua_S,"registerWithTouchDispatcher",tolua_Dota_CPriorityMenu_registerWithTouchDispatcher00);
   tolua_function(tolua_S,"ccTouchBegan",tolua_Dota_CPriorityMenu_ccTouchBegan00);
   tolua_function(tolua_S,"ccTouchEnded",tolua_Dota_CPriorityMenu_ccTouchEnded00);
   tolua_function(tolua_S,"ccTouchMoved",tolua_Dota_CPriorityMenu_ccTouchMoved00);
   tolua_function(tolua_S,"ccTouchCancelled",tolua_Dota_CPriorityMenu_ccTouchCancelled00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CTabMenu","CTabMenu","CCMenu",NULL);
  tolua_beginmodule(tolua_S,"CTabMenu");
   tolua_function(tolua_S,"create",tolua_Dota_CTabMenu_create00);
   tolua_function(tolua_S,"init",tolua_Dota_CTabMenu_init00);
   tolua_function(tolua_S,"registerWithTouchDispatcher",tolua_Dota_CTabMenu_registerWithTouchDispatcher00);
   tolua_function(tolua_S,"ccTouchBegan",tolua_Dota_CTabMenu_ccTouchBegan00);
   tolua_function(tolua_S,"ccTouchEnded",tolua_Dota_CTabMenu_ccTouchEnded00);
   tolua_function(tolua_S,"ccTouchMoved",tolua_Dota_CTabMenu_ccTouchMoved00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CImmovableMenu","CImmovableMenu","CCImmovableMenu",NULL);
  tolua_beginmodule(tolua_S,"CImmovableMenu");
   tolua_function(tolua_S,"create",tolua_Dota_CImmovableMenu_create00);
   tolua_function(tolua_S,"init",tolua_Dota_CImmovableMenu_init00);
   tolua_function(tolua_S,"registerWithTouchDispatcher",tolua_Dota_CImmovableMenu_registerWithTouchDispatcher00);
   tolua_function(tolua_S,"ccTouchBegan",tolua_Dota_CImmovableMenu_ccTouchBegan00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CTabImmovableMenu","CTabImmovableMenu","CImmovableMenu",NULL);
  tolua_beginmodule(tolua_S,"CTabImmovableMenu");
   tolua_function(tolua_S,"create",tolua_Dota_CTabImmovableMenu_create00);
   tolua_function(tolua_S,"init",tolua_Dota_CTabImmovableMenu_init00);
   tolua_function(tolua_S,"ccTouchBegan",tolua_Dota_CTabImmovableMenu_ccTouchBegan00);
   tolua_function(tolua_S,"ccTouchEnded",tolua_Dota_CTabImmovableMenu_ccTouchEnded00);
   tolua_function(tolua_S,"ccTouchMoved",tolua_Dota_CTabImmovableMenu_ccTouchMoved00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ArtFontLabelBatchNode","ArtFontLabelBatchNode","BaseObject",tolua_collect_ArtFontLabelBatchNode);
  #else
  tolua_cclass(tolua_S,"ArtFontLabelBatchNode","ArtFontLabelBatchNode","BaseObject",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ArtFontLabelBatchNode");
   tolua_function(tolua_S,"new",tolua_Dota_ArtFontLabelBatchNode_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_ArtFontLabelBatchNode_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_ArtFontLabelBatchNode_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_ArtFontLabelBatchNode_delete00);
   tolua_function(tolua_S,"CreateArtFontWithArray",tolua_Dota_ArtFontLabelBatchNode_CreateArtFontWithArray00);
   tolua_function(tolua_S,"InitNumberLabelBatchNode",tolua_Dota_ArtFontLabelBatchNode_InitNumberLabelBatchNode00);
   tolua_function(tolua_S,"SetLabelWithArray",tolua_Dota_ArtFontLabelBatchNode_SetLabelWithArray00);
   tolua_function(tolua_S,"SetAnchorPoint",tolua_Dota_ArtFontLabelBatchNode_SetAnchorPoint00);
   tolua_function(tolua_S,"SetPosition",tolua_Dota_ArtFontLabelBatchNode_SetPosition00);
   tolua_function(tolua_S,"SetScale",tolua_Dota_ArtFontLabelBatchNode_SetScale00);
   tolua_function(tolua_S,"GetLabelTotalWidth",tolua_Dota_ArtFontLabelBatchNode_GetLabelTotalWidth00);
   tolua_function(tolua_S,"GetAnchorPosition",tolua_Dota_ArtFontLabelBatchNode_GetAnchorPosition00);
   tolua_function(tolua_S,"GetPosition",tolua_Dota_ArtFontLabelBatchNode_GetPosition00);
   tolua_function(tolua_S,"setColor",tolua_Dota_ArtFontLabelBatchNode_setColor00);
   tolua_function(tolua_S,"getColor",tolua_Dota_ArtFontLabelBatchNode_getColor00);
   tolua_function(tolua_S,"getOpacity",tolua_Dota_ArtFontLabelBatchNode_getOpacity00);
   tolua_function(tolua_S,"setOpacity",tolua_Dota_ArtFontLabelBatchNode_setOpacity00);
   tolua_function(tolua_S,"setOpacityModifyRGB",tolua_Dota_ArtFontLabelBatchNode_setOpacityModifyRGB00);
   tolua_function(tolua_S,"isOpacityModifyRGB",tolua_Dota_ArtFontLabelBatchNode_isOpacityModifyRGB00);
   tolua_function(tolua_S,"isCascadeColorEnabled",tolua_Dota_ArtFontLabelBatchNode_isCascadeColorEnabled00);
   tolua_function(tolua_S,"setCascadeColorEnabled",tolua_Dota_ArtFontLabelBatchNode_setCascadeColorEnabled00);
   tolua_function(tolua_S,"updateDisplayedColor",tolua_Dota_ArtFontLabelBatchNode_updateDisplayedColor00);
   tolua_function(tolua_S,"isCascadeOpacityEnabled",tolua_Dota_ArtFontLabelBatchNode_isCascadeOpacityEnabled00);
   tolua_function(tolua_S,"setCascadeOpacityEnabled",tolua_Dota_ArtFontLabelBatchNode_setCascadeOpacityEnabled00);
   tolua_function(tolua_S,"updateDisplayedOpacity",tolua_Dota_ArtFontLabelBatchNode_updateDisplayedOpacity00);
   tolua_function(tolua_S,"getDisplayedColor",tolua_Dota_ArtFontLabelBatchNode_getDisplayedColor00);
   tolua_function(tolua_S,"getDisplayedOpacity",tolua_Dota_ArtFontLabelBatchNode_getDisplayedOpacity00);
   tolua_function(tolua_S,"SetVisible",tolua_Dota_ArtFontLabelBatchNode_SetVisible00);
   tolua_function(tolua_S,"GetVisible",tolua_Dota_ArtFontLabelBatchNode_GetVisible00);
   tolua_function(tolua_S,"GetBatchNodeLabel",tolua_Dota_ArtFontLabelBatchNode_GetBatchNodeLabel00);
   tolua_function(tolua_S,"Init",tolua_Dota_ArtFontLabelBatchNode_Init00);
   tolua_function(tolua_S,"Destroy",tolua_Dota_ArtFontLabelBatchNode_Destroy00);
   tolua_function(tolua_S,"OnCommandHanlder",tolua_Dota_ArtFontLabelBatchNode_OnCommandHanlder00);
   tolua_variable(tolua_S,"__CCRGBAProtocol__",tolua_get_ArtFontLabelBatchNode___CCRGBAProtocol__,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ErrorTipsData","ErrorTipsData","",NULL);
  tolua_beginmodule(tolua_S,"ErrorTipsData");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"AutoDelayProtocol","AutoDelayProtocol","",NULL);
  tolua_beginmodule(tolua_S,"AutoDelayProtocol");
   tolua_function(tolua_S,"autoDelayEventHandler",tolua_Dota_AutoDelayProtocol_autoDelayEventHandler00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"AutoDelayAnimation","AutoDelayAnimation","CCDelayTime",tolua_collect_AutoDelayAnimation);
  #else
  tolua_cclass(tolua_S,"AutoDelayAnimation","AutoDelayAnimation","CCDelayTime",NULL);
  #endif
  tolua_beginmodule(tolua_S,"AutoDelayAnimation");
   tolua_function(tolua_S,"create",tolua_Dota_AutoDelayAnimation_create00);
   tolua_function(tolua_S,"initDuration",tolua_Dota_AutoDelayAnimation_initDuration00);
   tolua_function(tolua_S,"setSpeedScale",tolua_Dota_AutoDelayAnimation_setSpeedScale00);
   tolua_function(tolua_S,"delete",tolua_Dota_AutoDelayAnimation_delete00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"AutoFadeOutLabelManager","AutoFadeOutLabelManager","AutoDelayProtocol",tolua_collect_AutoFadeOutLabelManager);
  #else
  tolua_cclass(tolua_S,"AutoFadeOutLabelManager","AutoFadeOutLabelManager","AutoDelayProtocol",NULL);
  #endif
  tolua_beginmodule(tolua_S,"AutoFadeOutLabelManager");
   tolua_function(tolua_S,"new",tolua_Dota_AutoFadeOutLabelManager_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_AutoFadeOutLabelManager_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_AutoFadeOutLabelManager_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_AutoFadeOutLabelManager_delete00);
   tolua_function(tolua_S,"CreateAutoFadeOutLabelManager",tolua_Dota_AutoFadeOutLabelManager_CreateAutoFadeOutLabelManager00);
   tolua_function(tolua_S,"autoDelayEventHandler",tolua_Dota_AutoFadeOutLabelManager_autoDelayEventHandler00);
   tolua_function(tolua_S,"SetPosition",tolua_Dota_AutoFadeOutLabelManager_SetPosition00);
   tolua_function(tolua_S,"AddParent",tolua_Dota_AutoFadeOutLabelManager_AddParent00);
   tolua_function(tolua_S,"Destroy",tolua_Dota_AutoFadeOutLabelManager_Destroy00);
   tolua_function(tolua_S,"GetIsValid",tolua_Dota_AutoFadeOutLabelManager_GetIsValid00);
   tolua_function(tolua_S,"SetIndex",tolua_Dota_AutoFadeOutLabelManager_SetIndex00);
   tolua_function(tolua_S,"GetIndex",tolua_Dota_AutoFadeOutLabelManager_GetIndex00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CAnimationSprite","CAnimationSprite","CCSprite",tolua_collect_CAnimationSprite);
  #else
  tolua_cclass(tolua_S,"CAnimationSprite","CAnimationSprite","CCSprite",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CAnimationSprite");
   tolua_function(tolua_S,"new",tolua_Dota_CAnimationSprite_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_CAnimationSprite_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_CAnimationSprite_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_CAnimationSprite_delete00);
   tolua_function(tolua_S,"createAnimationSpriteByID",tolua_Dota_CAnimationSprite_createAnimationSpriteByID00);
   tolua_function(tolua_S,"EffectCallBackEventHandler",tolua_Dota_CAnimationSprite_EffectCallBackEventHandler00);
   tolua_function(tolua_S,"RegisterEventHandler",tolua_Dota_CAnimationSprite_RegisterEventHandler00);
   tolua_function(tolua_S,"PlayEffect",tolua_Dota_CAnimationSprite_PlayEffect00);
   tolua_function(tolua_S,"StopEffect",tolua_Dota_CAnimationSprite_StopEffect00);
   tolua_function(tolua_S,"SetAnimationID",tolua_Dota_CAnimationSprite_SetAnimationID00);
   tolua_function(tolua_S,"setVisible",tolua_Dota_CAnimationSprite_setVisible00);
   tolua_function(tolua_S,"SetIsUnLoopEffect",tolua_Dota_CAnimationSprite_SetIsUnLoopEffect00);
   tolua_variable(tolua_S,"__AnimationEffectCallBackProtocol__",tolua_get_CAnimationSprite___AnimationEffectCallBackProtocol__,NULL);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCardsStarProgress","CCardsStarProgress","CCNode",tolua_collect_CCardsStarProgress);
  #else
  tolua_cclass(tolua_S,"CCardsStarProgress","CCardsStarProgress","CCNode",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCardsStarProgress");
   tolua_function(tolua_S,"new",tolua_Dota_CCardsStarProgress_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_CCardsStarProgress_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_CCardsStarProgress_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_CCardsStarProgress_delete00);
   tolua_function(tolua_S,"create",tolua_Dota_CCardsStarProgress_create00);
   tolua_function(tolua_S,"init",tolua_Dota_CCardsStarProgress_init00);
   tolua_function(tolua_S,"SetCurcount",tolua_Dota_CCardsStarProgress_SetCurcount00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCDragLayerProtocol","CCDragLayerProtocol","",NULL);
  tolua_beginmodule(tolua_S,"CCDragLayerProtocol");
   tolua_function(tolua_S,"delegateDragEndEventHandler",tolua_Dota_CCDragLayerProtocol_delegateDragEndEventHandler00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCDragNodeLayer","CCDragNodeLayer","CCLayer",tolua_collect_CCDragNodeLayer);
  #else
  tolua_cclass(tolua_S,"CCDragNodeLayer","CCDragNodeLayer","CCLayer",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCDragNodeLayer");
   tolua_function(tolua_S,"new",tolua_Dota_CCDragNodeLayer_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_CCDragNodeLayer_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_CCDragNodeLayer_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_CCDragNodeLayer_delete00);
   tolua_function(tolua_S,"createDragNodeLayer",tolua_Dota_CCDragNodeLayer_createDragNodeLayer00);
   tolua_function(tolua_S,"onEnter",tolua_Dota_CCDragNodeLayer_onEnter00);
   tolua_function(tolua_S,"onExit",tolua_Dota_CCDragNodeLayer_onExit00);
   tolua_function(tolua_S,"addSignSpriteVector",tolua_Dota_CCDragNodeLayer_addSignSpriteVector00);
   tolua_function(tolua_S,"addTargetSignSprite",tolua_Dota_CCDragNodeLayer_addTargetSignSprite00);
   tolua_function(tolua_S,"removeTargetSignSpriteWithID",tolua_Dota_CCDragNodeLayer_removeTargetSignSpriteWithID00);
   tolua_function(tolua_S,"addOtherAttachSprite",tolua_Dota_CCDragNodeLayer_addOtherAttachSprite00);
   tolua_function(tolua_S,"addTargetAttachSprite",tolua_Dota_CCDragNodeLayer_addTargetAttachSprite00);
   tolua_function(tolua_S,"removeAllTargetSignSprites",tolua_Dota_CCDragNodeLayer_removeAllTargetSignSprites00);
   tolua_function(tolua_S,"removeAllOtherAttachSprite",tolua_Dota_CCDragNodeLayer_removeAllOtherAttachSprite00);
   tolua_function(tolua_S,"removeAllTargetAttachSprite",tolua_Dota_CCDragNodeLayer_removeAllTargetAttachSprite00);
   tolua_function(tolua_S,"removeAllData",tolua_Dota_CCDragNodeLayer_removeAllData00);
   tolua_function(tolua_S,"ccTouchBegan",tolua_Dota_CCDragNodeLayer_ccTouchBegan00);
   tolua_function(tolua_S,"ccTouchMoved",tolua_Dota_CCDragNodeLayer_ccTouchMoved00);
   tolua_function(tolua_S,"ccTouchEnded",tolua_Dota_CCDragNodeLayer_ccTouchEnded00);
   tolua_function(tolua_S,"ccTouchCancelled",tolua_Dota_CCDragNodeLayer_ccTouchCancelled00);
   tolua_function(tolua_S,"clearAllSignTouchArray",tolua_Dota_CCDragNodeLayer_clearAllSignTouchArray00);
   tolua_function(tolua_S,"setDragLayerTouchEnable",tolua_Dota_CCDragNodeLayer_setDragLayerTouchEnable00);
   tolua_function(tolua_S,"setDragLayerTouchPriority",tolua_Dota_CCDragNodeLayer_setDragLayerTouchPriority00);
   tolua_function(tolua_S,"getDragLayerTouchEnabel",tolua_Dota_CCDragNodeLayer_getDragLayerTouchEnabel00);
   tolua_function(tolua_S,"setDefaultTargetSegmentHeight",tolua_Dota_CCDragNodeLayer_setDefaultTargetSegmentHeight00);
   tolua_function(tolua_S,"setDragEventDelegate",tolua_Dota_CCDragNodeLayer_setDragEventDelegate00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCGrapSprite","CCGrapSprite","CCSprite",tolua_collect_CCGrapSprite);
  #else
  tolua_cclass(tolua_S,"CCGrapSprite","CCGrapSprite","CCSprite",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCGrapSprite");
   tolua_function(tolua_S,"new",tolua_Dota_CCGrapSprite_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_CCGrapSprite_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_CCGrapSprite_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_CCGrapSprite_delete00);
   tolua_function(tolua_S,"createGrapSpriteWithFileName",tolua_Dota_CCGrapSprite_createGrapSpriteWithFileName00);
   tolua_function(tolua_S,"createGrapSpriteWithFrameName",tolua_Dota_CCGrapSprite_createGrapSpriteWithFrameName00);
   tolua_function(tolua_S,"initWithTexture",tolua_Dota_CCGrapSprite_initWithTexture00);
   tolua_function(tolua_S,"draw",tolua_Dota_CCGrapSprite_draw00);
   tolua_function(tolua_S,"initProgram",tolua_Dota_CCGrapSprite_initProgram00);
   tolua_function(tolua_S,"listenBackToForeground",tolua_Dota_CCGrapSprite_listenBackToForeground00);
   tolua_function(tolua_S,"setGrapTexture",tolua_Dota_CCGrapSprite_setGrapTexture00);
   tolua_function(tolua_S,"setProperty",tolua_Dota_CCGrapSprite_setProperty00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCornerNumIcon","CCornerNumIcon","CCSprite",tolua_collect_CCornerNumIcon);
  #else
  tolua_cclass(tolua_S,"CCornerNumIcon","CCornerNumIcon","CCSprite",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCornerNumIcon");
   tolua_function(tolua_S,"new",tolua_Dota_CCornerNumIcon_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_CCornerNumIcon_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_CCornerNumIcon_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_CCornerNumIcon_delete00);
   tolua_function(tolua_S,"create",tolua_Dota_CCornerNumIcon_create00);
   tolua_function(tolua_S,"init",tolua_Dota_CCornerNumIcon_init00);
   tolua_function(tolua_S,"setNum",tolua_Dota_CCornerNumIcon_setNum00);
   tolua_function(tolua_S,"getNumLabel",tolua_Dota_CCornerNumIcon_getNumLabel00);
   tolua_function(tolua_S,"setShow",tolua_Dota_CCornerNumIcon_setShow00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCRectClipNode","CCRectClipNode","CCNode",tolua_collect_CCRectClipNode);
  #else
  tolua_cclass(tolua_S,"CCRectClipNode","CCRectClipNode","CCNode",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCRectClipNode");
   tolua_function(tolua_S,"new",tolua_Dota_CCRectClipNode_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_CCRectClipNode_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_CCRectClipNode_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_CCRectClipNode_delete00);
   tolua_function(tolua_S,"init",tolua_Dota_CCRectClipNode_init00);
   tolua_function(tolua_S,"create",tolua_Dota_CCRectClipNode_create00);
   tolua_function(tolua_S,"visit",tolua_Dota_CCRectClipNode_visit00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CCSignSprite","CCSignSprite","CCSprite",tolua_collect_CCSignSprite);
  #else
  tolua_cclass(tolua_S,"CCSignSprite","CCSignSprite","CCSprite",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CCSignSprite");
   tolua_function(tolua_S,"new",tolua_Dota_CCSignSprite_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_CCSignSprite_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_CCSignSprite_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_CCSignSprite_delete00);
   tolua_function(tolua_S,"createCCSignSpriteWithFile",tolua_Dota_CCSignSprite_createCCSignSpriteWithFile00);
   tolua_function(tolua_S,"createCCSignSpriteWithFrameName",tolua_Dota_CCSignSprite_createCCSignSpriteWithFrameName00);
   tolua_function(tolua_S,"setInitPosition",tolua_Dota_CCSignSprite_setInitPosition00);
   tolua_function(tolua_S,"getInitPosition",tolua_Dota_CCSignSprite_getInitPosition00);
   tolua_function(tolua_S,"getDragNodeType",tolua_Dota_CCSignSprite_getDragNodeType00);
   tolua_function(tolua_S,"getDragEnable",tolua_Dota_CCSignSprite_getDragEnable00);
   tolua_function(tolua_S,"setDragEnable",tolua_Dota_CCSignSprite_setDragEnable00);
   tolua_function(tolua_S,"forceToInitPosition",tolua_Dota_CCSignSprite_forceToInitPosition00);
   tolua_function(tolua_S,"checkIsCoverWithRect",tolua_Dota_CCSignSprite_checkIsCoverWithRect00);
   tolua_variable(tolua_S,"__SingleTouchProtocol__",tolua_get_CCSignSprite___SingleTouchProtocol__,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CDragSpriteDelegate","CDragSpriteDelegate","",NULL);
  tolua_beginmodule(tolua_S,"CDragSpriteDelegate");
   tolua_function(tolua_S,"clickEvent",tolua_Dota_CDragSpriteDelegate_clickEvent00);
   tolua_function(tolua_S,"containsTheCopy",tolua_Dota_CDragSpriteDelegate_containsTheCopy00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CDragSprite","CDragSprite","CCSprite",tolua_collect_CDragSprite);
  #else
  tolua_cclass(tolua_S,"CDragSprite","CDragSprite","CCSprite",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CDragSprite");
   tolua_function(tolua_S,"new",tolua_Dota_CDragSprite_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_CDragSprite_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_CDragSprite_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_CDragSprite_delete00);
   tolua_function(tolua_S,"create",tolua_Dota_CDragSprite_create00);
   tolua_function(tolua_S,"initWithFile",tolua_Dota_CDragSprite_initWithFile00);
   tolua_function(tolua_S,"create",tolua_Dota_CDragSprite_create01);
   tolua_function(tolua_S,"initWithTexture",tolua_Dota_CDragSprite_initWithTexture00);
   tolua_function(tolua_S,"setDelegate",tolua_Dota_CDragSprite_setDelegate00);
   tolua_function(tolua_S,"isDragEabled",tolua_Dota_CDragSprite_isDragEabled00);
   tolua_function(tolua_S,"isDragEabled",tolua_Dota_CDragSprite_isDragEabled01);
   tolua_function(tolua_S,"copyzOrder",tolua_Dota_CDragSprite_copyzOrder00);
   tolua_function(tolua_S,"copyzOrder",tolua_Dota_CDragSprite_copyzOrder01);
   tolua_function(tolua_S,"dragType",tolua_Dota_CDragSprite_dragType00);
   tolua_function(tolua_S,"dragType",tolua_Dota_CDragSprite_dragType01);
   tolua_function(tolua_S,"setIDX",tolua_Dota_CDragSprite_setIDX00);
   tolua_function(tolua_S,"getIDX",tolua_Dota_CDragSprite_getIDX00);
   tolua_variable(tolua_S,"__CCTargetedTouchDelegate__",tolua_get_CDragSprite___CCTargetedTouchDelegate__,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CPageScrollDelegate","CPageScrollDelegate","",NULL);
  tolua_beginmodule(tolua_S,"CPageScrollDelegate");
   tolua_function(tolua_S,"changePage",tolua_Dota_CPageScrollDelegate_changePage00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CPageScroll","CPageScroll","CCLayer",tolua_collect_CPageScroll);
  #else
  tolua_cclass(tolua_S,"CPageScroll","CPageScroll","CCLayer",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CPageScroll");
   tolua_function(tolua_S,"new",tolua_Dota_CPageScroll_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_CPageScroll_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_CPageScroll_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_CPageScroll_delete00);
   tolua_function(tolua_S,"create",tolua_Dota_CPageScroll_create00);
   tolua_function(tolua_S,"init",tolua_Dota_CPageScroll_init00);
   tolua_function(tolua_S,"getContainer",tolua_Dota_CPageScroll_getContainer00);
   tolua_function(tolua_S,"isTouchInArea",tolua_Dota_CPageScroll_isTouchInArea00);
   tolua_function(tolua_S,"moveToPage",tolua_Dota_CPageScroll_moveToPage00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CPriorityLayerColor","CPriorityLayerColor","CCLayerColor",tolua_collect_CPriorityLayerColor);
  #else
  tolua_cclass(tolua_S,"CPriorityLayerColor","CPriorityLayerColor","CCLayerColor",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CPriorityLayerColor");
   tolua_function(tolua_S,"new",tolua_Dota_CPriorityLayerColor_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_CPriorityLayerColor_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_CPriorityLayerColor_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_CPriorityLayerColor_delete00);
   tolua_function(tolua_S,"create",tolua_Dota_CPriorityLayerColor_create00);
   tolua_function(tolua_S,"initWithColor",tolua_Dota_CPriorityLayerColor_initWithColor00);
   tolua_function(tolua_S,"setDelegate",tolua_Dota_CPriorityLayerColor_setDelegate00);
   tolua_function(tolua_S,"setIDX",tolua_Dota_CPriorityLayerColor_setIDX00);
   tolua_function(tolua_S,"getIDX",tolua_Dota_CPriorityLayerColor_getIDX00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CPriorityLayerColorDelegate","CPriorityLayerColorDelegate","",NULL);
  tolua_beginmodule(tolua_S,"CPriorityLayerColorDelegate");
   tolua_function(tolua_S,"touchEvent",tolua_Dota_CPriorityLayerColorDelegate_touchEvent00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CProgressInnerBar","CProgressInnerBar","CCSprite",tolua_collect_CProgressInnerBar);
  #else
  tolua_cclass(tolua_S,"CProgressInnerBar","CProgressInnerBar","CCSprite",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CProgressInnerBar");
   tolua_function(tolua_S,"new",tolua_Dota_CProgressInnerBar_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_CProgressInnerBar_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_CProgressInnerBar_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_CProgressInnerBar_delete00);
   tolua_function(tolua_S,"create",tolua_Dota_CProgressInnerBar_create00);
   tolua_function(tolua_S,"init",tolua_Dota_CProgressInnerBar_init00);
   tolua_function(tolua_S,"setPercent",tolua_Dota_CProgressInnerBar_setPercent00);
   tolua_function(tolua_S,"getPercent",tolua_Dota_CProgressInnerBar_getPercent00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CProgressTimerDelegate","CProgressTimerDelegate","",NULL);
  tolua_beginmodule(tolua_S,"CProgressTimerDelegate");
   tolua_function(tolua_S,"CallBack_NextLevel",tolua_Dota_CProgressTimerDelegate_CallBack_NextLevel00);
   tolua_function(tolua_S,"CallBack_RunFinish",tolua_Dota_CProgressTimerDelegate_CallBack_RunFinish00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CProgressTimer","CProgressTimer","CCProgressTimer",tolua_collect_CProgressTimer);
  #else
  tolua_cclass(tolua_S,"CProgressTimer","CProgressTimer","CCProgressTimer",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CProgressTimer");
   tolua_function(tolua_S,"new",tolua_Dota_CProgressTimer_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_CProgressTimer_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_CProgressTimer_new00_local);
   tolua_function(tolua_S,"new",tolua_Dota_CProgressTimer_new01);
   tolua_function(tolua_S,"new_local",tolua_Dota_CProgressTimer_new01_local);
   tolua_function(tolua_S,".call",tolua_Dota_CProgressTimer_new01_local);
   tolua_function(tolua_S,"create",tolua_Dota_CProgressTimer_create00);
   tolua_function(tolua_S,"init",tolua_Dota_CProgressTimer_init00);
   tolua_function(tolua_S,"setRunSchedule",tolua_Dota_CProgressTimer_setRunSchedule00);
   tolua_function(tolua_S,"RunFinish",tolua_Dota_CProgressTimer_RunFinish00);
   tolua_function(tolua_S,"NextLevel",tolua_Dota_CProgressTimer_NextLevel00);
   tolua_function(tolua_S,"setDelegate",tolua_Dota_CProgressTimer_setDelegate00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CSpriteSelected","CSpriteSelected","CCSprite",NULL);
  tolua_beginmodule(tolua_S,"CSpriteSelected");
   tolua_function(tolua_S,"create",tolua_Dota_CSpriteSelected_create00);
   tolua_function(tolua_S,"initWithFile",tolua_Dota_CSpriteSelected_initWithFile00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CSelectedSprite","CSelectedSprite","CCScale9Sprite",NULL);
  tolua_beginmodule(tolua_S,"CSelectedSprite");
   tolua_function(tolua_S,"create",tolua_Dota_CSelectedSprite_create00);
   tolua_function(tolua_S,"initWithFile",tolua_Dota_CSelectedSprite_initWithFile00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CSimpleActionSprite","CSimpleActionSprite","CCSprite",NULL);
  tolua_beginmodule(tolua_S,"CSimpleActionSprite");
   tolua_function(tolua_S,"create",tolua_Dota_CSimpleActionSprite_create00);
   tolua_function(tolua_S,"PlayAction",tolua_Dota_CSimpleActionSprite_PlayAction00);
   tolua_function(tolua_S,"StopAction",tolua_Dota_CSimpleActionSprite_StopAction00);
   tolua_function(tolua_S,"SetInitPosition",tolua_Dota_CSimpleActionSprite_SetInitPosition00);
   tolua_function(tolua_S,"addChild",tolua_Dota_CSimpleActionSprite_addChild00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CSprite","CSprite","CCSprite",NULL);
  tolua_beginmodule(tolua_S,"CSprite");
   tolua_function(tolua_S,"create",tolua_Dota_CSprite_create00);
   tolua_function(tolua_S,"init",tolua_Dota_CSprite_init00);
   tolua_function(tolua_S,"setFilePath1",tolua_Dota_CSprite_setFilePath100);
   tolua_function(tolua_S,"setFilePath2",tolua_Dota_CSprite_setFilePath200);
   tolua_function(tolua_S,"setFilePath3",tolua_Dota_CSprite_setFilePath300);
   tolua_function(tolua_S,"getNowShowFileIndex",tolua_Dota_CSprite_getNowShowFileIndex00);
   tolua_function(tolua_S,"changeToImage1",tolua_Dota_CSprite_changeToImage100);
   tolua_function(tolua_S,"changeToImage2",tolua_Dota_CSprite_changeToImage200);
   tolua_function(tolua_S,"changeToImage3",tolua_Dota_CSprite_changeToImage300);
   tolua_function(tolua_S,"hasImage1",tolua_Dota_CSprite_hasImage100);
   tolua_function(tolua_S,"hasImage2",tolua_Dota_CSprite_hasImage200);
   tolua_function(tolua_S,"hasImage3",tolua_Dota_CSprite_hasImage300);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CTitleSprite","CTitleSprite","CCSprite",tolua_collect_CTitleSprite);
  #else
  tolua_cclass(tolua_S,"CTitleSprite","CTitleSprite","CCSprite",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CTitleSprite");
   tolua_function(tolua_S,"new",tolua_Dota_CTitleSprite_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_CTitleSprite_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_CTitleSprite_new00_local);
   tolua_function(tolua_S,"create",tolua_Dota_CTitleSprite_create00);
   tolua_function(tolua_S,"init",tolua_Dota_CTitleSprite_init00);
   tolua_function(tolua_S,"SetLabelString",tolua_Dota_CTitleSprite_SetLabelString00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CSpriteInSprite","CSpriteInSprite","CCSprite",tolua_collect_CSpriteInSprite);
  #else
  tolua_cclass(tolua_S,"CSpriteInSprite","CSpriteInSprite","CCSprite",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CSpriteInSprite");
   tolua_function(tolua_S,"new",tolua_Dota_CSpriteInSprite_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_CSpriteInSprite_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_CSpriteInSprite_new00_local);
   tolua_function(tolua_S,"create",tolua_Dota_CSpriteInSprite_create00);
   tolua_function(tolua_S,"init",tolua_Dota_CSpriteInSprite_init00);
   tolua_function(tolua_S,"ChangeInnerImage",tolua_Dota_CSpriteInSprite_ChangeInnerImage00);
   tolua_function(tolua_S,"ChangeOutterImage",tolua_Dota_CSpriteInSprite_ChangeOutterImage00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"TableViewSourceDelegate","TableViewSourceDelegate","CCTableViewDataSource",NULL);
  tolua_beginmodule(tolua_S,"TableViewSourceDelegate");
   tolua_variable(tolua_S,"m_pCell",tolua_get_TableViewSourceDelegate_m_pCell_ptr,tolua_set_TableViewSourceDelegate_m_pCell_ptr);
   tolua_variable(tolua_S,"m_nCellSize",tolua_get_TableViewSourceDelegate_m_nCellSize,tolua_set_TableViewSourceDelegate_m_nCellSize);
   tolua_variable(tolua_S,"m_nCellNumbers",tolua_get_TableViewSourceDelegate_m_nCellNumbers,tolua_set_TableViewSourceDelegate_m_nCellNumbers);
   tolua_function(tolua_S,"tableCellSizeForIndex",tolua_Dota_TableViewSourceDelegate_tableCellSizeForIndex00);
   tolua_function(tolua_S,"tableCellAtIndex",tolua_Dota_TableViewSourceDelegate_tableCellAtIndex00);
   tolua_function(tolua_S,"numberOfCellsInTableView",tolua_Dota_TableViewSourceDelegate_numberOfCellsInTableView00);
   tolua_function(tolua_S,"scrollViewDidScroll",tolua_Dota_TableViewSourceDelegate_scrollViewDidScroll00);
   tolua_function(tolua_S,"registerScript",tolua_Dota_TableViewSourceDelegate_registerScript00);
   tolua_variable(tolua_S,"__CCTableViewDelegate__",tolua_get_TableViewSourceDelegate___CCTableViewDelegate__,NULL);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CTableView","CTableView","CCTableView",tolua_collect_CTableView);
  #else
  tolua_cclass(tolua_S,"CTableView","CTableView","CCTableView",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CTableView");
   tolua_function(tolua_S,"new",tolua_Dota_CTableView_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_CTableView_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_CTableView_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_CTableView_delete00);
   tolua_function(tolua_S,"create",tolua_Dota_CTableView_create00);
   tolua_function(tolua_S,"init",tolua_Dota_CTableView_init00);
   tolua_function(tolua_S,"registerWithTouchDispatcher",tolua_Dota_CTableView_registerWithTouchDispatcher00);
   tolua_function(tolua_S,"getPriority",tolua_Dota_CTableView_getPriority00);
   tolua_function(tolua_S,"getMyDelegate",tolua_Dota_CTableView_getMyDelegate00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CScrollView","CScrollView","CCScrollView",tolua_collect_CScrollView);
  #else
  tolua_cclass(tolua_S,"CScrollView","CScrollView","CCScrollView",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CScrollView");
   tolua_function(tolua_S,"new",tolua_Dota_CScrollView_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_CScrollView_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_CScrollView_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_CScrollView_delete00);
   tolua_function(tolua_S,"create",tolua_Dota_CScrollView_create00);
   tolua_function(tolua_S,"init",tolua_Dota_CScrollView_init00);
   tolua_function(tolua_S,"registerWithTouchDispatcher",tolua_Dota_CScrollView_registerWithTouchDispatcher00);
   tolua_function(tolua_S,"getPriority",tolua_Dota_CScrollView_getPriority00);
   tolua_function(tolua_S,"addText",tolua_Dota_CScrollView_addText00);
   tolua_function(tolua_S,"resizeContent",tolua_Dota_CScrollView_resizeContent00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CMapScrollView","CMapScrollView","CCScrollView",tolua_collect_CMapScrollView);
  #else
  tolua_cclass(tolua_S,"CMapScrollView","CMapScrollView","CCScrollView",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CMapScrollView");
   tolua_function(tolua_S,"new",tolua_Dota_CMapScrollView_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_CMapScrollView_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_CMapScrollView_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_CMapScrollView_delete00);
   tolua_function(tolua_S,"create",tolua_Dota_CMapScrollView_create00);
   tolua_function(tolua_S,"initWithViewSize",tolua_Dota_CMapScrollView_initWithViewSize00);
   tolua_function(tolua_S,"registerWithTouchDispatcher",tolua_Dota_CMapScrollView_registerWithTouchDispatcher00);
   tolua_function(tolua_S,"getPriority",tolua_Dota_CMapScrollView_getPriority00);
   tolua_function(tolua_S,"getChildByTag",tolua_Dota_CMapScrollView_getChildByTag00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CTeamIconProgress","CTeamIconProgress","CCNode",tolua_collect_CTeamIconProgress);
  #else
  tolua_cclass(tolua_S,"CTeamIconProgress","CTeamIconProgress","CCNode",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CTeamIconProgress");
   tolua_function(tolua_S,"new",tolua_Dota_CTeamIconProgress_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_CTeamIconProgress_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_CTeamIconProgress_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_CTeamIconProgress_delete00);
   tolua_function(tolua_S,"createTeamIconProgress",tolua_Dota_CTeamIconProgress_createTeamIconProgress00);
   tolua_function(tolua_S,"resetProgress",tolua_Dota_CTeamIconProgress_resetProgress00);
   tolua_function(tolua_S,"reduceActiveCount",tolua_Dota_CTeamIconProgress_reduceActiveCount00);
   tolua_function(tolua_S,"setActiveCount",tolua_Dota_CTeamIconProgress_setActiveCount00);
   tolua_function(tolua_S,"unActiveAllProgress",tolua_Dota_CTeamIconProgress_unActiveAllProgress00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CTimerEventProtocol","CTimerEventProtocol","",NULL);
  tolua_beginmodule(tolua_S,"CTimerEventProtocol");
   tolua_function(tolua_S,"TimerEventHandler",tolua_Dota_CTimerEventProtocol_TimerEventHandler00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CTimeLabel","CTimeLabel","CCLabelTTF",NULL);
  tolua_beginmodule(tolua_S,"CTimeLabel");
   tolua_function(tolua_S,"CreateWithTimeType",tolua_Dota_CTimeLabel_CreateWithTimeType00);
   tolua_function(tolua_S,"CreateWithTimeType",tolua_Dota_CTimeLabel_CreateWithTimeType01);
   tolua_function(tolua_S,"StartTimer",tolua_Dota_CTimeLabel_StartTimer00);
   tolua_function(tolua_S,"StartTimer",tolua_Dota_CTimeLabel_StartTimer01);
   tolua_function(tolua_S,"StartActivityMiniteTimer",tolua_Dota_CTimeLabel_StartActivityMiniteTimer00);
   tolua_function(tolua_S,"StopTimer",tolua_Dota_CTimeLabel_StopTimer00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CTouchSpriteDelegate","CTouchSpriteDelegate","",NULL);
  tolua_beginmodule(tolua_S,"CTouchSpriteDelegate");
   tolua_function(tolua_S,"rangeTouched",tolua_Dota_CTouchSpriteDelegate_rangeTouched00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"CTouchSprite","CTouchSprite","CCSprite",tolua_collect_CTouchSprite);
  #else
  tolua_cclass(tolua_S,"CTouchSprite","CTouchSprite","CCSprite",NULL);
  #endif
  tolua_beginmodule(tolua_S,"CTouchSprite");
   tolua_function(tolua_S,"new",tolua_Dota_CTouchSprite_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_CTouchSprite_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_CTouchSprite_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_CTouchSprite_delete00);
   tolua_function(tolua_S,"create",tolua_Dota_CTouchSprite_create00);
   tolua_function(tolua_S,"initWithFile",tolua_Dota_CTouchSprite_initWithFile00);
   tolua_function(tolua_S,"setDelegate",tolua_Dota_CTouchSprite_setDelegate00);
   tolua_function(tolua_S,"setIDX",tolua_Dota_CTouchSprite_setIDX00);
   tolua_function(tolua_S,"getIDX",tolua_Dota_CTouchSprite_getIDX00);
   tolua_function(tolua_S,"setSoundID",tolua_Dota_CTouchSprite_setSoundID00);
   tolua_variable(tolua_S,"__CCTargetedTouchDelegate__",tolua_get_CTouchSprite___CCTargetedTouchDelegate__,NULL);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"FAnimationButton","FAnimationButton","CCMenuItemSprite",tolua_collect_FAnimationButton);
  #else
  tolua_cclass(tolua_S,"FAnimationButton","FAnimationButton","CCMenuItemSprite",NULL);
  #endif
  tolua_beginmodule(tolua_S,"FAnimationButton");
   tolua_function(tolua_S,"new",tolua_Dota_FAnimationButton_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_FAnimationButton_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_FAnimationButton_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_FAnimationButton_delete00);
   tolua_function(tolua_S,"create",tolua_Dota_FAnimationButton_create00);
   tolua_function(tolua_S,"initWithNormalSprite",tolua_Dota_FAnimationButton_initWithNormalSprite00);
   tolua_function(tolua_S,"create",tolua_Dota_FAnimationButton_create01);
   tolua_function(tolua_S,"initWithNormalImage",tolua_Dota_FAnimationButton_initWithNormalImage00);
   tolua_function(tolua_S,"setIDX",tolua_Dota_FAnimationButton_setIDX00);
   tolua_function(tolua_S,"getIDX",tolua_Dota_FAnimationButton_getIDX00);
   tolua_function(tolua_S,"setSoundID",tolua_Dota_FAnimationButton_setSoundID00);
   tolua_function(tolua_S,"setAnimationId",tolua_Dota_FAnimationButton_setAnimationId00);
   tolua_function(tolua_S,"setAnimationPos",tolua_Dota_FAnimationButton_setAnimationPos00);
   tolua_function(tolua_S,"setAnimationCallBack",tolua_Dota_FAnimationButton_setAnimationCallBack00);
   tolua_function(tolua_S,"EffectCallBackEventHandler",tolua_Dota_FAnimationButton_EffectCallBackEventHandler00);
   tolua_function(tolua_S,"PlayAnimation",tolua_Dota_FAnimationButton_PlayAnimation00);
   tolua_function(tolua_S,"StopAnimation",tolua_Dota_FAnimationButton_StopAnimation00);
   tolua_function(tolua_S,"PlayTouchSound",tolua_Dota_FAnimationButton_PlayTouchSound00);
   tolua_variable(tolua_S,"__AnimationEffectCallBackProtocol__",tolua_get_FAnimationButton___AnimationEffectCallBackProtocol__,NULL);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"FAPriorityMenu","FAPriorityMenu","CCMenu",tolua_collect_FAPriorityMenu);
  #else
  tolua_cclass(tolua_S,"FAPriorityMenu","FAPriorityMenu","CCMenu",NULL);
  #endif
  tolua_beginmodule(tolua_S,"FAPriorityMenu");
   tolua_function(tolua_S,"new",tolua_Dota_FAPriorityMenu_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_FAPriorityMenu_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_FAPriorityMenu_new00_local);
   tolua_function(tolua_S,"create",tolua_Dota_FAPriorityMenu_create00);
   tolua_function(tolua_S,"init",tolua_Dota_FAPriorityMenu_init00);
   tolua_function(tolua_S,"registerWithTouchDispatcher",tolua_Dota_FAPriorityMenu_registerWithTouchDispatcher00);
   tolua_function(tolua_S,"ccTouchBegan",tolua_Dota_FAPriorityMenu_ccTouchBegan00);
   tolua_function(tolua_S,"ccTouchEnded",tolua_Dota_FAPriorityMenu_ccTouchEnded00);
   tolua_function(tolua_S,"ccTouchMoved",tolua_Dota_FAPriorityMenu_ccTouchMoved00);
   tolua_function(tolua_S,"ccTouchCancelled",tolua_Dota_FAPriorityMenu_ccTouchCancelled00);
   tolua_function(tolua_S,"SetTreatAsTabMenu",tolua_Dota_FAPriorityMenu_SetTreatAsTabMenu00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"FrameAnimationDelegate","FrameAnimationDelegate","",NULL);
  tolua_beginmodule(tolua_S,"FrameAnimationDelegate");
   tolua_function(tolua_S,"FrameAnimationIntercept",tolua_Dota_FrameAnimationDelegate_FrameAnimationIntercept00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"FrameAnimationNode","FrameAnimationNode","CCNode",NULL);
  tolua_beginmodule(tolua_S,"FrameAnimationNode");
   tolua_function(tolua_S,"create",tolua_Dota_FrameAnimationNode_create00);
   tolua_function(tolua_S,"InsertFrameIntercept",tolua_Dota_FrameAnimationNode_InsertFrameIntercept00);
   tolua_function(tolua_S,"ClearAllIntercepts",tolua_Dota_FrameAnimationNode_ClearAllIntercepts00);
   tolua_function(tolua_S,"AddDelegate",tolua_Dota_FrameAnimationNode_AddDelegate00);
   tolua_function(tolua_S,"Tick",tolua_Dota_FrameAnimationNode_Tick00);
   tolua_function(tolua_S,"Start",tolua_Dota_FrameAnimationNode_Start00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"GrapStarsProgress","GrapStarsProgress","CCNode",tolua_collect_GrapStarsProgress);
  #else
  tolua_cclass(tolua_S,"GrapStarsProgress","GrapStarsProgress","CCNode",NULL);
  #endif
  tolua_beginmodule(tolua_S,"GrapStarsProgress");
   tolua_function(tolua_S,"new",tolua_Dota_GrapStarsProgress_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_GrapStarsProgress_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_GrapStarsProgress_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_GrapStarsProgress_delete00);
   tolua_function(tolua_S,"createGrapStarsProgress",tolua_Dota_GrapStarsProgress_createGrapStarsProgress00);
   tolua_function(tolua_S,"initGrapStarsProgress",tolua_Dota_GrapStarsProgress_initGrapStarsProgress00);
   tolua_function(tolua_S,"setStars",tolua_Dota_GrapStarsProgress_setStars00);
   tolua_function(tolua_S,"setStars",tolua_Dota_GrapStarsProgress_setStars01);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"MaskNode","MaskNode","CCNode",NULL);
  tolua_beginmodule(tolua_S,"MaskNode");
   tolua_function(tolua_S,"init",tolua_Dota_MaskNode_init00);
   tolua_function(tolua_S,"setViewData",tolua_Dota_MaskNode_setViewData00);
   tolua_function(tolua_S,"GetViewData",tolua_Dota_MaskNode_GetViewData00);
   tolua_function(tolua_S,"GetViewPData",tolua_Dota_MaskNode_GetViewPData00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"MoveAnimationCallBackProtocol","MoveAnimationCallBackProtocol","",NULL);
  tolua_beginmodule(tolua_S,"MoveAnimationCallBackProtocol");
   tolua_function(tolua_S,"CallBackEventProtocol",tolua_Dota_MoveAnimationCallBackProtocol_CallBackEventProtocol00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"MoveAnimation","MoveAnimation","CCMoveTo",tolua_collect_MoveAnimation);
  #else
  tolua_cclass(tolua_S,"MoveAnimation","MoveAnimation","CCMoveTo",NULL);
  #endif
  tolua_beginmodule(tolua_S,"MoveAnimation");
   tolua_function(tolua_S,"initWithDuration",tolua_Dota_MoveAnimation_initWithDuration00);
   tolua_function(tolua_S,"delete",tolua_Dota_MoveAnimation_delete00);
   tolua_function(tolua_S,"destroy",tolua_Dota_MoveAnimation_destroy00);
   tolua_function(tolua_S,"copyWithZone",tolua_Dota_MoveAnimation_copyWithZone00);
   tolua_function(tolua_S,"startWithTarget",tolua_Dota_MoveAnimation_startWithTarget00);
   tolua_function(tolua_S,"update",tolua_Dota_MoveAnimation_update00);
   tolua_function(tolua_S,"updateAnimatioSpeedScale",tolua_Dota_MoveAnimation_updateAnimatioSpeedScale00);
   tolua_function(tolua_S,"setSpeedScale",tolua_Dota_MoveAnimation_setSpeedScale00);
   tolua_function(tolua_S,"create",tolua_Dota_MoveAnimation_create00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PreCCMoveTo","PreCCMoveTo","CCActionInterval",NULL);
  tolua_beginmodule(tolua_S,"PreCCMoveTo");
   tolua_function(tolua_S,"initWithDuration",tolua_Dota_PreCCMoveTo_initWithDuration00);
   tolua_function(tolua_S,"copyWithZone",tolua_Dota_PreCCMoveTo_copyWithZone00);
   tolua_function(tolua_S,"startWithTarget",tolua_Dota_PreCCMoveTo_startWithTarget00);
   tolua_function(tolua_S,"update",tolua_Dota_PreCCMoveTo_update00);
   tolua_function(tolua_S,"create",tolua_Dota_PreCCMoveTo_create00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PreCCMoveBy","PreCCMoveBy","PreCCMoveTo",NULL);
  tolua_beginmodule(tolua_S,"PreCCMoveBy");
   tolua_function(tolua_S,"initWithDuration",tolua_Dota_PreCCMoveBy_initWithDuration00);
   tolua_function(tolua_S,"startWithTarget",tolua_Dota_PreCCMoveBy_startWithTarget00);
   tolua_function(tolua_S,"reverse",tolua_Dota_PreCCMoveBy_reverse00);
   tolua_function(tolua_S,"create",tolua_Dota_PreCCMoveBy_create00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ScaleSprite","ScaleSprite","CCSprite",NULL);
  tolua_beginmodule(tolua_S,"ScaleSprite");
   tolua_function(tolua_S,"create",tolua_Dota_ScaleSprite_create00);
   tolua_function(tolua_S,"init",tolua_Dota_ScaleSprite_init00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SceneEffect","SceneEffect","CCSprite",tolua_collect_SceneEffect);
  #else
  tolua_cclass(tolua_S,"SceneEffect","SceneEffect","CCSprite",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SceneEffect");
   tolua_function(tolua_S,"new",tolua_Dota_SceneEffect_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_SceneEffect_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_SceneEffect_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_SceneEffect_delete00);
   tolua_function(tolua_S,"createWithEffectID",tolua_Dota_SceneEffect_createWithEffectID00);
   tolua_function(tolua_S,"initWithEffectID",tolua_Dota_SceneEffect_initWithEffectID00);
   tolua_function(tolua_S,"clone",tolua_Dota_SceneEffect_clone00);
   tolua_function(tolua_S,"ReplayAction",tolua_Dota_SceneEffect_ReplayAction00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SingleTouchProtocol","SingleTouchProtocol","",tolua_collect_SingleTouchProtocol);
  #else
  tolua_cclass(tolua_S,"SingleTouchProtocol","SingleTouchProtocol","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SingleTouchProtocol");
   tolua_function(tolua_S,"new",tolua_Dota_SingleTouchProtocol_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_SingleTouchProtocol_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_SingleTouchProtocol_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_SingleTouchProtocol_delete00);
   tolua_function(tolua_S,"checkRowRank",tolua_Dota_SingleTouchProtocol_checkRowRank00);
   tolua_function(tolua_S,"checkColumnRank",tolua_Dota_SingleTouchProtocol_checkColumnRank00);
   tolua_function(tolua_S,"checkIsContainTouch",tolua_Dota_SingleTouchProtocol_checkIsContainTouch00);
   tolua_function(tolua_S,"setSingleTouchUniqueID",tolua_Dota_SingleTouchProtocol_setSingleTouchUniqueID00);
   tolua_function(tolua_S,"setExpendTouchSize",tolua_Dota_SingleTouchProtocol_setExpendTouchSize00);
   tolua_function(tolua_S,"getExpendTouchSize",tolua_Dota_SingleTouchProtocol_getExpendTouchSize00);
   tolua_function(tolua_S,"getSingleTouchUniqueID",tolua_Dota_SingleTouchProtocol_getSingleTouchUniqueID00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"UIBaseDialogProtory","UIBaseDialogProtory","",NULL);
  tolua_beginmodule(tolua_S,"UIBaseDialogProtory");
   tolua_function(tolua_S,"BaseDialogCallBackHandler",tolua_Dota_UIBaseDialogProtory_BaseDialogCallBackHandler00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UIBaseDialog","UIBaseDialog","CCLayerMask",tolua_collect_UIBaseDialog);
  #else
  tolua_cclass(tolua_S,"UIBaseDialog","UIBaseDialog","CCLayerMask",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UIBaseDialog");
   tolua_function(tolua_S,"new",tolua_Dota_UIBaseDialog_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_UIBaseDialog_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_UIBaseDialog_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_UIBaseDialog_delete00);
   tolua_function(tolua_S,"createUIBaseDialog",tolua_Dota_UIBaseDialog_createUIBaseDialog00);
   tolua_function(tolua_S,"setTouchUnCloseRect",tolua_Dota_UIBaseDialog_setTouchUnCloseRect00);
   tolua_function(tolua_S,"setDelegatePrototy",tolua_Dota_UIBaseDialog_setDelegatePrototy00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"UITowSideStretchNodeLayer","UITowSideStretchNodeLayer","CCLayer",tolua_collect_UITowSideStretchNodeLayer);
  #else
  tolua_cclass(tolua_S,"UITowSideStretchNodeLayer","UITowSideStretchNodeLayer","CCLayer",NULL);
  #endif
  tolua_beginmodule(tolua_S,"UITowSideStretchNodeLayer");
   tolua_function(tolua_S,"new",tolua_Dota_UITowSideStretchNodeLayer_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_UITowSideStretchNodeLayer_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_UITowSideStretchNodeLayer_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_UITowSideStretchNodeLayer_delete00);
   tolua_function(tolua_S,"createTowSideStretchLayer",tolua_Dota_UITowSideStretchNodeLayer_createTowSideStretchLayer00);
   tolua_function(tolua_S,"onEnter",tolua_Dota_UITowSideStretchNodeLayer_onEnter00);
   tolua_function(tolua_S,"onExit",tolua_Dota_UITowSideStretchNodeLayer_onExit00);
   tolua_function(tolua_S,"ccTouchBegan",tolua_Dota_UITowSideStretchNodeLayer_ccTouchBegan00);
   tolua_function(tolua_S,"ccTouchMoved",tolua_Dota_UITowSideStretchNodeLayer_ccTouchMoved00);
   tolua_function(tolua_S,"ccTouchEnded",tolua_Dota_UITowSideStretchNodeLayer_ccTouchEnded00);
   tolua_function(tolua_S,"onShowUnfoldNode",tolua_Dota_UITowSideStretchNodeLayer_onShowUnfoldNode00);
   tolua_function(tolua_S,"onShowShrinkNode",tolua_Dota_UITowSideStretchNodeLayer_onShowShrinkNode00);
   tolua_function(tolua_S,"getLeftScreenRect",tolua_Dota_UITowSideStretchNodeLayer_getLeftScreenRect00);
   tolua_function(tolua_S,"getRightScreenRect",tolua_Dota_UITowSideStretchNodeLayer_getRightScreenRect00);
   tolua_function(tolua_S,"containTouchOnLeftRect",tolua_Dota_UITowSideStretchNodeLayer_containTouchOnLeftRect00);
   tolua_function(tolua_S,"containTouchOnRightRect",tolua_Dota_UITowSideStretchNodeLayer_containTouchOnRightRect00);
   tolua_function(tolua_S,"setLeftNormalNode",tolua_Dota_UITowSideStretchNodeLayer_setLeftNormalNode00);
   tolua_function(tolua_S,"setleftSelectNode",tolua_Dota_UITowSideStretchNodeLayer_setleftSelectNode00);
   tolua_function(tolua_S,"setRightNormalNode",tolua_Dota_UITowSideStretchNodeLayer_setRightNormalNode00);
   tolua_function(tolua_S,"setRightSelectNode",tolua_Dota_UITowSideStretchNodeLayer_setRightSelectNode00);
   tolua_function(tolua_S,"setStretchTime",tolua_Dota_UITowSideStretchNodeLayer_setStretchTime00);
   tolua_function(tolua_S,"setTouchEnable",tolua_Dota_UITowSideStretchNodeLayer_setTouchEnable00);
   tolua_function(tolua_S,"setTouchPriority",tolua_Dota_UITowSideStretchNodeLayer_setTouchPriority00);
   tolua_function(tolua_S,"setNormalAndSelectWith",tolua_Dota_UITowSideStretchNodeLayer_setNormalAndSelectWith00);
   tolua_function(tolua_S,"setNormalAndSelectYPos",tolua_Dota_UITowSideStretchNodeLayer_setNormalAndSelectYPos00);
   tolua_function(tolua_S,"getLeftNormalNode",tolua_Dota_UITowSideStretchNodeLayer_getLeftNormalNode00);
   tolua_function(tolua_S,"getleftSelectNode",tolua_Dota_UITowSideStretchNodeLayer_getleftSelectNode00);
   tolua_function(tolua_S,"getRightNormalNode",tolua_Dota_UITowSideStretchNodeLayer_getRightNormalNode00);
   tolua_function(tolua_S,"getRightSelectedNode",tolua_Dota_UITowSideStretchNodeLayer_getRightSelectedNode00);
   tolua_function(tolua_S,"getStretchTime",tolua_Dota_UITowSideStretchNodeLayer_getStretchTime00);
   tolua_function(tolua_S,"getTouchEnable",tolua_Dota_UITowSideStretchNodeLayer_getTouchEnable00);
   tolua_function(tolua_S,"getTouchPriority",tolua_Dota_UITowSideStretchNodeLayer_getTouchPriority00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"NFC_getLoopFrameEffect",tolua_Dota_NFC_getLoopFrameEffect00);
  tolua_function(tolua_S,"NFC_getUnLoopFrameEffect",tolua_Dota_NFC_getUnLoopFrameEffect00);
  tolua_function(tolua_S,"NFC_getUnLoopFrameEffect",tolua_Dota_NFC_getUnLoopFrameEffect01);
  tolua_function(tolua_S,"NFC_getUnLoopFrameEffect",tolua_Dota_NFC_getUnLoopFrameEffect02);
  tolua_function(tolua_S,"NFC_getUnLoopFrameEffect",tolua_Dota_NFC_getUnLoopFrameEffect03);
  tolua_function(tolua_S,"NFC_getAnimationSprite",tolua_Dota_NFC_getAnimationSprite00);
  tolua_function(tolua_S,"NFC_PlayEffet",tolua_Dota_NFC_PlayEffet00);
  tolua_function(tolua_S,"NFC_skeletonTransparentAction",tolua_Dota_NFC_skeletonTransparentAction00);
  tolua_function(tolua_S,"NFC_getParticelEffect",tolua_Dota_NFC_getParticelEffect00);
  tolua_function(tolua_S,"NFC_getVariableSpeedAction",tolua_Dota_NFC_getVariableSpeedAction00);
  tolua_function(tolua_S,"NFC_getTransimissionDelayComAction",tolua_Dota_NFC_getTransimissionDelayComAction00);
  tolua_function(tolua_S,"NFC_getTransimissionMoveComAction",tolua_Dota_NFC_getTransimissionMoveComAction00);
  tolua_function(tolua_S,"NFC_getSimpleActionSprite",tolua_Dota_NFC_getSimpleActionSprite00);
  tolua_function(tolua_S,"NFC_getSimpleActionSprite",tolua_Dota_NFC_getSimpleActionSprite01);
  tolua_function(tolua_S,"NFC_Action_scaleIn",tolua_Dota_NFC_Action_scaleIn00);
  tolua_function(tolua_S,"NFC_Action_scaleIn",tolua_Dota_NFC_Action_scaleIn01);
  tolua_function(tolua_S,"NFC_Action_fallDown",tolua_Dota_NFC_Action_fallDown00);
  tolua_function(tolua_S,"NFC_Action_MoveAndReverse",tolua_Dota_NFC_Action_MoveAndReverse00);
  tolua_function(tolua_S,"NFC_Action_FadeInAndReverse",tolua_Dota_NFC_Action_FadeInAndReverse00);
  tolua_function(tolua_S,"NFC_quitGame",tolua_Dota_NFC_quitGame00);
  tolua_function(tolua_S,"NFC_playSoundByID",tolua_Dota_NFC_playSoundByID00);
  tolua_function(tolua_S,"NFC_showErrorTips",tolua_Dota_NFC_showErrorTips00);
  tolua_function(tolua_S,"NFC_showErrorTips",tolua_Dota_NFC_showErrorTips01);
  tolua_function(tolua_S,"NFC_showErrorTips_2",tolua_Dota_NFC_showErrorTips_200);
  tolua_function(tolua_S,"NFC_showCommunicationWating",tolua_Dota_NFC_showCommunicationWating00);
  tolua_function(tolua_S,"NFC_showCommunicationWating_2",tolua_Dota_NFC_showCommunicationWating_200);
  tolua_function(tolua_S,"NFC_showMessageBox",tolua_Dota_NFC_showMessageBox00);
  tolua_function(tolua_S,"NFC_getFileFromResourceID",tolua_Dota_NFC_getFileFromResourceID00);
  tolua_function(tolua_S,"NFC_getIDStringFromTag",tolua_Dota_NFC_getIDStringFromTag00);
  tolua_function(tolua_S,"NFC_getValueFromClientConst",tolua_Dota_NFC_getValueFromClientConst00);
  tolua_function(tolua_S,"NFC_showMessageBoxSingle",tolua_Dota_NFC_showMessageBoxSingle00);
  tolua_function(tolua_S,"NFC_showNormalMsgBySYID",tolua_Dota_NFC_showNormalMsgBySYID00);
  tolua_function(tolua_S,"NFC_getNode",tolua_Dota_NFC_getNode00);
  tolua_function(tolua_S,"NFC_showNode",tolua_Dota_NFC_showNode00);
  tolua_function(tolua_S,"NFC_setScale",tolua_Dota_NFC_setScale00);
  tolua_function(tolua_S,"NFC_setCardsStarLevel",tolua_Dota_NFC_setCardsStarLevel00);
  tolua_function(tolua_S,"NFC_setCardsStarAdvance",tolua_Dota_NFC_setCardsStarAdvance00);
  tolua_function(tolua_S,"NFC_setCornerNum",tolua_Dota_NFC_setCornerNum00);
  tolua_function(tolua_S,"NFC_setLabelString",tolua_Dota_NFC_setLabelString00);
  tolua_function(tolua_S,"NFC_setLabelString",tolua_Dota_NFC_setLabelString01);
  tolua_function(tolua_S,"NFC_setLabelString",tolua_Dota_NFC_setLabelString02);
  tolua_function(tolua_S,"NFC_setLabelStringInt",tolua_Dota_NFC_setLabelStringInt00);
  tolua_function(tolua_S,"NFC_setLabelStringInt",tolua_Dota_NFC_setLabelStringInt01);
  tolua_function(tolua_S,"NFC_setLabelStringInt",tolua_Dota_NFC_setLabelStringInt02);
  tolua_function(tolua_S,"NFC_setLabelStringInt",tolua_Dota_NFC_setLabelStringInt03);
  tolua_function(tolua_S,"NFC_setLabelColor",tolua_Dota_NFC_setLabelColor00);
  tolua_function(tolua_S,"NFC_setLabelColor",tolua_Dota_NFC_setLabelColor01);
  tolua_function(tolua_S,"NFC_setLabelByFontStyleID",tolua_Dota_NFC_setLabelByFontStyleID00);
  tolua_function(tolua_S,"NFC_setLabelByFontID",tolua_Dota_NFC_setLabelByFontID00);
  tolua_function(tolua_S,"NFC_setActionSpriteEnable",tolua_Dota_NFC_setActionSpriteEnable00);
  tolua_function(tolua_S,"NFC_setCProgressInnerBar",tolua_Dota_NFC_setCProgressInnerBar00);
  tolua_function(tolua_S,"NFC_resumeActionsForSceneSprite",tolua_Dota_NFC_resumeActionsForSceneSprite00);
  tolua_function(tolua_S,"NFC_getArtFontLabel",tolua_Dota_NFC_getArtFontLabel00);
  tolua_function(tolua_S,"NFC_getRichTextCSSByFontStyleID",tolua_Dota_NFC_getRichTextCSSByFontStyleID00);
  tolua_function(tolua_S,"NFC_bindSelectorForBtn",tolua_Dota_NFC_bindSelectorForBtn00);
  tolua_function(tolua_S,"NFC_bindSelectorForDTHeroIcon",tolua_Dota_NFC_bindSelectorForDTHeroIcon00);
  tolua_function(tolua_S,"NFC_bindSelectorForCellDTHeroIcon",tolua_Dota_NFC_bindSelectorForCellDTHeroIcon00);
  tolua_function(tolua_S,"NFC_bindSelectotForCellBtn",tolua_Dota_NFC_bindSelectotForCellBtn00);
  tolua_function(tolua_S,"NFC_bindSelectorForTouchSprite",tolua_Dota_NFC_bindSelectorForTouchSprite00);
  tolua_function(tolua_S,"NFC_bindMenuSpriteAttachParams",tolua_Dota_NFC_bindMenuSpriteAttachParams00);
  tolua_function(tolua_S,"NFC_setMenuSpriteAttachParam",tolua_Dota_NFC_setMenuSpriteAttachParam00);
  tolua_function(tolua_S,"NFC_setTabMenuState",tolua_Dota_NFC_setTabMenuState00);
  tolua_function(tolua_S,"NFC_setMenuEnable",tolua_Dota_NFC_setMenuEnable00);
  tolua_function(tolua_S,"NFC_setNodeVisable",tolua_Dota_NFC_setNodeVisable00);
  tolua_function(tolua_S,"NFC_setTimeLabel",tolua_Dota_NFC_setTimeLabel00);
  tolua_function(tolua_S,"NFC_createLabelByViewData",tolua_Dota_NFC_createLabelByViewData00);
  tolua_function(tolua_S,"NFC_createLabelMutilineByViewData",tolua_Dota_NFC_createLabelMutilineByViewData00);
  tolua_function(tolua_S,"NFC_getHeightOfLabel",tolua_Dota_NFC_getHeightOfLabel00);
  tolua_function(tolua_S,"NFC_refreshTableView",tolua_Dota_NFC_refreshTableView00);
  tolua_function(tolua_S,"NFC_setOffsetForTableView",tolua_Dota_NFC_setOffsetForTableView00);
  tolua_function(tolua_S,"NFC_refreshTableViewAndSetOldOffset",tolua_Dota_NFC_refreshTableViewAndSetOldOffset00);
  tolua_function(tolua_S,"NFC_refreshScrollView",tolua_Dota_NFC_refreshScrollView00);
  tolua_function(tolua_S,"NFC_setPicForCCSprite",tolua_Dota_NFC_setPicForCCSprite00);
  tolua_function(tolua_S,"NFC_setPicForCCSprite",tolua_Dota_NFC_setPicForCCSprite01);
  tolua_function(tolua_S,"NFC_setPicForCCSprite",tolua_Dota_NFC_setPicForCCSprite02);
  tolua_function(tolua_S,"NFC_setPicForCCSprite_2",tolua_Dota_NFC_setPicForCCSprite_200);
  tolua_function(tolua_S,"NFC_setPicScale",tolua_Dota_NFC_setPicScale00);
  tolua_function(tolua_S,"NFC_getHeightOfSprite",tolua_Dota_NFC_getHeightOfSprite00);
  tolua_function(tolua_S,"NFC_setSpriteFlipX",tolua_Dota_NFC_setSpriteFlipX00);
  tolua_function(tolua_S,"NFC_setSpriteFlipY",tolua_Dota_NFC_setSpriteFlipY00);
  tolua_function(tolua_S,"NFC_createSpriteByViewData",tolua_Dota_NFC_createSpriteByViewData00);
  tolua_function(tolua_S,"NFC_getSizeFromSprite",tolua_Dota_NFC_getSizeFromSprite00);
  tolua_function(tolua_S,"NFC_changeImageForCSprite",tolua_Dota_NFC_changeImageForCSprite00);
  tolua_function(tolua_S,"NFC_setSpriteColor",tolua_Dota_NFC_setSpriteColor00);
  tolua_function(tolua_S,"NFC_setGrapSprite",tolua_Dota_NFC_setGrapSprite00);
  tolua_function(tolua_S,"NFC_setEnabledForMenuItem",tolua_Dota_NFC_setEnabledForMenuItem00);
  tolua_function(tolua_S,"NFC_setEnabledForMenuItem",tolua_Dota_NFC_setEnabledForMenuItem01);
  tolua_function(tolua_S,"NFC_getMenuItem",tolua_Dota_NFC_getMenuItem00);
  tolua_function(tolua_S,"NFC_createCLabelButtonByViewData",tolua_Dota_NFC_createCLabelButtonByViewData00);
  tolua_function(tolua_S,"NFC_createMenuItemByViewData",tolua_Dota_NFC_createMenuItemByViewData00);
  tolua_function(tolua_S,"NFC_setNormalImageForMenuItem",tolua_Dota_NFC_setNormalImageForMenuItem00);
  tolua_function(tolua_S,"NFC_setNoramlImageByUIIndex",tolua_Dota_NFC_setNoramlImageByUIIndex00);
  tolua_function(tolua_S,"NFC_setSelectedImageForMenuItem",tolua_Dota_NFC_setSelectedImageForMenuItem00);
  tolua_function(tolua_S,"NFC_setDisabledImageForMenuItem",tolua_Dota_NFC_setDisabledImageForMenuItem00);
  tolua_function(tolua_S,"NFC_getMenuItemSpriteSI",tolua_Dota_NFC_getMenuItemSpriteSI00);
  tolua_function(tolua_S,"NFC_setProgressForCProgressInnerBar",tolua_Dota_NFC_setProgressForCProgressInnerBar00);
  tolua_function(tolua_S,"NFC_createGuideArrow",tolua_Dota_NFC_createGuideArrow00);
  tolua_function(tolua_S,"NFC_createDTAwardBoardByViewData",tolua_Dota_NFC_createDTAwardBoardByViewData00);
  tolua_function(tolua_S,"NFC_setDTHeroIcon",tolua_Dota_NFC_setDTHeroIcon00);
  tolua_function(tolua_S,"NFC_setDTHeroIconVisiable",tolua_Dota_NFC_setDTHeroIconVisiable00);
  tolua_function(tolua_S,"NFC_bindDTHeroCellSelectorAndAttahParam",tolua_Dota_NFC_bindDTHeroCellSelectorAndAttahParam00);
  tolua_function(tolua_S,"NFC_setDTHeroQualiy",tolua_Dota_NFC_setDTHeroQualiy00);
  tolua_function(tolua_S,"NFC_setDTHeroColor",tolua_Dota_NFC_setDTHeroColor00);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"DTAwardBoard","DTAwardBoard","CCNode",tolua_collect_DTAwardBoard);
  #else
  tolua_cclass(tolua_S,"DTAwardBoard","DTAwardBoard","CCNode",NULL);
  #endif
  tolua_beginmodule(tolua_S,"DTAwardBoard");
   tolua_function(tolua_S,"new",tolua_Dota_DTAwardBoard_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_DTAwardBoard_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_DTAwardBoard_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_DTAwardBoard_delete00);
   tolua_function(tolua_S,"create",tolua_Dota_DTAwardBoard_create00);
   tolua_function(tolua_S,"init",tolua_Dota_DTAwardBoard_init00);
   tolua_function(tolua_S,"ChangeObject",tolua_Dota_DTAwardBoard_ChangeObject00);
   tolua_function(tolua_S,"setTarget",tolua_Dota_DTAwardBoard_setTarget00);
   tolua_function(tolua_S,"setTag",tolua_Dota_DTAwardBoard_setTag00);
   tolua_function(tolua_S,"setIDX",tolua_Dota_DTAwardBoard_setIDX00);
   tolua_function(tolua_S,"setAttachParam",tolua_Dota_DTAwardBoard_setAttachParam00);
   tolua_function(tolua_S,"getIDX",tolua_Dota_DTAwardBoard_getIDX00);
   tolua_function(tolua_S,"setContentScale",tolua_Dota_DTAwardBoard_setContentScale00);
   tolua_function(tolua_S,"getContentScale",tolua_Dota_DTAwardBoard_getContentScale00);
   tolua_function(tolua_S,"getContentSize",tolua_Dota_DTAwardBoard_getContentSize00);
   tolua_function(tolua_S,"setPosition",tolua_Dota_DTAwardBoard_setPosition00);
   tolua_function(tolua_S,"setEnabled",tolua_Dota_DTAwardBoard_setEnabled00);
   tolua_function(tolua_S,"setDisabled",tolua_Dota_DTAwardBoard_setDisabled00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"DTEquipBoardDelegate","DTEquipBoardDelegate","",NULL);
  tolua_beginmodule(tolua_S,"DTEquipBoardDelegate");
   tolua_function(tolua_S,"CallBack_ClickEquip",tolua_Dota_DTEquipBoardDelegate_CallBack_ClickEquip00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"DTEquipBoard","DTEquipBoard","CCNode",tolua_collect_DTEquipBoard);
  #else
  tolua_cclass(tolua_S,"DTEquipBoard","DTEquipBoard","CCNode",NULL);
  #endif
  tolua_beginmodule(tolua_S,"DTEquipBoard");
   tolua_function(tolua_S,"new",tolua_Dota_DTEquipBoard_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_DTEquipBoard_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_DTEquipBoard_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_DTEquipBoard_delete00);
   tolua_function(tolua_S,"create",tolua_Dota_DTEquipBoard_create00);
   tolua_function(tolua_S,"init",tolua_Dota_DTEquipBoard_init00);
   tolua_function(tolua_S,"SetEquip",tolua_Dota_DTEquipBoard_SetEquip00);
   tolua_function(tolua_S,"RemoveEquip",tolua_Dota_DTEquipBoard_RemoveEquip00);
   tolua_function(tolua_S,"setPosition",tolua_Dota_DTEquipBoard_setPosition00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"DTHeroIcon","DTHeroIcon","CCNode",NULL);
  tolua_beginmodule(tolua_S,"DTHeroIcon");
   tolua_function(tolua_S,"createHeroIcon",tolua_Dota_DTHeroIcon_createHeroIcon00);
   tolua_function(tolua_S,"setHeroIconID",tolua_Dota_DTHeroIcon_setHeroIconID00);
   tolua_function(tolua_S,"setHeroIconVisable",tolua_Dota_DTHeroIcon_setHeroIconVisable00);
   tolua_function(tolua_S,"setHeroQualiy",tolua_Dota_DTHeroIcon_setHeroQualiy00);
   tolua_function(tolua_S,"setIconScale",tolua_Dota_DTHeroIcon_setIconScale00);
   tolua_function(tolua_S,"setIconColor",tolua_Dota_DTHeroIcon_setIconColor00);
   tolua_function(tolua_S,"setHeroAttachParam",tolua_Dota_DTHeroIcon_setHeroAttachParam00);
   tolua_function(tolua_S,"setPosition",tolua_Dota_DTHeroIcon_setPosition00);
   tolua_function(tolua_S,"getPosition",tolua_Dota_DTHeroIcon_getPosition00);
   tolua_function(tolua_S,"setMenuSelector",tolua_Dota_DTHeroIcon_setMenuSelector00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"DTRoleStatusBarDelegate","DTRoleStatusBarDelegate","",NULL);
  tolua_beginmodule(tolua_S,"DTRoleStatusBarDelegate");
   tolua_function(tolua_S,"AvatarClickEvent",tolua_Dota_DTRoleStatusBarDelegate_AvatarClickEvent00);
   tolua_function(tolua_S,"SkillClickEvent",tolua_Dota_DTRoleStatusBarDelegate_SkillClickEvent00);
   tolua_function(tolua_S,"AddTLClickEvent",tolua_Dota_DTRoleStatusBarDelegate_AddTLClickEvent00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"DTRoleStatusBar","DTRoleStatusBar","CCNode",tolua_collect_DTRoleStatusBar);
  #else
  tolua_cclass(tolua_S,"DTRoleStatusBar","DTRoleStatusBar","CCNode",NULL);
  #endif
  tolua_beginmodule(tolua_S,"DTRoleStatusBar");
   tolua_function(tolua_S,"new",tolua_Dota_DTRoleStatusBar_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_DTRoleStatusBar_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_DTRoleStatusBar_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_DTRoleStatusBar_delete00);
   tolua_function(tolua_S,"create",tolua_Dota_DTRoleStatusBar_create00);
   tolua_function(tolua_S,"init",tolua_Dota_DTRoleStatusBar_init00);
   tolua_function(tolua_S,"setDelegate",tolua_Dota_DTRoleStatusBar_setDelegate00);
   tolua_function(tolua_S,"Tick",tolua_Dota_DTRoleStatusBar_Tick00);
   tolua_function(tolua_S,"Tick_Battle",tolua_Dota_DTRoleStatusBar_Tick_Battle00);
   tolua_function(tolua_S,"Refresh",tolua_Dota_DTRoleStatusBar_Refresh00);
   tolua_function(tolua_S,"ResetPropertyByNode",tolua_Dota_DTRoleStatusBar_ResetPropertyByNode00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"DTTimedGrayWindow","DTTimedGrayWindow","IWindow",tolua_collect_DTTimedGrayWindow);
  #else
  tolua_cclass(tolua_S,"DTTimedGrayWindow","DTTimedGrayWindow","IWindow",NULL);
  #endif
  tolua_beginmodule(tolua_S,"DTTimedGrayWindow");
   tolua_function(tolua_S,"new",tolua_Dota_DTTimedGrayWindow_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_DTTimedGrayWindow_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_DTTimedGrayWindow_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_DTTimedGrayWindow_delete00);
   tolua_function(tolua_S,"Init",tolua_Dota_DTTimedGrayWindow_Init00);
   tolua_function(tolua_S,"Load",tolua_Dota_DTTimedGrayWindow_Load00);
   tolua_function(tolua_S,"Tick",tolua_Dota_DTTimedGrayWindow_Tick00);
   tolua_function(tolua_S,"Destroy",tolua_Dota_DTTimedGrayWindow_Destroy00);
   tolua_function(tolua_S,"OnEventHandler",tolua_Dota_DTTimedGrayWindow_OnEventHandler00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"BlurSprite","BlurSprite","CCSprite",NULL);
  tolua_beginmodule(tolua_S,"BlurSprite");
   tolua_function(tolua_S,"setBlurSize",tolua_Dota_BlurSprite_setBlurSize00);
   tolua_function(tolua_S,"create",tolua_Dota_BlurSprite_create00);
   tolua_function(tolua_S,"initWithTexture",tolua_Dota_BlurSprite_initWithTexture00);
   tolua_function(tolua_S,"draw",tolua_Dota_BlurSprite_draw00);
   tolua_function(tolua_S,"initProgram",tolua_Dota_BlurSprite_initProgram00);
   tolua_function(tolua_S,"listenBackToForeground",tolua_Dota_BlurSprite_listenBackToForeground00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"RollingBoard","RollingBoard","CCNode",NULL);
  tolua_beginmodule(tolua_S,"RollingBoard");
   tolua_function(tolua_S,"create",tolua_Dota_RollingBoard_create00);
   tolua_function(tolua_S,"init",tolua_Dota_RollingBoard_init00);
   tolua_function(tolua_S,"RegisterCallBackScript",tolua_Dota_RollingBoard_RegisterCallBackScript00);
   tolua_function(tolua_S,"SetResultNum",tolua_Dota_RollingBoard_SetResultNum00);
   tolua_function(tolua_S,"Run",tolua_Dota_RollingBoard_Run00);
   tolua_function(tolua_S,"Stop",tolua_Dota_RollingBoard_Stop00);
   tolua_function(tolua_S,"ResetZero",tolua_Dota_RollingBoard_ResetZero00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"UIViewData","UIViewData","IData",NULL);
  tolua_beginmodule(tolua_S,"UIViewData");
   tolua_variable(tolua_S,"idx_",tolua_get_UIViewData_idx_,tolua_set_UIViewData_idx_);
   tolua_variable(tolua_S,"hide_",tolua_get_UIViewData_hide_,tolua_set_UIViewData_hide_);
   tolua_variable(tolua_S,"zorder_",tolua_get_UIViewData_zorder_,tolua_set_UIViewData_zorder_);
   tolua_variable(tolua_S,"scale_",tolua_get_UIViewData_scale_,tolua_set_UIViewData_scale_);
   tolua_variable(tolua_S,"rotation_",tolua_get_UIViewData_rotation_,tolua_set_UIViewData_rotation_);
   tolua_variable(tolua_S,"class_",tolua_get_UIViewData_class_,tolua_set_UIViewData_class_);
   tolua_variable(tolua_S,"touchpriority_",tolua_get_UIViewData_touchpriority_,tolua_set_UIViewData_touchpriority_);
   tolua_variable(tolua_S,"swallow_",tolua_get_UIViewData_swallow_,tolua_set_UIViewData_swallow_);
   tolua_variable(tolua_S,"m_nFontStyleID",tolua_get_UIViewData_m_nFontStyleID,tolua_set_UIViewData_m_nFontStyleID);
   tolua_variable(tolua_S,"labelstring_",tolua_get_UIViewData_labelstring_,tolua_set_UIViewData_labelstring_);
   tolua_variable(tolua_S,"fontname_",tolua_get_UIViewData_fontname_,tolua_set_UIViewData_fontname_);
   tolua_variable(tolua_S,"fontsize_",tolua_get_UIViewData_fontsize_,tolua_set_UIViewData_fontsize_);
   tolua_variable(tolua_S,"colorR_",tolua_get_UIViewData_colorR_,tolua_set_UIViewData_colorR_);
   tolua_variable(tolua_S,"colorG_",tolua_get_UIViewData_colorG_,tolua_set_UIViewData_colorG_);
   tolua_variable(tolua_S,"colorB_",tolua_get_UIViewData_colorB_,tolua_set_UIViewData_colorB_);
   tolua_variable(tolua_S,"alpha_",tolua_get_UIViewData_alpha_,tolua_set_UIViewData_alpha_);
   tolua_variable(tolua_S,"filepath_",tolua_get_UIViewData_filepath_,tolua_set_UIViewData_filepath_);
   tolua_variable(tolua_S,"filepath2_",tolua_get_UIViewData_filepath2_,tolua_set_UIViewData_filepath2_);
   tolua_variable(tolua_S,"filepath3_",tolua_get_UIViewData_filepath3_,tolua_set_UIViewData_filepath3_);
   tolua_variable(tolua_S,"width_",tolua_get_UIViewData_width_,tolua_set_UIViewData_width_);
   tolua_variable(tolua_S,"height_",tolua_get_UIViewData_height_,tolua_set_UIViewData_height_);
   tolua_variable(tolua_S,"anchorx_",tolua_get_UIViewData_anchorx_,tolua_set_UIViewData_anchorx_);
   tolua_variable(tolua_S,"anchory_",tolua_get_UIViewData_anchory_,tolua_set_UIViewData_anchory_);
   tolua_variable(tolua_S,"posx_",tolua_get_UIViewData_posx_,tolua_set_UIViewData_posx_);
   tolua_variable(tolua_S,"posy_",tolua_get_UIViewData_posy_,tolua_set_UIViewData_posy_);
   tolua_variable(tolua_S,"soundid_",tolua_get_UIViewData_soundid_,tolua_set_UIViewData_soundid_);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"RoleInfoData","RoleInfoData","",NULL);
  tolua_beginmodule(tolua_S,"RoleInfoData");
   tolua_variable(tolua_S,"instanceId_",tolua_get_RoleInfoData_instanceId_,tolua_set_RoleInfoData_instanceId_);
   tolua_variable(tolua_S,"name_",tolua_get_RoleInfoData_name_,tolua_set_RoleInfoData_name_);
   tolua_variable(tolua_S,"level_",tolua_get_RoleInfoData_level_,tolua_set_RoleInfoData_level_);
   tolua_variable(tolua_S,"exp_",tolua_get_RoleInfoData_exp_,tolua_set_RoleInfoData_exp_);
   tolua_variable(tolua_S,"maxExp_",tolua_get_RoleInfoData_maxExp_,tolua_set_RoleInfoData_maxExp_);
   tolua_variable(tolua_S,"vitality_",tolua_get_RoleInfoData_vitality_,tolua_set_RoleInfoData_vitality_);
   tolua_variable(tolua_S,"maxVitality_",tolua_get_RoleInfoData_maxVitality_,tolua_set_RoleInfoData_maxVitality_);
   tolua_variable(tolua_S,"jewels_",tolua_get_RoleInfoData_jewels_,tolua_set_RoleInfoData_jewels_);
   tolua_variable(tolua_S,"money_",tolua_get_RoleInfoData_money_,tolua_set_RoleInfoData_money_);
   tolua_variable(tolua_S,"vipLevel_",tolua_get_RoleInfoData_vipLevel_,tolua_set_RoleInfoData_vipLevel_);
   tolua_variable(tolua_S,"btlCapacity_",tolua_get_RoleInfoData_btlCapacity_,tolua_set_RoleInfoData_btlCapacity_);
   tolua_variable(tolua_S,"prestige_",tolua_get_RoleInfoData_prestige_,tolua_set_RoleInfoData_prestige_);
   tolua_variable(tolua_S,"heroLevel_",tolua_get_RoleInfoData_heroLevel_,tolua_set_RoleInfoData_heroLevel_);
   tolua_variable(tolua_S,"honorLevel_",tolua_get_RoleInfoData_honorLevel_,tolua_set_RoleInfoData_honorLevel_);
   tolua_variable(tolua_S,"honorExp_",tolua_get_RoleInfoData_honorExp_,tolua_set_RoleInfoData_honorExp_);
   tolua_variable(tolua_S,"honorMaxExp_",tolua_get_RoleInfoData_honorMaxExp_,tolua_set_RoleInfoData_honorMaxExp_);
   tolua_variable(tolua_S,"mapId_",tolua_get_RoleInfoData_mapId_,tolua_set_RoleInfoData_mapId_);
   tolua_variable(tolua_S,"stageId_",tolua_get_RoleInfoData_stageId_,tolua_set_RoleInfoData_stageId_);
   tolua_variable(tolua_S,"pvpRank_",tolua_get_RoleInfoData_pvpRank_,tolua_set_RoleInfoData_pvpRank_);
   tolua_variable(tolua_S,"guideStep_",tolua_get_RoleInfoData_guideStep_,tolua_set_RoleInfoData_guideStep_);
   tolua_variable(tolua_S,"functionGuide_",tolua_get_RoleInfoData_functionGuide_,tolua_set_RoleInfoData_functionGuide_);
   tolua_variable(tolua_S,"finishTaskCounts_",tolua_get_RoleInfoData_finishTaskCounts_,tolua_set_RoleInfoData_finishTaskCounts_);
   tolua_variable(tolua_S,"unReadEmailCounts_",tolua_get_RoleInfoData_unReadEmailCounts_,tolua_set_RoleInfoData_unReadEmailCounts_);
   tolua_variable(tolua_S,"leftFreeRevenueCount_",tolua_get_RoleInfoData_leftFreeRevenueCount_,tolua_set_RoleInfoData_leftFreeRevenueCount_);
   tolua_variable(tolua_S,"shopTipsNum_",tolua_get_RoleInfoData_shopTipsNum_,tolua_set_RoleInfoData_shopTipsNum_);
   tolua_variable(tolua_S,"heroCapaScore_",tolua_get_RoleInfoData_heroCapaScore_,tolua_set_RoleInfoData_heroCapaScore_);
   tolua_variable(tolua_S,"equipCapaScore_",tolua_get_RoleInfoData_equipCapaScore_,tolua_set_RoleInfoData_equipCapaScore_);
   tolua_variable(tolua_S,"slaveIdentity_",tolua_get_RoleInfoData_slaveIdentity_,tolua_set_RoleInfoData_slaveIdentity_);
   tolua_variable(tolua_S,"applyforFriendNum_",tolua_get_RoleInfoData_applyforFriendNum_,tolua_set_RoleInfoData_applyforFriendNum_);
   tolua_variable(tolua_S,"rewardprompt_",tolua_get_RoleInfoData_rewardprompt_,tolua_set_RoleInfoData_rewardprompt_);
   tolua_variable(tolua_S,"activityprompt_",tolua_get_RoleInfoData_activityprompt_,tolua_set_RoleInfoData_activityprompt_);
   tolua_variable(tolua_S,"mineralempty_",tolua_get_RoleInfoData_mineralempty_,tolua_set_RoleInfoData_mineralempty_);
   tolua_variable(tolua_S,"freesupplica_",tolua_get_RoleInfoData_freesupplica_,tolua_set_RoleInfoData_freesupplica_);
   tolua_variable(tolua_S,"vipreward_",tolua_get_RoleInfoData_vipreward_,tolua_set_RoleInfoData_vipreward_);
   tolua_variable(tolua_S,"bossCanPlay_",tolua_get_RoleInfoData_bossCanPlay_,tolua_set_RoleInfoData_bossCanPlay_);
   tolua_variable(tolua_S,"arena_awardCanReceive_",tolua_get_RoleInfoData_arena_awardCanReceive_,tolua_set_RoleInfoData_arena_awardCanReceive_);
   tolua_variable(tolua_S,"freesummon_",tolua_get_RoleInfoData_freesummon_,tolua_set_RoleInfoData_freesummon_);
   tolua_variable(tolua_S,"hasrefreshshop_",tolua_get_RoleInfoData_hasrefreshshop_,tolua_set_RoleInfoData_hasrefreshshop_);
   tolua_variable(tolua_S,"attribute_",tolua_get_RoleInfoData_attribute__ptr,tolua_set_RoleInfoData_attribute__ptr);
   tolua_variable(tolua_S,"isFastAthleticSpeed",tolua_get_RoleInfoData_isFastAthleticSpeed,tolua_set_RoleInfoData_isFastAthleticSpeed);
   tolua_variable(tolua_S,"athleticsSerialID_",tolua_get_RoleInfoData_athleticsSerialID_,tolua_set_RoleInfoData_athleticsSerialID_);
   tolua_variable(tolua_S,"bHadNewHeroTips",tolua_get_RoleInfoData_bHadNewHeroTips,tolua_set_RoleInfoData_bHadNewHeroTips);
   tolua_variable(tolua_S,"accumuRechNum",tolua_get_RoleInfoData_accumuRechNum,tolua_set_RoleInfoData_accumuRechNum);
   tolua_variable(tolua_S,"multiExp_",tolua_get_RoleInfoData_multiExp_,tolua_set_RoleInfoData_multiExp_);
   tolua_variable(tolua_S,"multiMoney_",tolua_get_RoleInfoData_multiMoney_,tolua_set_RoleInfoData_multiMoney_);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"PlayerStatus","PlayerStatus","",tolua_collect_PlayerStatus);
  #else
  tolua_cclass(tolua_S,"PlayerStatus","PlayerStatus","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"PlayerStatus");
   tolua_variable(tolua_S,"_home_more_isopen",tolua_get_PlayerStatus__home_more_isopen,tolua_set_PlayerStatus__home_more_isopen);
   tolua_function(tolua_S,"new",tolua_Dota_PlayerStatus_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_PlayerStatus_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_PlayerStatus_new00_local);
   tolua_function(tolua_S,"ResetStatus",tolua_Dota_PlayerStatus_ResetStatus00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"RoleInfoDataHandler","RoleInfoDataHandler","IDataHandler",tolua_collect_RoleInfoDataHandler);
  #else
  tolua_cclass(tolua_S,"RoleInfoDataHandler","RoleInfoDataHandler","IDataHandler",NULL);
  #endif
  tolua_beginmodule(tolua_S,"RoleInfoDataHandler");
   tolua_variable(tolua_S,"playerstatus_",tolua_get_RoleInfoDataHandler_playerstatus__ptr,tolua_set_RoleInfoDataHandler_playerstatus__ptr);
   tolua_variable(tolua_S,"m_pRIData",tolua_get_RoleInfoDataHandler_m_pRIData_ptr,tolua_set_RoleInfoDataHandler_m_pRIData_ptr);
   tolua_variable(tolua_S,"isLock",tolua_get_RoleInfoDataHandler_isLock,tolua_set_RoleInfoDataHandler_isLock);
   tolua_variable(tolua_S,"isUpdateCapacity_",tolua_get_RoleInfoDataHandler_isUpdateCapacity_,tolua_set_RoleInfoDataHandler_isUpdateCapacity_);
   tolua_function(tolua_S,"new",tolua_Dota_RoleInfoDataHandler_new00);
   tolua_function(tolua_S,"new_local",tolua_Dota_RoleInfoDataHandler_new00_local);
   tolua_function(tolua_S,".call",tolua_Dota_RoleInfoDataHandler_new00_local);
   tolua_function(tolua_S,"delete",tolua_Dota_RoleInfoDataHandler_delete00);
   tolua_function(tolua_S,"init",tolua_Dota_RoleInfoDataHandler_init00);
   tolua_function(tolua_S,"onDestroy",tolua_Dota_RoleInfoDataHandler_onDestroy00);
   tolua_function(tolua_S,"updateRoleAthleticsSerialID",tolua_Dota_RoleInfoDataHandler_updateRoleAthleticsSerialID00);
   tolua_function(tolua_S,"getRoleCurAthleticsSerialID",tolua_Dota_RoleInfoDataHandler_getRoleCurAthleticsSerialID00);
   tolua_function(tolua_S,"decodePacketData",tolua_Dota_RoleInfoDataHandler_decodePacketData00);
   tolua_function(tolua_S,"isOpenScene",tolua_Dota_RoleInfoDataHandler_isOpenScene00);
   tolua_function(tolua_S,"CheckNewFuncOPenGuide",tolua_Dota_RoleInfoDataHandler_CheckNewFuncOPenGuide00);
   tolua_function(tolua_S,"ToServerFinishNewFunc",tolua_Dota_RoleInfoDataHandler_ToServerFinishNewFunc00);
   tolua_function(tolua_S,"AddTL_Request",tolua_Dota_RoleInfoDataHandler_AddTL_Request00);
   tolua_function(tolua_S,"GetRestTimeToFullTL",tolua_Dota_RoleInfoDataHandler_GetRestTimeToFullTL00);
   tolua_function(tolua_S,"LuaGetInstance",tolua_Dota_RoleInfoDataHandler_LuaGetInstance00);
   tolua_variable(tolua_S,"__cobra_win__Singleton2_RoleInfoDataHandler___",tolua_get_RoleInfoDataHandler___cobra_win__Singleton2_RoleInfoDataHandler___,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"IDataHandler","IDataHandler","",NULL);
  tolua_beginmodule(tolua_S,"IDataHandler");
   tolua_function(tolua_S,"RegisterLuaHandler1",tolua_Dota_IDataHandler_RegisterLuaHandler100);
   tolua_function(tolua_S,"RegisterLuaHandler2",tolua_Dota_IDataHandler_RegisterLuaHandler200);
   tolua_function(tolua_S,"RegisterLuaHandler3",tolua_Dota_IDataHandler_RegisterLuaHandler300);
   tolua_function(tolua_S,"RegisterLuaHandler4",tolua_Dota_IDataHandler_RegisterLuaHandler400);
   tolua_function(tolua_S,"RegisterLuaHandler5",tolua_Dota_IDataHandler_RegisterLuaHandler500);
   tolua_function(tolua_S,"RegisterLuaHandler6",tolua_Dota_IDataHandler_RegisterLuaHandler600);
   tolua_function(tolua_S,"RegisterLuaHandler7",tolua_Dota_IDataHandler_RegisterLuaHandler700);
   tolua_function(tolua_S,"RegisterLuaHandler8",tolua_Dota_IDataHandler_RegisterLuaHandler800);
   tolua_function(tolua_S,"RegisterLuaHandler9",tolua_Dota_IDataHandler_RegisterLuaHandler900);
   tolua_function(tolua_S,"RegisterLuaHandler10",tolua_Dota_IDataHandler_RegisterLuaHandler1000);
   tolua_function(tolua_S,"PushInt_LuaFunc_Result",tolua_Dota_IDataHandler_PushInt_LuaFunc_Result00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"BagTemplateBase","BagTemplateBase","",NULL);
  tolua_beginmodule(tolua_S,"BagTemplateBase");
   tolua_variable(tolua_S,"catogory_",tolua_get_BagTemplateBase_unsigned_catogory_,tolua_set_BagTemplateBase_unsigned_catogory_);
   tolua_variable(tolua_S,"type_",tolua_get_BagTemplateBase_unsigned_type_,tolua_set_BagTemplateBase_unsigned_type_);
   tolua_variable(tolua_S,"templateid_",tolua_get_BagTemplateBase_templateid_,tolua_set_BagTemplateBase_templateid_);
   tolua_variable(tolua_S,"name_",tolua_get_BagTemplateBase_name_,tolua_set_BagTemplateBase_name_);
   tolua_variable(tolua_S,"description_",tolua_get_BagTemplateBase_description_,tolua_set_BagTemplateBase_description_);
   tolua_variable(tolua_S,"level_",tolua_get_BagTemplateBase_unsigned_level_,tolua_set_BagTemplateBase_unsigned_level_);
   tolua_variable(tolua_S,"quality_",tolua_get_BagTemplateBase_unsigned_quality_,tolua_set_BagTemplateBase_unsigned_quality_);
   tolua_variable(tolua_S,"price_",tolua_get_BagTemplateBase_price_,tolua_set_BagTemplateBase_price_);
   tolua_variable(tolua_S,"canUse_",tolua_get_BagTemplateBase_unsigned_canUse_,tolua_set_BagTemplateBase_unsigned_canUse_);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ObjectTemplate","ObjectTemplate","BagTemplateBase",NULL);
  tolua_beginmodule(tolua_S,"ObjectTemplate");
   tolua_variable(tolua_S,"iconId_",tolua_get_ObjectTemplate_iconId_,tolua_set_ObjectTemplate_iconId_);
   tolua_variable(tolua_S,"maxCount_",tolua_get_ObjectTemplate_unsigned_maxCount_,tolua_set_ObjectTemplate_unsigned_maxCount_);
   tolua_variable(tolua_S,"sortIndex",tolua_get_ObjectTemplate_sortIndex,tolua_set_ObjectTemplate_sortIndex);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"EquipTemplate","EquipTemplate","BagTemplateBase",NULL);
  tolua_beginmodule(tolua_S,"EquipTemplate");
   tolua_variable(tolua_S,"maxLevel_",tolua_get_EquipTemplate_unsigned_maxLevel_,tolua_set_EquipTemplate_unsigned_maxLevel_);
   tolua_variable(tolua_S,"iconId_",tolua_get_EquipTemplate_iconId_,tolua_set_EquipTemplate_iconId_);
   tolua_variable(tolua_S,"iconBigId_",tolua_get_EquipTemplate_iconBigId_,tolua_set_EquipTemplate_iconBigId_);
   tolua_variable(tolua_S,"maxCount_",tolua_get_EquipTemplate_unsigned_maxCount_,tolua_set_EquipTemplate_unsigned_maxCount_);
   tolua_variable(tolua_S,"baseAttrType_",tolua_get_EquipTemplate_unsigned_baseAttrType_,tolua_set_EquipTemplate_unsigned_baseAttrType_);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"SkinTemplate","SkinTemplate","BagTemplateBase",NULL);
  tolua_beginmodule(tolua_S,"SkinTemplate");
   tolua_variable(tolua_S,"iconid_",tolua_get_SkinTemplate_iconid_,tolua_set_SkinTemplate_iconid_);
   tolua_variable(tolua_S,"shapeid_",tolua_get_SkinTemplate_shapeid_,tolua_set_SkinTemplate_shapeid_);
   tolua_variable(tolua_S,"maxCount_",tolua_get_SkinTemplate_unsigned_maxCount_,tolua_set_SkinTemplate_unsigned_maxCount_);
   tolua_variable(tolua_S,"maxEnhanceLevel_",tolua_get_SkinTemplate_unsigned_maxEnhanceLevel_,tolua_set_SkinTemplate_unsigned_maxEnhanceLevel_);
   tolua_variable(tolua_S,"strConverRate_",tolua_get_SkinTemplate_unsigned_strConverRate_,tolua_set_SkinTemplate_unsigned_strConverRate_);
   tolua_variable(tolua_S,"agiConverRate_",tolua_get_SkinTemplate_unsigned_agiConverRate_,tolua_set_SkinTemplate_unsigned_agiConverRate_);
   tolua_variable(tolua_S,"intConverRate_",tolua_get_SkinTemplate_unsigned_intConverRate_,tolua_set_SkinTemplate_unsigned_intConverRate_);
   tolua_variable(tolua_S,"mianConverRate_",tolua_get_SkinTemplate_unsigned_mianConverRate_,tolua_set_SkinTemplate_unsigned_mianConverRate_);
   tolua_variable(tolua_S,"waaponid_",tolua_get_SkinTemplate_waaponid_,tolua_set_SkinTemplate_waaponid_);
   tolua_variable(tolua_S,"weaponIconId_",tolua_get_SkinTemplate_weaponIconId_,tolua_set_SkinTemplate_weaponIconId_);
   tolua_variable(tolua_S,"weaponname_",tolua_get_SkinTemplate_weaponname_,tolua_set_SkinTemplate_weaponname_);
   tolua_variable(tolua_S,"weaponDesc_",tolua_get_SkinTemplate_weaponDesc_,tolua_set_SkinTemplate_weaponDesc_);
   tolua_variable(tolua_S,"buffId_",tolua_get_SkinTemplate_unsigned_buffId_,tolua_set_SkinTemplate_unsigned_buffId_);
   tolua_variable(tolua_S,"buffLevel_",tolua_get_SkinTemplate_unsigned_buffLevel_,tolua_set_SkinTemplate_unsigned_buffLevel_);
   tolua_variable(tolua_S,"buffIconId_",tolua_get_SkinTemplate_buffIconId_,tolua_set_SkinTemplate_buffIconId_);
   tolua_variable(tolua_S,"buffName_",tolua_get_SkinTemplate_buffName_,tolua_set_SkinTemplate_buffName_);
   tolua_variable(tolua_S,"buffDesc_",tolua_get_SkinTemplate_buffDesc_,tolua_set_SkinTemplate_buffDesc_);
   tolua_variable(tolua_S,"skillId_",tolua_get_SkinTemplate_unsigned_skillId_,tolua_set_SkinTemplate_unsigned_skillId_);
   tolua_variable(tolua_S,"skllLevel_",tolua_get_SkinTemplate_unsigned_skllLevel_,tolua_set_SkinTemplate_unsigned_skllLevel_);
   tolua_variable(tolua_S,"skillName_",tolua_get_SkinTemplate_skillName_,tolua_set_SkinTemplate_skillName_);
   tolua_variable(tolua_S,"skllDesc_",tolua_get_SkinTemplate_skllDesc_,tolua_set_SkinTemplate_skllDesc_);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"BagEquipData","BagEquipData","IBagData",NULL);
  tolua_beginmodule(tolua_S,"BagEquipData");
   tolua_variable(tolua_S,"template_",tolua_get_BagEquipData_template__ptr,tolua_set_BagEquipData_template__ptr);
   tolua_variable(tolua_S,"id_",tolua_get_BagEquipData_id_,tolua_set_BagEquipData_id_);
   tolua_variable(tolua_S,"level_",tolua_get_BagEquipData_unsigned_level_,tolua_set_BagEquipData_unsigned_level_);
   tolua_variable(tolua_S,"levelMax_",tolua_get_BagEquipData_unsigned_levelMax_,tolua_set_BagEquipData_unsigned_levelMax_);
   tolua_variable(tolua_S,"exp_",tolua_get_BagEquipData_exp_,tolua_set_BagEquipData_exp_);
   tolua_variable(tolua_S,"maxexp_",tolua_get_BagEquipData_maxexp_,tolua_set_BagEquipData_maxexp_);
   tolua_variable(tolua_S,"advanceLevel_",tolua_get_BagEquipData_unsigned_advanceLevel_,tolua_set_BagEquipData_unsigned_advanceLevel_);
   tolua_variable(tolua_S,"advanceLevelMax_",tolua_get_BagEquipData_unsigned_advanceLevelMax_,tolua_set_BagEquipData_unsigned_advanceLevelMax_);
   tolua_variable(tolua_S,"mainAttriValue",tolua_get_BagEquipData_mainAttriValue,tolua_set_BagEquipData_mainAttriValue);
   tolua_variable(tolua_S,"mainAttriValueMax",tolua_get_BagEquipData_mainAttriValueMax,tolua_set_BagEquipData_mainAttriValueMax);
   tolua_variable(tolua_S,"equipScore_",tolua_get_BagEquipData_equipScore_,tolua_set_BagEquipData_equipScore_);
   tolua_variable(tolua_S,"attribute_",tolua_get_BagEquipData_attribute__ptr,tolua_set_BagEquipData_attribute__ptr);
   tolua_variable(tolua_S,"attributeMAX_",tolua_get_BagEquipData_attributeMAX__ptr,tolua_set_BagEquipData_attributeMAX__ptr);
   tolua_variable(tolua_S,"isEquiped_",tolua_get_BagEquipData_isEquiped_,tolua_set_BagEquipData_isEquiped_);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"BagEquipDataHandler","BagEquipDataHandler","IDataHandler",NULL);
  tolua_beginmodule(tolua_S,"BagEquipDataHandler");
   tolua_function(tolua_S,"LuaGetInstance",tolua_Dota_BagEquipDataHandler_LuaGetInstance00);
   tolua_variable(tolua_S,"__cobra_win__Singleton2_BagEquipDataHandler___",tolua_get_BagEquipDataHandler___cobra_win__Singleton2_BagEquipDataHandler___,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"RoleEquipData","RoleEquipData","",NULL);
  tolua_beginmodule(tolua_S,"RoleEquipData");
   tolua_variable(tolua_S,"index_",tolua_get_RoleEquipData_unsigned_index_,tolua_set_RoleEquipData_unsigned_index_);
   tolua_variable(tolua_S,"hasEquip_",tolua_get_RoleEquipData_unsigned_hasEquip_,tolua_set_RoleEquipData_unsigned_hasEquip_);
   tolua_variable(tolua_S,"equipdata_",tolua_get_RoleEquipData_equipdata__ptr,tolua_set_RoleEquipData_equipdata__ptr);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"RoleEquipDataHandler","RoleEquipDataHandler","IDataHandler",NULL);
  tolua_beginmodule(tolua_S,"RoleEquipDataHandler");
   tolua_variable(tolua_S,"m_mapEquipList",tolua_get_RoleEquipDataHandler_m_mapEquipList,tolua_set_RoleEquipDataHandler_m_mapEquipList);
   tolua_variable(tolua_S,"HeroEquip_Tab_IsSelected",tolua_get_RoleEquipDataHandler_HeroEquip_Tab_IsSelected,tolua_set_RoleEquipDataHandler_HeroEquip_Tab_IsSelected);
   tolua_function(tolua_S,"getEquipById",tolua_Dota_RoleEquipDataHandler_getEquipById00);
   tolua_function(tolua_S,"getEquipByType",tolua_Dota_RoleEquipDataHandler_getEquipByType00);
   tolua_function(tolua_S,"getRoleEquips",tolua_Dota_RoleEquipDataHandler_getRoleEquips00);
   tolua_function(tolua_S,"getRoleEquipsByType",tolua_Dota_RoleEquipDataHandler_getRoleEquipsByType00);
   tolua_function(tolua_S,"getRoleEquipsForStrengthen",tolua_Dota_RoleEquipDataHandler_getRoleEquipsForStrengthen00);
   tolua_function(tolua_S,"GetDefaultRoleEquip_EquipLvup",tolua_Dota_RoleEquipDataHandler_GetDefaultRoleEquip_EquipLvup00);
   tolua_function(tolua_S,"CheckAllRoleEquipsCanTopup",tolua_Dota_RoleEquipDataHandler_CheckAllRoleEquipsCanTopup00);
   tolua_function(tolua_S,"OffEquip_Request",tolua_Dota_RoleEquipDataHandler_OffEquip_Request00);
   tolua_function(tolua_S,"decodePacketData_OffEquip",tolua_Dota_RoleEquipDataHandler_decodePacketData_OffEquip00);
   tolua_function(tolua_S,"HanldeAfterOffEquip",tolua_Dota_RoleEquipDataHandler_HanldeAfterOffEquip00);
   tolua_function(tolua_S,"OffEquip_Local",tolua_Dota_RoleEquipDataHandler_OffEquip_Local00);
   tolua_function(tolua_S,"ChangeEquip_Request",tolua_Dota_RoleEquipDataHandler_ChangeEquip_Request00);
   tolua_function(tolua_S,"decodePacketData_ChangeEquip",tolua_Dota_RoleEquipDataHandler_decodePacketData_ChangeEquip00);
   tolua_function(tolua_S,"HanldeAfterChangeEquip",tolua_Dota_RoleEquipDataHandler_HanldeAfterChangeEquip00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_Dota (lua_State* tolua_S) {
 return tolua_Dota_open(tolua_S);
};
#endif

