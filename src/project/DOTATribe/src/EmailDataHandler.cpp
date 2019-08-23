//Name：EmailDataHandler
//Function：邮箱数据
//Written By：尹强

#include "../include/EmailDataHandler.h"
#include "../include/EmailPacket.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../Include/SysLangDataManager.h"
#include "../include/NFControlsManager.h"


/************************************************************************/
/*	 玩家邮箱信息的返回                                                  */
/************************************************************************/
EmailListDataObject::EmailListDataObject()
{
	count_ = 0;			//数量<br>
	type_ = 0;	//类型 0物品 1金钱<br>
	catogory = 0; //物品类型
	itemId_ = 0;			//物品ID<br>
	templateId_ = 0;	//物品模板ID<br>
	quality_ = 0;		//品质<br>
	iconId_ = 0;			//图标ID<br>
}

EmailListDataObject::~EmailListDataObject()
{
	count_ = 0;			//数量<br>
	type_ = 0;	//类型 0物品 1金钱<br>
	catogory = 0; //物品类型
	itemId_ = 0;			//物品ID<br>
	templateId_ = 0;	//物品模板ID<br>
	quality_ = 0;		//品质<br>
	iconId_ = 0;			//图标ID<br>
}



/************************************************************************/
/*	 查看邮件链表                                                     、 */
/************************************************************************/
EmailListData::EmailListData()
{
	mailID_ = 0;
	type_ = 0;		// 类型 0系统 1个人<br>
	hasread = 0;			//  是否读过 0未读1已读<br>
	title_ = "";			//  发件人ID<br>
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
	id_ = 0;		//收件人ID<br>	没有则传-1
	targetName_="";	//收件人名称<br>
	title_="";		//标题<br>
	content_="";		//内容<br>
	attachmentCount_=0;	//附件数量<br>
	attlist_.clear();		//附件列表
}
EmailWriteData::~EmailWriteData()
{

}





/************************************************************************/
/*   查看邮件信息                                                        */
/************************************************************************/
EmailInfoData::EmailInfoData()
{
	mailID_ = 0;
	type_ = 0;		// 类型 0系统 1个人<br>
	hasread = 0;			//  是否读过 0未读1已读<br>
	sourceId = 0;			//  发件人ID<br>
	sourceName = "";			//  发件人名称<br>
	time =  "";		//  发送时间<br>
	title =  "";			//  标题<br>
	content =  "";			//  内容<br>
	attachmentCount = 0;		//  附件数量<br>
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
	//标题

	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	title.assign(tmpChar);
	delete []tmpChar;
	tmpChar = NULL;

	packet>>sourceId;

	//发件人名称 sourceName

	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	sourceName.assign(tmpChar);
	delete []tmpChar;
	tmpChar = NULL;

	//发送时间

	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	time.assign(tmpChar);
	delete []tmpChar;
	tmpChar = NULL;

	//内容
	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	content.assign(tmpChar);
	delete []tmpChar;
	tmpChar = NULL;

	//附件量
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
	写邮件
*/
void EmailDataHandler::WriteEmail(EmailWriteData* emailData){
	CSEmailSendPacket packet(emailData);
	packet.Send();
	//显示等待界面
	NFC_showCommunicationWating(true);
}

	/*
		写邮件反馈
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
		查询邮件
	*/
void EmailDataHandler::QueryEmail(){
	CSEmailListPacket packet;
	packet.Send();
	//显示等待界面
	if (!m_isGettingAtt)
		NFC_showCommunicationWating(true);
	else{
		m_isGettingAttSending = true;
	}
}

	/*
		查询邮件反馈
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
	//唤出界面
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
		重载系统与个人邮件列表	
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
	一键收取全部附件步骤
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
	一键获取附件	
*/
void EmailDataHandler::GetATT(int mailID){
	CSGetEmailAttPacket packet(mailID);
	packet.Send();
	m_EmilId = mailID;
	if(!m_isGettingAtt){
		//显示等待界面
		NFC_showCommunicationWating(true);
	}
	else{
		LOGGERSYSTEM->LogDebug("GetAllATT Index:%d GetATT",m_getAllAttIndex);
		m_isGettingAttSending = true;
	}
}
/*
	一键获取附件反馈
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
	* 删除邮件请求<br>
*/
void EmailDataHandler::RemoveEmail(int mailId,int type){
	CSRemoveEmailPacket packet(mailId);
	packet.Send();
	m_EmilId = mailId;
	m_EmailType = type;
	//显示等待界面
	NFC_showCommunicationWating(true);
}
/*
	*删除邮件返回<br>
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
	点击查看邮件
*/
void EmailDataHandler::CheckEmailToServer(int emailid)
{
	CSCheckEmailPacket  packet(emailid);
	packet.Send();
	
	//显示等待界面
	//如果是在一键收取的过程中，则不对等待界面操作
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
	接收邮件信息
*/
void EmailDataHandler::ReceiveCheckEmailInfo(cobra_win::DPacket & packet)
{
	if(!m_pEmailInfo)
	{
		return;
	}

	m_pEmailInfo->decodePacketData(packet);

	//如果是在一键收取的过程中，不对界面进行操作
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
	清理数据
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
	m_vecSystemEmail.clear();	//系统邮件列表
	std::vector<EmailListData*>::iterator pos_begin1 = m_vecPersonalEmail.begin();
	std::vector<EmailListData*>::iterator pos_end1 = m_vecPersonalEmail.end();
	for (pos_begin1;pos_begin1 != pos_end1;pos_begin1++)
	{
		delete (*pos_begin1);
		(*pos_begin1) = NULL;
	}
	m_vecPersonalEmail.clear();	//个人邮件列表
}

/*
	删除系统链表信件
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
	删除个人链表信件
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
	获得当前未读系统读信件
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
	获得当前未读个人信件
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