//Name：PlayerTipsWindow
//Function：玩家好友tips
//Written By：李茜
//Maintainer:  zhoushaonan, shaobing
//Time:2013-9-18

#include "../include/PlayerTipsWindow.h"
#include "../include/EventTyper.h"
#include "../include/UIViewDataManger.h"
#include "../include/CMenuItemSprite.h"
//#include"../include/RoleInfoDataHandler.h"
#include "../include/FriendDataHandler.h"
#include "../include/RoleShapeDataManager.h"
#include "../include/NFControlsManager.h"
#include "../include/DTEquipBoard.h"
#include "../include/EquipTipsWindow.h"
#include "../include/SoulTipsWindow.h"
#include "../include/FriendAddPacket.h"
#include "../include/FriendAgreeSinglePacket.h"
#include <map>
#include <string>
#include <vector>

USING_NS_CC;


PlayerTipsWindow::PlayerTipsWindow()
:m_pRoot(0)
{
	m_WindowType   = _TYPEF_WINDOW_PLAYERTIPSWINDOW_;
	m_bModelWindow = true;
	currentTab	   = _kTAB1_;
}

PlayerTipsWindow::~PlayerTipsWindow()
{

}

bool PlayerTipsWindow::Init()
{
	RegisterEvent(_TYPEF_EVENT_SHOW_PLAYERTIPSWINDOW_);
	RegisterEvent(_TYPEF_EVENT_HIDE_PLAYERTIPSWINDOW_, true);
	RegisterEvent(_TYPEF_EVENT_UPDATE_PLAYERTIPSWINDOW_, true);

	return IWindow::Init();
}
bool PlayerTipsWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		_initLayout();
		return true;
	} 
	while (false);

	return false;
}

void PlayerTipsWindow::Tick()
{
	IWindow::Tick();
}

void PlayerTipsWindow::Destroy()
{
	IWindow::Destroy();
}

void PlayerTipsWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPEF_EVENT_SHOW_PLAYERTIPSWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPEF_EVENT_HIDE_PLAYERTIPSWINDOW_)
	{
		Destroy();
	}
	else if(iEventType == _TYPEF_EVENT_UPDATE_PLAYERTIPSWINDOW_)
	{
		OnUpdateWindowEventHandler(paramList);
	}
}

void PlayerTipsWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
}

void  PlayerTipsWindow::OnUpdateWindowEventHandler(std::list<std::string>& paramList)
{
}

void PlayerTipsWindow::_initLayout()
{
	LOGGERSYSTEM->LogDebug("PlayerTipsWindow: _initLayout");
	m_pRoot=CCNode::create();
	m_pRootNode->addChild(m_pRoot,10);
	LOGGERSYSTEM->LogDebug("Start _initData");
	_initData();
	LOGGERSYSTEM->LogDebug("Start _setMask");
	_setMask();
	LOGGERSYSTEM->LogDebug("Start _createSkeleton");
	_createSkeleton();
	LOGGERSYSTEM->LogDebug("_setStars");
	_setStars();
	LOGGERSYSTEM->LogDebug("_setInfo");
	_setInfo();
	LOGGERSYSTEM->LogDebug("_setInfoEnd");
}


