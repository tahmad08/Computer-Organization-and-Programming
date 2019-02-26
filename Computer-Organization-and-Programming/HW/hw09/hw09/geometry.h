/**
* @file geometry.h
* @author Cem Gokmen
* @date March 5, 2018
* @brief A geometry library describing a variety of geometric objects we expect
*        in drawings.
*/

// The stdint library contains the uint16_t type, which is an unsigned 16-bit
// integer that we typedef as a Pixel.
#include <stdint.h>

// We are typedefing an unsigned 16-bit integer as our Pixel type. Your code
// should use ONLY this type for reading and writing Pixels, so that if this
// typedef is changed to an 32-bit int on a system that supports deeper color,
// your code still performs accurately.
typedef uint16_t Pixel;

// The Vector struct is simply a pair of int x,y coordinates: a named
// tuple if you're thinking in Python.
typedef struct {
    int x, y;
} Vector;

// The Screen struct contains all information about a screen that you can draw
// on.
typedef struct {
    Vector size; // size of the screen: width in the x field, height in the y
    Pixel* buffer; // the video buffer / pixel array to write onto
} Screen;

// The Circle struct contains all information about a circle that you can draw.
// We will draw filled and unfilled circles.
typedef struct {
    Vector center; // coordinates (width, height) of the center of the circle
    int radius; // radius of the circle
    Pixel color; // the color of the circle
} Circle;

// The Line struct contains all information about a line that you can draw.
typedef struct {
    Vector start; // the coordinates of the starting point of the line
    Vector end; // the coordinates of the endpoint of the line
    Pixel color; // the color of the line
} Line;

// The Rectangle struct contains all information about a rectangle that you can draw. We will draw filled and unfilled rectangles.
typedef struct {
    Vector top_left; // the coordinates of the top left vertex of the rectangle
    Vector size; // the size of the rectangle (width, height)
    Pixel color; // the fill color of the rectangle
} Rectangle;

// The Polygon struct contains all information about a polygon you can draw.
typedef struct {
    Vector* vertices; // a pointer to an array of vertices
    int num_vertices; // number of elements in the vertex array
    Pixel color; // the color of the polygon perimeter
} Polygon;

// The Image struct contains all information about an image that you can draw.
typedef struct {
    Vector top_left; // the coordinates of the top left vertex of the rectangle
    Vector size; // the size of the original image (width, height)
    Pixel* buffer; // the pixel array to read the image pixels from
} Image;
