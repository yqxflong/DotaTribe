//Name��PESEquipSubView-Ӣ�ۻ�װ
//Function����װ
//Written By����ǿ

#include "../include/PESEquipSubView.h"
#include "../include/PESEquipDataHandler.h"
#include "../include/NFControlsManager.h"
#include "../include/LoggerSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/CPublicVarReader.h"
#include "../include/UIViewDataManger.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/IWindow.h"
#include "../include/StrengthenWindow.h"
//
#include "../include/RoleEquipDataHandler.h"
#include "../include/RoleShapeDataManager.h"
#include "../include/RoleInfoDataHandler.h"
//
#include "../include/IDStringDataManager.h"
#include "../include/CMenuItemSprite.h"
//
#include "../include/PESWindow.h"
#include "../include/GuideSystem.h"
#include "../include/EquipTipsWindow.h"
#include "../include/HERoleInfoNode.h"
#include "../include/HEHeroPropertyNode.h"
#include "../include/HELinkNode.h"
#include "../include/DTEquipBoard.h"
#include "../include/CSprite.h"
#include "../include/RoleHeroSkinsDataHandler.h"
#include "../include/NetObjectTipsDataHandler.h"
#include "../include/WindowManager.h"
#include "../include/EquipStrengthenDataHandler.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;


/************************************************************************/
/*                         PESEquipSubView                              */
/************************************************************************/

PESEquipSubView::PESEquipSubView()
:m_pSkeletonNode(0)
,m_pTable(0)
,m_szCELL_ITEM(0,0)
,m_szCELL_TITLE(0,0)
,m_cpTableCurOffset(0,0)
,m_nCurHeroIdx(-1)
{
	m_vecList.clear();
	m_pBottomNode=NULL;
	m_pLinkNode=NULL;
}

bool PESEquipSubView::onLoad(){
	if(CCNode::init()){
		this->autorelease();
		setPosition(CCPointZero);
		_initLayout();
		return true;
	}
	return false;
}

void PESEquipSubView::_initLayout(){
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kHEROEQUIP,this);
	_mapBtn();
	_showHeroDetailNode();
	_mapTable();
}

//@����idxˢ�½����ӦӢ������
void PESEquipSubView::_refreshHeroByIdx(int idx){
	if (m_nCurHeroIdx==idx||!NFC_HasTeamHero(idx))
		return;
	EquipStrengthenDataHandler::get_instance2()->m_HeroIndex = idx;
	m_nCurHeroIdx=idx;
	_refreshData();
	_refreshBagEquip();
	_refreshLinkNode();
	_refreshEquipCount();
//begin:��Ҫ����Ӣ��indexˢ�µ�
	_refreshHeroNameAndStarLv(idx);
	_refreshHeroShape(idx);
	_refreshRoleEquip(idx);
	_refreshHeroDetailNodeInfo(idx);
//end
	if (m_pBottomNode)
	{
		m_pBottomNode->refreshAllProperty(m_nCurHeroIdx);
	}
}

void PESEquipSubView::_refreshData(){
	m_vecList.clear();
	//��������ȷ�����͹���
	BAGEQUIPDATAHANDLER->reorderEquipListForHeroEquip();
	std::vector<BagEquipData*>::iterator it=BAGEQUIPDATAHANDLER->m_vecList.begin();
	std::vector<BagEquipData*>::iterator it_end=BAGEQUIPDATAHANDLER->m_vecList.end();
	int lastQuality=-1;
	for (;it!=it_end;it++)
	{
		BagEquipData* bb=*it;
		//��һ������
		if (lastQuality==-1){
			//��װ��֮ǰ�Ӹ�����ռλ
			_EQUIPITEM_ item;
			lastQuality=bb->template_->quality_;
			item.starCount_=bb->template_->quality_+1;
			m_vecList.push_back(item);
			//�Ӹ����͵�һ��װ��
			_EQUIPITEM_ item2;
			item2.equipdata_=bb;
			m_vecList.push_back(item2);
			continue;
		}
		//֮�������
		if (lastQuality!=bb->template_->quality_){
			//��װ��֮ǰ�Ӹ�����ռλ
			_EQUIPITEM_ item;
			lastQuality=bb->template_->quality_;
			item.starCount_=bb->template_->quality_+1;
			m_vecList.push_back(item);
			//�Ӹ����͵�һ��װ��
			_EQUIPITEM_ item2;
			item2.equipdata_=bb;
			m_vecList.push_back(item2);
		}else{
			_EQUIPITEM_ item;
			item.equipdata_=bb;
			m_vecList.push_back(item);
		}
	}
}

