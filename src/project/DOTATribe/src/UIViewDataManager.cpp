//Name：UIViewDataManager
//Written By：尹强

#include "../include/DOTATribeApp.h"
#include "../include/UIViewDataManger.h"
#include "../include/DBSystem.h"
#include <include/mem/DPacket.h>
#include <include/common/Parser.h>
#include "../include/DotaGameConfig.h"
#include "../include/LoggerSystem.h"
#include "../include/EngineSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/NodeFactoryManager.h"
#include "../include/FontStyleDataManager.h"
#include "../include/EngineSystem.h"
#include "../include/LuaSystem.h"

using  namespace  cobra_win;
using namespace std;

UIViewData::UIViewData()
:idx_(0)
,hide_(0)
,zorder_(0)
,scale_(0)
,rotation_(0)
,touchpriority_(0)
,swallow_(0)
,m_nSysLangID(0)
,m_nFontStyleID(0)
,fontsize_(0)
,colorR_(0)
,colorG_(0)
,colorB_(0)
,alpha_(0)
,width_(0)
,height_(0)
,anchorx_(0)
,anchory_(0)
,posx_(0)
,posy_(0)
,soundid_(-1)
{
	memset(class_,0,sizeof(class_));
	memset(fontname_,0,sizeof(fontname_));
	memset(filepath_,0,sizeof(filepath_));
	memset(filepath2_,0,sizeof(filepath2_));
	memset(filepath3_,0,sizeof(filepath3_));
}

bool  UIViewData::ParseBuffer(char* pBuffer, unsigned int iLen)
{
	bool isErr=false;
	Parser parser(pBuffer, iLen, '\t');

	if (!parser.parser_int_value(idx_))
		isErr=true;

	if(!parser.parser_int_value(hide_))
		isErr=true;

	if (!parser.parser_int_value(zorder_))
		isErr=true;

	if (!parser.parser_float_value(scale_))
		isErr=true;

	if (!parser.parser_float_value(rotation_))
		isErr=true;

	if(!parser.parser_string_value(class_,sizeof(class_)))
		isErr=true;

	if(!parser.parser_int_value(touchpriority_))
		isErr=true;

	if(!parser.parser_int_value(swallow_))
		isErr=true;

//~~~~~~~~~~读取labelstring~~~~~~~~~
	if(!parser.parser_int_value(m_nSysLangID))
		isErr=true;
	if (m_nSysLangID>0)
	{
		labelstring_=SysLangDataManager::get_instance2()->GetSysLangById(m_nSysLangID);
	}
//~~~~~~~~~~读取labelstring~~~~~~~~~

//~~~~~~~~~~读取fontstyle~~~~~~~~~
	if(!parser.parser_int_value(m_nFontStyleID))
		isErr=true;
//=============临时===========
	float fontsize_t;
	if(!parser.parser_float_value(fontsize_t))
		isErr=true;
//=============临时===========
	if(!parser.parser_int_value(colorR_))
		isErr=true;
	if(!parser.parser_int_value(colorG_))
		isErr=true;
	if(!parser.parser_int_value(colorB_))
		isErr=true;
	if (m_nFontStyleID>0)
	{
		FSData* fsd=FONTSTYLEDATAMANAGER->getDataByID(m_nFontStyleID);
		if (fsd)
		{
			strncpy(fontname_,fsd->fontname_,strlen(fsd->fontname_));
			fontsize_=fsd->fontsize_;
			colorR_=fsd->colorR_;
			colorG_=fsd->colorG_;
			colorB_=fsd->colorB_;
		}else
			strcpy(fontname_,"");
	}else{
		strcpy(fontname_,"");
	}
//~~~~~~~~~~需要读fontstyle属性的~~~~~~~~~

	if (!parser.parser_int_value(alpha_))
		isErr=true;

	if(!parser.parser_string_value(filepath_,sizeof(filepath_)))
		isErr=true;

	if(!parser.parser_string_value(filepath2_,sizeof(filepath2_)))
		isErr=true;

	if(!parser.parser_string_value(filepath3_,sizeof(filepath3_)))
		isErr=true;

	if(!parser.parser_float_value(width_))
		isErr=true;

	if(!parser.parser_float_value(height_))
		isErr=true;

	if(!parser.parser_float_value(anchorx_))
		isErr=true;

	if(!parser.parser_float_value(anchory_))
		isErr=true;

//=============================读取position=======================================
	float ip4_posx=0.0f;
	float ip4_posy=0.0f;
	float ip5_posx=0.0f;
	float ip5_posy=0.0f;
	float ipad_posx=0.0f;
	float ipad_posy=0.0f;
	float android_800_480_posx=0.0f;
	float android_800_480_posy=0.0f;
	float android_1280_800_posx = 0.0f;
	float android_1280_800_posy = 0.0f;

	if (!parser.parser_float_value(ip4_posx))
		isErr=true;

	if(!parser.parser_float_value(ip4_posy))
		isErr=true;

	if (!parser.parser_float_value(ip5_posx))
		isErr=true;

	if(!parser.parser_float_value(ip5_posy))
		isErr=true;

	if (!parser.parser_float_value(ipad_posx))
		isErr=true;

	if(!parser.parser_float_value(ipad_posy))
		isErr=true;

	if (!parser.parser_float_value(android_800_480_posx))
		isErr=true;

	if(!parser.parser_float_value(android_800_480_posy))
		isErr=true;

	if (!parser.parser_float_value(android_1280_800_posx))
		isErr=true;

	if(!parser.parser_float_value(android_1280_800_posy))
		isErr=true;

	int resolutionType=ENGINESYSTEM->GetLayoutConfig();
	if (resolutionType==kDEVICE_IPAD)
	{
		posx_=ipad_posx;
		posy_=ipad_posy;
	}else if(resolutionType==kDEVICE_IPHONE5){
		posx_=ip5_posx;
		posy_=ip5_posy;
	}else if(resolutionType==kDEVICE_IPHONE){
		posx_=ip4_posx;
		posy_=ip4_posy;
	}else if(resolutionType==kDEVICE_ANDROID){
		posx_=android_800_480_posx;
		posy_=android_800_480_posy;
	}
	else if(resolutionType == KDEVICE_ANDROID16_10)
	{
		posx_ = android_1280_800_posx;
		posy_ = android_1280_800_posy;
	}
	
//========================================================================
	if(!parser.parser_int_value(soundid_))
		isErr=true;

	if (isErr)
	{
		CCAssert(0,"Err: UIViewData read Error!");
		return false;
	}
	return true; 
}

