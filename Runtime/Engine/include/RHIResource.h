#pragma once
#include "RHIDefinitions.h"
#include <Platform.h>
#include <string>
#include "Array.hpp"
#include "RefCounting.h"
#include "MemoryLayout.h"
class RHIResource
{
	public:
		RHIResource(ERHIResourceType inResourceType);
		virtual ~RHIResource();
		unsigned int AddRef()const;
};
 
class RHIViewableResource :public RHIResource
{
};
struct RHIUniformBufferResource
{

};

__pragma (warning(push))
__pragma (warning(disable: 4995))
__pragma (warning(disable: 4996))
template<int counter>
struct InternalLinkType;
template<> struct InternalLinkType<477 - 1> 
{
	static void Initialize(FTypeLayoutDesc& TypeDesc)
	{
		InternalLinkType<477 - CounterBase + 1>::Initialize(TypeDesc); 
		alignas(FFieldLayoutDesc) static uint8 FieldBuffer[sizeof(FFieldLayoutDesc)] = { 0 };
		FFieldLayoutDesc& FieldDesc = *(FFieldLayoutDesc*)FieldBuffer; 
		FieldDesc.Name = L"GraphUniformBuffers";
		FieldDesc.UFieldNameLength = Freeze::FindFieldNameLength(FieldDesc.Name); 
		FieldDesc.Type = &StaticGetTypeLayoutDesc< TMemoryImageArray<FRHIUniformBufferResource>>();
		FieldDesc.WriteFrozenMemoryImageFunc = TGetFreezeImageFieldHelper< TMemoryImageArray<FRHIUniformBufferResource>>::Do();
		FieldDesc.Offset = ((::size_t) & reinterpret_cast<char const volatile&>((((DerivedType*)0)->GraphUniformBuffers)));
		FieldDesc.NumArray = 1u; FieldDesc.Flags = EFieldLayoutFlags::MakeFlags();
		FieldDesc.BitFieldSize = 0u; 
		FieldDesc.Next = TypeDesc.Fields; 
		TypeDesc.Fields = &FieldDesc;
	}
};
__pragma (warning(pop))
struct RHIUniformBufferLayoutInitializer
{
public:
	RHIUniformBufferLayoutInitializer() = default;
	explicit RHIUniformBufferLayoutInitializer(const TCHAR* name) :name{ name }
	{

	}

	explicit RHIUniformBufferLayoutInitializer(const TCHAR* name, uint32 constantBufferSize)
		:name{ name },
		constantBufferSize(constantBufferSize)
	{
		ComputeHash();
	}

	inline uint32 GetHash()const
	{
		return hash;
	}
	void ComputeHash()
	{

	}

};

struct RHIUniformBufferLayout :public RHIResource
{
	RHIUniformBufferLayout() = delete;
	explicit RHIUniformBufferLayout(const RHIUniformBufferLayoutInitializer&initializer):
		RHIResource(RRT_UniformBufferLayout)
	{

	}
	const std::string name;
	const Array<RHIUniformBufferResource>Resource;
	const Array<RHIUniformBufferResource>grahResources;
	const Array<RHIUniformBufferResource>graphTextures;
	const Array<RHIUniformBufferResource>graphBuffers;
	const Array<RHIUniformBufferResource>graphUniformBuffers;
	const Array<RHIUniformBufferResource>uniformBuffers;
	const uint32 hash;
	const uint32 constantBufferSize;
	const uint16 renderTargetsOffset;
	const UniformBufferStaticSlot staticSlot;
	const EUniformBufferBindingFlags bindingFlags;
	const bool hasNonGraphOutputs;
	const bool bNoEmulatedUniformBuffer;
};

class RHIView :public RHIResource
{
public:
	RHIView(ERHIResourceType inResourceType, RHIViewableResource* inParentResource)
		:RHIResource(inResourceType), parentResource(inParentResource)
	{

	}
	virtual RHIDescriptorHandle GetBindlessHandle()const;
	RHIViewableResource* GetParentResource()const;
protected:
	void SetParentResource(RHIViewableResource* inParentResource) {
		parentResource = inParentResource;
	}
private:
	RHIViewableResource* parentResource;
};

class RHIShaderResourceView :public  RHIView
{
};


class  RHIBuffer :public RHIViewableResource
{
private:
	uint32 size{};
	uint32 stride{};
	EBufferUsageFlags usage{};
};

class RHIUniformBuffer :public RHIResource
{
public:
	RHIUniformBuffer() = delete;
	RHIUniformBuffer(const RHIUniformBufferLayout* layout) :RHIRensource(RRT_UniformBuffer), layout{ layout }, layoutConstantBufferSize(layout->constanceBufferSize)
	{

	}
};
