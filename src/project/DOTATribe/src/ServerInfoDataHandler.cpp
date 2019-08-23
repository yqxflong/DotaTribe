//Name：	ServerInfoDataHandler
//Function：游戏登陆相关流程控制器
//Written By：尹强

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

//#############登陆返回结果类型############
static int LOGIN_RESULT_SUCCESS=0;	//登陆成功<br>
static int LOGIN_RESULT_ERROR_1=1;//参数不完整<br>
static int LOGIN_RESULT_ERROR_2=2;//用户不存在<br>
static int LOGIN_RESULT_ERROR_3=3;//密码错误<br>
static int LOGIN_RESULT_ERROR_4=4;//其它错误<br>
static int LOGIN_RESULT_ERROR_5=5;//91Session过期，重新登陆<br>
static int LOGIN_RESULT_ERROR_99=99;//验证服务器异常<br>

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
	//注册请求服务器超时事件
	EVENTSYSTEM->RegisterEventHandler(_TYPED_EVENT_COMMUNICATION_TIMEOUT_,OnEventServerRequest);

	return true;
}

	/*
		服务器请求超时事件
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
	获取Login参数体
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

	//修正于20140115
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
         * 服务器列表返回<br>
         * short count 数量<br>
         * for(count){<br>
         * int id 服务器ID<br>
         * String name 服务器名称<br>
         * String ip 服务器IP<br>
         * int port 服务器端口<br>
         * byte state 状态<br>
         * byte level 推荐级别  <br>
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
//服务器名称
		NFC_ParsePacketString(packet,tempServer.name_);
//服务器IP
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
	//判断当前最近登录是否是偶数
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
//游客账号
		packet>>tmp_len;
		char* tmpChar =new char[tmp_len+1];
		packet.read(tmpChar,tmp_len);
		tmpChar[tmp_len]='\0';
		string aname=tmpChar;
		delete [] tmpChar;tmpChar=0;
//游客密码
		packet>>tmp_len;
		tmpChar =new char[tmp_len+1];
		packet.read(tmpChar,tmp_len);
		tmpChar[tmp_len]='\0';
		string apwd=tmpChar;
		delete [] tmpChar;tmpChar=0;
//写入文件
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
	解析完网关登录公告之后
*/
void ServerInfoDataHandler::AfterDecodeNoticeGatewayData(){
	NFC_showCommunicationWating(false);
	if(m_isNoticeNeedShow){
		int type = _TYPE_NOTICEBOX_GATEWAY_;
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_NOTICEBOXWINDOW_, _to_event_param_(type));
	}
}


/*
	解析完服务器列表之后
*/
void ServerInfoDataHandler::AfterDecodeServerList(){ 
	NFC_showCommunicationWating(false);
	if (m_isSelServerWindow){//手动请求服务器列表之后
		IntegraServerInfo();
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATE_SELECTSERVERWINDOW_);
	}else{//开机获取服务器列表之后
		CheckDefaultGameServer();
		UPDATESYSTEM->QueryVersionInfo();
	}
}

	/*
		获得当前账号
	*/
std::string ServerInfoDataHandler::GetCurAccountName(){
	return GetGameLoginParam().m_Param0;
}


	/*
		获取当前服务器Ip和Name和port
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
		界面点击进入游戏
		情况1：未登录，出现登录界面
		情况2：已登录，进入游戏
	*/
void ServerInfoDataHandler::CheckAccountBeforeEnterGame(){
	if (m_CurServerData.state_==0)//维护中
	{
		NFC_showErrorTips(SysLangDataManager::get_instance2()->GetSysLangById(482));
		return;
	}
	//
#ifdef kENABLE_PLATFORM_PC
    int sdkType = SERVERINFODATAINFO->GetSDKLoginParam().m_iSdkType;
	if(sdkType == SDKLoginParam::_platform_null_){
		//保持待机状态，链接游戏服务器后会注册为游客
		m_nUserType=kSI_ATYPE_STANDBY;    
	}else{
		//设为已登录状态，稍后会用已存账号登录
		m_nUserType=kSI_ATYPE_LOGIN;
	}
	ConnectToGameServer();
#else
	//直接用SDK登录
	LoginSdk();
#endif
}

	/*
		判断当前是否未选服务器
	*/
