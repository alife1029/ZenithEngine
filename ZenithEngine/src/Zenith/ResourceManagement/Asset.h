#pragma once

#include "Zenith/Utils/UUID.h"
#include "Zenith/Renderer/Texture2D.h"

namespace Zenith
{
	class Asset
	{
		friend class ResourceManager;
	public:
		enum class Type
		{
			Texture2D = 1
		};

		operator Zenith::UUID() const;
		operator uint64_t() const;

		Asset();

	private:
		Zenith::UUID m_UUID;

	protected:
		void* m_Data;
	};

	class Texture2DAsset : public Asset
	{
	public:
		Texture2DAsset(unsigned char* pixels, int width, int height, int channelCount, unsigned int pixelPerUnit = 100u, Texture2D::Filter filter = Texture2D::Filter::Bilinear, Texture2D::Wrap wrap = Texture2D::Wrap::Clamp);
		Texture2DAsset(const std::string& imageFile, unsigned int pixelPerUnit = 100u, bool forceRGBA = false, Texture2D::Filter filter = Texture2D::Filter::Bilinear, Texture2D::Wrap wrap = Texture2D::Wrap::Clamp);

		operator Texture2D* () const;
	};
}
