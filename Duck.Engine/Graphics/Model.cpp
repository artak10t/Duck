#include "Model.h"

#include "../System/Logger.h"

#define CGLTF_IMPLEMENTATION
#include <cgltf/cgltf.h>

#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"

#include <queue>

namespace Duck
{
    Model::Model(const char* file)
    {
        // Init GLTF
        cgltf_options options = {};
        cgltf_data* model = nullptr;
        cgltf_parse_file(&options, file, &model);
        cgltf_load_buffers(&options, model, file);

        uint32_t transformIndex = 0;
        size_t vertexOffset = 0;
        size_t indexOffset = 0;

        // Iterate through nodes
        for (uint32_t i = 0; i < model->scene->nodes_count; ++i)
        {
            std::queue<cgltf_node*> nodes;
            nodes.push(model->scene->nodes[i]);
            while (!nodes.empty())
            {
                const auto* node = nodes.front();
                nodes.pop();

                // If node is not mesh then skip
                if (!node->mesh)
                {
                    for (uint32_t j = 0; j < node->children_count; ++j)
                    {
                        nodes.push(node->children[j]);
                    }
                    continue;
                }

                // If node is a mesh then create Mesh object and iterate through node data
                Mesh* mesh = new Mesh();
                for (uint32_t j = 0; j < node->mesh->primitives_count; ++j)
                {
                    const auto& primitive = node->mesh->primitives[j];
                    const Vector3* positionPtr = nullptr;
                    const Vector3* normalPtr = nullptr;
                    const Vector2* uvPtr = nullptr;
                    //const glm::vec4* tangentPtr = nullptr;
                    uint64_t vertexCount = 0;
                    
                    // Retrive attributes pointers
                    for (uint32_t k = 0; k < primitive.attributes_count; ++k)
                    {
                        const auto& attribute = primitive.attributes[k];
                        const auto* accessor = attribute.data;
                        const auto* view = accessor->buffer_view;
                        const auto* dataPtr = (const char*)view->buffer->data;
                        switch (attribute.type)
                        {
                        case cgltf_attribute_type_position:
                            vertexCount = accessor->count;
                            positionPtr = (const Vector3*)(dataPtr + view->offset + accessor->offset);
                            break;
                        case cgltf_attribute_type_normal:
                            normalPtr = (const Vector3*)(dataPtr + view->offset + accessor->offset);
                            break;
                        case cgltf_attribute_type_texcoord:
                            uvPtr = (const Vector2*)(dataPtr + view->offset + accessor->offset);
                            break;
                        /*
                        case cgltf_attribute_type_tangent:
                            tangentPtr = (const Vector4*)(dataPtr + view->offset + accessor->offset);
                            break;
                        */
                        default: 
                            break;
                        }
                    }

                    // Copy data into nesh
                    mesh->vertices.resize(vertexCount);
                    mesh->normals.resize(vertexCount);
                    mesh->uv.resize(vertexCount);
                    //mesh->tangent.resize(vertexCount)
                    if (positionPtr)
                    {
                        std::memcpy(&mesh->vertices[0], positionPtr, sizeof(Vector3) * vertexCount);
                    }
                    if (normalPtr)
                    {
                        std::memcpy(&mesh->normals[0], normalPtr, sizeof(Vector3) * vertexCount);
                    }
                    if (uvPtr)
                    {
                        for (uint32_t v = 0; v < vertexCount; ++v)
                        {
                            std::memcpy(&mesh->uv[v], uvPtr + v, sizeof(Vector2));

                            // Flip UV Vertically
                            mesh->uv[v].y *= -1;
                            mesh->uv[v].y += 1;
                        }
                    }
                    /*
                    if (tangentPtr)
                    {
                        std::memcpy(&mesh->tangent[v], tangentPtr, sizeof(Vector4) * vertexCount);
                    }
                    */

                    // Get triangles
                    const auto* accessor = primitive.indices;
                    const auto* view = accessor->buffer_view;
                    const char* dataPtr = (const char*)view->buffer->data;
                    mesh->triangles.reserve(accessor->count);
                    switch (accessor->component_type)
                    {
                        case cgltf_component_type_r_8:
                        case cgltf_component_type_r_8u:
                        {
                            const auto* ptr = (const uint8_t*)(dataPtr + view->offset + accessor->offset);
                            std::copy(ptr, ptr + accessor->count, std::back_inserter(mesh->triangles));
                        } break;

                        case cgltf_component_type_r_16:
                        case cgltf_component_type_r_16u:
                        {
                            const auto* ptr = (const uint16_t*)(dataPtr + view->offset + accessor->offset);
                            std::copy(ptr, ptr + accessor->count, std::back_inserter(mesh->triangles));
                        } break;

                        case cgltf_component_type_r_32f:
                        case cgltf_component_type_r_32u:
                        {
                            const auto* ptr = (const uint32_t*)(dataPtr + view->offset + accessor->offset);
                            std::copy(ptr, ptr + accessor->count, std::back_inserter(mesh->triangles));
                        } break;

                        default: 
                            break;
                    }
                }

                // Push children nodes into queue
                for (uint32_t j = 0; j < node->children_count; ++j)
                {
                    nodes.push(node->children[j]);
                }

                // Push Mesh into list of meshes
                mesh->UploadData();
                meshes.push_back(mesh);
            }
        }
    }

    Model::~Model()
    {
        for (Mesh* m : meshes)
            delete m;

        meshes.clear();
    }

    const void Model::Draw()
    {
        for (Mesh* m : meshes)
        {
            m->Draw();
        }
    }
}