//Name：DTEquipBoard
//Function：组合装备栏
//Written By：尹强

#include "../include/DTEquipBoard.h"
#include "../include/NFControlsManager.h"

USING_NS_CC;

DTEquipBoard::DTEquipBoard(){
	m_nEquipType=0;
	m_nEquipID=0;
	m_nTouchPriority=0;
	m_pDelegate=NULL;
	m_pEquip=NULL;
	m_pNum=NULL;
	m_pHint=NULL;
	m_pCorner=NULL;
	m_pBoard=NULL;
	m_pMask=NULL;
}

DTEquipBoard* DTEquipBoard::create(CCSprite* hint,CCSprite* corner,CCLabelTTF* num){
	DTEquipBoard* cc=new DTEquipBoard();
	if (cc->init(hint,corner,num))
	{
		cc->autorelease();
		return cc;
	}
	delete cc;cc=NULL;
	return cc;
}

bool DTEquipBoard::init(CCSprite* hint,CCSprite* corner,CCLabelTTF* num){
	if (!CCNode::init())
		return false;

	m_pHint=hint;
	m_pCorner=corner;
	m_pNum=num;
	m_pBoard=CCSprite::create();
	m_pMask=CCSprite::create();
	_resetBoard();
	_initLayout();
	_setCornerVisible(false);
	return true;
}

void DTEquipBoard::_initLayout(){
	//board
	m_pBoard->setZOrder(0);
	m_pBoard->setAnchorPoint(CCPointZero);
	m_pBoard->setPosition(CCPointZero);
	this->addChild(m_pBoard);
	//hint
	if (m_pHint)
	{
		m_pHint->setZOrder(0);
		m_pHint->setAnchorPoint(ccp(0.5,0.5));
		m_pHint->setPosition(ccp(m_pBoard->getContentSize().width/2,m_pBoard->getContentSize().height/2));
		m_pBoard->addChild(m_pHint);
	}

	//Mask
	m_pMask->setZOrder(2);
	m_pMask->setAnchorPoint(ccp(0.5,0.5));
	m_pMask->setPosition(ccp(m_pBoard->getContentSize().width/2,m_pBoard->getContentSize().height/2));
	m_pBoard->addChild(m_pMask);

	//corner
	m_pNum->setAnchorPoint(ccp(0.5,0.5));
	m_pNum->setPosition(ccp(m_pCorner->getContentSize().width/2,m_pCorner->getContentSize().height/2));
	m_pCorner->addChild(m_pNum);
	m_pCorner->setZOrder(1);
	m_pCorner->setAnchorPoint(ccp(0.3f,0.3f));
	m_pCorner->setPosition(CCPointZero);
	this->addChild(m_pCorner);
}

void DTEquipBoard::_setCornerNum(unsigned int num){
	NFC_setLabelStringInt(m_pNum,num);
}
void DTEquipBoard::_setCornerVisible(bool isvisible){
	m_pCorner->setVisible(isvisible);
}
void DTEquipBoard::_changeBoard(int quality){
	//board
	string file=varConfig::getCardBGFilePath(quality);
	m_pBoard->setProperty("File",file);

	//Mask
	file=varConfig::getCardMaskFilePath(quality);
	m_pMask->setProperty("File",file);

}

void DTEquipBoard::_resetBoard(){
	//board
	string file=varConfig::getCardNormalBGFilePath();
	m_pBoard->setProperty("File",file);

	//Mask
	file=varConfig::getCardNormalMaskFilePath();
	m_pMask->setProperty("File",file);

}

void DTEquipBoard::_showHint(bool isshow){
	if (m_pHint)
	{
		m_pHint->setVisible(isshow);
	}
}

//卸掉装备
void DTEquipBoard::RemoveEquip(){
	if (m_pEquip)
	{
		m_pEquip->removeFromParent();
		m_pEquip=NULL;
	}
	_showHint(true);
	_setCornerVisible(false);
	_resetBoard();
}

//设置优先级
void DTEquipBoard::setTouchPriority(int iPriority){
	m_nTouchPriority=iPriority;
}

//设置装备
void DTEquipBoard::SetEquip(int type,BagEquipData* equip,DTEquipBoardDelegate* pDel){
	assert(equip!=NULL);
	assert(equip->template_!=NULL);
	//
	m_nEquipType=type;
	m_nEquipID=equip->id_;
	m_pDelegate=pDel;
	RemoveEquip();
	//
	CImmovableMenu* menu=CImmovableMenu::create(m_nTouchPriority);
	menu->setAnchorPoint(CCPointZero);
	menu->setPosition(CCPointZero);
	menu->setZOrder(1);
	m_pBoard->addChild(menu);
	string file=NFC_getFileFromResourceID(equip->template_->iconId_);
	m_pEquip=CMenuItemSprite::create(file.c_str(),this,menu_selector(DTEquipBoard::On_Click_Equip));
	m_pEquip->setAnchorPoint(ccp(0.5,0.5));
	m_pEquip->setPosition(ccp(m_pBoard->getContentSize().width/2,m_pBoard->getContentSize().height/2));
	menu->addChild(m_pEquip);
	//
	_changeBoard(equip->template_->quality_);
	_showHint(false);
	_setCornerVisible(true);
	_setCornerNum(equip->level_);
}

void DTEquipBoard::SetEquip(int iconID,int quality,int level)
{ 
	RemoveEquip();
	CImmovableMenu* menu=CImmovableMenu::create(m_nTouchPriority);
	menu->setAnchorPoint(CCPointZero);
	menu->setPosition(CCPointZero);
	menu->setZOrder(1);
	m_pBoard->addChild(menu);
	string file=NFC_getFileFromResourceID(iconID);
	m_pEquip=CMenuItemSprite::create(file.c_str(),this,menu_selector(DTEquipBoard::On_Click_Equip));
	m_pEquip->setAnchorPoint(ccp(0.5,0.5));
	m_pEquip->setPosition(ccp(m_pBoard->getContentSize().width/2,m_pBoard->getContentSize().height/2));
	menu->addChild(m_pEquip);
	 
	_changeBoard(quality);
	_showHint(false);
	_setCornerVisible(true);
	_setCornerNum(level); 
}


void DTEquipBoard::On_Click_Equip(cocos2d::CCObject* pSender){
	if (m_pDelegate)
	{
		m_pDelegate->CallBack_ClickEquip(m_nEquipType,m_nEquipID);
	}
}