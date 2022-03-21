#pragma once

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <map>
#include <string>

class Texture
{
public:
	Texture(void){};
	~Texture(void);

	/** Loads a texture into memory and returns the id of the texture object created */
	int GetTexture(std::string fileName);
private:
	std::map<int, std::string> textures;
};