////////////////////////////////////////////////////////////////
//Name:	 AthleticsSkillPanel
//Auchor: 	xiaobo.wu
//Func:	 战斗技能信息面板
//Maintainer: 	xiaobo.wu
//date:   2014/01/03
////////////////////////////////////////////////////////////////
#include  <cocos2d.h>
#include  "../include/AthleticsSkillPanel.h"
#include  "../include/AthleticsWindow.h"
#include  "../include/SysLangDataManager.h"
#include  "../include/ResourceIDDataManager.h"
#include  "../include/NFControlsManager.h"
#include  "../include/AthleticsWindow.h"
 

#define   LEFTANCHOR  ccp(0.0f,0.0f)


//之后为提出来归为统一管理
#define   ATTACKID      90  
#define   SPEEDID		91
#define   HITID			92
#define   DODGEID		93
#define   SUNDERID		94
#define   ARMORID		95	
#define   CRITID		96
#define   TOUGHNESSID   97
 

//文字描述ID
#define    COATVALUEID       101
#define    COATLEVEID        102
#define    PETNAMEID         103
#define    PETLEVELID        104
#define    ATTACKVALUEID     105
#define    SPEEDVALUEID      106
#define    HITVALUEID        107
#define    DODGEVALUEID      108
#define    SUNDERVALUEID     109
#define    ARMORVALUEID      110
#define    CRITVALUEID       111
#define    TOUGENESSVALUEID  112
#define    SWORDLABELID		 682


//按钮图片ID
#define     EXPAND_PANEL_BTN   665

//分割线图片ID
#define     EXPAND_PANEL_SEGMENT 593
 		
  

AthleticsSkillPanel::AthleticsSkillPanel()
{
    skillPanelBackGround_=NULL;
    coatName_=NULL;
	coatLevel_=NULL;
	petName_=NULL;
	petLevel_=NULL;

	attackValue_=NULL;    //攻击值
	speedValue_=NULL;     //速度
	hitValue_=NULL;       //命中值
	dodgeValue_=NULL;     //闪避
    sunderValue_=NULL;    //破甲
	armorValue_=NULL;     //护甲
	critValue_=NULL;      //暴击
	toughnessValue_=NULL; //韧性

	memset(skillIconArray,NULL,sizeof(skillIconArray));
    spriteScaleValue_=Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_SKILL_START_OFFSET)->getScale();
	 
	offSetForRightPanel=0.0f;

	isLeftSkillPanel_=false;

}

AthleticsSkillPanel::~AthleticsSkillPanel()
{ 
	for (int i=0;i<MAXITEMCOUNT;i++)
	{ 
		if(skillIconArray[i]!=NULL)
		{ 
			skillIconArray[i]->removeFromParentAndCleanup(true);
			skillIconArray[i]=NULL;
		}
	}
	this->removeAllChildrenWithCleanup(true);
	this->removeFromParentAndCleanup(true);
 
}

AthleticsSkillPanel  * AthleticsSkillPanel::createAthleticSkillPanel(SKILLPENLDATA skillPanelData,bool isLeftPanel)
{
   AthleticsSkillPanel * pAthleticSkillPanel=new AthleticsSkillPanel();
   if(pAthleticSkillPanel&&pAthleticSkillPanel->initAthLeticSkillPanel(skillPanelData,isLeftPanel))
   {
       pAthleticSkillPanel->autorelease();
 	   return  pAthleticSkillPanel;
   }
   if(pAthleticSkillPanel!=NULL)
   {
	   delete pAthleticSkillPanel;
	   pAthleticSkillPanel=NULL;
   }
   return NULL;
}

 
bool    AthleticsSkillPanel::initAthLeticSkillPanel(SKILLPENLDATA skillPanelData,bool isLeftPanel)
{    
     //to do for modify for Plist Frame
	 skillPanelBackGround_=cocos2d::CCSprite::create();
 
	 skillPanelBackGround_->setProperty("File",ResourceIDDataManager::get_instance2()->getDataByID(EXPAND_PANEL_BTN).c_str());
	 isLeftSkillPanel_=isLeftPanel;
	 if(!isLeftPanel)
	 {
	    skillPanelBackGround_->setFlipX(true);
 	 }
	 skillPanelBackGround_->setAnchorPoint(LEFTANCHOR);

	 this->addChild(skillPanelBackGround_);
	  
	 offSetForRightPanel=((CCNode *)Athletics_UI_Node(AthleticsWindow::ATHlETICS_UI_SKILL_RIGHT_OFFSET))->getContentSize().width;
	  
	 updateAthleticsSkillPanelWithSkillData(skillPanelData);

	 onInitWithPanelUI();
     return true;
}



