﻿#ifndef  _DOTATRIBE_PACKETTYPER_H_
#define  _DOTATRIBE_PACKETTYPER_H_

/*
	[2字节包头][4字节数据长度][2字节协议号][(长度-8)个字节的数据]
*/
enum
{

	_TYPED_PACKET_UNKOWN_,
		
	_TYPED_PACKET_C2S_ACCOUNT_REGISTER_ = 200,						//c->s帐号注册请求
	_TYPED_PACKET_S2C_ACCOUNT_REGISTER_ = 201,						//s->c账号注册确认

	_TYPED_PACKET_C2S_ACCOUNTATTESTATION_ = 202,					//c - s,账号认证请求
	_TYPED_PACKET_S2C_ACCOUNTATTESTATION_ = 203,					//s - c,账号认证返回

	_TYPED_PACKET_C2S_ACCOUNT_BIND_ = 204,							//c - s,账号绑定请求
	_TYPED_PACKET_S2C_ACCOUNT_BINDRESULT_ = 205,					//s - c,账号绑定返回

	_TYPED_PACKET_C2S_DISCONNECT_CLIENT_ = 206,						//c - s,请求断开网络

	_TYPED_PACKET_C2S_LOGIN_P_=209,									//c->s登陆
	_TYPED_PACKET_S2C_LOGIN_P_=210,									//s->c登陆

	_TYPED_PACKET_C2S_PAYITEMLIST_CLIENT_ = 211,						//c - s,请求充值列表
	_TYPED_PACKET_S2C_PAYITEMLIST_RESULT_ = 212,						//s - c,充值列表返回

	_TYPED_PACKET_C2S_PAYCHECK_CLIENT_ = 215,							//c - s,充值确认
	_TYPED_PACKET_S2C_PAYCHECK_RESULT_ = 216,							//s - c,充值确认返回

	_TYPED_PACKET_C2S_PAY_CREATEOREDER_FORPP_CLIENT_ = 217,				//c - s,创建订单（给PP助手这个怪胎）
	_TYPED_PACKET_S2C_PAY_CREATEOREDER_RESULT_ = 218,					//s - c,创建订单返回

	_TYPED_PACKET_C2S_NETDEBUG_LOGIN_DURING_=301,					//c->s 客户端登陆耗时debug
	
	_TYPED_PACKET_C2S_CLIENT_ACTIVE_=303,							//c->s 客户端激活

	_TYPED_PACKET_C2S_QUICKLOGIN_=500,								//c->s请求快速登录
	_TYPED_PACKET_S2C_QUICKLOGINRESULT_=501,						//s->c快速登录返回信息

	_TYPED_PACKET_S2C_FORCEDISCONNECT_ = 1000,				//s->无条件断开连接

	_TYPED_PACKET_C2S_REGISTERACCOUNT_ = 1001,						//c->s帐号注册请求
	_TYPED_PACKET_S2C_REGISTERACCOUNT_ = 1002,						//s->c账号注册确认

	_TYPED_PACKET_C2S_CREATEROLE_=1003,		    //c->s创建角色			['Z''R'][n][1003][int序列号][int账号ID][int英雄ID][string角色名称]
	_TYPED_PACKET_S2C_ROLEINFO_=1004,			//s->c返回角色信息	

	_TYPED_PACKET_C2S_ENTER_TRANSCRIPT_=1008,	 //C -->> S 进入副本 请求协议     ['Z''R'][n][1009][int序列号]

	_TYPED_PACKET_S2C_ATHLETICSDATA_=1009,		 //S -->> C 战斗数据协议指令回执  ['Z''R'][n][1009][int序列号]

	_TYPED_PACKET_C2S_MISSION_=1010,				//c->s进入关卡选择				['Z''R'][n][2100][int序列号][int地图ID]
	_TYPED_PACKET_S2C_MISSIONRESULT_=1011,			//s->c关卡选择信息		

	_TYPED_PACKET_S2C_SERVERMESSAGE_ = 1012,

	_TYPED_PACKET_C2S_CHANGESKILLS_=1013,			//C -> S 选择技能

	_TYPED_PACKET_S2C_SELECTSKILLSREULT_=1014,      //S -> C 技能返回

	//_TYPED_PACKET_C2S_UPDATEMISSION_=1014,				//c->s更新关卡信息				['Z''R'][n][2100][int序列号] 
	_TYPED_PACKET_S2C_UPDATEMISSIONRESULT_=1015,			//s->c更新关卡信息		

	_TYPED_PACKET_C2S_MASSACRE_=1016,				//c->sl				['Z''R'][n][2100][int序列号] 
	_TYPED_PACKET_S2C_MASSACRERESULT_=1017,			//s->c接收扫荡信息				

	_TYPED_PACKET_S2C_REFRESHINFODATA_ = 1018,		//同步玩家信息	add by fangjun

	_TYPED_PACKET_C2S_CHAT_ = 1019,						//c->s发送聊天信息
	_TYPED_PACKET_S2C_CHATRESULT_ = 1020,				//s->c接收聊天信息

	_TYPED_PACKET_C2S_SALEOBJECT_ = 1021,		//c - s,出售物品
	_TYPED_PACKET_S2C_SALEOBJECT_ = 1022,		//s - c,出售成功

	_TYPED_PACKET_C2S_USEOBJECT_ = 1023,		//c - s,使用物品
	_TYPED_PACKET_S2C_USEOBJECT_ = 1024,		//s - c,使用成功


	_TYPED_PACKET_C2S_PERSONALCHAT_  = 1025,	//c->s发送聊天信息(名字)

	_TYPED_PACKET_C2S_HEARTBEAT_ = 1026,			//c->s,心跳包
	_TYPED_PACKET_S2C_HEARTBEATRESULT_ = 1027,		//s->c,心跳包结果

	_TYPED_PACKET_S2C_GETITEM_ = 1028,		//s->c,获得新物品

	_TYPED_PACKET_C2S_ROLELIST_ = 1030,		//c - s,游戏角色列表请求
	_TYPED_PACKET_S2C_ROLELIST_ = 1031,		//s - c，游戏角色列表返回
	
	_TYPED_PACKET_C2S_ENTERGAME_ = 1032,	//c - s,请求进入游戏
	
	_TYPED_PACKET_C2S_FAST_REGISTER_CLIENT_  = 1033,	//c - s,请求进入游戏
	_TYPED_PACKET_S2C_FAST_REGISTER_SERVER_  = 1034,	//s - c,请求进入游戏

	_TYPEF_PACKET_S2C_COMMON_QA_SERVER_=1035,			//S -C  服务器发过来提问信息
	_TYPEF_PACLET_C2S_COMMON_QA_CLIENT_=1036,			//C -S  发给服务器的提问回执消息

