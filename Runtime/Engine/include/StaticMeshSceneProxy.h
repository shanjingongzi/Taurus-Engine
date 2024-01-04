#pragma once
#include "PrimitiveSceneProxy.h"
class StaticMeshSceneProxy
{
	public:
		virtual void GetDynamicMeshElement(const Array<const SceneView*>views,const SceneViewFamily&viewFamily,uint32 visibilityMap,MeshElementCollector &collector);
		virtual bool GetMeshElement(int32 LODIndex,int32 batchIndex,int32 ElementIndex,uint8depthPriorityGroup,bool useSelectionOutline,bool allowPreculledIndeices,FMeshBatch &outMeshBatch)const;


	private:
};

