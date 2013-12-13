

#ifndef __HUMANDB_H__
#define __HUMANDB_H__

#include "Type.h"
#include "DB_Struct.h"
#include "TimeManager.h"
#include "GameTable.h"

#define			GetDBStr(db)			(db)->GetDBAttrLvl1(CATTR_LEVEL1_STR)
#define			GetDBCon(db)			(db)->GetDBAttrLvl1(CATTR_LEVEL1_CON)
#define			GetDBInt(db)			(db)->GetDBAttrLvl1(CATTR_LEVEL1_INT)
#define			GetDBDex(db)			(db)->GetDBAttrLvl1(CATTR_LEVEL1_DEX)

#define			SetDBStr(db,v)			(db)->SetDBAttrLvl1(CATTR_LEVEL1_STR,v)
#define			SetDBCon(db,v)			(db)->SetDBAttrLvl1(CATTR_LEVEL1_CON,v)
#define			SetDBInt(db,v)			(db)->SetDBAttrLvl1(CATTR_LEVEL1_INT,v)
#define			SetDBDex(db,v)			(db)->SetDBAttrLvl1(CATTR_LEVEL1_DEX,v)



class HumanDB
{

		
#define			N_SM_LOCK(type)						if(m_HumanSM){SM_LOCK(m_HumanSM->m_SMUHead.flag,type)};
#define			N_SM_UNLOCK(type)					if(m_HumanSM){SM_UNLOCK(m_HumanSM->m_SMUHead.flag,type)};

public :
	HumanDB( ) ;
	~HumanDB( ) ;

	VOID					CleanUp( ) ;
	VOID					ValidateShareMem(BOOL bForceAll,BOOL& bUpdateAttr);
	BOOL					IsNoDirectAttr(CHAR_ATTR_DB attrType);
	VOID					ValidatePlayerID(PlayerID_t	PID);
	inline VOID				Lock();
	inline VOID				UnLock();

	/*=========================================
	 *	基本属性访问方法
	 ===========================================*/
	inline	GUID_t				GetGUID()	const;
	inline	BOOL				IsFirstEnterScene();
	inline	VOID				ClearFirstEnterScene();
	inline	VOID				SetGUID( GUID_t guid );
	inline	INT					GetPortraitID() const;
	inline	VOID				SetPortraitID( INT nID );
	inline	const	CHAR*		GetName()const;
	inline	BYTE				GetSex();
	inline	INT					GetHP();
	inline	VOID				SetHP( INT hp );
	inline	INT					GetMP();
	inline	VOID				SetMP( INT mp );
	inline	INT					GetPneuma();
	inline	VOID				SetPneuma( INT pneuma );
	inline	INT					GetStrikePoint(VOID);
	inline	VOID				SetStrikePoint(INT nStrikePoint);
	inline	INT					GetVigor(VOID);
	inline	VOID				SetVigor(INT nVigor);
	inline	INT					GetMaxVigor(VOID);
	inline	VOID				SetMaxVigor(INT nMaxVigor);
	inline	INT					GetVigorRegeneRate(VOID);
	inline	VOID				SetVigorRegeneRate(INT nRate);
	inline	INT					GetEnergy(VOID);
	inline	VOID				SetEnergy(INT nEnergy);
	inline	INT					GetMaxEnergy(VOID);
	inline	VOID				SetMaxEnergy(INT nMaxEnergy);
	inline	INT					GetEnergyRegeneRate(VOID);
	inline	VOID				SetEnergyRegeneRate(INT nRate);
	inline	INT 				GetRage( VOID );
	inline	VOID				SetRage( INT nRage );
	inline	BYTE				GetLevel();
	inline	VOID				SetLevel( BYTE level );
	inline	INT					GetPKValue( VOID )const;
	inline	VOID				SetPKValue( INT nValue );
	inline	PET_GUID_t			GetCurrentPetGUID( VOID )const;
	inline	VOID				SetCurrentPetGUID( PET_GUID_t guid );
	inline	UINT				GetExp();
	inline	VOID				SetExp( UINT exp );

