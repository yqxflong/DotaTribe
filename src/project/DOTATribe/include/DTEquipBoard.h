//Name��DTEquipBoard
//Function�����װ����
//Written By����ǿ

#ifndef  _DOTATRIBE_HEEquipBoard_H_
#define  _DOTATRIBE_HEEquipBoard_H_

#include <cocos2d.h>
#include "../include/BagEquipDataHandler.h"


enum{
	kHETYPE_ROLE=0,		//����װ��
	kHETYPE_ELIST,		//װ���б�
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
	//begin:������Ӣ������װ��
	void RemoveEquip();
	//end

	//��д��������
	virtual void setPosition(const cocos2d::CCPoint& newPosition){
		cocos2d::CCNode::setPosition(ccp(newPosition.x-getAnchorPoint().x*getContentSize().width,newPosition.y-getAnchorPoint().x*getContentSize().height));
	}

	//�������ȼ�
	void setTouchPriority(int iPriority);
protected:
	void On_Click_Equip(cocos2d::CCObject* pSender);
private:
	int m_nEquipType;
	int m_nEquipID;
	DTEquipBoardDelegate* m_pDelegate;
	int m_nTouchPriority;
	CMenuItemSprite* m_pEquip;		//װ��icon
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