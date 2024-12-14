#pragma once

#include <glm/glm.hpp>
#include "Viewport.h"

namespace Zenith
{
	class Camera
	{
	public:
		Camera(Viewport* viewport);

		void Update() noexcept;

		void SetViewport(Viewport* viewport);

		const glm::mat4& GetViewMatrix() const noexcept;
		const glm::mat4& GetProjectionMatrix() const noexcept;
		const glm::mat4& GetCombinedMatrix() const noexcept;

	public:
		glm::vec3 Position{ 0.0f };
		float Rotation = 0.0f;
		float Size = 5.0f;
		float zNear = 1.0f;
		float zFar = 100.0f;

	private:
		glm::mat4	m_View,
					m_Projection,
					m_Combined;
		Viewport* m_Viewport;
	};
}
