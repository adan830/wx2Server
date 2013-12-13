#ifndef _RESULT_DEFINE_H_
#define _RESULT_DEFINE_H_

enum USEITEM_RESULT
{
	USEITEM_SUCCESS			=	0,
	USEITEM_CANNT_USE		=	1,
	USEITEM_LEVEL_FAIL		=	2,
	USEITEM_TYPE_FAIL		=	3,
	USEITEM_TARGET_TYPE_FAIL=	4,
	USEITEM_SKILL_FAIL		=	5,
	USEITEM_IDENT_TYPE_FAIL	=	6, //卷轴类型错误
	USEITEM_IDENT_TARGET_TYPE_FAIL =7,//目标类型错误
	USEITEM_IDENT_LEVEL_FAIL	= 8,//卷轴等级不够

	USEITEM_INVALID
};

enum	USEGEM_RESULT
{

	USEGEM_SUCCESS,
	USEGEM_EQUIP_FAIL,
	USEGEM_CANNT_USE,
	USEGEM_LEVEL_FAIL,
	USEGEM_EQUIP_GEM_FULL,
	USEGEM_CANNT_COMBINE_GEM,
	USEGEM_GEMREQ_FAIL,
	USEGEM_CANNT_FINDGEM,
	USEGEM_GEM_FAIL,
	USEGEM_FAIL
};

enum	REMOVEGEM_RESULT
{
	REMOVEGEM_SUCCESS,
	REMOVEGEM_NO_ITEM,
	REMOVEGEM_ERROR_GEMINDEX,
	REMOVEGEM_NO_GEM,
	REMOVEGEM_INVALID_EQUIP,
	REMOVEGEM_TOO_LARGE_GEMINDEX,
	REMOVEGEM_UNKNOW_ERROR,
	REMOVEGEM_BAG_FULL

};

enum	ADDHOLE_RESULT
{
	ADDHOLE_SUCCESS	=	1,
	ADDHOLE_EQUIP_FAIL,		//找不到装备
	ADDHOLE_ITEM_FAIL,
	ADDHOLE_FULL_FAIL,
	ADDHOLE_MONEY_FAIL,
	ADDHOLE_BAG_INVALID,
	ADDHOLE_FAIL,
};

enum	EQUIPLEVEUP_RESULT
{
	EQUIPLEVEUP_SUCCESS =	1,
	EQUIPLEVEUP_EQUIP_FAIL,
	EQUIPLEVEUP_COMMONEQUIP,
	EQUIPLEVEUP_FAIL_SUCCESS,
	EQUIPLEVEUP_ITEMTYPE_FAIL,
	EQUIPLEVEUP_ITEMNUM_FAIL,
	EQUIPLEVEUP_FULL_FAIL,
	EQUIPLEVEUP_MONEY_FAIL,
	EQUIPLEVEUP_BAG_INVALID,
	EQUIPLEVEUP_FAIL,
};

enum	EQUIPADSORMAGIC_RESULT
{
	EQUIPADSORMAGIC_SUCCESS =	1,
	EQUIPADSORMAGIC_EQUIP_FAIL,				//附魔失败

	EQUIPADSORMAGIC_EQUIPBYTE_ERROR,		//装备类型错误
	EQUIPADSORMAGIC_EQUIP_HAVE_MAGIC,		//装备已经附魔
	EQUIPADSORMAGIC_BEAMLEVEL_BIG_HUMANLEVEL,//珠子等级大于玩家等级
	EQUIPADSORMAGIC_BEAMLEVEL_BIG_EQUIPLEVEL,//珠子等级大于装备等级
	EQUIPADSORMAGIC_MONEY_NOT_ENOUGH,		//附魔金钱不够
};

enum	EQUIPCANCELMAGIC_RESULT
{
	EQUIPCANCELMAGIC_SUCCESS =	1,
	EQUIPCANCELMAGIC_EQUIP_FAIL,			//退魔失败
	EQUIPCANCELMAGIC_EQUIPTYPE_ERROR,		//装备类型错误
	EQUIPCANCELMAGIC_EQUIP_NO_MAGIC,		//装备没有附魔
	EQUIPCANCELMAGIC_MONEY_NOT_ENOUGH,		//退魔金钱不够
	EQUIPCANCELMAGIC_NO_GEM,				//没有放入退魔石
};