	_TYPED_PACKET_C2S_OPEN_LOCKBAG_ = 1037,				//c->s 发送给服务器开包格信息

	_TYPED_PACKET_C2S_GUIDE_MODULE_ = 1038,				//c->s 新手引导下一个模块

	_TYPED_PACKET_C2S_RESET_SKILLS_CLIENT_=1039,		//C - S 发起重置技能请求

	_TYPED_PACKET_C2S_RESET_SKILLS_SERVER_=1040,	    //S - C 服务器返回重置技能

	_TYPED_PACKET_C2S_ARENA_RANK_INFO_CLIENT_=1041,		//C- S  请求竞技场排行榜

	_TYPED_PACKET_S2C_ARENE_RANK_INFO_SERVER_=1042,     //S- C  服务器返回竞技场排行榜

	_TYPED_PACKET_C2S_FRIEND_ = 1043,							//好友信息
	_TYPED_PACKET_S2C_FRIENDA_RESULT_ = 1044,					//返回信息

	_TYPED_PACKET_C2S_FRIENDCHECKPLAYERINFO_ = 1045,			//查看玩家信息
	_TYPED_PACKET_S2C_FRIENDCHECKPLAYERINFO_RESULT_ = 1046,		//返回信息

	_TYPED_PACKET_C2S_FRIENDDELETE_ = 1047,						//删除好友
	_TYPED_PACKET_S2C_FRIENDDELETE_RESULT_ = 1048,				//返回信息

	_TYPED_PACKET_C2S_FRIENDAGREESINGLE_ = 1049,				//同意加为好友（单人）
	_TYPED_PACKET_S2C_FRIENDAGREESINGLE_RESULT_ = 1050,			//返回信息

	_TYPED_PACKET_C2S_FRIENDIGNORESINGLE_ = 1051,				//忽略申请（单人）
	_TYPED_PACKET_S2C_FRIENDIGNORESINGLE_RESULT_ = 1052,		//返回信息

	_TYPED_PACKET_C2S_FRIENDAGREEALL_ = 1053,					//同意加为好友（全体）
	_TYPED_PACKET_S2C_FRIENDAGREEALL_RESULT_ = 1054,			//返回信息

	_TYPED_PACKET_C2S_FRIENDIGNOREALL_ = 1055,					//忽略申请（全体）
	_TYPED_PACKET_S2C_FRIENDIGNOREALL_RESULT_ = 1056,			//返回信息

	_TYPED_PACKET_C2S_FRIENDADD_ = 1057,						//申请加好友
	_TYPED_PACKET_S2C_FRIENDADD_RESULT_ = 1058,					//返回信息

	_TYPED_PACKET_C2S_FRIENDREFURBISH_ = 1059,					//刷新推荐好友
	_TYPED_PACKET_S2C_FRIENDREFURBISH_RESULT_ = 1060,			//返回信息


	_TYPED_PACKET_C2S_FRIENDFIGHE_ = 1061,						//好友切磋
	//_TYPED_PACKET_S2C_FRIENDFIGHE_RESULT_ = 1062,				//返回信息

	_TYPED_PACKET_C2S_FRIENDFRINDFRIEND_ = 1062,				//查找好友
	_TYPED_PACKET_S2C_FRIENDFRINDFRIEND_RESULT_ = 1063,			//返回信息

	_TYPED_PACKET_C2S_EMAILLIST_=1070,		//c->s查询邮件列表
	_TYPED_PACKET_S2C_EMAILLIST_=1071,		//s->c查询邮件列表
	_TYPED_PACKET_C2S_EMAILSEND_=1072,		//c->s发送邮件
	_TYPED_PACKET_S2C_EMAILSEND_=1073,		//s->c发送邮件
	_TYPED_PACKET_C2S_EMAILGETATT_=1074,		//c->s一键获得附件
	_TYPED_PACKET_S2C_EMAILGETATT_=1075,		//s->c一键获得附件
	_TYPED_PACKET_C2S_EMAILREMOVE_=1076,		//c->s删除邮件
	_TYPED_PACKET_S2C_EMAILREMOVE_=1077,		//s->c删除邮件

	_TYPED_PACKET_C2S_CHECK_EMAIL_=1078,		    //c->s查看邮件请求
	_TYPED_PACKET_S2C_CHECK_EMAIL_RESULT=1079,	   //s->c查看邮件返回

	_TYPED_PACKET_S2C_MESSAGE_PROMPT_SERVER_=1080, //服务器推送消息

	_TYPED_PACKET_C2S_LOGINNOTICE_=1081,//c->s登陆公告
	_TYPED_PACKET_S2C_LOGINNOTICE_=1082,//s->c登陆公告

	_TYPED_PACKET_C2S_ARENA_INFO_CLINET_ = 1100,		//c - s 请求竞技场信息
	_TYPED_PACKET_S2S_ARENA_INFO_SERVER_ = 1101,		//s - c 服务器返回竞技场信息

	_TYPED_PACKET_C2S_ARENA_CHALLENGE_CLIENT_=1102,		//c - s 挑战请求

	_TYPEF_PACKET_C2S_ARENA_HISTORY_BATTLEINFO_CLEINT_=1103, //c - s 查看历史战斗信息请求

	_TYPEF_PACKET_C2S_ARENA_CLEAR_COLLDOWNTIME_CLIENT_=1104,  //s - c 发送清除冷却时间请求
		
	_TYPEF_PACKET_S2C_ARENA_CLEAR_COLLDOWNTIME_SERVER_=1105,  //c- s  服务器返回的冷却时间回执信息

	_TYPEF_PACKET_C2S_ARENA_ADD_CHALLENGECOUNT_CLIENT_=1106,  //c- s  发送增加挑战次数 

	_TYPEF_PACKET_S2C_ARENA_ADD_CHALLENGECOUNT_SERVER_=1107,  //s - c 服务器回执增加挑战次数消息

	_TYPED_PACKET_C2S_ARENA_GET_REWARD_CLIENT_=1108,		  // c - s 发送请求指令

	_TYPED_PACKET_S2C_ARENA_GET_REWARD_SERVER_=1109,	      //s -c  接受回执指令

	_TYPED_PACKET_C2S_ARENA_REWARD_CLIENT_=1110,			  // c - s  发送竞技场奖励请求

	_TYPED_PACKET_S2C_ARENA_REWARD_SERVER_=1111,			  // s - c  服务器回执奖励

	_TYPED_PACKET_C2S_ARENA_GET_CHALLENGECOUNT_REWARD_=1112,  // c - s 获取奖励申请
		