void PESEquipSubView::_refreshBagEquip(){
	NFC_refreshTableView(m_pTable);	
}

void PESEquipSubView::_refreshEquipCount(){
	char tmp[128]="";
	sprintf(tmp,"%d/%d",BAGEQUIPDATAHANDLER->m_vecList.size(),BAGEQUIPDATAHANDLER->m_bagMaxCount);
	NFC_setLabelString(kEQUIPCOUNT,this,tmp);
}

void PESEquipSubView::_refreshHeroNameAndStarLv(int idx){
	int quality=NFC_GetTeamHero(idx)->getHeroQualiy();
	string name=NFC_GetTeamHero(idx)->getHeroName();
	//star
	CCardsStarProgress* cc=(CCardsStarProgress*)NFC_getNode(kSTAR,this);
	cc->SetCurcount(quality+1);
	//name
	NFC_setLabelString(kNAME,this,name);
}

//@ˢ��Ӣ����Ϣģ����Ϣ
void PESEquipSubView::_refreshHeroDetailNodeInfo(int tabidx){
	m_pBottomNode->refreshAllProperty(tabidx);
}

void PESEquipSubView::_mapBtn(){
	CMenuItemSprite* cc;
	//strengthen
	cc=(CMenuItemSprite*)NFC_getMenuItem(kBTN_STRENGTHEN_BTN,this);
	cc->setIDX(kBTN_STRENGTHEN_BTN);
	cc->setTarget(this,menu_selector(PESEquipSubView::On_Click_Streng_Event));
}

bool PESEquipSubView::onDestroy(){
	m_cpTableCurOffset=ccp(0,0);
	UIVIEWDATAMANAGER->clearData();
	m_pSkeletonNode->removeFromParentAndCleanup(true);
	m_pSkeletonNode=0;
	this->removeAllChildrenWithCleanup(true);
	this->removeFromParentAndCleanup(true);
	return true;
}

bool PESEquipSubView::onTick(){
	return true;
}

//@���ݴ����TabIdxˢ�¶�Ӧ��Ӣ��װ������
void PESEquipSubView::onChangeTabIndex(int idx){
	_refreshHeroByIdx(idx);
}

void PESEquipSubView::_refreshHeroShape(int idx){
	CCNode* node=this->getChildByTag(kHERO);
	if(m_pSkeletonNode) 
		m_pSkeletonNode->removeFromParentAndCleanup(true); 
	int shapeID=NFC_GetTeamHero(idx)->getHeroShapeID();
	assert(shapeID>=0);
	RoleShapeData *pData = RoleShapeDataManager::get_instance2()->GetRoleShapeById(shapeID);
	m_pSkeletonNode = CCSkeletonAnimation::createWithFile(pData->mShapeAnimationFileDaiJi,pData->mShapeAnimationImage); 
	if(m_pSkeletonNode) 
		m_pSkeletonNode->setAnimation("DaiJi", true); 
	m_pSkeletonNode->setAnchorPoint(node->getAnchorPoint());
	m_pSkeletonNode->setPosition(node->getPosition());
	this->addChild(m_pSkeletonNode,node->getZOrder());
}

  /**
     * cell height for a given table.
     *
     * @param table table to hold the instances of Class
     * @return cell size
     */
CCSize PESEquipSubView::tableCellSizeForIndex(CCTableView *table, unsigned int idx){
	const _EQUIPITEM_ &item=m_vecList[idx];
	if (item.starCount_!=-1)
		return m_szCELL_TITLE;
	else
		return m_szCELL_ITEM;
	
}
    /**
     * a cell instance at a given index
     *
     * @param idx index to search for a cell
     * @return cell found at idx
     */
