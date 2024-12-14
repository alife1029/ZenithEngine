#pragma once

namespace Zenith
{
	class Time
	{
		friend class ZenithApp;
	public:
		static float Delta();
		static float Elapsed();
	private:
		static void Update();
	};
}