	_TYPED_PACKET_S2C_ARENA_GET_CHALLENGECOUNT_REWARD_=1113,  // s - c 奖励获取回执

	_TYPED_PACKET_C2S_ENTER_MAINTASK_ = 1200,					//客户端发起任务请求
	_TYPED_PACKET_S2C_ENTER_MAINTASK_RESULT = 1201,				//服务器任务信息回执

	_TYPED_PACKET_C2S_FINISH_MAINTASK_ = 1202,					//客户端发起任务奖励
	_TYPED_PACKET_S2C_FINISH_MAINTASK_RESULT_ = 1203,			//服务器回执新任务

	_TYPED_PACKET_C2S_QUERY_LACTIVITY_ = 1204,					//C->S获取活动列表
	_TYPED_PACKET_S2C_QUERY_LACTIVITY_ = 1205,					//S->C获取活动列表
	_TYPED_PACKET_C2S_GETAWARD_LACTIVITY_ = 1206,				//C->S获取奖励
	_TYPED_PACKET_S2C_GETAWARD_LACTIVITY_ = 1207,				//S->C获取奖励
	  
	_TYPED_PACKET_S2C_TASK_GETREWARD_PROMPT_SERVER_=1208,		//S-C 服务器推送的领取任务奖励

	_TYPED_PACKET_C2S_DIALIG_TASK_REWARD_CLIENT_=1209,			//S-C 强弹框的奖励领取

	_TYPED_PACKET_C2S_HERO_INFO_CLIENT_=1210,					//C-S 请求查看英雄信息

	_TYPED_PACKET_S2C_HERO_INFO_SERVER_=1211,					//S-C 服务返回英雄信息
	 
	_TYPED_PACKET_C2S_REPLACE_HERO_CLIENT_=1212,				//C-S 请求更换当前英雄

	_TYPED_PACKET_S2C_REPLACE_HERO_SERVER_=1213,				//S-C 服务器 回应 英雄更换请求
	  
	_TYPED_PACKET_C2S_LEADERSHIPLVUP_=1214,			//c->s 统率力升级请求
	_TYPED_PACKET_S2C_LEADERSHIPLVUP_=1215,			//s->c 统率力升级请求

	_TYPED_PACKET_C2S_HERO_ADVANCED_REQUIRE_CLIENT_=1216,		//C-S  请求进阶所需信息

	_TYPED_PACKET_S2C_HERO_ADVANCE_REQUIRE_SERVER_=1217,		//S-C  服务器返回进阶所需信息

	_TYPED_PACKET_C2S_HERO_ADVANCE_CLIENT_=1218,				//C-S  请求英雄进阶

	_TYPED_PACKET_S2C_HERO_ADVANCE_SERVER_=1219,				//S-C  服务器返回英雄进阶

	_TYPED_PACKET_C2S_HERO_VIPINFO_CLIENT_=1220,				//C-S  请求VIP信息

	_TYPED_PACKET_S2C_HERO_VIPINFO_RESULT_=1221,				//S-C  服务器返回VIP信息

	_TYPED_PACKET_C2S_BUY_ENERGY_=1222,							//C-S		购买体力
	_TYPED_PACKET_S2C_BUY_ENERGY_RESULT_=1223,					//S-C		购买体力返回

	_TYPED_PACKET_C2S_HERO_GETREWARD_CLIENT_=1224,				//C-S  请求VIP奖励领取

	_TYPED_PACKET_S2C_HERO_GETREWARD_RESULT_=1225,				//S-C  服务器返回VIP奖励领取

	_TYPED_PACKET_C2S_CLEAR_MAPTIMES_ = 1226,						//C->C请求清除次数
	_TYPED_PACKET_S2C_CLEAR_MAPTIMES_RESULT_ = 1227,				//S->C清除次数成功返回
	_TYPED_PACKET_C2S_BUY_HUNT_TIME_ = 1228,					//C->S	购买寻宝次数
	_TYPED_PACKET_S2C_BUY_HUNT_TIME_RESULT_ = 1229,				//S->C	购买寻宝次数返回
	_TYPED_PACKET_C2S_BUY_CLIMBTOWER_TIME_ = 1230,				//c->s	购买爬塔次数	 
	_TYPED_PACKET_S2C_BUY_CLIMBTOWER_TIME_RESULT_ = 1231,		//s->c	购买爬塔次数返回

	_TYPED_PACKET_C2S_NEWFUNCOPEN_FINISH_=  1232,				//c->s  通知服务器完成的新功能开启

	_TYPED_PACKET_S2C_UPDATAFRIEND_RESULT_ =1233,				//c->s 好友列表更新

	_TYPED_PACKET_C2S_EXCHANGE_CDKEY_ = 1234,					//c->s  兑换码兑换
	_TYPED_PACKET_S2C_EXCHANGE_CDKEY_RESULT_ = 1235,			//s->c  兑换码兑换结果



	_TYPED_PACKET_C2S_CHANGEEQUIP_=2003,	    //c->s更换装备			['Z''R'][n][2003][int序列号][int装备ID]  
	_TYPED_PACKET_S2C_CHANGEEQUIP_=2004,        //s->c换装后角色信息
																							/*
																							* 失败 ['Z''R'][n][2004][int序列号][int -1][string failureInfo]
																							* 成功 ['Z''R'][n][2004][int序列号][int  1][int count]{[byte type][int attrvalue]}
																							*/
	_TYPED_PACKET_C2S_CHANGESKIN_=2005,			//c->s更换外套			['Z''R'][n][2005][int序列号][int外套ID]  
	_TYPED_PACKET_S2C_CHANGESKIN_=2006,			//s->c换外套后角色信息
																							/*
																							* 失败 ['Z''R'][n][2006][int序列号][int -1][string failureInfo]
																							* 成功 ['Z''R'][n][2006][int序列号][int  1][int count]{[byte type][int attrvalue]}
																							*/
	_TYPED_PACKET_C2S_OFFEQUIP_=2007,			//c->s卸掉装备			['Z''R'][n][2007][int序列号][int装备ID] 
	_TYPED_PACKET_S2C_OFFEQUIP_=2008,			//s->c卸掉装备后的角色信息
																							/*
																							* 失败 ['Z''R'][n][2008][int序列号][int -1][string failureInfo]
																							* 成功 ['Z''R'][n][2008][int序列号][int  1][byte count]{[byte type][int attrvalue]} 
																						    */


	//_TYPED_PACKET_C2S_LEVELUP_,				//c->s升级请求					
	_TYPED_PACKET_C2S_LEVELUPRESULT_ =2010,		//c->s升级信息返回				['Z''R'][n][2100][int序列号][short等级][int技能1ID][int技能2ID][int新增天赋点数][int专精技能ID]																					 
																								



