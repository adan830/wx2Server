

#ifndef __DBSTRUCT_H__
#define __DBSTRUCT_H__

 #include "Type.h"
#include "GameDefine.h"
#include "GameDefine2.h"
#include "GameDefine_Attr.h"
#include "GameStruct_Impact.h"
#include "GameStruct_Skill.h"
#include "GameStruct_Country.h"

#pragma pack(push, 1)

class HumanDB;

//冷却时间
typedef CooldownList_T<MAX_COOLDOWN_LIST_SIZE_FOR_HUMAN> CooldownListForHuman_T;
typedef CooldownListForHuman_T _COOLDOWN_DB_LOAD_FOR_HUMAN;
typedef CooldownList_T<MAX_COOLDOWN_LIST_SIZE_FOR_PET> CooldownListForPet_T;
typedef CooldownListForPet_T _COOLDOWN_DB_LOAD_FOR_PET;

// 玩家对应的类似邮编区号的东东，如下图所示：
//
// FF  FF  FF  FF
// |   |   |   |
//预留 |   |   |
//   省份  |   |
//       城市  |
//           区域
//

struct POSTCODE
{
	INT m_PostCode;
	POSTCODE(){
		m_PostCode = 0;
	}
	INT GetPostCode() const{
		return m_PostCode;
	}
	BYTE GetProvinceCode() const {
		return (BYTE)((m_PostCode & 0x00FF0000) >> 16);
	}
	BYTE GetCityCode() const {
		return (BYTE)((m_PostCode & 0x0000FF00) >> 8);
	}
	BYTE GetSectionCode() const {
		return (BYTE)((m_PostCode & 0x000000FF));
	}
	VOID Assign(BYTE byProvinceCode, BYTE byCityCode, BYTE bySectionCode){
		m_PostCode = (INT)((byProvinceCode << 16) | (byCityCode << 8) | bySectionCode);
	}
	POSTCODE& operator=(const POSTCODE& value){
		this->m_PostCode = value.m_PostCode;
		return *this;
	}
	POSTCODE& operator=(const INT& value){
		this->m_PostCode = value;
		return *this;
	}

};
// HighSection是玩家的GUID,LowSection是当前的系统时间
struct PET_GUID_t
{
	PET_GUID_t()
	{
		m_uHighSection = 0;
		m_uLowSection = 0;
	}

	PET_GUID_t& operator=(const PET_GUID_t& val) 
	{
		m_uHighSection = val.m_uHighSection;
		m_uLowSection = val.m_uLowSection;
		return *this; 
	}

	BOOL operator==(const PET_GUID_t& val) const 
	{
		if (m_uHighSection == val.m_uHighSection &&
			m_uLowSection == val.m_uLowSection)
		{
			return TRUE;
		}
		return FALSE;
	}

	BOOL operator!=(const PET_GUID_t& val) const 
	{
		if (m_uHighSection != val.m_uHighSection ||
			m_uLowSection != val.m_uLowSection)
		{
			return TRUE;
		}
		return FALSE;
	}

	BOOL IsNull(VOID) const 
	{
		if (!m_uHighSection && !m_uLowSection)
		{
			return TRUE;
		}
		return FALSE;
	}

	VOID Init(const GUID_t& GUID, UINT CurTime)
	{
		m_uHighSection = GUID;
		m_uLowSection = CurTime;
	}
	
	VOID Reset(VOID)
	{
		m_uHighSection = 0;
		m_uLowSection = 0;
	}
	
	UINT	GetHighSection(VOID) const { return m_uHighSection; }
	UINT	GetLowSection(VOID) const { return m_uLowSection; }

	UINT	m_uHighSection;
	UINT	m_uLowSection;
};

// 阵营数据
struct _CAMP_DATA
{
	CampID_t	m_nCampID;
	UINT		m_uActiveFlags;
	UINT		m_uRelationFlags;

	_CAMP_DATA( VOID )
	{
		m_nCampID			= -1;
		m_uActiveFlags		= 0;
		m_uRelationFlags	= 0;
	}

	VOID CleanUp( VOID )
	{
		m_nCampID			= -1;
		m_uActiveFlags		= 0;
		m_uRelationFlags	= 0;
	}

	BOOL IsActiveFlag_Dirty( INT nID )const
	{
		if ( nID < 0 || nID >= 32 )
		{
			return FALSE;
		}
		return (m_uActiveFlags & (1<<nID)) != 0;
	}

	VOID SetActiveFlag_Dirty( INT nID, BOOL bDirty )
	{
		if ( nID < 0 || nID >= 32 )
		{
			return ;
		}
		if ( bDirty )
			m_uActiveFlags |= (1<<nID);
		else
			m_uActiveFlags &= ~(1<<nID);
	}

	BOOL IsRelationFlag_Dirty( INT nID )const
	{
		if ( nID < 0 || nID >= 32 )
		{
			return FALSE;
		}
		return (m_uRelationFlags & (1<<nID)) != 0;
	}

	VOID SetRelationFlag_Dirty( INT nID, BOOL bDirty )
	{
		if ( nID < 0 || nID >= 32 )
		{
			return ;
		}
		if ( bDirty )
			m_uRelationFlags |= (1<<nID);
		else
			m_uRelationFlags &= ~(1<<nID);
	}

	BOOL operator == ( const _CAMP_DATA &in )
	{
		if ( m_nCampID != in.m_nCampID
			|| m_uActiveFlags != in.m_uActiveFlags
			|| m_uRelationFlags != in.m_uRelationFlags )
		{
			return FALSE;
		}
		return TRUE;
	}

	BOOL operator != ( const _CAMP_DATA &in )
	{
		if ( m_nCampID != in.m_nCampID
			|| m_uActiveFlags != in.m_uActiveFlags
			|| m_uRelationFlags != in.m_uRelationFlags )
		{
			return TRUE;
		}
		return FALSE;
	}

	_CAMP_DATA &operator = ( const _CAMP_DATA &in )
	{
		if ( &in != this )
		{
			m_nCampID			= in.m_nCampID;
			m_uActiveFlags		= in.m_uActiveFlags;
			m_uRelationFlags	= in.m_uRelationFlags;
		}
		return *this;
	}
};

//角色商店数据

#define MAX_RESERVE 10
//需要保存的角色数据
struct _HUMAN_DB_LOAD
{

	struct _PSHOP_INFO
	{
		_PLAYERSHOP_GUID	m_ShopGuid[MAX_SHOP_NUM_PER_PLAYER];//自己所拥有的玩家商店的的GUID 0=物品店索引 1=宠物店索引
		_PLAYERSHOP_GUID	m_FavoriteList[MAX_FAVORITE_SHOPS];	//收藏夹列表
		
		_PSHOP_INFO()
		{
			CleanUp();

		}

		VOID CleanUp()
		{
			memset(this,0,sizeof(*this));
		}
	};
	//
	//基本信息
	//
	BOOL			m_bFirstEnterScence;			//第一次进场景
	INT				m_PortraitID;					//角色头像
	CHAR			m_Name[MAX_CHARACTER_NAME];		//角色名字
	CHAR			m_Title[MAX_CHARACTER_TITLE];	//角色名字
	GUID_t			m_GUID;							//角色完全唯一号
	BYTE			m_Sex;							//角色性别
	UINT			m_CreateDate;					//角色创建日期
	_TITLE			m_Titles;						//角色的详细称号
	INT				m_Level;						//角色等级
	INT				m_Vigor;						//活力
	INT				m_MaxVigor;						//活力上限
	INT				m_VigorRegeneRate;				//活力恢复速度
	INT				m_Energy;						//精力
	INT				m_MaxEnergy;					//精力上限
	INT				m_EnergyRegeneRate;				//精力恢复速度
	UINT			m_Exp;							//角色经验值
	UINT			m_Money;						//角色货币
	UINT			m_Gold;		    				//元宝
    UINT			m_Ticket;						//代金券
	INT				m_nGoodBadValue;				//善恶值
	CHAR			m_Passwd[MAX_PWD];				//二级密码
	UINT			m_uPwdDelTime;					//设置强制解除密码的时间
	UINT			m_HairColor;					//头发颜色	
	BYTE			m_FaceColor;					//脸形颜色
	BYTE			m_HairModel;					//头发模型
	BYTE			m_FaceModel;					//脸形模型
	INT				m_nMountID;				    	//坐骑ID                                           [7/8/2010 陈军龙]
	INT				m_nMountIndex;			    	//坐骑ITEM索引                                     [7/8/2010 陈军龙]
	INT				m_nMountList[MAX_MOUNT_SIZE];   //拥有的坐骑ID                                     [7/14/2010 陈军龙]

