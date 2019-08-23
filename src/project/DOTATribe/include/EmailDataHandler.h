//Name��EmailDataHandler
//Function����������
//Written By����ǿ

#ifndef _DOTATRIBE_EmailDataHandler_H_
#define _DOTATRIBE_EmailDataHandler_H_

#include <include/common/Singleton.h>
#include "../include/IDataHandler.h"
#include <include/mem/DPacket.h>
#include <list>
#include <vector>
#include <string>


class EmailListDataObject{
public:
	EmailListDataObject();
	~EmailListDataObject();

public:
	int count_;			//����<br>
	unsigned char type_;	//���� 0��Ʒ 1��Ǯ 2���� 3��ʯ 4���� 5���� <br>
	unsigned char catogory; //��Ʒ����
	int itemId_;			//��ƷID<br>
	int templateId_;	//��Ʒģ��ID<br>
	unsigned char quality_;		//Ʒ��<br>
	int iconId_;			//ͼ��ID<br>
};

enum{
	kSYSTEM = 0,
	kPERSONAL,
};

enum
{
	_TYPE_NOT_READ_ = 0,   //δ���ż�
	_TYPE_ALREADY_READ_,   //�Ѷ��ż�
	
};

/**
	 * ����ʼ���Ϣ����<br>
	 * short count ����<br>
	 * for(count){<br>
	 * int id<br>
	 * byte type ���� 0ϵͳ 1����<br>
	 * byte hasread �Ƿ���� 0δ��1�Ѷ�<br>
	 * String title ����<br>
	 * }<br>
	 */
class EmailListData{
public:
	EmailListData();
	~EmailListData();
public:
		int mailID_;						//�ʼ�ID
		unsigned char type_;		//����<br>
		unsigned char hasread;		//�Ƿ���� 0δ��1�Ѷ�<br>
		std::string title_;						//����<br>
public:
	void decodePacketData(cobra_win::DPacket & packet);
};

/**
	 * �����ʼ�����<br>
	 * int id �ռ���ID<br>
	 * String targetName �ռ�������<br>
	 * String title ����<br>
	 * String content ����<br>
	 * byte attachmentCount ��������<br>
	 * for(attachmentCount){<br>
	 * byte type ���� 0��Ʒ 1��Ǯ 2����<br>
	 * int amount ����<br>
	 * int itemId ��ƷID<br>
	 * int templateId ģ��ID<br>
	 * }<br>
	 */
class EmailWriteDataObject{
public:
	 unsigned char type_;	//���� 0��Ʒ 1��Ǯ 2����<br>
	 int amount_;				//����<br>
	 int itemId_;					//��ƷID<br>
	 int templateId_;			//ģ��ID<br>
};

class EmailWriteData{
public:
	EmailWriteData();
	~EmailWriteData();
public:
	 int id_;		//�ռ���ID<br>	û����-1
	 std::string targetName_;	//�ռ�������<br>
	 std::string  title_;		//����<br>
	 std::string content_;		//����<br>
	 unsigned char attachmentCount_;	//��������<br>
	 std::list<EmailWriteDataObject*> attlist_;		//�����б�
};


/**
	 * �鿴�ʼ�����<br>
	 * int id<br>
	 * byte type ���� 0ϵͳ 1����<br>
	 * byte hasread �Ƿ���� 0δ��1�Ѷ�<br>
	 * String title ����<br>
	 * int sourceId ������ID<br>
	 * String sourceName ����������<br>
	 * String time ����ʱ��<br>
	 * String content ����<br>
	 * byte attachmentCount ��������<br>
	 * for(attachmentCount){<br>
	 * byte type ���� 0��Ʒ 1��Ǯ<br>
	 * int count ����<br>
	 * if(type == ��Ʒ){<br>
	 * byte catogory ��Ʒ����<br>
	 * int itemId ��ƷID<br>
	 * int templateId ��Ʒģ��ID<br>
	 * byte quality Ʒ��<br>
	 * int iconId ͼ��ID<br>
	 * }<br>
	 * }<br>
	 */

