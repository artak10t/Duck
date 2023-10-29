@type vertex
#version 330 core
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
#version 330 core
in vec3 _normal;
in vec2 _uv;
in vec3 _frag;

layout(std140) uniform CameraUBO
{
	mat4 cameraProjection;
	mat4 cameraView;
	vec3 cameraPosition;
};

layout(std140) uniform LightingUBO
{
	vec3 ambientLight;
};

struct Material 
{
    sampler2D albedoTexture;
    sampler2D metallicTexture;
    float metallic;
}; 
uniform Material material;

uniform vec3 light;

out vec4 _fragColor;

void main()
{
	// Diffuse
	vec3 norm = normalize(_normal);
	vec3 lightDir = normalize(light - _frag);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(1, 1, 1); //LightColor

	// Specular
	vec3 viewDir = normalize(cameraPosition - _frag);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = material.metallic * spec * vec3(1, 1, 1); //LightColor 

	// Combined
	vec3 result = (ambientLight + diffuse + specular);
	_fragColor = texture(material.albedoTexture, _uv) * vec4(result, 1);
}