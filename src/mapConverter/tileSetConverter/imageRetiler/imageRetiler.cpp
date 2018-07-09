#include "imageRetiler.hpp"
#include "../../../gba/background.h"

Image ImageRetiler::getTile(Image image, unsigned imageX, unsigned imageY, unsigned tileSize) {
    vector<Color> tilePixels;
    tilePixels.reserve(tileSize * tileSize);
    for (unsigned tileY = 0; tileY < tileSize; tileY ++) {
        for (unsigned tileX = 0; tileX < tileSize; tileX++) {
            Color color = image.getPixel(imageY + tileY, imageX + tileX);
            tilePixels.push_back(color);
        }
    }

    return Image(tilePixels, tileSize, tileSize);
}

Image ImageRetiler::retile(Image image, unsigned tileSize) {
    Image newSheet;
    for (unsigned imageY = 0; imageY < image.getHeight(); imageY += tileSize) {
        for (unsigned imageX = 0; imageX < image.getWidth(); imageX += tileSize) {
            Image tile = getTile(image, imageX, imageY, tileSize);
            newSheet.appendToBottom(tile);
        }
    }

    return newSheet;
}