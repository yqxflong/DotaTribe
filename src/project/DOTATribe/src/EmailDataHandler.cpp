//Name��EmailDataHandler
//Function����������
//Written By����ǿ

#include "../include/EmailDataHandler.h"
#include "../include/EmailPacket.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../Include/SysLangDataManager.h"
#include "../include/NFControlsManager.h"


/************************************************************************/
/*	 ���������Ϣ�ķ���                                                  */
/************************************************************************/
EmailListDataObject::EmailListDataObject()
{
	count_ = 0;			//����<br>
	type_ = 0;	//���� 0��Ʒ 1��Ǯ<br>
	catogory = 0; //��Ʒ����
	itemId_ = 0;			//��ƷID<br>
	templateId_ = 0;	//��Ʒģ��ID<br>
	quality_ = 0;		//Ʒ��<br>
	iconId_ = 0;			//ͼ��ID<br>
}

EmailListDataObject::~EmailListDataObject()
{
	count_ = 0;			//����<br>
	type_ = 0;	//���� 0��Ʒ 1��Ǯ<br>
	catogory = 0; //��Ʒ����
	itemId_ = 0;			//��ƷID<br>
	templateId_ = 0;	//��Ʒģ��ID<br>
	quality_ = 0;		//Ʒ��<br>
	iconId_ = 0;			//ͼ��ID<br>
}



/************************************************************************/
/*	 �鿴�ʼ�����                                                     �� */
/************************************************************************/
EmailListData::EmailListData()
{
	mailID_ = 0;
	type_ = 0;		// ���� 0ϵͳ 1����<br>
	hasread = 0;			//  �Ƿ���� 0δ��1�Ѷ�<br>
	title_ = "";			//  ������ID<br>
}
EmailListData::~EmailListData()
{
	
}

void EmailListData::decodePacketData(cobra_win::DPacket & packet){
	unsigned short tmp_len;
	char *tmpChar=NULL;

	packet>>mailID_;
	packet>>type_;
	packet>>hasread;

	//title
	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	title_.assign(tmpChar);

	delete []tmpChar;
	tmpChar = NULL;
}

EmailWriteData::EmailWriteData()
{
	id_ = 0;		//�ռ���ID<br>	û����-1
	targetName_="";	//�ռ�������<br>
	title_="";		//����<br>
	content_="";		//����<br>
	attachmentCount_=0;	//��������<br>
	attlist_.clear();		//�����б�
}
EmailWriteData::~EmailWriteData()
{

}





/************************************************************************/
/*   �鿴�ʼ���Ϣ                                                        */
/************************************************************************/
EmailInfoData::EmailInfoData()
{
	mailID_ = 0;
	type_ = 0;		// ���� 0ϵͳ 1����<br>
	hasread = 0;			//  �Ƿ���� 0δ��1�Ѷ�<br>
	sourceId = 0;			//  ������ID<br>
	sourceName = "";			//  ����������<br>
	time =  "";		//  ����ʱ��<br>
	title =  "";			//  ����<br>
	content =  "";			//  ����<br>
	attachmentCount = 0;		//  ��������<br>
	attachmentlist.clear();
}
EmailInfoData::~EmailInfoData()
{
	attachmentlist.clear();
}

void EmailInfoData::decodePacketData(cobra_win::DPacket & packet)
{
	ClearAttachmentList();

	unsigned short tmp_len;
	char *tmpChar=NULL;
	//
	packet>>mailID_;
	packet>>type_;
	packet>>hasread;
	//����

	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	title.assign(tmpChar);
	delete []tmpChar;
	tmpChar = NULL;

	packet>>sourceId;

	//���������� sourceName

	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	sourceName.assign(tmpChar);
	delete []tmpChar;
	tmpChar = NULL;

	//����ʱ��

	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	time.assign(tmpChar);
	delete []tmpChar;
	tmpChar = NULL;

	//����
	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	content.assign(tmpChar);
	delete []tmpChar;
	tmpChar = NULL;

	//������
	packet>>attachmentCount;
	for (int i=0;i<attachmentCount;i++)
	{
		EmailListDataObject* ddo = new EmailListDataObject();
		
		packet>>ddo->type_;
		packet>>ddo->count_;
		
		if (ddo->type_ == 0)
		{
			packet>>ddo->catogory;
			packet>>ddo->itemId_;
			packet>>ddo->templateId_;
			packet>>ddo->quality_;
			packet>>ddo->iconId_;
		}
		
		attachmentlist.push_back(ddo);
	}
}