bool ServerInfoDataHandler::HasGameServer(){
	return LocalPlayerDataManager::get_instance2()->GetLatestServerIDList().size()>0;
}

	/*
		设置默认游戏服务器				
	*/				
void ServerInfoDataHandler::CheckDefaultGameServer(){
	if (HasGameServer()){
		//设置之前登陆的服务器作为默认服务器
		RecordTheGameServerInfo();
		return;
	}
	//寻找推荐级别最高的，作为默认服务器
	if (GSListHandler_->m_ServerInfoList.size()>0)
	{
		list<GameServerdata>::iterator it=GSListHandler_->m_ServerInfoList.begin();
		GameServerdata tmp=*it;
		RecordTheGameServerInfo(tmp);
	}else{
		//没有默认服务器
		GameServerdata nosd;
		nosd.isNull=true;
		RecordTheGameServerInfo(nosd);
	}
}
	
/*
		根据id找到某组服务器数据
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
		获取当前连接服务器的状态
	*/
int ServerInfoDataHandler::GetCurGameStatus(){
	return m_nCurGameStatus;
}

	/*
		获取当前连接服务器的状态
	*/
void ServerInfoDataHandler::SetCurGameStatus(int status){
	m_nCurGameStatus=status;
}


/*
	设置该用户的游戏账号及密码
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
	记录服务器信息从文件到内存
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
	记录服务器信息从外部到内存
*/
void ServerInfoDataHandler::RecordTheGameServerInfo(GameServerdata& gServerData){
	m_CurServerData=gServerData;
}

	/*
		将选择的服务器ID写入文件
	*/
void ServerInfoDataHandler::WriteTheGameServerInfo(const GameServerdata& gServerData){
	if (!gServerData.isNull)
	{
		LocalPlayerDataManager::get_instance2()->InsertServerID(gServerData.id_,TIMESYSTEM->GetCurrentSecond());
	}
}

	/*
		记录游客账号和密码
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
		记录当前账号和密码为注册用户的账号密码
	*/
void ServerInfoDataHandler::WriteLoginAccountNameAndPWD(){
	//记录注册用户的账号信息

	SDKLoginParam loginParam;
	loginParam.m_iSdkType = SDKLoginParam::_platform_appstore_;
	loginParam.m_Param0 = m_nUserAccountName;
	loginParam.m_Param1 = m_nUserAccountPWD;
	LocalPlayerDataManager::get_instance2()->SetSdkLoginParam(loginParam);

	LocalPlayerDataManager::get_instance2()->NeedSaveToDisk();
}

	/*
		客户端激活
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
		连接游戏服务器之后的操作
*/
void ServerInfoDataHandler::HandleAfterConnectGameServer(){
	//###重置心跳参数
	HEARTBEATDATAHANDLER->resetAllCount();
	//###处理登陆相关事宜
	if (m_nUserType==kSI_ATYPE_STANDBY){//待机走游客注册
		LOGGERSYSTEM->LogInfo("ServerInfoDataHandler::HandleAfterConnectGameServer===Standby status");
		CSQuickAccountRegisterPacket packet(Get_Device_ID());
		packet.Send();
	}else{//已登录情况
		LOGGERSYSTEM->LogInfo("ServerInfoDataHandler::HandleAfterConnectGameServer===Send Login Packet");
		SendAccountLogin();
	}
}

	/*
		处理当前网络连接成功后相关事宜
	*/
void ServerInfoDataHandler::HandleCurrentOperationAfterConnetNetwork(){
	LOGGERSYSTEM->LogInfo("ServerInfoDataHandler::HandleCurrentOperationAfterConnetNetwork===GameStatus:  %d",GetCurGameStatus());
	if(GetCurGameStatus()==_TYPE_LOGIN_STATE_GAMESERVER_CONNECT){//如果是连接游戏服务器
		SetCurGameStatus(_TYPE_LOGIN_STATE_GAMESERVER_SUCCESS_);
		SERVERINFODATAINFO->HandleAfterConnectGameServer();
	}	
}

	/*
		处理快速注册后的事宜
	*/
