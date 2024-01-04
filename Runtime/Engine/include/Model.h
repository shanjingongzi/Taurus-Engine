#pragma once
#include <vector>
#include <string>
#include <Mesh.h>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class Model
{
public:
	static Model* LoadFromFile(const std::string& fiename);
	static void ProcessNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& mesh);
	static Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	static std::vector<Texture> LoadTexture(aiMaterial* material, aiTextureType type, std::string typeName);
private:
	std::vector<Mesh>meshes;
	std::string directory;
};
