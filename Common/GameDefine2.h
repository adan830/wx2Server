//***************************************************************************************************
// 文件名称:	GameDefine2.h
// 系统名称:	
// 模块名称:	GameDefine
// 功能说明:	游戏中枚举值
//
// 相关文档:	
// 作    者:	liam
// 建立日期:	
// 审    核:	
// 软件版权:	
//
//修改记录:
//          1.
//				修 改 人:liam
//				修改时间:2007/10/30
//				修改内容:属性第一部分重构(具体参见文档)
//          2.
//				修 改 人:liam
//				修改时间:2007/11/02
//				修改内容:属性第二部分重构(具体参见文档)
//***************************************************************************************************
#ifndef __GAMEDEFINE2_H__
#define __GAMEDEFINE2_H__

#include "GameDefine.h"

enum BAGPOS_TYPE
{
	BAG_BASE	=-1,
	BAG_EXTRA1	,
	BAG_EXTRA2	,
	BAG_EXTRA3	,
	BAG_EXTRA4	,
	BAG_NUM		,
};
//物品分配方式
enum ITEM_DISTRIB_MODE
{
	ITEM_FREE_DISTRIB       = 0,//自由拾取
	ITEM_TEAMLEADER_DISTRIB = 1,//队长拾取
	ITEM_INTURNS_DISTRIB	= 2,//输流拾取
	ITEM_SEPARATE_DISTRIB	= 3,//分别拾取
	ITEM_DISTRIB_NUM,
};

//角色死亡后的复活操作
enum ENUM_DIE_RESULT_CODE
{
	DIE_RESULT_CODE_INVALID	= -1,
	ORIGIN_LOSSLESS_RELIVE,			//原地无损复活
	ORIGIN_DAMAGE_RELIVE,			//原地有损复活
	CITY_POS_RELIVE,				//城市定点复活
	DIE_RESULT_CODE_NUMBERS
};


enum COUNTRY_ATTRIBUTE
{
	COUATTRIBUTE_XINYUE			=0, //新月汗国
	COUATTRIBUTE_JINZHANG		,	//金帐汗国
	COUATTRIBUTE_XIYU			,	//西域汗国
	COUATTRIBUTE_DAMO			,	//大漠汗国
	COUATTRIBUTE_NUMBER			,//国家总数
};
//代练模式
enum SUB_TRAIN_MODE
{
	SUBTRAIN_MODE1				=0, //普通模式
	SUBTRAIN_MODE1POINT5		=1,
	SUBTRAIN_MODE2				=2,
	SUBTRAIN_MODE3				=3,
};

//门派类别
enum MENPAI_ATTRIBUTE
{
	MATTRIBUTE_UNKNOW			=-1,//非法数值
	MATTRIBUTE_SHAOLIN_GWS		=0,	//少林派[棍武僧]
	MATTRIBUTE_SHAOLIN_TLH		=1,	//少林派[铁罗汉]
	MATTRIBUTE_GAIBANG_GGB		=2,	//丐帮[棍丐帮]
	MATTRIBUTE_GAIBANG_ZGB		=3,	//丐帮[掌丐帮]
	MATTRIBUTE_WUDANG_JWD		=4,	//武当派[剑武当]
	MATTRIBUTE_WUDANG_QWD		=5,	//武当派[气武当]
	MATTRIBUTE_TANGMEN_DT		=6,	//唐门[刀唐]
	MATTRIBUTE_TANGMEN_XJT		=7,	//唐门[陷阱唐]
	MATTRIBUTE_XIAOYAO_XXY		=8,	//逍遥派[扇逍遥]
	MATTRIBUTE_XIAOYAO_ZXY		=9,	//逍遥派[指逍遥]
	MATTRIBUTE_YAOWANGGU_KYW	=10,	//药王谷[狂药王]
	MATTRIBUTE_YAOWANGGU_YYW	=11,	//药王谷[医药王]
	MATTRIBUTE_TAOHUAGU_DTH		=12,	//桃花岛[笛桃花]
	MATTRIBUTE_TAOHUAGU_YTH		=13,	//桃花岛[音桃花]
	MATTRIBUTE_EMEI_CEM			=14,	//峨嵋派[刺峨眉]
	MATTRIBUTE_EMEI_FEM			=15,	//峨嵋派[辅峨眉]
	MATTRIBUTE_WUMENPAI			=16,	//无门派
	MATTRIBUTE_NUMBER,				//门派总数(8个门派，每派分内功、外功)
};

#define	CLIENT_GAOMO_MENPAI	17
#define  CLIENT_MENPAI_NUM	(MATTRIBUTE_NUMBER +1)

//系别
enum COMMON_S
{
	COMMON_S1		=0,
	COMMON_S2,
	COMMON_S3,
	COMMON_S4,
	COMMON_S5,
	COMMON_S_NUMBER,
};

// 关系
enum ENUM_RELATION
{
	RELATION_INVALID	= -1,
	RELATION_ENEMY,			// 敌对
	RELATION_FRIEND,			// 友好

	RELATION_NUMBERS
};

enum ENUM_NPC_AI_ATTR
{
	NPC_AI_TYPE_INVALID		= -1,	// INVALID
	NPC_AI_TYPE_SCANNPC		= 0,	// 主动NPC
	NPC_AI_TYPE_NOTSCANNPC		= 1,	// 非主动NPC
	NPC_AI_TYPE_CANNOTATTACK	= 2,	// 不可攻击NPC

};

enum ITEM_POS_TYPE
{
	ENUM_BAG				=0,
	ENUM_EQUIP_POINT,
	INVALID_ITEM_POS_TYPE, 
};

//属性信息类别(对应BaseValueTable.ini信息)
enum ATTRIBUTEINFO_TYPE
{
	AINFOTYPE_BASE_HP			=0,		//初始生命上限														9
	AINFOTYPE_LEVEL_CON         ,       //等级对体质的影响系数												4
	AINFOTYPE_CON_HP			,		//体制对生命上限影响系数											10
	AINFOTYPE_LEVEL_HP			,		//等级对生命上限影响系数											11
	AINFOTYPE_BASE_HPRESTORE	,		//初始生命回复														16

	AINFOTYPE_LEVEL_HPRESTORE	,		//等级对生命回复影响系数											15
	AINFOTYPE_BASE_MP			,		//初始真气上限														12
	AINFOTYPE_INT_MP			,		//内力对真气上限的影响系数											13
	AINFOTYPE_LEVEL_MP			,		//等级对真气上限影响系数											14
	AINFOTYPE_BASE_MPRESTORE	,		//初始内力回复														18

	AINFOTYPE_LEVEL_MPRESTORE	,		//等级对内力回复影响系数											17
	AINFOTYPE_BASE_RAGE			,		//初始怒气上限														40
	AINFOTYPE_INT_RAGE			,		//内力对怒气上限影响系数											78
	AINFOTYPE_LEVEL_RAGE		,		//等级对怒气影响系数												62
	AINFOTYPE_LEVEL_RAGERESTORE	,		//等级对怒气回复影响系数											65

	AINFOTYPE_LEVEL_STRENGTH      ,     //等级对力道影响													1
	AINFOTYPE_BASE_NEARATTACK     ,     //初始远程内功攻击													30
	AINFOTYPE_INT_NEARATTACK	 ,     //内力对远程内功攻击的影响系数										29	
	AINFOTYPE_LEVEL_NEARATTACK    ,     //等级对远程内功攻击的影响系数										28
	AINFOTYPE_LEVEL_DEX	          ,     //等级对身法的影响系数												2

	AINFOTYPE_BASE_FARATTACK      ,     //初始远程外功攻击													24
	AINFOTYPE_STR_FARATTACK       ,     //力道对远程外功攻击的影响系数										23
	AINFOTYPE_LEVEL_FARATTACK     ,      //等级对远程外功攻击的影响系数										22	
	AINFOTYPE_BASE_NEARDEFENCE_P	,	//初始近程防御														79
	AINFOTYPE_LEVEL_NEARDEFENCE_P	,	//等级对远程内功防御的影响系数										34

	AINFOTYPE_BASE_FARDEFENCE_P 	,	//初始远程外功防御													48
	AINFOTYPE_LEVEL_FARDEFENCE_P	,	//等级对远程外功防御的影响系数										32
	AINFOTYPE_BASE_TOUGHNESS      ,     //初始韧性															42	
	AINFOTYPE_LEVEL_TOUGHNESS     ,     //等级对韧性的影响系数												41
	AINFOTYPE_INT_TOUGHNESS		,   //体质对韧性的影响系数							
	AINFOTYPE_LEVEL_INT			,   //等级对内力的影响系数													3
	