void    AthleticsSkillPanel::updateAthleticsSkillPanelWithSkillData(SKILLPENLDATA skillPanelData)
{
	if(!skillPanelData.coatName.empty())
	{    
		//外套名称
		setCoatName(skillPanelData.coatName);
	}
	if(!skillPanelData.coatlevel.empty()&&skillPanelData.coatlevel!="0")
	{ 
		//外套等级
		setCoatLevel(skillPanelData.coatlevel);
	}
	if(!skillPanelData.petName.empty())
	{
		//宠物昵称
		setPetName(skillPanelData.petName);
	}
	if(!skillPanelData.petlevel.empty())
	{
		//宠物等级
		setPetLevel(skillPanelData.petlevel);
	}

	if(!skillPanelData.attackValue.empty())
	{
		//攻击值
		setAttackValue(skillPanelData.attackValue);
	}
	if(!skillPanelData.speedValue.empty())
	{
		//速度值
		setSpeedValue(skillPanelData.speedValue);
	}
	if(!skillPanelData.hitValue.empty())
	{
		//命中
		setHitValue(skillPanelData.hitValue);
	}
	if(!skillPanelData.dodgeValue.empty())
	{
		//闪避
		setDodgeValue(skillPanelData.dodgeValue);

	}
	if(!skillPanelData.sunderValue.empty())
	{
		//破甲
		setSunderValue(skillPanelData.sunderValue);
	}
	if(!skillPanelData.armorValue.empty())
	{
		//护甲
		setArmorValue(skillPanelData.armorValue);

	}
	if(!skillPanelData.critValue.empty())
	{
		//暴击
		setCritValue(skillPanelData.critValue);
	}
	if(!skillPanelData.toughnessValue.empty())
	{
		//韧性
		setTougenessValue(skillPanelData.toughnessValue);
	}

	//更新技能数组
	setSkillIconArray(skillPanelData.skillIconArray);
	onRenderSkillIconOnPanel();
}

 
 
 
void     AthleticsSkillPanel::setCoatName(std::string coatName)
{
    //外套名称
	if(this->getChildByTag(COATVALUEID)!=NULL)
	{
		this->removeChildByTag(COATVALUEID,true);
	}
	coatName_=cocos2d::CCLabelTTF::create();  
	CCNode * pMaskNode=(CCNode *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_SKILL_HERONAME);
	NFC_setLabelByFontStyleID(coatName_,(int)pMaskNode->getContentSize().width);
	coatName_->setString(coatName.c_str());
	coatName_->setAnchorPoint(ccp(0,0));

	if(isLeftSkillPanel_)
	coatName_->setPosition(pMaskNode->getPosition());
	else
	coatName_->setPosition(ccp(pMaskNode->getPositionX()+offSetForRightPanel,pMaskNode->getPositionY()));

	this->addChild(coatName_,0,COATVALUEID);
	
}
 
void     AthleticsSkillPanel::setCoatLevel(std::string coatLevel)
{
  
}

