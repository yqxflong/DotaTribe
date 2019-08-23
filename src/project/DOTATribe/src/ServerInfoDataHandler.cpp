//Name��	ServerInfoDataHandler
//Function����Ϸ��½������̿�����
//Written By����ǿ

#include <cocos2d.h>
#include "../include/DOTATribeApp.h"
#include "../include/NFControlsManager.h"
#include "../include/NFToolController.h"
#include "../include/ServerListPacket.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/NetSystem.h"
#include "../include/UpdateSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/CSEnterGamePacket.h"
#include "../include/MessageBoxWindow.h"
#include "../include/LoginProcedure.h"
#include "../include/VariableSystem.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/EngineSystem.h"
#include "../include/CSQuickAccountRegisterPacket.h"
#include "../include/CSRolelistPacket.h"
#include "../include/CreateRoleProcedure.h"
#include "../include/CSRegisterAccountPacket.h"
#include "../include/IProcedure.h"
#include "../include/config_HomeWindow.h"
#include "../include/LoginPacket.h"
#include "../include/LocalPlayerDataManager.h"
#include "../include/LimitedActivityHandler.h"
#include "../include/PayGoodsControlDataHandler.h"
#include "../include/HeartBeatDataHandler.h"
#include "../include/DebugerSystem.h"
#include "../include/NetDebuger.h"
#include "../include/TimeSystem.h"
#include "../include/NoticeGatewayPacket.h"
#include "../include/CheckOpenFun.h"
#include "../include/RoleInfoDataHandler.h"

using namespace std;
using  namespace  cocos2d;

//#############��½���ؽ������############
static int LOGIN_RESULT_SUCCESS=0;	//��½�ɹ�<br>
static int LOGIN_RESULT_ERROR_1=1;//����������<br>
static int LOGIN_RESULT_ERROR_2=2;//�û�������<br>
static int LOGIN_RESULT_ERROR_3=3;//�������<br>
static int LOGIN_RESULT_ERROR_4=4;//��������<br>
static int LOGIN_RESULT_ERROR_5=5;//91Session���ڣ����µ�½<br>
static int LOGIN_RESULT_ERROR_99=99;//��֤�������쳣<br>

ServerInfoDataHandler::ServerInfoDataHandler(){
	m_nCurGameStatus=_TYPE_LOGIN_STATE_UNKOWN_;
	m_nUserType=kSI_ATYPE_STANDBY;
	m_Key = 0;
	m_RoleIdlist.clear();
	m_Rolenum =0;
	GSListHandler_ = new GameServerListHandler();
	m_isBNoticeTab = false;
	m_isSelServerWindow=false;
	CurSendHttpPacketType_=_HTTP_STATE_UNKNOWN_;
	m_bIsNewRole = 0;
}

ServerInfoDataHandler::~ServerInfoDataHandler(){
	delete GSListHandler_;		//delete
	GSListHandler_=0;
}

bool ServerInfoDataHandler::init(){
	SetLoginSdkDelegate();
	//ע�������������ʱ�¼�
	EVENTSYSTEM->RegisterEventHandler(_TYPED_EVENT_COMMUNICATION_TIMEOUT_,OnEventServerRequest);

	return true;
}

	/*
		����������ʱ�¼�
	*/
void ServerInfoDataHandler::OnEventServerRequest(int iEventType, std::string owerData, std::list<std::string>& paramList){
	if (DOTATribeApp::get_instance2()->IsLoginProcedureAsActiveProcedure()){
		std::string timeOutStr=SysLangDataManager::get_instance2()->GetSysLangById(15); 
		NFC_showErrorTips_2(timeOutStr);
		ServerInfoDataHandler::get_instance2()->DisconnectGameServer_Normal();
	}else{
		ServerInfoDataHandler::get_instance2()->ForceDisconnect();
	}
}

/*
	��ȡLogin������
*/
LoginParams ServerInfoDataHandler::_getLoginParams(){
	LoginParams param;
	param.clientType_=Get_Device_OS();
	param.deviceId_=Get_Device_ID();
	param.deviceSystem_=Get_Device_OS_Version();
	param.MACAddress_=Get_Device_Mac();
	param.version_=Get_GAME_Version();
	param.telecomOperator_=Get_Device_telecomOperator();
	param.AppendParam_=Get_Other_Param();
	param.isHacked_=Get_Hacked();

	param.sdkParam = GetSDKLoginParam();
	param.gameParam = GetGameLoginParam();

	//������20140115
	param.channelId_ = Get_Channel_ID();
	return param;
}

void ServerInfoDataHandler::onDestroy()
{
	m_RoleIdlist.clear();
	m_FontStyleIdMap.clear();
	m_ContentVector.clear();
	m_FunctionDatas.clear();
	EVENTSYSTEM->UnRegisterEventHandler(_TYPED_EVENT_COMMUNICATION_TIMEOUT_,OnEventServerRequest);
}
/**
         * �������б���<br>
         * short count ����<br>
         * for(count){<br>
         * int id ������ID<br>
         * String name ����������<br>
         * String ip ������IP<br>
         * int port �������˿�<br>
         * byte state ״̬<br>
         * byte level �Ƽ�����  <br>
         * }<br>
         */
void ServerInfoDataHandler::decodePacketData(cobra_win::DPacket & packet){
	SERVERINFODATAINFO->GSListHandler_->ClearServerInfoList();
	unsigned short tmpLen=0;
	char *tmpChar = 0;
	unsigned short count = 0;
	packet>>count;
	for (int i=0;i <count;i++)
	{
		GameServerdata tempServer;
		packet>>tempServer.id_;
		if (i==0)
			tempServer.title = _TYPE_TITLE_ALL;
//����������
		NFC_ParsePacketString(packet,tempServer.name_);
//������IP
		NFC_ParsePacketString(packet,tempServer.ip_);
//~~~
		packet>>tempServer.port_;
		packet>>tempServer.state_;
		packet>>tempServer.level_;
		//
		SERVERINFODATAINFO->GSListHandler_->m_ServerInfoList.push_back(tempServer);
	}
}

