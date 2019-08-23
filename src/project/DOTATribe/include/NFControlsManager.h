//Name：NFControlsManager
//Function：管理控件的一些操作
//Written By：尹强

#ifndef  _DOTATRIBE_NFControlsManager_H_
#define  _DOTATRIBE_NFControlsManager_H_

#include <cocos2d.h>
#include <cocos-ext.h>
#include <iostream>
#include "../include/DOTATribeApp.h"
#include "../include/CSprite.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/FontStyleDataManager.h"
#include "../include/CCardsStarProgress.h"
#include "../include/LoggerSystem.h"
#include "../include/ClientConstDataManager.h"
#include "../include/CPublicVarReader.h"
#include "../include/CCornerNumIcon.h"
#include "../include/ResourceIDDataManager.h"
#include "../include/IDStringDataManager.h"
#include "../include/CMenuItemSprite.h"
#include "../include/CTableView.h"
#include "../include/ArtFontDataManager.h"
#include "../include/ArtFontLabelBatchNode.h"
#include "../include/CProgressInnerBar.h"
#include "../include/CCGrapSprite.h"
#include "../include/EngineSystem.h"
#include "../include/AnimationEffect.h"
#include "../include/AnimationFileDataManager.h"
#include "../include/MessageBoxWindow.h"
#include "../include/CAnimationSprite.h"
#include "../include/GradualColorAction.h"
#include "../include/CProgressInnerBar.h"
#include "../include/CCardsStarProgress.h"
#include "../include/SceneEffect.h"
#include "../include/CSimpleActionSprite.h"
#include "../include/CTouchSprite.h"
#include "../include/CTimeLabel.h"
#include "../include/DTAwardBoard.h"
#include "../include/DTHeroIcon.h"
#include "../include/RoleHeroSkinsDataHandler.h"
#include "../include/RoleEquipDataHandler.h"
#include "../include/RoleSkillsDataHandler.h"


using namespace cocos2d;

/****
	quit game
	#May be rejected by appstore
**/
static void NFC_quitGame(){
	LOGGERSYSTEM->LogInfo("==You have Exit the Game By your operation!!==");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	cocos2d::CCDirector::sharedDirector()->getSystem()->onAndroidAppExit();
#else
	DOTATribeApp::get_instance2()->onAppExit();
	exit(0);
#endif
}

/****
	SoundPlay
**/
static void NFC_playSoundByID(int soundid){
	if (soundid<0)
		 soundid=ClientConstDataManager::get_instance2()->getValueByKey(CONST_KEY_SOUND_COMMON_OPEN);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SOUND_PLAY_,_to_event_param_(soundid));
}

/****
	ErrorTips
**/
static void NFC_showErrorTips(){
	EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_ERRORTIPSWINDOW_);
}

static void NFC_showErrorTips(std::string text){
	EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_ERRORTIPSWINDOW_,text);
}

static void NFC_showErrorTips_2(std::string text){
	EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_ERRORTIPSWINDOW_,text);
}

/****
	Communication Waitting
**/
static void NFC_showCommunicationWating(bool isshow){
	if (isshow)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_COMMUNICATIONWAITTINGWIN_);
	}else{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_COMMUNICATIONWAITTINGWIN_);
	}
}

static void NFC_showCommunicationWating_2(bool isshow){
	if (isshow)
	{
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_SHOW_COMMUNICATIONWAITTINGWIN_);
	}else{
		EVENTSYSTEM->PushEvent2(_TYPED_EVENT_HIDE_COMMUNICATIONWAITTINGWIN_);
	}
}

/****
	MessageBox
**/
static void NFC_showMessageBox(int type,std::string text){
	std::string str=_to_event_param_(type);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_MESSAGEBOXWINDOW_,str,"",text);
}

/*
	弹出message
	参数：内容，确认事件，取消事件
*/
static void NFC_showMessageBox(std::string text, int confirmEvent, int cancelEvent = -1)
{
	std::string str = _to_event_param_(kAUTOMESSAGEBOX);
	std::string confirmEvent_ = _to_event_param_(confirmEvent);
	std::string cancelEvent_ = _to_event_param_(cancelEvent);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_MESSAGEBOXWINDOW_,str,"",text, confirmEvent_, cancelEvent_);
}

/****
	ResourceID
**/
static std::string NFC_getFileFromResourceID(int iconID){
	return ResourceIDDataManager::get_instance2()->getDataByID(iconID);
}

/****
	IDString
**/
static std::string NFC_getIDStringFromTag(int tag,int subTag){
	return IDSTRINGDATAMANAGER->GetIDStringByID(tag,subTag);
}

/****
	Client Const
**/
static int NFC_getValueFromClientConst(std::string key){
	int vv=ClientConstDataManager::get_instance2()->getValueByKey(key.c_str());
	return vv;
}

/************************************************************************/
/* 显示单独按钮的messagebox                                                                     */
/************************************************************************/
static void NFC_showMessageBoxSingle(int type, std::string text)
{
	std::string str=_to_event_param_(type);
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_MESSAGEBOXWINDOW_1_,str,"",text);
}


/*
Normal MessageBox
*/
static void NFC_showNormalMsgBySYID(int resourceID)
{
	std::string  content=SysLangDataManager::get_instance2()->GetSysLangById(resourceID);
	if(!content.empty())
		NFC_showMessageBoxSingle(kDEFAULT,content.c_str());
}

/****
	Node
**/
static cocos2d::CCNode* NFC_getNode(int key,cocos2d::CCNode* root){
	cocos2d::CCNode* node=root->getChildByTag(key);
	return node;
}

