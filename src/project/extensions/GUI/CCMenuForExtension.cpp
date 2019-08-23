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
		����Ƿ���scrollview��ʾ����
		*��item��ȡ���ڵ�ݹ飬�����һ���ڵ�ΪCCScrollView�����飬�ô������Ƿ���CCScrollView��ʾ����
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