	inline	INT					GetCountry( ); //国家
	inline	VOID				SetCountry( INT nCountry );
	inline	INT					GetMenPai( );
	inline	VOID				SetMenPai( INT MenPai );
	inline	UINT				GetMoney();
	inline	VOID				SetMoney(UINT money);
    inline	UINT				GetGold();
    inline	VOID				SetGold(UINT gold);
    inline	UINT				GetTicket();
    inline	VOID				SetTicket(UINT ticket);

	inline	INT					GetGoodBadValue();
	inline	INT					SetGoodBadValue(INT nValue);
	inline	_PLAYERSHOP_GUID	GetShopGuid(INT nIndex);									
	inline	VOID				SetShopGuid( INT nIndex, _PLAYERSHOP_GUID pGuid );
	inline	_PLAYERSHOP_GUID	GetFavoriteShopGuid(INT nIndex);
	inline	VOID				SetFavoriteShopGuid( INT nIndex, _PLAYERSHOP_GUID pGuid );
	inline	const CHAR*			GetPasswd();
	inline	VOID				SetPasswd( const CHAR* szPasswd );
	inline	VOID				DelPasswd();
	inline	UINT				GetPasswdDeleteTime();
	inline	VOID				SetPasswdDeleteTime( UINT uTime );
	inline	BYTE				GetXinfaLevel(INT nXinfaID);
	inline	VOID				SetXinfaUplevel(INT nXinfaID, BYTE UplevelNum);
	inline	UINT				GetHairColor(VOID)const;
	inline	VOID				SetHairColor(UINT uColor);
	inline	BYTE				GetFaceColor(VOID)const;
	inline	VOID				SetFaceColor(BYTE byColor);
	inline	BYTE				GetHairModel(VOID)const;
	inline	VOID				SetHairModel(BYTE byModel);
	inline	BYTE				GetFaceModel(VOID)const;
	inline	VOID				SetFaceModel(BYTE byModel);

	inline	UINT				GetEquipID(HUMAN_EQUIP	equipPoint);
	inline	UINT				GetEquipLevel(HUMAN_EQUIP	equipPoint);
	inline	INT					GetDBAttrLvl1(CHAR_ATTR_LEVEL1 enAttrType);					//一级属性GET
	inline	VOID				SetDBAttrLvl1(CHAR_ATTR_LEVEL1 enAttrType,INT iValue);		//一级属性SET

	inline	INT					GetNeiShang();												//内伤

	inline 	const _CAMP_DATA	*GetDBCampData(VOID)const;	//取阵营
	inline	VOID				SetDBCampData(const _CAMP_DATA *pCampData);//设阵营
	inline	VOID				SetDBStartScene(SceneID_t	sceneID);
	inline	SceneID_t			GetDBBakScene();
	inline	VOID				SetDBBakScene(SceneID_t	sceneID);
	inline	VOID				SetDBPosition(const WORLD_POS& pos);						//position 不实时写数据库
	inline	VOID				SetDBBakPosition(const WORLD_POS& pos);
	inline  const WORLD_POS*	GetDBBakPosition();
	inline	VOID				WriteDBPosition(WORLD_POS& pos);							//玩家logout 时调用的函数
	
	inline	VOID				SetOnlineTime(UINT uTime);	    //设置总在线时间
	inline	UINT				GetOnlineTime();			    //取得总在线时间	
	inline  VOID				SetLoginTime(UINT uTime);	    //设置最后登录时间
	inline  UINT				GetLoginTime();				    //取得最后登录时间
	inline  VOID				SetLogoutTime(UINT uTime);	    //设置最后下线时间
	inline  UINT				GetLogoutTime();			    //取得最后下线时间
    inline  VOID				SetLeaveGuildTime(time_t uTime);//设置离开帮会的时间
    inline  time_t				GetLeaveGuildTime();		    //取得离开帮会的时间
	inline  VOID				SetDBVersion(UINT Ver);		    //设置数据库版本
	inline  UINT				GetDBVersion();				    //取得数据库版本