template<> UIViewDataManager* cobra_win::Singleton2<UIViewDataManager>::m_pMySelf = NULL;
	/*
		载入文件
	*/
void UIViewDataManager::loadData(int idx){
	clearData();

	// 从数据库加载，不能每次动态加载
	if (m_bLoadFromDB)
	{
		//通过key值去找到所需的UI信息
		map<int,string>::iterator itbuffer = m_BufferList.find(idx);
		std::string struiData = itbuffer->second;
		UIViewLoad((char*)struiData.c_str(),struiData.length());
	}
	else
	{
		//动态加载
		map<int,string>::iterator it=m_fileList.find(idx);
		std::string strfile = it->second;
		std::string str = "";
		LoadFromFile((char*)strfile.c_str(),str);
		UIViewLoad((char*)str.c_str(),str.length());
	}
}

/*
		注册文件
*/
void UIViewDataManager::registerFile(int idx,std::string filename,std::string Encyfilename){
	if (DOTA_CONFIG_MODE==kMODE_DEBUG)
	{
		std::string strtemp = Encyfilename;

		char buff[128]={0};
		sprintf(buff,"%s%s%s","resource/layout/",strtemp.c_str(),".txt");
		strtemp = buff;
		if (filename != strtemp)
		{
			CCAssert(0,"registerFile Error");
		}
	}

	if(m_bLoadFromDB)
		m_EncyfileList.insert(map<int,string>::value_type(idx,Encyfilename));
	else
		m_fileList.insert(map<int,string>::value_type(idx,filename));
}

/*
	自动create节点根据表中每一行
*/
void UIViewDataManager::AutoCreateNodeByTable(int key,cocos2d::CCNode* parentNode){
	assert(parentNode!=NULL);
	loadData(key);
	map<int,UIViewData*>::iterator it=m_dataList.begin();
	map<int,UIViewData*>::iterator it_end=m_dataList.end();
	for (;it!=it_end;it++)
	{
		ACNODEFACTORYMANAGER->createNodeByKey(it->second,parentNode);
	}
	clearData();
}

void UIViewDataManager::AutoCreateNodeByTable(int key, cocos2d::CCNode * parentNode, float offsetX, int times)
{
	assert(parentNode!=NULL);
	loadData(key);
	map<int,UIViewData*>::iterator it=m_dataList.begin();
	map<int,UIViewData*>::iterator it_end=m_dataList.end();
	for (;it!=it_end;it++)
	{
		it->second->posx_ += offsetX * times;
		//it->second->posy_ += offsetY * times;
		ACNODEFACTORYMANAGER->createNodeByKey(it->second,parentNode);
	}
	clearData();
}

UIViewData * UIViewDataManager::getControlDataByID(int idx){
	std::map<int,UIViewData*>::iterator shapeIter=m_dataList.find(idx);
	if(shapeIter!=m_dataList.end())
	{
		return shapeIter->second;
	}
	return NULL; 
}

std::string   UIViewDataManager::GetName()
{ 
	return m_filename;
} 


unsigned  int UIViewDataManager::GetSize()
{
	return m_dataList.size()*sizeof(UIViewData);
}


