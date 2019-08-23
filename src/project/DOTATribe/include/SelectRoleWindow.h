//Name��SelectRoleWindow
//Function��ѡ��ɫ
//Author:������

#ifndef  _DOTATRIBE_SELECTROLEWINDOW_H_
#define  _DOTATRIBE_SELECTROLEWINDOW_H_

#include "IWindow.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include <string>
#include <list>

using namespace cocos2d;
using namespace cocos2d::extension;

class CreateRoleData;
class SelectRoleWindow : public IWindow,public cocos2d::extension::CCEditBoxDelegate
{
public:
	SelectRoleWindow();
	virtual ~SelectRoleWindow();

	enum{
		udSKENODE,//�����������
		udBG,//����ͼ
		udTXTBG,//�������ֱ���
		udNAMEBG,//�������ֱ���
		udSERVERBG,//����������
		udENTERBTN,//������Ϸ��ť
		udSELECTNAMEBTN,//ѡ���ְ�ť
		udSERVERNAME,//��������
		udNAME,//����
		udTEXT,//����
		udEFFECT1,		//��Ч1
		udEFFECT2,		//��Ч2
		udEFFECT3,		//��Ч3
		udROLELEFT,		//����
		udROLECENTER,	//����
		udROLERIGHT,	//����
		udEditBOX,		//�����
		};
	std::map<int, CCSkeletonAnimation*> m_SelectPlayerMapList;
	int m_PlayerIndex;
	int m_PlayerCount;
	int m_LeftPlayerIndex;
	int m_MidPlayerIndex;
	int m_RightPlayerIndex;
	bool IsInSelectPlayer;
	bool IsFirstInSelectPlayer;
	bool IsMoving;
	bool IsBeginLeave;
	bool IsBeginEnter;
	CCLabelTTF* pRoleDesc;
	cocos2d::CCPoint  touchBeginPos;
	cocos2d::CCPoint  touchEndPos;
	CCSkeletonAnimation* m_LeftPlayerSkeleton;
	CCSkeletonAnimation* m_RightPlayerSkeleton;
	CCSkeletonAnimation* m_MidPlayerSkeleton;
	CreateRoleData* pLeftData;
	CreateRoleData* pMidData;
	CreateRoleData* pRightData;
	CCEditBox* pEditBox;
	CCNode* pRootNode;
	bool m_IsKeyBoard;
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
	/*
		��ʾ��������¼�����
	*/
	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	/*
		���´�������¼�����
	*/
	void   OnUpdateWindowEventHandler(std::list<std::string>& paramList);
		/*
		�󻬶��¼�����
	*/
	void   OnTurnLeftEventHandler();
	/*
		�һ����¼�����
	*/
	void   OnTurnRightEventHandler(); 

private:
	void   InitControl();
	void   InitRegister();
	inline void   _mapBtn();

	void CheckLeaveAnimation();
	void CheckEnterAnimation();

	void InitRolePosition();
	CCSkeletonAnimation * FindSkeletonByIndex(int index);
	void OnUpdateSelectPlayer();
	void OnPlayLeaveAnimation();
	void OnPlayEnterAnimation();
	void OnUpdatePlayerName(std::string name);

	std::string GetAnimationNameById(int shapeID,int skillID);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);   

/*
	virtual void keyboardWillShow(cocos2d::CCIMEKeyboardNotificationInfo& info); 
	virtual void keyboardDidShow(cocos2d::CCIMEKeyboardNotificationInfo& info); 
	virtual void keyboardWillHide(cocos2d::CCIMEKeyboardNotificationInfo& info); 
	virtual void keyboardDidHide(cocos2d::CCIMEKeyboardNotificationInfo& info);*/

	virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);
public:
	void On_Click_BtnClick(cocos2d::CCObject* pSender);
};

#endif
