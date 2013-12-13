// 好友消息结构
// fancy

#ifndef __GAMESTRUCT_MINORPASSWD_H__
#define __GAMESTRUCT_MINORPASSWD_H__

#include "Type.h"

class SocketInputStream;
class SocketOutputStream;

/////////////////////////////////////////////////////////////////////////////////

enum MINORPASSWD_REQUEST_TYPE
{
	MREQT_NONE							= 0,
	MREQT_PASSWDSETUP,									// 询问二级密码是否已经设置
	MREQT_DELETEPASSWDTIME,								// 询问是否处于强制解除阶段
	MREQT_SETPASSWD,									// 设置二级密码
	MREQT_MODIFYPASSWD,									// 修改二级密码
	MREQT_UNLOCKPASSWD,									// 二级密码解锁
	MREQT_DELETEPASSWD,									// 强制解除二级密码
	MREQT_CLEANPASSWD,									// 清空二级密码
	MREQT_SETPROTECTTYPE,								// 设置二级密码保护类型
	MREQT_SETPROTECTTIME,								// 设置上线保护时间
};

enum MINORPASSWD_RETURN_TYPE
{
	MRETT_NONE							= 0,
	MRETT_PASSWDSETUP,									// 二级密码是否已经设置
	MRETT_DELETEPASSWDTIME,								// 二级密码解除剩余时间（或者不在解除阶段）
	MRETT_SETPASSWDSUCC,								// 二级密码设置成功
	MRETT_MODIFYPASSWDSUCC,								// 二级密码修改成功
	MRETT_UNLOCKPASSWDSUCC,								// 二级密码解锁成功
	MRETT_DELETEPASSWDCANCEL,							// 强制解除二级密码失效
	MRETT_DELETEPASSWDSUCC,								// 二级密码强制解除成功
	MRETT_CLEANPASSWDSUCC,								// 清空二级密码成功
	MRETT_SETPASSWDPROTECT, 							// 设置保护类型成功
	MRETT_SETPROTECTTIMESUCC,    						// 设置上线保护时间成功

	MRETT_ERR_START,
	MRETT_ERR_SETPASSWDFAIL,							// 二级密码设置失败
	MRETT_ERR_MODIFYPASSWDFAIL,							// 二级密码修改失败
	MRETT_ERR_UNLOCKPASSWDFAIL,							// 二级密码解锁失败
	MRETT_ERR_DELETEPASSWDFAIL,							// 二级密码强制解除失败
	MRETT_ERR_CLEANPASSWDFAIL,					    	// 清空二级密码失败
    MRETT_ERR_SETPROTECTTIMEFAIL,                       // 设置上线保护时间失败
    MRETT_ERR_PASSWD,								    // 校验密码失败 
};

// 无参数
// MREQT_PASSWDSETUP
// MREQT_DELETEPASSWDTIME
// MREQT_DELETEPASSWD

// 输入一个密码
// MREQT_SETPASSWD
// MREQT_UNLOCKPASSWD
struct MINORPASSWD_PWD
{
	//数据
	UCHAR								m_uPasswdSize;
	CHAR								m_Passwd[MAX_PWD];		//二级密码

	//基本接口
	VOID								CleanUp( );
	UINT								GetSize( ) const;
	VOID								Read( SocketInputStream& iStream );
	VOID								Write( SocketOutputStream& oStream ) const;

	//数据应用接口
	UCHAR								GetPasswdSize( ) { return m_uPasswdSize; }

	const CHAR*							GetPasswd( ) { return m_Passwd; }
	VOID								SetPasswd( const CHAR* szPasswd )
	{
		Assert( szPasswd );
		strncpy(m_Passwd, szPasswd, sizeof(m_Passwd) - 1);
		m_uPasswdSize = (UCHAR)strlen(m_Passwd);
	}
};

// MREQT_MODIFYPASSWD
struct REQUEST_MINORPASSWD_MODIFY
{
	//数据
	UCHAR								m_uOldPasswdSize;
	CHAR								m_OldPasswd[MAX_PWD];	// 旧二级密码
	UCHAR								m_uNewPasswdSize;
	CHAR								m_NewPasswd[MAX_PWD];	// 新二级密码

	//基本接口
	VOID								CleanUp( );
	UINT								GetSize( ) const;
	VOID								Read( SocketInputStream& iStream );
	VOID								Write( SocketOutputStream& oStream ) const;

	//数据应用接口
	UCHAR								GetOldPasswdSize( ) { return m_uOldPasswdSize; }

	const CHAR*							GetOldPasswd( ) { return m_OldPasswd; }
	VOID								SetOldPasswd( const CHAR* szPasswd )
	{
		Assert( m_OldPasswd );
		strncpy(m_OldPasswd, szPasswd, sizeof(m_OldPasswd) - 1);
		m_uOldPasswdSize = (UCHAR)strlen(m_OldPasswd);
	}

	UCHAR								GetPasswdSize( ) { return m_uNewPasswdSize; }