	AINFOTYPE_BASE_ATTACK_MAGIC_NEAR ,	//初始近程内功攻击													27
	AINFOTYPE_DEX_ATTACK_MAGIC_NEAR	,	//身法对近程内功攻击的影响系数										26
	AINFOTYPE_LEVEL_ATTACK_MAGIC_NEAR	,	//等级对近程内功攻击的影响系数									25
	AINFOTYPE_BASE_DEFENCE_MAGIC_NEAR	,	//初始近程内功防御												49
	AINFOTYPE_LEVEL_DEFENCE_MAGIC_NEAR	,	//等级对近程内功防御的影响系数									33

	AINFOTYPE_BASE_HIT			,	//初始命中																80	
	AINFOTYPE_STR_HIT			,	//力道对命中的影响系数													5
	AINFOTYPE_LEVEL_HIT			,	//等级对命中的影响系数													6
	AINFOTYPE_BASE_MISS			,	//初始闪避																81
	AINFOTYPE_DEX_MISS			,	//身法对闪避的影响系数													7

	AINFOTYPE_LEVEL_MISS        ,	//等级对闪避的影响系数													8
	AINFOTYPE_BASE_CRITRATE		,	//初始暴击																82
	AINFOTYPE_INT_CRITRATE		,	//智力对会心率的影响系数												35
	AINFOTYPE_DEX_CRITRATE		,	//敏捷对会心率的影响系数												36
	AINFOTYPE_LEVEL_CRITRATE	,	//等级对暴击的影响系数													83

	AINFOTYPE_ATTACK_FLUCTUATION,	//攻击力浮动															61
	AINFOTYPE_BASE_ATTACK_MAGIC_FAR ,	//初始近程外功攻击													21
	AINFOTYPE_STR_ATTACK_MAGIC_FAR	,	//力道对近程外功攻击的影响系数										20
	AINFOTYPE_LEVEL_ATTACK_MAGIC_FAR	,	//等级对近程外功攻击的影响系数									19
	AINFOTYPE_BASE_DEFENCE_MAGIC_FAR	,	//初始近程外功防御												47

	AINFOTYPE_LEVEL_DEFENCE_MAGIC_FAR	,	//等级对近程外功防御的影响系数									31
	AINFOTYPE_MAX_PNEUMA,				//初始元气最大值													38
	AINFOTYPE_LEVEL_MAX_PNEUMA,			//等级对元气最大值的影响系数										63
	AINFOTYPE_RESTORE_PNEUMA,			//初始元气回复														37
	AINFOTYPE_LEVEL_RESTORE_PNEUMA,		//等级对元气回复影响系数											66

	AINFOTYPE_BASE_ATTACK_GOLD,		//初始金系攻击力														51
	AINFOTYPE_BASE_ATTACK_WOOD ,	//初始木系攻击力														52
	AINFOTYPE_BASE_ATTACK_WATER,	//初始水系攻击力														53
	AINFOTYPE_BASE_ATTACK_FIRE ,	//初始火系攻击力														54
	AINFOTYPE_BASE_ATTACK_SOIL,		//初始土系攻击力														55

	AINFOTYPE_BASE_DEFENCE_GOLD,	//初始金系防御力														56
	AINFOTYPE_BASE_DEFENCE_WOOD ,	//初始木系防御力														57
	AINFOTYPE_BASE_DEFENCE_WATER,	//初始水系防御力														58
	AINFOTYPE_BASE_DEFENCE_FIRE ,	//初始火系防御力														59
	AINFOTYPE_BASE_DEFENCE_SOIL,	//初始土系防御力														60

	AINFOTYPE_LEVEL_MAX_VIGOR,		//每升一级活力上限增加点数												64
	AINFOTYPE_LEVEL_RESTORE_VIGOR,	//等级对活力回复的影响系数												67
	AINFOTYPE_LEVEL_ATTACK_GOLD,	//等级对金系攻击力的影响系数											68
	AINFOTYPE_LEVEL_ATTACK_WOOD ,	//等级对土系攻击力的影响系数											69
	AINFOTYPE_LEVEL_ATTACK_WATER,	//等级对水系攻击力的影响系数											70

	AINFOTYPE_LEVEL_ATTACK_FIRE ,	//等级对火系攻击力的影响系数											71
	AINFOTYPE_LEVEL_ATTACK_SOIL,	//等级对木系攻击力的影响系数											72
	AINFOTYPE_LEVEL_DEFENCE_GOLD,	//等级对金系抵抗力的影响系数											73
	AINFOTYPE_LEVEL_DEFENCE_WOOD ,	//等级对木系抵抗力的影响系数											74
	AINFOTYPE_LEVEL_DEFENCE_WATER,	//等级对水系抵抗力的影响系数											75

	AINFOTYPE_LEVEL_DEFENCE_FIRE ,	//等级对火系抵抗力的影响系数											76
	AINFOTYPE_LEVEL_DEFENCE_SOIL,	//等级对土系抵抗力的影响系数											77
	AINFOTYPE_RESTORE_RAGE_FROM_EXP,//经验转换系数(产生怒气)												39

	AINFOTYPE_BASE_VIGOR_RESTORE,	//初始活力恢复值

	AINFOTYPE_NUMBER,					//属性信息总数
};
//攻击错误
enum ATTACK_ERROR
{
	AERROR_NOTLIVE		=-1,	//目标死了，攻击无效		
	AERROR_NOTSCENE		=-2,	//目标不在当前场景
	AERROR_OUTRANGE		=-3,	//攻击者与目标距离太远
	AERROR_INVALID		=-4,	//无效目标
	AERROR_HIT			=-5,	//没有命中
	AERROR_IAMDEAD		=-6,	//攻击者是个死人
	AERROR_BREAK		=-7,	//攻击被打断
	AERROR_CANNOTATTACK =-8,	//不能攻击的目标

};
//特殊属性
enum ESPECIAL_ABILITY_NUMBER
{
	EAN_GEM_COMPOUNDED	= MAX_CHAR_ABILITY_NUM + 1,	// 宝石合成
	EAN_GEM_EMBEDDED,								// 宝石镶嵌
};

// 冷却ID, 先写几个作测试
enum
{
		COOLDOWN_LIST_SIZE = 255,
};

enum
{
	COMMONCOOLDOWN_TIME = 750,
};
//技能消耗
enum SKILL_DEPLETE_LOGIC
{
	DEPLETE_INVALID = -1,
	DEPLETE_MANA = 0,	//
	DEPLETE_RAGE,		//怒气
	DEPLETE_STRIKE_POINT,//
	DEPLETE_ITEM_STD,
};
//人物状态
enum EFFECT_STATUS
{
	ESTATUS_COLD		=0,	//迟缓
	ESTATUS_FIRE		=1, //弱化
	ESTATUS_LIGHT		=2,	//眩晕
	ESTATUS_POISON		=3,	//中毒

	ESTATUS_NUMBER, //人物状态数量
};

enum SKILL_ATTRIBUTE
{
	SATTRIBUTE_ATTACK_P			=0, //增加物理攻击点数
	SATTRIBUTE_RATE_ATTACK_P	=1, //增加物理攻击百分比

	SATTRIBUTE_NUMBER, //技能影响属性的数量
};

//怪物AI的元素
enum MONSTER_AI_PRAM
{
	AIPARAM_SCANTIME			=0,	//如果此值大于0，则为主动攻击，值的含义就是扫描间隔
									//如果小于等于0，则为非主动攻击
	AIPARAM_RANDMOVETIME		=1,	//随机移动位置的时间间隔（毫秒）
	AIPARAM_CANNOTATTACK		=2,	//无法攻击的对象(已经废弃, 是否无敌是以MonsterAttrExTable.txt表中为主)
	AIPARAM_RETURN				=3, //如果此值大于0，则当怪物距离出生地大于此值时，怪物放弃追赶
	AIPARAM_SCANENEMYDIST		=4, //扫描敌人的最大距离	
	AIPARAM_SCANTEAMMATEDIST	=5, //扫描队友的最大距离	
	AIPARAM_RESETTARGET_DIST	=6, //如果当前的移动目标和敌人的位置之间的距离大于此数值
									//则需要重新设定移动目标
	AIPARAM_PATROLTIME			=7,//巡逻的时间间隔，若小于等于0，则不进行巡逻
	AIPARAM_STRIKEBACK			=8,//是否会还击

