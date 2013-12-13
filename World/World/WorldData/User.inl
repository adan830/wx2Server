/********************************************************************************
 *	文件名：	User.inl
 *	全路径：	d:\Prj\World\World\WorldData\User.inl
 *	创建人：	胡繁
 *	创建时间：	2006 年 3 月 3 日	12:18
 *
 *	功能说明：	一些 USER 的 inline 函数
 *	修改记录：
*********************************************************************************/

#ifndef __USER_INL__
#define __USER_INL__

#include "Config.h"

// 取得玩家的 UserID
ID_t USER::GetUserID() const
{
	return m_UserID;
}

// 设置玩家的 UserID
VOID USER::SetUserID( ID_t id )
{
	m_UserID = id;
}

// 取得玩家状态
UINT USER::UserStatus() const
{
	return m_UserStatus;
};

// 设置玩家状态
VOID USER::SetUserStatus( UINT uStatus )
{
	if( uStatus > US_NONE && uStatus < US_SIZE )
	{
		m_UserStatus = uStatus;
	}
	else
	{
		Assert( FALSE && "uStatus Exception!" );
	}
}

// 取得完整玩家数据
FULLUSERDATA* USER::GetFullUserData() const
{
	return m_pFullUserData;
}

// 设置完整玩家数据
VOID USER::SetFullUserData( FULLUSERDATA* pData )
{
	m_pFullUserData = pData;
}

// 取得玩家的 ServerID
ID_t USER::GetServerID() const
{
	if( GetSceneID()<0 ) return INVALID_ID ;
	return g_Config.SceneID2ServerID(GetSceneID()) ;
}

// 取得玩家 PlayerID
PlayerID_t USER::GetPlayerID() const
{
	return m_PlayerID;
}

// 设置玩家 PlayerID
VOID USER::SetPlayerID( PlayerID_t pid )
{
	m_PlayerID = pid;
}

// 取得玩家 GUID
GUID_t USER::GetGUID() const
{
	return m_SimpleData.m_GUID;
}

// 设置玩家 GUID
VOID USER::SetGUID( GUID_t guid )
{
	m_SimpleData.m_GUID = guid;
}

// 取得玩家 SceneID
SceneID_t USER::GetSceneID() const
{
	return m_SceneID;
}

// 设置玩家 SceneID
VOID USER::SetSceneID( SceneID_t SceneID )
{
	m_SceneID = SceneID;
}

// 得到玩家常用数据
const USER_SIMPLE_DATA* USER::GetUserSimpleData() const
{
	return &m_SimpleData;
}

// 取得玩家名字
const CHAR* USER::GetName() const
{
	return m_SimpleData.m_Name;
}

// 设置玩家名字
VOID USER::SetName( const CHAR* szName )
{
	Assert(szName);
	strncpy( m_SimpleData.m_Name, szName, sizeof(m_SimpleData.m_Name)-1 );
}

// 取得玩家性别
UINT USER::GetSex() const
{
	return m_SimpleData.m_uSex;
}

// 设置玩家性别
VOID USER::SetSex( UINT uSex )
{
	m_SimpleData.m_uSex = uSex;
}

// 取得角色所在的国家
INT USER::GetCountry() const
{
	return m_SimpleData.m_nCountry;
}

// 设置角色所在的国家
VOID USER::SetCountry(INT nCountry)
{
	m_SimpleData.m_nCountry = nCountry;
}

// 取得玩家的门派号
INT USER::GetMenpai() const
{
	return m_SimpleData.m_uMenPai;
}

// 设置玩家的门派号
VOID USER::SetMenpai(INT nMenpai)
{
	m_SimpleData.m_uMenPai = nMenpai;
}

// 得到玩家等级
INT USER::GetLevel() const
{
	return m_SimpleData.m_nLevel;
}

// 设置玩家等级
VOID USER::SetLevel(INT nLevel)
{
	m_SimpleData.m_nLevel = nLevel;
}

// 得到玩家的头像
INT USER::GetPortrait() const
{
	return m_SimpleData.m_nPortrait;
}

// 设置玩家头像
VOID USER::SetPortrait(INT nPortrait)
{
	m_SimpleData.m_nPortrait = nPortrait;
}

// 得到脸部模型
UCHAR USER::GetFaceModel() const
{
	return m_SimpleData.m_uFaceMeshID;
}

// 设置脸部模型
VOID USER::SetFaceModel(UCHAR uFaceMeshID)
{
	m_SimpleData.m_uFaceMeshID = uFaceMeshID;
}

// 得到头发模型
UCHAR USER::GetHairModel() const
{
	return m_SimpleData.m_uHairMeshID;
}

// 设置头发模型
VOID USER::SetHairModel(UCHAR uHairMeshID)
{
	m_SimpleData.m_uHairMeshID = uHairMeshID;
}

// 得到发色
UINT USER::GetHairColor() const
{
	return m_SimpleData.m_uHairColor;
}

// 设置发色
VOID USER::SetHairColor(UINT uHairColor)
{
	m_SimpleData.m_uHairColor = uHairColor;
}

// 设置身上Money
VOID USER::SetMoney(UINT Money)
{
	m_SimpleData.m_uMoney = Money;
}

// 得到身上Money
UINT USER::GetMoney() const
{
	return m_SimpleData.m_uMoney;
}

// 设置银行Money
VOID USER::SetBankMoney(UINT Money)
{
	m_SimpleData.m_uBankMoney = Money;
}

