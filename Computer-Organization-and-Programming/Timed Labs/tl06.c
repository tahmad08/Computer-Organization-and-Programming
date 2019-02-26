#include "gba.h"

/**
 * @todo 
 *   Return a pointer to the first pixel of the frame specified by count
 * 
 *   You will offset into the frames array, taking into account the dimension 
 *   of each frame. The frame images are square so the dimension is the width 
 *   which is equivalent to its height.
 */
const u16* getPointerToCurrentFrame(const u16 *frames, int img_dimension, int count)
{
    return (frames + ((img_dimension*img_dimension)*count));
}

/**
 *  @todo
 *   Draw the image, as oriented in its array, starting at the top-left corner
 *   of the videoBuffer with DMA. See the PDF for a diagram.
 *
 *   You MUST use the minimum number of DMA transfers possible.
 */
void drawSquareImage(const u16 *image, int img_dimension)
{

    for(int i = 0; i < img_dimension; i++) {
        DMA[3].src = image + ((i)*img_dimension);
        DMA[3].dst = videoBuffer + (i*240);
        DMA[3].cnt = img_dimension | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT | DMA_ON;
    }
}

/**
 *  @todo
 *   Draw the image, reversing the order of elements in each row but maintaining 
 *   the order of the rows, starting at the top-left corner of the videoBuffer 
 *   with DMA. See the PDF for a diagram.
 *
 *   You MUST use the minimum number of DMA transfers possible.
 */
void drawSquareImageFlippedHorizontal(const u16 *image, int img_dimension)
{
    for(int i = 0; i < img_dimension; i++) {
        DMA[3].src = image + img_dimension * i;
        DMA[3].dst = videoBuffer + (i*WIDTH) + img_dimension-1;
        DMA[3].cnt = img_dimension | DMA_SOURCE_INCREMENT | DMA_DESTINATION_DECREMENT | DMA_ON;
    }
    // for(int i = img_dimension; i >0; i--) {
    //     DMA[3].src = image + ((i)*img_dimension);
    //     DMA[3].dst = videoBuffer + (i*240);
    //     DMA[3].cnt = img_dimension | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT | DMA_ON;
    // }
}

/**
 *  @todo
 *   Draw the image, maintaining the order of elements in each row but reversing 
 *   the order of the rows, starting at the top-left corner of the videoBuffer 
 *   with DMA. See the PDF for a diagram.
 *
 *   You MUST use the minimum number of DMA transfers possible.
 */
void drawSquareImageFlippedVertical(const u16 *image, int img_dimension)
{
    for(int i = img_dimension; i >= 0; i--) {
        DMA[3].src = image + img_dimension * i;
        DMA[3].dst = videoBuffer + ((img_dimension - i) *WIDTH);
        DMA[3].cnt = img_dimension | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT | DMA_ON;
    }
    // UNUSED(image);
    // UNUSED(img_dimension);
}

/**
 *  @todo
 *   Draw the image, both reversing the order of elements in each row and 
 *   reversing the order of the rows, starting at the top-left corner of the 
 *   videoBuffer with DMA. See the PDF for a diagram.
 *
 *   You MUST use the minimum number of DMA transfers possible.
 */
void drawSquareImageFlippedBoth(const u16 *image, int img_dimension)
{
    for(int i = 0; i < img_dimension; i++) {
        DMA[3].src = image + img_dimension * i;
        DMA[3].dst = videoBuffer + (i*WIDTH) + img_dimension-1;
        DMA[3].cnt = img_dimension | DMA_SOURCE_INCREMENT | DMA_DESTINATION_DECREMENT | DMA_ON;
    }
    // UNUSED(image);
    // UNUSED(img_dimension);
}
