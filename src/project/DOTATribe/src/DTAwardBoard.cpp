//Name：DTAwardBoard
//Function：奖励图框控件
//Written By：尹强

#include "../include/DTAwardBoard.h"
#include "../include/CMenuItemSprite.h"
#include "../include/CPublicVarReader.h"
#include "../include/NFControlsManager.h"

#define DTAB_GRAY_COLOR  ccc4(0,0,0,180)
const float big_ratio = 0.33f;
const float small_ratio = 0.28f;
using namespace std;
USING_NS_CC;

DTAwardBoard::DTAwardBoard()
:m_pBoard(NULL)
,m_nPriority(0)
,m_bSwallow(true)
,m_pObject(NULL)
,m_pObjectItem(NULL)
,m_pNum_BG(NULL)
,m_pNum(NULL)
,m_pMask(NULL)
,m_pGray(NULL)
,m_fContentScale(1.0f)
{

}

DTAwardBoard* DTAwardBoard::create(cocos2d::CCSprite* numBg,cocos2d::CCLabelTTF* num,int priority,bool swallow){
	DTAwardBoard* dd=new DTAwardBoard();
	if (dd&&dd->init(numBg,num,priority,swallow))
	{
		dd->autorelease();
		return dd;
	}
	CC_SAFE_DELETE(dd);
	return NULL;
}

bool DTAwardBoard::init(cocos2d::CCSprite* numBg,cocos2d::CCLabelTTF* num,int priority,bool swallow){
	if (!CCNode::init())
		return false;

	m_pNum=num;
	m_pNum_BG=numBg;
	m_nPriority=priority;
	m_bSwallow=swallow;
	_initLayout();

	return true;
}

	/*
		更改物品
	*/
void DTAwardBoard::ChangeObject(int quality,int iconid,int num){
	setVisible(true);
	if (quality!=-1){
		_changeBoard(quality);
	}else{
		_resetBoard();
	}
	if (iconid!=-1){
		_changeObject(iconid);
		_setObjectVisible(true);
	}else{
		_setObjectVisible(false);
	}
	if (num!=-1){
		_setNum(num);
	}else{
		_setNumVisible(false);
	}
}

void DTAwardBoard::setTarget(cocos2d::CCObject *rec, cocos2d::SEL_MenuHandler selector){
	assert(m_pObjectItem!=NULL);
	m_pObjectItem->setEnabled(true);
	m_pObjectItem->setTarget(rec,selector);
}

//重写设置Tag
void DTAwardBoard::setTag(int nTag){
	cocos2d::CCNode::setTag(nTag);
	assert(m_pObjectItem!=NULL);
	m_pObjectItem->setTag(nTag);
}


//设置与获取按钮的Index
void DTAwardBoard::setIDX(int idx){
	assert(m_pObjectItem!=NULL);
	m_pObjectItem->setIDX(idx);
}
void DTAwardBoard::setAttachParam(int attachParam1,int attachParam2/* =0 */)
{
	assert(m_pObjectItem!=NULL);
	m_pObjectItem->setAttachData1(attachParam1);
	m_pObjectItem->setAttachData2(attachParam2);
}

int DTAwardBoard::getIDX() const{
	assert(m_pObjectItem!=NULL);
	return m_pObjectItem->getIDX();
}

//设置所装载图片的缩放比率
void DTAwardBoard::setContentScale(float times)
{
	m_fContentScale = times;
	m_pObjectItem->setScale(m_fContentScale);
}

float DTAwardBoard::getContentScale()
{
	return m_fContentScale;
}

//设置按钮启用情况
void DTAwardBoard::setEnabled(bool bEnabled){
	assert(m_pObjectItem!=NULL);
	m_pObjectItem->setEnabled(bEnabled);
}

//设置成失效状态,带灰层
void DTAwardBoard::setDisabled(bool bDisabled){
	assert(m_pObjectItem!=NULL);
	m_pObjectItem->setEnabled(!bDisabled);
	m_pGray->setVisible(bDisabled);
}

void DTAwardBoard::_initLayout(){
	_initBoard();
	_initObject();
	_initNum();
	_initGray();
}

