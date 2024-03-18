#pragma once
#include<iostream>
#include<unordered_map>
#include<SFML/Graphics.hpp>
#include"cdef.h"
class AssetLoader {
public:
	static sf::Texture* load_texture(const std::string &path);
	static std::unordered_map<std::string, sf::Texture*> load_textures();
};