#include"AssetLoader.h"
sf::Texture* AssetLoader::load_texture(const std::string& path) {
	sf::Texture* texture = new sf::Texture;
	if (!texture->loadFromFile(path)) {
		std::cerr << "couldn't load texture from file exiting now" << std::endl;
		exit(1);
	}
	return texture;
}

std::unordered_map<std::string, sf::Texture*> AssetLoader::load_textures() {
	std::unordered_map<std::string, sf::Texture*> res;
	res.insert(std::make_pair("rook", load_texture(TEXTURES::ROOK)));
	res.insert(std::make_pair("pawn", load_texture(TEXTURES::PAWN)));
	res.insert(std::make_pair("bishop", load_texture(TEXTURES::BISHOP)));
	res.insert(std::make_pair("king", load_texture(TEXTURES::KING)));
	res.insert(std::make_pair("horse", load_texture(TEXTURES::HORSE)));
	res.insert(std::make_pair("queen", load_texture(TEXTURES::QUEEN)));

	return res;
}