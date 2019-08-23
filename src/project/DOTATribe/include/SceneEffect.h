//Name: SceneEffect
//Func: Used to Create SceneEffect
//Written by: Johny

#ifndef __PUBLIC__SceneEffect__
#define __PUBLIC__SceneEffect__

#include <cocos2d.h>

class SceneEffect:public cocos2d::CCSprite{
public:
	SceneEffect();
	virtual ~SceneEffect(){};
	static SceneEffect* createWithEffectID(int effectID,float delay=0);
	bool initWithEffectID(int effectID,float delay);
	SceneEffect* clone();
protected:
private:
	int m_nEffectID;
	float m_fDelay;
	inline bool _setAction(int effectID,float delay);
public:
	void ReplayAction();
};

#endif