void EmailInfoData::ClearAttachmentList()
{
	std::vector<EmailListDataObject*>::iterator pos_begin = attachmentlist.begin();
	std::vector<EmailListDataObject*>::iterator pos_end = attachmentlist.end();

	for (pos_begin;pos_begin != pos_end;pos_begin++)
	{
		if ((*pos_begin) != NULL)
		{
			delete (*pos_begin);
			(*pos_begin) = NULL;
		}
	}
	attachmentlist.clear();
}

EmailDataHandler::EmailDataHandler(){
	m_vecSystemEmail.clear();
	m_vecPersonalEmail.clear();
	m_pEmailInfo = NULL;
	m_EmilId = 0;
	m_EmailType = 0;
	m_isGettingAtt = false;
	m_isGettingAttSending = false;
	m_getAllAttIndex = 0;
	m_getAllAttPerStep = 0;
	m_HasAttMailNum = 0;
	m_IsGetAllMaillist = false;
}
EmailDataHandler::~EmailDataHandler(){
	if (m_pEmailInfo!=NULL)
		delete m_pEmailInfo;
	m_pEmailInfo = NULL;
}

void EmailDataHandler::decodePacketData(cobra_win::DPacket & packet){
	ClearEmailDataList();
	unsigned short count;
	packet>>count;
	for (int i=0;i<count;i++)
	{
		EmailListData* dd = new EmailListData();
		dd->decodePacketData(packet);

		if (dd->type_== 0)
			m_vecSystemEmail.push_back(dd);
		else
			m_vecPersonalEmail.push_back(dd);
		
	}
}

/*
	д�ʼ�
*/
void EmailDataHandler::WriteEmail(EmailWriteData* emailData){
	CSEmailSendPacket packet(emailData);
	packet.Send();
	//��ʾ�ȴ�����
	NFC_showCommunicationWating(true);
}

	/*
		д�ʼ�����
	*/
void EmailDataHandler::FeedBack_WriteEmail(bool result){

	NFC_showCommunicationWating(false);
	if (result)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_WRITEEMAILWINDOW_);
		std::string str = SysLangDataManager::get_instance2()->GetSysLangById(4020);
		NFC_showErrorTips(str);
	}
}

	/*
		��ѯ�ʼ�
	*/
void EmailDataHandler::QueryEmail(){
	CSEmailListPacket packet;
	packet.Send();
	//��ʾ�ȴ�����
	if (!m_isGettingAtt)
		NFC_showCommunicationWating(true);
	else{
		m_isGettingAttSending = true;
	}
}

	/*
		��ѯ�ʼ�����
	*/
void EmailDataHandler::FeedBack_QueryEmail(){
	if (m_IsGetAllMaillist)
	{
		std::string str = _to_event_param_(_ENUM_UPDATE_EMAILLIST_TYPE_);
		EVENTSYSTEM->PushEvent(_TYPEF_EVENT_UPDATE_EMAILWINDOW_,str);
		NFC_showCommunicationWating(false);
		m_IsGetAllMaillist = false;
		GetAllAttStepBegin();
		return;
	}
	//��������
	if (m_isGettingAtt)
	{
		m_isGettingAttSending = false;
		m_isGettingAtt = false;
		m_getAllAttIndex = -1;
		m_getAllAttPerStep = 0;
		if (m_HasAttMailNum == 0){
			NFC_showMessageBox(kDEFAULT,SysLangDataManager::get_instance2()->GetSysLangById(5019));
		}
		m_HasAttMailNum = 0;
		std::string str = _to_event_param_(_ENUM_UPDATE_EMAILLIST_TYPE_);
		EVENTSYSTEM->PushEvent(_TYPEF_EVENT_UPDATE_EMAILWINDOW_,str);
		NFC_showCommunicationWating(false);
		return;
	}
	EVENTSYSTEM->PushEvent(_TYPEF_EVENT_SHOW_EMAILWINDOW_);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_FADEOUT_HOMEWINDOW_);
	std::string str = _to_event_param_(_ENUM_UPDATE_EMAILLIST_TYPE_);
	EVENTSYSTEM->PushEvent(_TYPEF_EVENT_UPDATE_EMAILWINDOW_,str);
	NFC_showCommunicationWating(false);

}

	/*
		����ϵͳ������ʼ��б�	
	*/