	_TYPED_PACKET_C2S_CREATEROLERANDOMNAME_=2017,				//c->s请求人物名称				['Z''R'][n][2100][int序列号] 
	_TYPED_PACKET_S2C_CREATEROLERANDOMNAMERESULT_=2018,			//s->c接收人物名称				['Z''R'][n][2100][int序列号][string名字]	


	_TYPED_PACKET_C2S_SKINSTRENMAIN_=2011,							//c->s开始强化外套
	_TYPED_PACKET_S2C_SKINSTRENMAIN_=2012,							//s->c强化外套结果
	_TYPED_PACKET_C2S_SKINSTRENCONDITION_=2013,						//c->s请求强化外套的条件
	_TYPED_PACKET_S2C_SKINSTRENCONDITION_=2014,						//s->c回应强化外套条件
	

	_TYPED_PACKET_C2S_HEROLEVELUP_=2025,							//c->s请求外套升级
	_TYPED_PACKET_S2C_HEROLEVELUPRESULT_=2026,						//s->c回应外套升级

	_TYPED_PACKET_C2S_EQUIPMENTLVUP_ = 2027,						//c->s装备升级
	_TYPED_PACKET_S2C_EQUIPMENTLVUP_RESULT_ = 2028,					//s->c装备升级结果


	_TYPED_PACKET_C2S_ATTRIBUTELOCK_ = 2029,						//c->s属性锁定
	_TYPED_PACKET_S2C_ATTRIBUTELOCKRESULT_ = 2030,					//s->c属性锁定结果

	_TYPED_PACKET_C2S_ATTRIBUTEUNLOCK_ = 2031,						//c->s属性解锁
	_TYPED_PACKET_S2C_ATTRIBUTEUNLOCKRESULT_ = 2032,				//s->c属性解锁结果

	_TYPED_PACKET_C2S_EQUIPTRAIN_ = 2033,							//c->s属性洗练
	_TYPED_PACKET_S2C_EQUIPTRAINRESULT_ = 2034,						//s->c属性洗练结果


	_TYPED_PACKET_C2S_HEROTECHNOLOGY_=2035,							//c->s请求英雄科技信息			
	_TYPED_PACKET_S2C_HEROTECHNOLOGYRESULT_=2036,					//s->c接收英雄科技信息	

	_TYPED_PACKET_C2S_HEROTECHNOLOGYACCELERATE_=2037,				//c->s请求英雄科技加速信息			
	_TYPED_PACKET_S2C_HEROTECHNOLOGYACCELERATERESULT_=2038,			//s->c接收英雄科技加速信息	

	_TYPED_PACKET_C2S_HEROLEVELUPSELECTMATERIAL_=2041,				//c->s请求请求外套升级素材选择
	_TYPED_PACKET_S2C_HEROLEVELUPSELECTMATERIALRESULT_=2042,		//s->c请求请求外套升级素材选择结果

	_TYPED_PACKET_C2S_TASKLISTQUERY_=2043,				//c->s 请求任务列表
	_TYPED_PACKET_S2C_TASKLISTQUERY_=2044,				//s->c 返回任务列表
	_TYPED_PACKET_C2S_TASKAWARD_=2045,					//c->s	请求任务奖励
	_TYPED_PACKET_S2C_TASKAWARD_=2046,					//s->c	返回任务奖励

	_TYPED_PACKET_C2S_ATTRIBUTE_TRAIN_SELECT_MAINATTRIBUTE_ = 2049,	//C->S设置主属性

	_TYPED_PACKET_C2S_ATTRIBUTE_TRAIN_GETALLSTATUS_ = 2051,			//c-s请求所属性状态数据
	_TYPED_PACKET_S2C_ATTRIBUTE_TRAIN_GETALLSTATUSRESULT_ = 2052,	//S->C请求所有属性状态数据结果

	_TYPED_PACKET_C2S_HEROTECHNOLOGYLEVELUP_=2053,					//c->s请求英雄科技升级信息			
	_TYPED_PACKET_S2C_HEROTECHNOLOGYLEVELUPRESULT_=2054,			//s->c接收英雄科技升级信息	

	_TYPED_PACKET_C2S_EQUIPLEVELUP_SELECTCARD_ = 2055,				//c->s请求装备升级素材选择
	_TYPED_PACKET_S2C_EQUIPLEVELUP_SELECTCARD_RESULT_ = 2056,		//s->c请求装备升级素材选择结果

	_TYPED_PACKET_C2S_EQUIPTRAIN_GETLOCKSTATUS_ = 2057,				//c->s请求装备属性锁状态
	_TYPED_PACEKT_S2C_EQUIPTRAIN_GETLOCKSTATUS_RESULT_ = 2058,		//s->c请求装备属性锁状态结果



	_TYPED_PACKET_C2S_ENTERTOWER_ = 2059,					//C->S请求进入恶魔塔
	_TYPED_PACKET_S2C_ENTERTOWER_RESULT_ = 2060,			//s->c请求进入恶魔塔结果



	_TYPED_PACKET_C2S_CHALLENGETOWER_ = 2061,				//c->s请求挑战关卡
	_TYPED_PACKET_S2C_CHALLENGETOWER_RESULT_ = 2062,		//S->C请求挑战关卡结果

	_TYPED_PACKET_C2S_RESETTOWER_ = 2063,					//C->S请求重置塔数据
	_TYPED_PACKET_S2C_RESETTOWER_RESULT_ = 2064,			//s->c请求重置塔数据结果

	_TYPED_PACKET_C2S_SHOP_INFO_ = 2065,				//c->s请求商店信息
	_TYPED_PACEKT_S2C_SHOP_INFO_ = 2066,		//s->c接收商店信息


	_TYPED_PACKET_C2S_SHOP_BUY_ = 2067,				//c->s请求购买
	_TYPED_PACEKT_S2C_SHOP_BUY_RESULT_ = 2068,		//s->c接收购买结果

	_TYPED_PACKET_S2C_GETFULLSTARREWARD_ = 2069,				//c->s请求购买
	_TYPED_PACKET_S2C_GETFULLSTARREWARDRESULT_ = 2070,		//s->c接收购买结果

	_TYPED_PACKET_C2S_GETTECHNOLOGYPOINT_ = 2073,				//c->s请求信仰征收消耗
	_TYPED_PACKET_S2C_GETTECHNOLOGYPOINT_RESULT = 2074,				//s->c接收信仰征收消耗结果

