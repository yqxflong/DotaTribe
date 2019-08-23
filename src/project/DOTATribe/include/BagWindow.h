//Name:BagWindow.h
//Function:����
//Author:fangjun
//Date:20130902

#ifndef _DOTA_BAGWINDOW_H_
#define _DOTA_BAGWINDOW_H_

#include <cocos2d.h>
#include <cocos-ext.h>
#include "../include/IWindow.h"
#include <string>
#include "../include/CPageScroll.h"
#include "../include/MaskNode.h"
#include "../include/CMenuItemSprite.h"
#include "../include/CSprite.h"
#include "../include/CSMapTable.h"
#include "../include/CTipsViewDelegate.h"

class PanelItem : public cocos2d::CCNode{
public:
	enum
	{
		pQUALITY = 0,
		pICON,
		pHat, //���ֲ�
		pELEVEL,//ǿ���ȼ�������
		pLEVEL,//�ȼ�������
		pCOUNT,//����������
		pRIGHTTOPBG,//���ϱ���
		pLEFTDOWNBG,//���±���
	};
	int _itemId;		//������װ��ƷId
	int _tag;
	int _type;			//��������
public:
	void _setEnhanceLevel(int elevel);
	void _setLevel(int level);
	void _setLabelCount(int count);
public:
	PanelItem();
	~PanelItem();
	static PanelItem* createEmpty(int tag, cocos2d::CCObject* target,cocos2d:: SEL_MenuHandler selector);
	void setItemId(int id);
	int getItemId();
};

class InfoPoolData{
public:
	enum{
		INFO_LOCK = -1,
		INFO_EMPTY = 0,
		INFO_HAS = 1,
	};
	InfoPoolData()
	{
		tag = -1; page = -1; itemid = -1; itemcount = -1; enhancelevel = -1;
		quality = -1; icon = -1; infoType = -1; drawed = false;
	};
public:
	int tag;//�����ƥ���λ��
	int page;//��ҳ
	int itemid;//��Ʒ��ID�������֪��������id����Ҫ���ⲿʹ��ʱע��
	int itemcount;//��Ʒ����
	int enhancelevel;//ǿ���ȼ�
	int level;//�ȼ�
	int quality;//����ͼ
	int icon;//ͼ��

	int infoType;//��������Ʒ����Ϣ
	
	bool drawed;
};

class BoardPoolData{
public:
	BoardPoolData()
	{
		tag = -1;
		page = -1;
		drawed = false;
	}
public:
	int tag;
	int page;
	bool drawed;
};

class BagPool{
public:
	std::vector<BoardPoolData *> board_pool_data;

	std::vector<InfoPoolData *> info_pool_data;

	float board_position[NEWBAG_NUMPERPAGE][2];
	float page_width;
	
	std::string empty_file;			//�հ�
	std::string select_file;		//ѡ�п�
	std::string lock_file;			//��ͼ

	bool all_board_drawed;
	bool all_info_drawed;

	int filltype;//�������������
public:
	BagPool();
public:
	/*
		�����
	*/
	void Insert(BoardPoolData * data);

	void Insert(InfoPoolData * data);
	/*
		ɾ����������
	*/
	void PopPage(int page);

	/*
		�����е����ݹ���
	*/
	void HangPageBoard(int page, cocos2d::CCNode * parent);

	void HangPageInfo(int page, cocos2d::CCNode * parent);

	void HangData(cocos2d::CCNode * parent);

	void HangPage(cocos2d::CCNode * parent);

	/*
		�����Ϣҳ
	*/
	void ClearInfoData();

	/*
		���
	*/
	void Destroy();

	/*
		��ʼ��
	*/
	void Init();

private:
	void createBoard(BoardPoolData * data, cocos2d::CCNode * parent);
	void createInfo(InfoPoolData * data, cocos2d::CCNode * parent);
};


class BagWindow : public IWindow, public CPageScrollDelegate, CTipsViewDelegate
{
private:
	enum{		
		pageObjectList = 0,
		pageComposeList,

	} PAGEKIND;
	
	enum{
		functionSALE,
		functionUSE,
	}USE_SALE;

	enum{
		oNameBg = 0,
		oName,
		oStar,//�Ǽ�
		oLevel,
		oLevelValue,
		oPrice,
		oPriceValue,
		oGoldIcon,
		oDes,
		oSaleBtn,
		oSaleLabel,
		oUseBtn,
		oUseLabel,
		oGuideArrow,
	}ObjectList;

	enum{
		cComposeLabel = 0,
		cNamebg,
		cQuality,
		cName,
		cNeedLebel,
		cNeedQuality1,
		cNeedQuality2,
		cNeedQuality3,
		cNeedQuality4,
		cNeedValue1,
		cNeedValue2,
		cNeedValue3,
		cNeedValue4,
		cCostLabel,
		cCostValue,
		cGoldIcon,
		cComposeBtn,
		cComposeBtnLabel,
	}ComposeList;

