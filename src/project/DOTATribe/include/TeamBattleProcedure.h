//Name:TeamBattleProcedure
//Function:��Ӹ�������
//Author:fangjun
//Date:20130918

#ifndef  _DOTATRIBE_TEAMBATTLEPROCEDURE_H_
#define  _DOTATRIBE_TEAMBATTLEPROCEDURE_H_

#include "IProcedure.h"

class  TeamBattleProcedure: public IProcedure
{
public:
	enum{
		_TEAMBATTLE_STATE_UNKNOW_,		//δ֪״̬
		_TEAMBATTLE_STATE_SELECTGATE_,	//ѡ����Ӹ����Ĺؿ�
		_TEAMBATTLE_STATE_WAITTEAMER_,	//���
		_TEAMBATTLE_STATE_STARTFIFHT_,	//��ʼս��

	};

private:
	int m_nowState;			//��ǰ����״̬
	int m_backWindow;		//�رջ���ҳ��


public:
	TeamBattleProcedure();
	virtual ~TeamBattleProcedure();

public:
	virtual      bool     Init();

	virtual      void     Tick();

	virtual      void     Destroy();

public:
	/*
		ϵͳ������Ϣ��Ӧ����
	*/
	virtual      void     OnInputEventHandler();

public:
	/*
		ϵͳ�����̨�¼���Ӧ����
	*/
	virtual      void     OnSystemEnterBackEventHandler();
	/*
		ϵͳ����ǰ̨�¼���Ӧ����
	*/
	virtual      void     OnSystemEnterFrontEventHandler();
	/* 
		ϵͳ��ͣ�¼���Ӧ����
	*/
	virtual      void     OnSystemPauseEventHandler();
	/*
		ϵͳ�ָ��¼���Ӧ����
	*/
	virtual      void     OnSystemResumeEventHandler();

public:
	/*
		���û���ҳ��
	*/
	void SetBackWindow(int backwindowId);

	/*
		���ָ��״̬������
	*/
	void GetProvideStateData(int stateEnumId);

	/*
		ת����ǰ״̬��
	*/
	void ChangeNowState(int stateEnumId);

	/*
		��õ�ǰ��������״̬
	*/
	int GetNowState();

	/*
		��ת������Home
	*/
	void ChangeProcedureToHomeWithLoading();

	/*
		��ת������������
	*/
	void ChangeProcedureToAthletic();

	/*
		disconnect with TeamBattleProcedure
	*/
	void DisconnectNetworkHandler();

	static void Event_Procedure_Handler(int iEventType, std::string owerData, std::list<std::string>& paramList);
};

#endif
