#pragma once
#include <vector>
#include "MeshBatchElement.h"
#include "RenderResource.h"
#include "Platform.h"
#include "MaterialRenderProxy.h"
/*存着一组MeshBatchElement的数据，这组数据有着相通的材质和顶点缓冲
*/

class MeshBatchElement
{
	RHIUniformBuffer* primitiveUniformBuffer;
	const TUniformBuffer<PrimitiveUniformShaderParameters>* primitiveUniformBufferResource;
	const IndexBuffer* indexBuffer;
	MeshBatchElementDynamicIndexBuffer dynamicIndexBuffer;
	union
	{
		uint32* instanceRuns;
		class SplineMeshSceneProxy* splineMeshSceneProxy;
	};
	const void* userData;
	void* vertexFactoryUserData;
	RHIBuffer* indirectArgsBuffer;
	uint32 indirectArgsOffset;
	EPrimitiveMode primitiveIDMode;
	uint32 firstIndex;
	uint32 numPrimitives;
	uint32 numInstances;
	uint32 baseVertexIndex;
	uint32 minVertexIndex;
	uint32 maxVertexIndex;
	int32 userIndex;
	float maxScreenSize;
	float minScreenSize;
	
	uint32 instancedLODIndex : 4;
	uint32 instancedLODRange : 4;
	uint32 bUserDataIsColorVertexBuffer : 1;
	uint32 bIsSplineProxy : 1;
	uint32 bIsInstanceRuns : 1;
	uint32 bForceInstanceCulling : 1;
	uint32 bPreserveInstanceOrder : 1;

	int32 visualizeElementIndex : 8;
	Color skinCacheDebugColor : Color::White;

	MeshBatchDynamicPrimitiveData* dynamicPrimitiveData;
	uint32 dynamicPrimitiveIndex;
	uint32 dynamicPrimitiveInstanceSceneDataOffset;

	inline int32 GetNumberPrimitives()const
	{
		if (bIsInstanceRuns && instanceRuns) {
			int32 count = 0;
			for (uint32 run = 0; run < numInstances; ++run) {
				count += numPrimitives * (instanceRuns[run * 2 + 1] - instanceRuns[run * 2] + 1);
			}
			return count;
		}
		else {
			return numPrimitives * numInstances;
		}
	}

	MeshBatchElement() :
		primitiveUniformBuffer(nullptr),
		primitiveUniformBufferResource(nullptr),
		indexBuffer(nullptr),
		userData(nullptr),
		vertexFactoryUserData(nullptr),
		indirectArgsBuffer(nullptr),
		indirectArgsOffset(nullptr),
		primitiveIDMode(PrimID_FromPrimitiveSceneInfo),
		numInstances(1),
		baseVertexIndex(0),
		userIndex(-1),
		minScreenSize(0.0f),
		maxScreenSize(1.0f),
		instancedLODIndex(0),
		instancedLODRange(0),
		bUserDataIsColorVertexBuffer(false),
		bIsSplineProxy(false),
		bIsInstanceRuns(false),
		bForceInstanceCulling(false),
		bPreserveInstanceOrder(false),
		visualizeElementIndex(INDEX_NONE),
		dynamicPrimitiveData(nullptr),
		dynamicPrimitiveIndex(INDEX_NONE),
		dynamicPrimitiveInstanceSceneDataOffset(INDEX_NONE)
	{
	}


	


};
class MeshBatch
{
	public:
		std::vector<MeshBatchElement>Elements;
		const VertextFactory *VertexFactory;
		const MaterialRenderProxy*materialRenderProxy;
		const LightCacheInterface* LCI;
		HitProxyId batchHitProxyId;
		float tessellationDisablingShadowMapMeshSize;
		uint16 meshIdInPrimitive;
		int8 LODIndex;
		uint8 segmentIndex;
		uint32 reverseCulling : 1;
		uint32 bDisableBackFaceCulling : 1;
		uint32 castShadow : 1;
		uint32 bUseForMaterial : 1;
		uint32 bUseForDepthPasss : 1;
		uint32 bUseAsOccluder : 1;
		uint32 bWireframe : 1;
		uint32 type : PT_NumBits;
		uint32 depthPriorityGroup : SDPG_NumBits;
		uint32 bCanApplyViewModeOverrides : 1;
		uint32 bUseSelectionOutline : 1;
		uint32 bSelectable : 1;
		uint32 bDitheredLODTransition : 1;
		uint32 bRenderToVirtualTexture : 1;
		uint32 RuntimeVirtualTextureMaterialType : RuntimeVirtualTexture::MaterialType_NumBits;
		uint32 bOverlayMaterial : 1;
		uint32 castRayTracedShadow : 1;
		int8 visualizedHLOGIndex;
		int8 visualizeLODIndex;
	private:
};

struct UniformBufferValue
{
	const FShaderParameterMetaData* type = nullptr;
	RHIUniformBuffer* uniformBuffer;
};

