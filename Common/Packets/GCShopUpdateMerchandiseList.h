// GCShopUpdateMerchandiseList.h
// 
// 商人发给客户端的商品列表
// 
//////////////////////////////////////////////////////

#ifndef __GCSHOPUPDATEMERCHANDISELIST_H__
#define __GCSHOPUPDATEMERCHANDISELIST_H__

#include "Type.h"
#include "Packet.h"
#include "PacketFactory.h"
#include "DB_Struct.h"

namespace Packets
{
	class GCShopUpdateMerchandiseList: public Packet
	{
	public:
        //商人所卖商品结构
        struct _MERCHANDISE_ITEM
        {
            UINT		idTable;		//资源id
            BYTE		byNumber;		//数量
            BYTE		nPriceType;		//价格类型
            UINT		nPrice;			//价格
            INT			MaxNumber;		//有限商品的数量
            _MERCHANDISE_ITEM()
            {
                idTable		=	0;		//资源id
                byNumber	=	0;		//数量
                nPrice		=	0;   	//价格
                nPriceType  =   0;
                MaxNumber	=	0;		//有限商品的数量
            }
        };
	public:
		GCShopUpdateMerchandiseList( )
		{
			m_nMerchadiseNum = 0;
		}
		virtual ~GCShopUpdateMerchandiseList( ){};

		//公用继承接口
		virtual BOOL			Read( SocketInputStream& iStream ) ;
		virtual BOOL			Write( SocketOutputStream& oStream )const ;
		virtual UINT			Execute( Player* pPlayer ) ;

		virtual PacketID_t		GetPacketID()const { return PACKET_GC_SHOPUPDATEMERCHANDISELIST ; }
		virtual UINT			GetPacketSize()const { return	sizeof(BYTE)+sizeof(UINT)+
			m_nMerchadiseNum*sizeof(_MERCHANDISE_ITEM);}

	public:
		BYTE			GetMerchadiseNum(VOID) const {return m_nMerchadiseNum;};
		VOID			SetMerchadiseNum(BYTE nNumber) {m_nMerchadiseNum = nNumber;};

		_MERCHANDISE_ITEM*	GetMerchadiseList(VOID) { return m_MerchadiseList; }
		VOID				SetMerchadiseList(_MERCHANDISE_ITEM* pSour)
		{
			memcpy(m_MerchadiseList, pSour, m_nMerchadiseNum*sizeof(_MERCHANDISE_ITEM));
		}

        VOID			SetVersion(UINT uVersion) { m_uVersion = uVersion; }
        UINT			GetVersion(void) { return m_uVersion; }

	private:
		//商品个数
		BYTE						m_nMerchadiseNum;
        UINT                        m_uVersion;         // 动态商店版本号，校验用
		//所有商品列表
		_MERCHANDISE_ITEM			m_MerchadiseList[MAX_BOOTH_NUMBER];
	};


	class GCShopUpdateMerchandiseListFactory : public PacketFactory 
	{
	public:
		Packet*		CreatePacket() { return new GCShopUpdateMerchandiseList() ; }
		PacketID_t	GetPacketID()const { return PACKET_GC_SHOPUPDATEMERCHANDISELIST; };
		UINT		GetPacketMaxSize()const { return 
			sizeof(GCShopUpdateMerchandiseList::_MERCHANDISE_ITEM)*MAX_BOOTH_NUMBER + sizeof(UINT)+ sizeof(BYTE);};
	};

	class GCShopUpdateMerchandiseListHandler 
	{
	public:
		static UINT Execute( GCShopUpdateMerchandiseList* pPacket, Player* pPlayer ) ;
	};
}

using namespace Packets;

#endif


