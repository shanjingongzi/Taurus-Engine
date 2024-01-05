#pragma once
#include <Platform.h>

enum class ERHIAccess :uint32
{
	Unknown=0,
	CPURead=1<<0,
	Present=1<<1,
	IndirectArgs=1<<2,
	VertexOrIndexBuffer=1<<3,
	SRVCompute=1<<4,
	SRVGraphics=1<<5,
	CopySrc=1<<6,
	ResolveSrc=1<<7,
	DSVRead=1<<8,

	UAVCompute=1<<9,
	UAVGraphics=1<<10,
	RTV=1<<11,
	CopyDest=1<<12,
	ResolveDest=1<<13,
	DSVWrite=1<<14,
	BVHRead=1<<15,
	BVHWrite=1<<16,
	Discard=1<<17,
	ShadingRateSource=1<<18,
	Last=ShadingRateSource,
	None=Unknown,
	Mask=(Last<<1)-1,
	SRVMask=SRVCompute | SRVGraphics,
};

enum class ERHIInterfaceType
{
	Hidden,
	Null,
	D3D11,
	D3D12,
	Vulkan,
	Metal,
	Agx,
	OpenGL
};

enum class ERHIFeatureSupport:uint8
{
	Unsupported,
	RutimeDependent,
	RuntimeGuaranteed,
	Num,
	NumBits
};
//绑定优化，减少 cpu到gpu的绑定次数
enum class ERHIBindlessSupport:uint8
{
	Unsupported,
	RayTracingOnly,
	AllShaderTypes,
	NumBits=2
};
//着色器频率
enum EShaderFrequency:uint8
{
	SF_Vertex=0,
	SF_Mesh=1,
	SF_Amplification=2,
	SF_Pixel=3,
	SF_Geometry=4,
	SF_Compute=5,
	SF_RayGen=6,
	SF_RayMiss=7,
	SF_RayHitGroup=8,
	SF_RayCallable=9,
	SF_NumFrequencies=10,
	SF_NumGraphicsFrequencies=5,
	SF_NumStanderFrequencies=6,
	SF_NumBits=4
};

enum ERHIResourceType : uint8
{
	RRT_None,

	RRT_SamplerState,
	RRT_RasterizerState,
	RRT_DepthStencilState,
	RRT_BlendState,
	RRT_VertexDeclaration,
	RRT_VertexShader,
	RRT_MeshShader,
	RRT_AmplificationShader,
	RRT_PixelShader,
	RRT_GeometryShader,
	RRT_RayTracingShader,
	RRT_ComputeShader,
	RRT_GraphicsPipelineState,
	RRT_ComputePipelineState,
	RRT_RayTracingPipelineState,
	RRT_BoundShaderState,
	RRT_UniformBufferLayout,
	RRT_UniformBuffer,
	RRT_Buffer,
	RRT_Texture,
	// @todo: texture type unification - remove these
	RRT_Texture2D,
	RRT_Texture2DArray,
	RRT_Texture3D,
	RRT_TextureCube,
	// @todo: texture type unification - remove these
	RRT_TextureReference,
	RRT_TimestampCalibrationQuery,
	RRT_GPUFence,
	RRT_RenderQuery,
	RRT_RenderQueryPool,
	RRT_ComputeFence,
	RRT_Viewport,
	RRT_UnorderedAccessView,
	RRT_ShaderResourceView,
	RRT_RayTracingAccelerationStructure,
	RRT_StagingBuffer,
	RRT_CustomPresent,
	RRT_ShaderLibrary,
	RRT_PipelineBinaryLibrary,

	RRT_Num
};


enum class EBufferUsageFlags:uint32
{
	None=0,
	Static=1<<0,
	Dynamic =1<<1,
	Volatile =1<<2,
	UnorderedAccess =1<<3,
	ByteAddressBuffer =1<<4,
	SourceCopy=1<<5,
	StreamOutput =1<<6,
	DrawIndirect=1<<7,
	ShaderResource=1<<8,
	keepCPUAccessible=1<<9,
	FastVRAM =1<<10,
	Shared=1<<12,
	AccelerationStructure=1<<13,
	VertexBuffer=1<<14,
	IndexBuffer=1<<15,
	StructuredBuffer=1<<16,
	MultiGPUAllocate=1<<17,
	MultiGPUGraphIgnore=1<<18,
	RayTracingScratch=(1<<19)|UnorderedAccess,
	NullResource=1<<20,
	AnyDynamic=(Dynamic |Volatile)
};

#define BUF_None                   EBufferUsageFlags::None
#define BUF_Static                 EBufferUsageFlags::Static
#define BUF_Dynamic                EBufferUsageFlags::Dynamic
#define BUF_Volatile               EBufferUsageFlags::Volatile
#define BUF_UnorderedAccess        EBufferUsageFlags::UnorderedAccess
#define BUF_ByteAddressBuffer      EBufferUsageFlags::ByteAddressBuffer
#define BUF_SourceCopy             EBufferUsageFlags::SourceCopy
#define BUF_StreamOutput           EBufferUsageFlags::StreamOutput
#define BUF_DrawIndirect           EBufferUsageFlags::DrawIndirect
#define BUF_ShaderResource         EBufferUsageFlags::ShaderResource
#define BUF_KeepCPUAccessible      EBufferUsageFlags::KeepCPUAccessible
#define BUF_FastVRAM               EBufferUsageFlags::FastVRAM
#define BUF_Transient              EBufferUsageFlags::Transient
#define BUF_Shared                 EBufferUsageFlags::Shared
#define BUF_AccelerationStructure  EBufferUsageFlags::AccelerationStructure
#define BUF_RayTracingScratch	   EBufferUsageFlags::RayTracingScratch
#define BUF_VertexBuffer           EBufferUsageFlags::VertexBuffer
#define BUF_IndexBuffer            EBufferUsageFlags::IndexBuffer
#define BUF_StructuredBuffer       EBufferUsageFlags::StructuredBuffer
#define BUF_AnyDynamic             EBufferUsageFlags::AnyDynamic
#define BUF_MultiGPUAllocate       EBufferUsageFlags::MultiGPUAllocate
#define BUF_MultiGPUGraphIgnore    EBufferUsageFlags::MultiGPUGraphIgnore
#define BUF_NullResource           EBufferUsageFlags::NullResource
