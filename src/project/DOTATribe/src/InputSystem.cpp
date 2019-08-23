#include <cocos2d.h>
#include "../include/InputSystem.h"
#include "../include/DOTATribeApp.h"
#include "../include/LoggerSystem.h"
#include "../include/IProcedure.h"


template<> InputSystem* cobra_win::Singleton2<InputSystem>::m_pMySelf = NULL;

InputSystem::InputSystem()
{
	m_TouchBeginPosition = cocos2d::CCPointMake(0, 0);
	m_InputEventQueue.clear();
}

InputSystem::~InputSystem()
{

}

cocos2d::CCPoint& InputSystem::GetTouchBeginPosition()
{
	return m_TouchBeginPosition;
}

std::list<InputEvent>& InputSystem::GetInputEventQueue()
{
	return m_InputEventQueue;
}

void InputSystem::AddInputEvent(InputEvent event)
{
	if (event.mEventID == _TYPED_INPUT_EVENT_TOUCHBEGIN_)
	{
		m_TouchBeginPosition = cocos2d::CCPointMake(event.mXPos, event.mYPos);
	}

	m_InputEventQueue.push_back(event);
}

bool  InputSystem::Init()
{
	m_InputEventQueue.clear();
	LOGGERSYSTEM->LogInfo("Init InputSystem Success\n");

	return true;
}

void  InputSystem::Tick()
{
	;
}

void  InputSystem::Destroy()
{
	m_InputEventQueue.clear();
	LOGGERSYSTEM->LogInfo("Destroy InputSystem Success\n");
}
