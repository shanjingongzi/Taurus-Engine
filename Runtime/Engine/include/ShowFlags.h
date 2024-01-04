#pragma once

enum EShowFlagGroup
{
	SFG_Normal,
	SFG_Advanced,
	SFG_CollisionModes,
	SFG_Developer,
	SFG_Visualize,
	SFG_LightTypes,
	SFG_LightingComponents,
	SFG_Lumen,
	SFG_Hidden,
	SFG_Transient,
	SFG_Custom,
	SFG_Max
};

enum EShowFlagsInitMode
{
	ESFIM_Game,
	ESFIM_Editor,
	ESFIM_VREditing,
	ESFIM_ALL0
};

struct EngineShowFlags
{
	enum EShowFlag
	{
		SF_FirstCusom,
	};
	enum class ECustomShowFlag :uint32
	{
		First = 1,
		None = 0xFFFFFF
	};
	bool HitProxies;
};

