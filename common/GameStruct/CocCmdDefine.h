#ifndef _COC_CMD_DEFINE_H
#define _COC_CMD_DEFINE_H

#ifndef GAME_COMMON
#define GAME_COMMON
#endif

//移动端chat协议版本号
enum MB_VER
{
	MB_CHAT_VER1		=	0x016,
	MB_CHAT_VER2,
	MB_CHAT_VER3,
	MB_CHAT_VER4,
	MB_CHAT_VER5,
	MB_CHAT_VER6,
	MB_CHAT_VER7,
	MB_CHAT_VER8,
	MB_CHAT_VER_CURR	=	MB_CHAT_VER8,			
};

class CocCmdType
{
public:
	enum
	{
		//从room继承cmd
		COC_KEEP_ALIVE = 1,
		COC_ACK = 2,	
		COC_FORCE_OFFLINE  = 0x0403,		//多地登录强制离线
		//coc专用cmd
		COC_USER_LOGIN = 3000,				//从三千开始是为了防止与room cmd重复
		COC_USER_LOGOUT,
		COC_T_CMD_SENDTIMEOUT,				//发送结果回调
		COC_KEEP_ALIVE_GAME,
		COC_ACK_INVOLID,
		COC_SCENE_BUILD,					//建造
		COC_SCENE_UPDATE_LEVEL,				//升级
		COC_SCENE_MOVE,						//移动
		COC_SCENE_REMOVE,					//拆除
		COC_SCENE_RESOURCE_COLLECT,			//收集（资源）
		COC_SCENE_INFO,						//获取场景中物体的信息（位置，等级等）
		COC_SCENE_CHECK_UPDATE,				//检查升级完成
		COC_TRAIN_SOLDIER,					//训练士兵
		COC_CANCEL_TRAIN_SOLDIER,			//取消正在训练的士兵
		COC_UPDATE_SOLDIER_LEVEL,			//升级士兵
		COC_FIND_USER_MAP,					//查看其他用户的地图
		COC_PUSH_SOLDIER_LIST,				//下发可以出征士兵
		COC_COMPLETEDIMMEDIATELY,			//立刻完成（使用宝石）
		COC_ACHIEVEMENT_APPLY,				//客户端领取成就奖励
		COC_PRODUCE_MAGIC,					//生产法术
		COC_SPEED_UP,						//加速
		COC_PICKET_SOLDIERS,				//派兵
		COC_WALL_MUTI_MOVE,					//城墙批量移动
		COC_WALL_MUTI_UPDATE,				//城墙批量升级
		COC_BUY_SHILED,						//购买护盾
		COC_BUY_ORNAMENT,					//购买装饰
		COC_SELL_ORNAMENT,					//出售装饰
		COC_MAP_COPY,						//地图复制
		COC_MAP_EDITE,						//地图编辑
		COC_REPORT_BUILD,					//建筑战报
		COC_REPORT_RESOURCE,				//资源战报
		COC_TERMINAT_ATTACK,				//结束战斗
		COC_GET_SOLDIER_RECORD,				//获取派兵记录
		COC_RECOVER_TRAP,					//修复陷阱
		COC_CANCEL_BUILD,					//取消建筑 建造 或升级
		COC_MACHING_USER,					//获取匹配信息
		COC_SVR_USER_INFO,					//收到用户信息
		COC_CANCEL_MACHING,					//取消匹配信息
		COC_GET_ATTACK_HISTORY_MAP,			//获取历史战争地图（回放）
		COC_CANCEL_MAGIC_PRODUCT,			//取消法术生产
		COC_GEMSTONE_BUY_RESOURCE,			//购买资源

		COC_TERMINAT_TOLLGATE,				//结束攻关

		COC_SET_NEW_USER_STEP,				//新手教程进行步骤
		COC_SET_USER_NAME,					//设置名称

