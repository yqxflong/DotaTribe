//Name��StartWindow
//Function����ʼ����
//Written By����ǿ

#include <cocos2d.h>
#include "../include/StartWindow.h"
#include "../include/DotaGameConfig.h"
#include "../include/NFControlsManager.h"
#include "../include/NFToolController.h"
#include "../include/NFAnimationController.h"
#include "../include/EventTyper.h"
#include "../include/UIViewDataManger.h"
#include "../include/CMenuItemSprite.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/SysLangDataManager.h"
#include "../include/MessageBoxWindow.h"
#include <string>
#include "../include/IProcedure.h"
#include "../include/LocalPlayerDataManager.h"

using namespace std;
USING_NS_CC;

StartWindow::StartWindow()
{
	m_WindowType   = _TYPED_WINDOW_START_;
	m_bModelWindow = true;
	m_pRoot=0;
	isNoticeShowed = false;
}

StartWindow::~StartWindow()
{

}

bool StartWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_STARTWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_STARTWINDOW_, true);
//``````
	RegisterEvent(_TYPED_EVENT_UPDATEWINDOW_UI_SHOW_DOWNLOAD,true);         //��ʾ�������UI
	RegisterEvent(_TYPED_EVENT_UPDATEWINDOW_UI_SHOW_NORMAL,true);				  //��ʾ������Ϸ��UI
	RegisterEvent(_TYPED_EVENT_UPDATEWINDOW_BEGIN_DOWNLOAD_ZIPFILE_,true);            // ��ʼ����ZIP��Դ�ļ�
	RegisterEvent(_TYPED_EVENT_UPDATEWINDOW_DOWNLOAD_ZIPFILE_FAILED_,true);           // ����ZIP��Դ�ļ�ʧ��
	RegisterEvent(_TYPED_EVENT_UPDATEWINDOW_DOWNLOAD_ZIPFILE_SUCCESS_,true);          // ����ZIP��Դ�ļ��ɹ�
	RegisterEvent(_TYPED_EVENT_UPDATEWINDOW_DOWNLOAD_ZIPFILE_PROGRESS_,true);         // �������ؽ���
	RegisterEvent(_TYPED_EVENT_UPDATEWINDOW_DOWNLOAD_ZIPFILE_INVALID_,true);         // ZIPУ��ʧ��
	RegisterEvent(_TYPED_EVENT_UPDATEWINDOW_BEGIN_UNZIP_ZIPFILE_,true);               // ��ʼ��ѹZIP��Դ�ļ�
	RegisterEvent(_TYPED_EVENT_UPDATEWINDOW_UNZIP_ZIPFILE_SUCCESS_,true);             // ��ѹZIP��Դ�ɹ�
	RegisterEvent(_TYPED_EVENT_UPDATEWINDOW_UNZIP_ZIPFILE_FAILED_,true);              // ��ѹZIP��Դʧ��
	RegisterEvent(_TYPED_EVENT_UPDATEWINDOW_BEGIN_VERIFY_FILE_,true);                 // ��ʼ�����ļ��ȶ�У��
	RegisterEvent(_TYPED_EVENT_UPDATEWINDOW_VERIFY_FILE_SUCCESS_,true);               // �ļ��ȶ�У��ɹ�
	RegisterEvent(_TYPED_EVENT_UPDATEWINDOW_VERIFY_FILE_FAILED_,true);                // �ļ��ȶ�У��ʧ��
	RegisterEvent(_TYPED_EVENT_UPDATEWINDOW_UI_SHOW_FILECOUNT,true);                //��ʾ�ļ�����
	return IWindow::Init();
}

void StartWindow::_initLayout(){
	//show Ad Bar
	CCDirector::sharedDirector()->getAd()->showAd(true);
	//
	m_pRoot=m_pRootNode;
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSTARTWINDOW,m_pRoot);
	//��ʼ��������
	CProgressInnerBar* cc=(CProgressInnerBar*)NFC_getNode(udPROGRESS,m_pRoot);
	cc->setPercent(0.0f);
}