	AIPARAM_NUMBER,
};
//角色属性
enum ENUM_UPDATE_CHAR_ATT
{
	UPDATE_CHAR_ATT_JOB		=0,			//职业
	UPDATE_CHAR_ATT_COUNTRY,			//国家
	UPDATE_CHAR_ATT_DATA_ID,		    // 数据资源ID
	UPDATE_CHAR_ATT_NAME,				// 姓名
	UPDATE_CHAR_ATT_COUNTRYTITLE,		// 国家头衔
	UPDATE_CHAR_ATT_GUILDTITLE,			// 帮会头衔
    UPDATE_CHAR_ATT_NORMALTITLE,		// 玩法头衔
	UPDATE_CHAR_ATT_LEVEL,				// 等级
	UPDATE_CHAR_ATT_HP_PERCENT,			// HP百分比
	UPDATE_CHAR_ATT_MP_PERCENT,			// MP百分比
	UPDATE_CHAR_ATT_PNEUMA_PERCENT,		// 元气百分比
	UPDATE_CHAR_ATT_RAGE,				// 怒气
	UPDATE_CHAR_ATT_STEALTH_LEVEL,		// 隐身级别
	UPDATE_CHAR_ATT_SIT,				// 是否为坐下状态
	UPDATE_CHAR_ATT_MOVE_SPEED,			// 移动速度
	UPDATE_CHAR_ATT_ATTACK_SPEED,		// 攻击速度
	UPDATE_CHAR_ATT_CAMP_ID,			// 阵营ID
	UPDATE_CHAR_ATT_PORTRAIT_ID,		// 头像ID
	UPDATE_CHAR_ATT_MODEL_ID,			// 模型ID
	UPDATE_CHAR_ATT_MOUNT_ID,			// 座骑ID
	UPDATE_CHAR_ATT_MOUNT_INDEX,		// 座骑Index                             [7/23/2010 陈军龙]
	UPDATE_CHAR_ATT_AITYPE,				// AI类型
	UPDATE_CHAR_ATT_PLAYER_DATA,		// 00|0000|0000|0000|0000
										//     |    |    |    |  
										//    头发 脸型 头发 脸型
										//    颜色 颜色 模型 模型
	UPDATE_CHAR_IS_IN_STALL,			// 是否摆摊状态
	UPDATE_CHAR_STALL_NAME,				// 摊位名

	UPDATE_CHAR_STALL_PUBLIC,			// 摊位是否开市(公开显示摊位牌给其他玩家)	20100706 BLL

	UPDATE_CHAR_OCCUPANT,				// 占有者(是谁打的，死了算谁的)
	UPDATE_CHAR_OWNER,					// 拥有者(是谁控制的)
	UPDATE_CHAR_BUSOBJID,					//Bus ID

	UPDATE_CHAR_ATT_NUMBERS //基础信息数量,(目前不能超过32)
};
//属性详细信息
enum ENUM_DETAIL_ATTRIB
{
	DETAIL_ATTRIB_LEVEL		= 0,		//等级
	DETAIL_ATTRIB_HP,					//生命值
	DETAIL_ATTRIB_MP,					//魔法值
	DETAIL_ATTRIB_PNEUMA,				//元气值
	DETAIL_ATTRIB_EXP,					//经验
	DETAIL_ATTRIB_MONEY,				//货币

	DETAIL_ATTRIB_STR,					//力量 力量
	DETAIL_ATTRIB_CON,					//体制 体制
	DETAIL_ATTRIB_INT,					//定力 智力
	DETAIL_ATTRIB_DEX,					//身法 敏捷
	DETAIL_ATTRIB_POINT_REMAIN,			//剩余点数
	DETAIL_ATTRIB_SKILLPOINT_REMAIN,    //剩余技能点
	DETAIL_ATTRIB_S_SKILLPOINT,

	DETAIL_ATTRIB_ATT_NEAR,             //近程攻击
	DETAIL_ATTRIB_ATT_FAR,              //远程攻击
	DETAIL_ATTRIB_DEF_NEAR,             //近程防御
	DETAIL_ATTRIB_DEF_FAR,              //远程防御

	DETAIL_ATTRIB_ATT_MAGIC_NEAR,		//近程内功攻击力
	DETAIL_ATTRIB_ATT_MAGIC_FAR,		//近程外功攻击力

	DETAIL_ATTRIB_DEF_MAGIC_NEAR,		//近程内功防御力
	DETAIL_ATTRIB_DEF_MAGIC_FAR,		//近程外功防御力

	DETAIL_ATTRIB_MAXHP,				//最大生命值
	DETAIL_ATTRIB_MAXMP,				//最大魔法值
	DETAIL_ATTRIB_MAXPNEUMA,			//最大元气值
	DETAIL_ATTRIB_HP_RESPEED,			//HP恢复速度  点/秒
	DETAIL_ATTRIB_MP_RESPEED,			//MP恢复速度  点/秒
	DETAIL_ATTRIB_VIGOR_RESPEED,		//活力恢复速度  点/秒

	DETAIL_ATTRIB_TOUGHNESS,            //韧性

	DETAIL_ATTRIB_HIT,					//命中率
	DETAIL_ATTRIB_MISS,					//闪避率
	DETAIL_ATTRIB_CRITRATE,				//会心率
	
	DETAIL_ATTRIB_MAXRAGE,				//怒气上限
	DETAIL_ATTRIB_RAGE,					//怒气
	DETAIL_ATTRIB_RAGE_RESPEED,			//怒气恢复
	DETAIL_ATTRIB_CRITICALHURT,			//爆击伤害
	DETAIL_ATTRIB_STRIKE_POINT,			//连技点

	DETAIL_ATTRIB_MOVESPEED,			//移动速度
	DETAIL_ATTRIB_ATTACKSPEED,			//攻击速度

	DETAIL_ATTRIB_ATTACK_GOLD,			//金攻击	
	DETAIL_ATTRIB_DEFENCE_GOLD,			//金防御

	DETAIL_ATTRIB_ATTACK_WOOD,			//木攻击
	DETAIL_ATTRIB_DEFENCE_WOOD,			//木防御

	DETAIL_ATTRIB_ATTACK_WATER,			//水攻击
	DETAIL_ATTRIB_DEFENCE_WATER,		//水防御

	DETAIL_ATTRIB_ATTACK_FIRE,			//火攻击	
	DETAIL_ATTRIB_DEFENCE_FIRE,			//火防御

	DETAIL_ATTRIB_ATTACK_SOIL,			//土攻击	
	DETAIL_ATTRIB_DEFENCE_SOIL,			//土防御

	DETAIL_ATTRIB_NEARATT_REDUCE,		///近程减免
	DETAIL_ATTRIB_FARATT_REDUCE,		///远程减免
	DETAIL_ATTRIB_MAGIC_NEAR_ATT_REDUCE,	///近程内功减免
	DETAIL_ATTRIB_MAGIC_FAR_ATT_REDUCE,	///近程外功减免
	DETAIL_ATTRIB_DREAD_RESIST,			///恐惧抗性
	DETAIL_ATTRIB_COMA_RESIST,			///昏迷抗性
	DETAIL_ATTRIB_HUSH_RESIST,			///沉默抗性
	DETAIL_ATTRIB_UNARM_RESIST,			///缴械抗性
	DETAIL_ATTRIB_ATTACKSPEED_RESIST,	///减攻速抗性
	DETAIL_ATTRIB_SKILLSPEED_RESIST,	///减施速抗性
	DETAIL_ATTRIB_MOVEREDUCE_RESIST,	///减移速抗性

	DETAIL_ATTRIB_COUNTRY,              //国家
	DETAIL_ATTRIB_MEMPAI,				//门派
	DETAIL_ATTRIB_GUILD,				//帮派
    DETAIL_ATTRIB_GUILD_POINT,			//帮派贡献度
    DETAIL_ATTRIB_PK_VALUE,			    //杀气
    DETAIL_ATTRIB_HONOR,			    //荣誉
	DETAIL_ATTRIB_FAMILY,				//家族
	DETAIL_ATTRIB_GUILD_OFFICIAL,		//帮会官职
	DETAIL_ATTRIB_CAMP,					//阵营
	DETAIL_ATTRIB_DATAID,				//DataID
	DETAIL_ATTRIB_PORTRAITID,			//头像
	DETAIL_ATTRIB_FACEMODEL,
	DETAIL_ATTRIB_MODELID,				//外形
	DETAIL_ATTRIB_MOUNTID,				//座骑
	DETAIL_ATTRIB_MOUNTINDEX,			//座骑索引                  [7/23/2010 陈军龙]
	DETAIL_ATTRIB_CURRENT_PET_GUID,		//当前的宠物GUID

