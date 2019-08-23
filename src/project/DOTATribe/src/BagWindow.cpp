//Name:BagWindow.h
//Function:����
//Author:fangjun
//Date:20130902
#include <cocos2d.h>
#include <cocos-ext.h>
#include "../include/NFControlsManager.h"
#include "../include/BagWindow.h"
#include "../include/EventTyper.h"
#include "../include/CMenuItemSprite.h"
#include "../include/UIViewDataManger.h"
#include "../include/RoleInfoDataHandler.h"
#include "../include/LoggerSystem.h"
#include "../include/BagWindowDataHandler.h"
#include "../include/CPublicVarReader.h"
#include "../include/BagOtherObjectHandler.h"
#include "../include/CSelectedSprite.h"
#include "../include/EventSystem.h"
#include "../include/RoleEquipDataHandler.h"
#include "../include/BagEquipDataHandler.h"
#include "../include/SysLangDataManager.h"
#include "../include/IDStringDataManager.h"
#include "../include/GuideSystem.h"
#include "../include/CPublicVarReader.h"
#include "../include/HeroTechnologyPacket.h"
#include "../include/config_HomeWindow.h"
#include "../include/MessageBoxWindow.h"
#include "../include/HeroTechnologyDataHandler.h"
#include "../include/PESWindow.h"
#include "../include/ClientConstDataManager.h"
#include "../include/CCardsStarProgress.h"
#include "../include/EngineSystem.h"
#include "../include/ProfSystem.h"
#include "../include/FAnimationButton.h"
#include "../include/NetObjectTipsDataHandler.h"

using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;


BagWindow::BagWindow()
:m_pRoot(NULL)
,m_pLeftNode(NULL)
,m_pRightPage(NULL)
,m_iSubPageKind(pageObjectList)
,m_iSelectedTag(-1)
,m_pSelectedItem(NULL)
,m_iBtnFunction(-1)
,m_bChangedSelectTag(false)
,m_pSelectSubPage(NULL)
,m_iMaxComposeNum(0)
,m_iBackWindow(0)
{
	m_WindowType = _TYPED_WINDOW_BAGWINDOW_;
	m_bModelWindow = false;
}

BagWindow::~BagWindow()
{
	m_pRoot = NULL;
	m_pLeftNode = NULL;
	m_pRightPage = NULL;
	m_iSubPageKind = pageObjectList;
	m_pSelectedItem = NULL;
	m_pSelectSubPage = NULL;
	m_iMaxComposeNum = 0;
}

void BagWindow::_initLayout()
{
	m_pRoot=m_pRootNode;
	m_pRoot->setAnchorPoint(CCPointZero);
	m_pRoot->setPosition(CCPointZero);

	//������
	UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kBAGWINDOW, m_pRoot);
	//��ʾָ������Ʒ����ļ�ͷ
	NFC_showNode(mObjectGuideArrow, m_pRoot, false);
	NFC_showNode(mObjectGuideArrowLabel, m_pRoot, false);


	_mapMainPageBtn();

	//Ĭ��ѡ�����ҳ��
	_setSelectPage();

	//�����ص�
	m_pLeftNode = m_pRoot->getChildByTag(mLeftNode);

	//�Ҳ���ص�
	MaskNode * mn = (MaskNode *)m_pRoot->getChildByTag(mRightNodeMask);

	//��ʼ���Ҳ����
	_initRightPanel(mn);

	//��ʾ��������Ϣ
	_setMainPageInfo();

	//��ʾ�����Ϣ
	_initLeftPage();

	//��ʾ�Ҳ������Ϣ,��������pool����ʾ����
	_setRightPanelInfo();

	//Ĭ����ʾҳ��
	_setDefaultPageAndItem(m_iSelectedTag);

}

void BagWindow::_initRightPanel(MaskNode * node)
{
	assert(node);

	const UIViewData & dd = node->GetViewData();
	//�����Ҳ����
	m_pRightPage = CPageScroll::create(CCSizeMake(dd.width_,dd.height_),NEWBAG_PAGENUM,this);
	m_pRightPage->setAnchorPoint(CCPointZero);
	m_pRightPage->setPosition(CCPointZero);

	assert(m_pRightPage);

	//����datahandler�еļ�¼ֵ
	BAGWINDOWDATAHANDLER->SetData(m_pRightPage, this);

	//��ʼ����������
	m_Pool.Init();

 	node->addChild(m_pRightPage);//node�Ϲ����Ҳ����

	//����ҳ��
	BoardPoolData * data = NULL;
	for(int i = 0;i < NEWBAG_ITEMCOUNT; ++i)
	{
		data = new BoardPoolData();
		data->tag = i;
		data->drawed = false;
		data->page = i / NEWBAG_NUMPERPAGE;
		m_Pool.Insert(data);
	}

	//Ԥ�ȹ�������ҳ��
	m_Pool.HangPageBoard(0, m_pRightPage->getContainer());
	//m_Pool.HangPageBoard(1, m_pRightPage->getContainer());

}

void BagWindow::_setText(int tag, cocos2d::CCNode * parent, const char * text)
{
	CCLabelTTF * ttf = (CCLabelTTF *)parent->getChildByTag(tag);
	ttf->setString(text);
}

void BagWindow::_setText(int tag, cocos2d::CCNode * parent, int num)
{
	char temp[128] = {0};
	sprintf(temp, "%d", num);
	_setText(tag, parent, temp);
}

void BagWindow::_setTexture(int tag,  cocos2d::CCNode * parent, const char * picpath)
{
	CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage(picpath);
	CCSprite * sp = (CCSprite *)parent->getChildByTag(tag);
	if(texture)
	{
		sp->setProperty("File",picpath);
		sp->setVisible(true);
	}

}


void BagWindow::_enableBtn(int tag, cocos2d::CCNode * parent, bool enable)
{
	CCMenu * menu = (CCMenu *)parent->getChildByTag(tag);
	CCMenuItem * item = (CCMenuItem *)menu->getChildByTag(tag);
	item->setEnabled(enable);
}

void BagWindow::_setVisible(int tag, cocos2d::CCNode * parent, bool visible)
{
	CCNode * node = parent->getChildByTag(tag);
	node->setVisible(visible);
}

cocos2d::CCMenuItem * BagWindow::_mapBtnWithTag(int tag, cocos2d::CCNode * parent, CCObject *rec, SEL_MenuHandler selector)
{
	CCMenu * menu = (CCMenu *)parent->getChildByTag(tag);
	CCMenuItem * item = (CCMenuItem *)menu->getChildByTag(0);
	item->setTag(tag);
	item->setTarget(rec, selector);
	return item;
}

void BagWindow::_mapMainPageBtn()
{
	CCMenu * menu = NULL;
	CMenuItemSprite * item = NULL;
	FAnimationButton * button = NULL;

	//��Ʒ�б�
	menu = (CCMenu *)m_pRoot->getChildByTag(mObjectListBtn);
	button = (FAnimationButton *)menu->getChildByTag(0);
	button->setTag(mObjectListBtn);
	button->setIDX(mObjectListBtn);
	button->setTarget(this, menu_selector(BagWindow::On_MainPage_Btn_Click));
	FAPriorityMenu * fmenu = (FAPriorityMenu *)menu;
	fmenu->SetTreatAsTabMenu(true);
	//��Ʒ�ϳ�
	menu = (CCMenu *)m_pRoot->getChildByTag(mComposeListBtn);
	button = (FAnimationButton *)menu->getChildByTag(0);
	button->setTag(mComposeListBtn);
	button->setIDX(mComposeListBtn);
	button->setTarget(this, menu_selector(BagWindow::On_MainPage_Btn_Click));
	fmenu = (FAPriorityMenu *)menu;
	fmenu->SetTreatAsTabMenu(true);

	//�رհ�ť
	menu = (CCMenu *)m_pRoot->getChildByTag(mCloseBtn);
	item = (CMenuItemSprite *)menu->getChildByTag(0);
	item->setTag(mCloseBtn);
	item->setIDX(mCloseBtn);
	item->setTarget(this, menu_selector(BagWindow::On_Close_Window));

}