	//
	//基本状态
	//
	SceneID_t		m_StartScene;					//角色所在场景
	SceneID_t		m_BakScene;						//角色所在备份场景
	GuildID_t		m_GuildID ;						//帮派
	INT     		m_FamilyID ;					//家族
	INT     		m_nGuildOfficial ;				//帮会官职
	INT     		m_nGP;	            			//帮会贡献度
    INT             m_nHonor;                       //  荣誉值
	TeamID_t		m_TeamID;						//角色所在的队伍号
	WORLD_POS		m_Position;						//角色位置
	WORLD_POS		m_BakPosition;					//角色备份位置
	UINT			m_OnlineTime;					//总在线时间
	UINT			m_LastLoginTime;				//最后一次登入时间
	UINT			m_LastLogoutTime;				//最后一次登出时间
	UINT			m_LeftDieTime;					//剩余死亡时间
	UINT			m_DBVersion;					//数据库版本
	time_t			m_LeaveGuildTime;		        //退出前一个帮会的时间
	
	//
	//战斗信息
	//
	_CAMP_DATA		m_CampData;					//阵营
	INT				m_nCountry;					//国家
	INT				m_MenPai;					//门派 MENPAI_ATTRIBUTE
	INT				m_NeiShang;					//内伤
	INT				m_HP;						//生命值
	INT				m_MP;						//魔法
	INT 			m_StrikePoint;				//连击点
	INT 			m_Rage;						//怒气
	INT				m_nPneuma;					//当前的元气值
	INT				m_nPKValue;					//杀气
	PET_GUID_t		m_guidCurrentPet;			//当前宠物
	_ATTR_LEVEL1	m_BaseAttrLevel1;			//基础一级战斗属性（不包括技能和装备增加的部分）
	INT				m_Level1Points;				//一级属性剩余点数
	INT				m_RemainSkillPoints;		//剩余技能点
	BOOL			m_bHorseMating;				//马繁殖标记
	INT				m_S_SkillPoints[COMMON_S_NUMBER];	//系技能点
	//
	//玩家商店
	//
	_PLAYERSHOP_GUID	m_ShopGuid[MAX_SHOP_NUM_PER_PLAYER];//自己所拥有的玩家商店的的GUID 0=物品店索引 1=宠物店索引
	_PLAYERSHOP_GUID	m_FavoriteList[MAX_FAVORITE_SHOPS];	//收藏夹列表
	POSTCODE			m_PostCode;				//玩家的邮编号
	//保留数据
	INT					m_Reserve[MAX_RESERVE];

	//
	_HUMAN_DB_LOAD()
	{
		CleanUp( );
	};
	VOID			CleanUp( );

	UINT			GetCrc(BOOL bLog)
	{
		UINT Crc= 0;

		Crc+= ConvertUChar(m_GUID,bLog);
		Crc+= ConvertUChar(m_Level,bLog);
		Crc+= ConvertUChar(m_Exp,bLog);
		Crc+= ConvertUChar(m_Money,bLog);
		Crc+= ConvertUChar(m_BaseAttrLevel1.m_pAttr[CATTR_LEVEL1_STR],bLog);
		//Crc+= ConvertUChar(m_BaseAttrLevel1.m_pAttr[CATTR_LEVEL1_SPR],bLog);
		Crc+= ConvertUChar(m_BaseAttrLevel1.m_pAttr[CATTR_LEVEL1_CON],bLog);
		Crc+= ConvertUChar(m_BaseAttrLevel1.m_pAttr[CATTR_LEVEL1_INT],bLog);
		Crc+= ConvertUChar(m_BaseAttrLevel1.m_pAttr[CATTR_LEVEL1_DEX],bLog);
		Crc+= ConvertUChar(m_Level1Points,bLog);
		//Crc+= ConvertUChar(m_iYuanBao,bLog);
		//Crc+= ConvertUChar(m_nZengDian,bLog);
		//Crc+= ConvertUChar(m_nBuyYuanBao,bLog);

		return Crc;

	}

};

//保存角色所拥有的银行里的物品信息
struct _BANK_DB_LOAD
{
	_ITEM			m_pItem[MAX_BANK_SIZE];
	INT				m_Count;
	BYTE			m_CurEndIndex;//银行当前大小
	INT				m_Money;
    INT             m_Gold;
    INT             m_Ticket;

	_BANK_DB_LOAD( )
	{
		CleanUp( );
	};
	VOID			CleanUp( );
};

//保存角色所拥有的身上的背包信息
struct _BAG_DB_LOAD
{
	friend	class	HumanDB;

	_ITEM				m_pItem[MAX_BAG_SIZE];
	
	//基本包大小
	INT					m_BaseBagSize;
	////任务包大小
	//INT					m_TaskBagSize;
	////材料包大小
	//INT					m_MatBagSize;

	INT					m_Count;

	_BAG_DB_LOAD( )
	{
		CleanUp( );
	};
	VOID				CleanUp();
	
private:
	const _ITEM*		GetBagDB(UINT	iBagIndex) const
	{
		Assert(iBagIndex<MAX_BAG_SIZE);
		return		&m_pItem[iBagIndex];
	}

	VOID				PutBagDB(const _ITEM* pItem,UINT iBagIndex)
	{
		Assert(iBagIndex<MAX_BAG_SIZE);
		Assert(pItem);

		memcpy(&m_pItem[iBagIndex],pItem,sizeof(_ITEM));
	}

	VOID				SwapBagDB(UINT iAIndex,UINT iBIndex)
	{
		Assert(iAIndex<MAX_BAG_SIZE);
		Assert(iBIndex<MAX_BAG_SIZE);
		
		SwapItem(&m_pItem[iAIndex],&m_pItem[iBIndex]);

	}

	BOOL				IncCount(UINT iBagIndex)
	{
		return	m_pItem[iBagIndex].IncCount();
	}

	BOOL				DecCount(UINT iBagIndex)
	{
		return	m_pItem[iBagIndex].DecCount();
	}

	VOID				SetItemBind(UINT iBagIndex,BOOL	bBind)
	{
		
		m_pItem[iBagIndex].SetItemBind(bBind);
		
	}

	VOID				SetItemDur(UINT BagIndex, INT Dur)
	{
		m_pItem[BagIndex].GetEquipData()->m_CurDurPoint = Dur; 
	}

};

//保存角色身上的装备信息
struct _EQUIP_DB_LOAD
{
	_ITEM			m_pItem[HEQUIP_NUMBER];//装备点

	USHORT			m_Flags;	//此数据上的第n位值就表示第n个装备点上是否有装备

	_EQUIP_DB_LOAD( )
	{
		CleanUp( );
	};
	VOID			CleanUp( );
	
	BOOL			IsSet( HUMAN_EQUIP eEquip )	const
	{ 
		return (m_Flags & (1<<(INT)eEquip))?(TRUE):(FALSE);
	}
	
	VOID			Set( HUMAN_EQUIP eEquip, BYTE bMark )
	{
		if ( bMark )
			m_Flags |= (1<<(INT)eEquip);
		else
			m_Flags &= (~(1<<(INT)eEquip));
	}
	
	const _ITEM*	GetEquipDB(HUMAN_EQUIP	EquipPoint)
	{
		return &m_pItem[EquipPoint];
	}

	VOID			SetEquipDur(HUMAN_EQUIP	EquipPoint, INT Dur)
	{
		m_pItem[EquipPoint].GetEquipData()->m_CurDurPoint = Dur; 
	}