	DETAIL_ATTRIB_LIMIT_MOVE,			//是否限制不能移动
	DETAIL_ATTRIB_CAN_ACTION1,			//技能限制标记1.
	DETAIL_ATTRIB_CAN_ACTION2,			//技能限制标记2.	

	DETAIL_ATTRIB_VIGOR,				//活力
	DETAIL_ATTRIB_MAX_VIGOR,			//活力上限
	DETAIL_ATTRIB_ENERGY,				//精力
	DETAIL_ATTRIB_MAX_ENERGY,			//精力上限

	DETAIL_ATTRIB_GOODBADVALUE,			//善恶值

	DETAIL_ATTRIB_GUID,			//GUID

	//DETAIL_ATTRIB_MISSION_HAVEDONE_FLAGS,	//任务的完成标志
	//DETAIL_ATTRIB_MISSION_KILLOBJECT_FLAGS,	//任务的杀怪标志
	//DETAIL_ATTRIB_MISSION_ENTERAREA_FLAGS,	//任务的区域标志
	//DETAIL_ATTRIB_MISSION_ITEMCHANGED_FLAGS,	//任务的道具更新标志


	DETAIL_ATTRIB_NUMBERS				
};

//伤害类型
typedef enum DAMAGE_TYPE
{
	//DAMAGE_NOSPECIALTYPE = 0,
	DAMAGE_TYPE_NEAR,
	DAMAGE_TYPE_FAR,		//远程伤害
	DAMAGE_TYPE_MAGIC_NEAR,	//近程内功伤害
	DAMAGE_TYPE_MAGIC_FAR,		//近程外功伤害
	DAMAGE_TYPE_GOLD,	//金系伤害
	DAMAGE_TYPE_WOOD,	//木系伤害
	DAMAGE_TYPE_WATER,	//水系伤害
	DAMAGE_TYPE_FIRE,	//火系伤害
	DAMAGE_TYPE_SOIL,	//土系伤害
	DAMAGE_TYPE_NUMBER,	//伤害类型数据
} DamageType_T;


// 角色属性
enum ENUM_CHAR_ATT
{
	CHAR_ATT_INVALID	= -1,
	CHAR_ATT_STR,				// 力量 力量
	//CHAR_ATT_SPR,				// 灵气 灵力
	CHAR_ATT_CON,				// 体制 体制
	CHAR_ATT_INT,				// 定力 智力
	CHAR_ATT_DEX,				// 身法 敏捷

	CHAR_ATT_HP,				// HP
	CHAR_ATT_MP,				// MP
	CHAR_ATT_MAX_HP,			// HP上限
	CHAR_ATT_MAX_MP,			// MP上限

	CHAR_ATT_RESTORE_HP,		// HP回复
	CHAR_ATT_RESTORE_MP,		// MP回复

	CHAR_ATT_HIT,				// 命中率
	CHAR_ATT_MISS,				// 闪避
	CHAR_ATT_CRIT_RATE,			// 会心率

	CHAR_ATT_SPEED,				// 移动速度
	CHAR_ATT_ATTACK_SPEED,		// 攻击速度

	//CHAR_ATT_ATTACK_PHYSICS,	// 物理攻击
	//CHAR_ATT_DEFENCE_PHYSICS,	// 物理防御
	
	CHAR_ATT_ATTACK_NEAR,	    // 近程攻击
	CHAR_ATT_DEFENCE_NEAR,	    // 近程防御

	CHAR_ATT_ATTACK_FAR,	    // 远程攻击
	CHAR_ATT_DEFENCE_FAR,	    // 远程防御

	CHAR_ATT_ATTACK_MAGIC_NEAR,	// 近程内功攻击
	CHAR_ATT_DEFENCE_MAGIC_NEAR,// 近程内功防御

	CHAR_ATT_ATTACK_MAGIC_FAR,	// 近程外功攻击
	CHAR_ATT_DEFENCE_MAGIC_FAR,	// 近程外功防御

	CHAR_ATT_ATTACK_GOLD,		// 金攻击
	CHAR_ATT_DEFENCE_GOLD,		// 金防御

	CHAR_ATT_ATTACK_WOOD,		// 木攻击
	CHAR_ATT_DEFENCE_WOOD,		// 木防御

	CHAR_ATT_ATTACK_WATER,		// 水攻击
	CHAR_ATT_DEFENCE_WATER,		// 水防御

	CHAR_ATT_ATTACK_FIRE,		// 火攻击
	CHAR_ATT_DEFENCE_FIRE,		// 火防御

	CHAR_ATT_ATTACK_SOIL,		// 土攻击
	CHAR_ATT_DEFENCE_SOIL,		// 土防御

	CHAR_ATT_ANGER,				// 怒气值
	CHAR_ATT_SKILL_POINT,		// 连技点

	CHAR_ATT_NUMBERS
};
//队伍错误信息
enum TEAM_ERROR
{
	TEAM_ERROR_INVITEDESTHASTEAM=0 ,	//邀请对象已经属于某个组了
	TEAM_ERROR_INVITEREFUSE ,			//被邀请人拒绝加入
	TEAM_ERROR_INVITETEAMFULL ,			//邀请人的队伍人数已经满了
	TEAM_ERROR_INVITELEADERREFUSE ,		//队长拒绝新成员被邀请加入
	TEAM_ERROR_DISMISSNOTLEADER ,		//解散队伍的人不是队长
	TEAM_ERROR_KICKNOTLEADER ,			//踢人者不是队长
	TEAM_ERROR_APPLYSOURHASTEAM ,		//申请人已经属于某个组了
	TEAM_ERROR_APPLYDESTHASNOTTEAM ,	//被申请者不属于某个组
	TEAM_ERROR_APPLYLEADERREFUSE ,		//队长不同意申请人加入队伍
	TEAM_ERROR_APPLYTEAMFULL ,			//被申请人的队伍人数已经满了
	TEAM_ERROR_APPLYLEADERGUIDERROR ,	//被申请人所在队伍的队长GUID发生变化
	TEAM_ERROR_APPOINTSOURNOTEAM ,		//旧队长不是队伍成员
	TEAM_ERROR_APPOINTDESTNOTEAM ,		//新队长不是队伍成员
	TEAM_ERROR_APPOINTNOTSAMETEAM ,		//任命时两个人不属于同一个队伍
	TEAM_ERROR_APPOINTSOURNOLEADER ,	//旧队长不是队伍的队长了
	TEAM_ERROR_APPLYLEADERCANTANSWER,	//队长目前无法答复
	TEAM_ERROR_INVITERNOTINTEAM,		//邀请人不在队长的队伍中
	TEAM_ERROR_APPLYWHENINTEAM,			//申请人在有队伍的情况下申请入队
	TEAM_ERROR_TEAMFULL,				//队伍人数已满。
	TEAM_ERROR_REFUSEINVITESETTING,		//被邀请人设置了拒绝邀请
	TEAM_ERROR_TARGETNOTONLINE,			//对方已经离线，加入失败。
	TEAM_ERROR_LEAVETEAM,				//对方已经离开队伍了，请加入其它队伍
	TEAM_ERROR_DISTRIBNOLEADER,			//非leader设置分配方式
	TEAM_ERROR_INVITEEOFFLINE,			//被邀请人处于离线状态
	
	TEAM_ERROR_NUMBER ,	//队伍功能错误号的最大值
};
//队伍消息
enum TEAM_RESULT
{
	TEAM_RESULT_MEMBERENTERTEAM=0 ,		//成员加入队伍
	TEAM_RESULT_MEMBERLEAVETEAM ,		//普通成员离开队伍
	TEAM_RESULT_LEADERLEAVETEAM ,		//队长离开队伍
	TEAM_RESULT_TEAMDISMISS ,			//队伍解散
	TEAM_RESULT_TEAMKICK ,				//踢除队员
	TEAM_RESULT_TEAMAPPOINT ,			//任命新队长
	TEAM_RESULT_TEAMREFRESH,			// 重新请求队伍信息的回复
	TEAM_RESULT_STARTCHANGESCENE,		// 开始切换场景
	TEAM_RESULT_ENTERSCENE,				// 队友进入新场景
	TEAM_RESULT_REFRESHSERVERINFO,		// 玩家跳转场景后，给服务器刷新队伍消息
	TEAM_RESULT_MEMBEROFFLINE,			// 玩家下线

	TEAM_RESULT_NUMBER , //队伍结果类型的最大值
};
//队伍信息通知
enum NOTIFY_TEAMINFO
{
	NOTIFY_USERCHANGESCENE=0 ,	//队员转移场景
	NOTIFY_USERENTERSCENE,		//队员进入场景

};

