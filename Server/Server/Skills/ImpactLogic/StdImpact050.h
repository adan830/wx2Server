///////////////////////////////////////////////////////////////////////////////
// 文件名：StdImpact050.h
// 程序员：高骐
// 功能说明：效果--在一段时间里爆击率增加，同时受到伤害将增加怒气
//			少林技能铁布衫用
// 修改记录：
//
//
//
///////////////////////////////////////////////////////////////////////////////

#ifndef STDIMPACT050_H
#define STDIMPACT050_H

#include "ImpactLogic.h"

namespace Combat_Module
{
	namespace Impact_Module
	{
		typedef class StdImpact050_T : public ImpactLogic_T
		{
			public:
				enum
				{
					ID = STD_IMPACT_050,
				};
				class ImpactDataDescriptorIndex_T
				{
					public:
						enum
						{
							IDX_RAGE_REGENERATE_REFIX = 0,
						};
				};

				StdImpact050_T() {};
				~StdImpact050_T() {};
				BOOL IsOverTimed(VOID) const {return TRUE;};
				BOOL IsIntervaled(VOID) const {return FALSE;};

				INT GetRageRegenerateRefix(OWN_IMPACT const& rImp) const
				{
					return Impact_GetImpactDataDescriptorValueByIndex
						(rImp.GetDataIndex(), 
						ImpactDataDescriptorIndex_T::IDX_RAGE_REGENERATE_REFIX,
						rImp.GetSkillLevel()
						);
				};
			public: //message handler
				VOID RefixRageRegeneration(OWN_IMPACT const& rImp, INT& rRageRegeneration) const;
			protected:
			private:
		} SOT_XiaoYao014_T;
	};
};
#endif //STDIMPACT050_H
