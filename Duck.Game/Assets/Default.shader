#type vertex
#version 330 core
layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec3 Color;
layout(location = 3) in vec2 UV;

out vec3 _normal;
out vec3 _color;
out vec2 _uv;

uniform mat4 position;

layout(std140) uniform CameraUBO
{
	mat4 CameraProjection;
	mat4 CameraView;
	vec3 CameraPosition;
};

void main()
{
	gl_Position = CameraProjection * CameraView * position * vec4(Position, 1.0);
	_normal = Normal;
	_color = Color;
	_uv = UV;
}

#type fragment
#version 330 core
in vec3 _normal;
in vec3 _color;
in vec2 _uv;

layout(std140) uniform LightingUBO
{
	vec3 AmbientLight;
};

out vec4 fragColor;
uniform sampler2D texture_0;

void main()
{
	fragColor = texture(texture_0, _uv) * vec4(_color * AmbientLight, 1);
}