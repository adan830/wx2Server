#include "stdafx.h" 
#include "CLAskCreateChar.h"
#include "ProcessPlayerManager.h"
#include "LoginPlayer.h"
#include "TimeManager.h"
#include "DBLogicManager.h"
#include "LCRetCreateChar.h"
//#include "DBCreateCharOp.h"
#include "DBCharCreate.h"
//#include "DBCheckCharName.h"
#include "PacketFactoryManager.h"
#include "ProcessManager.h"
#include "LCRetCharList.h"
#include "DBCharList.h"
#include "DBCharFullData.h"
#include "DB_Struct.h"
#include "Log.h"
#include "CharConfig.h"
#include "DBThreadManager.h"



UINT	CLAskCreateCharHandler::Execute(CLAskCreateChar* pPacket, Player* pPlayer)
{
	__ENTER_FUNCTION
		
		TID CurrentThreadID = MyGetCurrentThreadID();

		if(CurrentThreadID == g_pProcessPlayerManager->m_ThreadID) 
		{
			LoginPlayer* pLoginPlayer = static_cast<LoginPlayer*>(pPlayer);
			Assert(pLoginPlayer);
			
			if(pLoginPlayer->GetPlayerStatus()!=PS_LOGIN_NORMAL)
			{
				//没有权限，什么也不做
				return PACKET_EXE_CONTINUE;
			}

			//名称是否非法
			if(FALSE == StrSafeCheck(pPacket->GetName(),MAX_CHARACTER_NAME))
			{
				LCRetCreateChar Msg;
				Msg.SetAccount(pLoginPlayer->GetAccount());
				Msg.SetResult(ASKCREATECHAR_NAME_ERROR);
				pLoginPlayer->SendPacket(&Msg);

				g_pLog->FastSaveLog(LOG_FILE_0, "CLAskCreateCharHandler....Fails!, code = ASKCREATECHAR_NAME_ERROR,acc=%s",
					pLoginPlayer->GetAccount()) ;
				return PACKET_EXE_CONTINUE;
			}

			UINT uTime = g_pTimeManager->CurrentTime();

			if(uTime<pLoginPlayer->m_LastDBOpTime+DB_OPERATION_TIME)
			{
				LCRetCreateChar Msg;
				Msg.SetAccount(pLoginPlayer->GetAccount());
				Msg.SetResult(ASKCREATECHAR_OP_TIMES);

				//发送DB操作频繁消息
				pLoginPlayer->SendPacket(&Msg);
				
				g_pLog->FastSaveLog(LOG_FILE_0, "CLAskCreateCharHandler....Fails!, code = ASKCREATECHAR_OP_TIMES,acc = %s",
					pLoginPlayer->GetAccount()) ;

				return PACKET_EXE_CONTINUE;
			}

			//if(FALSE == pLoginPlayer->m_bAlreadyCheckCreateCode)
			//{
			//	LCRetCreateChar Msg;
			//	Msg.SetAccount(pPacket->GetAccount());
			//	Msg.SetResult(ASKCREATECHAR_CREATECODE_FALSE);

			//	//发送未验证验证码消息
			//	pLoginPlayer->SendPacket(&Msg);

			//	g_pLog->FastSaveLog(LOG_FILE_0, "ERROR:CLAskCreateCharHandler....Fails!, code = ASKCREATECHAR_CREATECODE_FALSE,acc = %s",
			//		pPacket->GetAccount()) ;

			//	return PACKET_EXE_CONTINUE;
			//}
			
			pPacket->SetPlayerID(pLoginPlayer->PlayerID());
			pPacket->SetAccount(pLoginPlayer->GetAccount());
			//将玩家操作加入DB 队列
			//并且设置最后操作时间

			if(g_pDBThreadManager->SendPacket(pPacket,pLoginPlayer->PlayerID()))
			{//加入成功，将消息发送到DB处理
				pLoginPlayer->m_LastDBOpTime = uTime;	
				return PACKET_EXE_NOTREMOVE;	
			}
			else
			{//DB 压力过大，让用户重新尝试
				LCRetCreateChar Msg;
				Msg.SetAccount(pPacket->GetAccount());
				Msg.SetResult(ASKCREATECHAR_SERVER_BUSY);
				pLoginPlayer->SendPacket(&Msg);

				g_pLog->FastSaveLog(LOG_FILE_0, "CLAskCreateCharHandler....Fails!, code = ASKCREATECHAR_SERVER_BUSY,acc=%s",
					pPacket->GetAccount()) ;
				return PACKET_EXE_CONTINUE;
			}

		}
		else if(g_pDBThreadManager->IsPoolTID(CurrentThreadID))
		{
		
			PlayerID_t	PlayerID	= pPacket->GetPlayerID();

			GUID_t	PlayerCharGUID = 1;

			LoginPlayer* pLoginPlayer = static_cast<LoginPlayer*>(pPlayer);
			Assert(pLoginPlayer);
			
			ASKCREATECHAR_RESULT	Result = ASKCREATECHAR_INTERNAL_ERROR;
			LCRetCreateChar* pMsg = (LCRetCreateChar*)g_pPacketFactoryManager->CreatePacket(PACKET_LC_RETCREATECHAR);
			if(!pMsg)
			{
				AssertEx(FALSE,"创建 LCRetCreateChar 消息失败");
			}

			if(pLoginPlayer->GetDBOperating() == TRUE)
			{
				pMsg->SetAccount(pPacket->GetAccount());
				pMsg->SetResult(ASKCREATECHAR_SERVER_BUSY);
				g_pProcessManager->SendPacket(pMsg,PlayerID);

				g_pLog->FastSaveLog(LOG_FILE_0, "CLAskCreateCharHandler::Execute()....数据库操作冲突!,acc = %s",
					pPacket->GetAccount()) ;
				return PACKET_EXE_CONTINUE;
			}
			
			//检查GUID 是否正确
			if(strcmp(pLoginPlayer->GetAccount(),pPacket->GetAccount())!= 0)
			{
				//应该是一次错误操作
				g_pLog->FastSaveLog(LOG_FILE_0, "ERROR: CLAskCreateChar DBOperation Errors,acc = %s,Packet acc = %s",
					pLoginPlayer->GetAccount(),pPacket->GetAccount()) ;
				g_pPacketFactoryManager->RemovePacket(pMsg);	// fix memory leak[4/16/2007]
				return PACKET_EXE_CONTINUE;
			}

			pLoginPlayer->SetDBOperating(TRUE);

			LCRetCharList* pRetListMsg = (LCRetCharList*)g_pPacketFactoryManager->CreatePacket(PACKET_LC_RETCHARLIST)	;
			if(!pRetListMsg)
			{
				AssertEx(FALSE,"创建 LCRetCharList 消息失败");
			}


			INT CharNumber = pLoginPlayer->GetCharNumber();

			if(CharNumber>=MAX_CREATE_PLAYER_NUM )
			{
				Result = ASKCREATECHAR_FULL; //角色满了
			}
			else if(CharNumber ==-1)
			{
				Result = ASKCREATECHAR_OP_ERROR;
			}
			else
			{

				ODBCInterface*	pInterface = g_pDBThreadManager->GetInterface(CurrentThreadID);
				if(!pInterface)
				{// 仅为安全考率而添加的[4/16/2007]
					g_pPacketFactoryManager->RemovePacket(pMsg);	// fix memory leak[4/16/2007]

					g_pPacketFactoryManager->RemovePacket(pRetListMsg);	// fix memory leak[4/16/2007]
					pLoginPlayer->SetDBOperating(FALSE);
					return PACKET_EXE_CONTINUE;
				}

				// 插入前需要先检查名称合法性，为移民功能添加[2007/08/13 YangJun]
				//DBCheckCharName CheckCharName(pInterface);
				//CheckCharName.SetCharName(pPacket->GetName());
				//BOOL bRetCheckName = CheckCharName.Load();
				//if(!bRetCheckName)
				//{
				//	g_pLog->FastSaveLog(LOG_FILE_0,"CheckCharName.Load()...acc = %s Get Errors: %s",
				//		pPacket->GetAccount(),CheckCharName.GetErrorMessage());
				//	//检查名称失败
				//	pMsg->SetAccount(pPacket->GetAccount());
				//	pMsg->SetResult(ASKCREATECHAR_INTERNAL_ERROR);
				//	g_pProcessManager->SendPacket(pMsg,PlayerID);

				//	g_pPacketFactoryManager->RemovePacket(pRetListMsg);		// fix memory leak[4/16/2007]
				//	pLoginPlayer->SetDBOperating(FALSE);
				//	return PACKET_EXE_NOTREMOVE;
				//}
				//bRetCheckName = CheckCharName.ParseResult(&Result);
				//if(!bRetCheckName)
				//{
				//	g_pLog->FastSaveLog(LOG_FILE_0,"CheckCharName.ParseResult()...acc = %s Get Errors: %s",
				//		pPacket->GetAccount(),CheckCharName.GetErrorMessage());

				//	pMsg->SetAccount(pPacket->GetAccount());
				//	pMsg->SetResult(Result);
				//	g_pProcessManager->SendPacket(pMsg,PlayerID);

				//	g_pPacketFactoryManager->RemovePacket(pRetListMsg);		// fix memory leak[4/16/2007]
				//	pLoginPlayer->SetDBOperating(FALSE);
				//	return PACKET_EXE_NOTREMOVE;
				//}

				//插入纪录
				//DBCreateCharOp CreateCharOp(pInterface);
				DBCharCreate CreateCharOp(pInterface);
				CreateCharOp.SetAccount(pPacket->GetAccount());
				CreateCharOp.SetCharName(pPacket->GetName());
				//CreateCharOp.SetCharGuid(pPacket->GetCharGuid());
				CreateCharOp.SetSex(pPacket->GetSex());
				CreateCharOp.SetHairColor(pPacket->GetHairColor());
				CreateCharOp.SetHairModel(pPacket->GetHairModel());
				CreateCharOp.SetFaceColor(pPacket->GetFaceColor());
				CreateCharOp.SetFaceModel(pPacket->GetFaceModel());
				//CreateCharOp.SetDefEquip(pPacket->GetDefEquip());
				CreateCharOp.SetHeadID(pPacket->GetHeadID());
				CreateCharOp.SetCountry(pPacket->GetCountry());
				
				BOOL bRetAddNew	 = CreateCharOp.AddNew();
				if(!bRetAddNew)
				{
					g_pLog->FastSaveLog(LOG_FILE_0,"CreateCharOp.AddNew()...acc = %s Get Errors: %s",
						pPacket->GetAccount(),CreateCharOp.GetErrorMessage());
					//添加新角色失败
					pMsg->SetAccount(pPacket->GetAccount());
					pMsg->SetResult(ASKCREATECHAR_INTERNAL_ERROR);
					g_pProcessManager->SendPacket(pMsg,PlayerID);

					g_pPacketFactoryManager->RemovePacket(pRetListMsg);		// fix memory leak[4/16/2007]
					pLoginPlayer->SetDBOperating(FALSE);
					return PACKET_EXE_NOTREMOVE;
				}
				bRetAddNew = CreateCharOp.ParseResult(&Result);
				if(!bRetAddNew)
				{
					g_pLog->FastSaveLog(LOG_FILE_0,"CreateCharOp.ParseResult()...acc = %s Get Errors: %s",
						pPacket->GetAccount(),CreateCharOp.GetErrorMessage());
					
					pMsg->SetAccount(pPacket->GetAccount());
					pMsg->SetResult(Result);
					g_pProcessManager->SendPacket(pMsg,PlayerID);

					g_pPacketFactoryManager->RemovePacket(pRetListMsg);		// fix memory leak[4/16/2007]
					pLoginPlayer->SetDBOperating(FALSE);
					return PACKET_EXE_NOTREMOVE;
				}
				
				PlayerCharGUID = CreateCharOp.GetCharGuid();
				Assert(PlayerCharGUID!=INVALID_ID);
				//设置基本属性
				
				FULLUSERDATA		UserData;
				DBCharFullData		CharFullDataObject(pInterface);
				CharFullDataObject.SetCharGuid(PlayerCharGUID);
			   
				BOOL bRetLoad =	CharFullDataObject.Load();
				if(!bRetLoad)
				{	
						//验证数据失败
						pMsg->SetAccount(pPacket->GetAccount());
						pMsg->SetCountry(pPacket->GetCountry());
						pMsg->SetMenPai(pPacket->GetProfession());
						pMsg->SetGUID(PlayerCharGUID);
						pMsg->SetResult(ASKCREATECHAR_NEXTDB_CREATE);
						g_pProcessManager->SendPacket(pMsg,PlayerID);

						g_pPacketFactoryManager->RemovePacket(pRetListMsg);		// fix memory leak[4/16/2007]
						pLoginPlayer->SetDBOperating(FALSE);
						g_pLog->FastSaveLog(LOG_FILE_0, "CLAskCreateCharHandler::Execute() ...Load()....Fails! Next DBThread Try!,acc = %s,guid=%X",
							pPacket->GetAccount(),PlayerCharGUID) ;
						return PACKET_EXE_NOTREMOVE;
				}
				
			   CharFullDataObject.ParseResult(&UserData);
			   // yangjun[12/5/2006]
			   //暂不添加DBChardbVersion的检查
			   g_CharConfig.InitCharAttr(&UserData, pPacket->GetCountry(), pPacket->GetProfession());
			   //设置创建时间
			   BOOL bRetSave = CharFullDataObject.Save(&UserData); //保存出始化信息
			   if(!bRetSave)
				{
					//初始化数据设置失败
					pMsg->SetAccount(pPacket->GetAccount());
					pMsg->SetResult(ASKCREATECHAR_INTERNAL_ERROR);
					g_pProcessManager->SendPacket(pMsg,PlayerID);
					g_pLog->FastSaveLog(LOG_FILE_0, "CLAskCreateCharHandler::Execute() ...Save()....Fails!,acc = %s,guid = %X",
						pPacket->GetAccount(),PlayerCharGUID) ;

					g_pPacketFactoryManager->RemovePacket(pRetListMsg);		// fix memory leak[4/16/2007]
					pLoginPlayer->SetDBOperating(FALSE);
					return PACKET_EXE_NOTREMOVE;
				}
				bRetSave	=	CharFullDataObject.ParseResult(&UserData);//保存全部档案
				if(!bRetSave)
				{
					//初始化数据设置失败
					pMsg->SetAccount(pPacket->GetAccount());
					pMsg->SetResult(ASKCREATECHAR_INTERNAL_ERROR);
					g_pProcessManager->SendPacket(pMsg,PlayerID);
					g_pLog->FastSaveLog(LOG_FILE_0, "CLAskCreateCharHandler::Execute() ...ParseResult....Fails!,acc=%s,guid=%X",
						pPacket->GetAccount(),PlayerCharGUID) ;

					g_pPacketFactoryManager->RemovePacket(pRetListMsg);		// fix memory leak[4/16/2007]
					pLoginPlayer->SetDBOperating(FALSE);
					return PACKET_EXE_NOTREMOVE;
				}

				//返回新的角色列表
				DBCharList	CharListObject(pInterface);
				CharListObject.SetAccount(pPacket->GetAccount());
				bRetLoad = 	CharListObject.Load();
				if(bRetLoad)
				{
					CharListObject.ParseResult(pRetListMsg->GetCharBaseInfo());

					pRetListMsg->SetAccount(pPacket->GetAccount());
					pRetListMsg->SetResult(ASKCHARLIST_SUCCESS);
					pRetListMsg->SetCharNumber(CharListObject.GetCharNumber());
				
					if(CharListObject.GetCharNumber()> (UINT)CharNumber)
					{
						Result = ASKCREATECHAR_SUCCESS;
						pLoginPlayer->m_bAlreadyCheckCreateCode = FALSE;
					}
					else
					{
						Result = ASKCREATECHAR_INTERNAL_ERROR;
					}
					pLoginPlayer->SetCharNumber(CharListObject.GetCharNumber());
					
					for(INT i=0;i<pLoginPlayer->GetCharNumber();i++)
					{
						pLoginPlayer->SetCharGUID(pRetListMsg->GetCharBaseInfo(i)->m_GUID,i);
					}
				}
				else //操作失败，可能是断开连接了
				{
					pRetListMsg->SetAccount(pPacket->GetAccount());
					pRetListMsg->SetResult(ASKCHARLIST_OP_FAILS);
					pRetListMsg->SetCharNumber(CharListObject.GetCharNumber());
				}
			
			}
			pMsg->SetAccount(pPacket->GetAccount());
			pMsg->SetResult(Result);
			g_pProcessManager->SendPacket(pMsg,PlayerID);
			g_pProcessManager->SendPacket(pRetListMsg,PlayerID);
			pLoginPlayer->SetDBOperating(FALSE);
			g_pLog->FastSaveLog(LOG_FILE_0, "CLAskCreateCharHandler::Execute()....OK! \
				Account = %s CharGuid = %X CharName = %s",\
				pPacket->GetAccount(),PlayerCharGUID,pPacket->GetName()) ;
			return PACKET_EXE_NOTREMOVE;
		}

		return PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR;
}