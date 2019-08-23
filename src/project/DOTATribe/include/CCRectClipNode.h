#ifndef   _DOTATIRBE_CCRECTCLIPNODE_H_
#define   _DOTATIRBE_CCRECTCLIPNODE_H_

////////////////////////////////////////////////////////////////
//Name:	 CCRectClipNode
//Auchor: 	xiaobo.wu
//Func:	 矩形裁剪结点（用于可视裁剪）
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////

#include  <cocos2d.h>

class   CCRectClipNode: public cocos2d::CCNode
{
public:
	CCRectClipNode();
	virtual ~CCRectClipNode();
	virtual  bool init(cocos2d::CCRect drawRect);
	static  CCRectClipNode * create(cocos2d::CCRect drawRect);
    virtual void visit(void);
protected:
	cocos2d::CCRect  m_fDrawRect;
};


#endif