void BagWindow::_refreshDrawInfoData(int bagType, int tag, int num)
{
	if(m_iSubPageKind == pageObjectList)
	{
		if(bagType == BAG_ITEM)
		{
			//ˢ����Ʒ
			if(num > 0)
			{//˵�������Ʒ���������ˣ�����������Ʒ
				BagOtherObject * boo = BAGOTHEROBJECTHANDLER->m_vecList[tag];
				int size = BAGOTHEROBJECTHANDLER->m_vecList.size();//0--size-1�Ǿ���Ʒ��size-1������Ʒ;;//���������Ʒ�϶�����Ʒ�б���������tag��size-1���
				if(tag >= size-1)//��ʵ����==�����˴�����ʡ�Զ����Ƿ�������Ʒ���жϣ�ֱ�����ü���
				{//����Ʒ
					InfoPoolData * data = m_Pool.info_pool_data[tag];
					data->itemcount = boo->itemcount_;
					data->enhancelevel = 0;
					data->quality = boo->template_->quality_;
					data->icon = boo->template_->iconId_;
					data->level = 0;
					data->infoType = InfoPoolData::INFO_HAS;
					data->drawed = false;
				}
				else
				{//�ص���������
					InfoPoolData * data = m_Pool.info_pool_data[tag];
					data->itemcount = boo->itemcount_;
					data->drawed = false;
				}
			}
			else if(num == 0)
			{//˵�������Ʒ��ʧ
				//BagOtherObject * boo = BAGOTHEROBJECTHANDLER->m_vecList[tag];
				int size = BAGOTHEROBJECTHANDLER->m_vecList.size();
				InfoPoolData * data = NULL;
				InfoPoolData * nextdata = NULL;
				for(int i = tag; i < size; ++i)
				{
					data = m_Pool.info_pool_data[i];
					nextdata = m_Pool.info_pool_data[i + 1];
					data->itemcount = nextdata->itemcount;
					data->enhancelevel = nextdata->enhancelevel;
					data->quality = nextdata->quality;
					data->icon = nextdata->icon;
					data->infoType = nextdata->infoType;
					data->level = nextdata->level;
					data->drawed = false;
				}
				data = m_Pool.info_pool_data[size];//��Ϊtag--size֮��ı���ǰ�ƶ���һλ����ô��sizeλ���ճ�
				data->infoType = InfoPoolData::INFO_EMPTY;
				data->drawed = false;

// 				if(size > 0)
// 				{
// 					if(m_Pool.info_pool_data[tag]->infoType != InfoPoolData::INFO_HAS)
// 						m_iSelectedTag = 0;
// 				}
// 				else
// 					m_iSelectedTag = -1;
				m_iSelectedTag = -1;
			}
		}

	}
	else if(m_iSubPageKind == pageComposeList)
	{
		if(bagType == BAG_ITEM)
		{
			//ˢ����Ʒ
			if(num > 0)
			{//˵�������Ʒ���������ˣ�����������Ʒ;;130908�������ֿ������輴��
				BagOtherObject * boo = BAGOTHEROBJECTHANDLER->m_vecList[tag];
				int otype = boo->template_->type_;
				if(otype == kOBJECTCOMPOSE || otype == kOBJECTRECIPE)
				{
					int idx = BAGOTHEROBJECTHANDLER->getIndexFromCanComposeList(tag, true);//���ڶ�λ�ϳ��б�����Ʒ��λ��
					InfoPoolData * data = m_Pool.info_pool_data[idx];
					data->itemcount = boo->itemcount_;
					data->enhancelevel = 0;
					data->quality = boo->template_->quality_;
					data->icon = boo->template_->iconId_;
					data->level = 0;
					data->infoType = InfoPoolData::INFO_HAS;
					data->drawed = false;
				}

			}
			else if(num == 0)
			{//˵�������Ʒ��ʧ
				//BagOtherObject * boo = BAGOTHEROBJECTHANDLER->m_vecList[tag];
				int idx = BAGOTHEROBJECTHANDLER->getIndexFromCanComposeList(tag, false);//��λ��ɾ������Ʒ�ںϳ��б��е�λ��//���Ϊ-1�Ļ���˵��tag֮ǰ�ı�����Ʒ��û�пɺϳɵ���Ʒ����ô֮ǰ
				int size = BAGOTHEROBJECTHANDLER->getBagObjectCanComposeNum();
				InfoPoolData * data = NULL;
				InfoPoolData * nextdata = NULL;
				for(int i = idx; i < size; ++i)
				{
					data = m_Pool.info_pool_data[i];
					nextdata = m_Pool.info_pool_data[i + 1];
					data->itemcount = nextdata->itemcount;
					data->enhancelevel = nextdata->enhancelevel;
					data->quality = nextdata->quality;
					data->icon = nextdata->icon;
					data->level = nextdata->level;
					data->infoType = nextdata->infoType;
					data->drawed = false;
				}
				data = m_Pool.info_pool_data[size];//��Ϊtag--size֮��ı���ǰ�ƶ���һλ����ô��sizeλ���ճ�
				data->infoType = InfoPoolData::INFO_EMPTY;
				data->drawed = false;

// 				if(size > 0)
// 				{
// 					if(m_Pool.info_pool_data[tag]->infoType != InfoPoolData::INFO_HAS)
// 						m_iSelectedTag = 0;
// 				}
// 				else
// 					m_iSelectedTag = -1;
				m_iSelectedTag = -1;
			}
		}
		
	}
	
	m_Pool.all_info_drawed = false;
	m_bChangedSelectTag = true;

	m_Pool.HangPageInfo(m_iSelectedTag / NEWBAG_NUMPERPAGE, m_pRightPage->getContainer());

}

void BagWindow::_setSelectPage()
{
	int n = m_iSubPageKind - pageObjectList;
	CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(mObjectListBtn + 2 * n);
	m_pSelectSubPage = (CCMenuItemSprite *)menu->getChildByTag(mObjectListBtn + 2 * n);
	m_pSelectSubPage->selected(true);
}


void BagWindow::_initLeftPage()
{
	if(pageObjectList == m_iSubPageKind)
	{
		if(m_pLeftNode)
			m_pLeftNode->removeAllChildrenWithCleanup(true);
		else
			return;
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kBAGWINDOWOBJECTLIST, m_pLeftNode);
		//�󶨰�ť
		_mapBtnWithTag(oSaleBtn, m_pLeftNode, this, menu_selector(BagWindow::On_LeftPage_Btn_Click));
		_mapBtnWithTag(oUseBtn, m_pLeftNode, this, menu_selector(BagWindow::On_LeftPage_Btn_Click));
		//��ʾָ����ͷ
		if(ROLEINFODATAHANDLER->m_pRIData->level_ <= BAG_GUIDE_USE_LEVEL)
		{
			cocos2d::extension::CCSkeletonAnimation * arrow = NFC_createGuideArrow();
			MaskNode * arrowParent = (MaskNode *)m_pLeftNode->getChildByTag(oGuideArrow);
			const UIViewData & ud = arrowParent->GetViewData();
			arrow->setAnchorPoint(ccp(ud.anchorx_, ud.anchory_));
			arrowParent->addChild(arrow, 100, 0);
			arrow->setVisible(false);
		}

	}
	else if(pageComposeList == m_iSubPageKind)
	{
		if(m_pLeftNode)
			m_pLeftNode->removeAllChildrenWithCleanup(true);
		else
			return;
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kBAGWINDOWCOMPOSELIST, m_pLeftNode);
		//�󶨰�ť
		//tips
		//_mapBtnWithTag(cQuality, m_pLeftNode, this, menu_selector(BagWindow::On_ObjectTips_Click));//�ϳ�Ŀ����
		//_mapBtnWithTag(cNeedQuality1, m_pLeftNode, this, menu_selector(BagWindow::On_ObjectTips_Click));//������1
		//_mapBtnWithTag(cNeedQuality2, m_pLeftNode, this, menu_selector(BagWindow::On_ObjectTips_Click));//������2
		//_mapBtnWithTag(cNeedQuality3, m_pLeftNode, this, menu_selector(BagWindow::On_ObjectTips_Click));//������3
		//_mapBtnWithTag(cNeedQuality4, m_pLeftNode, this, menu_selector(BagWindow::On_ObjectTips_Click));//������4
		_bindSelectorForTouchSprite(cQuality);
		_bindSelectorForTouchSprite(cNeedQuality1);
		_bindSelectorForTouchSprite(cNeedQuality2);
		_bindSelectorForTouchSprite(cNeedQuality3);
		_bindSelectorForTouchSprite(cNeedQuality4);
		//�ϳ�
		_mapBtnWithTag(cComposeBtn, m_pLeftNode, this, menu_selector(BagWindow::On_LeftPage_Btn_Click));

	}
	
}

void BagWindow::_bindSelectorForTouchSprite(int signID)
{
	DTAwardBoard * pTouchSprite=(DTAwardBoard *)m_pLeftNode->getChildByTag(signID);
	if(pTouchSprite!=NULL)
	{
		pTouchSprite->setIDX(signID);
		pTouchSprite->setTarget(this,menu_selector(BagWindow::On_ObjectTips_Click));
	}
} 

void BagWindow::_setMainPageInfo()
{
	//���ý�Ǯ\��ʯ
	this->refreshUIData();
}


void BagWindow::_setLeftPageInfo(int selecttag)
{
	//ͨ��ѡ�е�idx��ʾ��Ӧ��Ϣ
	if(m_iSelectedTag < 0)
		return;

	m_pLeftNode->setVisible(true);

	if(m_iSubPageKind == pageObjectList)
	{
		_refreshObjectInfo(selecttag);
	}
	else if(m_iSubPageKind == pageComposeList)
	{
		_refreshComposeInfo(selecttag);
	}

}


