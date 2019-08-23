// Name :		LessResourceWindow.h
// Function:	资源不足窗口
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _DOTATRIBE_LESSRESOURCEWINDOW_H_
#define  _DOTATRIBE_LESSRESOURCEWINDOW_H_


#include "IWindow.h"
#include "../include/CPriorityLayerColor.h"
#include "../include/LessResourceDataHandler.h"
using namespace std;
class LessResourceWindow : public IWindow,public CPriorityLayerColorDelegate
{
public:
	LessResourceWindow();
	virtual ~LessResourceWindow();
	enum
	{
		LessResource_Mark_Layer,
		LessResource_BG,
		LessResource_TitleBG,
		LessResource_Title,
		LessResource_Close_Button,
		LessResource_Desc_UP,
		LessResource_Item_BG,
		LessResource_Item,
		LessResource_Item_Num,
		LessResource_Other_Button,
		LessResource_Other_Button_Label,
		LessResource_Sure_Button,
		LessResource_Sure_Button_Label,
		LessResource_Mark_Layer2,
		LessResource_Mark_Layer2_Smale,
		LessResource_BG_Small,
		LessResource_Small_Button_Up,
		LessResource_Small_Button_Down,
		LessResource_Small_Button_Left,
		LessResource_Small_Button_Right,
		LessResource_end,
	};
	enum
	{
		LessResource_Less_Unknow,
		LessResource_Less_Energy,
		LessResource_Less_Town,
		LessResource_Less_Athletic,
		LessResource_Less_Hunt,
		LessResource_Less_Relic,
	};
	void InitLayer();
	void OnUpdateInfo();
	void HideCurWindow();
	std::string GetTypeString(int type);
	void GotoOther(DoingData* pData);
	int	GetDoingIcon(int type);
	
public:
	CCNode* m_pRoot;
	CPriorityLayerColor* pBigLayer;
	CPriorityLayerColor* pSmallLayer;
	virtual    bool    Init();
	virtual    bool    Load();
	virtual    void    Tick();
	virtual    void    Destroy();
public:

	virtual	void	OnEventHandler(int iEventType, std::list<std::string>& paramList);
	virtual	void	touchEvent(CPriorityLayerColor* pLayerColor);
	void On_Close(cocos2d::CCObject* pSender);
	void On_SingleClick(cocos2d::CCObject* pSender);
	void On_SureClick(cocos2d::CCObject* pSender);
	void On_ItemClick(cocos2d::CCObject* pSender);
private:

	void   OnShowWindowEventHandler(std::list<std::string>& paramList);
	void   OnUpdateUITextEventHandler(std::list<std::string>& paramList);

};


#endif
