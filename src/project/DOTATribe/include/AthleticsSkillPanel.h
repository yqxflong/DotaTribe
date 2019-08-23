#ifndef  _DOTATRIBE_ATHLETICSKILLPANEL_H
#define  _DOTATRIBE_ATHLETICSKILLPANEL_H

#include <cocos2d.h>

////////////////////////////////////////////////////////////////
//Name:	 AthleticsSkillPanel
//Auchor: 	xiaobo.wu
//Func:	 战斗技能信息面板
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////


#define    MAXITEMCOUNT			8

typedef  struct  skillPanle_tag
{
	std::string coatName;			// 外套名称
	std::string coatlevel;			// 外套等级	
	std::string petName;			// 宠物名称
	std::string petlevel;			// 宠物等级	
	std::string attackValue;		// 攻击值
	std::string speedValue;			// 速度值
	std::string hitValue;			// 命中值
	std::string dodgeValue;			// 防御值
	std::string sunderValue;		// 破甲值
	std::string armorValue;			// 护甲值
	std::string critValue;			// 暴击值
	std::string toughnessValue;		// 韧性值
	int  skillIconArray[MAXITEMCOUNT];

public:
    skillPanle_tag()
	{
		coatName="";
		coatlevel="";
		petName="";
		petlevel="";
		attackValue="";
		speedValue="";
		hitValue="";
		dodgeValue="";
		sunderValue="";
		armorValue="";
		critValue="";
		toughnessValue="";
		memset(skillIconArray,0,sizeof(skillIconArray));

	}
}SKILLPENLDATA;



//战斗技能面板结点
class  AthleticsSkillPanel: public cocos2d::CCNode
{
public:
     AthleticsSkillPanel();
	 virtual ~AthleticsSkillPanel();
public:
	static  AthleticsSkillPanel *  createAthleticSkillPanel(SKILLPENLDATA skillPanelData,bool isLeftPanel=true);
   
	void    updateAthleticsSkillPanelWithSkillData(SKILLPENLDATA skillPanelData);
public:

	void     setCoatName(std::string coatName);
	void     setCoatLevel(std::string coatLevel);
	void     setPetName(std::string petName);
	void     setPetLevel(std::string petLevel);
	void     setAttackValue(std::string attackValue);
	void     setSpeedValue(std::string speedValue);
	void     setHitValue(std::string hitValue);
	void     setDodgeValue(std::string dodgeValue);
	void     setSunderValue(std::string sunderValue);
	void     setArmorValue(std::string armorValue);
	void	 setCritValue(std::string critValue);
	void     setTougenessValue(std::string toughnessValue);
 
	void     setSkillIconArray(int * pskillIconArray);

protected:
	bool     initAthLeticSkillPanel(SKILLPENLDATA skillPanelData,bool isLeftPanel);
	void     onInitWithPanelUI();
	void     onRenderSkillIconOnPanel();

	std::string	  getConfigTextFromSysLangID(int langID);
private:
	 //属性数值
	cocos2d::CCSprite   *  skillPanelBackGround_;  //技能信息面板背景
	cocos2d::CCLabelTTF *  coatName_;		//外套名称
	cocos2d::CCLabelTTF *  coatLevel_;		//外套强化等级
	cocos2d::CCLabelTTF *  petName_;		//宠物昵称
	cocos2d::CCLabelTTF *  petLevel_;		//宠物强化等级

	cocos2d::CCLabelTTF *  attackValue_;    //攻击值
	cocos2d::CCLabelTTF *  speedValue_;     //速度
	cocos2d::CCLabelTTF *  hitValue_;       //命中值
	cocos2d::CCLabelTTF *  dodgeValue_;     //闪避
	cocos2d::CCLabelTTF *  sunderValue_;    //破甲
	cocos2d::CCLabelTTF *  armorValue_;     //护甲
	cocos2d::CCLabelTTF *  critValue_;      //暴击
	cocos2d::CCLabelTTF *  toughnessValue_; //韧性
 
	cocos2d::CCSprite *   skillIconArray[MAXITEMCOUNT];	

	bool	 isLeftSkillPanel_; 
	float    offSetForRightPanel;
	float    spriteScaleValue_;
};




#endif