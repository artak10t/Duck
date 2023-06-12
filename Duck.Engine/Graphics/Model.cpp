#include "Model.h"

#include "../System/Logger.h"

#define CGLTF_IMPLEMENTATION
#include <cgltf/cgltf.h>

namespace Duck
{
    Mesh* processMesh(const cgltf_primitive* primitive)
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        // Process Attributes
        for (unsigned int i = 0; i < primitive->attributes[0].data->count; i++)
        {
            Vertex vertex = { Vector3(0), Vector3(0), Vector2(0) };

            // Read Position
            cgltf_accessor_read_float(primitive->attributes[0].data, i, &vertex.position[0], 3);

            // Read Normal
            cgltf_accessor_read_float(primitive->attributes[1].data, i, &vertex.normal[0], 3);

            // Read UV
            cgltf_accessor_read_float(primitive->attributes[2].data, i, &vertex.uv[0], 2);

            // Flip UV Vertically
            vertex.uv.y *= -1;
            vertex.uv.y += 1;
            
            vertices.push_back(vertex);
        }

        // Process Indices
        for (unsigned int i = 0; i < primitive->indices->count; i++)
        {
            unsigned int j = 0;
            cgltf_accessor_read_uint(primitive->indices, i, &j, 1);
            indices.push_back(j);
        }

        Mesh* m = new Mesh(vertices, indices);
        return m;
    }

    static void processNode(std::vector<Mesh*>* meshes, cgltf_node* node)
    {
        // Process All Meshes
        if (node->mesh) 
        {
            for (unsigned int i = 0; i < node->mesh->primitives_count; i++)
            {
                meshes->push_back(processMesh(&node->mesh->primitives[i]));
            }
        }

        // Process Children Nodes
        for (unsigned int i = 0; i < node->children_count; i++)
            processNode(meshes, node->children[i]);
    }

    Model::Model(const char* path)
    {
        cgltf_options options = { cgltf_file_type_invalid, 0 };
        cgltf_data* data = NULL;
        cgltf_result result = cgltf_parse_file(&options, path, &data);

        //BETTER ERROR CHECKING
        if (result != cgltf_result_success) 
        {
            DUCK_ASSERT(false, "Model - Could not load '%s'", path);
            return;
        }

        result = cgltf_load_buffers(&options, data, path);
        if (result != cgltf_result_success) 
        {
            cgltf_free(data);
            DUCK_ASSERT(false, "Model - Could not load '%s'", path);
            return;
        }

        result = cgltf_validate(data);
        if (result != cgltf_result_success) 
        {
            cgltf_free(data);
            DUCK_ASSERT(false, "Model - Invalid file '%s'", path);
            return;
        }

        processNode(&meshes, data->scene->nodes[0]);

        cgltf_free(data);
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