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

#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)

#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)

#define BUTTONS *(volatile unsigned int *)0x4000130

#define SCANLINECOUNTER *(volatile short *)0x4000006




// Prototypes
void setPixel(int , int , unsigned short );
void drawRect(int row, int col, int height, int width, unsigned short color);
void delay(int n);
void waitForVblank();

int main() {
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	int row = 80;
	int col = 120;
	int rd = 1;
	int cd = 1;
	int size = 5;
	unsigned short color = RED;
	while(1) { // Game Loop
		if(KEY_DOWN_NOW(BUTTON_UP)) {
			size++;
			if(size>150) {
				size = 150;
			}
		}
		if(KEY_DOWN_NOW(BUTTON_DOWN)) {
			size--;
			if(size<3) {
				size = 3;
			}
		}
		row = row + rd;
		col += cd;
		if(row < 0) {
			row = 0;
			rd = -rd;
		}
		if(row > 159-size+1) {
			row = 159-size+1;
			rd = -rd;
		}
		if(col < 0) {
			col = 0;
			cd = -cd;
		}
		if(col > 239-size+1) {
			col = 239-size+1;
			cd = -cd;
		}
		drawRect(row, col, size, size, color);
		waitForVblank();
		drawRect(row, col, size, size, BLACK);

	} // Game Loop


}
// setPixel -- set the pixel at (row, col) to color
void setPixel(int row, int col, unsigned short color) {
	videoBuffer[OFFSET(row, col, 240)] = color;
}

// drawRect -- draw a rectangle on the screen
void drawRect(int row, int col, int height, int width, unsigned short color) {
        for (int r = 0; r < height; r++) {
                for (int c = 0; c < width; c++) {
                        setPixel(row + r, col + c, color);
                }
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

