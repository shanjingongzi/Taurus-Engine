#pragma once
#include "RHIFeatureLevel.h"
#include "World.h"
class PrimitiveComponent;
class RHICommandListImmediate;
class RDGBuilder;
enum EUpdateAllPrimitiveSceneInfosAsyncOps
{
	None = 0,
	CacheMeshDrawCommands = 1 << 0,
	CreateLightPrimitiveInteractions = 1 << 1,
	All=CacheMeshDrawCommands | CreateLightPrimitiveInteractions
};

class SceneInterface
{
	public:
		virtual void AddPrimitive(PrimitiveComponent* primitive) = 0;
		virtual void RemovePrimitive(PrimitiveComponent* primitive) = 0;
		virtual void ReleasePrimitive(PrimitiveComponent* primitive) = 0;


		virtual void UpdateAllPrimitiveSceneInfos(RDGBuilder& graphBuilder, EUpdateAllPrimitiveSceneInfosAsyncOps AsyncOps = EUpdateAllPrimitiveSceneInfosAsyncOps::None)=0;
		void UpdateAllPrimitiveSceneInfos(RHICommandListImmediate& rhiCmdList);

		virtual void UpdatePrimitiveTransform(PrimitiveComponent* primitive);
		virtual void UpdatePrimitiveOcclusionBoundSlack(PrimitiveComponent* primitive, float newSlack) = 0;
		virtual void UpdatePrimitiveAttachment(PrimitiveComponent* primitive) = 0;

		virtual void UpdatePrimitiveInstnaces(PrimitiveComponent* primive) = 0;

		virtual void UpdateCustomPrimitiveData(PrimitiveComponent* primitive) = 0;

		virtual World* GetWorld()const = 0;
protected:
	ERHIFeatureLevel::Type featureLevel;
	friend class SceneViewStateReference;
};