enum	EQUIPBIND_RESULT
{
	EQUIPBIND_SUCCESS	=	1,
	EQUIPBIND_EQUIP_FAIL,
	EQUIPBIND_BALIVE,
	EQUIPBIND_ITEM_FAIL,
	EQUIPBIND_FULL_FAIL,
	EQUIPBIND_MONEY_FAIL,
	EQUIPBIND_BAG_INVALID,
	EQUIPBIND_FAIL,
};


enum	EQUIPEXCHANGEPAITTYPE_RESULT
{
	EQUIPEXCHANGEPAITTYPE_SUCCESS	=	1,
	EQUIPEXCHANGEPAITTYPE_EQUIP_FAIL,
	EQUIPEXCHANGEPAITTYPE_EQUIPPAI_FAIL,
	EQUIPEXCHANGEPAITTYPE_EQUIPBIND_FAIL,
	EQUIPEXCHANGEPAITTYPE_ITEM_FAIL,
	EQUIPEXCHANGEPAITTYPE_BAG_INVALID,
	EQUIPEXCHANGEPAITTYPE_FAIL,
};

enum	EQUIPCHANGEPAITTYPE_RESULT
{
	EQUIPCHANGEPAITTYPE_SUCCESS	=	1,
	EQUIPCHANGEPAITTYPE_EQUIP_FAIL,
	EQUIPCHANGEPAITTYPE_ITEM_FAIL,
	EQUIPCHANGEPAITTYPE_BAG_INVALID,
	EQUIPCHANGEPAITTYPE_FAIL,
};

enum	EQUIPSUIT_RESULT
{
	EQUIPSUIT_SUCCESS	=	1,
	EQUIPSUIT_JOB_FAIL,
	EQUIPSUIT_LEVEL,
	EQUIPSUIT_EQUIP_FAIL,
};

enum	EQUIPSPECIALREPAIR_RESULT
{
	EQUIPSPECIALREPAIR_SUCCESS	=	1,
	EQUIPSPECIALREPAIR_NOREAPIR,
	EQUIPSPECIALREPAIR_ITEM,
	EQUIPSPECIALREPAIR_BAG_INVALID,
	EQUIPSPECIALREPAIR_FAIL,
};

enum	EQUIPREMOULD_RESULT
{
	EQUIPREMOULD_SUCCESS =	1,
	EQUIPREMOULD_EQUIP_FAIL,
	EQUIPREMOULD_COMMONEQUIP,
	EQUIPREMOULD_TYPE_FAIL,
	EQUIPREMOULD_MAX_FAIL,
	EQUIPREMOULD_MATERIAL_FAIL,
	EQUIPREMOULD_MATERIAL_LEVEL,
	EQUIPREMOULD_MATERIAL_COUNT,
	EQUIPREMOULD_BAG_INVALID,
	EQUIPREMOULD_MONEY_FAIL,
	EQUIPREMOULD_FAIL,
};

enum	EQUIPDECOMPOUND_RESULT
{
	EQUIPDECOMPOUND_SUCCESS =	1,
	EQUIPDECOMPOUND_EQUIP_FAIL,
	EQUIPDECOMPOUND_COMMONEQUIP,
	EQUIPDECOMPOUND_PRODUCT_FAIL,
	EQUIPDECOMPOUND_BAG_FAIL,
	EQUIPDECOMPOUND_TYPE_FAIL,
	EQUIPDECOMPOUND_BAG_INVALID,
	EQUIPDECOMPOUND_FAIL,
};
//add by gh 2010/06/29
enum EQUIPREFINING_RESULT
{
	EQUIPREFINING_NOT_SUCH_ITEM,	//没有该物品
	EQUIPREFINING_LEVEL_ERROR,		//等级错误
	EQUIPREFINING_STAR_ISNOT_ENOUGH,//星级不够
	EQUIPREFINING_MUSTBE_EMBED,		//没有镶嵌
	EQUIPREFINING_NOT_HAVE_ATTR,	//没有属性
	EQUIPREFINING_FAIL,				//炼化失败
	EQUIPREFINING_ERASE_ITEM_FAIL,	//删除物品失败
	EQUIPREFINING_SUCCESS,			//炼化成功
};
// end of add
enum	ITEMCREATE_RESULT
{
	ITEMCREATE_SUCCESS	=	1,
	ITEMCREATE_ITEM_FAIL,
	ITEMCREATE_MATERIAL_FAIL,
	ITEMCREATE_MATERIAL_LEVEL,
	ITEMCREATE_MATERIAL_COUNT,
	ITEMCREATE_BAG_FULL,
	ITEMCREATE_MONEY_FAIL,
	ITEMCREATE_FAIL,
};