		//请求调用接口
		COC_GET_USER_MAP_DATA,				//获取用户地图建筑信息
		COC_GET_USER_UPDATE_SOLDIER,		//获取用户升级中 的士兵
		COC_GET_USER_WORKER_LIST,			//获取用户worker工作队列信息
		COC_GET_USER_SOLDIER_LEVEL,			//获取用户士兵等级信息
		COC_GET_USER_PRODUCE_LIST,			//获取用户士兵法术生产队列信息
		COC_GET_USER_OWN_SOLDIER_LIST,		//获取用户拥有的士兵信息
		COC_GET_USER_ACHIEVEMEN,			//获取用户成就信息
		COC_GET_USER_SPPEDUP_INFO,			//获取用户使用加速功能信息
		COC_GET_USER_ATTACK_HISTORY_LIST,	//获取用户战斗历史记录信息
		COC_GET_USER_DEFEND_ONATTACK_INFO,	//防守方 被攻打信息
		COC_GET_USER_TOLLGATE_lIST,			//获取关卡信息记录
		COC_GET_USER_TOLLGATE_MAP,			//获取关卡地图
		COC_GET_USER_INFO_DATA,				//获取用户个人信息
		//参观
		COC_GET_USER_MAP_DATA_VISIT,			//获取用户地图建筑信息
		COC_GET_USER_UPDATE_SOLDIER_VISIT,		//获取用户升级中 的士兵
		COC_GET_USER_WORKER_LIST_VISIT,			//获取用户worker工作队列信息
		COC_GET_USER_SOLDIER_LEVEL_VISIT,		//获取用户士兵等级信息
		COC_GET_USER_PRODUCE_LIST_VISIT,		//获取用户士兵法术生产队列信息
		COC_GET_USER_OWN_SOLDIER_LIST_VISIT,	//获取用户拥有的士兵信息
		COC_USER_REVENGE,						//复仇
		COC_GET_OFFEND_SOLDIER_INFO,			//防守方 被攻打信息
		COC_ADD_WINNER_MSG,						//增加胜利留言
		COC_BUY_GEMSTONE_INFO,					//可购买宝石信息列表
		COC_CHARE_GEMSTONE,						//充值宝石
		COC_FIRST_CHARGE_GEMSTONE,				//用户首冲任务完成通知
		COC_FINISH_FIRST_CHARGE,				//领取首充奖励
		COC_BROTHERHOOD_INFO,					//兄弟关系进度
		COC_BROTHERLSIT_INFO,					//兄弟关系列表
		COC_BROTHER_TASK_REWARD,				//领取兄弟任务奖励
		COC_BIND_BROTHER,						//绑定兄弟关系
		COC_CLANLIST_INFO,						//请求部落信息列表
		COC_CLANINFO,							//请求我的部落信息
		COC_CLAN_ASKFOR_LIST,					//请求申请列表
		COC_CLAN_OPERATE,						//申请加入部落，取消申请
		COC_CLAN_KICK_USER,						//踢出部落
		COC_CLAN_CREATE,						//创建部落,删除部落
		COC_CLAN_DELETE,						//删除部落
		COC_CLAN_MODIFY,						//修改部落信息
		COC_CLAN_SEARCH,						//搜索部落
		COC_CLAN_CHANGE_RANK,					//任命操作
		COC_CLAN_CONFIRM_REQ,					//处理工会申请请求
		COC_CLAN_PID_ORDER,						//全站部落排行
		COC_CLAN_DONATE,						//部落捐献
		COC_CLAN_RECRUIT,						//部落招募士兵
		COC_CLAN_DONATE_INFO,					//请求捐献时间等信息

		COC_CLAN_WARBASTION_INFO,				//获取战争堡垒信息
		COC_CLAN_ALLOT,							//分配战力品
		COC_GET_CLAN_CHALLENGE_ATTACK_INFO,		//部落战报回放战斗信息







		//服务器下发信息
		COC_SERVER_ACHIEVEMENT_COMPLETE = 4000,		//服务器下发成就完成通知
		COC_SERVER_NOTIFY_MSG,						//服务器下发通知消息
		COC_SERVER_PUSH_LAST_TOLLGATE,				//服务器下发关卡信息记录
		COC_SERVER_USER_ATTACK_HISTORY_LIST,		//服务器下发用户战斗历史记录信息