void ServerInfoDataHandler::HandleAfterQuickRegister(){
	m_nUserType=kSI_ATYPE_LOGIN;
	SendAccountLogin();
}

	/*
		处理登陆结果
	*/
void ServerInfoDataHandler::HandleAfterLogin(int result){
	std::string message;
	if (result ==LOGIN_RESULT_SUCCESS)//认证成功
	{
		LOGGERSYSTEM->LogInfo("ServerInfoDataHandler::HandleAfterLogin===Login Success!");
		/*
			*先获取角色列表
		*/
		DEBUGERSYSTEM->m_pNetDebuger->setAccount_Auth_End();
		DEBUGERSYSTEM->m_pNetDebuger->setRole_Begin();
		CSRolelistPacket   cspacket(GetGameLoginParam().m_Param0, SERVERINFODATAINFO->getCurKey());
		cspacket.Send();
	}
	else//认证出错~
	{
		NFC_showCommunicationWating(false);
		//
		if (!DOTATribeApp::get_instance2()->IsLoginProcedureAsActiveProcedure()){
			//如果不为登陆流程，需要返回startwindow
			BackToStartWindow();
		}
		//
		if (result == LOGIN_RESULT_ERROR_1)//参数不完整
		{
			message = SysLangDataManager::get_instance2()->GetSysLangById(581).c_str();
		}
		else if (result == LOGIN_RESULT_ERROR_2)//用户不存在
		{	
			message = SysLangDataManager::get_instance2()->GetSysLangById(582).c_str();
		}
		else if (result ==LOGIN_RESULT_ERROR_3)//密码错误
		{
			message = SysLangDataManager::get_instance2()->GetSysLangById(583).c_str();
		}
		else if(result==LOGIN_RESULT_ERROR_4)//其他错误
		{
			message=SysLangDataManager::get_instance2()->GetSysLangById(9).c_str();
		}else if(result==LOGIN_RESULT_ERROR_5){//session 过期
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
		处理获取人物列表后的事宜
	*/
void ServerInfoDataHandler::HandleAfterRoleList(){
	LOGGERSYSTEM->LogInfo("ServerInfoDataHandler::HandleAfterRoleList");
//=====================统计网络延时====================//
	DEBUGERSYSTEM->m_pNetDebuger->setRole_End();
	DEBUGERSYSTEM->m_pNetDebuger->setLogin_Begin();
//=====================统计网络延时====================//
	if (SERVERINFODATAINFO->m_Rolenum == 0){//跳转到创建角色界面
		m_bIsNewRole = 0;
		DOTATribeApp::get_instance2()->m_pLoginProcedure->ChangeProcedureTo((IProcedure *)DOTATribeApp::get_instance2()->m_pCreateRoleProcedure);
		SetCurGameStatus(_TYPE_LOGIN_STATE_GAMESERVER_ENTERGAME);
	}else{//有角色
		m_bIsNewRole = 1;
		SetCurGameStatus(_TYPE_LOGIN_STATE_GAMESERVER_ENTERGAME);
		int id = SERVERINFODATAINFO->m_RoleIdlist[0];
		CSEnterGamePacket packet(id, GetGameLoginParam().m_Param0);
		packet.Send();
	}
}

	/*
		处理连接游戏服务器后的事情,常为断线重连
	*/
void ServerInfoDataHandler::HandleAfterRoleInfo(){
	LOGGERSYSTEM->LogInfo("ServerInfoDataHandler::HandleAfterRoleInfo");
	if (DOTATribeApp::get_instance2()->IsLoginProcedureAsActiveProcedure()
		||DOTATribeApp::get_instance2()->IsCreateRoleProcedureAsActiveProcedure()){//为登陆流程或者创建角色流程的时候
//=====================统计网络延时====================//
		DEBUGERSYSTEM->m_pNetDebuger->setLogin_End();
		DEBUGERSYSTEM->m_pNetDebuger->ToServer_LoginDebugInfo();
//=====================统计网络延时====================//
//=====================发送客户端激活=================//
		ToServer_ClientActive();
//=====================发送客户端激活=================//
		DOTATribeApp::get_instance2()->m_pCreateRoleProcedure->ChangeProcedureTo((IProcedure*)DOTATribeApp::get_instance2()->m_pHomeProcedure);
		SERVERINFODATAINFO->ShowSuspendWindow(true);//show SDK ToolBar

		SharePlayerAccountInfo();
	}else{
		//游戏中的断线重连
		//通知需要做特殊处理的地方
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_RECONNECT_INGAME_NOTIFY);
	}
	NFC_showCommunicationWating(false);
}

	/*
		获取服务器列表_开机
	*/
void ServerInfoDataHandler::QueryServerListData(){
	m_isSelServerWindow=false;
	NFC_showCommunicationWating(true);
	CurSendHttpPacketType_=_HTTP_STATE_DISTINCT_;

	std::string version = Get_GAME_Version();
	//安卓版本时会加上分发渠道号
	version = version + "_" + SERVERINFODATAINFO->Get_tuiguang_ad_Channel();

	CSServerListPacket  packet(Get_Channel_ID(), version);
	packet.SendHttp();
}

	/*
		获取服务器列表_选服界面
	*/
void ServerInfoDataHandler::QueryServerListData_selServerWindow(){
	m_isSelServerWindow=true;
	NFC_showCommunicationWating(true);
	CurSendHttpPacketType_=_HTTP_STATE_NORMAL;

	std::string version = Get_GAME_Version();
	//安卓版本时会加上分发渠道号
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
		返回等登录界面
	*/
void ServerInfoDataHandler::LogoutGame(){
	SERVERINFODATAINFO->SetCurGameStatus(_TYPE_LOGIN_STATE_STANDBY_);
	DisconnectGameServer_Normal();
	DOTATribeApp::get_instance2()->ResetAllGame();
	DOTATribeApp::get_instance2()->SetActiveProcedure(DOTATribeApp::get_instance2()->m_pLoginProcedure);
}

	/*
		检查是否清空心跳计数器
	*/
bool ServerInfoDataHandler::CanResetCounter_HeartCheck(){
	bool condition1=GetCurGameStatus()!=_TYPE_LOGIN_STATE_GAMESERVER_SUCCESS_;
	bool condition2=GetCurGameStatus()!=_TYPE_LOGIN_STATE_GAMESERVER_ENTERGAME;
	//
	return condition1&&condition2;
}

	/*
		发送注册账号
	*/
void ServerInfoDataHandler::SendAccountRegister(){
	CSRegisterAccountPacket packet(GetGameLoginParam().m_Param0, GetGameLoginParam().m_Param1);
	packet.Send();	
}

	/*
		发送登陆请求
	*/
void ServerInfoDataHandler::SendAccountLogin(){
	DEBUGERSYSTEM->m_pNetDebuger->setAccount_Auth_Begin();
	LoginParams param = _getLoginParams();
	CSLoginPacket packet(param);
	packet.Send();
}

	/*
		连接游戏服务器
	*/
void ServerInfoDataHandler::ConnectToGameServer(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	NFC_showCommunicationWating_2(true);
#else
	NFC_showCommunicationWating(true);
#endif
	//设置当前游戏状态为连接游戏服务器
	SetCurGameStatus(_TYPE_LOGIN_STATE_GAMESERVER_CONNECT);
	WriteTheGameServerInfo(m_CurServerData);

	if(!NETSYSTEM->ReConnectServer()){
		NFC_showErrorTips(SysLangDataManager::get_instance2()->GetSysLangById(18));
	}
}

	/*
		清空游客账号信息
	*/
void ServerInfoDataHandler::DeleteVisitorAccountInfo(){
	SDKLoginParam param;
	param.m_iSdkType = SDKLoginParam::_platform_null_;
	LocalPlayerDataManager::get_instance2()->SetSdkLoginParam(param);
	LocalPlayerDataManager::get_instance2()->NeedSaveToDisk();
}

	/*
		清空所有帐号信息
	*/
void ServerInfoDataHandler::DeleteAllAccountInfo(){
	SDKLoginParam param;
	param.m_iSdkType = SDKLoginParam::_platform_null_;
	LocalPlayerDataManager::get_instance2()->SetSdkLoginParam(param);
	LocalPlayerDataManager::get_instance2()->NeedSaveToDisk();

}

	/*
		返回登录界面，注销账号信息
	*/
void ServerInfoDataHandler::LogoutAccountInfo(){
	if (!DOTATribeApp::get_instance2()->IsLoginProcedureAsActiveProcedure()){
		//不为登陆流程的时候
		LogoutGame();
		DeleteAllAccountInfo();
		m_nUserType=kSI_ATYPE_STANDBY;
	}
}

	/*
		当前用户是否为登陆状态
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
		服务器通知强行断开连接
	*/
void ServerInfoDataHandler::ForceDisconnect(){
	NETSYSTEM->ForceDisconnectWithGameServer();
}

	/*
		自行断开游戏服务器
	*/
void ServerInfoDataHandler::DisconnectGameServer_Normal(){
	//断掉游戏服务器
	NETSYSTEM->DisconnectSocket();
}

	/*
		处理断线重连
	*/
void ServerInfoDataHandler::HandleDisConnect(bool isreconnect){

	if (isreconnect){
		ConnectToGameServer();
	}else{	//不重连，返回主界面
		LOGGERSYSTEM->LogInfo("====_handleNetWorkDisconnect===_TYPE_LOGIN_STATE_GAMESERVER_ENTERGAME");
		BackToStartWindow();
	}
}

	/*
		返回登陆界面
	*/
void ServerInfoDataHandler::BackToStartWindow(){
	//=====游戏重置====
	DOTATribeApp::get_instance2()->ResetAllGame();
	SERVERINFODATAINFO->SetCurGameStatus(_TYPE_LOGIN_STATE_STANDBY_);
	DOTATribeApp::get_instance2()->SetActiveProcedure(DOTATribeApp::get_instance2()->m_pLoginProcedure);
}

	/*
		登陆流程初始化
	*/
void ServerInfoDataHandler::LoginProcedureInit(){
	if (SERVERINFODATAINFO->GetCurGameStatus()==_TYPE_LOGIN_STATE_UNKOWN_){//
		LOGGERSYSTEM->LogInfo("====LoginProcedure===_TYPE_LOGIN_STATE_UNKOWN_");
		QueryServerListData();
	}else if(SERVERINFODATAINFO->GetCurGameStatus()==_TYPE_LOGIN_STATE_GAMESERVER_ENTERGAME){
		LOGGERSYSTEM->LogInfo("====LoginProcedure===_TYPE_LOGIN_STATE_GAMESERVER_ENTERGAME");
		SERVERINFODATAINFO->CheckAccountBeforeEnterGame();//直接帮用户进游戏
	}else{//返回开始游戏界面待机
		LOGGERSYSTEM->LogInfo("====LoginProcedure===ELSE");
		SERVERINFODATAINFO->SetCurGameStatus(_TYPE_LOGIN_STATE_STANDBY_);
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEWINDOW_UI_SHOW_NORMAL);
	}
	//关闭socket断开提示窗
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_MESSAGEBOXWINDOW_);
}

	/*
		通知socket断开了
	*/
void ServerInfoDataHandler::NotifySocketClosed(){
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOCKETCLOSED_HINT);
}

	/*
		处理网络状态切换
		wifi <-> 非wifi
	*/
