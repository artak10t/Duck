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

out vec4 _fragColor;

layout(std140) uniform CameraUBO
{
	mat4 cameraProjection;
	mat4 cameraView;
	vec3 cameraPosition;
};

layout(std140) uniform LightUBO
{
	vec3 ambient;
};

// Material
uniform sampler2D albedoMap;
uniform sampler2D metallicMap;
uniform sampler2D emissionMap;

uniform float metallic = float(10);

void main()
{
	// Ambient
    vec3 ambientColor = ambient * texture(albedoMap, _uv).rgb;

	// Diffuse
	vec3 normal = normalize(_normal);
							//Light pos
	vec3 direction = normalize(vec3(0, 0, 0) - _frag);
	float diffuse = max(dot(normal, direction), 0.0);
    vec3 diffuseColor = vec3(1, 1, 1) * diffuse * texture(albedoMap, _uv).rgb;  
						//Light Diffuse
	// Specular
	vec3 view = normalize(cameraPosition - _frag);
	vec3 reflection = reflect(-direction, normal);
	float specular = pow(max(dot(view, reflection), 0.0), metallic);
    vec3 specularColor = vec3(1, 1, 1) * specular * texture(metallicMap, _uv).rgb;  
						//Light Specular

	// Combined
    vec3 resultColor = ambientColor + diffuseColor + specularColor;
    _fragColor = vec4(resultColor, 1.0);
}