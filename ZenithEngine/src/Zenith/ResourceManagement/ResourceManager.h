#pragma once

#include "Zenith/Utils/UUID.h"

namespace Zenith
{
	class ResourceManager
	{
	public:
		Asset* LoadAsset(const std::string& path, Asset::Type assetType);
		Asset* LoadAsset(Zenith::UUID assetID);

	private:
		void PackAssets(const std::string& assetsRootDirectory);

	private:
		std::unordered_map<Zenith::UUID, std::shared_ptr<Asset>> m_Assets;
	};
}
