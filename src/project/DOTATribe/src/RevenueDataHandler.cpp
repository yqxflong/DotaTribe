// Name :		RevenueDataHandler.h
// Function:	点金数据
// Author :		zhoushaonan
// Maintainer:  zhoushaonan

#include "../include/RevenueDataHandler.h"
using namespace std;

RevenueDataHandler::RevenueDataHandler(){
	m_showArrow = false;
}

RevenueDataHandler::~RevenueDataHandler(){

}

void RevenueDataHandler::handlePacket(IPacket* packet){

}

bool RevenueDataHandler::init(){
	return true;
}

void RevenueDataHandler::onDestroy(){
	m_showArrow = false;
}

