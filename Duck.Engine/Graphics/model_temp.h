#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.h"
//#include "texture.h"

class Model
{
public:
	Model(std::string path);
	void Draw();
	~Model();

private:
	std::vector<Mesh*> meshes;
	std::string directory = "";
	void processNode(aiNode* node, const aiScene* scene);
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
};