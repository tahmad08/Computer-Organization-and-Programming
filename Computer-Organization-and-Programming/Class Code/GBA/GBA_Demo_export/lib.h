#include <stdio.h>
#include "DMA.h"
#include "text.h"

#define REG_DISPCTL *(unsigned short *)0x4000000

#define MODE3 3
#define BG2_ENABLE (1<<10)
#define OFFSET(r, c, rowlen) ((c) + (rowlen)*(r)) 

#define COLOR(r, g, b) ((r) | (g)<<5 | (b)<<10)
#define WHITE COLOR(31, 31, 31)
#define RED COLOR(31, 0,0)
#define GREEN COLOR(0,31,0)
#define BLUE COLOR(0, 0,31)
#define MAGENTA COLOR(31, 0, 31)
#define CYAN COLOR(0, 31, 31)
#define YELLOW COLOR(31, 31, 0)
#define BLACK 0
#define GRAY COLOR(25, 25, 25)

extern unsigned short *videoBuffer;

// Buttons

#define BUTTON_A		(0)
#define BUTTON_B		(1)
#define BUTTON_SELECT	(2)
#define BUTTON_START	(3)
#define BUTTON_RIGHT	(4)
#define BUTTON_LEFT		(5)
#define BUTTON_UP		(6)
#define BUTTON_DOWN		(7)
#define BUTTON_R		(8)
#define BUTTON_L		(9)
#define NBUTTONS		10

#define KEY_DOWN_NOW(key)  (~(BUTTONS) & (1<<key))

#define BUTTONS *(volatile unsigned int *)0x4000130

#define SCANLINECOUNTER *(volatile short *)0x4000006




// Prototypes
void setPixel(int , int , unsigned short );
void drawRect(int row, int col, int height, int width, unsigned short color);
void delay(int n);
void waitForVblank();
int rand();

#define MAXBALLS 8
