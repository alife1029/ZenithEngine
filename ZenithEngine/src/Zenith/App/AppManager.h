#pragma once

#include "App.h"

namespace Zenith
{
	class AppManager
	{
	public:
		static void RunApplication(ZenithApp* app);
		static ZenithApp* GetRunningApplication();
		static void QuitApplication(int returnValue = 0);
		static int GetReturnValue();
	private:
		static ZenithApp* s_RunningApplication;
		static bool s_IsRunning;
		static int s_ReturnValue;
	};
}
