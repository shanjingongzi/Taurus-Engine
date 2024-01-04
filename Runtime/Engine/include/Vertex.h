#pragma once
#include <Vector.hpp>
#include <Vector2.hpp>

#define MAX_BONE_INFLUENCE 4

class Vertex
{
    using Vector3=TE::Math::TVector<float>;
    using Vector2=TE::Math::TVector2<float>;
public:
    Vector3 position;
    Vector2 texCoords;
    Vector3 normal;
    Vector3 tangent;
    Vector3 bitangent;
    int boneIds[MAX_BONE_INFLUENCE];
    float weights[MAX_BONE_INFLUENCE];
};
