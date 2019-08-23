//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//  Type: The layer can be set priority and AvoidSwallow
//
#ifndef  _DOTATRIBE_CPRIORITYLAYERCOLOR_H_
#define  _DOTATRIBE_CPRIORITYLAYERCOLOR_H_

#include "cocos2d.h"

class CPriorityLayerColor;
class CPriorityLayerColorDelegate{
public:
	virtual void touchEvent(CPriorityLayerColor* pLayerColor)=0;
};

class CPriorityLayerColor:public cocos2d::CCLayerColor{
private:
	int m_nID;
	int m_nPriority;
	CPriorityLayerColorDelegate* m_pDelegate;
	bool m_bIsCallBack;
public:
	CPriorityLayerColor(){
		m_nID=0;
		m_nPriority=0;
		m_pDelegate=0;
		m_bIsCallBack=false;
	};
	~CPriorityLayerColor(){
		m_pDelegate=0;
	};
	static CPriorityLayerColor* create(const cocos2d::ccColor4B& color, GLfloat width, GLfloat height,int priority=0);
	bool initWithColor(const cocos2d::ccColor4B& color, GLfloat width, GLfloat height,int priority);
	//
	void setDelegate(CPriorityLayerColorDelegate* del){
		m_pDelegate=del;
	}
	//
	void setIDX(int idx){
		m_nID=idx;
	}
	int getIDX()const{
		return m_nID;
	}

protected:
	virtual void registerWithTouchDispatcher();
	bool cContainsThePoint(cocos2d::CCTouch *pTouch);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
};
#endif