//Name��DTAwardBoard
//Function������ͼ��ؼ�
//Written By����ǿ

#ifndef  _DOTATRIBE_DTAwardBoard_H_
#define  _DOTATRIBE_DTAwardBoard_H_

#include <cocos2d.h>


class CMenuItemSprite;
class DTAwardBoard:public cocos2d::CCNode
{
public:
	enum{
		kAB_EMPTY=0,		//�޽���
		kAB_EQUIP,			//װ��
		kAB_OBJECT,			//��Ʒ
		kAB_ICON,			//��ֵ
	};
public:
	DTAwardBoard();
	virtual ~DTAwardBoard(){};
	static DTAwardBoard* create(cocos2d::CCSprite* numBg,cocos2d::CCLabelTTF* num,int priority=0,bool swallow=true);
	bool init(cocos2d::CCSprite* numBg,cocos2d::CCLabelTTF* num,int priority,bool swallow);
	//
	/*
		������Ʒ
	*/
	void ChangeObject(int quality=-1,int iconid=-1,int num=-1);
	void setTarget(cocos2d::CCObject *rec, cocos2d::SEL_MenuHandler selector);

	//��д����Tag
	virtual void setTag(int nTag);

	//�������ȡ��ť��Index
	void setIDX(int idx);
	void setAttachParam(int attachParam1,int attachParam2=0);
	int getIDX() const;

	//�������趨ͼƬ����
	void setContentScale(float times);
	float getContentScale();

	//��д��ȡSize
	virtual const cocos2d::CCSize& getContentSize() const{
		return m_pMask->getContentSize();
	}
	//��д��������
	virtual void setPosition(const cocos2d::CCPoint& newPosition){
		cocos2d::CCNode::setPosition(ccp(newPosition.x-getAnchorPoint().x*getContentSize().width,newPosition.y-getAnchorPoint().x*getContentSize().height));
	}

	//���ð�ť�������
	void setEnabled(bool bEnabled);

	//���ó�ʧЧ״̬,���Ҳ�
	void setDisabled(bool bDisabled);
private:
	int m_nPriority;
	bool m_bSwallow;
	cocos2d::CCSprite* m_pBoard;	//�װ�
	cocos2d::CCMenu* m_pObject;		//��ƷMenu
	CMenuItemSprite* m_pObjectItem;	//��ƷItem
	cocos2d::CCSprite* m_pNum_BG;	//������ͼ
	cocos2d::CCLabelTTF* m_pNum;	//����
	cocos2d::CCSprite* m_pMask;		//��+�ɰ�
	cocos2d::CCLayerColor* m_pGray;		//�Ҳ�
	float m_fContentScale;//װ�������ű���
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