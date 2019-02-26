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

#define SCANLINECOUNTER *(volatile short *)0x4000006




// Prototypes
void setPixel(int , int , unsigned short );
void drawRect(int row, int col, int height, int width, unsigned short color);
void delay(int n);
void waitForVblank();

int main() {
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	//*(OFFSET(80, 120, 240) +videoBuffer ) = YELLOW; 
	//videoBuffer[OFFSET(80, 120, 240)] = YELLOW;
	//drawRect(10, 20, 30, 40, GREEN);
	int row = 80;
	int col = 120;
	int rd = 1;
	int cd = 1;
	int size = 5;
	unsigned short color = RED;
	while(1) { // Game Loop
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