void ServerInfoDataHandler::NotifyNetworkChanged(){
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_NETWORKCHANGED_HINT);
}


	/*
		处理socket断开的后续问题
		#显示网络错误弹窗
		#需要处理socket断开的问题，调用这个函数
		#断网提示唯一函数
	*/
void ServerInfoDataHandler::HandleConnectServerFail(){
	LOGGERSYSTEM->LogInfo("=======ServerInfoDataHandler::HandleConnectServerFail=====");
	NFC_showCommunicationWating(false);
    EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_APPSTOREWAITWINDOW_);
	//再次保护，登录流程不显示断网提示
	if (!DOTATribeApp::get_instance2()->IsLoginProcedureAsActiveProcedure()){
		NFC_showMessageBox(kNETWORKDISCONNECTED,SysLangDataManager::get_instance2()->GetSysLangById(658));
	}
}

/*
	处理socket连接失败
*/
void ServerInfoDataHandler::HandleSocketConnectFail(){
	NFC_showCommunicationWating(false);
	if (!DOTATribeApp::get_instance2()->IsLoginProcedureAsActiveProcedure()){
		//不为登陆流程的时候
		LOGGERSYSTEM->LogInfo("ServerInfoDataHandler::HandleSocketConnectFail==Not In LoginProcedure,Show MessageBox");
		NFC_showMessageBox(kNETWORKDISCONNECTED,SysLangDataManager::get_instance2()->GetSysLangById(658));
	}else{
		LOGGERSYSTEM->LogInfo("ServerInfoDataHandler::HandleSocketConnectFail==In LoginProcedure,Show Tips");
		NFC_showErrorTips(SysLangDataManager::get_instance2()->GetSysLangById(440));
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_UPDATEWINDOW_UI_SHOW_NORMAL);
	}
}

	/*
		处理HTTP连接失败
	*/
