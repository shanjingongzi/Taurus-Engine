#pragma once
#include "Noncopyable.h"
#include "MultiGPU.h"
#include <memory>
#include <string.h>
class RHICommandListBase:public NonCopyable
{
public:
	enum class ERecordingThread
	{
		Render,
		Any
	};
protected:
	RHICommandListBase(RHIGPUMask GPUMask, ERecordingThread recordingThread);
public:
	RHICommandListBase(RHICommandListBase& other);
	~RHICommandListBase();
	inline bool IsImmediate()const;
	inline RHICommandListImmediate& GetAsImmediate();
	const int32 GetUsedMemroy()const;
	
	void AddDispatchPrerequisite(const GraphEventRef& prereq);

	void FinishRecording();

	void HandleRTThreadTaskComplection(const GraphEventRef& completionGraphEvent)
	{
		FinishRecording();
	}

	void SetCurrentStat(TStatId stat);

	FORCEINLINE void* Alloc(int64 allocSize, int64 alignment)
	{
		return malloc(allocSize);
	}

	FORCEINLINE void AllocCopy(const void* sourceData, int64 allocSize, int64 alignment)
	{
		void* newData = Alloc(allocSize, alignment);
		memcpy(newData, sourceData, allocSize);
	}

	template<typename T>
	FORCEINLINE void* Alloc()
	{
		return Alloc(sizeof(T), alignof(T));
	}


	

};

class RHIComputeCommandList :public RHICommandListBase
{

};

class RHICommandList:public RHIComputeCommandList
{
public:
protected:
	using RHIComputeCommandList::OnBoundShaderChanged;
private:

};
class RHICommandListImmediate :public RHICommandList
{

};