void PlayerTipsWindow::_initData()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kPLAYERTIPSWINDOW,m_pRoot);
	
	m_selectedFont = FontStyleDataManager::get_instance2()->getDataByID(48);
	m_unselectedFont = FontStyleDataManager::get_instance2()->getDataByID(30);
	ccColor3B sC = {m_selectedFont->colorR_,m_selectedFont->colorG_,m_selectedFont->colorB_};
	ccColor3B uC = {m_unselectedFont->colorR_,m_unselectedFont->colorG_,m_unselectedFont->colorB_};


	CCMenu* tabMenu = (CCMenu*)NFC_getNode(udEQUIPTABBTN,m_pRoot);
	m_equipTabItem = (CMenuItemSprite*)tabMenu->getChildByTag(0);
	m_equipTabItem->setRotation(180.0);
	m_equipTabItem->setTag(udEQUIPTABBTN);
	m_equipTabItem->setTarget(this,menu_selector(PlayerTipsWindow::On_TabSelected));
	
	tabMenu = (CCMenu*)NFC_getNode(udSOULTABBTN,m_pRoot);
	m_soulTabItem = (CMenuItemSprite*)tabMenu->getChildByTag(0);
	m_soulTabItem->setRotation(180.0);
	m_soulTabItem->setTag(udSOULTABBTN);
	m_soulTabItem->setTarget(this,menu_selector(PlayerTipsWindow::On_TabSelected));

	m_equipTabLabel = (CCLabelTTF*)NFC_getNode(udEQUIPTABBTNLABEL,m_pRoot);
	m_soulTabLabel = (CCLabelTTF*)NFC_getNode(udSOULTABBTNLABEL,m_pRoot);

	currentTab = _kTAB1_;
	m_equipTabItem->selected(true);
	m_equipTabLabel->setFontName(m_selectedFont->fontname_);
	m_equipTabLabel->setFontSize(m_selectedFont->fontsize_);
	m_equipTabLabel->setColor(sC);

	m_soulTabItem->unselected();
	m_soulTabLabel->setFontName(m_unselectedFont->fontname_);
	m_soulTabLabel->setFontSize(m_unselectedFont->fontsize_);
	m_soulTabLabel->setColor(uC);
		
	

	CCMenu* ptemp = (CCMenu*)m_pRoot->getChildByTag(udCLOSEBTN);
	CMenuItemSprite* ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(PlayerTipsWindow::On_Close));

	ptemp = (CCMenu*)m_pRoot->getChildByTag(udADDFRIENDBTN);
	ptempItem = (CMenuItemSprite*)ptemp->getChildByTag(0);
	ptempItem->setTarget(this,menu_selector(PlayerTipsWindow::On_AddFriend));
}

void PlayerTipsWindow::_setStars(){
	MaskNode *pData = (MaskNode*)NFC_getNode(udSTAR_DATA,m_pRoot);
	/* MaskNode中，filePath1_是普通星，filePath2_是红星，并且其中anchor, pos, zorder属性有效，规则最左边的星星位置，每颗星之间的距离由属性width控制*/
	UIViewData* dd = pData->GetViewPData();
	int level = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.shapeLevel; 
	if(level < 6){
		//全部显示普通星
		for(int i = 0; i < level +1; i++){
			CCSprite* star = CCSprite::create(dd->filepath2_);
			star->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
			star->setPosition(ccp(dd->posx_ + i * dd->width_,dd->posy_));
			m_pRoot->addChild(star,dd->zorder_);
		}
	}
	else if(level >= 6 && level < 9){
		//先显示红星再显示普通星
		int j;
		for(j = 0; j < level + 1 -6; j++){
			CCSprite *star = CCSprite::create(dd->filepath_);
			star->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
			star->setPosition(ccp(dd->posx_ + j * dd->width_, dd->posy_));
			m_pRoot->addChild(star,dd->zorder_);
		}
		for(;j < 6; j++){
			CCSprite* star = CCSprite::create(dd->filepath2_);
			star->setAnchorPoint(ccp(dd->anchorx_,dd->anchory_));
			star->setPosition(ccp(dd->posx_ + j * dd->width_, dd->posy_));
			m_pRoot->addChild(star,dd->zorder_);
		}
	}
	else{
		return;
	}

}