void ServerInfoDataHandler::HandleHttpConnectFail(){
	if (CurSendHttpPacketType_==_HTTP_STATE_DISTINCT_)//强制要求返回结果的
	{
		NFC_showCommunicationWating(false);
		NFC_showMessageBoxSingle(kGATEWAY_CONNECTFAIL,SysLangDataManager::get_instance2()->GetSysLangById(710));
	}
	CurSendHttpPacketType_=_HTTP_STATE_UNKNOWN_;
}

//==============获取设备信息===========
	//获得设备操作系统
std::string ServerInfoDataHandler::Get_Device_OS(){
	return ENGINESYSTEM->GetOS();
}
	//获得设备ID
std::string ServerInfoDataHandler::Get_Device_ID()
{
	std::string deviceID = CCDirector::sharedDirector()->getSystem()->getDeviceUUID()+CCDirector::sharedDirector()->getSystem()->getDeviceIMEI();
	return deviceID;
}
	//获得上线平台
unsigned char ServerInfoDataHandler::Get_Channel_ID(){
	int sdktype = LocalPlayerDataManager::get_instance2()->GetSdkLoginParam().m_iSdkType;
	return sdktype;
}

std::string ServerInfoDataHandler::Get_tuiguang_ad_Channel()
{
	std::string temp;
	//安卓版本时会加上分发渠道号
	char channel[128] = "";
	VARIABLESYSTEM->GetVariable(VariableSystem::_TYPED_CONFIG_SYSTEM_, "Version", "Channel", channel, sizeof(channel));
	temp = channel;

	return temp;
}

	//操作系统版本
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
	//是否越狱   
unsigned char ServerInfoDataHandler::Get_Hacked(){
	return 0;
}


//==============登陆公告=================//
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

//登陆sdk
void ServerInfoDataHandler::LoginSdk(bool isExpired)
{
	CCDirector::sharedDirector()->getPlatform()->login(isExpired);
}

//从sdk登出
void ServerInfoDataHandler::LogoutSdk()
{
	CCDirector::sharedDirector()->getPlatform()->logout();
}

//显示Sdk账号中心
void ServerInfoDataHandler::ShowSdkCenter(){
	CCDirector::sharedDirector()->getPlatform()->ShowSDKCenter();
}

//显示SDK的悬浮窗
void ServerInfoDataHandler::ShowSuspendWindow(bool status)
{
	CCDirector::sharedDirector()->getPlatform()->ShowSuspendWindow(status);
}

//和外层共享玩家角色信息
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

//sdk登陆成功回调
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

//平台注销回调
void ServerInfoDataHandler::onLogoutCallBack(int sdkType, bool bSuccess, std::string param0, std::string param1, std::string param2, std::string param3, std::string param4
	, std::string param5, std::string param6, std::string param7, std::string param8, std::string param9){
		LogoutAccountInfo();
}

//登陆过期
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