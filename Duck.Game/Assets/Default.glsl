@type vertex
#version 330 core
layout(location = 0) in vec3 Vertex;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 UV;

out vec3 _normal;
out vec2 _uv;
out vec3 _frag;  

uniform mat4 mvp;
uniform mat4 model;

layout(std140) uniform CameraUBO
{
	mat4 CameraProjection;
	mat4 CameraView;
	vec3 CameraPosition;
};

void main()
{
    gl_Position = mvp * vec4(Vertex, 1.0);
    _frag = vec3(model * vec4(Vertex, 1.0));
	_normal = mat3(transpose(inverse(model))) * Normal;
	_uv = UV;
}

@type fragment
#version 330 core
in vec3 _normal;
in vec2 _uv;
in vec3 _frag;

layout(std140) uniform CameraUBO
{
	mat4 CameraProjection;
	mat4 CameraView;
	vec3 CameraPosition;
};

layout(std140) uniform LightingUBO
{
	vec3 AmbientLight;
};

uniform sampler2D texture_0;
uniform vec3 light;

out vec4 fragColor;

float specularStrength = 0.5;

void main()
{
	// Diffuse
	vec3 norm = normalize(_normal);
	vec3 lightDir = normalize(light - _frag);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(1, 1, 1); //LightColor

	// Specular
	vec3 viewDir = normalize(CameraPosition - _frag);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * vec3(1, 1, 1); //LightColor 

	// Combined
	vec3 result = (AmbientLight + diffuse + specular);
	fragColor = texture(texture_0, _uv) * vec4(result, 1);
}