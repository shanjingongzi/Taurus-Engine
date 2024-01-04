#pragma once
#include <string>

class IInterface_CollisionDataProvider
{
	public:
		virtual bool GetPhysicsTriMeshData(struct FTriMeshCollisionData* collisionData, bool InUseAllTriData) { return false; }
		virtual bool GetTriMeshSizeEstimates(struct TriMeshCollisionDataEstimates& outTriMeshEstimates, bool InUseAllTriData) { return false; }
		virtual bool ContainsPhysicsTriMMeshData(bool useAllTriData)const { return false; }
		virtual bool PollAsAsyncTriMeshData(bool useAllTriData)const {return false;}
		virtual bool WantsNegXTriMesh() { return false; }
		virtual void GetMeshId(std::string& OutMeshId) {};
	private:
};

