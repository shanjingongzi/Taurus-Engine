#pragma once
#include <Vertex.h>
#include <Texture.h>
#include <vector>
class Mesh
{
public:
    inline Mesh(const std::vector<Vertex> &vertices,const std::vector<unsigned int >&indices,std::vector<Texture> &textures):vertices{vertices},indices{indices},textures{textures}{}
    std::vector<Vertex>vertices;
    std::vector<unsigned int >indices;
    std::vector<Texture>textures;

private:
    unsigned int vao;

};
