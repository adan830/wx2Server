/********************************************************************************
 *	文件名：	GWEnterTeamFollowHandler.cpp
 *	全路径：	d:\Prj\World\World\Packets\GWEnterTeamFollowHandler.cpp
 *	创建人：	胡繁
 *	创建时间：	2005 年 11 月 23 日	15:39
 *
 *	功能说明：	
 *	修改记录：
*********************************************************************************/

#include "stdafx.h"
#include "GWEnterTeamFollow.h"

#include "Log.h"
#include "OnlineUser.h"
#include "Team.h"

uint GWEnterTeamFollowHandler::Execute( GWEnterTeamFollow* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	GUID_t guid = pPacket->GetGUID();

	USER* pUser = g_pOnlineUser->FindUser( guid );
	if ( pUser == NULL )
	{
		Assert(FALSE && "user not find!");
		return PACKET_EXE_CONTINUE;
	}

	if ( pUser->GetTeamID() == INVALID_ID )
	{
		Assert(FALSE && "isn't in a team!");
		return PACKET_EXE_CONTINUE;
	}

	Team* pTeam = g_pTeamList->GetTeam( pUser->GetTeamID() );
	if( pTeam==NULL )
	{
		Assert(FALSE && "team not found!");
		return PACKET_EXE_CONTINUE;
	}

	pTeam->AddFollowedMember(guid);

	Log::SaveLog( WORLD_LOGFILE, "GWEnterTeamFollow... GUID=%X start follow team.", guid);

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}
