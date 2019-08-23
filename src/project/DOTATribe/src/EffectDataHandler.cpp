//Name： EffectDataHandler
//Function：效果管理器
//Written By：尹强

#include <cocos2d.h>
#include "../include/EffectDataHandler.h"
#include "../include/EventSystem.h"
#include "../include/EventTyper.h"
#include "../include/SCRoleInfoPacket.h"
#include "../include/CPublicVarReader.h"
//
#include "../include/ClientConstDataManager.h"
#include "../include/NumberBufferDataManager.h"
#include "../include/ArtFontDataManager.h"
#include "../include/ResourceIDDataManager.h"
#include "../include/NFControlsManager.h"

using namespace std;

void EffectDataHandler::_registerEvent(){
	EVENTSYSTEM->RegisterEventHandler(_TYPED_EVENT_CLEAR_USING_EFFECT_,ClearEffectList);
}
void EffectDataHandler::_unRegisterEvent(){
	EVENTSYSTEM->UnRegisterEventHandler(_TYPED_EVENT_CLEAR_USING_EFFECT_,ClearEffectList);
}

//开启EffectHandler
void EffectDataHandler::OpenEffectHandler(){
	effectList_.clear();
	_registerEvent();
}

bool EffectDataHandler::init(){
	return true;
}

void EffectDataHandler::onDestroy(){
	list<EffectData*>::iterator it=effectList_.begin();
	list<EffectData*>::iterator it_end=effectList_.end();
	for (;it!=it_end;it++)
	{
		delete *it;
	}
	effectList_.clear();
}

void EffectDataHandler::pushToEffectList(EffectData* dd){
	//进一步加载数据
	_handleIcon(dd);
	int fonttype=_handleAnima(dd);
	_handleNum(dd,fonttype);
	//载入vec数组
	if (dd->getType()==kEFFECT_NUMBJ||dd->getType()==kEFFECT_OBJECTBJ){//如果是暴击
		_handleBJ(dd,fonttype);
	}
	//加入list
	effectList_.push_back(dd);
	EVENTSYSTEM->PushEvent(_TYPEF_EVENT_SHOW_EFFECTWINDOW_);
}

void EffectDataHandler::_handleIcon(EffectData* dd){
	if (dd->getType()==kEFFECT_OBJECT||dd->getType()==kEFFECT_OBJECTBJ)//为物品
	{
		dd->iconPath_=RESOURCEDAIDMANAGER->getDataByID(dd->getIConID());
		assert(dd->iconPath_!="");
	}else{//为数值
		int iconID=CLIENTCONSTDATAMANGER->getValueByKey(dd->getIConKey());
		dd->iconPath_=RESOURCEDAIDMANAGER->getDataByID(iconID);
	}
}

int EffectDataHandler::_handleAnima(EffectData* dd){
	int styleIdx=0;
	if(dd->getType()==kEFFECT_NUMBJ||dd->getType()==kEFFECT_OBJECTBJ){
		styleIdx=CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_USEITEM_CRISTYLE);
	}else{
		styleIdx=CLIENTCONSTDATAMANGER->getValueByKey(CONST_KEY_USEITEM_NORSTYLE);
	}
	NumberBufferData* nbd=NumberBufferDataManager::get_instance2()->GetNumberBufferDataByID(styleIdx);
	dd->animaTime_=(float)(nbd->numberBufferDurationTime*1.0/1000);
	dd->fadeoutStartTime_=(float)(nbd->numberBufferTriggerFadeOutTime*1.0/1000);
	dd->beginPosY_=nbd->numberBufferInitHeigh;
	dd->endPosY_=nbd->numberBufferEndHeigh;
	dd->scale_=nbd->numberBufferScale;
	return nbd->numberBufferFontType;
}

void EffectDataHandler::_handleNum(EffectData* dd,int fonttype){
	vector<int> vecSub=varConfig::getSubInt(dd->getCount());
	int fontid=ArtFontDataManager::get_instance2()->GetArtFontValueFromID(fonttype,_Art_Font_Index_ADD_);//+
	dd->vecFonts_.push_back(fontid);
	//n个单数
	for (int i=0;i<(int)vecSub.size();i++)
	{
		int num=vecSub[i];
		fontid=ArtFontDataManager::get_instance2()->GetArtFontValueFromID(fonttype,num);
		assert(fontid!=0);
		dd->vecFonts_.push_back(fontid);
	}
}

