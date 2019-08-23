////////////////////////////////////////////////////////////////
//Name:	 AutoScrollLabelManager
//Auchor: 	xiaobo.wu
//Func:	 自动滚动公告管理器
//Maintainer: 	xiaobo.wu
//date:   2013/11/18
////////////////////////////////////////////////////////////////
#include "../include/AutoScrollLabelManager.h"
#include "../include/AnnouncementDataManager.h"
#include "../include/NFControlsManager.h"
#include "../include/CCRectClipNode.h"


 
 
AutoScrollLabelManager::AutoScrollLabelManager()
{ 
	m_nNoticeStyleID=0;						//管理CSS Type ID
	m_snoticeContent="";					 
	m_vScrollLabelVec.clear();
	m_pAnnnouncementData=NULL;		
	m_fSingleDurationTime=0.0f;
	m_screenMidHight=0.0f;
	m_screenMidWidth=0.0f;
	m_fNoticeStringWidth=0.0f;
	m_fTotalScrollLengh=0.0f;
	m_TargetPosition=CCPointZero;
	m_nLabelIndex=0;
	m_nRepeatCount=0;
	m_bIsValid=true; 
	m_pParentNode=NULL;
	m_pRectClipRootNode=NULL;

}

AutoScrollLabelManager::~AutoScrollLabelManager()
{
	Destroy();
}


AutoScrollLabelManager * AutoScrollLabelManager::CreateAutoScrollLabelManager(cocos2d::CCNode * parentNode,int noticeStyleID,std::string noticeContent)
{
	AutoScrollLabelManager * pAutoScrollLabelManager=new AutoScrollLabelManager();
	if(pAutoScrollLabelManager&&pAutoScrollLabelManager->InitAutoScrollLabelManager(parentNode,noticeStyleID,noticeContent))
	{
		return pAutoScrollLabelManager;
	}
	if(pAutoScrollLabelManager!=NULL)
	{
		delete pAutoScrollLabelManager;
		pAutoScrollLabelManager=NULL;
	}
	return NULL;
}

bool AutoScrollLabelManager::InitAutoScrollLabelManager(cocos2d::CCNode * parentNode,int noticeStyeID,std::string noticeContent)
{    
	m_pAnnnouncementData=AnnouncementDataManager::get_instance2()->GetAnnouncementDataByID(noticeStyeID);
	if(m_pAnnnouncementData!=NULL&&!noticeContent.empty()&&parentNode)
	{
		m_screenMidHight=DOTATribeApp::get_instance2()->GetAppHeight()*1.0f/2;
		m_screenMidWidth=DOTATribeApp::get_instance2()->GetAppWidth()*1.0f/2;
		m_pParentNode=parentNode;
		m_nNoticeStyleID=noticeStyeID;
		m_snoticeContent=noticeContent;
		m_nRepeatCount=m_pAnnnouncementData->announcementRepeatCount;
		InitAutoRectClipNode();
		StartSingleDelayUnit();
		return true;
	}
	return false;
}

cocos2d::CCPoint  AutoScrollLabelManager::GetBackGroundImagePos()
{
	if(m_pAnnnouncementData!=NULL)
	{
		return ccp(m_screenMidWidth,m_screenMidHight+m_pAnnnouncementData->announcementVisiableY);
	}
	return CCPointZero;
}


 
void AutoScrollLabelManager::StartSingleDelayUnit()
{  
	m_nLabelIndex++;
	cocos2d::CCSingleLineLabelTTF * m_pNoticeLabel=(cocos2d::CCSingleLineLabelTTF *)CCSingleLineLabelTTF::create();
	m_pNoticeLabel->setAnchorPoint(ccp(0.0f,0.5f));
	m_pNoticeLabel->setString(m_snoticeContent.c_str());
	m_vScrollLabelVec.push_back(m_pNoticeLabel);
	/*
	设置Label的FontStyle
	*/
	NFC_setLabelByFontStyleID(m_pNoticeLabel,m_pAnnnouncementData->announcementFontStyleID);
	if(m_fNoticeStringWidth==0.0f)
	{
		m_fNoticeStringWidth=m_pNoticeLabel->getContentSize().width;
		m_fTotalScrollLengh=m_fNoticeStringWidth+m_pAnnnouncementData->announcementVisiableRightX-m_pAnnnouncementData->announcementVisiableLeftX;
	} 
	m_pNoticeLabel->setPosition(ccp(m_screenMidWidth+m_pAnnnouncementData->announcementVisiableRightX,m_pAnnnouncementData->announcementVisiableY+m_screenMidHight));
	m_TargetPosition=ccp(m_screenMidWidth+m_pAnnnouncementData->announcementVisiableLeftX-m_fNoticeStringWidth,m_screenMidHight+m_pAnnnouncementData->announcementVisiableY);
	m_fSingleDurationTime=m_fTotalScrollLengh/m_pAnnnouncementData->announcemenrScrollSpeed; 
	cocos2d::CCMoveTo * m_pMoveToAction=cocos2d::CCMoveTo::create(m_fSingleDurationTime,m_TargetPosition);
	CallFuncAction    * m_pCallFunctionAction=CallFuncAction::create(_AUTOSCROLL_SCROLL_DID_EVENT_TYPE_,this,m_pNoticeLabel);
	cocos2d::CCActionInterval * m_pSequenceAction=cocos2d::CCSequence::createWithTwoActions(m_pMoveToAction,m_pCallFunctionAction);
	m_pNoticeLabel->runAction(m_pSequenceAction); 
	m_pRectClipRootNode->addChild(m_pNoticeLabel);
	 
}
 

