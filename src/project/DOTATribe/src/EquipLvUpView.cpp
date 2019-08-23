//Name : EquipLvUpView
//Function：装备升级界面
//Written By : 方骏
//AnchorPoint:  (0,0) can not change

#include "../include/EquipLvUpView.h"
#include "../include/NFControlsManager.h"
#include "../include/NFAnimationController.h"
#include "../include/CPublicVarReader.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
//
#include "../include/GuideSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/UIViewDataManger.h"
#include "../include/StrengthenWindow.h"
#include "../include/RoleShapeDataManager.h"
//
#include "../include/EquipmentLvUpDataHandler.h"
#include "../include/RoleEquipDataHandler.h"
#include "../include/IDStringDataManager.h"
#include "../include/RoleInfoDataHandler.h"
//
#include "../include/CMenuItemSprite.h"
#include <string>
#include "../include/MessageBoxWindow.h"

#include "../include/MaskNode.h"
#include "../include/EngineSystem.h"

#include "../include/FAnimationButton.h"

//
#include "../include/CSprite.h"
#include "../include/CProgressInnerBar.h"
#include "../include/DTAwardBoard.h"
#include "../include/DTEquipBoard.h"
#include "../include/ShopInfoDataHandler.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

#define LvUp_EffectSound 72
#define EXPBALL 8

EquipLvUpView::EquipLvUpView(){
	m_pResultView = NULL;
	m_pTableView = NULL;

	m_pAnimationPlayNode = NULL;
	m_pAnimationFileData = NULL;
	m_pAnimationCallBack = NULL;
	m_pAnimation = NULL;
	m_pAnimationGrayLayer = NULL;

	m_iTickAnimationAction = 0;
	m_bInPlayingAnimation = false;
	m_pAnimationWhiteSp = NULL;

	m_pFrameAnimationNode = NULL;
	m_pArrow = NULL;
};


bool EquipLvUpView::onLoad(){
	if(CCNode::init()){
		this->autorelease();
		setPosition(CCPointZero);
		_initData();
		_initLayout();
		return true;
	}

	return false;
}
bool EquipLvUpView::onDestroy(){
	m_bInPlayingAnimation = false;
	m_iTickAnimationAction = 0;
	m_pAnimationWhiteSp = NULL;
	if(m_pArrow){ 
		m_pArrow->removeFromParentAndCleanup(true); 
		m_pArrow=NULL;
	}

	this->removeAllChildrenWithCleanup(true);
	this->removeFromParentAndCleanup(true);
	return true;
}

bool EquipLvUpView::onTick(){

	LvUpAnimationActionPart();

	if(m_pFrameAnimationNode)
		m_pFrameAnimationNode->Tick();

	return true;
}

void EquipLvUpView::EquipHasBeenSeleted(int equipID)
{
	EQUIPMENTLVUPDATAHANDLER->selectedEquipId =equipID;
	if (EQUIPMENTLVUPDATAHANDLER->selectedEquipId != -1&&EQUIPMENTLVUPDATAHANDLER->GetMainCard())
	{
		for (int i=udEXPBOARD;i<=udNOCOSTCARDHINT;i++)
		{
			CCNode* pNode = (CCNode*)this->getChildByTag(i);
			pNode->setVisible(true);
		}
		_mapAllBtn();
		_checkEquipID();
		Function_SetConstMoney();
		_checkCostCardEmpty();
	}
	else
	{
		for (int i=udEXPBOARD;i<=udDAIJIJIANTOUNODE;i++)
		{
			CCNode* pNode = (CCNode*)this->getChildByTag(i);
			pNode->setVisible(false);
		}

		for (int i=udBTNCHOOSE;i<=udBTNLVUPTITLE;i++)
		{
			CCNode* pNode = (CCNode*)this->getChildByTag(i);
			pNode->setVisible(true);
		}
		CCNode* pNode = (CCNode*)this->getChildByTag(udTABLEVIEW);
			pNode->setVisible(true);
	}

}

void EquipLvUpView::On_ClickEvent(cocos2d::CCObject* pSender){
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	if (cc->getIDX()==udBTNCHOOSE)
	{
		//新手引导
		GUIDESYSTEM->Next();
		_enterChooseCard();
	}else if(cc->getIDX()==udBTNBUY){
		_buyCost();
	}else if(cc->getIDX()==udBTNLVUP){
		//需要判定是否含有紫色卡牌，弹出确认使用卡牌框。
		if(EQUIPMENTLVUPDATAHANDLER->HasPurpleCard()||EQUIPMENTLVUPDATAHANDLER->HasOrangeCard())
		{
			std::string message = SysLangDataManager::get_instance2()->GetSysLangById(422);
			NFC_showMessageBox(kSELECTPURPLECARD,message);
		}
		else
		{
			_toLvUp();
			//~~~~新手引导~~~~
			GUIDESYSTEM->PauseGuide();
		}
	}
}

	/*
		检查素材卡是否为空
	*/