	VOID			PutEquipDB(const _ITEM*	pItem,HUMAN_EQUIP	EquipPoint)
	{
		Assert(pItem);
		
		if(m_pItem[EquipPoint].IsNullType())
			memcpy(&m_pItem[EquipPoint],pItem,sizeof(_ITEM));
		else
		{
			Assert(FALSE);
		}

	}


};
// add by gh for souxia 2010/05/12

struct	_SOUXIA_DB_LOAD
{
	SOUXIA_DATA		m_SouXiaData[MAX_SOUXIA_CONTAINER];

	_SOUXIA_DB_LOAD()
	{
		CleanUp();
	};

	void CleanUp()
	{
		for (int i=0; i<MAX_SOUXIA_CONTAINER; ++i)
		{
			m_SouXiaData[i].CleanUp();
		}
	}
};
typedef struct _SOUXIA_DB_LOAD _SOUXIA_LIST;


// end of add 

//保存角色的坐骑信息  [7/8/2010 陈军龙]
struct _MOUNT_DB_LOAD
{
    _ITEM  m_pItem[MAX_MOUNT_SIZE];

	_MOUNT_DB_LOAD( )
	{
		CleanUp( );
	};

	VOID  CleanUp( );
};

struct _ABILITY_DB_LOAD
{
	CHAR							m_aPrescr[MAX_CHAR_PRESCRIPTION_BYTE];
	_OWN_ABILITY					m_aABility[MAX_CHAR_ABILITY_NUM];

	_ABILITY_DB_LOAD()
	{
		CleanUp();
	}

	_OWN_ABILITY					&Get_Ability(AbilityID_t id)
	{
		INT idx;
		idx = (INT)id;
		Assert(idx>-1 && idx<MAX_CHAR_ABILITY_NUM);
		return m_aABility[idx];
	}

	_OWN_ABILITY					Get_Ability(AbilityID_t id) const
	{
		INT idx;
		idx = (INT)id;
		Assert(idx>-1 && idx<MAX_CHAR_ABILITY_NUM);
		return m_aABility[idx];
	}

	VOID	CleanUp();
};
typedef struct _ABILITY_DB_LOAD _ABILITY_LIST;

struct _SKILL_DB_LOAD
{
	BYTE			m_Count;
	_OWN_SKILL		m_aSkill[MAX_CHAR_SKILL_NUM];

	_SKILL_DB_LOAD( )
	{
		CleanUp( );
	}
	VOID			CleanUp( );
};
typedef struct _SKILL_DB_LOAD _SKILL_LIST;

//召唤兽跨服专用，不要写数据库
struct _Monster_Pet_DB
{
	_Monster_Pet_DB_Struct m_aMonsterPet[MAX_MONSTER_PET_TAKE];
	_Monster_Pet_DB()
	{
		CleanUp();
	}
	VOID CleanUp()
	{
		memset( this, -1, sizeof(_Monster_Pet_DB) );
	}
};
typedef struct _Monster_Pet_DB _MONSTER_PET_DB;

struct _XINFA_DB_LOAD
{
	BYTE			m_Count;
	_OWN_XINFA		m_aXinFa[MAX_CHAR_XINFA_NUM];

	_XINFA_DB_LOAD( )
	{
		CleanUp( );
	}
	VOID			CleanUp( );
};
typedef struct _XINFA_DB_LOAD _XINFA_LIST;

typedef struct _IMPACT_DB_LOAD
{
	BYTE			m_Count;
	_OWN_IMPACT		m_aImpacts[MAX_IMPACT_NUM];

	_IMPACT_DB_LOAD( )
	{
		CleanUp( );
	};
	VOID			CleanUp( );
} _IMPACT_LIST;

// 宠物DB
#define PET_MAX_SKILL_COUNT 12
//(PET_SKILL_INDEX_NUMBERS)

struct _PET_SKILL
{
	SkillID_t		m_nSkillID;
	BOOL			m_bCanUse;

	_PET_SKILL( VOID )
	{
		m_nSkillID	= INVALID_ID;
		m_bCanUse	= FALSE;
	}

	VOID CleanUp( VOID );
};

struct _PET_DB_LOAD
{
	enum PET_TYPE
	{
		PET_TYPE_INVALID	= -1,
		PET_TYPE_BABY		= 0,
		PET_TYPE_VARIANCE,
		PET_TYPE_WILENESS,
	};

	enum PET_AI_TYPE
	{
		PET_AI_INVALID = -1,
		PET_AI_COWARDICE = 0,	// 胆小
		PET_AI_WARINESS,		// 谨慎	
		PET_AI_LOYALISM,		// 忠诚
		PET_AI_CANNINESS,		// 精明
		PET_AI_VALOUR,			// 勇猛
	};

	PET_GUID_t		m_GUID;								// 唯一编号
	PET_GUID_t		m_SpouseGUID;						// 配偶唯一编号
	INT				m_iSex;								// 性别
	INT				m_nDataID;							// 宠物模型
	CHAR			m_szName[MAX_CHARACTER_NAME];		// 名字
	CHAR			m_szNick[MAX_NICK_NAME];			// 昵称
	INT				m_nLevel;							// 等级
	INT				m_nTakeLevel;						// 携带等级(多少等级的玩家可以携带此宠物)
	INT				m_nAttackType;						// 进攻类型（物/法）
	INT				m_AIType;							// AI类型
	_CAMP_DATA		m_CampData;							// 阵营

	BYTE			m_byGeneration;						// 几代宠
	BYTE			m_byHappiness;						// 快乐度

	INT				m_iSavvy;							// 悟性
	INT				m_nGenGu;							// 根骨
	FLOAT			m_fGrowRate;						// 成长率

	INT				m_iStrengthPerception;				// 力量资质
	INT				m_iSmartnessPerception;				// 敏捷资质
	INT 			m_iMindPerception;					// 智力资质
	INT 			m_iConstitutionPerception;			// 体质资质

	INT				m_nRemainPoint;						// 一级属性剩余点数
	INT				m_nExp;								// 经验值
	BOOL			m_bCheckup;							// 是否鉴定
	INT				m_iMatingLevel;						// 上一次交配时的等级,0代表没有交配过		

	_ATTR_LEVEL1	m_BaseAttrLevel1;					// 基础一级战斗属性（不包括技能和装备增加的部分）

	_PET_SKILL		m_SkillList[PET_MAX_SKILL_COUNT];	// 宠物技能列表,前6个是领悟技能槽，后6个是学习槽

	_COOLDOWN_DB_LOAD_FOR_PET m_CooldownList;			//宠物的冷却列表
	BOOL			m_bMating;							//是否处于交配状态
	UINT			m_uMatingStartTime;					//交配开始时间,5小时后可以领取,48小时不领取则删除
	BOOL			m_bMatingMsgSend;					//是否已繁殖完成，同时标记是否发送繁殖成功邮件
	
	_PET_DB_LOAD()
	{
		 CleanUp();
	}

	VOID CleanUp( VOID );
};

typedef _PET_DB_LOAD	_PET_DB;


#define HUMAN_PET_MAX_COUNT	(6)

enum 
{
	PET_INDEX_INVALID	= -1,
	PET_INDEX_SELF_BEGIN,	// 自己身上的第一只
	PET_INDEX_SELF_2,		// 自己身上第二只
	PET_INDEX_SELF_3,		// 自己身上第三只
	PET_INDEX_SELF_4,		// 自己身上第四只
	PET_INDEX_SELF_5,		// 自己身上第五只
	PET_INDEX_SELF_6,		// 自己身上第六只

	PET_INDEX_SELF_NUMBERS,

