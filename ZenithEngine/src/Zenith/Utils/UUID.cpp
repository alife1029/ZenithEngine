#include "zenithpch.h"
#include "UUID.h"

namespace Zenith
{
	static std::random_device s_RandomDevice;
	static std::mt19937_64 s_RandomEngine(s_RandomDevice());
	static std::uniform_int_distribution<uint64_t> s_Dist;

	UUID::UUID()
		:
		m_UUID(s_Dist(s_RandomEngine))
	{
	}
	UUID::UUID(uint64_t uuid)
		:
		m_UUID(uuid)
	{
	}
	UUID::operator uint64_t() const
	{
		return m_UUID;
	}
}
