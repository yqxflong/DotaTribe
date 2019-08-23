//Author: xiaobo.wu
//Description:  技能面板数据层
//Date:  2013.06.30 
#include      "../include/SelectSkillMode.h"
#include      "../include/SkillTableDataManager.h"
#include      "../include/InputCommand.h"
#include      "../include/ResourceIDDataManager.h"
#include      "../include/CSChangeSkillsPacket.h"
#include      "../include/EventSystem.h"
#include      "../include/EventTyper.h"
#include	  "../include/NFControlsManager.h"
 
 
 
SelectSkillMode::SelectSkillMode()
{ 
	pSelectSkillController=NULL;
    pCommonSkillDataArray=NULL;
	pSkillsData=NULL;
	m_HeroIndex = 0;
	dynamicActiveSkills.clear();
		 
}
 

SelectSkillMode::~SelectSkillMode()
{
    Destroy();
}

 
SelectSkillMode *  SelectSkillMode::createSelectSkillModeWithController(SelectSkillController * selectSkillController)
{
	 SelectSkillMode * pSelectSkillMode=new SelectSkillMode();
	 if(pSelectSkillMode&&pSelectSkillMode->InitSelectSkillModeWithController(selectSkillController))
	 {
		 return  pSelectSkillMode;
	 }
	 if(pSelectSkillMode!=NULL)
	 {
		 delete pSelectSkillMode;
		 pSelectSkillMode=NULL;
	 }
	 return NULL;
}


bool   SelectSkillMode::InitSelectSkillModeWithController(SelectSkillController * selectSkillController)
{   
	do 
	{  
		if(selectSkillController==NULL)
			break; 

		pSelectSkillController=selectSkillController;
		m_HeroIndex = pSelectSkillController->m_heroIndex;
		if(!OnUpdateLocalSkillData())
		{
			this->Destroy(); 
			break ;
		}

		return true;
 
	} while (0);

	return false;
}





void  SelectSkillMode::Destroy()
{
	//销毁动态资源
    if(pCommonSkillDataArray!=NULL)
	{
		for(int i =0 ; i< MAX_SKILLPANEL_COLUMN; i++)
		{
             delete [] pCommonSkillDataArray[i];
			 pCommonSkillDataArray[i]=NULL;
		}
		delete [] pCommonSkillDataArray;
		pCommonSkillDataArray=NULL;
	}
}


/*
 安装新的技能
 param1 :  凹槽索引 从0开始
 param2 :  技能ID
*/

void  SelectSkillMode::AddEquipSkillVectorWithID(int notchID,int skillItemID)
{
	size_t  equipSkillCount=GetNotchSkillEquipVec().size();
	for(size_t index=0;index<equipSkillCount;index++)
	{
		if(GetNotchSkillEquipVec().at(index)->skillID==skillItemID&&GetNotchSkillEquipVec().at(index)->index==notchID)
		{
			return ;
		}
	}
	 
	//发送通知消息
	if(pSelectSkillController!=NULL)
	{
		//通知网络层  
		EventSystem::get_instance2()->PushEvent2(_TYPED_EVENT_SHOW_COMMUNICATIONWAITTINGWIN_);  
		CSChangeSkillsPacket  dataPacket(0,skillItemID,_DEFAULT_SKILL_ITEMID_,notchID,m_HeroIndex);
		dataPacket.Send();
	}
 
}

void  SelectSkillMode::RemoveEquipSkillVectorWithID(int skillItemID)
{ 
	size_t equipSkillCount=GetNotchSkillEquipVec().size();
    //删除数据
	std::vector<PSkillNotoch>::iterator  iter_erase=GetNotchSkillEquipVec().begin();
	while(iter_erase!=GetNotchSkillEquipVec().end())
	{
		if((*iter_erase)->skillID==skillItemID)
		{ 
			EventSystem::get_instance2()->PushEvent2(_TYPED_EVENT_SHOW_COMMUNICATIONWAITTINGWIN_);  
			CSChangeSkillsPacket  dataPacket(1,skillItemID,(*iter_erase)->index,-1,m_HeroIndex);
			dataPacket.Send();
			break;
		}
		iter_erase++;
	} 
	 
 
}

bool   SelectSkillMode::UpdateEquipSkillVectorWithID(bool isInstall,int skillItemID,int notchID)
{
    //判断当前是否已经安装技能
    if(isInstall)
	AddEquipSkillVectorWithID(notchID,skillItemID);
	else
	RemoveEquipSkillVectorWithID(skillItemID);

	return true;
 
}