void PlayerTipsWindow::On_TabSelected(cocos2d::CCObject* pSender){
	CMenuItemSprite* item = (CMenuItemSprite*)pSender;
	ccColor3B sC = {m_selectedFont->colorR_,m_selectedFont->colorG_,m_selectedFont->colorB_};
	ccColor3B uC = {m_unselectedFont->colorR_,m_unselectedFont->colorG_,m_unselectedFont->colorB_};
	int tag = item->getTag();
	if( tag == udEQUIPTABBTN ){
		//设置标签页状态
		currentTab = _kTAB1_;
		m_equipTabItem->selected(true);
		m_equipTabLabel->setFontName(m_selectedFont->fontname_);
		m_equipTabLabel->setFontSize(m_selectedFont->fontsize_);
		m_equipTabLabel->setColor(sC);

		m_soulTabItem->unselected();
		m_soulTabLabel->setFontName(m_unselectedFont->fontname_);
		m_soulTabLabel->setFontSize(m_unselectedFont->fontsize_);
		m_soulTabLabel->setColor(uC);

		//更新UI
		NFC_showNode(udBOARD_1,m_pRoot,true);
		NFC_showNode(udBOARD_2,m_pRoot,true);
		NFC_showNode(udBOARD_3,m_pRoot,true);
		NFC_showNode(udBOARD_4,m_pRoot,true);
		NFC_showNode(udBOARD_5,m_pRoot,true);
		NFC_showNode(udBOARD_6,m_pRoot,true);
		NFC_showNode(udBOARD_7,m_pRoot,true);
		NFC_showNode(udBOARD_8,m_pRoot,true);

		NFC_showNode(udSOUL_1,m_pRoot,false);
		NFC_showNode(udSOUL_2,m_pRoot,false);
		NFC_showNode(udSOUL_3,m_pRoot,false);
		NFC_showNode(udSOUL_4,m_pRoot,false);

	}
	else if( tag == udSOULTABBTN ){
		//设置标签位置
		currentTab = _kTAB2_;
		m_equipTabItem->unselected();
		m_equipTabLabel->setFontName(m_unselectedFont->fontname_);
		m_equipTabLabel->setFontSize(m_unselectedFont->fontsize_);
		m_equipTabLabel->setColor(uC);

		m_soulTabItem->selected(true);
		m_soulTabLabel->setFontName(m_selectedFont->fontname_);
		m_soulTabLabel->setFontSize(m_selectedFont->fontsize_);
		m_soulTabLabel->setColor(sC);
		
		//更新UI
		NFC_showNode(udBOARD_1,m_pRoot,false);
		NFC_showNode(udBOARD_2,m_pRoot,false);
		NFC_showNode(udBOARD_3,m_pRoot,false);
		NFC_showNode(udBOARD_4,m_pRoot,false);
		NFC_showNode(udBOARD_5,m_pRoot,false);
		NFC_showNode(udBOARD_6,m_pRoot,false);
		NFC_showNode(udBOARD_7,m_pRoot,false);
		NFC_showNode(udBOARD_8,m_pRoot,false);

		NFC_showNode(udSOUL_1,m_pRoot,true);
		NFC_showNode(udSOUL_2,m_pRoot,true);
		NFC_showNode(udSOUL_3,m_pRoot,true);
		NFC_showNode(udSOUL_4,m_pRoot,true);
	}
	else{
		return;
	}
}
void PlayerTipsWindow::On_Close(cocos2d::CCObject* pSender)
{
	PushEvent(_TYPEF_EVENT_HIDE_PLAYERTIPSWINDOW_);
}

void PlayerTipsWindow::_setMask()
{
	//遮罩层大
	CPriorityLayerColor* cc=(CPriorityLayerColor*)m_pRoot->getChildByTag(MASKCCP);
	cc->setDelegate(this);
	cc->setPosition(CCPointZero);

	//遮罩层小
	CCSprite* bg = (CCSprite*)NFC_getNode(udBG,m_pRoot);
	CPriorityLayerColor* dd = (CPriorityLayerColor*)NFC_getNode(MASKSMALL,m_pRoot);
	dd->setAnchorPoint(ccp(0,0));
	dd->setContentSize(bg->getContentSize());
	dd->setPosition(ccp(bg->getPositionX() - bg->getAnchorPoint().x * bg->getContentSize().width,
		bg->getPositionY() - bg->getAnchorPoint().y * bg->getContentSize().height));
}

void PlayerTipsWindow::touchEvent(CPriorityLayerColor* pLayerColor)
{
//	if(pLayerColor->getTag() == MASKCCP)
//		PushEvent(_TYPEF_EVENT_HIDE_PLAYERTIPSWINDOW_);
}