	TARGETPET_INDEX		=100,		//
/*
	PET_INDEX_EXCHANGE_BEGIN  = 100,	// 交易时的第一只
	PET_INDEX_EXCHANGE_2,			// 交易时的第二只
	PET_INDEX_EXCHANGE_3,			// 交易时的第三只
	PET_INDEX_EXCHANGE_4,			// 交易时的第四只
	PET_INDEX_EXCHANGE_5,			// 交易时的第五只

	PET_INDEX_EXCHANGE_NUMBERS,

	PET_INDEX_STALL_BEGIN  = 200,	// 摆摊时的第一只
	PET_INDEX_STALL_2,				// 摆摊时的第二只
	PET_INDEX_STALL_3,				// 摆摊时的第三只
	PET_INDEX_STALL_4,				// 摆摊时的第四只
	PET_INDEX_STALL_5,				// 摆摊时的第五只

	PET_INDEX_STALL_NUMBERS,

	PET_INDEX_PLAYERSHOP_BEGIN  = 300,		// 玩家商店中的
	PET_INDEX_PLAYERSHOP_2,					// 玩家商店的第二只
	PET_INDEX_PLAYERSHOP_3,					// 玩家商店的第三只
	PET_INDEX_PLAYERSHOP_4,					// 玩家商店的第四只
	PET_INDEX_PLAYERSHOP_5,					// 玩家商店的第五只

	PET_INDEX_PLAYERSHOP_NUMBERS,
*/
};

struct _PET_DB_LIST_LOAD
{
	// GUID为无效时表明该位为空
	_PET_DB_LOAD	m_aPetDB[HUMAN_PET_MAX_COUNT];

	VOID CleanUp( VOID );
};
typedef _PET_DB_LIST_LOAD	_PET_DB_LIST;

#define MAX_MISSION_PARAM_NUM (8)
struct _OWN_MISSION
{
	MissionID_t		m_idMission;
	ScriptID_t		m_idScript;
	// 0x0000|PetChanged事件|ItemChanged事件|EnterZone事件|KillObject事件|
	BYTE			m_yFlags;			
	
	union
	{
		UINT	m_aParam[MAX_MISSION_PARAM_NUM];
		FLOAT	m_afParam[MAX_MISSION_PARAM_NUM];
		INT		m_anParam[MAX_MISSION_PARAM_NUM];
		BOOL	m_abParam[MAX_MISSION_PARAM_NUM];
		VOID	*m_apParam[MAX_MISSION_PARAM_NUM];
	};

	VOID Cleanup( VOID )
	{
		m_idScript	= INVALID_ID;
		m_idMission = INVALID_ID;
		m_yFlags	= 0;
		memset( m_aParam, 0, sizeof ( m_aParam ) );
	}

	BOOL IsActiveMission( )const{
		if( m_idMission != INVALID_ID &&
			m_idScript != INVALID_ID )
			return TRUE ;
		else
			return FALSE ;
	};

	//kill obj event
	VOID SetFlags_KillObject( BOOL bSet ){
		( bSet )?(m_yFlags |= 0x00000001):(m_yFlags &= ~0x00000001);
	}
	BOOL IsFlags_KillObject( VOID )const{
		return (m_yFlags & 0x00000001) != 0;
	}
	//enter area event
	VOID SetFlags_EnterArea( BOOL bSet ){
		( bSet )?(m_yFlags |= (0x00000001<<1)):(m_yFlags &= ~(0x00000001<<1));
	}
	BOOL IsFlags_EnterArea( VOID )const{
		return (m_yFlags & (0x00000001<<1)) != 0;
	}
	//item changed event
	VOID SetFlags_ItemChanged( BOOL bSet ){
		( bSet )?(m_yFlags |= (0x00000001<<2)):(m_yFlags &= ~(0x00000001<<2));
	}
	BOOL IsFlags_ItemChanged( VOID )const{
		return (m_yFlags & (0x00000001<<2)) != 0;
	}
	//pet changed event
	VOID SetFlags_PetChanged( BOOL bSet ){
		( bSet )?(m_yFlags |= (0x00000001<<3)):(m_yFlags &= ~(0x00000001<<3));
	}
	BOOL IsFlags_PetChanged( VOID )const{
		return (m_yFlags & (0x00000001<<3)) != 0;
	}
};

struct _MISSION_DB_LOAD
{
	BYTE			m_Count;
	_OWN_MISSION	m_aMission[MAX_CHAR_MISSION_NUM];//角色所接的任务信息
	UINT			m_aMissionHaveDoneFlags[MAX_CHAR_MISSION_FLAG_LEN];//角色的任务完成标志
	INT				m_aMissionData[MAX_CHAR_MISSION_DATA_NUM] ;//角色身上的任务自定义数据

	_MISSION_DB_LOAD( )
	{
		CleanUp( );
	}
	VOID			CleanUp( );
};
typedef struct _MISSION_DB_LOAD _MISSION_LIST;

struct _OWN_RELATION
{
	RELATION_MEMBER		m_Member;
	INT					m_FriendPoint;		//友好度
	BYTE				m_Type;				//关系标志, 见enum RELATION_TYPE
	BYTE				m_Group;			//所在的组
	CHAR				m_GroupName[MAX_GROUP_NAME];

	_OWN_RELATION( )
	{
		CleanUp( ) ;
	};
	VOID CleanUp( )
	{
		m_Member.CleanUp( ) ;
		m_FriendPoint = 0 ;
		m_Type = RELATION_TYPE_NONE ;
		m_Group = 0;
		memset(m_GroupName,0,MAX_GROUP_NAME);
	};
	VOID Init(const _OWN_RELATION* pRelation)
	{
		Assert(pRelation);
		memcpy( (void*)&m_Member, &(pRelation->m_Member), sizeof(m_Member) );
		m_FriendPoint = pRelation->m_FriendPoint;
		m_Type = pRelation->m_Type;
		m_Group = pRelation->m_Group;
		memcpy(m_GroupName,pRelation->m_GroupName,sizeof(m_GroupName));
	}
};

struct _RELATION_DB_LOAD
{
	//存盘数据
	struct RelationData
	{
		UCHAR			m_aRelationCount[RELATION_GROUP_NUMBER];		// 各个组的人数
	
		// 自定义组的名字
		CHAR			m_szName[RELATION_GROUP_F5][MAX_GROUP_NAME];	

		CHAR			m_szMood[MOOD_DATA_SIZE];						// 心情
		MarriageInfo		m_MarriageInfo;								// 婚姻信息
		PrenticeInfo		m_PrenticeInfo;								// 徒弟信息
		MasterInfo			m_MasterInfo;								// 师傅信息

		RelationData()
		{
			for( int i=0;i<RELATION_GROUP_NUMBER;i++)
				m_aRelationCount[i] = 0;
		
			memset((void*)m_szName, 0, sizeof(m_szName));		
			memset((void*)m_szMood, 0, sizeof(m_szMood));
			m_MarriageInfo.CleanUp() ;
			m_PrenticeInfo.CleanUp() ;
			m_MasterInfo.CleanUp() ;
		}
	};

	_OWN_RELATION		m_aRelation[MAX_RELATION_SIZE];				// 联系人数据池
	UCHAR				m_aRelationCount[RELATION_GROUP_NUMBER];	// 各个组的人数
	// 自定义组的名字
	CHAR				m_szName[RELATION_GROUP_F5][MAX_GROUP_NAME];
	CHAR				m_szMood[MOOD_DATA_SIZE];					// 心情
	MarriageInfo		m_MarriageInfo;								// 婚姻信息
	PrenticeInfo		m_PrenticeInfo;								// 徒弟信息
	MasterInfo			m_MasterInfo;								// 师傅信息

	_RELATION_DB_LOAD( )
	{
		CleanUp( ) ;
	};
	VOID CleanUp( ) ;


	RelationData	GetRelationData()
	{
		RelationData	ReData;

		memcpy(ReData.m_aRelationCount,m_aRelationCount,sizeof(UCHAR)*RELATION_GROUP_NUMBER);	// 各个组的人数
		
		size_t len = sizeof(CHAR)*(RELATION_GROUP_F5)*MAX_GROUP_NAME;
		memcpy(ReData.m_szName,m_szName,len);	

		memcpy(ReData.m_szMood,m_szMood,sizeof(CHAR)*MOOD_DATA_SIZE);			// 心情
		memcpy(&ReData.m_MarriageInfo,&m_MarriageInfo,sizeof(MarriageInfo));	// 婚姻信息
		memcpy(&ReData.m_PrenticeInfo,&m_PrenticeInfo,sizeof(PrenticeInfo));	// 徒弟信息
		memcpy(&ReData.m_MasterInfo,&m_MasterInfo,sizeof(MasterInfo));			// 师傅信息
		return ReData;
	}
	
