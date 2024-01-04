#ifndef TVECTOR_H
#define TVECTOR_H
#include "PlatformMathSSE.h"
#include "MathUtility.h"
#define FORCEINLINE inline
namespace TE
{
namespace Math
{
template<typename T>
struct TVector
{
public:
    using Real = T;
    union {
        struct {
            Real x;
            Real y;
            Real z;
        };
        Real xyz[3];
    }; 
    static const TVector<T>zeroVector;
    static const TVector<T>oneVector;
    static const TVector<T>upVector;
    static const TVector<T>downVector;
    static const TVector<T>forwardVector;
    static const TVector<T>backwardVector;
    static const TVector<T>rightVector;
    static const TVector<T>leftVector;
    static const TVector<T>xAxisVector;
    static const TVector<T>yAxisVector;
    static const TVector<T>zAxisVector;

    static inline TVector<T>Zero() { return zeroVector; }
    static inline TVector<T>One() { return oneVector; }
    static inline TVector<T>UnitX() { return xAxisVector; }
    static inline TVector<T>UnitY() { return yAxisVector; }
    static inline TVector<T>UnitZ() { return zAxisVector; }
    
    FORCEINLINE TVector();
    explicit FORCEINLINE TVector(T inF);
    FORCEINLINE TVector(T inX, T inY, T inZ);
    
    FORCEINLINE TVector<T>operator^(const TVector<T>& v)const;
    FORCEINLINE TVector<T>Cross(const TVector<T>& v2)const;

    FORCEINLINE static TVector<T>CrossProduct(const TVector<T>& A,const TVector<T>& B);
    FORCEINLINE TVector<T>operator+(const TVector<T>& v)const;
    FORCEINLINE TVector<T>operator-(const TVector<T>& v)const;
    FORCEINLINE TVector<T>operator*(const TVector<T>& v)const;
    FORCEINLINE TVector<T>operator/(const TVector<T>& v)const;
    FORCEINLINE TVector<T>operator *(T value);
    FORCEINLINE TVector<T>operator *=(T value);
    FORCEINLINE T& operator[](int i);
    FORCEINLINE T operator[](int i)const;
    FORCEINLINE T Dot(const TVector<T>& v)const;
    FORCEINLINE static T DotProduct(const TVector<T>& a, const TVector<T>& b);
    FORCEINLINE T operator|(const TVector<T>& v)const;

    FORCEINLINE bool  Normalize(T tolerance=SMALL_NUMBER);

    FORCEINLINE static T DistSquared(const TVector<T>& a, const TVector<T>& b);

    FORCEINLINE bool IsNearlyZero(double value=0){
      return true;
    }



};
template<typename T>
const TVector<T>TVector<T>::zeroVector = TVector<T>(0.0,0.0,0.0);

template<typename T>
FORCEINLINE TVector<T>::TVector(){}
template<typename T>
FORCEINLINE TVector<T>::TVector(T inX,T inY,T inZ):x(inX),y(inY),z(inZ)
{

}

template<typename T>
FORCEINLINE TVector<T> TVector<T>::operator^(const TVector<T>& v)const
{
    return TVector<T>(
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
        );
}

template<typename T>
FORCEINLINE TVector<T> TVector<T>::Cross(const TVector<T>& v)const
{
    return *this ^ v;
}

template<typename T>
FORCEINLINE TVector<T> TVector<T>::CrossProduct(const TVector<T>& A, const TVector<T>& B)
{
    return A ^ B;
}

template<typename T>
FORCEINLINE TVector<T> TVector<T>::operator+(const TVector<T>& v)const
{
    return TVector<T>(x + v.x, y + v.y, z + v.z);
}

template<typename T>
FORCEINLINE TVector<T> TVector<T>::operator-(const TVector<T>& v)const
{
    return TVector<T>(x - v.x, y - v.y, z - v.z);
}

template<typename T>
FORCEINLINE T TVector<T>::operator|(const TVector<T>& v)const
{
    return x * v.x + y * v.y + z * v.z;
}

template<typename T>
FORCEINLINE TVector<T> TVector<T>::operator*(const TVector<T>&v)const
{
    return TVector<T>(x * v.x, y * v.y, z * v.z);
}

template<typename T>
FORCEINLINE TVector<T> TVector<T>::operator/(const TVector<T>& v)const
{
    return TVector<T>(x * v.x, y * v.y, z * v.z);
}

template <typename T>
FORCEINLINE T TVector<T>::Dot(const TVector<T>& v)const
{
    return x * v.x + y + v.y + z + v.z;
}
template<typename T>
FORCEINLINE bool TVector<T>::Normalize(T tolerance)
{
    const T squareSum = x * x + y * y + z * z;
    if (squareSum > tolerance) {
        const T scale = SSE::InvSqrt(squareSum);
        x *= scale;
        y *= scale;
        z *= scale;
        return true;
    }
    return false;
}
template<typename T>
FORCEINLINE TVector<T> TVector<T>::operator *(T value)
{
    return TVector<T>(x * value, y * value, z * value);
}

template<typename T>
FORCEINLINE T TVector<T>::DotProduct(const TVector<T>& a, const TVector<T>& b)
{
    return a.Dot(b);
}

template<typename T>
FORCEINLINE T TVector<T>::DistSquared(const TVector<T>& a, const TVector<T>& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template<typename T>
FORCEINLINE TVector<T> TVector<T>::operator *=(T value)
{
    x *= value;
    y *= value;
    z *= value;
    return *this;
}

template<typename T>
FORCEINLINE TVector<T> operator*(T value, const TVector<T>& a)
{
    return a.operator*(value);
}
template<typename T>
FORCEINLINE T& TVector<T>::operator[](int i)
{
    return xyz[i];
}
template<typename T>
FORCEINLINE T TVector<T>::operator[](int i)const
{
    return xyz[i];
}

};
};

using Vector = TE::Math::TVector<double>;
using Vector3f = TE::Math::TVector<float>;
using Vector3i = TE::Math::TVector <int>;

#endif