void BagWindow::_refreshObjectInfo(int selecttag)
{
	InfoPoolData * data = m_Pool.info_pool_data[selecttag];
	if(data->infoType == InfoPoolData::INFO_HAS)
	{
		cout<<"select is "<<selecttag<<":"<<"has"<<endl;
		BagOtherObject * boo = BAGOTHEROBJECTHANDLER->m_vecList[selecttag];
		//����
		_setText(oName, m_pLeftNode, boo->template_->name_.c_str());
		//�Ǽ�
		CCardsStarProgress * star = (CCardsStarProgress *)m_pLeftNode->getChildByTag(oStar);
		star->SetCurcount(boo->template_->quality_ + 1);
		//ʹ�õȼ�
		_setText(oLevelValue, m_pLeftNode, boo->template_->level_);
		//�۸�
		if(boo->template_->price_ > 0)
		{
			_setText(oPriceValue, m_pLeftNode, boo->template_->price_);
			_setVisible(oGoldIcon, m_pLeftNode, true);
		}
		else
		{
			std::string nosale = SysLangDataManager::get_instance2()->GetSysLangById(552);
			_setText(oPriceValue, m_pLeftNode, nosale.c_str());
			_setVisible(oGoldIcon, m_pLeftNode, false);
		}
		//����
		_setText(oDes, m_pLeftNode, boo->template_->description_.c_str());
		//��ť
		if(boo->template_->canUse_)
		{
			_enableBtn(oUseBtn, m_pLeftNode, true);
			if(m_pLeftNode->getChildByTag(oGuideArrow)->getChildByTag(0) != NULL)
			{
				m_pLeftNode->getChildByTag(oGuideArrow)->getChildByTag(0)->setVisible(true);
			}
		}
		else
		{
			_enableBtn(oUseBtn, m_pLeftNode, false);
			if(m_pLeftNode->getChildByTag(oGuideArrow)->getChildByTag(0) != NULL)
			{
				m_pLeftNode->getChildByTag(oGuideArrow)->getChildByTag(0)->setVisible(false);
			}
		}
		boo->template_->price_ > 0 ? _enableBtn(oSaleBtn, m_pLeftNode, true) : _enableBtn(oSaleBtn, m_pLeftNode, false);		
	}
	else if(data->infoType == InfoPoolData::INFO_EMPTY)
	{
		cout<<"select is "<<selecttag<<":"<<"empty"<<endl;
		_enableBtn(oUseBtn, m_pLeftNode, false);
		_enableBtn(oSaleBtn, m_pLeftNode, false);
	}
	else if(data->infoType == InfoPoolData::INFO_LOCK)
	{
		cout<<"select is "<<selecttag<<":"<<"lock"<<endl;
		_enableBtn(oUseBtn, m_pLeftNode, false);
		_enableBtn(oSaleBtn, m_pLeftNode, false);
	}
}

void BagWindow::_refreshComposeInfo(int selecttag)
{
	CCMenu * menu = NULL;
	CMenuItemSprite * item = NULL;
	CCSprite * picsp = NULL;
	InfoPoolData * data = m_Pool.info_pool_data[selecttag];
	if(data->infoType == InfoPoolData::INFO_HAS)
	{
		cout<<"select is "<<selecttag<<":"<<"has"<<endl;
		BagOtherObject * boo = BAGOTHEROBJECTHANDLER->getBagObjectByCanIndex(selecttag);
		//�ϳ���Ʒ����
		_setText(cName, m_pLeftNode, boo->composeDetail_->destObject_->name_.c_str());
		//���úϳ���������ͼ��ͼ��
		if(boo->composeDetail_->destObject_->catogory_ == kBAGOBJECT)//�ϳ���Ʒ
		{
			ObjectTemplate * ot = (ObjectTemplate *)boo->composeDetail_->destObject_;
			DTAwardBoard* pic = (DTAwardBoard*)m_pLeftNode->getChildByTag(cQuality);
			pic->ChangeObject(ot->quality_,ot->iconId_);
			pic->setContentScale(1);
			//string ico = RESOURCEDAIDMANAGER->getDataByID(ot->iconId_);//��Ʒͼ��
			//unsigned char quality = ot->quality_;
			//std::string qua = varConfig::getCardBGFilePath(quality);//����ͼ����ɫ
			////����������ɫ
			//menu = (CCMenu *)m_pLeftNode->getChildByTag(cQuality);
			//item = (CMenuItemSprite *)menu->getChildByTag(cQuality);
			//picsp = CCSprite::create();
			//picsp->setProperty("File",qua);
			//item->setNormalImage(picsp);
			//picsp = CCSprite::create();
			//picsp->setProperty("File",qua);
			//item->setSelectedImage(picsp);
			//������Ʒͼ
			//_setTexture(cIcon, m_pLeftNode, ico.c_str());
			//CCSprite * spicon = (CCSprite *)m_pLeftNode->getChildByTag(cIcon);
			//spicon->setScale(1);
		}
		else if(boo->composeDetail_->destObject_->catogory_ == kBAGEQUIP)//�ϳ�װ��
		{
			EquipTemplate * et = (EquipTemplate *)boo->composeDetail_->destObject_;

			DTAwardBoard* pic = (DTAwardBoard*)m_pLeftNode->getChildByTag(cQuality);
			pic->ChangeObject(et->quality_,et->iconId_);
			pic->setContentScale(1);

			//string ico = RESOURCEDAIDMANAGER->getDataByID(et->iconId_);//��Ʒͼ��
			//unsigned char quality = et->quality_;
			//std::string qua = varConfig::getCardBGFilePath(quality);//����ͼ����ɫ
			////����������ɫ
			//CCMenu * menu = (CCMenu *)m_pLeftNode->getChildByTag(cQuality);
			//CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(cQuality);
			//CCSprite * nor = CCSprite::create();
			//nor->setProperty("File",qua);
			//CCSprite * sel = CCSprite::create();
			//sel->setProperty("File",qua);
			//item->setNormalImage(nor);
			//item->setSelectedImage(sel);
			////������Ʒͼ
			//_setTexture(cIcon, m_pLeftNode, ico.c_str());
			//CCSprite * spicon = (CCSprite *)m_pLeftNode->getChildByTag(cIcon);
			//spicon->setScale(1);
		}
		else if(boo->composeDetail_->destObject_->catogory_ == kBAGSKIN)//�ϳ�����
		{
			SkinTemplate * st = (SkinTemplate *)boo->composeDetail_->destObject_;
			DTAwardBoard* pic = (DTAwardBoard*)m_pLeftNode->getChildByTag(cQuality);
			pic->ChangeObject(st->quality_,st->iconid_[0]);
			pic->setContentScale((float)CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f);
			//string ico = RESOURCEDAIDMANAGER->getDataByID(st->iconid_[0]);//��Ʒͼ��
			//unsigned char quality = st->quality_;
			//std::string qua = varConfig::getCardBGFilePath(quality);//����ͼ����ɫ
			////����������ɫ
			//CCMenu * menu = (CCMenu *)m_pLeftNode->getChildByTag(cQuality);
			//CMenuItemSprite * item = (CMenuItemSprite *)menu->getChildByTag(cQuality);
			//CCSprite * nor = CCSprite::create();
			//nor->setProperty("File",qua);
			//CCSprite * sel = CCSprite::create();
			//sel->setProperty("File",qua);
			//item->setNormalImage(nor);
			//item->setSelectedImage(sel);
			//������Ʒͼ
			//_setTexture(cIcon, m_pLeftNode, ico.c_str());
			//CCSprite * spicon = (CCSprite *)m_pLeftNode->getChildByTag(cIcon);
			//spicon->setScale((float)CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_AVATAR_SCALE_TIMES) / 100.0f);
		}
		//���úϳ�������Ʒ
		int needObjectNum = boo->composeDetail_->needObjectList_.size();
		//��������
		ComposeDetail * cd = boo->composeDetail_;
		int minTmp = ~(1<<(sizeof(int) * 8 - 1));//�Ƚ����ɺϳ�����Ϊint�����ֵ
		//������Ʒ
		int i = 0;
		CCMenu * menu = NULL;
		CMenuItemSprite * item = NULL;
		CCSprite * picsp = NULL;
		for(; i < needObjectNum && i < 4; ++i)
		{
			if(cd->needObjectList_[i]->catogory_ == kBAGOBJECT)
			{
				ObjectTemplate * tmp = dynamic_cast<ObjectTemplate *>(cd->needObjectList_[i]);
				DTAwardBoard* pic = (DTAwardBoard*)m_pLeftNode->getChildByTag(cNeedQuality1 + i);
				//����ͼ
				//string qualityPic = varConfig::getCardBGFilePath(tmp->quality_);
				//menu = (CCMenu *)m_pLeftNode->getChildByTag(cNeedQuality1 + i);
				//item = (CMenuItemSprite *)menu->getChildByTag(cNeedQuality1 + i);
				//picsp = CCSprite::create();
				//picsp->setProperty("File",qualityPic.c_str());
				//item->setNormalImage(picsp);
				//picsp = CCSprite::create();
				//picsp->setProperty("File",qualityPic);
				//item->setSelectedImage(picsp);
				//_setVisible(cNeedQuality1 + i, m_pLeftNode, true);
				pic->setEnabled(true);
				pic->setVisible(true);
				//��Ʒͼ
				pic->ChangeObject(tmp->quality_,tmp->iconId_);
				//string oPic = RESOURCEDAIDMANAGER->getDataByID(tmp->iconId_);
				//_setTexture(cNeedIcon1 + i, m_pLeftNode, oPic.c_str());
				//_setVisible(cNeedIcon1 + i, m_pLeftNode, true);
				//������Ʒ����
				char txt[128];
				int needNum = cd->needObjectNumList_[i];
				int haveNum = BAGOTHEROBJECTHANDLER->getObjectCountByTemplateId(tmp->templateid_);
				sprintf(txt, "%d/%d", haveNum, needNum);
				haveNum >= needNum ? NFC_setLabelColor(cNeedValue1 + i, m_pLeftNode, color_BagNormal) : NFC_setLabelColor(cNeedValue1 + i, m_pLeftNode, color_BagRed);
				_setText(cNeedValue1 + i, m_pLeftNode, txt);
				_setVisible(cNeedValue1 + i, m_pLeftNode, true);
				//���ϳ���
				if(haveNum / needNum < minTmp)
					minTmp = haveNum / needNum;
			}
			else if(cd->needObjectList_[i]->catogory_ == kBAGEQUIP)
			{
				EquipTemplate * tmp = dynamic_cast<EquipTemplate *>(cd->needObjectList_[i]);
				DTAwardBoard* pic = (DTAwardBoard*)m_pLeftNode->getChildByTag(cNeedQuality1 + i);

				//string qualityPic = varConfig::getCardBGFilePath(tmp->quality_);
				//menu = (CCMenu *)m_pLeftNode->getChildByTag(cNeedQuality1 + i);
				//item = (CMenuItemSprite *)menu->getChildByTag(cNeedQuality1 + i);
				//picsp = CCSprite::create();
				//picsp->setProperty("File",qualityPic);
				//item->setNormalImage(picsp);
				//picsp = CCSprite::create();
				//picsp->setProperty("File",qualityPic);
				//item->setSelectedImage(picsp);
				//_setVisible(cNeedQuality1 + i, m_pLeftNode, true);
				pic->setEnabled(true);
				pic->setVisible(true);
				//��Ʒͼ
				pic->ChangeObject(tmp->quality_,tmp->iconId_);
				//string oPic = RESOURCEDAIDMANAGER->getDataByID(tmp->iconId_);
				//_setTexture(cNeedIcon1 + i, m_pLeftNode, oPic.c_str());
				//_setVisible(cNeedIcon1 + i, m_pLeftNode, true);

				//������Ʒ����
				char txt[128];
				int needNum = cd->needObjectNumList_[i];
				int haveNum = BAGEQUIPDATAHANDLER->getObjectCountByTemplateId(tmp->templateid_);
				sprintf(txt, "%d/%d", haveNum, needNum);
				_setText(cNeedValue1 + i, m_pLeftNode, txt);
				_setVisible(cNeedValue1 + i, m_pLeftNode, true);
				//���ϳ���
				if(haveNum / needNum < minTmp)
					minTmp = haveNum / needNum;
			}
			else if(cd->needObjectList_[i]->catogory_ == kBAGSKIN)
			{
				SkinTemplate * tmp = dynamic_cast<SkinTemplate *>(cd->needObjectList_[i]);
				DTAwardBoard* pic = (DTAwardBoard*)m_pLeftNode->getChildByTag(cNeedQuality1 + i);
				pic->setEnabled(true);
				pic->setVisible(true);
				//string qualityPic = varConfig::getCardBGFilePath(tmp->quality_);
				//menu = (CCMenu *)m_pLeftNode->getChildByTag(cNeedQuality1 + i);
				//item = (CMenuItemSprite *)menu->getChildByTag(cNeedQuality1 + i);
				//picsp = CCSprite::create();
				//picsp->setProperty("File",qualityPic);
				//item->setNormalImage(picsp);
				//picsp = CCSprite::create();
				//picsp->setProperty("File",qualityPic);
				//item->setSelectedImage(picsp);
				//item->setEnabled(true);
				//_setVisible(cNeedQuality1 + i, m_pLeftNode, true);

				//��Ʒͼ	
				pic->ChangeObject(tmp->quality_,tmp->iconid_[0]);

				//string oPic = RESOURCEDAIDMANAGER->getDataByID(tmp->iconid_[0]);
				//_setTexture(cNeedIcon1 + i, m_pLeftNode, oPic.c_str());
				//_setVisible(cNeedIcon1 + i, m_pLeftNode, true);

				////������Ʒ����
				//char txt[128];
				//int needNum = cd->needObjectNumList_[i];
				//int haveNum = BAGSKINDATAHANDLER->getObjectCountByTemplateId(tmp->templateid_);
				//sprintf(txt, "%d/%d", haveNum, needNum);
				//_setText(cNeedValue1 + i, m_pLeftNode, txt);
				//_setVisible(cNeedValue1 + i, m_pLeftNode, true);
				////���ϳ���
				//if(haveNum / needNum < minTmp)
				//	minTmp = haveNum / needNum;
			}

		}
		//�������ɺϳ���
		this->m_iMaxComposeNum = minTmp;
		//���ʣ�µĸ��Ӳ���ʾ
		for(; i < 4; ++i)
		{
			DTAwardBoard* pic = (DTAwardBoard*)m_pLeftNode->getChildByTag(cNeedQuality1 + i);
			pic->setVisible(true);
			pic->setEnabled(false);
			//_setVisible(cNeedQuality1 + i, m_pLeftNode, true);
			//menu = (CCMenu *)m_pLeftNode->getChildByTag(cNeedQuality1 + i);
			//item = (CMenuItemSprite*)menu->getChildByTag(cNeedQuality1 + i);
			//picsp = CCSprite::create();
			//picsp->setProperty("File",m_Pool.empty_file);
			//item->setNormalImage(picsp);
			//picsp = CCSprite::create();
			//picsp->setProperty("File",m_Pool.empty_file);
			//item->setSelectedImage(picsp);
			//item->setEnabled(false);//���ܵ��
			pic->ChangeObject();
			_setVisible(cNeedValue1 + i, m_pLeftNode, false);
		}

		//�ϳɽ�Ǯ
		_setText(cCostValue, m_pLeftNode, boo->composeDetail_->costMoney_);

		//��ť
		if(ROLEINFODATAHANDLER->m_pRIData->money_ >= boo->composeDetail_->costMoney_ && m_iMaxComposeNum > 0)
		{
			_enableBtn(cComposeBtn, m_pLeftNode, true);
		}
		else
		{
			_enableBtn(cComposeBtn, m_pLeftNode, false);
		}
	}
	else if(data->infoType == InfoPoolData::INFO_EMPTY)
	{
		_enableBtn(cComposeBtn, m_pLeftNode, false);
	}
	else if(data->infoType == InfoPoolData::INFO_LOCK)
	{
		_enableBtn(cComposeBtn, m_pLeftNode, false);
	}
}

