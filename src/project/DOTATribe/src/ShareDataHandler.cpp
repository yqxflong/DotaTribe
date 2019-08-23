//Name：ShareDataHandler
//Function：分享管理器
//Written By：尹强

#include <cocos2d.h>
#include "../include/ShareDataHandler.h"

USING_NS_CC;

void ShareDataHandler::onDestroy(){

}

bool ShareDataHandler::init(){
	return true;
}

void ShareDataHandler::ShareTo_WeChat_PengYouQuan(){
	CCDirector::sharedDirector()->getPlatform()->ShareTo_WeChat_PengYouQuan("Hi","desc","xx/xx/xx.png");
}
	
void ShareDataHandler::ToServer_FinishShare(){

}
	
void ShareDataHandler::decodePacket(cobra_win::DPacket & packet){

}