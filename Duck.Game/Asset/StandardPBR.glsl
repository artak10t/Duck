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

// Material
uniform sampler2D albedoMap;
uniform sampler2D metallicMap;
uniform sampler2D emissionMap;

uniform float metallic = float(10);

// Light
uniform vec3 light;

out vec4 _fragColor;

void main()
{
	// Ambient
    vec3 ambient = ambientLight * texture(albedoMap, _uv).rgb;

	// Diffuse
	vec3 norm = normalize(_normal);
	vec3 dir = normalize(light - _frag);
	float diff = max(dot(norm, dir), 0.0);
    vec3 diffuse = vec3(1, 1, 1) * diff * texture(albedoMap, _uv).rgb;  
				   //Light Diffuse
	// Specular
	vec3 view = normalize(cameraPosition - _frag);
	vec3 ref = reflect(-dir, norm);
	float spec = pow(max(dot(view, ref), 0.0), metallic);
    vec3 specular = vec3(1, 1, 1) * spec * texture(metallicMap, _uv).rgb;  
					//Light Specular

	// Combined
    vec3 result = ambient + diffuse + specular;
    _fragColor = vec4(result, 1.0);
}