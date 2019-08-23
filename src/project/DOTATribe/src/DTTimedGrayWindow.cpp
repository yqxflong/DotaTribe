//Name：DTTimedGrayWindow
//Function：倒计时隔绝层
//Written By：尹强

#include "../include/DTTimedGrayWindow.h"
#include "../include/EventTyper.h"
#include "../include/TimeSystem.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/CPublicVarReader.h"

using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

static float REST_TIME=1.0f;

DTTimedGrayWindow::DTTimedGrayWindow()
	:m_fTick(0.0f)
{
	m_WindowType   = _TYPED_WINDOW_DTTIMEDGRAYLAYER_;
	m_bModelWindow = true;
}

bool DTTimedGrayWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_DTTIMEDGRAYWINDOW_);

	return IWindow::Init();
}

bool DTTimedGrayWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;

		CPriorityLayerColor* cc=CPriorityLayerColor::create(ccc4(0,0,0,0),1136,768,kPRIORITY_FORBID_ALL_TOUCHES);
		cc->setPosition(CCPointZero);
		m_pRootNode->addChild(cc);

		return true;
	} 
	while (false);

	return false;
}

void DTTimedGrayWindow::Tick()
{
	IWindow::Tick();

	m_fTick+=TimeSystem::get_instance2()->GetLastTickTime();
	if (m_fTick>=REST_TIME){
		Destroy();
	}
}

void DTTimedGrayWindow::Destroy()
{
	IWindow::Destroy();
	m_fTick=0.0f;
}

void DTTimedGrayWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_DTTIMEDGRAYWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
}

void DTTimedGrayWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
	//倒计时归位
	m_fTick=0.0f;
}