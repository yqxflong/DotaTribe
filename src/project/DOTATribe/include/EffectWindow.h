//Name��EffectWindow
//Function������չ��Ч���Ĵ��ڣ���ʱ���ڻ����Ʒʱ
//Written By����ǿ

#ifndef  _DOTATRIBE_EffectWindow_H_
#define  _DOTATRIBE_EffectWindow_H_

#include "IWindow.h"

class EffectData;
class EffectWindow: public IWindow{
private:
	enum{
		udICON,
		udNUMLABEL,
		udNUMBJLABEL,
	};
	cocos2d::CCNode* m_pRoot;
public:
	enum{
		kOBJECT=0,
		kMONEY,
		kDIAMOND,
		kEXP,
	};
	EffectWindow();
	virtual ~EffectWindow(){};
private:
	inline void _initLayout();
//����ÿ��Ч��
	inline void _createICON(cocos2d::CCNode* effectNode,EffectData* dd);
	inline void _createLabel(cocos2d::CCNode* effectNode,EffectData* dd);
	inline void _createBJLabel(cocos2d::CCNode* effectNode,EffectData* dd);
	inline void _showEffect(cocos2d::CCNode* effectNode,EffectData* dd);
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

protected:
	void On_Animation_CallBack(cocos2d::CCNode* pSender);
};

#endif