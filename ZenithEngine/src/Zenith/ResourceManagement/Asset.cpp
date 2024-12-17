#include "zenithpch.h"
#include "ResourceManager.h"
#include "Asset.h"

namespace Zenith
{
#pragma region Asset base class
	Asset::operator Zenith::UUID() const
	{
		return m_UUID;
	}
	
	Asset::operator uint64_t() const
	{
		return m_UUID;
	}
	Asset::Asset()
		:
		m_UUID(UUID()),
		m_Data(nullptr)
	{
	}
#pragma endregion

#pragma region Texture2DAsset
	Texture2DAsset::Texture2DAsset(unsigned char* pixels, int width, int height, int channelCount, unsigned int pixelPerUnit, Texture2D::Filter filter, Texture2D::Wrap wrap)
		:
		Asset()
	{
		m_Data = reinterpret_cast<void*>(new Texture2D(pixels, width, height, channelCount, pixelPerUnit, filter, wrap));
	}
	Texture2DAsset::Texture2DAsset(const std::string& imageFile, unsigned int pixelPerUnit, bool forceRGBA, Texture2D::Filter filter, Texture2D::Wrap wrap)
		:
		Asset()
	{
		m_Data = reinterpret_cast<void*>(new Texture2D(imageFile, pixelPerUnit, forceRGBA, filter, wrap));
	}
	Texture2DAsset::operator Texture2D* () const
	{
		return (Texture2D*)m_Data;
	}
#pragma endregion
}