const GameServerdata& ServerInfoDataHandler::ByIndexServerInfo(int index)
{
	std::list<GameServerdata>::iterator pos = SERVERINFODATAINFO->GSListHandler_->m_ServerInfoList.begin();
	std::list<GameServerdata>::iterator posend = SERVERINFODATAINFO->GSListHandler_->m_ServerInfoList.end();
	int id = 0;
	for (pos;pos!=posend;pos++)
	{
		if (id == index)
		{
			return (*pos);
		}
		id++;
	}
}
int ServerInfoDataHandler::GetSoonServerIndex()
{
	std::list<GameServerdata>::iterator pos = SERVERINFODATAINFO->GSListHandler_->m_ServerInfoList.begin();
	std::list<GameServerdata>::iterator posend = SERVERINFODATAINFO->GSListHandler_->m_ServerInfoList.end();
	int index = 0;
	for(pos;pos!=posend;pos++)
	{
		if ((*pos).title == _TYPE_TITLE_SOON)
		{
			return index;
		}
		index++;
	}
	return -1;
}

int ServerInfoDataHandler::GetAllServerIndex()
{
	std::list<GameServerdata>::iterator pos = SERVERINFODATAINFO->GSListHandler_->m_ServerInfoList.begin();
	std::list<GameServerdata>::iterator posend = SERVERINFODATAINFO->GSListHandler_->m_ServerInfoList.end();
	int index = 0;
	for(pos;pos!=posend;pos++)
	{
		if ((*pos).title == _TYPE_TITLE_ALL)
		{
			return index;
		}
		index++;
	}
	return -1;
}

void ServerInfoDataHandler::IntegraServerInfo()
{
	std::list<int> SoonServerList = LocalPlayerDataManager::get_instance2()->GetLatestServerIDList();
	if(SoonServerList.size() == 0)
		return;
	if (SERVERINFODATAINFO->GSListHandler_->m_ServerInfoList.size() == 0)
		return;
	std::list<int>::const_iterator it = SoonServerList.begin();
	std::list<int>::const_iterator it_end = SoonServerList.end();
	bool isSoon = false;
	std::list<GameServerdata> tempGameDataList;
	for (it;it != it_end;it++)
	{
		std::list<GameServerdata>::iterator pos = SERVERINFODATAINFO->GSListHandler_->m_ServerInfoList.begin();
		std::list<GameServerdata>::iterator posend = SERVERINFODATAINFO->GSListHandler_->m_ServerInfoList.end();
		for (pos;pos!=posend;pos++)
		{
			if ((*it) == (*pos).id_)
			{
				GameServerdata temp;
				temp.id_= (*pos).id_;
				temp.ip_= (*pos).ip_;
				temp.isshow_= (*pos).isshow_;
				temp.level_= (*pos).level_;
				temp.name_= (*pos).name_;
				temp.port_= (*pos).port_;
				temp.state_= (*pos).state_;
				tempGameDataList.push_back(temp);
				//SERVERINFODATAINFO->GSListHandler_->m_ServerInfoList.push_front(temp);
				isSoon = true;
				break;
			}
		}
	}
	size_t leng = tempGameDataList.size();
	if (leng == 0)
		return;
	//�жϵ�ǰ�����¼�Ƿ���ż��
	if (leng%2)
	{
		GameServerdata temp;
		temp.isshow_ = false;
		tempGameDataList.push_back(temp);
	}
	std::list<GameServerdata>::const_reverse_iterator  tempit_begin = tempGameDataList.rbegin();
	std::list<GameServerdata>::const_reverse_iterator  tempit_end = tempGameDataList.rend();
	for (tempit_begin;tempit_begin!=tempit_end;tempit_begin++)
	{
		SERVERINFODATAINFO->GSListHandler_->m_ServerInfoList.push_front((*tempit_begin));
	}
	if (isSoon)
	{
		std::list<GameServerdata>::iterator pos1 = SERVERINFODATAINFO->GSListHandler_->m_ServerInfoList.begin();
		std::list<GameServerdata>::iterator posend1 = SERVERINFODATAINFO->GSListHandler_->m_ServerInfoList.end();
		if (pos1!=posend1)
		{
			(*pos1).title = _TYPE_TITLE_SOON;
		}
	}
}

void ServerInfoDataHandler::decodePacketData_QuickRegister(cobra_win::DPacket & packet){
	unsigned short result =0;
	packet>>result;
	unsigned short tmp_len =0;
	if (result == 0)
	{
//�ο��˺�
		packet>>tmp_len;
		char* tmpChar =new char[tmp_len+1];
		packet.read(tmpChar,tmp_len);
		tmpChar[tmp_len]='\0';
		string aname=tmpChar;
		delete [] tmpChar;tmpChar=0;
//�ο�����
		packet>>tmp_len;
		tmpChar =new char[tmp_len+1];
		packet.read(tmpChar,tmp_len);
		tmpChar[tmp_len]='\0';
		string apwd=tmpChar;
		delete [] tmpChar;tmpChar=0;
//д���ļ�
		WriteVisitorAccountNameAndPWD(aname,apwd);
	}
}

void ServerInfoDataHandler::decodePacketData_Rolelist(cobra_win::DPacket & packet){
	packet>>SERVERINFODATAINFO->m_Rolenum;
	unsigned char rolenum = SERVERINFODATAINFO->m_Rolenum;
	if (rolenum)
	{
		unsigned char index =0;
		for (index;index<rolenum;index++)
		{
			int id;
			packet>>id;
			SERVERINFODATAINFO->m_RoleIdlist.push_back(id);
		}
	}
}