	VOID	SetRelationData(RelationData& ReData)
	{
		memcpy(m_aRelationCount,ReData.m_aRelationCount,sizeof(UCHAR)*RELATION_GROUP_NUMBER);	// 各个组的人数
	
		size_t len = sizeof(CHAR)*(RELATION_GROUP_F5)*MAX_GROUP_NAME;
		memcpy(m_szName,ReData.m_szName,len);	

		memcpy(m_szMood,ReData.m_szMood,sizeof(CHAR)*MOOD_DATA_SIZE);			// 心情
		memcpy(&m_MarriageInfo,&ReData.m_MarriageInfo,sizeof(MarriageInfo));	// 婚姻信息
		memcpy(&m_PrenticeInfo,&ReData.m_PrenticeInfo,sizeof(PrenticeInfo));	// 徒弟信息
		memcpy(&m_MasterInfo,&ReData.m_MasterInfo,sizeof(MasterInfo));			// 师傅信息

	}
};

#define MAX_SETTING_DATA 64
//改变_OWN_SETTING结构，请先和杨军讨论，谢谢！！！
struct _OWN_SETTING
{
	BYTE				m_SettingType ;
	INT					m_SettingData ;

	_OWN_SETTING( )
	{
		CleanUp( ) ;
	}
	VOID CleanUp( )
	{
		m_SettingType = 0 ;
		m_SettingData = 0 ;
	}
};

#define MAX_SUIT_SETTING 10
#define MAX_SUIT_NAME_SIZE 12
struct _SUIT_SETTING
{
	CHAR				m_SuitName[MAX_SUIT_NAME_SIZE];
	_ITEM_GUID			m_EquipData[HEQUIP_NUMBER];

	_SUIT_SETTING( )
	{
		CleanUp( ) ;
	}
	VOID CleanUp( )
	{
		memset(m_SuitName, 0, sizeof(CHAR)*MAX_SUIT_NAME_SIZE);
		memset(m_EquipData, 0, sizeof(_ITEM_GUID)*HEQUIP_NUMBER);
	}
};

struct _SUBTRAIN_SETTING 
{
	BOOL			m_bSubTrainOpen;					//带练开启状态
	INT				m_SubTrainMode;						//带练模式
	UINT			m_SubTrainBeginTime;				//带练开始时间
	UINT			m_SubTrainMoney;					//金钱积累
	UINT			m_SubTrainExper;					//经验积累
	UINT			m_SubTrainExpRate;					//带练经验效率
	UINT			m_SubTrainMoneyRate;				//带练金钱效率
	_SUBTRAIN_SETTING( )
	{
		CleanUp( ) ;
	}
	VOID CleanUp( )
	{
		m_bSubTrainOpen = FALSE;
		m_SubTrainMode  = SUBTRAIN_MODE1;
		m_SubTrainBeginTime = 0;
		m_SubTrainMoney	= 0;
		m_SubTrainExper = 0;
		m_SubTrainExpRate  = 0;
		m_SubTrainMoneyRate = 0;
	}
};

struct _SETTING_DB_LOAD
{
	_OWN_SETTING		m_aSetting[MAX_SETTING_DATA] ;//索引值为：SETTING_TYPE
	_SUIT_SETTING		m_SuitSetting[MAX_SUIT_SETTING];
	_SUBTRAIN_SETTING   m_SubTrainSetting;

	_SETTING_DB_LOAD( )
	{
		CleanUp( ) ;
	}
	VOID CleanUp( )
	{
		for( INT i=0; i<MAX_SETTING_DATA; i++ )
		{
			m_aSetting[i].CleanUp() ;
		}

		for(INT i=0; i<MAX_SUIT_SETTING; ++i)
		{
			m_SuitSetting[i].CleanUp();
		}

		m_SubTrainSetting.CleanUp();
	}
};

typedef struct _SETTING_DB_LOAD _SETTING_LIST;

struct _PRIVATE_INFO_DB_LOAD 
{
	BYTE		m_InfoType;			//保密程度
	UINT		m_CharGUID;			//角色编号
	BYTE		m_Age;				//年龄
	BYTE		m_Sex;				//性别
	CHAR		m_JobInfo[MAX_JOBINFO_LENGTH];		//职业信息
	CHAR		m_SchoolInfo[MAX_SCHOOLINFO_LENGTH];//毕业院校
	BYTE		m_BloodType;		//血型
	BYTE		m_YearAnimal;		//生肖
	BYTE		m_Consella;			//星座
	BYTE		m_Province;			//省份
	CHAR		m_City[MAX_CITY_LENGTH];	//城市
	CHAR		m_EmailInfo[MAX_EMAIL_LENGTH];//邮件
	CHAR		m_LuckWord[MAX_LUCKWORD_LENGTH];//心情寄语

	_PRIVATE_INFO_DB_LOAD()
	{
		CleanUp();
	}
	VOID CleanUp()
	{
		memset(this,0,sizeof(*this));
		m_CharGUID = INVALID_ID ;
	}
};

struct HUMAN_DB_ATTR_FLAG
{
	HUMAN_DB_ATTR_FLAG()
	{
		CleanUp();
	}

	VOID		CleanUp()
	{
		memset(this,0,sizeof(*this));
	}

	

	BOOL		IsUpdated(INT BitOffSet)
	{
		if(m_Flags[BitOffSet/8] & (1<<(BitOffSet%8)))
			return TRUE;
		return FALSE;
	}
	VOID		SetBitFlag(INT BitOffSet,BOOL	bValue)
	{
		if ( bValue )
			m_Flags[BitOffSet/8] |= (1<<(BitOffSet%8));
		else
			m_Flags[BitOffSet/8] &= (~(1<<(BitOffSet%8)));
	}
	
	CHAR		m_Flags[HUMAN_DB_ATTR_FLAG_LENGTH];
};

struct HUMAN_DB_ATTR_REG
{
	HUMAN_DB_ATTR_REG()
	{
		CleanUp();
	}
	VOID	CleanUp()
	{
		memset(this,0,sizeof(*this));
	}

	VOID*							m_AttrPtr[CATTR_DB_NUMBER];	//角色属性注册
	INT								m_AttrSize[CATTR_DB_NUMBER];//角色属性大小
};

struct FULLUSERDATA
{
	FULLUSERDATA()
	{
		CleanUp();
	}
	_HUMAN_DB_LOAD				m_Human;
	_BANK_DB_LOAD				m_Bank;
	_BAG_DB_LOAD				m_Bag;
	_EQUIP_DB_LOAD				m_Equip;
	_SKILL_DB_LOAD				m_Skill;
	_COOLDOWN_DB_LOAD_FOR_HUMAN m_Cooldown;
	_XINFA_DB_LOAD				m_XinFa;
	_IMPACT_DB_LOAD				m_Impact;
	_ABILITY_DB_LOAD			m_Ability;
	_MISSION_DB_LOAD			m_Mission;
	_SETTING_DB_LOAD			m_Setting;
	_PET_DB_LIST_LOAD			m_PetList;
	_RELATION_DB_LOAD			m_Relation ;
	_PRIVATE_INFO_DB_LOAD		m_PrivateInfo;
	_SOUXIA_DB_LOAD				m_SouXia;
	_MOUNT_DB_LOAD              m_Mount;           // [7/8/2010 陈军龙]
	BOOL						m_bIsPasswdUnlock;

	VOID	CleanUp( )
	{
		m_Human.CleanUp();
		m_Equip.CleanUp();
		m_Bag.CleanUp();
		m_Bank.CleanUp();
		m_Skill.CleanUp();
		m_Cooldown.CleanUp();
		m_XinFa.CleanUp();
		m_Impact.CleanUp();
		m_Ability.CleanUp();
		m_Mission.CleanUp();
		m_Setting.CleanUp();
		m_PetList.CleanUp();
		m_Relation.CleanUp() ;
		m_PrivateInfo.CleanUp();
		m_SouXia.CleanUp();
		m_Mount.CleanUp();           // [7/8/2010 陈军龙]
		m_bIsPasswdUnlock = FALSE;
	};

