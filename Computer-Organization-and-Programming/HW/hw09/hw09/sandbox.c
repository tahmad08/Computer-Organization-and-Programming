#include <stdlib.h>
#include "graphics.h"
#include "tester/qdbmp.h"
#include "images/azul.h"

#define RED ((Pixel) 0x1F)
#define BLUE ((Pixel) 0x7C00)
#define GREEN ((Pixel) 0x3E0)
#define YELLOW ((Pixel) 0x3FF)
#define BLACK ((Pixel) 0x0)
#define WHITE ((Pixel) 0x7FFF)

void save_buffer(char* filename, Pixel *buffer, unsigned int width,
                   unsigned int height) {
    BMP* bmp = BMP_Create(width, height, 24);
    Pixel pixel;
    uint8_t r, g, b;

    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            pixel = buffer[y * width + x];
            r = ((pixel) & 0x1F) * 255 / 31;
            g = ((pixel >> 5) & 0x1F) * 255 / 31;
            b = ((pixel >> 10) & 0x1F) * 255 / 31;
            BMP_SetPixelRGB(bmp, x, y, r, g, b);
        }
    }

    BMP_WriteFile(bmp, filename);
    BMP_Free(bmp);
}

int main(void) {
    unsigned int width = 240;
    unsigned int height = 160;

    // Create a buffer that can visualize overflow / underflow
    unsigned int margin = 10;
    unsigned int buffer_width = width;
    unsigned int buffer_height = height + (2 * margin);
    unsigned int buffer_size = buffer_width * buffer_height;
    Pixel fake_buffer[buffer_size];

    // Wipe the buffer
    for (unsigned int i = 0; i < buffer_size; i++) {
        fake_buffer[i] = WHITE;
    }

    // Draw a frame outside the actual display
    for (unsigned int i = 0; i < buffer_width; i++) {
        fake_buffer[(margin - 1) * buffer_width + i] = BLACK;
        fake_buffer[(margin + height) * buffer_width + i] = BLACK;
    }

    // Get a pointer to the actual location of the display
    Pixel* buffer = fake_buffer + (margin * buffer_width);
    Screen screen = {{width, height}, buffer};

    //
    // YOU CAN EDIT THE PART AFTER THIS TO TEST YOUR WORK
    // YOU SHOULD ONLY USE THE `screen` VARIABLE FROM ABOVE, NOTHING ELSE
    //

    // Uncomment the following for circles
    /*Vector p = {120, 80};
    Circle c = {p, 10, RED};
    drawCircle(&screen, &c);*/

    // Uncomment the following for an Image
    Vector topleft = {0,0};
    Vector size = {AZUL_WIDTH, AZUL_HEIGHT};
    Image image = {topleft, size, azul};
    Image rotated = rotateImage(&image, 90);
    drawImage(&screen, &rotated, noFilter);

    // Uncomment the following for a line
    /*Vector start = {10, 10};
    Vector end = {200, 60};
    Line l = {start, end, BLACK};
    drawLine(&screen, &l);*/

    //
    // DON'T TOUCH THE CODE AFTER THIS - THIS IS WHAT OUTPUTS YOUR IMAGE
    //
    save_buffer("output.bmp", fake_buffer, buffer_width, buffer_height);

    return 0;
}
