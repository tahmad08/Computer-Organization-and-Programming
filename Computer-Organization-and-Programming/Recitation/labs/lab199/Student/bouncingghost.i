# 1 "bouncingghost.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "bouncingghost.c"
# 1 "lib.h" 1
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned char u8;


void waitForVblank(void);
void setPixel(int row, int col, u16 color);

void drawRectangle(int row, int col, int width, int height, u16 color);

void drawGhost(int r, int c, int width, int height, const unsigned short *image);
# 28 "lib.h"
extern volatile unsigned short *videoBuffer;
# 74 "lib.h"
typedef struct
{
 const volatile void *src;
 const volatile void *dst;
 u32 cnt;
} DMA_CONTROLLER;
# 2 "bouncingghost.c" 2
# 1 "ghost.h" 1
# 16 "ghost.h"
extern const unsigned short ghost[3360];
# 3 "bouncingghost.c" 2

volatile unsigned short *videoBuffer = (volatile unsigned short *)0x6000000;

int main(void) {

 *(volatile unsigned short *) 0x4000000 = 3 | (1<<10);

 int row = 0;
 int col = 0;


 while(1) {
  int oldRow = row;
  int oldCol = col;
  if ((~((*(volatile unsigned int *)0x4000130)) & (1<<4))) {
         col++;
     }
     if ((~((*(volatile unsigned int *)0x4000130)) & (1<<5))) {
         col--;
     }
     if ((~((*(volatile unsigned int *)0x4000130)) & (1<<6))) {
         row--;
     }
     if ((~((*(volatile unsigned int *)0x4000130)) & (1<<7))) {
         row++;
     }


  waitForVblank();
  drawRectangle(oldRow, oldCol, 56, 60, 0);

  drawGhost(row, col, 56, 60, ghost);
# 51 "bouncingghost.c"
 }

}



void setPixel(int row, int col, u16 color)
{
 videoBuffer[row*240 + col] = color;
}

void drawRectangle(int row, int col, int width, int height, u16 color)
{
 for (int x = 0; x < height; x++) {
     for (int y = 0; y < width; y++) {
      setPixel(row + x, col + y, color);
  }
    }
}

void waitForVblank(void) {
   while (*(volatile unsigned short *)0x4000006 > 160);
   while (*(volatile unsigned short *)0x4000006 < 160);
}


void drawGhost(int r, int c, int width, int height, const unsigned short *image) {
 for (int x = 0; x < height; x++) {
  ((volatile DMA_CONTROLLER *) 0x040000B0)[3].src = image + ((0)+(width)*(x));
  ((volatile DMA_CONTROLLER *) 0x040000B0)[3].dst = videoBuffer + ((c)+(240)*(x+r));
  ((volatile DMA_CONTROLLER *) 0x040000B0)[3].cnt = width | (1 << 31) | (0 << 21) | (0 << 23);
 }
}