	_ITEM*	GetItem(UINT uDBPos)
	{
		Assert(uDBPos<=DB_BANK_POS_END);
		if(uDBPos>=DB_BANK_POS_START) 
		{
			return &m_Bank.m_pItem[uDBPos-DB_BANK_POS_START];
		}
		else if(uDBPos>=DB_EQUIP_POS_START)
		{
			return &m_Equip.m_pItem[uDBPos-DB_EQUIP_POS_START];
		}
		else if(uDBPos>=DB_BAG_POS_START)
		{
			return &m_Bag.m_pItem[uDBPos-DB_BAG_POS_START];
		}

		return NULL;
	}

	INT&	GetMagicIntSetting()
	{
		return m_Setting.m_aSetting[SETTING_TYPE_MAGICINT].m_SettingData;
	}

	BYTE&	GetMagicIntType()
	{
		return m_Setting.m_aSetting[SETTING_TYPE_MAGICINT].m_SettingType;
	}

	VOID OutputToDisk( char* filename )
	{
		if( filename==NULL || filename[0]==0 )
			return ;

		_MY_TRY
		{
			FILE* fp = fopen( filename, "wb" ) ;
			if( fp )
			{
				fwrite( &m_Human,sizeof(_HUMAN_DB_LOAD), 1, fp ) ;
				fwrite( &m_Equip, sizeof(_EQUIP_DB_LOAD), 1, fp ) ;
				fwrite( &m_Bag, sizeof(_BAG_DB_LOAD), 1, fp ) ;
				fwrite( &m_Bank, sizeof(_BANK_DB_LOAD), 1, fp ) ;
				fwrite( &m_Skill, sizeof(_SKILL_DB_LOAD), 1, fp ) ;
				fwrite( &m_Cooldown, sizeof(_COOLDOWN_DB_LOAD_FOR_HUMAN), 1, fp ) ;
				fwrite( &m_XinFa, sizeof(_XINFA_DB_LOAD), 1, fp ) ;
				fwrite( &m_Impact, sizeof(_IMPACT_DB_LOAD), 1, fp ) ;
				fwrite( &m_Ability, sizeof(_ABILITY_DB_LOAD), 1, fp ) ;
				fwrite( &m_Mission, sizeof(_MISSION_DB_LOAD), 1, fp ) ;
				fwrite( &m_Setting, sizeof(_SETTING_DB_LOAD), 1, fp ) ;
				fwrite( &m_PetList, sizeof(_PET_DB_LIST_LOAD), 1, fp ) ;
				fwrite( &m_Relation, sizeof(_RELATION_DB_LOAD), 1, fp ) ;
				fwrite( &m_PrivateInfo, sizeof(_PRIVATE_INFO_DB_LOAD), 1, fp ) ;
				fwrite( &m_bIsPasswdUnlock, sizeof(BOOL), 1, fp ) ;
				fwrite( &m_SouXia, sizeof(_SOUXIA_DB_LOAD), 1, fp ) ;
				fwrite( &m_Mount, sizeof(_MOUNT_DB_LOAD), 1, fp ) ;                      // [7/8/2010 陈军龙] 
				//fwrite( &m_DRideData, sizeof(_DRIDE_DATA), 1, fp ) ;

				fclose( fp ) ;
			}
		}
		_MY_CATCH
		{
		}
	}
};

#define SM_USE_FREE				0
#define SM_USE_READYFREE		1
#define SM_USE_FREEED			2
#define SM_USE_HOLDDATA			3

struct  SMUHead
{
	UINT		PoolId;
	SMUID_t		SMUid;
	INT			UseStatus;
	CHAR		flag;
	PlayerID_t	PID;
	UINT		SaveTime;	//应该是保存绝对时间，
							//因为牵涉到不同进程之间通讯
							//精确到秒
	SMUHead()
	{
		CleanUp();
	}

	VOID	CleanUp()
	{
		PoolId			=	-1;
		SMUid			=	0;
		PID				=	-1;
		UseStatus		=	SM_USE_FREE;
		flag			=	SM_FREE;
		SaveTime		=	0;
	}

}; 


struct HumanSMU	
{
	 SMUHead						m_SMUHead;
	 HUMAN_DB_ATTR_FLAG				m_AttrFlag;	//角色属性标志位
	_HUMAN_DB_LOAD					m_HumanSM ;	//角色基本信息
	_BANK_DB_LOAD					m_BankSM ;	//角色银行物品信息
	_SKILL_DB_LOAD					m_SkillSM ;	//角色身上拥有的技能信息
	_COOLDOWN_DB_LOAD_FOR_HUMAN		m_CooldownSM ; //角色身上的冷却信息
	_XINFA_DB_LOAD					m_XinFaSM ;	//角色学会的心法信息
	_IMPACT_DB_LOAD					m_ImpactSM ;//角色身上所施加的附加效果信息
	_ABILITY_DB_LOAD				m_AbilitySM; // 角色学会的生活技能信息以及配方表
	_MISSION_DB_LOAD				m_MissionSM; // 任务列表
	_SETTING_DB_LOAD				m_SettingSM; // 任务列表
	_PET_DB_LIST_LOAD				m_PetListSM; // 宠物列表
	_BAG_DB_LOAD					m_BagSM;	//角色背包物品信息
	_EQUIP_DB_LOAD					m_EquipSM;	//角色装备信息
	_RELATION_DB_LOAD				m_RelationSM; //角色联系人（好友、黑名单）
	_PRIVATE_INFO_DB_LOAD			m_PrivateInfoSM;//私人信息
	_SOUXIA_DB_LOAD					m_SouXiaSM; // 捜侠录信息 add by gh 2010/05/10
	_MOUNT_DB_LOAD                  m_MountSM;  // 坐骑信息   [7/8/2010 陈军龙]

public:

	VOID	CleanUp()
	{
		
		m_SMUHead.CleanUp();
		m_AttrFlag.CleanUp();
		m_HumanSM.CleanUp();
		m_BankSM.CleanUp();
		m_SkillSM.CleanUp();
		m_CooldownSM.CleanUp();
		m_XinFaSM.CleanUp();
		m_ImpactSM.CleanUp();
		m_AbilitySM.CleanUp();
		m_MissionSM.CleanUp();
		m_SettingSM.CleanUp();
		m_PetListSM.CleanUp();
		m_BagSM.CleanUp();
		m_EquipSM.CleanUp();
		m_RelationSM.CleanUp() ;
		m_PrivateInfoSM.CleanUp();
		m_SouXiaSM.CleanUp();
		m_MountSM.CleanUp();        // [7/8/2010 陈军龙]
	}


	VOID	SetPoolID(UINT poolID)
	{
		m_SMUHead.PoolId = poolID;
	}	

	UINT	GetPoolID()
	{
		return m_SMUHead.PoolId;
	}


	BOOL	SetUseStatus(INT Use,CHAR Type)
	{
		Lock(Type);

		m_SMUHead.UseStatus	= Use;

		UnLock(Type);

		return TRUE;
	}

	INT	GetUseStatus(CHAR Type)
	{
		INT iRet;
		Lock(Type);
		
		iRet = m_SMUHead.UseStatus;

		UnLock(Type);
		
		return iRet;

	}

	INT		GetUseStatusFast()
	{
		return m_SMUHead.UseStatus;
	}

	UINT	GetTime2Save(CHAR Type)
	{
		UINT	uTime;
		Lock(Type);

		uTime= m_SMUHead.SaveTime;

		UnLock(Type);

		return uTime;
	}

	INT		GetTime2SaveFast()
	{
		return m_SMUHead.SaveTime;
	}

	VOID	SetTime2Save(UINT uTime,CHAR Type)
	{
		Lock(Type);
		m_SMUHead.SaveTime = uTime;
		UnLock(Type);
	}