	inline	VOID				SetDBGuid(GUID_t	guid);
	inline	GuildID_t			GetDBGuildID( ) ;
	inline	VOID				SetDBGuildID( GuildID_t guildID ) ;
    inline	INT                 GetDBFamilyID( ) ;
    inline	VOID				SetDBFamilyID( INT nFamilyID ) ;
    inline	INT                 GetDBGuildOfficial( ) ;
    inline	VOID				SetDBGuildOfficial( INT nOfficial ) ;
    inline	INT                 GetDBGuildPoint( ) ;
    inline	VOID				SetDBGuildPoint( INT nGP ) ;
    inline	INT                 GetDBHonor( ) ;
    inline	VOID				SetDBHonor( INT nHonor ) ;


	inline	TeamID_t			GetDBTeamID( ) ;
	inline	VOID				SetDBTeamID( TeamID_t teamID ) ;
	
	inline	INT                 GetMountID( ) ;                // [7/8/2010 陈军龙]
	inline	VOID				SetMountID( INT nID ) ;        // [7/8/2010 陈军龙]
	inline	INT                 GetMountIndex( ) ;             // [7/8/2010 陈军龙]
	inline	VOID				SetMountIndex( INT nIndex ) ;  // [7/8/2010 陈军龙]

	//////////////////////////////////////////////////////////////////////////
	//所有称号数据访问方法		
	//////////////////////////////////////////////////////////////////////////
    inline    const _TITLE*     GetTitleInfo() const;
    inline    VOID				SetCurCountryTitle( INT iTitleID );                              //设置当前国家称号，如果当前称号不存在，会自动添加
    inline    VOID              SetCurGuildTitle(INT iTitleID );                                 //设置当前帮会称号，如果当前称号不存在，会自动添加
    inline    VOID              SetCurNormalTitle(INT iTitleID );                                //设置当前玩法称号，如果当前称号不存在，会自动添加
    inline    VOID				SetCurCountryTitle( INT iTitleID, INT &BuffID1, INT &BuffID2  ); //设置当前国家称号，如果当前称号不存在，会自动添加
    inline    VOID              SetCurGuildTitle(INT iTitleID, INT &BuffID1, INT &BuffID2 );     //设置当前帮会称号，如果当前称号不存在，会自动添加
    inline    VOID              SetCurNormalTitle(INT iTitleID, INT &BuffID1, INT &BuffID2 );    //设置当前玩法称号，如果当前称号不存在，会自动添加
    inline    INT				GetCurCountryTitle();
    inline    INT               GetCurGuildTitle();
    inline    INT               GetCurNormalTitle();

    inline    VOID              AddTitle(INT iTitleID, INT &BuffID1, INT &BuffID2 );
    inline    INT               RemoveTitle(INT iTitleID);
    inline    VOID              SetGuildTitleName(const CHAR *pszTitle, INT iSize);
    inline    const CHAR*       GetGuildTitleName() const;
    inline    VOID              SetCountryTitleName(const CHAR *pszTitle, INT iSize);
    inline    const CHAR*       GetCountryTitleName() const;
    inline    VOID              SetNormalTitleName(const CHAR *pszTitle, INT iSize);          //设置玩法称号
    inline    const CHAR*       GetNormalTitleName() const;
    inline    VOID              SetOfficalTitleName(const CHAR *pszTitle, INT iSize);         //保存玩家自定义称号
    inline    const CHAR*       GetOfficalTitleName() const;


    inline    const CHAR*       GetTitleNameByID( INT iTitleID, INT iSex  ) ;
    inline    BOOL              UpdateTitleTime();
    
	//////////////////////////////////////////////////////////////////////////
	//银行数据访问方法		
	//////////////////////////////////////////////////////////////////////////
	inline	const INT			GetBankItemCount( ) const ;
	inline	VOID				SetBankItemCount( const INT Bankitemcount ) ;
	inline	const _ITEM*		GetBankItem( const INT bankindex ) const ;
	inline	VOID				SetBankItem( const INT bankindex, const _ITEM* item ) ;
	inline	const INT			GetBankEndIndex( ) const ;
	inline	VOID				SetBankEndIndex( const INT bankindex ) ;
	inline	const INT			GetBankMoney( ) const ;
	inline	VOID				SetBankMoney( const INT money ) ;
	inline  VOID				EraseBankItem(UINT uBankIndex);
    inline	const INT			GetBankSize( ) const ;
	inline  VOID				ExpandBankSize(UINT uBanksize);

