#pragma once
#include "StaticMeshVertexDataInterface.h"
#include "RHIFwd.h"
#include "RenderResource.h"
class StaticMeshVertexBuffer
{
private:
	class TangentsVertexBuffer :public VertexBuffer
	{

	}tangentVertexBuffer;

	class TexcoordVertexBuffer :public VertexBuffer
	{

	}texcoordVertexBuffer;

	StaticMeshVertexDataInterface*tangentsData;
	ShaderResourceViewRHIRef tagentsSRV;
	
	StaticMeshVertexDataInterface *texcoordData;
	ShaderResourceViewRHIRef textureCoordinatesSRV;

	uint8* tangentsDataPtr;
	uint8* texCoordDataPtr;

	uint32 tangentsStride;

	uint32 texCoordStride;

	uint32 numTexCoords;

	uint32 numVertices;

	bool userFullPrecisionUVs;
	bool userHighPrecisionTangentBasis;
	bool needCPUAccess=true;


public:
	StaticMeshVertexBuffer();
	~StaticMeshVertexBuffer();
	void CleanUp();
	void Init(int InNumVertices,int InNumTexCoords,bool InNumTexCoords,bool needCPUAccess=true);
	void Init(const std::vector<StaticMeshBuildVertex>&InVertices,int InNumberTexCoords,bool needCPUAccess=true);
	void Init(const StaticMeshVertexBuffer &InVertexBuffer,bool needCPUAccesss=true);
	int GetNumVertices()const;
	int GetNumCoords()const;
	bool GetUseFullPrecisionUVs()const;
        bool 
};
