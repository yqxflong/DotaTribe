//Name��RoleStatusWindow
//Function������״̬��
//Written By����ǿ

#ifndef  _DOTATRIBE_RoleStatusWindow_H_
#define  _DOTATRIBE_RoleStatusWindow_H_

#include "IWindow.h"
#include "../include/DTRoleStatusBar.h"

class RoleStatusWindow : public IWindow
	,public DTRoleStatusBarDelegate
{
public:
	int Current_WindowType_;
private:
	enum{
		kROLESTATUSBAR,	//����״̬��ռλ�ڵ�
		kMainTask,		//��������
		kMAINTASKEFFECT,	//����������Ч
		kSkeletonAniamtion, //�������
		kNewTaskNode,		//��������ʾ
		kNewHeroNode,		//��Ӣ����ʾ
//=======================
		kREAL_ROLESTATUSBAR,	//����״̬��
	};
	DTRoleStatusBar* m_pRoleStatusBar;
	int m_nShowCounter;	//��ʾ������
public:
	RoleStatusWindow();
	virtual ~RoleStatusWindow(){};

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
		ˢ�½���
	*/
	void RefreshUI();

public:
	/*
		��Ϣ�¼���Ӧ����
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

	/*
		����ˢ��UI�¼�
	*/
	static void Event_RefreshUI_Handler(int iEventType, std::string owerData, std::list<std::string>& paramList);

	/*
		DTRoleStatusBar CallBack
	*/
	virtual void AvatarClickEvent();
	virtual void SkillClickEvent();
	virtual void AddTLClickEvent();
	/*
		MainTask CallBack
	*/
	void MainTaskClickEvent(cocos2d::CCObject* pSender);
	void UpdateMainTaskHint();
	void UpdateRoleState();
protected:
	/*
		��ʾTop����¼�����
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
private:
	inline void _registerEvent();
	inline void _unregisterEvent();
	inline void _initLayout();
	inline void _mapRoleStatus();
	inline void _mapMainTask();
};


#endif
