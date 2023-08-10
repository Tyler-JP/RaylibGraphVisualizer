#include "include/ResourceLoader.h"

Texture2D ResourceLoader::LoadTextures(const std::string& filePath) {
    Image image = LoadImage(filePath.c_str());
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);
    return texture;
}

void ResourceLoader::UnloadTexture(Texture2D texture) {
    UnloadTexture(texture);
}