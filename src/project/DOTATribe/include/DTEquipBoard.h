//Name：DTEquipBoard
//Function：组合装备栏
//Written By：尹强

#ifndef  _DOTATRIBE_HEEquipBoard_H_
#define  _DOTATRIBE_HEEquipBoard_H_

#include <cocos2d.h>
#include "../include/BagEquipDataHandler.h"


enum{
	kHETYPE_ROLE=0,		//人物装备
	kHETYPE_ELIST,		//装备列表
};


class DTEquipBoardDelegate{
public:
	virtual void CallBack_ClickEquip(int type,int equipID)=0;
};

class CMenuItemSprite;
class DTEquipBoard:public cocos2d::CCNode
{
public:
	DTEquipBoard();
	virtual ~DTEquipBoard(){};
	static DTEquipBoard* create(cocos2d::CCSprite* hint,cocos2d::CCSprite* corner,cocos2d::CCLabelTTF* num);
	bool init(cocos2d::CCSprite* hint,cocos2d::CCSprite* corner,cocos2d::CCLabelTTF* num);
	//
	void SetEquip(int type,BagEquipData* equip,DTEquipBoardDelegate* pDel);
	void SetEquip(int iconID,int quality,int level);
	//begin:仅用于英雄身上装备
	void RemoveEquip();
	//end

	//重写设置坐标
	virtual void setPosition(const cocos2d::CCPoint& newPosition){
		cocos2d::CCNode::setPosition(ccp(newPosition.x-getAnchorPoint().x*getContentSize().width,newPosition.y-getAnchorPoint().x*getContentSize().height));
	}

	//设置优先级
	void setTouchPriority(int iPriority);
protected:
	void On_Click_Equip(cocos2d::CCObject* pSender);
private:
	int m_nEquipType;
	int m_nEquipID;
	DTEquipBoardDelegate* m_pDelegate;
	int m_nTouchPriority;
	CMenuItemSprite* m_pEquip;		//装备icon
	cocos2d::CCLabelTTF* m_pNum;
	cocos2d::CCSprite* m_pHint;
	cocos2d::CCSprite* m_pCorner;
	cocos2d::CCSprite* m_pBoard;
	cocos2d::CCSprite* m_pMask;
	//
	void _initLayout();
	void _setCornerNum(unsigned int num);
	void _setCornerVisible(bool isvisible);
	void _changeBoard(int quality);
	void _resetBoard();
	void _showHint(bool isshow);
};

#endif