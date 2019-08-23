//Name：UIViewDataManager
//Written By：尹强

#ifndef   _DOTATRIBE_UIVIEWDATAMANAGER_H
#define   _DOTATRIBE_UIVIEWDATAMANAGER_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>
#include <cocos2d.h>

#pragma pack(push, 1)
/*
	所有UI布局的表的列必须统一
*/
class   UIViewData: public IData
{
private:
	int m_nSysLangID;						//文字ID
public:
	int idx_;		//控件索引
	int hide_;		//0:显示 1:隐藏
	int zorder_;	//层次
	float scale_;	//缩放
	float rotation_;	//旋转
	char class_[128];		//类型
	int touchpriority_;	//暂时被fontsize_替代
	int swallow_;				//暂时被colorR替代
	int m_nFontStyleID;					//FontyStyleID
	std::string labelstring_;
	char fontname_[128];		//font字体名
	float fontsize_;			//label 字体大小;		如果是menuitem则为priority
	int colorR_;				//RGB-R;					如果是menuitem则为1:不swallow，0：swallow
	int colorG_;				//RGB-G
	int colorB_;				//RGB-B
	int alpha_;				//alpha值
	char filepath_[128];	//图片路径
	char filepath2_[128];	//图片路径
	char filepath3_[128];	//图片路径
	float width_;
	float height_;
	float anchorx_;			
	float anchory_;
	float posx_;
	float posy_;
	int soundid_;		//如果需要声音的事件，否则为-1
public:
	UIViewData();
	virtual~UIViewData(){};

public:
	 
	virtual  bool  ParseBuffer(char* pBuffer, unsigned int iLen);
};

#pragma pack(pop)
 


class UIViewDataManager : public IDataManager, public cobra_win::Singleton2<UIViewDataManager>
{
public:
	enum{
//#################Public Node####################
		kPUBLIC_ROLESTATUSBAR=0,
//#################LogoWindow Just For Android####################
		kANDROID_LOGOWINDOW,
//#################Game View####################
		kROLESTATUSWINDOW,
		kHOMEWINDOW,
		kHOMEWINDOW_MAP,
		kSTARTWINDOW,
		kHEROWINDOW,
		kHEROEQUIP,
		kHEROEQUIPCELL,
		kHEROEQUIP_ROLEINFO,
		kHEROEQUIP_HERODETAIL,
		kHEROEQUIP_LINKNODE,
		kROLESKINSELECTWINDOW,
		kROLESKINSELECTWINDOWCELL,
		kMASSACREVIEW,
		kEQUIPTIPS,					//装备tips
		kEQUIPCOMPARE,				//装备对比tips
		kOBJECTTIPS,				//物品tips
		KSELECTSKILLVIEW,			//选择技能界面数据
		KSKILLTIPSVIEW,				//技能tipsUI
		kSELECTSERVERWINDOW,		//服务器选择
		kSERVERROOTCELL,
		kMESSAGEBOXWINDOW,
		kINPUTNUMWINDOW,
		//begin:Strenghten
		kSTRENGTHENWINDOW,	//强化窗口
		kSTRENGTHENWINDOW_CELL,//强化窗口Cell
		kEQUIPLVUPVIEW,//装备升级界面
		kEQUIPPROMOTEVIEW,
		kEQUIPLVUPVIEWCELL,//装备升级界面右侧cell
		kEQUIPMENTSELECTCARDWINDOW,	//装备升级选卡
		kEQUIPMENTSELECTCARDWINDOWCELL,//装备升级选卡cell
		kEQUIPRECASTVIEW,			   //装备重铸界面
		//end
		kSYSTEMSETWINDOW,	//系统设置界面

		kNOTICEBOXWINDOW,		//公告界面
		kNOTICEBOXGATEWAYWINDOW,		//网关公告界面
		kARENAVIEW,				//竞技场UI数据
		KARENAVIEWCELL,		    //竞技场TableCell数据
		KARENARANKLISTVIEW,     //排行榜数据
		KARENARANKCELL,			//排行榜TableCell数据

