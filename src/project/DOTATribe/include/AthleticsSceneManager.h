//Name��AtheleticsSceneManager
//Function��ս��ϵͳ�����
//Author:	Johny

#ifndef   _DOTATRIBE_ATHLETICSSCENEMANAGER_H
#define   _DOTATRIBE_ATHLETICSSCENEMANAGER_H

#include  <cocos2d.h>
#include  <include/common/Singleton.h>
#include  "../include/HeroicRole.h"
#include  "../include/AthleticProcedureDataType.h"
#include  "../include/AthleticsUIManager.h"
#include  "../include/RoleInfoDataHandler.h"
#include  "../include/UIBaseDialog.h"
#include  "../include/CommonEffect.h"
#include  "../include/NpcTalkView.h"
 
#include  <map>
#include  <set>
#include <math.h>
using  namespace  cobra_win;
 
#define   LowRoleZOrder		  6				//�ͽ�ɫZOrderֵ
#define   LeftRoleTag		  111			//���ɫTagֵ
#define   HighRoleZOrder	  9				//�߽�ɫZOrderֵ
#define   RightRoleTag		  112			//�ҽ�ɫTagֵ
#define   SkillsPanelZOrder	  15			//������Ϣ����ZOrder�㼶
#define   ScreenEffectTag	  3333			//��Ļ��ЧColorLayer��Tag

class UIBaseDialogProtory;
  
class AthleticsSceneManager : public cocos2d::CCNode, public UIBaseDialogProtory, public cobra_win::Singleton2<AthleticsSceneManager> 
{ 

public:
    //@ս����¼����
	enum
	{
		_ATHLETICS_UNKONW_RECORD_TYPE_=-1,			//δ֪��¼����
		_ATHLETICS_LIVE_RECORD_TYPE_,				//ֱ��ս����¼����
		_ATHLETICS_REPLAY_RECORD_TYPE_,				//ת��ս����¼����
	};

	//@ս���ۿ�����
	enum
	{
		_ATHLECTICS_UNKONW_WATCH_TYPE_,				//δ֪�ۿ�����	
		_ATHLECTICS_SELFT_WATCH_TYPE_,				//��̨��������
		_ATHLECTICS_OTHER_WATCH_TYPE_,				//�����ֹۿ�����
	};
		 
	 
	//@�ڲ��¼�֪ͨ
	enum
	{
		_ATHLETICS_UNKOWN_EVENT_,					//δ֪�ڲ��¼�֪ͨ
		_ATHLETICS_ADMITTANCE_FINISH_CALL_EVENT_,	//��ɫ�볡�����ص����
		_ATHLETICS_GAME_OVER_CALL_EVENT_,			//��Ϸ���

	};
	 
	AthleticsSceneManager();
	virtual ~AthleticsSceneManager();
public:
	//@����
	bool  Init();
	void  Tick();
	void  Destroy();

	//@���ս��������Root��
	cocos2d::CCNode *  GetAthleticsRootLayer();

	//@���ս�����ò�
	cocos2d::CCNode *  GetAthleticsDiableMark();

	//@���NPC�Ի���
	cocos2d::CCNode *  GetAthleticsNpcTalkLayer();

    //@��ý�ɫ��Ŀ�깥��λ��
	cocos2d::CCPoint  GetRoleTargetPositon(bool isLeft=true);
	 
	//@����NPC�Ի������״̬
	void    SetAthleticsNpcTalkLayerVisible(bool isVisible);

	//@�¼�֪ͨ�ӿ�
	void   OnCommandHanlder(int EventTypeID,void * ptr); 

	//@�Ի��ص�������
	void   BaseDialogCallBackHandler(int eventType,void * ptr);
	 
	//@ɾ��ս����Ч��������
	void  DestroySkillsEffectTextureData();
 
	//@ս����ͼ��Ϣ���ݰ�
	bool  LoadAthleticsMapInfo();

    //@սǰ��ɫ��Ϣ������
	bool   LoadAthleticPreData();

	//@ս�������Ϣ������
	bool   LoadAthleticResultData();

	//@����Ƿ�Ϊ�鿴ս������
	bool  LoadAthleticRecordType();

	//@����Ƿ���Ҫ����NPCTalk
	bool  LoadNpcTalkConfigData();

