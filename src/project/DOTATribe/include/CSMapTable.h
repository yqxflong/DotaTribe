/*
	��������ͻ��˵Ĺ�ϵ��
*/
#ifndef _GLOBAL_CSMAPTABLE_
#define _GLOBAL_CSMAPTABLE_

#include <map>
#include <include/mem/DPacket.h>
/*
	serial Num
*/
enum{
	kCREATEROLEPACKET=0,
	kCHANGEEQUIPPACKET=1,
	kOFFEQUIPPACKET=2,
	kCHANGESKINPACKET=10,
	kSKINSTRENCONDITION=11,
	kSKINSTRENMAIN=12,
	kBAGSALEOBJECTPACKET = 20,
	kBAGUSEOBJECTPACKET = 21,

};
/*
	�̵���Ʒ��Ӧ�Ļ���
*/
enum
{
	_TYPE_GOLD_ = 0,
	_TYPE_JEWEL_ ,
	_TYPE_PRESTIGE_,
	_TYPE_EXCHANGE_ITEM_,
};

/*
	��������
*/
enum{
	BAG_ITEM = 0,		//��ͨ��Ʒ
	BAG_EQUIP = 1,		//װ��
	BAG_SKIN = 2,		//����
};

/*
	װ������
*/
enum{
	kEQUIP_TYPE_MAINWEAPON=0,		//����
	kEQUIP_TYPE_CLOTH,							//�·�
	kEQUIP_TYPE_HAND,							//�ֲ�
	kEQUIP_TYPE_SHOES,							//Ь��
	kEQUIP_TYPE_2ndWEAPON,				//����
	kEQUIP_TYPE_BALL,								//����
	kEQUIP_TYPE_HAT,								//ͷ��
	kEQUIP_TYPE_DECORATION,				//��Ʒ
	kEQUIP_TYPE_EXPBALL,				//������
};

/*
	��ƬƷ��
*/
enum{
	kCARD_1_STAR=0,//��ɫ		====1��
	kCARD_2_STAR,//��ɫ			====2��
	kCARD_3_STAR,//��ɫ			====3��
	kCARD_4_STAR,//��ɫ			====4��
	kCARD_5_STAR,//��ɫ			====5��
	kCARD_6_STAR,//��ɫ			====6��
};

/*
	��ͨ��Ʒ������
*/
enum{
	kOBJECTDRUG = 0,		//ҩƷ
	kOBJECTBOX = 1,			//����
	kOBJECTCOMPOSE = 2,		//�ϳ�
	kOBJECTRECIPE = 3,		//�䷽
	kOBJECTOTHER = 4,		//����
};

enum{
	kBAGOBJECT=0,		//��ͨ��Ʒ
	kBAGEQUIP,				//װ��
	kBAGSKIN,				//����
};

enum{
	kPLAYER=0,				//������Ϣ
	kATTRIBUTES,			//14��ͨ������
};

enum{
	kLEVEL=0,			//��ɫ�ȼ� <br>
	kEXP,					//��ɫ���� <br>
	kVITALITY,			//���� <br>
	kJEWELS,				//��ʯ <br>
    kMONEY,				//��Ǯ <br>
	kVIPLEVEL,			//VIP�ȼ� <br>
	kBTLCAPACITY,	//ս���� <br>
	kPRESTIGE,			//���� <br>
};

