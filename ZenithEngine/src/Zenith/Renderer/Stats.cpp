#include "zenithpch.h"
#include "Stats.h"

namespace Zenith
{
	size_t RendererStats::s_BatchCount = 0;
	size_t RendererStats::s_TriangleCount = 0;
	size_t RendererStats::s_VertexCount = 0;
	
	size_t RendererStats::GetBatchCount()
	{
		return s_BatchCount;
	}
	size_t RendererStats::GetTriangleCount()
	{
		return s_TriangleCount;
	}
	size_t RendererStats::GetVertexCount()
	{
		return s_VertexCount;
	}

	void RendererStats::Reset()
	{
		s_BatchCount = 0;
		s_TriangleCount = 0;
		s_VertexCount = 0;
	}
}
