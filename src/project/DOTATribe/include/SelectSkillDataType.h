#ifndef  _DOTATRIBE_SELECTSKILLDATATYPE_H_
#define  _DOTATRIBE_SELECTSKILLDATATYPE_H_  

//Author: xiaobo.wu
//Description:  技能面板数据类型
//Date:  2013.06.30 
 
#define   FOR_EACH_ELEMENT_BEGIN(count)   for(size_t index=0;index<count;index++) {

#define   FOR_EACH_ELEMENT_END		}

#define   MAX_NOTCH_NUM				  6		    //技能凹槽数	
#define   MAX_SKILLPANEL_ROW		  10        //横列
#define   MAX_SKILLPANEL_COLUMN		  4		    //纵列


//本地技能数据结构体
typedef  struct commonskilldata_tag
{
	int skillItemID;
	int skillIconID;
	bool isActiveSkill;
	bool isAdeptSkill;
public:
	commonskilldata_tag()
	{
		skillItemID=-1;
		skillIconID=-1;
		isActiveSkill=false;
		isAdeptSkill=false;
	}
}COMMONSKILLDATA,*PCOMMONSKILLDATA;

 
#endif