		kEQUIPTRAINVIEW,		//装备洗练

		kCLIMBTOWERVIEW,			//爬塔
		kCLIMBTOWERVIEWBEGIN,		//爬塔开始
		kCLIMBTOWERVIEWEND,			//爬塔中途，即某层结束的
		kCLIMBTOWERFIGHTRESULT,		//快速战斗战报界面，新增
		kCLIMBTOWERFIGHTRESULTCELL,	//快速战斗战报cell，新增
		kCLIMBTOWERREWARD,			//层级奖励，新增
		kCLIMBTOWERREWARDCELL,		//层级奖励Cell，新增

		kCHAT,					//聊天界面
		kSHOPWINDOW,			//神秘商店
		kMARKETWINDOW,			//商城
		kSHOPVIEW,				//商店子界面
		kSHOPVIEWCELL,			//商店tablecell
		kRANDOMSHOPINFONODE,	//随机商店信息	
		kRANDOMSHOPCELL,		//随机商店cell
		kSELECTROLEWINDOW,		//选择角色界面

	    kEFFECTWINDOW,			//效果界面
		kGUIDEWINDOW,			//新手引导界面
		kBAGWINDOW,					//背包主界面，新
		kBAGWINDOWOBJECTLIST,		//背包物品列表，新
		kBAGWINDOWCOMPOSELIST,			//背包合成，新
		kBAGWINDOWRIGHTPANELITEM,			//背包右侧页面，新
		kBAGWINDOWRIGHTPANELPOSITION,		//背包右侧格子位置，新

		kSHOPINPUTNUMWINDOW,			//商店批次购买窗口
		kREVENUEWINDOW,					//征收窗口

		kTIPSWINDOW,					//公共提示界面
		kNPCTALKVIEW,					//NPC对话窗口配置

		kSELECTSONMISSIONWINDOW,			//选择关卡
		kSELECTSONCELL,						//关卡CELL

		kVIPVIEW,							//VIP
		kVIPVIEWLAYER,                      //VIP特权信息

		kSHOPTIPS,							//商店tips
		kFRIENDWINDOW,						//好友

		kTEAMBATTLE,			//组队副本
		kTEAMBATTLECELL,		//组队副本界面的副本列表
		kTEAMSELECT,			//组队选择队伍
		kTEAMSELECTCELL,        //组队选择队伍列表
		kTEAMBATTLEGATEREWARD,	//组队副本，副本通关奖励
		kTEAMSELECTVIEWLIST,	//弹出窗口
		kTEAMSELECTVIEWCELL_SLAVE,	//弹出窗口绘制的奴隶界面
		kTEAMSELECTVIEWCELL_MERCENARY,	//弹出窗口绘制的仆从界面

		kPLAYERTIPSWINDOW,     //好友玩家tips
		kEMAILWINDOW,			//邮箱窗口
		kEMAILWINDOWCELL,		//邮箱窗口cell
		kEMAILWINDOWATTACHMENTCELL,		//邮箱附件窗口cell
		kEMAILWRITELETTERWINDOW,//写信窗口
		kEQUIPTIPSWINDOW,		//装备tip窗口

		kPUCONGWINDOW,			//矿洞系统页面

		kSERVANTWINDOW,			//仆从主窗口
		kSERVANTMASTERPAGE0,	//奴隶主页面0
		kSERVANTMASTERPAGE0_CELL,	//抓捕界面的cell
		kSERVANTMASTERPAGE1,	//奴隶主页面1
		kSERVANTMASTERPAGE2,	//奴隶主页面2
		kSERVANTMASTERPAGE2_CELL,	//奴隶主页面2cell
		kSERVANTSLAVEPAGE0,		//奴隶页面0
		kSERVANTSLAVEPAGE1,		//奴隶页面1
		kSERVANTSLAVEPAGE2,		//奴隶页面2
		kSERVANTSLAVEPAGE2_CELL,	//奴隶页面2cell
		kSERVANT_MASTER_NEWS_CELL,	//奴隶主新闻的cell
		kSERVANT_SLAVE_NEWS_CELL,	//奴隶新闻cell
		