std::string SelectSkillMode::GetSkillIconNameFromSkillID(int skillItemID)
{
   	SkillTableData * pSkillTableDataItem=SkillTableDataManager::get_instance2()->GetSkillTableDataByID(skillItemID);
	if(pSkillTableDataItem!=NULL)
	{
		int skillIconID=pSkillTableDataItem->skillItemIconID;
		return ResourceIDDataManager::get_instance2()->getDataByID(skillIconID);
	}
	return "";
}
 



bool   SelectSkillMode::ChangeEquipSkillWithID(int fromSkillItemID,int toNotchiID)
{ 
	size_t  equipSkillCount=GetNotchSkillEquipVec().size();
    int  fromSkillVectorIndex=-1;
	int  toSkillVectorIndex=-1;
	FOR_EACH_ELEMENT_BEGIN(equipSkillCount)
	if(GetNotchSkillEquipVec().at(index)->skillID==fromSkillItemID)
	 fromSkillVectorIndex=index;
	if(GetNotchSkillEquipVec().at(index)->index==toNotchiID)
	 toSkillVectorIndex=index;
	FOR_EACH_ELEMENT_END

	if(fromSkillVectorIndex==toSkillVectorIndex)
		return  false;

	if(toSkillVectorIndex<0||fromSkillVectorIndex<0)
		return  false;
 
	//发送网络事件通知 
	CSChangeSkillsPacket  dataPacket(2,fromSkillItemID,GetNotchSkillEquipVec().at(fromSkillVectorIndex)->index,GetNotchSkillEquipVec().at(toSkillVectorIndex)->index,m_HeroIndex);
	dataPacket.Send();
 
	//添加Loading遮罩层
	EventSystem::get_instance2()->PushEvent2(_TYPED_EVENT_SHOW_COMMUNICATIONWAITTINGWIN_);  
	
    return true;
}



void  SelectSkillMode::OnCommandHandler(int eventType,void * ptr)
{

}



std::vector<PSkillNotoch> &  SelectSkillMode::GetNotchSkillEquipVec()
{ 
    return pSkillsData->skillNotchList;
}
 
std::vector<PSkillItem> &  SelectSkillMode::GetServerSkillsDataVec()
{
	return pSkillsData->skillBagList;
}


void  SelectSkillMode::UpdateRoleSkillsData()
{

}
 

/*
	 从内存中获得背包技能
*/
bool   SelectSkillMode::GetRoleSkillsFromSkillsHandler()
{
    if(NFC_GetHeroSkillManager(pSelectSkillController->m_heroIndex)!=NULL)
	{
        pSkillsData=NFC_GetHeroSkillManager(pSelectSkillController->m_heroIndex)->getRoleSkillsData();
		if(pSkillsData!=NULL)
		{
			GetActiveSkillFromSkillsHandler();
			return true;
		}
	}	 
	return false;
}


void  SelectSkillMode::GetActiveSkillFromSkillsHandler()
{
	if(pSkillsData!=NULL)
	{
		dynamicActiveSkills.clear();
		size_t bagSkillCount=pSkillsData->skillBagList.size();
		bool ispro=false;
		for(size_t skillIndex=0;skillIndex<bagSkillCount;skillIndex++)
		{
			PSkillItem pSkillItem=pSkillsData->skillBagList.at(skillIndex);
			if(pSkillItem!=NULL)
			{	
				ispro=pSkillItem->ispro==1 ? true:false;
				dynamicActiveSkills.insert(std::map<short,bool>::value_type(pSkillItem->skillID,ispro));
			}
		}
	}
}


bool  SelectSkillMode::CheckSkillsDataFromMemory()
{
	if(NFC_GetHeroSkillManager(pSelectSkillController->m_heroIndex)!=NULL)
	{
		pSkillsData=NFC_GetHeroSkillManager(pSelectSkillController->m_heroIndex)->getRoleSkillsData();
		if(pSkillsData!=NULL)
			return true;
	}
	return false;
}


