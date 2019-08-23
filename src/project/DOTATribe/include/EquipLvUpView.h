//Name : EquipLvUpView
//Function��װ����������
//Written By : ����->��ǿ
//AnchorPoint:  (0,0) can not change

#ifndef  _DOTATRIBE_EQUIPLVUPVIEW_H_
#define  _DOTATRIBE_EQUIPLVUPVIEW_H_

#include "../include/SubView.h"
#include "../include/CTouchSprite.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/AnimationEffect.h"
#include "../include/AnimationFileDataManager.h"
#include "../include/BagEquipDataHandler.h"

#include "../include/FAnimationButton.h"

class BagEquipData;
class EquipLvUpView: public HLSubView
	,public cocos2d::extension::CCTableViewDataSource
	,public AnimationEffectCallBackProtocol
	,public FrameAnimationDelegate
	,public CPriorityLayerColorDelegate
{
private:
	enum{
		udRIGHTBG,
		udEXPBOARD,
		udEXPBAR,
		udEQUIP,			//����ڵ�
		udBTNCHOOSE,
		udBTNBUY,
		udBTNLVUP,
		udBTNCHOOSETITLE,
		udBTNBUYTITLE,
		udBTNLVUPTITLE,
		udLV,
		udLVVALUE,
		udATTRIBUTE,
		udATTRIBUTEVALUE,
		udCOSTICON,
		udCOSTNUM,
		udTABLEVIEW,
		udTABLEVIEWCELL,		//����ڵ�
		udAnimationNode,	//��Ч���ص�
		udNOCOSTCARDHINT,		//���ز���ʾ
		udNOEXPBALLHINT,		//�޾�������ʾ
		udDAIJIJIANTOUNODE,	//������ͷ�ڵ�
		udADDMATERIAL,		//һ����ӵ����
		udADDICON,			
		udADDLABELTEXT,		
	}VIEW;
	enum{
		udBG1,
		udBG2,
		udOBJ1,
		udOBJ2,
		udNAME1,
		udNAME2,
		udSTAR1,
		udSTAR2,
		udTYPE1,
		udTYPE2,
	}CELL;
	cocos2d::CCSize m_szCell;
	cocos2d::CCNode * m_pResultView;
	cocos2d::extension::CCTableView * m_pTableView;
	cocos2d::ccColor3B m_oCostColor;
	//////////////////////
	cocos2d::CCSprite * m_pAnimationPlayNode;//���Ŷ����ڵ�
	AnimationFileData * m_pAnimationFileData;//��Ч�ļ�
	PAnimation_Call_Node m_pAnimationCallBack;//�ص�����
	cocos2d::CCAnimation * m_pAnimation;//����
	CPriorityLayerColor * m_pAnimationGrayLayer;//�Ҷ�
	CPriorityLayerColor * m_pOneKeyAddLayer;//һ����ӻҲ�

	BagEquipData m_OldEquipData;

	int m_iTickAnimationAction;
	bool m_bInPlayingAnimation;
	CCSprite * m_pAnimationWhiteSp;

	FrameAnimationNode * m_pFrameAnimationNode;
	cocos2d::extension::CCSkeletonAnimation* m_pArrow;//����������ͷ

	cocos2d::CCArray* ProgressArray;
	int ProgressRunTimes;
public:
	EquipLvUpView();
	virtual ~EquipLvUpView(){};
private:
	inline void _initData();
	inline void _initLayout();
	inline void _initOldCostColor();
	inline void _initAddMaterialLayer();
	inline void _initAnimationEffect();
	inline void _setCellSize();
	inline void _mapAllBtn();
	inline void _mapBtn(int key);
	inline void _setTableView();
	inline void _setAddMaterialIconAndLabel();
	inline void _setExpBar(BagEquipData* bb);
	inline void _showAddMaterial(bool flag);
	inline void _showEquip();

	//���ý�������Ϣ
	inline void _setResultInfo();
	inline void _setResultExpBar(int exp,int mapexp);
	//
	/*
		����ѡȡ�زĽ���
	*/
	inline void _enterChooseCard();

	//�жϲ���ʾѡ���Ӣ����Ϣ
	inline void _checkEquipID();
	//�鿴�Ƿ��������������ť
	inline void _checkLvBtnStatus();
	//
	/*
		����װ����Ϣ
	*/
	inline void _showEquipInfo(bool isShow);

	/*
		����button
	*/
	inline void _enableBtns(bool enabled);
	/*
		Cell���
	*/
	inline void _createTableCell(cocos2d::extension::CCTableViewCell* cell);
	inline void _setTableCell(cocos2d::extension::CCTableViewCell* cell,int idx);
	void _setBlockInfo(cocos2d::extension::CCTableViewCell* cell,int blockIdx);
	void _showBlock2(cocos2d::CCNode* cell,bool isShow);
	void _initProgressTimer();
	//���Ŷ���
	inline void PlayEffect();
	//����������
	void _setProgress();
	//�����������ص�
	void CallbackBtnEnable();
	//�����������ص�2
	void CallbackTTF();
	//�������ֲ㣬������Ч��ʾʱ�����û����
	void _createGrayLayer();
	void _removeGrayLayer();
	/*
		�������������ͷ
	*/
	void _setGuidejiantou();
	/*
		���ز�
	*/
	inline void _buyCost();

	//����Ǯ��ɫ
	inline void _checkCostColor();

	//���û��ѽ�Ǯ
	inline void _setCost();

	/*
		��ʾװ����������Ķ���
	*/
	inline void _showResultView();	
	/*
		����زĿ��Ƿ�Ϊ��
	*/
	void _checkCostCardEmpty();
	/*
		��龭�����Ƿ�Ϊ��
	*/
	bool _checkExpBallEmpty();
	/*
		��������
	*/
	void _resetMainCard(int equipID);
	/*
		������������
	*/
	void _setOldEquipInfo(BagEquipData* data);
	/*
		�رս������
	*/
	void _closeResultView();
	/*
		����װ��������Ϣ
	*/
	void _refreshLeftInfo();
	/*
		ˢ���ұ���Ϣ
	*/
	void _refreshRightInfo();
	
protected:
	virtual bool onLoad();
	virtual bool onDestroy();
	virtual bool onTick();
	/*
		����װ���б�ĵ���
	*/
	virtual void EquipHasBeenSeleted(int equipID);

	//����ǿ�����ڵĻص�
	virtual void EventWindowCallBack(int iEventType, std::list<std::string>& paramList);
	//
	void On_ClickEvent(cocos2d::CCObject* pSender);

protected:
	    /**
     * cell height for a given table.
     *
     * @param table table to hold the instances of Class
     * @return cell size
     */
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    /**
     * a cell instance at a given index
     *
     * @param idx index to search for a cell
     * @return cell found at idx
     */
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    /**
     * Returns number of cells in a given table view.
     * 
     * @return number of cells
     */
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

public:
	//���������ص�
	virtual void  EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr);
	//�Ҳ����ֻص�
	virtual void touchEvent(CPriorityLayerColor* pLayerColor);
public:
	/*
		�����¼������õ�ǰ���ڵĻ��ѽ�Ǯ����������������ť�Ƿ����
	*/
	void Function_SetConstMoney();

	/*
		�����¼�����ʾ�����������
	*/
	void Function_ShowResultView();

	/*
		�������̽���������ڴ����Ѵ������
	*/
	void LvUpCleadEnd();


	//��������
	void _toLvUp();

	/*
		ѡ��ɫ����ȷ��ʹ�ÿ򷵻أ�ȷ��ʹ��
	*/
	void Function_ConfirmLvUp();

private:
	void LvUpAnimationActionPart();

public:
	virtual void FrameAnimationIntercept(int frameId, cocos2d::CCNode * node);
};


#endif
