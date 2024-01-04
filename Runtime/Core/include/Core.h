#ifndef CORE_H
#define CORE_H

#ifndef TAURUS_ENGINE_API
#define TAURUS_ENGINE_API //6__declspec(dllexport) 
#else 
#define EXPORT_ENGINE_API _declspec(dllimport) 
#endif

#include "glm/glm.hpp"
using Matrix=glm::mat3;
using Color=glm::vec3;
using Point=glm::vec3;
class Plane;
class Line;
class AABB;
class OBB;

inline float Clamp(const float &n,const float &min,const float & max)
{
    float tmp=n;
    tmp=n<min?min:n;
    tmp=n>max?max:n;
    return tmp;
}

//求任意一点到平面上的最近点
Point  ClosestPointPlane(const Point &pt,const Plane &plane);

//求任意一点到线段上的最近点
void ClosestPointPointSegment(const Point &pt,const Point &a,const Point &b,float &t,Point &d);

//求任意一点到线段的最近距离大小
float SqDistPointSegment(const Point &a,const Point &b,const Point &c);

//点到AABB的距离
float SqDistPointAABB(Point pt,const AABB &);

float SqDistPointOBB(Point p,const OBB  &b);
#endif
