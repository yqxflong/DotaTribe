//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//  Type: The Corner Num
//

#ifndef  _DOTATRIBE_CCornerNumIcon_H_
#define  _DOTATRIBE_CCornerNumIcon_H_

#include <cocos2d.h>

class CCornerNumIcon:public cocos2d::CCSprite{
private:
	unsigned int m_nCount;		//当前的数量
	cocos2d::CCLabelTTF* m_pNum;
	std::string m_strFile1;
	std::string m_strFile2;
	std::string m_strFile3;
public:
	CCornerNumIcon();
	virtual ~CCornerNumIcon();
	static CCornerNumIcon* create(const char* file1,const char* file2,const char* file3);
	bool init(const char* file1,const char* file2,const char* file3);
	void setNum(unsigned int num);
	cocos2d::CCLabelTTF* getNumLabel(){
		return m_pNum;
	};
	void setShow(bool isshow);
private:
	inline void _setNumLabel();
	inline void _changeToFile1();
	inline void _changeToFile2();
	inline void _changeToFile3();
	inline void _resetNumLabelLocation();
};
#endif