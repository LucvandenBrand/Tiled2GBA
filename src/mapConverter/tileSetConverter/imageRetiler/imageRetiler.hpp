#ifndef IMAGE_RETILER_H
#define IMAGE_RETILER_H

#include "../image/image.hpp"

/**
 * Provides methods for restructuring the tiles of an image.
 */
class ImageRetiler {
public:
    /**
     * Restructure the tiles to be sorted into a single row of 8 pixels wide.
     * This is the format the GBA understands.
     * @param image The image to retile.
     * @param tileSize The size of the (square) tiles.
     * @return The retiled image.
     */
    Image retile(Image image, unsigned tileSize);

private:
    Image getTile(Image image, unsigned imageX, unsigned imageY, unsigned tileSize);
};

#endif // IMAGE_RETILER_H