//系统聊天时指定的显示位置
enum ENUM_SYSTEM_CHAR_SHOW_POS
{
	CHAT_MAIN_WINDOW = 0,	//显示在主界面的聊天窗口内
	CHAT_LEFTDOWN,			//左下角个人的系统提示内
	CHAT_RIGHTDOWN,			//右下角系统的系统提示内
	CHAT_PLUMB_SCROLL,		//垂直滚动提示内
	CHAT_PLANE_SCROLL,		//水平滚动提示内
	CHAR_SHOW_POS_NUM

};
//聊天类型
enum ENUM_CHAT_TYPE
{
	CHAT_TYPE_INVALID = -1,

	CHAT_TYPE_NEAR =0 ,	//普通说话消息
	CHAT_TYPE_TEAM ,		//队聊消息
	CHAT_TYPE_WORLD,		//世界
	CHAT_TYPE_USER ,		//私聊消息
	CHAT_TYPE_SYSTEM ,		//系统消息
	CHAT_TYPE_JIAZU ,		//家族消息
	CHAT_TYPE_GUILD ,		//帮派消息
	CHAT_TYPE_COUNTRY,//////////国家
//以上8个是 策划要求的

	CHAT_TYPE_MENPAI,//门派
	
	CHAT_TYPE_CHANNEL ,		//自建聊天频道消息
	CHAT_TYPE_SCENE ,		//场景消息
	CHAT_TYPE_SELF,			//仅客户端使用的消息

	CHAT_TYPE_DMA_FORCE,		//双人强制
	CHAT_TYPE_DMA_REQUEST,		//双人邀请
	CHAT_TYPE_DMA_AGREE,		//双人同意
	CHAT_TYPE_DMA_REFUSE,		//双人拒绝
	CHAT_TYPE_DMA_CANCEL,		//双人停止
 
 
	CHAT_TYPE_NUMBER,			//聊天类型的最大值
};

//修正定义by czg 2009-12-9
#define CHAT_TYPE_NORMAL CHAT_TYPE_NEAR
#define CHAT_TYPE_TELL CHAT_TYPE_USER
//聊天消耗 
enum CHAT_NEED_TYPE
{
	CHAT_NEED_NONE		= -1,					
	CHAT_NEED_MP		= 0 ,				//需要消耗MP
	CHAT_NEED_ENERGY	= 1 ,				//需要精力
	CHAT_NEED_VIGOR		= 2 ,				//需要活力

	CHAT_NEED_NUMBER,					//消耗类型的最大值
};
//聊天错误
enum CHANNEL_ERROR
{
	CHANNEL_ERROR_HASCHANNEL = 0 ,		//此用户已经创建了一个聊天频道了
	CHANNEL_ERROR_CHANNELFULL ,			//聊天频道创建失败
	CHANNEL_ERROR_NOCHANNEL ,			//没有频道信息
	CHANNEL_ERROR_CHANNELMEMBERFULL ,	//聊天频道内人数满了
	CHANNEL_ERROR_MEMBEREXIST ,			//用户已经存在聊天频道内了
	CHANNEL_ERROR_NOTINCHANNEL ,		//用户不在此聊天频道内


	CHANNEL_ERROR_NUMBER , //自建聊天频道错误号的最大值
};
//聊天消失
enum CHANNEL_RESULT
{
	CHANNEL_RESULT_CREATE = 0 ,			//创建聊天频道
	CHANNEL_RESULT_ADDMEMBER ,			//聊天频道内添加了新成员
	CHANNEL_RESULT_DISMISS ,			//自建聊天频道解散
	CHANNEL_RESULT_KICKMEMBER ,			//踢除成员


	CHANNEL_RESULT_NUMBER , //自建聊天频道结果类型的最大值
};

// 队员信息
enum ENUM_TEAM_MEMBER_ATT
{
	TEAM_MEMBER_ATT_INVALID	= -1,

	TEAM_MEMBER_ATT_FAMILY,			// 门派
	TEAM_MEMBER_ATT_LEVEL,			// 等级
	TEAM_MEMBER_ATT_POSITION,		// 位置

	TEAM_MEMBER_ATT_HP,				// HP
	TEAM_MEMBER_ATT_MAX_HP,			// HP上限
	TEAM_MEMBER_ATT_MP,				// MP
	TEAM_MEMBER_ATT_MAX_MP,			// MP上限
	TEAM_MEMBER_ATT_ANGER,			// 怒气值

	TEAM_MEMBER_ATT_WEAPON,			// 武器
	TEAM_MEMBER_ASSIHAND,			// 副武器
	TEAM_MEMBER_ATT_CAP,			// 帽子
	TEAM_MEMBER_ATT_SCAPULAR,		// 肩甲
	TEAM_MEMBER_ATT_ARMOR,			// 衣服
	TEAM_MEMBER_ATT_CUFF,			// 手套
	TEAM_MEMBER_ATT_BOOT,			// 靴子

	TEAM_MEMBER_ATT_BUFF,			// 有益 buff

	TEAM_MEMBER_ATT_DEADLINK,		// 断线
	TEAM_MEMBER_ATT_DEAD,			// 死亡
	TEAM_MEMBER_ATT_FACEMESH,		// 面部模型
	TEAM_MEMBER_ATT_HAIRMESH,		// 头发模型
	TEAM_MEMBER_ATT_HAIRCOLOR,		// 头发颜色

	TEAM_MEMBER_ATT_NUMBERS
};

//共享内存类型
enum	SHAREMEM_TYPE
{
	ST_INVAILD		=  -1,
	ST_HUMAN_SMU	=	1,
	ST_GUILD_SMU	=	2,
	ST_MAIL_SMU		=	3,
	ST_PSHOP_SMU	=	4,
	ST_USERDATA_SMU	=	5,
	ST_HUMANEXT_SMU	=	6,
	ST_ITEMSERIAL_SMU = 7,
};


//共享内存使用状态
enum   SHAREMEM_USE_STATUS
{
	SUS_NEVER_USE		= 0,				//没有被使用过
    SUS_SERVER_USED				= 1,		//Server 占用
	SUS_SERVER_HAVE_CLEANED		= 2,		//Server 正常ShutDown ，已经清除
	SUS_WORLD_USED				= 3,		//World 占用
	SUS_WORLD_HAVE_CLEANED		= 4,		//World 正常ShutDown ，已经清除
};

enum UDRETURN
{
	UDR_NOTFINDUSERDATA = 0 ,	//没有发现用户数据
	UDR_USERDATA ,				//拥有用户信息
	UDR_USERDATALIVING ,		//用户信息还在目的服务器的缓存中
	UDR_USERSERVERCRASH,		//用户Server已经Crash,可能还在缓存中,Server正在处理这块缓存
	UDR_KEYERROR ,				//验证码错误
};

enum ENUM_COMBAT_EVENT //技能和效果关心的事件
{
	EVENT_ON_DAMAGE = 0,
	EVENT_ON_HIT_BY_SKILL,
	EVENT_ON_HIT_TARGET,
	EVENT_ON_BE_CRITICAL_HIT,
	EVENT_ON_CRITICAL_HIT_TARGET,
	EVENT_ON_HEAL_TARGET,
	EVENT_ON_BE_HEAL,
	EVENT_ON_DEAD,
	NUMBER_OF_EVENTS
};

// 杀气值
enum ENUM_PK_VALUE_RANGE
{
	PK_VALUE_RANGE_1	= 1,
	PK_VALUE_RANGE_20	= 20,
	PK_VALUE_RANGE_40	= 40,
	PK_VALUE_RANGE_60	= 60,
	PK_VALUE_RANGE_80	= 80,
	PK_VALUE_RANGE_MAX	= 1000,
};
//队伍跟随消息
enum TEAM_FOLLOW_RESULT
{
	TF_RESULT_REFUSE_FOLLOW = 0,	// 队员拒绝跟随队长
	TF_RESULT_ENTER_FOLLOW,			// 队员进入组队跟随状态
	TF_RESULT_STOP_FOLLOW,			// 队员退出组队跟随状态
	TF_RESULT_FOLLOW_FLAG,			// 通知客户端进入组队跟随状态的标记（ENTER_FOLLOW 的 quiet 模式）
};
//队伍跟随错误消息
enum TEAM_FOLLOW_ERROR
{
	TF_ERROR_TOO_FAR = 0,			// 离队长太远了（而不能跟随）
	TF_ERROR_IN_TEAM_FOLLOW,		// 已经处于组队跟随状态（而不能做某些操作）
	TF_ERROR_STALL_OPEN,			// 正在摆摊
	TF_ERROR_NOT_IN_FOLLOW_MODE,	// 队伍目前不处于跟随状态
};