CCTableViewCell* PESEquipSubView::tableCellAtIndex(CCTableView *table, unsigned int idx) {
	CCTableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
		_createTableCell(cell);
	}
	_setTableCell(idx,cell);

	return cell;
}
//
void PESEquipSubView::_createTableCell(cocos2d::extension::CCTableViewCell* cell){
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kHEROEQUIPCELL,cell);
	_mapCellBtn(cell);
}

void PESEquipSubView::_mapCellBtn(cocos2d::CCNode* cell){
	CMenuItemSprite* cc=(CMenuItemSprite*)NFC_getMenuItem(kCELLBTN,cell);
	cc->setTarget(this,menu_selector(PESEquipSubView::On_Cell_Click_Event));
}


void PESEquipSubView::_setTableCell(int idx,cocos2d::extension::CCTableViewCell* cell){
	_EQUIPITEM_ &item=m_vecList[idx];
	if (item.starCount_!=-1)
	{
		_cell_showTitle(cell);
		//���ñ���
		NFC_setCardsStarLevel(kCELL_TITLE_STAR,cell,item.starCount_);
	}else{
		if (item.equipdata_->template_->canUse_>0)
		{
			_cell_showEquip(cell);
			//����װ������
			_setCellEquip(item.equipdata_,cell);
			_setCellEquipType(item.equipdata_,cell);
			_setCellEquipName(item.equipdata_,cell);
			_setCellEquipMainProp(item.equipdata_,cell);
			_setCellEquipScore(item.equipdata_,cell);
			_setCellEquipScoreArrow(item.equipdata_,cell);
			_setCellEquipBtn(idx,item.equipdata_,cell);
		}else{
			_cell_showExpBall(cell);
			//���þ���������
			_setCellEquip(item.equipdata_,cell);
			_setCellEquipName(item.equipdata_,cell);
			_setCellExpBall_Descrip(item.equipdata_,cell);
		}
	}
}

void PESEquipSubView::_setCellEquip(BagEquipData* ed,cocos2d::CCNode* cell){
	DTEquipBoard* cc=(DTEquipBoard*)NFC_getNode(kCELLBOARD,cell);
	cc->SetEquip(kHETYPE_ELIST,ed,this);
}

void PESEquipSubView::_setCellEquipType(BagEquipData* ed,cocos2d::CCNode* cell){
	string type=IDSTRINGDATAMANAGER->GetIDStringByID(1,ed->template_->type_);
	NFC_setLabelString(kCELLTYPE,cell,type);
}

void PESEquipSubView::_setCellEquipName(BagEquipData* ed,cocos2d::CCNode* cell){
	//����װ������+���׼���
	if(ed->advanceLevel_>0){
		char tmp[128]="";
		string sys=SysLangDataManager::get_instance2()->GetSysLangById(761);
		sprintf(tmp,sys.c_str(),ed->template_->name_.c_str(),ed->advanceLevel_);
		NFC_setLabelString(kCELLEQUIPNAME,cell,tmp);
	}else{
		NFC_setLabelString(kCELLEQUIPNAME,cell,ed->template_->name_);
	}
}

void PESEquipSubView::_setCellEquipMainProp(BagEquipData* ed,cocos2d::CCNode* cell){
	char tmp[32]="";
	unsigned char mainID=ed->template_->baseAttrType_;
	if (mainID==kMINATTACK){//�������ǹ�����
		int minatt=ed->mainAttriValue;
		int maxatt=ed->mainAttriValueMax;
		sprintf(tmp,"%s: %d-%d",SysLangDataManager::get_instance2()->GetSysLangById(207).c_str(),minatt,maxatt);
		NFC_setLabelString(kCELLMAINPROP,cell,tmp);
	}else{
		int mainValue=ed->mainAttriValue;
		string str=NFC_getIDStringFromTag(3,mainID);
		sprintf(tmp,"%s: %d",str.c_str(),mainValue);
		NFC_setLabelString(kCELLMAINPROP,cell,tmp);
	}
}

//begin:for expball
void PESEquipSubView::_setCellExpBall_Descrip(BagEquipData* ed,cocos2d::CCNode* cell){
	NFC_setLabelString(kCELLMAINPROP,cell,ed->template_->description_);
}
//end