enum	SWITCHITEM_RESULT
{
	SWITCHITEM_SUCCESS	=	0,
	SWITCHITEM_EXTRBAG_EXCHANGE_FAIL,
	SWITCHITEM_SOURCEEXTRBAG_NOALIVE,
	SWITCHITEM_SOURCEEXTRBAG_ITEM_FAIL,
	SWITCHITEM_DESTEXTRBAG_TIME_FAIL,
	SWITCHITEM_DESTCEEXTRBAG_NOALIVE,
	SWITCHITEM_FAIL,
};

enum    SUBTRAIN_RESULT
{
	SUBTRAIN_MODEERROR_OPEN_BEGINFAIL	=1,		//开始状态不可以继续开始
	SUBTRAIN_MODEERROR_CLOSE_TIMEFAIL,
	SUBTRAIN_MODEERROR_CLOSE_STOPFAI,		//停止状态不可以继续停止
	SUBTRAIN_MODEERROR_OPEN_GETEXPFAIL,		//开始状态不可以提取经验
	SUBTRAIN_MODEERROR_OPEN_CLEANFAIL,		//开始状态不可以清除带练
	SUBTRAIN_MODEERROR_MONEY_GETEXPFAIL,	//提取经验钱不够
	SUBTRAIN_MODEERROR_OPEN_ASKMODEFAIL,	//开始状态不能改变模式
};

enum	UseEquipResultCode
{
	USEEQUIP_SUCCESS	=	1,
	USEEQUIP_LEVEL_FAIL,
	USEEQUIP_TYPE_FAIL,
	USEEQUIP_IDENT_FAIL,
	USEEQUIP_JOB_FAIL,
	USEEQUIP_BAGINDEX_FAIL,
	USEEQUIP_CURDUR_ZERO,
};

enum	UseExtraBagResultCode
{
	USEEXTRABAG_SUCCESS	=	1,
	USEEXTRABAG_TYPE_FAIL,
};

enum	UnExtraBagResultCode
{
	UNEXTRABAG_SUCCESS	=	1,
	UNEXTRABAG_BAG_FULL,
	UNEXTRABAG_HAS_ITEM,
};

enum	LEVELUP_RESULT
{
	LEVELUP_SUCCESS,
	LEVELUP_NO_EXP,
};


enum	ATTR_RESUlT
{
	ATTR_RESUlT_SUCCESS,
	ATTR_RESULT_NOT_ENOUGH_REMAIN_POINT,
	ATTR_RESULT_NO_SUCH_ATTR,
	ATTR_RESUlT_NO_POINT,
};


enum	PickResultCode
{
	PICK_SUCCESS,
	PICK_BAG_FULL,
	PICK_INVALID_OWNER,			
	PICK_INVALID_ITEM,			//拾取物品不存在
	PICK_TOO_FAR,				//角色距离太远
	PICK_DEAD,					//角色已经死亡
	PICK_CLOSED_BOX
};

enum RATTR_RESULT
{
	RATTR_SUCCESS,
	RATTR_NO_POINT,
	RATTR_NO_LEVEL
};

enum	UnEquipResultCode
{
	UNEQUIP_SUCCESS	=	1,
	UNEQUIP_BAG_FULL,
	UNEQUIP_BAGPOS_INVALID,
	UNEQUIP_BAG_INVALIDTIME,
	UNEQUIP_HAS_ITEM,

};

enum	DISCARDITEM_RESULT
{
	DISCARDITEM_SUCCESS,
	DISCARDITEM_FAIL
};


enum LOGIN_CONNECT_RESULT
{
	LOGINCR_SUCCESS,			//成功
	LOGINCR_FULL,				//Login满
	LOGINCR_STOP_SERVICE,		//暂时停止服务
};