		//
		COC_CANCEL_REMOVE,					//取消移除
		COC_REMOVE_SOLDIER,					//删除士兵
		COC_GET_SERVER_PUSH_LIST,			//获取服务主动推送数据
		COC_SEND_MAGIC,						//释放法术
		COC_GET_RANKING_LIST,				//排行榜
		COC_CHECK_VER,						//版本号校验
		//查询兑换功能
		COC_SELECT_PLATFORM_MONEY,			//查询平台币
		COC_SELECT_STATION_MONEY,			//查询站点币
		COC_PLATFORM_MONEY_BUY_GEMSTONE,	//平台币买宝石
		COC_STATION_MONEY_BUY_RESOURCE,		//站点币买资源
		COC_GET_SHIELD_LIST,				//获取护盾列表
		COC_SERVER_MAIL_MSG,				//推送邮件消息
		COC_SERVER_SYS_MSG,					//推送系统消息
		COC_CHANGE_USER_NAME,				//更改用户名称
		COC_MAIL_PRIZE_APPLY,				//客户端领取系统奖励
		COC_GET_MAILMSG_LIST,				//获取系统邮件消息
		COC_DELETE_MAILMSG_LIST,			//删除邮件信息
		COC_GET_ONLINEPRIZE_INFO,			//获取在线奖励配置信息以及当前获取的奖励id和新的在线时长
		COC_GET_CURR_ONLINEPRIZE,			//领取当前的在线奖励
		COC_MACHING_USER_WITH_ID,			//指定匹配id
		COC_GET_DAY_ACTIVE_TASK_PRIZE_INFO,	//日活奖励信息配置
		COC_GET_DAY_ACTIVE_TASK_lIST,		//获取日活完成度信息
		COC_GET_CURR_DAY_ACTIVE_PRIZE,		//领取日活奖励
		COC_PUSH_ORNAMENT_UP_PERCENT,		//推送装饰品提速比例
		COC_GAME_CHALLENGE,					//站点挑战赛
		COC_REPORT_BUILD_CHALLENGE,			//建筑战报
		COC_TERMINAT_CHALLENGE,				//结束攻关
		COC_GET_CHALLENGE_RANKING_LIST,		//站点挑战赛
		COC_SERVER_CHALLENGE_DESCRIBE,		//站点挑战赛描述信息， 不单独请求，取列表时推送
		COC_GET_CHALLENGE_ATTACK_INFO,		//站点挑战赛战斗信息
		COC_SVR_CLAN_CHANGED,				//更新部落信息
		COC_SVR_CLAN_JOIN,					//加入部落
		COC_SVR_CLAN_LEAVE,					//离开部落
		COC_SVR_CLAN_STATEACHE,				//部落缓存信息
		COC_SVR_CLANREQ_ADD,				//申请加入部落列表增量增加
		COC_SVR_CLANREQ_DEL,				//申请加入部落列表增量删除
		COC_SVR_CLAN_UPDATELEVEL,			//部落等级提升通知
		COC_SVR_CLAN_MEMLIST,				//推送部落成员信息
		COC_SVR_CLAN_CHANGERANK,			//任命通知
		COC_SVR_CLAN_DONATE,				//部落捐献通知
		COC_SVR_CLAN_DONATE_INFO,			//部落捐献信息推送
		COC_SVR_LAST_WINPOINT_RANK,			//上赛季胜点排行
		COC_SVR_CUR_WINPOINT_RANK,			//本赛季胜点排行
		COC_SVR_CLAN_WINPIONT,				//部落胜点推送(加预计排名)
		COC_SVR_CLAN_AWARD_LIST,			//战利品创库推送
		COC_SVR_CLAN_AWARD_ALLOT,			//战利品分发公告推送
		COC_SVR_CLAN_RANKAWARD_MAIL,		//赛季排名奖励邮件
		COC_SVR_CLAN_ATTACK_HISTORY_LIST,	//部落战报战斗历史记录信息
	};
};

class Immediately
{
public:
	enum
	{
		COC_BUID,
		COC_REMOVE,
		COC_LAB,
		COC_TRAINS,
		COC_MAGIC,
		COC_UPDATE,
	};
};
class ChangeName
{
public:
	enum
	{
		CHANGE_SUCESS,		//改名成功
		CHANGE_MONEY,		//金额不足
		CHANGE_IN_USE,		//名字已经被使用
		CHANGE_EMPTY,		//空的名字
	};
};
class SoldierGroup
{
public:
	enum
	{
		GROUP_BARRACK,
		GROUP_CASTLE,
	};
};
class GameNotifyCmd
{
public:
	enum
	{
		SUCCESS,							//没有错误
		KICK_OUT,							//服务踢人
		NEED_WAIT,							//登录未完成， 需要等待
		REVENGE_REPEAT,						//重复复仇
		REVENGE_ONLINE,						//在线或者护盾状态
		REVENGE_ONATTACK,					//被攻打状态
		COCVER_ERRO,						//版本号错误
		USER_LOGOUT,						//退出登录 
		EXCHANGE_MONEY_NOT_ENOUGH,			//兑换资金不足
		EXCHANGE_DB_ERRO,					//DB故障，请重试
		SERVER_WAIT,						//服务维护中
		NITIFY,								//通知
		RESOURCE_IS_FULL,					//资源存储已满
		STATTION_GOLD_SUCESS,				//站点币操作成功
		STATTION_GOLD_FAIL,					//站点币操作失败
		STATTION_GOLD_FAIL_DB,				//站点币操作失败
		GEMSTONE_NOT_ENOUGH,				//宝石不足
		MONEY_LOCKED_BYGAME,				//虚拟币被锁定
	};
};



