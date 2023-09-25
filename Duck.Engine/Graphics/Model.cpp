#include "Model.h"

#include "../System/Logger.h"

namespace Duck
{
    Model::Model(const std::vector<Mesh*>& meshes)
    {
        this->meshes = meshes;
    }

    Model::~Model()
    {
        for (unsigned int i = 0; i < meshes.size(); i++)
            delete meshes[i];

        meshes.clear();
    }

    const void Model::Draw()
    {
        for (unsigned int i = 0; i < meshes.size(); i++)
            meshes[i]->Draw();
    }
}