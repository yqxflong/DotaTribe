#ifndef  _DOTATRIBE_INPUTEVENT_H_
#define  _DOTATRIBE_INPUTEVENT_H_


/*
	输入相关的事件标示
*/
enum InputEventID
{
	_TYPED_INPUT_EVENT_UNKOWN_,          // 未知的输入事件标示
	_TYPED_INPUT_EVENT_TOUCHMOVE_,       // TOUCH移动的输入事件标示
	_TYPED_INPUT_EVENT_TOUCHBEGIN_,      // TOUCH按下的输入事件标示
	_TYPED_INPUT_EVENT_TOUCHEND_,        // TOUCH弹起的输入事件标示
	_TYPED_INPUT_EVENT_TOUCHCANCELED_,   // TOUCH取消的输入事件标示
	_TYPED_INPUT_EVENT_ACCELERATE_,      // 重力感应的输入事件标示
	_TYPED_INPUT_EVENT_KEY_BACK_CLICKED_,// 返回按键按下的输入事件标示
	_TYPED_INPUT_EVENT_KEY_MENU_CLICKED_,// 系统菜单按键按下的输入事件标示
	_TYPED_INPUT_EVENT_NUMBER_,
};

/*
	输入事件结构体
*/
class InputEvent
{
public:
	int    mEventID;   // 输入的事件ID
	float  mPreXPos;   // 事件发生前对应的X坐标
	float  mPreYPos;   // 事件发生前对应的Y坐标
	float  mXPos;      // 事件发生时对应的X坐标
	float  mYPos;      // 事件发生时对应的Y坐标
	float  mZPos;      // 事件发生时对应的Z坐标
	double mTimeStamp; // 重力响应发生时的时间戳
	bool   mProcessed; // 是否已经处理

public:
	InputEvent()
	{
		mEventID   = _TYPED_INPUT_EVENT_UNKOWN_;
		mPreXPos   = 0.0f;
		mPreYPos   = 0.0f;
		mXPos      = 0.0f;
		mYPos      = 0.0f;
		mZPos      = 0.0f;
		mTimeStamp = 0.0f;
		mProcessed = false;
	}
};


#endif
