#include "zenithpch.h"
#include "Time.h"

using namespace std::chrono;

namespace Zenith
{
	static steady_clock::time_point s_StartingPoint = steady_clock::now();
	static steady_clock::time_point s_LastFrame = steady_clock::now();
	static steady_clock::time_point s_CurrentFrame = steady_clock::now();

	float Time::Delta()
	{
		return duration<float>(s_CurrentFrame - s_LastFrame).count();
	}

	float Time::Elapsed()
	{
		return duration<float>(s_CurrentFrame - s_StartingPoint).count();
	}

	void Time::Update()
	{
		s_LastFrame = s_CurrentFrame;
		s_CurrentFrame = steady_clock::now();
	}
}