void EffectDataHandler::_handleBJ(EffectData* dd,int fonttype){
	int bjcount=dd->getBJCount();
	int fontid=0;
	if (bjcount==2)
		fontid=ArtFontDataManager::get_instance2()->GetArtFontValueFromID(fonttype,_Art_Font_Index_Two_);
	else if(bjcount==4)
		fontid=ArtFontDataManager::get_instance2()->GetArtFontValueFromID(fonttype,_Art_Font_Index_Four_);
	else if(bjcount==10)
		fontid=ArtFontDataManager::get_instance2()->GetArtFontValueFromID(fonttype,_Art_Font_Index_Ten_);
	else
		assert(fontid!=0);
	dd->vecFonts_.push_back(fontid);
	fontid=ArtFontDataManager::get_instance2()->GetArtFontValueFromID(fonttype,_Art_Font_Index_BaoJi_);
	dd->vecFonts_.push_back(fontid);
}

	/*
		同步金钱
	*/
void EffectDataHandler::Effect_GetNum(int key,int count){
	EffectData* dd;
	switch(key){
		case kEFFECT_TYPE_MONEY:
			dd=new EffectData(kEFFECT_NUM,0,CONST_KEY_ICON_GOLD,count,0);
			pushToEffectList(dd);
			break;
		case kEFFECT_TYPE_EXP:
			dd=new EffectData(kEFFECT_NUM,0,CONST_KEY_ICON_EXP,count,0);
			pushToEffectList(dd);
			break;
		case kEFFECT_TYPE_DIAMOND:
			dd=new EffectData(kEFFECT_NUM,0,CONST_KEY_ICON_DIAMOND,count,0);
			pushToEffectList(dd);
			break;
		case kEFFECT_TYPE_TL:
			dd=new EffectData(kEFFECT_NUM,0,CONST_KEY_ICON_ENG,count,0);
			pushToEffectList(dd);
			break;
		case kEFFECT_TYPE_STR:
			dd=new EffectData(kEFFECT_NUM,0,CONST_KEY_ICON_STRSKILL,count,0);
			pushToEffectList(dd);
			break;
		case kEFFECT_TYPE_DEX:
			dd=new EffectData(kEFFECT_NUM,0,CONST_KEY_ICON_DEXSKILL,count,0);
			pushToEffectList(dd);
			break;
		case kEFFECT_TYPE_INTEL:
			dd=new EffectData(kEFFECT_NUM,0,CONST_KEY_ICON_INISKILL,count,0);
			pushToEffectList(dd);
			break;
		case kEFFECT_TYPE_PRESTAGE:
			dd=new EffectData(kEFFECT_NUM,0,CONST_KEY_ICON_PRESTAGE,count,0);
			pushToEffectList(dd);
			break;
		case kEFFECT_TYPE_EXPLOIT:
			dd=new EffectData(kEFFECT_NUM,0,CONST_KEY_ICON_EXPLOIT,count,0);
			pushToEffectList(dd);
			break;
		case kEFFECT_TYPE_HERO_EXP:
			dd=new EffectData(kEFFECT_NUM,0,CONST_KEY_ICON_HEROEXP,count,0);
			pushToEffectList(dd);
			break;
		case kEFFECT_TYPE_EQUIP_EXP:
			dd=new EffectData(kEFFECT_NUM,0,CONST_KEY_ICON_EQUIPEXP,count,0);
			pushToEffectList(dd);
			break;
		default:
			break;
	}
}

	/*
		同步数值,暴击
	*/
