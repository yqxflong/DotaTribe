//Name��UIViewDataManager
//Written By����ǿ

#ifndef   _DOTATRIBE_UIVIEWDATAMANAGER_H
#define   _DOTATRIBE_UIVIEWDATAMANAGER_H

 
#include <include/common/Singleton.h>
#include "IDataManager.h"
#include <string>
#include <map>
#include <cocos2d.h>

#pragma pack(push, 1)
/*
	����UI���ֵı���б���ͳһ
*/
class   UIViewData: public IData
{
private:
	int m_nSysLangID;						//����ID
public:
	int idx_;		//�ؼ�����
	int hide_;		//0:��ʾ 1:����
	int zorder_;	//���
	float scale_;	//����
	float rotation_;	//��ת
	char class_[128];		//����
	int touchpriority_;	//��ʱ��fontsize_���
	int swallow_;				//��ʱ��colorR���
	int m_nFontStyleID;					//FontyStyleID
	std::string labelstring_;
	char fontname_[128];		//font������
	float fontsize_;			//label �����С;		�����menuitem��Ϊpriority
	int colorR_;				//RGB-R;					�����menuitem��Ϊ1:��swallow��0��swallow
	int colorG_;				//RGB-G
	int colorB_;				//RGB-B
	int alpha_;				//alphaֵ
	char filepath_[128];	//ͼƬ·��
	char filepath2_[128];	//ͼƬ·��
	char filepath3_[128];	//ͼƬ·��
	float width_;
	float height_;
	float anchorx_;			
	float anchory_;
	float posx_;
	float posy_;
	int soundid_;		//�����Ҫ�������¼�������Ϊ-1
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
		kEQUIPTIPS,					//װ��tips
		kEQUIPCOMPARE,				//װ���Ա�tips
		kOBJECTTIPS,				//��Ʒtips
		KSELECTSKILLVIEW,			//ѡ���ܽ�������
		KSKILLTIPSVIEW,				//����tipsUI
		kSELECTSERVERWINDOW,		//������ѡ��
		kSERVERROOTCELL,
		kMESSAGEBOXWINDOW,
		kINPUTNUMWINDOW,
		//begin:Strenghten
		kSTRENGTHENWINDOW,	//ǿ������
		kSTRENGTHENWINDOW_CELL,//ǿ������Cell
		kEQUIPLVUPVIEW,//װ����������
		kEQUIPPROMOTEVIEW,
		kEQUIPLVUPVIEWCELL,//װ�����������Ҳ�cell
		kEQUIPMENTSELECTCARDWINDOW,	//װ������ѡ��
		kEQUIPMENTSELECTCARDWINDOWCELL,//װ������ѡ��cell
		kEQUIPRECASTVIEW,			   //װ����������
		//end
		kSYSTEMSETWINDOW,	//ϵͳ���ý���

		kNOTICEBOXWINDOW,		//�������
		kNOTICEBOXGATEWAYWINDOW,		//���ع������
		kARENAVIEW,				//������UI����
		KARENAVIEWCELL,		    //������TableCell����
		KARENARANKLISTVIEW,     //���а�����
		KARENARANKCELL,			//���а�TableCell����

		kEQUIPTRAINVIEW,		//װ��ϴ��

		kCLIMBTOWERVIEW,			//����
		kCLIMBTOWERVIEWBEGIN,		//������ʼ
		kCLIMBTOWERVIEWEND,			//������;����ĳ�������
		kCLIMBTOWERFIGHTRESULT,		//����ս��ս�����棬����
		kCLIMBTOWERFIGHTRESULTCELL,	//����ս��ս��cell������
		kCLIMBTOWERREWARD,			//�㼶����������
		kCLIMBTOWERREWARDCELL,		//�㼶����Cell������

