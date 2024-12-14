#pragma once

namespace Zenith
{
	class RendererStats
	{
		friend class AppManager;
		friend class BatchRenderer;
		friend class UIRenderer;
	public:
		static size_t GetBatchCount();
		static size_t GetTriangleCount();
		static size_t GetVertexCount();
		
	private:
		static void Reset();

	private:
		static size_t s_BatchCount;
		static size_t s_TriangleCount;
		static size_t s_VertexCount;
	};
}
