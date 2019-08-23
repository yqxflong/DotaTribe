//Name：SelectRoleWindow
//Function：选角色界面
//Author:周少男

#include "../include/SelectRoleWindow.h"
#include "../include/DOTATribeApp.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/UIViewDataManger.h"
#include "../include/LoggerSystem.h"
#include "../include/CMenuItemSprite.h"
#include "../include/MessageBoxWindow.h"
#include "../include/ServerInfoDataHandler.h"
#include "../include/VariableSystem.h"
#include "../include/HomeProcedure.h"
#include "../include/CreateRoleProcedure.h"
#include "../include/UIScrollNodeLayer.h"
#include "../include/ClientConstDataManager.h"
#include "../include/CPublicVarReader.h"
#include "../include/CreateRoleDataManager.h"
#include "../include/PlayerDataMessage.h"
#include "../include/RoleShapeDataManager.h"
#include "../include/RoleBaseDataManager.h"
#include "../include/ActionSetDataManager.h"
#include "../include/DBSystem.h"
#include "../include/SysLangDataManager.h"
#include "../include/CSCreateRolePacket.h"
#include "../include/CreateRoleRandomNamePacket.h"
#include "../include/CreateRoleRandomNameDataHandler.h"
#include "../include/NFControlsManager.h"
#include "../include/LoginProcedure.h"
#include <include/common/Random.h>
#include  "../include/MoveAnimation.h"
#include "../include/Common.h"

using namespace std;
using namespace extension;


#define  NameLengthMax 12
#define  NameLengthMin 2
#define FontName	"ArialRoundedMTBold" //默认字体
SelectRoleWindow::SelectRoleWindow()
:pRootNode(0)
{
	m_WindowType = _TYPED_WINDOW_SELECTROLE;

	m_PlayerIndex = 1;
	m_PlayerCount = 0;
	m_LeftPlayerIndex = 0;
	m_MidPlayerIndex = 0;
	m_RightPlayerIndex = 0;
	IsInSelectPlayer = true;
	IsFirstInSelectPlayer = true;
	IsMoving = false;
	IsBeginLeave = false;
	IsBeginEnter = false;
	pEditBox =NULL;
	m_IsKeyBoard = false;
}

SelectRoleWindow::~SelectRoleWindow()
{
}

bool SelectRoleWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_SELECTROLEWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_SELECTROLEWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_UI_TEXT_, true);
	RegisterEvent(_TYPED_EVENT_COMMOND_TURNLEFT_, true);
	RegisterEvent(_TYPED_EVENT_COMMOND_TURNRIGHT_, true);

	return IWindow::Init();
}

bool SelectRoleWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;
		InitRegister();
		//_playAllEffect();
		return true;
	} 
	while (false);

	return false;
}

void SelectRoleWindow::Tick()
{

	if(IsBeginLeave)
		CheckLeaveAnimation();
	if(IsBeginEnter)
		CheckEnterAnimation();

	IWindow::Tick();

}

void SelectRoleWindow::Destroy()
{
	cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	m_PlayerIndex = 1;
	m_PlayerCount = 0;
	m_LeftPlayerIndex = 0;
	m_MidPlayerIndex = 0;
	m_RightPlayerIndex = 0;
	IsInSelectPlayer = true;
	IsFirstInSelectPlayer = true;
	IsMoving = false;
	IsBeginLeave = false;
	IsBeginEnter = false;
	pRoleDesc=NULL;
	m_LeftPlayerSkeleton=NULL;
	m_RightPlayerSkeleton=NULL;
	m_MidPlayerSkeleton=NULL;
	pLeftData=NULL;
	pMidData=NULL; 
	pRightData=NULL;
	pEditBox=NULL;
	pRootNode=NULL;
	m_IsKeyBoard = false;
	IWindow::Destroy();
}

void SelectRoleWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{

	if (iEventType == _TYPED_EVENT_SHOW_SELECTROLEWINDOW_) 
	{
		OnShowWindowEventHandler(paramList);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_SELECTROLEWINDOW_)
	{
		Destroy();
	}
	else if (iEventType == _TYPED_EVENT_UPDATE_UI_TEXT_)
	{
		OnUpdateWindowEventHandler(paramList);
	}
}

void SelectRoleWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,100,true);
	Show(true);
}

void SelectRoleWindow::OnUpdateWindowEventHandler(std::list<std::string>& paramList)
{
	OnUpdatePlayerName(CreateRoleRandomNameDataHandler::get_instance2()->GetPlayerName());
}

void SelectRoleWindow::InitRegister()
{
	pRootNode=m_pRootNode;
	InitControl();
	_mapBtn();
	InitRolePosition();

	C2SCreateRoleRandomNamePacket crpacket(0);
	crpacket.Send();
}	


void SelectRoleWindow::InitControl()
{
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kSELECTROLEWINDOW,pRootNode);
	cocos2d::extension::CCScale9Sprite *pSprite = cocos2d::extension::CCScale9Sprite::create();
	pSprite->setProperty("File",PIC_IMAGE_NULL_);
	pEditBox = CCEditBox::create(CCSizeMake(200,40),pSprite); 
	pEditBox->setFont(FontName,22);
	pEditBox->setMaxLength(20);
	pEditBox->setInputMode(kEditBoxInputModeAny);
	pEditBox->setReturnType(kKeyboardReturnTypeDone);
	pEditBox->setDelegate(this);
	pEditBox->setPriorityFromParent(false);
	pEditBox->setPriority(kPRIORITYHIGHER);
	CCLabelTTF* temp = (CCLabelTTF*)pRootNode->getChildByTag(udNAME);
	pEditBox->setPosition(ccp(temp->getPositionX(),temp->getPositionY()));
	temp->getParent()->addChild(pEditBox,100);
}



void SelectRoleWindow::_mapBtn()
{
	CCMenu* menu = (CCMenu*)pRootNode->getChildByTag(udENTERBTN);
	CMenuItemSprite* cc= (CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udENTERBTN);
	cc->setTarget(this,menu_selector(SelectRoleWindow::On_Click_BtnClick));

	menu = (CCMenu*)pRootNode->getChildByTag(udSELECTNAMEBTN);
	cc= (CMenuItemSprite*)menu->getChildByTag(0);
	cc->setIDX(udSELECTNAMEBTN);
	cc->setTarget(this,menu_selector(SelectRoleWindow::On_Click_BtnClick));
}


void SelectRoleWindow::On_Click_BtnClick(cocos2d::CCObject* pSender)
{
	CMenuItemSprite* cc = (CMenuItemSprite*)pSender;
	int idx = cc->getIDX();

	if(idx==udENTERBTN)//进入游戏
	{
		//VARIABLESYSTEM->SetVariable(VariableSystem::_TYPED_CONFIG_ACCOUNT_,"dd","ddd",100);
		CreateRoleData *pData;
		if (m_PlayerIndex+1 >m_PlayerCount)
			pData = CreateRoleDataManager::get_instance2()->GetCreateRoleDataByID(1);
		else
			pData = CreateRoleDataManager::get_instance2()->GetCreateRoleDataByID(m_PlayerIndex+1);

		PlayerDataMessage::get_instance()->SetPlayerId(pData->mRoleModelID);
		std::string temp = pEditBox->getText();
		if (temp != "")
		{
			int _size = 0;
			std::list<std::string> templist = parser_utf8_string(temp.c_str());
			std::list<std::string>::iterator itor = templist.begin();
			std::list<std::string>::iterator itor_end = templist.end();
			for(;itor != itor_end;itor++)
			{
				if((*itor).size() >1 )
					_size += 2;
				else
					_size += 1;
			}
			if (_size > NameLengthMax || _size < NameLengthMin)
			{
				std::string str2=SysLangDataManager::get_instance2()->GetSysLangById(136);
				NFC_showMessageBox(kDEFAULT,str2);
			}
			else
			{
				CSCreateRolePacket crpacket(0,SERVERINFODATAINFO->GetCurAccountName().c_str(),pData->mRoleModelID,pEditBox->getText());
				crpacket.Send();
				NFC_showCommunicationWating(true);
			}
		}
		else
		{
			std::string strempty = SysLangDataManager::get_instance2()->GetSysLangById(17);
			NFC_showMessageBox(kDEFAULT,strempty);
		}
	}
	else if(idx == udSELECTNAMEBTN)
	{
		LOGGERSYSTEM->LogInfo("OnNameEditButtonClick~~~~");
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
		if (m_IsKeyBoard)
			return;
#endif
		C2SCreateRoleRandomNamePacket crpacket(0);
		crpacket.Send();
	}
}



