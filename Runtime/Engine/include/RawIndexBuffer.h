#pragma once
#include "RenderResource.h"

class RawStaticIndexBuffer:IndexBuffer
{
public:

private:
	int32 CachedNumIndiceis;
	bool b32Bit;
	bool bShouldExpandTo32Bit;
};