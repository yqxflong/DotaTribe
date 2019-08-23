#ifndef  _LC_COBRA_WIN_GUARD_H
#define  _LC_COBRA_WIN_GUARD_H


#include "NonCopyable.h"

namespace  cobra_win
{


template <typename TYPE>
class  Guard : public NonCopyable
{
private:
	TYPE&  m_lock;

public:
	Guard(TYPE& lock) : m_lock(lock)
	{
		m_lock.lock();
	}
	~Guard()
	{
		m_lock.unlock();
	}
};


}


#endif
