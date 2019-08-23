#ifndef  _COCOS_TOOLS_SINGLETOUCH_PROTORY_H_
#define  _COCOS_TOOLS_SINGLETOUCH_PROTORY_H_
/////////////////////////////////////////////////
//author:  xiaobo.wu
//description:  ÍÏ×§´¥ÃþËã·¨
//date:   2013/11/20
/////////////////////////////////////////////////  
#include  <cocos2d.h>


class  SingleTouchProtocol
{ 
public:
	SingleTouchProtocol(void);
	virtual ~SingleTouchProtocol();
	virtual  bool   checkRowRank(float touchYPos);
	virtual  bool   checkColumnRank(float touchXPos);
	virtual  bool	checkIsContainTouch(cocos2d::CCPoint &touchPos);
	virtual  void   setSingleTouchUniqueID(int singleTouchID);
	virtual  void   setExpendTouchSize(float touchExpendWidth,float touchExpendHeight=0.0f);
	virtual  cocos2d::CCSize  getExpendTouchSize();
	virtual  int    getSingleTouchUniqueID();
protected:
	float  m_fLeft;
	float  m_fRight;
	float  m_fTop;
	float  m_fBottom;
	float  m_fExpendTouchWidth;
	float  m_fExpendTouchHeight;
	int    m_nSingleTouchUniqueID;
};


#endif