/************************************************************************/
/*   �鿴�ʼ���Ϣ                                                        */
/************************************************************************/
class EmailInfoData
{
public:
	EmailInfoData();
	~EmailInfoData();
public:
	int mailID_;
	unsigned char type_;			// ���� 0ϵͳ 1����<br>
	unsigned char hasread;			//  �Ƿ���� 0δ��1�Ѷ�<br>
	std::string title;			//  ����<br>
	int sourceId;					//  ������ID<br>
	std::string sourceName;			//  ����������<br>
	std::string time;			//  ����ʱ��<br>
	std::string content;			//  ����<br>
	unsigned char attachmentCount;			//  ��������<br>
	std::vector<EmailListDataObject*> attachmentlist;
public:
	void decodePacketData(cobra_win::DPacket & packet);

	void ClearAttachmentList();
};

/************************************************************************/
/*   �������ݾ��                                                        */
/************************************************************************/
enum{
	_ENUM_UPDATE_EMAILLIST_TYPE_ = 0,			//�����ʼ��б�
	_ENUM_UPDATE_EMAILINFO_TYPE_,				//�����ʼ�����
	_ENUM_UPDATE_GETATTACHMENTINFO_TYPE_,		//��ø���֮�����
	_ENUM_UPDATE_SENDEMAIL_TYPE_,				//�����ʼ�����
	_ENUM_UPDATE_EMAILREMOVE_TYPE_				//ɾ���ʼ�

};

class EmailDataHandler : public IDataHandler, public cobra_win::Singleton2<EmailDataHandler>{
public:
	std::vector<EmailListData*> m_vecSystemEmail;	//ϵͳ�ʼ��б�
	std::vector<EmailListData*> m_vecPersonalEmail;	//�����ʼ��б�

	EmailInfoData *m_pEmailInfo;
private:
	int m_EmilId;			//Ҫ�ʼ���id
	int m_EmailType;		//�ʼ�����
public:
	bool m_isGettingAtt;			//�Ƿ����ڽ���һ����ȡ����
	bool m_isGettingAttSending;		//�Ƿ����ڵȴ��ظ�
	int m_getAllAttIndex;			//
	int m_getAllAttPerStep;			//Check 0 Get 1
	int m_HasAttMailNum;			//
	bool m_IsGetAllMaillist;		//�Ƿ�����Ϊһ����ȡ��������ȡ�ʼ��б�
public:
	EmailDataHandler();
	virtual ~EmailDataHandler();
public:
	void decodePacketData(cobra_win::DPacket & packet);
	virtual void handlePacket(IPacket* packet);
	virtual void onDestroy();
	virtual bool init();

	/*
		һ����ȡȫ���ʼ�����
	*/
	void GetAllATTStep();
	void GetAllAttStepBegin();
	void GetAllATTStepDone();
	void GetAllStop();
	/*
		��������
	*/
	void ClearEmailDataList();

	/*
		����ϵͳ������ʼ��б�	
	*/
	void reloadSystemAndPersonalEmail();
	/*
		д�ʼ�
	*/
	void WriteEmail(EmailWriteData* emailData);
	/*
		д�ʼ�����
	*/
	void FeedBack_WriteEmail(bool result);

	/*
		��ѯ�ʼ�
	*/
	void QueryEmail();
	/*
		��ѯ�ʼ�����
	*/
	void FeedBack_QueryEmail();

	/*
		һ����ȡ����	
	*/
	void GetATT(int mailID);
	/*
		һ����ȡ��������
	*/
	void FeedBack_GetATT(bool result);
	/*
		* ɾ���ʼ�����<br>
	*/
	void RemoveEmail(int mailId,int type);
	/*
		*ɾ���ʼ�����<br>
	*/
	void FeedBack_RemoveEmail(bool result);

	/*
		����鿴�ʼ�
	*/
	void CheckEmailToServer(int emailid);

	/*
		�����ʼ���Ϣ
	*/
	void ReceiveCheckEmailInfo(cobra_win::DPacket & packet);
private:
	/*
		ɾ��ϵͳ�����ż�
	*/
	void RemoveSystemEmailList();
	/*
		ɾ�����������ż�
	*/
	void RemovePersonalEmailList();
public:
	/*
		��õ�ǰδ��ϵͳ���ż�
	*/
	int GetSystemEmailUnreadNum();
	/*
		��õ�ǰδ�������ż�
	*/
	int GetProsonEmailUnreadNum();
};
#define EMAILDATAHANDLER (EmailDataHandler::get_instance2())

#endif

