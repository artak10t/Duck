#include "Renderer.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Camera.h"

#include "../System/Logger.h"

#define MAX_POINT_LIGHTS 256
#define MAX_SPOT_LIGHTS 256

namespace Duck
{
	Light Renderer::AmbientLight;
	LightDirectional Renderer::DirectionalLight;
	Vector4 Renderer::BackgroundColor = { 0.6f, 0.7f, 0.9f, 1 };
	Renderer::View Renderer::viewMode = View::Shaded;

	unsigned int Renderer::cameraUBO = 0;
	unsigned int Renderer::lightUBO = 0;

	void Renderer::Init()
	{
		gladLoadGL();

		// Depth
		glEnable(GL_DEPTH_TEST);

		// Blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Face Culling
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);

		// Create Camera UBO
		glGenBuffers(1, &cameraUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, cameraUBO);
		glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(Matrix4) + sizeof(Vector3), NULL, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, cameraUBO);

		// Create Lighting UBO
		glGenBuffers(1, &lightUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(Light) + sizeof(LightDirectional), NULL, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		glBindBufferBase(GL_UNIFORM_BUFFER, 1, lightUBO);

		Logger::Trace("Renderer Initialized");
	}

	void Renderer::ClearBuffer()
	{
		glClearColor(BackgroundColor.x, BackgroundColor.y, BackgroundColor.z, BackgroundColor.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::UpdateCameraUBO()
	{
		if (Camera::GetMain())
		{
			glBindBuffer(GL_UNIFORM_BUFFER, cameraUBO);

			glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Matrix4), &Camera::GetMain()->Projection()[0][0]);
			glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Matrix4), sizeof(Matrix4), &Camera::GetMain()->View()[0][0]);
			glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(Matrix4), sizeof(Vector3), &Camera::GetMain()->transform.position);

			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}
	}

	void Renderer::UpdateLightUBO()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, lightUBO);

		// Ambient Light
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Vector3), &AmbientLight.diffuse);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Vector4), sizeof(Vector3), &AmbientLight.specular);

		// Directional Light
		glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(Vector4), sizeof(Vector3), &DirectionalLight.diffuse);
		glBufferSubData(GL_UNIFORM_BUFFER, 3 * sizeof(Vector4), sizeof(Vector3), &DirectionalLight.specular);
		glBufferSubData(GL_UNIFORM_BUFFER, 4 * sizeof(Vector4), sizeof(Vector3), &DirectionalLight.direction);

		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void Renderer::SetView(Renderer::View mode)
	{
		viewMode = mode;

		switch (viewMode)
		{
		case View::Shaded:
			glEnable(GL_CULL_FACE);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		case View::Wireframe:
			glDisable(GL_CULL_FACE);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		}
	}

	Renderer::View Renderer::GetView()
	{
		return viewMode;
	}
}