	inline	VOID				SwapBankWithBank(UINT iBankIndexFr, UINT iBankIndexTo );
	inline	VOID				SwapBankWithBag(UINT iBagIndex, UINT iBankIndex );
	inline	VOID				SwapBankWithEquip( HUMAN_EQUIP	equipPoint, UINT iBankIndex ) ;
	inline	VOID				OverWriteBag2Bank(UINT iBagIndex, UINT iBankIndex);
	inline	VOID				OverWriteEquip2Bank(HUMAN_EQUIP	equipPoint, UINT iBankIndex);
	inline	VOID				OverWriteBank2Bag(UINT iBagIndex, UINT iBankIndex);
	inline	VOID				OverWriteBank2Equip(HUMAN_EQUIP	equipPoint, UINT iBankIndex);

	VOID						SetFreeOwnFlag(INT Flag);
	INT							GetFreeOwnFlag();

	
	//////////////////////////////////////////////////////////////////////////
	//背包数据访问方法		
	//////////////////////////////////////////////////////////////////////////
	inline	VOID				EraseBagItem(uint BagIndex);
	inline	VOID				SwapEquipBag(HUMAN_EQUIP	equipPoint,uint iBagIndex);
	inline	VOID				OverWriteBag2Equip(uint iBagIndex,HUMAN_EQUIP	equipPoint);
	inline	VOID				OverWriteEquip2Bag(HUMAN_EQUIP	equipPoint,uint iBagIndex);
	inline	VOID				PutBagDB(const _ITEM* pItem,uint iBagIndex);
	inline	VOID				SwapBagDB(uint iAIndex,uint iBIndex);
	inline	BOOL				IncBagItemCount(uint iBagIndex);
	inline	BOOL				DecBagItemCount(uint iBagIndex);
	inline	VOID				SetItemBind(uint iBagIndex,BOOL	bBind);
	inline	const _ITEM*		GetBagItem(uint	iBagIndex)	const ;
	inline	const _ITEM*		GetEquipItem(HUMAN_EQUIP equipPoint);
	inline	VOID				EraseEquipItem(HUMAN_EQUIP equipPoint);
	inline	VOID				SetEquipMark(HUMAN_EQUIP eEquipPoint, BYTE bMark);
	inline	VOID				SetEquipDur(HUMAN_EQUIP eEquipPoint, INT Dur);
	inline	VOID				SetItemDur(uint BagIndex, INT Dur);
	inline	VOID				RandSet( ) ;										//测试用，随机设置用户相关信息
	inline	UINT				GetBaseBagSize();
	inline	UINT				GetExtraContainerSize();
	inline	UINT				GetExtraBagSize(UINT nIndex);
	
	inline	UINT				GetTaskBagSize();
	inline	UINT				GetMatBagSize();

	//////////////////////////////////////////////////////////////////////////
	//坐骑数据访问方法		   [7/8/2010 陈军龙]
	//////////////////////////////////////////////////////////////////////////
	inline const	_ITEM*		GetMountItem(UINT iMountIndex);
	inline	VOID				EraseMountItem(UINT iMountIndex);


	//////////////////////////////////////////////////////////////////////////
	//冷却时间访问
	//////////////////////////////////////////////////////////////////////////
	