enum SERVER_TYPE			//服务器端程序类型
{
	SERVER_GAME = 0 ,		//游戏服务器端程序
	SERVER_LOGIN = 1 ,		//登陆服务器端程序
	SERVER_SHAREMEN = 2 ,	//共享存储端程序
	SERVER_WORLD = 3,
	SERVER_BILLING = 4,		//公告服务器?
	SERVER_NUMBER ,
};
//关系组
enum RELATION_GROUP
{
	RELATION_GROUP_FRIEND_ALL		= 0,		//全部好友
	RELATION_GROUP_F1,							//好友1组
	RELATION_GROUP_F2,							//好友2组
	RELATION_GROUP_F3,							//好友3组
	RELATION_GROUP_F4,							//好友4组
	RELATION_GROUP_F5,							//好友5组
	RELATION_GROUP_BLACK,						//黑名单组
	RELATION_GROUP_ENEMY,						//敌人组
	
	RELATION_GROUP_NUMBER ,						//存储组数量

	RELATION_GROUP_TEMPFRIEND,					//临时好友
};

enum RELATION_TYPE //联系人关系
{
	RELATION_TYPE_NONE				= 0,		//空
	RELATION_TYPE_FRIEND,						//好友
	RELATION_TYPE_BROTHER,						//结拜
	RELATION_TYPE_MARRY,						//结婚
	RELATION_TYPE_BLACKNAME,					//黑名单
	RELATION_TYPE_ENEMY,						//仇人
	RELATION_TYPE_TEMPFRIEND,					//临时好友
	RELATION_TYPE_STRANGER,						//陌生人关系
	RELATION_TYPE_MASTER,						//师傅关系
	RELATION_TYPE_PRENTICE,						//徒弟关系
	RELATION_TYPE_SIZE,							//关系种类
};



#define RELATION_FRIEND_OFFSET 0
#define RELATION_BLACKNAME_OFFSET 200
#define RELATION_ENEMY_OFFSET	  230


enum ENUM_SKILL_CLASS_BY_USER_TYPE//技能的使用者分类
{
	A_SKILL_FOR_PLAYER 	= 0,
	A_SKILL_FOR_MONSTER = 1,
	A_SKILL_FOR_PET 	= 2,
	A_SKILL_FOR_ITEM 	= 3,
};
enum CONSTANT_VALUE //一些常量
{
	DEFAULT_ATTACK_FLUCTUATION = 8, //攻击浮动 +/- 8%
};



//GM指令类型
enum COMMAND_TYPE
{
	COMMAND_TYPE_NONE = 0 ,				//空指令
	COMMAND_TYPE_TELEPORT ,				//将一个OBJ移动到某地
	COMMAND_TYPE_MODIFYMENPAI ,			//修改角色门派属性
	COMMAND_TYPE_MODIFYXINFA ,			//修改角色心法等级
	COMMAND_TYPE_LEVELUPALLXINFA,		//所有心法等级修改
	COMMAND_TYPE_CREATEITEM ,			//创建物品
	COMMAND_TYPE_RELIVE ,				//复活自己
	COMMAND_TYPE_CHAT ,					//发送Chat消息
	COMMAND_TYPE_ENABLEGOD ,			//充许无敌
	COMMAND_TYPE_DISABLEGOD ,			//禁止无敌
	COMMAND_TYPE_IAMGOD ,				//变成无敌
	COMMAND_TYPE_IAMDOG ,				//取消无敌
	COMMAND_TYPE_DEBUG_RELOADCONFIG ,	//重新读取Config配置文件
	COMMAND_TYPE_SYSCHAT ,				//系统弹出消息
	COMMAND_TYPE_DEBUG_SHUTDOWN ,		//关闭服务器
	COMMAND_TYPE_TEAM_INVITE ,			//队伍-邀请
	COMMAND_TYPE_TEAM_RETINVITE ,		//队伍-邀请回应
	COMMAND_TYPE_TEAM_LEADERRETINVITE , //队伍-队长邀请回应
	COMMAND_TYPE_TEAM_APPLY ,			//队伍-申请
	COMMAND_TYPE_TEAM_RETAPPLY ,		//队伍-申请回应
	COMMAND_TYPE_TEAM_LEAVE ,			//队伍-离开
	COMMAND_TYPE_TEAM_KICK ,			//队伍-踢人
	COMMAND_TYPE_TEAM_DISMISS ,			//队伍-解散
	COMMAND_TYPE_TEAM_APPOINT ,			//队伍-任命
	COMMAND_TYPE_ABILITY_DETAIL,		//请求生活技能详细信息
	COMMAND_TYPE_USE_ABILITY,			//使用生活技能
	COMMAND_TYPE_COMBOUND_GEM,			//合成宝石
	COMMAND_TYPE_USE_GEM,				//宝石镶嵌
	COMMAND_TYPE_CHANNEL_CREATE,		//自建聊天频道-创建
	COMMAND_TYPE_CHANNEL_INVITE,		//自建聊天频道-邀请
	COMMAND_TYPE_CHANNEL_DISMISS,		//自建聊天频道-解散
	COMMAND_TYPE_CHANNEL_KICK,			//自建聊天频道-踢除成员
	COMMAND_TYPE_GOTO ,					//传送玩家本身到目标位置（或新场景）
	COMMAND_TYPE_FULLRECOVER ,			//回复满血、魔
	COMMAND_TYPE_CREATEPET ,			//创建宠物
	COMMAND_TYPE_DELETEPET ,			//删除宠物
	COMMAND_TYPE_CAPTUREPET ,			//捕捉宠物
	COMMAND_TYPE_CALLUPPET ,			//召唤宠物
	COMMAND_TYPE_RECALLPET ,			//收回宠物
	COMMAND_TYPE_FREEPETTONATURE ,		//放生宠物
	COMMAND_TYPE_RETURNTOCHILD ,		//宠物还童
	COMMAND_TYPE_SKILL_RELIVE,			//技能复活
	COMMAND_TYPE_CREATESCENE ,			//创建一个副本场景
	COMMAND_TYPE_CLOSESCENE ,			//强制关闭一个副本场景
	COMMAND_TYPE_SET_SCENE_TYPE,		//设置场景类型
	COMMAND_TYPE_SET_PK_VALUE,			//设置杀气
	COMMAND_TYPE_SET_MODEL_ID,			//设置模型ID
	COMMAND_TYPE_SET_EQUIP_DUR,			//设置装备耐久度
	COMMAND_TYPE_SETDAMAGE,				//设置伤害
	COMMAND_TYPE_KILLOBJ,				//杀死一个OBJ
	COMMAND_TYPE_CREATEMONSTER,			//生成一只怪物
	COMMAND_TYPE_DELETEMONSTER,			//删除一只生成的怪物
	COMMAND_TYPE_SETAITYPE,				//修改AI类型
	COMMAND_TYPE_MODIFYMONEY,			//修改金钱
	COMMAND_TYPE_MAKETEAMFOLLOW,		//模拟队伍跟随
	COMMAND_TYPE_SENDMAIL,				//发送邮件
	COMMAND_TYPE_RECVMAIL,				//接收邮件
	COMMAND_TYPE_CREATEGUILD,			// 创建帮会
	COMMAND_TYPE_JOINGUILD,				// 加入帮会
	COMMAND_TYPE_GUILDRECRUIT,			// 帮会收人
	COMMAND_TYPE_GUILDEXPEL,			// 帮会踢人
	COMMAND_TYPE_LEAVEGUILD,			// 离开帮会
	COMMAND_TYPE_GUILDDISMISS,			// 解散帮会
	COMMAND_TYPE_ASKGUILDLIST,			// 帮会列表
	COMMAND_TYPE_SETMOVEMODE,			// 设置移动模式 走/跑/疾跑
	COMMAND_TYPE_ASKRELATIONLIST,		// 关系列表
	COMMAND_TYPE_ADDFRIEND,				// 加入一个好友
	COMMAND_TYPE_SETFRIENDPOINT,		// 设置友好度
	COMMAND_TYPE_ADDBLACKNAME,			// 加入黑名单
	COMMAND_TYPE_DELFRIEND,				// 删除一个好友
	COMMAND_TYPE_DELBLACK,				// 从黑名单里删除一个玩家
	COMMAND_TYPE_TRANSITION,			// 组间转移
	COMMAND_TYPE_SETCAMPID,				// 设置阵营
	COMMAND_TYPE_SAVE,					// 保存用户档案
	COMMAND_TYPE_GETOBJINFO,			// 取得某个obj的服务器端数据
	COMMAND_TYPE_LEVELUP,				// 升级
	COMMAND_TYPE_ABILITYUP,				// 生活技能升级
	COMMAND_TYPE_WHO,					// 当前场景
	COMMAND_TYPE_ALLWHO,				// 所有场景
	COMMAND_TYPE_CATCHPLAYER,			// 取得世界中某个玩家的基本信息
	COMMAND_TYPE_PLAYERINFO,			// 取得场景中某个玩家的详细信息
	COMMAND_TYPE_SETPETHAPPINESS,		// 设置宠物的快乐度
	COMMAND_TYPE_SETPETHP,				// 设置宠物HP
	COMMAND_TYPE_SETPETLIFE,			// 设置宠物的寿命
	COMMAND_TYPE_PETLEVELUP,			// 升级当前宠物
	COMMAND_TYPE_SETPETSKILL,			// 设置宠物的技能
	COMMAND_TYPE_USEPETSKILL,			// 使用宠物的技能
	COMMAND_TYPE_LEVELDOWN,				// 降级，只降低级别数值，不管其他相关的属性
	COMMAND_TYPE_ADDEXP,				// 增加经验
	COMMAND_TYPE_CREATECITY,			// 建立城市
	COMMAND_TYPE_DELETECITY,			// 摧毁城市
	COMMAND_TYPE_LOADMONSTER,			// 像场景增加一批怪物
	COMMAND_TYPE_SETHAIRCOLOR,			// 设置玩家头发颜色
	COMMAND_TYPE_SETHAIRMODEL,			// 设置玩家头发模型
	COMMAND_TYPE_CREATEGUARD,			// 创建分身
	COMMAND_TYPE_CREATETRAP,			// 创建陷阱
	COMMAND_TYPE_USEITEM,				// 使用物品
	COMMAND_TYPE_FORGETRECIPE,			// 忘记配方
	COMMAND_TYPE_SEND_IMPACT_TO_UNIT,	// 给某个角色一个效果
	COMMAND_TYPE_RELOAD_COMBAT_TABLES,	// 重新装载战斗数据表
	COMMAND_TYPE_USE_SKILL,				// 施放魔法
	COMMAND_TYPE_SAVEPACKETINFO,		// 保存消息分配信息
	COMMAND_TYPE_SETVIGOR,				// 设置活力值
	COMMAND_TYPE_SETENERGY,				// 设置精力值
	COMMAND_TYPE_PETPULLULATE,			// 宠物成长率
	COMMAND_TYPE_ADD_SKILL,				// 添加技能
	COMMAND_TYPE_REMOVE_SKILL,			// 删除技能
	COMMAND_TYPE_FINGERGUID,			// 用 GUID 找玩家信息
	COMMAND_TYPE_FINGERNAME,			// 用名字找玩家信息
	COMMAND_TYPE_ADVANCEDFINGER,		// 高级查找
	COMMAND_TYPE_SETABILITYEXP,			// 设置生活技能熟练度
	COMMAND_TYPE_SETGOODBAD,			// 设置善恶值
	COMMAND_TYPE_SETCURDUR,				// 设置当前耐久
	COMMAND_TYPE_NUMBER , //指令数量
};