void PESEquipSubView::_setCellEquipScore(BagEquipData* ed,cocos2d::CCNode* cell){
	char tmp[32]="";
	string sys=SysLangDataManager::get_instance2()->GetSysLangById(41);
	sprintf(tmp,sys.c_str(),ed->equipScore_);
	NFC_setLabelString(kCELLEQUIPSCOREVALUE,cell,tmp);
}

void PESEquipSubView::_setCellEquipScoreArrow(BagEquipData* ed,cocos2d::CCNode* cell){
	int theEquipScore=ed->equipScore_;
	int roleEquipScore=0;
	IHeroSkinItem* hero=ROLEHEROSKINSDATAHANDLER->GetCurHeroSkinItem(m_nCurHeroIdx);
	RoleEquipDataHandler* equipManager=hero->getEquipManager();
	BagEquipData* rd=equipManager->getEquipByType(ed->template_->type_);
	if (rd)roleEquipScore=rd->equipScore_;		//���ûװ��ͬ����װ�����򱣳�0ս��
	NFC_showNode(kCELLSCOREARROW,cell,true);
	if (theEquipScore>roleEquipScore)
		//��ɫ��ͷ
		NFC_changeImageForCSprite(kCELLSCOREARROW,cell,0);
	else if(theEquipScore<roleEquipScore)
		//��ɫ��ͷ
		NFC_changeImageForCSprite(kCELLSCOREARROW,cell,1);
	else 
		//���ؼ�ͷ
		NFC_showNode(kCELLSCOREARROW,cell,false);
	//����ͷ����ս��ֵ
	CCNode* arrow=NFC_getNode(kCELLSCOREARROW,cell);
	CCNode* battle=NFC_getNode(kCELLEQUIPSCOREVALUE,cell);
	arrow->setPositionX(battle->getPositionX()+battle->getContentSize().width);
}

void PESEquipSubView::_setCellEquipBtn(int idx,BagEquipData* ed,cocos2d::CCNode* cell){
	CMenuItemSprite* cc=(CMenuItemSprite*)NFC_getMenuItem(kCELLBTN,cell);
	cc->setIDX(idx);
}

unsigned int PESEquipSubView::numberOfCellsInTableView(CCTableView *table) {
	int count=m_vecList.size();
	return count;
}

void PESEquipSubView::On_Click_Event(CCObject* pSender){
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int idx=cc->getIDX();
}

//װ����ť����¼�
void PESEquipSubView::On_Cell_Click_Event(cocos2d::CCObject* pSender){
	CMenuItemSprite* cc=(CMenuItemSprite*)pSender;
	int idx=cc->getIDX();
	_equipEquipment(idx);
}

void PESEquipSubView::On_Click_Streng_Event(cocos2d::CCObject* pSender)
{
	PESWindow* pWindow = (PESWindow*)WINDOWMANAGER->GetWindowByType(IWindow::_TYPED_WINDOW_PESWINDOW_);
	EquipStrengthenDataHandler::get_instance2()->m_HeroIndex = m_nCurHeroIdx;
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_STRENTHENWINDOW_,_to_event_param_(ESTREN_TAB1),_to_event_param_(pWindow->m_nBackWindowType));
	pWindow->m_nBackWindowType = -1;
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_PESWINDOW_);
	
	//========��������==========
	GUIDESYSTEM->Next();
}

