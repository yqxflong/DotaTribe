//Name��NoticeBoxWindow
//Function�����浯��
//Written By����ǿ

#ifndef  _DOTATRIBE_NOTICEBOXWINDOW_H_
#define  _DOTATRIBE_NOTICEBOXWINDOW_H_

#include "../include/IWindow.h"
#include <cocos2d.h>
#include <cocos-ext.h>
#include "../include/CTableView.h"
#include "../include/MaskNode.h"
class NoticeBoxWindow : public IWindow
{
private:
	enum{
		udGRAYLAYER,
		udBG,
		udCLOSEBTN,
		udSURETEXT,
		udSCROLLVIEW,
		udTEXTTITLE,
		udTEXTCONTENT,
		udMASKNODE,
	};

	enum{
		GWudGRAYLAYER,
		GWudBG,
		GWudCLOSEBTN,
		GWudSCROLLVIEW,
		GWudCLOSEBTN_LABEL,
		GWudTEXTTITLE,
		GWudTEXTCONTENT,
		GWudTEXTDEFAULT
	};

	cocos2d::CCLayer* m_pRootLayer;
	CScrollView* m_pScroll;
	int m_Type;
public:
	NoticeBoxWindow();
	virtual ~NoticeBoxWindow(){};
private:
	inline void _initLayout();
	inline void _mapBtn();
	inline void _transferNode();
	inline void _setviewforScroll();
	inline void _setviewforScroll_gateway();
	inline void _initLayoutGateWay();
	inline void _mapBtnGateWay();
	inline void _transferNodeGateWay();

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

public:
	/*
		��Ϣ�¼���Ӧ����
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

private:
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);

private:
	/*
		��ť�¼�
	*/
	void   On_Click_BtnClick(cocos2d::CCObject* pSender);

};


#endif