// 宠物技能列表
enum ENUM_PET_SKILL_INDEX
{
	PET_SKILL_INDEX_INVALID = -1,
	PET_SKILL_INDEX_CONTROL_BY_PLAYER,
	PET_SKILL_INDEX_CONTROL_BY_AI0,
	PET_SKILL_INDEX_CONTROL_BY_AI1,
	PET_SKILL_INDEX_CONTROL_BY_AI2,
	PET_SKILL_INDEX_CONTROL_BY_AI3,
	PET_SKILL_INDEX_MENPAI,

	PET_SKILL_INDEX_NUMBERS
};

// 宠物技能操作模式
enum PET_SKILL_OPERATEMODE
{
	PET_SKILL_OPERATE_INVALID			= -1, // INVALID
	PET_SKILL_OPERATE_NEEDOWNER			= 0,  // 需要主人触发
	PET_SKILL_OPERATE_AISTRATEGY		= 1,  // 由AI来触发	
	PET_SKILL_OPERATE_INCEACEATTR		= 2,  // 增强宠物属性

	PET_SKILL_OPERATE_NUMBERS,
	
};

// 邮件类型
enum MAIL_TYPE
{
	MAIL_TYPE_NORMAL = 0 ,//普通邮件
	MAIL_TYPE_SYSTEM = 1 ,//系统邮件
	MAIL_TYPE_SCRIPT = 2 ,//脚本邮件，服务器端接收到此邮件后会调用一个脚本
	MAIL_TYPE_NORMAL2 = 3 , // 系统给玩家代发
};

// 可执行邮件功能
//!!!!此定义必须与脚本ScriptGlobal.lua中的定义完全相同，
//!!!!切勿在不了解整个可执行邮件流程的情况下随便添加
#define MAIL_REPUDIATE			1			//强制离婚
#define MAIL_BETRAYMASTER		2			//叛师
#define MAIL_EXPELPRENTICE		3			//开除徒弟
#define MAIL_UPDATE_ATTR		4			//更新不在线玩家属性(通过可执行邮件系统自动在玩家上线时更新)
#define MAIL_DELFRIEND			5			//删除好友

enum
{
	MAIL_ATTR_GUILD = 1,					//工会ID
	MAIL_ATTR_MONEY,						//身上的金钱
};

//请求邮件的请求类型
enum ASK_TYPE
{
	ASK_TYPE_LOGIN = 0 ,//用户刚登陆游戏时发送的邮件检查消息,
						//如果有邮件，服务器发送通知消息
	ASK_TYPE_MAIL ,	//用户向服务器提出需要邮件的消息
					//如果有邮件则发送邮件数据
};

// 游戏设置标志
// 低 16 位是需要传到 World 的，高 16 位是只需要 Server 保存的
enum GAME_SETTING_FLAG
{
	GSF_CANNOT_ADD_FRIEND			= 0,		//拒绝添加好友
	GSF_CANNOT_RECV_MAIL			= 1,		//拒绝接收邮件
	GSF_CANNOT_RECV_STRANGER_MAIL	= 2,		//拒绝接收陌生人邮件
	GSF_REFUSE_TEAM_INVITE			= 3,		// 拒绝组队邀请
	GSF_REFUSE_LOOK_SPOUSE_INFO		= 16,		// 拒绝查看配偶资料
	GSF_REFUSE_TRADE				= 17,		// 拒绝交易
	GSF_CLOSE_POPUP					= 18,		// 关闭当前泡泡框
	GSE_REFUSE_FACTION_INVITE		= 19,		// 拒绝帮派邀请
	GSE_LOCKED_SHORTCUT				= 20,		// 锁定快捷栏
	GSE_SHOW_OTHERPLAYER_NAME		= 21,		// 显示其他玩家的名字
	GSE_SHOW_RESTURN_NAME			= 22,		// 显示物品掉落名称
	GSE_SHOW_NPC_NAME				= 23,		// 显示怪物名称
};
enum SETTING_TYPE
{
	SETTING_TYPE_NONE = 0 ,
	SETTING_TYPE_GAME ,		//联系人设置, bit含义见 enum GAME_SETTING_FLAG
	SETTING_TYPE_K0 ,		//0号快捷栏设置
	SETTING_TYPE_K1 ,		//1号快捷栏设置
	SETTING_TYPE_K2 ,		//2号快捷栏设置
	SETTING_TYPE_K3 ,		//3号快捷栏设置
	SETTING_TYPE_K4 ,		//4号快捷栏设置
	SETTING_TYPE_K5 ,		//5号快捷栏设置
	SETTING_TYPE_K6 ,		//6号快捷栏设置
	SETTING_TYPE_K7 ,		//7号快捷栏设置
	SETTING_TYPE_K8 ,		//8号快捷栏设置
	SETTING_TYPE_K9 ,		//9号快捷栏设置
	SETTING_TYPE_K10 ,	//右边0号快捷栏设置
	SETTING_TYPE_K11 ,	//右边1号快捷栏设置
	SETTING_TYPE_K12 ,	//右边2号快捷栏设置
	SETTING_TYPE_K13 ,	//右边3号快捷栏设置
	SETTING_TYPE_K14 ,	//右边4号快捷栏设置
	SETTING_TYPE_K15 ,	//右边5号快捷栏设置
	SETTING_TYPE_K16 ,	//右边6号快捷栏设置
	SETTING_TYPE_K17 ,	//右边7号快捷栏设置
	SETTING_TYPE_K18 ,	//右边8号快捷栏设置
	SETTING_TYPE_K19 ,	//右边9号快捷栏设置
	SETTING_TYPE_K20 ,	//右边0号快捷栏设置
	SETTING_TYPE_K21 ,	//右边1号快捷栏设置
	SETTING_TYPE_K22 ,	//右边2号快捷栏设置
	SETTING_TYPE_K23 ,	//右边3号快捷栏设置
	SETTING_TYPE_K24 ,	//右边4号快捷栏设置
	SETTING_TYPE_K25 ,	//右边5号快捷栏设置
	SETTING_TYPE_K26 ,	//右边6号快捷栏设置
	SETTING_TYPE_K27 ,	//右边7号快捷栏设置
	SETTING_TYPE_K28 ,	//右边8号快捷栏设置
	SETTING_TYPE_K29 ,	//右边9号快捷栏设置