		kCHAT,					//�������
		kSHOPWINDOW,			//�����̵�
		kMARKETWINDOW,			//�̳�
		kSHOPVIEW,				//�̵��ӽ���
		kSHOPVIEWCELL,			//�̵�tablecell
		kRANDOMSHOPINFONODE,	//����̵���Ϣ	
		kRANDOMSHOPCELL,		//����̵�cell
		kSELECTROLEWINDOW,		//ѡ���ɫ����

	    kEFFECTWINDOW,			//Ч������
		kGUIDEWINDOW,			//������������
		kBAGWINDOW,					//���������棬��
		kBAGWINDOWOBJECTLIST,		//������Ʒ�б���
		kBAGWINDOWCOMPOSELIST,			//�����ϳɣ���
		kBAGWINDOWRIGHTPANELITEM,			//�����Ҳ�ҳ�棬��
		kBAGWINDOWRIGHTPANELPOSITION,		//�����Ҳ����λ�ã���

		kSHOPINPUTNUMWINDOW,			//�̵����ι��򴰿�
		kREVENUEWINDOW,					//���մ���

		kTIPSWINDOW,					//������ʾ����
		kNPCTALKVIEW,					//NPC�Ի���������

		kSELECTSONMISSIONWINDOW,			//ѡ��ؿ�
		kSELECTSONCELL,						//�ؿ�CELL

		kVIPVIEW,							//VIP
		kVIPVIEWLAYER,                      //VIP��Ȩ��Ϣ

		kSHOPTIPS,							//�̵�tips
		kFRIENDWINDOW,						//����

		kTEAMBATTLE,			//��Ӹ���
		kTEAMBATTLECELL,		//��Ӹ�������ĸ����б�
		kTEAMSELECT,			//���ѡ�����
		kTEAMSELECTCELL,        //���ѡ������б�
		kTEAMBATTLEGATEREWARD,	//��Ӹ���������ͨ�ؽ���
		kTEAMSELECTVIEWLIST,	//��������
		kTEAMSELECTVIEWCELL_SLAVE,	//�������ڻ��Ƶ�ū������
		kTEAMSELECTVIEWCELL_MERCENARY,	//�������ڻ��Ƶ��ʹӽ���

		kPLAYERTIPSWINDOW,     //�������tips
		kEMAILWINDOW,			//���䴰��
		kEMAILWINDOWCELL,		//���䴰��cell
		kEMAILWINDOWATTACHMENTCELL,		//���丽������cell
		kEMAILWRITELETTERWINDOW,//д�Ŵ���
		kEQUIPTIPSWINDOW,		//װ��tip����

		kPUCONGWINDOW,			//��ϵͳҳ��

		kSERVANTWINDOW,			//�ʹ�������
		kSERVANTMASTERPAGE0,	//ū����ҳ��0
		kSERVANTMASTERPAGE0_CELL,	//ץ�������cell
		kSERVANTMASTERPAGE1,	//ū����ҳ��1
		kSERVANTMASTERPAGE2,	//ū����ҳ��2
		kSERVANTMASTERPAGE2_CELL,	//ū����ҳ��2cell
		kSERVANTSLAVEPAGE0,		//ū��ҳ��0
		kSERVANTSLAVEPAGE1,		//ū��ҳ��1
		kSERVANTSLAVEPAGE2,		//ū��ҳ��2
		kSERVANTSLAVEPAGE2_CELL,	//ū��ҳ��2cell
		kSERVANT_MASTER_NEWS_CELL,	//ū�������ŵ�cell
		kSERVANT_SLAVE_NEWS_CELL,	//ū������cell
		
		kRECHARGEWINDOW,			//��ֵ����
		kRECHARGEWARNWINDOW,		//��ֵ���˺���ʾ����

		kMAINTASKWINDOW,				//�ۺ��������
		kTASKLISTCELL,					//����Cell����
		kFORCEPUSHREWARDWINDOW,			//ǿ�����ͽ�������
		kCHECKLEADERSHIPWINDOW,			//�鿴ͳ��������

