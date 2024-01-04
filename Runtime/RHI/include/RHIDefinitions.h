#pragma once
#include <Platform.h>

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