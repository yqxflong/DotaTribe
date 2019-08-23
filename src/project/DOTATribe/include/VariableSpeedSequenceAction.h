#ifndef  _DOTATRIBE_VARIABLESPEEDSPEQUENCEACTION_H_
#define  _DOTATRIBE_VARIABLESPEEDSPEQUENCEACTION_H_
/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  变速序列组合动画  (漏洞 不支持单一动画 必须多个动画组合)
//date:   2013/10/28
///////////////////////////////////////////////// 
#include  <cocos2d.h>
#include "base_nodes/CCNode.h"
#include "../cocos2dx/actions/CCAction.h"
#include <CCProtocols.h>
#include "sprite_nodes/CCSpriteFrame.h"
#include "sprite_nodes/CCAnimation.h"

using namespace cocos2d;

class  VariableSpeedSequenceAction : public cocos2d::CCActionInterval
{
public:
	~VariableSpeedSequenceAction(void);

	/** initializes the action */
	bool initWithTwoActions(CCFiniteTimeAction *pActionOne, CCFiniteTimeAction *pActionTwo);
	 
	virtual void startWithTarget(CCNode *pTarget);
	virtual void stop(void);
	virtual void update(float t);
	virtual CCActionInterval* reverse(void);
	virtual void step(float dt);
	virtual void setSpeedScale(float speedScale);
public:

	/** helper constructor to create an array of sequenceable actions */
	static VariableSpeedSequenceAction* create(CCFiniteTimeAction *pAction1, ...);
	/** helper constructor to create an array of sequenceable actions given an array */
	static VariableSpeedSequenceAction* create(CCArray *arrayOfActions);
	/** helper constructor to create an array of sequence-able actions */
	static VariableSpeedSequenceAction* createWithVariableList(CCFiniteTimeAction *pAction1, va_list args);
	/** creates the action */
	static VariableSpeedSequenceAction* createWithTwoActions(CCFiniteTimeAction *pActionOne, CCFiniteTimeAction *pActionTwo);

protected:
	CCFiniteTimeAction *m_pActions[2];
	float m_split;
	int m_last;
	float m_fSpeedScale;
};
 
#endif
