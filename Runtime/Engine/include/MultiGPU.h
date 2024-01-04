#pragma once
#include "Platform.h"
#include "AssertionMacros.h"
#if PLATFORM_DESKTOP
#define WITH_SL1 1
#define WITH_MGPU 1
#define MAX_NUM_GPUS 8
extern RHI_API uint32 GNumExplicitGPUsForRendering;
extern RHI_API uint32 GVirtalMGPU;
#else
#define WITH_SLI 0
#define WITH_MGPU  0
#define MAX_NUM_GPUS 1
#define GNumExplicitGPUsForRendering 1
#define GVirtualMGPU 0
#endif
struct RHIGPUMask
{
private:
	uint32 GPUMask;
	FORCEINLINE explicit RHIGPUMask(uint32 inGPUMask):GPUMask{inGPUMask}
	{
#if WITH_MGPU
		check(inGPUMask!=0)
#else
	    check(inGPUMask==1)
#endif
	}

public:
	FORCEINLINE RHIGPUMask():RHIGPUMask(RHIGPUMask::GPU0())
	{
	}

	FORCEINLINE static RHIGPUMask FromIndex(uint32 GPUIndex){return RHIGPUMask(1<<GPUIndex);}

	FORCEINLINE uint32 ToIndex()const
	{
#if WITH_MGPU
		return Math::CountTrailingZeros(GPUMask);
#else
		return 1;
#endif
	}

	FORCEINLINE bool HasSingleIndex()const
	{
#if WITH_MGPU 
		return Math::IsPowerOfTwo(GPUMask);
#else
		return true;
#endif
	}

	FORCEINLINE uint32 GetNumActive()const
	{
#if WITH_MGPU
		return PlatformMath::CountBits(GPUMask);
#else
		return 1;
#endif
	}

	FORCEINLINE uint32 GetLastIndex() const
	{
#if WITH_MGPU
		return FPlatformMath::FloorLog2(GPUMask);
#else
		return 0;
#endif
	}

	FORCEINLINE uint32 GetFirstIndex() const
	{
#if WITH_MGPU
		return FPlatformMath::CountTrailingZeros(GPUMask);
#else
		return 0;
#endif
	}

	FORCEINLINE static const RHIGPUMask GPU0() { return RHIGPUMask(1); }
	FORCEINLINE static const RHIGPUMask All() { return RHIGPUMask((1 << GNumExplicitGPUsForRendering) - 1); }
	FORCEINLINE static const RHIGPUMask FilterGPUsBefore(uint32 GPUIndex) { return RHIGPUMask(~((1u << GPUIndex) - 1)) & All(); }

	struct FIterator
	{
		FORCEINLINE explicit FIterator(const uint32 InGPUMask) : GPUMask(InGPUMask), FirstGPUIndexInMask(0)
		{
#if WITH_MGPU
			FirstGPUIndexInMask = PlatformMath::CountTrailingZeros(InGPUMask);
#endif
		}

		FORCEINLINE explicit FIterator(const RHIGPUMask& InGPUMask) : FIterator(InGPUMask.GPUMask)
		{
		}

		FORCEINLINE FIterator& operator++()
		{
#if WITH_MGPU
			GPUMask &= ~(1 << FirstGPUIndexInMask);
			FirstGPUIndexInMask = PlatformMath::CountTrailingZeros(GPUMask);
#else
			GPUMask = 0;
#endif
			return *this;
		}

		FORCEINLINE FIterator operator++(int)
		{
			FIterator Copy(*this);
			++*this;
			return Copy;
		}

		FORCEINLINE uint32 operator*() const { return FirstGPUIndexInMask; }
		FORCEINLINE bool operator !=(const FIterator& Rhs) const { return GPUMask != Rhs.GPUMask; }
		FORCEINLINE explicit operator bool() const { return GPUMask != 0; }
		FORCEINLINE bool operator !() const { return !(bool)*this; }

private:
	uint32 GPUMask;
	unsigned long FirstGPUIndexInMask;
};



