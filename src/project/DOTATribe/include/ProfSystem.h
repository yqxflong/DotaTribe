#ifndef  _VIP3D_PROFSYSTEM_H_
#define  _VIP3D_PROFSYSTEM_H_


#include <include/common/Singleton.h>
#include <stack>
using  namespace  cobra_win;


/*
	开始统计
*/
#define  _BEGIN_PROF_CHUNK_(NAME) \
{ \
	PROFSYSTEM->Start(NAME); \
}

/*
	结束统计
*/
#define  _END_PROF_CHUNK_() \
{ \
	PROFSYSTEM->End(); \
}

class ProfSystem : public cobra_win::Singleton2<ProfSystem>
{
public:
	struct _PROF_INFO_
	{
		const char* mChunkName;
		long  long  mStartTime;
		_PROF_INFO_()
		{
			memset(this, 0, sizeof(_PROF_INFO_));
		}
	};

protected:
	std::stack<_PROF_INFO_> m_ProfList;// 统计信息堆栈

public:
	ProfSystem();
	virtual ~ProfSystem();

public:
	//@标配
	bool     Init();
	void     Tick();
	void     Destroy();

//@Lua
public:
	//@开始统计
	void     Start(const char* pChunkName);
	//@结束统计
	void     End();

	ProfSystem* GetLuaInstance(){
		return ProfSystem::get_instance2();
	}
};

#define  PROFSYSTEM  (ProfSystem::get_instance2())


#endif