void PlayerTipsWindow::_createSkeleton()
{ 
	//骨骼动画
	MaskNode* node=(MaskNode*)m_pRoot->getChildByTag(udSKELETONNODE);
	const UIViewData & dd=node->GetViewData();

	RoleShapeData *pData = RoleShapeDataManager::get_instance2()->GetRoleShapeById(FriendDataHandler::get_instance2()->m_SelectPlayerInfo.shapeId);
	cocos2d::extension::CCSkeletonAnimation * m_pSkeletonNode = CCSkeletonAnimation::createWithFile(pData->mShapeAnimationFileDaiJi,pData->mShapeAnimationImage);
	if(m_pSkeletonNode)
		m_pSkeletonNode->setAnimation("DaiJi",true); 
	m_pSkeletonNode->setAnchorPoint(node->getAnchorPoint());

	m_pSkeletonNode->setScale(pData->mShowScale / 100.0f);

	

	m_pSkeletonNode->setPosition(node->getPosition());
	m_pRoot->addChild(m_pSkeletonNode,node->getZOrder());



}

void PlayerTipsWindow::_setInfo()
{
	char temp[128] = "";
	LOGGERSYSTEM->LogDebug("_setInfo 123");
	//名字
	_setTTFText(udPLAYERNAME,FriendDataHandler::get_instance2()->m_SelectPlayerInfo.name.c_str());
	//lv值
	unsigned short lvl = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.level;
	sprintf(temp,"LV.%d",lvl);
	_setTTFText(udLVVALUE,temp);
	LOGGERSYSTEM->LogDebug("_setInfo 123");

	CCLabelTTF* nameLabel = (CCLabelTTF*)NFC_getNode(udPLAYERNAME,m_pRoot);
	CCLabelTTF* lvlLabel = (CCLabelTTF*)NFC_getNode(udLVVALUE,m_pRoot);
	lvlLabel->setPositionX(nameLabel->getPositionX() + nameLabel->getContentSize().width + 20);
	
	LOGGERSYSTEM->LogDebug("_setInfo 123");

	//战力
	int value = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.btlCapa;
	_setTTFText(udABILITYVALUE,value);		

	//HP
	value = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.hp;
	_setTTFText(udHPVALUE,value);

	LOGGERSYSTEM->LogDebug("_setInfo 123");
	//Mp
	value = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.mp;
	_setTTFText(udMPVALUE,value);

    //攻击
	int min = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.minAttack;
	int max = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.maxAttack;
	sprintf(temp,"%d~%d",min,max);
	_setTTFText(udATTACKVALUE,temp);

	LOGGERSYSTEM->LogDebug("_setInfo 123");
	//速度
	value = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.speed;
	_setTTFText(udSPEEDVALUE,value);

	//命中
	value = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.hit;
	_setTTFText(udHITVALUE,value);

	LOGGERSYSTEM->LogDebug("_setInfo 123");
	//破甲
	value = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.exposeArmor;
	_setTTFText(udSUNDERVALUE,value);

	LOGGERSYSTEM->LogDebug("_setInfo 123");
	//暴击
	value = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.cirt;
	_setTTFText(udGRITVALUE,value);

	LOGGERSYSTEM->LogDebug("_setInfo 123");
	//闪避
	value = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.dodge;
	_setTTFText(udDODGEVALUE,value);

	LOGGERSYSTEM->LogDebug("_setInfo 123");
	//护甲
	value = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.armor;
	_setTTFText(udARMORVALUE,value);
	LOGGERSYSTEM->LogDebug("_setInfo 123");

	//韧性
	value = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.uncirt;
	_setTTFText(udTOUGHNESSVALUE,value);

	LOGGERSYSTEM->LogDebug("_setInfo 123");
	//力量
	value = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.strength;
	_setTTFText(udSTRVALUE,value);

	LOGGERSYSTEM->LogDebug("_setInfo 123");
	//敏捷
	value = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.agility;
	_setTTFText(udAGIVALUE,value);

	LOGGERSYSTEM->LogDebug("_setInfo 123");
	//智力
	value = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.intelligence;
	_setTTFText(udINTVALUE,value);

	LOGGERSYSTEM->LogDebug("_setInfo 123");
	_setTTFText(udHERONAME, FriendDataHandler::get_instance2()->m_SelectPlayerInfo.shapeName.c_str());
	LOGGERSYSTEM->LogDebug("_setInfo 123");
	
	LOGGERSYSTEM->LogDebug("_setInfo start _setEquipInfo");
	_setEquipInfo();
	LOGGERSYSTEM->LogDebug("_setInfo end _setEquipInfo");

	LOGGERSYSTEM->LogDebug("_setInfo start _setSkillInfo");
	_setSkillInfo();
	LOGGERSYSTEM->LogDebug("_setInfo end _setSkillInfo");
	LOGGERSYSTEM->LogDebug("_setInfo start _setSoulInfo");
	_setSoulInfo();
	LOGGERSYSTEM->LogDebug("_setInfo end _setSoulInfo");
}

