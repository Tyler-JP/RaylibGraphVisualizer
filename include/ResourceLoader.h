#pragma once
#include "raylib.h"
#include <string>

class ResourceLoader {
public:
	static Texture2D LoadTextures(const std::string& filePath);
	static void UnloadTexture(Texture2D texture);
};