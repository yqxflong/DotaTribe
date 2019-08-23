//CCMenuForExtension
//For Implement Check CCMenuItem Contained by Its Parent when one of them is CCScrollView
//Johny

#include <menu_nodes/CCMenu.h>
#include "CCScrollView/CCScrollView.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCMenuItem* CCMenu::itemForTouch(CCTouch *touch)
{
	CCPoint touchLocation = touch->getLocation();

	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCMenuItem* pChild = dynamic_cast<CCMenuItem*>(pObject);
			if (pChild && pChild->isVisible() && pChild->isEnabled())
			{
				if(!_checkContainedByParentIfScrollView(pChild,touchLocation))
					return NULL;
				//
				CCPoint local = pChild->convertToNodeSpace(touchLocation);
				CCRect r = pChild->rect();
				r.origin = CCPointZero;

				if (r.containsPoint(local))
				{
					return pChild;
				}
			}
		}
	}

	return NULL;
}

	/*
		检查是否在scrollview显示区域
		*将item以取父节点递归，如果有一个节点为CCScrollView，则检查，该触摸点是否在CCScrollView显示区域
	*/
bool CCMenu::_checkContainedByParentIfScrollView(CCNode* item,const CCPoint&touchPoint){
	CCNode* parent=item->getParent();
	if (!parent)
		return true;
	cocos2d::extension::CCScrollView* cc=dynamic_cast<cocos2d::extension::CCScrollView*>(parent);
	if (cc)
	{
		return cc->getViewRect().containsPoint(touchPoint);
	}else{
		return _checkContainedByParentIfScrollView(parent,touchPoint);
	}
}