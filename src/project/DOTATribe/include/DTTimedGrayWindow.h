//Name��DTTimedGrayWindow
//Function������ʱ������
//Written By����ǿ
//PS: Ψһ��ʧ;��Ϊ����ʱ����

#ifndef  _DOTATRIBE_DTTimedGrayWindow_H_
#define  _DOTATRIBE_DTTimedGrayWindow_H_

#include "IWindow.h"

class DTTimedGrayWindow : public IWindow
{
private:
	float m_fTick;
public:
	DTTimedGrayWindow();
	virtual ~DTTimedGrayWindow(){};

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

public:
	/*
		��Ϣ�¼���Ӧ����
	*/
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);

private:
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
};


#endif