//通知码
class CocCmdStateType
{
public:
	enum
	{
		COC_HANDLE_SUCCESS = 0x0001,								//登陆成功
		COC_HANDLE_FAILED,											//对于不明确错误,统一以此返回
		COC_INVALID_UIN,											//uin不存在
		COC_WRONG_PASSWD,											//密码错误
		COC_USER_IS_ONLINE,											//对方是在线状态
		COC_REQUEST_SUCCESS,										//请求的操作被处理
		COC_REQUEST_ERRO,											//请求没有被处理
		// 	LOGIN_NO_ROOM_MEMBER,										//不是房间成员
		// 	LOGON_ROOM_IS_BUSY,											//房间正繁忙,提示客户端稍后再连
		// 	LOGON_NO_THIS_ROOM,  										//该房间不存在(可能已解散,或被临时冻结)
		// 	LOGON_REJECT,												//被拒绝登录
		// 	LOGON_REQ,													//正在请求登陆中
		// 	LOGON_VISITOR_ISFULL,										//房间已满
		// 	LOGON_ROOM_CLOSE,											//房间是关闭的
		// 	LOGON_WRONG_ROOM_PASSWD,									//房间密码错误
		// 	LOGON_ROOM_ISFULL,											//游客已满
		// 	LOGON_BLACKLIST_UIN,										//用户在黑名单中
		// 	LOGON_BLACKLIST_IP,											//IP在黑名单中
		// 	LOGON_FORBID_JOIN,											//该房间不允许您进入
		// 	LOGON_REQUEST_DATA,											//登录成功后，请求数据中故//借用下 whg 20090604
		// 	LOGON_REQUEST_SUCESS,										//登录成功后，请求数据中全部返回//借用下 whg 20090604
		// 	LOGON_ROOM_ONLY_SUBSCRIBER,									//只允许订阅者进入
		// 	LOGON_ROOM_ONLY_VIP,										//收费房间，只允许缴费用户进入（包括已经订阅者）
		// 	LOGON_ROOM_PAY_ERROR,										//扣费不失败（系统错误或余额不足)
		// 	LOGON_ROOM_INGAME,											//正在游戏房间
		// 	LOGON_BLACKLIST_MAC,										//机器码在黑名单中
		// 	LOGON_MAX_LIMIT,											//单个mac登录超过最大限制
	};
};


class CocBindBrother
{
public:
	enum
	{
		COC_BIND_SUCCESS,											//成功				
		COC_BIND_FAILED,											//对于不明确错误,统一以此返回
		COC_INVALID_GAMEID,											//游戏id不存在
		COC_ALREADY_BIND,											//已经绑定过了
		COC_MAC_REPEAT,												//mac已经存在
		COC_LEVEL_LIMIT,											//大本营等级不相符
		COC_BIND_SELF,												//自己绑定自己
	};

};

class COCClanState
{
public:
	enum
	{
		CLAN_NORMAL_STATE,				//无状态
		CLAN_REQ_STATE,					//申请状态
		CLAN_IN_STATE,					//在部落中
	};
};

//coc所有操作状态码，统一在此定义
class CocNewState
{
public:
	enum
	{
		COC_SUCCESS,											//成功		
		COC_CLAN_BASECAMP_ERROR,								//大本营等级不相符
		COC_CLAN_GEMSTONE_NOTENOUGH,							//宝石不足
		COC_CLAN_NAME_REPEAT,									//名字重复
		COC_ALREADY_IN_CLAN,									//已经在部落中
		COC_CLAN_TOMANY_MEMBER,									//超过成员个数限制
		COC_CLANID_NOT_EXIST,									//部落不存在
		COC_NOT_CLAN_MEMBER,									//不是部落成员
		COC_CLAN_ACL_NOTENOUGH,									//权限不足
		COC_CLAN_CDTIME,										//冷却中
		COC_CLAN_LEAVE_ERR,										//首领不能离开
		COC_CLAN_ALREADY_REQ,									//不能重复申请
		COC_CLAN_CLANID_EXIST,									//部落id存在
		COC_CLAN_NAME_ERR,										//部落名字不能为空
		COC_CLAN_NAME_LEN_ERR,									//部落名字超出限制
		COC_CLAN_CUP_NOTENOUGH,									//奖杯数太小
		COC_CLAN_RANK_NUM_LIMIT,								//任命超过最大人数限制
		COC_CLAN_FAILD,											//未知错误
		COC_CLAN_NOT_INCLA,										//不再部落中
		COC_CLAN_TIMES_NOTENOUGH,								//次数不够
		COC_CLAN_REQ_TIMEOUT,									//请求过期

		COC_CLAN_CONFIG_EXCEPTION,								//配置异常
		COC_CLAN_COLDTIME,										//冷却时间中
		COC_CLAN_CONTRIBUTION_ONTENOUGH,						//部落贡献不足
	};
};

class ResourceErrorCode
{
public:
	enum
	{
		RESOURCE_GOLD_NOTENOUGH = 101,							//金币不足
		RESOURCE_HOLYWARTER_NOTENOUGH,							//圣水不足
		RESOURCE_BLACKWATER_NOTENOUGH,							//黑水不足
		RESOURCE_GEMSTONE_NOTENOUGH,							//宝石不足
		RESOURCE_NOTDEFINE,										//未定义类型
	};
};

#endif
