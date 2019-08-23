#include "../include/IDebuger.h"


IDebuger::IDebuger()
{
	m_DebugerType = _TYPED_DEBUGER_UNKOWN_;
}

IDebuger::~IDebuger()
{

}

int IDebuger::GetDebugerType()
{
	return m_DebugerType;
}
