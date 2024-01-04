#ifndef VECTOR2_HPP
#define VECTOR2_HPP

namespace TE
{
namespace Math
{
template<typename T>
struct TVector2
{
	inline TVector2(T x, T y) :x{ x }, y{ y }{}
	inline TVector2() : x{ 0 }, y{ 0 }{}
	T operator[](size_t index) { return data[index]; }
	union {
		struct {
			T x;
			T y;
		};
		T data[2];
	};
	friend bool operator==(const TVector2& a, const TVector2& b) {
		return a.x == b.x && a.y == b.y;
	}
	
};

}
}
using Vector2 = TE::Math::TVector2<double>;
using Vector2f = TE::Math::TVector2<float>;

#endif
