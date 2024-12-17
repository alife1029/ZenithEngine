#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <Zenith/Utils/UUID.h>
#include <Zenith/ResourceManagement/Asset.h>
#include <yaml-cpp/yaml.h>

struct Asset 
{
	uint64_t uuid; 
	uint32_t offset;
	uint16_t fileIndex;
	uint16_t assetType;
};

void Pack(std::string& manifestVersion, YAML::Node& section, uint16_t assetType, const std::string& manifestDir, const std::string& outFileDir, const std::string& outFileName, std::vector<Asset>& assets);

int main(int argc, char** argv)
{
	std::cout << "Zenith Asset Packer v0.0.1" << std::endl;

	if (argc < 2)
	{
		std::cout << "Assets folder root must be specified!" << std::endl;
		return -1;
	}

	std::string dir = argv[1];
	std::cout << "Directory about to pack: " << dir << std::endl;

	// Open resource manifest file
	YAML::Node manifest = YAML::LoadFile(dir + "/resources.yaml");

	// Get file version
	std::string fileVersion = manifest["version"].as<std::string>();
	std::cout << "Manifest file version: " << fileVersion << std::endl;

	// Package assets
	if (fileVersion == "0.0.1")
	{
		std::vector<Asset> assets;

#pragma region Packing assets
		Pack(fileVersion, manifest["texture2d_assets"], static_cast<uint16_t>(Zenith::Asset::Type::Texture2D), dir, dir + "/out/textures", "texturepack", assets);
		std::cout << "Texture2D Assets Packed!" << std::endl;
		Pack(fileVersion, manifest["audio_assets"], static_cast<uint16_t>(Zenith::Asset::Type::Audio), dir, dir + "/out/audio", "audiopack", assets);
		std::cout << "Audio Assets Packed!" << std::endl;
		Pack(fileVersion, manifest["font_assets"], static_cast<uint16_t>(Zenith::Asset::Type::Font), dir, dir + "/out/fonts", "fontpack", assets);
		std::cout << "Font Assets Packed!" << std::endl;
#pragma endregion

#pragma region Manifest file
		// Create manifest file for asset indexing
		std::ofstream ofs(dir + "/out/resources.bin", std::ios::out | std::ios::binary);

		struct ManifestHeader
		{
			uint64_t resourcesBinVersion;
			uint64_t assetCount;
		} header { 1, assets.size() };
		
		// Write header
		ofs.write(reinterpret_cast<char*>(&header), sizeof(header));

		// Write body
		for (Asset asset : assets)
		{
			ofs.write(reinterpret_cast<char*>(&asset), sizeof(asset));
		}

		int eof = EOF;
		ofs.write(reinterpret_cast<char*>(&eof), sizeof(eof)); // Write EOF

		ofs.close();

		std::cout << "Manifest file generated!" << std::endl;
#pragma endregion
	}

	return 0;
}

void Pack(std::string& manifestVersion, YAML::Node& section, uint16_t assetType, const std::string& manifestDir, const std::string& outFileDir, const std::string& outFileName, std::vector<Asset>& assets)
{
	if (manifestVersion == "0.0.1")
	{
		// Create output folder
		std::filesystem::create_directories(outFileDir);

		std::ofstream outPackageFile(outFileDir + "/" + outFileName + "0.bin", std::ios::out | std::ios::binary);
		uint64_t fileIndex = 0;
		uint64_t offset = 0;

		for (YAML::iterator node = section.begin(); node != section.end(); node++)
		{
			std::string _id = node->first.as<std::string>();
			char* pEnd = nullptr;

			std::string resFileName = node->second["file"].as<std::string>();

			// Read the file content
			std::ifstream inFile(manifestDir + "/" + resFileName, std::ios::binary | std::ios::ate);
			std::streamsize inFileSize = inFile.tellg();
			inFile.seekg(0, std::ios::beg);
			std::vector<char> buffer(inFileSize);
			if (!inFile.read(buffer.data(), inFileSize))
			{
				// FAILED TO READ FILE
				std::cout << "Failed to read resource file!\nFile: " << manifestDir << "/" << resFileName << std::endl;
				inFile.close();
				continue;
			}
			inFile.close();

		write_package:
			// Write into the package
			if (offset < 4294967295) // Max offset is 4 GB
			{
				// Write into current package file
				outPackageFile.write(buffer.data(), buffer.size());
			}
			else
			{
				// Create a new package file
				int eof = EOF;
				outPackageFile.write(reinterpret_cast<char*>(&eof), sizeof(eof)); // Write EOF
				outPackageFile.close();
				offset = 0;
				std::ostringstream oss;
				oss << outFileDir << "/" << outFileName << ++fileIndex << ".bin";
				outPackageFile = std::ofstream(oss.str(), std::ios::out | std::ios::binary);

				goto write_package;
			}

			Asset asset = {
				strtoull(_id.c_str(), &pEnd, 16),
				static_cast<uint32_t>(offset),
				static_cast<uint16_t>(fileIndex),
				assetType
			};
			
			assets.push_back(asset);

			// Increment the offset
			offset += static_cast<uint64_t>(inFileSize);
		}

		int eof = EOF;
		outPackageFile.write(reinterpret_cast<char*>(&eof), sizeof(eof)); // Write EOF
		outPackageFile.close();
	}
}
