#include "model.h"

Model::Model(std::string path)
{
    // Load Model
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "Error - Model: " << importer.GetErrorString() << " :: " << path << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::Draw()
{
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i]->Draw();
}

Model::~Model()
{
    for (unsigned int i = 0; i < meshes.size(); i++)
        delete meshes[i];

    meshes.clear();
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    // Process All Nodes
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    // Process Node's Children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
        processNode(node->mChildren[i], scene);
}

Mesh* Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    //std::vector<Texture> textures;

    // Process Vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex = {glm::vec3(0), glm::vec3(0), glm::vec3(0), glm::vec2(0)};

        // Vertex Position
        glm::vec3 vecPos = glm::vec3(0);
        vecPos.x = mesh->mVertices[i].x;
        vecPos.y = mesh->mVertices[i].y;
        vecPos.z = mesh->mVertices[i].z;
        vertex.Position = vecPos;

        // Vertex Normal
        glm::vec3 vecNorm = glm::vec3(0);
        vecNorm.x = mesh->mNormals[i].x;
        vecNorm.y = mesh->mNormals[i].y;
        vecNorm.z = mesh->mNormals[i].z;
        vertex.Normal = vecNorm;

        // Vertex Color (No alpha support)
        glm::vec3 vecCol = glm::vec3(1);
        if (mesh->HasVertexColors(i))
        {
            vecCol.x = mesh->mColors[i]->r;
            vecCol.y = mesh->mColors[i]->g;
            vecCol.z = mesh->mColors[i]->b;
        }
        vertex.Color = vecCol;

        // Vertex TexCoords
        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vecTex;
            vecTex.x = mesh->mTextureCoords[0][i].x;
            vecTex.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vecTex;
        }
        else
        {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    // Process Indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    /*
    // Process Materials (Textures)
    if (mesh->mMaterialIndex >= 0)
    {

    }
    */

    Mesh* m = new Mesh(vertices, indices);

    return m;
}