void EquipLvUpView::_checkCostCardEmpty(){
	if(EQUIPMENTLVUPDATAHANDLER->GetEquipCostCardList().size()==0){
		NFC_setEnabledForMenuItem(udBTNCHOOSE,this,false);
		NFC_showNode(udNOCOSTCARDHINT,this,true);
		NFC_showNode(udNOEXPBALLHINT,this,false);
		NFC_showNode(udDAIJIJIANTOUNODE,this,true);
	}
	else if (_checkExpBallEmpty())
	{
		NFC_setEnabledForMenuItem(udBTNCHOOSE,this,true);
		NFC_showNode(udNOCOSTCARDHINT,this,false);
		NFC_showNode(udNOEXPBALLHINT,this,true);
		NFC_showNode(udDAIJIJIANTOUNODE,this,false);
	}
	else
	{
		NFC_setEnabledForMenuItem(udBTNCHOOSE,this,true);
		NFC_showNode(udNOCOSTCARDHINT,this,false);
		NFC_showNode(udNOEXPBALLHINT,this,false);
		NFC_showNode(udDAIJIJIANTOUNODE,this,false);
	}
}

bool EquipLvUpView::_checkExpBallEmpty()
{
	if (EQUIPMENTLVUPDATAHANDLER->vecEquipCostCard.size() >0)
		return false;
	std::vector<EquipCardsStructure>cardlist =EQUIPMENTLVUPDATAHANDLER->GetEquipCostCardList();
	for (int i=0;i<cardlist.size();i++)
	{
		if (cardlist[i].data->template_->type_ == EXPBALL)
			return false;
	}
	return true;
}
void EquipLvUpView::_initData(){
	EQUIPMENTLVUPDATAHANDLER->checkCostList();
}

void EquipLvUpView::_initOldCostColor(){
	CCLabelTTF* cc=(CCLabelTTF*)this->getChildByTag(udCOSTNUM);
	m_oCostColor=cc->getColor();
}

//一键增加所有经验珠素材
void EquipLvUpView::_initAddMaterialLayer()
{
	CPriorityLayerColor* cc=(CPriorityLayerColor*)this->getChildByTag(udADDMATERIAL);
	cc->setDelegate(this);
	m_pOneKeyAddLayer = cc;
	//
	_setAddMaterialIconAndLabel();
}

//设置素材区的提示
void EquipLvUpView::_setAddMaterialIconAndLabel()
{
	if (!EQUIPMENTLVUPDATAHANDLER->vecEquipCostCard.size() >0)
	{
		std::vector<EquipCardsStructure> CardList = EQUIPMENTLVUPDATAHANDLER->GetEquipCostCardList();
		int count = 0;
		for(int i = 0; i < (int)CardList.size(); ++i)
		{
			EquipCardsStructure & ecs = CardList[i];
			if(ecs.data->template_->type_ == EXPBALL)
				count++;
		}
		if (count > 0)
			_showAddMaterial(true);
		else
			_showAddMaterial(false);
	}
	else
		_showAddMaterial(false);
};

void EquipLvUpView::_showAddMaterial(bool flag)
{
	CCNode* cc = this->getChildByTag(udADDICON);
	cc->setVisible(flag);
	cc = this->getChildByTag(udADDLABELTEXT);
	cc->setVisible(flag);
}

void EquipLvUpView::_initLayout(){
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kEQUIPLVUPVIEW,this);
	_initAddMaterialLayer();
	_initOldCostColor();
	_initProgressTimer();
	_initAnimationEffect();
	_setCellSize();
	_setTableView();
	_mapAllBtn();
	_checkEquipID();
	Function_SetConstMoney();
	_checkCostCardEmpty();
	_setGuidejiantou();
}
void EquipLvUpView::_initProgressTimer()
{
	((CCProgressTimer*)this->getChildByTag(udEXPBAR))->setType(kCCProgressTimerTypeBar);
	//    Setup for a bar starting from the left since the midpoint is 1 for the x
	((CCProgressTimer*)this->getChildByTag(udEXPBAR))->setMidpoint(ccp(0,0));
	//    Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
	((CCProgressTimer*)this->getChildByTag(udEXPBAR))->setBarChangeRate(ccp(1, 0));
}

void EquipLvUpView::_initAnimationEffect()
{
	//特效数据
	m_pAnimationPlayNode = cocos2d::CCSprite::create();
	MaskNode * effectNode = (MaskNode *)this->getChildByTag(udAnimationNode);
	effectNode->addChild(m_pAnimationPlayNode);
}