void EmailDataHandler::reloadSystemAndPersonalEmail(){
	
	//m_vecSystemEmail.clear();
	//m_vecPersonalEmail.clear();
	////
	//std::list<EmailListData*>::iterator it=m_listEmail.begin();
	//std::list<EmailListData*>::iterator it_end=m_listEmail.end();
	//for (;it!=it_end;it++)
	//{
	//	EmailListData* dd=*it;
	//	if (dd->type_== 0)
	//		m_vecSystemEmail.push_back(dd);
	//	else
	//		m_vecPersonalEmail.push_back(dd);
	//}
}
/*
	һ����ȡȫ����������
*/
void EmailDataHandler::GetAllATTStep(){
	if (m_isGettingAttSending || !m_isGettingAtt)
		return;
	LOGGERSYSTEM->LogDebug("AllATTStep: %d, %d",m_getAllAttIndex,m_getAllAttPerStep);
	if (m_vecSystemEmail.size() <= m_getAllAttIndex){
		GetAllATTStepDone();
		return;
	}
	if (m_getAllAttPerStep == 0)
	{
		CheckEmailToServer(m_vecSystemEmail[m_getAllAttIndex]->mailID_);
	}
	else{
		GetATT(m_vecSystemEmail[m_getAllAttIndex]->mailID_);
	}
}
void EmailDataHandler::GetAllATTStepDone(){
	m_isGettingAtt = false;
	QueryEmail();
}

void EmailDataHandler::GetAllStop()
{
	m_isGettingAtt = false;
}
void EmailDataHandler::GetAllAttStepBegin(){
	m_isGettingAtt = true;
	m_isGettingAttSending = false;
	m_getAllAttIndex = 0;
	m_getAllAttPerStep = 0;
	m_HasAttMailNum = 0;
	NFC_showCommunicationWating(true);
}

/*
	һ����ȡ����	
*/
void EmailDataHandler::GetATT(int mailID){
	CSGetEmailAttPacket packet(mailID);
	packet.Send();
	m_EmilId = mailID;
	if(!m_isGettingAtt){
		//��ʾ�ȴ�����
		NFC_showCommunicationWating(true);
	}
	else{
		LOGGERSYSTEM->LogDebug("GetAllATT Index:%d GetATT",m_getAllAttIndex);
		m_isGettingAttSending = true;
	}
}
/*
	һ����ȡ��������
*/
void EmailDataHandler::FeedBack_GetATT(bool result){
	if(result)
	{
		if(!m_isGettingAtt){
			NFC_showCommunicationWating(false);
			FeedBack_RemoveEmail(result);
		}
		else{
			m_isGettingAttSending = false;
			m_getAllAttIndex++;
			m_getAllAttPerStep = 0;
		}
	}
}

/*
	* ɾ���ʼ�����<br>
*/
void EmailDataHandler::RemoveEmail(int mailId,int type){
	CSRemoveEmailPacket packet(mailId);
	packet.Send();
	m_EmilId = mailId;
	m_EmailType = type;
	//��ʾ�ȴ�����
	NFC_showCommunicationWating(true);
}
/*
	*ɾ���ʼ�����<br>
*/
void EmailDataHandler::FeedBack_RemoveEmail(bool result){
	NFC_showCommunicationWating(false);
	if(result)
	{
		if (m_EmailType == 0)
		{
			RemoveSystemEmailList();
		}
		else if(m_EmailType == 1)
		{
			RemovePersonalEmailList();
		}
		std::string str = _to_event_param_(_ENUM_UPDATE_EMAILREMOVE_TYPE_);
		EVENTSYSTEM->PushEvent(_TYPEF_EVENT_UPDATE_EMAILWINDOW_,str);
	}
}

/*
	����鿴�ʼ�
*/
void EmailDataHandler::CheckEmailToServer(int emailid)
{
	CSCheckEmailPacket  packet(emailid);
	packet.Send();
	
	//��ʾ�ȴ�����
	//�������һ����ȡ�Ĺ����У��򲻶Եȴ��������
	if(!m_isGettingAtt)
	{
		NFC_showCommunicationWating(true);
	}
	else{
		LOGGERSYSTEM->LogDebug("GetAllATT Index:%d CheckEmailToServer",m_getAllAttIndex);
		m_isGettingAttSending = true;
	}
}

