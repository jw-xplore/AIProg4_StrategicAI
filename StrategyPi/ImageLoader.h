#include <raylib.h>

/*
Preloads image textures to be reused by other objects
*/
class ImageLoader
{
public:
    Texture2D* textures;

    ~ImageLoader();

    ImageLoader();
};

enum ELoadedImage
{
    Worker,
    Stone,
    Fog,
    Tree,
    CoalMine,
    IronMine,
    Storage,
    Smithy,
    Barracks,
    ELoadedImageCount,
};