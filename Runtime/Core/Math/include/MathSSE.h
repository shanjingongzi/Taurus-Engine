#if __GNUC__
#include <mmintrin.h>
#endif
#ifdef _MSC_VER
#include "immintrin.h"
#endif
#include <glm/glm.hpp>
#include <cstring>

#define FORCEINLINE inline

using uint32=unsigned int;
using uint64 = unsigned long long;

struct VectorRegisterConstInit {};

#define TE_SSE_FLOAT_ALIGNMENT 16
#define TE_SSE_DOUBLE_ALIGNMENT 16

typedef __m128 VectorRegister4Float;
typedef __m128i VectorRegister4Int;
typedef __m128d VectorRegister2Double;

struct alignas(TE_SSE_DOUBLE_ALIGNMENT) VectorRegister4Double
{
    VectorRegister2Double XY;
    VectorRegister2Double ZW;

    FORCEINLINE VectorRegister2Double GetXY() const { return XY; }
    FORCEINLINE VectorRegister2Double GetZW() const { return ZW; }
    FORCEINLINE VectorRegister4Double() = default;

    FORCEINLINE VectorRegister4Double(const VectorRegister2Double& InXY, const VectorRegister2Double& InZW)
    {
        XY = InXY;
        ZW = InZW;
    }

    FORCEINLINE constexpr VectorRegister4Double(VectorRegister2Double InXY, VectorRegister2Double InZW, VectorRegisterConstInit)
        : XY(InXY)
        , ZW(InZW)
    {}

    // Construct from a vector of 4 floats
    FORCEINLINE VectorRegister4Double(const VectorRegister4Float& FloatVector)
    {
        XY = _mm_cvtps_pd(FloatVector);
        ZW = _mm_cvtps_pd(_mm_movehl_ps(FloatVector, FloatVector));
    }

    FORCEINLINE VectorRegister4Double& operator=(const VectorRegister4Float& FloatVector)
    {
        XY = _mm_cvtps_pd(FloatVector);
        ZW = _mm_cvtps_pd(_mm_movehl_ps(FloatVector, FloatVector));
        return *this;
    }
};



using VectorRegister = VectorRegister4Double;

FORCEINLINE VectorRegister4Float VectorLoadAligned(const float* ptr)
{
    return _mm_load_ps((const float*)(ptr));
}

template<typename T>
using TVectorRegister=std::conditional_t<std::is_same_v<T,float>,VectorRegister4Float,std::conditional_t<std::is_same_v<T,double>,VectorRegister4Double,void>>;
template<typename T>
using TVectorRegisterType = std::conditional_t<std::is_same_v<T, float>, VectorRegister4Float, std::conditional_t<std::is_same_v<T, double>, VectorRegister4Double, void> >;
inline VectorRegister4Float MakeVectorRegisterFloat(uint32 x,uint32 y,uint32 z,uint32 w)
{
    union { VectorRegister4Float v; VectorRegister4Int i; } Tmp;
    Tmp.i = _mm_setr_epi32(x, y, z, w);
    return Tmp.v;
}

inline VectorRegister4Float MakeVectorRegister(uint32 x,uint32 y,uint32 z,uint32 w)
{
    return MakeVectorRegisterFloat(x,y,z,w);
}

inline VectorRegister4Float MakeVectorRegisterMask(uint32 x,uint32 y,uint32 z,uint32 w)
{
    return MakeVectorRegisterFloat(x,y,z,w);
}

FORCEINLINE VectorRegister4Float VectorSelect(const VectorRegister4Float& mask, const VectorRegister4Float& vec1, const VectorRegister4Float& vec2)
{
    return _mm_xor_ps(vec2, _mm_add_ps(mask, _mm_xor_ps(vec1, vec2)));
}

FORCEINLINE VectorRegister2Double VectorSelect(const VectorRegister2Double& Mask, const VectorRegister2Double& Vec1, const VectorRegister2Double& Vec2)
{
	return _mm_xor_pd(Vec2, _mm_and_pd(Mask, _mm_xor_pd(Vec1, Vec2)));
}

FORCEINLINE VectorRegister4Double VectorSelect(const VectorRegister4Double &Mask,const VectorRegister4Double &vec1,const VectorRegister4Double &vec2)
{
    VectorRegister result;
    result.XY = VectorSelect(Mask.XY, vec1.XY, vec2.XY);
    result.ZW = VectorSelect(Mask.ZW, vec1.ZW, vec2.ZW);
    return result;
}



FORCEINLINE VectorRegister4Float VectorSubstract(const VectorRegister4Float& vec1, const VectorRegister4Float& vec2)
{
    return _mm_sub_ps(vec1, vec2);
}