void PlayerTipsWindow::_setEquipInfo(){
	std::map<int,BagEquipData*> equips = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.equips;
	std::map<int,BagEquipData*>::iterator it = equips.begin();
	std::map<int,BagEquipData*>::iterator end = equips.end();
	//遍历
	for(;it != end; it++){
		if((*it).second->isEquiped_ == false)
			continue;
		// 8个装备槽，分别判断
		DTEquipBoard *item;
		switch((*it).first){
		case 0:						//武器
			item = (DTEquipBoard*)NFC_getNode(udBOARD_1,m_pRoot);
			item->SetEquip(kHETYPE_ROLE,(*it).second,this);
			break;
		case 1:						//衣服
			item = (DTEquipBoard*)NFC_getNode(udBOARD_2,m_pRoot);
			item->SetEquip(kHETYPE_ROLE,(*it).second,this);
			break;
		case 2:						//戒指
			item = (DTEquipBoard*)NFC_getNode(udBOARD_3,m_pRoot);
			item->SetEquip(kHETYPE_ROLE,(*it).second,this);
			break;
		case 3:						//鞋子
			item = (DTEquipBoard*)NFC_getNode(udBOARD_4,m_pRoot);
			item->SetEquip(kHETYPE_ROLE,(*it).second,this);
			break;
		case 4:						//圣物
			item = (DTEquipBoard*)NFC_getNode(udBOARD_5,m_pRoot);
			item->SetEquip(kHETYPE_ROLE,(*it).second,this);
			break;
		case 5:						//法球
			item = (DTEquipBoard*)NFC_getNode(udBOARD_6,m_pRoot);
			item->SetEquip(kHETYPE_ROLE,(*it).second,this);
			break;
		case 6:						//头盔
			item = (DTEquipBoard*)NFC_getNode(udBOARD_7,m_pRoot);
			item->SetEquip(kHETYPE_ROLE,(*it).second,this);
			break;
		case 7:						//饰品
			item = (DTEquipBoard*)NFC_getNode(udBOARD_8,m_pRoot);
			item->SetEquip(kHETYPE_ROLE,(*it).second,this);
			break;
		}
		LOGGERSYSTEM->LogDebug("Equip: %d",(*it).second->id_);
	}
}

void PlayerTipsWindow::CallBack_ClickEquip(int type, int equipId){
	CCLOG("EquipId = %d Click",equipId);
	if (type==kHETYPE_ROLE)
	{	
		std::string  strisequip = _to_event_param_(kTIPS_OTHEREQUIP);
		std::string  stridx = _to_event_param_(equipId);	
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_EQUIPTIPSWINDOW_,stridx,strisequip);
	}

}

void PlayerTipsWindow::_setSkillInfo(){
	std::map<int,SkillItem*> skills = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.skills;
	std::map<int,SkillItem*>::iterator it = skills.begin();
	std::map<int,SkillItem*>::iterator end = skills.end();
	int index = 0;
	CCSprite* item=NULL;
	for(;it != end; it++){
		int skillID=(*it).second->skillID;
		if(skillID< 0)
			continue;
		int skillIconID=(*it).second->skillIconID;
		string file=ResourceIDDataManager::get_instance2()->getDataByID(skillIconID).c_str();
		item = (CCSprite*)NFC_getNode(udSKILL_1 + index,m_pRoot);
		item->setProperty("File",file);	
		index++;
		LOGGERSYSTEM->LogInfo("Skill: %d",(*it).second->skillIconID);
	}
}