void ServerInfoDataHandler::decodePacketData_Notice_Gateway(cobra_win::DPacket & packet){
	unsigned char isShow = 0;
	packet>>isShow;
	if(isShow == 0){
		m_isNoticeNeedShow = false;
		return;
	}
	else{
		m_isNoticeNeedShow = true;
	}
	char buff[2048] = {0};
	unsigned char fontNum = 0;
	packet>>fontNum;		//Font Num
	m_FontStyleIdMap.clear();
	for(IByte i=0; i < fontNum; i++){
		int fontId = 0;
		int fontSize = 0;
		std::string fontName = "";
		std::string fontColor = ""; 
		packet>>fontId;
		packet>>fontSize;
		NFC_ParsePacketString(packet,fontName);
		NFC_ParsePacketString(packet,fontColor);
		memset(buff,0,sizeof(buff));
		sprintf(buff,_RICH_TEXT_TYPE_,fontSize,fontName.c_str(),fontColor.c_str(),"%s");
		m_FontStyleIdMap.insert(std::map<int,std::string>::value_type(fontId,buff));
	}
	unsigned char noticeNum = 0;
	packet>>noticeNum;
	m_ContentVector.clear();
	for(IByte i = 0; i < noticeNum; i++){
		NoticeData data;
		int id = 0;
		packet>>id;
		std::map<int,std::string>::iterator it = m_FontStyleIdMap.find(id);
		if(it != m_FontStyleIdMap.end()){
			std::string tmptitle = "";
			memset(buff,0,sizeof(buff));
			NFC_ParsePacketString(packet,tmptitle);
			sprintf(buff,it->second.c_str(),tmptitle.c_str());
			data.mTitle = buff;
		}
		int id_content = 0;
		packet>>id_content;
		std::map<int,std::string>::iterator it1 = m_FontStyleIdMap.find(id_content);
		if(it1 != m_FontStyleIdMap.end()){
			std::string tmpcontent = "";
			memset(buff,0,sizeof(buff));
			NFC_ParsePacketString(packet,tmpcontent);
			sprintf(buff,it1->second.c_str(),tmpcontent.c_str());
			data.mContent = buff;
		}
		m_ContentVector.push_back(data);
	}
}

void ServerInfoDataHandler::decodePacketData_CheckOpenFunction(cobra_win::DPacket & packet){
	m_FunctionDatas.clear();
	unsigned char count;
	packet>>count;
	for(int i = 0; i < count; i++){
		FunctionData data;
		int id;
		packet>>id;
		unsigned char isOpen;
		packet>>isOpen;
		data.functionId = id;
		data.isOpen = (isOpen==1)?true:false;
		m_FunctionDatas.push_back(data);
	}
}


/*
	���������ص�¼����֮��
*/
void ServerInfoDataHandler::AfterDecodeNoticeGatewayData(){
	NFC_showCommunicationWating(false);
	if(m_isNoticeNeedShow){
		int type = _TYPE_NOTICEBOX_GATEWAY_;
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_NOTICEBOXWINDOW_, _to_event_param_(type));
	}
}


/*
	������������б�֮��
*/
void ServerInfoDataHandler::AfterDecodeServerList(){ 
	NFC_showCommunicationWating(false);
	if (m_isSelServerWindow){//�ֶ�����������б�֮��
		IntegraServerInfo();
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_SELECTSERVERWINDOW_);
	}else{//������ȡ�������б�֮��
		CheckDefaultGameServer();
		UPDATESYSTEM->QueryVersionInfo();
	}
}

	/*
		��õ�ǰ�˺�
	*/
std::string ServerInfoDataHandler::GetCurAccountName(){
	return GetGameLoginParam().m_Param0;
}


	/*
		��ȡ��ǰ������Ip��Name��port
	*/
int ServerInfoDataHandler::GetCurrentServerId() const
{
	return m_CurServerData.id_;
}

const char* ServerInfoDataHandler::getCurServerName(){
	return m_CurServerData.name_.c_str();
}

int ServerInfoDataHandler::GetCurServerState() const{
	return m_CurServerData.state_;
}

int ServerInfoDataHandler::GetCurServerLevel() const{
	return m_CurServerData.level_;
}

const char* ServerInfoDataHandler::getCurServerIP(){
	return m_CurServerData.ip_.c_str();
}
//
int ServerInfoDataHandler::getCurPort(){
	return m_CurServerData.port_;
}

	/*
		������������Ϸ
		���1��δ��¼�����ֵ�¼����
		���2���ѵ�¼��������Ϸ
	*/
void ServerInfoDataHandler::CheckAccountBeforeEnterGame(){
	if (m_CurServerData.state_==0)//ά����
	{
		NFC_showErrorTips(SysLangDataManager::get_instance2()->GetSysLangById(482));
		return;
	}
	//
#ifdef kENABLE_PLATFORM_PC
    int sdkType = SERVERINFODATAINFO->GetSDKLoginParam().m_iSdkType;
	if(sdkType == SDKLoginParam::_platform_null_){
		//���ִ���״̬��������Ϸ���������ע��Ϊ�ο�
		m_nUserType=kSI_ATYPE_STANDBY;    
	}else{
		//��Ϊ�ѵ�¼״̬���Ժ�����Ѵ��˺ŵ�¼
		m_nUserType=kSI_ATYPE_LOGIN;
	}
	ConnectToGameServer();
#else
	//ֱ����SDK��¼
	LoginSdk();
#endif
}

	/*
		�жϵ�ǰ�Ƿ�δѡ������
	*/
bool ServerInfoDataHandler::HasGameServer(){
	return LocalPlayerDataManager::get_instance2()->GetLatestServerIDList().size()>0;
}

	/*
		����Ĭ����Ϸ������				
	*/				
void ServerInfoDataHandler::CheckDefaultGameServer(){
	if (HasGameServer()){
		//����֮ǰ��½�ķ�������ΪĬ�Ϸ�����
		RecordTheGameServerInfo();
		return;
	}
	//Ѱ���Ƽ�������ߵģ���ΪĬ�Ϸ�����
	if (GSListHandler_->m_ServerInfoList.size()>0)
	{
		list<GameServerdata>::iterator it=GSListHandler_->m_ServerInfoList.begin();
		GameServerdata tmp=*it;
		RecordTheGameServerInfo(tmp);
	}else{
		//û��Ĭ�Ϸ�����
		GameServerdata nosd;
		nosd.isNull=true;
		RecordTheGameServerInfo(nosd);
	}
}
	
