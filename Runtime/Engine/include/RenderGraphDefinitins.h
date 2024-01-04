#pragma once
#include "Platform.h"
enum class ERDGBuilderFlags
{
	None=0,
	AllowParallelExecute=1<<0
};

enum class ERDGPassFlags:uint16
{
	None=0,
	Raster=1<<0,
	Compute=1<<1,
	AsyncCompute=1<<2,
	Copy=1<<3,
	NeverCull=1<<4,
	SkipRenderPasss=1<<5,
	NeverMerge=1<<6,
	NeverParallel=1<<7,
	ParallelTranslate=1<<8,
	RendBack=Copy |NeverCull
};

enum class RDGBufferFlags:uint8
{
	None=0,
	MultiFrame=1<<0,
	SkipTracking=1<<1,
	ForceImmediateFirstBarrier=1<<2,
	ReadOnly,
	ForceTarcking
};


enum class ERDGTextureFlags:uint8
{
	None=0,
	MultiFRAME=1<<0,
	SkipTracking=1<<1,
	ForceImmediateFirstBarrier=1<<2,
	MaintainCompression=1<<3,
	ReadOnly,
	ForceTracking
};


