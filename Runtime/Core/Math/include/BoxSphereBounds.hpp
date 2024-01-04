#ifndef T_BOX_SPHERE_BOUNDS_H
#define T_BOX_SPHERE_BOUNDS_H

#include "Box.hpp"


#define FORCEINLINE inline

template<typename T,typename TExtent>
class TBoxSphereBounds
{
public:
	using Vector = TE::Math::TVector<T>;
	using Real = T;	
	Vector origin;
	Vector boxExtent;
	TExtent sphereRadius;
public:
	TBoxSphereBounds() {}

	TBoxSphereBounds(const Vector& inOrigin, const Vector& inBoxExtent,const TExtent& inSphereRadius) :origin(inOrigin), boxExtent(inBoxExtent), sphereRadius(inSphereRadius)
	{
		DiagnosticCheckNaN();
	}

	FORCEINLINE TBox<T>GetBox()const
	{
		return TBox<T>(origin - boxExtent, origin + boxExtent);
	}
private:
	void DiagnosticCheckNaN()
	{

	}


};

using BoxSphereBounds = TBoxSphereBounds<double, double>;

#endif