	inline  VOID				SetCooldown(CooldownID_t nID,Time_t nTime);
	inline	BOOL				IsCooldowned(CooldownID_t nID) const;
	inline	VOID				HeartBeat_Cooldown(Time_t nDeltaTime);
	inline	Time_t				GetCooldownRemain(CooldownID_t nID) const;
	//////////////////////////////////////////////////////////////////////////
	//技能数据访问
	//////////////////////////////////////////////////////////////////////////
	inline BYTE					GetSkillCount();
	inline VOID					SetSkillCount(BYTE Count);
	inline _OWN_SKILL&			GetSkillID(BYTE Index);
	inline VOID					SetSkillID(const _OWN_SKILL& oSkill,BYTE Index);
	inline VOID					SetSkillLevel(const INT nID, BYTE Index, const INT nLevel);
	inline	INT					GetRemainPoints();	//剩余一级属性点
	inline  INT					GetRemainSkillPoints();  //剩余技能点
	inline	INT					Get_S_SkillPoints(INT nS);	//获得系技能点
	inline	VOID				SetDBRemainPoints(INT Point);
	inline  VOID                SetDBRemainSkillPoints(INT Point);
	inline  VOID                SetDB_S_SkillPoints(INT nS, INT Point);
	inline  VOID				SetMonsterPetAttr( INT iIndex, _Monster_Pet_DB_Struct* pMonsterPet );
	inline  VOID				SetHorseMattingFlag( BOOL bFlag );
	//////////////////////////////////////////////////////////////////////////
	//心法数据访问
	//////////////////////////////////////////////////////////////////////////
	inline BYTE					GetXinFaCount();
	inline VOID					SetXinFaCount(BYTE Count);
	inline SkillID_t			GetXinfaID(BYTE Index);
	inline VOID					SetXinfaID(SkillID_t nID,BYTE Index);
	inline BYTE					GetXinfaLevel(BYTE Index);
	inline VOID					SetXinfaLevel(BYTE Level,BYTE Index);
	//////////////////////////////////////////////////////////////////////////
	//Impact数据访问
	//////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////
	//任务数据访问
	//////////////////////////////////////////////////////////////////////////
	inline VOID					SetMissionDone(MissionID_t idMission,MissionID_t idIndex);
	inline VOID					SetMissionParam( UINT uIndexMission, UINT uIndexParam, INT nValue );
	inline VOID					SetMissionData( INT nIndex, INT nData );//设置当前附加任务数据
	inline VOID					SetMission(UINT uIndex,MissionID_t idMission,ScriptID_t idScript);
	inline VOID					SetMissionCount(UINT uCount);
	inline VOID					SetFlags_KillObject(UINT uIndex, BOOL bSet );
	inline VOID					SetFlags_EnterArea(UINT uIndex, BOOL bSet );
	inline VOID					SetFlags_ItemChanged(UINT uIndex, BOOL bSet );
	inline VOID					SetFlags_PetChanged(UINT uIndex, BOOL bSet );
	inline VOID					ClearMission(UINT uIndex);
	//////////////////////////////////////////////////////////////////////////
	//关系数据访问方法
	//////////////////////////////////////////////////////////////////////////

	inline  VOID				SetRelation(INT Index, const _OWN_RELATION* pRelation);
	inline	VOID				ModifyFriendType( INT nIndex, RELATION_TYPE RelationType );
	inline	VOID				UpdateRelationInfo( INT Index, const RELATION_MEMBER* pMemberInfo );
	inline	VOID				SetMood(const CHAR* szMood);
	inline	VOID				SetName(const INT index,const CHAR* szName);
	inline	VOID				ModifyFriendPoint(INT Index, INT nFriendPoint);
	inline	VOID				AdjustRelationType(INT Index, UCHAR uType);
	inline	VOID				AdjustRelationGroup(INT Index, UCHAR uGroup);
	inline	VOID				DeleteRelation(INT Index);
	inline	VOID				IncRelationCount(INT Index);
	inline	VOID				DecRelationCount(INT Index);
	inline	VOID				SetSpouse(const MarriageInfo* pMarriageInfo);
	inline	VOID				AddPrentice(GUID_t guid);
	inline	VOID				DelPrentice(GUID_t guid);
	inline	VOID				SetMoralPoint(UINT uPoint);
	inline	VOID				SetBetrayTime(time_t BetrayTime);
	inline	VOID				SetMaster(const MasterInfo* pMasterInfo);


	inline	VOID				SetAbilityLevel(AbilityID_t abilityid,INT lvl);
	inline	VOID				SetAbilityExp(AbilityID_t abilityid,INT exp);
	inline  VOID				SetPrescrLearnedFlag( const PrescriptionID_t prescrid, BOOL flag );

	//////////////////////////////////////////////////////////////////////////
	//宠物数据访问方法
	//////////////////////////////////////////////////////////////////////////
	inline const	_PET_DB_LOAD*	GetPet(uint	iIndex)	const ;


