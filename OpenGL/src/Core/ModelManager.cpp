#include "ModelManager.h"

Model ModelManager::gunModel;
Model ModelManager::zombieModel;
Model ModelManager::bonfireModel;
Model ModelManager::dungeonModel;
Model ModelManager::chestModel;
Model ModelManager::goldenCoinModel;
Model ModelManager::silverCoinModel;

void ModelManager::Init()
{
	std::filesystem::path absolutePath = std::filesystem::current_path() / "res" / "objects";
	stbi_set_flip_vertically_on_load(true);
	gunModel = Model(GetStringAbsolutePathToObj(absolutePath, "gun/arma.obj"));
	zombieModel = Model(GetStringAbsolutePathToObj(absolutePath, "zombie/zombie.obj"));
	bonfireModel = Model(GetStringAbsolutePathToObj(absolutePath, "bonfire/bonfire.obj"));
	dungeonModel = Model(GetStringAbsolutePathToObj(absolutePath, "dungeon/dungeon.obj"));
	chestModel = Model(GetStringAbsolutePathToObj(absolutePath, "chest/chest.obj"));
	goldenCoinModel = Model(GetStringAbsolutePathToObj(absolutePath, "goldenCoin/goldenCoin.obj"));
	silverCoinModel = Model(GetStringAbsolutePathToObj(absolutePath, "silverCoin/silverCoin.obj"));
}

std::string ModelManager::GetStringAbsolutePathToObj(std::filesystem::path basePath, std::string filePath)
{
	std::filesystem::path fullPath = basePath / filePath;
	std::string pathString = fullPath.string();
	std::replace(pathString.begin(), pathString.end(), '\\', '/');
	return pathString;
}