void DTAwardBoard::_initBoard(){
	m_pBoard=CCSprite::create();
	m_pMask=CCSprite::create();
	_resetBoard();
	//board
	m_pBoard->setZOrder(0);
	m_pBoard->setAnchorPoint(CCPointZero);
	m_pBoard->setPosition(CCPointZero);
	this->addChild(m_pBoard);	
	//mask
	m_pMask->setZOrder(2);
	m_pMask->setAnchorPoint(ccp(0.5f,0.5f));
	m_pMask->setPosition(ccp(m_pBoard->getContentSize().width/2,m_pBoard->getContentSize().height/2));
	m_pBoard->addChild(m_pMask);
}
void DTAwardBoard::_initObject(){
	//menu
	m_pObject=CImmovableMenu::create(m_nPriority,m_bSwallow);
	m_pObject->setAnchorPoint(CCPointZero);
	m_pObject->setPosition(CCPointZero);
	m_pObject->setZOrder(1);
	m_pBoard->addChild(m_pObject);
	//item
	m_pObjectItem=CMenuItemSprite::create();
	m_pObjectItem->setAnchorPoint(ccp(0.5,0.5));
	m_pObjectItem->setPosition(ccp(m_pBoard->getContentSize().width/2,m_pBoard->getContentSize().height/2));
	m_pObject->addChild(m_pObjectItem,0,0);
	//
	_setObjectVisible(false);
}
void DTAwardBoard::_initNum(){
	//num bg
	m_pNum_BG->setZOrder(3);
	m_pNum_BG->setAnchorPoint(ccp(1.0f,0.0f));
	m_pNum_BG->setPosition(ccp(m_pBoard->getContentSize().width,0.0f));
	m_pBoard->addChild(m_pNum_BG);
	//num
	m_pNum->setZOrder(0);
	m_pNum->setAnchorPoint(ccp(1.0,0.0));
	m_pNum->setPosition(ccp(m_pBoard->getContentSize().width-3.0f,0.0f));
	m_pBoard->addChild(m_pNum,10);
	//
	_setNumVisible(false);
}

void DTAwardBoard::_initGray(){
	const CCSize& sz_board=m_pBoard->getContentSize();
	m_pGray=CCLayerColor::create(DTAB_GRAY_COLOR);
	m_pGray->setContentSize(sz_board);
	m_pGray->setPosition(CCPointZero);
	this->addChild(m_pGray,m_pBoard->getZOrder()+1);
	m_pGray->setVisible(false);
}

void DTAwardBoard::_setNum(unsigned int num){
	NFC_setLabelStringInt(m_pNum,num);
	_setNumVisible(num>1?true:false,num);
}
void DTAwardBoard::_setNumVisible(bool isvisible,int num){
	m_pNum_BG->setVisible(isvisible);
	m_pNum->setVisible(isvisible);
	if (isvisible)
	{
		char buff[64]={0};
		sprintf(buff,"%d",num);
		std::string str = buff;
		int len = str.length();
		len -= 3;
		if (len > 0)
		{
			m_pNum_BG->setScaleX(1.0f+big_ratio*len);
		}
		else if (len < 0)
		{
			m_pNum_BG->setScaleX(1.0f+small_ratio*len);
		}
		else
		{
			m_pNum_BG->setScaleX(1.0f);
		}
	}
}

void DTAwardBoard::_setObjectVisible(bool isvisible){
	m_pObject->setVisible(isvisible);
}

void DTAwardBoard::_changeBoard(int quality){
	//board
	string file=varConfig::getCardBGFilePath(quality);
	m_pBoard->setProperty("File",file);
	//Mask
	file=varConfig::getCardMaskFilePath(quality);
	m_pMask->setProperty("File",file);
}
void DTAwardBoard::_resetBoard(){
	//board
	string file=varConfig::getCardNormalBGFilePath();
	m_pBoard->setProperty("File",file);
	//Mask
	file=varConfig::getCardNormalMaskFilePath();
	m_pMask->setProperty("File",file);
}

void DTAwardBoard::_changeObject(int iconid){
	string file=NFC_getFileFromResourceID(iconid);
	assert(file.length()>0);
	CCSprite* nor=CCSprite::create();
	nor->setProperty("File",file);
	m_pObjectItem->setNormalImageAndRelocation(nor);
}


