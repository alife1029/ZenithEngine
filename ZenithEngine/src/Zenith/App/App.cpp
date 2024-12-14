#include "zenithpch.h"

#include "App.h"
#include "Zenith/Utils/Time.h"

namespace Zenith
{
	ZenithApp::ZenithApp() 
		:
		m_Window(nullptr)
	{
		
	}

	ZenithApp::~ZenithApp() 
	{
	}

	void ZenithApp::Start() 
	{
	}

	void ZenithApp::Update() 
	{
		Time::Update();
	}

	Window* ZenithApp::GetWindow() const noexcept
	{
		return m_Window;
	}
}