	CHAR	GetLockValueFast()
	{
		return m_SMUHead.flag;
	}

	VOID	SetPlayerID(CHAR Type,PlayerID_t	nID)
	{
		Lock(Type);
		m_SMUHead.PID	=	nID;
		UnLock(Type);
	}

	PlayerID_t	GetPlayerID(CHAR Type)
	{
		PlayerID_t	id;
		Lock(Type);
		id = m_SMUHead.PID;
		UnLock(Type);

		return id;
	}

	BOOL	TryLock(CHAR Type)
	{
		return sm_trylock(m_SMUHead.flag,Type);
	}

	VOID	Lock(CHAR Type)
	{
		sm_lock(m_SMUHead.flag,Type);

	}

	VOID	UnLock(CHAR Type)
	{
		sm_unlock(m_SMUHead.flag,Type);
	}

	VOID	Copy2FullData(CHAR Type,FULLUSERDATA* pData)
	{
		Lock(Type);
		
		Assert(pData);
		
		memcpy(&pData->m_Ability,&m_AbilitySM,sizeof(m_AbilitySM));
		memcpy(&pData->m_Bag,&m_BagSM,sizeof(m_BagSM));
		memcpy(&pData->m_Bank,&m_BankSM,sizeof(m_BankSM));
		memcpy(&pData->m_Cooldown,&m_CooldownSM,sizeof(m_CooldownSM));
		memcpy(&pData->m_Equip,&m_EquipSM,sizeof(m_EquipSM));
		memcpy(&pData->m_Human,&m_HumanSM,sizeof(m_HumanSM));
		memcpy(&pData->m_Impact,&m_ImpactSM,sizeof(m_ImpactSM));
		memcpy(&pData->m_Mission,&m_MissionSM,sizeof(m_MissionSM));
		memcpy(&pData->m_Setting,&m_SettingSM,sizeof(m_SettingSM));
		memcpy(&pData->m_PetList,&m_PetListSM,sizeof(m_PetListSM));
		memcpy(&pData->m_Relation,&m_RelationSM,sizeof(m_RelationSM));
		memcpy(&pData->m_Skill,&m_SkillSM,sizeof(m_SkillSM));
		memcpy(&pData->m_XinFa,&m_XinFaSM,sizeof(m_XinFaSM));
		memcpy(&pData->m_PrivateInfo,&m_PrivateInfoSM,sizeof(m_PrivateInfoSM));
		memcpy(&pData->m_SouXia,&m_SouXiaSM,sizeof(m_SouXiaSM));	// add by gh for souxia 1010/05/10
		memcpy(&pData->m_Mount,&m_MountSM,sizeof(m_MountSM));       // [7/8/2010 陈军龙]

		UnLock(Type);
	}

	BOOL	TryCopy2FullData(CHAR Type,FULLUSERDATA* pData)
	{
		if(!pData)
			return FALSE;

		if(TryLock(Type))
		{
			memcpy(&pData->m_Ability,&m_AbilitySM,sizeof(m_AbilitySM));
			memcpy(&pData->m_Bag,&m_BagSM,sizeof(m_BagSM));
			memcpy(&pData->m_Bank,&m_BankSM,sizeof(m_BankSM));
			memcpy(&pData->m_Cooldown,&m_CooldownSM,sizeof(m_CooldownSM));
			memcpy(&pData->m_Equip,&m_EquipSM,sizeof(m_EquipSM));
			memcpy(&pData->m_Human,&m_HumanSM,sizeof(m_HumanSM));
			memcpy(&pData->m_Impact,&m_ImpactSM,sizeof(m_ImpactSM));
			memcpy(&pData->m_Mission,&m_MissionSM,sizeof(m_MissionSM));
			memcpy(&pData->m_Setting,&m_SettingSM,sizeof(m_SettingSM));
			memcpy(&pData->m_PetList,&m_PetListSM,sizeof(m_PetListSM));
			memcpy(&pData->m_Relation,&m_RelationSM,sizeof(m_RelationSM));
			memcpy(&pData->m_Skill,&m_SkillSM,sizeof(m_SkillSM));
			memcpy(&pData->m_XinFa,&m_XinFaSM,sizeof(m_XinFaSM));
			memcpy(&pData->m_PrivateInfo,&m_PrivateInfoSM,sizeof(m_PrivateInfoSM));
			memcpy(&pData->m_SouXia,&m_SouXiaSM,sizeof(m_SouXiaSM));	// add by gh for souxia 1010/05/10
			memcpy(&pData->m_Mount,&m_MountSM,sizeof(m_MountSM));       // [7/8/2010 陈军龙]

			UnLock(Type);

			return TRUE;
		}

		return FALSE;
	}

};

struct SMHead
{
	SM_KEY			m_Key;
	unsigned long	m_Size;
	UINT			m_HeadVer;//最后存盘版本
	SMHead()
	{
		m_Key		=	0;
		m_Size		=	0;
		m_HeadVer	=	0;
	}
};

struct GUILDUSER_DB
{
	GUID_t				m_UserGUID;							//玩家GUID
	CHAR				m_szUserName[MAX_CHARACTER_NAME];	//玩家名字
	GUILD_POSITION		m_Position;							//职务
	UINT				m_uAccess;							//权限
	UINT				m_uLastLoginTime;					//最后上线时间
	UINT				m_uLevel;							//人物级别
	BYTE				m_bMenPaiID;						//门派
	INT					m_iCurContribute;					//贡献
	INT					m_iMaxContribute;					//最大贡献
	INT					m_iJoinTime;						//加入时间
    BYTE                m_iSex;                             //性别
    CHAR                m_szTitleName[MAX_CHARACTER_TITLE];


	GUILDUSER_DB( )
	{
		CleanUp( );
	};
	VOID CleanUp( )
	{	
		m_UserGUID = INVALID_ID;
		memset( m_szUserName, 0, sizeof(CHAR)*MAX_CHARACTER_NAME );
		memset( m_szTitleName, 0, sizeof(CHAR)*MAX_CHARACTER_TITLE );
		m_Position = GUILD_POSITION_TRAINEE;
		m_uAccess = 0;
		m_uLastLoginTime = 0;
		m_uLevel	=	0;							//人物级别
		m_bMenPaiID	=	INVALID_JOB;				//门派
		m_iCurContribute	=	0;					//贡献
		m_iMaxContribute	=	0;					//最大贡献
		m_iJoinTime	=	0;						    //加入时间
        m_iSex      = 3;
	}
};

struct FAMILYUSER_DB
{
    INT                 m_aFamilyUser[GUILD_FAMILY_SIZE][USER_FAMILY_SIZE]; //家族成员 只记录m_aGuildUser下标

    enum ORESULT
    {
        RET_SUCCESS = 0,
        RET_POS_FULL,	//人都满了
        RET_NO_EXIST,	//不存在

        RET_UNKOWN,
    };

    FAMILYUSER_DB &operator = ( const FAMILYUSER_DB &in )
    {
        if ( &in != this )
        {
            for (INT i=0; i<GUILD_FAMILY_SIZE; ++i)
            {
                for (INT j=0; j<USER_FAMILY_SIZE ; ++j)
                {
                    m_aFamilyUser[i][j] = in.m_aFamilyUser[i][j];
                }
            }
        }
        return *this;
    } 

    INT Add (INT iFamilyId, INT iIndex)   //家族ID，玩家在m_aGuildUser的下标
    {
        for (INT i=0; i<USER_FAMILY_SIZE ; ++i)
        {
            if (INVALID_ID == m_aFamilyUser[iFamilyId][i])
            {
                m_aFamilyUser[iFamilyId][i] = iIndex;
                return RET_SUCCESS;
            }
        }
        return RET_POS_FULL;
    }

    INT Remove (INT iFamilyId, INT iIndex)
    {
        for (INT i=0; i<USER_FAMILY_SIZE; ++i)
        {
            if (iIndex == m_aFamilyUser[iFamilyId][i])
            {
                m_aFamilyUser[iFamilyId][i] = INVALID_ID;
                return RET_SUCCESS;
            }
        }
        return RET_NO_EXIST;
    }

