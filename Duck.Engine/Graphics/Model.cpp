#include "Model.h"

#include "../System/Logger.h"

namespace Duck
{
    Model::Model(const std::vector<Mesh*>& meshes)
    {
        m_Meshes = meshes;
    }

    Model::~Model()
    {
        for (unsigned int i = 0; i < m_Meshes.size(); i++)
            delete m_Meshes[i];

        m_Meshes.clear();
    }

    const void Model::Draw()
    {
        for (unsigned int i = 0; i < m_Meshes.size(); i++)
            m_Meshes[i]->Draw();
    }
}