void SelectRoleWindow::OnUpdatePlayerName(std::string name)
{
	pEditBox->setText(name.c_str());
}


void SelectRoleWindow::CheckLeaveAnimation()
{

	if (m_MidPlayerSkeleton->states[0]->time >= m_MidPlayerSkeleton->states[0]->animation->duration)
		m_MidPlayerSkeleton->setVisible(false);

	if (m_RightPlayerSkeleton->states[0]->time >= m_RightPlayerSkeleton->states[0]->animation->duration)
		m_RightPlayerSkeleton->setVisible(false);

	if (m_LeftPlayerSkeleton->states[0]->time >= m_LeftPlayerSkeleton->states[0]->animation->duration)
		m_LeftPlayerSkeleton->setVisible(false);

	if (m_MidPlayerSkeleton->states[0]->time >= m_MidPlayerSkeleton->states[0]->animation->duration
		&&m_RightPlayerSkeleton->states[0]->time >= m_RightPlayerSkeleton->states[0]->animation->duration
		&&m_LeftPlayerSkeleton->states[0]->time >= m_LeftPlayerSkeleton->states[0]->animation->duration)
	{
		IsBeginLeave = false;
		OnUpdateSelectPlayer();
	}


}

void SelectRoleWindow::CheckEnterAnimation()
{

	if(m_MidPlayerSkeleton->states[0]->time >= 0.1)
		m_MidPlayerSkeleton->setVisible(true);

	if(m_RightPlayerSkeleton->states[0]->time >= 0.1)
		m_RightPlayerSkeleton->setVisible(true);

	if(m_LeftPlayerSkeleton->states[0]->time >= 0.1)
		m_LeftPlayerSkeleton->setVisible(true);

	if (m_MidPlayerSkeleton->states[0]->time >= m_MidPlayerSkeleton->states[0]->animation->duration
		&&m_RightPlayerSkeleton->states[0]->time >= m_RightPlayerSkeleton->states[0]->animation->duration
		&&m_LeftPlayerSkeleton->states[0]->time >= m_LeftPlayerSkeleton->states[0]->animation->duration)
	{
		IsBeginEnter = false;
		m_LeftPlayerSkeleton->setAnimation(GetAnimationNameById(pLeftData->mRoleShapeID,pLeftData->mRoleDisabledAnimationID).c_str(),true);
		m_RightPlayerSkeleton->setAnimation(GetAnimationNameById(pRightData->mRoleShapeID,pRightData->mRoleDisabledAnimationID).c_str(),true);
		m_MidPlayerSkeleton->setAnimation(GetAnimationNameById(pMidData->mRoleShapeID,pMidData->mRoleSelectedAnimationID).c_str(),true); 
	}
}