void BagWindow::refreshUIData()
{
	//ˢ�½�����Ϣ
	CCLabelTTF * ttf = (CCLabelTTF *)m_pRoot->getChildByTag(mJewelValue);
	char temp[128] = {0};
	sprintf(temp, "%d", ROLEINFODATAHANDLER->m_pRIData->jewels_);
	ttf->setString(temp);
	ttf = (CCLabelTTF *)m_pRoot->getChildByTag(mGoldValue);
	sprintf(temp, "%d", ROLEINFODATAHANDLER->m_pRIData->money_);
	ttf->setString(temp);
}

void BagWindow::_setRightPanelInfo()
{
	m_Pool.ClearInfoData();

	if(m_iSubPageKind == pageObjectList)
	{
		//������Ʒ�б�
		BAGOTHEROBJECTHANDLER->reorderBagObject();

		m_Pool.filltype = pageObjectList;//���Ϊ��Ʒ

		int all = NEWBAG_ITEMCOUNT;
		int hassize = BAGOTHEROBJECTHANDLER->m_vecList.size();
		int opensize = BAGOTHEROBJECTHANDLER->m_bagMaxCount;
		//int opensize = ROLEINFODATAHANDLER->m_pRIData->maxCount_;
		int emptysize = opensize - hassize;
		int lock = all - opensize;
		for(int i = 0; i < all; ++i)
		{
			InfoPoolData * data = new InfoPoolData();
			data->tag = i;
			data->page = i / NEWBAG_NUMPERPAGE;

			if(i < hassize)
			{
				BagOtherObject * boo = BAGOTHEROBJECTHANDLER->m_vecList[i];
				//data->itemid = -1;	//�˴�������itemid
				data->itemcount = boo->itemcount_;
				data->enhancelevel = 0;
				data->quality = boo->template_->quality_;
				data->icon = boo->template_->iconId_;
				data->level = 0;
				data->infoType = InfoPoolData::INFO_HAS;
			}
			else if(i < opensize)
			{
				data->infoType = InfoPoolData::INFO_EMPTY;
			}
			else
			{
				data->infoType = InfoPoolData::INFO_LOCK;
			}
			m_Pool.Insert(data);
		}
		
		//Ĭ��ѡ�е���Ʒ
		if(hassize > 0)
		{
			m_pLeftNode->setVisible(true);	

			m_iSelectedTag = 0;
		}
		else
		{
			m_pLeftNode->setVisible(false);
			m_iSelectedTag = -1;
		}
		m_Pool.HangPageInfo(0, m_pRightPage->getContainer());
	}
	else if(m_iSubPageKind == pageComposeList)
	{
		m_Pool.filltype = pageComposeList;//���Ϊ�ϳ�
		int all = NEWBAG_ITEMCOUNT;
		int hassize = BAGOTHEROBJECTHANDLER->getBagObjectCanComposeNum();
		int opensize = BAGOTHEROBJECTHANDLER->m_bagMaxCount;
		//int opensize = ROLEINFODATAHANDLER->m_pRIData->maxCount_;
		int emptysize = opensize - hassize;
		int lock = all - opensize;
		for(int i = 0; i < all; ++i)
		{
			InfoPoolData * data = new InfoPoolData();
			data->tag = i;
			data->page = i / NEWBAG_NUMPERPAGE;

			if(i < hassize)
			{
				BagOtherObject * boo = BAGOTHEROBJECTHANDLER->getBagObjectByCanIndex(i);
				//data->itemid = -1;	//�˴�������itemid
				data->itemcount = boo->itemcount_;
				data->enhancelevel = 0;
				data->quality = boo->template_->quality_;
				data->icon = boo->template_->iconId_;
				data->level = 0;
				data->infoType = InfoPoolData::INFO_HAS;
			}
			else if(i < opensize)
			{
				data->infoType = InfoPoolData::INFO_EMPTY;
			}
			else
			{
				data->infoType = InfoPoolData::INFO_LOCK;
			}
			m_Pool.Insert(data);
		}

		//Ĭ��ѡ�е���Ʒ
		if(hassize > 0)
		{
			m_pLeftNode->setVisible(true);

			//m_Pool.HangData(m_pRightPage->getContainer());
			m_iSelectedTag = 0;
		}
		else
		{
			m_pLeftNode->setVisible(false);
			m_iSelectedTag = -1;
		}
		m_Pool.HangPageInfo(0, m_pRightPage->getContainer());
	}

	m_bChangedSelectTag = true;
}