// 得到银行Money
UINT USER::GetBankMoney() const
{
	return m_SimpleData.m_uBankMoney;
}
// 取得玩家的队伍号
TeamID_t USER::GetTeamID() const
{
	return m_TeamID;
}

// 设置玩家队伍号
VOID USER::SetTeamID( TeamID_t tid )
{
	m_TeamID = tid;
}

// 取得玩家的称号
const CHAR* USER::GetTitle() const
{
	return m_SimpleData.m_szTitle;
}

// 设置玩家的称号
VOID USER::SetTitle(const CHAR* szTitle)
{
	Assert(szTitle);
	strncpy( m_SimpleData.m_szTitle, szTitle, MAX_CHARACTER_TITLE-1 );
}

// 得到玩家帮会 ID
GuildID_t USER::GetGuildID() const
{
	return m_SimpleData.m_GuildID;
}

// 设置玩家帮会 ID
VOID USER::SetGuildID(GuildID_t gid)
{
	m_SimpleData.m_GuildID = gid;
}

// 设置玩家帮会名字
VOID USER::SetGuildName(const CHAR *szGuildName)
{
    memcpy(&m_SimpleData.m_szGuildName[0], szGuildName, MAX_GUILD_NAME_SIZE);
}

// 得到玩家帮会名字
const CHAR* USER::GetGuildName() const
{
    return m_SimpleData.m_szGuildName;
}

// 设置玩家家族名字
VOID USER::SetFamilyName(const CHAR *szFamilyName)
{
    memcpy(&m_SimpleData.m_szFamilyName[0], szFamilyName, MAX_GUILD_FAMILY_NAME_SIZE);
}

// 设置帮会邀请认证信息
VOID USER::SetGuildInviteKey(const USER_GUILD_DATA &Key)
{
    m_GuildData.m_bInvit = Key.m_bInvit;
    m_GuildData.m_GuildId= Key.m_GuildId;
    m_GuildData.m_iTime  = Key.m_iTime;
}

// 判断此前是否已被邀请
BOOL USER::BeInGuildInvite(uint uTime)
{

    if (m_GuildData.m_bInvit)
    {
        if ((uTime-m_GuildData.m_iTime)> USER_GUILD_DATA::TIME_LIMIT)//超时
        {
            CleanUpGuildInviteKey();
            return TRUE;
        }
    }

    return m_GuildData.m_bInvit;
}

// 对照帮会邀请认证信息
BOOL USER::CompareGuildInviteKey(const GuildID_t GuildId)
{
    return (GuildId == m_GuildData.m_GuildId)?TRUE:FALSE; 
}

// 清空帮会邀请认证信息
VOID USER::CleanUpGuildInviteKey()
{
    m_GuildData.m_bInvit = FALSE;
    m_GuildData.m_GuildId= INVALID_GUILD_ID;
    m_GuildData.m_iTime  = -1;
}

// 得到玩家创建的聊天频道号
ChannelID_t USER::GetChannelID() const
{
	return m_ChannelID;
}

// 设置玩家创建的聊天频道号
VOID USER::SetChannelID( ChannelID_t cid )
{
	m_ChannelID = cid;
}

// 得到用户验证码
UINT USER::GetKey() const
{
	return m_uKey;
}

// 设置用户验证码
VOID USER::SetKey( UINT uKey )
{
	m_uKey = uKey;
}

// 清除帮会数据
VOID USER::CleanUpGuildData()
{
	m_SimpleData.m_GuildID = INVALID_ID;
	m_GuildData.CleanUp();
}

// 清除玩家关系数据
VOID USER::CleanUpRelationData()
{
	m_RelationData.CleanUp();
}

// 取得玩家的心情
const CHAR* USER::GetMood() const
{
	return m_RelationData.m_szMood;
}

// 保存心情
VOID USER::SetMood( const CHAR* szMood )
{
	Assert( szMood );
	strncpy( m_RelationData.m_szMood, szMood, MOOD_DATA_SIZE-1 );
}

// 保存设置
VOID USER::SetSettings(USHORT uSettings)
{
	m_RelationData.m_Flag.m_wFlags = uSettings;
}

// 是否拒绝被加为好友
BOOL USER::IsCannotAddFriend()
{
	return m_RelationData.m_Flag.isSetBit(GSF_CANNOT_ADD_FRIEND);
}

// 是否拒绝收发邮件
BOOL USER::IsCannotRecvMail()
{
	return m_RelationData.m_Flag.isSetBit(GSF_CANNOT_RECV_MAIL);
}

// 是否拒绝陌生人的邮件
BOOL USER::IsCannotRecvStrangerMail()
{
	return m_RelationData.m_Flag.isSetBit(GSF_CANNOT_RECV_STRANGER_MAIL);
}

// 是否拒绝组队申请
BOOL USER::IsRefuseTeamInvite()
{
	return m_RelationData.m_Flag.isSetBit(GSF_REFUSE_TEAM_INVITE);
}


//取玩家账号
const CHAR*		USER::GetAccount()	const
{
	return m_SimpleData.m_Account;
}
//设置玩家账号
VOID	USER::SetAccount(const CHAR* pAccount)
{
	Assert(pAccount);
	strncpy(m_SimpleData.m_Account,pAccount,MAX_ACCOUNT_LENGTH-1);
}

#endif // __USER_INL__
