/********************************************************************************
 *	文件名：	GCReturnTeamFollow.h
 *	全路径：	d:\Prj\Common\Packets\GCReturnTeamFollow.h
 *	创建人：	胡繁
 *	创建时间：	2005 年 11 月 23 日	18:03
 *
 *	功能说明：	队员关于组队跟随的操作结果返回给相关队友
 *	修改记录：
*********************************************************************************/
#ifndef _GC_RETURNTEAMFOLLOW_H_
#define _GC_RETURNTEAMFOLLOW_H_

#include "Type.h"
#include "Packet.h"
#include "PacketFactory.h"

namespace Packets
{
	class GCReturnTeamFollow:	public Packet
	{
	public:
		GCReturnTeamFollow(){};
		virtual		~GCReturnTeamFollow(){};

		//公用接口
		virtual BOOL			Read( SocketInputStream& iStream );
		virtual BOOL			Write( SocketOutputStream& oStream ) const;
		virtual UINT			Execute( Player* pPlayer );

		virtual PacketID_t		GetPacketID() const { return PACKET_GC_RETURN_TEAMFOLLOW; }
		virtual UINT			GetPacketSize() const { return sizeof(UCHAR) + sizeof(GUID_t); }

	public :
		VOID					SetReturn( TEAM_FOLLOW_RESULT Ret ) { m_Return = Ret; }
		TEAM_FOLLOW_RESULT		GetReturn( ) { return (TEAM_FOLLOW_RESULT)m_Return; }

		VOID					SetGUID( GUID_t guid ) { m_GUID = guid; }
		GUID_t					GetGUID( ) { return m_GUID; }

	private :
		UCHAR					m_Return;
		GUID_t					m_GUID;
	};

	class GCReturnTeamFollowFactory: public	PacketFactory
	{
	public:
		Packet*		CreatePacket() { return new GCReturnTeamFollow(); }
		PacketID_t	GetPacketID() const			{ return PACKET_GC_RETURN_TEAMFOLLOW; }
		UINT		GetPacketMaxSize() const	{ return sizeof(UCHAR) + sizeof(GUID_t); }
	};

	class GCReturnTeamFollowHandler
	{
	public:
		static UINT Execute(GCReturnTeamFollow* pPacket,Player* pPlayer);
	};

}

using namespace Packets;

#endif // _GC_RETURNTEAMFOLLOW_H_
