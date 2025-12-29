#include "ImageLoader.h"

ImageLoader::ImageLoader()
{
    textures = new Texture2D[ELoadedImage::ELoadedImageCount];
    
    textures[ELoadedImage::Worker] = LoadTexture("resources/npc_worker.png");
    textures[ELoadedImage::Fog] = LoadTexture("resources/fog.png");
}