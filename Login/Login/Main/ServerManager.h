

#ifndef __SERVERMANAGER_H__
#define __SERVERMANAGER_H__

#include "Type.h"
#include "Config.h"
#include "ServerSocket.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "ServerPlayer.h"
#include "BillingPlayer.h"


#define WORLD_PLAYER_ID			0
#define BILLING_PLAYER_ID		1

//系统内可以拥有的最多的服务器端程序数量
#define MAX_SERVER 24


class ServerManager
{
public :
	ServerManager( ) ;
	~ServerManager( ) ;

	VOID				CleanUp( ) ;

	//初始化
	BOOL				Init( ) ;

	//总逻辑接口
	BOOL				Tick( ) ;

	//网络数据侦测
	BOOL				Select( ) ;
	//数据接收或者新连接接收
	BOOL				ProcessInputs( ) ;
	//数据发送
	BOOL				ProcessOutputs( ) ;
	//连接异常断开处理
	BOOL				ProcessExceptions( ) ;
	//消息处理
	BOOL				ProcessCommands( ) ;

	//逻辑处理
	virtual BOOL		HeartBeat( ) ;

	BOOL				ProcessCacheCommands( ) ;

	BOOL				RecvPacket( Packet*& pPacket, PlayerID_t& PlayerID, uint& Flag ) ;
	//重新调整缓存大小
	BOOL				ResizeCache( ) ;

public :
	//新连接注册（只有注册后的网络句柄才能接收数据）
	BOOL				AddServer( SOCKET fd ) ;
	//连接撤销
	BOOL				DelServer( SOCKET fd ) ;
	//断开连接后的清除回收处理
	BOOL				RemoveServer(PlayerID_t id) ;
	//获取指定编号的ServerPlayer 
	Player*				GetServerPlayer(PlayerID_t id);
	//连接到世界服务器端程序
	BOOL				ConnectWorldServer( ) ;
	//连接到Billing服务器程序
	BOOL				ConnectBillingServer( );

	//取WorldQueue用户，发送数据到World
	BOOL				SendQueuePlayerToWorld();
	BOOL				ResetQueuePos();
public :
	//******************************************************************************
    //通用接口
	//******************************************************************************

	//取得当前的服务器端程序ID
	ID_t				GetLoginID( ) ;
	//取得当前的服务器端程序信息
	_SERVER_DATA*		GetCurrentServerInfo( ) ;
	//取得指定的服务器端程序的信息
	_SERVER_DATA*		FindServerInfo( ID_t ServerID ) ;

	//判断指定的服务器端连接是否处于活动状态
	BOOL				IsWorldServerActive( ) ;
	BOOL				IsBillingServerActive( );

	//向此模块发送消息
	//此接口支持数据同步，即可以在不同线程内调用
	//此接口是其他场景向别的服务器发送消息的唯一接口
	BOOL				SendPacket( Packet* pPacket , 
									ID_t ServerID , 
									uint Flag=PF_NONE ) ;

	//设置某个场景中的人数
	VOID			SetScenePlayerCount( SceneID_t SceneID, INT count ){
		if( SceneID < 0 || SceneID>=MAX_SCENE ) return ;
		m_aScenePlayerCount[SceneID] = count ;
	};
	//读取某个场景中的人数
	INT				GetScenePlayerCount( SceneID_t SceneID ){
		if( SceneID < 0 || SceneID>=MAX_SCENE ) return 0 ;
		return m_aScenePlayerCount[SceneID] ;
	};

	INT					GetServerPlayerPoolSize( ID_t ServerID ) ;
	VOID				SetServerPlayerPoolSize( ID_t ServerID, INT nPlayerPoolSize ) ;

private :
	//
	//网络数据
	enum{
		SELECT_BAK = 0,	//当前系统中拥有的完整句柄数据
		SELECT_USE = 1,	//用于select调用的句柄数据
		SELECT_MAX = 2, //结构使用数量
	};
	fd_set			m_ReadFDs[SELECT_MAX];
	fd_set			m_WriteFDs[SELECT_MAX];
	fd_set			m_ExceptFDs[SELECT_MAX];
	
	timeval			m_Timeout[SELECT_MAX];

	SOCKET			m_MinFD;
	SOCKET			m_MaxFD;

	INT				m_nFDSize ;
	//网络数据
	//

	MyLock			m_Lock ;

	//当前用于侦听网络连接的Socket
	//ServerSocket*	m_pServerSocket ;
	//SOCKET			m_SocketID ;

	//当前服务器端程序的信息
	_SERVER_DATA*	m_pCurServerInfo ;

	//当前游戏世界中配置的所有服务器端成员, 
	//每个服务器端程序与其他所有服务器端程序都有一个对应的tcp连接
	//此数组的下标即为当前连接的PlayerID_t
	ServerPlayer	m_WorldPlayer;

	BillingPlayer	m_BillingPlayer;

	//快速查找数组
	//数组下标值是ServerID, 数组内容是ServerPlayerID(即：m_pServerPlayer[]的下标)
	PlayerID_t		m_pServerHash[MAX_SERVER] ;

	//每个逻辑场景内的人数
	INT				m_aScenePlayerCount[MAX_SCENE] ;//场景中人数

	//当前世界每个Server内使用的玩家池的数量，数组下标为ServerID ;
	INT				m_aServerPlayerPoolSize[MAX_SERVER] ;

	//消息缓存
	ASYNC_PACKET*			m_PacketQue ;
	uint					m_QueSize ;
	uint					m_Head ;
	uint					m_Tail ;
	BOOL					m_KickALL;

	uint			m_CurrentTime;
	INT				m_LogTurnTime;
public :
	TID						m_ThreadID ;
};

extern ServerManager* g_pServerManager ;

#endif
