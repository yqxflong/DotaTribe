//Name��StartWindow
//Function����ʼ����
//Written By����ǿ

#ifndef  _DOTATRIBE_StartWindow_H_
#define  _DOTATRIBE_StartWindow_H_

#include "IWindow.h"

class StartWindow : public IWindow
{
private:
	enum{
		udBG,
		udPROGRESS,
		udPROGRESS_BG,
		udPERCENTLABEL,
		udSERVERBTN,		//ѡ����ť
		udENTERBTN,			//������Ϸ
		udSERVER_NAME,		//����������
		udSERVER_STATUS,	//������״̬
		udSERVER_HINT,		//���ѡȡ
		udENTERLABEL,
		udFILECOUNT,
		udLOGOICON,
		udVERSION,

	};
	cocos2d::CCNode* m_pRoot;
	bool isNoticeShowed;
public:
	StartWindow();
	virtual ~StartWindow();
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
private:
	inline void _initLayout();
	inline void _mapBtn();
	inline void _setDefaultServer();
	inline void _setVerson();
	inline void _setFileCount(int filecount,int totalcount);
	inline void _showDownloadControls(bool isshow);
	inline void _showNormalControls(bool isshow);
	//
protected:
	void On_Click_Event(cocos2d::CCObject* pSender);
public:
	/*
		��Ϣ�¼���Ӧ����
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);
	//
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	void   On_UI_Show_Download(std::list<std::string>& paramList);
	void   On_UI_Show_Normal(std::list<std::string>& paramList);
	void   On_UI_Update_ByLogin(std::list<std::string>& paramList);
};

#endif