/*
		����id�ҵ�ĳ�����������
*/
GameServerdata ServerInfoDataHandler::GetServerDataByID(int id){
	list<GameServerdata>::iterator it=GSListHandler_->m_ServerInfoList.begin();
	for (;it!=GSListHandler_->m_ServerInfoList.end();it++)
	{
		if ((*it).id_==id){
			return *it;
		}
	}
	GameServerdata nullGSD;
	nullGSD.isNull=true;
	return nullGSD;
}

	/*
		��ȡ��ǰ���ӷ�������״̬
	*/
int ServerInfoDataHandler::GetCurGameStatus(){
	return m_nCurGameStatus;
}

	/*
		��ȡ��ǰ���ӷ�������״̬
	*/
void ServerInfoDataHandler::SetCurGameStatus(int status){
	m_nCurGameStatus=status;
}


/*
	���ø��û�����Ϸ�˺ż�����
*/
void ServerInfoDataHandler::setCurAccountNameAndPWD(std::string aname,std::string apwd){
	this->m_nUserAccountName = aname;
	this->m_nUserAccountPWD = apwd;

	SDKLoginParam loginParam;
	loginParam.m_iSdkType = SDKLoginParam::_platform_appstore_;
	loginParam.m_Param0 = m_nUserAccountName;
	loginParam.m_Param1 = m_nUserAccountPWD;
	LocalPlayerDataManager::get_instance2()->SetSdkLoginParam(loginParam);
}



/*
	��¼��������Ϣ���ļ����ڴ�
*/
void ServerInfoDataHandler::RecordTheGameServerInfo(){
	std::list<int> listID=LocalPlayerDataManager::get_instance2()->GetLatestServerIDList();
	if (listID.size()>0)
	{
		int gserverid=listID.front();
		GameServerdata tmp=GetServerDataByID(gserverid);
		if (!tmp.isNull)
		{
			m_CurServerData=tmp;
		}
	}
}

/*
	��¼��������Ϣ���ⲿ���ڴ�
*/
void ServerInfoDataHandler::RecordTheGameServerInfo(GameServerdata& gServerData){
	m_CurServerData=gServerData;
}

	/*
		��ѡ��ķ�����IDд���ļ�
	*/
void ServerInfoDataHandler::WriteTheGameServerInfo(const GameServerdata& gServerData){
	if (!gServerData.isNull)
	{
		LocalPlayerDataManager::get_instance2()->InsertServerID(gServerData.id_,TIMESYSTEM->GetCurrentSecond());
	}
}

	/*
		��¼�ο��˺ź�����
	*/
void ServerInfoDataHandler::WriteVisitorAccountNameAndPWD(std::string aname,std::string apwd){
	SDKLoginParam sdkParam;
	sdkParam.m_iSdkType = SDKLoginParam::_platform_guest_;
	LocalPlayerDataManager::get_instance2()->SetSdkLoginParam(sdkParam);
	GameLoginParam gameParam;
	gameParam.m_Param0 = aname;
	gameParam.m_Param1 = apwd;
	LocalPlayerDataManager::get_instance2()->SetGameLoginParam(gameParam);

	LocalPlayerDataManager::get_instance2()->NeedSaveToDisk();
}

	/*
		��¼��ǰ�˺ź�����Ϊע���û����˺�����
	*/
void ServerInfoDataHandler::WriteLoginAccountNameAndPWD(){
	//��¼ע���û����˺���Ϣ

	SDKLoginParam loginParam;
	loginParam.m_iSdkType = SDKLoginParam::_platform_appstore_;
	loginParam.m_Param0 = m_nUserAccountName;
	loginParam.m_Param1 = m_nUserAccountPWD;
	LocalPlayerDataManager::get_instance2()->SetSdkLoginParam(loginParam);

	LocalPlayerDataManager::get_instance2()->NeedSaveToDisk();
}

	/*
		�ͻ��˼���
	*/
void ServerInfoDataHandler::ToServer_ClientActive(){
	bool hasSent=false;
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_ACCOUNT_, "ClientRecord", "ClientActive",hasSent);
	if (!hasSent)
	{
		CSClientActivePacket packet(Get_GAME_Version(),(int)Get_Channel_ID(),Get_Device_ID(),Get_Device_Mac());
		packet.Send();
		VARIABLESYSTEM->SetVariable(VariableSystem::_TYPED_CONFIG_ACCOUNT_, "ClientRecord", "ClientActive",true);
	}
}

/*
		������Ϸ������֮��Ĳ���
*/
void ServerInfoDataHandler::HandleAfterConnectGameServer(){
	//###������������
	HEARTBEATDATAHANDLER->resetAllCount();
	//###�����½�������
	if (m_nUserType==kSI_ATYPE_STANDBY){//�������ο�ע��
		LOGGERSYSTEM->LogInfo("ServerInfoDataHandler::HandleAfterConnectGameServer===Standby status");
		CSQuickAccountRegisterPacket packet(Get_Device_ID());
		packet.Send();
	}else{//�ѵ�¼���
		LOGGERSYSTEM->LogInfo("ServerInfoDataHandler::HandleAfterConnectGameServer===Send Login Packet");
		SendAccountLogin();
	}
}

	/*
		����ǰ�������ӳɹ����������
	*/
void ServerInfoDataHandler::HandleCurrentOperationAfterConnetNetwork(){
	LOGGERSYSTEM->LogInfo("ServerInfoDataHandler::HandleCurrentOperationAfterConnetNetwork===GameStatus:  %d",GetCurGameStatus());
	if(GetCurGameStatus()==_TYPE_LOGIN_STATE_GAMESERVER_CONNECT){//�����������Ϸ������
		SetCurGameStatus(_TYPE_LOGIN_STATE_GAMESERVER_SUCCESS_);
		SERVERINFODATAINFO->HandleAfterConnectGameServer();
	}	
}

	/*
		�������ע��������
	*/
