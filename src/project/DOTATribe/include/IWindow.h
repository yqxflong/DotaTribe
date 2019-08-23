#ifndef  _DOTATRIBE_IWINDOW_H_
#define  _DOTATRIBE_IWINDOW_H_


#include <cocos2d.h>
#include <cocos-ext.h>
#include <string>
#include <list>
#include "LoggerSystem.h"
using  namespace  cocos2d;
using  namespace  cocos2d::extension;


class IWindow : public cocos2d::CCNode
	, public cocos2d::CCTouchDelegate
{
public:
	enum
	{
		_TYPED_WINDOW_UNKOWN_,           // δ֪���͵�UI����
		_TYPED_WINDOW_START_,           // ��ʼ����
		_TYPED_WINDOW_LOADING_,          // ���ؽ���������
		_TYPED_WINDOW_DTTIMEDGRAYLAYER_, //����ʱ������
		_TYPED_WINDOW_ROLESTATUS_,              //����״̬��
		_TYPED_WINDOW_MESSAGEBOX_,       // MessageBox����
		_TYPED_WINDOW_LOGO_,             // LOGO����
		_TYPED_WINDOW_HOME_,			 // ������
		_TYPED_WINDOW_ATHLETIC_,         // ��ս������
		_TYPED_WINDOW_ATHLETICSRESULT_,  // ս���������
		_TYPED_WINDOW_SELECTROLE,		 // ѡ���ɫ����
		_TYPED_WINDOW_STRENGTHEN_,			// Ӣ����������
		_TYPED_WINDOW_LEVELUPNORMAL_,    // ������������
		_TYPED_WINDOW_PESWINDOW_,			//�����Ϣ����
		_TYPED_WINDOW_SKINSELECTWINDOW_,    //�����׽���
		_TYPED_WINDOW_SELECTSKILLWINDOW_,  //ѡ���ܽ���
		_TYPED_WINDOW_SELECTMISSION_,		//�����ͼѡ�����
		_TYPED_WINDOW_SELECTSONMISSION_,	//�ؿ�ѡ�����
		_TYPED_WINDOW_MASSACRE_,			//ɨ������
		_TYPED_WINDOW_SELECTCARDLISTWINDOW_, //ѡȡ�زĿ�����
		_TYPED_WINDOW_HEROBAR_,			    //Ӣ�۾ƹݽ���
		_TYPED_WINDOW_SELECTSERVER_,	    //ѡ�����������
		_TYPED_WINDOW_INPUTNUMWINDOW_,		//�������ֽ���
        _TYPED_WINDOW_RESULTHEROUP_,        //Ӣ�������������
		_TYPED_WINDOW_HEROTECHNOLOGY_,      //Ӣ�ۿƼ�����
		_TYPED_WINDOW_EQUIPMENTSELECT_,		//ѡ��װ�����棬��װ������ʹ��
		_TYPED_WINDOW_EQUIPMENTSELECTCARD_,	//װ��������ѡ��Ƭ����
		_TYPED_WINDOW_SYSTEMSETWINDOW_,		//ϵͳ���ý���
		_TYPED_WINDOW_ARENAWINDOW_,			//����������
		_TYPED_WINDOW_CHATWINDOW_,			//�������
		_TYPED_WINDOW_NOTICEBOXWINDOW_,		//�������
		_TYPED_WINDOW_SHOPWINDOW_,			//�̵����
		_TYPED_WINDOW_EFFECTWINDOW_,		//EffectWindow
		_TYPED_WINDOW_CLIMBWINDOW_,			//��������
		_TYPED_WINDOW_BAGWINDOW_,			//�±���
		_TYPED_WINDOW_SHOPINPUTBUYWINDOW_,	//�̵��������򴰿�
		_TYPED_WINDOW_REVENUE_,				//���մ���
		_TYPED_WINDOW_GUIDE_,				//GuideWindow
	    _TYPEF_WINDOW_TIPSWINDOW_,		    //QA���ɴ���
		_TYPED_WINDOW_MARKETWINDOW_,		//�̳Ǵ���
		_TYPED_WINDOW_COMMUNICATIONWAITTINGWINDOW_, //ͨ�ŵȴ�����
		_TYPEF_WINDOW_HEROTIPSWINDOW_,            //Ӣ��tips
		_TYPED_WINDOW_TEAMBATTLEWINDOW_,	//��Ӹ���
		_TYPED_WINDOW_TEAMSELECTWINDOW_,	//���ѡ�����
		_TYPED_WINDOW_FRIEND_,
		_TYPEF_WINDOW_PLAYERTIPSWINDOW_,            //�������tips
		_TYPED_WINDOW_RANK_WINDOW_,			//�������а�
		_TYPED_WINDOW_EMAIL_WINDOW_,			//���䴰��
		_TYPED_WINDOW_PUCONG_WINDOW_,			//�ʹӸ�����
		_TYPED_WINDOW_NETOBJECTTIPSWINDOW_,		//������Ʒtips
		_TYPED_WINDOW_EQUIPTIPSWINDOW_,		//װ��tips����
		_TYPED_WINDOW_WRITEEMAILWINDOW_,		//д�Ŵ���
		_TYPED_WINDOW_ERRORTIPSWINDOW_,		//������ʾ����

		_TYPED_WINDOW_BATTLECAPABILITYWINDOW_,		//ս����������

		_TYPED_WINDOW_HELPWINDOW_,					//��������

		_TYPED_WINDOW_MAINTASKWINDOW_,			    //�������񴰿�

		_TYPED_WINDOW_ANNOUNCEMENT_WINDOW_,		    //���洰��

		_TYPED_WINDOW_LIMITEDACTIVITY_WINDOW_,			//��ʱ�����

		_TYPED_WINDOW_RECHARGE_WINDOW_,				 //��ֵ����
		_TYPED_WINDOW_RECHARGEWARN_WINDOW_,				 //��ֵ���˺����Ѵ���
		_TYPED_WINDOW_VIP_WINDOW_,					//VIP����
		_TYPED_WINDOW_TEMPLE_,				//������
		_TYPED_WINDOW_CONVICTION_,			//��������

		_TYPED_WINDOW_FORCEPUSHTASKREWARD_WINDOW_,		//������ǿ����������������

		_TYPED_WINDOW_MINEAREA_WINDOW_,			//��������
		 
		_TYPED_WINDOW_ACTIVITY_,			//�������
		_TYPED_WINDOW_ACTIVITY_SPRING,		//��Ȫ�����

		_TYPEF_WINDOW_HeroIllustratedWindow_,	//Ӣ��ͼ������

		_TYPEF_WINDOW_LessResourceWindow_,	//��Դ���㴰��


		_TYPEF_WINDOW_LEADERSHIPLVUPWINDOW_,	//�쵼����������
		_TYPED_WINDOW_ALTARWINDOW_,				//�׼�����
		_TYPED_WINDOW_GAINHEROWINDOW_,			//���Ӣ�۴���
		_TYPEF_WINDOW_HeroAdvancedWindow_,		//Ӣ�۽��״���
		_TYPED_WINDOW_GAINSOULDEBRIWINDOW_,		//�������Ƭ����
		_TYPED_WINDOW_CHECKLEADERSHIPWINDOW_,	//�鿴��ǰͳ��������
		_TYPED_WINDOW_MULTIREWARDWINDOW_,		//��������򴰿�
		_TYPED_WINDOW_FIRSTRECHWINDOW_,			//�׳���������
		_TYPED_WINDOW_NEWEQUIPREMINDWINDOW_,	//��װ�����Ѵ���
		_TYPED_WINDOW_ARENAREWARDWINDOW_,		//�鿴��������������
		_TYPED_WINDOW_LEVELUPREWARDACTIVITYWINDOW_,//�������������
		_TYPED_WINDOW_SHOPTIPSWINDOW_,			//�̵�TIPS����

		_TYPED_WINDOW_BOSSSCORE_,				//boss����ϵͳ
		
		_TYPED_WINDOW_ACTIVITYLOGIN_,			//ÿ�ջ����

		_TYPED_WINDOW_HEROSOULWINDOW_,			//Ӣ��ս�괰��
		_TYPED_WINDOW_EXCHANGEACTIVITYWINDOW_,	//�һ������
		_TYPED_WINDOW_ACTIVITYGROWUPPLAN_,		//�ɳ��ƻ������

		_TYPED_WINDOW_SOULTIPSWINDOW_,			//ս��TIPS����

		_TYPED_WINDOW_APPSTOREWAITWINDOW_,		//AppStore֧���ȴ�����

		_TYPED_WINDOW_VIPGIFTWINDOW_,			//vip�������

		_TYPED_WINDOW_TENCALLWINDOW,			//ʮ������ʾ����
		_TYPED_WINDOW_GAINCALLITEMWINDOW_,		//����ٻ���Ʒ����
		_TYPED_WINDOW_TEAMINFOWINDOW_,			//������Ϣ����

		_TYPED_WINDOW_NUMBER_,					//window����
	};

public:
	enum
	{
		_TYPED_ALERT_WINDOW_UNKOWN_,                   // δ֪�����͵ľ�����ʾ����
 
	};

public:
	enum
	{
		_TYPED_WINDOW_ZORDER_UNKOWN_, // δ֪�Ĵ���Z-Order����
		_TYPED_WINDOW_ZORDER_NORMAL_, // ��ͨ�Ĵ���Z-Order����
		_TYPED_WINDOW_ZORDER_HIGH_,   // �ߵȼ����ڵ�Z-Order����
		_TYPED_WINDOW_ZOREDR_HIGHEST_,// ��ߵȼ����ڵ�Z-Order����
		_TYPED_WINDOW_ZOREDR_TOP_,    // ��߸����Ĵ���Z-Order����(��Ϊ�����ͻ���ϵͳ��ϵͳ��Ϣ���)
	};

public:
	struct _SCRIPT_TIMER_FUNCTION_
	{
		long  long  mStartTime;     // ��ʼʱ��
		int         mIntervalTime;  // ���ʱ��
		std::string mScriptFunction;// �ű���ʱ�ص�����
		_SCRIPT_TIMER_FUNCTION_()
		{
			mStartTime    = 0;
			mIntervalTime = 0;
		}
	};

protected:
	int                 m_WindowType;       // ������������
	std::string         m_WindowName;       // ��������
	bool                m_bModelWindow;     // �Ƿ�Ϊģ̬ģʽ����
	int                 m_WindowZOrder;     // ����Z-Order����
	std::string         m_ParentWindowName; // ���ڸ����ڵ�����
	bool                m_bLoaded;          // �Ƿ��Ѿ�����
	bool                m_bShow;            // ��layout��Ӧ�ĸ������Ƿ�ɼ�
	bool                m_bTickListener;    // �Ƿ�֡�ص�����
	cocos2d::CCNode*    m_pRootNode;        // ��Layout��Ӧ�ĸ�����
	bool				m_bIsForceClearUnUseTex; //�Ƿ�ǿ�ƻص�δ������
	bool				m_bIsForceClearAnimation;//�Ƿ�ǿ���ͷŶ�������


protected:
	long    long        m_TickCounter;      // �߼�֡����

protected:
	std::string         m_WindowDataList[16];// �����ڲ������б�(���ڽ��б��沿���������)

protected:
	std::list<_SCRIPT_TIMER_FUNCTION_> m_ScriptTimerList;// �ű���ʱ�ӿ�

public:
	IWindow();
	virtual ~IWindow();

public:
	/*
		�õ���ǰLAYOUT����
	*/
	int                GetWindowType();
	/*
		�Ƿ��Ѿ�����
	*/
	bool               IsLoad();
	/*
		�õ�������ָ��
	*/
	cocos2d::CCNode*   GetRootNode();

public:
	/*
		���ô���ָ������������
	*/
	void  SetWindowDataByPos(std::string str, unsigned int pos);
	/*
		�õ�
	*/
	std::string GetWindowDataByPos(unsigned int pos);

public:
	/*
		�Ƿ�֡����
	*/
	virtual    void    SetTickListenser(bool bListenser);
	/*
		����LAYOUT��ʾ������
	*/
	virtual    void    Show(bool bShow);
	/*
		�ж�LAYOYUT�Ƿ�ɼ�
	*/
	virtual    bool    IsVisible();

public:
	/*
		����X����
	*/
	virtual    void    SetXPosition(float xPos);
	/*
		�õ�X����
	*/
	virtual    float   GetXPosition();
	/*
		����Y����
	*/
	virtual    void    SetYPosition(float yPos);
	/*
		�õ�Y����
	*/
	virtual    float   GetYPosition();
	/*
		����X���ű���
	*/
	virtual    void    SetXScale(float xScale);
	/*
		����Y���ű���
	*/
	virtual    void    SetYScale(float yScale);
	/*
		ע��UI���¼�
	*/
	virtual    void    RegisterEvent(int iEventType, bool bNotifyOnlyWhenVisible=false);
	/*
		�ַ��¼�
	*/
	virtual    void    PushEvent(int iEventType);
	/*
		�ַ��¼�
	*/
	virtual    void    PushEvent(int iEventType, char* pArgs);
	/*
		���Ŵ��ڴ�ʱ����Ч
	*/
	virtual    void    PlayOpenSound();

	/*
		���Ŵ��ڹر�ʱ����Ч
	*/
	virtual    void    PlayCloseSound();
public:
	/*
		ע��ű���ʱ�ص��ӿ�
	*/
	virtual    void    RegisterTimerFunction(float time, std::string functionName);

public:
	/*
		��ʼ������
	*/
	virtual    bool    Init();
	/*
		���ش���
	*/
	virtual    bool    Load();
	/*
		����´���
	*/
	virtual    void    Tick();
	/*
		���ٴ���
	*/ 
	virtual    void    Destroy();

	/*
		���ش�������ͼƬ��Դplist
	*/
	void LoadPlistForWindow();
	/*
		�����������ͼƬ��Դplist
	*/
	void UnloadPlistForWindow();
public:
	/*
		��Ϣ�¼���Ӧ����
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList)   =   0;

public:
	/*
		��ʼ�Ӵ�����
	*/
	virtual    bool    ccTouchBegan(cocos2d::CCTouch* touche, cocos2d::CCEvent* event);
	/*
		�ƶ�����
	*/
	virtual    void    ccTouchMoved(cocos2d::CCTouch* touche, cocos2d::CCEvent* event);
	/*
		�Ӵ���������
	*/
	virtual    void    ccTouchEnded(cocos2d::CCTouch* touche, cocos2d::CCEvent* event);
	/*
		�Ӵ�ȡ������
	*/
	virtual    void    ccTouchCancel(cocos2d::CCTouch* touche, cocos2d::CCEvent* event);
};


#endif
