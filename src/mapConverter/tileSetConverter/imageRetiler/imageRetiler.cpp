#include "imageRetiler.hpp"

Image ImageRetiler::getTile(Image image, unsigned imageX, unsigned imageY, unsigned tileWidth, unsigned tileHeight) {
    vector<Color> tilePixels;
    tilePixels.reserve(tileWidth * tileHeight);
    for (unsigned tileY = 0; tileY < tileHeight; tileY ++) {
        for (unsigned tileX = 0; tileX < tileWidth; tileX++) {
            Color color = image.getPixel(imageY + tileY, imageX + tileX);
            tilePixels.push_back(color);
        }
    }

    return Image(tilePixels, tileWidth, tileHeight);
}

Image ImageRetiler::retile(Image image, unsigned tileWidth, unsigned tileHeight) {
    Image newSheet;
    for (unsigned imageY = 0; imageY < image.getHeight(); imageY += tileHeight) {
        for (unsigned imageX = 0; imageX < image.getWidth(); imageX += tileWidth) {
            Image tile = getTile(image, imageX, imageY, tileWidth, tileHeight);
            newSheet.appendToBottom(tile);
        }
    }
    return newSheet;
}