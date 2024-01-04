#pragma once
#include "StreamableRenderAsset.h"
#include "IInterface_AssetUserData.h"
#include "IInterface_CollisionDataProvider.h"
#include "IAsyncCompilation.h"
#include "StaticMeshRenderData.h"

class StaticMesh:public StreamableRenderAsset,public IInterface_CollisionDataProvider,public IInterface_AssetUserData,public IInterface_AsyncCompilation
{
	/*pointer to the data used to render this static mesh*/
	StaticMeshRenderData* renderData;
	public:
	private:
};
