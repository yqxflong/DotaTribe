//Name��IPopWindow
//Function�����е����Ļ���
//Author����ǿ

#include "../include/IPopWindow.h"
#include "../include/PopWindowManager.h"
#include "../include/ClientConstDataManager.h"

IPopWindow::IPopWindow(){
	priority_=-1;
}

IPopWindow::~IPopWindow(){

}

//��ʾ����
void IPopWindow::ShowPopWindow(){
	PopWindowManager::get_instance2()->isPaused=true;
	PopWindowManager::get_instance2()->RemovePopWindow(this);
}
//�����Ѿ�����
void IPopWindow::PopWindowDidHide(){
	PopWindowManager::get_instance2()->isPaused=false;
}

int IPopWindow::GetPriorityByCurWindowDef(std::string key){
	int priority= ClientConstDataManager::get_instance2()->getValueByKey(key.c_str());
	return priority;
}