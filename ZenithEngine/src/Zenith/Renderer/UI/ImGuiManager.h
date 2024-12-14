#pragma once

#include "Zenith/App/Window.h"

namespace Zenith
{
	class ImGuiManager
	{
	public:
		static void Initialize(Window* window);
		static void Shutdown();

		static void NewFrame();
		static void EndFrame();
	};
}