	//////////////////////////////////////////////////////////////////////////
	//用户设置数据访问方法
	//////////////////////////////////////////////////////////////////////////
	inline	VOID				SetSettingData( INT nType, _OWN_SETTING* Value ) ;
	inline const	_OWN_SETTING*	GetSetting( INT nType ) const ;
	//////////////////////////////////////////////////////////////////////////
	//玩家私有信息访问方法
	//////////////////////////////////////////////////////////////////////////
	inline  VOID				SetPrivateInfo(_PRIVATE_INFO_DB_LOAD* pPrivateInfo);
	inline  VOID				SetSouXiaDBInfo(_SOUXIA_DB_LOAD* pSouXiaInfo, SHORT offSet);
	inline	INT					GetReserve(INT index);
	inline	VOID				SetReserve(INT index,INT value);
	inline  SOUXIA_DATA*		GetSouXiaInfo(SHORT index);

public :
	/*========================================
	 *	初始化角色各种数据库信息
	 ========================================*/
	BOOL						InitHumanDB( ) ;
	BOOL						InitEquipDB( ) ;
	BOOL						InitBagDB( ) ;
	BOOL						InitBankDB( ) ;
	BOOL						InitEffectDB( ) ;
	BOOL						InitSkillDB( ) ;
	BOOL						InitCooldownDB();
	



private:
	inline _ITEM*				_GetBagItem(UINT uBagIndex);
	inline _ITEM*				_GetBankItem(UINT uBankIndex);
	inline VOID					_RegDBAttr(CHAR_ATTR_DB eOffSet,VOID* pArg,INT iSize);//注册单个属性
	inline VOID					_RegSMAttr(CHAR_ATTR_DB eOffSet,VOID* pArg,INT iSize);//注册ShareMem属性
	VOID						_RegisterDBAttributes();  //注册所有属性
	VOID						_RegisterSMAttributes();  //注册所有ShareMem属性
	
public:
	
	_PET_DB_LIST_LOAD*				m_dbPetList;	//宠物

	//属性脏标记访问方法
	VOID						SetDBEnumAttrDirty(CHAR_ATTR_DB eOffSet,BOOL bFlag = TRUE);
	BOOL						GetDBEnumAttrDirty(CHAR_ATTR_DB eOffSet);
	//向GLServer刷新数据的脏标记访问方法
	VOID						SetToWorldEnumAttrDirty(CHAR_ATTR_DB eOffSet,BOOL bFlag = TRUE);
	BOOL						GetToWorldEnumAttrDirty(CHAR_ATTR_DB eOffSet);

private:
	
	
	_HUMAN_DB_LOAD*					m_dbHuman ;		//角色基本信息
	_BAG_DB_LOAD*					m_dbBag ;		//角色背包物品信息
	_EQUIP_DB_LOAD*					m_dbEquip ;		//角色装备信息
	_BANK_DB_LOAD*					m_dbBank ;		//角色银行物品信息
	_SKILL_DB_LOAD*					m_dbSkill ;		//角色身上拥有的技能信息
	_COOLDOWN_DB_LOAD_FOR_HUMAN*	m_dbCooldown ;	//角色身上的冷却信息
	_RELATION_DB_LOAD*				m_dbRelation;	//角色联系人（好友、黑名单）
	_ABILITY_DB_LOAD*				m_dbAbility;	//角色学会的生活技能信息以及配方表
	_XINFA_DB_LOAD*					m_dbXinFa ;		//角色学会的心法信息
	_IMPACT_DB_LOAD*				m_dbImpact ;	//角色身上所施加的附加效果信息
	_MISSION_DB_LOAD*				m_dbMission;	//任务列表
	_SETTING_DB_LOAD*				m_dbSetting ;	//设置数据
	_PRIVATE_INFO_DB_LOAD*			m_dbPrivateInfo;//私人信息
	_MONSTER_PET_DB*				m_dbMonsterPet;	//召唤兽跨服专用，不要写数据库
	_SOUXIA_DB_LOAD*				m_dbSouXia;		//搜侠录信息 add by gh 2010/05/15
    _MOUNT_DB_LOAD*                 m_dbMount;      //角色的坐骑信息  [7/1/2010 陈军龙]

private:
	//共享内存相关数据
	HumanSMU*						m_HumanSM;		//共享内存数据
	HUMAN_DB_ATTR_FLAG*				m_AttrFlag;		//角色属性刷新控制数据
	HUMAN_DB_ATTR_FLAG*				m_AttrFlag_ToWorld;		//角色属性向GLServer刷新的控制数据
	HUMAN_DB_ATTR_REG*				m_AttrReg;		//角色属性注册数据
	HUMAN_DB_ATTR_REG*				m_AttrRegSM;	//角色属性在ShareMem中注册数据

public:
	inline const	_BAG_DB_LOAD*					GetBag();
	inline const	_HUMAN_DB_LOAD*					GetHumanDB()	const;
	inline const	_EQUIP_DB_LOAD*					GetEquipDB();
	inline const	_BANK_DB_LOAD*					GetBankDB();
	inline const	_SKILL_DB_LOAD*					GetSkillDB();
	inline const	_COOLDOWN_DB_LOAD_FOR_HUMAN* 	GetCooldownDB() const;
	inline const	_RELATION_DB_LOAD*				GetRelationDB()	const;
	inline const	_ABILITY_DB_LOAD*				GetAbilityDB()	const;
	inline const	_XINFA_DB_LOAD*					GetXinFaDB()	const;
	inline const	_IMPACT_DB_LOAD*				GetImpactDB()	const;
	inline const	_MISSION_DB_LOAD*				GetMissionDB()  const;
	inline const	_SETTING_DB_LOAD*				GetSettingDB()  const;
	inline const	_PRIVATE_INFO_DB_LOAD*			GetPrivateInfoDB() const;
	inline const	_MONSTER_PET_DB*				GetMonsterPetDB() const;
	inline const	_SOUXIA_DB_LOAD*				GetSouXiaDB()	const;
	inline const	_MOUNT_DB_LOAD*			        GetMountDB()    const;    // [7/8/2010 陈军龙]

