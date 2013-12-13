/********************************************************************
	created:	2008/05/13
	created:	13:5:2008   20:01
	filename: 	MapServer\Server\Skills\ImpactLogic\StdImpact075.cpp
	file path:	MapServer\Server\Skills\ImpactLogic
	file base:	StdImpact075
	file ext:	cpp
	author:		Richard
	
	purpose:	与impact29功能完全一样,只是不用gather而是直接使用技能ID

				参考impact29
*********************************************************************/

#include "stdafx.h"
#include "StdImpact075.h"
#include "Skill_Core.h"
#include "Obj_Human.h"

namespace Combat_Module
{
	using namespace Combat_Module;
	using namespace Combat_Module::Skill_Module;
	
	namespace Impact_Module
	{
		BOOL StdImpact075_T::InitFromData(OWN_IMPACT& rImp, ImpactData_T const& rData) const
		{
			__ENTER_FUNCTION
			//SetShieldHp(rImp, GetShieldHpInTable(rImp));
			//SetAbsorbRate(rImp, GetAbsorbRateInTable(rImp));
			return TRUE;
			__LEAVE_FUNCTION
			return FALSE;
		}
		VOID StdImpact075_T::RefixSkill(OWN_IMPACT& rImp, SkillInfo_T& rSkill) const
		{
			__ENTER_FUNCTION

			if( GetTargetSkillID(rImp) == rSkill.GetSkillID() )
			{
				RefixAllSkillAttr(rSkill, rImp);
			}

			__LEAVE_FUNCTION
		}

		BOOL StdImpact075_T::RefixPowerByRate(OWN_IMPACT& rImp, INT nRate) const
		{
			__ENTER_FUNCTION
			//INT nValue = GetShieldHp(rImp);
			//nRate+=100;
			//nValue = Float2Int((nValue*nRate)/1000.0f);
			//if(0>nValue)
			//{
			//	nValue=0;
			//}
			//SetShieldHp	(rImp, nValue);
			return TRUE;
			__LEAVE_FUNCTION
			return FALSE;
		}
		
		INT StdImpact075_T::GetRifixResult( INT iBase, INT iRefix, INT iRefixType ) const 
		{
			__ENTER_FUNCTION

			INT iRefixResult = 0;
			//按点数修正
			if( iRefixType <= 0 )
			{
				iRefixResult = iBase + iRefix;
			}
			else
			{//按百分比修正
				iRefix += 100;
				iRefixResult = Float2Int((iBase*iRefix)/100.0f);
			}
			return iRefixResult;
			__LEAVE_FUNCTION
			return 0;
		}

		FLOAT StdImpact075_T::GetRifixResult( FLOAT fBase, FLOAT fRefix, INT iRefixType ) const
		{
			__ENTER_FUNCTION

			FLOAT fRefixResult = 0;
			//按点数修正
			if( iRefixType <= 0 )
			{
				fRefixResult = fBase + fRefix;
			}
			else
			{//按百分比修正
				fRefix += 100;
				fRefixResult = ((fBase*fRefix)/100.0f);
			}
			return fRefixResult;
			__LEAVE_FUNCTION
			return 0;
		}
		VOID StdImpact075_T::RefixAllSkillAttr( SkillInfo_T &rSkill, OWN_IMPACT& rImp ) const 
		{
			__ENTER_FUNCTION

			//取得修正参数的类型，0 = 按点数修正， 1 = 按百分比修正
			INT iRefixType = GetRefixType( rImp );
			INT iRefixPara = 0;
			INT iBase	   = 0;
			INT iResult	   = 0;	
			//修正冷却时间
			iBase		= rSkill.GetCooldownTime();
			iRefixPara	= GetCooldownTimeRefix( rImp );
			iResult		= GetRifixResult( iBase, iRefixPara, iRefixType );
			rSkill.SetCooldownTime( iResult );
			//修正聚气时间
			iBase		= rSkill.GetChargeTime();
			iRefixPara	= GetChargeTimeRefix(rImp);
			iResult		= GetRifixResult( iBase, iRefixPara, iRefixType );
			rSkill.SetChargeTime( iResult );
			//修正引导时间
			iBase		= rSkill.GetChannelTime();
			iRefixPara	= GetChannelTimeRefix( rImp );
			iResult		= GetRifixResult( iBase, iRefixPara, iRefixType );
			rSkill.SetChannelTime( iResult );


			//对连续攻击次数和引导时间的修正
			iBase		= rSkill.GetChargesOrInterval();
			iRefixPara	= GetAttackTimesOrChannelTimeRefix( rImp );
			iResult		= GetRifixResult( iBase, iRefixPara, iRefixType );
			rSkill.SetChargesOrInterval( iResult );

			//修正命中率
			iBase		= rSkill.GetAccuracy();
			iRefixPara	= GetAccuracyRefix(rImp);
			iResult		= GetRifixResult( iBase, iRefixPara, iRefixType );
			rSkill.SetAccuracy( iResult );
			
			//修正会心率
			iBase		= rSkill.GetCriticalRate();
			iRefixPara	= GetCriticalrateRefix(rImp);
			iResult		= GetRifixResult( iBase, iRefixPara, iRefixType );
			rSkill.SetCriticalRate( iResult );
			
			//修正最大目标个数
			iBase		= rSkill.GetMaxTargetNumber();
			iRefixPara	= GetMaxTargetRefix(rImp);
			iResult		= GetRifixResult( iBase, iRefixPara, iRefixType );
			rSkill.SetMaxTargetNumber( iResult );

			//按百分比修正消耗
			if( iRefixType > 0 )
			{
				iBase		= rSkill.GetDepleteRefixByRate();
				iRefixPara	= GetDepleteRefix(rImp);
				iResult		= GetRifixResult( iBase, iRefixPara, iRefixType );
				rSkill.SetDepleteRefixByRate( iResult );
			}
			else
			{//按点数修正消耗
				iBase		= rSkill.GetDepleteRefixByValue();
				iRefixPara	= GetDepleteRefix(rImp);
				iResult		= GetRifixResult( iBase, iRefixPara, iRefixType );
				rSkill.SetDepleteRefixByValue( iResult );
			}
			
			
			__LEAVE_FUNCTION
		}
	};
};

