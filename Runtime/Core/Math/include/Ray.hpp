#ifndef TRAY_H
#define TRAY_H
#include "Vector.hpp"
#include <math.h>
#define FORCEINLNIE inline
namespace TE
{
    namespace Math
    {

        template <typename T>
        struct TRay
        {
        public:
            using Real = T;
            TVector<T>origin;
            TVector<T>direction;
            FORCEINLINE TRay() {
                origin = TVector<T>::zeroVector;
                direction = TVector<T>(0, 0, 1);
            }

            FORCEINLINE TRay(const TVector<T>& inOrigin, const TVector<T>& inDirection, bool directionIsNormalized = false)
            {
                this->origin = inOrigin;
                this->direction = inDirection;
                if (directionIsNormalized) {
                    this->direction.Normalize();
                }
            }

        public:
            TVector<T> PointAt(T rayParamter)
            {
                return origin + direction*rayParamter;
            }

            T GetParamerter(const TVector<T>& point)const
            {
                return TVector<T>::DotProduct(point - origin, direction);
            }

            T DistSquared(const TVector<T>& point)const
            {
                T rayParameter = TVector<T>::DotProduct(point - origin, direction);
                if (rayParameter < 0) {
                    return TVector<T>::DistSquared(origin, point);
                }
                else {
                    TVector<T>projectionPt = origin + rayParameter*direction;
                    return TVector<T>::DistSquared(projectionPt, point);
                }
            }

            T Dist(const TVector<T>  & point)const
            {
                return sqrt(DistSquared(point));
            }

            TVector<T>ClossPoint(const TVector<T>& point)const
            {
                T rayParameter = TVector<T>::DotProduct(point - origin, direction);
                if (rayParameter < 0) {
                    return origin;
                }
                else {
                    return origin + rayParameter * direction;
                }
            }


        };
    };
 };

#endif