#pragma once
#include "Camera.h"
#include "../Math/Vector4.h"

/**
* OpenGL renderer implementation.
*/
namespace Duck::Renderer
{
	enum class Polygon
	{
		Shaded,
		Wireframe
	};

	/**
	 * Default buffer color after clear.
	 */
	inline Vector4 BufferColor = { 0.6f, 0.7f, 0.9f, 1 };

	/**
	 * Initialization of renderer. Should be done after window creation.
	 * @param none
	 * @return void
	 */
	void Init();

	/**
	 * Clear current window's buffer.
	 * @param none
	 * @return void
	 */
	void ClearBuffer();

	/**
	 * Updates global uniform data for a shader program.
	 * @param none
	 * @return void
	 */
	void UpdateGlobalUBO();

	/**
	 * Set renderer shading mode.
	 * @param PolygonMode can be Shaded or Wireframe.
	 * @return void
	 */
	void ShadingMode(Polygon mode);
}