	_TYPED_PACKET_C2S_ADDTECHNOLOGYPOINT_ = 2077,				//c->s请求信仰征收
	//_TYPED_PACKET_S2C_GETTECHNOLOGYPOINT_ = 2078,				//s->c接收信仰征收结果

	_TYPED_PACKET_C2S_STARTTOWER_ = 2081,					//进入爬塔的“开始”
	_TYPED_PACKET_S2C_STARTTOWER_RESULT_ = 2082,			//进入爬塔的“开始”回复


	_TYPED_PACKET_S2C_HEROALTAR_BUYITEM_RESULT_ = 2086,	//服务器回复献祭物品不足

	_TYPED_PACKET_C2S_TEAMBATTLESETDATA_ = 2087,					//进入组队副本的主界面
	_TYPED_PACKET_S2C_TEAMBATTLEGETDATA_RESULT_ = 2088,		//进入组队副本主界面返回列表



	_TYPED_PACKET_C2S_TEAMSELECTENTER_ = 2089,				//进入组队副本的选择队员界面
	_TYPED_PACKET_S2C_TEAMSELECTENTER_RESULT_ = 2090,		//进入选择队友界面返回列表


	_TYPED_PACKET_C2S_TEAMSELECT_JOINTEAM_ = 2091,				//加入队伍
	_TYPED_PACKET_S2C_TEAMSELECT_JOINTEAMRESULT_ = 2092,		//返回我当前的队伍

	_TYPED_PACKET_C2S_TEAMSELECT_STOPTEAMSYNC_ = 2093,			//停止队伍列表及我的队伍排序的同步

	_TYPED_PACKET_C2S_TEAMSELECT_REMOVEMEMBER_ = 2095,			//移除队员，-1：解散  -2：离开   x>0:移除
	_TYPED_PACKET_S2C_TEAMSELECT_BEREMOVED_ = 2098,				//被队长移除，只通知被移除队员

	_TYPED_PACKET_C2S_TEAMSELECT_REORDERTEAM_ = 2099,			//改变出战循序

	_TYPED_PACKET_C2S_TEAMSELECT_START_STAGE_ = 2101,			//开始组队副本的关卡
	 
	_TYPED_PACKET_C2S_TEAMBATTLERESET_ = 2103,							//c-s重置副本
	_TYPED_PACKET_S2C_TEAMBATTLERESET_RESULT_ = 2104,					//s-c重置副本

	_TYPED_PACKET_C2S_TEAMBATTLE_GATEREWARD_ = 2105,			//c->s获取通关奖励
	_TYPED_PACKET_S2C_TEAMBATTLE_GATEREWARD_RESULT_ = 2106,		//s->c获取通关奖励

	_TYPED_PACKET_C2S_TOWERRANK_ = 2107,						//C->C请求爬塔排行榜
	_TYPED_PACKET_S2C_TOWERRANK_RESULT_ = 2108,					//s->c获得排行榜数据返回

	_TYPED_PACKET_S2C_TEAMSELECT_TEAMLIST_ = 2109,				//s->c服务器返回队伍列表

	_TYPED_PACKET_C2S_ASKFORADDENERGY_ = 2111,						//C->C请求购买体力
	_TYPED_PACKET_S2C_ASKFORADDENERGY_RESULT_ = 2112,				//S->C请求购买的购买成功返回

	_TYPED_PACKET_C2S_MASTER_CATCH_ = 2113,					//c->s抓捕奴隶
	//_TYPED_PACKET_S2C_MASTER_CATCH_RESULT_ = 2114,			//S->C抓捕奴隶结果//走战斗

	_TYPED_PACKET_C2S_MASTER_ENTER_CATCH_ = 2115,				//C->S进入抓捕奴隶界面，获得信息
	_TYPED_PACKET_S2C_MASTER_ENTER_CATCH_RESULT_ = 2116,		//S->C获得信息结果

	_TYPED_PACKET_C2S_MASTER_ENTER_PLAY_ = 2117,						//C->S进入互动
	_TYPED_PACKET_S2C_MASTER_ENTER_PLAY_RESULT_ = 2118,				//s->c进入互动结果

	_TYPED_PACKET_C2S_MASTER_PLAY_ = 2119,							//c->s互动操作
	_TYPED_PACKET_S2C_MASTER_PLAY_RESULT_ = 2120,					//S->C互动操作结果

	//_TYPED_PACKET_C2S_MASTER_NEWS_ = 2121,							//C->S奴隶主新闻
	_TYPED_PACKET_S2C_MASTER_NEWS_ = 2122,							//S->C奴隶主新闻

	_TYPED_PACKET_C2S_MASTER_ENTER_RESCUE_ = 2123,					//C->S进入解救
	_TYPED_PACKET_S2C_MASTER_ENTER_RESCUE_RESULT_ = 2124,			//s->c进入解救显示待解救列表

	_TYPED_PACKET_C2S_MASTER_RESCUE_ = 2125,					//c->s解救好友
	//_TYPED_PACKET_S2C_MASTER_RESCUE_RESULT_ = 2126,			//S->C解救好友结果//走战斗

	_TYPED_PACKET_C2S_SLAVE_ENTER_REVOLT_ = 2127,					//C->S进入反抗
	_TYPED_PACKET_S2C_SLAVE_ENTER_REVOLT_RESULT_ = 2128,			//S->C进入反抗结果

	_TYPED_PACKET_C2S_SLAVE_BRIBE_ = 2129,							//C->S贿赂看守
	_TYPED_PACKET_S2C_SLAVE_BRIBE_RESULT_ = 2130,					//S->C贿赂看守成功

	_TYPED_PACKET_C2S_SLAVE_REVOLT_ = 2131,							//C->S反抗
	//_TYPED_PACKET_S2C_SLAVE_REVOLT_RESULT_ = 2132,					//S->C反抗结果//走战斗

	_TYPED_PACKET_C2S_SLAVE_ENTER_PLAY_ = 2141,						//c->s进入互动
	_TYPED_PACKET_S2C_SLAVE_ENTER_PLAT_RESULT_ = 2142,				//s->c进入互动结果

	_TYPED_PACKET_C2S_SLAVE_PLAY_ = 2133,							//C->S和奴隶主互动
	_TYPED_PACKET_S2C_SLAVE_PLAY_RESULT_ = 2134,					//S->C互动成功

	//_TYPED_PACKET_C2S_SLAVE_NEWS_ = 2135, 							//C->S奴隶新闻
	_TYPED_PACKET_S2C_SLAVE_NEWS_ = 2136,							//S->C奴隶新闻返回

	_TYPED_PACKET_C2S_SLAVE_ENTER_SOS_ = 2137,						//C->S进入求救
	_TYPED_PACKET_S2C_SLAVE_ENTER_SOS_RESULT_ = 2138,				//s->c进入求救结果