bool  UIViewDataManager::Init()
{
	//载入文件

	/**
		大家注意了：以后再用UIViewDATA的时候注册的时候传上参数，第三个参数是加密时UI布局加密文件名称
	*/
	//=============Public Controls=============//
	registerFile(kPUBLIC_ROLESTATUSBAR,"resource/layout/ll_dota_rolestatusbar_layout.txt","ll_dota_rolestatusbar_layout");
	//=============LogoWindow Just For Android=============//
	registerFile(kANDROID_LOGOWINDOW,"resource/layout/ll_logowindow_layout.txt","ll_logowindow_layout");
	//===================Game Window================//
	registerFile(kROLESTATUSWINDOW,"resource/layout/ll_rolestatuswindow_layout.txt","ll_rolestatuswindow_layout");
	registerFile(kHOMEWINDOW,"resource/layout/ll_homewindow_layout.txt","ll_homewindow_layout");
	registerFile(kHOMEWINDOW_MAP,"resource/layout/ll_homewindow_homemap_layout.txt","ll_homewindow_homemap_layout");
	registerFile(kSTARTWINDOW,"resource/layout/ll_startwindow_layout.txt","ll_startwindow_layout");

	//begin:HeroWindow
	registerFile(kHEROWINDOW,"resource/layout/ll_herowindow_layout.txt","ll_herowindow_layout");
	registerFile(kHEROEQUIP,"resource/layout/ll_heroequip_layout.txt","ll_heroequip_layout");
	registerFile(kHEROEQUIPCELL,"resource/layout/ll_heroequipcell_layout.txt","ll_heroequipcell_layout");
	registerFile(kHEROEQUIP_ROLEINFO,"resource/layout/ll_heroequip_info_layout.txt","ll_heroequip_info_layout");
	registerFile(kHEROEQUIP_HERODETAIL,"resource/layout/ll_heroequip_detail_layout.txt","ll_heroequip_detail_layout");
	registerFile(kHEROEQUIP_LINKNODE,"resource/layout/ll_heroequip_linknode_layout.txt","ll_heroequip_linknode_layout");
	registerFile(kLEADERSHIPLVUPWINDOW,"resource/layout/ll_leadershiplvupwindow_layout.txt","ll_leadershiplvupwindow_layout");
	//end
	registerFile(kMASSACREVIEW,"resource/layout/ll_massacre_layout.txt","ll_massacre_layout");
	registerFile(kEQUIPTIPS,"resource/layout/ll_equip_tips_curequipnode_layout.txt","ll_equip_tips_curequipnode_layout");
	registerFile(kEQUIPCOMPARE,"resource/layout/ll_equip_tips_equipednode_layout.txt","ll_equip_tips_equipednode_layout");
	registerFile(kOBJECTTIPS,"resource/layout/ll_objecttips_layout.txt","ll_objecttips_layout");
	registerFile(KSELECTSKILLVIEW,"resource/layout/ll_selectskill_layout.txt","ll_selectskill_layout");
	registerFile(KSKILLTIPSVIEW,"resource/layout/ll_skilltips_layout.txt","ll_skilltips_layout");
	 
	registerFile(kSELECTSERVERWINDOW,"resource/layout/ll_selectserver_layout.txt","ll_selectserver_layout");
	
	registerFile(kSERVERROOTCELL,"resource/layout/ll_selectserverrootcell_layout.txt","ll_selectserverrootcell_layout");


	registerFile(kMESSAGEBOXWINDOW,"resource/layout/ll_messagebox_layout.txt","ll_messagebox_layout");

	registerFile(kINPUTNUMWINDOW, "resource/layout/ll_inputnum_layout.txt","ll_inputnum_layout");
	
	registerFile(kEQUIPPROMOTEVIEW, "resource/layout/ll_equippromoteview_layout.txt","ll_equippromoteview_layout");
	//begin:Strengthen
	registerFile(kSTRENGTHENWINDOW,"resource/layout/ll_strengthenwindow_layout.txt","ll_strengthenwindow_layout");
	registerFile(kSTRENGTHENWINDOW_CELL,"resource/layout/ll_strengthenwindowcell_layout.txt","ll_strengthenwindowcell_layout");
	registerFile(kEQUIPLVUPVIEW, "resource/layout/ll_equiplvupview_layout.txt","ll_equiplvupview_layout");
	registerFile(kEQUIPLVUPVIEWCELL, "resource/layout/ll_equiplvupviewcell_layout.txt","ll_equiplvupviewcell_layout");
	registerFile(kEQUIPMENTSELECTCARDWINDOW, "resource/layout/ll_equipmentselectcard_layout.txt","ll_equipmentselectcard_layout");
	registerFile(kEQUIPMENTSELECTCARDWINDOWCELL, "resource/layout/ll_equipmentselectcardcell_layout.txt","ll_equipmentselectcardcell_layout");
	registerFile(kEQUIPRECASTVIEW,"resource/layout/ll_equipsrecast_layout.txt","ll_equipsrecast_layout");
	//end

	//begin:SystemSetting
	registerFile(kSYSTEMSETWINDOW,"resource/layout/ll_systemsetguest_layout.txt","ll_systemsetguest_layout");
	//end

	registerFile(kARENAVIEW,"resource/layout/ll_arena_layout.txt","ll_arena_layout");

	registerFile(kEQUIPTRAINVIEW, "resource/layout/ll_equiptrainview_layout.txt","ll_equiptrainview_layout");

	registerFile(kNOTICEBOXWINDOW,"resource/layout/ll_noticeboxwindow_layout.txt","ll_noticeboxwindow_layout");

	registerFile(kNOTICEBOXGATEWAYWINDOW,"resource/layout/ll_gatewaynoticeboxwindow_layout.txt","ll_gatewaynoticeboxwindow_layout");

	registerFile(kCHAT,"resource/layout/ll_chat_layout.txt","ll_chat_layout");
	registerFile(kCHAT_CELL_,"resource/layout/ll_chat_cell_layout.txt","ll_chat_cell_layout");
	registerFile(kCHAT_POP_,"resource/layout/ll_chat_pop_layout.txt","ll_chat_pop_layout");

	registerFile(KARENAVIEWCELL,"resource/layout/ll_arenalistcell_layout.txt","ll_arenalistcell_layout");
 
	registerFile(KARENARANKLISTVIEW,"resource/layout/ll_rankinglist_layout.txt","ll_rankinglist_layout");
	registerFile(KARENARANKCELL,"resource/layout/ll_rankingcell_layout.txt","ll_rankingcell_layout");
	
	registerFile(kMARKETWINDOW,"resource/layout/ll_marketwindow_layout.txt","ll_marketwindow_layout");
	registerFile(kSHOPWINDOW,"resource/layout/ll_shopwindow_layout.txt","ll_shopwindow_layout");
	registerFile(kSHOPVIEW,"resource/layout/ll_shopview_layout.txt","ll_shopview_layout");
	registerFile(kSHOPVIEWCELL,"resource/layout/ll_shopviewcell_layout.txt","ll_shopviewcell_layout");
	registerFile(kRANDOMSHOPINFONODE,"resource/layout/ll_randominfonode_layout.txt","ll_randominfonode_layout");
	registerFile(kRANDOMSHOPCELL,"resource/layout/ll_randomshopcell_layout.txt","ll_randomshopcell_layout");

	registerFile(kEFFECTWINDOW,"resource/layout/ll_effectwindow_layout.txt","ll_effectwindow_layout");
	registerFile(kSELECTROLEWINDOW,"resource/layout/ll_selectrolewindow_layout.txt","ll_selectrolewindow_layout");
 
	registerFile(kCLIMBTOWERVIEW, "resource/layout/ll_climbtower_layout.txt","ll_climbtower_layout");
	registerFile(kCLIMBTOWERVIEWBEGIN, "resource/layout/ll_climbtower_begin_layout.txt","ll_climbtower_begin_layout");
	registerFile(kCLIMBTOWERVIEWEND, "resource/layout/ll_climbtower_end_layout.txt","ll_climbtower_end_layout");
	registerFile(kCLIMBTOWERFIGHTRESULT, "resource/layout/ll_climbtower_fightresult_layout.txt", "ll_climbtower_fightresult_layout");//新增
	registerFile(kCLIMBTOWERFIGHTRESULTCELL, "resource/layout/ll_climbtower_fightresult_cell_layout.txt", "ll_climbtower_fightresult_cell_layout");//新增
	registerFile(kCLIMBTOWERREWARD, "resource/layout/ll_climbtower_reward_layout.txt", "ll_climbtower_reward_layout");//新增
	registerFile(kCLIMBTOWERREWARDCELL, "resource/layout/ll_climbtower_reward_cell_layout.txt", "ll_climbtower_reward_cell_layout");//新增
	
	registerFile(kGUIDEWINDOW, "resource/layout/ll_guidewindow_layout.txt","ll_guidewindow_layout");
	
	registerFile(kBAGWINDOW, "resource/layout/ll_bagwindow_layout.txt","ll_bagwindow_layout");
	registerFile(kBAGWINDOWOBJECTLIST, "resource/layout/ll_bagwindow_objectlist_layout.txt","ll_bagwindow_objectlist_layout");
	registerFile(kBAGWINDOWCOMPOSELIST, "resource/layout/ll_bagwindow_composelist_layout.txt","ll_bagwindow_composelist_layout");


	registerFile(kBAGWINDOWRIGHTPANELITEM, "resource/layout/ll_bagwindow_rightpage_layout.txt","ll_bagwindow_rightpage_layout");
	registerFile(kBAGWINDOWRIGHTPANELPOSITION, "resource/layout/ll_bagwindow_rightpanel_position_layout.txt","ll_bagwindow_rightpanel_position_layout");
	registerFile(kSHOPINPUTNUMWINDOW, "resource/layout/ll_shopinputnum_layout.txt","ll_shopinputnum_layout");
	registerFile(kREVENUEWINDOW, "resource/layout/ll_revenue_layout.txt","ll_revenue_layout");
	registerFile(kLESSRESOURCEWINDOW, "resource/layout/ll_lessresource_layout.txt","ll_lessresource_layout");

	registerFile(kTIPSWINDOW, "resource/layout/ll_tipswindow_layout.txt","ll_tipswindow_layout");
	registerFile(kNPCTALKVIEW, "resource/layout/ll_npctalk_layout.txt","ll_npctalk_layout");


	registerFile(kSELECTSONMISSIONWINDOW,"resource/layout/ll_selectsonmission_layout.txt","ll_selectsonmission_layout");
	registerFile(kSELECTSONCELL,"resource/layout/ll_custom_cell_layout.txt","ll_custom_cell_layout");
 
	registerFile(kVIPVIEW,"resource/layout/ll_vipview_layout.txt","ll_vipview_layout");
	registerFile(kVIPVIEWLAYER,"resource/layout/ll_vipviewlayer_layout.txt","ll_vipviewlayer_layout");

	registerFile(kSHOPTIPS,"resource/layout/ll_shoptips_layout.txt","ll_shoptips_layout");
	registerFile(kFRIENDWINDOW,"resource/layout/ll_friendwindow_layout.txt","ll_friendwindow_layout");
	
	registerFile(kTEAMBATTLE, "resource/layout/ll_teambattle_layout.txt","ll_teambattle_layout");
	registerFile(kTEAMBATTLECELL, "resource/layout/ll_teambattlecell_layout.txt","ll_teambattlecell_layout");
	registerFile(kTEAMSELECT, "resource/layout/ll_teamselect_layout.txt","ll_teamselect_layout");
	registerFile(kTEAMSELECTCELL, "resource/layout/ll_teamselectcell_layout.txt","ll_teamselectcell_layout");
	registerFile(kTEAMBATTLEGATEREWARD, "resource/layout/ll_teambattle_gatereward_layout.txt","ll_teambattle_gatereward_layout");
	registerFile(kTEAMSELECTVIEWLIST, "resource/layout/ll_teamselect_viewlist_layout.txt","ll_teamselect_viewlist_layout");
	registerFile(kTEAMSELECTVIEWCELL_SLAVE, "resource/layout/ll_teamselect_viewlistcell_slave_layout.txt","ll_teamselect_viewlistcell_slave_layout");
	registerFile(kTEAMSELECTVIEWCELL_MERCENARY, "resource/layout/ll_teamselect_viewlistcell_mercenary_layout.txt","ll_teamselect_viewlistcell_mercenary_layout");

	registerFile(kPLAYERTIPSWINDOW, "resource/layout/ll_playertipswindow_layout.txt","ll_playertipswindow_layout");
	registerFile(kEMAILWINDOW,"resource/layout/ll_emailwindow_layout.txt","ll_emailwindow_layout");
	registerFile(kEMAILWINDOWCELL,"resource/layout/ll_emailwindowcell_layout.txt","ll_emailwindowcell_layout");
	registerFile(kEMAILWINDOWATTACHMENTCELL,"resource/layout/ll_emailattachmentcell_layout.txt","ll_emailattachmentcell_layout");
	registerFile(kEQUIPTIPSWINDOW,"resource/layout/ll_equip_tips_layout.txt","ll_equip_tips_layout");
	registerFile(kEMAILWRITELETTERWINDOW,"resource/layout/ll_emailwriteletter_layout.txt","ll_emailwriteletter_layout");
	registerFile(kRECHARGEWINDOW,"resource/layout/ll_rechargewindow_layout.txt","ll_rechargewindow_layout");
	registerFile(kRECHARGEWARNWINDOW,"resource/layout/ll_rechargewarnwindow_layout.txt","ll_rechargewarnwindow_layout");
	registerFile(kTEMPLEWINDOW,"resource/layout/ll_templewindow_layout.txt","ll_templewindow_layout");
	registerFile(kCONVICTIONWINDOW,"resource/layout/ll_convictionwindow_layout.txt","ll_convictionwindow_layout");
	registerFile(kALTARWINDOW,"resource/layout/ll_heroaltarwindow_layout.txt","ll_heroaltarwindow_layout");
	registerFile(kALTARDEBRISWINDOW,"resource/layout/ll_altarnode_layout.txt","ll_altarnode_layout");
	registerFile(kHEROSUMMONWINDOW,"resource/layout/ll_herosummon_layout.txt","ll_herosummon_layout");
	registerFile(kHEROHOLYNODE,"resource/layout/ll_heroholycall_layout.txt","ll_heroholycall_layout");
	registerFile(kGAINHEROWINDOW,"resource/layout/ll_gainhero_layout.txt","ll_gainhero_layout");
	registerFile(kGAINSOULDEBRIWINDOW,"resource/layout/ll_gainsouldebri_layout.txt","ll_gainsouldebri_layout");
	registerFile(kTENCALLWINDOW,"resource/layout/ll_tencallwindow_layout.txt","ll_tencallwindow_layout");
	registerFile(kGAINCALLITEMWINDOW,"resource/layout/ll_gainitem_layout.txt","ll_gainitem_layout");
	registerFile(kMISSIONWINDOW,"resource/layout/ll_mission_layout.txt","ll_mission_layout");
	registerFile(kCHECKLEADERSHIPWINDOW,"resource/layout/ll_checkleadership_layout.txt","ll_checkleadership_layout");
	registerFile(kLEVELUPNORMALWINDOW,"resource/layout/ll_levelupnormal_layout.txt","ll_levelupnormal_layout");
	registerFile(kATHLETICRESULTWINDOW,"resource/layout/ll_athleticresult_layout.txt","ll_athleticresult_layout");
	
	
	//活动窗口
	registerFile(kACTIVITYWINDOW,"resource/layout/ll_activitywindow_layout.txt","ll_activitywindow_layout");
	registerFile(kSPRINGVIEW,"resource/layout/ll_springview_layout.txt","ll_springview_layout");
	
	//帮助
	registerFile(kSELECTSKILL_HELP_, "resource/layout/ll_selectskillhelpwindow_layout.txt","ll_selectskillhelpwindow_layout");
	registerFile(kSTRENGTHEN_HELP_,"resource/layout/ll_strengthenhelpwindow_layout.txt","ll_strengthenhelpwindow_layout");
	registerFile(kEQUIPMENT_HELP_,"resource/layout/ll_equipmenthelpwindow_layout.txt","ll_equipmenthelpwindow_layout");
	registerFile(kARENA_HELP_,"resource/layout/ll_arenahelpwindow_layout.txt","ll_arenahelpwindow_layout");
	registerFile(kHEROTECHNOLOGY_HELP_,"resource/layout/ll_herotechnologyhelp_layout.txt","ll_herotechnologyhelp_layout");
	registerFile(kSERVANT_HELP_,"resource/layout/ll_servantwindowhelp_layout.txt","ll_servantwindowhelp_layout");
	registerFile(kSLAVE_HELP_,"resource/layout/ll_slavewindowhelp_layout.txt","ll_slavewindowhelp_layout");
	registerFile(kTEAMBATTLE_HELP_,"resource/layout/ll_teambattlehelp_layout.txt","ll_teambattlehelp_layout");
	//end

	registerFile(kPUCONGWINDOW, "resource/layout/ll_pucongwindow_layout.txt", "ll_pucongwindow_layout");
	
	//仆从,begin
	registerFile(kSERVANTWINDOW, "resource/layout/ll_servantwindow_layout.txt","ll_servantwindow_layout");
	registerFile(kSERVANTMASTERPAGE0, "resource/layout/ll_servant_masterpage0_layout.txt","ll_servant_masterpage0_layout");
	registerFile(kSERVANTMASTERPAGE0_CELL, "resource/layout/ll_servant_masterpage0_cell_layout.txt","ll_servant_masterpage0_cell_layout");
	registerFile(kSERVANTMASTERPAGE1, "resource/layout/ll_servant_masterpage1_layout.txt","ll_servant_masterpage1_layout");
	registerFile(kSERVANTMASTERPAGE2, "resource/layout/ll_servant_masterpage2_layout.txt","ll_servant_masterpage2_layout");
	registerFile(kSERVANTMASTERPAGE2_CELL, "resource/layout/ll_servant_masterpage2_cell_layout.txt","ll_servant_masterpage2_cell_layout");
	registerFile(kSERVANTSLAVEPAGE0, "resource/layout/ll_servant_slavepage0_layout.txt","ll_servant_slavepage0_layout");
	registerFile(kSERVANTSLAVEPAGE1, "resource/layout/ll_servant_slavepage1_layout.txt","ll_servant_slavepage1_layout");
	registerFile(kSERVANTSLAVEPAGE2, "resource/layout/ll_servant_slavepage2_layout.txt","ll_servant_slavepage2_layout");
	registerFile(kSERVANTSLAVEPAGE2_CELL, "resource/layout/ll_servant_slavepage2_cell_layout.txt","ll_servant_slavepage2_cell_layout");
	registerFile(kSERVANT_MASTER_NEWS_CELL, "resource/layout/ll_servant_master_news_cell_layout.txt","ll_servant_master_news_cell_layout");
	registerFile(kSERVANT_SLAVE_NEWS_CELL, "resource/layout/ll_servant_slave_news_cell_layout.txt","ll_servant_slave_news_cell_layout");
	//end

	//综合任务， begin
	registerFile(kMAINTASKWINDOW, "resource/layout/ll_maintaskwindow_layout.txt", "ll_maintaskwindow_layout");
	registerFile(kTASKLISTCELL, "resource/layout/ll_taskcell_layout.txt", "ll_taskcell_layout");
	registerFile(kFORCEPUSHREWARDWINDOW, "resource/layout/ll_forcepushreward_layout.txt", "ll_forcepushreward_layout");
	//end

	//限时活动，begin
	registerFile(kLIMITEDACTIVITY,"resource/layout/ll_limitedactivitywindow_layout.txt","ll_limitedactivitywindow_layout");
	registerFile(kLIMITEDACTIVITY_ACTVITY,"resource/layout/ll_limitedactivitywindow_activity_layout.txt","ll_limitedactivitywindow_activity_layout");
	registerFile(kLIMITEDACTIVITY_CELL_L,"resource/layout/ll_limitedactivitywindowcell_layout.txt","ll_limitedactivitywindowcell_layout");
	registerFile(kLIMITEDACTIVITY_NOTICEBOX,"resource/layout/ll_limitedactivitywindow_noticebox_layout.txt","ll_limitedactivitywindow_noticebox_layout");
	registerFile(kLIMITEDACTIVITY_EXCHANGE, "resource/layout/ll_limiteactivitywindow_exchange_layout.txt","ll_limiteactivitywindow_exchange_layout");
	//end

	//矿洞，begin
	registerFile(kMININGWINDOW, "resource/layout/ll_miningwindow_layout.txt","ll_miningwindow_layout");
	registerFile(kHUNTWINDOW, "resource/layout/ll_huntwindow_layout.txt", "ll_huntwindow_layout");
	registerFile(kGOBLINAREAWINDOW, "resource/layout/ll_minearea_goblin_layout.txt", "ll_minearea_goblin_layout");
	registerFile(kDWARVENAREAWINDOW, "resource/layout/ll_minearea_dwarven_layout.txt", "ll_minearea_dwarven_layout");
	registerFile(kDRAGONAREAWINDOW, "resource/layout/ll_minearea_dragon_layout.txt", "ll_minearea_dragon_layout");
	registerFile(kHUNTMININGWINDOW, "resource/layout/ll_minearea_hunt_layout.txt", "ll_minearea_hunt_layout");
	//end

	//英雄图鉴 begin
	registerFile(kHeroIllustratedWindow, "resource/layout/ll_heroillustrated_layout.txt", "ll_heroillustrated_layout");
	registerFile(kHerolllustratedStarCell, "resource/layout/ll_hero_star_cell.txt", "ll_hero_star_cell");
	registerFile(kHeroIllustratedHeroCell, "resource/layout/ll_hero_cell.txt", "ll_hero_cell");

	//英雄进阶 begin
	registerFile(kHeroAdvancedWindow, "resource/layout/ll_heroadvanced_layout.txt", "ll_heroadvanced_layout");
	//end
	//begin:网络等待界面
	registerFile(kCOMMUNICATINGWINDOW,"resource/layout/ll_communicatingwindow_layout.txt","ll_communicatingwindow_layout");
	//end
	 
	//战斗界面
	registerFile(kAthleticsWindow,"resource/layout/ll_athletics_layout.txt","ll_athletics_layout");

	//多个物品奖励窗口
	registerFile(kMULTIREWARDWINDOW,"resource/layout/ll_multirewardwindow_layout.txt","ll_multirewardwindow_layout");

	//竞技场奖励窗口
	registerFile(kARENAREWARDWINDOW,"resource/layout/ll_arenaresult_layout.txt","ll_arenaresult_layout");
	registerFile(kARENAREWARDCELL,"resource/layout/ll_arenaresultcell_layout.txt","ll_arenaresultcell_layout");
	  
	//首充界面窗口
	registerFile(kFIRSTRECHWINDOW,"resource/layout/ll_firstrechwindow_layout.txt","ll_firstrechwindow_layout");
	registerFile(kFIRSTRECHCELL,"resource/layout/ll_firstrechgiftcell_layout.txt","ll_firstrechgiftcell_layout");

	registerFile(kNEWEQUIPREMINDWINDOW,"resource/layout/ll_newequipremind_layout.txt","ll_newequipremind_layout");
	 
	//升级奖励活动窗口
	registerFile(kLEVELUPREWARDACTIVITYWINDOW,"resource/layout/ll_leveluprewardview_layout.txt","ll_leveluprewardview_layout");
	registerFile(kLEVELUPREWARDACTIVITYCELL,"resource/layout/ll_leveluprewardcell_layout.txt","ll_leveluprewardcell_layout");


	//战魂窗口配置
	registerFile(kHEROSOULWINDOW,"resource/layout/ll_herosoul_layout.txt","ll_herosoul_layout");
	 
	
	//boss积分
	registerFile(kBOSSSCOREWINDOW, "resource/layout/ll_bossscore_layout.txt","ll_bossscore_layout");
	registerFile(KBOSSSCOREREWARDWINDOW, "resource/layout/ll_bossscore_reward_layout.txt","ll_bossscore_reward_layout");
	registerFile(kBOSSSCOREREWARDCELL, "resource/layout/ll_bossscore_rewardcell_layout.txt","ll_bossscore_rewardcell_layout");

	//战魂装备
	registerFile(kSOULEQUIPVIEW, "resource/layout/ll_soulequip_layout.txt","ll_soulequip_layout");
	registerFile(kSOULEQUIPCELL, "resource/layout/ll_soulequipcell_layout.txt","ll_soulequipcell_layout");
	 
	 
	//每日登陆奖励窗口
	registerFile(kLOGINACTIVITYWINDOW, "resource/layout/ll_loginactivitywindow_layout.txt","ll_loginactivitywindow_layout");
	registerFile(kLOGINACTIVITYCELL, "resource/layout/ll_loginactivitycell_layout.txt","ll_loginactivitycell_layout");
	//成长计划活动窗口
	registerFile(kGROWUPPLANACTIVITYWINDOW, "resource/layout/ll_growupplanwindow_layout.txt","ll_growupplanwindow_layout");
	registerFile(kGROWUPPLANAREWARDCELL, "resource/layout/ll_growuprewardcell_layout.txt","ll_growuprewardcell_layout");

	//兑换奖励窗口
	registerFile(kEXCHANGEACTIVITYWINDOW, "resource/layout/ll_exchangeactivity_layout.txt","ll_exchangeactivity_layout");
	registerFile(kEXCHANGEACTIVITYCELL, "resource/layout/ll_exchangeactivityxell_layout.txt","ll_exchangeactivityxell_layout");
	//战魂tips
	registerFile(kHEROSOULTIPSWINDOW, "resource/layout/ll_soul_tips_layout.txt","ll_soul_tips_layout");

	//app支付等待窗口
	registerFile(kAPPSTOREWAITWINDOW, "resource/layout/ll_appstorewaitwindow_layout.txt","ll_appstorewaitwindow_layout");
	//Vip礼包窗口
	registerFile(kVIPGIFTWINDOW, "resource/layout/ll_vipgiftwindow_layout.txt","ll_vipgiftwindow_layout");
	registerFile(kVIPGIFTCELL, "resource/layout/ll_vipgiftcell_layout.txt","ll_vipgiftcell_layout");

	//Loading窗口
	registerFile(kLOADINGWINDOW,"resource/layout/ll_loadingwindow_layout.txt","ll_loadingwindow_layout");
	//队伍信息窗口
	registerFile(kTEAMINFOWINDOW,"resource/layout/ll_teaminfowindow_layout.txt","ll_teaminfowindow_layout");
	registerFile(kTEAMHEROSHOWNODE,"resource/layout/ll_heroinfonode_layout.txt","ll_heroinfonode_layout");
	
	//LUASYSTEM->RegisterLuaViewFile();

	// 如果是从数据库加载
	if (m_bLoadFromDB)
	{
		std::map<int,std::string>::iterator iter   = m_EncyfileList.begin();
		std::map<int,std::string>::iterator iter_e = m_EncyfileList.end();
		for ( ; iter!=iter_e; ++iter)
		{
			int type = iter->first;
			std::string tableName = iter->second;
			
			std::string str = "";
			// 从数据库
			LoadFromDB((char*)tableName.c_str(),str);
			
			m_BufferList.insert(map<int,string>::value_type(type,str));
		}
	}
	
	return true;
}


