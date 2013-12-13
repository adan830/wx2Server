#ifndef _WGDetailOtherOnlineAttrib_Horse_H_
#define _WGDetailOtherOnlineAttrib_Horse_H_

#include "Type.h"
#include "Packet.h"
#include "PacketFactory.h"
#include "DB_Struct.h"
#include "GCDetailAttrib_Pet.h"

#define MAX_EXTRAINFO_LENGTH 256

namespace Packets
{
	//enum 
	//{
	//	TYPE_NORMAL = 0, 
	//	TYPE_EXCHANGE,
	//	TYPE_STALL,
	//	TYPE_PLAYERSHOP,
	//	TYPE_CONTEX_MENU_OTHER_PET,
	//};

	//enum ENUM_PET_DETAIL_ATTR
	//{
	//	PET_DETAIL_ATTR_INVALID		= -1,
	//	PET_DETAIL_ATTR_OBJ_ID,				// ObjID
	//	PET_DETAIL_ATTR_DATA_ID,			// DataID
	//	PET_DETAIL_ATTR_NAME,				// 名称
	//	PET_DETAIL_ATTR_NICK_NAME,			// 昵称
	//	PET_DETAIL_ATTR_AI_TYPE,			// 性格
	//	PET_DETAIL_ATTR_SPOUSE_GUID,		// 配偶ID
	//	PET_DETAIL_ATTR_LEVEL,				// 等级
	//	PET_DETAIL_ATTR_EXP,				// 经验
	//	PET_DETAIL_ATTR_HP,					// 血当前值
	//	PET_DETAIL_ATTR_HPMAX,				// 血最大值

	//	PET_DETAIL_ATTR_LIFE,				// 当前寿命
	//	PET_DETAIL_ATTR_GENERATION,			// 几代宠
	//	PET_DETAIL_ATTR_HAPPINESS,			// 快乐度

	//	//PET_DETAIL_ATTR_ATT_PHYSICS,		// 物理攻击力
	//	PET_DETAIL_ATTR_ATT_NEAR,
	//	PET_DETAIL_ATTR_ATT_FAR,

	//	PET_DETAIL_ATTR_ATT_MAGIC_NEAR,			// 近程内功攻击力
	//	//PET_DETAIL_ATTR_DEF_PHYSICS,		// 物理防御力
	//	PET_DETAIL_ATTR_DEF_NEAR,
	//	PET_DETAIL_ATTR_DEF_FAR,

	//	PET_DETAIL_ATTR_DEF_MAGIC_NEAR,			// 近程内功防御力

	//	PET_DETAIL_ATTR_HIT,				// 命中率
	//	PET_DETAIL_ATTR_MISS,				// 闪避率
	//	PET_DETAIL_ATTR_CRITICAL,			// 会心率

	//	PET_DETAIL_ATTR_MODELID,			// 外形
	//	PET_DETAIL_ATTR_MOUNTID,			// 座骑ID

	//	PET_DETAIL_ATTR_STRPERCEPTION,		// 力量资质
	//	PET_DETAIL_ATTR_CONPERCEPTION,		// 体力资质
	//	PET_DETAIL_ATTR_DEXPERCEPTION,		// 身法资质
	//	//PET_DETAIL_ATTR_SPRPERCEPTION,		// 灵气资质
	//	PET_DETAIL_ATTR_INTPERCEPTION,		// 定力资质

	//	PET_DETAIL_ATTR_STR,				// 力量
	//	PET_DETAIL_ATTR_CON,				// 体力
	//	PET_DETAIL_ATTR_DEX,				// 身法
	//	PET_DETAIL_ATTR_INT,				// 定力
	//	PET_DETAIL_ATTR_GENGU,				// 根骨

	//	PET_DETAIL_ATTR_POINT_REMAIN,		// 潜能点

	//	PET_DETAIL_ATTR_SKILL_0,			// 技能0
	//	PET_DETAIL_ATTR_SKILL_1,			// 技能1
	//	PET_DETAIL_ATTR_SKILL_2,			// 技能2
	//	PET_DETAIL_ATTR_SKILL_3,			// 技能3
	//	PET_DETAIL_ATTR_SKILL_4,			// 技能4
	//	PET_DETAIL_ATTR_SKILL_5,			// 技能5
	//	PET_DETAIL_ATTR_SKILL_6,			// 技能6
	//	PET_DETAIL_ATTR_SKILL_7,			// 技能7
	//	PET_DETAIL_ATTR_SKILL_8,			// 技能8
	//	PET_DETAIL_ATTR_SKILL_9,			// 技能9
	//	PET_DETAIL_ATTR_SKILL_10,			// 技能10
	//	PET_DETAIL_ATTR_SKILL_11,			// 技能11