void     AthleticsSkillPanel::setPetName(std::string petName)
{
     //宠物名称
	if(this->getChildByTag(PETNAMEID)!=NULL)
	{
		this->removeChildByTag(PETNAMEID,true);
	}
	petName_=cocos2d::CCLabelTTF::create();
	CCNode * pMaskNode=(CCNode *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_SKILL_COMBAT_LABLE);
	NFC_setLabelByFontStyleID(petName_,(int)pMaskNode->getContentSize().width);
	petName_->setString(petName.c_str());
	petName_->setAnchorPoint(ccp(0,0));
 
	if(isLeftSkillPanel_)
	petName_->setPosition(pMaskNode->getPosition());
	else
	petName_->setPosition(ccp(pMaskNode->getPositionX()+offSetForRightPanel,pMaskNode->getPositionY()));
	this->addChild(petName_,0,PETNAMEID);

	 
}
void     AthleticsSkillPanel::setPetLevel(std::string petLevel)
{
	 //宠物等级
	if(this->getChildByTag(PETLEVELID)!=NULL)
	{
		this->removeChildByTag(PETLEVELID,true);
	}
	petLevel_=cocos2d::CCLabelTTF::create();
	CCNode * pMaskNode=(CCNode *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_SKILL_COMBAT_VALUE);
	NFC_setLabelByFontStyleID(petLevel_,(int)pMaskNode->getContentSize().width);
	petLevel_->setString(petLevel.c_str());
	petLevel_->setAnchorPoint(ccp(0,0));
 
	if(isLeftSkillPanel_)
	petLevel_->setPosition(pMaskNode->getPosition());
	else
    petLevel_->setPosition(ccp(pMaskNode->getPositionX()+offSetForRightPanel,pMaskNode->getPositionY()));
	this->addChild(petLevel_,0,PETLEVELID);
	
}
void     AthleticsSkillPanel::setAttackValue(std::string attackValue)
{
      //攻击值
	if(this->getChildByTag(ATTACKVALUEID)!=NULL)
	{
		this->removeChildByTag(ATTACKVALUEID,true);
	}
	attackValue_=cocos2d::CCLabelTTF::create();
	CCNode * pMaskNode=(CCNode *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_SKILL_ATTACK_VALUE);
	NFC_setLabelByFontStyleID(attackValue_,(int)pMaskNode->getContentSize().width);
	attackValue_->setString(attackValue.c_str());
	attackValue_->setAnchorPoint(ccp(0,0));
	 
	if(isLeftSkillPanel_)
	attackValue_->setPosition(pMaskNode->getPosition());
	else
	attackValue_->setPosition(ccp(pMaskNode->getPositionX()+offSetForRightPanel,pMaskNode->getPositionY()));
	this->addChild(attackValue_,0,ATTACKVALUEID);

}
void     AthleticsSkillPanel::setSpeedValue(std::string speedValue)
{
	if(this->getChildByTag(SPEEDVALUEID)!=NULL)
	{
		this->removeChildByTag(SPEEDVALUEID,true);
	}
	speedValue_=cocos2d::CCLabelTTF::create();
	CCNode * pMaskNode=(CCNode *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_SKILL_SPEED_VALUE);
	NFC_setLabelByFontStyleID(speedValue_,(int)pMaskNode->getContentSize().width);
	speedValue_->setString(speedValue.c_str());
	speedValue_->setAnchorPoint(ccp(0,0));
 
	if(isLeftSkillPanel_)
	speedValue_->setPosition(pMaskNode->getPosition());
	else
	speedValue_->setPosition(ccp(pMaskNode->getPositionX()+offSetForRightPanel,pMaskNode->getPositionY()));
	this->addChild(speedValue_,0,SPEEDVALUEID);
	 

}
void     AthleticsSkillPanel::setHitValue(std::string hitValue)
{
	if(this->getChildByTag(HITVALUEID)!=NULL)
	{
		this->removeChildByTag(HITVALUEID,true);
	}
	hitValue_=cocos2d::CCLabelTTF::create();
	CCNode * pMaskNode=(CCNode *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_SKILL_HIT_VALUE);
	NFC_setLabelByFontStyleID(hitValue_,(int)pMaskNode->getContentSize().width);
	hitValue_->setString(hitValue.c_str());
	hitValue_->setAnchorPoint(ccp(0,0));
 
	if(isLeftSkillPanel_)
	hitValue_->setPosition(pMaskNode->getPosition());
	else
	hitValue_->setPosition(ccp(pMaskNode->getPositionX()+offSetForRightPanel,pMaskNode->getPositionY()));
	this->addChild(hitValue_,0,HITVALUEID);

}
void     AthleticsSkillPanel::setDodgeValue(std::string dodgeValue)
{
	if(this->getChildByTag(DODGEVALUEID)!=NULL)
	{
		this->removeChildByTag(DODGEVALUEID,true);
	}
	dodgeValue_=cocos2d::CCLabelTTF::create();
	CCNode * pMaskNode=(CCNode *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_SKILL_DODGE_VALUE);
	NFC_setLabelByFontStyleID(dodgeValue_,(int)pMaskNode->getContentSize().width);
	dodgeValue_->setString(dodgeValue.c_str());
	dodgeValue_->setAnchorPoint(ccp(0,0));
	 
	if(isLeftSkillPanel_)
	dodgeValue_->setPosition(pMaskNode->getPosition());
	else
	dodgeValue_->setPosition(ccp(pMaskNode->getPositionX()+offSetForRightPanel,pMaskNode->getPositionY()));
	this->addChild(dodgeValue_,0,DODGEVALUEID);
	 
}
void     AthleticsSkillPanel::setSunderValue(std::string sunderValue)
{
	if(this->getChildByTag(SUNDERVALUEID)!=NULL)
	{
		this->removeChildByTag(SUNDERVALUEID,true);
	}
	sunderValue_=cocos2d::CCLabelTTF::create();
	CCNode * pMaskNode=(CCNode *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_SKILL_SUNDER_VALUE);
	NFC_setLabelByFontStyleID(sunderValue_,(int)pMaskNode->getContentSize().width);
	sunderValue_->setString(sunderValue.c_str());
	sunderValue_->setAnchorPoint(ccp(0,0));
 
	if(isLeftSkillPanel_)
	sunderValue_->setPosition(pMaskNode->getPosition());
	else
	sunderValue_->setPosition(ccp(pMaskNode->getPositionX()+offSetForRightPanel,pMaskNode->getPositionY()));
	this->addChild(sunderValue_,0,SUNDERVALUEID);
  
}