void ServerInfoDataHandler::HandleAfterQuickRegister(){
	m_nUserType=kSI_ATYPE_LOGIN;
	SendAccountLogin();
}

	/*
		�����½���
	*/
void ServerInfoDataHandler::HandleAfterLogin(int result){
	std::string message;
	if (result ==LOGIN_RESULT_SUCCESS)//��֤�ɹ�
	{
		LOGGERSYSTEM->LogInfo("ServerInfoDataHandler::HandleAfterLogin===Login Success!");
		/*
			*�Ȼ�ȡ��ɫ�б�
		*/
		DEBUGERSYSTEM->m_pNetDebuger->setAccount_Auth_End();
		DEBUGERSYSTEM->m_pNetDebuger->setRole_Begin();
		CSRolelistPacket   cspacket(GetGameLoginParam().m_Param0, SERVERINFODATAINFO->getCurKey());
		cspacket.Send();
	}
	else//��֤����~
	{
		NFC_showCommunicationWating(false);
		//
		if (!DOTATribeApp::get_instance2()->IsLoginProcedureAsActiveProcedure()){
			//�����Ϊ��½���̣���Ҫ����startwindow
			BackToStartWindow();
		}
		//
		if (result == LOGIN_RESULT_ERROR_1)//����������
		{
			message = SysLangDataManager::get_instance2()->GetSysLangById(581).c_str();
		}
		else if (result == LOGIN_RESULT_ERROR_2)//�û�������
		{	
			message = SysLangDataManager::get_instance2()->GetSysLangById(582).c_str();
		}
		else if (result ==LOGIN_RESULT_ERROR_3)//�������
		{
			message = SysLangDataManager::get_instance2()->GetSysLangById(583).c_str();
		}
		else if(result==LOGIN_RESULT_ERROR_4)//��������
		{
			message=SysLangDataManager::get_instance2()->GetSysLangById(9).c_str();
		}else if(result==LOGIN_RESULT_ERROR_5){//session ����
			LOGGERSYSTEM->LogInfo("ServerInfoDataHandler::HandleAfterLogin===Session Expired");
			LoginOutOfDate();
			return;
		}else if(result==LOGIN_RESULT_ERROR_99){
			message=SysLangDataManager::get_instance2()->GetSysLangById(10).c_str();
		}
		NFC_showMessageBox(kDEFAULT,message);
	}
}

	/*
		�����ȡ�����б�������
	*/
void ServerInfoDataHandler::HandleAfterRoleList(){
	LOGGERSYSTEM->LogInfo("ServerInfoDataHandler::HandleAfterRoleList");
//=====================ͳ��������ʱ====================//
	DEBUGERSYSTEM->m_pNetDebuger->setRole_End();
	DEBUGERSYSTEM->m_pNetDebuger->setLogin_Begin();
//=====================ͳ��������ʱ====================//
	if (SERVERINFODATAINFO->m_Rolenum == 0){//��ת��������ɫ����
		m_bIsNewRole = 0;
		DOTATribeApp::get_instance2()->m_pLoginProcedure->ChangeProcedureTo((IProcedure *)DOTATribeApp::get_instance2()->m_pCreateRoleProcedure);
		SetCurGameStatus(_TYPE_LOGIN_STATE_GAMESERVER_ENTERGAME);
	}else{//�н�ɫ
		m_bIsNewRole = 1;
		SetCurGameStatus(_TYPE_LOGIN_STATE_GAMESERVER_ENTERGAME);
		int id = SERVERINFODATAINFO->m_RoleIdlist[0];
		CSEnterGamePacket packet(id, GetGameLoginParam().m_Param0);
		packet.Send();
	}
}

	/*
		����������Ϸ�������������,��Ϊ��������
	*/
