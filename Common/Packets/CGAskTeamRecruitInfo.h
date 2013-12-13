/********************************************************************************
 *	文件名：	CGAskTeamRecruitInfo.h
 *	创建人：	王勇鸷
 *	创建时间：	2008 年 5 月 14 日	17:57
 *
 *	功能说明：	请求得到组队征兵信息
 *	修改记录：
*********************************************************************************/

#ifndef _CG_ASK_TEAM_RECRUIT_INFO_H_
#define _CG_ASK_TEAM_RECRUIT_INFO_H_

#include "Type.h"
#include "Packet.h"
#include "PacketFactory.h"
#include "GameStruct_Team.h"

namespace Packets
{
	class CGAskTeamRecruitInfo:	public Packet
	{
	public:
		CGAskTeamRecruitInfo(){};
		virtual		~CGAskTeamRecruitInfo(){};

		//公用接口
		virtual BOOL			Read( SocketInputStream& iStream ) ;
		virtual BOOL			Write( SocketOutputStream& oStream )const ;
		virtual UINT			Execute( Player* pPlayer ) ;

		virtual PacketID_t		GetPacketID()const { return PACKET_CG_ASK_TEAM_RECRUIT ; }
		virtual UINT			GetPacketSize() const
		{
			UINT size = sizeof(UCHAR) + sizeof(GUID_t);
			return size;
		}

		VOID				SetType(UCHAR Type) { m_Type=Type; }
		UCHAR				GetType() { return m_Type; }
		
		VOID				SetGUID(GUID_t id) { m_GUID=id; }
		GUID_t				GetGUID() { return m_GUID; }

	public :

		//LEADER_RECRUIT = 0,		//队长请求
		//MEMBER_RECRUIT ,			//队员请求
		UCHAR					m_Type;
		GUID_t					m_GUID;	

	};

	class CGAskTeamRecruitInfoFactory: public PacketFactory
	{
	public:
		Packet*		CreatePacket() { return new CGAskTeamRecruitInfo() ; }
		PacketID_t	GetPacketID()const			{ return PACKET_CG_ASK_TEAM_RECRUIT ; }
		UINT		GetPacketMaxSize()	const	
		{ 
			UINT size = sizeof(UCHAR) + sizeof(GUID_t);

			return size;
		}					
	};

	class CGAskTeamRecruitInfoHandler
	{
	public:
		static UINT Execute(CGAskTeamRecruitInfo* pPacket,Player* pPlayer);
	};
}

using namespace Packets;

#endif// 
