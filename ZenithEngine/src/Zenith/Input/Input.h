#pragma once

#include "Key.h"
#include "Zenith/App/Window.h"

#include <vector>

namespace Zenith
{
	class Input
	{
		friend class ZenithApp;
	public:
		static bool IsKeyPressed(Key key) noexcept;
		static bool IsKeyPressed(unsigned char key) noexcept;
		static bool IsKeyJustPressed(Key key) noexcept;
		static bool IsKeyJustPressed(unsigned char key) noexcept;
		static std::vector<unsigned char> GetPressingKeys() noexcept;
		static void SetupEventWindow(Window* eventWnd) noexcept;
	};
}
