@type vertex
#version 430 core

layout(location = 0) in vec3 in_vertex;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_uv;

out vec3 _normal;
out vec2 _uv;
out vec3 _frag;  

uniform mat4 mvp;
uniform mat4 model;

void main()
{
    gl_Position = mvp * vec4(in_vertex, 1.0);
    _frag = vec3(model * vec4(in_vertex, 1.0));
	_normal = mat3(transpose(inverse(model))) * in_normal;
	_uv = in_uv;
}

@type fragment
#version 430 core

in vec3 _normal;
in vec2 _uv;
in vec3 _frag;

out vec4 _fragColor;

struct Camera
{
	mat4 projection;
	mat4 view;
	vec3 position;
};

struct AmbientLight
{
	vec3 diffuse;
	vec3 specular;
};

struct DirectionalLight
{
	vec3 diffuse;
	vec3 specular;
    vec3 direction;
};

layout(std140) uniform CameraUBO
{
    Camera camera;
};

layout(std140) uniform LightUBO
{
	AmbientLight ambientLight;
    DirectionalLight directionalLight;
};

// Material
uniform sampler2D albedoMap;
uniform sampler2D metallicMap;
uniform sampler2D emissionMap;
uniform float metallic = float(10);

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 view);
//vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 view);
//vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 view);

void main()
{
    vec3 normal = normalize(_normal);
    vec3 view = normalize(camera.position - _frag);

	// Calculate Lights
	vec3 resultColor = vec3(0, 0, 0);
    resultColor += ambientLight.diffuse * texture(albedoMap, _uv).rgb;
	resultColor += CalcDirectionalLight(directionalLight, normal, view);

    _fragColor = vec4(resultColor, 1.0);
}

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 view)
{
    vec3 direction = normalize(-light.direction);

    // Diffuse
    float diffuse = max(dot(normal, direction), 0.0);

    // Specular
    vec3 reflection = reflect(-direction, normal);
    float specular = pow(max(dot(view, reflection), 0.0), metallic);

    // Combine
    vec3 diffuseColor = light.diffuse * diffuse * vec3(texture(albedoMap, _uv));
    vec3 specularColor = light.specular * specular * vec3(texture(metallicMap, _uv));
    return (diffuseColor + specularColor);
}