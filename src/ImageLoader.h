#include <raylib.h>

/*
Preloads image textures to be reused by other objects
*/
class ImageLoader
{
public:
    Texture2D* textures;

    ImageLoader();
};

enum ELoadedImage
{
    Worker,
    Fog,
    Tree,
    CoalMine,
    IronMine,
    ELoadedImageCount,
};