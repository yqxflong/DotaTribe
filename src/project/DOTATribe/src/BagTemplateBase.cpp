#include "../include/BagTemplateBase.h"


ObjectTemplate * ObjectTemplate::__set(const ObjectTemplate * obj)
{
	this->catogory_ = obj->catogory_;
	this->type_ = obj->type_;
	this->templateid_ = obj->templateid_;
	this->name_ = obj->name_;
	this->description_ = obj->description_;
	this->level_ = obj->level_;
	this->quality_ = obj->quality_;
	this->price_ = obj->price_;
	this->canUse_ = obj->canUse_;

	this->iconId_ = obj->iconId_;
	this->maxCount_ = obj->maxCount_;
	this->sortIndex = obj->sortIndex;

	return this;

}

bool ObjectTemplate::decodeTemplatePacketData(cobra_win::DPacket & packet)
{

	packet>>type_;
	packet>>templateid_;
	unsigned short strlen = 0;
	char * str = NULL;
	packet>>strlen;//Ãû×Ö
	str = new char[strlen+1];
	packet.read(str,strlen);
	str[strlen] = '\0';
	name_.assign(str);
	delete[] str;
	str = NULL;
	packet>>strlen;//ÃèÊö
	str = new char[strlen+1];
	packet.read(str,strlen);
	str[strlen] = '\0';
	description_.assign(str);
	delete[] str;
	str = NULL;
	packet>>level_;
	packet>>quality_;
	packet>>iconId_;
	packet>>maxCount_;
	packet>>canUse_;
	packet>>price_;
	packet>>sortIndex;//ÅÅÐòId

	return true;
}

EquipTemplate * EquipTemplate::__set(const EquipTemplate * obj)
{
	this->catogory_ = obj->catogory_;
	this->type_ = obj->type_;
	this->templateid_ = obj->templateid_;
	this->name_ = obj->name_;
	this->description_ = obj->description_;
	this->level_ = obj->level_;
	this->quality_ = obj->quality_;
	this->price_ = obj->price_;
	this->canUse_ = obj->canUse_;

	this->maxLevel_ = obj->maxLevel_;
	this->iconId_ = obj->iconId_;
	this->iconBigId_ = obj->iconBigId_;
	this->maxCount_ = obj->maxCount_;
	this->baseAttrType_ = obj->baseAttrType_;

	return this;
}

bool EquipTemplate::decodeTemplatePacketData(cobra_win::DPacket & packet)
{
	packet>>type_;
	packet>>canUse_;
	packet>>templateid_;
	unsigned short tmp_len;
	char * tmpChar = NULL;
	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	name_.assign(tmpChar);
	delete[] tmpChar;
	tmpChar=NULL;
	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	description_.assign(tmpChar);
	delete[] tmpChar;
	tmpChar=NULL;
	packet>>level_;
	packet>>maxLevel_;
	packet>>quality_;
	packet>>iconId_;
	packet>>iconBigId_;
	packet>>maxCount_;
	packet>>price_;
	packet>>baseAttrType_;

	return true;

}

bool SkinTemplate::decodeTemplatePacketData(cobra_win::DPacket & packet)
{

	packet>>type_;
	packet>>canUse_;
	packet>>templateid_;
	unsigned short tmp_len;
	char * tmpChar = NULL;
	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	name_.assign(tmpChar);
	delete[] tmpChar;
	tmpChar = NULL;
	packet>>tmp_len;
	tmpChar=new char[tmp_len+1];
	packet.read(tmpChar,tmp_len);
	tmpChar[tmp_len]='\0';
	description_.assign(tmpChar);
	delete [] tmpChar;
	tmpChar = NULL;
	packet>>quality_;
	packet>>level_;
	//~~~~~~~~~iconid && shapeid
	unsigned short tmp;
	packet>>tmp;
	iconid_.push_back(tmp);
	packet>>tmp;
	iconid_.push_back(tmp);
	packet>>tmp;
	iconid_.push_back(tmp);
	packet>>tmp;
	shapeid_.push_back(tmp);
	packet>>tmp;
	shapeid_.push_back(tmp);
	packet>>tmp;
	shapeid_.push_back(tmp);
	//~~~~~~~~~
	packet>>maxCount_;
	packet>>price_;
	packet>>maxEnhanceLevel_;
	packet>>strConverRate_;
	packet>>agiConverRate_;
	packet>>intConverRate_;
	packet>>mianConverRate_;
	packet>>waaponid_;
	if (waaponid_>0)
	{
		//LOGGERSYSTEM->LogInfo("SCRolInfoPacket-- Read Bag Data	--skin	--	weapon");
		packet>>weaponIconId_;
		//¶ÁWeaponname
		packet>>tmp_len;
		tmpChar=new char[tmp_len+1];
		packet.read(tmpChar,tmp_len);
		tmpChar[tmp_len]='\0';
		weaponname_.assign(tmpChar);
		delete[] tmpChar;
		tmpChar = NULL;
		//¶ÁWeapoDescrip
		packet>>tmp_len;
		tmpChar=new char[tmp_len+1];
		packet.read(tmpChar,tmp_len);
		tmpChar[tmp_len]='\0';
		weaponDesc_.assign(tmpChar);
		delete [] tmpChar;
		tmpChar = NULL;
	}
	packet>>buffId_;
	if (buffId_>0)
	{
		//LOGGERSYSTEM->LogInfo("SCRolInfoPacket-- Read Bag Data	--skin -- buff");
		packet>>buffLevel_;
		packet>>buffIconId_;
		//¶ÁbuffName
		packet>>tmp_len;
		tmpChar=new char[tmp_len+1];
		packet.read(tmpChar,tmp_len);
		tmpChar[tmp_len]='\0';
		buffName_.assign(tmpChar);
		delete[] tmpChar;
		tmpChar=NULL;
		//¶ÁbuffScrip
		packet>>tmp_len;
		tmpChar=new char[tmp_len+1];
		packet.read(tmpChar,tmp_len);
		tmpChar[tmp_len]='\0';
		buffDesc_.assign(tmpChar);
		delete[] tmpChar;
		tmpChar=NULL;
	}
	packet>>skillId_;
	if (skillId_>0)
	{
		//LOGGERSYSTEM->LogInfo("SCRolInfoPacket-- Read Bag Data	--skin	--skill");
		packet>>skllLevel_;
		//¶ÁSkilName
		packet>>tmp_len;
		tmpChar=new char[tmp_len+1];
		packet.read(tmpChar,tmp_len);
		tmpChar[tmp_len]='\0';
		skillName_.assign(tmpChar);
		delete[] tmpChar;
		tmpChar=NULL;
		//¶ÁSkilDescrip
		packet>>tmp_len;
		tmpChar=new char[tmp_len+1];
		packet.read(tmpChar,tmp_len);
		tmpChar[tmp_len]='\0';
		skllDesc_.assign(tmpChar);
		delete[] tmpChar;
		tmpChar=NULL;
	}
	return true;
}