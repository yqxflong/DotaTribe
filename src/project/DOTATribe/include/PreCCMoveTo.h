#ifndef  _DOTATRIBE_PRECCMOVETO_H_
#define  _DOTATRIBE_PRECCMOVETO_H_

#include  <cocos2d.h>
////////////////////////////////////////////////////////////////
//Name:	 PreCCMoveTo
//Auchor: 	xiaobo.wu
//Func:	 优化后的CCMoveto
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////

using  namespace cocos2d;

class PreCCMoveTo: public cocos2d::CCActionInterval
{
public:
	/** initializes the action */
	bool initWithDuration(float duration, const CCPoint& position);

	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual void startWithTarget(CCNode *pTarget);
	virtual void update(float time);

public:
	/** creates the action */
	static PreCCMoveTo* create(float duration, const CCPoint& position);
protected:
	CCPoint m_endPosition;
	CCPoint m_startPosition;
	CCPoint m_delta;
};


class  PreCCMoveBy: public PreCCMoveTo
{
public:
	/** initializes the action */
	bool initWithDuration(float duration, const CCPoint& position);
	virtual void startWithTarget(CCNode *pTarget);
	virtual CCActionInterval* reverse(void);

public:
	/** creates the action */
	static PreCCMoveBy* create(float duration, const CCPoint& position);
};


#endif