void EquipLvUpView::_setCellSize(){
	CCNode* node=(CCNode*)this->getChildByTag(udTABLEVIEWCELL);
	m_szCell=node->getContentSize();
}
void EquipLvUpView::_mapAllBtn(){
	for (int i=udBTNCHOOSE;i<=udBTNLVUP;i++)
		_mapBtn(i);
}
void EquipLvUpView::_mapBtn(int key){
	CCMenu* menu=(CCMenu*)this->getChildByTag(key);
	CMenuItemSprite* cc=(CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(key);
	cc->setTarget(this,menu_selector(EquipLvUpView::On_ClickEvent));
}
void EquipLvUpView::_setTableView(){
	m_pTableView=(CCTableView*)this->getChildByTag(udTABLEVIEW);
	m_pTableView->setDataSource(this);
	m_pTableView->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pTableView->setTouchEnabled(true);
	m_pTableView->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
	NFC_refreshTableView(m_pTableView);
}
void EquipLvUpView::_showEquip()
{
	int eid = EQUIPMENTLVUPDATAHANDLER->selectedEquipId;
	if(eid >= 0)//表示有装备
	{
		BagEquipData * bed = EQUIPMENTLVUPDATAHANDLER->GetMainCard();
		if(NULL == bed)
			return;

		//显示装备，挂载在替代节点上
		DTAwardBoard * dtab = (DTAwardBoard *)this->getChildByTag(udEQUIP);
		dtab->ChangeObject(bed->template_->quality_, bed->template_->iconId_, 1);
	}
}
	/*
		进入选取素材界面
	*/
void EquipLvUpView::_enterChooseCard(){
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_EQUIPSELECTCARDWINDOW_);
}

	/*
		设置主卡
	*/
void EquipLvUpView::_resetMainCard(int equipID){
	//显示要升级的装备
	_showEquip();
	//显示属性
	_refreshLeftInfo();
}

void EquipLvUpView::_setOldEquipInfo(BagEquipData* data)
{
	if (data)
	{
		m_OldEquipData.exp_ = data->exp_;
		m_OldEquipData.maxexp_ = data->maxexp_;
		m_OldEquipData.level_ = data->level_;
		m_OldEquipData.mainAttriValue = data->mainAttriValue;
		m_OldEquipData.mainAttriValueMax = data->mainAttriValueMax;
	}
}
	/*
		如果有装备ID
	*/
void EquipLvUpView::_checkEquipID(){
	int equipId = EQUIPMENTLVUPDATAHANDLER->selectedEquipId;//选中的物品ID
	if (0>equipId)
	{
		_showEquipInfo(false);
	}
	else
	{
		_resetMainCard(equipId);
		_setOldEquipInfo(EQUIPMENTLVUPDATAHANDLER->GetMainCard());
	}

}

//查看是否可以启用升级按钮
void EquipLvUpView::_checkLvBtnStatus(){
	bool condition1=EQUIPMENTLVUPDATAHANDLER->isMoneyEnough();
	bool condition2=EQUIPMENTLVUPDATAHANDLER->selectedEquipId>0;
	bool condition3=EQUIPMENTLVUPDATAHANDLER->vecEquipCostCard.size()>0;
	bool condition4 = false;
	BagEquipData * bed = EQUIPMENTLVUPDATAHANDLER->GetMainCard();
	if(bed && (bed->level_ < bed->levelMax_))
	{
		condition4 = true;
	}
	if(condition1&&condition2&&condition3&&condition4)
		_enableBtns(true);
	else
		_enableBtns(false);		
}

	/*
		隐藏装备信息
	*/
void EquipLvUpView::_showEquipInfo(bool isShow){
	NFC_showNode(udLVVALUE,this,isShow);
	NFC_showNode(udEXPBAR,this,isShow);

}

void EquipLvUpView::_refreshLeftInfo()
{
	int eid = EQUIPMENTLVUPDATAHANDLER->selectedEquipId;
	//此Id可以为背包中的，也可以为身上已装备的
	//先检查背包中,再检查身上的
	BagEquipData * bed = EQUIPMENTLVUPDATAHANDLER->GetMainCard();
	if(NULL == bed)
		return;
	char tmp[128];
	//等级
	sprintf(tmp, "%d/%d", bed->level_, bed->levelMax_);
	NFC_setLabelString(udLVVALUE,this,tmp);
	if(bed->level_ >= bed->levelMax_)
	{//设置红色
		FSData * dd = FONTSTYLEDATAMANAGER->getDataByID(5);
		NFC_setLabelColor(udLVVALUE, this, ccc3(dd->colorR_, dd->colorG_, dd->colorB_));
	}
	else
	{//设置普通
		FSData * dd = FONTSTYLEDATAMANAGER->getDataByID(81);
		NFC_setLabelColor(udLVVALUE, this, ccc3(dd->colorR_, dd->colorG_, dd->colorB_));
	}

	//经验条
	_setExpBar(bed);

	//属性1
	//主属性
	unsigned char maintype = bed->template_->baseAttrType_;
	if(maintype == kMINATTACK)//攻击力
	{
		NFC_setLabelString(udATTRIBUTE,this,SysLangDataManager::get_instance2()->GetSysLangById(207).c_str());
	}
	else
	{
		string s = IDSTRINGDATAMANAGER->GetIDStringByID(3,maintype);
		NFC_setLabelString(udATTRIBUTE,this,s.c_str());
	}
	//主属性值
	if(maintype == kMINATTACK)//攻击力
	{
		string s = SysLangDataManager::get_instance2()->GetSysLangById(186);
		sprintf(tmp, "%d%s%d", bed->mainAttriValue, s.c_str(), bed->mainAttriValueMax);
		NFC_setLabelString(udATTRIBUTEVALUE,this,tmp);
	}
	else
	{
		sprintf(tmp, "%d", bed->mainAttriValue);
		NFC_setLabelString(udATTRIBUTEVALUE,this,tmp);

	}

}

