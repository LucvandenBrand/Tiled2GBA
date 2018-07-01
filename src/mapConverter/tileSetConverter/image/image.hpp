#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>
#include <string>
#include <vector>

using namespace std;

typedef struct {
    unsigned char red, green, blue, alpha;
} Color;

const Color BLACK = {0, 0, 0, 1};

class Image {
public:
    Image();
    explicit Image(string path);
    Image(vector<Color> &pixels, unsigned width, unsigned height);

    void resize(unsigned width, unsigned height);
    void appendToBottom(Image image);

    Color getPixel(unsigned row, unsigned col);
    unsigned getWidth();
    unsigned getHeight();
private:
    const unsigned BYTES_PER_PIXEL = 4;
    unsigned d_width, d_height;
    vector<Color> d_pixels;
};

#endif // IMAGE_H