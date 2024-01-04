#pragma once
#include "glm/glm.hpp"
#include "Vector.hpp"
template<typename T>
struct TBox
{
public:
	typedef typename TE::Math::TVector<T> Vector;
	using Real = T;
	using Vector4 = glm::tvec4<T>;
	Vector min;
	Vector max;
	unsigned char IsValid;
	TBox() { IsValid = 0; }
	TBox(const Vector& inMin, const Vector& inMax) :min(inMin), max(inMax), IsValid(1) {}
	TBox(const Vector4& inMin, const Vector4& inMax) :min(Vector(inMin.x, inMin.y, inMin.z)), max(Vector(inMax.x, inMax.y, inMax.z)), IsValid(1) {}
	Vector GetSize()const
	{
		return (max - min);
	}

	void GetCenterAndExtent(Vector& center, Vector& extent)const
	{
		center = max + min;
		center.x /= 2;
		center.y /= 2;
		center.z /= 2;
		extent = max - min;
	}
};

using Box = TBox<double>;