bool  SelectSkillMode::OnUpdateLocalSkillData(bool isNeedPostUpdateUI/* =false */)
{
	 if(!CheckSkillsDataFromMemory())
		 return false;
 
	//alloc本地技能数据数组
	 if(pCommonSkillDataArray!=NULL)
	 {
		 for(int i =0 ; i< MAX_SKILLPANEL_COLUMN; i++)
		 {
			 delete [] pCommonSkillDataArray[i];
			 pCommonSkillDataArray[i]=NULL;
		 }
		 delete [] pCommonSkillDataArray;
		 pCommonSkillDataArray=NULL;
	 }
	  
	pCommonSkillDataArray=new PCOMMONSKILLDATA[MAX_SKILLPANEL_COLUMN];
    for(int i = 0 ; i < MAX_SKILLPANEL_COLUMN ;i++)
	{ 
		pCommonSkillDataArray[i]=new COMMONSKILLDATA[MAX_SKILLPANEL_ROW];
		if(pCommonSkillDataArray[i]==NULL)
		{
			return false;
		}
	} 
	size_t skillItemCount=GetServerSkillsDataVec().size();

	FOR_EACH_ELEMENT_BEGIN(skillItemCount)
		PSkillItem  pSkillItem=GetServerSkillsDataVec().at(index);
	    if(pSkillItem!=NULL)
		{
            SkillTableData * pSkillTableDataItem=SkillTableDataManager::get_instance2()->GetSkillTableDataByID(pSkillItem->skillID);
			if(pSkillTableDataItem!=NULL)
			{
				if(pSkillTableDataItem->skillItemClientYPos==0&&pSkillTableDataItem->skillItemClientXPos==0)
					continue ;
				if(pSkillTableDataItem->skillItemClientYPos<=MAX_SKILLPANEL_COLUMN&&pSkillTableDataItem->skillItemClientXPos<=MAX_SKILLPANEL_ROW)
				{
					pCommonSkillDataArray[pSkillTableDataItem->skillItemClientYPos-1][ pSkillTableDataItem->skillItemClientXPos-1].skillIconID=pSkillTableDataItem->skillItemIconID;
					pCommonSkillDataArray[pSkillTableDataItem->skillItemClientYPos-1][ pSkillTableDataItem->skillItemClientXPos-1].skillItemID=pSkillTableDataItem->skillItemID_;
					if(pSkillItem->isActive==_SUCCESS_VALUE_FROM_SERVER_)
					{
						pCommonSkillDataArray[pSkillTableDataItem->skillItemClientYPos-1][ pSkillTableDataItem->skillItemClientXPos-1].skillIconID=pSkillItem->skillIconID;
						pCommonSkillDataArray[pSkillTableDataItem->skillItemClientYPos-1][ pSkillTableDataItem->skillItemClientXPos-1].isActiveSkill=true;
						if(pSkillItem->ispro==_SUCCESS_VALUE_FROM_SERVER_)
						{
							pCommonSkillDataArray[pSkillTableDataItem->skillItemClientYPos-1][ pSkillTableDataItem->skillItemClientXPos-1].isAdeptSkill=true;
						}
					}
				}
			}
		}
    FOR_EACH_ELEMENT_END
 	

	if(isNeedPostUpdateUI&&pSelectSkillController)
	{ 
		 pSelectSkillController->onCommandHandler(_TYPED_INPUT_COMMAND_LOADCOMMONSKILLDATA_END_,NULL);
		 pSelectSkillController->onCommandHandler(_TYPED_INPUT_COMMAND_SELECTSKILLDATA_MODIFY_,NULL);
 	}

	return true;

}

//////////////////////////////////////////////////////////////////////////


PSkillItem    SelectSkillMode::GetSkillsBagInfoFromID(int skillItemID)
{
	 if(pSkillsData!=NULL)
	 {
		 size_t  skillCount=pSkillsData->skillBagList.size();
		 FOR_EACH_ELEMENT_BEGIN(skillCount)
		 PSkillItem  pSkillItem=pSkillsData->skillBagList.at(index);
		 if(pSkillItem!=NULL&&pSkillItem->skillID==skillItemID)
		 {
             return pSkillItem;
		 }
		 FOR_EACH_ELEMENT_END
	 }
	 return NULL;
}

PSkillNotoch  SelectSkillMode::GetSkillsTargetInfoFromID(int skillItemID)
{
	if(pSkillsData!=NULL)
	{
		size_t  skillCount=pSkillsData->skillNotchList.size();
		FOR_EACH_ELEMENT_BEGIN(skillCount)
		   PSkillNotoch  pSkillNotch=pSkillsData->skillNotchList.at(index);
		   if(pSkillNotch!=NULL&&pSkillNotch->skillID==skillItemID)
		   {
               return pSkillNotch;
		   }
		FOR_EACH_ELEMENT_END
	}
	return NULL;
}



PCOMMONSKILLDATA *  SelectSkillMode::GetCommonSkillDataArray()
{
    return   pCommonSkillDataArray;
}

 