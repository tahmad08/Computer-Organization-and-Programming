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




// Prototypes
void setPixel(int , int , unsigned short );
void drawRect(int row, int col, int height, int width, unsigned short color);

int main() {
	REG_DISPCTL = MODE3 | BG2_ENABLE;

	int row = 80;
	int col = 120;
	int size = 5;
	unsigned short color = RED;

	drawRect(row, col, size, size, color);

	while(1)
		;

}
// setPixel -- set the pixel at (row, col) to color
void setPixel(int row, int col, unsigned short color) {
	videoBuffer[OFFSET(row, col, 240)] = color;
}

// drawRect — draw a rectangle 
void drawRect(int row, int col, int height, int width, unsigned short color) {
	for(int r=0; r<height; r++) {
		for(int c = 0; c<width; c++) {
			setPixel(row+r, col+c, color);
		}
	}
}
