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
    Model::Model(std::string_view file)
    {
        // Init GLTF
        cgltf_options options = {};
        cgltf_data* model = nullptr;
        cgltf_parse_file(&options, file.data(), &model);
        cgltf_load_buffers(&options, model, file.data());

        //Materials
        /*
        fs::path path(file.data());
        const auto basePath = path.parent_path();
        std::unordered_map<std::string, size_t> textureIds;
        _cubes.Textures.reserve(model->materials_count);
        const uint32_t maxBatches = model->materials_count / 16 + 1;
        for (uint32_t i = 0; i < model->materials_count; ++i)
        {
            const auto& material = model->materials[i];
            if (material.has_pbr_metallic_roughness && material.pbr_metallic_roughness.base_color_texture.texture != nullptr)
            {
                const auto* image = material.pbr_metallic_roughness.base_color_texture.texture->image;
                const auto texturePath = FindTexturePath(basePath, image);
                if (textureIds.contains(texturePath))
                {
                    continue;
                }
                uint32_t texture;
                glCreateTextures(GL_TEXTURE_2D, 1, &texture);

                glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                int32_t width = 0;
                int32_t height = 0;
                int32_t channels = STBI_rgb_alpha;
                const auto* textureData = stbi_load(texturePath.c_str(), &width, &height, &channels, STBI_rgb_alpha);
                const auto levels = (uint32_t)std::floor(std::log2(std::max(width, height)));
                glTextureStorage2D(texture, levels, GL_RGBA8, width, height);
                glTextureSubImage2D(texture, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
                glGenerateTextureMipmap(texture);
                stbi_image_free((void*)textureData);
                _cubes.Textures.emplace_back(texture);
                textureIds[texturePath] = _cubes.Textures.size() - 1;
            }
        }
        */

        uint32_t transformIndex = 0;
        size_t vertexOffset = 0;
        size_t indexOffset = 0;
       // std::vector<MeshCreateInfo> meshCreateInfos;
       // meshCreateInfos.reserve(1024);
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
                    
                    // Get data pointers
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

                    // Get data
                    mesh->vertices.resize(vertexCount);
                    mesh->normals.resize(vertexCount);
                    mesh->uv.resize(vertexCount);
                    //mesh->tangent.resize(vertexCount)
                    for (uint32_t v = 0; v < vertexCount; ++v)
                    {
                        if (positionPtr)
                        {
                            std::memcpy(&mesh->vertices[v], positionPtr + v, sizeof(Vector3));
                        }
                        if (normalPtr)
                        {
                            std::memcpy(&mesh->normals[v], normalPtr + v, sizeof(Vector3));
                        }
                        if (uvPtr)
                        {
                            std::memcpy(&mesh->uv[v], uvPtr + v, sizeof(Vector2));

                            // Flip uv
                            mesh->uv[v].y *= -1;
                            mesh->uv[v].y += 1;
                        }
                        /*
                        if (tangentPtr)
                        {
                            std::memcpy(&mesh->tangent[v], tangentPtr + v, sizeof(glm::vec4));
                        }
                        */
                    }

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

                    /*
                    std::string baseColorURI = "";
                    if (primitive.material->pbr_metallic_roughness.base_color_texture.texture != nullptr)
                    {
                        baseColorURI = FindTexturePath(basePath, primitive.material->pbr_metallic_roughness.base_color_texture.texture->image);
                    }
                    else
                    {
                        baseColorURI = "";
                    }
                    const auto indexCount = indices.size();
                    meshCreateInfos.emplace_back(MeshCreateInfo
                        {
                            std::move(vertices),
                            std::move(indices),
                            transformIndex++,
                            baseColorURI == "" ? 0 : (uint32_t)textureIds[baseColorURI],
                            0,
                            vertexOffset,
                            indexOffset,
                            _cubes.VertexBuffer,
                            _cubes.IndexBuffer
                        });
                    
                    // Get transform
                    cgltf_node_transform_world(node, glm::value_ptr(_cubes.Transforms.emplace_back()));
                    vertexOffset += vertexCount * sizeof(Vertex);
                    indexOffset += indexCount * sizeof(uint32_t);
                    */
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

        /*
        _cubes.Commands.resize(maxBatches);
        _cubes.ObjectData.resize(maxBatches);

        // Allocate GL buffers
        glCreateVertexArrays(1, &_cubes.InputLayout);
        glCreateBuffers(1, &_cubes.VertexBuffer);
        glCreateBuffers(1, &_cubes.IndexBuffer);
        glCreateBuffers(1, &_cubes.TransformData);
        glGenBuffers(_cubes.Commands.size(), _cubes.Commands.data());
        glCreateBuffers(_cubes.ObjectData.size(), _cubes.ObjectData.data());

        size_t vertexSize = 0;
        size_t indexSize = 0;
        for (const auto& meshCreateInfo : meshCreateInfos)
        {
            vertexSize += meshCreateInfo.Vertices.size() * sizeof(Vertex);
            indexSize += meshCreateInfo.Indices.size() * sizeof(uint32_t);
        }

        glNamedBufferStorage(_cubes.VertexBuffer, vertexSize, nullptr, GL_DYNAMIC_STORAGE_BIT);
        glNamedBufferStorage(_cubes.IndexBuffer, indexSize, nullptr, GL_DYNAMIC_STORAGE_BIT);

        glVertexArrayVertexBuffer(_cubes.InputLayout, 0, _cubes.VertexBuffer, 0, sizeof(Vertex));
        glVertexArrayElementBuffer(_cubes.InputLayout, _cubes.IndexBuffer);

        glEnableVertexArrayAttrib(_cubes.InputLayout, 0);
        glEnableVertexArrayAttrib(_cubes.InputLayout, 1);
        glEnableVertexArrayAttrib(_cubes.InputLayout, 2);
        glEnableVertexArrayAttrib(_cubes.InputLayout, 3);

        glVertexArrayAttribFormat(_cubes.InputLayout, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, Position));
        glVertexArrayAttribFormat(_cubes.InputLayout, 1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, Normal));
        glVertexArrayAttribFormat(_cubes.InputLayout, 2, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, Uv));
        glVertexArrayAttribFormat(_cubes.InputLayout, 3, 4, GL_FLOAT, GL_FALSE, offsetof(Vertex, Tangent));

        glVertexArrayAttribBinding(_cubes.InputLayout, 0, 0);
        glVertexArrayAttribBinding(_cubes.InputLayout, 1, 0);
        glVertexArrayAttribBinding(_cubes.InputLayout, 2, 0);
        glVertexArrayAttribBinding(_cubes.InputLayout, 3, 0);

        for (auto& info : meshCreateInfos)
        {
            info.VertexBuffer = _cubes.VertexBuffer;
            info.IndexBuffer = _cubes.IndexBuffer;
            glNamedBufferSubData(
                info.VertexBuffer,
                info.VertexOffset,
                info.Vertices.size() * sizeof(Vertex),
                info.Vertices.data());
            glNamedBufferSubData(
                info.IndexBuffer,
                info.IndexOffset,
                info.Indices.size() * sizeof(uint32_t),
                info.Indices.data());
            _cubes.Meshes.emplace_back(Mesh
                {
                    (uint32_t)info.Indices.size(),
                    (int32_t)(info.VertexOffset / sizeof(Vertex)),
                    (uint32_t)(info.IndexOffset / sizeof(uint32_t)),
                    info.TransformIndex,
                    info.BaseColorTexture,
                    info.NormalTexture
                });
        }
        */
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