void BagWindow::_setMenuPage(int pageid)
{
	
}

void BagWindow::_setDefaultPageAndItem(int selectIdx)
{
	if(selectIdx >= 0)
	{
		PanelItem * node = (PanelItem *)m_pRightPage->getContainer()->getChildByTag(selectIdx);
		CCMenu * menu = (CCMenu *)node->getChildByTag(PanelItem::pQUALITY);
		CCMenuItemSprite * item = (CCMenuItemSprite *)menu->getChildByTag(selectIdx);
		if(m_pSelectedItem)
		{
			m_pSelectedItem->unselected();
		}
		item->selected(true);
		m_pSelectedItem = item;
		
		_setLeftPageInfo(m_iSelectedTag);

		changePage(selectIdx / NEWBAG_NUMPERPAGE);
		m_pRightPage->moveToPage(selectIdx / NEWBAG_NUMPERPAGE);

		m_pLeftNode->setVisible(true);
	}
	else
	{
		changePage(selectIdx / NEWBAG_NUMPERPAGE);
		m_pRightPage->moveToPage(selectIdx / NEWBAG_NUMPERPAGE);

		m_pLeftNode->setVisible(false);

		if(m_pSelectedItem)
			m_pSelectedItem->unselected();
		m_pSelectedItem = NULL;

	}
}

void BagWindow::On_MainPage_Btn_Click(cocos2d::CCObject * pSender)
{
	CCMenuItemSprite * item = (CCMenuItemSprite *)pSender;
	int idx = item->getTag();
	if(idx == mObjectListBtn)
	{//��Ʒ�б�
		if(m_iSubPageKind != pageObjectList)
		{
			int n = m_iSubPageKind - pageObjectList;
			m_iSubPageKind = pageObjectList;
			_initLeftPage();
			//�����Ҳ���Ϣ
			_setRightPanelInfo();

			m_pSelectSubPage->unselected();
			m_pSelectSubPage = item;
			
			NFC_showNode(mObjectGuideArrow, m_pRoot, false);
			NFC_showNode(mObjectGuideArrowLabel, m_pRoot, false);
		}
		m_pSelectSubPage->selected(true);
		
	}
	else if(idx == mComposeListBtn)
	{//�ϳ�
		if(m_iSubPageKind != pageComposeList)
		{
			int n = m_iSubPageKind - pageObjectList;
			m_iSubPageKind = pageComposeList;
			_initLeftPage();
			//�����Ҳ���Ϣ
			_setRightPanelInfo();

			m_pSelectSubPage->unselected();
			m_pSelectSubPage = item;
			
			if(ROLEINFODATAHANDLER->m_pRIData->level_ <= BAG_GUIDE_BACKOBJECT_LEVEL)
			{
				NFC_showNode(mObjectGuideArrow, m_pRoot, true);
				NFC_showNode(mObjectGuideArrowLabel, m_pRoot, true);
			}
			else
			{
				NFC_showNode(mObjectGuideArrow, m_pRoot, false);
				NFC_showNode(mObjectGuideArrowLabel, m_pRoot, false);
			}
		}
		m_pSelectSubPage->selected(true);

	}
	
}

void BagWindow::On_LeftPage_Btn_Click(cocos2d::CCObject * pSender)
{
	CCMenuItem * item = (CCMenuItem *)pSender;
	int tag = item->getTag();

	if(m_iSubPageKind == pageObjectList)
	{
		if(tag == oUseBtn)
		{
			if(m_iSelectedTag >= (int)BAGOTHEROBJECTHANDLER->m_vecList.size() || m_iSelectedTag < 0)
				return;
			m_iBtnFunction = functionUSE;
			BagOtherObject * boo = BAGOTHEROBJECTHANDLER->m_vecList[m_iSelectedTag];
			if(boo->template_->type_ != kOBJECTCOMPOSE && boo->template_->type_ != kOBJECTRECIPE)
			{//һ����Ʒ,ֱ��ʹ��
				if(boo->itemcount_ >= 10)
				{//����
					std::string maxnum = _to_event_param_(boo->itemcount_);
					EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_INPUTNUMWINDOW_, boo->template_->name_, maxnum);
				}
				else
				{
					Function_NumInputResult(1);
				}
			}
			else
			{	//�ɺϳɻ����䷽����Ҫ��ת���ϳɽ���
				BagOtherObject * boo = BAGOTHEROBJECTHANDLER->m_vecList[m_iSelectedTag];
				int _t = BAGOTHEROBJECTHANDLER->getIndexFromCanComposeList(m_iSelectedTag, true);
				CCMenu * menu = (CCMenu *)m_pRoot->getChildByTag(mComposeListBtn);
				CCMenuItemSprite * item = (CCMenuItemSprite *)menu->getChildByTag(mComposeListBtn);

				int n = m_iSubPageKind - pageObjectList;
				m_iSubPageKind = pageComposeList;
				_initLeftPage();
				//�����Ҳ���Ϣ
				_setRightPanelInfo();
				m_pSelectSubPage->unselected();
				m_pSelectSubPage = item;
				m_pSelectSubPage->selected(true);

				//��ʾ�ص���Ʒ����ļ�ͷ
				if(ROLEINFODATAHANDLER->m_pRIData->level_ <= BAG_GUIDE_BACKOBJECT_LEVEL)
				{
					NFC_showNode(mObjectGuideArrow, m_pRoot, true);
					NFC_showNode(mObjectGuideArrowLabel, m_pRoot, true);
				}
				else
				{
					NFC_showNode(mObjectGuideArrow, m_pRoot, false);
					NFC_showNode(mObjectGuideArrowLabel, m_pRoot, false);
				}

				//����ѡ�е���tag
				m_iSelectedTag = _t;
				m_bChangedSelectTag = true;				
			}
			
		}
		else if(tag == oSaleBtn)
		{
			if(m_iSelectedTag >= (int)BAGOTHEROBJECTHANDLER->m_vecList.size() || m_iSelectedTag < 0)
				return;
			m_iBtnFunction = functionSALE;

			BagOtherObject * boo = BAGOTHEROBJECTHANDLER->m_vecList[m_iSelectedTag];
			assert(boo);

			if(boo->template_->quality_ >= 3)
			{
				NFC_showMessageBox(kBAGSALEIMPORTANTOBJECT, SysLangDataManager::get_instance2()->GetSysLangById(686));
			}
			else
			{
				Function_ComfirmSaleImportant();
			}
		}
	}
	else if(m_iSubPageKind == pageComposeList)
	{
		if(tag == cComposeBtn)
		{
			if(this->m_iMaxComposeNum >= 10)
			{
				//��������
				BagOtherObject * boo = BAGOTHEROBJECTHANDLER->getBagObjectByCanIndex(m_iSelectedTag);
				std::string maxnum = _to_event_param_(this->m_iMaxComposeNum);
				EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_INPUTNUMWINDOW_, boo->template_->name_, maxnum);
			}
			else
			{
				//ֱ����Ӧ1����������
				Function_NumInputResult(1);
			}
		}
	}

}

void BagWindow::On_RightMenu_Click(cocos2d::CCObject * pSender)
{
	CCMenuItemSprite * item = (CCMenuItemSprite *)pSender;
	int tag = item->getTag();

	if(m_pRightPage->isTouchInArea() == false)
	{
		if(item == m_pSelectedItem)
			item->selected(true);
		else
			item->unselected();

		return;
	}

	//�жϸ���״̬
	InfoPoolData * data = m_Pool.info_pool_data[tag];

	if(m_iSelectedTag != tag)
	{
		if(data->infoType == InfoPoolData::INFO_HAS)
		{
			if(m_pSelectedItem)
				m_pSelectedItem->unselected();
			item->selected(true);
			m_pSelectedItem = item;
			m_iSelectedTag = tag;

			//�������ҳ����ʾ��Ϣ
			_setLeftPageInfo(m_iSelectedTag);
		}
		else
		{
			item->unselected();
			if(data->infoType == InfoPoolData::INFO_LOCK)
			{
				int bagType = 0;
				if(m_iSubPageKind == pageObjectList || m_iSubPageKind == pageComposeList)
				{
					bagType = BAG_ITEM;
				}
				BAGWINDOWDATAHANDLER->ToServerOpenLockBag(bagType, tag + 1);//1�Ǻͷ�����Э�̣����͵��Ƕ��ٸ�����
			}
		}
	}
	else
	{
		if(data->infoType == InfoPoolData::INFO_HAS)
			item->selected(true);
	}

}