//add by fangjun begin�� use for 1018
enum {
	kINFOLEVEL,		//�ȼ�
	kINFOEXP,		//����
	kINFOMAXEXP,		//�����
	kINFOVITALITY,		//����
	kINFOJEWELS,		//��ʯ
	kINFOMONEY,		//��Ǯ
	kINFOBAGGRID,		//����
	kINFOSKILL,		//����
	kINFOMAXHP,		//���Ѫ��
	kINFOMAXMP,		//�������
	kINFOMINATTACK,		//��С����
	kINFOMAXATTACK,		//��󹥻�
	kINFOSPEED,		//�ٶ�
	kINFOSTR,		//����
	kINFOAGI,		//����
	kINFOINTE,		//����
	kINFOARMOR,		//����
	kINFOEXPOSEARMOR,		//�Ƽ�
	kINFOHIT,		//����
	kINFODODGE,		//����
	kINFOCRIT,		//����
	kINFOUNCRIT,		//�ⱬ
	kINFOHEROCAPA,			//Ӣ��ս����
	kINFOHEROCAPASCORE,		//Ӣ��ս������
	kINFOEQUIPCAPA,			//װ��ս����
	kINFOEQUIPCAPASCORE,	//װ��ս������
	kINFOTECHCAPA,			//�Ƽ�ս����
	kINFOTECHCAPASCORE,		//�Ƽ�ս��������
	kINFOTRAINCAPA,			//����ѵ��ս����
	kINFOTRAINCAPASCORE,	//����ѵ��ս��������
	kINFOSOULCAPA,			//���ս����
	kINFOSOULCAPASCORE,		//���ս��������
	kINFOFRIENDCAPA,		//����ս����
	kINFOFRIENDCAPASCORE,		//����ս��������
	kINFOSUMCAPA,			//��ս����
	kINFOSUMCAPASCORE,			//��ս��������
	kINFOVIPLEVEL,			//VIP����
	kINFOPRESTIGE,			//����
	kINFOPVPRANK,			//����������
	kINFOBAGSIZE,			//��������
	kINFOROLESKIN,			//��������
	kINFOROLEEQUIP,		    //����װ��
	kINFOROLESKILLNOTCH,	//ͬ�����ܰ���
	kINFOQUESTTIPS,			//��������
	kINFOMAILTIPS,			//�ʼ�����
	kINFOCOLLECTTIPS,		//ʣ��������մ���
	kINFOSHOPTIPS,			//�̵��������
	kINFOSERVANTIDENTITY,	//�������ʹ�ϵͳ�����
	kINFOAPPLYFORFRIENDNUM,	//�����������
	kINFOMAINTASKFINISHED,	//�����������
	kInfoHeroLevel,			//Ӣ�۵ȼ�
	kInfoHeroExp,			//��ǰӢ�۾���
	kInfoHeroLeveUpNeedExp,	//�������辭��
	kInfoHerohonorLevel,	//Ӣ��ͳ��������
	kInfoHerohonorExp,		//Ӣ������ֵ
	kInfoHerohonorLevelUpExp,//������������ֵ
	kINFOAWARDNOTICE,		 //��������
	kINFOACTIVITY,			 //���ʻ
	kInfoNewTask,			 //����������
	kACCUMURECH,			 //�ۻ���ֵ
	kMERNALEMPTY,		     //���ûռ
	kFREESUPPLICATION,		 //����ѵ���Ը
	kVIPREWARD,				 //vip������ʾ
	kBOSSSCORE,				//boss���ֽ���
	kARENAREWARD_HINT,		//����������ʾ
	kHEROSOUL,				//�����ս��		
	kFREESUMMON_HINT,		//�ٻ��Ƿ����
	kREFRESHSHOP,		//�����̵��Ƿ����ˢ��
	kBOSSFREETIME,			//boss������Ѵ���
	kHUNTOBJECTLEFTTIME,		//Ѱ��ʣ���������ʹ����Ʒʱ��ͬ��������
	kLASTARENATIME,			 //ʣ�ྺ������ս����
	kMULTI_EXP,				//���鱶��
	kMULTI_MONEY,			//��Ǯ����
	kUnLockSkill,			//��������
	kONEHEROSTRENGTH,		//����Ӣ��ս��ͬ��
};
//end

enum{
	kSTRENGTH=0,		//����
	kAGILITY,					//����
	kINTELLIGENCE,		//����
	kMAXHP,					//���Ѫ��
	kMAXMP,					//�������
	kSPEED,					//�ٶ�
	kMINATTACK,			//��С����
	kMAXATTACK,			//��󹥻�
	kARMOR,					//����
	kEXPOSEARMOR,		//�Ƽ�
	kHIT,						//����
	kDODGE,					//����
	kCRIT,						//����
	kUNCRIT,					//����
	kCOUNT=14,			//����
};
/*
	14��ͨ������
*/
class  Attribute
{
public:
	std::map<int,int> mapPropertyList_;		//��list��index��ͨ������ö��һһ��Ӧ
	~Attribute()
	{
		mapPropertyList_.clear();
	}
	Attribute * __set(Attribute * obj)
	{
		mapPropertyList_.clear();
		std::map<int,int>::iterator it = obj->mapPropertyList_.begin();
		std::map<int,int>::iterator it_e = obj->mapPropertyList_.end();
		for(; it != it_e; ++it)
		{
			mapPropertyList_.insert(std::map<int,int>::value_type(it->first, it->second));
		}
		
		return this;
	}
public:
	void decodePacketData_ChangeEquip(cobra_win::DPacket & packet, int heroindex);
};

//��ǰ֧�ֵĻ����
enum
{
	_ACTIVITY_UNKONW_TYPE_ = 0,			//δ֪�����
	_ACTIVITY_SPRING_TYPE_,				//��Ȫ�
	_ACTIVITY_FIRSTRECHGIFT_TYPE_,		//�׳�
	_ACTIVITY_LEVELUPREWARD_TYPE_,		//�����
	_ACTIVITY_LOGINREWARD_TYPE_,		//��¼�콱��
	_ACTIVITY_VIPBAGREWARD_TYPE_,		//VIP������ȡ�����
	_ACTIVITY_EXCHANGEREWARD_TYPE_,		//�һ������
	_ACTIVITY_GROWUPPLAN_TYPE_,			//�ɳ��ƻ������
	_ACTIVITY_LIANJIN_TYPE_,			//����
};

#define NEWBAG_ITEMCOUNT			120
#define NEWBAG_NUMPERPAGE			20
#define NEWBAG_PAGENUM				6

#define BAG_GUIDE_USE_LEVEL						30
#define BAG_GUIDE_BACKOBJECT_LEVEL				40
#define HUNT_GUIDE_LEVEL						30

#define KUANGDONG_DWARVEN_PAGES		8

#define TOWER_FLOOR_TOTAL			400

#endif