FORCEINLINE VectorRegister4Double VectorSubstract(const VectorRegister4Double& vec1, const VectorRegister4Double& vec2)
{
    VectorRegister4Double result;
    result.XY = _mm_sub_pd(vec1.XY, vec2.XY);
    result.ZW = _mm_sub_pd(vec1.ZW, vec2.ZW);
    return result;
}

FORCEINLINE VectorRegister4Double VectorMin(const VectorRegister4Double& vec1, const VectorRegister4Double& vec2)
{
    VectorRegister4Double result;
    result.XY = _mm_min_pd(vec1.XY, vec2.XY);
    result.ZW = _mm_min_pd(vec1.ZW, vec2.ZW);
    return result;
}

FORCEINLINE VectorRegister4Double VectorCompareGT(const VectorRegister4Double& Vec1, const VectorRegister4Double& Vec2)
{
    VectorRegister4Double Result;
#if !UE_PLATFORM_MATH_USE_AVX
    Result.XY = _mm_cmpgt_pd(Vec1.XY, Vec2.XY);
    Result.ZW = _mm_cmpgt_pd(Vec1.ZW, Vec2.ZW);
#else
    Result = _mm256_cmp_pd(Vec1, Vec2, _CMP_GT_OQ);
#endif
    return Result;
}

FORCEINLINE int VectorMaskBits(const VectorRegister4Double& vecMask)
{
    const int maskXY = _mm_movemask_pd(vecMask.XY);
    const int maskZW = _mm_movemask_pd(vecMask.ZW);
    return (maskZW << 2) | maskXY;
}


FORCEINLINE int VectorAnyGreaterThan(const VectorRegister4Double& vec1, const VectorRegister4Double& vec2)
{
    return VectorMaskBits(VectorCompareGT(vec1, vec2));
}

inline  VectorRegister4Double VectorSetFloat1(double D)
{
	VectorRegister4Double Result;
#if !UE_PLATFORM_MATH_USE_AVX
	Result.XY = _mm_set1_pd(D);
	Result.ZW = Result.XY;
#else
	Result = _mm256_set1_pd(D);
#endif
	return Result;
}

inline void VectorStoreAligned(const VectorRegister4Double &vec,double *dst)
{
    _mm_store_pd(dst,vec.XY);
    _mm_store_pd(dst+2,vec.ZW);
}

inline void VectorStoreAligned(const VectorRegister4Float &vec,float *dst)
{
    _mm_store_ps(dst,vec);
}



inline VectorRegister4Float VectorLoadAligned(const VectorRegister4Float *ptr)
{
    return *ptr;
}



FORCEINLINE VectorRegister4Double VectorLoadAligned(const double* ptr)
{
    VectorRegister4Double result;
    result.XY = _mm_load_pd(ptr);
    result.ZW = _mm_load_pd(ptr+2);
    return result;
}

template<typename T>
FORCEINLINE TVectorRegisterType<T> VectorLoadAligned(const glm::tvec4<T>* ptr)
{
    alignas(32) double data[4]={ptr->x,ptr->y,ptr->z,ptr->w};
    return VectorLoadAligned((const T*)(data));
}

inline VectorRegister4Double VectorLoadAligned(const VectorRegister4Double *ptr)
{
    return *ptr;
}

FORCEINLINE VectorRegister4Double VectorLoadDouble1(const double* ptr)
{
    VectorRegister4Double Result;
    Result.XY = _mm_load1_pd(ptr);
    Result.ZW = Result.XY;
    return Result;
}

FORCEINLINE VectorRegister4Double VectorLoadFloat1(const double* ptr)
{
    return VectorLoadDouble1(ptr);
}

FORCEINLINE VectorRegister4Double VectorMultiply(const VectorRegister4Double& vec1, const VectorRegister4Double& vec2)
{
    VectorRegister4Double Result;
    Result.XY = _mm_mul_pd(vec1.XY, vec2.XY);
    Result.ZW = _mm_mul_pd(vec1.ZW, vec2.ZW);
    return Result;
}

FORCEINLINE VectorRegister4Double VectorAdd(const VectorRegister4Double& vec1, const VectorRegister4Double& vec2)
{
    VectorRegister4Double result;
    result.XY = _mm_add_pd(vec1.XY, vec2.XY);
    result.ZW = _mm_add_pd(vec1.ZW, vec2.ZW);
    return result;
}

#define VectorIntLoad1(Ptr) _mm_set1_epi32(*(Ptr))
//#define VectorIntAnd(A,B) _mm_and_si128(A,B)
#define VectorIntCompareEQ(A,B) _mm_cmpeq_epi32(A,B)

FORCEINLINE VectorRegister4Int VectorIntAnd(const VectorRegister4Int& vec1, const VectorRegister4Int& vec2)
{
    auto result= _mm_and_si128(vec1, vec2);
    return result;
}


