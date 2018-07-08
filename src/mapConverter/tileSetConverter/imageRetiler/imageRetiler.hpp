#ifndef IMAGE_RETILER_H
#define IMAGE_RETILER_H

#include "../image/image.hpp"

class ImageRetiler {
public:
    Image getTile(Image image, unsigned imageX, unsigned imageY, unsigned tileSize);
    Image retile(Image image, unsigned tileSize);
};

#endif // IMAGE_RETILER_H