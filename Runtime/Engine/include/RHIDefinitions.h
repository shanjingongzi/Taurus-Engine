#pragma once
#include "Platform.h"
enum ERHIResourceType:unsigned char
{
	RRT_None,

	RRT_SamplerState,
	RRT_RasterizerState,
	RRT_UniformBufferLayout,
};

enum class EBufferUsageFlags :uint32
{
	None = 0,
	Static = 1 << 0,
	Dynamic =1<<1,
	Volatile=1<<2
};

using UniformBufferStaticSlot = uint8;

enum class EUniformBufferBindingFlags :uint8
{
	Shader = 1 << 0,
	Static = 1 << 1,
	StaticAndShader = Static | Shader
};

enum ERHIDescriptorHeapType : unsigned char
{

};

struct RHIDescriptorHandle
{
	RHIDescriptorHandle() = default;
	RHIDescriptorHandle(ERHIDescriptorHeapType inType, unsigned int inIndex) :index(inIndex), type(inType)
	{

	}

	inline unsigned int GetIndex()const {
		return index;
	}

	inline ERHIDescriptorHeapType GetType()const {
		return (ERHIDescriptorHeapType)type;
	}

	inline  unsigned char GetRowType()const {
		return type;
	}
	
private:
	unsigned int index;
	unsigned char type;
};