/*
	�����ʼ���Ϣ
*/
void EmailDataHandler::ReceiveCheckEmailInfo(cobra_win::DPacket & packet)
{
	if(!m_pEmailInfo)
	{
		return;
	}

	m_pEmailInfo->decodePacketData(packet);

	//�������һ����ȡ�Ĺ����У����Խ�����в���
	if(!m_isGettingAtt){
		NFC_showCommunicationWating(false);
		std::string str = _to_event_param_(_ENUM_UPDATE_EMAILINFO_TYPE_);
		EVENTSYSTEM->PushEvent(_TYPEF_EVENT_UPDATE_EMAILWINDOW_,str);
	}
	else{
		m_isGettingAttSending = false;
		if (m_pEmailInfo->attachmentCount > 0){
			m_getAllAttPerStep = 1;
			m_HasAttMailNum++;
		}
		else{
			m_getAllAttIndex++;
		}
	}
}

void EmailDataHandler::handlePacket(IPacket* packet)
{

}
void EmailDataHandler::onDestroy()
{
	ClearEmailDataList();
	m_EmilId = 0;
	m_EmailType = 0;
	m_isGettingAtt = false;
	m_isGettingAttSending = false;
	m_getAllAttIndex = 0;
	m_getAllAttPerStep = 0;
	m_HasAttMailNum = 0;
	m_IsGetAllMaillist = false;
	m_pEmailInfo->ClearAttachmentList();
}
bool EmailDataHandler::init()
{
	m_pEmailInfo = new EmailInfoData();
	return true;
}

/*
	��������
*/
void EmailDataHandler::ClearEmailDataList()
{
	std::vector<EmailListData*>::iterator pos_begin = m_vecSystemEmail.begin();
	std::vector<EmailListData*>::iterator pos_end = m_vecSystemEmail.end();
	for (pos_begin;pos_begin != pos_end;pos_begin++)
	{
		delete (*pos_begin);
		(*pos_begin) = NULL;
	}
	m_vecSystemEmail.clear();	//ϵͳ�ʼ��б�
	std::vector<EmailListData*>::iterator pos_begin1 = m_vecPersonalEmail.begin();
	std::vector<EmailListData*>::iterator pos_end1 = m_vecPersonalEmail.end();
	for (pos_begin1;pos_begin1 != pos_end1;pos_begin1++)
	{
		delete (*pos_begin1);
		(*pos_begin1) = NULL;
	}
	m_vecPersonalEmail.clear();	//�����ʼ��б�
}

/*
	ɾ��ϵͳ�����ż�
*/
void EmailDataHandler::RemoveSystemEmailList()
{
	std::vector<EmailListData*>::iterator pos_begin = m_vecSystemEmail.begin();
	std::vector<EmailListData*>::iterator pos_end = m_vecSystemEmail.end();
	for (pos_begin;pos_begin != pos_end;pos_begin++)
	{
		if ((*pos_begin)->mailID_ == m_EmilId )
		{
			delete (*pos_begin);
			(*pos_begin) = NULL;
			m_vecSystemEmail.erase(pos_begin);
			break;
		}
	}
}
/*
	ɾ�����������ż�
*/
void EmailDataHandler::RemovePersonalEmailList()
{
	std::vector<EmailListData*>::iterator pos_begin = m_vecPersonalEmail.begin();
	std::vector<EmailListData*>::iterator pos_end = m_vecPersonalEmail.end();
	for (pos_begin;pos_begin != pos_end;pos_begin++)
	{
		if ((*pos_begin)->mailID_ == m_EmilId)
		{
			delete (*pos_begin);
			(*pos_begin) = NULL;
			m_vecPersonalEmail.erase(pos_begin);
			break;
		}
	}
}

/*
	��õ�ǰδ��ϵͳ���ż�
*/
int EmailDataHandler::GetSystemEmailUnreadNum()
{
	std::vector<EmailListData*>::iterator pos_begin = m_vecSystemEmail.begin();
	std::vector<EmailListData*>::iterator pos_end = m_vecSystemEmail.end();
	int num = 0;
	for (pos_begin;pos_begin != pos_end;pos_begin++)
	{
		if ((*pos_begin)->hasread == 0)
		{
			num++;
		}
	}
	return num;
}
/*
	��õ�ǰδ�������ż�
*/
int EmailDataHandler::GetProsonEmailUnreadNum()
{
	std::vector<EmailListData*>::iterator pos_begin = m_vecPersonalEmail.begin();
	std::vector<EmailListData*>::iterator pos_end = m_vecPersonalEmail.end();
	int num = 0;
	for (pos_begin;pos_begin != pos_end;pos_begin++)
	{
		if ((*pos_begin)->hasread == 0)
		{
			num++;
		}
	}
	return num;
}