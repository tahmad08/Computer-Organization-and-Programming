#include "DMA.h"

#define REG_DISPCTL *(unsigned short *)0x4000000

#define MODE3 3
#define BG2_ENABLE (1<<10)
#define OFFSET(r, c, rowlen) ((c) + (rowlen)*(r)) 
#define COLOR(r, g, b) ((r) | (g)<<5 | (b)<<10)
#define WHITE COLOR(31,31,31)
#define RED COLOR(31, 0,0)
#define GREEN COLOR(0,31,0)
#define BLUE COLOR(0,0,31)
#define MAGENTA COLOR(31, 0, 31)
#define CYAN COLOR(0, 31, 31)
#define YELLOW COLOR(31, 31, 0)
#define BLACK 0

unsigned short *videoBuffer = (unsigned short *)0x6000000;

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

int main() {
	REG_DISPCTL = MODE3 | BG2_ENABLE;

	int deltas[] = { -3, -2, -1, 1, 2, 3 };
        int ndeltas = sizeof(deltas) / sizeof(deltas[0]);
        unsigned short colors[] = {RED, BLUE, GREEN, WHITE, CYAN, YELLOW, MAGENTA};
        int ncolors = sizeof(colors) / sizeof(colors[0]);

	int buttondown[NBUTTONS] = {0};
	int button[NBUTTONS] = {0};


        struct ball {
                int row;
                int col;
                int rd;
                int cd;
                unsigned short color;
        };

        struct state {
                int size;
                int nballs;
                struct ball balls[MAXBALLS];
        } state[2];

        state[0].size = 5;
        state[0].nballs = MAXBALLS;
        for (int i = 0; i < MAXBALLS; i++) {
                state[0].balls[i].row = rand() % 160;
                state[0].balls[i].col = rand() % 240;
                state[0].balls[i].rd = deltas[rand() % ndeltas];
                state[0].balls[i].cd = deltas[rand() % ndeltas];
                state[0].balls[i].color = colors[i % ncolors];
        }


        while(1) {
                // Save the previous state
                state[1] = state[0];

		// See what's changed and update current input stat 
                for (int i = 0; i < NBUTTONS; i++) {
			button[i] = KEY_DOWN_NOW(i) == 0 && buttondown[i];
			buttondown[i] = KEY_DOWN_NOW(i) != 0;
		}


                // Compute the graphics for the current state
                if (button[BUTTON_UP]) {
                        state[0].size++;
                        if (state[0].size > 20)
                                state[0].size = 20;
                }
                if (button[BUTTON_DOWN]) {
                        state[0].size--;
                        if (state[0].size < 1)
                                state[0].size = 1;
                }

                for (int i = 0; i < state[0].nballs; i++) {
                        struct ball *bp = &state[0].balls[i];
                        bp->row += bp->rd;
                        bp->col += bp->cd;
                        if (bp->row < 0) {
                                bp->row = 0;
                                bp->rd = -bp->rd;
                        }
                        if (bp->row > 159 - state[0].size + 1) {
                                bp->row = 159 - state[0].size + 1;
                                bp->rd = -bp->rd;
                        }
                        if (bp->col < 0) {
                                bp->col = 0;
                                bp->cd = -bp->cd;
                        }
                        if (bp->col > 239 - state[0].size + 1) {
                                bp->col = 239 - state[0].size + 1;
                                bp->cd = -bp->cd;
                        }
                }

                waitForVblank();

                // Erase graphics from previous state
                for (int i = 0; i < state[1].nballs; i++) {
                        drawRect(state[1].balls[i].row, state[1].balls[i].col,
                                        state[1].size, state[1].size, BLACK);
                }

                // Draw graphics for the current state
                for (int i = 0; i < state[0].nballs; i++) {
                        drawRect(state[0].balls[i].row, state[0].balls[i].col,
                                        state[0].size, state[0].size,
                                        state[0].balls[i].color);
                }
        }
}

// setPixel -- set the pixel at (row, col) to color
void setPixel(int row, int col, unsigned short color) {
	videoBuffer[OFFSET(row, col, 240)] = color;
}

// drawRect -- draw a rectangle on the screen
void drawRect(int row, int col, int height, int width, unsigned short color) {
        for (int r = 0; r < height; r++) {
        //        for (int c = 0; c < width; c++) {
        //                setPixel(row + r, col + c, color);
        //        }
		DMA[3].src = &color;
		DMA[3].dst = &videoBuffer[OFFSET(row + r, col, 240)];
		DMA[3].cnt = width | DMA_ON | DMA_SOURCE_FIXED;
        }

}


// Delay for about n tenths of a second
void delay(int n) {
        volatile int x = 0;
        for (int i = 0; i < n * 8000; i++) {
                x++;
        }
}



void waitForVblank() {
        while(SCANLINECOUNTER > 160)
                ;
        while(SCANLINECOUNTER < 160)
                ;
}