		kRECHARGEWINDOW,			//充值界面
		kRECHARGEWARNWINDOW,		//充值绑定账号提示界面

		kMAINTASKWINDOW,				//综合任务界面
		kTASKLISTCELL,					//任务Cell界面
		kFORCEPUSHREWARDWINDOW,			//强制推送奖励界面
		kCHECKLEADERSHIPWINDOW,			//查看统率力界面

		//begin:显示活动
		kLIMITEDACTIVITY,				//限时活动面板
		kLIMITEDACTIVITY_ACTVITY,		//活动节点
		kLIMITEDACTIVITY_CELL_L,		//限时活动面板左侧cell
		kLIMITEDACTIVITY_EXCHANGE,				//兑换码功能
		kTEMPLEWINDOW,					//神庙窗口
		kCONVICTIONWINDOW,				//信仰窗口
		kLIMITEDACTIVITY_NOTICEBOX,		//登录公告节点
		kACTIVITYWINDOW,				//活动主窗口
		kSPRINGVIEW,					//活动温泉

		kLESSRESOURCEWINDOW,			//资源不足界面
		kMININGWINDOW,				//挖矿主页
		kHUNTWINDOW,				//寻宝
		kGOBLINAREAWINDOW,			//地精矿页
		kDWARVENAREAWINDOW,			//矮人矿页
		kDRAGONAREAWINDOW,			//巨龙矿页
		kHUNTMININGWINDOW,			//寻宝页
		 
		kHeroIllustratedWindow,		//英雄图鉴	
		kHerolllustratedStarCell,	//图鉴星星Cell
		kHeroIllustratedHeroCell,	//图鉴英雄Cell

		kHeroAdvancedWindow,		//英雄进阶窗口
		kMISSIONWINDOW,				//世界地图

		kALTARWINDOW,				//英雄献祭界面
		kALTARDEBRISWINDOW,			//英雄碎片献祭界面
		kHEROSUMMONWINDOW,			//英雄召唤界面
		kHEROHOLYNODE,				//英雄神圣召唤界面
		kGAINHEROWINDOW,			//获得英雄界面
		kGAINSOULDEBRIWINDOW,			//获得英雄界面
		kTENCALLWINDOW,				//十连抽召唤界面
		kGAINCALLITEMWINDOW,		//召唤获得物品界面
		//end


		kLEADERSHIPLVUPWINDOW,		//领导力升级界面
		kLEVELUPNORMALWINDOW,		//升级界面
		kCOMMUNICATINGWINDOW,		//网络等待界面
		kATHLETICRESULTWINDOW,		//战斗结算

		kAthleticsWindow,			//战斗界面
		kMULTIREWARDWINDOW,			//多个物品奖励窗口
		kARENAREWARDWINDOW,			//竞技场奖励窗口
		kARENAREWARDCELL,			//竞技场奖励列表子节点
		 

		kFIRSTRECHWINDOW,			//首充窗口
		kFIRSTRECHCELL,				//首充附件

		kLEVELUPREWARDACTIVITYWINDOW,//升级奖励活动界面
		kLEVELUPREWARDACTIVITYCELL,	 //升级奖励Cell
		 
		kNEWEQUIPREMINDWINDOW,		//新装备提醒窗口

		kHEROSOULWINDOW,			//战魂窗口

		kBOSSSCOREWINDOW,			//boss积分窗口
		KBOSSSCOREREWARDWINDOW,		//boss积分奖励窗口
		kBOSSSCOREREWARDCELL,		//boss积分奖励窗口cell

		kLOGINACTIVITYWINDOW,		//每日登陆活动奖励
		kLOGINACTIVITYCELL,			//每日登陆活动奖励cell

		kGROWUPPLANACTIVITYWINDOW,	//成长计划活动奖励
		kGROWUPPLANAREWARDCELL,		//成长计划活动奖励cell

		kSOULEQUIPVIEW,				//战魂装备页面
		kSOULEQUIPCELL,				//战魂装备Cell

