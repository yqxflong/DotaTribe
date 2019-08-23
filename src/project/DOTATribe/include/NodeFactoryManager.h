//Name: NodeFactoryManager.h
//Func: Used to Manage NodeFactory
//Written by: Johny

#ifndef __AutoCocos__NodeFactoryManager__
#define __AutoCocos__NodeFactoryManager__

#include <iostream>
#include <cocos2d.h>
#include <cocos-ext.h>
#include <map>
#include "../include/UIViewDataManger.h"

/*
    each kind of _class must be herited by CCNode
 */
class NodeFactory {
    
public:
	virtual ~NodeFactory(){};
	virtual cocos2d::CCNode* createNode(cocos2d::CCNode* parentNode,UIViewData* dd)=0;
};

class NodeFactoryManager{
private:
    std::map<std::string,NodeFactory*> m_map;
public:
    static NodeFactoryManager* instance();
    void OnDestroy();
    cocos2d::CCNode* createNodeByKey(UIViewData* dd,cocos2d::CCNode* parentNode);
private:
    /*
     Register NodeFactory by this method
     */
    bool _init();
    /*
     before recreate the NodeFacortyManager or exit the program
     */
    void _clearFacortyList();
    
    void _registerNodeFactory(std::string key,NodeFactory* nf);
    
    void _removeNodeFactory(std::string key);

    
};
#define ACNODEFACTORYMANAGER			NodeFactoryManager::instance()

#endif /* defined(__AutoCocos__NodeFactoryManager__) */
