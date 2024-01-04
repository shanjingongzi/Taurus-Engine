#pragma once
#include "MeshComponent.h"
#include "StaticMesh.h"
class StaticMeshComponent:public MeshComponent
{
public:
	int forceLoadModel;
	int previousLODLevel_DEPRECATED;
	int minLOD;
	int subDevisionStepSize;
	StaticMesh* staticMesh;
	void SetStaticMeshInternal(StaticMesh*);
protected:
private:

};
