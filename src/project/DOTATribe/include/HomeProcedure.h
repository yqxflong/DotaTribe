//Name��HomeProcedure
//Function������������
//Written By����ǿ

#ifndef  _DOTATRIBE_HOMEPROCEDURE_H_
#define  _DOTATRIBE_HOMEPROCEDURE_H_

#include "IProcedure.h"

class HomeProcedure : public IProcedure
{
private:
	int m_showWindow;
	bool m_bIsFristTime;
	int m_nSubViewType;
public:
	HomeProcedure();
	virtual ~HomeProcedure();
public:
	/*
		�Ƿ���Խ���ָ������
	*/
	bool  IsCanEnterScene(int sceneId);
	/*
		�л�����
	*/
	void  ChangeProcedureTo(IProcedure* procedure);

	/*
		�л���������Ӹ���
	*/
	void ChangeProcedureToTeamBattle();

	/*
		�����л�����ʱ��ת���ҳ��
	*/
	void SetShowWindow(int iWindowEventId);

	/*
	   �����Ӵ�������
	*/
	void SetSubViewType(int nSubViewType);

public:
	/*
		��ʼ������
	*/
	virtual      bool     Init();
	/*
		�߼��崦��
	*/
	virtual      void     Tick();
	/*
		��������
	*/
	virtual      void     Destroy();

protected:
	/*
		ϵͳ������Ϣ��Ӧ����
	*/
	virtual      void     OnInputEventHandler();
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
	static void Event_Procedure_Handler(int iEventType, std::string owerData, std::list<std::string>& paramList);
};


#endif