void EffectDataHandler::Effect_GetNumBJ(int key,int count,int bjcount){
	EffectData* dd;
	switch(key){
		case kEFFECT_TYPE_MONEY:
			dd=new EffectData(kEFFECT_NUMBJ,0,CONST_KEY_ICON_GOLD,count,bjcount);
			pushToEffectList(dd);
			break;
		case kEFFECT_TYPE_EXP:
			dd=new EffectData(kEFFECT_NUM,0,CONST_KEY_ICON_EXP,count,bjcount);
			pushToEffectList(dd);
			break;
		case kEFFECT_TYPE_DIAMOND:
			dd=new EffectData(kEFFECT_NUMBJ,0,CONST_KEY_ICON_DIAMOND,count,bjcount);
			pushToEffectList(dd);
			break;
		case kEFFECT_TYPE_TL:
			dd=new EffectData(kEFFECT_NUMBJ,0,CONST_KEY_ICON_ENG,count,bjcount);
			pushToEffectList(dd);
			break;
		case kEFFECT_TYPE_STR:
			dd=new EffectData(kEFFECT_NUMBJ,0,CONST_KEY_ICON_STRSKILL,count,bjcount);
			pushToEffectList(dd);
			break;
		case kEFFECT_TYPE_DEX:
			dd=new EffectData(kEFFECT_NUMBJ,0,CONST_KEY_ICON_DEXSKILL,count,bjcount);
			pushToEffectList(dd);
			break;
		case kEFFECT_TYPE_INTEL:
			dd=new EffectData(kEFFECT_NUMBJ,0,CONST_KEY_ICON_INISKILL,count,bjcount);
			pushToEffectList(dd);
			break;
		case kEFFECT_TYPE_PRESTAGE:
			dd=new EffectData(kEFFECT_NUMBJ,0,CONST_KEY_ICON_PRESTAGE,count,bjcount);
			pushToEffectList(dd);
			break;
		case kEFFECT_TYPE_EXPLOIT:
			dd=new EffectData(kEFFECT_NUMBJ,0,CONST_KEY_ICON_EXPLOIT,count,bjcount);
			pushToEffectList(dd);
			break;
		case kEFFECT_TYPE_HERO_EXP:
			dd=new EffectData(kEFFECT_NUMBJ,0,CONST_KEY_ICON_HEROEXP,count,bjcount);
			pushToEffectList(dd);
			break;
		case kEFFECT_TYPE_EQUIP_EXP:
			dd=new EffectData(kEFFECT_NUMBJ,0,CONST_KEY_ICON_EQUIPEXP,count,bjcount);
			pushToEffectList(dd);
			break;
		default:
			break;
	}
}

/*
	同步物品
*/
void EffectDataHandler::Effect_GetObject(int iconid,int count){
	EffectData* dd=new EffectData(kEFFECT_OBJECT,iconid,"",count,0);
	pushToEffectList(dd);
}

	/*
		同步物品暴击
	*/
void EffectDataHandler::Effect_GetObjectBJ(int iconid,int count,int bjcount){
	EffectData* dd=new EffectData(kEFFECT_OBJECTBJ,iconid,"",count,bjcount);
	pushToEffectList(dd);
}

 /**
         * 提示获得物品<br>
         * byte type 类型 0物品 1金钱 2经验<br>
         * int count 数量<br>
         * byte critValue 暴击值<br>		1不是暴击
         * if(type == 0){<br>
         * int itemIconId<br>
         * }<br>
         */
void EffectDataHandler::decodePacketData(cobra_win::DPacket & packet){
	unsigned char type;
	int count;
	unsigned char bjcount;
	int itemIconID=0;
	packet>>type;
	packet>>count;
	packet>>bjcount;
	if (type==kEFFECT_TYPE_OBJECT)
	{
		packet>>itemIconID;
	}
	ShowFlowEffect(type,count,bjcount,itemIconID);
}

void EffectDataHandler::HandleAfterOnePacket(){
	NFC_showCommunicationWating(false);
}

	/*
		实现飘字接口
	*/
void EffectDataHandler::ShowFlowEffect(int type,int count,int bjcount,int itemiconid){
	if (type==kEFFECT_TYPE_OBJECT){
		if (bjcount==1)
			Effect_GetObject(itemiconid,count);
		else
			Effect_GetObjectBJ(itemiconid,count,bjcount);
	}else{
		if (bjcount==1)
			Effect_GetNum(type,count);
		else
			Effect_GetNumBJ(type,count,bjcount);
	}
}

//清空所有效果
void EffectDataHandler::ClearEffectList(int iEventType, std::string owerData, std::list<std::string>& paramList){
	list<EffectData*>::iterator it=EFFECTDATAHANDLER->effectList_.begin();
	list<EffectData*>::iterator it_end=EFFECTDATAHANDLER->effectList_.end();
	for (;it!=it_end;it++)
		delete *it;
	EFFECTDATAHANDLER->effectList_.clear();
}