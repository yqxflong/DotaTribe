//Name：EffectWindow
//Function：用于展现效果的窗口，暂时用于获得物品时
//Written By：尹强

#ifndef  _DOTATRIBE_EffectWindow_H_
#define  _DOTATRIBE_EffectWindow_H_

#include "IWindow.h"

class EffectData;
class EffectWindow: public IWindow{
private:
	enum{
		udICON,
		udNUMLABEL,
		udNUMBJLABEL,
	};
	cocos2d::CCNode* m_pRoot;
public:
	enum{
		kOBJECT=0,
		kMONEY,
		kDIAMOND,
		kEXP,
	};
	EffectWindow();
	virtual ~EffectWindow(){};
private:
	inline void _initLayout();
//创建每个效果
	inline void _createICON(cocos2d::CCNode* effectNode,EffectData* dd);
	inline void _createLabel(cocos2d::CCNode* effectNode,EffectData* dd);
	inline void _createBJLabel(cocos2d::CCNode* effectNode,EffectData* dd);
	inline void _showEffect(cocos2d::CCNode* effectNode,EffectData* dd);
public:
	/*
		初始化处理
	*/
	virtual    bool    Init();
	/*
		加载处理
	*/
	virtual    bool    Load();
	/*
		桢更新处理
	*/
	virtual    void    Tick();
	/*
		销毁处理
	*/ 
	virtual    void    Destroy();

public:
	/*
		消息事件响应处理
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

private:
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);

protected:
	void On_Animation_CallBack(cocos2d::CCNode* pSender);
};

#endif