void  UIViewDataManager::Tick()
{

}


void  UIViewDataManager::Destroy()
{
	//清除文件list
	m_fileList.clear();
	//清除datalist
	clearData();
} 

/*
	清除内存
*/
void UIViewDataManager::clearData(){
	std::map<int, UIViewData*>::iterator iter   = m_dataList.begin();
	std::map<int, UIViewData*>::iterator iter_e = m_dataList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		delete iter->second;
	}
	m_dataList.clear();
}


bool  UIViewDataManager::Varify(IData* pData)
{
	if (!DBSYSTEM->IsNeedVerify())
		return true;

	UIViewData* pEquipItem = (UIViewData*)pData;
	assert(pEquipItem != NULL);

	return true;
}

bool  UIViewDataManager::VarifyAfterLoadAll()
{
	return true;
}

bool  UIViewDataManager::LoadData(char* pBuffer, unsigned int iBufferLen)
{

	UIViewData* pItemData = new UIViewData();
	if (!pItemData->ParseBuffer(pBuffer, iBufferLen))
	{
		delete pItemData;
		pItemData = NULL;
		return false;
	}

	if (!Varify(pItemData))
	{
		delete pItemData;
		pItemData = NULL;
		return false;
	}

	m_dataList.insert(std::map<int, UIViewData*>::value_type(pItemData->idx_, pItemData));

	return true;
}

