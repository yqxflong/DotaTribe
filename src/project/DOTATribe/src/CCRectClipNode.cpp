////////////////////////////////////////////////////////////////
//Name:	 CCRectClipNode
//Auchor: 	xiaobo.wu
//Func:	 矩形裁剪结点（用于可视裁剪）
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////
#include "../include/CCRectClipNode.h"
using namespace cocos2d;

CCRectClipNode::CCRectClipNode()
{
	m_fDrawRect=cocos2d::CCRectZero;
}


CCRectClipNode::~CCRectClipNode()
{

}

CCRectClipNode * CCRectClipNode::create(cocos2d::CCRect drawRect)
{
   CCRectClipNode * pRectClipNode=new CCRectClipNode();
   if(pRectClipNode&&pRectClipNode->init(drawRect))
   {
	   pRectClipNode->autorelease();
	   return pRectClipNode;
   }
   CC_SAFE_DELETE(pRectClipNode);
   return NULL;
}

void CCRectClipNode::visit(void)
{  if(!m_bVisible)
    return ;
	//kmGLPushMatrix();
	glEnable(GL_SCISSOR_TEST);
	CCEGLView::sharedOpenGLView()->setScissorInPoints(m_fDrawRect.origin.x,m_fDrawRect.origin.y,m_fDrawRect.size.width,m_fDrawRect.size.height);
	cocos2d::CCNode::visit(); //ergodic all children
	glDisable(GL_SCISSOR_TEST);
	//kmGLPopMatrix();
}
bool CCRectClipNode::init(cocos2d::CCRect drawRect)
{
   m_fDrawRect=drawRect;
   return CCNode::init();
}


