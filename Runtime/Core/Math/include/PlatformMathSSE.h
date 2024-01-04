#pragma once 
#include "xmmintrin.h"
#include "emmintrin.h"
#define FORCEINLINE inline 

namespace TE
{
	namespace SSE
	{
		static FORCEINLINE float InvSqrt(float inValue)
		{
			const __m128 one = _mm_set_ss(1.0f);
			const __m128 y0 =  _mm_set_ss(inValue);
			const __m128 x0 =  _mm_sqrt_ss(y0);
			const __m128 r0 = _mm_div_ss(one, x0);
			float temp;
			_mm_store_ss(&temp, r0);
			return temp;
		}

		static FORCEINLINE double InvSqrt(double inValue)
		{
			const __m128d one = _mm_set_sd(1.0);
			const __m128d y0 = _mm_set_sd(inValue);
			const __m128d x0 = _mm_sqrt_sd(one,y0);
			const __m128d r0 = _mm_div_sd(one, x0);
			double temp;
			_mm_store_sd(&temp, r0);
			return temp;
		}

	}
}