void EquipLvUpView::_setExpBar(BagEquipData* bb){
	int curexp=bb->exp_;
	int maxexp=bb->maxexp_;

	float frontpos = (float)(100.0*curexp/maxexp);

	CCFiniteTimeAction*  action = CCSequence::create(
		CCProgressFromTo::create(0.5,frontpos,frontpos),NULL);
	(CCProgressTimer*)this->getChildByTag(udEXPBAR)->runAction(action);
}

	    /**
     * cell height for a given table.
     *
     * @param table table to hold the instances of Class
     * @return cell size
     */
CCSize EquipLvUpView::cellSizeForTable(CCTableView *table){
	return m_szCell;
};
    /**
     * a cell instance at a given index
     *
     * @param idx index to search for a cell
     * @return cell found at idx
     */
CCTableViewCell* EquipLvUpView::tableCellAtIndex(CCTableView *table, unsigned int idx){
	CCTableViewCell *cell = table->dequeueCell();
	if (!cell) {//相同的cell结构只会走一次
		cell = new CCTableViewCell();
		cell->autorelease();
		_createTableCell(cell);
	}
	_setTableCell(cell,idx);
	return cell;
};
    /**
     * Returns number of cells in a given table view.
     * 
     * @return number of cells
     */
unsigned int EquipLvUpView::numberOfCellsInTableView(CCTableView *table){
	int sz=EQUIPMENTLVUPDATAHANDLER->vecEquipCostCard.size();
	unsigned short count =sz / 2;
	unsigned short rest = sz % 2;
	if(rest > 0)++count;
	return count;

};

	/*
		Cell相关
	*/
void EquipLvUpView::_createTableCell(cocos2d::extension::CCTableViewCell* cell){
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kEQUIPLVUPVIEWCELL,cell);
}
void EquipLvUpView::_setTableCell(cocos2d::extension::CCTableViewCell* cell,int idx){
	int blockIdx=idx*2;
	_setBlockInfo(cell,blockIdx);
	blockIdx++;
	if (blockIdx >= (int)EQUIPMENTLVUPDATAHANDLER->vecEquipCostCard.size()){
		_showBlock2(cell,false);
	}else{
		_showBlock2(cell,true);
		_setBlockInfo(cell,blockIdx);
	}
}

void EquipLvUpView::_setBlockInfo(cocos2d::extension::CCTableViewCell* cell,int blockIdx){
	int rest = blockIdx % 2;
	BagEquipData* bb= BAGEQUIPDATAHANDLER->getEquipByAllEquips(EQUIPMENTLVUPDATAHANDLER->vecEquipCostCard[blockIdx]); 
	
	//equip
	DTEquipBoard* dd=(DTEquipBoard*)NFC_getNode(udOBJ1+rest,cell);
	dd->SetEquip(kHETYPE_ELIST,bb,NULL);

	//设置装备名字+进阶级别
	if(bb->advanceLevel_>0){
		char tmp[128]="";
		string sys=SysLangDataManager::get_instance2()->GetSysLangById(761);
		sprintf(tmp,sys.c_str(),bb->template_->name_.c_str(),bb->advanceLevel_);
		NFC_setLabelString(udNAME1 + rest,cell,tmp);
	}else{
		NFC_setLabelString(udNAME1 + rest,cell,bb->template_->name_);
	}

	//star
	NFC_setCardsStarLevel(udSTAR1+rest,cell,bb->template_->quality_+1);

	//Type
	std::string type = IDStringDataManager::get_instance2()->GetIDStringByID(1, bb->template_->type_);
	NFC_setLabelString(udTYPE1 + rest,cell,type.c_str());
}


void EquipLvUpView::_showBlock2(cocos2d::CCNode* cell,bool isShow){
	for (int i=udBG2;i<=udTYPE2;i+=2)
		NFC_showNode(i,cell,isShow);
}

	/*
		禁用button
	*/
void EquipLvUpView::_enableBtns(bool enabled){
	NFC_setEnabledForMenuItem(udBTNLVUP,this,enabled);
}