		//begin:��ʾ�
		kLIMITEDACTIVITY,				//��ʱ����
		kLIMITEDACTIVITY_ACTVITY,		//��ڵ�
		kLIMITEDACTIVITY_CELL_L,		//��ʱ�������cell
		kLIMITEDACTIVITY_EXCHANGE,				//�һ��빦��
		kTEMPLEWINDOW,					//������
		kCONVICTIONWINDOW,				//��������
		kLIMITEDACTIVITY_NOTICEBOX,		//��¼����ڵ�
		kACTIVITYWINDOW,				//�������
		kSPRINGVIEW,					//���Ȫ

		kLESSRESOURCEWINDOW,			//��Դ�������
		kMININGWINDOW,				//�ڿ���ҳ
		kHUNTWINDOW,				//Ѱ��
		kGOBLINAREAWINDOW,			//�ؾ���ҳ
		kDWARVENAREAWINDOW,			//���˿�ҳ
		kDRAGONAREAWINDOW,			//������ҳ
		kHUNTMININGWINDOW,			//Ѱ��ҳ
		 
		kHeroIllustratedWindow,		//Ӣ��ͼ��	
		kHerolllustratedStarCell,	//ͼ������Cell
		kHeroIllustratedHeroCell,	//ͼ��Ӣ��Cell

		kHeroAdvancedWindow,		//Ӣ�۽��״���
		kMISSIONWINDOW,				//�����ͼ

		kALTARWINDOW,				//Ӣ���׼�����
		kALTARDEBRISWINDOW,			//Ӣ����Ƭ�׼�����
		kHEROSUMMONWINDOW,			//Ӣ���ٻ�����
		kHEROHOLYNODE,				//Ӣ����ʥ�ٻ�����
		kGAINHEROWINDOW,			//���Ӣ�۽���
		kGAINSOULDEBRIWINDOW,			//���Ӣ�۽���
		kTENCALLWINDOW,				//ʮ�����ٻ�����
		kGAINCALLITEMWINDOW,		//�ٻ������Ʒ����
		//end


		kLEADERSHIPLVUPWINDOW,		//�쵼����������
		kLEVELUPNORMALWINDOW,		//��������
		kCOMMUNICATINGWINDOW,		//����ȴ�����
		kATHLETICRESULTWINDOW,		//ս������

		kAthleticsWindow,			//ս������
		kMULTIREWARDWINDOW,			//�����Ʒ��������
		kARENAREWARDWINDOW,			//��������������
		kARENAREWARDCELL,			//�����������б��ӽڵ�
		 

		kFIRSTRECHWINDOW,			//�׳䴰��
		kFIRSTRECHCELL,				//�׳丽��

		kLEVELUPREWARDACTIVITYWINDOW,//�������������
		kLEVELUPREWARDACTIVITYCELL,	 //��������Cell
		 
		kNEWEQUIPREMINDWINDOW,		//��װ�����Ѵ���

		kHEROSOULWINDOW,			//ս�괰��

		kBOSSSCOREWINDOW,			//boss���ִ���
		KBOSSSCOREREWARDWINDOW,		//boss���ֽ�������
		kBOSSSCOREREWARDCELL,		//boss���ֽ�������cell

		kLOGINACTIVITYWINDOW,		//ÿ�յ�½�����
		kLOGINACTIVITYCELL,			//ÿ�յ�½�����cell

		kGROWUPPLANACTIVITYWINDOW,	//�ɳ��ƻ������
		kGROWUPPLANAREWARDCELL,		//�ɳ��ƻ������cell

		kSOULEQUIPVIEW,				//ս��װ��ҳ��
		kSOULEQUIPCELL,				//ս��װ��Cell

		kEXCHANGEACTIVITYWINDOW,	//�һ������
		kEXCHANGEACTIVITYCELL,		//�һ��Cell

		kHEROSOULTIPSWINDOW,		//ս��tips����

