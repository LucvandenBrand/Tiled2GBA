#ifndef IMAGE_RETILER_H
#define IMAGE_RETILER_H

#include "../image/image.hpp"

class ImageRetiler {
public:
    Image getTile(Image image, unsigned imageX, unsigned imageY, unsigned tileWidth, unsigned tileHeight);
    Image retile(Image image, unsigned tileWidth, unsigned tileHeight);
};

#endif // IMAGE_RETILER_H