static void NFC_showNode(int key,cocos2d::CCNode* root,bool isShow){
	cocos2d::CCNode* node=root->getChildByTag(key);
	node->setVisible(isShow);
}

static void NFC_setScale(int key,cocos2d::CCNode* root,float scale){
	cocos2d::CCNode* node=root->getChildByTag(key);
	node->setScale(scale);
}

/****
	CCardsStarProgress
**/
static void NFC_setCardsStarLevel(int key,cocos2d::CCNode* root,int count){
	cocos2d::CCNode* node=root->getChildByTag(key);
	CCardsStarProgress* cc=dynamic_cast<CCardsStarProgress*>(node);
	assert(cc!=NULL);
	cc->SetCurcount(count);
}

static void NFC_setCardsStarAdvance(int key,cocos2d::CCNode* root,int advanceCount){
	cocos2d::CCNode* node=root->getChildByTag(key);
	CCardsStarProgress* cc=dynamic_cast<CCardsStarProgress*>(node);
	assert(cc!=NULL);
	cc->SetCurcount(advanceCount,advanceCount);
}




/****
	CCornerNumIcon
**/
static void NFC_setCornerNum(int key,cocos2d::CCNode* root,int count){
	cocos2d::CCNode* node=root->getChildByTag(key);
	CCornerNumIcon* cc=dynamic_cast<CCornerNumIcon*>(node);
	assert(cc!=NULL);
	cc->setNum(count);
}

/****
	Label
**/
static void NFC_setLabelString(int key,cocos2d::CCNode* root,std::string txt){
	cocos2d::CCNode* node=root->getChildByTag(key);
	cocos2d::CCLabelTTF* cc=dynamic_cast<cocos2d::CCLabelTTF*>(node);
	assert(cc!=NULL);
	cc->setString(txt.c_str());
}

static void NFC_setLabelString(int key,cocos2d::CCNode* root,std::string txt, bool visible){
	cocos2d::CCNode* node=root->getChildByTag(key);
	cocos2d::CCLabelTTF* cc=dynamic_cast<cocos2d::CCLabelTTF*>(node);
	assert(cc!=NULL);
	cc->setString(txt.c_str());
	node->setVisible(visible);
}

static void NFC_setLabelString(cocos2d::CCLabelTTF* cc,std::string txt){
	assert(cc!=NULL);
	cc->setString(txt.c_str());
}

static void NFC_setLabelString(int key,cocos2d::CCNode * root,int tID,bool visible)
{
	cocos2d::CCNode* node = root->getChildByTag(key);
	cocos2d::CCLabelTTF* cc=dynamic_cast<cocos2d::CCLabelTTF*>(node);
	assert(cc!=NULL);
	cc->setString(SysLangDataManager::get_instance2()->GetSysLangById(tID).c_str());
	node->setVisible(visible);
}

static void NFC_setLabelStringInt(int key,cocos2d::CCNode* root,int num){
	cocos2d::CCNode* node=root->getChildByTag(key);
	cocos2d::CCLabelTTF* cc=dynamic_cast<cocos2d::CCLabelTTF*>(node);
	assert(cc!=NULL);
	char tmp[64];
	sprintf(tmp,"%d",num);
	cc->setString(tmp);
}

static void NFC_setLabelStringInt(int key,cocos2d::CCNode* root,int num, bool visible){
	cocos2d::CCNode* node=root->getChildByTag(key);
	cocos2d::CCLabelTTF* cc=dynamic_cast<cocos2d::CCLabelTTF*>(node);
	assert(cc!=NULL);
	char tmp[64];
	sprintf(tmp,"%d",num);
	cc->setString(tmp);
	node->setVisible(visible);
}

static void NFC_setLabelStringInt(int key,cocos2d::CCNode* root,int num,int sysTxtID,bool visible){
	cocos2d::CCNode* node=root->getChildByTag(key);
	cocos2d::CCLabelTTF* cc=dynamic_cast<cocos2d::CCLabelTTF*>(node);
	std::string  sysLangTxt = SysLangDataManager::get_instance2()->GetSysLangById(sysTxtID);
	if(!sysLangTxt.empty())
	{
		char tmp[64]={0};
		sprintf(tmp,sysLangTxt.c_str(),num);
		cc->setString(tmp);
		node->setVisible(visible);
	} 
}





static void NFC_setLabelStringInt(cocos2d::CCLabelTTF* cc,int num){
	assert(cc!=NULL);
	char tmp[64];
	sprintf(tmp,"%d",num);
	cc->setString(tmp);
}

static void NFC_setLabelColor(int key,cocos2d::CCNode* root,const cocos2d::ccColor3B& color){
	cocos2d::CCNode* node=root->getChildByTag(key);
	cocos2d::CCLabelTTF* cc=dynamic_cast<cocos2d::CCLabelTTF*>(node);
	assert(cc!=NULL);
	cc->setColor(color);
}

static void NFC_setLabelColor(cocos2d::CCLabelTTF* root,const cocos2d::ccColor3B& color){
	cocos2d::CCLabelTTF* cc=root;
	assert(cc!=NULL);
	cc->setColor(color);
}

static void NFC_setLabelByFontStyleID(cocos2d::CCLabelTTF* cc,int fontstyleID){
	assert(cc!=NULL);
	FSData* dd=FONTSTYLEDATAMANAGER->getDataByID(fontstyleID);
	assert(dd!=NULL);
	cc->setFontName(dd->fontname_);
	cc->setFontSize(dd->fontsize_);
	cc->setColor(cocos2d::ccc3(dd->colorR_,dd->colorG_,dd->colorB_));
}


