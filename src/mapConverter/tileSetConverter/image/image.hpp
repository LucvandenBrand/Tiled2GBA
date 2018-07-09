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

/**
 * Contains image data and related image operations.
 */
class Image {
public:
    /**
     * Construct an empty image of size 0x0.
     */
    Image();

    /**
     * Copy constructor.
     * @param otherImage The image to copy.
     */
    Image(const Image& otherImage);

    /**
     * Construct an image from an image on disk.
     * @param path The location of the image on the disk.
     */
    explicit Image(string path);

    /**
     * Construct a new image out of a collection of Color values.
     * @param pixels The Color values.
     * @param width The width of the image.
     * @param height The height of the image.
     */
    Image(vector<Color> &pixels, unsigned width, unsigned height);

    /**
     * Assign operator.
     * @param otherImage The image to assign to this image.
     * @return This image.
     */
    Image& operator= (const Image & otherImage);

    /**
     * Change the dimensions of this image.
     * Any size outside the boundaries will become black (0).
     * @param width The new width.
     * @param height The new height.
     */
    void resize(unsigned width, unsigned height);

    /**
     * Append an image to the bottom of this image.
     * This operation might resize the image depending on the appended image.
     * @param image The image to append.
     */
    void appendToBottom(Image image);

    /**
     * Return the Color at (row, col).
     * @param row The row (y) from the top of the image.
     * @param col The colum (x) from the left of the image.
     * @return Color of the pixel.
     */
    Color getPixel(unsigned row, unsigned col);

    /**
     * Return the width of the image.
     * @return The width.
     */
    unsigned getWidth();

    /**
     * Return the height of the image.
     * @return The height.
     */
    unsigned getHeight();

private:
    unsigned d_width, d_height;
    vector<Color> d_pixels;
};

#endif // IMAGE_H