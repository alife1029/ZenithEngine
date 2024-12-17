#include "zenithpch.h"
#include "ResourceManager.h"
#include "Asset.h"
#include <yaml-cpp/yaml.h>

namespace Zenith
{
	Asset* ResourceManager::LoadAsset(const std::string& path, Asset::Type assetType)
	{
		return nullptr;
	}

	Asset* ResourceManager::LoadAsset(Zenith::UUID assetID)
	{
		return nullptr;
	}
	
	void ResourceManager::PackAssets(const std::string& assetsRootDirectory)
	{
		// Firstly, load asset manifest file
	}
}
