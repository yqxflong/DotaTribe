// Name :		MultiReWardWindow.h
// Function:	�����������
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _DOTATRIBE_MULTIREWARDWINDOW_H_
#define  _DOTATRIBE_MULTIREWARDWINDOW_H_


#include "IWindow.h"
#include "cocos2d.h"
#include "../include/CTableView.h"
#include "../include/UIViewDataManger.h"
#include "../include/MultiRewardDataHandler.h"
#include "../include/IPopWindow.h"

class MultiReWardWindow : public IWindow
	,public IPopWindow
	,public CCScrollViewDelegate
{
public:
	MultiReWardWindow();
	virtual ~MultiReWardWindow();

	enum{
			MultiReward_MaskLayer,
			MultiReward_BG,
			MultiReward_GETGOODSTITLE,
			MultiReward_PREVIEWTITLE,
			MultiReward_SureButton,
			MultiReward_SureButtonLabel,
			MultiReward_ArrowUp,
			MultiReward_ArrowDown,
			MultiReward_ScrollLayer,
			MultiReward_CellBG1,
			MultiReward_CellObject1,
			MultiReward_CellName1,
			MultiReward_CellNum1,
			MultiReward_CellBG2,
			MultiReward_CellObject2,
			MultiReward_CellName2,
			MultiReward_CellNum2,
		};
	enum
	{
		//���� 0:��Ʒ 1:��Ǯ 2: ���� 3:��ʯ 4:���� 5:����
		Type_Item,
		Type_Menoy,
		Type_Exp,
		Type_Diamond,
		Type_Pregist,
		Type_Energy,
	};

	enum
	{
		SysLang_Item,
		SysLang_Menoy=4021,
		SysLang_Exp,
		SysLang_Diamond,
		SysLang_Pregist,
		SysLang_Energy,
	};


	CCLayer* m_pRoot;
	CScrollView* scroll;

	bool			m_scrollflag;
	bool			m_isFirstIn;
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

	//��ʾ����
	virtual void ShowPopWindow();
	//�����Ѿ�����
	virtual void PopWindowDidHide();

public:
	/*
		��Ϣ�¼���Ӧ����
	*/
	virtual void    OnEventHandler(int iEventType, std::list<std::string>& paramList);
private:
	/*
		��ʾ��������¼�����
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	void ShowWindow();
	/*
		��ʼ������
	*/
	void InitLayer();
	void OnUpdateRewardInfo();
	void setArrow(CCScrollView* view);
	void On_Click_Close(cocos2d::CCObject* pSender);
	void ReSetData(MultiRewardData* data);
	float InitRewardList(CCLayer* layer);
	int _getQualityByData(MultiRewardData* data);
	void _chooseTitle();
	//�����ص�
	virtual void scrollViewDidScroll(CCScrollView* view);
	virtual void scrollViewDidZoom(CCScrollView* view){};
};

#endif
