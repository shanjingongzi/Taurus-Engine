#pragma once

enum {MAX_TEXCOORDS=4};

struct MeshUVChannelInfo
{
	bool initialized;
	bool overrideDesities;
	float localUVDensities[MAX_TEXCOORDS];
};
