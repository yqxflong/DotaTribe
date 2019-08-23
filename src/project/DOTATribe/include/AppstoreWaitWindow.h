//Name��AppstoreWaitWindow
//Function��Appstore�ȴ�֧����
//Written By��lvyunlong

#ifndef  _DOTATRIBE_APPSTOREWAITWINDOW_H_
#define  _DOTATRIBE_APPSTOREWAITWINDOW_H_

#include "IWindow.h"

class AppstoreWaitWindow : public IWindow
{
private:
	enum{
		udGRAYLAYER,
		udSENCE,
	};
	cocos2d::CCNode* m_pRoot;
public:
	AppstoreWaitWindow();
	virtual ~AppstoreWaitWindow();
private:
	inline void _initLayout();
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
	/*
		��ʾTop����¼�����
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		����֧������
	*/
	void   OnHideWindowEventHandler(std::list<std::string>& paramList);

};


#endif
