//Name：IPopWindow
//Function：所有弹窗的基类
//Author：尹强

#include "../include/IPopWindow.h"
#include "../include/PopWindowManager.h"
#include "../include/ClientConstDataManager.h"

IPopWindow::IPopWindow(){
	priority_=-1;
}

IPopWindow::~IPopWindow(){

}

//显示弹窗
void IPopWindow::ShowPopWindow(){
	PopWindowManager::get_instance2()->isPaused=true;
	PopWindowManager::get_instance2()->RemovePopWindow(this);
}
//弹窗已经隐藏
void IPopWindow::PopWindowDidHide(){
	PopWindowManager::get_instance2()->isPaused=false;
}

int IPopWindow::GetPriorityByCurWindowDef(std::string key){
	int priority= ClientConstDataManager::get_instance2()->getValueByKey(key.c_str());
	return priority;
}