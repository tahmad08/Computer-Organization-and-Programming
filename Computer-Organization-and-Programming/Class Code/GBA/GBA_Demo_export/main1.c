#define REG_DISPCTL *(unsigned short *)0x4000000
#define MODE3 3
#define BG2_ENABLE (1<<10)

unsigned short *videoBuffer = (unsigned short *)0x6000000;



int main() {
	REG_DISPCTL = MODE3 | BG2_ENABLE;

	videoBuffer[1208] = 0x7fff;

	while(1)
		;

}