	enum{
		mBagBg = 0,//��������
		mBagBg2,	//����2
		mCloseBtn,	//�رհ�ť
		mBagPic,//����ͼ
		mBagNameBg,	//�����ֵ�ͼ
		mBagName,//������
		mObjectListBtn,//��Ʒ�б�ť
		mComposeListBtn,//�ϳɰ�ť
		mLeftArrow,		//�����ͷ
		mRightArrow,	//���Ҽ�ͷ
		mLeftArrowMove,		//���������ͷ
		mRightArrowMove,	//���ҹ�����ͷ
		mPageNumBg,		//ҳ���ͼ
		mPageNumValue,	//ҳ��ֵ
		mJewelBg,
		mJewelValue,//��ʯֵ
		mGoldBg,
		mGoldValue,//���ֵ
		mLeftNode,//����ص�
		mRightNodeMask,//�ҹ��ص�
		mObjectGuideArrow,				//ָ������Ʒҳ����
		mObjectGuideArrowLabel,			//ָ������Ʒҳ��������
	}Main;

private:
	cocos2d::CCNode * m_pRoot;//�����ڸ��ڵ�

	cocos2d::CCNode * m_pLeftNode;	//��ߵĸ��ڵ�
	CPageScroll* m_pRightPage;		//�Ҳ�ɷ�ҳ���

	int m_iSubPageKind;//��ʾ��ҳ���
	cocos2d::CCMenuItemSprite * m_pSelectSubPage;//ѡ����Ҳ����

	//CSprite * m_pCurPage;		//��¼��ǰ�ķ�ҳ

	int m_iSelectedTag;	//ѡ�е�id����ʵ����tag�����Ǻ��б�vectorλ�ö�Ӧ
	cocos2d::CCMenuItemSprite * m_pSelectedItem;//ѡ�е�item,Ϊ��ѡ��ʱ�����ȡ���ϴ�ѡ��

	int m_iBtnFunction;//��������򵯳�ǰ����

	bool m_bChangedSelectTag;//��Ǹ�����ѡ�п�

	int m_iMaxComposeNum;//��Ʒ�ϳ�ʱ���ɺϳ�������ֵ0

private:
	int m_iBackWindow;//���صĽ���

private:
	BagPool m_Pool;
	friend class BagPool;

public:
	BagWindow();
	virtual ~BagWindow();
private:
	inline void _initLayout();

	inline void _setText(int tag, cocos2d::CCNode * parent, const char * text);
	inline void _setText(int tag, cocos2d::CCNode * parent, int num);
	inline void _setTexture(int tag,  cocos2d::CCNode * parent, const char * picpath);
	//inline void _setBtnTexture(int tag, cocos2d::CCNode * parent, const char * nor, const char * sel, const char dis);
	inline void _enableBtn(int tag, cocos2d::CCNode * parent, bool enable);
	inline void _setVisible(int tag, cocos2d::CCNode * parent, bool visible);
	inline cocos2d::CCMenuItem * _mapBtnWithTag(int tag, cocos2d::CCNode * parent, CCObject *rec, cocos2d::SEL_MenuHandler selector);

	//��ʼ���Ҳ��б�
	inline void _initRightPanel(MaskNode * node);
	inline void _initLeftPage();//��ʾ������

	inline void _bindSelectorForTouchSprite(int signID);//�󶨵���¼�

	inline void _setMainPageInfo();//������������Ϣ
	inline void _setLeftPageInfo(int selecttag);//������������Ϣ
	inline void _setRightPanelInfo();//�����Ҳ���ʾ��Ϣ
	inline void _setMenuPage(int pageid);//���÷�ҳѡ��

	inline void _setDefaultPageAndItem(int selectTag);//����Ĭ�ϵ�ҳ��ѡ�п�

	inline void _mapMainPageBtn();//�������水ť//�����Ҳ��ڸ��Ե�init�д���

	inline void _refreshDrawInfoData(int bagType, int tag, int num);//ˢ�»������ݲ���,����1����Ʒ���࣬����2Ϊ�Լ�������index������3Ϊ��Ʒ����

	inline void _setSelectPage();//ѡ��ѡȡ��ҳ��

	//���ˢ�����
	void _refreshObjectInfo(int selecttag);
	void _refreshComposeInfo(int selecttag);

	//���ý�Ǯ\��ʯ
	void refreshUIData();

public:
	//��ҳ��
	void On_MainPage_Btn_Click(cocos2d::CCObject * pSender);

	//������
	void On_LeftPage_Btn_Click(cocos2d::CCObject * pSender);

	//�Ҳ���
	void On_RightMenu_Click(cocos2d::CCObject * pSender);

	//�ϳɽ���tips
	void On_ObjectTips_Click(cocos2d::CCObject * pSender);
public:
	/*
		��ʼ������
	*/
	virtual    bool    Init();
	/*
		���ش���
	*/
	virtual    bool    Load();
	/*
		����´���
	*/
	virtual    void    Tick();
	/*
		���ٴ���
	*/ 
	virtual    void    Destroy();

	/*
		��ҳ�б�̳е��¼�
	*/
	virtual void changePage(int idx);
	
	/*
		ȡ��tips��ʾ
	*/
	virtual void cancelTipsLayer();

public:
	/*
		��Ϣ�¼���Ӧ����
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

private:
	/*
		show�¼�����
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	/*
		Refresh������ȴ���
	*/
	void OnRefreshWindowEventHandler(std::list<std::string>& paramList);


private:
	/*
		�������빦�ܽ��
	*/
	void Function_NumInputResult(int num);

	/*
		ȷ����������Ʒ
	*/
	void Function_ComfirmSaleImportant();

protected:
	/*
		�رմ����¼�
	*/
	void On_Close_Window(cocos2d::CCObject* pSender);

};

#endif
