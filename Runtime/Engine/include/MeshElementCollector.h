#pragma once
#include "Platform.h"
#include <functional>
#include "RHIFeatureLevel.h"
#include <Array.hpp>
#include <MeshBatch.h>


class CORE_API MeshElementCollector
{
	inline PrimitiveDrawInterface*GetPDI(int32 viewIndex)
	{
		return simpleElementCollectors[viewIndex];
	}

	inline MeshBatch&AllocateMesh();

	GlobalDynamicIndexBuffer &GetDynamicIndexBuffer();

	GlobalDynamicVertexBuffer &GetDynamicVertexBuffer();

	GlobalDynamicReadBuffer&GetDynamicReadBuffer();

	uint32 GetMeshBatchCount(uint32 viewIndex)const;

	uint32 GetMeshEelementCount(uint32 viewIndex)const;

	void AddMesh(int32 viewIndex,MeshBatch &meshBatch);

	void RegisterOneFrameMaterialProxy(MaterialRenderProxy *proxy);

	template<typename T,typename ...ARGS>
	T &AllocateOneFrameResource(ARGS &&...args)
	{
	}

	inline bool ShouldUseTasks()const;

	inline void  AddTask(std::function<void()>&&task);
	inline void  AddTask(std::function<void()>&task);

	void ProcessTasks();
	
	inline ERHIFeatureLevel::Type GetFeatureLevel()const
	{
		return featureLevel;
	}

protected:

	MeshElementCollector(ERHIFeatureLevel::Type featureLevel, SceneRenderingBulkObjectAllocator& allocator);
	~MeshElementCollector();

	void DeleteTemporaryProxies();

	void SetPrimitive(const PrimitiveSceneProxy* primitiveSceneProxy, HitProxyId defayultHitProxyId);

	void ClearViewMeshArrays();

	void AddViewMeshArray(
		SceneView* view,
		Array<MeshBatchAndRelevance>viewMeshs,
		SimpleElementCollector* viewSimpleElementCollector,
		GPUScenePrimitiveCollector* dynamicPrimitiveCollector,
		ERHIFeatureLevel::Type featureType,
		GlobalDynamicIndexBuffer* dynamicIndexBuffer,
		GlobalDynamicVertexBuffer* dynamicVertexBuffer,
		GlobalDynamicReadBuffer* dynamicReadBuffer
	);

	Array<MeshBatch>meshBatchStorage;
	Array<Array<MeshBatchAndRelevance>*>meshBatches;

	Array<SimpleElementCollector>simpleElementCollector;
	Array<SceneView* >views;
	Array<uint16>meshIdInPrimitivePreview;

	Array<MaterialRenderProxy*>temporaryProxies;
	SceneRenderingBulkObjectAllocator* oneFrameResources;
	const PrimitiveSceneProxy* primitiveSceneProxy;
	GlobalDynamicIndexBuffer* dynamicIndexBuffer;
	GlobalDynamicVertexBuffer* dynamicVertexBuffer;
	GlobalDynamicReadBuffer* dynamicReadBuffer;
	ERHIFeatureLevel::Type featureLevel;
	const bool useAsyncTasks;
	Array <std::function<void()>>paralleTasks;
	Array<GPUScenePrimitiveCollector >dynamicPrimitiveCollector;
	friend class SceneRenderer;
	friend class DeferredShadingSceneRenderer;
	friend class ProjectedShadowInfo;
	friend class CardPageRenderData;
	friend class ViewFamilyInfo;
};