    FAMILYUSER_DB( )
    {
        CleanUp( );
    };

    VOID CleanUp( )
    {
        for( INT i=0; i<GUILD_FAMILY_SIZE; ++i )
        {
            for( INT j=0; j<USER_FAMILY_SIZE; ++j )
            {
                m_aFamilyUser[i][j] = INVALID_ID;
            }
        }
    }
};

struct GUILD_DB
{
	GuildID_t				m_GuildID;							//帮会ID
	CHAR					m_GuildName[MAX_GUILD_NAME_SIZE];   //帮会名称
	CHAR					m_GuildDesc[MAX_GUILD_DESC_SIZE];   //帮会宗旨
	GUILD_STATUS			m_Status;							//帮会的状态
	GUID_t					m_ChieftainGUID;					//帮主的 GUID
	INT						m_nProposerCount;					//申请人数
	INT						m_UserCount;						//帮会用户数量
	INT						m_MaxUserSize;						//帮会人口上限
	INT						m_GuildPoint;						//帮会贡献点
	INT						m_GuildMoney;						//帮会资金
	GUILDUSER_DB			m_aGuildUser[USER_ARRAY_SIZE];		//帮会成员
	CityID_t				m_CityID;							//绑定的城市ID
	INT						m_nTime;
	INT						m_Longevity;				        //资历
	INT						m_Contribute;				        //贡献度
	INT						m_Honor;					        //人气
	GUILD_ADMIN_t			m_AdminLayout;
    FAMILYUSER_DB           m_FamilyUser;                       //家族信息
    BYTE                    m_iSex;
    CHAR                    m_szTitleName[MAX_CHARACTER_TITLE];   //称号名字

	GUILD_DB()
	{
		CleanUp();	
	}

	VOID CleanUp()
	{
		m_GuildID = INVALID_ID;
		memset( m_GuildName, 0, MAX_GUILD_NAME_SIZE*sizeof(CHAR) );
		memset( m_szTitleName, 0, MAX_CHARACTER_TITLE*sizeof(CHAR) );
		memset( m_GuildDesc, 0, MAX_GUILD_DESC_SIZE*sizeof(CHAR) );
		m_ChieftainGUID		= INVALID_ID;
		m_nProposerCount	= 0;
		m_UserCount = 0;
		m_MaxUserSize = 0;
		m_GuildPoint = 0;
		m_GuildMoney = 0;
        m_iSex       = 2;
        m_FamilyUser.CleanUp();

		for( INT i=0; i<USER_ARRAY_SIZE; i++ )
		{
			m_aGuildUser[i].CleanUp();
		}

		m_CityID = INVALID_ID;
		m_nTime	 = 0;
		m_Longevity		=	0;			//资历
		m_Contribute	=	0;			//贡献度
		m_Honor			=	0;			//人气

		m_AdminLayout.CleanUp();
	}
};

enum	GUILD_USE_STATS
{
	GUILD_ADDNEW	=0,		//新加的需要保存
	GUILD_DELETE,			//删除的需要保存
	GUILD_SAVED,			//已经保存过
};

struct GuildSMU
{
	SMUHead				m_SMUHead;
	GUILD_DB			m_GuildSM;


	VOID	Lock(CHAR Type)
	{
		sm_lock(m_SMUHead.flag,Type);

	}

	VOID	UnLock(CHAR Type)
	{
		sm_unlock(m_SMUHead.flag,Type);
	}
	
	VOID	SetPoolID(UINT poolID)
	{
		m_SMUHead.PoolId = poolID;
	}	

	UINT	GetPoolID()
	{
		return m_SMUHead.PoolId;
	}
	BOOL	SetUseStatus(INT Use,CHAR Type)
	{
		Lock(Type);
		m_SMUHead.UseStatus	= Use;
		UnLock(Type);
		return TRUE;
	}
	INT	GetUseStatus(CHAR Type)
	{
		INT iRet;
		Lock(Type);
		iRet = m_SMUHead.UseStatus;
		UnLock(Type);
		return iRet;
	}
	UINT	GetTime2Save(CHAR Type)
	{
		UINT	uTime;
		Lock(Type);
		uTime= m_SMUHead.SaveTime;
		UnLock(Type);
		return uTime;
	}

	VOID	SetTime2Save(UINT uTime,CHAR Type)
	{
		Lock(Type);
		m_SMUHead.SaveTime = uTime;
		UnLock(Type);
	}

	VOID	Init()
	{
		m_GuildSM.CleanUp();
	}
};

enum	MAIL_USE_STATS
{
	MAIL_ADDNEW		= 0,	//新加的需要保存
	MAIL_DELETE,			//删除的需要保存
	MAIL_REFRESH,			//邮件信息刷新
	MAIL_SAVED,				//已经保存过
};

struct MailSMU 
{
	SMUHead				m_SMUHead;
	MAIL				m_MailSM;

	VOID	Lock(CHAR Type)
	{
		sm_lock(m_SMUHead.flag,Type);

	}

	VOID	UnLock(CHAR Type)
	{
		sm_unlock(m_SMUHead.flag,Type);
	}

	VOID	SetPoolID(UINT poolID)
	{
		m_SMUHead.PoolId = poolID;
	}	

	UINT	GetPoolID()
	{
		return m_SMUHead.PoolId;
	}
	BOOL	SetUseStatus(INT Use,CHAR Type)
	{
		Lock(Type);
		m_SMUHead.UseStatus	= Use;
		UnLock(Type);
		return TRUE;
	}
	INT	GetUseStatus(CHAR Type)
	{
		INT iRet;
		Lock(Type);
		iRet = m_SMUHead.UseStatus;
		UnLock(Type);
		return iRet;
	}
	UINT	GetTime2Save(CHAR Type)
	{
		UINT	uTime;
		Lock(Type);
		uTime= m_SMUHead.SaveTime;
		UnLock(Type);
		return uTime;
	}

	VOID	SetTime2Save(UINT uTime,CHAR Type)
	{
		Lock(Type);
		m_SMUHead.SaveTime = uTime;
		UnLock(Type);
	}

	VOID	Init()
	{
		m_MailSM.CleanUp();
	}
};


struct ItemSerialKeySMU
{
	SMUHead				m_SMUHead;
	UINT				m_ItemSerial;

	VOID	Lock(CHAR Type)
	{
		sm_lock(m_SMUHead.flag,Type);

	}

	VOID	UnLock(CHAR Type)
	{
		sm_unlock(m_SMUHead.flag,Type);
	}

	VOID	SetPoolID(UINT poolID)
	{
		m_SMUHead.PoolId = poolID;
	}	

	UINT	GetPoolID()
	{
		return m_SMUHead.PoolId;
	}
	BOOL	SetUseStatus(INT Use,CHAR Type)
	{
		Lock(Type);
		m_SMUHead.UseStatus	= Use;
		UnLock(Type);
		return TRUE;
	}
	INT	GetUseStatus(CHAR Type)
	{
		INT iRet;
		Lock(Type);
		iRet = m_SMUHead.UseStatus;
		UnLock(Type);
		return iRet;
	}
	UINT	GetTime2Save(CHAR Type)
	{
		UINT	uTime;
		Lock(Type);
		uTime= m_SMUHead.SaveTime;
		UnLock(Type);
		return uTime;
	}

	VOID	SetTime2Save(UINT uTime,CHAR Type)
	{
		Lock(Type);
		m_SMUHead.SaveTime = uTime;
		UnLock(Type);
	}

	UINT	GetSerial(CHAR Type)
	{
		UINT Serial;
		Lock(Type);
		Serial = m_ItemSerial;
		UnLock(Type);

		return Serial;
	}

	VOID	SetSerial(CHAR Type,UINT Serial)
	{
		Lock(Type);
		m_ItemSerial = Serial;
		UnLock(Type);
	}


	VOID	Init()
	{
		m_ItemSerial = 0;
	}
};



#pragma pack(pop)

#endif