static  void NFC_setLabelByFontID(int uiIndex,cocos2d::CCNode * pRoot,int fontstyleID)
{
	cocos2d::CCNode* node=pRoot->getChildByTag(uiIndex);
	cocos2d::CCLabelTTF* cc=dynamic_cast<cocos2d::CCLabelTTF*>(node);
	NFC_setLabelByFontStyleID(cc,fontstyleID);
}


static void NFC_setActionSpriteEnable(int uiIndex,cocos2d::CCNode * pRoot,bool isEnable)
{
	CSimpleActionSprite * pSprite=(CSimpleActionSprite *)pRoot->getChildByTag(uiIndex); 
	if(pSprite)
	{
		if(isEnable)
		pSprite->PlayAction(); 
		else
		pSprite->StopAction(); 
	} 
}

static void  NFC_setAnimationSpriteEnable(int uiIndex,cocos2d::CCNode * pRoot,bool isEnable)
{
	CAnimationSprite * pAnimationSprite = (CAnimationSprite *)pRoot->getChildByTag(uiIndex);
	if(isEnable)
	pAnimationSprite->PlayEffect();
	else
	pAnimationSprite->StopEffect();
}


/*
	CProgressInnerBar
*/
static  void  NFC_setCProgressInnerBar(int barUIIndex,cocos2d::CCNode * pParent,float fPercent)
{
	CProgressInnerBar * pProgressInnerBar =(CProgressInnerBar *)pParent->getChildByTag(barUIIndex);
	if(pProgressInnerBar)
	pProgressInnerBar->setPercent(fPercent);
}

/*
	SceneEffect
*/
static  void  NFC_resumeActionsForSceneSprite(int key,cocos2d::CCNode* root)
{
	cocos2d::CCNode* node=root->getChildByTag(key);
	SceneEffect* cc=dynamic_cast<SceneEffect*>(node);
	assert(cc!=NULL);
	cc->ReplayAction();
}


/****
	ArtFontLabelNode
**/
static cocos2d::CCNode* NFC_getArtFontLabel(int type,int num){
	std::vector<int> vecSub=varConfig::getSubInt(num);
	std::vector<int> vecFontID; vecFontID.clear();
	//n个单数
	for (int i=0;i<(int)vecSub.size();i++)
	{
		int num=vecSub[i];
		int fontid=ArtFontDataManager::get_instance2()->GetArtFontValueFromID(type,num);
		assert(fontid!=0);
		vecFontID.push_back(fontid);
	}
	ArtFontLabelBatchNode* Label=ArtFontLabelBatchNode::CreateArtFontWithArray(vecFontID);
	cocos2d::CCNode* node=Label->GetBatchNodeLabel();
	delete Label;Label=NULL;
	return node;
}

/*
根据FontStyleID 翻译对应的富文本模板
*/
static std::string NFC_getRichTextCSSByFontStyleID(int fontstyleID,std::string formatStr)
{
	FSData* dd=FONTSTYLEDATAMANAGER->getDataByID(fontstyleID);
	char  richCSSTemplate[256]={0};
	std::string baseRichTxtCSS="<a type=\'text\' fontsize=\'%f\' fontname=\'%s\' fontcolor=\'{%d,%d,%d}\' text=\'%s\'></a>";
	if(std::string::npos==formatStr.find("%s"))
	formatStr="%s";
	sprintf(richCSSTemplate,baseRichTxtCSS.c_str(),dd->fontsize_,dd->fontname_,dd->colorR_,dd->colorG_,dd->colorB_,formatStr.c_str());
	return richCSSTemplate;
}

/*
绑定按钮点击回调事件接口
*/
static void  NFC_bindSelectorForBtn(int btnUIIndex,cocos2d::CCNode * pParent,cocos2d::CCNode * pDelegate,SEL_MenuHandler pSelector)	
{
	cocos2d::CCMenu * pMemu=(cocos2d::CCMenu *)pParent->getChildByTag(btnUIIndex);
	if(pMemu!=NULL)
	{
		CMenuItemSprite  * pMenuItem=(CMenuItemSprite *)pMemu->getChildByTag(0);
		if(pMenuItem!=NULL)
		{
			pMenuItem->setIDX(btnUIIndex);
			pMenuItem->setTarget(pDelegate,pSelector);
		}
	} 
}

static void  NFC_bindSelectorForDTHeroIcon(int btnUIIndex,cocos2d::CCNode * pParent,cocos2d::CCNode * pDelegate,SEL_MenuHandler pSelector)	
{
	DTHeroIcon * pHeroIcon = (DTHeroIcon *) pParent->getChildByTag(btnUIIndex);
	if(pHeroIcon)
	{
		pHeroIcon->setMenuSelector(btnUIIndex,pDelegate,pSelector); 
	}
}

static void  NFC_bindSelectorForCellDTHeroIcon(int btnUIIndex,int cellIndex,cocos2d::CCNode * pParent,cocos2d::CCNode * pDelegate,SEL_MenuHandler pSelector)	
{
	DTHeroIcon * pHeroIcon = (DTHeroIcon *) pParent->getChildByTag(btnUIIndex);
	if(pHeroIcon)
	{
		pHeroIcon->setMenuSelector(cellIndex,pDelegate,pSelector); 
	}
}

/*
绑定TableView中按钮回调事件接口
*/
static void NFC_bindSelectotForCellBtn(int btnUIIndex,int cellIndex,cocos2d::CCNode * pParent,cocos2d::CCNode * pDelegate,SEL_MenuHandler pSelector)
{
	cocos2d::CCMenu * pMemu=(cocos2d::CCMenu *)pParent->getChildByTag(btnUIIndex);
	if(pMemu!=NULL)
	{
		CMenuItemSprite  * pMenuItem=(CMenuItemSprite *)pMemu->getChildByTag(0);
		if(pMenuItem!=NULL)
		{
			pMenuItem->setIDX(cellIndex);
			pMenuItem->setTarget(pDelegate,pSelector);
		}
		pMemu->setVisible(true);
	} 
}

