#ifndef  _DOTATRIBE_UPDATESYSTEM_H_
#define  _DOTATRIBE_UPDATESYSTEM_H_

#include <include/common/Singleton.h>
#include <include/IAntManager.h>
#include <include/mem/DPacket.h>
#include <string>
#include <list>
using  namespace  cobra_win;
using  namespace  miniant;

class UpdateSystem : public miniant::IAntCallbackHandler, public cobra_win::Singleton2<UpdateSystem>
{
private:
	enum{
		kUSuccess=0,
		kUNeedUpdate,
		kUServerNotSupport,
	};
private:
	//������ѹ��Դ��
	void _finishUnzipResource();
public:
	unsigned char ret_;		//0.�ɹ�	1.С�汾����   2.��汾����   3.�汾�ڵ�ǰ��������֧�֣������Խ�����Ϸ<br>
	std::string appUpdateURL_;		//appstore ���ص�ַ
	int totalCount_;	//�����ļ�����
protected:
	miniant::IAntManager* m_pAntManager;     // ���ϸ�������������

protected:
	std::list<Versions> m_AllVersionList;    // �ͻ������а汾��Ϣ�б�

protected:
	int m_UpdateVersionSize;                 // �ͻ��˴����µİ汾��Ϣ����
	std::list<Versions> m_UpdateVersionList; // �ͻ��˴����µİ汾��Ϣ�б�

protected:
	bool m_bHasUpdated; // �Ƿ������

public:
	UpdateSystem();
	virtual ~UpdateSystem();

public:
	/*
		������ϸ�������������
	*/
	miniant::IAntManager* GetAntManager();
	/*
		�Ƿ���Դ������
	*/
	bool  IsHasUpdated();

public:
	bool  Init();
	void  Tick();
	void  Destroy();
	/*
		������ȡ�汾��Ϣ��
	*/
	void decodePacketData(cobra_win::DPacket & packet);

	/*
		����汾��Ϣ
	*/
	void QueryVersionInfo();
	/*
		��ȡ�������Ϣ�Ĳ���
	*/
	void HandleAfterGetVersionInfo();
	/*
		���汾����
	*/
	void HandleCheckVersionAndDownload();

	/*
		��ʼ���߸���
	*/
	void StartUpdateOnline();

	/*
		׼��Appstore����
	*/
	void HandleAppStoreDownload();

	/*
		ȷ����汾����ʱ��download�ļ����Ѿ�ɾ��
	*/
	void ConfirmSandBoxDownloadHasBeenCleared();

public:
	/*
		URL�ı��ļ�����ʧ���¼�����(.txt or .xml)
	*/
	virtual  void  OnURLFileDownLoadFailedHandler(int urlTag, int errorCode){};
	/*
		URL�ı��ļ����سɹ��¼�����(.txt or .xml)
	*/
	virtual  void  OnURLFileDownLoadSucceededHandler(int urlTag, std::string text){}; 
	/*
		URL�ı��ļ����ؽ����¼�����(.txt or .xml)
	*/
	virtual  void  OnURLFileDownLoadProgressHandler(double total, double downloaded){};
public:
	/*
		ZIP�ļ�����ʧ���¼�����
	*/
	virtual  void  OnZipFileDownLoadFailedHandler(int errorCode);
	/*
		ZIP�ļ����سɹ��¼�����
	*/
	virtual  void  OnZipFileDownLoadSucceededHandler(double length);
	/*
		ZIP�ļ����ؽ����¼�����
	*/
	virtual  void  OnZipFileDownLoadProgressHandler(double total, double downloaded);
	/*
		ZIP�ļ�MD5ֵУ��ɹ��¼�����
	*/
	virtual  void  OnVerifyZipFileFailedHandler();
	/*
		ZIP�ļ�MD5ֵУ��ʧ���¼�����
	*/
	virtual  void  OnVerifyZipFileSucceededHandler();
	/*
		ZIP�ļ���ѹ�¼�����
	*/
	virtual  void  OnUnZipStartHandler();
	/*
		ZIP�ļ���ѹʧ���¼�����
	*/
	virtual  void  OnUnZipFailedHandler(int errorCode);
	/*
		ZIP�ļ���ѹ�ɹ��¼�����
	*/
	virtual  void  OnUnZipSucceededHandler();

public:
	//@ָ���ļ�MD5У��ɹ��¼�����
	virtual  void  OnVerifyFileFailedHandler(std::string fileName){};
	//@ָ���ļ�MD5У��ʧ���¼�����
	virtual  void  OnVerifyFileSucceededHandler(){};


	UpdateSystem* GetLuaInstance(){
		return UpdateSystem::get_instance2();
	}
};

#define  UPDATESYSTEM  (UpdateSystem::get_instance2())


#endif
