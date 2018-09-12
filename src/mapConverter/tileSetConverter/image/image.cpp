#include "image.hpp"
#include "../../../lib/lodepng/lodepng.h"
#include <stdexcept>

Image::Image() : d_width(0), d_height(0) {}

Image::Image(const Image& otherImage) {
    d_width = otherImage.d_width;
    d_height = otherImage.d_height;
    d_pixels = otherImage.d_pixels;
}

Image& Image::operator= (const Image & otherImage) {
    d_width = otherImage.d_width;
    d_height = otherImage.d_height;
    d_pixels = otherImage.d_pixels;

    return *this;
}

Image::Image(string path) {
    vector<unsigned char> imageData;
    unsigned error = lodepng::decode(imageData, d_width, d_height, path);

    if (error)
        throw  runtime_error("Tile set image decoding error " + to_string(error) + ": " + lodepng_error_text(error));

    d_pixels.reserve(d_width * d_height);
    for (unsigned index = 0; index < imageData.size(); index += 4) {
        Color color = BLACK;
        color.red   = imageData[index];
        color.green = imageData[index + 1];
        color.blue  = imageData[index + 2];
        color.alpha = imageData[index + 3];
        d_pixels.push_back(color);
    }
}

Image::Image(vector<Color> &pixels, unsigned width, unsigned height) :
        d_pixels(pixels),
        d_width(width),
        d_height(height) {
}

void Image::resize(unsigned width, unsigned height) {
    vector<Color> newPixels;
    newPixels.reserve(width * height);
    for (unsigned row = 0; row < width; row++) {
        for (unsigned col = 0; col < height; col++) {
            newPixels.push_back(getPixel(row, col));
        }
    }

    d_pixels = newPixels;
    d_width = width;
    d_height = height;
}

void Image::appendToBottom(Image image) {
    if (image.getWidth() > d_width)
        resize(image.getWidth(), d_height);
    else if (image.getWidth() < d_width)
        image.resize(d_width, image.getHeight());

    d_pixels.insert(d_pixels.end(), image.d_pixels.begin(), image.d_pixels.end());
    d_height += image.getHeight();
}

Color Image::getPixel(unsigned row, unsigned col) {
    if (row >= d_height || col >= d_width)
        return BLACK;

    unsigned index = row * d_width + col;
    return d_pixels[index];
}

unsigned Image::getWidth() {
    return d_width;
}

unsigned Image::getHeight() {
    return d_height;
}