enum LOGIN_RESULT
{
	LOGINR_SUCCESS,				//成功
	LOGINR_AUTH_FAIL,			//验证失败
	LOGINR_VERSION_FAIL,		//版本错误
	LOGINR_NOT_EN_POINT,		//点数不够,请冲值
	LOGINR_STOP_SERVICE,		//暂时停止服务
	LOGINR_OTHER_ONLINE,		//在其他游戏世界在线
	LOGINR_OTHER_ERROR,			//未知错误
	LOGINR_FORBIT,				//账号停权
	LOGINR_USER_ONLINE,			//有对应角色在线,直接踢出

	LOGINR_NEED_REG,			//passport 中存在,需要注册
	LOGINR_REG_SUCCESS,			//passport 注册成功
	LOGINR_REG_ALREADYEXIST,	//passport 已经注册过了
	LOGINR_REG_FAIL,			//passport 注册失败
	LOGINR_PASSPORTNEEDACT,     //passport 通过,需要去网站激活(据说是临时功能) Steven.Han 2007.01.16
	LOGINR_NEED_WEB_REG,		//本地帐号库不存在，需要到网站注册（临时功能）YangJun 2007.04.02
	LOGINR_CHECK_MIBAO_STATUS,	//提醒用户检查密保的使用状态
	LOGINR_MIBAO_ERROR,			//密保卡密码不对
	LOGINR_WRONG_IP_ADDR,		//ip地址错误
	LOGINR_LOCK_BY_MOBILE,		//已被手机锁定
	LOGINR_FATIGUE_ONLYONE,		//防沉迷用户只许同时登录一个帐号(1身份证->n帐号)
	LOGINR_MAC_ERROR,			//MAC地址的MD5值不对
	LOGINR_NO_NEW_LICENSE,		//用户没有接受新的许可协议
	LOGINR_NEW_LICENSE_FAIL,	//用户许可协议验证失败
	LOGINR_MUST_WAIT,			//必须等待20秒再登录
	LOGINR_NOTIFY_SAFESIGN,		//提醒玩家去网站填写实名和绑定密保卡
	LOGINR_ONLY_SUCCESS,		//此状态不重新设置LoginPlayer的安全标识
	LOGINR_SAFESIGN_SUCCESS,	//安全状态确认成功
};



enum ASKCHARLIST_RESULT
{
	ASKCHARLIST_SUCCESS,		//成功
	ASKCHARLIST_OP_FAILS,		//操作失败
	ASKCHARLIST_SERVER_BUSY,	//服务器忙，重试
	ASKCHARLIST_OP_TIMES,		//操作过于频繁
};

enum ASKCREATECHAR_RESULT
{
	ASKCREATECHAR_SUCCESS,			//成功
	ASKCREATECHAR_SERVER_BUSY,		//服务器忙，重试
	ASKCREATECHAR_OP_TIMES,			//操作过于频繁
	ASKCREATECHAR_FULL,				//角色已经满了
	ASKCREATECHAR_SAME_NAME,		//角色重名
	ASKCREATECHAR_OP_ERROR,			//错误操作流程
	ASKCREATECHAR_INTERNAL_ERROR,	//内部错误

	ASKCREATECHAR_NEXTDB_CREATE,	//请求下一个DBThread继续处理人物创建
	ASKCREATECHAR_NAME_ERROR,		//名称非法
	ASKCREATECHAR_CREATECODE_FALSE,	//验证码未验证
};

enum ASKDELETECHAR_RESULT
{
	ASKDELETECHAR_SUCCESS,		  //成功
	ASKDELETECHAR_SERVER_BUSY,	  //服务器忙，重试
	ASKDELETECHAR_OP_TIMES,		  //操作过于频繁
	ASKDELETECHARR_EMPTY,		  //没有角色删除
	ASKDELETECHAR_OP_ERROR,		  //错误操作流程
	ASKDELETECHAR_NOT_OWNER,	  //不是角色的所有者
	ASKDELETECHAR_INTERNAL_ERROR, //内部错误
	ASKDELETECHAR_LEVEL10_ERROR = ASKDELETECHAR_SUCCESS,  //删除>=10级的人物
};


