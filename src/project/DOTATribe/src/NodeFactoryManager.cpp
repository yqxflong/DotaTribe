//Name: NodeFactoryManager.h
//Func: Used to Manage NodeFactory
//Written by: Johny

#include "../include/NodeFactoryManager.h"
#include <cocos-ext.h>
//
#include "../include/NFCCNodeFactory.h"
#include "../include/NFCCLayerFactory.h"
#include "../include/NFCCLabelFactory.h"
#include "../include/NFCCSpriteFactory.h"
#include "../include/NFCCMenuFactory.h"
#include "../include/NFCCTableViewFactory.h"
#include "../include/NFCProgressInnerBarFactory.h"
#include "../include/NFCCEditBoxFactory.h"
#include "../include/NFUIPageViewFactory.h"
//
#include "../include/NFDTBoardFactory.h"


using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

static NodeFactoryManager* _instance=NULL;

NodeFactoryManager* NodeFactoryManager::instance(){
    if (!_instance) {
        _instance=new NodeFactoryManager;
        if(_instance&&_instance->_init())
            return _instance;
        else
            return NULL;
    }
    return _instance;
}

void NodeFactoryManager::OnDestroy(){
    if (_instance){
        _instance->_clearFacortyList();
        delete _instance;
        _instance=NULL;
    }
}

bool NodeFactoryManager::_init(){
    /*
     register factory
     */
//~~~~~~~Node~~~~~~~
    _registerNodeFactory("CCNode",new NFCCNodeFactory);
	_registerNodeFactory("MaskNode", new NFMaskNodeFactory);
	_registerNodeFactory("CCardsStarProgress", new NFStarLevelNodeFactory);
	_registerNodeFactory("HeroEquipBoard", new NFDTEquipBoardFactory);
	_registerNodeFactory("DTAwardBoard", new NFDTAwardBoardFactory);
	_registerNodeFactory("DTHeroIcon", new NFDTHeroIconFactory);
	_registerNodeFactory("GrapStarsProgress", new NFGrapStarsProgressFactory); 

//~~~~~~~Layer~~~~~~~
    _registerNodeFactory("CCLayer",new NFCCLayerFactory);
    _registerNodeFactory("CCLayerColor",new NFCCLayerColorFactory);
	_registerNodeFactory("CPriorityLayerColor",new NFCPriorityLayerColorFactory);
//~~~~~~~Label~~~~~~~
	_registerNodeFactory("CCLabelTTF",new NFCCLabelTTFFactory);
	_registerNodeFactory("CCLabelTTFMultiline",new NFCCLabelTTFMultilineFactory);
	_registerNodeFactory("CTimeLabel",new NFCCTimeLabelFactory);
//~~~~~~~Sprite~~~~~~~
	_registerNodeFactory("CSprite",new NFCSpriteFactory);
	_registerNodeFactory("CSpriteInSprite",new NFCSpriteInSpriteFactory);
	_registerNodeFactory("ScaleSprite", new NFScaleSpriteFactory);
	_registerNodeFactory("CCAnimationSprite",new NFCCAnimationSpriteFactory);
	_registerNodeFactory("CCSprite",new NFCCSpriteFactory);
	_registerNodeFactory("CCScale9Sprite",new NFCCScale9SpriteFactory);
	_registerNodeFactory("CTouchSprite",new NFCTouchSpriteFactory);
	_registerNodeFactory("SceneEffect",new NFSceneEffectFactory);
	_registerNodeFactory("CCornerNumIcon",new NFCCornerNumIconFactory);
	_registerNodeFactory("CTitleSprite",new NFCTitleSpriteFactory);
	_registerNodeFactory("CCGrapSprite",new NFCExtGrapSpriteFactory);
	_registerNodeFactory("CSkeletonAnimation",new NFCSkeletonAnimationFactory);
	_registerNodeFactory("CAnimationSprite",new NFCAnimationSpriteFactory);
	_registerNodeFactory("CCParticleSystemQuad",new NFCParticelNodeFactory);
	_registerNodeFactory("CSimpleActionSprite",new NFCCSimpleActionNodeFacrtory);
//==========PageView=========
	_registerNodeFactory("UIPageView",new NFUIPageViewFactory);

	  
	 
//~~~~~~~MenuItem~~~~~~~
	_registerNodeFactory("CLabelButton",new NFCLabelButtonFactory);
	_registerNodeFactory("CMenuItemSpriteSI",new NFCMenuItemSpriteSIFactory);
    _registerNodeFactory("CMenuItemSprite",new NFCMenuItemSpriteFactory);
	_registerNodeFactory("CMenuItemSpriteSelected",new NFCMenuItemSpriteSelectedFactory);
	_registerNodeFactory("CImMenuItemSpriteSI",new CImMenuItemSpriteSIFactory);
	_registerNodeFactory("CImMenuItemSprite",new CImMenuItemSpriteFactory);
	_registerNodeFactory("CImMenuItemSpriteSelected",new NFCImMenuItemSpriteSelectedFactory);
	_registerNodeFactory("CTabMenuItemSprite",new CTabMenuItemSpriteFactory);
	_registerNodeFactory("CTabImmovableMenuItemSpriteSelected",new NFCTabImmovableMenuItemSpriteSelectedFactory);
//~~~~~~~EditBox~~~~~~
	_registerNodeFactory("CCEditBox",new NFCCEditBoxFactory);
//~~~~~~~ProgressBar~~~~~~~
	_registerNodeFactory("CProgressInnerBar",new NFCProgressInnerBarFactory);
	_registerNodeFactory("CCProgressTimer",new NFCCProgressTimerFactory);
	_registerNodeFactory("CProgressTimer", new NFCProgressTimerFactory);
//~~~~~~~TableView~~~~~~~
	_registerNodeFactory("CCTableView",new NFCCTableViewFactory);
	_registerNodeFactory("CTableView",new NFCTableViewFactory);
	_registerNodeFactory("CScrollView",new NFCScrollViewFactory);
	_registerNodeFactory("CMapScrollView",new NFCMapScrollViewFactory);
//~~~~~~used By Home~~~~~
	_registerNodeFactory("HWMoreItem", new NFHWMoreItemFactory);

	_registerNodeFactory("FAnimationButton", new NFFAnimationButtonFactory);
    return true;
}

void NodeFactoryManager::_clearFacortyList(){
    map<std::string,NodeFactory*>::iterator it=m_map.begin();
    map<std::string,NodeFactory*>::iterator it_end=m_map.end();
    for (;it!=it_end;it++) {
        delete it->second;
    }
    m_map.clear();
}

void NodeFactoryManager::_registerNodeFactory(std::string key,NodeFactory* nf){
    m_map.insert(std::map<std::string,NodeFactory* >::value_type(key,nf));
}

void NodeFactoryManager::_removeNodeFactory(std::string key){
    map<std::string,NodeFactory* >::iterator it=m_map.find(key);
    NodeFactory* nf=it->second;
    assert(nf!=NULL);
    delete nf;
    m_map.erase(it);
}

cocos2d::CCNode* NodeFactoryManager::createNodeByKey(UIViewData* dd,CCNode* parentNode){
	NodeFactory* nf=m_map[dd->class_];
    if (!nf)return NULL;
    return nf->createNode(parentNode,dd);
}