	_TYPED_PACKET_C2S_SLAVE_SOS_ = 2139,							//C->S求救好友
	//_TYPED_PACKET_S2C_SLAVE_SOS_RESULT_ = 2140,						//S->C求救好友结果//走战斗

	_TYPED_PACKET_C2S_NETOBJECTTIPS_ = 2151,			//c->s请求物品tips
	_TYPED_PACKET_S2C_NETOBJECTTIPS_RESULT_ = 2152,		//s->c返回物品tips结果

	_TYPED_PACKET_C2S_TEAMSELECT_ASKSLAVELIST_ = 2153,				//c->s请求奴隶列表
	_TYPED_PACEKT_S2C_TEAMSELECT_ASKSLAVELIST_RESULT_ = 2154,		//s->c请求列表结果
	_TYPED_PACKET_C2S_TEAMSELECT_HIRE_SLAVE_ = 2155,				//C->S请求召唤奴隶
	_TYPED_PACKET_C2S_TEAMSELECT_ASKMERCENARYLIST_ = 2157,			//C->S请求佣兵列表
	_TYPED_PACKET_S2C_TEAMSELECT_ASKMERCENARYLIST_RESULT_ = 2158,	//S->C请求佣兵结果
	_TYPED_PACEKT_C2S_TEAMSELECT_HIRE_MERCENARY_ = 2159,			//c->s请求雇佣佣兵



	_TYPED_PACKET_C2S_RESTINGTECHNOLOGYPOINT_ = 2165,				//c->s请求重置科技点数
	_TYPED_PACEKT_S2C_RESTINGTECHNOLOGYPOINT_RESULT_ = 2166,		//s->c重置科技点数结果


	_TYPED_PACKET_C2S_REVENUE_ = 2167,					//c->s请求征收信息
	_TYPED_PACKET_S2C_REVENUERESULT_ = 2168,			//s->c接收征收信息结果

	_TYPED_PACKET_C2S_COSTREVENUE_ = 2169,					//c->s请求点金

	_TYPED_PACKET_C2S_ENTER_MINING_ = 2171,				//进入挖矿界面
	_TYPED_PACKET_S2C_ENTER_MINING_RESULT_ = 2172,		//进入挖矿界面返回

	_TYPED_PACKET_C2S_ENTER_GOBLINAREA_ = 2173,				//进入地精矿区
	_TYPED_PACKET_S2C_ENTER_GOBLINAREA_RESULT_ = 2174,		//进入地精矿区返回

	_TYPED_PACKET_C2S_STOP_MINING_ = 2175,				//结束采矿
	_TYPED_PACKET_S2C_STOP_MINING_RESULT_ = 2176,		//结束采集返回

	_TYPED_PACKET_C2S_ENTER_DWARVENAREA_ = 2177,				//进入矮人矿区
	_TYPED_PACKET_S2C_ENTER_DWARVENAREA_RESULT_ = 2178,			//进入矮人矿区返回

	_TYPED_PACKET_C2S_DWARVENAREA_LOOT_ = 2179,					//矮人矿区抢位置，正常返回为战斗
	_TYPED_PACKET_S2C_DWARVENAREA_LOOT_RESULT_ = 2180,			//矮人矿区抢位置的不正常返回

	_TYPED_PACKET_C2S_ENTER_DRAGONAREA_ = 2181,					//进入巨龙矿区
	_TYPED_PACEKT_S2C_ENTER_DRAGONAREA_RESULT_ = 2182,			//进入巨龙矿区返回

	_TYPED_PACKET_C2S_DRAGON_CHALLENGEOWNER_ = 2183,			//挑战巨龙矿区矿主
	
	_TYPED_PACKET_C2S_START_MINING_ = 2185,						//开始采矿
	_TYPED_PACKET_S2C_START_MINING_RESULT_ = 2186,				//开始采矿返回

	_TYPED_PACKET_C2S_ENTER_HUNT_ = 2187,						//进入寻宝
	_TYPED_PACKET_S2C_ENTER_HUNT_RESULT_ = 2188,				//进入寻宝返回

	_TYPED_PACKET_C2S_HUNTMINING_ = 2189,						//寻宝
	_TYPED_PACKET_S2C_HUNTMINING_RESULT_ = 2190,				//寻宝结果返回

	_TYPED_PACKET_C2S_HUNTGRAB_ = 2191,						//寻宝挑战
	
	_TYPED_PACKET_C2S_HUNT_HELLOMONEY_ = 2193,				//加好友/打招呼后领钱
	_TYPED_PACKET_S2C_HUNT_HELLOMONEY_RESULT_ = 2194,		//领钱返回

	_TYPED_PACKET_C2S_HUNT_BUYMINERAL_ = 2195,				//花钻石直接购买物品
	_TYPED_PACKET_S2C_HUNT_BUYMINERAL_RESULT_ = 2196,		//购买物品返回

	_TYPED_PACKET_S2C_LESSRESOURCE_RESULT_ = 2198,			//资源不足

	_TYPED_PACKET_S2C_LESSRESOURCE_BUY_ = 2199,				//资源不足购买
	_TYPED_PACKET_S2C_LESSRESOURCE_BUY_RESULT_ = 2200,		//资源不足购买返回

	_TYPED_PACKET_C2S_CLIMBTOWER_JEWELRESET_ = 2201,		//爬塔，钻石重置
	_TYPED_PACKET_S2C_CLIMBTOWER_JEWELRESET_RESULT_ = 2202,	//爬塔，钻石重置成功
	_TYPED_PACKET_C2S_CLIMBTOWER_FASTFIGHT_ = 2203,			//爬塔，快速战斗
	_TYPED_PACKET_S2C_CLIMBTOWER_FASTFIGHT_RESULT_ = 2204,	//爬塔，快速战斗结果

	_TYPED_PACKET_C2S_CLIMBTOWER_REWARD_ = 2205,			//宝箱奖励
	_TYPED_PACKET_S2C_CLIMBTOWER_REWARD_DATA_ = 2206,		//宝箱奖励数据
	_TYPED_PACKET_C2S_CLIMBTOWER_GETREWARD_ = 2207,			//领取某层奖励
	_TYPED_PACKET_S2C_CLIMBTOWER_GETREWARD_RESULT_ = 2208,	//领取某曾奖励结果



	_TYPED_PACKET_C2S_EQUIPPROMOTE_ = 2209,					//装备进阶
	_TYPED_PACKET_S2C_EQUIPPROMOTE_RESULT_ = 2210,			//装备进阶返回