/*
绑定TouchSprite回调事件接口
*/
static void  NFC_bindSelectorForTouchSprite(int btnUIIndex,cocos2d::CCNode * pParent,CTouchSpriteDelegate * pDelegate)
{
	CTouchSprite * pTouchSprite=(CTouchSprite *)pParent->getChildByTag(btnUIIndex);
	if(pTouchSprite)
	{
		pTouchSprite->setIDX(btnUIIndex);
		pTouchSprite->setDelegate(pDelegate);
	}
}


/*
绑定按钮多个附加参数
*/
static void  NFC_bindMenuSpriteAttachParams(int btnUIIndex,cocos2d::CCNode * pParant,int attachPatam1,int attachParam2,cocos2d::CCNode * pDelegate,SEL_MenuHandler pSelector)
{
	cocos2d::CCMenu * pMemu = (cocos2d::CCMenu *)pParant->getChildByTag(btnUIIndex);
	if(pMemu!=NULL)
	{
		CMenuItemSprite  * pMenuItem = (CMenuItemSprite *)pMemu->getChildByTag(0);
		if(pMenuItem)
		{
			pMenuItem->setAttachData1(attachPatam1);
			pMenuItem->setAttachData2(attachParam2);
			pMenuItem->setTarget(pDelegate,pSelector);
		} 
	} 
}
 

static void  NFC_setMenuSpriteAttachParam(int uiIndex,cocos2d::CCNode * pParant,int attachParam1,int attachParam2)
{
	cocos2d::CCMenu * pMenu = (cocos2d::CCMenu *)pParant->getChildByTag(uiIndex);
	if(pMenu)
	{ 
	   CMenuItemSprite  * pMenuItemSprite =(CMenuItemSprite *)pMenu->getChildByTag(0);
	   if(pMenuItemSprite)
	   {  
		   pMenuItemSprite->setAttachData1(attachParam1);
		   pMenuItemSprite->setAttachData1(attachParam2);
	   }
	}
}


static void NFC_setTabMenuState(int tabUIIndex,cocos2d::CCNode *pParent,bool isSelectAble)
{
	cocos2d::CCMenu * pMemu=(cocos2d::CCMenu *)pParent->getChildByTag(tabUIIndex);
	if(pMemu!=NULL)
	{
		CMenuItemSprite  * pMenuItem=(CMenuItemSprite *)pMemu->getChildByTag(0);
		if(pMenuItem!=NULL)
		{
			pMenuItem->setIDX(tabUIIndex);
			if(isSelectAble)
			{
				pMenuItem->selected(true);
			}
			else
			{
				pMenuItem->unselected();
			}
		}
	}
}

/*
设置按钮禁用状态事件接口
*/
static void  NFC_setMenuEnable(int uiIndex,cocos2d::CCNode * pParent,bool isEnable)
{
	 cocos2d::CCMenu * pMenu = (cocos2d::CCMenu *)pParent->getChildByTag(uiIndex);
	 if(pMenu)
	 {
		 pMenu->setVisible(true);
		 CMenuItemSprite * pMenuItemSprite = (CMenuItemSprite *)  pMenu->getChildByTag(0);
		 if(pMenuItemSprite)
		 {
			 pMenuItemSprite->setEnabled(isEnable);
		 } 
	 }
}

 
/*
设置UI接口可视接口
*/
static void  NFC_setNodeVisable(int btnUIIndex,cocos2d::CCNode * pParent,bool isVisiable)	
{
	if(btnUIIndex >= 0)
	{
		cocos2d::CCNode * pChild=(cocos2d::CCNode *)pParent->getChildByTag(btnUIIndex);
		if(pChild)
		{
			pChild->setVisible(isVisiable);
		} 
	} 
}


static  void  NFC_setTimeLabel(int uiIndex,cocos2d::CCNode * pParent,CTimerEventProtocol * pDelegate,int timeDistance)
{
	CTimeLabel * pTimeLabel = (CTimeLabel *) pParent->getChildByTag(uiIndex);
	if(pTimeLabel)
	{
		pTimeLabel->setTimerEventDelegate(pDelegate);
		if(timeDistance!=0)
		pTimeLabel->StartTimer(timeDistance);
		else
		pTimeLabel->StopTimer(true);
	}
}



//创建CCLabelTTF 根据 UIViewData
static cocos2d::CCLabelTTF* NFC_createLabelByViewData(cocos2d::CCNode* parentNode,const UIViewData& dd){
	CCLabelTTF* cc=CCLabelTTF::create(dd.labelstring_.c_str(),dd.fontname_,dd.fontsize_);
	cc->setTag(dd.idx_);
	bool isVisible=dd.hide_==0?true:false;
	cc->setVisible(isVisible);
	cc->setColor(ccc3(dd.colorR_,dd.colorG_,dd.colorB_));
	cc->setAnchorPoint(ccp(dd.anchorx_,dd.anchory_));
	cc->setPosition(ccp(dd.posx_,dd.posy_));
	parentNode->addChild(cc,dd.zorder_);
	return cc;
}

