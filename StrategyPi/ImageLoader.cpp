#include "ImageLoader.h"

ImageLoader::~ImageLoader()
{
    delete textures;
}

ImageLoader::ImageLoader()
{
    textures = new Texture2D[ELoadedImage::ELoadedImageCount];
    
    textures[ELoadedImage::Worker] = LoadTexture("resources/npc_worker.png");
    textures[ELoadedImage::Fog] = LoadTexture("resources/fog.png");
    textures[ELoadedImage::Tree] = LoadTexture("resources/tree.png");
    textures[ELoadedImage::CoalMine] = LoadTexture("resources/coal_mine.png");
    textures[ELoadedImage::IronMine] = LoadTexture("resources/iron_mine.png");
}