//@װ��icon����ص�
void PESEquipSubView::CallBack_ClickEquip(int type,int equipID){
	if (type==kHETYPE_ROLE)
	{	
		std::string  strisequip = _to_event_param_(kTIPS_ROLEEQUIP);
		std::string  stridx = _to_event_param_(equipID);	
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_EQUIPTIPSWINDOW_,stridx,strisequip,_to_event_param_(m_nCurHeroIdx));
				
	}else if(type==kHETYPE_ELIST){
		BagEquipData* bb=BAGEQUIPDATAHANDLER->getEquipById(equipID);
		if (bb)
		{
			if(bb->template_->type_ == kEQUIP_TYPE_EXPBALL)
			{

				NETOBJECTTIPSDATAHANDLER->m_pObjectTips->name = bb->template_->name_;
				NETOBJECTTIPSDATAHANDLER->m_pObjectTips->level = bb->template_->level_;
				NETOBJECTTIPSDATAHANDLER->m_pObjectTips->price =  bb->template_->price_;
				NETOBJECTTIPSDATAHANDLER->m_pObjectTips->description = bb->template_->description_;
				NETOBJECTTIPSDATAHANDLER->m_pObjectTips->isSalebtn_ = true;
				NETOBJECTTIPSDATAHANDLER->m_pObjectTips->pEquip_ = bb;
				NETOBJECTTIPSDATAHANDLER->m_pObjectTips->objectId = bb->id_;
				EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_NETOBJECTTIPSWINDOW_);
				return;
			}

			if (bb->template_->canUse_>0)
			{
				std::string  strisequip = _to_event_param_(kTIPS_BAGEQUIP);
				std::string  stridx = _to_event_param_(equipID);	
				EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_EQUIPTIPSWINDOW_,stridx,strisequip);
			}
		}
	}

}

	/*
		ˢ������װ��
	*/
void PESEquipSubView::On_RefreshRoleEquip(){
	_refreshRoleEquip(m_nCurHeroIdx);
	//ˢ��װ���б�
	_refreshTableViewButRememberOldPos();
}

	/*
		ˢ��װ���б�
	*/
void PESEquipSubView::On_RefreshEquipList(){
	//��������
	_refreshData();
	//ˢ��װ���б�
	_refreshTableViewButRememberOldPos();
	//���linknode
	_refreshLinkNode();
	//ˢ��װ������
	_refreshEquipCount();
}

/*
	Tips�ص�װ��
*/
void PESEquipSubView::On_Tips_CallBack_Equip(int idx)
{
	equipEquipmentByID(idx,m_nCurHeroIdx);
}
/*
	Tips�ص�ж��
*/
void PESEquipSubView::On_Tips_CallBack_Disboard(int type)
{
	_request4leaveEquip(type);
}

//@װ��һ��װ��by InstanceID
void PESEquipSubView::equipEquipmentByID(int id,int heroIdx){
	BagEquipData* bb=BAGEQUIPDATAHANDLER->getEquipById(id);
	int etype=bb->template_->type_;
	assert(etype>=0&&etype<=7);//8��װ��
	NFC_GetHeroEquipManager(heroIdx)->ChangeEquip_Request(id,heroIdx);
}

	/*
		ƥ��װ���б�
	*/
void PESEquipSubView::_mapTable(){
	//׼��cell��С
	CCNode* node=this->getChildByTag(kTABLECELL);
	m_szCELL_ITEM=node->getContentSize();
	node=NFC_getNode(kTABLECELL_SUBTITLE,this);
	m_szCELL_TITLE=node->getContentSize();
	//����table
	m_pTable=(CCTableView*)this->getChildByTag(kTABLE);
	m_pTable->setDataSource(this);
	m_pTable->setDirection(cocos2d::extension::kCCScrollViewDirectionVertical);
	m_pTable->setTouchEnabled(true);
	m_pTable->setVerticalFillOrder(cocos2d::extension::kCCTableViewFillTopDown);
}

	/*
		ˢ�¿�װ������
	*/
void PESEquipSubView::_refreshLinkNode(){
	if (m_pLinkNode)
	{
		m_pLinkNode->removeFromParent();
		m_pLinkNode=NULL;
	}
	if (m_vecList.size()==0)
	{
		CCNode* node=NFC_getNode(kLINKNODE,this);
		m_pLinkNode=HELinkNode::create();
		m_pLinkNode->setPosition(node->getPosition());
		this->addChild(m_pLinkNode);
	}
}

	/*
		Cell ��ʾtitle
	*/
void PESEquipSubView::_cell_showTitle(cocos2d::CCNode* cell){
	//begin:hide all equip control
	for (int i=kCELLBG;i<=kCELLTYPE;i++)
	{
		NFC_showNode(i,cell,false);
	}
	//end
	//begin:show title
	NFC_showNode(kCELL_TITLE_BG,cell,true);
	NFC_showNode(kCELL_TITLE_STAR,cell,true);
	//end
}

	/*
		Cell ��ʾװ��
	*/
