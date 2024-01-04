#pragma once
#include "Platform.h"
#include "RenderResource.h"
/*单个网格模型的数据，包换渲染器中所需的部分数据，如顶端，索引，UniformBuffer及各种标识等
 */

class MeshBatchElement
{
public:
	class RHIUniformBuffer* primitiveUniformBuffer;
	const IndexBuffer*indexBuffer;
	union{
		int *InstanceRuns;
		class SplineMeshSceneProxy;
	};
	const void *UserData;
	void *vertexFactoryUserData;
	class RHIVertexBuffer*indirectAragsBuffer;
	uint32 indirectArgsOffset;
	int firstIndex;
	int numPrimitives;
	int numInstances;
	int BaseVertexIndex;
	int MinVertexIndex;
	int MaxVertexIndex;
	int userIndex;
	int minScreeeSize;
	float maxScreenSize;
	int GetNumberPrimitives()const
	{
	}
private:
};