//创建CCLabelTTF Mutiline 根据 UIViewData
static cocos2d::CCLabelTTF* NFC_createLabelMutilineByViewData(cocos2d::CCNode* parentNode,const UIViewData& dd){
	CCLabelTTF* cc=CCLabelTTF::create(dd.labelstring_.c_str(),dd.fontname_,dd.fontsize_);
	cc->setDimensions(CCSizeMake(dd.width_,dd.height_));
	cc->setHorizontalAlignment(kCCTextAlignmentLeft);
	cc->setTag(dd.idx_);
	bool isVisible=dd.hide_==0?true:false;
	cc->setVisible(isVisible);
	cc->setColor(ccc3(dd.colorR_,dd.colorG_,dd.colorB_));
	cc->setAnchorPoint(ccp(dd.anchorx_,dd.anchory_));
	cc->setPosition(ccp(dd.posx_,dd.posy_));
	parentNode->addChild(cc,dd.zorder_);
	return cc;
}

static float NFC_getHeightOfLabel(float maxwidth,std::string txt)
{
	cocos2d::CCLabelTTF* cc=cocos2d::CCLabelTTF::create();
	if (maxwidth>0)
	{
		cc->setDimensions(cocos2d::CCSizeMake(maxwidth,0));
	}
	cc->setString(txt.c_str());
	return cc->getContentSize().height;
}

/****
	TableView
**/
static void NFC_refreshTableView(cocos2d::extension::CCTableView* tb){
	assert(tb!=NULL);
	tb->reloadData();
	tb->setContentOffset(ccp(0,tb->getViewSize().height-tb->getContentSize().height));
}

static void NFC_refreshTableViewForH(cocos2d::extension::CCTableView* tb,cocos2d::CCSize offSize){
	assert(tb!=NULL);
	tb->reloadData();
	tb->setContentOffset(ccp(0-offSize.width,0));
}
 
static void NFC_refreshTableWithOffSet(cocos2d::extension::CCTableView* tb,const cocos2d::CCPoint& offset){
	tb->reloadData();
	if(offset.equals(cocos2d::CCPointZero))
	{ 
		tb->setContentOffset(ccp(0,tb->getViewSize().height-tb->getContentSize().height));
	}
	else
	{ 
		if(offset.y<=(tb->getViewSize().height-tb->getContentSize().height))
		{
			tb->setContentOffset(ccp(0,tb->getViewSize().height-tb->getContentSize().height));
		}
		else
		{
			tb->setContentOffset(offset);
		} 
	}
}

static void NFC_setOffsetForTableView(cocos2d::extension::CCTableView* tb,const cocos2d::CCPoint& offset){
	assert(tb!=NULL);
	tb->setContentOffset(offset);
}

static void NFC_refreshTableViewAndSetOldOffset(cocos2d::extension::CCTableView* tb){
	cocos2d::CCPoint offSet=tb->getContentOffset();	
	float oldHeight=tb->getContentSize().height;
	NFC_refreshTableView(tb);
	float curHeight=tb->getContentSize().height;
	offSet.y+=oldHeight-curHeight;
	NFC_setOffsetForTableView(tb,offSet);
}



/****
	ScrollView
**/
static void NFC_refreshScrollView(cocos2d::extension::CCScrollView* ss){
	assert(ss!=NULL);
	ss->setContentOffset(ccp(0,ss->getViewSize().height-ss->getContentSize().height));
}

/****
	CCSprite
**/
static void NFC_setPicForCCSprite(int key,cocos2d::CCNode* root,const char* file, bool visible){
	cocos2d::CCNode* node=root->getChildByTag(key);
	cocos2d::CCSprite* cc=dynamic_cast<cocos2d::CCSprite*>(node);
	assert(cc!=NULL);
	cc->setProperty("File",file);
	node->setVisible(visible);
}

static void NFC_setPicForCCSprite(int key,cocos2d::CCNode* root,const char* file){
	cocos2d::CCNode* node=root->getChildByTag(key);
	cocos2d::CCSprite* cc=dynamic_cast<cocos2d::CCSprite*>(node);
	assert(cc!=NULL);
	cc->setProperty("File",file);
}

static void NFC_setPicForCCSprite(int key,cocos2d::CCNode* root, std::string file, bool visable){
	NFC_setPicForCCSprite(key, root, file.c_str(), visable);
}

static void NFC_setPicForCCSprite_2(cocos2d::CCSprite* cc,const char* file, bool visible = true){
	cc->setProperty("File",file);
	cc->setVisible(visible);
}

static void NFC_setPicScale(int tag, cocos2d::CCNode * parent, float scale)
{
	cocos2d::CCSprite* node=(cocos2d::CCSprite*)parent->getChildByTag(tag);
	node->setScale(1.0f);
	node->setScale(scale);
}

static float NFC_getHeightOfSprite(const char* file)
{
	cocos2d::CCSprite* cc=cocos2d::CCSprite::create();
	cc->setProperty("File",file);
	return cc->getContentSize().height;
}
 
static void NFC_setSpriteFlipX(int UIIndex,cocos2d::CCNode * pParent,bool isFlipX)
{
	cocos2d::CCSprite * pSprite=(cocos2d::CCSprite *)pParent->getChildByTag(UIIndex);
	if(pSprite)
	pSprite->setFlipX(isFlipX);
}
static void NFC_setSpriteFlipY(int UIIndex,cocos2d::CCNode * pParent,bool isFlipY)
{ 
	cocos2d::CCSprite * pSprite=(cocos2d::CCSprite *)pParent->getChildByTag(UIIndex);
	if(pSprite)
	pSprite->setFlipY(isFlipY);
}


