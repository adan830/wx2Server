// CGCharUseSkill.h
// 
// 使用技能
// 
//////////////////////////////////////////////////////

#ifndef __CGCHARUSESKILL_H__
#define __CGCHARUSESKILL_H__

#include "Type.h"
#include "Packet.h"
#include "PacketFactory.h"
#include "GameStruct_Skill.h"

namespace Packets
{
class CGCharUseSkill : public Packet
{
public:

	CGCharUseSkill( ){}
	virtual ~CGCharUseSkill( ){}

	//公用继承接口
	virtual BOOL			Read( SocketInputStream& iStream ) ;
	virtual BOOL			Write( SocketOutputStream& oStream )const ;
	virtual UINT			Execute( Player* pPlayer ) ;

	virtual PacketID_t		GetPacketID()const { return PACKET_CG_CHARUSESKILL ; }
	virtual UINT			GetPacketSize()const 
	{
		return	sizeof(ObjID_t) +
				sizeof(SkillID_t) +
				sizeof(GUID_t) +
				sizeof(ObjID_t) +
				sizeof(WORLD_POS) +
				sizeof(FLOAT) + 
				sizeof(INT);
	}

public:
	//使用数据接口
	VOID			setObjID(ObjID_t id) { m_ObjID = id; }
	ObjID_t			getObjID(VOID)const { return m_ObjID; }

	VOID			setSkillDataID(SkillID_t ID) { m_SkillDataID = ID; }
	SkillID_t		getSkillDataID(VOID)const { return m_SkillDataID; }

	VOID			setTargetGUID(GUID_t guidTarget) { m_guidTarget = guidTarget; }
	GUID_t			getTargetGUID(VOID)const { return m_guidTarget; }

	VOID			setTargetID(ObjID_t ID) { m_TargetID = ID; }
	ObjID_t			getTargetID(VOID)const { return m_TargetID; }

	VOID				setTargetPos(WORLD_POS& pos) { m_posTarget = pos; }
	const WORLD_POS&	getTargetPos(VOID)const { return m_posTarget; }

	VOID			setDir(FLOAT fDir) { m_fDir = fDir; }
	FLOAT			getDir(VOID)const { return m_fDir; }

	INT				GetHurtDelayTime() const { return m_iHurtDelayTime; }
	VOID			SetHurtDelayTime(INT val) { m_iHurtDelayTime = val; }

private:
	ObjID_t			m_ObjID;			// ObjID
	SkillID_t		m_SkillDataID;		// 技能的资源ID
	GUID_t			m_guidTarget;		// 目标角色的GUID
	ObjID_t			m_TargetID;			// 目标角色
	WORLD_POS		m_posTarget;		// 目标坐标
	FLOAT			m_fDir;				// 技能的方向
	INT				m_iHurtDelayTime;	// 技能伤害的延迟时间

};


class CGCharUseSkillFactory : public PacketFactory 
{
public:
	Packet*		CreatePacket() { return new CGCharUseSkill() ; }
	PacketID_t	GetPacketID()const { return PACKET_CG_CHARUSESKILL; }
	UINT		GetPacketMaxSize()const { return	sizeof(ObjID_t) +
													sizeof(SkillID_t) +
													sizeof(GUID_t) +
													sizeof(ObjID_t) +
													sizeof(WORLD_POS) +
													sizeof(FLOAT) +
													sizeof(INT); }
};

class CGCharUseSkillHandler 
{
public:
	static UINT Execute( CGCharUseSkill* pPacket, Player* pPlayer ) ;
};




}

using namespace Packets;



#endif