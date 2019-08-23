// Name :		LevelupNormalWindow.h
// Function:	½ÇÉ«Éý¼¶´°¿Ú
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#ifndef  _DOTATRIBE_LEVELUPNORMALWINDOW_H_
#define  _DOTATRIBE_LEVELUPNORMALWINDOW_H_


#include "IWindow.h"
#include "../include/LevelUpDataHandler.h"
#include "../include/IPopWindow.h"

class LevelupNormalWindow : public IWindow,public IPopWindow
{
public:
	LevelupNormalWindow();
	virtual ~LevelupNormalWindow();
	enum
	{
		LvUp_MarkLayer,
		LvUp_Type1BG,
		LvUp_Type1LvImage,
		LvUp_Type1LvValue,
		LvUp_Type1SureButton,
		LvUp_Type1SureButtonLabel,

		LvUp_Type2BG,
		LvUp_Type2LvImage,
		LvUp_Type2LvValue,
		LvUp_Type2SkillLabel,
		LvUp_Type2SkillBG,
		LvUp_Type2SkillImage,
		LvUp_Type2SeeButton,
		LvUp_Type2SeeButtonLabel,
		LvUp_Type2SureButton,
		LvUp_Type2SureButtonLabel,
		LvUp_Type2SeeButtonEffect,

		LvUp_Type3BG,
		LvUp_Type3LvImage,
		LvUp_Type3LvValue,
		LvUp_Type3Skill1Label,
		LvUp_Type3Skill1BG,
		LvUp_Type3Skill1Image,
		LvUp_Type3Skill2Label,
		LvUp_Type3Skill2BG,
		LvUp_Type3Skill2Image,
		LvUp_Type3SeeButton,
		LvUp_Type3SeeButtonLabel,
		LvUp_Type3SureButton,
		LvUp_Type3SureButtonLabel,
		LvUp_Type3SeeButtonEffect,

		LvUp_Type4BG,
		LvUp_Type4LvImage,
		LvUp_Type4LvValue,
		LvUp_Type4FunctionImage,
		LvUp_Type4Skill1Label,
		LvUp_Type4Skill1BG,
		LvUp_Type4Skill1Image,
		LvUp_Type4Skill2Label,
		LvUp_Type4Skill2BG,
		LvUp_Type4Skill2Image,
		LvUp_Type4SeeButton,
		LvUp_Type4SeeButtonLabel,
		LvUp_Type4SureButton,
		LvUp_Type4SureButtonLabel,
		LvUp_Type4SeeButtonEffect,

		LvUp_End,
	};
	enum
	{
		LvUp_TypeUnknow,
		LvUp_Type1,
		LvUp_Type2,
		LvUp_Type3,
		LvUp_Type4,
	};
	CCNode* m_pLabel;
	CCNode* m_Root;
	CCNode* m_Layer1;
	CCNode* m_Layer2;
	CCNode* m_Layer3;
	CCNode* m_Layer4;
	CCSprite* pAdpetEffect2;
	CCSprite* pAdpetEffect3;
	int m_functionID;
	int m_newSkillID;
	int m_subType; 
public:
	virtual    bool    Init();
	virtual    bool    Load();
	virtual    void    Tick();
	virtual    void    Destroy();
	//ÏÔÊ¾µ¯´°
	virtual void ShowPopWindow();
	//µ¯´°ÒÑ¾­Òþ²Ø
	virtual void PopWindowDidHide();
public:
	virtual    void    OnEventHandler(int iEventType, std::list<std::string>& paramList);
	CCNode* SetLvArtFont();
	CCNode* SetShowLayer(int type);
	int	GetType(LevelUpData* pData);
	void SetFunctionId();
	void SetNewSkillId();
	void InitLayerout();
	void SetLayerInfo();
	void SetFunctionImage();
	void DeleteUsedLvUpData();
	void ShowSelfRoot(bool flag);
	void OnSureButtonClick(cocos2d::CCObject* pSender);
	void OnViewButtonClick(cocos2d::CCObject* pSender);
	void OnShowWindowEventHandler(std::list<std::string>& paramList);
	void ShowWindow();
	void OnUpdateUITextEventHandler(std::list<std::string>& paramList);

private:
	inline void _uckCreateLayerout();
	inline void _uckCreateLayer();
	inline void _uckCreateLayer1();
	inline void _uckLayerSetLv();
	inline void _uckCreateLayer2();
	inline void _uckCreateLayer3();
	inline void _uckCreateLayer4();
	inline void _uckSetLayerLv(int lv ,CCNode* layer,int tag);
	inline void _uckSetSkillName(CCNode* layer,int tag,bool isProfessional);
	inline void _uckSetSkillBG(CCNode* layer,int tag,bool isProfessional);
	inline void _uckSetSkillImage(CCNode* layer,int tag,int skill);
protected:
	int  m_nUiAdpetEffectID;
};


#endif