void ServerInfoDataHandler::HandleAfterRoleInfo(){
	LOGGERSYSTEM->LogInfo("ServerInfoDataHandler::HandleAfterRoleInfo");
	if (DOTATribeApp::get_instance2()->IsLoginProcedureAsActiveProcedure()
		||DOTATribeApp::get_instance2()->IsCreateRoleProcedureAsActiveProcedure()){//Ϊ��½���̻��ߴ�����ɫ���̵�ʱ��
//=====================ͳ��������ʱ====================//
		DEBUGERSYSTEM->m_pNetDebuger->setLogin_End();
		DEBUGERSYSTEM->m_pNetDebuger->ToServer_LoginDebugInfo();
//=====================ͳ��������ʱ====================//
//=====================���Ϳͻ��˼���=================//
		ToServer_ClientActive();
//=====================���Ϳͻ��˼���=================//
		DOTATribeApp::get_instance2()->m_pCreateRoleProcedure->ChangeProcedureTo((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
		SERVERINFODATAINFO->ShowSuspendWindow(true);//show SDK ToolBar

		SharePlayerAccountInfo();
	}else{
		//��Ϸ�еĶ�������
		//֪ͨ��Ҫ�����⴦��ĵط�
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_RECONNECT_INGAME_NOTIFY);
	}
	NFC_showCommunicationWating(false);
}

	/*
		��ȡ�������б�_����
	*/
void ServerInfoDataHandler::QueryServerListData(){
	m_isSelServerWindow=false;
	NFC_showCommunicationWating(true);
	CurSendHttpPacketType_=_HTTP_STATE_DISTINCT_;

	std::string version = Get_GAME_Version();
	//��׿�汾ʱ����Ϸַ�������
	version = version + "_" + SERVERINFODATAINFO->Get_tuiguang_ad_Channel();

	CSServerListPacket  packet(Get_Channel_ID(), version);
	packet.SendHttp();
}

	/*
		��ȡ�������б�_ѡ������
	*/
void ServerInfoDataHandler::QueryServerListData_selServerWindow(){
	m_isSelServerWindow=true;
	NFC_showCommunicationWating(true);
	CurSendHttpPacketType_=_HTTP_STATE_NORMAL;

	std::string version = Get_GAME_Version();
	//��׿�汾ʱ����Ϸַ�������
	version = version + "_" + SERVERINFODATAINFO->Get_tuiguang_ad_Channel();

	CSServerListPacket  packet(Get_Channel_ID(), version);
	packet.SendHttp();
}

void ServerInfoDataHandler::QueryNoticeGatewayData(){
	NFC_showCommunicationWating(true);
	CurSendHttpPacketType_ = _HTTP_STATE_NORMAL;
	C2SNoticeGatewayPacket packet;
	packet.SendHttp();
}


	/*
		���صȵ�¼����
	*/
void ServerInfoDataHandler::LogoutGame(){
	SERVERINFODATAINFO->SetCurGameStatus(_TYPE_LOGIN_STATE_STANDBY_);
	DisconnectGameServer_Normal();
	DOTATribeApp::get_instance2()->ResetAllGame();
	DOTATribeApp::get_instance2()->SetActiveProcedure(DOTATribeApp::get_instance2()->m_pLoginProcedure);
}

	/*
		����Ƿ��������������
	*/
bool ServerInfoDataHandler::CanResetCounter_HeartCheck(){
	bool condition1=GetCurGameStatus()!=_TYPE_LOGIN_STATE_GAMESERVER_SUCCESS_;
	bool condition2=GetCurGameStatus()!=_TYPE_LOGIN_STATE_GAMESERVER_ENTERGAME;
	//
	return condition1&&condition2;
}

	/*
		����ע���˺�
	*/
void ServerInfoDataHandler::SendAccountRegister(){
	CSRegisterAccountPacket packet(GetGameLoginParam().m_Param0, GetGameLoginParam().m_Param1);
	packet.Send();	
}

	/*
		���͵�½����
	*/
void ServerInfoDataHandler::SendAccountLogin(){
	DEBUGERSYSTEM->m_pNetDebuger->setAccount_Auth_Begin();
	LoginParams param = _getLoginParams();
	CSLoginPacket packet(param);
	packet.Send();
}

	/*
		������Ϸ������
	*/
void ServerInfoDataHandler::ConnectToGameServer(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	NFC_showCommunicationWating_2(true);
#else
	NFC_showCommunicationWating(true);
#endif
	//���õ�ǰ��Ϸ״̬Ϊ������Ϸ������
	SetCurGameStatus(_TYPE_LOGIN_STATE_GAMESERVER_CONNECT);
	WriteTheGameServerInfo(m_CurServerData);

	if(!NETSYSTEM->ReConnectServer()){
		NFC_showErrorTips(SysLangDataManager::get_instance2()->GetSysLangById(18));
	}
}

	/*
		����ο��˺���Ϣ
	*/
void ServerInfoDataHandler::DeleteVisitorAccountInfo(){
	SDKLoginParam param;
	param.m_iSdkType = SDKLoginParam::_platform_null_;
	LocalPlayerDataManager::get_instance2()->SetSdkLoginParam(param);
	LocalPlayerDataManager::get_instance2()->NeedSaveToDisk();
}

	/*
		��������ʺ���Ϣ
	*/
void ServerInfoDataHandler::DeleteAllAccountInfo(){
	SDKLoginParam param;
	param.m_iSdkType = SDKLoginParam::_platform_null_;
	LocalPlayerDataManager::get_instance2()->SetSdkLoginParam(param);
	LocalPlayerDataManager::get_instance2()->NeedSaveToDisk();

}

	/*
		���ص�¼���棬ע���˺���Ϣ
	*/
void ServerInfoDataHandler::LogoutAccountInfo(){
	if (!DOTATribeApp::get_instance2()->IsLoginProcedureAsActiveProcedure()){
		//��Ϊ��½���̵�ʱ��
		LogoutGame();
		DeleteAllAccountInfo();
		m_nUserType=kSI_ATYPE_STANDBY;
	}
}

	/*
		��ǰ�û��Ƿ�Ϊ��½״̬
	*/
bool ServerInfoDataHandler::IsLoginGame(){

	int sdkType = GetSDKLoginParam().m_iSdkType;
	if(sdkType == SDKLoginParam::_platform_null_){
		return false;
	}
	else{
		return true;
	}
}

	/*
		������֪ͨǿ�жϿ�����
	*/
void ServerInfoDataHandler::ForceDisconnect(){
	NETSYSTEM->ForceDisconnectWithGameServer();
}

	/*
		���жϿ���Ϸ������
	*/
void ServerInfoDataHandler::DisconnectGameServer_Normal(){
	//�ϵ���Ϸ������
	NETSYSTEM->DisconnectSocket();
}

	/*
		�����������
	*/
void ServerInfoDataHandler::HandleDisConnect(bool isreconnect){

	if (isreconnect){
		ConnectToGameServer();
	}else{	//������������������
		LOGGERSYSTEM->LogInfo("====_handleNetWorkDisconnect===_TYPE_LOGIN_STATE_GAMESERVER_ENTERGAME");
		BackToStartWindow();
	}
}

	/*
		���ص�½����
	*/
void ServerInfoDataHandler::BackToStartWindow(){
	//=====��Ϸ����====
	DOTATribeApp::get_instance2()->ResetAllGame();
	SERVERINFODATAINFO->SetCurGameStatus(_TYPE_LOGIN_STATE_STANDBY_);
	DOTATribeApp::get_instance2()->SetActiveProcedure(DOTATribeApp::get_instance2()->m_pLoginProcedure);
}

	/*
		��½���̳�ʼ��
	*/
void ServerInfoDataHandler::LoginProcedureInit(){
	if (SERVERINFODATAINFO->GetCurGameStatus()==_TYPE_LOGIN_STATE_UNKOWN_){//
		LOGGERSYSTEM->LogInfo("====LoginProcedure===_TYPE_LOGIN_STATE_UNKOWN_");
		QueryServerListData();
	}else if(SERVERINFODATAINFO->GetCurGameStatus()==_TYPE_LOGIN_STATE_GAMESERVER_ENTERGAME){
		LOGGERSYSTEM->LogInfo("====LoginProcedure===_TYPE_LOGIN_STATE_GAMESERVER_ENTERGAME");
		SERVERINFODATAINFO->CheckAccountBeforeEnterGame();//ֱ�Ӱ��û�����Ϸ
	}else{//���ؿ�ʼ��Ϸ�������
		LOGGERSYSTEM->LogInfo("====LoginProcedure===ELSE");
		SERVERINFODATAINFO->SetCurGameStatus(_TYPE_LOGIN_STATE_STANDBY_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEWINDOW_UI_SHOW_NORMAL);
	}
	//�ر�socket�Ͽ���ʾ��
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_MESSAGEBOXWINDOW_);
}

	/*
		֪ͨsocket�Ͽ���
	*/