	_TYPED_PACKET_S2C_SUREPROMOTE_ = 2211,					//确认进阶
	_TYPED_PACKET_S2C_SUREPROMOTE_RESULT_ = 2212,			//确认进阶返回

	_TYPED_PACKET_C2S_PAYADDITION_ = 2213,					//支付附加参数请求 
	_TYPED_PACKET_S2C_PAYADDITION_RESULT_ = 2214,			//支付附加参数请求返回

	_TYPED_PACKET_C2S_FIRSTRECHGIFT_ = 2215,				//首充活动信息请求 
	_TYPED_PACKET_S2C_FIRSTRECHGIFT_RESULT_ = 2216,			//首充活动信息返回

	_TYPED_PACKET_C2S_GETFIRSTRECH_ = 2217,					//领取首充奖励请求 
	_TYPED_PACKET_S2C_GETFIRSTRECH_RESULT_ = 2218,			//领取首充奖励返回

	_TYPED_PACKET_C2S_VIPGIFT_ = 2219,						//Vip礼包请求信息
	_TYPED_PACKET_S2C_VIPGIFT_RESILT = 2220,				//Vip礼包信息返回

	_TYPED_PACKET_C2S_VIPGIFTBUY_ = 2221,						//Vip礼包购买请求
	_TYPED_PACKET_S2C_VIPGIFTBUY_RESILT = 2222,					//Vip礼包购买返回

	_TYPED_PACKET_C2S_VIPGIFT_PREVIEW_ = 2223,					//Vip礼包预览请求
	_TYPED_PACKET_S2C_VIPGIFT_PREVIEW_RESULT_ = 2224,			//Vip礼包预览返回

	_TYPED_PACKET_C2S_RANDOMSHOP_INFO_ = 2227,					//随机商店信息请求
	_TYPED_PACKET_S2C_RANDOMSHOP_INFO_RESULT_ = 2228,			//随机商店信息返回

	_TYPED_PACKET_C2S_RANDOMSHOP_BUY_ = 2229,					//随机商店购买商品请求
	_TYPED_PACKET_S2C_RANDOMSHOP_BUY_RESULT_ = 2230,			//随机商店购买成功之后返回

	_TYPED_PACKET_C2S_RANDOMSHOP_REFRESH_ = 2231,					//随机商店刷新请求
	_TYPED_PACKET_S2C_RANDOMSHOP_REFRESH_RESULT_ = 2232,			//随机商店刷新成功返回

	_TYPED_PACKET_C2S_ENTER_BOSSSCORE_ = 2233,				//进入boss积分
	_TYPED_PACKET_S2C_ENTER_BOSSSCORE_RESULT_ = 2234,		//进入boss积分返回

	_TYPED_PACKET_C2S_CHALLENGE_BOSSSCORE_ = 2235,			//boss积分挑战
	//_TYPED_PACKET_S2C_CHALLENGE_BOSSSCORE_RESULT_ = 2236,

	_TYPED_PACKET_C2S_ENTER_BOSSSCORE_RANK_ = 2237,			//进入boss积分排行榜
	_TYPED_PACKET_S2C_ENTER_BOSSSCORE_RANK_RESULT_ = 2238,	//进入boss积分排行榜返回

	_TYPED_PACKET_C2S_ENTER_BOSSSCORE_REWARD_ = 2239,		//进入boss积分奖励
	_TYPED_PACKET_S2C_ENTER_BOSSSCORE_REWARD_RESULT_ = 2240,//进入boss积分奖励返回

	_TYPED_PACKET_C2S_GET_BOSSSCORE_REWARD_ = 2241,			//领取boss积分奖励
	_TYPED_PACKET_S2C_GET_BOSSSCORE_REWARD_RESULT_ = 2242,	//领取boss积分奖励返回


	_TYPED_PACKET_C2S_EXCHANGE_INFO_CLIENT_ =2243,			//请求兑换信息
	_TYPED_PACKET_S2C_EXCHANGE_INFO_SERVER_ =2244,			//服务器返回兑换信息
			
	_TYPED_PACKET_C2S_EXCHANGE_EXCHANGE_CLIENT_=2245,		//请求兑换
	_TYPED_PACKET_S2C_EXCHANGE_EXCHANGE_SERVER_=2246,		//返回正常兑换

	_TYPED_PACKET_C2S_HUNT_LIEREN_CHAKAN_ = 2247,			//请求寻宝事件信息
	_TYPED_PACKET_S2C_HUNT_LIEREN_CHAKAN_RESULT_ = 2248,	//返回寻宝事件信息结果

	_TYPED_PACKET_C2S_HUNT_LIEREN_QIANGDUO_NO_ = 2249,				//放弃抢夺
	_TYPED_PACKET_S2C_HUNT_LIEREN_QIANGDUO_NO_RESULT_ = 2250,		//放弃抢夺结果

	_TYPED_PACKET_C2S_HUNT_LIEREN_QIANGDUO_YES_ = 2251,				//抢夺
	//_TYPED_PACKET_S2C_HUNT_LIEREN_QIANGDUO_YES_RESULT_ = 2252,		//抢夺结果返回，，//走战斗
	 
	_TYPED_PACKET_C2S_HEROTOTEMINFO_ = 3100,				//请求图腾信息
	_TYPED_PACKET_S2C_HEROTOTEMINFO_RESULT_ = 3102,			//图腾信息服务器返回
	_TYPED_PACKET_C2S_HEROALTARINFO_ = 3103,				//请求献祭信息
	_TYPED_PACKET_S2C_HEROALATRINFO_RESULT_ = 3104,			//服务器返回献祭信息

	_TYPED_PACKET_C2S_HERODEBRISALTAR_ = 3105,				//客户端发送献祭碎片信息
	_TYPED_PACKET_S2C_HERODEBRISALTAR_RESULT_ = 3106,		//服务器返回碎片献祭结果信息

	_TYPED_PACKET_C2S_ALTARCHECKINFOTABLE_ = 3107,				//请求献祭 每级最大经验的表 
	_TYPED_PACKET_S2C_ALTARCHECKINFOTABLE_RESULT_ = 3108,		//服务器返回返回献祭的等级,属性值和最大经验值对应表

	_TYPED_PACKET_C2S_ACTIVITY_ = 3110,					//申请活动列表
	_TYPED_PACKET_S2C_ACTIVITY_RESULT_ = 3111,			//接收活动列表

	_TYPED_PACKET_C2S_CHIOSE_ACTIVITY_ = 3112,					//选择活动
	_TYPED_PACKET_S2C_ACTIVITY_SPRING_RESULT_ = 3113,			//进入温泉活动返回

	_TYPED_PACKET_S2C_ACTIVITY_SPRINGREWARD_RESULT_ = 3114,			//领取温泉奖励返回