		kEXCHANGEACTIVITYWINDOW,	//兑换活动窗口
		kEXCHANGEACTIVITYCELL,		//兑换活动Cell

		kHEROSOULTIPSWINDOW,		//战魂tips窗口

		kVIPGIFTWINDOW,			//Vip礼包窗口
		kVIPGIFTCELL,				//Vip礼包Cell
		kTEAMINFOWINDOW,		//队伍信息窗口
		kTEAMHEROSHOWNODE,		//英雄展示节点页面
		kAPPSTOREWAITWINDOW,		//app支付等待窗口
//#################也用于push帮助窗口的参数####################
		kSELECTSKILL_HELP_,			//技能选择帮助界面
		kSTRENGTHEN_HELP_,			//强化帮助界面
		kEQUIPMENT_HELP_,			//装备帮助界面
		kARENA_HELP_,				//竞技场帮助界面
		kHEROTECHNOLOGY_HELP_,		//英雄科技帮助界面
		kSERVANT_HELP_,				//仆从帮助界面
		kSLAVE_HELP_,				//奴隶帮助界面
		kTEAMBATTLE_HELP_,			//组队副本帮助界面
		kLOADINGWINDOW,				//Loading界面
		kCHAT_CELL_,				//聊天界面CELL
		kCHAT_POP_,					//聊天界面POP

//####################1000~1999为lua中使用######################
		kLUA_LAYOUT_BEGIN				=1000,
		kLUA_LAYOUT_END			        =1999,
	};
protected:
	std::map<int,std::string> m_fileList;		 //没有加密的文件名
	std::map<int,std::string> m_EncyfileList;    //有加密的文件名
	std::map<int, UIViewData*> m_dataList;
	std::string m_filename;

	std::map<int, std::string> m_BufferList;
public:
	UIViewDataManager(bool bLoadFromDB, bool bEncryption): IDataManager(bLoadFromDB, bEncryption){
		
	};
	virtual ~UIViewDataManager(){};
	/*
	测试期间，慎用
	*/
	void AutoCreateNodeByTable(int key,cocos2d::CCNode* parentNode);

	/*
		方骏所有，翻版必究
	*/
	void AutoCreateNodeByTable(int key, cocos2d::CCNode * parentNode, float offsetX, int times);
public:
	
    UIViewData * getControlDataByID(int idx);

	/*
		得到对应的数据管理器名称
	*/
	virtual  std::string   GetName();
	/*
		得到对应的数据管理器内存占用大小
	*/
	virtual  unsigned  int GetSize();

public:
	/*
		初始化数据管理器
	*/
	virtual  bool  Init();
	/*
		数据管理器帧更新处理
	*/
	virtual  void  Tick();
	/*
		销毁数据管理器
	*/
	virtual  void  Destroy();
	//
	//
	/*
		载入文件,进入界面时需要调用
	*/
	void loadData(int idx);
	/*
		清除内存，离开界面前调用
	*/
	void clearData();

protected:
	/*
		从文件加载对应的资源
	*/
	virtual  bool  LoadFromFile(char* filename,std::string& buffer);
	/*
		从数据库加载对应的资源
	*/
	virtual  bool  LoadFromDB(char* Encyname,std::string& buffer);
	/*
		解析字符串资源
	*/
	bool UIViewLoad(char* pBuffer,unsigned int iLength);

public:
	/*
		校验加载的数据(单行数据的有效性校验)
	*/
	virtual  bool  Varify(IData* pData);
	/*
		校验加载的数据(所有数据加载完之后进行的表与表关联性校验)
	*/
	virtual  bool  VarifyAfterLoadAll();

protected:
	/*
		创建指定的ItemData数据
	*/
	virtual  bool  LoadData(char* pBuffer, unsigned int iBufferLen);

public:
	/*
		注册文件
	*/
	void registerFile(int idx,std::string filename,std::string Encyfilename);

private:
	friend   class   cobra_win::Singleton2<UIViewDataManager>;
};

#define  UIVIEWDATAMANAGER  UIViewDataManager::get_instance2()
  
#endif