#ifndef  _DOTATRIBE_DEBUGERSYSTEM_H_
#define  _DOTATRIBE_DEBUGERSYSTEM_H_


#include <include/common/Singleton.h>
using  namespace  cobra_win;

class IDebuger;
class NetDebuger;
class LogicDebuger;
class RenderDebuger;
class DebugerSystem : public cobra_win::Singleton2<DebugerSystem>
{
public:
	DebugerSystem();
	virtual ~DebugerSystem();

public:
	//@标配
	bool     Init();
	void     Tick();
	void     Destroy();

//@Lua
public:
	NetDebuger*    m_pNetDebuger;    // 网络信息调试器
	LogicDebuger*  m_pLogicDebuger;  // 逻辑信息调试器
	RenderDebuger* m_pRenderDebuger; // 渲染信息调试器

	DebugerSystem* GetLuaInstance(){
		return DebugerSystem::get_instance2();
	}
};

#define  DEBUGERSYSTEM  (DebugerSystem::get_instance2())


#endif