	//请不要在human的逻辑计算中调用下列函数
	inline VOID								WriteHumanDB(const	_HUMAN_DB_LOAD* pHumanDB);
	inline VOID								WriteBagDB(const	_BAG_DB_LOAD* pBagDB);
	inline VOID								WriteEquipDB(const	_EQUIP_DB_LOAD*	pEquipDB);
	inline VOID								WriteBankDB(const	_BANK_DB_LOAD*	pBankDB);
	inline VOID								WriteSkillDB(const _SKILL_DB_LOAD* pSkillDB);
	inline VOID								WriteCooldownDB(const _COOLDOWN_DB_LOAD_FOR_HUMAN*	pCooldownDB);
	inline VOID								WriteRelationDB(const _RELATION_DB_LOAD* pRelationDB);
	inline VOID								WriteAbilityDB(const _ABILITY_DB_LOAD* pAbilityDB);
	inline VOID								WriteXinFaDB(const _XINFA_DB_LOAD* pXinFaDB);
	inline VOID								WriteImpactDB(const _IMPACT_DB_LOAD* pImpactDB);
	inline VOID								WriteMissionDB(const _MISSION_DB_LOAD* pMissionDB);
	inline VOID								WriteSettingDB(const _SETTING_DB_LOAD* pSettingDB);
	inline VOID								WritePrivateInfo(const _PRIVATE_INFO_DB_LOAD* pPrivateDB);
	inline VOID								WriteSouXiaDB(const _SOUXIA_DB_LOAD* pSouXiaDB);
	inline VOID								WriteMountDB(const _MOUNT_DB_LOAD* pMountDB);                        // [7/8/2010 陈军龙]

private:
	//////////////////////////////////////////////////////////////////////////
	// 接口和方法  2005.11.25 版
	//////////////////////////////////////////////////////////////////////////
	//共享内存、DB属性注册数据
	VOID*									GetDBEnumAttr(CHAR_ATTR_DB eOffSet);
	VOID*									GetSMEnumAttr(CHAR_ATTR_DB eOffSet);
	INT										GetDBEnumAttrSize(CHAR_ATTR_DB eOffSet);
	
};

#include "HumanDB.inl"

#endif