void EquipLvUpView::Function_SetConstMoney()
{
	//检查花费
	_setCost();
	//检查花费颜色
	_checkCostColor();
	//检查是否可升级
	_checkLvBtnStatus();
}
//刷新右边信息
void EquipLvUpView::_refreshRightInfo(){
	//刷新材料界面
	NFC_refreshTableView(m_pTableView);
	//检查升级按钮状态
	_checkLvBtnStatus();
	//刷新金钱
	Function_SetConstMoney();	
	//检查素材是否为空
	_checkCostCardEmpty();
	//检测是否可以一键添加
	_setAddMaterialIconAndLabel();
}
//服务器返回升级结果回调
void EquipLvUpView::Function_ShowResultView()
{
	LOGGERSYSTEM->LogInfo("EquipLvUpView::Function_ShowResultView --- begin\n");
	
	//创建播放特效遮罩层
	_createGrayLayer();

	MaskNode * node = (MaskNode *)this->getChildByTag(udAnimationNode);
	m_pAnimationWhiteSp = CCSprite::create(node->GetViewData().filepath_);
	m_pAnimationWhiteSp->setOpacity((GLubyte)0.0f);
	m_pAnimationWhiteSp->setScale(2.0f);
	//node->addChild(m_pAnimationWhiteSp, 0, 1);

	m_pFrameAnimationNode = FrameAnimationNode::create(11, 12, DOTATribeApp::get_instance2()->GetFPS());
	m_pFrameAnimationNode->setPosition(node->getPosition());
	m_pFrameAnimationNode->addChild(m_pAnimationWhiteSp);
	this->addChild(m_pFrameAnimationNode, 10);
	
	m_pFrameAnimationNode->AddDelegate(this);
	m_pFrameAnimationNode->InsertFrameIntercept(0);
	m_pFrameAnimationNode->InsertFrameIntercept(3);
	m_pFrameAnimationNode->InsertFrameIntercept(4);
	m_pFrameAnimationNode->InsertFrameIntercept(5);
	m_pFrameAnimationNode->InsertFrameIntercept(6);
	m_pFrameAnimationNode->InsertFrameIntercept(11);

	m_pFrameAnimationNode->Start();

	m_bInPlayingAnimation = true;

	LOGGERSYSTEM->LogInfo("EquipLvUpView::Function_ShowResultView --- end\n");
}
//升级操作
void EquipLvUpView::_toLvUp()
{
	//show DT隔绝层
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_DTTIMEDGRAYWINDOW_);

	//检查装备等级条件
	if (!EQUIPMENTLVUPDATAHANDLER->IsMainCardMeetLevelCondition()){
		NFC_showErrorTips(SysLangDataManager::get_instance2()->GetSysLangById(6));
		return;
	}
	//在此处备份当前选择的装备的数据
	int eid = EQUIPMENTLVUPDATAHANDLER->selectedEquipId;
	BagEquipData * bed = EQUIPMENTLVUPDATAHANDLER->GetMainCard();
	if(NULL == bed)
		return;
	BagEquipData * store= &(EQUIPMENTLVUPDATAHANDLER->selectEquip_StoreOnly);
	EQUIPMENTLVUPDATAHANDLER->CopyStore(store, bed);//升级前数据备份
	EQUIPMENTLVUPDATAHANDLER->toServerLvUp();
	_checkLvBtnStatus();

}
void EquipLvUpView::Function_ConfirmLvUp()
{
	_toLvUp();
}
void EquipLvUpView::PlayEffect()
{
	LOGGERSYSTEM->LogInfo("EquipLvUpView::PlayEffect --- begin\n");

	MaskNode * effectNode = (MaskNode *)this->getChildByTag(udAnimationNode);
	int effectId = effectNode->GetViewData().colorR_;
	if(effectId <= 0)
		return;
	m_pAnimationFileData = AnimationFileDataManager::get_instance2()->GetAnimationByIdx(effectId);

	m_pAnimation = EngineSystem::get_instance2()->GetAnimtionByName(m_pAnimationFileData->mAnimationName);

	m_pAnimationPlayNode->setDisplayFrameWithAnimationName(m_pAnimationFileData->mAnimationName, 0);
	m_pAnimationPlayNode->setScale(m_pAnimationFileData->mAnimationScale);
	m_pAnimationPlayNode->setVisible(false);

	if(m_pAnimation)
	{
		CCAnimationEffect * pAnimationEffect = CCAnimationEffect::create(m_pAnimationPlayNode,m_pAnimation, this);
		if(pAnimationEffect)
		{
			m_pAnimationPlayNode->setVisible(true);
			m_pAnimationPlayNode->runAction(pAnimationEffect);
		}
	}

	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOUND_PLAY_,_to_event_param_(m_pAnimationFileData->mAnimationUISoundID));

	LOGGERSYSTEM->LogInfo("EquipLvUpView::PlayEffect --- end\n");
}
void EquipLvUpView::_createGrayLayer()
{
	m_pAnimationGrayLayer = CPriorityLayerColor::create(ccc4(0,0,0,0),3000,2000,kPRIORITYLOW2);
	m_pAnimationGrayLayer->setAnchorPoint(ccp(0,0));
	m_pAnimationGrayLayer->setPosition(ccp(0,0));
	this->addChild(m_pAnimationGrayLayer,10);
}
void EquipLvUpView::_removeGrayLayer()
{
	if(m_pAnimationGrayLayer)
		m_pAnimationGrayLayer->removeFromParentAndCleanup(true);
	m_pAnimationGrayLayer = NULL;
}
void EquipLvUpView::touchEvent(CPriorityLayerColor* pLayerColor)
{
	if (pLayerColor == m_pAnimationGrayLayer)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOUND_STOP_,_to_event_param_(LvUp_EffectSound));
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOUND_PLAY_,_to_event_param_(LvUp_EffectSound)); 
		//属性
		BagEquipData * bed = EQUIPMENTLVUPDATAHANDLER->GetMainCard();
		if(!bed)
			return;

		char tmp[128];
		//等级
		m_OldEquipData.level_ += ProgressRunTimes;
		sprintf(tmp, "%d/%d",m_OldEquipData.level_, bed->levelMax_);
		NFC_setLabelString(udLVVALUE,this,tmp);
		if(m_OldEquipData.level_ >= bed->levelMax_)
		{//设置红色
			FSData * dd = FONTSTYLEDATAMANAGER->getDataByID(5);
			NFC_setLabelColor(udLVVALUE, this, ccc3(dd->colorR_, dd->colorG_, dd->colorB_));
		}
		else
		{//设置普通
			FSData * dd = FONTSTYLEDATAMANAGER->getDataByID(81);
			NFC_setLabelColor(udLVVALUE, this, ccc3(dd->colorR_, dd->colorG_, dd->colorB_));
		}

		unsigned char maintype = bed->template_->baseAttrType_;

		EquipmentLvUpData * dd = EQUIPMENTLVUPDATAHANDLER->equipLvUpData;
		//主属性值
		if(maintype == kMINATTACK)//攻击力
		{
			string s = SysLangDataManager::get_instance2()->GetSysLangById(186);
			m_OldEquipData.mainAttriValue += dd->changeValue*ProgressRunTimes;
			m_OldEquipData.mainAttriValueMax +=dd->changeValueMax*ProgressRunTimes;
			sprintf(tmp, "%d%s%d", m_OldEquipData.mainAttriValue, s.c_str(),m_OldEquipData.mainAttriValueMax);
			NFC_setLabelString(udATTRIBUTEVALUE,this,tmp);
		}
		else
		{
			m_OldEquipData.mainAttriValue +=dd->changeValue*ProgressRunTimes;
			sprintf(tmp, "%d", m_OldEquipData.mainAttriValue);
			NFC_setLabelString(udATTRIBUTEVALUE,this,tmp);

		}
		this->getChildByTag(udEXPBAR)->stopAllActions();
		ProgressArray = cocos2d::CCArray::create();
		float posend = (float)(100.0*bed->exp_/bed->maxexp_);
		CCFiniteTimeAction*  action = CCSequence::create(CCProgressFromTo::create(0.3f,0,posend),
			CCCallFunc::create(this, callfunc_selector(EquipLvUpView::CallbackBtnEnable)), 
			NULL);
		ProgressArray->addObject(action);
		(CCProgressTimer*)this->getChildByTag(udEXPBAR)->runAction(CCSequence::create(ProgressArray));
		_removeGrayLayer();
	}
	else if(pLayerColor == m_pOneKeyAddLayer)
	{
		if (!EQUIPMENTLVUPDATAHANDLER->vecEquipCostCard.size() >0)
		{
			//清空选择的卡片
			EQUIPMENTLVUPDATAHANDLER->needMoneyAll=0;
			EQUIPMENTLVUPDATAHANDLER->vecEquipCostCard.clear();
			//获得素材列表
			std::vector<EquipCardsStructure> CardList = EQUIPMENTLVUPDATAHANDLER->GetEquipCostCardList();
			//单独取出素材列表中的经验珠
			std::vector<EquipCardsStructure> ExpBallCardList;
			ExpBallCardList.clear();
			for(int i = 0; i < (int)CardList.size(); ++i){
				if (CardList[i].data->template_->type_ == EXPBALL){
					ExpBallCardList.push_back(CardList[i]);
				}
			}
			//排序，templateid小的在前
			for(int i = 0; i < ExpBallCardList.size(); ++i){
				for(int j = i; j < ExpBallCardList.size(); ++j){
					if( ExpBallCardList[i].data->template_->templateid_ > ExpBallCardList[j].data->template_->templateid_ ){
						EquipCardsStructure tmp;
						tmp = ExpBallCardList[i];
						ExpBallCardList[i] = ExpBallCardList[j];
						ExpBallCardList[j] = tmp;
					}
				}
			}
			//将结果添加到Datahandler中
			for(int i = 0; i < (int)ExpBallCardList.size(); ++i){
				if( EQUIPMENTLVUPDATAHANDLER->vecEquipCostCard.size() < 20){
					ExpBallCardList[i].isSelected = true;
					EQUIPMENTLVUPDATAHANDLER->vecEquipCostCard.push_back(ExpBallCardList[i].data->id_);
				}
			}

			//此处需要和服务器通讯计算金钱等
			EQUIPMENTLVUPDATAHANDLER->toServerSelectCard();	
			_setCellSize();
			_setTableView();
			_showAddMaterial(false);

			//新手引导
			GUIDESYSTEM->Next();
		}
	}
}
//特效播放结束回调
void  EquipLvUpView::EffectCallBackEventHandler(int eventType,cocos2d::CCNode * animationNode,PCallBack_Node ptr)
{
	LOGGERSYSTEM->LogInfo("EquipLvUpView::EffectCallBackEventHandler --- begin\n");
	m_pAnimationPlayNode->setVisible(false);
	//设置经验条动画
	_setProgress();
	m_pAnimationGrayLayer->setDelegate(this);
	LOGGERSYSTEM->LogInfo("EquipLvUpView::EffectCallBackEventHandler --- end\n");
}
void EquipLvUpView::_setProgress()
{
	BagEquipData * bed = EQUIPMENTLVUPDATAHANDLER->GetMainCard();

	int times = bed->level_ - m_OldEquipData.level_;
	CCLOG("===================================EquitView Level Up %d===================================",times);
	if (times == 0)
	{
		//没有升级
		float frontpos = (float)(100.0*m_OldEquipData.exp_/m_OldEquipData.maxexp_);
		float behindpos =(float)(100.0*bed->exp_/m_OldEquipData.maxexp_);
		CCFiniteTimeAction*  action = CCSequence::create(
			CCProgressFromTo::create(0.3f,frontpos,behindpos),
			CCCallFunc::create(this, callfunc_selector(EquipLvUpView::CallbackBtnEnable)), 
			NULL);
		(CCProgressTimer*)this->getChildByTag(udEXPBAR)->runAction(action);

		ProgressRunTimes = 0;
		//m_ViewHeroCurExp = AltarlaterExp;
	}
	else
	{

		//升满当前级别
		cocos2d::CCArray* arr = cocos2d::CCArray::create();
		float frontpos = (float)(100.0*m_OldEquipData.exp_/m_OldEquipData.maxexp_);
		CCFiniteTimeAction*  action = CCSequence::create(
			CCProgressFromTo::create(0.3f,frontpos,100), 
			CCCallFunc::create(this, callfunc_selector(EquipLvUpView::CallbackTTF)), 
			NULL);
		arr->addObject(action);

		int i =1;
		for (i;i<times;i++)
		{
			CCFiniteTimeAction*  action1 = CCSequence::create(
				CCProgressFromTo::create(0.3f,0,100), 
				CCCallFunc::create(this, callfunc_selector(EquipLvUpView::CallbackTTF)), 
				NULL);
			arr->addObject(action1);
		}

		//升级之后的进度条
		float posend = (float)(100.0*bed->exp_/bed->maxexp_);
		CCFiniteTimeAction*  action2 = CCSequence::create(
			CCProgressFromTo::create(0.3f,0,posend), 
			CCCallFunc::create(this, callfunc_selector(EquipLvUpView::CallbackBtnEnable)), 
			NULL);
		arr->addObject(action2);
		ProgressRunTimes = times;
		(CCProgressTimer*)this->getChildByTag(udEXPBAR)->runAction(CCSequence::create(arr));
	}
}
void EquipLvUpView::CallbackBtnEnable()
{
	_setOldEquipInfo(EQUIPMENTLVUPDATAHANDLER->GetMainCard());
	_removeGrayLayer();
	//========新手引导=========
	GUIDESYSTEM->RestoreGuide();
}
void EquipLvUpView::CallbackTTF()
{
	ProgressRunTimes--;
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOUND_STOP_,_to_event_param_(LvUp_EffectSound));
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOUND_PLAY_,_to_event_param_(LvUp_EffectSound)); 
	//属性
	BagEquipData * bed = EQUIPMENTLVUPDATAHANDLER->GetMainCard();
	if(!bed)
		return;

	char tmp[128];
	//等级
	m_OldEquipData.level_++;
	sprintf(tmp, "%d/%d",m_OldEquipData.level_, bed->levelMax_);
	NFC_setLabelString(udLVVALUE,this,tmp);
	if(m_OldEquipData.level_ >= bed->levelMax_)
	{//设置红色
		FSData * dd = FONTSTYLEDATAMANAGER->getDataByID(5);
		NFC_setLabelColor(udLVVALUE, this, ccc3(dd->colorR_, dd->colorG_, dd->colorB_));
	}
	else
	{//设置普通
		FSData * dd = FONTSTYLEDATAMANAGER->getDataByID(81);
		NFC_setLabelColor(udLVVALUE, this, ccc3(dd->colorR_, dd->colorG_, dd->colorB_));
	}

	unsigned char maintype = bed->template_->baseAttrType_;

	EquipmentLvUpData * dd = EQUIPMENTLVUPDATAHANDLER->equipLvUpData;
	//主属性值
	if(maintype == kMINATTACK)//攻击力
	{
		string s = SysLangDataManager::get_instance2()->GetSysLangById(186);
		m_OldEquipData.mainAttriValue += dd->changeValue;
		m_OldEquipData.mainAttriValueMax +=dd->changeValueMax;
		sprintf(tmp, "%d%s%d", m_OldEquipData.mainAttriValue, s.c_str(),m_OldEquipData.mainAttriValueMax);
		NFC_setLabelString(udATTRIBUTEVALUE,this,tmp);
	}
	else
	{
		 m_OldEquipData.mainAttriValue +=dd->changeValue;
		sprintf(tmp, "%d", m_OldEquipData.mainAttriValue);
		NFC_setLabelString(udATTRIBUTEVALUE,this,tmp);

	}
}