void StartWindow::_showDownloadControls(bool isshow){
	NFC_showNode(udPROGRESS,m_pRoot,isshow);
	NFC_showNode(udPROGRESS_BG,m_pRoot,isshow);
	NFC_showNode(udPERCENTLABEL,m_pRoot,isshow);
	NFC_showNode(udFILECOUNT,m_pRoot,isshow);
}

void StartWindow::_showNormalControls(bool isshow){
	NFC_showNode(udSERVERBTN,m_pRoot,isshow);
	NFC_showNode(udSERVER_NAME,m_pRoot,isshow);
	NFC_showNode(udSERVER_STATUS,m_pRoot,isshow);
	NFC_showNode(udSERVER_HINT,m_pRoot,isshow);
	NFC_showNode(udENTERBTN,m_pRoot,isshow);
	NFC_showNode(udENTERLABEL,m_pRoot,isshow);
	//
	//�����ʾserver ��ʾ���������
	if (isshow)
	{
		CCNode* hint=NFC_getNode(udSERVER_HINT,m_pRoot);
		assert(hint!=NULL);
		int during=ClientConstDataManager::get_instance2()->getValueByKey(CONST_KEY_START_SHINT_FADE_DURING);
		float during_s=(float)(during*1.0/1000);
		NFC_Action_FadeInAndReverse(hint,during_s,true);
	}
}

void StartWindow::_setFileCount(int filecount,int totalcount){
	char tmp[128];
	sprintf(tmp,SysLangDataManager::get_instance2()->GetSysLangById(654).c_str(),filecount,totalcount);
	NFC_setLabelString(udFILECOUNT,m_pRoot,tmp);
}

void StartWindow::_mapBtn(){
	CCMenu* menu=(CCMenu*)NFC_getNode(udSERVERBTN,m_pRoot);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setTarget(this,menu_selector(StartWindow::On_Click_Event));
	cc->setIDX(udSERVERBTN);
	//
	menu=(CCMenu*)NFC_getNode(udENTERBTN,m_pRoot);
	cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setTarget(this,menu_selector(StartWindow::On_Click_Event));
	cc->setIDX(udENTERBTN);
}

//����Ĭ�ϵķ���������
void StartWindow::_setDefaultServer(){
	//server name
	NFC_setLabelString(udSERVER_NAME,m_pRoot,SERVERINFODATAINFO->getCurServerName());
	//server status
	if (SERVERINFODATAINFO->GetCurServerState()==0)//ά����
	{
		NFC_changeImageForCSprite(udSERVER_STATUS,m_pRoot,0);
	}else{
		if (SERVERINFODATAINFO->GetCurServerLevel()==0)
		{
			//�·�
			NFC_changeImageForCSprite(udSERVER_STATUS,m_pRoot,1);
		}else{
			//��
			NFC_changeImageForCSprite(udSERVER_STATUS,m_pRoot,2);
		}
	}

}

void StartWindow::_setVerson()
{
	char buff[64] = {0};
	sprintf(buff,"V%s",DOTATribeApp::get_instance2()->GetVersion().c_str());
	NFC_setLabelString(udVERSION,m_pRoot,buff);
}

bool StartWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		_initLayout();
		_mapBtn();

		return true;
	} 
	while (false);

	return false;
}

void StartWindow::Tick()
{
	IWindow::Tick();
}

void StartWindow::Destroy()
{
	//hide Ad Bar
	CCDirector::sharedDirector()->getAd()->showAd(false);
	IWindow::Destroy();
}

void StartWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_STARTWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_STARTWINDOW_)
	{
		Destroy();
	}else if(iEventType == _TYPED_EVENT_UPDATEWINDOW_UI_SHOW_DOWNLOAD){
		//��ʾ���ؽ���
		On_UI_Show_Download(paramList);
	}else if(iEventType == _TYPED_EVENT_UPDATEWINDOW_UI_SHOW_NORMAL){
		//��ʾ������Ϸ����
		On_UI_Show_Normal(paramList);
	}else if(iEventType == _TYPED_EVENT_UPDATEWINDOW_BEGIN_DOWNLOAD_ZIPFILE_){
		NFC_setLabelString(udPERCENTLABEL,m_pRoot,SysLangDataManager::get_instance2()->GetSysLangById(644).c_str());
	}else if(iEventType == _TYPED_EVENT_UPDATEWINDOW_DOWNLOAD_ZIPFILE_FAILED_){
		NFC_setLabelString(udPERCENTLABEL,m_pRoot,SysLangDataManager::get_instance2()->GetSysLangById(645).c_str());
	}else if(iEventType == _TYPED_EVENT_UPDATEWINDOW_DOWNLOAD_ZIPFILE_SUCCESS_){
		NFC_setLabelString(udPERCENTLABEL,m_pRoot,SysLangDataManager::get_instance2()->GetSysLangById(646).c_str());
	}else if(iEventType == _TYPED_EVENT_UPDATEWINDOW_DOWNLOAD_ZIPFILE_PROGRESS_){
		//ˢ������~~
		std::string per=paramList.front();
		NFC_setProgressForCProgressInnerBar(udPROGRESS,m_pRoot,(float)atof(per.c_str()));
		char tmp[128];
		sprintf(tmp,"%.2f%%",atof(per.c_str()));
		NFC_setLabelString(udPERCENTLABEL,m_pRoot,tmp);
	}else if(iEventType == _TYPED_EVENT_UPDATEWINDOW_DOWNLOAD_ZIPFILE_INVALID_){
		NFC_setLabelString(udPERCENTLABEL,m_pRoot,SysLangDataManager::get_instance2()->GetSysLangById(647).c_str());
	}else if(iEventType == _TYPED_EVENT_UPDATEWINDOW_BEGIN_UNZIP_ZIPFILE_){
		NFC_setLabelString(udPERCENTLABEL,m_pRoot,SysLangDataManager::get_instance2()->GetSysLangById(648).c_str());
	}else if(iEventType == _TYPED_EVENT_UPDATEWINDOW_UNZIP_ZIPFILE_SUCCESS_){
		NFC_setLabelString(udPERCENTLABEL,m_pRoot,SysLangDataManager::get_instance2()->GetSysLangById(649).c_str());
	}else if(iEventType == _TYPED_EVENT_UPDATEWINDOW_UNZIP_ZIPFILE_FAILED_){
		NFC_setLabelString(udPERCENTLABEL,m_pRoot,SysLangDataManager::get_instance2()->GetSysLangById(650).c_str());
	}else if(iEventType == _TYPED_EVENT_UPDATEWINDOW_BEGIN_VERIFY_FILE_){
		NFC_setLabelString(udPERCENTLABEL,m_pRoot,SysLangDataManager::get_instance2()->GetSysLangById(651).c_str());
	}else if(iEventType == _TYPED_EVENT_UPDATEWINDOW_VERIFY_FILE_SUCCESS_){
		NFC_setLabelString(udPERCENTLABEL,m_pRoot,SysLangDataManager::get_instance2()->GetSysLangById(652).c_str());
	}else if(iEventType == _TYPED_EVENT_UPDATEWINDOW_VERIFY_FILE_FAILED_){
		NFC_setLabelString(udPERCENTLABEL,m_pRoot,SysLangDataManager::get_instance2()->GetSysLangById(653).c_str());
	}else if(iEventType==_TYPED_EVENT_UPDATEWINDOW_UI_SHOW_FILECOUNT){
		std::list<std::string>::iterator it=paramList.begin();
		int filecount=atoi((*it++).c_str());
		int total=atoi((*it).c_str());
		_setFileCount(total-filecount,total);
	}
}


void StartWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
}

void   StartWindow::On_UI_Show_Download(std::list<std::string>& paramList){
	_showNormalControls(false);
	_showDownloadControls(true);
}
void   StartWindow::On_UI_Show_Normal(std::list<std::string>& paramList){
	_showDownloadControls(false);
	_showNormalControls(true);
	_setDefaultServer();
	_setVerson();

}

void StartWindow::On_Click_Event(cocos2d::CCObject* pSender){
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	if (cc->getIDX()==udSERVERBTN)
	{
		//����ѡ����������
		PushEvent(_TYPED_EVENT_SHOW_SELECTSERVERWINDOW_);
	}else if(cc->getIDX()==udENTERBTN){
		//������Ϸ
		SERVERINFODATAINFO->CheckAccountBeforeEnterGame();
	}
}