void BagWindow::On_ObjectTips_Click(cocos2d::CCObject * pSender)
{
	CCMenuItemSprite * item = (CCMenuItemSprite *)pSender;
	BagOtherObject * boo = BAGOTHEROBJECTHANDLER->getBagObjectByCanIndex(m_iSelectedTag);
	ComposeDetail * cd = boo->composeDetail_;
	//CObjectTipsData * dd=new CObjectTipsData;
	int tag = item->getTag();
	if(tag == cQuality)
	{
		//Ŀ����
		if(boo->composeDetail_->destObject_->catogory_ == kBAGOBJECT)//�ϳ���Ʒ
		{
			ObjectTemplate * ot = (ObjectTemplate *)boo->composeDetail_->destObject_;
			NETOBJECTTIPSDATAHANDLER->m_pObjectTips->name = ot->name_;
			NETOBJECTTIPSDATAHANDLER->m_pObjectTips->level = ot->level_;
			NETOBJECTTIPSDATAHANDLER->m_pObjectTips->price = ot->price_;
			NETOBJECTTIPSDATAHANDLER->m_pObjectTips->description = ot->description_;
		}
		else if(boo->composeDetail_->destObject_->catogory_ == kBAGEQUIP)//�ϳ�װ��
		{
			EquipTemplate * et = (EquipTemplate *)boo->composeDetail_->destObject_;
			NETOBJECTTIPSDATAHANDLER->m_pObjectTips->name = et->name_;
			NETOBJECTTIPSDATAHANDLER->m_pObjectTips->level = et->level_;
			NETOBJECTTIPSDATAHANDLER->m_pObjectTips->price = et->price_;
			NETOBJECTTIPSDATAHANDLER->m_pObjectTips->description = et->description_;

		}
		else if(boo->composeDetail_->destObject_->catogory_ == kBAGSKIN)//�ϳ�����
		{
			SkinTemplate * st = (SkinTemplate *)boo->composeDetail_->destObject_;
			NETOBJECTTIPSDATAHANDLER->m_pObjectTips->name = st->name_;
			NETOBJECTTIPSDATAHANDLER->m_pObjectTips->level = st->level_;
			NETOBJECTTIPSDATAHANDLER->m_pObjectTips->price = st->price_;
			NETOBJECTTIPSDATAHANDLER->m_pObjectTips->description = st->description_;
		}
	}
	else
	{
		int desId = tag - cNeedQuality1;

		if(cd->needObjectList_[desId]->catogory_ == kBAGOBJECT)
		{
			ObjectTemplate * ot = dynamic_cast<ObjectTemplate *>(cd->needObjectList_[desId]);
			NETOBJECTTIPSDATAHANDLER->m_pObjectTips->name = ot->name_;
			NETOBJECTTIPSDATAHANDLER->m_pObjectTips->level = ot->level_;
			NETOBJECTTIPSDATAHANDLER->m_pObjectTips->price = ot->price_;
			NETOBJECTTIPSDATAHANDLER->m_pObjectTips->description = ot->description_;
		}
		else if(cd->needObjectList_[desId]->catogory_ == kBAGEQUIP)
		{
			EquipTemplate * et = dynamic_cast<EquipTemplate *>(cd->needObjectList_[desId]);
			NETOBJECTTIPSDATAHANDLER->m_pObjectTips->name = et->name_;
			NETOBJECTTIPSDATAHANDLER->m_pObjectTips->level = et->level_;
			NETOBJECTTIPSDATAHANDLER->m_pObjectTips->price = et->price_;
			NETOBJECTTIPSDATAHANDLER->m_pObjectTips->description = et->description_;
		}
		else if(cd->needObjectList_[desId]->catogory_ == kBAGSKIN)
		{
			SkinTemplate * et = dynamic_cast<SkinTemplate *>(cd->needObjectList_[desId]);
			NETOBJECTTIPSDATAHANDLER->m_pObjectTips->name = et->name_;
			NETOBJECTTIPSDATAHANDLER->m_pObjectTips->level = et->level_;
			NETOBJECTTIPSDATAHANDLER->m_pObjectTips->price = et->price_;
			NETOBJECTTIPSDATAHANDLER->m_pObjectTips->description = et->description_;
		}
	}
	NETOBJECTTIPSDATAHANDLER->m_pObjectTips->isSalebtn_ = false;
	NETOBJECTTIPSDATAHANDLER->m_pObjectTips->pEquip_ = NULL;
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_NETOBJECTTIPSWINDOW_,_to_event_param_(_ENUM_NETORCOMMONOBJECT_TYPE_));

}


bool BagWindow::Init()
{
	RegisterEvent(_TYPED_EVENT_SHOW_BAGWINDOW_);
	RegisterEvent(_TYPED_EVENT_HIDE_BAGWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_UPDATE_BAGWINDOW_, true);
	RegisterEvent(_TYPED_EVENT_REFRESH_UPDATEUI_, true);//ˢ�½�Ǯ��ʯ��

	RegisterEvent(_TYPED_EVENT_HIDE_INPUTNUMWINDOW_, true);//ע����������ʧ

	RegisterEvent(_TYPED_EVENT_BAGREFRESH_BAG_ITEM_, true);//ע�ᱳ����Ʒ����

	RegisterEvent(_TYPED_EVENT_BAG_OPENLOCK_SIZE_, true);//ע�ᱳ����������

	RegisterEvent(_TYPED_EVENT_REFRESH_BAGSALEIMPORTANTOBJECT_COMFIRM_, true);//ȷ����������Ʒ

	return IWindow::Init();
}


bool BagWindow::Load()
{
	do 
	{
		if (!IWindow::Load())
			break;

		_initLayout();//���ƽ���

		return true;
	} 
	while (false);

	return false;
}


void BagWindow::Tick()
{
	IWindow::Tick();

	if(m_pRightPage)
	{
		m_Pool.HangData(m_pRightPage->getContainer());
		//m_Pool.HangPage(m_pRightPage->getContainer());
	}

	if(m_bChangedSelectTag)
	{
		_setDefaultPageAndItem(m_iSelectedTag);
		m_bChangedSelectTag = false;
	}
}


void BagWindow::Destroy()
{
	m_iSubPageKind = pageObjectList;//�˴���Ϊ���´ν�����ʾ��һ��ҳ

	m_Pool.Destroy();

	m_iSelectedTag = -1;
	m_pSelectedItem = NULL;

	m_iBtnFunction = -1;

	m_bChangedSelectTag = false;

	m_iMaxComposeNum = 0;

	m_pRightPage=NULL;

	BAGWINDOWDATAHANDLER->HandleCloseBag();

	IWindow::Destroy();
}

void BagWindow::changePage(int idx)
{
	LOGGERSYSTEM->LogInfo("BagWindow::changePage:	%d",idx);

	CCLabelTTF * ttf = (CCLabelTTF *)m_pRoot->getChildByTag(mPageNumValue);
	char page[64] = {0};
	sprintf(page, "%d/%d", idx + 1, NEWBAG_PAGENUM);
	ttf->setString(page);

	if(idx == 0)
	{//����ͷ�û�
		NFC_setNodeVisable(mLeftArrowMove,m_pRoot,false);
		NFC_setNodeVisable(mLeftArrow,m_pRoot,true);
	}
	else
	{
		NFC_setNodeVisable(mLeftArrowMove,m_pRoot,true);
		NFC_setNodeVisable(mLeftArrow,m_pRoot,false);
	}

	if(idx == NEWBAG_PAGENUM - 1                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                )
	{//�Ҳ��ͷ�û�
		NFC_setNodeVisable(mRightArrowMove,m_pRoot,false);
		NFC_setNodeVisable(mRightArrow,m_pRoot,true);
	}
	else
	{
		NFC_setNodeVisable(mRightArrowMove,m_pRoot,true);
		NFC_setNodeVisable(mRightArrow,m_pRoot,false);
	}

	LOGGERSYSTEM->LogInfo("BagWindow::changepage End!!");
}

void BagWindow::cancelTipsLayer()
{

}

void BagWindow::OnEventHandler(int iEventType, std::list<std::string>& paramList)
{
	if (iEventType == _TYPED_EVENT_SHOW_BAGWINDOW_)
	{
		OnShowWindowEventHandler(paramList);
		//Fadein(IWINDOW_FADEIN_DURING);
	}
	else if (iEventType == _TYPED_EVENT_HIDE_BAGWINDOW_)
	{
		//Fadeout(IWINDOW_FADEOUT_DURING);
		Destroy();
	}
	else if(iEventType == _TYPED_EVENT_REFRESH_UPDATEUI_)
	{//��Ǯ��ʯ��ʾ
		OnRefreshWindowEventHandler(paramList);
	}
	else if(iEventType == _TYPED_EVENT_HIDE_INPUTNUMWINDOW_)
	{
		if (paramList.size()>=1)
		{
			std::list<std::string>::iterator it=paramList.begin();
			std::string str = *it;
			int num = 0;
			sscanf(str.c_str(), "%d", &num);
			//ȡ�������ݣ��������
			Function_NumInputResult(num);
		}
	}
	else if(iEventType == _TYPED_EVENT_BAGREFRESH_BAG_ITEM_)
	{
		if(paramList.size() >= 2)
		{
			std::list<std::string>::iterator it = paramList.begin();
			int bagType = 0;
			int tag = 0;
			int count = 0;
			std::string str = *it;
			sscanf(str.c_str(), "%d", &bagType);
			it++;
			str = *it;
			sscanf(str.c_str(), "%d", &tag);
			it++;
			str = *it;
			sscanf(str.c_str(), "%d", &count);
			_refreshDrawInfoData(bagType, tag, count);
		}
	}
	else if(iEventType == _TYPED_EVENT_BAG_OPENLOCK_SIZE_)
	{
		InfoPoolData * data = NULL;
		int maxCount = 0;
		if(m_iSubPageKind == pageObjectList || m_iSubPageKind == pageComposeList)
		{
			maxCount = BAGOTHEROBJECTHANDLER->m_bagMaxCount;
		}

		for(int i = 0; i < maxCount; ++i)
		{
			data = m_Pool.info_pool_data[i];
			if(data->infoType == InfoPoolData::INFO_LOCK)
			{
				data->infoType = InfoPoolData::INFO_EMPTY;
				data->drawed = false;
				m_Pool.all_info_drawed = false;
			}
		}

	}
	else if(iEventType == _TYPED_EVENT_REFRESH_BAGSALEIMPORTANTOBJECT_COMFIRM_)
	{
		Function_ComfirmSaleImportant();
	}
}