//引导购买箭头

void EquipLvUpView::_setGuidejiantou()
{
	//新手引导则返回
	if (GUIDESYSTEM->isRunning())
		return;
	//
	if(m_pArrow){ 
		m_pArrow->removeFromParentAndCleanup(true); 
	}
	m_pArrow = CCSkeletonAnimation::createWithFile(SPINE_GUIDE_ARROW_JSON,SPINE_GUIDE_ARROW_ALTAS);
	if(m_pArrow) 
		m_pArrow->setAnimation(SPINE_GUIDE_ARROW_DAIJI,true);
	MaskNode* node = (MaskNode*)NFC_getNode(udDAIJIJIANTOUNODE,this);
	node->addChild(m_pArrow,10);
}

//购买素材
void EquipLvUpView::_buyCost(){
	string param1=_to_event_param_(0);
	string param2=_to_event_param_(_TYPED_EVENT_SHOW_STRENTHENWINDOW_);
	if (ROLEINFODATAHANDLER->m_pRIData->level_ <= 29)
	{
		SHOPINFODATAHANDLER->m_iShowArrow = true;
	}
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_MARKETPWINDOW_,param1,param2);
}
//检查金钱颜色
void EquipLvUpView::_checkCostColor(){
	if (!EQUIPMENTLVUPDATAHANDLER->isMoneyEnough())
		NFC_setLabelColor(udCOSTNUM,this,ccRED);
	else
		NFC_setLabelColor(udCOSTNUM,this,m_oCostColor);
}
//设置花费金钱
void EquipLvUpView::_setCost(){
	if (EQUIPMENTLVUPDATAHANDLER->needMoneyAll>0){
		char tmp[128];
		sprintf(tmp, "%d", EQUIPMENTLVUPDATAHANDLER->needMoneyAll);
		NFC_setLabelString(udCOSTNUM,this,tmp);
	}else{
		NFC_setLabelString(udCOSTNUM,this,"");
	}
}