	//@���Npc���������
	void  NpcTalkManagerHandler(int eventType);
 
	//@��ʼ��ս������UI   ���𳡾����������Լ������������UI����
	void   InitAthleticSceneUI();
 
	//@���ݵ�ǰ���ִ�  ����ս����ɫ��������  ��ʱ�ص��볡����
	void   OnUpdateAthleticsRoleSkeleton(RoleUniqeDefine role1,RoleUniqeDefine role2);			

    //@��ʱ�볡�ص�  �����볡����
	void   CallBackPlayAdmittance();

	//@�ӳ�ս������ص� ����ս���������
	void   CallBackPlayResultUI();

    //@Ԥ����ս����ɫ������ɫ
	bool   PreLoadAthleticRole();

	//@��ȡս������(���� ���� ��� �д��)
	char  GetAthleticBattleType();
	 
    //@��ȡ���ս������  (�����)
	HeroicRole *  GetLeftFightRole();

    //@��ȡ�ұ�ս������  (�з���)
	HeroicRole *  GetRightFightRole();

	//@��ȡ�����ߵĶ���
	HeroicRole *  GetExecuteRole(bool isLeft);
	 
	//@�ж���Ϸ�Ƿ��Ѿ�����
	bool  IsGameOver();

	//@������Ϸ�Ƿ����
	void  SetGameOver();

	//@����ʤ���ߵĶ���
	void  OnPlayWinAnimation();

	//@�����û���Ѫ��
	void  OnUpdateRoleHPValue();

	//@���½�ɫ������
	void  OnUpdateRoleMPValue();

	//@�ز�ս��
	void  OnRePlayAthleticsGame();   
  
	//@���½�ɫBufferTick
	void  OnUpdateRoleTickBuffer();

	//@Postս�����UI֪ͨ
	void  PostGameOverUINofitication();

	//@���������˵�Ѫ��������
	void  OnResetAllRoleHPAndMP();

    //@���Ѫ���������ľ���������
	float GetHPRectWidth();
	float GetMPRectWidth();

	//@�������ò�
	void   ShowAthleticsDisableLayer();

	//@�رս��ò�
	void   HideAthleticsDiableLayer();
	 
	//@��Ļ����Ч   
	void  OnPlayScreenShake(int compositeEffectID,int shakeItemID);

	//@�ر���Ч
	void  OnStopScreenShake(int compositeEffectID=-1);


	//@�������ٶ�
	void  OnSetScreenShakeEffectSpeedScale();

	//@������Ļ����Ч
	void  UpdateScreenShakeEffect();

	//@�����첽���ص�����
	void  SetSycLoadTexurePlistPool(std::set<std::string> & texturePlistPool);
	 
	//@�ı䳡�������ٶ��л�
	void  OnChangeAthleticsSpeed();				
	void  UpdateAthleticsSystemSpeed(float athleticsSpeed);
	void  UpdateAthleticSpeedUI();
 
												
	//@����С���ս��
	void   AddHeroicRoleInGroup(PBaseRoleInfo pBaseRoleInfo,bool isPlayerGronp);		
  
	//@��������ָ��Role
	HeroicRole *     IsRoleInPlayGroup(RoleUniqeDefine & role);

	//@��õз���ָ��Role
	HeroicRole *     IsRoleInEnmeyGroup(RoleUniqeDefine & role);

	//@����RoleInfo
	void			 SetRoleWithRoleData(RoleUniqeDefine & role);
	 
	//@��õ�ǰս���Ĺۿ�����
	char    GetAthelticsWatchType();

	//@���õ�ǰս���Ĺۿ�����
	void    SetAthleticsWatchType(char watchType);

	//@��ȡ���ս�����
	bool    GetAthleticsResult();

	//@���ʤ�����Ƿ��ڳ�ʼλ��
	bool	IsWinRoleNeedHoming();
	
	//@��ȡ����λ�Ľ�ɫ��Ϣ
	void    GetNeedHomingRoleInfo(RoleUniqeDefine & roleInfo);

	//@����ս����������֪ͨ
	void    PostCurRoundWillDid();

	//@������Ӹ���
	void    UpdateTeamIcon(bool isPlayerGroup);

	//@���ս�ܶ���ͷ��
	void    UnActiveAllTeamIcon(bool isPlayerGroup);
  
