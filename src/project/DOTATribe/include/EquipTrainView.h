//Name:EquipTrainView
//Function:װ��ϴ��
//Author:fangjun
//Date:20130819

#ifndef _DOTATRIBE_EQUIPTRAIN_VIEW_H_
#define _DOTATRIBE_EQUIPTRAIN_VIEW_H_

#include "../include/SubView.h"
#include "../include/CDragSprite.h"
#include "../include/BagEquipDataHandler.h"
#include "../include/AnimationEffect.h"
#include "../include/AnimationFileDataManager.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/CAnimationSprite.h"

class EquipTrainView : public HLSubView, AnimationEffectCallBackProtocol
{
private:
	enum{
		tBg = 0,
		tLock1,
		tLock2,
		tLock3,
		tLock4,
		tAttri1,
		tAttri2,
		tAttri3,
		tAttri4,
		tAttri1Max,
		tAttri2Max,
		tAttri3Max,
		tAttri4Max,
		tNewAttri1,
		tNewAttri2,
		tNewAttri3,
		tNewAttri4,
		tNewAttri1Max,
		tNewAttri2Max,
		tNewAttri3Max,
		tNewAttri4Max,
		tLockMask1,//��λ������ڵ㣬xΪ���x���꣬yΪ�Ҳ�x����
		tLockMask2,
		tLockMask3,
		tLockMask4,
		tLockNumBg,
		tLockValue,//������
		tGoldPic,
		tGoldValue,//���ѽ�Ǯ��
		tTrainBtn,
		tTrainLabel,
		tOneTrainBtn,
		tOneTrainLabel,
		tAnimationNode,//��Ч���ؽڵ�
		tArrow1,
		tArrow2,
		tArrow3,
		tArrow4,
	}Page;

	BagEquipData * m_pCurEquip;//ֹͣʹ�ö���ָ�룬��Ϊ��ͬ��������Ϣʱԭ�д��ڵĶ�����ܻᱻ���ǡ�

	CAnimationSprite * m_pAnimationPlayNode;//���Ŷ����ڵ�
	CPriorityLayerColor * m_pAnimationGrayLayer;

	bool m_bInOneKeyTrainMode;

	int m_iWillUnLockAttributeIndex;

public:
	EquipTrainView();
	virtual ~EquipTrainView();

private:
	inline void _initLayout();
	inline void _initAnimationEffect();//��ʼ����Ч����
	inline void _mapAllBtn();
	inline void _enableTrainBtn(bool enabled);
	inline void _enableOneKeyTrainBtn(bool enabled);

	inline void _setBtnSelected(int key, bool selected);//for lockbtn only

	inline void _setResultAreaVisiable(bool visiable);

	inline void _setLabel(int key, cocos2d::CCNode * pParent, const char * txt);

	inline void _setNodeVisible(int key, bool isVisible);
	inline void _setNodeVisible(int key, CCNode * pParent, bool isVisible);

	//��ʾ���Ϊϴ��֮ǰ������
	inline void _showLeftAttribute();
	inline void _showLeftAttributeWhenOneKey();

	inline void _mapAttriToLockPosition();//�����Ժ�����λ�ð�

	inline void _showLockStatus();//��ʾ������״̬
	inline void _showMoney();//��ʾ���ѽ�Ǯ
	inline void _showLockObjectNum();//��ʾ����Ʒ����

	inline void Train();//ϴ��

	//���Ŷ���
	inline void PlayEffect();
	//�������ֲ㣬������Ч��ʾʱ�����û����
	void _createGrayLayer(int pri);
	void _removeGrayLayer();

protected:
	virtual bool onLoad();

	virtual bool onDestroy();

	virtual bool onTick();

	/*
		����װ���б�ĵ���
	*/
	virtual void EquipHasBeenSeleted(int equipID);
	
	/*
		����ǿ�����ڵĻص�
	*/
	virtual void EventWindowCallBack(int iEventType, std::list<std::string>& paramList);

	void On_ClickEvent(cocos2d::CCObject* pSender);

	void On_Lock_ClickEvent(cocos2d::CCObject * pSender);

public:
	//���������ص�
	virtual void  EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr);

public:
	/*
		�����¼������õ�ǰ����������
	*/
	void Function_LockAttribute();

	/*
		�����¼������õ�ǰ����������
	*/
	void Function_UnLockAttribute();

	/*
		�����¼�������ϴ�����
	*/
	void Function_TrainResult();

	/*
		�����¼������װ��������״̬��
	*/
	void Function_GetAttributeStatus();

	/*
		�����¼�����ñ�����Ʒ����ʱ֪ͨҳ����и���
	*/
	void Function_RefreshBagObjectShow();

	/*
		ȷ��ʹ��һ��ϴ��
	*/
	void Function_ConfirmUseOneKeyTrain();

public:
	void MoveLockPosition(bool right);//�л�����ʾλ��,true�ұߣ�left�����
};



#endif