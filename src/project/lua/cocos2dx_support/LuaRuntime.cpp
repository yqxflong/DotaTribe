/*
** Lua binding: Runtime
** Generated automatically by tolua++-1.0.92 on 07/11/14 14:50:25.
*/

/****************************************************************************
 Copyright (c) 2011 Dota
 ****************************************************************************/

extern "C" {
#include "tolua_fix.h"
}

#include <map>
#include <string>

#include "DebugerSystem.h"
#include "EngineSystem.h"
#include "IAPSystem.h"
#include "NetDebuger.h"
#include "ProfSystem.h"
#include "SoundSystem.h"
#include "TimeSystem.h"
#include "VariableSystem.h"


using namespace std;



#include "LuaRuntime.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_EngineSystem (lua_State* tolua_S)
{
 EngineSystem* self = (EngineSystem*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_IAPSystem (lua_State* tolua_S)
{
 IAPSystem* self = (IAPSystem*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_tm (lua_State* tolua_S)
{
 tm* self = (tm*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_SoundSystem___EFFECT_INFO_ (lua_State* tolua_S)
{
 SoundSystem::_EFFECT_INFO_* self = (SoundSystem::_EFFECT_INFO_*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_VariableSystem___VARIBLE_ (lua_State* tolua_S)
{
 VariableSystem::_VARIBLE_* self = (VariableSystem::_VARIBLE_*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_SoundSystem (lua_State* tolua_S)
{
 SoundSystem* self = (SoundSystem*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_VariableSystem (lua_State* tolua_S)
{
 VariableSystem* self = (VariableSystem*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"DebugerSystem");
 tolua_usertype(tolua_S,"LogicDebuger");
 tolua_usertype(tolua_S,"NetDebuger");
 tolua_usertype(tolua_S,"cobra_win::Singleton2<DebugerSystem>");
 tolua_usertype(tolua_S,"ProfSystem");
 tolua_usertype(tolua_S,"VariableSystem");
 tolua_usertype(tolua_S,"cocos2d::CCAnimation");
 tolua_usertype(tolua_S,"cobra_win::Singleton2<IAPSystem>");
 tolua_usertype(tolua_S,"RenderDebuger");
 tolua_usertype(tolua_S,"SoundSystem");
 tolua_usertype(tolua_S,"tm");
 tolua_usertype(tolua_S,"VariableSystem::_VARIBLE_");
 tolua_usertype(tolua_S,"cobra_win::Singleton2<VariableSystem>");
 tolua_usertype(tolua_S,"cobra_win::Singleton2<TimeSystem>");
 tolua_usertype(tolua_S,"TimeSystem");
 tolua_usertype(tolua_S,"std::list<std::string>");
 tolua_usertype(tolua_S,"std::set<int>");
 tolua_usertype(tolua_S,"IDebuger");
 tolua_usertype(tolua_S,"SoundSystem::_EFFECT_INFO_");
 tolua_usertype(tolua_S,"cobra_win::Singleton2<SoundSystem>");
 tolua_usertype(tolua_S,"IAPSystem");
 tolua_usertype(tolua_S,"cocos2d::CCScene");
 tolua_usertype(tolua_S,"EngineSystem");
 tolua_usertype(tolua_S,"cobra_win::Singleton2<EngineSystem>");
 tolua_usertype(tolua_S,"cocos2d::CCPaymentDelegate");
 tolua_usertype(tolua_S,"cobra_win::Singleton2<ProfSystem>");
}

/* get function: m_pNetDebuger of class  DebugerSystem */
#ifndef TOLUA_DISABLE_tolua_get_DebugerSystem_m_pNetDebuger_ptr
static int tolua_get_DebugerSystem_m_pNetDebuger_ptr(lua_State* tolua_S)
{
  DebugerSystem* self = (DebugerSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_pNetDebuger'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->m_pNetDebuger,"NetDebuger");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_pNetDebuger of class  DebugerSystem */
#ifndef TOLUA_DISABLE_tolua_set_DebugerSystem_m_pNetDebuger_ptr
static int tolua_set_DebugerSystem_m_pNetDebuger_ptr(lua_State* tolua_S)
{
  DebugerSystem* self = (DebugerSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_pNetDebuger'",NULL);
  if (!tolua_isusertype(tolua_S,2,"NetDebuger",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_pNetDebuger = ((NetDebuger*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_pLogicDebuger of class  DebugerSystem */
#ifndef TOLUA_DISABLE_tolua_get_DebugerSystem_m_pLogicDebuger_ptr
static int tolua_get_DebugerSystem_m_pLogicDebuger_ptr(lua_State* tolua_S)
{
  DebugerSystem* self = (DebugerSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_pLogicDebuger'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->m_pLogicDebuger,"LogicDebuger");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_pLogicDebuger of class  DebugerSystem */
#ifndef TOLUA_DISABLE_tolua_set_DebugerSystem_m_pLogicDebuger_ptr
static int tolua_set_DebugerSystem_m_pLogicDebuger_ptr(lua_State* tolua_S)
{
  DebugerSystem* self = (DebugerSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_pLogicDebuger'",NULL);
  if (!tolua_isusertype(tolua_S,2,"LogicDebuger",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_pLogicDebuger = ((LogicDebuger*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: m_pRenderDebuger of class  DebugerSystem */
#ifndef TOLUA_DISABLE_tolua_get_DebugerSystem_m_pRenderDebuger_ptr
static int tolua_get_DebugerSystem_m_pRenderDebuger_ptr(lua_State* tolua_S)
{
  DebugerSystem* self = (DebugerSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_pRenderDebuger'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->m_pRenderDebuger,"RenderDebuger");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: m_pRenderDebuger of class  DebugerSystem */
#ifndef TOLUA_DISABLE_tolua_set_DebugerSystem_m_pRenderDebuger_ptr
static int tolua_set_DebugerSystem_m_pRenderDebuger_ptr(lua_State* tolua_S)
{
  DebugerSystem* self = (DebugerSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'm_pRenderDebuger'",NULL);
  if (!tolua_isusertype(tolua_S,2,"RenderDebuger",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->m_pRenderDebuger = ((RenderDebuger*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLuaInstance of class  DebugerSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_DebugerSystem_GetLuaInstance00
static int tolua_Runtime_DebugerSystem_GetLuaInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DebugerSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DebugerSystem* self = (DebugerSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLuaInstance'", NULL);
#endif
  {
   DebugerSystem* tolua_ret = (DebugerSystem*)  self->GetLuaInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DebugerSystem");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLuaInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_new00
static int tolua_Runtime_EngineSystem_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   EngineSystem* tolua_ret = (EngineSystem*)  Mtolua_new((EngineSystem)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"EngineSystem");
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

/* method: new_local of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_new00_local
static int tolua_Runtime_EngineSystem_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   EngineSystem* tolua_ret = (EngineSystem*)  Mtolua_new((EngineSystem)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"EngineSystem");
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

/* method: delete of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_delete00
static int tolua_Runtime_EngineSystem_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EngineSystem* self = (EngineSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetOS of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_GetOS00
static int tolua_Runtime_EngineSystem_GetOS00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::string tolua_ret = (std::string)  EngineSystem::GetOS();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOS'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDocumentDir of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_GetDocumentDir00
static int tolua_Runtime_EngineSystem_GetDocumentDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::string tolua_ret = (std::string)  EngineSystem::GetDocumentDir();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDocumentDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateDocumentSubDir of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_CreateDocumentSubDir00
static int tolua_Runtime_EngineSystem_CreateDocumentSubDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string subDir = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   std::string tolua_ret = (std::string)  EngineSystem::CreateDocumentSubDir(subDir);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateDocumentSubDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DeleteDocumentSubDir of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_DeleteDocumentSubDir00
static int tolua_Runtime_EngineSystem_DeleteDocumentSubDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string subDir = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   EngineSystem::DeleteDocumentSubDir(subDir);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DeleteDocumentSubDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAppFilePath of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_GetAppFilePath00
static int tolua_Runtime_EngineSystem_GetAppFilePath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::string fileName = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  {
   std::string tolua_ret = (std::string)  EngineSystem::GetAppFilePath(fileName);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAppFilePath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRecordDataPath of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_GetRecordDataPath00
static int tolua_Runtime_EngineSystem_GetRecordDataPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::string tolua_ret = (std::string)  EngineSystem::GetRecordDataPath();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRecordDataPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDeviceType of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_GetDeviceType00
static int tolua_Runtime_EngineSystem_GetDeviceType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   int tolua_ret = (int)  EngineSystem::GetDeviceType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDeviceType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsIPad1 of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_IsIPad100
static int tolua_Runtime_EngineSystem_IsIPad100(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  EngineSystem::IsIPad1();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsIPad1'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsIPhone5 of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_IsIPhone500
static int tolua_Runtime_EngineSystem_IsIPhone500(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  EngineSystem::IsIPhone5();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsIPhone5'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsShowOffers of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_IsShowOffers00
static int tolua_Runtime_EngineSystem_IsShowOffers00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  EngineSystem::IsShowOffers();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsShowOffers'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsAndroid_1136_640 of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_IsAndroid_1136_64000
static int tolua_Runtime_EngineSystem_IsAndroid_1136_64000(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  EngineSystem::IsAndroid_1136_640();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsAndroid_1136_640'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsAndroid_3_2 of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_IsAndroid_3_200
static int tolua_Runtime_EngineSystem_IsAndroid_3_200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  EngineSystem::IsAndroid_3_2();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsAndroid_3_2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsAndroid_4_3 of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_IsAndroid_4_300
static int tolua_Runtime_EngineSystem_IsAndroid_4_300(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  EngineSystem::IsAndroid_4_3();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsAndroid_4_3'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsAndroid_15_9 of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_IsAndroid_15_900
static int tolua_Runtime_EngineSystem_IsAndroid_15_900(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  EngineSystem::IsAndroid_15_9();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsAndroid_15_9'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsAndroid_16_9 of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_IsAndroid_16_900
static int tolua_Runtime_EngineSystem_IsAndroid_16_900(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  EngineSystem::IsAndroid_16_9();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsAndroid_16_9'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsAndroid_16_10 of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_IsAndroid_16_1000
static int tolua_Runtime_EngineSystem_IsAndroid_16_1000(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  EngineSystem::IsAndroid_16_10();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsAndroid_16_10'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsAndroid_1024_600 of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_IsAndroid_1024_60000
static int tolua_Runtime_EngineSystem_IsAndroid_1024_60000(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  EngineSystem::IsAndroid_1024_600();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsAndroid_1024_600'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsAndroid_1184_720 of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_IsAndroid_1184_72000
static int tolua_Runtime_EngineSystem_IsAndroid_1184_72000(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  EngineSystem::IsAndroid_1184_720();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsAndroid_1184_720'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsAndroid_1196_720 of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_IsAndroid_1196_72000
static int tolua_Runtime_EngineSystem_IsAndroid_1196_72000(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  EngineSystem::IsAndroid_1196_720();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsAndroid_1196_720'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScene of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_GetScene00
static int tolua_Runtime_EngineSystem_GetScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EngineSystem* self = (EngineSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetScene'", NULL);
#endif
  {
   cocos2d::CCScene* tolua_ret = (cocos2d::CCScene*)  self->GetScene();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"cocos2d::CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: EnableMultiTouch of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_EnableMultiTouch00
static int tolua_Runtime_EngineSystem_EnableMultiTouch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EngineSystem* self = (EngineSystem*)  tolua_tousertype(tolua_S,1,0);
  bool bEnabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'EnableMultiTouch'", NULL);
#endif
  {
   self->EnableMultiTouch(bEnabled);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EnableMultiTouch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OpenURL of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_OpenURL00
static int tolua_Runtime_EngineSystem_OpenURL00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EngineSystem* self = (EngineSystem*)  tolua_tousertype(tolua_S,1,0);
  char* pBuffer = ((char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OpenURL'", NULL);
#endif
  {
   self->OpenURL(pBuffer);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OpenURL'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ScreenShot of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_ScreenShot00
static int tolua_Runtime_EngineSystem_ScreenShot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EngineSystem* self = (EngineSystem*)  tolua_tousertype(tolua_S,1,0);
  std::string filename = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ScreenShot'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ScreenShot(filename);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ScreenShot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ShowFeedbackDialog of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_ShowFeedbackDialog00
static int tolua_Runtime_EngineSystem_ShowFeedbackDialog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EngineSystem* self = (EngineSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ShowFeedbackDialog'", NULL);
#endif
  {
   self->ShowFeedbackDialog();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ShowFeedbackDialog'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsNetWorkAvailable of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_IsNetWorkAvailable00
static int tolua_Runtime_EngineSystem_IsNetWorkAvailable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EngineSystem* self = (EngineSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsNetWorkAvailable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsNetWorkAvailable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsNetWorkAvailable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ShowAd of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_ShowAd00
static int tolua_Runtime_EngineSystem_ShowAd00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EngineSystem* self = (EngineSystem*)  tolua_tousertype(tolua_S,1,0);
  bool bShow = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ShowAd'", NULL);
#endif
  {
   self->ShowAd(bShow);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ShowAd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UpdateNewVersionDialog of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_UpdateNewVersionDialog00
static int tolua_Runtime_EngineSystem_UpdateNewVersionDialog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EngineSystem* self = (EngineSystem*)  tolua_tousertype(tolua_S,1,0);
  std::string title = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  std::string yes = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  std::string cancel = ((std::string)  tolua_tocppstring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UpdateNewVersionDialog'", NULL);
#endif
  {
   self->UpdateNewVersionDialog(title,yes,cancel);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UpdateNewVersionDialog'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ForceClearAnimationCache of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_ForceClearAnimationCache00
static int tolua_Runtime_EngineSystem_ForceClearAnimationCache00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EngineSystem* self = (EngineSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ForceClearAnimationCache'", NULL);
#endif
  {
   self->ForceClearAnimationCache();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ForceClearAnimationCache'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FreeMemory of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_FreeMemory00
static int tolua_Runtime_EngineSystem_FreeMemory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EngineSystem* self = (EngineSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FreeMemory'", NULL);
#endif
  {
   self->FreeMemory();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FreeMemory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAnimtionByName of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_GetAnimtionByName00
static int tolua_Runtime_EngineSystem_GetAnimtionByName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EngineSystem* self = (EngineSystem*)  tolua_tousertype(tolua_S,1,0);
  std::string name = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAnimtionByName'", NULL);
#endif
  {
   cocos2d::CCAnimation* tolua_ret = (cocos2d::CCAnimation*)  self->GetAnimtionByName(name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"cocos2d::CCAnimation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAnimtionByName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAnimationByID of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_GetAnimationByID00
static int tolua_Runtime_EngineSystem_GetAnimationByID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EngineSystem* self = (EngineSystem*)  tolua_tousertype(tolua_S,1,0);
  int animationID = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAnimationByID'", NULL);
#endif
  {
   cocos2d::CCAnimation* tolua_ret = (cocos2d::CCAnimation*)  self->GetAnimationByID(animationID);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"cocos2d::CCAnimation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAnimationByID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLayoutConfig of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_GetLayoutConfig00
static int tolua_Runtime_EngineSystem_GetLayoutConfig00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EngineSystem* self = (EngineSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLayoutConfig'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetLayoutConfig();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLayoutConfig'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InitAppEnv of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_InitAppEnv00
static int tolua_Runtime_EngineSystem_InitAppEnv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   EngineSystem::InitAppEnv();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InitAppEnv'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoadAppFile of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_LoadAppFile00
static int tolua_Runtime_EngineSystem_LoadAppFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  char* pFileName = ((char*)  tolua_tostring(tolua_S,2,0));
  char* pBuffer = ((char*)  tolua_tostring(tolua_S,3,0));
  unsigned int iLength = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
  {
   bool tolua_ret = (bool)  EngineSystem::LoadAppFile(pFileName,pBuffer,iLength);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushstring(tolua_S,(const char*)pBuffer);
   tolua_pushnumber(tolua_S,(lua_Number)iLength);
  }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadAppFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoadTempFile of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_LoadTempFile00
static int tolua_Runtime_EngineSystem_LoadTempFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  char* pFileName = ((char*)  tolua_tostring(tolua_S,2,0));
  char* pBuffer = ((char*)  tolua_tostring(tolua_S,3,0));
  unsigned int iLength = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
  {
   bool tolua_ret = (bool)  EngineSystem::LoadTempFile(pFileName,pBuffer,iLength);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushstring(tolua_S,(const char*)pBuffer);
   tolua_pushnumber(tolua_S,(lua_Number)iLength);
  }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadTempFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLuaInstance of class  EngineSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_EngineSystem_GetLuaInstance00
static int tolua_Runtime_EngineSystem_GetLuaInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"EngineSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  EngineSystem* self = (EngineSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLuaInstance'", NULL);
#endif
  {
   EngineSystem* tolua_ret = (EngineSystem*)  self->GetLuaInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"EngineSystem");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLuaInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  IAPSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_IAPSystem_new00
static int tolua_Runtime_IAPSystem_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"IAPSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   IAPSystem* tolua_ret = (IAPSystem*)  Mtolua_new((IAPSystem)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"IAPSystem");
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

/* method: new_local of class  IAPSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_IAPSystem_new00_local
static int tolua_Runtime_IAPSystem_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"IAPSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   IAPSystem* tolua_ret = (IAPSystem*)  Mtolua_new((IAPSystem)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"IAPSystem");
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

/* method: delete of class  IAPSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_IAPSystem_delete00
static int tolua_Runtime_IAPSystem_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IAPSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IAPSystem* self = (IAPSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: IsAvailable of class  IAPSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_IAPSystem_IsAvailable00
static int tolua_Runtime_IAPSystem_IsAvailable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IAPSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IAPSystem* self = (IAPSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsAvailable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsAvailable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsAvailable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsHasIAPId of class  IAPSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_IAPSystem_IsHasIAPId00
static int tolua_Runtime_IAPSystem_IsHasIAPId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IAPSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IAPSystem* self = (IAPSystem*)  tolua_tousertype(tolua_S,1,0);
  std::string iapId = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsHasIAPId'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsHasIAPId(iapId);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsHasIAPId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InitPaymentEnv of class  IAPSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_IAPSystem_InitPaymentEnv00
static int tolua_Runtime_IAPSystem_InitPaymentEnv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IAPSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IAPSystem* self = (IAPSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InitPaymentEnv'", NULL);
#endif
  {
   self->InitPaymentEnv();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InitPaymentEnv'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: BuyProductByType of class  IAPSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_IAPSystem_BuyProductByType00
static int tolua_Runtime_IAPSystem_BuyProductByType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IAPSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IAPSystem* self = (IAPSystem*)  tolua_tousertype(tolua_S,1,0);
  int productType = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BuyProductByType'", NULL);
#endif
  {
   self->BuyProductByType(productType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BuyProductByType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: BuyProductById of class  IAPSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_IAPSystem_BuyProductById00
static int tolua_Runtime_IAPSystem_BuyProductById00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IAPSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IAPSystem* self = (IAPSystem*)  tolua_tousertype(tolua_S,1,0);
  std::string productId = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BuyProductById'", NULL);
#endif
  {
   self->BuyProductById(productId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BuyProductById'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SdkBuyProductById of class  IAPSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_IAPSystem_SdkBuyProductById00
static int tolua_Runtime_IAPSystem_SdkBuyProductById00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IAPSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IAPSystem* self = (IAPSystem*)  tolua_tousertype(tolua_S,1,0);
  std::string productId = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SdkBuyProductById'", NULL);
#endif
  {
   self->SdkBuyProductById(productId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SdkBuyProductById'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveIAPId of class  IAPSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_IAPSystem_RemoveIAPId00
static int tolua_Runtime_IAPSystem_RemoveIAPId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IAPSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IAPSystem* self = (IAPSystem*)  tolua_tousertype(tolua_S,1,0);
  std::string iapId = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveIAPId'", NULL);
#endif
  {
   self->RemoveIAPId(iapId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveIAPId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: EndPayment of class  IAPSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_IAPSystem_EndPayment00
static int tolua_Runtime_IAPSystem_EndPayment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IAPSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IAPSystem* self = (IAPSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'EndPayment'", NULL);
#endif
  {
   self->EndPayment();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EndPayment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VerifyIAPIdentifier of class  IAPSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_IAPSystem_VerifyIAPIdentifier00
static int tolua_Runtime_IAPSystem_VerifyIAPIdentifier00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IAPSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IAPSystem* self = (IAPSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VerifyIAPIdentifier'", NULL);
#endif
  {
   self->VerifyIAPIdentifier();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'VerifyIAPIdentifier'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onPayFailed of class  IAPSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_IAPSystem_onPayFailed00
static int tolua_Runtime_IAPSystem_onPayFailed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IAPSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IAPSystem* self = (IAPSystem*)  tolua_tousertype(tolua_S,1,0);
  std::string IAPId = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  std::string error = ((std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onPayFailed'", NULL);
#endif
  {
   self->onPayFailed(IAPId,error);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onPayFailed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onPaySuccess of class  IAPSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_IAPSystem_onPaySuccess00
static int tolua_Runtime_IAPSystem_onPaySuccess00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IAPSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IAPSystem* self = (IAPSystem*)  tolua_tousertype(tolua_S,1,0);
  std::string IAPId = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  std::string transactionId = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  std::string transactionReceipt = ((std::string)  tolua_tocppstring(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onPaySuccess'", NULL);
#endif
  {
   self->onPaySuccess(IAPId,transactionId,transactionReceipt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onPaySuccess'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onVerifySuccess of class  IAPSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_IAPSystem_onVerifySuccess00
static int tolua_Runtime_IAPSystem_onVerifySuccess00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IAPSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IAPSystem* self = (IAPSystem*)  tolua_tousertype(tolua_S,1,0);
  std::string IAPId = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onVerifySuccess'", NULL);
#endif
  {
   self->onVerifySuccess(IAPId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onVerifySuccess'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onVerifyFailed of class  IAPSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_IAPSystem_onVerifyFailed00
static int tolua_Runtime_IAPSystem_onVerifyFailed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IAPSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IAPSystem* self = (IAPSystem*)  tolua_tousertype(tolua_S,1,0);
  std::string IAPId = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  std::string error = ((std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onVerifyFailed'", NULL);
#endif
  {
   self->onVerifyFailed(IAPId,error);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onVerifyFailed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onRestoreSuccess of class  IAPSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_IAPSystem_onRestoreSuccess00
static int tolua_Runtime_IAPSystem_onRestoreSuccess00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IAPSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IAPSystem* self = (IAPSystem*)  tolua_tousertype(tolua_S,1,0);
  std::string IAPId = ((std::string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onRestoreSuccess'", NULL);
#endif
  {
   self->onRestoreSuccess(IAPId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onRestoreSuccess'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: insertPayment of class  IAPSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_IAPSystem_insertPayment00
static int tolua_Runtime_IAPSystem_insertPayment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IAPSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IAPSystem* self = (IAPSystem*)  tolua_tousertype(tolua_S,1,0);
  std::string productId = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  std::string transactionId = ((std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'insertPayment'", NULL);
#endif
  {
   self->insertPayment(productId,transactionId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'insertPayment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLuaInstance of class  IAPSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_IAPSystem_GetLuaInstance00
static int tolua_Runtime_IAPSystem_GetLuaInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IAPSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IAPSystem* self = (IAPSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLuaInstance'", NULL);
#endif
  {
   IAPSystem* tolua_ret = (IAPSystem*)  self->GetLuaInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"IAPSystem");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLuaInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __cobra_win of class  IAPSystem */
#ifndef TOLUA_DISABLE_tolua_get_IAPSystem___cobra_win__Singleton2_IAPSystem___
static int tolua_get_IAPSystem___cobra_win__Singleton2_IAPSystem___(lua_State* tolua_S)
{
  IAPSystem* self = (IAPSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__cobra_win'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<cobra_win::Singleton2<IAPSystem>*>(self), "cobra_win::Singleton2<IAPSystem>");
#else
   tolua_pushusertype(tolua_S,(void*)((cobra_win::Singleton2<IAPSystem>*)self), "cobra_win::Singleton2<IAPSystem>");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDebugerType of class  IDebuger */
#ifndef TOLUA_DISABLE_tolua_Runtime_IDebuger_GetDebugerType00
static int tolua_Runtime_IDebuger_GetDebugerType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"IDebuger",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  IDebuger* self = (IDebuger*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDebugerType'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetDebugerType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDebugerType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAccount_Auth_Begin of class  NetDebuger */
#ifndef TOLUA_DISABLE_tolua_Runtime_NetDebuger_setAccount_Auth_Begin00
static int tolua_Runtime_NetDebuger_setAccount_Auth_Begin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetDebuger",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetDebuger* self = (NetDebuger*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAccount_Auth_Begin'", NULL);
#endif
  {
   self->setAccount_Auth_Begin();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAccount_Auth_Begin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAccount_Auth_End of class  NetDebuger */
#ifndef TOLUA_DISABLE_tolua_Runtime_NetDebuger_setAccount_Auth_End00
static int tolua_Runtime_NetDebuger_setAccount_Auth_End00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetDebuger",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetDebuger* self = (NetDebuger*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAccount_Auth_End'", NULL);
#endif
  {
   self->setAccount_Auth_End();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAccount_Auth_End'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLogin_Begin of class  NetDebuger */
#ifndef TOLUA_DISABLE_tolua_Runtime_NetDebuger_setLogin_Begin00
static int tolua_Runtime_NetDebuger_setLogin_Begin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetDebuger",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetDebuger* self = (NetDebuger*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLogin_Begin'", NULL);
#endif
  {
   self->setLogin_Begin();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLogin_Begin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLogin_End of class  NetDebuger */
#ifndef TOLUA_DISABLE_tolua_Runtime_NetDebuger_setLogin_End00
static int tolua_Runtime_NetDebuger_setLogin_End00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetDebuger",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetDebuger* self = (NetDebuger*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLogin_End'", NULL);
#endif
  {
   self->setLogin_End();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLogin_End'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRole_Begin of class  NetDebuger */
#ifndef TOLUA_DISABLE_tolua_Runtime_NetDebuger_setRole_Begin00
static int tolua_Runtime_NetDebuger_setRole_Begin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetDebuger",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetDebuger* self = (NetDebuger*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRole_Begin'", NULL);
#endif
  {
   self->setRole_Begin();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRole_Begin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRole_End of class  NetDebuger */
#ifndef TOLUA_DISABLE_tolua_Runtime_NetDebuger_setRole_End00
static int tolua_Runtime_NetDebuger_setRole_End00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetDebuger",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetDebuger* self = (NetDebuger*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRole_End'", NULL);
#endif
  {
   self->setRole_End();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRole_End'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ToServer_LoginDebugInfo of class  NetDebuger */
#ifndef TOLUA_DISABLE_tolua_Runtime_NetDebuger_ToServer_LoginDebugInfo00
static int tolua_Runtime_NetDebuger_ToServer_LoginDebugInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetDebuger",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetDebuger* self = (NetDebuger*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ToServer_LoginDebugInfo'", NULL);
#endif
  {
   self->ToServer_LoginDebugInfo();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ToServer_LoginDebugInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Start of class  ProfSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_ProfSystem_Start00
static int tolua_Runtime_ProfSystem_Start00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProfSystem",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProfSystem* self = (ProfSystem*)  tolua_tousertype(tolua_S,1,0);
  const char* pChunkName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Start'", NULL);
#endif
  {
   self->Start(pChunkName);
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

/* method: End of class  ProfSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_ProfSystem_End00
static int tolua_Runtime_ProfSystem_End00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProfSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProfSystem* self = (ProfSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'End'", NULL);
#endif
  {
   self->End();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'End'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLuaInstance of class  ProfSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_ProfSystem_GetLuaInstance00
static int tolua_Runtime_ProfSystem_GetLuaInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProfSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProfSystem* self = (ProfSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLuaInstance'", NULL);
#endif
  {
   ProfSystem* tolua_ret = (ProfSystem*)  self->GetLuaInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ProfSystem");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLuaInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mEffectType of class  _EFFECT_INFO_ */
#ifndef TOLUA_DISABLE_tolua_get_SoundSystem___EFFECT_INFO__mEffectType
static int tolua_get_SoundSystem___EFFECT_INFO__mEffectType(lua_State* tolua_S)
{
  SoundSystem::_EFFECT_INFO_* self = (SoundSystem::_EFFECT_INFO_*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mEffectType'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->mEffectType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mEffectType of class  _EFFECT_INFO_ */
#ifndef TOLUA_DISABLE_tolua_set_SoundSystem___EFFECT_INFO__mEffectType
static int tolua_set_SoundSystem___EFFECT_INFO__mEffectType(lua_State* tolua_S)
{
  SoundSystem::_EFFECT_INFO_* self = (SoundSystem::_EFFECT_INFO_*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mEffectType'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mEffectType = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mSoundName of class  _EFFECT_INFO_ */
#ifndef TOLUA_DISABLE_tolua_get_SoundSystem___EFFECT_INFO__mSoundName
static int tolua_get_SoundSystem___EFFECT_INFO__mSoundName(lua_State* tolua_S)
{
  SoundSystem::_EFFECT_INFO_* self = (SoundSystem::_EFFECT_INFO_*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mSoundName'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->mSoundName);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mSoundName of class  _EFFECT_INFO_ */
#ifndef TOLUA_DISABLE_tolua_set_SoundSystem___EFFECT_INFO__mSoundName
static int tolua_set_SoundSystem___EFFECT_INFO__mSoundName(lua_State* tolua_S)
{
  SoundSystem::_EFFECT_INFO_* self = (SoundSystem::_EFFECT_INFO_*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mSoundName'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->mSoundName,(const char*)tolua_tostring(tolua_S,2,0),128-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mSoundId of class  _EFFECT_INFO_ */
#ifndef TOLUA_DISABLE_tolua_get_SoundSystem___EFFECT_INFO__mSoundId
static int tolua_get_SoundSystem___EFFECT_INFO__mSoundId(lua_State* tolua_S)
{
  SoundSystem::_EFFECT_INFO_* self = (SoundSystem::_EFFECT_INFO_*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mSoundId'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->mSoundId);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mSoundId of class  _EFFECT_INFO_ */
#ifndef TOLUA_DISABLE_tolua_set_SoundSystem___EFFECT_INFO__mSoundId
static int tolua_set_SoundSystem___EFFECT_INFO__mSoundId(lua_State* tolua_S)
{
  SoundSystem::_EFFECT_INFO_* self = (SoundSystem::_EFFECT_INFO_*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mSoundId'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mSoundId = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mStartTime of class  _EFFECT_INFO_ */
#ifndef TOLUA_DISABLE_tolua_get_SoundSystem___EFFECT_INFO__mStartTime
static int tolua_get_SoundSystem___EFFECT_INFO__mStartTime(lua_State* tolua_S)
{
  SoundSystem::_EFFECT_INFO_* self = (SoundSystem::_EFFECT_INFO_*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mStartTime'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->mStartTime);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mStartTime of class  _EFFECT_INFO_ */
#ifndef TOLUA_DISABLE_tolua_set_SoundSystem___EFFECT_INFO__mStartTime
static int tolua_set_SoundSystem___EFFECT_INFO__mStartTime(lua_State* tolua_S)
{
  SoundSystem::_EFFECT_INFO_* self = (SoundSystem::_EFFECT_INFO_*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mStartTime'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mStartTime = ((long long)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mLoop of class  _EFFECT_INFO_ */
#ifndef TOLUA_DISABLE_tolua_get_SoundSystem___EFFECT_INFO__mLoop
static int tolua_get_SoundSystem___EFFECT_INFO__mLoop(lua_State* tolua_S)
{
  SoundSystem::_EFFECT_INFO_* self = (SoundSystem::_EFFECT_INFO_*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mLoop'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->mLoop);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mLoop of class  _EFFECT_INFO_ */
#ifndef TOLUA_DISABLE_tolua_set_SoundSystem___EFFECT_INFO__mLoop
static int tolua_set_SoundSystem___EFFECT_INFO__mLoop(lua_State* tolua_S)
{
  SoundSystem::_EFFECT_INFO_* self = (SoundSystem::_EFFECT_INFO_*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mLoop'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mLoop = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  _EFFECT_INFO_ */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem__EFFECT_INFO__new00
static int tolua_Runtime_SoundSystem__EFFECT_INFO__new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SoundSystem::_EFFECT_INFO_",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SoundSystem::_EFFECT_INFO_* tolua_ret = (SoundSystem::_EFFECT_INFO_*)  Mtolua_new((SoundSystem::_EFFECT_INFO_)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SoundSystem::_EFFECT_INFO_");
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

/* method: new_local of class  _EFFECT_INFO_ */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem__EFFECT_INFO__new00_local
static int tolua_Runtime_SoundSystem__EFFECT_INFO__new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SoundSystem::_EFFECT_INFO_",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SoundSystem::_EFFECT_INFO_* tolua_ret = (SoundSystem::_EFFECT_INFO_*)  Mtolua_new((SoundSystem::_EFFECT_INFO_)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SoundSystem::_EFFECT_INFO_");
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

/* method: new of class  SoundSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem_new00
static int tolua_Runtime_SoundSystem_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SoundSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SoundSystem* tolua_ret = (SoundSystem*)  Mtolua_new((SoundSystem)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SoundSystem");
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

/* method: new_local of class  SoundSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem_new00_local
static int tolua_Runtime_SoundSystem_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SoundSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   SoundSystem* tolua_ret = (SoundSystem*)  Mtolua_new((SoundSystem)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SoundSystem");
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

/* method: delete of class  SoundSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem_delete00
static int tolua_Runtime_SoundSystem_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSystem* self = (SoundSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: MuteBackgroundMusic of class  SoundSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem_MuteBackgroundMusic00
static int tolua_Runtime_SoundSystem_MuteBackgroundMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSystem",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSystem* self = (SoundSystem*)  tolua_tousertype(tolua_S,1,0);
  bool bMute = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MuteBackgroundMusic'", NULL);
#endif
  {
   self->MuteBackgroundMusic(bMute);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MuteBackgroundMusic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MuteEffectSound of class  SoundSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem_MuteEffectSound00
static int tolua_Runtime_SoundSystem_MuteEffectSound00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSystem",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSystem* self = (SoundSystem*)  tolua_tousertype(tolua_S,1,0);
  bool bMute = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MuteEffectSound'", NULL);
#endif
  {
   self->MuteEffectSound(bMute);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MuteEffectSound'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsBackgroundMusicMute of class  SoundSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem_IsBackgroundMusicMute00
static int tolua_Runtime_SoundSystem_IsBackgroundMusicMute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSystem* self = (SoundSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsBackgroundMusicMute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsBackgroundMusicMute();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsBackgroundMusicMute'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsEffectSoundMute of class  SoundSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem_IsEffectSoundMute00
static int tolua_Runtime_SoundSystem_IsEffectSoundMute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSystem* self = (SoundSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsEffectSoundMute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsEffectSoundMute();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsEffectSoundMute'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PlayEffect of class  SoundSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem_PlayEffect00
static int tolua_Runtime_SoundSystem_PlayEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSystem* self = (SoundSystem*)  tolua_tousertype(tolua_S,1,0);
  int effectID = ((int)  tolua_tonumber(tolua_S,2,0));
  std::string soundName = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  bool bLoop = ((bool)  tolua_toboolean(tolua_S,4,0));
  float fPitch = ((float)  tolua_tonumber(tolua_S,5,1.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PlayEffect'", NULL);
#endif
  {
   self->PlayEffect(effectID,soundName,bLoop,fPitch);
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

/* method: StopEffect of class  SoundSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem_StopEffect00
static int tolua_Runtime_SoundSystem_StopEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSystem* self = (SoundSystem*)  tolua_tousertype(tolua_S,1,0);
  int effectID = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StopEffect'", NULL);
#endif
  {
   self->StopEffect(effectID);
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

/* method: StopAllEffect of class  SoundSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem_StopAllEffect00
static int tolua_Runtime_SoundSystem_StopAllEffect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSystem* self = (SoundSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StopAllEffect'", NULL);
#endif
  {
   self->StopAllEffect();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StopAllEffect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PlayBackgroundMusic of class  SoundSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem_PlayBackgroundMusic00
static int tolua_Runtime_SoundSystem_PlayBackgroundMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSystem",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSystem* self = (SoundSystem*)  tolua_tousertype(tolua_S,1,0);
  std::string soundName = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  int soundVolume = ((int)  tolua_tonumber(tolua_S,3,10));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PlayBackgroundMusic'", NULL);
#endif
  {
   self->PlayBackgroundMusic(soundName,soundVolume);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PlayBackgroundMusic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: StopBackgroundMusic of class  SoundSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem_StopBackgroundMusic00
static int tolua_Runtime_SoundSystem_StopBackgroundMusic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSystem* self = (SoundSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StopBackgroundMusic'", NULL);
#endif
  {
   self->StopBackgroundMusic();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StopBackgroundMusic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PreLoadSoundEffectQueue of class  SoundSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem_PreLoadSoundEffectQueue00
static int tolua_Runtime_SoundSystem_PreLoadSoundEffectQueue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSystem",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"std::set<int>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSystem* self = (SoundSystem*)  tolua_tousertype(tolua_S,1,0);
  std::set<int>* soundEffectVec = ((std::set<int>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PreLoadSoundEffectQueue'", NULL);
#endif
  {
   self->PreLoadSoundEffectQueue(*soundEffectVec);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PreLoadSoundEffectQueue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UnLoadSoundEffectQueue of class  SoundSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem_UnLoadSoundEffectQueue00
static int tolua_Runtime_SoundSystem_UnLoadSoundEffectQueue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSystem* self = (SoundSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UnLoadSoundEffectQueue'", NULL);
#endif
  {
   self->UnLoadSoundEffectQueue();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UnLoadSoundEffectQueue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBackgroundMusicVolume of class  SoundSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem_SetBackgroundMusicVolume00
static int tolua_Runtime_SoundSystem_SetBackgroundMusicVolume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSystem* self = (SoundSystem*)  tolua_tousertype(tolua_S,1,0);
  float volume = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBackgroundMusicVolume'", NULL);
#endif
  {
   self->SetBackgroundMusicVolume(volume);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBackgroundMusicVolume'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBackgroundMusicVolume of class  SoundSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem_GetBackgroundMusicVolume00
static int tolua_Runtime_SoundSystem_GetBackgroundMusicVolume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSystem* self = (SoundSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBackgroundMusicVolume'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetBackgroundMusicVolume();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBackgroundMusicVolume'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Init of class  SoundSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem_Init00
static int tolua_Runtime_SoundSystem_Init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSystem* self = (SoundSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Tick of class  SoundSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem_Tick00
static int tolua_Runtime_SoundSystem_Tick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSystem* self = (SoundSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Destroy of class  SoundSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem_Destroy00
static int tolua_Runtime_SoundSystem_Destroy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSystem* self = (SoundSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: OnPauseEventHandler of class  SoundSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem_OnPauseEventHandler00
static int tolua_Runtime_SoundSystem_OnPauseEventHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSystem* self = (SoundSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnPauseEventHandler'", NULL);
#endif
  {
   self->OnPauseEventHandler();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnPauseEventHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnResumeEventHandler of class  SoundSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem_OnResumeEventHandler00
static int tolua_Runtime_SoundSystem_OnResumeEventHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSystem* self = (SoundSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnResumeEventHandler'", NULL);
#endif
  {
   self->OnResumeEventHandler();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnResumeEventHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnEnterBackgroundEventHandler of class  SoundSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem_OnEnterBackgroundEventHandler00
static int tolua_Runtime_SoundSystem_OnEnterBackgroundEventHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSystem* self = (SoundSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnEnterBackgroundEventHandler'", NULL);
#endif
  {
   self->OnEnterBackgroundEventHandler();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnEnterBackgroundEventHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnEnterForegroundEventHandler of class  SoundSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem_OnEnterForegroundEventHandler00
static int tolua_Runtime_SoundSystem_OnEnterForegroundEventHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSystem* self = (SoundSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnEnterForegroundEventHandler'", NULL);
#endif
  {
   self->OnEnterForegroundEventHandler();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnEnterForegroundEventHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: On_SoundEvent_Handle_Play of class  SoundSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem_On_SoundEvent_Handle_Play00
static int tolua_Runtime_SoundSystem_On_SoundEvent_Handle_Play00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SoundSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"std::list<std::string>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int iEventType = ((int)  tolua_tonumber(tolua_S,2,0));
  std::string owerData = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  std::list<std::string>* paramList = ((std::list<std::string>*)  tolua_tousertype(tolua_S,4,0));
  {
   SoundSystem::On_SoundEvent_Handle_Play(iEventType,owerData,*paramList);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'On_SoundEvent_Handle_Play'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: On_SoundEvent_Handle_Stop of class  SoundSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem_On_SoundEvent_Handle_Stop00
static int tolua_Runtime_SoundSystem_On_SoundEvent_Handle_Stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SoundSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"std::list<std::string>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int iEventType = ((int)  tolua_tonumber(tolua_S,2,0));
  std::string owerData = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  std::list<std::string>* paramList = ((std::list<std::string>*)  tolua_tousertype(tolua_S,4,0));
  {
   SoundSystem::On_SoundEvent_Handle_Stop(iEventType,owerData,*paramList);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'On_SoundEvent_Handle_Stop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLuaInstance of class  SoundSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_SoundSystem_GetLuaInstance00
static int tolua_Runtime_SoundSystem_GetLuaInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSystem* self = (SoundSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLuaInstance'", NULL);
#endif
  {
   SoundSystem* tolua_ret = (SoundSystem*)  self->GetLuaInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SoundSystem");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLuaInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLastTickTime of class  TimeSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_TimeSystem_GetLastTickTime00
static int tolua_Runtime_TimeSystem_GetLastTickTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TimeSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TimeSystem* self = (TimeSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLastTickTime'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetLastTickTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLastTickTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCurrentMicroSecond of class  TimeSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_TimeSystem_GetCurrentMicroSecond00
static int tolua_Runtime_TimeSystem_GetCurrentMicroSecond00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TimeSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   long long tolua_ret = (long long)  TimeSystem::GetCurrentMicroSecond();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCurrentMicroSecond'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCurrentSecond of class  TimeSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_TimeSystem_GetCurrentSecond00
static int tolua_Runtime_TimeSystem_GetCurrentSecond00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TimeSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   long long tolua_ret = (long long)  TimeSystem::GetCurrentSecond();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCurrentSecond'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetIntervalDay of class  TimeSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_TimeSystem_GetIntervalDay00
static int tolua_Runtime_TimeSystem_GetIntervalDay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TimeSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  long long start = ((long long)  tolua_tonumber(tolua_S,2,0));
  long long end = ((long long)  tolua_tonumber(tolua_S,3,0));
  {
   int tolua_ret = (int)  TimeSystem::GetIntervalDay(start,end);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetIntervalDay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNowDateBySecond of class  TimeSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_TimeSystem_GetNowDateBySecond00
static int tolua_Runtime_TimeSystem_GetNowDateBySecond00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TimeSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  long long sec = ((long long)  tolua_tonumber(tolua_S,2,0));
  {
   struct tm tolua_ret = (struct tm)  TimeSystem::GetNowDateBySecond(sec);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((tm)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"tm");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(tm));
     tolua_pushusertype(tolua_S,tolua_obj,"tm");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNowDateBySecond'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetStandBJDateBySecond of class  TimeSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_TimeSystem_GetStandBJDateBySecond00
static int tolua_Runtime_TimeSystem_GetStandBJDateBySecond00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TimeSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  long long sec = ((long long)  tolua_tonumber(tolua_S,2,0));
  {
   struct tm tolua_ret = (struct tm)  TimeSystem::GetStandBJDateBySecond(sec);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((tm)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"tm");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(tm));
     tolua_pushusertype(tolua_S,tolua_obj,"tm");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStandBJDateBySecond'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNowSecondByDate of class  TimeSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_TimeSystem_GetNowSecondByDate00
static int tolua_Runtime_TimeSystem_GetNowSecondByDate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TimeSystem",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"tm",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  tm time = *((tm*)  tolua_tousertype(tolua_S,2,0));
  {
   long long tolua_ret = (long long)  TimeSystem::GetNowSecondByDate(time);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNowSecondByDate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDateZeroTime of class  TimeSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_TimeSystem_GetDateZeroTime00
static int tolua_Runtime_TimeSystem_GetDateZeroTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TimeSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  long long sec = ((long long)  tolua_tonumber(tolua_S,2,0));
  {
   long long tolua_ret = (long long)  TimeSystem::GetDateZeroTime(sec);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDateZeroTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLuaInstance of class  TimeSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_TimeSystem_GetLuaInstance00
static int tolua_Runtime_TimeSystem_GetLuaInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TimeSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TimeSystem* self = (TimeSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLuaInstance'", NULL);
#endif
  {
   TimeSystem* tolua_ret = (TimeSystem*)  self->GetLuaInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TimeSystem");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLuaInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mFileType of class  _VARIBLE_ */
#ifndef TOLUA_DISABLE_tolua_get_VariableSystem___VARIBLE__mFileType
static int tolua_get_VariableSystem___VARIBLE__mFileType(lua_State* tolua_S)
{
  VariableSystem::_VARIBLE_* self = (VariableSystem::_VARIBLE_*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mFileType'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->mFileType);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mFileType of class  _VARIBLE_ */
#ifndef TOLUA_DISABLE_tolua_set_VariableSystem___VARIBLE__mFileType
static int tolua_set_VariableSystem___VARIBLE__mFileType(lua_State* tolua_S)
{
  VariableSystem::_VARIBLE_* self = (VariableSystem::_VARIBLE_*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mFileType'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mFileType = ((VariableSystem::ConfigType) (int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mSection of class  _VARIBLE_ */
#ifndef TOLUA_DISABLE_tolua_get_VariableSystem___VARIBLE__mSection
static int tolua_get_VariableSystem___VARIBLE__mSection(lua_State* tolua_S)
{
  VariableSystem::_VARIBLE_* self = (VariableSystem::_VARIBLE_*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mSection'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->mSection);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mSection of class  _VARIBLE_ */
#ifndef TOLUA_DISABLE_tolua_set_VariableSystem___VARIBLE__mSection
static int tolua_set_VariableSystem___VARIBLE__mSection(lua_State* tolua_S)
{
  VariableSystem::_VARIBLE_* self = (VariableSystem::_VARIBLE_*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mSection'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->mSection,(const char*)tolua_tostring(tolua_S,2,0),256-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mKey of class  _VARIBLE_ */
#ifndef TOLUA_DISABLE_tolua_get_VariableSystem___VARIBLE__mKey
static int tolua_get_VariableSystem___VARIBLE__mKey(lua_State* tolua_S)
{
  VariableSystem::_VARIBLE_* self = (VariableSystem::_VARIBLE_*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mKey'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->mKey);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mKey of class  _VARIBLE_ */
#ifndef TOLUA_DISABLE_tolua_set_VariableSystem___VARIBLE__mKey
static int tolua_set_VariableSystem___VARIBLE__mKey(lua_State* tolua_S)
{
  VariableSystem::_VARIBLE_* self = (VariableSystem::_VARIBLE_*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mKey'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->mKey,(const char*)tolua_tostring(tolua_S,2,0),256-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mValue of class  _VARIBLE_ */
#ifndef TOLUA_DISABLE_tolua_get_VariableSystem___VARIBLE__mValue
static int tolua_get_VariableSystem___VARIBLE__mValue(lua_State* tolua_S)
{
  VariableSystem::_VARIBLE_* self = (VariableSystem::_VARIBLE_*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mValue'",NULL);
#endif
  tolua_pushstring(tolua_S,(const char*)self->mValue);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mValue of class  _VARIBLE_ */
#ifndef TOLUA_DISABLE_tolua_set_VariableSystem___VARIBLE__mValue
static int tolua_set_VariableSystem___VARIBLE__mValue(lua_State* tolua_S)
{
  VariableSystem::_VARIBLE_* self = (VariableSystem::_VARIBLE_*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mValue'",NULL);
  if (!tolua_istable(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
 strncpy((char*)
self->mValue,(const char*)tolua_tostring(tolua_S,2,0),256-1);
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  _VARIBLE_ */
#ifndef TOLUA_DISABLE_tolua_Runtime_VariableSystem__VARIBLE__new00
static int tolua_Runtime_VariableSystem__VARIBLE__new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"VariableSystem::_VARIBLE_",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   VariableSystem::_VARIBLE_* tolua_ret = (VariableSystem::_VARIBLE_*)  Mtolua_new((VariableSystem::_VARIBLE_)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"VariableSystem::_VARIBLE_");
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

/* method: new_local of class  _VARIBLE_ */
#ifndef TOLUA_DISABLE_tolua_Runtime_VariableSystem__VARIBLE__new00_local
static int tolua_Runtime_VariableSystem__VARIBLE__new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"VariableSystem::_VARIBLE_",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   VariableSystem::_VARIBLE_* tolua_ret = (VariableSystem::_VARIBLE_*)  Mtolua_new((VariableSystem::_VARIBLE_)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"VariableSystem::_VARIBLE_");
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

/* method: new of class  VariableSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_VariableSystem_new00
static int tolua_Runtime_VariableSystem_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"VariableSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   VariableSystem* tolua_ret = (VariableSystem*)  Mtolua_new((VariableSystem)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"VariableSystem");
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

/* method: new_local of class  VariableSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_VariableSystem_new00_local
static int tolua_Runtime_VariableSystem_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"VariableSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   VariableSystem* tolua_ret = (VariableSystem*)  Mtolua_new((VariableSystem)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"VariableSystem");
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

/* method: delete of class  VariableSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_VariableSystem_delete00
static int tolua_Runtime_VariableSystem_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariableSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariableSystem* self = (VariableSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetConfigName of class  VariableSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_VariableSystem_GetConfigName00
static int tolua_Runtime_VariableSystem_GetConfigName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariableSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariableSystem* self = (VariableSystem*)  tolua_tousertype(tolua_S,1,0);
  VariableSystem::ConfigType FileType = ((VariableSystem::ConfigType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetConfigName'", NULL);
#endif
  {
   char* tolua_ret = (char*)  self->GetConfigName(FileType);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetConfigName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoadConfigByType of class  VariableSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_VariableSystem_LoadConfigByType00
static int tolua_Runtime_VariableSystem_LoadConfigByType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariableSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariableSystem* self = (VariableSystem*)  tolua_tousertype(tolua_S,1,0);
  VariableSystem::ConfigType FileType = ((VariableSystem::ConfigType) (int)  tolua_tonumber(tolua_S,2,0));
  char* pFileName = ((char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoadConfigByType'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->LoadConfigByType(FileType,pFileName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadConfigByType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UnLoadConfigByType of class  VariableSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_VariableSystem_UnLoadConfigByType00
static int tolua_Runtime_VariableSystem_UnLoadConfigByType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariableSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariableSystem* self = (VariableSystem*)  tolua_tousertype(tolua_S,1,0);
  VariableSystem::ConfigType FileType = ((VariableSystem::ConfigType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UnLoadConfigByType'", NULL);
#endif
  {
   self->UnLoadConfigByType(FileType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UnLoadConfigByType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVariable of class  VariableSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_VariableSystem_GetVariable00
static int tolua_Runtime_VariableSystem_GetVariable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariableSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariableSystem* self = (VariableSystem*)  tolua_tousertype(tolua_S,1,0);
  VariableSystem::ConfigType FileType = ((VariableSystem::ConfigType) (int)  tolua_tonumber(tolua_S,2,0));
  char* pSection = ((char*)  tolua_tostring(tolua_S,3,0));
  char* pKey = ((char*)  tolua_tostring(tolua_S,4,0));
  bool bValue = ((bool)  tolua_toboolean(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVariable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetVariable(FileType,pSection,pKey,bValue);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushboolean(tolua_S,(bool)bValue);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetVariable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVariable of class  VariableSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_VariableSystem_GetVariable01
static int tolua_Runtime_VariableSystem_GetVariable01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariableSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  VariableSystem* self = (VariableSystem*)  tolua_tousertype(tolua_S,1,0);
  VariableSystem::ConfigType FileType = ((VariableSystem::ConfigType) (int)  tolua_tonumber(tolua_S,2,0));
  char* pSection = ((char*)  tolua_tostring(tolua_S,3,0));
  char* pKey = ((char*)  tolua_tostring(tolua_S,4,0));
  int iValue = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVariable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetVariable(FileType,pSection,pKey,iValue);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushnumber(tolua_S,(lua_Number)iValue);
  }
 }
 return 2;
tolua_lerror:
 return tolua_Runtime_VariableSystem_GetVariable00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVariable of class  VariableSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_VariableSystem_GetVariable02
static int tolua_Runtime_VariableSystem_GetVariable02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariableSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  VariableSystem* self = (VariableSystem*)  tolua_tousertype(tolua_S,1,0);
  VariableSystem::ConfigType FileType = ((VariableSystem::ConfigType) (int)  tolua_tonumber(tolua_S,2,0));
  char* pSection = ((char*)  tolua_tostring(tolua_S,3,0));
  char* pKey = ((char*)  tolua_tostring(tolua_S,4,0));
  long long iValue = ((long long)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVariable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetVariable(FileType,pSection,pKey,iValue);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushnumber(tolua_S,(lua_Number)iValue);
  }
 }
 return 2;
tolua_lerror:
 return tolua_Runtime_VariableSystem_GetVariable01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVariable of class  VariableSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_VariableSystem_GetVariable03
static int tolua_Runtime_VariableSystem_GetVariable03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariableSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  VariableSystem* self = (VariableSystem*)  tolua_tousertype(tolua_S,1,0);
  VariableSystem::ConfigType FileType = ((VariableSystem::ConfigType) (int)  tolua_tonumber(tolua_S,2,0));
  char* pSection = ((char*)  tolua_tostring(tolua_S,3,0));
  char* pKey = ((char*)  tolua_tostring(tolua_S,4,0));
  float fValue = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVariable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetVariable(FileType,pSection,pKey,fValue);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushnumber(tolua_S,(lua_Number)fValue);
  }
 }
 return 2;
tolua_lerror:
 return tolua_Runtime_VariableSystem_GetVariable02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVariable of class  VariableSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_VariableSystem_GetVariable04
static int tolua_Runtime_VariableSystem_GetVariable04(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariableSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  VariableSystem* self = (VariableSystem*)  tolua_tousertype(tolua_S,1,0);
  VariableSystem::ConfigType FileType = ((VariableSystem::ConfigType) (int)  tolua_tonumber(tolua_S,2,0));
  char* pSection = ((char*)  tolua_tostring(tolua_S,3,0));
  char* pKey = ((char*)  tolua_tostring(tolua_S,4,0));
  char value = ((char)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVariable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetVariable(FileType,pSection,pKey,value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushnumber(tolua_S,(lua_Number)value);
  }
 }
 return 2;
tolua_lerror:
 return tolua_Runtime_VariableSystem_GetVariable03(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVariable of class  VariableSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_VariableSystem_GetVariable05
static int tolua_Runtime_VariableSystem_GetVariable05(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariableSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  VariableSystem* self = (VariableSystem*)  tolua_tousertype(tolua_S,1,0);
  VariableSystem::ConfigType FileType = ((VariableSystem::ConfigType) (int)  tolua_tonumber(tolua_S,2,0));
  char* pSection = ((char*)  tolua_tostring(tolua_S,3,0));
  char* pKey = ((char*)  tolua_tostring(tolua_S,4,0));
  char* pValue = ((char*)  tolua_tostring(tolua_S,5,0));
  unsigned int iValueLen = ((unsigned int)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVariable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetVariable(FileType,pSection,pKey,pValue,iValueLen);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Runtime_VariableSystem_GetVariable04(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVariable of class  VariableSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_VariableSystem_SetVariable00
static int tolua_Runtime_VariableSystem_SetVariable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariableSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariableSystem* self = (VariableSystem*)  tolua_tousertype(tolua_S,1,0);
  VariableSystem::ConfigType FileType = ((VariableSystem::ConfigType) (int)  tolua_tonumber(tolua_S,2,0));
  char* pSection = ((char*)  tolua_tostring(tolua_S,3,0));
  char* pKey = ((char*)  tolua_tostring(tolua_S,4,0));
  bool bValue = ((bool)  tolua_toboolean(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVariable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetVariable(FileType,pSection,pKey,bValue);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetVariable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVariable of class  VariableSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_VariableSystem_SetVariable01
static int tolua_Runtime_VariableSystem_SetVariable01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariableSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  VariableSystem* self = (VariableSystem*)  tolua_tousertype(tolua_S,1,0);
  VariableSystem::ConfigType FileType = ((VariableSystem::ConfigType) (int)  tolua_tonumber(tolua_S,2,0));
  char* pSection = ((char*)  tolua_tostring(tolua_S,3,0));
  char* pKey = ((char*)  tolua_tostring(tolua_S,4,0));
  int iValue = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVariable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetVariable(FileType,pSection,pKey,iValue);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Runtime_VariableSystem_SetVariable00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVariable of class  VariableSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_VariableSystem_SetVariable02
static int tolua_Runtime_VariableSystem_SetVariable02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariableSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  VariableSystem* self = (VariableSystem*)  tolua_tousertype(tolua_S,1,0);
  VariableSystem::ConfigType FileType = ((VariableSystem::ConfigType) (int)  tolua_tonumber(tolua_S,2,0));
  char* pSection = ((char*)  tolua_tostring(tolua_S,3,0));
  char* pKey = ((char*)  tolua_tostring(tolua_S,4,0));
  long long iValue = ((long long)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVariable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetVariable(FileType,pSection,pKey,iValue);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Runtime_VariableSystem_SetVariable01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVariable of class  VariableSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_VariableSystem_SetVariable03
static int tolua_Runtime_VariableSystem_SetVariable03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariableSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  VariableSystem* self = (VariableSystem*)  tolua_tousertype(tolua_S,1,0);
  VariableSystem::ConfigType FileType = ((VariableSystem::ConfigType) (int)  tolua_tonumber(tolua_S,2,0));
  char* pSection = ((char*)  tolua_tostring(tolua_S,3,0));
  char* pKey = ((char*)  tolua_tostring(tolua_S,4,0));
  float fValue = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVariable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetVariable(FileType,pSection,pKey,fValue);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Runtime_VariableSystem_SetVariable02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVariable of class  VariableSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_VariableSystem_SetVariable04
static int tolua_Runtime_VariableSystem_SetVariable04(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariableSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  VariableSystem* self = (VariableSystem*)  tolua_tousertype(tolua_S,1,0);
  VariableSystem::ConfigType FileType = ((VariableSystem::ConfigType) (int)  tolua_tonumber(tolua_S,2,0));
  char* pSection = ((char*)  tolua_tostring(tolua_S,3,0));
  char* pKey = ((char*)  tolua_tostring(tolua_S,4,0));
  char value = ((char)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVariable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetVariable(FileType,pSection,pKey,value);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Runtime_VariableSystem_SetVariable03(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVariable of class  VariableSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_VariableSystem_SetVariable05
static int tolua_Runtime_VariableSystem_SetVariable05(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariableSystem",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  VariableSystem* self = (VariableSystem*)  tolua_tousertype(tolua_S,1,0);
  VariableSystem::ConfigType FileType = ((VariableSystem::ConfigType) (int)  tolua_tonumber(tolua_S,2,0));
  char* pSection = ((char*)  tolua_tostring(tolua_S,3,0));
  char* pKey = ((char*)  tolua_tostring(tolua_S,4,0));
  char* pValue = ((char*)  tolua_tostring(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVariable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetVariable(FileType,pSection,pKey,pValue);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Runtime_VariableSystem_SetVariable04(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Init of class  VariableSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_VariableSystem_Init00
static int tolua_Runtime_VariableSystem_Init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariableSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariableSystem* self = (VariableSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Tick of class  VariableSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_VariableSystem_Tick00
static int tolua_Runtime_VariableSystem_Tick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariableSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariableSystem* self = (VariableSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Destroy of class  VariableSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_VariableSystem_Destroy00
static int tolua_Runtime_VariableSystem_Destroy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariableSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariableSystem* self = (VariableSystem*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetLuaInstance of class  VariableSystem */
#ifndef TOLUA_DISABLE_tolua_Runtime_VariableSystem_GetLuaInstance00
static int tolua_Runtime_VariableSystem_GetLuaInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariableSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariableSystem* self = (VariableSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLuaInstance'", NULL);
#endif
  {
   VariableSystem* tolua_ret = (VariableSystem*)  self->GetLuaInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"VariableSystem");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLuaInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_Runtime_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"DebugerSystem","DebugerSystem","cobra_win::Singleton2<DebugerSystem>",NULL);
  tolua_beginmodule(tolua_S,"DebugerSystem");
   tolua_variable(tolua_S,"m_pNetDebuger",tolua_get_DebugerSystem_m_pNetDebuger_ptr,tolua_set_DebugerSystem_m_pNetDebuger_ptr);
   tolua_variable(tolua_S,"m_pLogicDebuger",tolua_get_DebugerSystem_m_pLogicDebuger_ptr,tolua_set_DebugerSystem_m_pLogicDebuger_ptr);
   tolua_variable(tolua_S,"m_pRenderDebuger",tolua_get_DebugerSystem_m_pRenderDebuger_ptr,tolua_set_DebugerSystem_m_pRenderDebuger_ptr);
   tolua_function(tolua_S,"GetLuaInstance",tolua_Runtime_DebugerSystem_GetLuaInstance00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"EngineSystem","EngineSystem","cobra_win::Singleton2<EngineSystem>",tolua_collect_EngineSystem);
  #else
  tolua_cclass(tolua_S,"EngineSystem","EngineSystem","cobra_win::Singleton2<EngineSystem>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"EngineSystem");
   tolua_function(tolua_S,"new",tolua_Runtime_EngineSystem_new00);
   tolua_function(tolua_S,"new_local",tolua_Runtime_EngineSystem_new00_local);
   tolua_function(tolua_S,".call",tolua_Runtime_EngineSystem_new00_local);
   tolua_function(tolua_S,"delete",tolua_Runtime_EngineSystem_delete00);
   tolua_function(tolua_S,"GetOS",tolua_Runtime_EngineSystem_GetOS00);
   tolua_function(tolua_S,"GetDocumentDir",tolua_Runtime_EngineSystem_GetDocumentDir00);
   tolua_function(tolua_S,"CreateDocumentSubDir",tolua_Runtime_EngineSystem_CreateDocumentSubDir00);
   tolua_function(tolua_S,"DeleteDocumentSubDir",tolua_Runtime_EngineSystem_DeleteDocumentSubDir00);
   tolua_function(tolua_S,"GetAppFilePath",tolua_Runtime_EngineSystem_GetAppFilePath00);
   tolua_function(tolua_S,"GetRecordDataPath",tolua_Runtime_EngineSystem_GetRecordDataPath00);
   tolua_function(tolua_S,"GetDeviceType",tolua_Runtime_EngineSystem_GetDeviceType00);
   tolua_function(tolua_S,"IsIPad1",tolua_Runtime_EngineSystem_IsIPad100);
   tolua_function(tolua_S,"IsIPhone5",tolua_Runtime_EngineSystem_IsIPhone500);
   tolua_function(tolua_S,"IsShowOffers",tolua_Runtime_EngineSystem_IsShowOffers00);
   tolua_function(tolua_S,"IsAndroid_1136_640",tolua_Runtime_EngineSystem_IsAndroid_1136_64000);
   tolua_function(tolua_S,"IsAndroid_3_2",tolua_Runtime_EngineSystem_IsAndroid_3_200);
   tolua_function(tolua_S,"IsAndroid_4_3",tolua_Runtime_EngineSystem_IsAndroid_4_300);
   tolua_function(tolua_S,"IsAndroid_15_9",tolua_Runtime_EngineSystem_IsAndroid_15_900);
   tolua_function(tolua_S,"IsAndroid_16_9",tolua_Runtime_EngineSystem_IsAndroid_16_900);
   tolua_function(tolua_S,"IsAndroid_16_10",tolua_Runtime_EngineSystem_IsAndroid_16_1000);
   tolua_function(tolua_S,"IsAndroid_1024_600",tolua_Runtime_EngineSystem_IsAndroid_1024_60000);
   tolua_function(tolua_S,"IsAndroid_1184_720",tolua_Runtime_EngineSystem_IsAndroid_1184_72000);
   tolua_function(tolua_S,"IsAndroid_1196_720",tolua_Runtime_EngineSystem_IsAndroid_1196_72000);
   tolua_function(tolua_S,"GetScene",tolua_Runtime_EngineSystem_GetScene00);
   tolua_function(tolua_S,"EnableMultiTouch",tolua_Runtime_EngineSystem_EnableMultiTouch00);
   tolua_function(tolua_S,"OpenURL",tolua_Runtime_EngineSystem_OpenURL00);
   tolua_function(tolua_S,"ScreenShot",tolua_Runtime_EngineSystem_ScreenShot00);
   tolua_function(tolua_S,"ShowFeedbackDialog",tolua_Runtime_EngineSystem_ShowFeedbackDialog00);
   tolua_function(tolua_S,"IsNetWorkAvailable",tolua_Runtime_EngineSystem_IsNetWorkAvailable00);
   tolua_function(tolua_S,"ShowAd",tolua_Runtime_EngineSystem_ShowAd00);
   tolua_function(tolua_S,"UpdateNewVersionDialog",tolua_Runtime_EngineSystem_UpdateNewVersionDialog00);
   tolua_function(tolua_S,"ForceClearAnimationCache",tolua_Runtime_EngineSystem_ForceClearAnimationCache00);
   tolua_function(tolua_S,"FreeMemory",tolua_Runtime_EngineSystem_FreeMemory00);
   tolua_function(tolua_S,"GetAnimtionByName",tolua_Runtime_EngineSystem_GetAnimtionByName00);
   tolua_function(tolua_S,"GetAnimationByID",tolua_Runtime_EngineSystem_GetAnimationByID00);
   tolua_function(tolua_S,"GetLayoutConfig",tolua_Runtime_EngineSystem_GetLayoutConfig00);
   tolua_function(tolua_S,"InitAppEnv",tolua_Runtime_EngineSystem_InitAppEnv00);
   tolua_function(tolua_S,"LoadAppFile",tolua_Runtime_EngineSystem_LoadAppFile00);
   tolua_function(tolua_S,"LoadTempFile",tolua_Runtime_EngineSystem_LoadTempFile00);
   tolua_function(tolua_S,"GetLuaInstance",tolua_Runtime_EngineSystem_GetLuaInstance00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"IAPSystem","IAPSystem","cocos2d::CCPaymentDelegate",tolua_collect_IAPSystem);
  #else
  tolua_cclass(tolua_S,"IAPSystem","IAPSystem","cocos2d::CCPaymentDelegate",NULL);
  #endif
  tolua_beginmodule(tolua_S,"IAPSystem");
   tolua_function(tolua_S,"new",tolua_Runtime_IAPSystem_new00);
   tolua_function(tolua_S,"new_local",tolua_Runtime_IAPSystem_new00_local);
   tolua_function(tolua_S,".call",tolua_Runtime_IAPSystem_new00_local);
   tolua_function(tolua_S,"delete",tolua_Runtime_IAPSystem_delete00);
   tolua_function(tolua_S,"IsAvailable",tolua_Runtime_IAPSystem_IsAvailable00);
   tolua_function(tolua_S,"IsHasIAPId",tolua_Runtime_IAPSystem_IsHasIAPId00);
   tolua_function(tolua_S,"InitPaymentEnv",tolua_Runtime_IAPSystem_InitPaymentEnv00);
   tolua_function(tolua_S,"BuyProductByType",tolua_Runtime_IAPSystem_BuyProductByType00);
   tolua_function(tolua_S,"BuyProductById",tolua_Runtime_IAPSystem_BuyProductById00);
   tolua_function(tolua_S,"SdkBuyProductById",tolua_Runtime_IAPSystem_SdkBuyProductById00);
   tolua_function(tolua_S,"RemoveIAPId",tolua_Runtime_IAPSystem_RemoveIAPId00);
   tolua_function(tolua_S,"EndPayment",tolua_Runtime_IAPSystem_EndPayment00);
   tolua_function(tolua_S,"VerifyIAPIdentifier",tolua_Runtime_IAPSystem_VerifyIAPIdentifier00);
   tolua_function(tolua_S,"onPayFailed",tolua_Runtime_IAPSystem_onPayFailed00);
   tolua_function(tolua_S,"onPaySuccess",tolua_Runtime_IAPSystem_onPaySuccess00);
   tolua_function(tolua_S,"onVerifySuccess",tolua_Runtime_IAPSystem_onVerifySuccess00);
   tolua_function(tolua_S,"onVerifyFailed",tolua_Runtime_IAPSystem_onVerifyFailed00);
   tolua_function(tolua_S,"onRestoreSuccess",tolua_Runtime_IAPSystem_onRestoreSuccess00);
   tolua_function(tolua_S,"insertPayment",tolua_Runtime_IAPSystem_insertPayment00);
   tolua_function(tolua_S,"GetLuaInstance",tolua_Runtime_IAPSystem_GetLuaInstance00);
   tolua_variable(tolua_S,"__cobra_win__Singleton2_IAPSystem___",tolua_get_IAPSystem___cobra_win__Singleton2_IAPSystem___,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"IDebuger","IDebuger","",NULL);
  tolua_beginmodule(tolua_S,"IDebuger");
   tolua_function(tolua_S,"GetDebugerType",tolua_Runtime_IDebuger_GetDebugerType00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"NetDebuger","NetDebuger","IDebuger",NULL);
  tolua_beginmodule(tolua_S,"NetDebuger");
   tolua_function(tolua_S,"setAccount_Auth_Begin",tolua_Runtime_NetDebuger_setAccount_Auth_Begin00);
   tolua_function(tolua_S,"setAccount_Auth_End",tolua_Runtime_NetDebuger_setAccount_Auth_End00);
   tolua_function(tolua_S,"setLogin_Begin",tolua_Runtime_NetDebuger_setLogin_Begin00);
   tolua_function(tolua_S,"setLogin_End",tolua_Runtime_NetDebuger_setLogin_End00);
   tolua_function(tolua_S,"setRole_Begin",tolua_Runtime_NetDebuger_setRole_Begin00);
   tolua_function(tolua_S,"setRole_End",tolua_Runtime_NetDebuger_setRole_End00);
   tolua_function(tolua_S,"ToServer_LoginDebugInfo",tolua_Runtime_NetDebuger_ToServer_LoginDebugInfo00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ProfSystem","ProfSystem","cobra_win::Singleton2<ProfSystem>",NULL);
  tolua_beginmodule(tolua_S,"ProfSystem");
   tolua_function(tolua_S,"Start",tolua_Runtime_ProfSystem_Start00);
   tolua_function(tolua_S,"End",tolua_Runtime_ProfSystem_End00);
   tolua_function(tolua_S,"GetLuaInstance",tolua_Runtime_ProfSystem_GetLuaInstance00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"SoundSystem","SoundSystem","cobra_win::Singleton2<SoundSystem>",tolua_collect_SoundSystem);
  #else
  tolua_cclass(tolua_S,"SoundSystem","SoundSystem","cobra_win::Singleton2<SoundSystem>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"SoundSystem");
   tolua_constant(tolua_S,"_TYPED_EFFECTSOUND_UNKOWN_",SoundSystem::_TYPED_EFFECTSOUND_UNKOWN_);
   tolua_constant(tolua_S,"_TYPED_EFFECTSOUND_COMMONBUTTON_",SoundSystem::_TYPED_EFFECTSOUND_COMMONBUTTON_);
   tolua_constant(tolua_S,"_TYPED_EFFECTSOUND_ITEM_",SoundSystem::_TYPED_EFFECTSOUND_ITEM_);
   tolua_constant(tolua_S,"_TYPED_EFFECTSOUND_EFFECT_",SoundSystem::_TYPED_EFFECTSOUND_EFFECT_);
   tolua_constant(tolua_S,"_TYPED_EFFECTSOUND_MONSTER_",SoundSystem::_TYPED_EFFECTSOUND_MONSTER_);
   tolua_constant(tolua_S,"_TYPED_EFFECTSOUND_OTHER_",SoundSystem::_TYPED_EFFECTSOUND_OTHER_);
   tolua_constant(tolua_S,"_TYPED_EFFECTSOUND_NUMBER_",SoundSystem::_TYPED_EFFECTSOUND_NUMBER_);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"_EFFECT_INFO_","SoundSystem::_EFFECT_INFO_","",tolua_collect_SoundSystem___EFFECT_INFO_);
   #else
   tolua_cclass(tolua_S,"_EFFECT_INFO_","SoundSystem::_EFFECT_INFO_","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"_EFFECT_INFO_");
    tolua_variable(tolua_S,"mEffectType",tolua_get_SoundSystem___EFFECT_INFO__mEffectType,tolua_set_SoundSystem___EFFECT_INFO__mEffectType);
    tolua_variable(tolua_S,"mSoundName",tolua_get_SoundSystem___EFFECT_INFO__mSoundName,tolua_set_SoundSystem___EFFECT_INFO__mSoundName);
    tolua_variable(tolua_S,"mSoundId",tolua_get_SoundSystem___EFFECT_INFO__mSoundId,tolua_set_SoundSystem___EFFECT_INFO__mSoundId);
    tolua_variable(tolua_S,"mStartTime",tolua_get_SoundSystem___EFFECT_INFO__mStartTime,tolua_set_SoundSystem___EFFECT_INFO__mStartTime);
    tolua_variable(tolua_S,"mLoop",tolua_get_SoundSystem___EFFECT_INFO__mLoop,tolua_set_SoundSystem___EFFECT_INFO__mLoop);
    tolua_function(tolua_S,"new",tolua_Runtime_SoundSystem__EFFECT_INFO__new00);
    tolua_function(tolua_S,"new_local",tolua_Runtime_SoundSystem__EFFECT_INFO__new00_local);
    tolua_function(tolua_S,".call",tolua_Runtime_SoundSystem__EFFECT_INFO__new00_local);
   tolua_endmodule(tolua_S);
   tolua_function(tolua_S,"new",tolua_Runtime_SoundSystem_new00);
   tolua_function(tolua_S,"new_local",tolua_Runtime_SoundSystem_new00_local);
   tolua_function(tolua_S,".call",tolua_Runtime_SoundSystem_new00_local);
   tolua_function(tolua_S,"delete",tolua_Runtime_SoundSystem_delete00);
   tolua_function(tolua_S,"MuteBackgroundMusic",tolua_Runtime_SoundSystem_MuteBackgroundMusic00);
   tolua_function(tolua_S,"MuteEffectSound",tolua_Runtime_SoundSystem_MuteEffectSound00);
   tolua_function(tolua_S,"IsBackgroundMusicMute",tolua_Runtime_SoundSystem_IsBackgroundMusicMute00);
   tolua_function(tolua_S,"IsEffectSoundMute",tolua_Runtime_SoundSystem_IsEffectSoundMute00);
   tolua_function(tolua_S,"PlayEffect",tolua_Runtime_SoundSystem_PlayEffect00);
   tolua_function(tolua_S,"StopEffect",tolua_Runtime_SoundSystem_StopEffect00);
   tolua_function(tolua_S,"StopAllEffect",tolua_Runtime_SoundSystem_StopAllEffect00);
   tolua_function(tolua_S,"PlayBackgroundMusic",tolua_Runtime_SoundSystem_PlayBackgroundMusic00);
   tolua_function(tolua_S,"StopBackgroundMusic",tolua_Runtime_SoundSystem_StopBackgroundMusic00);
   tolua_function(tolua_S,"PreLoadSoundEffectQueue",tolua_Runtime_SoundSystem_PreLoadSoundEffectQueue00);
   tolua_function(tolua_S,"UnLoadSoundEffectQueue",tolua_Runtime_SoundSystem_UnLoadSoundEffectQueue00);
   tolua_function(tolua_S,"SetBackgroundMusicVolume",tolua_Runtime_SoundSystem_SetBackgroundMusicVolume00);
   tolua_function(tolua_S,"GetBackgroundMusicVolume",tolua_Runtime_SoundSystem_GetBackgroundMusicVolume00);
   tolua_function(tolua_S,"Init",tolua_Runtime_SoundSystem_Init00);
   tolua_function(tolua_S,"Tick",tolua_Runtime_SoundSystem_Tick00);
   tolua_function(tolua_S,"Destroy",tolua_Runtime_SoundSystem_Destroy00);
   tolua_function(tolua_S,"OnPauseEventHandler",tolua_Runtime_SoundSystem_OnPauseEventHandler00);
   tolua_function(tolua_S,"OnResumeEventHandler",tolua_Runtime_SoundSystem_OnResumeEventHandler00);
   tolua_function(tolua_S,"OnEnterBackgroundEventHandler",tolua_Runtime_SoundSystem_OnEnterBackgroundEventHandler00);
   tolua_function(tolua_S,"OnEnterForegroundEventHandler",tolua_Runtime_SoundSystem_OnEnterForegroundEventHandler00);
   tolua_function(tolua_S,"On_SoundEvent_Handle_Play",tolua_Runtime_SoundSystem_On_SoundEvent_Handle_Play00);
   tolua_function(tolua_S,"On_SoundEvent_Handle_Stop",tolua_Runtime_SoundSystem_On_SoundEvent_Handle_Stop00);
   tolua_function(tolua_S,"GetLuaInstance",tolua_Runtime_SoundSystem_GetLuaInstance00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"TimeSystem","TimeSystem","cobra_win::Singleton2<TimeSystem>",NULL);
  tolua_beginmodule(tolua_S,"TimeSystem");
   tolua_function(tolua_S,"GetLastTickTime",tolua_Runtime_TimeSystem_GetLastTickTime00);
   tolua_function(tolua_S,"GetCurrentMicroSecond",tolua_Runtime_TimeSystem_GetCurrentMicroSecond00);
   tolua_function(tolua_S,"GetCurrentSecond",tolua_Runtime_TimeSystem_GetCurrentSecond00);
   tolua_function(tolua_S,"GetIntervalDay",tolua_Runtime_TimeSystem_GetIntervalDay00);
   tolua_function(tolua_S,"GetNowDateBySecond",tolua_Runtime_TimeSystem_GetNowDateBySecond00);
   tolua_function(tolua_S,"GetStandBJDateBySecond",tolua_Runtime_TimeSystem_GetStandBJDateBySecond00);
   tolua_function(tolua_S,"GetNowSecondByDate",tolua_Runtime_TimeSystem_GetNowSecondByDate00);
   tolua_function(tolua_S,"GetDateZeroTime",tolua_Runtime_TimeSystem_GetDateZeroTime00);
   tolua_function(tolua_S,"GetLuaInstance",tolua_Runtime_TimeSystem_GetLuaInstance00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"VariableSystem","VariableSystem","cobra_win::Singleton2<VariableSystem>",tolua_collect_VariableSystem);
  #else
  tolua_cclass(tolua_S,"VariableSystem","VariableSystem","cobra_win::Singleton2<VariableSystem>",NULL);
  #endif
  tolua_beginmodule(tolua_S,"VariableSystem");
   tolua_constant(tolua_S,"_TYPED_CONFIG_UNKOWN_",VariableSystem::_TYPED_CONFIG_UNKOWN_);
   tolua_constant(tolua_S,"_TYPED_CONFIG_LOGGER_",VariableSystem::_TYPED_CONFIG_LOGGER_);
   tolua_constant(tolua_S,"_TYPED_CONFIG_SYSTEM_",VariableSystem::_TYPED_CONFIG_SYSTEM_);
   tolua_constant(tolua_S,"_TYPED_CONFIG_ACCOUNT_",VariableSystem::_TYPED_CONFIG_ACCOUNT_);
   tolua_constant(tolua_S,"_TYPED_CONFIG_MEM_",VariableSystem::_TYPED_CONFIG_MEM_);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"_VARIBLE_","VariableSystem::_VARIBLE_","",tolua_collect_VariableSystem___VARIBLE_);
   #else
   tolua_cclass(tolua_S,"_VARIBLE_","VariableSystem::_VARIBLE_","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"_VARIBLE_");
    tolua_variable(tolua_S,"mFileType",tolua_get_VariableSystem___VARIBLE__mFileType,tolua_set_VariableSystem___VARIBLE__mFileType);
    tolua_variable(tolua_S,"mSection",tolua_get_VariableSystem___VARIBLE__mSection,tolua_set_VariableSystem___VARIBLE__mSection);
    tolua_variable(tolua_S,"mKey",tolua_get_VariableSystem___VARIBLE__mKey,tolua_set_VariableSystem___VARIBLE__mKey);
    tolua_variable(tolua_S,"mValue",tolua_get_VariableSystem___VARIBLE__mValue,tolua_set_VariableSystem___VARIBLE__mValue);
    tolua_function(tolua_S,"new",tolua_Runtime_VariableSystem__VARIBLE__new00);
    tolua_function(tolua_S,"new_local",tolua_Runtime_VariableSystem__VARIBLE__new00_local);
    tolua_function(tolua_S,".call",tolua_Runtime_VariableSystem__VARIBLE__new00_local);
   tolua_endmodule(tolua_S);
   tolua_function(tolua_S,"new",tolua_Runtime_VariableSystem_new00);
   tolua_function(tolua_S,"new_local",tolua_Runtime_VariableSystem_new00_local);
   tolua_function(tolua_S,".call",tolua_Runtime_VariableSystem_new00_local);
   tolua_function(tolua_S,"delete",tolua_Runtime_VariableSystem_delete00);
   tolua_function(tolua_S,"GetConfigName",tolua_Runtime_VariableSystem_GetConfigName00);
   tolua_function(tolua_S,"LoadConfigByType",tolua_Runtime_VariableSystem_LoadConfigByType00);
   tolua_function(tolua_S,"UnLoadConfigByType",tolua_Runtime_VariableSystem_UnLoadConfigByType00);
   tolua_function(tolua_S,"GetVariable",tolua_Runtime_VariableSystem_GetVariable00);
   tolua_function(tolua_S,"GetVariable",tolua_Runtime_VariableSystem_GetVariable01);
   tolua_function(tolua_S,"GetVariable",tolua_Runtime_VariableSystem_GetVariable02);
   tolua_function(tolua_S,"GetVariable",tolua_Runtime_VariableSystem_GetVariable03);
   tolua_function(tolua_S,"GetVariable",tolua_Runtime_VariableSystem_GetVariable04);
   tolua_function(tolua_S,"GetVariable",tolua_Runtime_VariableSystem_GetVariable05);
   tolua_function(tolua_S,"SetVariable",tolua_Runtime_VariableSystem_SetVariable00);
   tolua_function(tolua_S,"SetVariable",tolua_Runtime_VariableSystem_SetVariable01);
   tolua_function(tolua_S,"SetVariable",tolua_Runtime_VariableSystem_SetVariable02);
   tolua_function(tolua_S,"SetVariable",tolua_Runtime_VariableSystem_SetVariable03);
   tolua_function(tolua_S,"SetVariable",tolua_Runtime_VariableSystem_SetVariable04);
   tolua_function(tolua_S,"SetVariable",tolua_Runtime_VariableSystem_SetVariable05);
   tolua_function(tolua_S,"Init",tolua_Runtime_VariableSystem_Init00);
   tolua_function(tolua_S,"Tick",tolua_Runtime_VariableSystem_Tick00);
   tolua_function(tolua_S,"Destroy",tolua_Runtime_VariableSystem_Destroy00);
   tolua_function(tolua_S,"GetLuaInstance",tolua_Runtime_VariableSystem_GetLuaInstance00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_Runtime (lua_State* tolua_S) {
 return tolua_Runtime_open(tolua_S);
};
#endif