	_TYPED_PACKET_S2C_ACTIVITY_LEVELUPREWARD_ = 3115,			//升级奖励活动返回

	_TYPED_PACKET_C2S_ACTIVITY_REQUEST_LEVELUPREWARD_ = 3116,	//请求领取升级奖励
	_TYPED_PACKET_S2C_ACTIVITY_RECEIPT_LEVELUPREWARD_ = 3117,	//领取升级奖励回执
	
	_TYPED_PACKET_S2C_ACTIVITY_LOGINLIST_RESULT_ = 3119,	//每日登录奖励返回

	_TYPED_PACKET_C2S_ACTIVITY_SPING_IN = 3120,			//泡温泉

	_TYPED_PACKET_C2S_ACTIVITY_REQUEST_LOGINREWARD_ = 3121,	//请求领取登录奖励
	_TYPED_PACKET_S2C_ACTIVITY_RECEIPT_LOGINREWARD_ = 3122,	//领取升级登录回执

	_TYPED_PACKET_S2C_ACTIVITY_RECEIPT_GROWUPPLAN_ = 3123,	//成长计划信息回执

	_TYPED_PACKET_C2S_ACTIVITY_REQUEST_BUYGROWPLANREWARD_ = 3124,	//请求购买成长计划
	_TYPED_PACKET_S2C_ACTIVITY_RECEIPT_BUYGROWPLANREWARD_ = 3125,	//购买成长计划回执

	_TYPED_PACKET_C2S_ACTIVITY_REQUEST_GETGROWPLAN_ = 3126,	//请求领取成长计划奖励
	_TYPED_PACKET_S2C_ACTIVITY_RECEIPT_GETGROWPLAN_ = 3127,	//成长计划领取回执

	_TYPED_PACKET_C2S_HEROSUMMONINFO_ = 3130,				//请求召唤界面信息
	_TYPED_PACKET_S2C_HEROSUMMONINFO_RESULT_ = 3131,			//服务器返回召唤界面信息

	_TYPED_PACKET_C2S_HEROCALL_ = 3132,				//召唤英雄
	_TYPED_PACKET_S2C_HEROCALL_RESULT_ = 3133,		//召唤英雄返回

	_TYPED_PACKET_S2C_TENCALL_RESULT_ = 3134,		//十连抽英雄召唤英雄返回

	_TYPED_PACKET_S2C_USERITEM_GAINHERO_ = 3140,		//使用物品获得英雄

	_TYPED_PACKET_S2C_ANNOUNCEMENT_MESSAGE_SERVER_=3150,	//服务器推送广播公共消息

	_TYPED_PACKET_C2S_CHECKROLEBASEINFO_ = 3160,			//查看人物基本信息请求
	_TYPED_PACKET_S2C_CHECKROLEBASEINFO_RESULT_ = 3161,		//人物基本信息返回


	_TYPED_PACKET_S2C_MULTIREWARD_RESULT_ = 3170,			//多个物品奖励返回

	_TYPED_PACKET_C2S_NEWGUIDE_STEP_=3180,					//c->s新手引导每一小步的完成情况

	_TYPED_PACKET_C2S_SOUL_ENTER_INFO_CLIENT_=3200,    //c -> s 请求进入英雄战魂信息
	_TYPED_PACKET_S2C_SOUL_ENTER_INFO_SERVER_=3201,	   //s -> c 服务器返回英雄战魂信息	

	_TYPED_PACKET_C2S_SOUL_CHALLENEG_CLIENT_=3202,		//c -> s 请求挑战英雄战魂
	 
	_TYPED_PACKET_C2S_SOUL_ACTIVE_CLIENT_=3205,			//c -> s 请求激活英雄战魂
	_TYPED_PACKET_C2S_SOUL_ACTIVE_SERVER_=3206,			//s -> c 服务器返回激活战魂信息

	_TYPED_PACKET_C2S_SOUL_UNLOCK_CLIENT_=3207,			// 请求解锁英雄战魂
	_TYPED_PACKET_S2C_SOUL_UNLOCK_SERVER_=3208,			// 服务器返回解锁英雄战魂
	_TYPED_PACKET_C2S_EQUP_SOUL_CLIENT_=3209,			// 请求装备英雄战魂
	_TYPED_PACKET_S2C_EQUP_SOUL_SERVER_=3210,			// 服务器返回装备英雄战魂
	_TYPED_PACKET_C2S_UNEQUP_SOUL_CLIENT_=3211,			// 请求卸载英雄战魂
	_TYPED_PACKET_S2C_UNEQUP_SOUL_SERVER_=3212,			// 服务器返回卸载英雄战魂

	_TYPED_PACKET_C2S_UNLOCK_SKILL_CLIENT_=3230,		// 请求解锁第六格技能

	_TYPED_PACKET_C2S_EQUIP_RECAST_INFO_CLIENT_=4104,	//请求装备重铸信息
	_TYPED_PACKET_S2C_EQUIP_RECAST_INFO_SERVER_=4105,	//返回装备重铸信息
	_TYPED_PACKET_C2S_EQUIP_RECAST_DO_CLIENT_=4106,		//发起装备重铸执行请求
	_TYPED_PACKET_S2C_EQUIP_RECAST_DO_SERVER_=4107,		//成功返回装备重铸执行结果
	_TYPED_PACKET_C2S_CHECK_PLAYER_INFO_CLIENT=4108,	//请求玩家信息
	_TYPED_PACKET_S2C_CHECK_PLAYER_INFO_CLIENT=4109,	//请求玩家信息返回
	_TYPED_PACKET_C2S_CHECK_OPEN_FUNCTION_=4110,		//请求是否开户的功能列表
	_TYPED_PACKET_S2C_CHECK_OPEN_FUNCTION_=4111,		//请求是否开启的功能列表返回

	_TYPED_PACKET_C2S_DOUBLE_PAY_INFO_=4112,		//客户端请求首冲双倍信息

	_TYPED_PACKET_S2C_DOUBLE_PAY_INFO_RESULT_=4113,		//服务器返回首冲双倍信息


	_TYPE_PACKET_S2C_LUA_	= 5000,			//lua用于分辨解析用,Lua占用第5000段包


	_TYPE_PACKET_C2S_HEROTEAMCHANGE_ = 6001,				//请求换英雄
	_TYPE_PACKET_S2C_HEROTEAMCHANGE_RESULT_ = 6002,			//请求换英雄返回

	_TYPED_PACKET_C2S_ASKFORROLEINFO_=9999,				//c->s请求人物信息				['Z''R'][n][2100][int序列号] 


	



};


#endif
