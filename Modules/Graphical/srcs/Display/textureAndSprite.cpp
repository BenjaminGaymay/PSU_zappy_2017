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
	if (!createTexture(index, path, _textures))
		return false;
	spritesMap[index] = std::make_unique<sf::Sprite>(*texturesMap[index]);
	return true;
}

/**
 * @brief sprite dataBase
 */
void Graphical::Sfml::createBlocks()
{
	createSprite(0, _picturePath + "sand.png", _blocks, _textures);
	createSprite(1, _picturePath + "emerald.png", _blocks, _textures);
	createSprite(2, _picturePath + "diamond.png", _blocks, _textures);
	createSprite(3, _picturePath + "rubis.png", _blocks, _textures);
	createSprite(4, _picturePath + "agate.png", _blocks, _textures);
	createSprite(5, _picturePath + "citrine.png", _blocks, _textures);
	createSprite(6, _picturePath + "saphir.png", _blocks, _textures);
	createSprite(7, _picturePath + "food.png", _blocks, _textures);
	createSprite(8, _picturePath + "egg.png", _blocks, _textures);
	createSprite(9, _picturePath + "player.png", _blocks, _textures);
	createSprite(10, _picturePath + "button.png", _blocks, _textures);
	createSprite(11, _picturePath + "player_icon.png", _blocks, _textures);
	createSprite(12, _picturePath + "reset.png", _blocks, _textures);
	createSprite(13, _picturePath + "close.png", _blocks, _textures);
	createSprite(14, _picturePath + "backPack.png", _blocks, _textures);
	createSprite(15, _picturePath + "case.png", _blocks, _textures);
	createSprite(16, _picturePath + "toolbar.png", _blocks, _textures);
	createSprite(17, _picturePath + "title.png", _blocks, _textures);
	createSprite(18, _picturePath + "hand_open.png", _blocks, _textures);
	createSprite(19, _picturePath + "hand_close.png", _blocks, _textures);
}
