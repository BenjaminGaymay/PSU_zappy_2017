//
// EPITECH PROJECT, 2018
// arcade
// File description:
// Sfml lib texture and sprite
//

#include "Sfml.hpp"

bool Graphical::Sfml::createTexture(const int &index, const std::string &path,
						   std::map<const int, std::unique_ptr<sf::Texture>> &map)
{
	std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();

	if (!texture->loadFromFile(path))
		return false;
	map[index] = std::move(texture);
	return true;
}

bool Graphical::Sfml::createSprite(const int &index, const std::string &path,
						  std::map<const int, std::unique_ptr<sf::Sprite>> &spritesMap,
						  std::map<const int, std::unique_ptr<sf::Texture>> &texturesMap)
{
	if (!this->createTexture(index, path, _textures))
		return false;
	spritesMap[index] = std::make_unique<sf::Sprite>(*texturesMap[index]);
	return true;
}

Graphical::Pos Graphical::Sfml::getEntityPos(const char &block)
{
	static std::map<char, Graphical::Pos> map = {
			{1, {0, 0}},
			{2, {1, 0}},
			{3, {2, 0}},
			{4, {0, 1}},
			{5, {1, 1}},
			{6, {2, 1}},
			{7, {0, 2}},
	};
	return map[block];
};

void Graphical::Sfml::createBlocks()
{
	this->createSprite(0, _picturePath + "sand.png", _blocks, _textures);
	this->createSprite(1, _picturePath + "emerald.png", _blocks, _textures);
	this->createSprite(2, _picturePath + "diamond.png", _blocks, _textures);
	this->createSprite(3, _picturePath + "rubis.png", _blocks, _textures);
	this->createSprite(4, _picturePath + "agate.png", _blocks, _textures);
	this->createSprite(5, _picturePath + "citrine.png", _blocks, _textures);
	this->createSprite(6, _picturePath + "saphir.png", _blocks, _textures);
	this->createSprite(7, _picturePath + "food.png", _blocks, _textures);
	this->createSprite(8, _picturePath + "player.png", _blocks, _textures);
	this->createSprite(9, _picturePath + "button.png", _blocks, _textures);
}