void SelectRoleWindow::InitRolePosition()
{
	//加载人物骨骼
	m_SelectPlayerMapList.clear();
	CCNode* node=(CCNode*)pRootNode->getChildByTag(udSKENODE);


	std::map<int, CreateRoleData*>::iterator iter   = CreateRoleDataManager::get_instance2()->m_CreateRoleDataMapList.begin();
	std::map<int, CreateRoleData*>::iterator iter_e = CreateRoleDataManager::get_instance2()->m_CreateRoleDataMapList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		RoleShapeData* pData = RoleShapeDataManager::get_instance2()->GetRoleShapeById(iter->second->mRoleShapeID);
		CCLOG("%d",iter->second->mRoleIndexID);
		CreateRoleData* pData_c = CreateRoleDataManager::get_instance2()->GetCreateRoleDataByID(iter->second->mRoleIndexID);
		CCSkeletonAnimation* pSkeleton = CCSkeletonAnimation::createWithFile(pData->mShapeAnimationFileDaiJi,pData->mShapeAnimationImage);
		if(pSkeleton)
		{
			pSkeleton->setAnimation(GetAnimationNameById(iter->second->mRoleShapeID,pData_c->mRoleDisabledAnimationID).c_str(),false);
			AnimationStateData_setMixByName(pSkeleton->states[0]->data, GetAnimationNameById(iter->second->mRoleShapeID,pData_c->mRoleDisabledAnimationID).c_str(), GetAnimationNameById(iter->second->mRoleShapeID,pData_c->mRoleLeaveAnimationID).c_str(),0.25);
			AnimationStateData_setMixByName(pSkeleton->states[0]->data, GetAnimationNameById(iter->second->mRoleShapeID,pData_c->mRoleEntranceAnimationID).c_str(), GetAnimationNameById(iter->second->mRoleShapeID,pData_c->mRoleSelectedAnimationID).c_str(),0.25);
			AnimationStateData_setMixByName(pSkeleton->states[0]->data, GetAnimationNameById(iter->second->mRoleShapeID,pData_c->mRoleEntranceAnimationID).c_str(), GetAnimationNameById(iter->second->mRoleShapeID,pData_c->mRoleDisabledAnimationID).c_str(),0.25);
			AnimationStateData_setMixByName(pSkeleton->states[0]->data, GetAnimationNameById(iter->second->mRoleShapeID,pData_c->mRoleEntranceAnimationID).c_str(), GetAnimationNameById(iter->second->mRoleShapeID,pData_c->mRoleLeaveAnimationID).c_str(),0.25);
			pSkeleton->timeScale = ClientConstDataManager::get_instance2()->getValueByKey(CONST_KEY_BATTLE_NORSPD)/10.f;
			pSkeleton->setVisible(false);
			node->addChild(pSkeleton);
			m_SelectPlayerMapList.insert(std::map<int, CCSkeletonAnimation*>::value_type(iter->second->mRoleIndexID, pSkeleton));
			m_PlayerCount++;
		}	
	}

	OnUpdateSelectPlayer();

}



CCSkeletonAnimation * SelectRoleWindow::FindSkeletonByIndex(int index)
{
	std::map<int, CCSkeletonAnimation*>::iterator iter =  m_SelectPlayerMapList.find(index);
	if (iter->second)
		return iter->second;

	return NULL;
}

