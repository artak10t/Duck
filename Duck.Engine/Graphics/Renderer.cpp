#include "Renderer.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Camera.h"
#include "Lighting.h"

#include "../System/Logger.h"

namespace Duck::Renderer
{
	//Uniform Buffer Objects
	static unsigned int m_CameraUBO = 0;
	static unsigned int m_LightingUBO = 0;

	void Init()
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
		glGenBuffers(1, &m_CameraUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, m_CameraUBO);
		glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(Matrix4) + sizeof(Vector3), NULL, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_CameraUBO);

		// Create Lighting UBO
		glGenBuffers(1, &m_LightingUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, m_LightingUBO);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(Vector3), NULL, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		glBindBufferBase(GL_UNIFORM_BUFFER, 1, m_LightingUBO);

		Logger::Trace("Renderer Initialized");
	}

	void ClearBuffer()
	{
		glClearColor(BackgroundColor.r, BackgroundColor.g, BackgroundColor.b, BackgroundColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void UpdateGlobalUBO()
	{
		// If main camera exists update global uniform camera data
		if (Camera::GetMain())
		{
			glBindBuffer(GL_UNIFORM_BUFFER, m_CameraUBO);
			glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Matrix4), &Camera::GetMain()->Projection()[0][0]);
			glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Matrix4), sizeof(Matrix4), &Camera::GetMain()->View()[0][0]);
			glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(Matrix4), sizeof(Vector3), &Camera::GetMain()->transform.position);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}

		//Lighting UBO
		glBindBuffer(GL_UNIFORM_BUFFER, m_LightingUBO);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Vector3), &Lighting::AmbientLight.GetLight());
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void SetView(View mode)
	{
		switch (mode)
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
}