#include "AssetModel.h"

#include "../System/Logger.h"

#define CGLTF_IMPLEMENTATION
#include <cgltf/cgltf.h>

namespace Duck::Resources
{
	static std::unordered_map<const char*, Model*> m_Cache;

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

    static void processNode(std::vector<Mesh*>& meshes, cgltf_node* node)
    {
        // Process All Meshes
        if (node->mesh)
        {
            for (unsigned int i = 0; i < node->mesh->primitives_count; i++)
            {
                meshes.push_back(processMesh(&node->mesh->primitives[i]));
            }
        }

        // Process Children Nodes
        for (unsigned int i = 0; i < node->children_count; i++)
            processNode(meshes, node->children[i]);
    }

	template<>
	Model* Load<Model>(const char* file)
	{
		if (m_Cache.find(file) != m_Cache.end())
			return m_Cache.at(file);

		// Get Path
		std::string path = GetAssetsPath() + file;

		// Load Model
        cgltf_options options = { cgltf_file_type_invalid, 0 };
        cgltf_data* data = NULL;
        cgltf_result result = cgltf_parse_file(&options, path.c_str(), &data);

        switch (result)
        {
        case cgltf_result_success:
            break;
        case cgltf_result_data_too_short:
            DUCK_ASSERT(false, "Model - Data too short '%s'", path);
            break;
        case cgltf_result_unknown_format:
            DUCK_ASSERT(false, "Model - Unknown format '%s'", path);
            break;
        case cgltf_result_invalid_json:
            DUCK_ASSERT(false, "Model - Invalid json '%s'", path);
            break;
        case cgltf_result_invalid_gltf:
            DUCK_ASSERT(false, "Model - Invalid gltf '%s'", path);
            break;
        case cgltf_result_invalid_options:
            DUCK_ASSERT(false, "Model - Invalid options '%s'", path);
            break;
        case cgltf_result_file_not_found:
            DUCK_ASSERT(false, "Model - File not found '%s'", path);
            break;
        case cgltf_result_io_error:
            DUCK_ASSERT(false, "Model - IO error '%s'", path);
            break;
        case cgltf_result_out_of_memory:
            DUCK_ASSERT(false, "Model - Out of memory '%s'", path);
            break;
        case cgltf_result_legacy_gltf:
            DUCK_ASSERT(false, "Model - Legacy gltf '%s'", path);
            break;
        case cgltf_result_max_enum:
            DUCK_ASSERT(false, "Model - Max enum '%s'", path);
            break;
        default:
            DUCK_ASSERT(false, "Model - Unknown error '%s'", path);
            break;
        }

        result = cgltf_load_buffers(&options, data, path.c_str());
        if (result != cgltf_result_success)
        {
            cgltf_free(data);
            DUCK_ASSERT(false, "Model - Could not load '%s'", path);
        }

        result = cgltf_validate(data);
        if (result != cgltf_result_success)
        {
            cgltf_free(data);
            DUCK_ASSERT(false, "Model - Invalid file '%s'", path);
        }

        std::vector<Mesh*> tempMesh;
        processNode(tempMesh, data->scene->nodes[0]);
        cgltf_free(data);

		// Cache Model
		m_Cache.emplace(file, new Model(tempMesh));

		Logger::Info("Shader - '%s' Loaded", file);

		return m_Cache.at(file);
	}

	template<>
	void Unload<Model>(const char* file)
	{
		if (m_Cache.find(file) == m_Cache.end())
			return;

		delete m_Cache.at(file);
		m_Cache.erase(file);
	}
}