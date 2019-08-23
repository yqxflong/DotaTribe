//Name��HELeadershipLvUpWindow
//Function���쵼����������
//Written By����ǿ

#ifndef  _DOTATRIBE_HELeadershipLvUpWindow_H_
#define  _DOTATRIBE_HELeadershipLvUpWindow_H_

#include "IWindow.h"
#include "../include/IPopWindow.h"


class HELeadershipLvUpWindow : public IWindow,public IPopWindow
{
private:
	enum{
		kGRAYLAYER,
		kBOXBG,
		kBTN,
		kBTN_LABEL,
		kHINT,
		kHEROLVTEXT,
		kHEROLV_BASE,
		kHEROLV_NEW,
		kIMPROVETEXT1,
		kIMPROVE1_BASE,
		kIMPROVE1_NEW,
		kIMPROVETEXT2,
		kIMPROVE2_BASE,
		kIMPROVE2_NEW,
		kIMPROVETEXT3,
		kIMPROVE3_BASE,
		kIMPROVE3_NEW,
		kARROW1,
		kARROW2,
		kARROW3,
		kARROW4,
	};
	cocos2d::CCNode* m_pRootLayer;
public:
	HELeadershipLvUpWindow();
	virtual ~HELeadershipLvUpWindow(){};
private:
	inline void _initLayout();
	inline void _mapBtn();
	inline void _setContent();
	//
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


	//��Ҫ����̳в���д
	virtual void ShowPopWindow();
	virtual void PopWindowDidHide();
public:
	/*
		��Ϣ�¼���Ӧ����
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

private:
	/*
		��ʾTop����¼�����
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		չʾ�Լ��Ĵ���
	*/
	void ShowWindow();
private:
	/*
		��ť�¼�
	*/
	void   On_Click_Event(cocos2d::CCObject* pSender);
};


#endif
