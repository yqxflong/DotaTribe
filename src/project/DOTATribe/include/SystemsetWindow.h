//Name��ϵͳ���ý���
//Function��ϵͳ����
//Written By��������

#ifndef  _DOTATRIBE_SYSTEMSETWINDOW_H_
#define  _DOTATRIBE_SYSTEMSETWINDOW_H_


#include "../include/IWindow.h"
#include <string>
#include "cocos-ext.h"

class SystemsetWindow : public IWindow
{
private:
	enum{
		syLayerColorBG,
		syBaseBG,
		syPlayerNameBG,
		syServerNameBG,
		syCloseBtn,
		syUSERCENTERBtn,
		syLogouBtn,
		syYinyueBtn,
		syYinxiaoBtn,
		syUSERCENTERLB,
		syLogouLB,
		syLByinyue,
		syLByinxiao,
		syCurrPlayerTTF,
		syCurrPlayerNameTTF,
		syCurrServerTTF,
		syCurrServerNameTTF,
	};
private:
	inline void _initLayout();
	inline void _mapBtns();
	inline void _setText();
private:
	cocos2d::CCNode *m_SystemNode;
	const int m_nSVZorder;
	int idx;
	bool m_isBguest;
public:
	SystemsetWindow();
	virtual ~SystemsetWindow();
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
		��ʾװ������¼�����
	*/
	inline void   OnShowWindowEventHandler(std::list<std::string>& paramList);

	/*
		����װ������¼�����
	*/
	inline void OnHideWindowEventHandler(std::list<std::string>& paramList);

	/*
		����װ������¼�����
	*/
	inline void OnUpdateWindowEventHandler(std::list<std::string>& paramList);

	/*
		����װ������¼�����
	*/
	inline void OnFadeoutWindowEventHandler(std::list<std::string>& paramList);

protected:
	//����¼�
	void On_Click_Event(cocos2d::CCObject* pSender);
	//�û��˻������¼�
	void On_Click_User_Event(cocos2d::CCObject* pSender);
	//���ص�¼�¼�
	void On_Click_LoginBack_Event(cocos2d::CCObject* pSender);
protected:
	//�����ǿ�����
	bool IsBackgroundMusic();
	//��Ч�ǿ�����
	bool IsEffectSound();
};

#endif