		kVIPGIFTWINDOW,			//Vip�������
		kVIPGIFTCELL,				//Vip���Cell
		kTEAMINFOWINDOW,		//������Ϣ����
		kTEAMHEROSHOWNODE,		//Ӣ��չʾ�ڵ�ҳ��
		kAPPSTOREWAITWINDOW,		//app֧���ȴ�����
//#################Ҳ����push�������ڵĲ���####################
		kSELECTSKILL_HELP_,			//����ѡ���������
		kSTRENGTHEN_HELP_,			//ǿ����������
		kEQUIPMENT_HELP_,			//װ����������
		kARENA_HELP_,				//��������������
		kHEROTECHNOLOGY_HELP_,		//Ӣ�ۿƼ���������
		kSERVANT_HELP_,				//�ʹӰ�������
		kSLAVE_HELP_,				//ū����������
		kTEAMBATTLE_HELP_,			//��Ӹ�����������
		kLOADINGWINDOW,				//Loading����
		kCHAT_CELL_,				//�������CELL
		kCHAT_POP_,					//�������POP

//####################1000~1999Ϊlua��ʹ��######################
		kLUA_LAYOUT_BEGIN				=1000,
		kLUA_LAYOUT_END			        =1999,
	};
protected:
	std::map<int,std::string> m_fileList;		 //û�м��ܵ��ļ���
	std::map<int,std::string> m_EncyfileList;    //�м��ܵ��ļ���
	std::map<int, UIViewData*> m_dataList;
	std::string m_filename;

	std::map<int, std::string> m_BufferList;
public:
	UIViewDataManager(bool bLoadFromDB, bool bEncryption): IDataManager(bLoadFromDB, bEncryption){
		
	};
	virtual ~UIViewDataManager(){};
	/*
	�����ڼ䣬����
	*/
	void AutoCreateNodeByTable(int key,cocos2d::CCNode* parentNode);

	/*
		�������У�����ؾ�
	*/
	void AutoCreateNodeByTable(int key, cocos2d::CCNode * parentNode, float offsetX, int times);
public:
	
    UIViewData * getControlDataByID(int idx);

	/*
		�õ���Ӧ�����ݹ���������
	*/
	virtual  std::string   GetName();
	/*
		�õ���Ӧ�����ݹ������ڴ�ռ�ô�С
	*/
	virtual  unsigned  int GetSize();

public:
	/*
		��ʼ�����ݹ�����
	*/
	virtual  bool  Init();
	/*
		���ݹ�����֡���´���
	*/
	virtual  void  Tick();
	/*
		�������ݹ�����
	*/
	virtual  void  Destroy();
	//
	//
	/*
		�����ļ�,�������ʱ��Ҫ����
	*/
	void loadData(int idx);
	/*
		����ڴ棬�뿪����ǰ����
	*/
	void clearData();

protected:
	/*
		���ļ����ض�Ӧ����Դ
	*/
	virtual  bool  LoadFromFile(char* filename,std::string& buffer);
	/*
		�����ݿ���ض�Ӧ����Դ
	*/
	virtual  bool  LoadFromDB(char* Encyname,std::string& buffer);
	/*
		�����ַ�����Դ
	*/
	bool UIViewLoad(char* pBuffer,unsigned int iLength);

public:
	/*
		У����ص�����(�������ݵ���Ч��У��)
	*/
	virtual  bool  Varify(IData* pData);
	/*
		У����ص�����(�������ݼ�����֮����еı���������У��)
	*/
	virtual  bool  VarifyAfterLoadAll();

protected:
	/*
		����ָ����ItemData����
	*/
	virtual  bool  LoadData(char* pBuffer, unsigned int iBufferLen);

public:
	/*
		ע���ļ�
	*/
	void registerFile(int idx,std::string filename,std::string Encyfilename);

private:
	friend   class   cobra_win::Singleton2<UIViewDataManager>;
};

#define  UIVIEWDATAMANAGER  UIViewDataManager::get_instance2()
  
#endif