void ServerInfoDataHandler::NotifySocketClosed(){
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOCKETCLOSED_HINT);
}

	/*
		��������״̬�л�
		wifi <-> ��wifi
	*/
void ServerInfoDataHandler::NotifyNetworkChanged(){
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_NETWORKCHANGED_HINT);
}


	/*
		����socket�Ͽ��ĺ�������
		#��ʾ������󵯴�
		#��Ҫ����socket�Ͽ������⣬�����������
		#������ʾΨһ����
	*/
void ServerInfoDataHandler::HandleConnectServerFail(){
	LOGGERSYSTEM->LogInfo("=======ServerInfoDataHandler::HandleConnectServerFail=====");
	NFC_showCommunicationWating(false);
    EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_APPSTOREWAITWINDOW_);
	//�ٴα�������¼���̲���ʾ������ʾ
	if (!DOTATribeApp::get_instance2()->IsLoginProcedureAsActiveProcedure()){
		NFC_showMessageBox(kNETWORKDISCONNECTED,SysLangDataManager::get_instance2()->GetSysLangById(658));
	}
}

/*
	����socket����ʧ��
*/
void ServerInfoDataHandler::HandleSocketConnectFail(){
	NFC_showCommunicationWating(false);
	if (!DOTATribeApp::get_instance2()->IsLoginProcedureAsActiveProcedure()){
		//��Ϊ��½���̵�ʱ��
		LOGGERSYSTEM->LogInfo("ServerInfoDataHandler::HandleSocketConnectFail==Not In LoginProcedure,Show MessageBox");
		NFC_showMessageBox(kNETWORKDISCONNECTED,SysLangDataManager::get_instance2()->GetSysLangById(658));
	}else{
		LOGGERSYSTEM->LogInfo("ServerInfoDataHandler::HandleSocketConnectFail==In LoginProcedure,Show Tips");
		NFC_showErrorTips(SysLangDataManager::get_instance2()->GetSysLangById(440));
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEWINDOW_UI_SHOW_NORMAL);
	}
}

	/*
		����HTTP����ʧ��
	*/
void ServerInfoDataHandler::HandleHttpConnectFail(){
	if (CurSendHttpPacketType_==_HTTP_STATE_DISTINCT_)//ǿ��Ҫ�󷵻ؽ����
	{
		NFC_showCommunicationWating(false);
		NFC_showMessageBoxSingle(kGATEWAY_CONNECTFAIL,SysLangDataManager::get_instance2()->GetSysLangById(710));
	}
	CurSendHttpPacketType_=_HTTP_STATE_UNKNOWN_;
}

//==============��ȡ�豸��Ϣ===========
	//����豸����ϵͳ
std::string ServerInfoDataHandler::Get_Device_OS(){
	return ENGINESYSTEM->GetOS();
}
	//����豸ID
std::string ServerInfoDataHandler::Get_Device_ID()
{
	std::string deviceID = CCDirector::sharedDirector()->getSystem()->getDeviceUUID()+CCDirector::sharedDirector()->getSystem()->getDeviceIMEI();
	return deviceID;
}
	//�������ƽ̨
unsigned char ServerInfoDataHandler::Get_Channel_ID(){
	int sdktype = LocalPlayerDataManager::get_instance2()->GetSdkLoginParam().m_iSdkType;
	return sdktype;
}

std::string ServerInfoDataHandler::Get_tuiguang_ad_Channel()
{
	std::string temp;
	//��׿�汾ʱ����Ϸַ�������
	char channel[128] = "";
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "Version", "Channel", channel, sizeof(channel));
	temp = channel;

	return temp;
}

	//����ϵͳ�汾
std::string ServerInfoDataHandler::Get_Device_OS_Version(){
	return "NULL";
}
	//MACAddress 
std::string ServerInfoDataHandler::Get_Device_Mac(){
	return CCDirector::sharedDirector()->getSystem()->getDeviceMacAddr();
}
	//Version
std::string ServerInfoDataHandler::Get_GAME_Version(){
	return DGC_GetGameVersion();
}
	//telecomOperator  
std::string ServerInfoDataHandler::Get_Device_telecomOperator(){
	return "NULL";
}
	//AppendParam   
std::string ServerInfoDataHandler::Get_Other_Param(){
	return "NULL";
}
	//�Ƿ�Խ��   
unsigned char ServerInfoDataHandler::Get_Hacked(){
	return 0;
}


//==============��½����=================//
void ServerInfoDataHandler::LoginNotice_Request(bool istab){
	CSNoticePacket packet;
	packet.Send();
	m_isBNoticeTab = istab;
	NFC_showCommunicationWating(true);
}

void ServerInfoDataHandler::CheckOpenFun_Request(){
	C2SCheckOpenFunPacket packet;
	packet.Send();
	NFC_showCommunicationWating(true);
}

void ServerInfoDataHandler::HandleAfterLoginNoticeResp(const std::string& content){
	LimitedActivityHandler::get_instance2()->NoticeContent_=content;
	if (m_isBNoticeTab)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_LIMITEDACTIVITYWINDOW_NOTICE);
	}
	else
	{
		int type = _TYPE_NOTICEBOX_GAMESERVER_;
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_NOTICEBOXWINDOW_,_to_event_param_(type));
	}
	
	NFC_showCommunicationWating(false);
}