//创建CCSprite by UIviewData
static cocos2d::CCSprite* NFC_createSpriteByViewData(cocos2d::CCNode* parentNode,const UIViewData& dd)
{
	bool isVisible=dd.hide_==0?true:false;
	CCSprite* cc=CCSprite::create();
	if (strcmp(dd.filepath_,"0")!=0)
		cc->setProperty("File",dd.filepath_);
	cc->setTag(dd.idx_);
	cc->setVisible(isVisible);
	if (dd.scale_!=1.0f)
		cc->setScale(dd.scale_);
	if (dd.rotation_!=0.0f)
		cc->setRotation(dd.rotation_);
	cc->setAnchorPoint(ccp(dd.anchorx_,dd.anchory_));
	cc->setPosition(ccp(dd.posx_,dd.posy_));
	parentNode->addChild(cc,dd.zorder_);
	return cc;
}

static const cocos2d::CCSize& NFC_getSizeFromSprite(int key,cocos2d::CCNode* root)
{
	cocos2d::CCNode* node=root->getChildByTag(key);
	cocos2d::CCSprite* cc=dynamic_cast<cocos2d::CCSprite*>(node);
	assert(cc!=NULL);
	return cc->getContentSize();
}

/****
	CSprite
**/
static void NFC_changeImageForCSprite(int key,cocos2d::CCNode* root,unsigned int idx){
	cocos2d::CCNode* node=root->getChildByTag(key);
	CSprite* cc=dynamic_cast<CSprite*>(node);
	assert(cc!=NULL);
	cc->setVisible(true);
	if (idx==0)
		cc->changeToImage1();
	else if(idx==1)
		cc->changeToImage2();
	else if(idx==2)
		cc->changeToImage3();
}

static  void  NFC_setSpriteColor(int uiIndex,cocos2d::CCNode * pRoot,cocos2d::ccColor3B & color)
{ 
	cocos2d::CCSprite* pSprite=(cocos2d::CCSprite* )pRoot->getChildByTag(uiIndex);
	if(pSprite)
	{
		pSprite->setColor(color);
	}
}


static  void  NFC_setGrapSprite(int uiIndex,cocos2d::CCNode * pRoot,bool isGrapEnable)
{ 
  CCGrapSprite * pGrapSprite=(CCGrapSprite *)pRoot->getChildByTag(uiIndex);
  if(pGrapSprite)
  pGrapSprite->setGrapTexture(isGrapEnable);
}


/****
	CCMenuItem
**/
static void NFC_setEnabledForMenuItem(int key,cocos2d::CCNode* root,bool isEnabled){
	cocos2d::CCMenu* menu=(cocos2d::CCMenu*)root->getChildByTag(key);
	cocos2d::CCMenuItem* cc=(cocos2d::CCMenuItem*)menu->getChildByTag(0);
	cc->setEnabled(isEnabled);
}

static void NFC_setEnabledForMenuItem(int menutag, int itemtag, cocos2d::CCNode * parent, bool enable)
{
	cocos2d::CCMenu * menu = (cocos2d::CCMenu *)parent->getChildByTag(menutag);
	cocos2d::CCMenuItem * item = (cocos2d::CCMenuItem *)menu->getChildByTag(itemtag);
	item->setEnabled(enable);
}

static cocos2d::CCMenuItem* NFC_getMenuItem(int key,cocos2d::CCNode* root){
	cocos2d::CCMenu* menu=(cocos2d::CCMenu*)root->getChildByTag(key);
	cocos2d::CCMenuItem* cc=(cocos2d::CCMenuItem*)menu->getChildByTag(0);
	return cc;
}


//创建CLabelButton 根据 UIViewData
static CLabelButtonItem* NFC_createCLabelButtonByViewData(cocos2d::CCNode* parentNode,const UIViewData& dd){
	bool isSwallow=dd.swallow_==0?false:true;
	CPriorityMenu* menu=CPriorityMenu::create(dd.touchpriority_,isSwallow);
	menu->setTag(dd.idx_);
	bool isVisible=dd.hide_==0?true:false;
	menu->setVisible(isVisible);
	menu->setPosition(CCPointZero);
	parentNode->addChild(menu,dd.zorder_);
	//
	CCSprite* sel=CCSprite::create();
	sel->setProperty("File",dd.filepath_);
	CCSprite* nor=CCSprite::create();
	nor->setProperty("File",dd.filepath2_);
	CCLabelTTF* lb=CCLabelTTF::create();
	lb->setFontName(dd.fontname_);
	lb->setFontSize(dd.fontsize_);
	lb->setColor(ccc3(dd.colorR_,dd.colorG_,dd.colorB_));
	lb->setString(dd.labelstring_.c_str());
	CLabelButtonItem* cc=CLabelButtonItem::create(sel,nor,lb);
	if (dd.scale_!=1.0f)
		cc->setScale(dd.scale_);
	if (dd.rotation_!=0.0f)
		cc->setRotation(dd.rotation_);
	cc->setTag(0);
	cc->setSoundID(dd.soundid_);
	cc->setAnchorPoint(ccp(dd.anchorx_,dd.anchory_));
	cc->setPosition(ccp(dd.posx_,dd.posy_));
	menu->addChild(cc);
	return cc;
}