void	AutoScrollLabelManager::EndScrollManager()
{  
	 SetValid(false);
	 Destroy();
}


void   AutoScrollLabelManager::ClearPreScrollLabel()
{ 
	//to do 
}


/*
创建自动裁剪根结点
*/
void AutoScrollLabelManager::InitAutoRectClipNode()
{ 
	if(m_pRectClipRootNode==NULL)
	{
		CCRect drawRect=CCRectMake(m_screenMidWidth+m_pAnnnouncementData->announcementVisiableLeftX,0,m_pAnnnouncementData->announcementVisiableRightX-m_pAnnnouncementData->announcementVisiableLeftX,2*m_screenMidWidth);
		m_pRectClipRootNode=CCRectClipNode::create(drawRect);
		if(m_pRectClipRootNode!=NULL)
		{ 
			m_pParentNode->addChild(m_pRectClipRootNode,1);
		}
	}
}
/*
销毁自动裁剪根结点
*/
void AutoScrollLabelManager::DestroyAutoRectClipNode()
{
	if(m_pRectClipRootNode!=NULL)
	{
		m_pRectClipRootNode->stopAllActions();
		m_pRectClipRootNode->removeAllChildrenWithCleanup(true);
		m_pRectClipRootNode->removeFromParentAndCleanup(true);
		m_pRectClipRootNode=NULL;
	}
}



void  AutoScrollLabelManager::CallFunctionHandler(int eventType,void * attachParam)
{
	switch(eventType)
	{
	case _AUTOSCROLL_SCROLL_DID_EVENT_TYPE_:
		{
			cocos2d::CCSingleLineLabelTTF * pAttachParam=(cocos2d::CCSingleLineLabelTTF *)attachParam;
			if(pAttachParam!=NULL)
			{
				pAttachParam->stopAllActions();
				pAttachParam->setVisible(false);
			}
			if(m_nLabelIndex<m_nRepeatCount)	
			{ 
			    if(m_pAnnnouncementData->announcementIntervalTime==0.0f)
				{
					StartSingleDelayUnit();
					break;
				}
				else
				{
					cocos2d::CCDelayTime * m_pDelayInter=cocos2d::CCDelayTime::create(m_pAnnnouncementData->announcementIntervalTime);
					CallFuncAction    *  m_pCallFunctionAction=CallFuncAction::create(_AUTOSCROLL_INNNAL_TIME_DID_EVENT_TYPE_,this);
					cocos2d::CCActionInterval * m_pSequenceAction=cocos2d::CCSequence::createWithTwoActions(m_pDelayInter,m_pCallFunctionAction);
					m_pRectClipRootNode->runAction(m_pSequenceAction); 
				}
				break; 
			}
			else
			{
				EndScrollManager();
			} 
			break;
		} 
	case _AUTOSCROLL_INNNAL_TIME_DID_EVENT_TYPE_:
		{
			if(m_nLabelIndex<m_nRepeatCount)
			{
				 StartSingleDelayUnit();
			}
			else
			{
				EndScrollManager();
			}
			break;
		}
	default:
		break;
	}
}

void   AutoScrollLabelManager::Destroy()
{ 
	/*
	 清空管理器中的所有label
	*/
	size_t labelCount=m_vScrollLabelVec.size();
	for(size_t subLabelIndex=0;subLabelIndex<labelCount;subLabelIndex++)
	{ 
		m_vScrollLabelVec.at(subLabelIndex)->stopAllActions();
		m_vScrollLabelVec.at(subLabelIndex)->removeFromParentAndCleanup(true);
	}
	m_vScrollLabelVec.clear();
	DestroyAutoRectClipNode();
	if(m_pParentNode!=NULL)
	{
		m_pParentNode->stopAllActions();
		m_pParentNode=NULL;
	}
}


void  AutoScrollLabelManager::SetValid(bool isValid)
{
	m_bIsValid=isValid;
}

/*
获取管理器是否合法
*/
bool AutoScrollLabelManager::GetValid()
{
	return m_bIsValid;
}