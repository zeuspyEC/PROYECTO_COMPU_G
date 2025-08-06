#pragma once

#include "learnopengl/model.h"
#include <filesystem>

class ModelManager
{
public:
	static Model gunModel;
	static Model zombieModel;
	static Model bonfireModel;
	static Model dungeonModel;
	static Model chestModel;
	static Model goldenCoinModel;
	static Model silverCoinModel;
	static void Init();
private:
	static std::string GetStringAbsolutePathToObj(std::filesystem::path absolutePath, std::string filePath);
};
