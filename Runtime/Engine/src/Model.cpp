#include "Model.h"
Model*Model::LoadFromFile(const std::string &filepath)
{
    Assimp::Importer importer;
    const aiScene*scene=importer.ReadFile(filepath,aiProcess_Triangulate|aiProcess_GenSmoothNormals|aiProcess_CalcTangentSpace);
    if(!scene||scene->mFlags &AI_SCENE_FLAGS_INCOMPLETE ||!scene->mRootNode){
       return nullptr;
    }
    Model*model=new Model();
    model->directory=filepath.substr(0,filepath.find_last_of("/"));
    ProcessNode(scene->mRootNode,scene,model->meshes);
    return model;
}

void Model::ProcessNode(aiNode *node,const aiScene *scene,std::vector<Mesh>&meshes)
{
   for(unsigned int i=0;i<node->mNumMeshes;++i){
        aiMesh *amesh=scene->mMeshes[node->mMeshes[i]];
        Mesh mesh=ProcessMesh(amesh,scene);
        meshes.emplace_back(mesh);

   }
   for(unsigned int i=0;i<node->mNumChildren;++i){
       ProcessNode(node->mChildren[i],scene,meshes);
   }
}

Mesh Model::ProcessMesh(aiMesh *mesh,const aiScene*scene)
{
    std::vector<Vertex>vertices;
    std::vector<unsigned int>indices;
    std::vector<Texture>textures;
    for(unsigned int i=0;i<mesh->mNumVertices;++i){
       Vertex vertex;
        {
            auto aVertex=mesh->mVertices[i];
            vertex.position={aVertex.x,aVertex.y,aVertex.z};
        }
        {
            if(mesh->HasNormals()){
                auto aNormal=mesh->mNormals[i];
                vertex.normal={aNormal.x,aNormal.y,aNormal.z};
            }
        }
        {
            if(mesh->mTextureCoords[0]){
                auto texture=mesh->mTextureCoords[0][i];
                vertex.texCoords={texture.x,texture.y};
                auto aTangent=mesh->mTangents[i];
                vertex.tangent={aTangent.x,aTangent.y,aTangent.z};
                auto aBitTangent=mesh->mBitangents[i];
                vertex.bitangent={aBitTangent.x,aBitTangent.y,aBitTangent.z};
            }
            else{
                vertex.texCoords={0.0,0.0};
            }

        }
        vertices.emplace_back(vertex);
    }
    for(unsigned int i=0;i<mesh->mNumFaces;++i){
        aiFace face=mesh->mFaces[i];
        for(unsigned int j=0;j<face.mNumIndices;++j){
            indices.emplace_back(face.mIndices[j]);
        }
    }
    aiMaterial *material=scene->mMaterials[mesh->mMaterialIndex];
    std::vector<Texture>diffusseMaps=LoadTexture(material,aiTextureType_DIFFUSE,"texture_diffuse");
    textures.insert(textures.end(),diffusseMaps.begin(),diffusseMaps.end());
    std::vector<Texture>specularMaps=LoadTexture(material,aiTextureType_SPECULAR,"texture_specular");
    textures.insert(textures.end(),specularMaps.begin(),specularMaps.end());
    std::vector<Texture>normalMaps=LoadTexture(material,aiTextureType_HEIGHT,"texture_normal");
    textures.insert(textures.end(),normalMaps.begin(),normalMaps.end());
    std::vector<Texture>heightMaps=LoadTexture(material,aiTextureType_AMBIENT,"texture_height");
    textures.insert(textures.end(),heightMaps.begin(),heightMaps.end());
    return{vertices,indices,textures};
}

std::vector<Texture> Model::LoadTexture(aiMaterial *material,aiTextureType type,std::string typeName)
{
    std::vector<Texture>textures;
    for(unsigned int i=0;i<material->GetTextureCount(type);++i){
        aiString str;
        material->GetTexture((aiTextureType)type,i,&str);
		Texture texture;
        texture.path = str.C_Str();
        texture.type = typeName;
        textures.emplace_back(texture);
    }
    return std::move(textures);
}