/*
	从文件加载对应的资源
*/
bool  UIViewDataManager::LoadFromFile(char* filename,std::string& buffer)
{
	char * m_pLayoutText = NULL;
	unsigned int iLength = 0;
	if (!EngineSystem::LoadAppFile(filename, m_pLayoutText, iLength))
		return false;

	// 先进行解密
	if (m_bEncryption)
		DBSYSTEM->XORBuffer((char*)DBSYSTEM->GetEncryptionKey().c_str(), m_pLayoutText, iLength);

	buffer = m_pLayoutText;
	if (m_pLayoutText!=NULL)
	{
		delete []m_pLayoutText;
		m_pLayoutText = NULL;
	}

	return true;
}
/*
	从数据库加载对应的资源
*/
bool  UIViewDataManager::LoadFromDB(char* Encyname,std::string& buffer)
{
	
	char * m_pLayoutText = NULL;
	unsigned int iLength = 0;
	if (!DBSystem::LoadUIDBTable(Encyname, m_pLayoutText, iLength))
		return false;

	// 先进行解密
	if (m_bEncryption)
		DBSYSTEM->XORBuffer((char*)DBSYSTEM->GetEncryptionKey().c_str(), m_pLayoutText, iLength);

	buffer = m_pLayoutText;

	if (m_pLayoutText!=NULL)
	{
		delete []m_pLayoutText;
		m_pLayoutText = NULL;
	}
	return true;
}