void SelectRoleWindow::OnUpdateSelectPlayer()
{
	if (!IsInSelectPlayer)
		return;
	std::map<int, CCSkeletonAnimation*>::iterator iter   = m_SelectPlayerMapList.begin();
	std::map<int, CCSkeletonAnimation*>::iterator iter_e = m_SelectPlayerMapList.end();
	for ( ; iter!=iter_e; ++iter)
	{
		if (iter->second)
		{
			iter->second->setVisible(false);
			iter->second->setRotationY(0.0f);
			iter->second->setColor(ccWHITE);
			iter->second->setOpacity(255);
			iter->second->setScale(1.0f);
			iter->second->getParent()->reorderChild(iter->second,0);

		}
	}


	//设置坐标
	//左
	MaskNode* node=(MaskNode*)m_pRootNode->getChildByTag(udROLELEFT);
	const UIViewData & tempData=node->GetViewData();
	CCSkeletonAnimation *pSkeleton = FindSkeletonByIndex(m_PlayerIndex);
	pSkeleton->setRotationY(180.f);
	m_LeftPlayerIndex =m_PlayerIndex;
	pSkeleton->setPosition(ccp(tempData.posx_,tempData.posy_));
	m_LeftPlayerSkeleton = pSkeleton;
	pLeftData = CreateRoleDataManager::get_instance2()->GetCreateRoleDataByID(m_LeftPlayerIndex);
	m_LeftPlayerSkeleton->setScale(tempData.scale_);
	ccColor3B m_color = ccc3((GLubyte)tempData.colorR_, (GLubyte)tempData.colorG_, (GLubyte)tempData.colorB_);
	m_LeftPlayerSkeleton->setColor(m_color);
	m_LeftPlayerSkeleton->setOpacity((GLubyte)tempData.alpha_);
	//右
	node=(MaskNode*)m_pRootNode->getChildByTag(udROLERIGHT);
	const UIViewData & tempData1=node->GetViewData();
	if (m_PlayerIndex+2>m_PlayerCount)
	{
		pSkeleton = FindSkeletonByIndex((m_PlayerIndex+2-m_PlayerCount));
		m_RightPlayerIndex = m_PlayerIndex+2-m_PlayerCount;
	}
	else
	{
		pSkeleton = FindSkeletonByIndex(m_PlayerIndex+2);
		m_RightPlayerIndex = m_PlayerIndex+2;
	}	
	pSkeleton->setPosition(ccp(tempData1.posx_,tempData1.posy_));
	m_RightPlayerSkeleton = pSkeleton;
	m_RightPlayerSkeleton->setScale(tempData1.scale_);
	pRightData = CreateRoleDataManager::get_instance2()->GetCreateRoleDataByID(m_RightPlayerIndex);
	m_RightPlayerSkeleton->setColor(m_color);
	m_RightPlayerSkeleton->setOpacity((GLubyte)tempData1.alpha_);
	//中
	node=(MaskNode*)m_pRootNode->getChildByTag(udROLECENTER);
	const UIViewData & tempData2=node->GetViewData();
	if (m_PlayerIndex+1>m_PlayerCount)
	{
		pSkeleton = FindSkeletonByIndex((m_PlayerIndex+1-m_PlayerCount));
		m_MidPlayerIndex =m_PlayerIndex+1-m_PlayerCount;
	}
	else
	{
		pSkeleton = FindSkeletonByIndex(m_PlayerIndex+1);
		m_MidPlayerIndex =m_PlayerIndex+1;
	}
	pSkeleton->setPosition(tempData2.posx_,tempData2.posy_);
	m_MidPlayerSkeleton = pSkeleton;
	m_MidPlayerSkeleton->setScale(tempData2.scale_);
	pMidData = CreateRoleDataManager::get_instance2()->GetCreateRoleDataByID(m_MidPlayerIndex);
	pRoleDesc = (CCLabelTTF*)pRootNode->getChildByTag(udTEXT);
	pRoleDesc->setString(SysLangDataManager::get_instance2()->GetSysLangById(pMidData->mRoleDescribeInfoID).c_str());

	pRoleDesc = (CCLabelTTF*)pRootNode->getChildByTag(udSERVERNAME);
	pRoleDesc->setString(SERVERINFODATAINFO->getCurServerName());
	//设置灰度
	IsMoving = false;
	if(!IsFirstInSelectPlayer)
		OnPlayEnterAnimation();
	if (IsFirstInSelectPlayer)
	{
		m_LeftPlayerSkeleton->setAnimation(GetAnimationNameById(pLeftData->mRoleShapeID,pLeftData->mRoleDisabledAnimationID).c_str(),false);
		m_MidPlayerSkeleton->setAnimation(GetAnimationNameById(pMidData->mRoleShapeID,pMidData->mRoleSelectedAnimationID).c_str(),true);
		m_RightPlayerSkeleton->setAnimation(GetAnimationNameById(pRightData->mRoleShapeID,pRightData->mRoleDisabledAnimationID).c_str(),false);
		m_MidPlayerSkeleton->setVisible(true);
		m_RightPlayerSkeleton->setVisible(true);
		m_LeftPlayerSkeleton->setVisible(true);
	}
	IsFirstInSelectPlayer =false;
}

std::string SelectRoleWindow::GetAnimationNameById(int shapeID,int skillID)
{
	// 	人物动画
	RoleShapeData* pShapeData = RoleShapeDataManager::get_instance2()->GetRoleShapeById(shapeID);
	if(pShapeData && pShapeData->mActionSetDataManager)
	return pShapeData->mActionSetDataManager->GetActionNameByActionId(skillID);
	return "";
}

bool SelectRoleWindow::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{

	if(!IsMoving)
	{
		cocos2d::CCPoint touchPosition=pTouch->getLocationInView();
		touchBeginPos=cocos2d::CCDirector::sharedDirector()->convertToGL(touchPosition);
		if (touchBeginPos.y>200)
			IsMoving =true;
	}

	return true;
}

