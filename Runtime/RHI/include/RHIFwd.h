#pragma once
#include <Platform.h>

namespace ERHIFeatureLevel
{
    enum Type:int;
}
//base types
enum EShaderPlatform:uint16;
enum ECubeFace:uint16;
enum EPixelFormat:uint8;
enum class EPixlFormatChannelflags:uint8;
enum class EBufferUsageFlags:uint32;
enum class ETextureCreateFlags:uint64;

//command lists
class RHICommandListBase;
class RHIComputeCommandList;
class RHICommandList;
class RHICommandListImmediate;

struct RHIResourceUpdateInfo;
struct RHIResourceUpdatebacher;

struct SamplerStateInitializerRHI;
struct RasterizerStateInitializerRHI;
struct DepthStencilStateInitializerRHI;
class BlendStateInitializerRHI;


//resource

class RHIAmplificationShader;
class RHIBlendState;
class RHIBoundShaderState;
class RHIBuffer;
class RHIComputeFence;
class RHIComputePipelineState;
class RHIcomputeShader;
class RHICustomPresent;
class RHIGeometryShader;
class RHIGPUFence;
class RHIGraphicsPipelineState;
class RHIMeshShader;
class RHIPipelineBinnaryLibray;
class RHIPixelshader;
class RHIRasterizerState;
class RHIRayTracingGeometry;
class RHIRayTracingPipelineState;
class RHIRayTracingScene;
class RHIRayTracingShader;
class RHIRenderQuery;
class RHIRenderQueryPool;
class RHIResource;
class RHISamplerState;
class RHIShader;
class RHIShaderLibrary;
class RHIShaderResourceView;
class RHIStagingBuffer;
class RHITexture;
class RHITextureReference;
class RHITimestampCalibrationQuery;
class RHIUniformBuffer;
class RHIUnorderedAccessView;
class RHIVertexDeclaration;
class RHIVertexShader;
class RHIViewableResource;
class RHIViewport;

struct FHIUnoformBufferLayout;