	SETTING_TYPE_CHAT_TAB1_PART1,	//聊天自定义tab1设置第一部分
	SETTING_TYPE_CHAT_TAB1_PART2,	//聊天自定义tab1设置第二部分
	SETTING_TYPE_CHAT_TAB2_PART1,	//聊天自定义tab2设置第一部分
	SETTING_TYPE_CHAT_TAB2_PART2,	//聊天自定义tab2设置第二部分
	SETTING_TYPE_CHAT_TAB3_PART1,	//聊天自定义tab3设置第一部分
	SETTING_TYPE_CHAT_TAB3_PART2,	//聊天自定义tab3设置第二部分
	SETTING_TYPE_CHAT_TAB4_PART1,	//聊天自定义tab4设置第一部分
	SETTING_TYPE_CHAT_TAB4_PART2,	//聊天自定义tab4设置第二部分

	SETTING_TYPE_ATTRI_AUTO_POINT,	//保存自动属性分配点数,把INT分成了四个BYTE,刚好保存
	SETTING_TYPE_MAGICINT,			//MagicInt

	SETTING_TYPE_NUMBER ,//用户设置数据的类型数量
};

// 性别
enum ENUM_SEX
{
	SEX_INVALID	= -1,
	SEX_FEMALE,			// 雌
	SEX_MALE,			// 雄

	SEX_NUMBERS
};

// 玩家死亡类型
enum ENUM_HUMAN_DIE_TYPE
{
	HUMAN_DIE_TYPE_INVALID = -1,
	HUMAN_DIE_TYPE_INTERCHANGE,		// 切磋
	HUMAN_DIE_TYPE_MONSTER_KILL,	// 被怪杀死
	HUMAN_DIE_TYPE_PLAYER_KILL,		// 被玩家杀死

	HUMAN_DIE_TYPE_NUMBERS
};

enum TASK_EVENT
{
	TASK_EVENT_KILLOBJ		= 0 ,	//杀死怪物
	TASK_EVENT_ENTERAREA	= 1 ,	//进入事件区
	TASK_EVENT_ITEMCHANGED	= 2 ,	//物品变化
	TASK_EVENT_PETCHANGED	= 3 ,	//宠物变化
};

enum	CMD_MODE
{
	CMD_MODE_CLEARALL	=	1,		//清除模式
	CMD_MODE_LOADDUMP	=	2,		//载入dump模式
};


enum	WORLD_TIME
{
	WT_IND_1	=	0,	//子时
	WT_IND_2,			//丑时
	WT_IND_3,			//寅时
	WT_IND_4,			//卯时
	WT_IND_5,			//辰时
	WT_IND_6,			//巳时
	WT_IND_7,			//午时
	WT_IND_8,			//未时
	WT_IND_9,			//申时
	WT_IND_10,			//酉时
	WT_IND_11,			//戌时
	WT_IND_12			//亥时
};

enum	NPC_SHOP_TYPE
{
	SHOP_All		= 1,	//
	SHOP_DEFENCE	= 2,	//防具
	SHOP_ADORN		= 3,	//饰物
	SHOP_WEAPON		= 4,	//武器

	SHOP_FOOD		= 5,	//食物
	SHOP_MATERIAL	= 6,	//材料
	SHOP_COMITEM	= 7,	//药品
};

typedef enum _SYSTEM_USE_SKILL_ID
{
	MELEE_ATTACK = 0,
	CAPTURE_PET = 1,
	CALL_UP_PET = 2,
	SYSTEM_RESERVED_3	= 3,
	SYSTEM_RESERVED_4	= 4,
	SYSTEM_RESERVED_5	= 5,
	SYSTEM_RESERVED_6	= 6,
	SYSTEM_RESERVED_7	= 7,
	SHADOW_GUARD 		= 8,
	XIAOYAO_TRAPS		= 9,
} SystemUseSkillID_T;

typedef enum _SYSTEM_USE_IMPACT_ID
{
	IMP_DAMAGES_OF_ATTACKS = 0,
	IMP_NOTYPE_DAMAGE,
} SystemUseImpactID_T;

namespace AcceptableDistanceError_NS //战斗距离计算，可接受的距离误差
{
	enum
	{
		ADE_FOR_HUMAN = 2,
		ADE_FOR_NPC = 1,
	};
};

enum CURRENCY_UNIT	// 货币单位
{
	CU_MONEY,		// 钱
	CU_GOODBAD,		// 善恶值
	CU_MORALPOINT,	// 师德点
};


enum DEFAULT_CHAR_DATA
{
	CHAR_ENTERSCENCE		=0, //起始场景ID
	CHAR_BORNX             ,   //出生X坐标
	CHAR_BORNY             ,   //出生Y坐标
	CHAR_CAMP			  ,   //初始阵营

	CHAR_INILEVEL          ,   //初始等级	
	CHAR_INIEXP            ,   //初始经验
	CHAR_INIHP             ,   //初始生命
	CHAR_INIRAGE            ,   //初始怒气

	CHAR_INIPNEUMA         ,   //初始元气
	CHAR_MAX_VIGOR			,  //初始活力上限
	//CHAR_INISTR            ,   //初始力量
	//CHAR_INICON            ,   //初始体质

	//CHAR_INIINT            ,   //初始智力
	//CHAR_INIDEX            ,   //初始敏捷
	CHAR_INISKILL1         ,   //初始战斗技能1	
	CHAR_INISKILL2         ,   //初始战斗技能2	

	CHAR_INISKILL3         ,   //初始战斗技能3	
	CHAR_INISKILL4         ,   //初始战斗技能4	
	CHAR_INISKILL5         ,   //初始战斗技能5	
	CHAR_INIABILITY1		,   //初始生活技能1	

	CHAR_INIABILITY2		,   //初始生活技能2	
	CHAR_INIABILITY3		,   //初始生活技能3	
	CHAR_INIABILITY4		,   //初始生活技能4	
	CHAR_INIABILITY5		,   //初始生活技能5	

	CHAR_INICOMMON_SKILL1	,   //初始生活技能1
	CHAR_INICOMMON_SKILL2	,   //初始生活技能2
	CHAR_INICOMMON_SKILL3	,   //初始生活技能3
	CHAR_INICOMMON_SKILL4	,   //初始生活技能4
	CHAR_INICOMMON_SKILL5	,   //初始生活技能5

	CHAR_INIMONEY          ,   //初始金钱	

	CHAR_ININUM			   ,
};

#define MAX_MONSTER_PET_TAKE	3		//玩家最多携带召唤兽的数量
#define MONSTER_PET_MAX_SKILL	6		//召唤兽最多可用技能数量
#define MONSTER_PET_MAX_IMPACT	8		//召唤兽在跨场景时可记录的已经中的buff的数量

#define MAX_MONSTER_HORSE_TAKE	2	//玩家最多可以召唤的马的数量

//同乡频道配置表
#define IPREGION_NAME_LENGTH		12
#define IPREGION_UNKNOWN			-1		//非法频道编号
#define IPREGION_SPARK				1		//火星频道编号

// add by gh for souxia 2010/05/11
enum SOUXIA_TYPE
{
	ITEM_SOUXIALU = 0, // 捜侠录类型
	ITEM_MEMORYCLUB	,  // 搜侠记忆棒
	ITEM_DISMANTLE	,  // 拆解道具
	ITEM_REFINING	,  // 炼化道具
	ITEM_SEW		,  // 缝合道具
};


enum SOUXIA_PAGE_TYPE
{
	ITEM_SOUXIASKILL = 1, // 搜侠技能
	ITEM_PRODUCT		, // 神器配方   
	ITEM_PET_ZHAOHUAN	, // 神兽召唤
	ITEM_ZUOJI_ZHAOHUAN	, // 坐骑召唤
};
#endif