enum ASKCHARLOGIN_RESULT
{
	ASKCHARLOGIN_SUCCESS,		//成功
	ASKCHARLIST_WORLD_FULL,		//世界满了
	ASKCHARLOGIN_SERVER_BUSY,	//服务器忙，重试
	ASKCHARLOGIN_LOADDB_ERROR,	//角色载入出错
	ASKCHARLOGIN_OP_TIMES,		//操作过于频繁
	ASKCHARLOGIN_NOT_OWNER,		//不是角色的所有者
	ASKCHARLOGIN_SERVER_STOP,	//服务器维护
	ASKCHARLOGIN_INVALID_SCENE,	//非法的SceneID
	ASKCHARLOGIN_CHARLIVING,	//角色在线稍后重进
	ASKCHARLOGIN_NO_POINT,		//无足够点数
	ASKCHARLOGIN_END_TIME,		//月卡到期
	ASKCHARLOGIN_NOT_LOGON,		//非法流程
	ASKCHARLOGIN_CRC_ERROR,		//CRC检查失败
	ASKCHARLOGIN_MAGICINT_ERROR,//MagicInt检查失败
	ASKCHARLOGIN_VALIDATE_ERROR,//登录图形验证失败
};


enum CLIENT_TURN_STATUS
{
	CTS_TURN,					//排队状态
	CTS_NORMAL,					//排队完毕状态
	CTS_OVER,					//超过排队上限
};

//add for souxia 2010/06/01
enum	SOUXIA_RESULT
{
	SOUXIA_SKILL_UPGRADE_SUCCESS	,//成功
	SOUXIA_SKILL_UPGRADE_FAIL		,//失败
	HUMAN_SOUXIA_ADD_FAIL			,//人身上增加捜侠录失败
	HUMAN_LEVEL_NOT_ENOUGH			,//人物等级不够
	SOUXIA_SKILL_STUDY_TYPE_ERROR	,//学习类型错误
	SOUXIA_SKILL_FULL				,//技能满了
	SOUXIA_PRODUCT_FULL				,//配方满了
	SOUXIA_PET_ZHAOHUAN_FULL		,//神兽召唤技能满了
	SOUXIA_ZUOJI_ZHAOHUAN_FULL		,//坐骑召唤技能满了

	GET_ITEM_ERROR					,//获取物品错误
	BAG_OUT_OF_SPACE				,//背包满
	ERASE_ITEM_FAIL					,//删除物品失败

	SOUXIA_DISMANTLE_FAIL			,//拆解失败
	SOUXIA_DISMANTLE_SUCCESS		,//拆解成功

	SOUXIA_REFINING_SUCCESS			,//炼化成功
	SOUXIA_SKILL_REFINING_FAIL		,//炼化失败
	SOUXIA_EMPTY					,//捜侠录都为空

	SOUXIA_SKILL_SEW_FAIL			,//缝合失败
	SOUXIA_SEW_SUCCESS				,//缝合成功

	SOUXIA_SKILL_PAGE_FULL			,//技能页满了
	SOUXIA_PRODUCT_PAGE_FULL		,//配方页满了
	SOUXIA_PET_ZHAOHUAN_PAGE_FULL	,//神兽召唤页满了
	SOUXIA_ZUOJI_ZHAOHUAN_PAGE_FULL	,//坐骑召唤页满了
};


//add for ability 2010/07/15
enum	ABILITY_RESULT
{
	ABILITY_UPGRADE_SUCCESS	,//成功
	ABILITY_UPGRADE_NPC_ERROR,//NPC错误
	ABILITY_UPGRADE_NPC_DISTANCE_FAR,//距离NPC太远
	ABILITY_UPGRADE_MONEY_ERROR	,	//金钱不足失败
	ABILITY_UPGRADE_EXP_ERROR	,	//玩家经验不足失败
	ABILITY_UPGRADE_SKILL_EXP_ERROR	,//技能经验不足失败
	ABILITY_UPGRADE_HUMAN_LEVEL_ERROR	,//玩家等级不够
	ABILITY_UPGRADE_LEVEL_ERROR	,//级别大于上限
	ABILITY_UPGRADE_FAIL		,//失败	
	
};

#endif