void PESEquipSubView::_cell_showEquip(cocos2d::CCNode* cell){
	//begin:hide title
	NFC_showNode(kCELL_TITLE_BG,cell,false);
	NFC_showNode(kCELL_TITLE_STAR,cell,false);
	//end
	//begin:show all equip control
	for (int i=kCELLBG;i<=kCELLTYPE;i++)
	{
		NFC_showNode(i,cell,true);
	}
	//end
}

	/*
		Cell ��ʾ������
	*/
void PESEquipSubView::_cell_showExpBall(cocos2d::CCNode* cell){
	_cell_showEquip(cell);
	//begin:hide control for expball
	NFC_showNode(kCELLEQUIPSCOREVALUE,cell,false);
	NFC_showNode(kCELLSCOREARROW,cell,false);
	NFC_showNode(kCELLTYPE,cell,false);
	NFC_showNode(kCELLBTN,cell,false);
	NFC_showNode(kCELLBTN_LABEL,cell,false);
	//end
}

	/*
		ˢ��װ���б����Ǽ�סԭ��λ��
	*/
void PESEquipSubView::_refreshTableViewButRememberOldPos(){
	//��¼Table��ǰλ��
	m_cpTableCurOffset=m_pTable->getContentOffset();	
	m_fTableCurHeight=m_pTable->getContentSize().height;
	//ˢ��Table
	NFC_refreshTableView(m_pTable);
	//�ָ�table֮ǰλ��
	float curHeight=m_pTable->getContentSize().height;
	m_cpTableCurOffset.y+=m_fTableCurHeight-curHeight;
	NFC_setOffsetForTableView(m_pTable,m_cpTableCurOffset);
}


//@װ��һ��װ��by Idx
void PESEquipSubView::_equipEquipment(int idx){
	assert(idx<(int)m_vecList.size());
	_EQUIPITEM_ &item=m_vecList[idx];
	BagEquipData* bb=item.equipdata_;//ȡ����idx��װ��
	equipEquipmentByID(bb->id_,m_nCurHeroIdx);
}

//@���������ж��װ��
void PESEquipSubView::_request4leaveEquip(int etype){
	assert(etype>=0&&etype<=7);//8��װ��
	std::map<int,RoleEquipData*>::iterator it=NFC_GetHeroEquipManager(m_nCurHeroIdx)->m_mapEquipList.find(etype);
	BagEquipData* bb=it->second->equipdata_;
	NFC_GetHeroEquipManager(m_nCurHeroIdx)->OffEquip_Request(bb->id_,m_nCurHeroIdx);
}

//@��������ÿ��װ��
//#kBOARD1-8����������װ��map��Ӧ
void PESEquipSubView::_refreshRoleEquip(int idx){
	for (int i=kBOARD_1;i<=kBOARD_8;i++)
	{
		DTEquipBoard* cc=(DTEquipBoard*)NFC_getNode(i,this);
		int idx_ep=i-kBOARD_1;
		map<int,RoleEquipData*>::iterator it=NFC_GetHeroEquipManager(idx)->m_mapEquipList.find(idx_ep);		//i from1
		RoleEquipData* rr=it->second;
		if (rr->hasEquip_)
			cc->SetEquip(kHETYPE_ROLE,rr->equipdata_,this);
		else
			cc->RemoveEquip();
	}
}

//��ʾӢ����ϸ��Ϣ
void PESEquipSubView::_showHeroDetailNode(){
	CCNode* bottomNode=NFC_getNode(kBOTTOM_NODE,this);
	m_pBottomNode=HEHeroPropertyNode::create();
	m_pBottomNode->setZOrder(bottomNode->getZOrder());
	m_pBottomNode->setPosition(bottomNode->getPosition());
	this->addChild(m_pBottomNode);
}

	/*
		�����ڵ�֪ͨ
	*/
void PESEquipSubView::EventWindowCallBack(int iEventType, std::list<std::string>& paramList){
	if (m_pBottomNode){
		m_pBottomNode->EventWindowCallBack(iEventType,paramList);
	}
}