SDKLoginParam ServerInfoDataHandler::GetSDKLoginParam()
{
	return LocalPlayerDataManager::get_instance2()->GetSdkLoginParam();
}

GameLoginParam ServerInfoDataHandler::GetGameLoginParam()
{
	return LocalPlayerDataManager::get_instance2()->GetGameLoginParam();
}

void ServerInfoDataHandler::SetLoginSdkDelegate()
{
	CCDirector::sharedDirector()->getPlatform()->setDelegate(this);
}

//��½sdk
void ServerInfoDataHandler::LoginSdk(bool isExpired)
{
	CCDirector::sharedDirector()->getPlatform()->login(isExpired);
}

//��sdk�ǳ�
void ServerInfoDataHandler::LogoutSdk()
{
	CCDirector::sharedDirector()->getPlatform()->logout();
}

//��ʾSdk�˺�����
void ServerInfoDataHandler::ShowSdkCenter(){
	CCDirector::sharedDirector()->getPlatform()->ShowSDKCenter();
}

//��ʾSDK��������
void ServerInfoDataHandler::ShowSuspendWindow(bool status)
{
	CCDirector::sharedDirector()->getPlatform()->ShowSuspendWindow(status);
}

//����㹲����ҽ�ɫ��Ϣ
void ServerInfoDataHandler::SharePlayerAccountInfo()
{
	std::string param1 = getCurServerName();
	param1 += "_" + _to_event_param_(m_bIsNewRole);
	CCDirector::sharedDirector()->getPlatform()->SharePlayerAccountInfo(param1, ROLEINFODATAHANDLER->m_pRIData->name_, GetCurrentServerId(), ROLEINFODATAHANDLER->m_pRIData->instanceId_
		, ROLEINFODATAHANDLER->m_pRIData->level_, ROLEINFODATAHANDLER->m_pRIData->vipLevel_);
}

void ServerInfoDataHandler::DelayForCYSDK(){
    NFC_showCommunicationWating(false);
    SERVERINFODATAINFO->ConnectToGameServer();
}

//sdk��½�ɹ��ص�
void ServerInfoDataHandler::onLoginResultHandler(int sdkType, bool bSuccess, std::string param0, std::string param1, std::string param2, std::string param3, std::string param4
	, std::string param5, std::string param6, std::string param7, std::string param8, std::string param9)
{
    LOGGERSYSTEM->LogInfo("=======ServerInfoDataHandler::onLoginResultHandler==1===param0: %s",param0.c_str());
	m_nUserType=kSI_ATYPE_LOGIN;
	//
	SDKLoginParam sdkParam;
	sdkParam.m_iSdkType = sdkType;
	sdkParam.m_Param0 = param0;
	sdkParam.m_Param1 = param1;
	sdkParam.m_Param2 = param2;
	sdkParam.m_Param3 = param3;
	sdkParam.m_Param4 = param4;
	sdkParam.m_Param5 = param5;
	sdkParam.m_Param6 = param6;
	sdkParam.m_Param7 = param7;
	sdkParam.m_Param8 = param8;
	sdkParam.m_Param9 = param9;

    LOGGERSYSTEM->LogInfo("=======ServerInfoDataHandler::onLoginResultHandler==2===");
#ifdef kENABLE_PLATFORM_SDKANDROID
	if(sdkParam.m_iSdkType == SDKLoginParam::_platform_cyou_)
	{
		char channel[128] = "";
		VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "Version", "Channel", channel, sizeof(channel));
		std::string temp = channel;
		sdkParam.m_Param3 = sdkParam.m_Param3 + temp;
	}
#endif

#ifdef kSDK_CYOU_JBREAK_ENABEL
	if(sdkParam.m_iSdkType == SDKLoginParam::_platform_cyou_jbreak_)
	{
		char channel[128] = "";
		VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "Version", "Channel", channel, sizeof(channel));
		std::string temp = channel;
		sdkParam.m_Param3 = sdkParam.m_Param3 + temp;
	}
#endif
    
	LocalPlayerDataManager::get_instance2()->SetSdkLoginParam(sdkParam);

	LocalPlayerDataManager::get_instance2()->NeedSaveToDisk();

	if (bSuccess)
	{
        //TODO:tmp use 4s delay to avoid cy sdk freezing
        DOTATribeApp::get_instance2()->scheduleOnce(schedule_selector(DOTATribeApp::DelayForCYSDK), 4);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		NFC_showCommunicationWating_2(true);
#else
		NFC_showCommunicationWating(true);
#endif
	}
    
    LOGGERSYSTEM->LogInfo("=======ServerInfoDataHandler::onLoginResultHandler==3===");
}

//ƽ̨ע���ص�
void ServerInfoDataHandler::onLogoutCallBack(int sdkType, bool bSuccess, std::string param0, std::string param1, std::string param2, std::string param3, std::string param4
	, std::string param5, std::string param6, std::string param7, std::string param8, std::string param9){
		LogoutAccountInfo();
}

//��½����
void ServerInfoDataHandler::LoginOutOfDate()
{
	SERVERINFODATAINFO->SetCurUserType(kSI_ATYPE_LOGIN);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEWINDOW_UI_SHOW_NORMAL);
	DeleteAllAccountInfo();
	LoginSdk(true);
	DisconnectGameServer_Normal();
}

void ServerInfoDataHandler::onPayResultCallBack(int sdkType, int resultCode, std::string param0,std::string param1){
#ifdef kENABLE_PLATFORM_SDKIOS
	PAYGOODSCONTROLDATAHANDLER->LocalPayIAPCheck();
#endif
#ifdef kENABLE_PLATFORM_SDKANDROID
	PAYGOODSCONTROLDATAHANDLER->LocalPayIAPCheck();
#endif
}