void     AthleticsSkillPanel::setArmorValue(std::string armorValue)
{
	if(this->getChildByTag(ARMORVALUEID)!=NULL)
	{
		this->removeChildByTag(ARMORVALUEID,true);
	}
	armorValue_=cocos2d::CCLabelTTF::create();
	CCNode * pMaskNode=(CCNode *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_SKILL_ARMOR_VALUE);
	NFC_setLabelByFontStyleID(armorValue_,(int)pMaskNode->getContentSize().width);
	armorValue_->setString(armorValue.c_str());
	armorValue_->setAnchorPoint(ccp(0,0));

	if(isLeftSkillPanel_)
	armorValue_->setPosition(pMaskNode->getPosition());
	else
	armorValue_->setPosition(ccp(pMaskNode->getPositionX()+offSetForRightPanel,pMaskNode->getPositionY()));
	this->addChild(armorValue_,0,ARMORVALUEID);
 
}
void	 AthleticsSkillPanel::setCritValue(std::string critValue)
{
	if(this->getChildByTag(CRITVALUEID)!=NULL)
	{
		this->removeChildByTag(CRITVALUEID,true);
	}
	critValue_=cocos2d::CCLabelTTF::create();
	CCNode * pMaskNode=(CCNode *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_SKILL_CRIT_VALUE);
	NFC_setLabelByFontStyleID(critValue_,(int)pMaskNode->getContentSize().width);
	critValue_->setString(critValue.c_str());
	critValue_->setAnchorPoint(ccp(0,0));
 
	if(isLeftSkillPanel_)
	critValue_->setPosition(pMaskNode->getPosition());
	else
	critValue_->setPosition(ccp(pMaskNode->getPositionX()+offSetForRightPanel,pMaskNode->getPositionY()));
	this->addChild(critValue_,0,CRITVALUEID);
 

}
void     AthleticsSkillPanel::setTougenessValue(std::string toughnessValue)
{
	if(this->getChildByTag(TOUGENESSVALUEID)!=NULL)
	{
		this->removeChildByTag(TOUGENESSVALUEID,true);
	}
	toughnessValue_=cocos2d::CCLabelTTF::create();
	CCNode * pMaskNode=(CCNode *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_SKILL_TENACITY_VALUE);
	NFC_setLabelByFontStyleID(toughnessValue_,(int)pMaskNode->getContentSize().width);
	toughnessValue_->setString(toughnessValue.c_str());
	toughnessValue_->setAnchorPoint(ccp(0,0));
 
	if(isLeftSkillPanel_)
	toughnessValue_->setPosition(pMaskNode->getPosition());
	else
    toughnessValue_->setPosition(ccp(pMaskNode->getPositionX()+offSetForRightPanel,pMaskNode->getPositionY()));
	this->addChild(toughnessValue_,0,TOUGENESSVALUEID);
	 
}
void     AthleticsSkillPanel::setSkillIconArray(int * pskillIconArray)
{
   int  skillIndex=0;
   std::string   skillIconPath;
   for(int i=0;i<MAXITEMCOUNT;i++)
   { 
	   if(skillIconArray[i]!=NULL)
	   {
		   this->removeChild(skillIconArray[i],true);
		   skillIconArray[i]=NULL;
	   }
	   if(pskillIconArray[i]!=0&&pskillIconArray[i]!=-1)
	   {
		   skillIconPath=ResourceIDDataManager::get_instance2()->getDataByID(pskillIconArray[i]);
		   if(!skillIconPath.empty())
		   {
			   skillIconArray[skillIndex]=cocos2d::CCSprite::create();
			   skillIconArray[skillIndex]->setProperty("File",skillIconPath);
			   skillIconArray[skillIndex]->setScale(spriteScaleValue_);
			   skillIndex++;
		   }
	   }
	 
   } 
}



