#include "RenderResource.h"


RenderResource::RenderResource() :listIndex(INDEX_NONE), featureLevel(ERHIFeatureLevel::Num)
{
}

RenderResource::RenderResource(ERHIFeatureLevel::Type inFeatureLevel):listIndex(INDEX_NONE),featureLevel(inFeatureLevel)
{

}
void RenderResource::InitResource()
{
}

void RenderResource::ReleaseResource() 
{
}

void RenderResource::UpdateRHI()
{

}


