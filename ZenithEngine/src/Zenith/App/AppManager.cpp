#include "zenithpch.h"

#include "AppManager.h"
#include "Zenith/Renderer/Stats.h"

namespace Zenith
{
	ZenithApp* AppManager::s_RunningApplication = nullptr;
	bool AppManager::s_IsRunning = false;
	int AppManager::s_ReturnValue = -1;

	void AppManager::RunApplication(ZenithApp* app)
	{
		assert(!s_IsRunning);

		s_RunningApplication = app;
		s_IsRunning = true;

		app->Start();
		while (s_IsRunning)
		{
			app->Update();
			RendererStats::Reset();
		}

		QuitApplication();
	}
	
	void AppManager::QuitApplication(int returnValue)
	{
		s_RunningApplication = nullptr;
		s_IsRunning = false;
		s_ReturnValue = returnValue;
	}

	ZenithApp* AppManager::GetRunningApplication()
	{
		return s_RunningApplication;
	}

	int AppManager::GetReturnValue()
	{
		assert(!s_IsRunning);
		return s_ReturnValue;
	}
}
