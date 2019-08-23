//  Game:DotaTribe
//  Copyright 2013 PlayCool. All rights reserved.
//  Writte By:Johny
//  Type: The Corner Num
//

#include "../include/CCornerNumIcon.h"

USING_NS_CC;

CCornerNumIcon::CCornerNumIcon()
:m_pNum(0)
,m_nCount(0){

}
CCornerNumIcon::~CCornerNumIcon(){

}

CCornerNumIcon* CCornerNumIcon::create(const char* file1,const char* file2,const char* file3){
	 CCornerNumIcon* cc=new CCornerNumIcon();
	 if(cc->init(file1,file2,file3)){
		 cc->autorelease();
		 return cc;
	 }
	 delete cc;cc=NULL;
	 return cc;
}

bool CCornerNumIcon::init(const char* file1,const char* file2,const char* file3){
	if (!CCSprite::init())
		return false;
	m_strFile1=file1;
	m_strFile2=file2;
	m_strFile3=file3;
	_setNumLabel();
	return true;
}

void CCornerNumIcon::_setNumLabel(){
	m_pNum=CCLabelTTF::create();
	this->addChild(m_pNum);
	_resetNumLabelLocation();
}

void CCornerNumIcon::setNum(unsigned int num){
	m_nCount=num;
	if(num<=0)
		setShow(false);
	else if (num<10)
		_changeToFile1();
	else if(num<100)
		_changeToFile2();
	else
		_changeToFile3();
	char tmp[32];
	if (num>99)
		sprintf(tmp,"99+",num);
	else
		sprintf(tmp,"%d",num);
	m_pNum->setString(tmp);
	_resetNumLabelLocation();
}

void CCornerNumIcon::_changeToFile1(){
	this->setProperty("File",m_strFile1);
}
void CCornerNumIcon::_changeToFile2(){
	this->setProperty("File",m_strFile2);
}
void CCornerNumIcon::_changeToFile3(){
	this->setProperty("File",m_strFile3);
}

void CCornerNumIcon::_resetNumLabelLocation(){
	m_pNum->setAnchorPoint(ccp(0.5,0.5));
	m_pNum->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height/2));
}

void CCornerNumIcon::setShow(bool isshow){
	if (m_nCount<=0)
		setVisible(false);
	else
		setVisible(isshow);
}