void BagWindow::OnShowWindowEventHandler(std::list<std::string>& paramList)
{
	Show(true);
	if(paramList.size() > 1)
	{
		string tmp;
		list<string>::iterator it=paramList.begin();
		//��һ������Ϊ�ӽ���
		if (paramList.size()>0){
			tmp=*it++;
			int ntabNum=atoi(tmp.c_str());
			m_iSubPageKind = pageObjectList + ntabNum;
		}
		if (paramList.size()>1){
			tmp=*it++;
			m_iBackWindow = atoi(tmp.c_str());
		}
	}
// 	else
// 	{
// 		m_iBackWindow = 0;
// 	}

}


void BagWindow::OnRefreshWindowEventHandler(std::list<std::string>& paramList)
{
	_setMainPageInfo();

}

void BagWindow::Function_NumInputResult(int num)
{
	if(m_iSubPageKind == pageObjectList)
	{
		assert(m_iSelectedTag >= 0);
		BagOtherObject * boo = BAGOTHEROBJECTHANDLER->m_vecList[m_iSelectedTag];
		if(m_iBtnFunction == functionSALE)
		{
			BAGOTHEROBJECTHANDLER->saleObject(boo, num);
			//boo->itemcount_ -= num;
		}
		else if(m_iBtnFunction == functionUSE)
		{
			BAGOTHEROBJECTHANDLER->useObject(boo, num);
			//boo->itemcount_ -= num;
			//~~~~~~��������~~~~~~
			GUIDESYSTEM->Next();
		}
	}
	else if(m_iSubPageKind == pageComposeList)
	{
		BagOtherObject * boo = BAGOTHEROBJECTHANDLER->getBagObjectByCanIndex(m_iSelectedTag);
		BAGOTHEROBJECTHANDLER->useObject(boo, num);
	}
	
}

void BagWindow::Function_ComfirmSaleImportant()
{
	if(m_iSubPageKind == pageObjectList)
	{
		assert(m_iSelectedTag >= 0);
		BagOtherObject * boo = BAGOTHEROBJECTHANDLER->m_vecList[m_iSelectedTag];

		if(boo->itemcount_ >= 10)
		{
			//��������
			std::string maxnum = "";
			char max[128] = "";
			sprintf(max, "%d", boo->itemcount_);
			maxnum.assign(max);
			EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_INPUTNUMWINDOW_,boo->template_->name_, maxnum);
		}
		else
		{
			Function_NumInputResult(1);
		}
	}

}

void BagWindow::On_Close_Window(cocos2d::CCObject* pSender)
{
	LOGGERSYSTEM->LogInfo("On_Close_Bag_Window");
	EVENTSYSTEM->PushEvent(_TYPED_EVENT_HIDE_BAGWINDOW_);
	if (m_iBackWindow <= 0)
	{
		EVENTSYSTEM->PushEvent(_TYPED_EVENT_SHOW_HOMEWINDOW_);
	}else{
		EVENTSYSTEM->PushEvent(m_iBackWindow);
		m_iBackWindow = 0;
	}
}


/************************************************************************/
/* PanelItem                                                            */
/************************************************************************/

void PanelItem::_setEnhanceLevel(int level)
{
	CCLabelTTF* cc=(CCLabelTTF*)this->getChildByTag(pELEVEL);
	char tmp[8];
	sprintf(tmp,"+%d",level);
	cc->setString(tmp);
	CCNode * sp = this->getChildByTag(pRIGHTTOPBG);
	if(level > 0)
	{
		cc->setVisible(true);
		sp->setVisible(true);
	}
	else
	{
		cc->setVisible(false);
		sp->setVisible(false);
	}
}

void PanelItem::_setLevel(int level)
{
	CCLabelTTF* cc=(CCLabelTTF*)this->getChildByTag(pLEVEL);
	char tmp[8];
	sprintf(tmp,"Lv:%d",level);
	cc->setString(tmp);
	CCNode * sp = this->getChildByTag(pLEFTDOWNBG);
	if(level > 0)
	{
		cc->setVisible(true);
		sp->setVisible(true);
	}
	else
	{
		cc->setVisible(false);
		sp->setVisible(false);
	}
}

void PanelItem::_setLabelCount(int count)
{
	CCLabelTTF* cc=(CCLabelTTF*)this->getChildByTag(pCOUNT);
	char tmp[8];
	sprintf(tmp,"%d",count);
	cc->setString(tmp);
	if(count > 1)
	{
		cc->setVisible(true);
	}
	else
	{
		cc->setVisible(false);
	}
}


PanelItem::PanelItem()
{
	_itemId = 0;
	_tag = 0;
	_type = 0;
}

PanelItem::~PanelItem()
{

}

PanelItem* PanelItem::createEmpty(int tag, cocos2d::CCObject* target,cocos2d:: SEL_MenuHandler selector)
{
	PanelItem *cc=new PanelItem();
	if(cc)
	{
		cc->_tag = tag;//��tag�����ڲ�����ͼ��ť��tag��ͬʱ��־��Ʒ���ڴ洢��vectorλ��

		//��������
		UIVIEWDATAMANAGER->AutoCreateNodeByTable(UIViewDataManager::kBAGWINDOWRIGHTPANELITEM, cc);
		//map
		cocos2d::CCMenu * menu = (CCMenu*)cc->getChildByTag(pQUALITY);
		CCMenuItemSprite * item = (CCMenuItemSprite *)menu->getChildByTag(0);
		item->setTag(tag);
		item->setTarget(target, selector);

		CCNode * sp = NULL;
		sp = cc->getChildByTag(pRIGHTTOPBG);
		sp->setVisible(false);
		sp = cc->getChildByTag(pLEFTDOWNBG);
		sp->setVisible(false);

		cc->autorelease();
		return cc;
	}
	delete cc;
	return NULL;
}


/************************************************************************/
/* Pool                                                                 */
/************************************************************************/
BagPool::BagPool()
{
	board_pool_data.clear();
	info_pool_data.clear();
	memset(board_position, 0, sizeof(board_position));
	page_width = 0;
	all_board_drawed = false;
	all_info_drawed = false;

	filltype = -1;
}

void BagPool::Insert(BoardPoolData * data)
{
	data->drawed = false;
	board_pool_data.push_back(data);
}

void BagPool::Insert(InfoPoolData * data)
{
	data->drawed = false;
	info_pool_data.push_back(data);
}

/*
	ɾ����������
*/
void BagPool::PopPage(int page)
{
	cout<<"BagPoll::PopPage"<<endl;
}

/*
	�����е�ĳҳ����
*/
void BagPool::HangPageBoard(int page, CCNode * parent)
{
	assert(parent);

	//�װ�
	std::vector<BoardPoolData *>::iterator i = this->board_pool_data.begin();
	std::vector<BoardPoolData *>::iterator i_e = this->board_pool_data.end();
	for(; i != i_e; ++i)
	{
		if((*i)->page == page && (*i)->drawed == false)
		{
			(*i)->drawed = true;
			//����type������Ӧ��ObjectItem��Ȼ�����
			createBoard(*i, parent);
		}
	}

}

void BagPool::HangPageInfo(int page, cocos2d::CCNode * parent)
{
	std::vector<InfoPoolData *>::iterator i = this->info_pool_data.begin();
	std::vector<InfoPoolData *>::iterator i_e = this->info_pool_data.end();
	for(; i != i_e; ++i)
	{
		if((*i)->page == page && (*i)->drawed == false)
		{
			(*i)->drawed = true;
			//����type��ʾ��Ӧ����Ϣ
			CCNode * mp = parent->getChildByTag((*i)->tag);//�õ���Ӧ�ĸ��ӣ�����Ӹ������ҵ���Ӧ����Ʒ
			createInfo(*i, mp);
			//break;	//edit at 20130925
		}
	}
// 	if(i == i_e)//edit at 20130925
// 	{
// 		all_info_drawed = true;
// 	}
}

void BagPool::HangData(CCNode * parent)
{
	assert(parent);

	if(!all_board_drawed)
	{
		//�װ�
		std::vector<BoardPoolData *>::iterator i = this->board_pool_data.begin();
		std::vector<BoardPoolData *>::iterator i_e = this->board_pool_data.end();
		for(; i != i_e; ++i)
		{
			if((*i)->drawed == false)
			{
				(*i)->drawed = true;
				//����type������Ӧ�ĵװ壬Ȼ�����
				createBoard(*i, parent);
				break;
			}
		}
		if(i == i_e)
		{
			all_board_drawed = true;
		}
	}
	
	if(!all_info_drawed)
	{
		//��Ϣ��ʾ
		std::vector<InfoPoolData *>::iterator ii = this->info_pool_data.begin();
		std::vector<InfoPoolData *>::iterator ii_e = this->info_pool_data.end();
		for(; ii != ii_e; ++ii)
		{
			if((*ii)->drawed == false)
			{
				(*ii)->drawed = true;
				//����type��ʾ��Ӧ����Ϣ
				CCNode * mp = parent->getChildByTag((*ii)->tag);//�õ���Ӧ�ĸ��ӣ�����Ӹ������ҵ���Ӧ����Ʒ
				createInfo(*ii, mp);
				break;
			}
		}
		if(ii == ii_e)
		{
			all_info_drawed = true;
		}
	}
	
}

