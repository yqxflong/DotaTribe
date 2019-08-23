//Name：AthleticProcedureDataHandler
//Function：战斗过程指令管理器
//Author:	Johny

#ifndef   _DOTATRIBE_ATHLETICPROCEDUREDATAHANDLER_H_ 
#define   _DOTATRIBE_ATHLETICPROCEDUREDATAHANDLER_H_

#include   <include/common/Singleton.h>
#include   "../include/IDataHandler.h"
#include   "../include/AthleticProcedureDataType.h"
#include   <set>

class   AthleticProcedureDataHandler: public IDataHandler,public cobra_win::Singleton2<AthleticProcedureDataHandler>
{
public: 
	 int  athleticsSerialID;								//战斗序列ID

	 char athleticsBattleType;								//战斗类型
	  
	 bool isReTryBattle;									//战败后 重新战斗

	 bool isDuriningLocal;									//是否处于Cache

	 bool isUsingLocalDataReplace;							//是否采用替换模式

	 PreMapInfoData			    preMapInfoData;			    //发起请求的地图信息	（注意区别之后的数据） 用于判断NPCTalk显示逻辑	

	 PAthleticsMapInfo			pAthleticsMapInfo;			//战斗地图信息

	 PPreAthleticsData          pPreAthleticsData;			//战斗单位信息(战前人物信息数据)

	 PAthleticsProData          pAthleticProData;			//全战斗过程信息数据

  	 PAthleticsResultData       pAthleticResultData;		//战斗结果信息数据

	 PAthleticsBaseReward       pAthleticBaseReward;        //战斗奖励信息数据

	 /*
	  在此预分析战报提取技能和技能特效和场景特效
	 */
	 std::map<int,std::set<int> > athleticsPlayerSkillsPool;	//预分析人物技能池
	 std::map<int,std::set<int> > athleticsMonsterSkillsPool;	//预分析怪物技能池

	 std::vector<RoleShapeInfo>	  athleticsPlayerShapePool;		//预分析人物外形池
	 std::vector<RoleShapeInfo>	  athleticsMonsterShapePool;	//预分析怪物外形池
	 std::map<int,std::set<int> > athleticsShapeSkillsPool;		//预分析外形技能组

	 std::map<int,std::set<int> > athleticsPlayerActionPool;	//预分析玩家动作池
	 std::map<int,std::set<int> > athleticsMonsterActionPool;	//预分析怪物动作池
	 std::map<int,std::set<int> > athleticsShapeActionsPool;	//预分析外形受击动作池   //追加
	  
	 std::set<int>				  athleticsCompositeEffectPool;	//预分析组合特效ID池
	 std::set<std::string>		  athleticsEffectPlistPool;		//预分析特效纹理池
	 int						  athleticsSceneID;				//预分析的场景ID
	  
	   
public:
	AthleticProcedureDataHandler();
	~AthleticProcedureDataHandler();

	/*
		销毁接口
	*/
	virtual void onDestroy();

	/*
	   销毁战斗内存数据
	*/
	virtual void DestroyMemData();

	/*
		初始化接口
	*/
	virtual bool init();
	 
	/*
	 加入预分析技能池
	*/
	void   pushSkillsPool(char roleType,int roleID,int skillID);

	/*
	加入预分析动作池
	*/
	void   pushActionsPool(char roleType,int roleID,int actionID);

	/*
	加入预分析的特效池
	*/
	void   pushEffectsPool(int effectID);
	/*
	加入预分析的场景ID
	*/
	void    pushSceneID(int sceneID);

	/*
	加入预加载的帧动画Plist文件
	*/
	void   pushAnimationPlistPool(std::string plistName);

	/*
	加入角色外形池
	*/
	void    pushRoleShapesPool(char roleType,int roleID,int shapeID);
	/*
	开始分析外形技能组
	*/
	void    startAnalysisShapeSkillsArray();

	/*
	导出角色外形ShapeID
	*/
	void    exportAthleticsShapeArray(std::set<int> & rolesShapeArray);

	/*
	获取跳过战斗的VIP等级
	*/
	int    getSkipAthleticVIPLevelByType(char athleticType); 
public:
	friend   class   cobra_win::Singleton2<AthleticProcedureDataHandler>;
};

#define   ATHLETICPROCEDUREDATA			(AthleticProcedureDataHandler::get_instance2())
 
#endif