//创建CCMenuitem 根据 UIViewData
static CMenuItemSprite* NFC_createMenuItemByViewData(cocos2d::CCNode* parentNode,const UIViewData& dd){
	bool isSwallow=dd.swallow_==0?false:true;
	CPriorityMenu* menu=CPriorityMenu::create(dd.touchpriority_,isSwallow);
	menu->setTag(dd.idx_);
	bool isVisible=dd.hide_==0?true:false;
	menu->setVisible(isVisible);
	menu->setPosition(CCPointZero);
	parentNode->addChild(menu,dd.zorder_);
	CMenuItemSprite* cc=CMenuItemSprite::create(dd.filepath_,dd.filepath2_,NULL,NULL);;
	if (strcmp(dd.filepath3_,"0")!=0){
		CCSprite* sp=CCSprite::create();
		sp->setProperty("File",dd.filepath3_);
		cc->setDisabledImage(sp);
	}
	if (dd.scale_!=1.0f)
		cc->setScale(dd.scale_);
	if (dd.rotation_!=0.0f)
		cc->setRotation(dd.rotation_);
	cc->setTag(0);
	cc->setSoundID(dd.soundid_);
	cc->setAnchorPoint(ccp(dd.anchorx_,dd.anchory_));
	cc->setPosition(ccp(dd.posx_,dd.posy_));
	menu->addChild(cc);
	return cc;
}
 
static void NFC_setNormalImageForMenuItem(CMenuItemSprite* cc,std::string filepath){
	cocos2d::CCSprite* nor=cocos2d::CCSprite::create();
	nor->setProperty("File",filepath);
	cc->setNormalImageAndRelocation(nor);
}


