/*
同步客户端交易盒的变化给对方
*/

#include "stdafx.h"
#include "CGExchangeSynchItemII.h"
#include "GCExchangeSynchII.h"
#include "GCExchangeError.h"
#include "GCExchangeSynchLock.h"
#include "GamePlayer.h"
#include "Obj_Human.h"
#include "Scene.h"
#include "Log.h"

#include "ItemOperator.h"
#include "HumanItemLogic.h"
#include "GCDetailAttrib_Pet.h"
#include "GameTable.h"
using namespace EXCHANGE_MSG;

uint CGExchangeSynchItemIIHandler::Execute( CGExchangeSynchItemII* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

	GamePlayer* pGamePlayer = (GamePlayer*)pPlayer ;
	Assert( pGamePlayer ) ;

	Obj_Human* pHuman = pGamePlayer->GetHuman() ;
	Assert( pHuman ) ;

	Scene* pScene = pHuman->getScene() ;
	if( pScene==NULL )
	{
		Assert(FALSE) ;
		return PACKET_EXE_ERROR ;
	}

	//检查线程执行资源是否正确
	Assert( MyGetCurrentThreadID()==pScene->m_ThreadID ) ;

	//验证交易状态
	EXCHANGE_CERTIFY_EACH_OTHER(pHuman)  // 验证交易双方是否掉线合法
	EXCHANGE_CERTIFY_ISLOCK(pHuman)		 // 验证当前人物的交易状态是否已经上锁
	ObjID_t	DestID = pHuman->m_ExchangBox.m_ObjID;
	Obj_Human* pDestHuman = pScene->GetHumanManager()->GetHuman( DestID );
	EXCHANGE_CERTIFY_STATUS(pHuman, EXCHANGE_SYNCH_DATA) // 验证当前人物的交易状态是否正确
	EXCHANGE_CERTIFY_STATUS(pDestHuman, EXCHANGE_SYNCH_DATA)

	//操作
	BYTE		Opt = pPacket->GetOpt();
	BYTE		FromType = pPacket->GetFromType();
	BYTE		ToType = pPacket->GetToType();
	BYTE		FromIndex = pPacket->GetFromIndex();
	BYTE		ToIndex = pPacket->GetToIndex();
	PET_GUID_t	PetGuid = pPacket->GetPetGuid();

	_ITEM				ItemTemp;
	GCExchangeSynchII	Msg;
	GCExchangeError		MsgError;
	ItemContainer*		pExchangeContainer		= &(pHuman->m_ExchangBox.m_Container);
	ItemContainer*		pExchangePetContainer	= &(pHuman->m_ExchangBox.m_PetContainer);

	switch(Opt)
	{
	case OPT_ERROR:
		{
		}
		break;
	case OPT_ADDITEM:
		{
			switch(FromType)
			{
			case POS_BAG:
				{
					//验证位置里是否有东西
					Item* pItem = HumanItemLogic::GetBagItem(pHuman, FromIndex);

                    if ( pItem != NULL && pItem->GetItemClass() == ICLASS_EQUIP)
                    {
                        if(pItem->GetEquipBindLevel()>0) // 装备绑定
                        {
							MsgError.SetID(ERR_ITEM_LOCKED);
							pGamePlayer->SendPacket(&MsgError);
                            g_pLog->FastSaveLog( LOG_FILE_1, "<交易> [%s] 该物品[%d]已绑定，不可交易",	pHuman->GetName(), FromIndex ) ;
                            return PACKET_EXE_CONTINUE;
                        }
                    }
                    
					if (pItem == NULL)
					{
						MsgError.SetID(ERR_ILLEGAL);
						pGamePlayer->SendPacket(&MsgError);
						g_pLog->FastSaveLog( LOG_FILE_1, "<交易> [%s] 背包位置 [%d] 处不存在物品",	pHuman->GetName(), FromIndex ) ;
						return PACKET_EXE_CONTINUE;
					}
					if(pItem->IsEmpty() == FALSE)
					{
						ItemContainer*	pBagContainer = HumanItemLogic::GetBagContainer(pHuman, FromIndex);

						if ( pBagContainer == NULL )
						{
							MsgError.SetID(ERR_ILLEGAL);
							pGamePlayer->SendPacket(&MsgError);
							g_pLog->FastSaveLog( LOG_FILE_1, "<交易> [%s] 背包不存在",	pHuman->GetName() ) ;
							return PACKET_EXE_CONTINUE;
						}

						//先查一遍交易盒中是不是已经有该物品了
						for(INT i = 0; i<EXCHANGE_BOX_SIZE; i++)
						{
							_ITEM_GUID guid = (pBagContainer->GetItem(pBagContainer->BagIndex2ConIndex(FromIndex)))->GetGUID() ;
							if(pExchangeContainer->GetItem(i)->GetGUID() == guid)
							{//物品已经在交易盒中，丢弃该消息
								return PACKET_EXE_CONTINUE ;
							}

						}

						//自动找格
						INT result = 
							g_ItemOperator.CopyItem
							(
								pBagContainer,
								pBagContainer->BagIndex2ConIndex(FromIndex),
								pExchangeContainer
							);

						if(result>=0)
						{//拷贝成功，

							//发送消息给双方客户端
							Item* pIt = pExchangeContainer->GetItem(result);	

							g_pLog->FastSaveLog( LOG_FILE_1, "<交易> [%s] 加入交易物品 [%d]",	pHuman->GetName(), pIt->GetItemTableIndex() ) ;												

							if( pIt != NULL && pIt->IsEmpty() == FALSE )
							{
								INT iConIndex = pBagContainer->BagIndex2ConIndex(FromIndex);
								//先锁定此物品
								g_ItemOperator.LockItem( pBagContainer, iConIndex );
								
								//标示次物品已经放在交易栏中,计算空间用
								pBagContainer->GetItem(iConIndex)->SetInExchange(TRUE);

								//再发
								pIt->SaveValueTo(&ItemTemp);//取出实例
								
								/*
								先发自己
								*/
								Msg.SetIsMyself(TRUE);//发给自己
								Msg.SetOpt(OPT_ADDITEM);//设置操作类型
								Msg.SetFromType(POS_BAG);//设置来自类型
								Msg.SetFromIndex(FromIndex);//设置来自索引
								Msg.SetToIndex(result);//设置目标位置索引
								pGamePlayer->SendPacket(&Msg);

								/*
								再发对方
								*/
								Msg.SetIsMyself(FALSE);//发给对方
								Msg.SetOpt(OPT_ADDITEM);//设置操作类型
								Msg.SetToIndex(result);

								_EXCHANGE_ITEM Exitem;
								Exitem.byNumber = ItemTemp.GetItemCount();
								Exitem.isBlueEquip	= 1;
								Exitem.item_data	= ItemTemp;
                                Exitem.uBagPos      = result;
								Msg.SetItem(&Exitem);

								pDestHuman->GetPlayer()->SendPacket(&Msg);

                                //改变物品  自己解锁
                                pHuman->m_ExchangBox.m_IsLocked = FALSE;
                                if(pDestHuman->m_ExchangBox.m_IsLocked == TRUE)
                                {//如果对方已经加锁
                                    pDestHuman->m_ExchangBox.m_IsLocked = FALSE;
                                    GCExchangeSynchLock MsgToDes, MsgToSelf;

                                    //通知对方，解双方锁
                                    MsgToDes.SetIsBoth(TRUE);
                                    MsgToDes.SetIsLocked(FALSE);
                                    pDestHuman->GetPlayer()->SendPacket(&MsgToDes);

                                    //通知自己解对方锁
                                    MsgToSelf.SetIsMyself(FALSE);
                                    MsgToSelf.SetIsLocked(FALSE);
                                    pHuman->GetPlayer()->SendPacket(&MsgToSelf);

                                }
                                else
                                {//对方没有加锁，直接同步
                                    GCExchangeSynchLock MsgToDes;
                                    MsgToDes.SetIsMyself (FALSE);
                                    MsgToDes.SetIsLocked(FALSE);
                                    pDestHuman->GetPlayer()->SendPacket(&MsgToDes);
                                }
							}
							else
							{
								MsgError.SetID(ERR_ILLEGAL);
								pGamePlayer->SendPacket(&MsgError);
								g_pLog->FastSaveLog( LOG_FILE_1, "<交易> [%s] 加入非法交易物品 [%d]",	pHuman->GetName(), pIt->GetItemTableIndex() ) ;
								return PACKET_EXE_CONTINUE ;

							}//if( pIt != NULL && pIt->IsEmpty() == FALSE )
						}
						else
						{//拷贝失败
							MsgError.SetID(ERR_NOT_ENOUGHT_EXROOM);
							pGamePlayer->SendPacket(&MsgError);
							g_pLog->FastSaveLog( LOG_FILE_1, "<交易> [%s] 交易盒没有足够空间",	pHuman->GetName() ) ;
							return PACKET_EXE_CONTINUE ;

						}//if(result>=0)

					}
					else
					{
						MsgError.SetID(ERR_ILLEGAL);
						pGamePlayer->SendPacket(&MsgError);
						g_pLog->FastSaveLog( LOG_FILE_1, "<交易> [%s] 没有获取到所要交易的背包物品",	pHuman->GetName() ) ;
						return PACKET_EXE_CONTINUE ;

					}//if(pItem->IsEmpty() == FALSE)

				}
				break;
			case POS_EQUIP:
				{
				}
				break;
			case POS_PET:
				{
				}
				break;
			default:
				break;
			}

		}
		break;
	case OPT_REMOVEITEM:
		{
			switch(ToType)
			{
				case POS_BAG:
					{
						Item* pIt = pExchangeContainer->GetItem(FromIndex);

						if( pIt != NULL && pIt->IsEmpty() == FALSE )
						{							
							INT BagIndex = -1;
							ItemContainer*	pBagContainer = HumanItemLogic::GetBagItemContain( pHuman,&pIt->GetGUID(), BagIndex);

							if ( pBagContainer == NULL )
							{
								MsgError.SetID(ERR_ILLEGAL);
								pGamePlayer->SendPacket(&MsgError);
								g_pLog->FastSaveLog( LOG_FILE_1, "<交易> [%s] 背包不存在",	pHuman->GetName() ) ;
								return PACKET_EXE_CONTINUE;
							}

							//从交易盒中删掉此物品
							if(g_ItemOperator.EraseItem(pExchangeContainer, FromIndex))
							{
								//解锁此物品
								g_ItemOperator.UnlockItem( pBagContainer, BagIndex );

								//标示次物品已经取消放在交易栏中,计算空间用
								pBagContainer->GetItem(BagIndex)->SetInExchange(FALSE);

								g_pLog->FastSaveLog( LOG_FILE_1, "<交易> [%s] 删除交易物品 [%d]",	pHuman->GetName(), BagIndex) ;

								//发消息								
								if(BagIndex>=0)
								{
									/*
									先发自己
									*/
									Msg.SetIsMyself(TRUE);//发给自己
									Msg.SetOpt(OPT_REMOVEITEM);//设置操作类型
									Msg.SetToType(POS_BAG);//设置目的类型
									Msg.SetToIndex(BagIndex);//设置目的索引
									Msg.SetFromIndex(FromIndex);//设置来源索引
									pGamePlayer->SendPacket(&Msg);

									/*
									再发对方
									*/
									Msg.SetIsMyself(FALSE);//发给对方
									Msg.SetOpt(OPT_REMOVEITEM);//设置操作类型
									Msg.SetFromIndex(FromIndex);//设置来源索引
									pDestHuman->GetPlayer()->SendPacket(&Msg);

                                    //改变物品    自己解锁
                                    pHuman->m_ExchangBox.m_IsLocked = FALSE;
                                    if(pDestHuman->m_ExchangBox.m_IsLocked == TRUE)
                                    {//如果对方已经加锁
                                        pDestHuman->m_ExchangBox.m_IsLocked = FALSE;
                                        GCExchangeSynchLock MsgToDes, MsgToSelf;

                                        //通知对方，解双方锁
                                        MsgToDes.SetIsBoth(TRUE);
                                        MsgToDes.SetIsLocked(FALSE);
                                        pDestHuman->GetPlayer()->SendPacket(&MsgToDes);

                                        //通知自己解对方锁
                                        MsgToSelf.SetIsMyself(FALSE);
                                        MsgToSelf.SetIsLocked(FALSE);
                                        pHuman->GetPlayer()->SendPacket(&MsgToSelf);

                                    }
                                    else
                                    {//对方没有加锁，直接同步
                                        GCExchangeSynchLock MsgToDes;
                                        MsgToDes.SetIsMyself (FALSE);
                                        MsgToDes.SetIsLocked(FALSE);
                                        pDestHuman->GetPlayer()->SendPacket(&MsgToDes);
                                    }
								}
								else
								{
									MsgError.SetID(ERR_ILLEGAL);
									pGamePlayer->SendPacket(&MsgError);
									return PACKET_EXE_CONTINUE;
								}

							}
							else
							{
								MsgError.SetID(ERR_ILLEGAL);
								pGamePlayer->SendPacket(&MsgError);
								g_pLog->FastSaveLog( LOG_FILE_1, "<交易> [%s] 删除交易盒位置 [%d] 处的物品时出错",	pHuman->GetName(), FromIndex ) ;
								return PACKET_EXE_CONTINUE;
							}

						}
						else
						{
							MsgError.SetID(ERR_ILLEGAL);
							pGamePlayer->SendPacket(&MsgError);
							g_pLog->FastSaveLog( LOG_FILE_1, "<交易> [%s] 交易盒位置 [%d] 处不存在物品",	pHuman->GetName(), FromIndex ) ;
							return PACKET_EXE_CONTINUE;
						}
					}
					break;

				case POS_EQUIP:
					{
					}
					break;

				case POS_PET:
					{
					}
					break;
				default:
					break;

			}

		}
		break;
	case OPT_ADDPET:
		{
			ItemContainer*	pPetContainer = pHuman->GetPetContain();
			FromIndex = pPetContainer->GetIndexByGUID( &PetGuid );

            if (255 == FromIndex)
            {
                g_pLog->FastSaveLog( LOG_FILE_1, "<交易> [%s] 加入非法交易宠物",	pHuman->GetName()) ;
                return PACKET_EXE_CONTINUE ;
            }

			//先查一遍交易盒中是不是已经有该物品了
			for(INT i = 0; i<EXCHANGE_PET_BOX_SIZE; i++)
			{
				if(pExchangePetContainer->GetItem(i)->GetPetGUID() == pPetContainer->GetItem(FromIndex)->GetPetGUID() )
				{//物品已经在交易盒中，丢弃该消息
					return PACKET_EXE_CONTINUE ;
				}
			}

			//自动找格
			INT result = 
				g_ItemOperator.CopyItem
				(
				pPetContainer,
				FromIndex,
				pExchangePetContainer
				);

			if(result>=0)
			{//拷贝成功
				Item* pIt = pExchangePetContainer->GetItem(result);
				g_pLog->FastSaveLog( LOG_FILE_1, "<交易> [%s] 加入交易宠物 [%s]",	pHuman->GetName(), pIt->GetName() ) ;
				if(pIt->IsEmpty() == FALSE)
				{
					//先锁定此物品
					g_ItemOperator.LockItem( pPetContainer, FromIndex );

					//标示次物品已经放在交易栏中,计算空间用
					pPetContainer->GetItem(FromIndex)->SetInExchange(TRUE);
					/*
					先发自己
					*/
					Msg.SetIsMyself(TRUE);//发给自己
					Msg.SetOpt(OPT_ADDPET);//设置操作类型
					Msg.SetToIndex(result);//设置目的地位置
					Msg.SetPetGuid(PetGuid);//宠物GUID
					pGamePlayer->SendPacket(&Msg);

					/*
					再发对方
					*/
					GCDetailAttrib_Pet PetMsgDetail;
					//组装GCDetailAttrib_Pet结构
					Obj_Human::CalculatePetDetailAttrib(PetMsgDetail, pIt);
					PetMsgDetail.SetTradeIndex( result );

					PET_EXTRA_STRUCT::GCExchangePetView_t ExtraPetInfo;
					ExtraPetInfo.m_bFlag	=	TYPE_EXCHANGE;
					PetMsgDetail.SetExtraInfoLength(ExtraPetInfo.GetSize());
					PetMsgDetail.SetExtraInfoData((BYTE*)&ExtraPetInfo);
					pDestHuman->GetPlayer()->SendPacket(&PetMsgDetail);	

                    //改变金钱    自己解锁
                    pHuman->m_ExchangBox.m_IsLocked = FALSE;
                    if(pDestHuman->m_ExchangBox.m_IsLocked == TRUE)
                    {//如果对方已经加锁
                        pDestHuman->m_ExchangBox.m_IsLocked = FALSE;
                        GCExchangeSynchLock MsgToDes, MsgToSelf;

                        //通知对方，解双方锁
                        MsgToDes.SetIsBoth(TRUE);
                        MsgToDes.SetIsLocked(FALSE);
                        pDestHuman->GetPlayer()->SendPacket(&MsgToDes);

                        //通知自己解对方锁
                        MsgToSelf.SetIsMyself(FALSE);
                        MsgToSelf.SetIsLocked(FALSE);
                        pHuman->GetPlayer()->SendPacket(&MsgToSelf);

                    }
                    else
                    {//对方没有加锁，直接同步
                        GCExchangeSynchLock MsgToDes;
                        MsgToDes.SetIsMyself (FALSE);
                        MsgToDes.SetIsLocked(FALSE);
                        pDestHuman->GetPlayer()->SendPacket(&MsgToDes);
                    }
				}
				else
				{
					MsgError.SetID(ERR_ILLEGAL);
					pGamePlayer->SendPacket(&MsgError);
					g_pLog->FastSaveLog( LOG_FILE_1, "<交易> [%s] 加入非法交易宠物 [%s]",	pHuman->GetName(), pIt->GetName() ) ;
					return PACKET_EXE_CONTINUE ;
				}
			}
		}
		break;
	case OPT_REMOVEPET:
		{
			ItemContainer*	pPetContainer = pHuman->GetPetContain();
			INT nIndexInPet = pPetContainer->GetIndexByGUID(&PetGuid);
			FromIndex = pExchangePetContainer->GetIndexByGUID(&PetGuid);

			if(g_ItemOperator.EraseItem(pExchangePetContainer, FromIndex))
			{
				//解锁此物品
				g_ItemOperator.UnlockItem( pPetContainer, nIndexInPet );

				//标示次物品已经放在交易栏中,计算空间用
				pPetContainer->GetItem(nIndexInPet)->SetInExchange(FALSE);

				//发消息
				g_pLog->FastSaveLog( LOG_FILE_1, "<交易> [%s] 删除交易宠物 [%s]",	pHuman->GetName(), pPetContainer->GetItem(nIndexInPet)->GetName()) ;
				if(nIndexInPet>=0)
				{
					/*
					先发自己
					*/
					Msg.SetIsMyself(TRUE);//发给自己
					Msg.SetOpt(OPT_REMOVEPET);//设置操作类型
					Msg.SetPetGuid(PetGuid);//宠物GUID
					pGamePlayer->SendPacket(&Msg);

					/*
					再发对方
					*/
					Msg.SetIsMyself(FALSE);//发给对方
					Msg.SetOpt(OPT_REMOVEPET);//设置操作类型
					Msg.SetPetGuid(PetGuid);//宠物GUID
					pDestHuman->GetPlayer()->SendPacket(&Msg);

                    //改变金钱    自己解锁
                    pHuman->m_ExchangBox.m_IsLocked = FALSE;
                    if(pDestHuman->m_ExchangBox.m_IsLocked == TRUE)
                    {//如果对方已经加锁
                        pDestHuman->m_ExchangBox.m_IsLocked = FALSE;
                        GCExchangeSynchLock MsgToDes, MsgToSelf;

                        //通知对方，解双方锁
                        MsgToDes.SetIsBoth(TRUE);
                        MsgToDes.SetIsLocked(FALSE);
                        pDestHuman->GetPlayer()->SendPacket(&MsgToDes);

                        //通知自己解对方锁
                        MsgToSelf.SetIsMyself(FALSE);
                        MsgToSelf.SetIsLocked(FALSE);
                        pHuman->GetPlayer()->SendPacket(&MsgToSelf);

                    }
                    else
                    {//对方没有加锁，直接同步
                        GCExchangeSynchLock MsgToDes;
                        MsgToDes.SetIsMyself (FALSE);
                        MsgToDes.SetIsLocked(FALSE);
                        pDestHuman->GetPlayer()->SendPacket(&MsgToDes);
                    }
				}
				else
				{
					MsgError.SetID(ERR_ILLEGAL);
					pGamePlayer->SendPacket(&MsgError);
					return PACKET_EXE_CONTINUE;
				}
			}
			else
			{
				MsgError.SetID(ERR_ILLEGAL);
				pGamePlayer->SendPacket(&MsgError);
				g_pLog->FastSaveLog( LOG_FILE_1, "<交易> [%s] 删除交易盒位置 [%d] 处的物品时出错",	pHuman->GetName(), FromIndex ) ;
				return PACKET_EXE_CONTINUE;
			}
		}
		break;
	default:
		break;
	}
		return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
