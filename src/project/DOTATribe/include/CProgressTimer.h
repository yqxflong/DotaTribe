//Name：CProgressTimer
//Function：扩展的进度条
//Written By：lvyunlong

#ifndef  _DOTATRIBE_CPROGRESSTIMER_H_
#define  _DOTATRIBE_CPROGRESSTIMER_H_

#include <cocos2d.h>

class CProgressTimerDelegate{
public:
	virtual void CallBack_NextLevel()=0;
	virtual void CallBack_RunFinish()=0;
};

class  CProgressTimer:public cocos2d::CCProgressTimer
{
public:
	CProgressTimer()
	{
		m_Duration_ = 1;
		m_pDelegate = NULL;
	}
	virtual ~ CProgressTimer(){};
	static  CProgressTimer* create(const char *pszFileName,float time);
	bool init(const char *pszFileName,float time);
	void setRunSchedule(float posbegin,float posend,int times);
	void RunFinish();
	void NextLevel();
	void setDelegate(CProgressTimerDelegate *Delegate);
private:
	float m_Duration_;
	CProgressTimerDelegate *m_pDelegate;
};

#endif