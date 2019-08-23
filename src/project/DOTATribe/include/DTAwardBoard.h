//Name：DTAwardBoard
//Function：奖励图框控件
//Written By：尹强

#ifndef  _DOTATRIBE_DTAwardBoard_H_
#define  _DOTATRIBE_DTAwardBoard_H_

#include <cocos2d.h>


class CMenuItemSprite;
class DTAwardBoard:public cocos2d::CCNode
{
public:
	enum{
		kAB_EMPTY=0,		//无奖励
		kAB_EQUIP,			//装备
		kAB_OBJECT,			//物品
		kAB_ICON,			//数值
	};
public:
	DTAwardBoard();
	virtual ~DTAwardBoard(){};
	static DTAwardBoard* create(cocos2d::CCSprite* numBg,cocos2d::CCLabelTTF* num,int priority=0,bool swallow=true);
	bool init(cocos2d::CCSprite* numBg,cocos2d::CCLabelTTF* num,int priority,bool swallow);
	//
	/*
		更改物品
	*/
	void ChangeObject(int quality=-1,int iconid=-1,int num=-1);
	void setTarget(cocos2d::CCObject *rec, cocos2d::SEL_MenuHandler selector);

	//重写设置Tag
	virtual void setTag(int nTag);

	//设置与获取按钮的Index
	void setIDX(int idx);
	void setAttachParam(int attachParam1,int attachParam2=0);
	int getIDX() const;

	//设置所设定图片缩放
	void setContentScale(float times);
	float getContentScale();

	//重写获取Size
	virtual const cocos2d::CCSize& getContentSize() const{
		return m_pMask->getContentSize();
	}
	//重写设置坐标
	virtual void setPosition(const cocos2d::CCPoint& newPosition){
		cocos2d::CCNode::setPosition(ccp(newPosition.x-getAnchorPoint().x*getContentSize().width,newPosition.y-getAnchorPoint().x*getContentSize().height));
	}

	//设置按钮启用情况
	void setEnabled(bool bEnabled);

	//设置成失效状态,带灰层
	void setDisabled(bool bDisabled);
private:
	int m_nPriority;
	bool m_bSwallow;
	cocos2d::CCSprite* m_pBoard;	//底板
	cocos2d::CCMenu* m_pObject;		//物品Menu
	CMenuItemSprite* m_pObjectItem;	//物品Item
	cocos2d::CCSprite* m_pNum_BG;	//数量底图
	cocos2d::CCLabelTTF* m_pNum;	//数量
	cocos2d::CCSprite* m_pMask;		//框+蒙版
	cocos2d::CCLayerColor* m_pGray;		//灰层
	float m_fContentScale;//装载物缩放倍数
	//
	void _initLayout();
	void _initBoard();
	void _initObject();
	void _initNum();
	void _initGray();
	void _setNum(unsigned int num);
	void _setNumVisible(bool isvisible,int num = 0);
	void _setObjectVisible(bool isvisible);
	void _changeBoard(int quality);
	void _resetBoard();
	void _changeObject(int iconid);
};

#endif