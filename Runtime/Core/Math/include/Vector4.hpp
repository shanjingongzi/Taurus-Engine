#pragma once

namespace TE
{
	namespace Math
	{

		template<typename T>
		class TVector4
		{
			typedef T Real;
			union {
				struct {
					Real x;
					Real y;
					Real z;
					Real w;
				};
				Real data[4];
			};
			TVector4();
			TVector4(Real Inx, Real InY, Real InZ, Real InW) :x(Inx), Y(InY), z(InZ), w(InZ) {}
		};
	}
}

using Vector4 = TE::Math::TVector4<double>;
using Vector4f = TE::Math::TVector4<float>;
using Vector4i = TE::Math::TVector4<int>;