void PlayerTipsWindow::_setSoulInfo(){
	std::vector<IHeroSoulItem*> souls = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.souls;
	std::vector<IHeroSoulItem*>::iterator it = souls.begin();
	std::vector<IHeroSoulItem*>::iterator end = souls.end();

	std::map<int,SoulEquipItem*> soulStatus = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.soulStatus;

	int idx = 0;
	for(;it != end; it++){
		if( (*it)->getHeroSoulEquipIndex() == -1){
			LOGGERSYSTEM->LogDebug("Soul Equip == -1");
			continue;
		}
		LOGGERSYSTEM->LogDebug("Before If: %d, %d, %s, %d", (*it)->getHeroSoulEquipIndex(), (*it)->getHeroSoulBufferID(), (*it)->getHeroSoulBufferName().c_str(), (*it)->getHeroSoulBufferIconID());
		if( soulStatus.at((*it)->getHeroSoulEquipIndex()) != NULL && soulStatus.at((*it)->getHeroSoulEquipIndex())->m_uHeroSoulEquipIsOpen == true ){
			LOGGERSYSTEM->LogDebug("!123");
			DTHeroIcon* icon;
			switch((*it)->getHeroSoulEquipIndex()){
			case 0:
				icon = (DTHeroIcon*)NFC_getNode(udSOUL_1,m_pRoot);
				NFC_bindSelectorForDTHeroIcon(udSOUL_1,m_pRoot,this,menu_selector(PlayerTipsWindow::OnSoulIconClick));
				break;
			case 1:
				icon = (DTHeroIcon*)NFC_getNode(udSOUL_2,m_pRoot);
				NFC_bindSelectorForDTHeroIcon(udSOUL_2,m_pRoot,this,menu_selector(PlayerTipsWindow::OnSoulIconClick));
				break;
			case 2:
				icon = (DTHeroIcon*)NFC_getNode(udSOUL_3,m_pRoot);
				NFC_bindSelectorForDTHeroIcon(udSOUL_3,m_pRoot,this,menu_selector(PlayerTipsWindow::OnSoulIconClick));
				break;
			case 3:
				icon = (DTHeroIcon*)NFC_getNode(udSOUL_4,m_pRoot);
				NFC_bindSelectorForDTHeroIcon(udSOUL_4,m_pRoot,this,menu_selector(PlayerTipsWindow::OnSoulIconClick));
				break;
			}
			LOGGERSYSTEM->LogDebug("!456");
			icon->setHeroIconID((*it)->getHeroSoulBufferIconID());
			LOGGERSYSTEM->LogDebug("!789");
			icon->getHeroItemSprite()->setIDX((*it)->getHeroSoulBufferID());
			//icon->setIconScale(0.8);
			LOGGERSYSTEM->LogDebug("Soul: %d",icon->getHeroIconID());
		}
	}
}

void PlayerTipsWindow::_setTTFText(int key, const char * text)
{
	CCLabelTTF * ttf = (CCLabelTTF *)m_pRoot->getChildByTag(key);
	ttf->setString(text);
}

void PlayerTipsWindow::_setTTFText(int key, int text)
{
	char tmp[128] = "";
	sprintf(tmp, "%d", text);
	CCLabelTTF * ttf = (CCLabelTTF *)m_pRoot->getChildByTag(key);
	ttf->setString(tmp);
}

void PlayerTipsWindow::OnSoulIconClick(cocos2d::CCObject* pSender){
	CMenuItemSprite* item = (CMenuItemSprite*)pSender;
	CCLOG("Soul Tip Click! ID=%d",item->getIDX());
	int soulId = item->getIDX();

	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_SOULTIPSWINDOW_,_to_event_param_(soulId),_to_event_param_(_SOULTIPS_OTHER_));
}

void PlayerTipsWindow::On_AddFriend(cocos2d::CCObject* pSender){
	//如果是从申请列表过来，则直接同意申请，否则发出好友申请
	if (FriendDataHandler::get_instance2()->m_isFriend_Apply)
	{
		int playerid = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.id;
		C2SFriendAgreeSinglePacket pack(playerid);
		pack.Send();
	}
	else{
		int playerid = FriendDataHandler::get_instance2()->m_SelectPlayerInfo.id;
		C2SFriendAddPacket pack(playerid);
		pack.Send();
	}
}