	//	PET_DETAIL_ATTR_SAVVY,				// 悟性
	//	PET_DETAIL_ATTR_GROWRATE,			// 成长率
	//	PET_DETAIL_ATTR_SEX,				// 性别
	//	PET_DETAIL_ATTR_NUMBERS
	//};

	//enum HorseState
	//{
	//	//正常状态
	//	HorseState_Normal,
	//	//交配中，锁定，不能操作
	//	HorseState_Mating
	//};
	class WGDetailOtherOnlineAttrib_Horse :
		public Packet
	{
	public:
		WGDetailOtherOnlineAttrib_Horse( ){
			m_Flags.m_uHighFlags	=	0;
			m_Flags.m_uLowFlags		=	0;
			m_ExtraInfoLength		=	0;
			memset(m_ExtraInfoData, 0, MAX_EXTRAINFO_LENGTH);
			memset( m_szNickName, 0, sizeof(m_szNickName) );
			memset( m_szName, 0, sizeof(m_szName) );

			m_iHorseState = HorseState_Normal;
		}
		virtual ~WGDetailOtherOnlineAttrib_Horse( ){}

		//公用继承接口
		virtual BOOL			Read( SocketInputStream& iStream ) ;
		virtual BOOL			Write( SocketOutputStream& oStream )const ;
		virtual UINT			Execute( Player* pPlayer ) ;

		virtual PacketID_t		GetPacketID()const { return PACKET_WG_DETAILOTHERONLINEATTRIB_HORSE; }
		virtual UINT			GetPacketSize()const 
		{
			UINT uSize = sizeof(PET_GUID_t) + sizeof(Flag64) + sizeof(INT) + sizeof(INT);
			UINT i;
			for ( i = 0; i < PET_DETAIL_ATTR_NUMBERS; i++ )
			{
				if(m_Flags.isSetBit(i))
				{
					switch ( i )
					{
					case PET_DETAIL_ATTR_SPOUSE_GUID:
						uSize += sizeof(PET_GUID_t);
						break;
					case PET_DETAIL_ATTR_OBJ_ID:
						uSize += sizeof(ObjID_t);
						break;
					case PET_DETAIL_ATTR_NAME:
						uSize += sizeof(BYTE) + m_byNameSize;
						break;
					case PET_DETAIL_ATTR_NICK_NAME:
						uSize += sizeof(BYTE) + m_byNickNameSize;
						break;
					case PET_DETAIL_ATTR_GENERATION:
					case PET_DETAIL_ATTR_HAPPINESS:
						uSize += sizeof(BYTE);
						break;

					case PET_DETAIL_ATTR_SKILL_0:
					case PET_DETAIL_ATTR_SKILL_1:
					case PET_DETAIL_ATTR_SKILL_2:
					case PET_DETAIL_ATTR_SKILL_3:
					case PET_DETAIL_ATTR_SKILL_4:
					case PET_DETAIL_ATTR_SKILL_5:
					case PET_DETAIL_ATTR_SKILL_6:
					case PET_DETAIL_ATTR_SKILL_7:
					case PET_DETAIL_ATTR_SKILL_8:
					case PET_DETAIL_ATTR_SKILL_9:
					case PET_DETAIL_ATTR_SKILL_10:
					case PET_DETAIL_ATTR_SKILL_11:

						uSize += sizeof( _PET_SKILL );
						break;
					default:
						uSize += sizeof( UINT );	
						break;
					}
				}
			}

			uSize += sizeof(BYTE);
			uSize += m_ExtraInfoLength;
			return uSize;
		}

	public:
		PET_GUID_t				GetGUID( VOID )const{ return m_GUID; }
		VOID					SetGUID( PET_GUID_t GUID ){ m_GUID = GUID; }

		INT						GetTradeIndex( VOID )const{ return m_nTradeIndex; }
		VOID					SetTradeIndex( INT nIndex ){ m_nTradeIndex = nIndex; }

		Flag64					GetFlags( VOID )const{ return m_Flags; }

		BOOL					IsUpdateAttrib( ENUM_PET_DETAIL_ATTR eAttrib )const{ return m_Flags.isSetBit((INT)eAttrib)?(TRUE):(FALSE); }
		VOID					SetUpdateAttrib( ENUM_PET_DETAIL_ATTR eAttrib, BOOL bUpdate ){ m_Flags.UpdateBits((INT)eAttrib,bUpdate); }

		VOID					SetPlayerID(ObjID_t id) { m_ObjID = id; SetUpdateAttrib(PET_DETAIL_ATTR_OBJ_ID,TRUE); }
		ObjID_t					GetPlayerID(VOID)const { return m_ObjID; }

		VOID					SetDataID(INT id) { m_nDataID = id; SetUpdateAttrib(PET_DETAIL_ATTR_DATA_ID,TRUE); }
		INT						GetDataID(VOID)const { return m_nDataID; }

		VOID					SetName( const CHAR *pszName )
		{
			m_byNameSize = (BYTE)(strlen( pszName ));
			strncpy( m_szName, pszName, MAX_CHARACTER_NAME-1 );
			SetUpdateAttrib(PET_DETAIL_ATTR_NAME,TRUE);
		}

		const CHAR*				GetName( VOID )const;

		const CHAR*				GetNickName() const;
		VOID					SetNickName( const CHAR* pszNickName )
		{
			m_byNickNameSize = (BYTE)(strlen( pszNickName ));
			strncpy( m_szNickName, pszNickName, MAX_CHARACTER_NAME-1 );
			SetUpdateAttrib(PET_DETAIL_ATTR_NICK_NAME,TRUE);
		}

		INT						GetAIType( VOID )const{ return m_nAIType; }
		VOID					SetAIType( INT nAIType ){ m_nAIType = nAIType; SetUpdateAttrib(PET_DETAIL_ATTR_AI_TYPE, TRUE); }

		PET_GUID_t				GetSpouseGUID( VOID )const{ return m_SpouseGUID; }
		VOID					SetSpouseGUID( PET_GUID_t guid ){ m_SpouseGUID = guid; SetUpdateAttrib(PET_DETAIL_ATTR_SPOUSE_GUID, TRUE); }

		INT						GetLevel( VOID )const{ return m_nLevel; }
		VOID					SetLevel( INT nLevel ){ m_nLevel = nLevel; SetUpdateAttrib(PET_DETAIL_ATTR_LEVEL, TRUE); }

		INT						GetExp( VOID )const{ return m_nExp; }
		VOID					SetExp( INT nExp ){ m_nExp = nExp; SetUpdateAttrib(PET_DETAIL_ATTR_EXP, TRUE ); }

		INT						GetHP( VOID )const{ return m_nHP; }
		VOID					SetHP( INT nHP ){ m_nHP = nHP; SetUpdateAttrib(PET_DETAIL_ATTR_HP, TRUE ); }

		INT						GetHPMax( VOID )const{ return m_nHPMax; }
		VOID					SetHPMax( INT nHPMax ){ m_nHPMax = nHPMax; SetUpdateAttrib(PET_DETAIL_ATTR_HPMAX, TRUE ); }

		INT						GetLife( VOID )const{ return m_nLife; }
		VOID					SetLife( INT nLife ){ m_nLife = nLife; SetUpdateAttrib(PET_DETAIL_ATTR_LIFE, TRUE ); }

		BYTE					GetGeneration( VOID )const{ return m_byGeneration; }
		VOID					SetGeneration( BYTE byGeneration ){ m_byGeneration = byGeneration; SetUpdateAttrib(PET_DETAIL_ATTR_GENERATION, TRUE ); }

		BYTE					GetHappiness( VOID )const{ return m_byHappiness; }
		VOID					SetHappiness( BYTE byHappiness ){ m_byHappiness = byHappiness; SetUpdateAttrib(PET_DETAIL_ATTR_HAPPINESS, TRUE ); }

		/*INT						GetAtt_Physics( VOID )const{ return m_nAtt_Physics; }
		VOID					SetAtt_Physics( INT nAtt_Physics ){ m_nAtt_Physics = nAtt_Physics; SetUpdateAttrib(PET_DETAIL_ATTR_ATT_PHYSICS, TRUE ); }*/

		INT						GetAtt_Near( VOID )const{ return m_nAtt_Near; }
		VOID					SetAtt_Near( INT nAtt_Near ){ m_nAtt_Near = nAtt_Near; SetUpdateAttrib(PET_DETAIL_ATTR_ATT_NEAR, TRUE ); }
		INT						GetAtt_Far( VOID )const{ return m_nAtt_Far; }
		VOID					SetAtt_Far( INT nAtt_Far ){ m_nAtt_Far = nAtt_Far; SetUpdateAttrib(PET_DETAIL_ATTR_ATT_FAR, TRUE ); }

		INT						GetAtt_MagicNear( VOID )const{ return m_nAtt_MagicNear; }
		INT						GetAtt_MagicFar( VOID )const{ return m_nAtt_MagicFar; }

		VOID					SetAtt_MagicNear( INT nAtt_MagicNear ){ m_nAtt_MagicNear = nAtt_MagicNear; SetUpdateAttrib(PET_DETAIL_ATTR_ATT_MAGIC_NEAR, TRUE ); }
		VOID					SetAtt_MagicFar( INT nAtt_MagicFar ){ m_nAtt_MagicFar = nAtt_MagicFar; SetUpdateAttrib(PET_DETAIL_ATTR_ATT_MAGIC_FAR, TRUE ); }

		/*INT						GetDef_Physics( VOID )const{ return m_nDef_Physics; }
		VOID					SetDef_Physics( INT nDef_Physics ){ m_nDef_Physics = nDef_Physics; SetUpdateAttrib(PET_DETAIL_ATTR_DEF_PHYSICS, TRUE ); }*/
		INT						GetDef_Near( VOID )const{ return m_nDef_Near; }
		VOID					SetDef_Near( INT nDef_Near ){ m_nDef_Near = nDef_Near; SetUpdateAttrib(PET_DETAIL_ATTR_DEF_NEAR, TRUE ); }
		INT						GetDef_Far( VOID )const{ return m_nDef_Far; }
		VOID					SetDef_Far( INT nDef_Far ){ m_nDef_Far = nDef_Far; SetUpdateAttrib(PET_DETAIL_ATTR_DEF_FAR, TRUE ); }

		INT						GetDef_MagicNear( VOID )const{ return m_nDef_MagicNear; }
		INT						GetDef_MagicFar( VOID )const{ return m_nDef_MagicFar; }

		VOID					SetDef_MagicNear( INT nDef_MagicNear ){ m_nDef_MagicNear = nDef_MagicNear; SetUpdateAttrib(PET_DETAIL_ATTR_DEF_MAGIC_NEAR, TRUE ); }
		VOID					SetDef_MagicFar( INT nDef_MagicFar ){ m_nDef_MagicFar = nDef_MagicFar; SetUpdateAttrib(PET_DETAIL_ATTR_DEF_MAGIC_FAR, TRUE ); }

		INT						GetHit( VOID )const{ return m_nHit; }
		VOID					SetHit( INT nHit ){ m_nHit = nHit; SetUpdateAttrib(PET_DETAIL_ATTR_HIT, TRUE ); }

		INT						GetMiss( VOID )const{ return m_nMiss; }
		VOID					SetMiss( INT nMiss ){ m_nMiss = nMiss; SetUpdateAttrib(PET_DETAIL_ATTR_MISS, TRUE ); }

		INT						GetCritical( VOID )const{ return m_nCritical; }
		VOID					SetCritical( INT nCritical ){ m_nCritical = nCritical; SetUpdateAttrib(PET_DETAIL_ATTR_CRITICAL, TRUE ); }

		INT						GetModelID( VOID )const{ return m_nModelID; }
		VOID					SetModelID( INT nModelID ){ m_nModelID = nModelID; SetUpdateAttrib(PET_DETAIL_ATTR_MODELID, TRUE ); }

		INT						GetMountID( VOID )const{ return m_nMountID; }
		VOID					SetMountID( INT nMountID ){ m_nMountID = nMountID; SetUpdateAttrib(PET_DETAIL_ATTR_MOUNTID, TRUE ); }

		INT						GetStrPerception( VOID )const{ return m_StrPerception; }
		VOID					SetStrPerception(INT StrPerception ){ m_StrPerception = StrPerception; SetUpdateAttrib(PET_DETAIL_ATTR_STRPERCEPTION, TRUE ); }

		INT						GetConPerception( VOID )const{ return m_ConPerception; }
		VOID					SetConPerception(INT ConPerception ){ m_ConPerception = ConPerception; SetUpdateAttrib(PET_DETAIL_ATTR_CONPERCEPTION, TRUE ); }

		INT						GetDexPerception( VOID )const{ return m_DexPerception; }
		VOID					SetDexPerception(INT  DexPerception ){ m_DexPerception = DexPerception; SetUpdateAttrib(PET_DETAIL_ATTR_DEXPERCEPTION, TRUE ); }

		/*INT						GetSprPerception( VOID )const{ return m_SprPerception; }
		VOID					SetSprPerception(INT SprPerception ){ m_SprPerception = SprPerception; SetUpdateAttrib(PET_DETAIL_ATTR_SPRPERCEPTION, TRUE ); }*/

		INT						GetIntPerception( VOID )const{ return m_IntPerception; }
		VOID					SetIntPerception(INT  IntPerception ){ m_IntPerception = IntPerception; SetUpdateAttrib(PET_DETAIL_ATTR_INTPERCEPTION, TRUE ); }

		INT						GetStr( VOID )const{ return m_Str; }
		VOID					SetStr( INT Str ){ m_Str = Str; SetUpdateAttrib(PET_DETAIL_ATTR_STR, TRUE ); }

		INT						GetCon( VOID )const{ return m_Con; }
		VOID					SetCon( INT Con ){ m_Con = Con; SetUpdateAttrib(PET_DETAIL_ATTR_CON, TRUE ); }

		INT						GetDex( VOID )const{ return m_Dex; }
		VOID					SetDex( INT  Dex ){ m_Dex = Dex; SetUpdateAttrib(PET_DETAIL_ATTR_DEX, TRUE ); }

		/*INT						GetSpr( VOID )const{ return m_Spr; }
		VOID					SetSpr( INT Spr ){ m_Spr = Spr; SetUpdateAttrib(PET_DETAIL_ATTR_SPR, TRUE ); }*/

		INT						GetInt( VOID )const{ return m_Int; }
		VOID					SetInt( INT  Int ){ m_Int = Int; SetUpdateAttrib(PET_DETAIL_ATTR_INT, TRUE ); }

		INT						GetGenGu( VOID )const{ return m_GenGu; }
		VOID					SetGenGu( INT  nGenGu ){ m_GenGu = nGenGu; SetUpdateAttrib(PET_DETAIL_ATTR_GENGU, TRUE ); }

		INT						GetRemainPoint( VOID )const{ return m_nRemainPoint; }
		VOID					SetRemainPoint( INT nRemainPoint ){ m_nRemainPoint = nRemainPoint; SetUpdateAttrib(PET_DETAIL_ATTR_POINT_REMAIN, TRUE ); }

		const _PET_SKILL		*GetSkill( UINT uIndex )const{ return ((uIndex<PET_MAX_SKILL_COUNT)?(&(m_aSkill[uIndex])):(NULL)); }
		VOID					SetSkill( UINT uIndex, const _PET_SKILL *pSkill )
		{
			if ( pSkill != NULL && uIndex < PET_MAX_SKILL_COUNT )
			{
				m_aSkill[uIndex] = *pSkill;
				SetUpdateAttrib( (ENUM_PET_DETAIL_ATTR)(uIndex + PET_DETAIL_ATTR_SKILL_0), TRUE );
			}
			else
			{
				Assert( (pSkill != NULL && uIndex < PET_MAX_SKILL_COUNT) && "WGDetailOtherOnlineAttrib_Horse::SetSkill" );
			}
		}

		BYTE					GetExtraInfoLength(VOID) const {return m_ExtraInfoLength;}
		VOID					SetExtraInfoLength(BYTE ExtraInfoLength) {m_ExtraInfoLength = ExtraInfoLength;}

		BYTE*					GetExtraInfoData(VOID) {return m_ExtraInfoData;}
		VOID					SetExtraInfoData(BYTE* ExtraInfoData)
		{
			memcpy(m_ExtraInfoData, ExtraInfoData, m_ExtraInfoLength*sizeof(BYTE));
		}

		INT  GetGrowRate() const { return m_iGrowRate; }
		VOID SetGrowRate(INT val) { m_iGrowRate = val; SetUpdateAttrib(PET_DETAIL_ATTR_GROWRATE, TRUE );}
		INT	 GetSavvy() const { return m_iSavvy; }
		VOID SetSavvy(INT val) { m_iSavvy = val; SetUpdateAttrib(PET_DETAIL_ATTR_SAVVY, TRUE );}
		INT  GetHorseState() const { return m_iHorseState; }
		VOID SetHorseState(INT val) { m_iHorseState = val; }
		INT	 GetSex() const { return m_iSex; }
		VOID SetSex(INT val) { m_iSex = val; SetUpdateAttrib(PET_DETAIL_ATTR_SEX, TRUE );}

	private:
		PET_GUID_t		m_GUID;										// ID
		INT				m_nTradeIndex;								// 交易用到的索引值

		Flag64			m_Flags;									// 每个位表示一个属性是否要刷新 ENUM_DETAIL_ATTRIB

		ObjID_t			m_ObjID;									// 所有Obj类型的ObjID
		INT				m_nDataID;									// 模型ID,宠物类型
		BYTE			m_byNameSize;								// 名称长度,不包括最后的'\0'
		BYTE			m_byNickNameSize;							// 昵称长度,不包括最后的'\0'
		CHAR			m_szName[MAX_CHARACTER_NAME];				// 名称
		CHAR			m_szNickName[MAX_CHARACTER_NAME];			// 昵称
		INT				m_nAIType;									// 性格
		PET_GUID_t		m_SpouseGUID;								// 配偶的GUID
		INT				m_nLevel;									// 等级
		INT				m_nExp;										// 经验
		INT				m_nHP;										// 血当前值
		INT				m_nHPMax;									// 血最大值
		INT				m_iHorseState;								// 马当前所处的状态

		INT				m_nLife;									// 当前寿命
		BYTE			m_byGeneration;								// 几代宠
		BYTE			m_byHappiness;								// 快乐度

		INT				m_nAtt_Near;
		INT				m_nAtt_Far;

		INT				m_nAtt_MagicNear;							// 近程内功攻击力
		INT				m_nAtt_MagicFar;							// 近程外功攻击力

		INT				m_nDef_Near;
		INT				m_nDef_Far;

		INT				m_nDef_MagicNear;							// 近程内功防御力
		INT				m_nDef_MagicFar;							// 近程外功防御力

		INT				m_nHit;										// 命中率
		INT				m_nMiss;									// 闪避率
		INT				m_nCritical;								// 会心率

		INT				m_nModelID;									// 外形
		INT				m_nMountID;									// 座骑ID

		INT				m_StrPerception;							// 力量资质
		INT				m_ConPerception;							// 体力资质
		INT 			m_DexPerception;							// 身法资质
		INT 			m_IntPerception;							// 定力资质

		INT				m_Str;										// 力量
		INT				m_Con;										// 体力
		INT 			m_Dex;										// 身法
		INT 			m_Int;										// 定力
		INT 			m_GenGu;									// 根骨
		INT				m_iSavvy;									// 悟性
		INT				m_iGrowRate;								// 成长率
		INT				m_nRemainPoint;								// 潜能点
		INT				m_iSex;										// 性别

		_PET_SKILL		m_aSkill[PET_MAX_SKILL_COUNT];				// 技能列表

		BYTE			m_ExtraInfoLength;							// 附加信息长度
		BYTE			m_ExtraInfoData[MAX_EXTRAINFO_LENGTH];		// 附加信息内容


	};

	class WGDetailOtherOnlineAttrib_HorseFactory : public PacketFactory 
	{
	public:
		Packet*		CreatePacket() { return new WGDetailOtherOnlineAttrib_Horse() ; }
		PacketID_t	GetPacketID()const { return PACKET_WG_DETAILOTHERONLINEATTRIB_HORSE; }
		UINT		GetPacketMaxSize()const
		{
			UINT uSize = sizeof(WGDetailOtherOnlineAttrib_Horse) - sizeof(Packet) ;
			return uSize;
		}
	};

	class WGDetailOtherOnlineAttrib_HorseHandler 
	{
	public:
		static UINT Execute( WGDetailOtherOnlineAttrib_Horse* pPacket, Player* pPlayer ) ;
	};


}


#endif

