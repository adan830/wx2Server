注意：
	1、物品技能（功用，有点像技能）的逻辑ID来自SkillLogic_T中的enum定义， Descriptor Formats 在各个技能的cpp文件里硬实现的。
	2、逻辑ID并非技能ID!!

技能列表：

错骨分筋/摧心裂脾/玄阴至阳/玉碎昆岗/五星连珠/神行百变/指鹿为马/怒发冲冠/天地同寿/火星冲日/偷梁换柱/雷霆之怒/七星落长空/义愤填膺/人鬼同途
LogicID : 0 
消耗部分的格式：|法力需求|无.....
效果描述部分的格式：|生效一次的附加效果1|引导周期的附加效果1|生效一次的附加效果2|引导周期的附加效果2|无....ID :

MingJiaoSkill001 = 迁怒于人
LogicID : 50
消耗部分的格式：|法力需求|无.....
效果描述部分的格式：|专项效果数据索引(标准效果索引)|无....ID :

MingJiaoSkill002 = 厚积薄发
LogicID : 51
消耗部分的格式：|怒气需求|无.....
效果描述部分的格式：|怒气转换物理攻击的转换率（50为 50%的怒气转化成物理攻击力）|无....