void SelectRoleWindow::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}


void SelectRoleWindow::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!IsMoving)
		return;
	if (IsBeginEnter || IsBeginLeave)
		return;
	cocos2d::CCPoint touchPosition=pTouch->getLocationInView();
	touchEndPos=cocos2d::CCDirector::sharedDirector()->convertToGL(touchPosition);
	float temp = touchEndPos.x - touchBeginPos.x;
	if(fabs(temp) >100)
	{
		if (temp >0)
			OnTurnRightEventHandler();
		else
			OnTurnLeftEventHandler();
	}
	else
	{
		if (touchEndPos.x > cocos2d::CCDirector::sharedDirector()->getWinSize().width /2 +50)
			OnTurnLeftEventHandler();
		else if (touchEndPos.x < cocos2d::CCDirector::sharedDirector()->getWinSize().width /2 -50)
			OnTurnRightEventHandler();
	}

}

void SelectRoleWindow::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){

}


void SelectRoleWindow::OnTurnLeftEventHandler()
{
	if (m_PlayerIndex+1>m_PlayerCount)
		m_PlayerIndex = 1;
	else
		m_PlayerIndex++;

	OnPlayLeaveAnimation();

}
void SelectRoleWindow::OnPlayLeaveAnimation()
{
	IsBeginLeave = true;
	m_LeftPlayerSkeleton->setAnimation(GetAnimationNameById(pLeftData->mRoleShapeID,pLeftData->mRoleLeaveAnimationID).c_str(),false);
	m_MidPlayerSkeleton->setAnimation(GetAnimationNameById(pMidData->mRoleShapeID,pMidData->mRoleLeaveAnimationID).c_str(),false);
	m_RightPlayerSkeleton->setAnimation(GetAnimationNameById(pRightData->mRoleShapeID,pRightData->mRoleLeaveAnimationID).c_str(),false);
}

void SelectRoleWindow::OnTurnRightEventHandler()
{
	if (m_PlayerIndex-1<1)
		m_PlayerIndex = m_PlayerCount;
	else
		m_PlayerIndex--;
	OnPlayLeaveAnimation();
}

void SelectRoleWindow::OnPlayEnterAnimation()
{
	
	IsBeginEnter = true;
	m_LeftPlayerSkeleton->setAnimation(GetAnimationNameById(pLeftData->mRoleShapeID,pLeftData->mRoleEntranceAnimationID).c_str(),false);
	m_MidPlayerSkeleton->setAnimation(GetAnimationNameById(pMidData->mRoleShapeID,pMidData->mRoleEntranceAnimationID).c_str(),false);
	m_RightPlayerSkeleton->setAnimation(GetAnimationNameById(pRightData->mRoleShapeID,pRightData->mRoleEntranceAnimationID).c_str(),false);

}

/*
	EditBox 相关
*/
/*
void SelectRoleWindow::keyboardWillShow(cocos2d::CCIMEKeyboardNotificationInfo& info) 
{ 
	pRootNode->setPositionY(300); 
	pEditBox->setPositionY(pRootNode->getPositionY()+140);   

} 
void SelectRoleWindow::keyboardDidShow(cocos2d::CCIMEKeyboardNotificationInfo& info) 
{ 
	int a = 0;
} 
void SelectRoleWindow::keyboardWillHide(cocos2d::CCIMEKeyboardNotificationInfo& info) 
{ 
	pRootNode->setPositionY(0); 
	pEditBox->setPositionY(pRootNode->getPositionY()+140); 
} 
void SelectRoleWindow::keyboardDidHide(cocos2d::CCIMEKeyboardNotificationInfo& info) 
{ 
	int a = 0;
}*/

void SelectRoleWindow::editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox)
{
	m_IsKeyBoard = true;
}
void SelectRoleWindow::editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox)
{

}
void SelectRoleWindow::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text)
{

}
void SelectRoleWindow::editBoxReturn(cocos2d::extension::CCEditBox* editBox)
{
	m_IsKeyBoard = false;
}