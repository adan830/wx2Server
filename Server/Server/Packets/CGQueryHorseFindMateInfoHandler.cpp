/********************************************************************************
 *	创建人：	武文斌
 *	创建时间：	2008 年 5 月 20 日	
 *
 *	功能说明：	
 *	修改记录：
*********************************************************************************/

#include "stdafx.h"
#include "CGQueryHorseFindMateInfo.h"
#include "Log.h"
#include "GamePlayer.h"
#include "Scene.h"
#include "PacketFactoryManager.h"
#include "ServerManager.h"
#include "HorseFindMateModule.h"

namespace Packets
{

uint	CGQueryHorseFindMateInfoHandler::Execute(CGQueryHorseFindMateInfo* pPacket, Player* pPlayer )
{
__ENTER_FUNCTION

	GamePlayer* pGamePlayer = (GamePlayer*)pPlayer;
	Assert( pGamePlayer );

	Obj_Human* pHuman = pGamePlayer->GetHuman();
	Assert( pHuman );

	Scene* pScene = pHuman->getScene();
	if( pScene==NULL )
	{
		Assert(FALSE);
		return PACKET_EXE_ERROR;
	}

	//检查线程执行资源是否正确
	Assert( MyGetCurrentThreadID()==pScene->m_ThreadID );
	
	HorseFindMateModule::GetInstance().QueryHorseFindMateInfo(pHuman, pPacket->GetMaxPostion());	

	g_pLog->FastSaveLog(LOG_FILE_1, "CGQueryHorseFindMateInfoHandler: ok obj=%d,scene=%d",
		pHuman->GetID(), pScene->SceneID());

	return PACKET_EXE_CONTINUE;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}

}
