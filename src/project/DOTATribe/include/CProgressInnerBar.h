//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//  Type: fit for experience,life,energy...
//

#ifndef __PUBLIC__CPROGRESSINNERBAR__
#define __PUBLIC__CPROGRESSINNERBAR__

#include "cocos2d.h"


class CProgressInnerBar:public cocos2d::CCSprite{
private:
	float m_fPercent;
public:
	CProgressInnerBar(){
		m_fPercent=1.0f;
	};
	virtual ~CProgressInnerBar(){};
	static CProgressInnerBar* create(const char *pszFileName);
	bool init(const char *pszFileName);
	void setPercent(float percent){
		if(percent > 1.0f)
		{
			percent = 1.0f;
		}

		m_fPercent=percent;
	}
	float getPercent() const{
		return m_fPercent;
	}
protected:
	virtual void visit();
};


#endif 