void    AthleticsSkillPanel::onRenderSkillIconOnPanel()
{ 
	float addInter=Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_SKILL_INTERVAL)->getContentSize().width;
	float startOffset=Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_SKILL_START_OFFSET)->getContentSize().width;
	float heightlevel1=Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_SKILL_UP_CONFIG)->getContentSize().width;
	float heightlevel2=Athletics_UI_Node(AthleticsWindow::ATHELTICS_UI_SKILL_DONW_CONFIG)->getContentSize().width;
	if(!isLeftSkillPanel_)
	startOffset+=offSetForRightPanel;
 
    for(int i=0;i<MAXITEMCOUNT;i++)
	{ 
		if(skillIconArray[i]!=NULL)
		{
			if(i<4)
			{
				skillIconArray[i]->setPosition(ccp(startOffset+addInter*i,heightlevel1));
			}
			else
			{
				skillIconArray[i]->setPosition(ccp(startOffset+addInter*(i-4),heightlevel2));
			}
			this->addChild(skillIconArray[i]);
		}
		else
		{
			return ;
		}
	}
}



std::string	  AthleticsSkillPanel::getConfigTextFromSysLangID(int langID)
{
	return SysLangDataManager::get_instance2()->GetSysLangById(langID);
}


void     AthleticsSkillPanel::onInitWithPanelUI()
{
	cocos2d::CCLabelTTF  * attackName_=cocos2d::CCLabelTTF::create();
	CCNode * pMaskNode=(CCNode *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_SKILL_ATTACK_LABLE);
	NFC_setLabelByFontStyleID(attackName_,(int)pMaskNode->getContentSize().width);
	attackName_->setString(getConfigTextFromSysLangID(ATTACKID).c_str());
	attackName_->setAnchorPoint(LEFTANCHOR);
 
	if(isLeftSkillPanel_)
	attackName_->setPosition(pMaskNode->getPosition());
	else
	attackName_->setPosition(ccp(pMaskNode->getPositionX()+offSetForRightPanel,pMaskNode->getPositionY()));
	this->addChild(attackName_);
 

	cocos2d::CCLabelTTF *  speedName=cocos2d::CCLabelTTF::create();
	pMaskNode=(CCNode *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_SKILL_SPEED_LABLE);
	NFC_setLabelByFontStyleID(speedName,(int)pMaskNode->getContentSize().width);
	speedName->setString(getConfigTextFromSysLangID(SPEEDID).c_str());
	speedName->setAnchorPoint(LEFTANCHOR);
	 
	if(isLeftSkillPanel_)
	speedName->setPosition(pMaskNode->getPosition());
	else
	speedName->setPosition(ccp(pMaskNode->getPositionX()+offSetForRightPanel,pMaskNode->getPositionY()));
	this->addChild(speedName);


	cocos2d::CCLabelTTF *  hitName=cocos2d::CCLabelTTF::create();
	pMaskNode=(CCNode *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_SKILL_HIT_LABLE);
	NFC_setLabelByFontStyleID(hitName,(int)pMaskNode->getContentSize().width);
	hitName->setString(getConfigTextFromSysLangID(HITID).c_str());
	hitName->setAnchorPoint(LEFTANCHOR);
 
	if(isLeftSkillPanel_)
	hitName->setPosition(pMaskNode->getPosition());
	else
	hitName->setPosition(ccp(pMaskNode->getPositionX()+offSetForRightPanel,pMaskNode->getPositionY()));
	this->addChild(hitName);
	 

	cocos2d::CCLabelTTF *  dodgeName=cocos2d::CCLabelTTF::create();
	pMaskNode=(CCNode *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_SKILL_DODGE_LABLE);
	NFC_setLabelByFontStyleID(dodgeName,(int)pMaskNode->getContentSize().width);
	dodgeName->setString(getConfigTextFromSysLangID(DODGEID).c_str());
	dodgeName->setAnchorPoint(LEFTANCHOR);
 
	if(isLeftSkillPanel_)
	dodgeName->setPosition(pMaskNode->getPosition());
	else
	dodgeName->setPosition(ccp(pMaskNode->getPositionX()+offSetForRightPanel,pMaskNode->getPositionY()));
	this->addChild(dodgeName);
 


	cocos2d::CCLabelTTF *  sunderName=cocos2d::CCLabelTTF::create();
	pMaskNode=(CCNode *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_SKILL_SUNDER_LABLE);
	NFC_setLabelByFontStyleID(sunderName,(int)pMaskNode->getContentSize().width);
	sunderName->setString(getConfigTextFromSysLangID(SUNDERID).c_str());
	sunderName->setAnchorPoint(LEFTANCHOR);
  
	if(isLeftSkillPanel_)
	sunderName->setPosition(pMaskNode->getPosition());
	else
	sunderName->setPosition(ccp(pMaskNode->getPositionX()+offSetForRightPanel,pMaskNode->getPositionY()));
	this->addChild(sunderName);
 

	cocos2d::CCLabelTTF *  armorName=cocos2d::CCLabelTTF::create();
	pMaskNode=(CCNode *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_SKILL_ARMOR_LABLE);
	NFC_setLabelByFontStyleID(armorName,(int)pMaskNode->getContentSize().width);
	armorName->setString(getConfigTextFromSysLangID(ARMORID).c_str());
	armorName->setAnchorPoint(LEFTANCHOR);
 
	if(isLeftSkillPanel_)
	armorName->setPosition(pMaskNode->getPosition());
	else
	armorName->setPosition(ccp(pMaskNode->getPositionX()+offSetForRightPanel,pMaskNode->getPositionY()));
	this->addChild(armorName);
	 
 
	cocos2d::CCLabelTTF *   critName=cocos2d::CCLabelTTF::create();
	pMaskNode=(CCNode *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_SKILL_CRIT_LABLE);
	NFC_setLabelByFontStyleID(critName,(int)pMaskNode->getContentSize().width);
	critName->setString(getConfigTextFromSysLangID(CRITID).c_str());
	critName->setAnchorPoint(LEFTANCHOR);
	 
	if(isLeftSkillPanel_)
	critName->setPosition(pMaskNode->getPosition());
	else
	critName->setPosition(ccp(pMaskNode->getPositionX()+offSetForRightPanel,pMaskNode->getPositionY()));
	this->addChild(critName);
 
	 
	cocos2d::CCLabelTTF *   toughnessName=cocos2d::CCLabelTTF::create();
	pMaskNode=(CCNode *)Athletics_UI_Node(AthleticsWindow::ATHLETICS_UI_SKILL_TENACITY_LABLE);
	NFC_setLabelByFontStyleID(toughnessName,(int)(int)pMaskNode->getContentSize().width);
	toughnessName->setString(getConfigTextFromSysLangID(TOUGHNESSID).c_str());
	toughnessName->setAnchorPoint(LEFTANCHOR);
	 
	if(isLeftSkillPanel_)
	toughnessName->setPosition(pMaskNode->getPosition());
	else
	toughnessName->setPosition(ccp(pMaskNode->getPositionX()+offSetForRightPanel,pMaskNode->getPositionY()));
	this->addChild(toughnessName);
  
}