/*
	解析字符串资源
*/
bool UIViewDataManager::UIViewLoad(char* pBuffer,unsigned int iLength)
{
	// 构建DPacket解包器
	DPacket packet(pBuffer, iLength+1);

	// 跳过第一行
	char   buffer[10240] = "";
	size_t pos = 0;
	do 
	{
		if (pos == sizeof(buffer))
			return false;

		if (packet.get_read_pos() >= packet.size())
			return false;

		packet.read(buffer+pos, 1);
		if (pos>0 && *(buffer+pos)=='\r')
			break;

		pos++;
	}
	while(true);

	// 逐行读取解析
	do 
	{
		char   buffer[10240] = "";
		size_t num           = 0;
		bool   reset         = false;

		{
			size_t pos = 0;
			do 
			{
				if (pos == sizeof(buffer))
				{
					reset = true;
					break;
				}

				if (packet.get_read_pos() >= packet.size())
					break;

				packet.read(buffer+pos, 1);
				if (pos>0 && *(buffer+pos)=='\n')
				{
					if (*(buffer+pos-1) == '\r')
					{
						*(buffer+pos-1) = '\0';
					}

					*(buffer+pos) = '\0';
					num = pos;
					break;
				}

				pos++;
			}
			while(true);
		}

		if (reset || num<=2)
			break;

		if (!LoadData(buffer, num-1))
			return false;

		;
	}
	while (true);
	return true;
}