	//@�Ƿ���Դ���VIP����ս��
	bool    IsTriggerVIPSkipHandler();
private:
	//@����ս�����
	void  AnalyseAthleticsResult();

	//@�жϵ�ǰVIP�ȼ��Ƿ����������ս��
	bool  IsVIPCanSkipAthletics();

	//@VIP����ս������
	void  VipSkipAthleicsHandler();

	//@�رս�ɫ����Action 
	void  StopActiveRoleAllAction();
	  
private:	 
	/*
	 to do  ͳһ����������������
	*/
	PAthleticsMapInfo		 pAthleticsMapInfo;				//ս����ͼ��Ϣ
	PPreAthleticsData		 pPreAthleticsData;			    //սǰ������Ϣ���ݰ�
	PAthleticsResultData     pAthleticResultData;			//ս��������ݰ�
 
    AthleticsUIManager  *    pAthleticsUIManager;			//ս������UI������

	NpcTalkView   *			 pNpcTalkView;					//NPC�Ի���ͼ
     
	std::vector<HeroicRole *>       playGroupHeroicList;    //�����
	std::vector<HeroicRole *>       enemyGroupHeroicList;	//�з���
  
    int  curPlayGroupRoleID;		//��ǰ������ɫID
	char curPlayGroupRoleType;		//��ǰս����ɫ����
 
	int  curEnmeyGroupRoleID;		//��ǰ�з����ɫID
	char curEnmeyGroupRoleType;		//��ǰս����ɫ����

    bool isPlayGroupRoleChange;		//��ǰ������ɫ�Ƿ�ı� 
	bool isEnemyGroupRoleChange;	//��ǰ�о����ɫ�Ƿ�ı�
	 
	bool isTryPlayNpcTack;			//�Ƿ񲥷�NPCTalk
	char npcBattleTalkState;		// NPCTack����״̬
 
  //////////////////////////////////////////////////////////////////////////
	  
	HeroicRole *  leftFightRole_;		//���ɫ
	HeroicRole *  rightFightRole_;		//�ҽ�ɫ
	  
	float     hpRectWidth_;				//HP���������
	float     mpRectWidth_;				//MP���������
 		
	bool      isGameOver_;				//�ж���Ϸ�Ƿ����

	bool      isRePlayAthletics_;		//�Ƿ��ز�ս��

	std::multimap<int,CommonEffect *> m_shakeEffectList;
	 
	std::set<std::string>  preLoadPlistTexturePool;
	  
	unsigned char     athleticBattleType;  //ս������
 
	short	 callBackAdmittanceCount;	//��ɫ�볡������ɻص�����

	short    admittanceTickCount;		//�볡�����ص�����������

	char     athleticRecordType;		//ս����¼����

	char     athleticWatchType;			//ս���ۿ�����
	  
	bool	 isBattleWin;				//ս���Ƿ�ʤ�� 

	float    m_fRoleAdmissonDelayTime;   //ս����ɫ�볡�ӳ�ʱ�� 

	float    m_fResultWinDelayTime;		 //ս�������ʱʱ��

	bool	 m_bIsTriggerVIPSkip;		//�Ƿ񴥷�����VIPս��

	bool	 m_bIsLayOutUIData;		//�Ƿ��Ѿ�ɾ��UI����

	bool	m_bStartGame;

//@ս���ٶȹ���
//#������ٰ�ť���任˳��Ϊ1->2->3->1��
//begin
public:
	//�Ƿ�Ϊ1���ٶ�
	bool IsNormalSpeed(){
		return fabs(AthleticsSpeed-NormalSpeed)<0.001;
	}
	bool IsDoubleSpeed(){
		return fabs(AthleticsSpeed-NormalSpeedx2)<0.001;
	}
	bool IsTripleSpeed(){
		return fabs(AthleticsSpeed-NormalSpeedx3)<0.001;
	}

	static float AthleticsSpeed;		//��ǰս���ٶ�
private:
	float	  NormalSpeed;				//1���ٶ�
	float     NormalSpeedx2;			//2���ٶ�
	float	  NormalSpeedx3;			//3���ٶ�
//end
};

#define  ATHLETICSSCENEMANAGER  (AthleticsSceneManager::get_instance2())

#endif