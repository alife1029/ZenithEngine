#pragma once

#include "Window.h"

namespace Zenith
{
	class ZenithApp 
	{
	public:
		ZenithApp();
		virtual ~ZenithApp();
		ZenithApp(const ZenithApp&) = delete;
		ZenithApp& operator=(const ZenithApp&) = delete;

		virtual void Start();
		virtual void Update();

		Window* GetWindow() const noexcept;

	protected:
		Window* m_Window;
	};
}
