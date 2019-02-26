#define REG_DISPCTL *(unsigned short *)0x4000000
#define MODE3 3
#define BG2_ENABLE (1<<10)

#define OFFSET(r, c, rowlen) ((c) + (rowlen)*(r)) 

unsigned short *videoBuffer = (unsigned short *)0x6000000;




// Prototypes
void setPixel(int , int , unsigned short );

int main() {
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	int row = 80;
	int col = 120;

	setPixel(row, col, 0x7fff);

	while(1)
		;

}
// setPixel -- set the pixel at (row, col) to color
void setPixel(int row, int col, unsigned short color) {
	videoBuffer[OFFSET(row, col, 240)] = color;
}