void BagPool::HangPage(cocos2d::CCNode * parent)
{
	if(!all_board_drawed)
	{
		//�װ�
		std::vector<BoardPoolData *>::iterator i = this->board_pool_data.begin();
		std::vector<BoardPoolData *>::iterator i_e = this->board_pool_data.end();
		for(; i != i_e; ++i)
		{
			if((*i)->drawed == false)
			{
				(*i)->drawed = true;
				//����type������Ӧ�ĵװ壬Ȼ�����
				createBoard(*i, parent);

				if(i + 1 != i_e)
				{
					if((*i)->page != (*(i + 1))->page)
					{
						std::cout<<"Pool --  Hang Page Board : "<<(*i)->page<<endl;
						break;
					}
				}
			}
		}
		if(i == i_e)
		{
			all_board_drawed = true;
		}
	}

	if(!all_info_drawed)
	{
		//��Ϣ��ʾ
		std::vector<InfoPoolData *>::iterator ii = this->info_pool_data.begin();
		std::vector<InfoPoolData *>::iterator ii_e = this->info_pool_data.end();
		for(; ii != ii_e; ++ii)
		{
			if((*ii)->drawed == false)
			{
				(*ii)->drawed = true;
				//����type��ʾ��Ӧ����Ϣ
				CCNode * mp = parent->getChildByTag((*ii)->tag);//�õ���Ӧ�ĸ��ӣ�����Ӹ������ҵ���Ӧ����Ʒ
				createInfo(*ii, mp);
				
				if(ii + 1 != ii_e)
				{
					if((*ii)->page != (*(ii + 1))->page)
					{
						std::cout<<"Pool --  Hang Page Info : "<<(*ii)->page<<endl;
						break;
					}
				}

			}
		}
		if(ii == ii_e)
		{
			all_info_drawed = true;
		}
	}
}

void BagPool::createBoard(BoardPoolData * data, CCNode * parent)
{
	//�����װ�
	PanelItem * pi = PanelItem::createEmpty(data->tag, BAGWINDOWDATAHANDLER->DATA_Window, menu_selector(BagWindow::On_RightMenu_Click));

	float posx = board_position[data->tag % NEWBAG_NUMPERPAGE][0] + page_width * data->page;
	float posy = board_position[data->tag % NEWBAG_NUMPERPAGE][1];
	pi->setAnchorPoint(CCPointZero);
	pi->setPosition(ccp(posx, posy));
	pi->setTag(data->tag);

	parent->addChild(pi);

}

void BagPool::createInfo(InfoPoolData * data, CCNode * parent)
{
	if(data->infoType == InfoPoolData::INFO_HAS)
	{
		PanelItem * pi = (PanelItem *)parent;
		//����ͼ
		CCMenu * menu = (CCMenu *)pi->getChildByTag(PanelItem::pQUALITY);
		CCMenuItemSprite * item = (CCMenuItemSprite *)menu->getChildByTag(data->tag);
		bool _isselected = item->isSelected();
		std::string quality = varConfig::getCardBGFilePath(data->quality);
		CCSprite * spq = CCSprite::create();
		spq->setProperty("File",quality);
		item->setNormalImage(spq);
		CSpriteSelected* sp_sel=CSpriteSelected::create(select_file.c_str(),quality.c_str());
		item->setSelectedImage(sp_sel);
		if(_isselected)
			item->selected(true);

		//ͼ��
		CCSprite * sp = (CCSprite *)parent->getChildByTag(PanelItem::pICON);
		std::string icon = RESOURCEDAIDMANAGER->getDataByID(data->icon);
		sp->setProperty("File",icon);
		sp->setVisible(true);

		//���ֲ�
		CCSprite * hat = (CCSprite *)parent->getChildByTag(PanelItem::pHat);
		hat->setProperty("File", varConfig::getCardMaskFilePath(data->quality));
		hat->setVisible(true);

		//��Ʒid
		pi->_itemId = data->itemid;
		//����
		pi->_setLabelCount(data->itemcount);
		//ǿ���ȼ�
		pi->_setEnhanceLevel(data->enhancelevel);
		//�ȼ�
		pi->_setLevel(data->level);
	}
	else if(data->infoType == InfoPoolData::INFO_EMPTY)
	{
		PanelItem * pi = (PanelItem *)parent;
		//����ͼ
		CCMenu * menu = (CCMenu *)pi->getChildByTag(PanelItem::pQUALITY);
		CCMenuItemSprite * item = (CCMenuItemSprite *)menu->getChildByTag(data->tag);
// 		string quality = varConfig::getCardBGFilePath(0);
 		CCSprite * spq = CCSprite::create();
		spq->setProperty("File",empty_file);
 		item->setNormalImage(spq);
		CSpriteSelected* sp_sel=CSpriteSelected::create(select_file.c_str(), empty_file.c_str());
		item->setSelectedImage(sp_sel);
		//ͼ��
		CCSprite * sp = (CCSprite *)parent->getChildByTag(PanelItem::pICON);
		sp->setVisible(false);
		//���ֲ�
		CCSprite * hat = (CCSprite *)parent->getChildByTag(PanelItem::pHat);
		hat->setProperty("File", varConfig::getCardNormalMaskFilePath());
		hat->setVisible(true);

		//��Ʒid
		pi->_itemId = data->itemid;
		//����
		pi->_setLabelCount(0);
		//ǿ���ȼ�
		pi->_setEnhanceLevel(0);
		//�ȼ�
		pi->_setLevel(0);
	}
	else if(data->infoType == InfoPoolData::INFO_LOCK)
	{
		PanelItem * pi = (PanelItem *)parent;
		//����ͼ
		CCMenu * menu = (CCMenu *)pi->getChildByTag(PanelItem::pQUALITY);
		CCMenuItemSprite * item = (CCMenuItemSprite *)menu->getChildByTag(data->tag);
// 		string quality = varConfig::getCardBGFilePath(0);
 		CCSprite * spq = CCSprite::create();
		spq->setProperty("File",empty_file);
 		item->setNormalImage(spq);
		CSpriteSelected* sp_sel=CSpriteSelected::create(select_file.c_str(), empty_file.c_str());
		item->setSelectedImage(sp_sel);
		//ͼ��
		CCSprite * sp = (CCSprite *)parent->getChildByTag(PanelItem::pICON);
		/*string icon = RESOURCEDAIDMANAGER->getDataByID(data->icon);*/
		CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage(lock_file.c_str());
		if(texture!=NULL)
		{
			sp->setProperty("File",lock_file);
			sp->setVisible(true);
			sp->setScale(1);
		}
		//���ֲ�
		CCSprite * hat = (CCSprite *)parent->getChildByTag(PanelItem::pHat);
		hat->setProperty("File", varConfig::getCardNormalMaskFilePath());
		hat->setVisible(true);

		//��Ʒid
		pi->_itemId = data->itemid;
		//����
		pi->_setLabelCount(0);
		//ǿ���ȼ�
		pi->_setEnhanceLevel(0);
		//�ȼ�
		pi->_setLevel(0);
	}
	
}

void BagPool::ClearInfoData()
{
	//��Ϣ
	std::vector<InfoPoolData *>::iterator ii = this->info_pool_data.begin();
	std::vector<InfoPoolData *>::iterator ii_e = this->info_pool_data.end();
	for(; ii != ii_e; ++ii)
	{
		delete *ii;
		*ii = NULL;
	}
	this->info_pool_data.clear();

	this->all_info_drawed = false;
}

void BagPool::Destroy()
{
	std::vector<BoardPoolData *>::iterator i = this->board_pool_data.begin();
	std::vector<BoardPoolData *>::iterator i_e = this->board_pool_data.end();
	for(; i != i_e; ++i)
	{
		delete *i;
		*i = NULL;
	}
	this->board_pool_data.clear();

	//��Ϣ
	std::vector<InfoPoolData *>::iterator ii = this->info_pool_data.begin();
	std::vector<InfoPoolData *>::iterator ii_e = this->info_pool_data.end();
	for(; ii != ii_e; ++ii)
	{
		delete *ii;
		*ii = NULL;
	}
	this->info_pool_data.clear();

	this->all_board_drawed = false;
	this->all_info_drawed = false;

}

void BagPool::Init()
{
	UIVIEWDATAMANAGER->loadData(UIViewDataManager::kBAGWINDOWRIGHTPANELPOSITION);
	UIViewData * dd = NULL;
	for(int i = 0; i < NEWBAG_NUMPERPAGE; ++i)
	{
		dd = UIVIEWDATAMANAGER->getControlDataByID(i);
		board_position[i][0] = dd->posx_;
		board_position[i][1] = dd->posy_;
	}

	dd = UIVIEWDATAMANAGER->getControlDataByID(NEWBAG_NUMPERPAGE);

	empty_file.assign(dd->filepath_);
	select_file.assign(dd->filepath2_);
	lock_file.assign(dd->filepath3_);

	page_width = BAGWINDOWDATAHANDLER->DATA_RightPanel->getContentSize().width;
}