	const CHAR*							GetNewPasswd( ) { return m_NewPasswd; }
	VOID								SetNewPasswd( const CHAR* szPasswd )
	{
		Assert( m_NewPasswd );
		strncpy(m_NewPasswd, szPasswd, sizeof(m_NewPasswd) - 1);
		m_uNewPasswdSize = (UCHAR)strlen(m_NewPasswd);
	}
};

// e.g.
// set minor password
// CGMinorPasswd Msg;
// CG_MINORPASSWD* pMinorPasswd = Msg.GetMinorPassword();
// pMinorPasswd->CleanUp();
// pMinorPasswd->m_Type = MREQT_SETPASSWD;
// pMinorPasswd->m_OnePasswd.CleanUp();
// pMinorPasswd->m_OnePasswd.SetPasswd( szPasswd );

struct CG_MINORPASSWD
{
	UCHAR								m_Type;				// enum MINORPASSWD_REQUEST_TYPE

	union
	{
		MINORPASSWD_PWD					m_OnePasswd;
		REQUEST_MINORPASSWD_MODIFY		m_ModifyPasswd;
        INT                             m_nFlag;            // 保护类型
        CHAR                            m_cTime;            // 上线保护时间
	};

	VOID								CleanUp( );
	UINT								GetSize( ) const;
	VOID								Read( SocketInputStream& iStream );
	VOID								Write( SocketOutputStream& oStream ) const;

};

/////////////////////////////////////////////////////////////////////////////////

// 无参数

// MRETT_SETPASSWDSUCC
// MRETT_MODIFYPASSWDSUCC
// MRETT_UNLOCKPASSWDSUCC
// MRETT_DELETEPASSWDCANCEL
// MRETT_DELETEPASSWDSUCC

// MRETT_ERR_SETPASSWDFAIL
// MRETT_ERR_MODIFYPASSWDFAIL
// MRETT_ERR_UNLOCKPASSWDFAIL
// MRETT_ERR_DELETEPASSWDFAIL

// MRETT_PASSWDSETUP
struct RETURN_MINORPASSWD_SETUP
{
	INT 								m_uFlag;			// 0 为未设置，1 为已设置

	//基本接口
	VOID								CleanUp( );
	UINT								GetSize( ) const;
	VOID								Read( SocketInputStream& iStream );
	VOID								Write( SocketOutputStream& oStream ) const;

	//数据应用接口
	INT 								GetSetupFlag( ) { return m_uFlag; }
	VOID								SetSetupFlag( INT uFlag ) { m_uFlag = uFlag; }
};

// MRETT_DELETEPASSWDTIME
struct RETURN_DELETE_MINORPASSWD_TIME
{
	UINT								m_uTime;			// 0 为未处于强制解除阶段，否则为强制解除的时间

	//基本接口
	VOID								CleanUp( );
	UINT								GetSize( ) const;
	VOID								Read( SocketInputStream& iStream );
	VOID								Write( SocketOutputStream& oStream ) const;

	//数据应用接口
	UINT								GetDeleteTime( ) { return m_uTime; }
	VOID								SetDeleteTime( UINT uTime ) { m_uTime = uTime; }
};

struct GC_MINORPASSWD
{
	UCHAR								m_Type;				// enum MINORPASSWD_RETURN_TYPE

	union
	{
		RETURN_MINORPASSWD_SETUP		m_ReturnSetup;
		RETURN_DELETE_MINORPASSWD_TIME	m_ReturnDeleteTime;
	};

	VOID								CleanUp( );
	UINT								GetSize( ) const;
	VOID								Read( SocketInputStream& iStream );
	VOID								Write( SocketOutputStream& oStream ) const;
};

struct MINORPASSWD_INFO                                 //密码保护数据结构
{
    enum PROTECT_TYPE
    {
        PROTECT_EQUIP = 1,                              //已经绑定的装备
        PROTECT_BANK  = 2,                              //仓库
        PROTECT_MONEY = 4,                              //金币使用
        PROTECT_STALL = 8,                              //摆摊和购买
        PROTECT_GUILD = 16,                             //帮会
    };

public:
    MINORPASSWD_INFO ()
    {
        m_nFlag             = 0;
        m_cProtectTime      = 3;                        //默认保护时间3min
        m_bUnProtect        = FALSE;
        //memset(m_szPasswd, 0, MAX_PWD);
    }

public:
    VOID            SetFlag( PROTECT_TYPE type ) { m_nFlag |= type; };
    VOID            SetFlag( INT nType ) { m_nFlag = nType; };
    BOOL            CompareFlag ( PROTECT_TYPE type ) { return type & m_nFlag; };

    VOID            SetProtectTime ( CHAR cTime ) { m_cProtectTime = cTime; };
    CHAR            GetProtectTime () { return m_cProtectTime; };

    VOID            SetProtectFlag (BOOL bFlag) { m_bUnProtect = bFlag; };
    BOOL            GetProtectFlag () { return m_bUnProtect; };
private:
    //CHAR			m_szPasswd[MAX_PWD];				//二级密码
    BOOL            m_bUnProtect;                       //是否暂时取消密码保护
    INT             m_nFlag;                            //保护分类
    CHAR            m_cProtectTime;                     //登录保护时间
};

//////////////////////////////////////////////////////////////////////////

#endif // __GAMESTRUCT_MINORPASSWD_H__