static  void  NFC_setNoramlImageByUIIndex(int uiIndex,cocos2d::CCNode * pRoot,std::string fileName)
{
	cocos2d::CCMenu* menu=(cocos2d::CCMenu*)pRoot->getChildByTag(uiIndex);
	CMenuItemSprite * cc= (CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(uiIndex);
	NFC_setNormalImageForMenuItem(cc,fileName);
	menu->setVisible(true);
}


static void NFC_setSelectedImageForMenuItem(cocos2d::CCMenuItemSprite* cc,std::string filepath){
	cocos2d::CCSprite* sel=cocos2d::CCSprite::create();
	sel->setProperty("File",filepath);
	cc->setSelectedImage(sel);
}

static void NFC_setDisabledImageForMenuItem(cocos2d::CCMenuItemSprite* cc,std::string filepath){
	cocos2d::CCSprite* sel=cocos2d::CCSprite::create();
	sel->setProperty("File",filepath);
	cc->setDisabledImage(sel);
}

static void  NFC_getMenuItemSpriteSI(cocos2d::CCNode * parentNode,UIViewData dd)
{
	bool isSwallow=dd.swallow_==0?false:true;
	CPriorityMenu* menu=CPriorityMenu::create(dd.touchpriority_,isSwallow);
	menu->setTag(dd.idx_);
	bool isVisible=dd.hide_==0?true:false;
	menu->setVisible(isVisible);
	menu->setPosition(CCPointZero);
	parentNode->addChild(menu,dd.zorder_);
	CCSprite* sp1=CCSprite::create();
	sp1->setProperty("File",dd.filepath_);
	sp1->setScale(dd.width_);
	CMenuItemSprite* cc=CMenuItemSprite::create(sp1,NULL,NULL,NULL);
	if (strcmp(dd.filepath3_,"0")!=0){
		CCSprite* sp=CCSprite::create();
		sp->setProperty("File",dd.filepath3_);
		sp->setScale(dd.width_);
		cc->setDisabledImage(sp);
	}
	if (dd.scale_!=1.0f)
		cc->setScale(dd.scale_);
	if (dd.rotation_!=0.0f)
		cc->setRotation(dd.rotation_);
	cc->setTag(0);
	cc->setSelectedType(CMenuItemSprite::kSELECTEDTYPE_SCALETO_BIG);
	cc->setSoundID(dd.soundid_);
	cc->setAnchorPoint(ccp(dd.anchorx_,dd.anchory_));
	cc->setPosition(ccp(dd.posx_,dd.posy_));
	menu->addChild(cc);
}


/****
	CProgressInnerBar
**/
static void NFC_setProgressForCProgressInnerBar(int key,cocos2d::CCNode* root,float percent){
	CProgressInnerBar* cc=(CProgressInnerBar*)root->getChildByTag(key);
	cc->setPercent(percent);
}

//创建箭头
static cocos2d::extension::CCSkeletonAnimation * NFC_createGuideArrow()
{
	cocos2d::extension::CCSkeletonAnimation* m_pArrow = CCSkeletonAnimation::createWithFile(SPINE_GUIDE_ARROW_JSON,SPINE_GUIDE_ARROW_ALTAS);
	assert(m_pArrow!=NULL);
	m_pArrow->setAnimation(SPINE_GUIDE_ARROW_DAIJI, true);
	return m_pArrow;
}

//创建DTAwardBoard by UIviewData
static DTAwardBoard* NFC_createDTAwardBoardByViewData(cocos2d::CCNode* parentNode,const UIViewData& dd)
{
	CCSprite* numBg=CCSprite::create();
	numBg->setProperty("File",dd.filepath_);
	CCLabelTTF* num=CCLabelTTF::create();
	num->setFontName(dd.fontname_);
	num->setColor(ccc3(dd.colorR_,dd.colorG_,dd.colorB_));
	num->setFontSize(dd.fontsize_);
	//
	bool isSwallow=dd.swallow_==1?true:false;
	DTAwardBoard* cc=DTAwardBoard::create(numBg,num,dd.touchpriority_,isSwallow);
	cc->setTag(dd.idx_);
	cc->setZOrder(dd.zorder_);
	bool isVisible=dd.hide_==0?true:false;
	cc->setVisible(isVisible);
	cc->setAnchorPoint(ccp(dd.anchorx_,dd.anchory_));
	cc->setPosition(ccp(dd.posx_,dd.posy_));
	parentNode->addChild(cc);
	return cc;
}
 
 
static void NFC_setDTHeroIcon(int uiIndex,cocos2d::CCNode * pParent,int IconID,bool isVisiable)
{
	DTHeroIcon * pDTHeroIcon = (DTHeroIcon *)pParent->getChildByTag(uiIndex);
	if(pDTHeroIcon)
	{
		pDTHeroIcon->setHeroIconID(IconID);
		pDTHeroIcon->setVisible(isVisiable);
	}
}

static void NFC_setDTHeroIconVisiable(int uiIndex,cocos2d::CCNode * pParent,bool isVisiable)
{
	DTHeroIcon * pDTHeroIcon = (DTHeroIcon *)pParent->getChildByTag(uiIndex);
	if(pDTHeroIcon)
	{ 
		pDTHeroIcon->setHeroIconVisable(isVisiable);
	}
}

static  void  NFC_bindDTHeroCellSelectorAndAttahParam(int uiIndex,int cellIndex,cocos2d::CCNode *pParent,cocos2d::CCNode * pDelegate,SEL_MenuHandler pSelector,int attachParam1,int attachParam2)
{
	DTHeroIcon * pDTHeroIcon = (DTHeroIcon *) pParent->getChildByTag(uiIndex);
	if(pDTHeroIcon)
	{
		pDTHeroIcon->setMenuSelector(cellIndex,pDelegate,pSelector);
		pDTHeroIcon->setHeroAttachParam(attachParam1,attachParam2);
	}

}

static  void  NFC_setDTHeroQualiy(int uiIndex,cocos2d::CCNode * pParent,int quality)
{
	DTHeroIcon * pDTHeroIcon = (DTHeroIcon *) pParent->getChildByTag(uiIndex);
	if(pDTHeroIcon)
	{
		pDTHeroIcon->setHeroQualiy(quality);
	}
} 
 
static  void  NFC_setDTHeroColor(int uiIndex,cocos2d::CCNode * pParent,const cocos2d::ccColor3B & color3)
{
	DTHeroIcon * pDTHeroIcon = (DTHeroIcon *) pParent->getChildByTag(uiIndex);
	if(pDTHeroIcon)
	{
		pDTHeroIcon->setIconColor(color3);
	}
} 


//===============获取数据的快捷接口==========================

//@判断该位置是否有英雄
static bool NFC_HasTeamHero(int pos=0){
	return ROLEHEROSKINSDATAHANDLER->HasTeamHero(pos);
}

//@判断该英雄是否在队伍中
static bool NFC_IsHeroInTeam(int uniqueID){
	return ROLEHEROSKINSDATAHANDLER->IsHeroInTeam(uniqueID);
}

//@读取队伍中的英雄
static IHeroSkinItem* NFC_GetTeamHero(int pos=0){
	IHeroSkinItem* hero=ROLEHEROSKINSDATAHANDLER->GetCurHeroSkinItem(pos);
	return hero;
}

//@更换队伍中指定位置的英雄
static void NFC_ChangeTeamHero(IHeroSkinItem * pHeroSkinItem,int pos = 0){
	RoleHeroSkinsDataHandler::get_instance2()->ChangeHeroByPos(pHeroSkinItem, pos);
}

//@读取图鉴里的英雄
static IHeroSkinItem* NFC_GetHeroFromLib(int idx=0){
	IHeroSkinItem* hero = RoleHeroSkinsDataHandler::get_instance2()->GetHeroSkinItemByID(idx);
	return hero;
}


//@读取英雄属性管理器
static Attribute* NFC_GetHeroAttributeManager(int pos=0){
	IHeroSkinItem* hero=ROLEHEROSKINSDATAHANDLER->GetCurHeroSkinItem(pos);
	if (hero!=NULL)
	{
		return hero->getAttributeManager();
	}
	return NULL;
}

//@读取英雄装备管理器
static RoleEquipDataHandler* NFC_GetHeroEquipManager(int pos=0){
	IHeroSkinItem* hero=ROLEHEROSKINSDATAHANDLER->GetCurHeroSkinItem(pos);
	if (hero != NULL)
	{
		RoleEquipDataHandler* manager = hero->getEquipManager();
		return manager;
	}
	return NULL;
}

//@读取英雄技能管理器
static RoleSkillsDataHandler* NFC_GetHeroSkillManager(int pos=0){
	IHeroSkinItem* hero=ROLEHEROSKINSDATAHANDLER->GetCurHeroSkinItem(pos);
	if (hero != NULL)
	{
		RoleSkillsDataHandler* manager = hero->getSkillManager();
		return manager;
	}
	return NULL;
}

//@交换英雄队列交换
static void NFC_SetHeroChangeManager(int index,int index1){
	IHeroSkinItem* temp1 = NFC_GetTeamHero(index);
	if (temp1 == NULL)
		return;
	IHeroSkinItem* temp2 = NFC_GetTeamHero(index1);
	if (temp2 == NULL)
		return;
/*
	std::vector<IHeroSkinItem *> vecHeroList;
	if(index == 0)
	{
		vecHeroList.push_back(temp2);
		vecHeroList.push_back(temp1);
		if (NFC_HasTeamHero(2))
		{
			vecHeroList.push_back(NFC_GetTeamHero(2));
		}
	}
	else if (index == 1)
	{
		IHeroSkinItem* item = NFC_GetTeamHero(0);
		vecHeroList.push_back(item);
		vecHeroList.push_back(temp2);
		vecHeroList.push_back(temp1);
	}
	ROLEHEROSKINSDATAHANDLER->SetHeroVector(vecHeroList);*/
	swap(ROLEHEROSKINSDATAHANDLER->GetHeroVector()[index],ROLEHEROSKINSDATAHANDLER->GetHeroVector()[index1]);


}

 
#endif