void EquipLvUpView::EventWindowCallBack(int iEventType, std::list<std::string>& paramList)
{
	if(iEventType == _TEPED_EVENT_EQUIPLVUP_GET_COSTMONEY_)
	{
		Function_SetConstMoney();
	}
	else if(iEventType == _TEPED_EVENT_EQUIPLVUP_GET_LVUPRESULT_)
	{
		Function_ShowResultView();
	}
	else if(iEventType == _TYPED_EVENT_CONFIRMUSE_CONTAINPURPLECARD_)
	{
		Function_ConfirmLvUp();
	}else if(iEventType==_TEPED_EVENT_EQUIPLVUP_AFTER_CHOOSECOST_){
		if (m_pTableView)
			NFC_refreshTableView(m_pTableView);
		_checkCostCardEmpty();
		_setAddMaterialIconAndLabel();
		_setGuidejiantou();
		_refreshRightInfo();
	}
}

void EquipLvUpView::LvUpAnimationActionPart()
{
	if(m_bInPlayingAnimation)
	{
		m_iTickAnimationAction++;
		if(m_iTickAnimationAction <= 2.5 * 3)
		{//0-30(100/255)
			float dur = 0.30f * 255 / (3 * 2.5f);
			m_pAnimationWhiteSp->setOpacity(m_pAnimationWhiteSp->getOpacity() + dur);
		}
		else if(m_iTickAnimationAction <= 2.5 * 4)
		{//30-75
			float dur = 0.45f * 255 / (1 * 2.5f);
			m_pAnimationWhiteSp->setOpacity(m_pAnimationWhiteSp->getOpacity() + dur);
		}
		else if(m_iTickAnimationAction <= 2.5 * 6)
		{//75-30
			float dur = 0.45f * 255 / (2 * 2.5f);
			m_pAnimationWhiteSp->setOpacity(m_pAnimationWhiteSp->getOpacity() - dur);
		}
		else if(m_iTickAnimationAction <= 2.5 * 11)
		{//30-0
			float dur = 0.30 * 255 / (5 * 2.5f);
			m_pAnimationWhiteSp->setOpacity(m_pAnimationWhiteSp->getOpacity() - dur);
		}
		else
		{
			m_bInPlayingAnimation = false;
			m_iTickAnimationAction = 0;

			m_pAnimationWhiteSp->removeFromParentAndCleanup(true);
			m_pAnimationWhiteSp = NULL;

		}
	}
}


void EquipLvUpView::FrameAnimationIntercept(int frameId, cocos2d::CCNode * node)
{
	if(frameId == 0)
	{
		PlayEffect();
	}
	else if(frameId == 5)
	{
		_refreshRightInfo();//这句一定要在后面写
	}
}